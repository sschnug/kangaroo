/*!
	@file evalrec.tcc
	@brief The source file for EvalRec template class.
	@details This is the source file for EvalRec template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef EvalRecTccIncluded
#define EvalRecTccIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace


/*!
	@class EvalRec
	@brief A class to represent eval records.
	@details This is a class to represent eval records.
*/
template <typename dat>
class EvalRec
{
	public:
		EvalRec();													//!< Constructor.
		~EvalRec();													//!< Destructor.
		EvalRec(EvalRec<dat> const & that);							//!< Duplicator.
		EvalRec<dat> const & operator = (EvalRec<dat> const & that);//!< Assigner.

		void finalise(dat const & theDat);							//!< Finalise the record.
		void initCurr(dat const & theDat);							//!< Initialise the current buffer.
		void initNext(Clk const simulClk, dat const & theDat);		//!< Initialise the next buffer.
		void updtCurr(Clk const execClk, dat const & theDat);		//!< Update the current buffer.
		void updtNext(Clk const simulClk, dat const & theDat);		//!< Update the next buffer.

		#if CompLazy
		void initLate(Clk const emulClk, dat const & theDat);		//!< Initialise the late buffer
		void updtLate(Clk const emulClk, dat const & theDat);		//!< Update the late buffer.
		#endif // CompLazy

		//! @name Modifications
		//! @{

		void copytoPrevBuff();										//!< Copy to prev buff.
		void copytoNextBuff();										//!< Copy to next buff.
		void resetNextDiff();										//!< Reset next diff.
		void resetPrevDiff();										//!< Reset prev diff.

		#if CompLazy
		void copytoLateBuff();										//!< Copy to late buff.
		void resetLateDiff();										//!< Reset late diff.
		void resetLtNxDiff();										//!< Reset late next diff.
		#endif // CompLazy

		void determPrevDiff(Clk const execClk);						//!< Determine prev diff.
		void determNextDiff(Clk const simulClk);					//!< Determine next diff.

		#if CompLazy
		void determLateDiff(Clk const emulClk);						//!< Determine late diff.
		#endif // CompLazy

		//! @}

		//! @name Data
		//! @{

		dat const & CurrData() const;								//!< Return curr data = curr buff.
		Bll PrevDiff(Clk const execClk) const;						//!< PrevDiff = PrevClk == execClk.
		Bll NextDiff(Clk const simulClk) const;						//!< NextDiff = NextClk == simulClk.
		dat const & PrevData(Clk const execClk) const;				//!< PrevDiff ? PrevBuff : CurrBuff.
		dat const & NextData(Clk const simulClk) const;				//!< NextDiff ? NextBuff : CurrBuff.

		#if CompLazy
		dat const & LateData(Clk const emulClk) const;				//!< LateDiff ? LateBuff : CurrBuff.
		Bll LateDiff(Clk const emulClk) const;						//!< LateDiff = LateClk == emulClk.
		Bll LtNxDiff(Clk const emulClk, Clk const simulClk) const;	//!< LtNxDiff = NextData() != LateData().
		#endif // CompLazy

		//! @name Synchronisation
		//! @{

		void syncExecClk();		//!< Synchronise the execution clock.
		void syncSimulClk();	//!< Synchronise the simulation clock.

		//! @}

	public:

		dat PrevBuff;			//!< PrevBuff is valid only at PrevClk.
		dat CurrBuff;			//!< CurrBuff is valid after initialisation.
		dat NextBuff;			//!< NextBuff is valid only at NextClk.
		Clk PrevClk;			//!< PrevClk determines validity of PrevBuff.
		Clk NextClk;			//!< NextClk determines validity of NextBuff.

		#if CompLazy
		dat LateBuff;			//!< LateBuff is valid only at LateClk.
		Clk LateClk;			//!< LateClk determines validity of LateBuff.
		#endif // CompLazy

	private:

		#if CompLazy
		Bll LtNxBuff;			//!< LtNxBuff is valid only at LtNxClk;
		Clk LtNxClk;			//!< LtNxClk != simulClk => NextData() != LateData().
		#endif // CompLazy
};



/*!
	The constructor.
*/
template <typename dat>
inline EvalRec<dat>::EvalRec() : PrevBuff(), CurrBuff(), NextBuff(),
		PrevClk(NotClk), NextClk(NotClk)
		#if CompLazy
		, LateBuff(), LateClk(NotClk), LtNxBuff(), LtNxClk(NotClk)
		#endif
{
	WatchError
	//	Nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
template <typename dat>
inline EvalRec<dat>::~EvalRec()
{
	WatchError
	//	Nothing to be done.
	CatchError
}




/*!
	The duplicator.
*/
template <typename dat>
inline EvalRec<dat>::EvalRec(EvalRec<dat> const & that) : PrevBuff(that.PrevBuff),
		CurrBuff(that.CurrBuff), NextBuff(that.NextBuff), PrevClk(that.PrevClk),
		NextClk(that.NextClk)
		#if CompLazy
		, LateBuff(that.LateBuff), LateClk(that.LateClk), LtNxBuff(that.LtNxBuff),
		LtNxClk(that.LtNxClk)
		#endif
{
	WatchError
	//	Nothing to be done.
	CatchError
}




/*!
	The assigner.
*/
template <typename dat>
inline EvalRec<dat> const & EvalRec<dat>::operator = (EvalRec<dat> const & that)
{
	WatchError
	if (this == &that) return *this;
	PrevBuff = that.PrevBuff;
	CurrBuff = that.CurrBuff;
	NextBuff = that.NextBuff;
	PrevClk = that.PrevClk;
	NextClk = that.NextClk;
	#if CompLazy
	LateBuff = that.LateBuff;
	LateClk = that.LateClk;
	LtNxBuff = that.LtNxBuff;
	LtNxClk = that.LtNxClk;
	#endif
	return *this;
	CatchError
}




/*!
	Synchronise the execution clock.
*/
template<typename dat>
inline void EvalRec<dat>::syncExecClk()
{
	WatchError
	if (PrevClk < InvClk) PrevClk = NotClk;
	#if CompLazy
	if (LateClk < InvClk) LateClk = NotClk;
	#endif // CompLazy
	CatchError
}



/*!
	Synchronise the simulation clock.
*/
template<typename dat>
inline void EvalRec<dat>::syncSimulClk()
{
	WatchError
	if (NextClk < InvClk) NextClk = NotClk;
	#if CompLazy
	if (LtNxClk < InvClk) LtNxClk = NotClk;
	#endif // CompLazy
	CatchError
}



/*!
	Perform finalisation of the field.
*/
template<typename dat>
inline void EvalRec<dat>::finalise(dat const & theDat)
{
	WatchError
	CurrBuff = theDat;
	PrevClk = NextClk = EtrClk;
	#if CompLazy
	LtNxBuff = false;
	LateClk = LtNxClk = EtrClk;
	#endif // CompLazy
	CatchError
}



/*!
	Perform curr buffer initialisation.
*/
template<typename dat>
inline void EvalRec<dat>::initCurr(dat const & theDat)
{
	WatchError
	CurrBuff = theDat;
	PrevClk = NotClk;
	CatchError
}



/*!
	Perform curr data update.
*/
template<typename dat>
inline void EvalRec<dat>::updtCurr(Clk const execClk, dat const & theDat)
{
	WatchError
	Warn(execClk < PrevClk, eClockConflict);

	if (eq<dat,Bll>::iof(CurrBuff, theDat))
		PrevClk = NotClk;
	else
	{
		PrevClk = execClk;
		PrevBuff = CurrBuff;
		CurrBuff = theDat;
	}
	CatchError
}


/*!
	Perform next data initialisation.
*/
template<typename dat>
inline void EvalRec<dat>::initNext(Clk const simulClk, dat const & theDat)
{
	WatchError
	Warn(simulClk < NextClk, eClockConflict);

	NextBuff = theDat;
	if (eq<dat,Bll>::iof(NextBuff, CurrBuff))
		NextClk = NotClk;
	else
		NextClk = simulClk;
	CatchError
}



/*!
	Perform next data update.
*/
template<typename dat>
inline void EvalRec<dat>::updtNext(Clk const simulClk, dat const & theDat)
{
	WatchError
	Warn(simulClk < NextClk, eClockConflict);

	if (eq<dat,Bll>::iof(CurrBuff, theDat))
		NextClk = NotClk;
	else
	{
		NextClk = simulClk;
		NextBuff = theDat;
	}
	CatchError
}




#if CompLazy
/*!
	Perform late data initialisation.
*/
template<typename dat>
inline void EvalRec<dat>::initLate(Clk const emulClk, dat const & theDat)
{
	WatchError
	Warn(emulClk < LateClk, eClockConflict);

	LateBuff = theDat;
	if (eq<dat,Bll>::iof(LateBuff, CurrBuff))
		LateClk = NotClk;
	else
		LateClk = emulClk;
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	Perform late data update.
*/
template<typename dat>
inline void EvalRec<dat>::updtLate(Clk const emulClk, dat const & theDat)
{
	WatchError
	Warn(emulClk < LateClk, eClockConflict);

	if (eq<dat,Bll>::iof(CurrBuff, theDat))
		LateClk = NotClk;
	else
	{
		LateClk = emulClk;
		LateBuff = theDat;
	}
	CatchError
}
#endif	//CompLazy


/*!
	Copy curr buff to prev buff.
*/
template<typename dat>
inline void EvalRec<dat>::copytoPrevBuff()
{
	WatchError
	PrevBuff = CurrBuff;
	CatchError
}



/*!
	Copy curr buff to next buff.
*/
template<typename dat>
inline void EvalRec<dat>::copytoNextBuff()
{
	WatchError
	NextBuff = CurrBuff;
	CatchError
}



#if CompLazy
/*!
	Copy curr buff to late buff.
*/
template<typename dat>
inline void EvalRec<dat>::copytoLateBuff()
{
	WatchError
	LateBuff = CurrBuff;
	CatchError
}
#endif // CompLazy



/*!
	Reset prev diff to false.
*/
template<typename dat>
inline void EvalRec<dat>::resetPrevDiff()
{
	WatchError
	PrevClk = NotClk;
	CatchError
}



/*!
	Reset next diff to false.
*/
template<typename dat>
inline void EvalRec<dat>::resetNextDiff()
{
	WatchError
	NextClk = NotClk;
	CatchError
}



#if CompLazy
/*!
	Reset late diff to false.
*/
template<typename dat>
inline void EvalRec<dat>::resetLateDiff()
{
	WatchError
	LateClk = NotClk;
	CatchError
}
#endif // CompLazy


#if CompLazy
/*!
	Reset late next diff to false.
*/
template<typename dat>
inline void EvalRec<dat>::resetLtNxDiff()
{
	WatchError
	LtNxClk = NotClk;
	CatchError
}
#endif // CompLazy


/*!
	Determine prev diff again.
*/
template<typename dat>
inline void EvalRec<dat>::determPrevDiff(Clk const execClk)
{
	WatchError
	Warn(execClk < PrevClk, eClockConflict);

	PrevClk = (ne<dat,Bll>::iof(PrevBuff, CurrBuff) ? execClk : NotClk);
	CatchError
}



/*!
	Determine next diff again.
*/
template<typename dat>
inline void EvalRec<dat>::determNextDiff(Clk const simulClk)
{
	WatchError
	Warn(simulClk < NextClk, eClockConflict);

	NextClk = (ne<dat,Bll>::iof(NextBuff, CurrBuff) ? simulClk : NotClk);
	CatchError
}



#if CompLazy
/*!
	Determine late diff again.
*/
template<typename dat>
inline void EvalRec<dat>::determLateDiff(Clk const emulClk)
{
	WatchError
	Warn(emulClk < LateClk, eClockConflict);

	LateClk = (ne<dat,Bll>::iof(LateBuff, CurrBuff) ? emulClk : NotClk);
	CatchError
}
#endif // CompLazy



/*!
	Return curr data.
*/
template<typename dat>
inline dat const & EvalRec<dat>::CurrData() const
{
	WatchError
	return CurrBuff;
	CatchError
}



/*!
	Return next data from PrevBuff or CurrBuff.
*/
template<typename dat>
inline dat const & EvalRec<dat>::PrevData(Clk const execClk) const
{
	WatchError
	return PrevClk == execClk ? PrevBuff : CurrBuff;
	CatchError
}



#if CompLazy
/*!
	Return late data from LateBuff or CurrBuff.
*/
template<typename dat>
inline dat const & EvalRec<dat>::LateData(Clk const emulClk) const
{
	WatchError
	return LateClk == emulClk ? LateBuff : CurrBuff;
	CatchError
}
#endif	//CompLazy


/*!
	Return next data from NextBuff or CurrBuff.
*/
template<typename dat>
inline dat const & EvalRec<dat>::NextData(Clk const simulClk) const
{
	WatchError
	return NextClk == simulClk ? NextBuff : CurrBuff;
	CatchError
}


/*!
	PrevDiff = PrevBuff holds value.
*/
template<typename dat>
inline Bll EvalRec<dat>::PrevDiff(Clk const execClk) const
{
	WatchError
	return PrevClk == execClk;
	CatchError
}


/*!
	NextDiff = NextBuff holds value.
*/
template<typename dat>
inline Bll EvalRec<dat>::NextDiff(Clk const simulClk) const
{
	WatchError
	return NextClk == simulClk;
	CatchError
}



#if CompLazy
/*!
	LateDiff = LateBuff holds value.
*/
template<typename dat>
inline Bll EvalRec<dat>::LateDiff(Clk const emulClk) const
{
	WatchError
	return LateClk == emulClk;
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	LtNxDiff = NextData and LateData are different. This method internally mutates.
*/
template<typename dat>
inline Bll EvalRec<dat>::LtNxDiff(Clk const emulClk, Clk const simulClk) const
{
	WatchError
	if (LtNxClk < simulClk)
	{
		ccast<Bll &>(LtNxBuff) = ne<dat,Bll>::iof(NextData(simulClk), LateData(emulClk));
		ccast<Clk &>(LtNxClk) = simulClk;
	}
	return LtNxBuff;
	CatchError
}
#endif	//CompLazy



closeKangarooSpace



#endif//EvalRecTccIncluded
