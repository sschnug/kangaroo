/*!
	@file dynarangectlvarvf.cpp
	@brief The implementation file for DynaRangeCtlVarVf class.
	@details This is the implementation file for DynaRangeCtlVarVf class.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see dynarangectlvarvf.hpp
*/



#include "cbls/vars/rangevars/dynarangectlvarvf.hpp"



openKangarooSpace



/*!
	Define an integer range variable.
*/
Hdl DynaRangeCtlVarVf::def(Hdl const hdlSys, Flt const & StatLeft, Flt const & StatRight, Flt const & StepSize)
{
	WatchError
	DynaRangeCtlVarVf * tVar = new DynaRangeCtlVarVf(hdlSys, StatLeft, StatRight, StepSize);
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
	Set the range control expressions.
*/
void DynaRangeCtlVarVf::setDynaRangeX(Fss const theFss, Prm const & LeftValue, Prm const & RightValue)
{
	EvalTblFlt const & tPxtTbl = EvalTblFlt::refc(this->mTermSys.SysHdl);

	mDynaLeftTerm = this->mTermSys.ptrmTerm(LeftValue.TermGen, LeftValue.TermHdl);

	Loc const tLeftLoc = getPxLoc(theFss, mDynaLeftTerm, LeftValue.PrmSpec);
	mDynaLeftRec = tPxtTbl.ptrcEvalRec(tLeftLoc);

	mDynaRightTerm = this->mTermSys.ptrmTerm(RightValue.TermGen, RightValue.TermHdl);
	Loc const tRightLoc = getPxLoc(theFss, mDynaRightTerm, RightValue.PrmSpec);
	mDynaRightRec = tPxtTbl.ptrcEvalRec(tRightLoc);
	if (!mTermSys.chkExecMode(NullComp))
		updateDomain();
}




/*!
	The constructor.
*/
DynaRangeCtlVarVf::DynaRangeCtlVarVf(Hdl const hdlSys, Flt const & StatLeft, Flt const & StatRight, Flt const & StepSize) :
		RangeVarVf(hdlSys), mStatLeftValue(StatLeft), mStatRightValue(StatRight), mStepSizeValue(StepSize),
		mDynaLeftTerm(Null), mDynaRightTerm(Null), mDynaLeftRec(Null), mDynaRightRec(Null),
		mDynaLeftValue(mStatLeftValue), mDynaRightValue(mStatRightValue)
{
	WatchError
	Warn(mStatLeftValue > mStatRightValue, eRangeDefn);
	Warn(StepSize <= 0, eStepSize);

	setTermCls(TermStub<DynaRangeCtlVarVf>::TermCls);
	setTermHvl(calcTermHvl());
	CatchError
}


/*!
	The duplicator.
*/
DynaRangeCtlVarVf::DynaRangeCtlVarVf(DynaRangeCtlVarVf const & that) : RangeVarVf(that),
		mStatLeftValue(that.mStatLeftValue), mStatRightValue(that.mStatRightValue),
		mStepSizeValue(that.mStepSizeValue)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}


/*!
	The assigner.
*/
DynaRangeCtlVarVf const & DynaRangeCtlVarVf::operator = (DynaRangeCtlVarVf const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}


/*!
	The destructor.
*/
DynaRangeCtlVarVf::~DynaRangeCtlVarVf()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll DynaRangeCtlVarVf::identical(Var const & that) const
{
	WatchError
	if (that.TermCls != TermStub<DynaRangeCtlVarVf>::TermCls)
		return false;
	DynaRangeCtlVarVf const & tVar = scast<DynaRangeCtlVarVf const &>(that);
	return eq<Flt,Bll>::iof(tVar.mStatRightValue, mStatRightValue) &&
			eq<Flt,Bll>::iof(tVar.mStatLeftValue, mStatLeftValue) &&
						eq<Flt,Bll>::iof(tVar.mStepSizeValue, mStepSizeValue);
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll DynaRangeCtlVarVf::identical(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	if (that->TermCls != TermStub<DynaRangeCtlVarVf>::TermCls)
		return false;
	DynaRangeCtlVarVf const * tVar = scast<DynaRangeCtlVarVf const *>(that);
	return eq<Flt,Bll>::iof(tVar->mStatRightValue, mStatRightValue) &&
			eq<Flt,Bll>::iof(tVar->mStatLeftValue, mStatLeftValue) &&
			eq<Flt,Bll>::iof(tVar->mStepSizeValue, mStepSizeValue);
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll DynaRangeCtlVarVf::assignable(Var const & that) const
{
	WatchError
	if (that.TermTyp != TermStub<RangeVarVf>::TermTyp)
		return false;
	Flt const & tValueFlt = RangeVarVf::cast(that).ValueRec().CurrData();
	return tValueFlt >= mStatLeftValue && tValueFlt <= mStatRightValue;
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll DynaRangeCtlVarVf::assignable(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	if (that->TermTyp != TermStub<RangeVarVf>::TermTyp)
		return false;
	Flt const & tValueFlt = RangeVarVf::cast(that)->ValueRec().CurrData();
	return tValueFlt >= mStatLeftValue && tValueFlt <= mStatRightValue;
	CatchError
}



/*!
	Whether two variables are swappable?
*/
Bll DynaRangeCtlVarVf::swappable(Var const & that) const
{
	WatchError
	if (that.TermTyp != TermStub<RangeVarVf>::TermTyp)
		return false;
	Flt const & tValueFlt = RangeVarVf::cast(that).ValueRec().CurrData();
	return tValueFlt >= mStatLeftValue && tValueFlt <= mStatRightValue && that.assignable(this);
	CatchError
}



/*!
	Whether two variables are swappable?
*/
Bll DynaRangeCtlVarVf::swappable(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	if (that->TermTyp != TermStub<RangeVarVf>::TermTyp)
		return false;
	Flt const & tValueFlt = RangeVarVf::cast(that)->ValueRec().CurrData();
	return tValueFlt >= mStatLeftValue && tValueFlt <= mStatRightValue && that->assignable(this);
	CatchError
}


/*!
	Valid with respect to the static domain?
*/
Bll DynaRangeCtlVarVf::validStat(Flt const & theFlt) const
{
	WatchError
	return theFlt >= mStatLeftValue && theFlt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll DynaRangeCtlVarVf::validDyna(Flt const & theFlt) const
{
	WatchError
	return theFlt >= mDynaLeftValue && theFlt <= mDynaRightValue;
	CatchError
}



/*!
	Valid with respect to the static domain?
*/
Bll DynaRangeCtlVarVf::validStat(Wrp const & theWrp) const
{
	WatchError
	Flt const & tValueFlt = theWrp.itemFlt();
	return tValueFlt >= mStatLeftValue && tValueFlt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll DynaRangeCtlVarVf::validDyna(Wrp const & theWrp) const
{
	WatchError
	Flt const & tValueFlt = theWrp.itemFlt();
	return tValueFlt >= mDynaLeftValue && tValueFlt <= mDynaRightValue;
	CatchError
}



/*!
	Whether the current value is the static right value?
*/
Bll DynaRangeCtlVarVf::chkCurrStatRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mStatRightValue);
	CatchError
}



/*!
	Whether the current value is the static left value?
*/
Bll DynaRangeCtlVarVf::chkCurrStatLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mStatLeftValue);
	CatchError
}



/*!
	Whether the current value is the dynamic right value?
*/
Bll DynaRangeCtlVarVf::chkCurrDynaRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mDynaRightValue);
	CatchError
}



/*!
	Whether the current value is the dynamic left value?
*/
Bll DynaRangeCtlVarVf::chkCurrDynaLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mDynaLeftValue);
	CatchError
}



/*!
	Whether the next value is the static right value?
*/
Bll DynaRangeCtlVarVf::chkNextStatRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mStatRightValue);
	CatchError
}



/*!
	Whether the next value is the static left value?
*/
Bll DynaRangeCtlVarVf::chkNextStatLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mStatLeftValue);
	CatchError
}



/*!
	Whether the next value is the dynamic right value?
*/
Bll DynaRangeCtlVarVf::chkNextDynaRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mDynaRightValue);
	CatchError
}



/*!
	Whether the next value is the left value?
*/
Bll DynaRangeCtlVarVf::chkNextDynaLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mDynaLeftValue);
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Flt DynaRangeCtlVarVf::StatRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mStatLeftValue, mStatRightValue);
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Flt DynaRangeCtlVarVf::DynaRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mDynaLeftValue, mDynaRightValue);
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Wrp DynaRangeCtlVarVf::StatRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mStatLeftValue, mStatRightValue));
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Wrp DynaRangeCtlVarVf::DynaRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mDynaLeftValue, mDynaRightValue));
	CatchError
}



/*!
	The static left value.
*/
Flt DynaRangeCtlVarVf::StatLeftValue() const
{
	WatchError
	return mStatLeftValue;
	CatchError
}


/*!
	The static right value.
*/
Flt DynaRangeCtlVarVf::StatRightValue() const
{
	WatchError
	return mStatRightValue;
	CatchError
}


/*!
	The dynamic left value.
*/
Flt DynaRangeCtlVarVf::DynaLeftValue() const
{
	WatchError
	return mDynaLeftValue;
	CatchError
}


/*!
	The dynamic right value.
*/
Flt DynaRangeCtlVarVf::DynaRightValue() const
{
	WatchError
	return mDynaRightValue;
	CatchError
}



/*!
	The step size value.
*/
Flt DynaRangeCtlVarVf::StepSizeValue() const
{
	WatchError
	return mStepSizeValue;
	CatchError
}


/*!
	Wrap for the static left value.
*/
Wrp DynaRangeCtlVarVf::StatLeftWrap() const
{
	WatchError
	return Wrp(mStatLeftValue);
	CatchError
}


/*!
	Wrap for the static right value.
*/
Wrp DynaRangeCtlVarVf::StatRightWrap() const
{
	WatchError
	return Wrp(mStatRightValue);
	CatchError
}


/*!
	Wrap for the dynamic left value.
*/
Wrp DynaRangeCtlVarVf::DynaLeftWrap() const
{
	WatchError
	return Wrp(mDynaLeftValue);
	CatchError
}


/*!
	Wrap for the dynamic right value.
*/
Wrp DynaRangeCtlVarVf::DynaRightWrap() const
{
	WatchError
	return Wrp(mDynaRightValue);
	CatchError
}



/*!
	Wrap for the step size value.
*/
Wrp DynaRangeCtlVarVf::StepSizeWrap() const
{
	WatchError
	return Wrp(mStepSizeValue);
	CatchError
}



/*!
	Perform anew execution with a value.
*/
void DynaRangeCtlVarVf::execAnewValue(Flt const & theFlt)
{
	WatchError
	Warn(mStatLeftValue > theFlt, eOutOfRange);
	Warn(mStatRightValue < theFlt, eOutOfRange);

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
void DynaRangeCtlVarVf::execAnewWrap(Wrp const & theWrp)
{
	WatchError
	Warn(mStatLeftValue > theWrp.itemFlt(), eOutOfRange);
	Warn(mStatRightValue < theWrp.itemFlt(), eOutOfRange);

	runPreExecAnew();
	mValueRec->initCurr(theWrp.itemFlt());
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform anew execution wth a random value from the static domain.
*/
void DynaRangeCtlVarVf::execAnewStatRand(Rnd & theRnd)
{
	WatchError
	runPreExecAnew();
	mValueRec->initCurr(uniform(theRnd, mStatLeftValue, mStatRightValue));
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform anew execution wth a random value from the dynamic domain.
*/
void DynaRangeCtlVarVf::execAnewDynaRand(Rnd & theRnd)
{
	WatchError
	runPreExecAnew();
	mValueRec->initCurr(uniform(theRnd, mDynaLeftValue, mDynaRightValue));
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform incremental execution with a value.
*/
void DynaRangeCtlVarVf::execIncrValue(Flt const & theFlt)
{
	WatchError
	Warn(mStatLeftValue > theFlt, eOutOfRange);
	Warn(mStatRightValue < theFlt, eOutOfRange);

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
void DynaRangeCtlVarVf::execIncrWrap(Wrp const & theWrp)
{
	WatchError
	Warn(mStatLeftValue > theWrp.itemFlt(), eOutOfRange);
	Warn(mStatRightValue < theWrp.itemFlt(), eOutOfRange);

	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), theWrp.itemFlt());
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with a random value from the static domain.
*/
void DynaRangeCtlVarVf::execIncrStatRand(Rnd & theRnd)
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), uniform(theRnd, mStatLeftValue, mStatRightValue));
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with a random value from the dynamic domain.
*/
void DynaRangeCtlVarVf::execIncrDynaRand(Rnd & theRnd)
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(),
		uniform(theRnd, mDynaLeftValue, mDynaRightValue));
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with the static left value.
*/
void DynaRangeCtlVarVf::execIncrStatLeft()
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), mStatLeftValue);
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with the dynamic left value.
*/
void DynaRangeCtlVarVf::execIncrDynaLeft()
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), mDynaLeftValue);
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with the succeeding value.
*/
void DynaRangeCtlVarVf::execIncrSuccessor()
{
	WatchError
	Warn(mValueRec->CurrBuff >= mStatRightValue, eOutOfRange);

	runPreExecIncr();
	mValueRec->copytoPrevBuff();
	mValueRec->CurrBuff += mStepSizeValue;
	mValueRec->PrevClk = mTermSys.ExecClk();
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with the preceeding value.
*/
void DynaRangeCtlVarVf::execIncrPredecessor()
{
	WatchError
	Warn(mValueRec->CurrBuff <= mStatLeftValue, eOutOfRange);

	runPreExecIncr();
	mValueRec->copytoPrevBuff();
	mValueRec->CurrBuff -= mStepSizeValue;
	mValueRec->PrevClk = mTermSys.ExecClk();
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with the static right value.
*/
void DynaRangeCtlVarVf::execIncrStatRight()
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), mStatRightValue);
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with the dynamic right value.
*/
void DynaRangeCtlVarVf::execIncrDynaRight()
{
	WatchError
	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), mDynaRightValue);
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}


/*!
	Perform anew simulation with a random value from the static domain.
*/
void DynaRangeCtlVarVf::simulAnewStatRand(Rnd & theRnd)
{
	WatchError
	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), uniform(theRnd, mStatLeftValue, mStatRightValue));

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Perform anew simulation with a random value from the dynamic domain.
*/
void DynaRangeCtlVarVf::simulAnewDynaRand(Rnd & theRnd)
{
	WatchError
	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(),
		uniform(theRnd, mDynaLeftValue, mDynaRightValue));

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}


/*!
	Perform anew simulation with a value.
*/
void DynaRangeCtlVarVf::simulAnewValue(Flt const & theFlt)
{
	WatchError
	Warn(mStatLeftValue > theFlt, eOutOfRange);
	Warn(mStatRightValue < theFlt, eOutOfRange);

	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), theFlt);

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with a value.
*/
void DynaRangeCtlVarVf::simulIncrValue(Flt const & theFlt)
{
	WatchError
	Warn(mStatLeftValue > theFlt, eOutOfRange);
	Warn(mStatRightValue < theFlt, eOutOfRange);

	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), theFlt);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform anew simulation with a value wrap.
*/
void DynaRangeCtlVarVf::simulAnewWrap(Wrp const & theWrp)
{
	WatchError
	Warn(mStatLeftValue > theWrp.itemFlt(), eOutOfRange);
	Warn(mStatRightValue < theWrp.itemFlt(), eOutOfRange);

	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), theWrp.itemFlt());

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}




/*!
	Perform incremental simulation with a random value from the static domain.
*/
void DynaRangeCtlVarVf::simulIncrStatRand(Rnd & theRnd)
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), uniform(theRnd, mStatLeftValue, mStatRightValue));

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with a random value from the dynamic domain.
*/
void DynaRangeCtlVarVf::simulIncrDynaRand(Rnd & theRnd)
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(),
			uniform(theRnd, mDynaLeftValue, mDynaRightValue));

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with a value wrap.
*/
void DynaRangeCtlVarVf::simulIncrWrap(Wrp const & theWrp)
{
	WatchError
	Warn(mStatLeftValue > theWrp.itemFlt(), eOutOfRange);
	Warn(mStatRightValue < theWrp.itemFlt(), eOutOfRange);

	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), theWrp.itemFlt());

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with the static left value.
*/
void DynaRangeCtlVarVf::simulIncrStatLeft()
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), mStatLeftValue);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with the dynamic left value.
*/
void DynaRangeCtlVarVf::simulIncrDynaLeft()
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), mDynaLeftValue);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with the succeeding value.
*/
void DynaRangeCtlVarVf::simulIncrSuccessor()
{
	WatchError
	Warn(mValueRec->NextBuff >= mStatRightValue, eOutOfRange);

	runPreSimulIncr();
	mValueRec->NextBuff += mStepSizeValue;
	mValueRec->NextClk = mTermSys.SimulClk();

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with the preceding value.
*/
void DynaRangeCtlVarVf::simulIncrPredecessor()
{
	WatchError
	Warn(mValueRec->NextBuff <= mStatLeftValue, eOutOfRange);

	runPreSimulIncr();
	mValueRec->NextBuff -= mStepSizeValue;
	mValueRec->NextClk = mTermSys.SimulClk();

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with the static right value.
*/
void DynaRangeCtlVarVf::simulIncrStatRight()
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), mStatRightValue);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}


/*!
	Perform incremental simulation with the dynamic right value.
*/
void DynaRangeCtlVarVf::simulIncrDynaRight()
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), mDynaRightValue);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Domain update defined?
*/
inline Bll DynaRangeCtlVarVf::DomainUpdateDefined() const
{
	WatchError
	return true;
	CatchError
}


/*!
	Update the dynamic domain.
*/
void DynaRangeCtlVarVf::updateDomain()
{
	WatchError
	Warn(!mDynaLeftTerm, eNullPointer);
	Warn(!mDynaRightTerm, eNullPointer);
	Warn(!mDynaLeftRec, eNullPointer);
	Warn(!mDynaRightRec, eNullPointer);

	#if CompLazy
	Term::performExec(mDynaLeftTerm);
	Term::performExec(mDynaRightTerm);
	#endif // CompLazy

	if (mDynaLeftRec->CurrData() <= mStatLeftValue)
		mDynaLeftValue = mStatLeftValue;
	else
		mDynaLeftValue = mDynaLeftRec->CurrData();

	if (mDynaRightRec->CurrData() >= mStatRightValue)
		mDynaRightValue = mStatRightValue;
	else
		mDynaRightValue = mDynaRightRec->CurrData();
	Alert(mDynaRightValue < mDynaLeftValue, eInvalidRange);
	CatchError
}



closeKangarooSpace
