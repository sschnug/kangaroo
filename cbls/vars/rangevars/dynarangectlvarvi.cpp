/*!
	@file dynarangectlvarvi.cpp
	@brief The implementation file for DynaRangeCtlVarVi class.
	@details This is the implementation file for DynaRangeCtlVarVi class.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see dynarangectlvarvi.hpp
*/



#include "cbls/vars/rangevars/dynarangectlvarvi.hpp"



openKangarooSpace



/*!
	Define an integer range variable.
*/
Hdl DynaRangeCtlVarVi::def(Hdl const hdlSys, Int const & StatLeft, Int const & StatRight)
{
	WatchError
	DynaRangeCtlVarVi * tVar = new DynaRangeCtlVarVi(hdlSys, StatLeft, StatRight);
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
	Set the range control expressions.
*/
void DynaRangeCtlVarVi::setDynaRangeX(Fss const theFss, Prm const & LeftValue, Prm const & RightValue)
{
	EvalTblInt const & tPxtTbl = EvalTblInt::refc(this->mTermSys.SysHdl);

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
DynaRangeCtlVarVi::DynaRangeCtlVarVi(Hdl const hdlSys, Int const & StatLeft, Int const & StatRight) :
		RangeVarVi(hdlSys), mStatLeftValue(StatLeft), mStatRightValue(StatRight),
		mDynaLeftTerm(Null), mDynaRightTerm(Null), mDynaLeftRec(Null), mDynaRightRec(Null),
		mDynaLeftValue(mStatLeftValue), mDynaRightValue(mStatRightValue)
{
	WatchError
	Warn(mStatLeftValue > mStatRightValue, eRangeDefn);

	setTermCls(TermStub<DynaRangeCtlVarVi>::TermCls);
	setTermHvl(calcTermHvl());
	CatchError
}


/*!
	The duplicator.
*/
DynaRangeCtlVarVi::DynaRangeCtlVarVi(DynaRangeCtlVarVi const & that) : RangeVarVi(that),
		mStatLeftValue(that.mStatLeftValue), mStatRightValue(that.mStatRightValue)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}


/*!
	The assigner.
*/
DynaRangeCtlVarVi const & DynaRangeCtlVarVi::operator = (DynaRangeCtlVarVi const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}


/*!
	The destructor.
*/
DynaRangeCtlVarVi::~DynaRangeCtlVarVi()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll DynaRangeCtlVarVi::identical(Var const & that) const
{
	WatchError
	if (that.TermCls != TermStub<DynaRangeCtlVarVi>::TermCls)
		return false;
	DynaRangeCtlVarVi const & tVar = scast<DynaRangeCtlVarVi const &>(that);
	return tVar.mStatRightValue == mStatRightValue && tVar.mStatLeftValue == mStatLeftValue;
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll DynaRangeCtlVarVi::identical(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	if (that->TermCls != TermStub<DynaRangeCtlVarVi>::TermCls)
		return false;
	DynaRangeCtlVarVi const * tVar = scast<DynaRangeCtlVarVi const *>(that);
	return tVar->mStatRightValue == mStatRightValue && tVar->mStatLeftValue == mStatLeftValue;
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll DynaRangeCtlVarVi::assignable(Var const & that) const
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
Bll DynaRangeCtlVarVi::assignable(Var const * that) const
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
Bll DynaRangeCtlVarVi::swappable(Var const & that) const
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
Bll DynaRangeCtlVarVi::swappable(Var const * that) const
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
Bll DynaRangeCtlVarVi::validStat(Wrp const & theWrp) const
{
	WatchError
	Int const & tValueInt = theWrp.itemInt();
	return tValueInt >= mStatLeftValue && tValueInt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the static domain?
*/
Bll DynaRangeCtlVarVi::validStat(Int const & theInt) const
{
	WatchError
	return theInt >= mStatLeftValue && theInt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll DynaRangeCtlVarVi::validDyna(Int const & theInt) const
{
	WatchError
	return theInt >= mDynaLeftValue && theInt <= mDynaRightValue;
	CatchError
}



/*!
	Valid with respect to the dynamic domain?
*/
Bll DynaRangeCtlVarVi::validDyna(Wrp const & theWrp) const
{
	WatchError
	Int const & tValueInt = theWrp.itemInt();
	return tValueInt >= mDynaLeftValue && tValueInt <= mDynaRightValue;
	CatchError
}



/*!
	Whether the current value is the static right value?
*/
Bll DynaRangeCtlVarVi::chkCurrStatRight() const
{
	WatchError
	return mValueRec->CurrBuff == mStatRightValue;
	CatchError
}



/*!
	Whether the current value is the static left value?
*/
Bll DynaRangeCtlVarVi::chkCurrStatLeft() const
{
	WatchError
	return mValueRec->CurrBuff == mStatLeftValue;
	CatchError
}



/*!
	Whether the current value is the dynamic right value?
*/
Bll DynaRangeCtlVarVi::chkCurrDynaRight() const
{
	WatchError
	return mValueRec->CurrBuff == mDynaRightValue;
	CatchError
}



/*!
	Whether the current value is the dynamic left value?
*/
Bll DynaRangeCtlVarVi::chkCurrDynaLeft() const
{
	WatchError
	return mValueRec->CurrBuff == mDynaLeftValue;
	CatchError
}



/*!
	Whether the next value is the static right value?
*/
Bll DynaRangeCtlVarVi::chkNextStatRight() const
{
	WatchError
	return mValueRec->NextBuff == mStatRightValue;
	CatchError
}



/*!
	Whether the next value is the static left value?
*/
Bll DynaRangeCtlVarVi::chkNextStatLeft() const
{
	WatchError
	return mValueRec->NextBuff == mStatLeftValue;
	CatchError
}



/*!
	Whether the next value is the dynamic right value?
*/
Bll DynaRangeCtlVarVi::chkNextDynaRight() const
{
	WatchError
	return mValueRec->NextBuff == mDynaRightValue;
	CatchError
}



/*!
	Whether the next value is the left value?
*/
Bll DynaRangeCtlVarVi::chkNextDynaLeft() const
{
	WatchError
	return mValueRec->NextBuff == mDynaLeftValue;
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Int DynaRangeCtlVarVi::StatRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mStatLeftValue, mStatRightValue);
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Int DynaRangeCtlVarVi::DynaRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mDynaLeftValue, mDynaRightValue);
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Wrp DynaRangeCtlVarVi::StatRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mStatLeftValue, mStatRightValue));
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Wrp DynaRangeCtlVarVi::DynaRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mDynaLeftValue, mDynaRightValue));
	CatchError
}



/*!
	The static left value.
*/
Int DynaRangeCtlVarVi::StatLeftValue() const
{
	WatchError
	return mStatLeftValue;
	CatchError
}


/*!
	The static right value.
*/
Int DynaRangeCtlVarVi::StatRightValue() const
{
	WatchError
	return mStatRightValue;
	CatchError
}


/*!
	The dynamic left value.
*/
Int DynaRangeCtlVarVi::DynaLeftValue() const
{
	WatchError
	return mDynaLeftValue;
	CatchError
}


/*!
	The dynamic right value.
*/
Int DynaRangeCtlVarVi::DynaRightValue() const
{
	WatchError
	return mDynaRightValue;
	CatchError
}



/*!
	The step size value.
*/
Int DynaRangeCtlVarVi::StepSizeValue() const
{
	WatchError
	return 1;
	CatchError
}



/*!
	Wrap for the static left value.
*/
Wrp DynaRangeCtlVarVi::StatLeftWrap() const
{
	WatchError
	return Wrp(mStatLeftValue);
	CatchError
}


/*!
	Wrap for the static right value.
*/
Wrp DynaRangeCtlVarVi::StatRightWrap() const
{
	WatchError
	return Wrp(mStatRightValue);
	CatchError
}


/*!
	Wrap for the dynamic left value.
*/
Wrp DynaRangeCtlVarVi::DynaLeftWrap() const
{
	WatchError
	return Wrp(mDynaLeftValue);
	CatchError
}


/*!
	Wrap for the dynamic right value.
*/
Wrp DynaRangeCtlVarVi::DynaRightWrap() const
{
	WatchError
	return Wrp(mDynaRightValue);
	CatchError
}



/*!
	Wrap for the step size value.
*/
Wrp DynaRangeCtlVarVi::StepSizeWrap() const
{
	WatchError
	return Wrp(castInt(1));
	CatchError
}




/*!
	Perform anew execution with a value.
*/
void DynaRangeCtlVarVi::execAnewValue(Int const & theInt)
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
void DynaRangeCtlVarVi::execAnewWrap(Wrp const & theWrp)
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
void DynaRangeCtlVarVi::execAnewStatRand(Rnd & theRnd)
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
void DynaRangeCtlVarVi::execAnewDynaRand(Rnd & theRnd)
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
void DynaRangeCtlVarVi::execIncrValue(Int const & theInt)
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
void DynaRangeCtlVarVi::execIncrWrap(Wrp const & theWrp)
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
void DynaRangeCtlVarVi::execIncrStatRand(Rnd & theRnd)
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
void DynaRangeCtlVarVi::execIncrDynaRand(Rnd & theRnd)
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
void DynaRangeCtlVarVi::execIncrStatLeft()
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
void DynaRangeCtlVarVi::execIncrDynaLeft()
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
void DynaRangeCtlVarVi::execIncrSuccessor()
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
void DynaRangeCtlVarVi::execIncrPredecessor()
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
void DynaRangeCtlVarVi::execIncrStatRight()
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
void DynaRangeCtlVarVi::execIncrDynaRight()
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
void DynaRangeCtlVarVi::simulAnewStatRand(Rnd & theRnd)
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
void DynaRangeCtlVarVi::simulAnewDynaRand(Rnd & theRnd)
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
void DynaRangeCtlVarVi::simulAnewValue(Int const & theInt)
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
void DynaRangeCtlVarVi::simulAnewWrap(Wrp const & theWrp)
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
void DynaRangeCtlVarVi::simulIncrStatRand(Rnd & theRnd)
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
void DynaRangeCtlVarVi::simulIncrDynaRand(Rnd & theRnd)
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
void DynaRangeCtlVarVi::simulIncrValue(Int const & theInt)
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
void DynaRangeCtlVarVi::simulIncrWrap(Wrp const & theWrp)
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
void DynaRangeCtlVarVi::simulIncrStatLeft()
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
void DynaRangeCtlVarVi::simulIncrDynaLeft()
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
void DynaRangeCtlVarVi::simulIncrSuccessor()
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
void DynaRangeCtlVarVi::simulIncrPredecessor()
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
void DynaRangeCtlVarVi::simulIncrStatRight()
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
void DynaRangeCtlVarVi::simulIncrDynaRight()
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
inline Bll DynaRangeCtlVarVi::DomainUpdateDefined() const
{
	WatchError
	return true;
	CatchError
}


/*!
	Update the dynamic domain.
*/
void DynaRangeCtlVarVi::updateDomain()
{
	WatchError
	Warn(!mDynaLeftTerm, eNullPointer);
	Warn(!mDynaRightTerm, eNullPointer);
	Warn(!mDynaRightRec, eNullPointer);
	Warn(!mDynaLeftRec, eNullPointer);

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
