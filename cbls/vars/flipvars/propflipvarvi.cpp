/*!
	@file propflipvarvi.cpp
	@brief The implementation file for PropFlipVarVi class.
	@details This is the implementation file for PropFlipVarVi class.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see propflipvarvi.hpp
*/



#include "cbls/vars/flipvars/propflipvarvi.hpp"



openKangarooSpace



/*!
	Define an integer range variable.
*/
Hdl PropFlipVarVi::def(Hdl const hdlSys)
{
	WatchError
	PropFlipVarVi * tVar = new PropFlipVarVi(hdlSys);
	Hdl const tHdl = tVar->defSysVar();
	if (tHdl != InvHdl) { delete tVar; return tHdl; }

	EvalTblInt & tValueTbl = EvalTblInt::refm(hdlSys);
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
PropFlipVarVi::PropFlipVarVi(Hdl const hdlSys) : FlipVarVi(hdlSys)
{
	WatchError
	setTermCls(TermStub<PropFlipVarVi>::TermCls);
	setTermHvl(calcTermHvl());
	CatchError
}


/*!
	The duplicator.
*/
PropFlipVarVi::PropFlipVarVi(PropFlipVarVi const & that) : FlipVarVi(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}


/*!
	The assigner.
*/
PropFlipVarVi const & PropFlipVarVi::operator = (PropFlipVarVi const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}


/*!
	The destructor.
*/
PropFlipVarVi::~PropFlipVarVi()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll PropFlipVarVi::identical(Var const & that) const
{
	WatchError
	return (that.TermCls == TermStub<PropFlipVarVi>::TermCls);
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll PropFlipVarVi::identical(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	return (that->TermCls == TermStub<PropFlipVarVi>::TermCls);
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll PropFlipVarVi::assignable(Var const & that) const
{
	WatchError
	return (that.TermTyp == TermStub<FlipVarVi>::TermTyp);
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll PropFlipVarVi::assignable(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	return (that->TermTyp == TermStub<FlipVarVi>::TermTyp);
	CatchError
}



/*!
	Whether two variables are swappable?
*/
Bll PropFlipVarVi::swappable(Var const & that) const
{
	WatchError
	return (that.TermTyp == TermStub<FlipVarVi>::TermTyp);
	CatchError
}



/*!
	Whether two variables are swappable?
*/
Bll PropFlipVarVi::swappable(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	return (that->TermTyp == TermStub<FlipVarVi>::TermTyp);
	CatchError
}


/*!
	Valid with respect to the valid?
*/
Bll PropFlipVarVi::validValue(Int const & theInt) const
{
	WatchError
	return theInt >= 0 && theInt <= 1;
	CatchError
}



/*!
	Valid with respect to the static domain?
*/
Bll PropFlipVarVi::validStat(Wrp const & theWrp) const
{
	WatchError
	return theWrp.itemInt() >= 0 && theWrp.itemInt() <= 1;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll PropFlipVarVi::validDyna(Wrp const & theWrp) const
{
	WatchError
	return theWrp.itemInt() >= 0 && theWrp.itemInt() <= 1;
	CatchError
}



/*!
	Whether the current value is the right value?
*/
Bll PropFlipVarVi::chkCurrRight() const
{
	WatchError
	return mValueRec->CurrBuff;
	CatchError
}



/*!
	Whether the current value is the left value?
*/
Bll PropFlipVarVi::chkCurrLeft() const
{
	WatchError
	return !mValueRec->CurrBuff;
	CatchError
}




/*!
	Whether the next value is the right value?
*/
Bll PropFlipVarVi::chkNextRight() const
{
	WatchError
	return mValueRec->NextBuff;
	CatchError
}



/*!
	Whether the next value is the left value?
*/
Bll PropFlipVarVi::chkNextLeft() const
{
	WatchError
	return !mValueRec->NextBuff;
	CatchError
}



/*!
	Current state of the var.
*/
Bll PropFlipVarVi::CurrState() const
{
	WatchError
	return mValueRec->CurrBuff;
	CatchError
}


/*!
	Next state of the var.
*/
Bll PropFlipVarVi::NextState() const
{
	WatchError
	return mValueRec->NextData(mTermSys.SimulClk());
	CatchError
}




/*!
	Random state of the var.
*/
Bll PropFlipVarVi::RandState(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd);
	CatchError
}




/*!
	State for a given wrap value.
*/
Bll PropFlipVarVi::WrapState(Wrp const & theWrp) const
{
	WatchError
	return theWrp.itemInt();
	CatchError
}



/*!
	Randomly chosen value.
*/
Int PropFlipVarVi::RandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd);
	CatchError
}




/*!
	The left value.
*/
Int PropFlipVarVi::LeftValue() const
{
	WatchError
	return false;
	CatchError
}



/*!
	The right value.
*/
Int PropFlipVarVi::RightValue() const
{
	WatchError
	return true;
	CatchError
}



/*!
	The state value.
*/
Int PropFlipVarVi::StateValue(Bll const RightNotLeft) const
{
	WatchError
	return RightNotLeft;
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Wrp PropFlipVarVi::StatRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(castInt(uniform(theRnd)));
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Wrp PropFlipVarVi::DynaRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(castInt(uniform(theRnd)));
	CatchError
}



/*!
	Wrap for the left value.
*/
Wrp PropFlipVarVi::LeftWrap() const
{
	WatchError
	return Wrp(castInt(0));
	CatchError
}



/*!
	Wrap for the right value.
*/
Wrp PropFlipVarVi::RightWrap() const
{
	WatchError
	return Wrp(castInt(1));
	CatchError
}



/*!
	Wrap of a given state.
*/
Wrp PropFlipVarVi::StateWrap(Bll const RightNotLeft) const
{
	WatchError
	return Wrp(castInt(RightNotLeft));
	CatchError
}



/*!
	Perform anew execution with a value.
*/
void PropFlipVarVi::execAnewValue(Int const & theInt)
{
	WatchError
	Warn(theInt < 0 || theInt > 1, eOutOfDomain);

	runPreExecAnew();
	mValueRec->initCurr(theInt);
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}




/*!
	Perform anew execution with a value wrap.
*/
void PropFlipVarVi::execAnewWrap(Wrp const & theWrp)
{
	WatchError
	Warn(theWrp.itemInt() < 0 || theWrp.itemInt() > 1, eOutOfDomain);

	runPreExecAnew();
	mValueRec->initCurr(theWrp.itemInt());
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform anew execution with truth value.
*/
void PropFlipVarVi::execAnewState(Bll const RightNotLeft)
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
void PropFlipVarVi::execAnewStatRand(Rnd & theRnd)
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
void PropFlipVarVi::execAnewDynaRand(Rnd & theRnd)
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
void PropFlipVarVi::execAnewFlip()
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
void PropFlipVarVi::execIncrValue(Int const & theInt)
{
	WatchError
	Warn(theInt < 0 || theInt > 1, eOutOfDomain);

	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), theInt);
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}




/*!
	Perform incremental execution with a value wrap.
*/
void PropFlipVarVi::execIncrWrap(Wrp const & theWrp)
{
	WatchError
	Warn(theWrp.itemInt() < 0 || theWrp.itemInt() > 1, eOutOfDomain);

	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), theWrp.itemInt());
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with a truth value.
*/
void PropFlipVarVi::execIncrState(Bll const RightNotLeft)
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
void PropFlipVarVi::execIncrStatRand(Rnd & theRnd)
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
void PropFlipVarVi::execIncrDynaRand(Rnd & theRnd)
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
void PropFlipVarVi::execIncrFlip()
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
void PropFlipVarVi::simulAnewStatRand(Rnd & theRnd)
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
void PropFlipVarVi::simulAnewDynaRand(Rnd & theRnd)
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
	Perform anew simulation with a value wrap.
*/
void PropFlipVarVi::simulAnewValue(Int const & theInt)
{
	WatchError
	Warn(theInt < 0 || theInt > 1, eOutOfDomain);

	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), theInt);

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}


/*!
	Perform anew simulation with a value wrap.
*/
void PropFlipVarVi::simulAnewWrap(Wrp const & theWrp)
{
	WatchError
	Warn(theWrp.itemInt() < 0 || theWrp.itemInt() > 1, eOutOfDomain);

	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), theWrp.itemInt());

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}


/*!
	Perform anew simulation with a truth value.
*/
void PropFlipVarVi::simulAnewState(Bll RightNotLeft)
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
void PropFlipVarVi::simulAnewFlip()
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
void PropFlipVarVi::simulIncrStatRand(Rnd & theRnd)
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
void PropFlipVarVi::simulIncrDynaRand(Rnd & theRnd)
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
void PropFlipVarVi::simulIncrValue(Int const &theInt)
{
	WatchError
	Warn(theInt < 0 || theInt > 1, eOutOfDomain);

	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), theInt);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}


/*!
	Perform incremental simulation with a value wrap.
*/
void PropFlipVarVi::simulIncrWrap(Wrp const & theWrp)
{
	WatchError
	Warn(theWrp.itemInt() < 0 || theWrp.itemInt() > 1, eOutOfDomain);

	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), theWrp.itemInt());

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with a truth value.
*/
void PropFlipVarVi::simulIncrState(Bll const RightNotLeft)
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
void PropFlipVarVi::simulIncrFlip()
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
