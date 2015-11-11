/*!
	@file hintfld.tcc
	@brief The source file for HintFld template class.
	@details This is the source file for HintFld template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef HintFldTccIncluded
#define HintFldTccIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace


/*!
	@class HintFld
	@brief A class to represent hint flds.
	@details This is a class to represent hint flds.
*/
template <typename dat>
class HintFld
{
	public:
		HintFld();													//! Constructor.
		~HintFld();													//!< Destructor.
		HintFld(HintFld const & that);								//!< Duplicator.
		HintFld const & operator = (HintFld const & that);			//!< Assigner.

		void finalise(dat const & theDat);							//!< Finalise the field
		void initCurr(dat const & theDat);							//!< Initialise the current buffer.
		Bll updtCurr(Clk const execClk, dat const & theDat);		//!< Update the current buffer.

		//! @name Modification
		//! @{

		void copytoPrevBuff();										//!< Copy to prev buff.
		void resetPrevDiff();										//!< Reset prev diff.
		Bll determPrevDiff(Clk const execClk);						//!< Determine prev diff.

		//! @}

		//! @name Data
		//! @{

		dat const & CurrData() const;								//!< Return curr data = curr buff.
		Bll PrevDiff(Clk const execClk) const;						//!< PrevDiff = PrevClk == execClk.
		dat const & PrevData(Clk const execClk) const;				//!< PrevDiff ? PrevBuff : CurrBuff.

		//! @}

		//! @name Synchronisation
		//! @{

		void syncExecClk();											//!< Synchronise.

		//! @}

	public:

		dat PrevBuff;												//!< Prev data when PrevDiff.
		dat CurrBuff;												//!< Curr data after init.
		Clk PrevClk;												//!< PrevClk == execClk ? PrevBuff : CurrBuff.
};



/*!
	The constructor.
*/
template <typename dat>
inline HintFld<dat>::HintFld() : PrevBuff(), CurrBuff(), PrevClk(NotClk)
{
	WatchError
	//	Nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
template <typename dat>
inline HintFld<dat>::~HintFld()
{
	WatchError
	//	Nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
template <typename dat>
inline HintFld<dat>::HintFld(HintFld<dat> const & that) : PrevBuff(that.PrevBuff),
		CurrBuff(that.CurrBuff), PrevClk(that.PrevClk)
{
	WatchError
	//	Nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
template <typename dat>
inline HintFld<dat> const & HintFld<dat>::operator = (HintFld<dat> const & that)
{
	WatchError
	if (this == &that) return *this;
	PrevBuff = that.PrevBuff;
	CurrBuff = that.CurrBuff;
	PrevClk = that.PrevClk;
	return *this;
	CatchError
}



/*!
	Synchronise the execution clock
*/
template<typename dat>
inline void HintFld<dat>::syncExecClk()
{
	WatchError
	if (PrevClk < InvClk) PrevClk = NotClk;
	CatchError
}



/*!
	Peform finalisation of the fld.
*/
template<typename dat>
inline void HintFld<dat>::finalise(dat const & theDat)
{
	WatchError
	CurrBuff = theDat;
	PrevClk = EtrClk;
	CatchError
}



/*!
	Perform curr data initialisation.
*/
template<typename dat>
inline void HintFld<dat>::initCurr(dat const & theDat)
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
inline Bll HintFld<dat>::updtCurr(Clk const execClk, dat const & theDat)
{
	WatchError
	Warn(execClk < PrevClk, eClockConflict);

	if (eq<dat,Bll>::iof(CurrBuff, theDat))
	{
		PrevClk = NotClk;
		return false;
	}
	else
	{
		PrevClk = execClk;
		PrevBuff = CurrBuff;
		CurrBuff = theDat;
		return true;
	}
	CatchError
}



/*!
	Copy to prev data to false.
*/
template<typename dat>
inline void HintFld<dat>::copytoPrevBuff()
{
	WatchError
	PrevBuff = CurrBuff;
	CatchError
}



/*!
	Reset prev diff to false.
*/
template<typename dat>
inline void HintFld<dat>::resetPrevDiff()
{
	WatchError
	PrevClk = NotClk;
	CatchError
}



/*!
	Determine prev diff.
*/
template<typename dat>
inline Bll HintFld<dat>::determPrevDiff(Clk const execClk)
{
	WatchError
	Warn(execClk < PrevClk, eClockConflict);

	if (PrevBuff != CurrBuff)
	{
		PrevClk = execClk;
		return true;
	}
	else
	{
		PrevClk = NotClk;
		return false;
	}
	CatchError
}



/*!
	Return curr data.
*/
template<typename dat>
inline dat const & HintFld<dat>::CurrData() const
{
	WatchError
	return CurrBuff;
	CatchError
}



/*!
	PrevData = PrevBuff or CurrBuff.
*/
template<typename dat>
inline dat const & HintFld<dat>::PrevData(Clk const execClk) const
{
	WatchError
	return PrevClk != execClk ? PrevBuff : CurrBuff;
	CatchError
}



/*!
	PrevDiff = PrevBuff holds value.
*/
template<typename dat>
inline Bll HintFld<dat>::PrevDiff(Clk const execClk) const
{
	WatchError
	return PrevClk == execClk;
	CatchError
}


closeKangarooSpace



#endif//HintFldTccIncluded
