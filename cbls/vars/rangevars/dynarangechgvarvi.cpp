/*!
	@file dynarangechgvarvi.cpp
	@brief The implementation file for DynaRangeChgVarVi class.
	@details This is the implementation file for DynaRangeChgVarVi class.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see dynarangechgvarvi.hpp
*/



#include "cbls/vars/rangevars/dynarangechgvarvi.hpp"



openKangarooSpace



/*!
	Define an integer range variable.
*/
Hdl DynaRangeChgVarVi::def(Hdl const hdlSys, Int const & StatLeft, Int const & StatRight)
{
	WatchError
	DynaRangeChgVarVi * tVar = new DynaRangeChgVarVi(hdlSys, StatLeft, StatRight);
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
	Set the dynamic range.
*/
void DynaRangeChgVarVi::setDynaRange(Int const LeftValue, Int const RightValue)
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
void DynaRangeChgVarVi::setDynaLeft(Int const LeftValue)
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
void DynaRangeChgVarVi::setDynaRight(Int const RightValue)
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
DynaRangeChgVarVi::DynaRangeChgVarVi(Hdl const hdlSys, Int const & StatLeft, Int const & StatRight) :
		RangeVarVi(hdlSys), mStatLeftValue(StatLeft), mStatRightValue(StatRight),
		mDynaLeftValue(mStatLeftValue), mDynaRightValue(mStatRightValue)
{
	WatchError
	Warn(mStatLeftValue > mStatRightValue, eRangeDefn);

	setTermCls(TermStub<DynaRangeChgVarVi>::TermCls);
	setTermHvl(calcTermHvl());
	CatchError
}


/*!
	The duplicator.
*/
DynaRangeChgVarVi::DynaRangeChgVarVi(DynaRangeChgVarVi const & that) : RangeVarVi(that),
		mStatLeftValue(that.mStatLeftValue), mStatRightValue(that.mStatRightValue)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}


/*!
	The assigner.
*/
DynaRangeChgVarVi const & DynaRangeChgVarVi::operator = (DynaRangeChgVarVi const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}


/*!
	The destructor.
*/
DynaRangeChgVarVi::~DynaRangeChgVarVi()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll DynaRangeChgVarVi::identical(Var const & that) const
{
	WatchError
	if (that.TermCls != TermStub<DynaRangeChgVarVi>::TermCls)
		return false;
	DynaRangeChgVarVi const & tVar = scast<DynaRangeChgVarVi const &>(that);
	return tVar.mStatRightValue == mStatRightValue && tVar.mStatLeftValue == mStatLeftValue;
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll DynaRangeChgVarVi::identical(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	if (that->TermCls != TermStub<DynaRangeChgVarVi>::TermCls)
		return false;
	DynaRangeChgVarVi const * tVar = scast<DynaRangeChgVarVi const *>(that);
	return tVar->mStatRightValue == mStatRightValue && tVar->mStatLeftValue == mStatLeftValue;
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll DynaRangeChgVarVi::assignable(Var const & that) const
{
	WatchError
	if (that.TermTyp != TermStub<RangeVarVi>::TermTyp)
		return false;
	Int const & tValueInt = RangeVarVi::cast(that).ValueRec().CurrData();
	return tValueInt >= mStatLeftValue && tValueInt <= mStatRightValue;
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll DynaRangeChgVarVi::assignable(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	if (that->TermTyp != TermStub<RangeVarVi>::TermTyp)
		return false;
	Int const & tValueInt = RangeVarVi::cast(that)->ValueRec().CurrData();
	return tValueInt >= mStatLeftValue && tValueInt <= mStatRightValue;
	CatchError
}



/*!
	Whether two variables are swappable?
*/
Bll DynaRangeChgVarVi::swappable(Var const & that) const
{
	WatchError
	if (that.TermTyp != TermStub<RangeVarVi>::TermTyp)
		return false;
	Int const & tValueInt = RangeVarVi::cast(that).ValueRec().CurrData();
	return tValueInt >= mStatLeftValue && tValueInt <= mStatRightValue && that.assignable(this);
	CatchError
}



/*!
	Whether two variables are swappable?
*/
Bll DynaRangeChgVarVi::swappable(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	if (that->TermTyp != TermStub<RangeVarVi>::TermTyp)
		return false;
	Int const & tValueInt = RangeVarVi::cast(that)->ValueRec().CurrData();
	return tValueInt >= mStatLeftValue && tValueInt <= mStatRightValue && that->assignable(this);
	CatchError
}



/*!
	Valid with respect to the static domain?
*/
Bll DynaRangeChgVarVi::validStat(Int const & theInt) const
{
	WatchError
	return theInt >= mStatLeftValue && theInt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll DynaRangeChgVarVi::validDyna(Int const & theInt) const
{
	WatchError
	return theInt >= mDynaLeftValue && theInt <= mDynaRightValue;
	CatchError
}



/*!
	Valid with respect to the static domain?
*/
Bll DynaRangeChgVarVi::validStat(Wrp const & theWrp) const
{
	WatchError
	Int const & tValueInt = theWrp.itemInt();
	return tValueInt >= mStatLeftValue && tValueInt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll DynaRangeChgVarVi::validDyna(Wrp const & theWrp) const
{
	WatchError
	Int const & tValueInt = theWrp.itemInt();
	return tValueInt >= mDynaLeftValue && tValueInt <= mDynaRightValue;
	CatchError
}



/*!
	Whether the current value is the static right value?
*/
Bll DynaRangeChgVarVi::chkCurrStatRight() const
{
	WatchError
	return mValueRec->CurrBuff == mStatRightValue;
	CatchError
}



/*!
	Whether the current value is the static left value?
*/
Bll DynaRangeChgVarVi::chkCurrStatLeft() const
{
	WatchError
	return mValueRec->CurrBuff == mStatLeftValue;
	CatchError
}



/*!
	Whether the current value is the dynamic right value?
*/
Bll DynaRangeChgVarVi::chkCurrDynaRight() const
{
	WatchError
	return mValueRec->CurrBuff == mDynaRightValue;
	CatchError
}



/*!
	Whether the current value is the dynamic left value?
*/
Bll DynaRangeChgVarVi::chkCurrDynaLeft() const
{
	WatchError
	return mValueRec->CurrBuff == mDynaLeftValue;
	CatchError
}



/*!
	Whether the next value is the static right value?
*/
Bll DynaRangeChgVarVi::chkNextStatRight() const
{
	WatchError
	return mValueRec->NextBuff == mStatRightValue;
	CatchError
}



/*!
	Whether the next value is the static left value?
*/
Bll DynaRangeChgVarVi::chkNextStatLeft() const
{
	WatchError
	return mValueRec->NextBuff == mStatLeftValue;
	CatchError
}



/*!
	Whether the next value is the dynamic right value?
*/
Bll DynaRangeChgVarVi::chkNextDynaRight() const
{
	WatchError
	return mValueRec->NextBuff == mDynaRightValue;
	CatchError
}



/*!
	Whether the next value is the left value?
*/
Bll DynaRangeChgVarVi::chkNextDynaLeft() const
{
	WatchError
	return mValueRec->NextBuff == mDynaLeftValue;
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Int DynaRangeChgVarVi::StatRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mStatLeftValue, mStatRightValue);
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Int DynaRangeChgVarVi::DynaRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mDynaLeftValue, mDynaRightValue);
	CatchError
}




/*!
	Random value chosen from the static domain.
*/
Wrp DynaRangeChgVarVi::StatRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mStatLeftValue, mStatRightValue));
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Wrp DynaRangeChgVarVi::DynaRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mDynaLeftValue, mDynaRightValue));
	CatchError
}



/*!
	The static left value.
*/
Int DynaRangeChgVarVi::StatLeftValue() const
{
	WatchError
	return mStatLeftValue;
	CatchError
}


/*!
	The static right value.
*/
Int DynaRangeChgVarVi::StatRightValue() const
{
	WatchError
	return mStatRightValue;
	CatchError
}


/*!
	The dynamic left value.
*/
Int DynaRangeChgVarVi::DynaLeftValue() const
{
	WatchError
	return mDynaLeftValue;
	CatchError
}


/*!
	The dynamic right value.
*/
Int DynaRangeChgVarVi::DynaRightValue() const
{
	WatchError
	return mDynaRightValue;
	CatchError
}



/*!
	The step size value.
*/
Int DynaRangeChgVarVi::StepSizeValue() const
{
	WatchError
	return 1;
	CatchError
}



/*!
	Wrap for the static left value.
*/
Wrp DynaRangeChgVarVi::StatLeftWrap() const
{
	WatchError
	return Wrp(mStatLeftValue);
	CatchError
}


/*!
	Wrap for the static right value.
*/
Wrp DynaRangeChgVarVi::StatRightWrap() const
{
	WatchError
	return Wrp(mStatRightValue);
	CatchError
}


/*!
	Wrap for the dynamic left value.
*/
Wrp DynaRangeChgVarVi::DynaLeftWrap() const
{
	WatchError
	return Wrp(mDynaLeftValue);
	CatchError
}


/*!
	Wrap for the dynamic right value.
*/
Wrp DynaRangeChgVarVi::DynaRightWrap() const
{
	WatchError
	return Wrp(mDynaRightValue);
	CatchError
}



/*!
	Wrap for the step size value.
*/
Wrp DynaRangeChgVarVi::StepSizeWrap() const
{
	WatchError
	return Wrp(castInt(1));
	CatchError
}



/*!
	Perform anew execution with a value.
*/
void DynaRangeChgVarVi::execAnewValue(Int const & theInt)
{
	WatchError
	Warn(mStatLeftValue > theInt, eOutOfRange);
	Warn(mStatRightValue < theInt, eOutOfRange);

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
void DynaRangeChgVarVi::execAnewWrap(Wrp const & theWrp)
{
	WatchError
	Warn(mStatLeftValue > theWrp.itemInt(), eOutOfRange);
	Warn(mStatRightValue < theWrp.itemInt(), eOutOfRange);

	runPreExecAnew();
	mValueRec->initCurr(theWrp.itemInt());
	#if ExecUpwdLazy
	runPostExecAnew();
	#endif
	CatchError
}



/*!
	Perform anew execution wth a random value from the static domain.
*/
void DynaRangeChgVarVi::execAnewStatRand(Rnd & theRnd)
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
void DynaRangeChgVarVi::execAnewDynaRand(Rnd & theRnd)
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
void DynaRangeChgVarVi::execIncrValue(Int const & theInt)
{
	WatchError
	Warn(mStatLeftValue > theInt, eOutOfRange);
	Warn(mStatRightValue < theInt, eOutOfRange);

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
void DynaRangeChgVarVi::execIncrWrap(Wrp const & theWrp)
{
	WatchError
	Warn(mStatLeftValue > theWrp.itemInt(), eOutOfRange);
	Warn(mStatRightValue < theWrp.itemInt(), eOutOfRange);

	runPreExecIncr();
	mValueRec->updtCurr(mTermSys.ExecClk(), theWrp.itemInt());
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with a random value from the static domain.
*/
void DynaRangeChgVarVi::execIncrStatRand(Rnd & theRnd)
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
void DynaRangeChgVarVi::execIncrDynaRand(Rnd & theRnd)
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
void DynaRangeChgVarVi::execIncrStatLeft()
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
void DynaRangeChgVarVi::execIncrDynaLeft()
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
void DynaRangeChgVarVi::execIncrSuccessor()
{
	WatchError
	Warn(mValueRec->CurrBuff >= mStatRightValue, eOutOfRange);

	runPreExecIncr();
	mValueRec->copytoPrevBuff();
	++mValueRec->CurrBuff;
	mValueRec->PrevClk = mTermSys.ExecClk();
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with the preceeding value.
*/
void DynaRangeChgVarVi::execIncrPredecessor()
{
	WatchError
	Warn(mValueRec->CurrBuff <= mStatLeftValue, eOutOfRange);

	runPreExecIncr();
	mValueRec->copytoPrevBuff();
	--mValueRec->CurrBuff;
	mValueRec->PrevClk = mTermSys.ExecClk();
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with the static right value.
*/
void DynaRangeChgVarVi::execIncrStatRight()
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
void DynaRangeChgVarVi::execIncrDynaRight()
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
void DynaRangeChgVarVi::simulAnewStatRand(Rnd & theRnd)
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
void DynaRangeChgVarVi::simulAnewDynaRand(Rnd & theRnd)
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
void DynaRangeChgVarVi::simulAnewValue(Int const & theInt)
{
	WatchError
	Warn(mStatLeftValue > theInt, eOutOfRange);
	Warn(mStatRightValue < theInt, eOutOfRange);

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
void DynaRangeChgVarVi::simulAnewWrap(Wrp const & theWrp)
{
	WatchError
	Warn(mStatLeftValue > theWrp.itemInt(), eOutOfRange);
	Warn(mStatRightValue < theWrp.itemInt(), eOutOfRange);

	runPreSimulAnew();
	mValueRec->initNext(mTermSys.SimulClk(), theWrp.itemInt());

	#if SimulUpwd
	runPostSimulAnew();
	#endif
	CatchError
}


/*!
	Perform incremental simulation with a random value from the static domain.
*/
void DynaRangeChgVarVi::simulIncrStatRand(Rnd & theRnd)
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
void DynaRangeChgVarVi::simulIncrDynaRand(Rnd & theRnd)
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
void DynaRangeChgVarVi::simulIncrValue(Int const & theInt)
{
	WatchError
	Warn(mStatLeftValue > theInt, eOutOfRange);
	Warn(mStatRightValue < theInt, eOutOfRange);

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
void DynaRangeChgVarVi::simulIncrWrap(Wrp const & theWrp)
{
	WatchError
	Warn(mStatLeftValue > theWrp.itemInt(), eOutOfRange);
	Warn(mStatRightValue < theWrp.itemInt(), eOutOfRange);

	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), theWrp.itemInt());

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with the static left value.
*/
void DynaRangeChgVarVi::simulIncrStatLeft()
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
void DynaRangeChgVarVi::simulIncrDynaLeft()
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
void DynaRangeChgVarVi::simulIncrSuccessor()
{
	WatchError
	Warn(mValueRec->NextBuff >= mStatRightValue, eOutOfRange);

	runPreSimulIncr();
	++mValueRec->NextBuff;
	mValueRec->NextClk = mTermSys.SimulClk();

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with the preceding value.
*/
void DynaRangeChgVarVi::simulIncrPredecessor()
{
	WatchError
	Warn(mValueRec->NextBuff <= mStatLeftValue, eOutOfRange);

	runPreSimulIncr();
	--mValueRec->NextBuff;
	mValueRec->NextClk = mTermSys.SimulClk();

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with the static right value.
*/
void DynaRangeChgVarVi::simulIncrStatRight()
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
void DynaRangeChgVarVi::simulIncrDynaRight()
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
