/*!
	@file statrangevarvi.cpp
	@brief The implementation file for StatRangeVarVi class.
	@details This is the implementation file for StatRangeVarVi class.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see statrangevarvi.hpp
*/



#include "cbls/vars/rangevars/statrangevarvi.hpp"



openKangarooSpace



/*!
	Define a float range variable.
*/
Hdl StatRangeVarVi::def(Hdl const hdlSys, Int const & StatLeft, Int const & StatRight)
{
	WatchError
	StatRangeVarVi * tVar = new StatRangeVarVi(hdlSys, StatLeft, StatRight);
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
StatRangeVarVi::StatRangeVarVi(Hdl const hdlSys, Int const & StatLeft, Int const & StatRight) :
		RangeVarVi(hdlSys), mStatLeftValue(StatLeft), mStatRightValue(StatRight)
{
	WatchError
	Warn(mStatLeftValue > mStatRightValue, eRangeDefn);

	setTermCls(TermStub<StatRangeVarVi>::TermCls);
	setTermHvl(calcTermHvl());
	CatchError
}


/*!
	The duplicator.
*/
StatRangeVarVi::StatRangeVarVi(StatRangeVarVi const & that) : RangeVarVi(that),
		mStatLeftValue(that.mStatLeftValue), mStatRightValue(that.mStatRightValue)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
StatRangeVarVi const & StatRangeVarVi::operator = (StatRangeVarVi const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}


/*!
	The destructor.
*/
StatRangeVarVi::~StatRangeVarVi()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll StatRangeVarVi::identical(Var const & that) const
{
	WatchError
	if (that.TermCls != TermStub<StatRangeVarVi>::TermCls)
		return false;
	StatRangeVarVi const & tVar = scast<StatRangeVarVi const &>(that);
	return tVar.mStatRightValue == mStatRightValue &&
			tVar.mStatLeftValue == mStatLeftValue;
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll StatRangeVarVi::identical(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	if (that->TermCls != TermStub<StatRangeVarVi>::TermCls)
		return false;
	StatRangeVarVi const * tVar = scast<StatRangeVarVi const *>(that);
	return tVar->mStatRightValue == mStatRightValue &&
			tVar->mStatLeftValue == mStatLeftValue;
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll StatRangeVarVi::assignable(Var const & that) const
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
Bll StatRangeVarVi::assignable(Var const * that) const
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
Bll StatRangeVarVi::swappable(Var const & that) const
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
Bll StatRangeVarVi::swappable(Var const * that) const
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
Bll StatRangeVarVi::validStat(Int const & theInt) const
{
	WatchError
	return theInt >= mStatLeftValue && theInt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll StatRangeVarVi::validDyna(Int const & theInt) const
{
	WatchError
	return theInt >= mStatLeftValue && theInt <= mStatRightValue;
	CatchError
}



/*!
	Valid with respect to the static domain?
*/
Bll StatRangeVarVi::validStat(Wrp const & theWrp) const
{
	WatchError
	Int const & tValueInt = theWrp.itemInt();
	return tValueInt >= mStatLeftValue && tValueInt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll StatRangeVarVi::validDyna(Wrp const & theWrp) const
{
	WatchError
	Int const & tValueInt = theWrp.itemInt();
	return tValueInt >= mStatLeftValue && tValueInt <= mStatRightValue;
	CatchError
}




/*!
	Whether the current value is the static right value?
*/
Bll StatRangeVarVi::chkCurrStatRight() const
{
	WatchError
	return mValueRec->CurrBuff == mStatRightValue;
	CatchError
}



/*!
	Whether the current value is the static left value?
*/
Bll StatRangeVarVi::chkCurrStatLeft() const
{
	WatchError
	return mValueRec->CurrBuff == mStatLeftValue;
	CatchError
}



/*!
	Whether the current value is the dynamic right value?
*/
Bll StatRangeVarVi::chkCurrDynaRight() const
{
	WatchError
	return mValueRec->CurrBuff == mStatRightValue;
	CatchError
}



/*!
	Whether the current value is the dynamic left value?
*/
Bll StatRangeVarVi::chkCurrDynaLeft() const
{
	WatchError
	return mValueRec->CurrBuff == mStatLeftValue;
	CatchError
}



/*!
	Whether the next value is the static right value?
*/
Bll StatRangeVarVi::chkNextStatRight() const
{
	WatchError
	return mValueRec->NextBuff == mStatRightValue;
	CatchError
}



/*!
	Whether the next value is the static left value?
*/
Bll StatRangeVarVi::chkNextStatLeft() const
{
	WatchError
	return mValueRec->NextBuff == mStatLeftValue;
	CatchError
}



/*!
	Whether the next value is the dynamic right value?
*/
Bll StatRangeVarVi::chkNextDynaRight() const
{
	WatchError
	return mValueRec->NextBuff == mStatRightValue;
	CatchError
}



/*!
	Whether the next value is the left value?
*/
Bll StatRangeVarVi::chkNextDynaLeft() const
{
	WatchError
	return mValueRec->NextBuff == mStatLeftValue;
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Int StatRangeVarVi::StatRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mStatLeftValue, mStatRightValue);
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Int StatRangeVarVi::DynaRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mStatLeftValue, mStatRightValue);
	CatchError
}




/*!
	Random value chosen from the static domain.
*/
Wrp StatRangeVarVi::StatRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mStatLeftValue, mStatRightValue));
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Wrp StatRangeVarVi::DynaRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mStatLeftValue, mStatRightValue));
	CatchError
}



/*!
	The static left value.
*/
Int StatRangeVarVi::StatLeftValue() const
{
	WatchError
	return mStatLeftValue;
	CatchError
}


/*!
	The static right value.
*/
Int StatRangeVarVi::StatRightValue() const
{
	WatchError
	return mStatRightValue;
	CatchError
}


/*!
	The dynamic left value.
*/
Int StatRangeVarVi::DynaLeftValue() const
{
	WatchError
	return mStatLeftValue;
	CatchError
}


/*!
	The dynamic right value.
*/
Int StatRangeVarVi::DynaRightValue() const
{
	WatchError
	return mStatRightValue;
	CatchError
}




/*!
	The step size value.
*/
Int StatRangeVarVi::StepSizeValue() const
{
	WatchError
	return 1;
	CatchError
}




/*!
	Wrap for the static left value.
*/
Wrp StatRangeVarVi::StatLeftWrap() const
{
	WatchError
	return Wrp(mStatLeftValue);
	CatchError
}


/*!
	Wrap for the static right value.
*/
Wrp StatRangeVarVi::StatRightWrap() const
{
	WatchError
	return Wrp(mStatRightValue);
	CatchError
}


/*!
	Wrap for the dynamic left value.
*/
Wrp StatRangeVarVi::DynaLeftWrap() const
{
	WatchError
	return Wrp(mStatLeftValue);
	CatchError
}


/*!
	Wrap for the dynamic right value.
*/
Wrp StatRangeVarVi::DynaRightWrap() const
{
	WatchError
	return Wrp(mStatRightValue);
	CatchError
}




/*!
	Wrap for the step size value.
*/
Wrp StatRangeVarVi::StepSizeWrap() const
{
	WatchError
	return Wrp(castInt(1));
	CatchError
}




/*!
	Perform anew execution with a value.
*/
void StatRangeVarVi::execAnewValue(Int const & theInt)
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
void StatRangeVarVi::execAnewWrap(Wrp const & theWrp)
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
void StatRangeVarVi::execAnewStatRand(Rnd & theRnd)
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
	Perform anew execution wth a random value from the dyanmic domain.
*/
void StatRangeVarVi::execAnewDynaRand(Rnd & theRnd)
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
	Perform incremental execution with a value.
*/
void StatRangeVarVi::execIncrValue(Int const & theInt)
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
void StatRangeVarVi::execIncrWrap(Wrp const & theWrp)
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
void StatRangeVarVi::execIncrStatRand(Rnd & theRnd)
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
void StatRangeVarVi::execIncrDynaRand(Rnd & theRnd)
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
	Perform incremental execution with the static left value.
*/
void StatRangeVarVi::execIncrStatLeft()
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
void StatRangeVarVi::execIncrDynaLeft()
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
	Perform incremental execution with the succeeding value.
*/
void StatRangeVarVi::execIncrSuccessor()
{
	WatchError
	Warn(mValueRec->CurrBuff >= mStatRightValue, eOutOfRange);

	runPreExecIncr();
	mValueRec->copytoPrevBuff();
	mValueRec->CurrBuff += 1;
	mValueRec->PrevClk = mTermSys.ExecClk();
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with the preceeding value.
*/
void StatRangeVarVi::execIncrPredecessor()
{
	WatchError
	Warn(mValueRec->CurrBuff <= mStatLeftValue, eOutOfRange);

	runPreExecIncr();
	mValueRec->copytoPrevBuff();
	mValueRec->CurrBuff -= 1;
	mValueRec->PrevClk = mTermSys.ExecClk();
	#if ExecUpwdLazy
	runPostExecIncr();
	#endif
	CatchError
}



/*!
	Perform incremental execution with the static right value.
*/
void StatRangeVarVi::execIncrStatRight()
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
void StatRangeVarVi::execIncrDynaRight()
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
	Perform anew simulation with a random value from the static domain.
*/
void StatRangeVarVi::simulAnewStatRand(Rnd & theRnd)
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
void StatRangeVarVi::simulAnewDynaRand(Rnd & theRnd)
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
	Perform anew simulation with a value.
*/
void StatRangeVarVi::simulAnewValue(Int const & theInt)
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
void StatRangeVarVi::simulAnewWrap(Wrp const & theWrp)
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
void StatRangeVarVi::simulIncrStatRand(Rnd & theRnd)
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
void StatRangeVarVi::simulIncrDynaRand(Rnd & theRnd)
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
	Perform incremental simulation with a value.
*/
void StatRangeVarVi::simulIncrValue(Int const & theInt)
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
void StatRangeVarVi::simulIncrWrap(Wrp const & theWrp)
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
void StatRangeVarVi::simulIncrStatLeft()
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
void StatRangeVarVi::simulIncrDynaLeft()
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
	Perform incremental simulation with the succeeding value.
*/
void StatRangeVarVi::simulIncrSuccessor()
{
	WatchError
	Warn(mValueRec->NextBuff >= mStatRightValue, eOutOfRange);

	runPreSimulIncr();
	mValueRec->NextBuff += 1;
	mValueRec->NextClk = mTermSys.SimulClk();

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with the preceding value.
*/
void StatRangeVarVi::simulIncrPredecessor()
{
	WatchError
	Warn(mValueRec->NextBuff <= mStatLeftValue, eOutOfRange);

	runPreSimulIncr();
	mValueRec->NextBuff -= 1;
	mValueRec->NextClk = mTermSys.SimulClk();

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



/*!
	Perform incremental simulation with the static right value.
*/
void StatRangeVarVi::simulIncrStatRight()
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
void StatRangeVarVi::simulIncrDynaRight()
{
	WatchError
	runPreSimulIncr();
	mValueRec->initNext(mTermSys.SimulClk(), mStatRightValue);

	#if SimulUpwd
	runPostSimulIncr();
	#endif
	CatchError
}



closeKangarooSpace
