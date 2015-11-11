/*!
	@file dynarangechgvarvf.cpp
	@brief The implementation file for DynaRangeChgVarVf class.
	@details This is the implementation file for DynaRangeChgVarVf class.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see dynarangechgvarvf.hpp
*/



#include "cbls/vars/rangevars/dynarangechgvarvf.hpp"



openKangarooSpace



/*!
	Define an integer range variable.
*/
Hdl DynaRangeChgVarVf::def(Hdl const hdlSys, Flt const & StatLeft, Flt const & StatRight, Flt const & StepSize)
{
	WatchError
	DynaRangeChgVarVf * tVar = new DynaRangeChgVarVf(hdlSys, StatLeft, StatRight, StepSize);
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
	Set the dynamic range.
*/
void DynaRangeChgVarVf::setDynaRange(Flt const LeftValue, Flt const RightValue)
{
	WatchError
	if (LeftValue <= mStatLeftValue)
		mDynaLeftValue = mStatLeftValue;
	else
		mDynaLeftValue = LeftValue;

	if (RightValue >= mStatRightValue)
		mDynaRightValue = mStatRightValue;
	else
		mDynaRightValue = RightValue;
	Alert(mDynaRightValue < mDynaLeftValue, eInvalidRange);
	CatchError
}



/*!
	Set the left boundary of the dynamic range.
*/
void DynaRangeChgVarVf::setDynaLeft(Flt const LeftValue)
{
	WatchError
	if (LeftValue <= mStatLeftValue)
		mDynaLeftValue = mStatLeftValue;
	else
		mDynaLeftValue = LeftValue;
	Alert(mDynaRightValue < mDynaLeftValue, eInvalidRange);
	CatchError
}



/*!
	Set the right boundary of the dynamic range.
*/
void DynaRangeChgVarVf::setDynaRight(Flt const RightValue)
{
	WatchError
	if (RightValue >= mStatRightValue)
		mDynaRightValue = mStatRightValue;
	else
		mDynaRightValue = RightValue;
	Alert(mDynaRightValue < mDynaLeftValue, eInvalidRange);
	CatchError
}



/*!
	The constructor.
*/
DynaRangeChgVarVf::DynaRangeChgVarVf(Hdl const hdlSys, Flt const & StatLeft, Flt const & StatRight, Flt const & StepSize) :
		RangeVarVf(hdlSys), mStatLeftValue(StatLeft), mStatRightValue(StatRight), mStepSizeValue(StepSize),
		mDynaLeftValue(mStatLeftValue), mDynaRightValue(mStatRightValue)
{
	WatchError
	Warn(mStatLeftValue > mStatRightValue, eRangeDefn);
	Warn(StepSize <= 0, eStepSize);

	setTermCls(TermStub<DynaRangeChgVarVf>::TermCls);
	setTermHvl(calcTermHvl());
	CatchError
}


/*!
	The duplicator.
*/
DynaRangeChgVarVf::DynaRangeChgVarVf(DynaRangeChgVarVf const & that) : RangeVarVf(that),
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
DynaRangeChgVarVf const & DynaRangeChgVarVf::operator = (DynaRangeChgVarVf const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}


/*!
	The destructor.
*/
DynaRangeChgVarVf::~DynaRangeChgVarVf()
{
	WatchError
	//	nothing to be done.
	CatchError
}




/*!
	Whether two variables are identical?
*/
Bll DynaRangeChgVarVf::identical(Var const & that) const
{
	WatchError
	if (that.TermCls != TermStub<DynaRangeChgVarVf>::TermCls)
		return false;
	DynaRangeChgVarVf const & tVar = scast<DynaRangeChgVarVf const &>(that);
	return eq<Flt,Bll>::iof(tVar.mStatRightValue, mStatRightValue) &&
			eq<Flt,Bll>::iof(tVar.mStatLeftValue, mStatLeftValue) &&
						eq<Flt,Bll>::iof(tVar.mStepSizeValue, mStepSizeValue);
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll DynaRangeChgVarVf::identical(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	if (that->TermCls != TermStub<DynaRangeChgVarVf>::TermCls)
		return false;
	DynaRangeChgVarVf const * tVar = scast<DynaRangeChgVarVf const *>(that);
	return eq<Flt,Bll>::iof(tVar->mStatRightValue, mStatRightValue) &&
			eq<Flt,Bll>::iof(tVar->mStatLeftValue, mStatLeftValue) &&
			eq<Flt,Bll>::iof(tVar->mStepSizeValue, mStepSizeValue);
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll DynaRangeChgVarVf::assignable(Var const & that) const
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
Bll DynaRangeChgVarVf::assignable(Var const * that) const
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
Bll DynaRangeChgVarVf::swappable(Var const & that) const
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
Bll DynaRangeChgVarVf::swappable(Var const * that) const
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
Bll DynaRangeChgVarVf::validStat(Flt const & theFlt) const
{
	WatchError
	return theFlt >= mStatLeftValue && theFlt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll DynaRangeChgVarVf::validDyna(Flt const & theFlt) const
{
	WatchError
	return theFlt >= mDynaLeftValue && theFlt <= mDynaRightValue;
	CatchError
}



/*!
	Valid with respect to the static domain?
*/
Bll DynaRangeChgVarVf::validStat(Wrp const & theWrp) const
{
	WatchError
	Flt const & tValueFlt = theWrp.itemFlt();
	return tValueFlt >= mStatLeftValue && tValueFlt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll DynaRangeChgVarVf::validDyna(Wrp const & theWrp) const
{
	WatchError
	Flt const & tValueFlt = theWrp.itemFlt();
	return tValueFlt >= mDynaLeftValue && tValueFlt <= mDynaRightValue;
	CatchError
}



/*!
	Whether the current value is the static right value?
*/
Bll DynaRangeChgVarVf::chkCurrStatRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mStatRightValue);
	CatchError
}



/*!
	Whether the current value is the static left value?
*/
Bll DynaRangeChgVarVf::chkCurrStatLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mStatLeftValue);
	CatchError
}



/*!
	Whether the current value is the dynamic right value?
*/
Bll DynaRangeChgVarVf::chkCurrDynaRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mDynaRightValue);
	CatchError
}



/*!
	Whether the current value is the dynamic left value?
*/
Bll DynaRangeChgVarVf::chkCurrDynaLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mDynaLeftValue);
	CatchError
}



/*!
	Whether the next value is the static right value?
*/
Bll DynaRangeChgVarVf::chkNextStatRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mStatRightValue);
	CatchError
}



/*!
	Whether the next value is the static left value?
*/
Bll DynaRangeChgVarVf::chkNextStatLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mStatLeftValue);
	CatchError
}



/*!
	Whether the next value is the dynamic right value?
*/
Bll DynaRangeChgVarVf::chkNextDynaRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mDynaRightValue);
	CatchError
}



/*!
	Whether the next value is the left value?
*/
Bll DynaRangeChgVarVf::chkNextDynaLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mDynaLeftValue);
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Flt DynaRangeChgVarVf::StatRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mStatLeftValue, mStatRightValue);
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Flt DynaRangeChgVarVf::DynaRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mDynaLeftValue, mDynaRightValue);
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Wrp DynaRangeChgVarVf::StatRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mStatLeftValue, mStatRightValue));
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Wrp DynaRangeChgVarVf::DynaRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mDynaLeftValue, mDynaRightValue));
	CatchError
}



/*!
	The static left value.
*/
Flt DynaRangeChgVarVf::StatLeftValue() const
{
	WatchError
	return mStatLeftValue;
	CatchError
}


/*!
	The static right value.
*/
Flt DynaRangeChgVarVf::StatRightValue() const
{
	WatchError
	return mStatRightValue;
	CatchError
}


/*!
	The dynamic left value.
*/
Flt DynaRangeChgVarVf::DynaLeftValue() const
{
	WatchError
	return mDynaLeftValue;
	CatchError
}


/*!
	The dynamic right value.
*/
Flt DynaRangeChgVarVf::DynaRightValue() const
{
	WatchError
	return mDynaRightValue;
	CatchError
}



/*!
	The step size value.
*/
Flt DynaRangeChgVarVf::StepSizeValue() const
{
	WatchError
	return mStepSizeValue;
	CatchError
}


/*!
	Wrap for the static left value.
*/
Wrp DynaRangeChgVarVf::StatLeftWrap() const
{
	WatchError
	return Wrp(mStatLeftValue);
	CatchError
}


/*!
	Wrap for the static right value.
*/
Wrp DynaRangeChgVarVf::StatRightWrap() const
{
	WatchError
	return Wrp(mStatRightValue);
	CatchError
}


/*!
	Wrap for the dynamic left value.
*/
Wrp DynaRangeChgVarVf::DynaLeftWrap() const
{
	WatchError
	return Wrp(mDynaLeftValue);
	CatchError
}


/*!
	Wrap for the dynamic right value.
*/
Wrp DynaRangeChgVarVf::DynaRightWrap() const
{
	WatchError
	return Wrp(mDynaRightValue);
	CatchError
}



/*!
	Wrap for the step size value.
*/
Wrp DynaRangeChgVarVf::StepSizeWrap() const
{
	WatchError
	return Wrp(mStepSizeValue);
	CatchError
}



/*!
	Perform anew execution with a value.
*/
void DynaRangeChgVarVf::execAnewValue(Flt const & theFlt)
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
void DynaRangeChgVarVf::execAnewWrap(Wrp const & theWrp)
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
void DynaRangeChgVarVf::execAnewStatRand(Rnd & theRnd)
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
void DynaRangeChgVarVf::execAnewDynaRand(Rnd & theRnd)
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
void DynaRangeChgVarVf::execIncrValue(Flt const & theFlt)
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
void DynaRangeChgVarVf::execIncrWrap(Wrp const & theWrp)
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
void DynaRangeChgVarVf::execIncrStatRand(Rnd & theRnd)
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
void DynaRangeChgVarVf::execIncrDynaRand(Rnd & theRnd)
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
void DynaRangeChgVarVf::execIncrStatLeft()
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
void DynaRangeChgVarVf::execIncrDynaLeft()
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
void DynaRangeChgVarVf::execIncrSuccessor()
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
void DynaRangeChgVarVf::execIncrPredecessor()
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
void DynaRangeChgVarVf::execIncrStatRight()
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
void DynaRangeChgVarVf::execIncrDynaRight()
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
void DynaRangeChgVarVf::simulAnewStatRand(Rnd & theRnd)
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
void DynaRangeChgVarVf::simulAnewDynaRand(Rnd & theRnd)
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
void DynaRangeChgVarVf::simulAnewValue(Flt const & theFlt)
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
	Perform anew simulation with a value wrap.
*/
void DynaRangeChgVarVf::simulAnewWrap(Wrp const & theWrp)
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
void DynaRangeChgVarVf::simulIncrStatRand(Rnd & theRnd)
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
void DynaRangeChgVarVf::simulIncrDynaRand(Rnd & theRnd)
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
	Perform incremental simulation with a value.
*/
void DynaRangeChgVarVf::simulIncrValue(Flt const & theFlt)
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
	Perform incremental simulation with a value wrap.
*/
void DynaRangeChgVarVf::simulIncrWrap(Wrp const & theWrp)
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
void DynaRangeChgVarVf::simulIncrStatLeft()
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
void DynaRangeChgVarVf::simulIncrDynaLeft()
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
void DynaRangeChgVarVf::simulIncrSuccessor()
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
void DynaRangeChgVarVf::simulIncrPredecessor()
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
void DynaRangeChgVarVf::simulIncrStatRight()
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
void DynaRangeChgVarVf::simulIncrDynaRight()
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), mDynaRightValue);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



closeKangarooSpace
