/*!
	@file propflipvarvb.cpp
	@brief The implementation file for PropFlipVarVb class.
	@details This is the implementation file for PropFlipVarVb class.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see propflipvarvb.hpp
*/



#include "cbls/vars/flipvars/propflipvarvb.hpp"



openKangarooSpace



/*!
	Define an integer range variable.
*/
Hdl PropFlipVarVb::def(Hdl const hdlSys)
{
	WatchError
	PropFlipVarVb * tVar = new PropFlipVarVb(hdlSys);
	Hdl const tHdl = tVar->defSysVar();
	if (tHdl != InvHdl) { delete tVar; return tHdl; }

	EvalTblBln & tValueTbl = EvalTblBln::refm(hdlSys);
	tValueTbl.setEvalRec(tVar->mValueRec, tVar->mValueLoc);

	#if CompLazy
	tVar->mValueRec->resetLateDiff();	//	variables would have no backlog
	tVar->mValueRec->resetLtNxDiff();	//	variables would have no backlog
	#endif

	return tVar->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
PropFlipVarVb::PropFlipVarVb(Hdl const hdlSys) : FlipVarVb(hdlSys)
{
	WatchError
	setTermCls(TermStub<PropFlipVarVb>::TermCls);
	setTermHvl(calcTermHvl());
	CatchError
}


/*!
	The duplicator.
*/
PropFlipVarVb::PropFlipVarVb(PropFlipVarVb const & that) : FlipVarVb(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}


/*!
	The assigner.
*/
PropFlipVarVb const & PropFlipVarVb::operator = (PropFlipVarVb const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}


/*!
	The destructor.
*/
PropFlipVarVb::~PropFlipVarVb()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll PropFlipVarVb::identical(Var const & that) const
{
	WatchError
	return (that.TermCls == TermStub<PropFlipVarVb>::TermCls);
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll PropFlipVarVb::identical(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	return (that->TermCls == TermStub<PropFlipVarVb>::TermCls);
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll PropFlipVarVb::assignable(Var const & that) const
{
	WatchError
	return (that.TermTyp == TermStub<FlipVarVb>::TermTyp);
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll PropFlipVarVb::assignable(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	return (that->TermTyp == TermStub<FlipVarVb>::TermTyp);
	CatchError
}



/*!
	Whether two variables are swappable?
*/
Bll PropFlipVarVb::swappable(Var const & that) const
{
	WatchError
	return (that.TermTyp == TermStub<FlipVarVb>::TermTyp);
	CatchError
}



/*!
	Whether two variables are swappable?
*/
Bll PropFlipVarVb::swappable(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	return (that->TermTyp == TermStub<FlipVarVb>::TermTyp);
	CatchError
}



/*!
	Valid with respect to the valid?
*/
Bll PropFlipVarVb::validValue(Bln const & theValue) const
{
	WatchError
	return true;
	CatchError
}



/*!
	Valid with respect to the static domain?
*/
Bll PropFlipVarVb::validStat(Wrp const & theWrp) const
{
	WatchError
	return theWrp.chkWrap(Wb);
	CatchError
}




/*!
	Valid with respect to the dynamic domain?
*/
Bll PropFlipVarVb::validDyna(Wrp const & theWrp) const
{
	WatchError
	return theWrp.chkWrap(Wb);
	CatchError
}



/*!
	Whether the current value is the right value?
*/
Bll PropFlipVarVb::chkCurrRight() const
{
	WatchError
	return mValueRec->CurrBuff;
	CatchError
}



/*!
	Whether the current value is the left value?
*/
Bll PropFlipVarVb::chkCurrLeft() const
{
	WatchError
	return !mValueRec->CurrBuff;
	CatchError
}




/*!
	Whether the next value is the right value?
*/
Bll PropFlipVarVb::chkNextRight() const
{
	WatchError
	return mValueRec->NextBuff;
	CatchError
}



/*!
	Whether the next value is the left value?
*/
Bll PropFlipVarVb::chkNextLeft() const
{
	WatchError
	return !mValueRec->NextBuff;
	CatchError
}




/*!
	Current state of the var.
*/
Bll PropFlipVarVb::CurrState() const
{
	WatchError
	return mValueRec->CurrBuff;
	CatchError
}




/*!
	Next state of the var.
*/
Bll PropFlipVarVb::NextState() const
{
	WatchError
	return mValueRec->NextData(mTermSys.SimulClk());
	CatchError
}



/*!
	Random state of the var.
*/
Bll PropFlipVarVb::RandState(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd);
	CatchError
}




/*!
	State for a given wrap value.
*/
Bll PropFlipVarVb::WrapState(Wrp const & theWrp) const
{
	WatchError
	return theWrp.itemBln();
	CatchError
}




/*!
	Randomly chosen value.
*/
Bln PropFlipVarVb::RandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd);
	CatchError
}



/*!
	The left value.
*/
Bln PropFlipVarVb::LeftValue() const
{
	WatchError
	return false;
	CatchError
}



/*!
	The right value.
*/
Bln PropFlipVarVb::RightValue() const
{
	WatchError
	return true;
	CatchError
}



/*!
	The state value.
*/
Bln PropFlipVarVb::StateValue(Bll const RightNotLeft) const
{
	WatchError
	return RightNotLeft;
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Wrp PropFlipVarVb::StatRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd));
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Wrp PropFlipVarVb::DynaRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd));
	CatchError
}



/*!
	Wrap for the left value.
*/
Wrp PropFlipVarVb::LeftWrap() const
{
	WatchError
	return Wrp(false);
	CatchError
}



/*!
	Wrap for the right value.
*/
Wrp PropFlipVarVb::RightWrap() const
{
	WatchError
	return Wrp(true);
	CatchError
}



/*!
	Wrap of a given state.
*/
Wrp PropFlipVarVb::StateWrap(Bll const RightNotLeft) const
{
	WatchError
	return Wrp(RightNotLeft);
	CatchError
}




/*!
	Perform anew execution with a value.
*/
void PropFlipVarVb::execAnewValue(Bln const & theBln)
{
	WatchError
	runPreExecAnew();
	mValueRec->initCurr(theBln);
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform anew execution with a value wrap.
*/
void PropFlipVarVb::execAnewWrap(Wrp const & theWrp)
{
	WatchError
	runPreExecAnew();
	mValueRec->initCurr(theWrp.itemBln());
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform anew execution with truth value.
*/
void PropFlipVarVb::execAnewState(Bll const RightNotLeft)
{
	WatchError
	runPreExecAnew();
	mValueRec->initCurr(RightNotLeft);
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform anew execution wth a random value from the static domain.
*/
void PropFlipVarVb::execAnewStatRand(Rnd & theRnd)
{
	WatchError
	runPreExecAnew();
	mValueRec->initCurr(uniform(theRnd));
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform anew execution wth a random value from the dyanmic domain.
*/
void PropFlipVarVb::execAnewDynaRand(Rnd & theRnd)
{
	WatchError
	runPreExecAnew();
	mValueRec->initCurr(uniform(theRnd));
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform anew execution with the next value.
*/
void PropFlipVarVb::execAnewFlip()
{
	WatchError
	runPreExecAnew();
	mValueRec->initCurr(!mValueRec->CurrBuff);
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform incremental execution with a value.
*/
void PropFlipVarVb::execIncrValue(Bln const & theBln)
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), theBln);
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with a value wrap.
*/
void PropFlipVarVb::execIncrWrap(Wrp const & theWrp)
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), theWrp.itemBln());
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with a truth value.
*/
void PropFlipVarVb::execIncrState(Bll const RightNotLeft)
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), RightNotLeft);
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with a random value from the static domain.
*/
void PropFlipVarVb::execIncrStatRand(Rnd & theRnd)
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), uniform(theRnd));
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with a random value from the dynamic domain.
*/
void PropFlipVarVb::execIncrDynaRand(Rnd & theRnd)
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), uniform(theRnd));
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution by flipping.
*/
void PropFlipVarVb::execIncrFlip()
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), !mValueRec->CurrBuff);
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform anew simulation with a random value from the static domain.
*/
void PropFlipVarVb::simulAnewStatRand(Rnd & theRnd)
{
	WatchError
	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), uniform(theRnd));

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Perform anew simulation with a random value from the dynamic domain.
*/
void PropFlipVarVb::simulAnewDynaRand(Rnd & theRnd)
{
	WatchError
	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), uniform(theRnd));

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Perform anew simulation with a value.
*/
void PropFlipVarVb::simulAnewValue(Bln const & theBln)
{
	WatchError
	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), theBln);

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Perform anew simulation with a value wrap.
*/
void PropFlipVarVb::simulAnewWrap(Wrp const & theWrp)
{
	WatchError
	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), theWrp.itemBln());

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}


/*!
	Perform anew simulation with a truth value.
*/
void PropFlipVarVb::simulAnewState(Bll RightNotLeft)
{
	WatchError
	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), RightNotLeft);

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Perform anew simulation by flipping.
*/
void PropFlipVarVb::simulAnewFlip()
{
	WatchError
	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), !mValueRec->CurrBuff);

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with a random value from the static domain.
*/
void PropFlipVarVb::simulIncrStatRand(Rnd & theRnd)
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), uniform(theRnd));

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with a random value from the dynamic domain.
*/
void PropFlipVarVb::simulIncrDynaRand(Rnd & theRnd)
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), uniform(theRnd));

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with a value.
*/
void PropFlipVarVb::simulIncrValue(Bln const & theBln)
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), theBln);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}




/*!
	Perform incremental simulation with a value wrap.
*/
void PropFlipVarVb::simulIncrWrap(Wrp const & theWrp)
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), theWrp.itemBln());

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with a truth value.
*/
void PropFlipVarVb::simulIncrState(Bll const RightNotLeft)
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), RightNotLeft);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation by flipping.
*/
void PropFlipVarVb::simulIncrFlip()
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), !mValueRec->CurrBuff);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



closeKangarooSpace
