/*!
	@file flipvarvt.tcc
	@brief The prototype file for FlipVarVt template class.
	@details This is the prototype file for FlipVarVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef FlipVarVtTccIncluded
#define FlipVarVtTccIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"



openKangarooSpace



/*!
	@class FlipVarVt
	@brief A template class to represent flip variables.
	@details This template class represents flip variables.
*/
template <typename vt>
class FlipVarVt : public FlipVar
{
	public:

		static FlipVarVt<vt> & refm(Hdl const hdlSys, Hdl const hdlVar);		//!< Reference.
		static FlipVarVt<vt> * ptrm(Hdl const hdlSys, Hdl const hdlVar);		//!< Pointer.
		static FlipVarVt<vt> const & refc(Hdl const hdlSys, Hdl const hdlVar);	//!< Reference.
		static FlipVarVt<vt> const * ptrc(Hdl const hdlSys, Hdl const hdlVar);	//!< Pointer.

		//! @name Casting
		//! @{

		static FlipVarVt<vt> const & cast(Term const & theTerm);	//!< Perform casting.
		static FlipVarVt<vt> const * cast(Term const * theTerm);	//!< Perform casting.
		static FlipVarVt<vt> & cast(Term & theTerm);				//!< Perform casting.
		static FlipVarVt<vt> * cast(Term * theTerm);				//!< Perform casting.

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

		virtual Bll chkNextCurr() const;						//!< Whether the next value is the current value.
		virtual Bll validValue(vt const & theValue) const = 0;	//!< Valid with respect to the domain?

		//! @name Values
		//! @{

		vt CurrValue() const;								//!< Current value of the variable.
		vt NextValue() const;								//!< Next value of the variable.
		virtual vt RandValue(Rnd & theRnd) const = 0;		//!< Random value chosen.
		virtual vt LeftValue() const = 0;					//!< The static left value.
		virtual vt RightValue() const = 0;					//!< The static right value.

		//! @}
		//! @name Executions
		//! @{

		virtual void execAnewNext();							//!< Execute anew with the next value.
		virtual void execIncrNext();							//!< Execute incrementally with the next value.
		virtual void execIncrSwap(Var * that);					//!< Execute with swapping variables' values.
		virtual void execIncrSwap(Var & that);					//!< Execute with swapping variables' values.
		virtual void execIncrDiff(Var const * that);			//!< Execute with another variable's value.
		virtual void execIncrDiff(Var const & that);			//!< Execute with another variable's value.
		virtual void execAnewValue(vt const & theValue) = 0;	//!< Execute anew with a given value.
		virtual void execIncrValue(vt const & theValue) = 0;	//!< Execute incrementally with a given value.

		//! @}

		//! @name Simulations
		//! @{

		virtual void simulAnewCurr();							//!< Simulate anew with the current value.
		virtual void simulIncrCurr();							//!< Simulate incrementally with the current value.
		virtual void simulIncrSwap(Var * that);					//!< Simulate with swapping variables' values.
		virtual void simulIncrSwap(Var & that);					//!< Simulate with swapping variables' values.
		virtual void simulIncrDiff(Var const * that);			//!< Simulate with another variable's value.
		virtual void simulIncrDiff(Var const & that);			//!< Simulate with another variable's value.
		virtual void simulAnewValue(vt const & theValue) = 0;	//!< Simulate anew with a given value.
		virtual void simulIncrValue(vt const & theValue) = 0;	//!< Simulate incrementally with a given value.

		//! @}

	protected:

		virtual ~FlipVarVt();							//!< Destructor.
		FlipVarVt(Hdl const hdlSys);					//!< Constructor.
		FlipVarVt(FlipVarVt<vt> const & theFlipVarVt);	//!< Duplicator.
		FlipVarVt<vt> const & operator =
				(FlipVarVt<vt> const & theFlipVarVt);	//!< Assigner.

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

		Loc mValueLoc;				//!< Locator of the value record.
		EvalRec<vt> * mValueRec;	//!< Point to the value record.
};



/*!
	Whether a term is suitable for casting?
*/
template <typename vt>
inline Bln FlipVarVt<vt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FlipVarVt<vt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting?
*/
template <typename vt>
inline Bln FlipVarVt<vt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FlipVarVt<vt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting?
*/
template <typename vt>
inline Bln FlipVarVt<vt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FlipVarVt<vt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting?
*/
template <typename vt>
inline Bln FlipVarVt<vt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FlipVarVt<vt> >::TermTyp;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename vt>
inline FlipVarVt<vt> & FlipVarVt<vt>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FlipVarVt<vt> >::TermTyp, eWrongTyp);

	return scast<FlipVarVt &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename vt>
inline FlipVarVt<vt> * FlipVarVt<vt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FlipVarVt<vt> >::TermTyp, eWrongTyp);

	return scast<FlipVarVt<vt> *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename vt>
inline FlipVarVt<vt> const & FlipVarVt<vt>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FlipVarVt<vt> >::TermTyp, eWrongTyp);

	return scast<FlipVarVt<vt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename vt>
inline FlipVarVt<vt> const * FlipVarVt<vt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FlipVarVt<vt> >::TermTyp, eWrongTyp);

	return scast<FlipVarVt<vt> const *>(theTerm);
	CatchError
}


/*!
	Refer to a variable.
*/
template <typename vt>
inline FlipVarVt<vt> & FlipVarVt<vt>::refm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmVar(hdlVar));
	CatchError
}



/*!
	Point to a variable.
*/
template <typename vt>
inline FlipVarVt<vt> * FlipVarVt<vt>::ptrm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmVar(hdlVar));
	CatchError
}



/*!
	Refer to a variable.
*/
template <typename vt>
inline FlipVarVt<vt> const & FlipVarVt<vt>::refc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcVar(hdlVar));
	CatchError
}



/*!
	Point to a variable.
*/
template <typename vt>
inline FlipVarVt<vt> const * FlipVarVt<vt>::ptrc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcVar(hdlVar));
	CatchError
}



/*!
	The constructor.
*/
template <typename vt>
inline FlipVarVt<vt>::FlipVarVt(Hdl const hdlSys) : FlipVar(hdlSys), mValueLoc(InvLoc)
{
	WatchError
	setTermTyp(TermStub< FlipVarVt<vt> >::TermTyp);
	CatchError
}


/*!
	The destructor.
*/
template <typename vt>
inline FlipVarVt<vt>::~FlipVarVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Return the value locator.
*/
template<typename vt>
Loc FlipVarVt<vt>::ValueLoc() const
{
	WatchError
	return mValueLoc;
	CatchError
}



/*!
	Return the value type.
*/
template<typename vt>
Typ FlipVarVt<vt>::ValueType() const
{
	WatchError
	return DataStub< vt >::DataTyp;
	CatchError
}



/*!
	Return the value record.
*/
template <typename vt>
inline EvalRec<vt> const & FlipVarVt<vt>::ValueRec() const
{
	WatchError
	return *mValueRec;
	CatchError
}



/*!
	Return the value wrap.
*/
template <typename vt>
inline Wrp FlipVarVt<vt>::CurrWrap() const
{
	WatchError
	return Wrp(mValueRec->CurrData());
	CatchError
}



/*!
	Return the value wrap.
*/
template <typename vt>
inline Wrp FlipVarVt<vt>::NextWrap() const
{
	WatchError
	return Wrp(mValueRec->NextData(mTermSys.SimulClk()));
	CatchError
}



/*!
	Return the value.
*/
template <typename vt>
inline vt FlipVarVt<vt>::CurrValue() const
{
	WatchError
	return mValueRec->CurrData();
	CatchError
}



/*!
	Return the value.
*/
template <typename vt>
inline vt FlipVarVt<vt>::NextValue() const
{
	WatchError
	return mValueRec->NextData(mTermSys.SimulClk());
	CatchError
}




/*!
	Whether the next value is the current value?
*/
template <typename vt>
inline Bll FlipVarVt<vt>::chkNextCurr() const
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
inline void FlipVarVt<vt>::runPostExecAnew()
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
inline void FlipVarVt<vt>::runPostExecIncr()
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
inline void FlipVarVt<vt>::runPostSimulAnew()
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
inline void FlipVarVt<vt>::runPostSimulIncr()
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
FlipVarVt<vt>::FlipVarVt(FlipVarVt<vt> const & theFlipVarVt) : FlipVar(theFlipVarVt)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename vt>
FlipVarVt<vt> const & FlipVarVt<vt>::operator = (FlipVarVt const & theFlipVarVt)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Perform anew execution with the next value.
*/
template <typename vt>
void FlipVarVt<vt>::execAnewNext()
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
void FlipVarVt<vt>::execIncrNext()
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
void FlipVarVt<vt>::execIncrDiff(Var const & that)
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
void FlipVarVt<vt>::execIncrDiff(Var const * that)
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
void FlipVarVt<vt>::simulAnewCurr()
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
void FlipVarVt<vt>::simulIncrCurr()
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
void FlipVarVt<vt>::simulIncrDiff(Var const * that)
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
void FlipVarVt<vt>::simulIncrDiff(Var const & that)
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
void FlipVarVt<vt>::execIncrSwap(Var * that)
{
	WatchError
	Warn(!that, eNullPointer);
	Warn(!swappable(that), eVarsNotSwappable);

	FlipVarVt<vt> * tVar = FlipVarVt<vt>::cast(that);
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
void FlipVarVt<vt>::execIncrSwap(Var & that)
{
	WatchError
	Warn(!swappable(that), eVarsNotSwappable);

	FlipVarVt<vt> & tVar = FlipVarVt<vt>::cast(that);
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
void FlipVarVt<vt>::simulIncrSwap(Var * that)
{
	WatchError
	Warn(!that, eNullPointer);
	Warn(!swappable(that), eVarsNotSwappable);

	FlipVarVt<vt> * tVar = FlipVarVt<vt>::cast(that);
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
void FlipVarVt<vt>::simulIncrSwap(Var & that)
{
	WatchError
	Warn(!swappable(that), eVarsNotSwappable);

	FlipVarVt<vt> & tVar = FlipVarVt<vt>::cast(that);
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


#endif//FlipVarVtTccIncluded
