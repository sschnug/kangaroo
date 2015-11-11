/*!
	@file rangevarvt.tcc
	@brief The prototype file for RangeVarVt template class.
	@details This is the prototype file for RangeVarVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef RangeVarVtTccIncluded
#define RangeVarVtTccIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"



openKangarooSpace



/*!
	@class RangeVarVt
	@brief A template class to represent range variables.
	@details This template class represents range variables.
*/
template <typename vt>
class RangeVarVt : public RangeVar
{
	public:

		static RangeVarVt<vt> & refm(Hdl const hdlSys, Hdl const hdlVar);			//!< Reference.
		static RangeVarVt<vt> * ptrm(Hdl const hdlSys, Hdl const hdlVar);			//!< Pointer.
		static RangeVarVt<vt> const & refc(Hdl const hdlSys, Hdl const hdlVar);	//!< Reference.
		static RangeVarVt<vt> const * ptrc(Hdl const hdlSys, Hdl const hdlVar);	//!< Pointer.

		//! @name Casting
		//! @{

		static RangeVarVt<vt> const & cast(Term const & theTerm);	//!< Perform casting.
		static RangeVarVt<vt> const * cast(Term const * theTerm);	//!< Perform casting.
		static RangeVarVt<vt> & cast(Term & theTerm);				//!< Perform casting.
		static RangeVarVt<vt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);			//!< Suits casting?
		static Bll suit(Term const * theTerm);			//!< Suits casting?
		static Bll suit(Term & theTerm);				//!< Suits casting?
		static Bll suit(Term * theTerm);				//!< Suits casting?

		//! @}

	public:

		EvalRec<vt> const & ValueRec() const;			//!< Value record.
		virtual Wrp CurrWrap() const;					//!< Current value.
		virtual Wrp NextWrap() const;					//!< Next value.

		virtual Typ ValueType() const;					//!< Value type.
		virtual Loc ValueLoc() const;					//!< Value locator.

		virtual Bll chkNextCurr() const;				//!< Whether the next value is the current value.

		//! @name Validity
		//! @{

		virtual Bll validStat(vt const & theValue) const = 0;	//!< Valid with respect to the static domain?
		virtual Bll validDyna(vt const & theValue) const = 0;	//!< Valid with respect to the dynamic domain?

		//! @}
		//! @name Values
		//! @{

		vt CurrValue() const;								//!< Current value of the variable.
		vt NextValue() const;								//!< Next value of the variable.
		virtual vt StatRandValue(Rnd & theRnd) const = 0;	//!< Random value chosen from the static domain.
		virtual vt DynaRandValue(Rnd & theRnd) const = 0;	//!< Random value chosen from the dynamic domain.
		virtual vt StepSizeValue() const = 0;				//!< The step size value.
		virtual vt StatLeftValue() const = 0;				//!< The static left value.
		virtual vt StatRightValue() const = 0;				//!< The static right value.
		virtual vt DynaLeftValue() const = 0;				//!< The dynamic right value.
		virtual vt DynaRightValue() const = 0;				//!< The dynamic right value.

		//! @}

		//! @name Execution
		//! @{

		virtual void execAnewNext();						//!< Execute anew with the next value.
		virtual void execIncrNext();						//!< Execute incrementally with the next value.
		virtual void execIncrSwap(Var * that);				//!< Execute with swapping variables' values.
		virtual void execIncrSwap(Var & that);				//!< Execute with swapping variables' values.
		virtual void execIncrDiff(Var const * that);		//!< Execute with another variable's value.
		virtual void execIncrDiff(Var const & that);		//!< Execute with another variable's value.
		virtual void execAnewValue(vt const & theValue) = 0;//!< Execute anew with a given value.
		virtual void execIncrValue(vt const & theValue) = 0;//!< Execute incrementally with a given value.

		//! @}

		//! @name Simulation
		//! @{

		virtual void simulAnewCurr();						//!< Simulate anew with the current value.
		virtual void simulIncrCurr();						//!< Simulate incrementally with the current value.
		virtual void simulIncrSwap(Var * that);				//!< Simulate with swapping variables' values.
		virtual void simulIncrSwap(Var & that);				//!< Simulate with swapping variables' values.
		virtual void simulIncrDiff(Var const * that);		//!< Simulate with another variable's value.
		virtual void simulIncrDiff(Var const & that);		//!< Simulate with another variable's value.
		virtual void simulAnewValue(vt const & theValue) = 0;//!< Simulate anew with a given value.
		virtual void simulIncrValue(vt const & theValue) = 0;//!< Simulate incrementally with a given value.

		//! @}

	protected:

		virtual ~RangeVarVt();														//!< Destructor.
		RangeVarVt(Hdl const hdlSys);												//!< Constructor.
		RangeVarVt(RangeVarVt<vt> const & theRangeVarVt);							//!< Duplicator.
		RangeVarVt<vt> const & operator = (RangeVarVt<vt> const & theRangeVarVt);	//!< Assigner.

		//! @name Postprocessing
		//! @{
		#if ExecUpwdLazy
		void runPostExecAnew();		//!< Postprocessing for anew execution.
		void runPostExecIncr();		//!< Postprocessing for incremental execution.
		#endif //ExecUpwdLazy
		#if SimulUpwd
		void runPostSimulAnew();	//!< Postprocessing for anew simulation.
		void runPostSimulIncr();	//!< Postprocessing for incremental simulaiton.
		#endif//SimulUpwd

		//! @}

	protected:

		Loc 			mValueLoc;		//!< Locator of the value record.
		EvalRec<vt> * 	mValueRec;		//!< Point to the value record.
};



/*!
	Whether a term is suitable for casting?
*/
template <typename vt>
inline Bln RangeVarVt<vt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< RangeVarVt<vt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting?
*/
template <typename vt>
inline Bln RangeVarVt<vt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< RangeVarVt<vt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting?
*/
template <typename vt>
inline Bln RangeVarVt<vt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< RangeVarVt<vt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting?
*/
template <typename vt>
inline Bln RangeVarVt<vt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< RangeVarVt<vt> >::TermTyp;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename vt>
inline RangeVarVt<vt> & RangeVarVt<vt>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< RangeVarVt<vt> >::TermTyp, eWrongTyp);

	return scast<RangeVarVt &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename vt>
inline RangeVarVt<vt> * RangeVarVt<vt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< RangeVarVt<vt> >::TermTyp, eWrongTyp);

	return scast<RangeVarVt<vt> *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename vt>
inline RangeVarVt<vt> const & RangeVarVt<vt>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< RangeVarVt<vt> >::TermTyp, eWrongTyp);

	return scast<RangeVarVt<vt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename vt>
inline RangeVarVt<vt> const * RangeVarVt<vt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< RangeVarVt<vt> >::TermTyp, eWrongTyp);

	return scast<RangeVarVt<vt> const *>(theTerm);
	CatchError
}


/*!
	Refer to a variable.
*/
template <typename vt>
inline RangeVarVt<vt> & RangeVarVt<vt>::refm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmVar(hdlVar));
	CatchError
}



/*!
	Point to a variable.
*/
template <typename vt>
inline RangeVarVt<vt> * RangeVarVt<vt>::ptrm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmVar(hdlVar));
	CatchError
}



/*!
	Refer to a variable.
*/
template <typename vt>
inline RangeVarVt<vt> const & RangeVarVt<vt>::refc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcVar(hdlVar));
	CatchError
}



/*!
	Point to a variable.
*/
template <typename vt>
inline RangeVarVt<vt> const * RangeVarVt<vt>::ptrc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcVar(hdlVar));
	CatchError
}



/*!
	The constructor.
*/
template <typename vt>
inline RangeVarVt<vt>::RangeVarVt(Hdl const hdlSys) : RangeVar(hdlSys), mValueLoc(InvLoc)
{
	WatchError
	setTermTyp(TermStub< RangeVarVt<vt> >::TermTyp);
	CatchError
}


/*!
	The destructor.
*/
template <typename vt>
inline RangeVarVt<vt>::~RangeVarVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Return the value locator.
*/
template<typename vt>
Loc RangeVarVt<vt>::ValueLoc() const
{
	WatchError
	return mValueLoc;
	CatchError
}



/*!
	Return the value type.
*/
template<typename vt>
Typ RangeVarVt<vt>::ValueType() const
{
	WatchError
	return DataStub< vt >::DataTyp;
	CatchError
}



/*!
	Return the value record.
*/
template <typename vt>
inline EvalRec<vt> const & RangeVarVt<vt>::ValueRec() const
{
	WatchError
	return *mValueRec;
	CatchError
}


/*!
	Return the current value wrap.
*/
template <typename vt>
inline Wrp RangeVarVt<vt>::CurrWrap() const
{
	WatchError
	return Wrp(mValueRec->CurrData());
	CatchError
}



/*!
	Return the next value wrap.
*/
template <typename vt>
inline Wrp RangeVarVt<vt>::NextWrap() const
{
	WatchError
	return Wrp(mValueRec->NextData(mTermSys.SimulClk()));
	CatchError
}



/*!
	Return the current value.
*/
template <typename vt>
inline vt RangeVarVt<vt>::CurrValue() const
{
	WatchError
	return mValueRec->CurrData();
	CatchError
}



/*!
	Return the next value wrap.
*/
template <typename vt>
inline vt RangeVarVt<vt>::NextValue() const
{
	WatchError
	return mValueRec->NextData(mTermSys.SimulClk());
	CatchError
}


/*!
	Whether the next value is the current value?
*/
template <typename vt>
inline Bll RangeVarVt<vt>::chkNextCurr() const
{
	WatchError
	return eq<vt,Bll>::iof(mValueRec->NextBuff, mValueRec->CurrBuff);
	CatchError
}




#if ExecUpwdLazy
/*!
	Run postprocessing for anew execution.
*/
template <typename vt>
inline void RangeVarVt<vt>::runPostExecAnew()
{
	WatchError
	#if ExecUpwd
	scheduleExecAnewArgs();
	#endif
	#if ExecLazy
	clearEvalUndoArgs();
	#endif
	CatchError
}
#endif //ExecUpwdLazy



#if ExecUpwdLazy
/*!
	Run postprocessing for incremental execution.
*/
template <typename vt>
inline void RangeVarVt<vt>::runPostExecIncr()
{
	WatchError
	#if ExecUpwd
	if (mValueRec->PrevDiff(mTermSys.ExecClk()))
		scheduleExecIncrArgs();
	#endif
	#if ExecLazy
	if (mValueRec->PrevDiff(mTermSys.ExecClk()))
		notifyEvalUndoArgs();
	#endif
	CatchError
}
#endif //ExecUpwdLazy


#if SimulUpwd
/*!
	Run postprocessing for anew simulation.
*/
template <typename vt>
inline void RangeVarVt<vt>::runPostSimulAnew()
{
	WatchError
	this->scheduleSimulAnewArgs();
	CatchError
}
#endif//SimulUpwd



#if SimulUpwd
/*!
	Run postprocessing for incremental simulation.
*/
template <typename vt>
inline void RangeVarVt<vt>::runPostSimulIncr()
{
	WatchError
	if (mValueRec->NextDiff(mTermSys.SimulClk()))
		this->scheduleSimulIncrArgs();
	CatchError
}
#endif//SimulUpwd



/*!
	The duplicator.
*/
template <typename vt>
RangeVarVt<vt>::RangeVarVt(RangeVarVt<vt> const & theRangeVarVt) : RangeVar(theRangeVarVt)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename vt>
RangeVarVt<vt> const & RangeVarVt<vt>::operator = (RangeVarVt const & theRangeVarVt)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}




/*!
	Perform anew execution with the next value.
*/
template <typename vt>
void RangeVarVt<vt>::execAnewNext()
{
	WatchError
	runPreExecAnew();
	mValueRec->initCurr(mValueRec->NextBuff);
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}




/*!
	Perform incremental execution with the next value.
*/
template <typename vt>
void RangeVarVt<vt>::execIncrNext()
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), mValueRec->NextBuff);
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with another variable's value.
*/
template <typename vt>
void RangeVarVt<vt>::execIncrDiff(Var const & that)
{
	Warn(!assignable(that), eValNotAssignable);

	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), cast(that).ValueRec().CurrData());
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
}



/*!
	Perform incremental execution with another variable's value.
*/
template <typename vt>
void RangeVarVt<vt>::execIncrDiff(Var const * that)
{
	Warn(!that, eNullPointer);
	Warn(!assignable(that), eValNotAssignable);

	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), cast(that)->ValueRec().CurrData());
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
}



/*!
	Perform anew simulation with the current value.
*/
template <typename vt>
void RangeVarVt<vt>::simulAnewCurr()
{
	WatchError
	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), mValueRec->CurrBuff);

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with the current value.
*/
template <typename vt>
void RangeVarVt<vt>::simulIncrCurr()
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), mValueRec->CurrBuff);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with another variable's value.
*/
template <typename vt>
void RangeVarVt<vt>::simulIncrDiff(Var const * that)
{
	Warn(!that, eNullPointer);
	Warn(!assignable(that), eValNotAssignable);

	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), cast(that)->ValueRec().CurrData());

	#if SimulUpwd
	runPostSimulIncr();
	#endif
}



/*!
	Perform incremental simulation with another variable's value.
*/
template <typename vt>
void RangeVarVt<vt>::simulIncrDiff(Var const & that)
{
	Warn(!assignable(that), eValNotAssignable);

	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), cast(that).ValueRec().CurrData());

	#if SimulUpwd
	runPostSimulIncr();
	#endif
}



/*!
	Perform incremental execution by swapping variables' values.
*/
template <typename vt>
void RangeVarVt<vt>::execIncrSwap(Var * that)
{
	WatchError
	Warn(!that, eNullPointer);
	Warn(!swappable(that), eVarsNotSwappable);

	RangeVarVt<vt> * tVar = RangeVarVt<vt>::cast(that);
	EvalRec<vt> * tValueRec = tVar->mValueRec;

	this->runPreExecIncr(); tVar->runPreExecIncr();
	if (ne<vt,Bll>::iof(mValueRec->CurrBuff, tValueRec->CurrBuff))
	{
		mValueRec->copytoPrevBuff();
		tValueRec->copytoPrevBuff();
		exchange<vt>(mValueRec->CurrBuff, tValueRec->CurrBuff);
		mValueRec->determPrevDiff(mTermSys.ExecClk());
		tValueRec->determPrevDiff(mTermSys.ExecClk());
	}
	#if ExecUpwdLazy
	this->runPostExecIncr(); tVar->runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution by swapping variables' values.
*/
template <typename vt>
void RangeVarVt<vt>::execIncrSwap(Var & that)
{
	WatchError
	Warn(!swappable(that), eVarsNotSwappable);

	RangeVarVt<vt> & tVar = RangeVarVt<vt>::cast(that);
	EvalRec<vt> * tValueRec = tVar.mValueRec;

	this->runPreExecIncr(); tVar.runPreExecIncr();
	if (ne<vt,Bll>::iof(mValueRec->CurrBuff, tValueRec->CurrBuff))
	{
		mValueRec->copytoPrevBuff();
		tValueRec->copytoPrevBuff();
		exchange<vt>(mValueRec->CurrBuff, tValueRec->CurrBuff);
		mValueRec->determPrevDiff(mTermSys.ExecClk());
		tValueRec->determPrevDiff(mTermSys.ExecClk());
	}
	#if ExecUpwdLazy
	this->runPostExecIncr(); tVar.runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation by swapping variables' values.
*/
template <typename vt>
void RangeVarVt<vt>::simulIncrSwap(Var * that)
{
	WatchError
	Warn(!that, eNullPointer);
	Warn(!swappable(that), eVarsNotSwappable);

	RangeVarVt<vt> * tVar = RangeVarVt<vt>::cast(that);
	EvalRec<vt> * tValueRec = tVar->mValueRec;

	this->runPreSimulIncr(); tVar->runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), tValueRec->CurrBuff);
	tValueRec->initNext(mTermSys.SimulClk(), mValueRec->CurrBuff);

	#if SimulUpwd
	this->runPostSimulIncr(); tVar->runPostSimulIncr();
	#endif//SimulUpwd
	CatchError
}



/*!
	Perform incremental simulation by swapping variables' values.
*/
template <typename vt>
void RangeVarVt<vt>::simulIncrSwap(Var & that)
{
	WatchError
	Warn(!swappable(that), eVarsNotSwappable);

	RangeVarVt<vt> & tVar = RangeVarVt<vt>::cast(that);
	EvalRec<vt> * tValueRec = tVar.mValueRec;

	this->runPreSimulIncr(); tVar.runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), tValueRec->CurrBuff);
	tValueRec->initNext(mTermSys.SimulClk(), mValueRec->CurrBuff);

	#if SimulUpwd
	this->runPostSimulIncr(); tVar.runPostSimulIncr();
	#endif//SimulUpwd
	CatchError
}



closeKangarooSpace


#endif//RangeVarVtTccIncluded
