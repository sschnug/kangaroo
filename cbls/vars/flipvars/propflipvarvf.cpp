/*!
	@file propflipvarvf.cpp
	@brief The implementation file for PropFlipVarVf class.
	@details This is the implementation file for PropFlipVarVf class.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see propflipvarvf.hpp
*/



#include "cbls/vars/flipvars/propflipvarvf.hpp"



openKangarooSpace



/*!
	Define an integer range variable.
*/
Hdl PropFlipVarVf::def(Hdl const hdlSys)
{
	WatchError
	PropFlipVarVf * tVar = new PropFlipVarVf(hdlSys);
	Hdl const tHdl = tVar->defSysVar();
	if (tHdl != InvHdl) { delete tVar; return tHdl; }

	EvalTblFlt & tValueTbl = EvalTblFlt::refm(hdlSys);
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
PropFlipVarVf::PropFlipVarVf(Hdl const hdlSys) : FlipVarVf(hdlSys)
{
	WatchError
	setTermCls(TermStub<PropFlipVarVf>::TermCls);
	setTermHvl(calcTermHvl());
	CatchError
}


/*!
	The duplicator.
*/
PropFlipVarVf::PropFlipVarVf(PropFlipVarVf const & that) : FlipVarVf(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}


/*!
	The assigner.
*/
PropFlipVarVf const & PropFlipVarVf::operator = (PropFlipVarVf const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}


/*!
	The destructor.
*/
PropFlipVarVf::~PropFlipVarVf()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll PropFlipVarVf::identical(Var const & that) const
{
	WatchError
	return (that.TermCls == TermStub<PropFlipVarVf>::TermCls);
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll PropFlipVarVf::identical(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	return (that->TermCls == TermStub<PropFlipVarVf>::TermCls);
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll PropFlipVarVf::assignable(Var const & that) const
{
	WatchError
	return (that.TermTyp == TermStub<FlipVarVf>::TermTyp);
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll PropFlipVarVf::assignable(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	return (that->TermTyp == TermStub<FlipVarVf>::TermTyp);
	CatchError
}



/*!
	Whether two variables are swappable?
*/
Bll PropFlipVarVf::swappable(Var const & that) const
{
	WatchError
	return (that.TermTyp == TermStub<FlipVarVf>::TermTyp);
	CatchError
}



/*!
	Whether two variables are swappable?
*/
Bll PropFlipVarVf::swappable(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	return (that->TermTyp == TermStub<FlipVarVf>::TermTyp);
	CatchError
}



/*!
	Valid with respect to the valid?
*/
Bll PropFlipVarVf::validValue(Flt const & theFlt) const
{
	WatchError
	return theFlt >= 0.0 && theFlt <= 1.0;
	CatchError
}



/*!
	Valid with respect to the static domain?
*/
Bll PropFlipVarVf::validStat(Wrp const & theWrp) const
{
	WatchError
	return theWrp.itemFlt() >= 0.0 && theWrp.itemFlt() <= 1.0;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll PropFlipVarVf::validDyna(Wrp const & theWrp) const
{
	WatchError
	return theWrp.itemFlt() >= 0.0 && theWrp.itemFlt() <= 1.0;
	CatchError
}



/*!
	Whether the current value is the right value?
*/
Bll PropFlipVarVf::chkCurrRight() const
{
	WatchError
	return tc<Flt,Bll>::iof(mValueRec->CurrBuff);
	CatchError
}



/*!
	Whether the current value is the left value?
*/
Bll PropFlipVarVf::chkCurrLeft() const
{
	WatchError
	return !tc<Flt,Bll>::iof(mValueRec->CurrBuff);
	CatchError
}




/*!
	Whether the next value is the right value?
*/
Bll PropFlipVarVf::chkNextRight() const
{
	WatchError
	return tc<Flt,Bll>::iof(mValueRec->NextBuff);
	CatchError
}



/*!
	Whether the next value is the left value?
*/
Bll PropFlipVarVf::chkNextLeft() const
{
	WatchError
	return !tc<Flt,Bll>::iof(mValueRec->NextBuff);
	CatchError
}




/*!
	Current state of the var.
*/
Bll PropFlipVarVf::CurrState() const
{
	WatchError
	return tc<Flt,Bll>::iof(mValueRec->CurrBuff);
	CatchError
}



/*!
	Next state of the var.
*/
Bll PropFlipVarVf::NextState() const
{
	WatchError
	return tc<Flt,Bll>::iof(mValueRec->NextData(mTermSys.SimulClk()));
	CatchError
}




/*!
	Random state of the var.
*/
Bll PropFlipVarVf::RandState(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd);
	CatchError
}




/*!
	State for a given wrap value.
*/
Bll PropFlipVarVf::WrapState(Wrp const & theWrp) const
{
	WatchError
	return tc<Flt,Bll>::iof(theWrp.itemFlt());
	CatchError
}




/*!
	Randomly chosen value.
*/
Flt PropFlipVarVf::RandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd);
	CatchError
}



/*!
	The left value.
*/
Flt PropFlipVarVf::LeftValue() const
{
	WatchError
	return false;
	CatchError
}



/*!
	The right value.
*/
Flt PropFlipVarVf::RightValue() const
{
	WatchError
	return true;
	CatchError
}



/*!
	The state value.
*/
Flt PropFlipVarVf::StateValue(Bll const RightNotLeft) const
{
	WatchError
	return RightNotLeft;
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Wrp PropFlipVarVf::StatRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(castFlt(uniform(theRnd)));
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Wrp PropFlipVarVf::DynaRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(castFlt(uniform(theRnd)));
	CatchError
}



/*!
	Wrap for the left value.
*/
Wrp PropFlipVarVf::LeftWrap() const
{
	WatchError
	return Wrp(castFlt(0.0));
	CatchError
}



/*!
	Wrap for the right value.
*/
Wrp PropFlipVarVf::RightWrap() const
{
	WatchError
	return Wrp(castFlt(1.0));
	CatchError
}



/*!
	Wrap of a given state.
*/
Wrp PropFlipVarVf::StateWrap(Bll const RightNotLeft) const
{
	WatchError
	return Wrp(castFlt(RightNotLeft));
	CatchError
}



/*!
	Perform anew execution with a value.
*/
void PropFlipVarVf::execAnewValue(Flt const & theFlt)
{
	WatchError
	Warn(theFlt < 0.0 || theFlt > 1.0, eOutOfDomain);

	runPreExecAnew();
	mValueRec->initCurr(theFlt);
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform anew execution with a value wrap.
*/
void PropFlipVarVf::execAnewWrap(Wrp const & theWrp)
{
	WatchError
	Warn(theWrp.itemFlt() < 0.0 || theWrp.itemFlt() > 1.0, eOutOfDomain);

	runPreExecAnew();
	mValueRec->initCurr(theWrp.itemFlt());
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform anew execution with truth value.
*/
void PropFlipVarVf::execAnewState(Bll const RightNotLeft)
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
void PropFlipVarVf::execAnewStatRand(Rnd & theRnd)
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
void PropFlipVarVf::execAnewDynaRand(Rnd & theRnd)
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
void PropFlipVarVf::execAnewFlip()
{
	WatchError
	runPreExecAnew();
	mValueRec->initCurr(!tc<Flt,Bll>::iof(mValueRec->CurrBuff));
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}




/*!
	Perform incremental execution with a value.
*/
void PropFlipVarVf::execIncrValue(Flt const & theFlt)
{
	WatchError
	Warn(theFlt < 0.0 || theFlt > 1.0, eOutOfDomain);

	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), theFlt);
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}




/*!
	Perform incremental execution with a value wrap.
*/
void PropFlipVarVf::execIncrWrap(Wrp const & theWrp)
{
	WatchError
	Warn(theWrp.itemFlt() < 0.0 || theWrp.itemFlt() > 1.0, eOutOfDomain);

	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), theWrp.itemFlt());
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with a truth value.
*/
void PropFlipVarVf::execIncrState(Bll const RightNotLeft)
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
void PropFlipVarVf::execIncrStatRand(Rnd & theRnd)
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
void PropFlipVarVf::execIncrDynaRand(Rnd & theRnd)
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
void PropFlipVarVf::execIncrFlip()
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), !tc<Flt,Bll>::iof(mValueRec->CurrBuff));
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform anew simulation with a random value from the static domain.
*/
void PropFlipVarVf::simulAnewStatRand(Rnd & theRnd)
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
void PropFlipVarVf::simulAnewDynaRand(Rnd & theRnd)
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
void PropFlipVarVf::simulAnewValue(Flt const & theFlt)
{
	WatchError
	Warn(theFlt < 0.0 || theFlt > 1.0, eOutOfDomain);

	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), theFlt);

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Perform anew simulation with a value wrap.
*/
void PropFlipVarVf::simulAnewWrap(Wrp const & theWrp)
{
	WatchError
	Warn(theWrp.itemFlt() < 0.0 || theWrp.itemFlt() > 1.0, eOutOfDomain);

	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), theWrp.itemFlt());

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}


/*!
	Perform anew simulation with a truth value.
*/
void PropFlipVarVf::simulAnewState(Bll RightNotLeft)
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
void PropFlipVarVf::simulAnewFlip()
{
	WatchError
	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), !tc<Flt,Bll>::iof(mValueRec->CurrBuff));

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}




/*!
	Perform incremental simulation with a random value from the static domain.
*/
void PropFlipVarVf::simulIncrStatRand(Rnd & theRnd)
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
void PropFlipVarVf::simulIncrDynaRand(Rnd & theRnd)
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
void PropFlipVarVf::simulIncrValue(Flt const & theFlt)
{
	WatchError
	Warn(theFlt < 0.0 || theFlt > 1.0, eOutOfDomain);

	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), theFlt);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with a value wrap.
*/
void PropFlipVarVf::simulIncrWrap(Wrp const & theWrp)
{
	WatchError
	Warn(theWrp.itemFlt() < 0.0 || theWrp.itemFlt() > 1.0, eOutOfDomain);

	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), theWrp.itemFlt());

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with a truth value.
*/
void PropFlipVarVf::simulIncrState(Bll const RightNotLeft)
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
void PropFlipVarVf::simulIncrFlip()
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), !tc<Flt,Bll>::iof(mValueRec->CurrBuff));

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



closeKangarooSpace
