/*!
	@file statrangevarvf.cpp
	@brief The implementation file for StatRangeVarVf class.
	@details This is the implementation file for StatRangeVarVf class.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see statrangevarvf.hpp
*/



#include "cbls/vars/rangevars/statrangevarvf.hpp"



openKangarooSpace



/*!
	Define a float range variable.
*/
Hdl StatRangeVarVf::def(Hdl const hdlSys, Flt const & StatLeft,
		Flt const & StatRight, Flt const & StepSize)
{
	WatchError
	StatRangeVarVf * tVar = new StatRangeVarVf(hdlSys, StatLeft, StatRight, StepSize);
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
StatRangeVarVf::StatRangeVarVf(Hdl const hdlSys, Flt const & StatLeft,
		Flt const & StatRight, Flt const & StepSize) :
		RangeVarVf(hdlSys), mStatLeftValue(StatLeft),
		mStatRightValue(StatRight), mStepSizeValue(StepSize)
{
	WatchError
	Warn(mStatLeftValue > mStatRightValue, eRangeDefn);
	Warn(StepSize <= 0, eStepSize);


	setTermCls(TermStub<StatRangeVarVf>::TermCls);
	setTermHvl(calcTermHvl());
	CatchError
}


/*!
	The duplicator.
*/
StatRangeVarVf::StatRangeVarVf(StatRangeVarVf const & that) : RangeVarVf(that),
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
StatRangeVarVf const & StatRangeVarVf::operator = (StatRangeVarVf const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}


/*!
	The destructor.
*/
StatRangeVarVf::~StatRangeVarVf()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll StatRangeVarVf::identical(Var const & that) const
{
	WatchError
	if (that.TermCls != TermStub<StatRangeVarVf>::TermCls)
		return false;
	StatRangeVarVf const & tVar = scast<StatRangeVarVf const &>(that);
	return eq<Flt,Bll>::iof(tVar.mStatRightValue, mStatRightValue) &&
			eq<Flt,Bll>::iof(tVar.mStatLeftValue, mStatLeftValue) &&
			eq<Flt,Bll>::iof(tVar.mStepSizeValue, mStepSizeValue);
	CatchError
}



/*!
	Whether two variables are identical?
*/
Bll StatRangeVarVf::identical(Var const * that) const
{
	WatchError
	Warn(!that, eNullPointer);

	if (that->TermCls != TermStub<StatRangeVarVf>::TermCls)
		return false;
	StatRangeVarVf const * tVar = scast<StatRangeVarVf const *>(that);
	return eq<Flt,Bll>::iof(tVar->mStatRightValue, mStatRightValue) &&
			eq<Flt,Bll>::iof(tVar->mStatLeftValue, mStatLeftValue) &&
			eq<Flt,Bll>::iof(tVar->mStepSizeValue, mStepSizeValue);
	CatchError
}



/*!
	Wether another variable's value is assignable?
*/
Bll StatRangeVarVf::assignable(Var const & that) const
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
Bll StatRangeVarVf::assignable(Var const * that) const
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
Bll StatRangeVarVf::swappable(Var const & that) const
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
Bll StatRangeVarVf::swappable(Var const * that) const
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
Bll StatRangeVarVf::validStat(Flt const & theFlt) const
{
	WatchError
	return theFlt >= mStatLeftValue && theFlt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll StatRangeVarVf::validDyna(Flt const & theFlt) const
{
	WatchError
	return theFlt >= mStatLeftValue && theFlt <= mStatRightValue;
	CatchError
}



/*!
	Valid with respect to the static domain?
*/
Bll StatRangeVarVf::validStat(Wrp const & theWrp) const
{
	WatchError
	Flt const & tValueFlt = theWrp.itemFlt();
	return tValueFlt >= mStatLeftValue && tValueFlt <= mStatRightValue;
	CatchError
}


/*!
	Valid with respect to the dynamic domain?
*/
Bll StatRangeVarVf::validDyna(Wrp const & theWrp) const
{
	WatchError
	Flt const & tValueFlt = theWrp.itemFlt();
	return tValueFlt >= mStatLeftValue && tValueFlt <= mStatRightValue;
	CatchError
}




/*!
	Whether the current value is the static right value?
*/
Bll StatRangeVarVf::chkCurrStatRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mStatRightValue);
	CatchError
}



/*!
	Whether the current value is the static left value?
*/
Bll StatRangeVarVf::chkCurrStatLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mStatLeftValue);
	CatchError
}



/*!
	Whether the current value is the dynamic right value?
*/
Bll StatRangeVarVf::chkCurrDynaRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mStatRightValue);
	CatchError
}



/*!
	Whether the current value is the dynamic left value?
*/
Bll StatRangeVarVf::chkCurrDynaLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->CurrBuff, mStatLeftValue);
	CatchError
}



/*!
	Whether the next value is the static right value?
*/
Bll StatRangeVarVf::chkNextStatRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mStatRightValue);
	CatchError
}



/*!
	Whether the next value is the static left value?
*/
Bll StatRangeVarVf::chkNextStatLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mStatLeftValue);
	CatchError
}



/*!
	Whether the next value is the dynamic right value?
*/
Bll StatRangeVarVf::chkNextDynaRight() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mStatRightValue);
	CatchError
}



/*!
	Whether the next value is the left value?
*/
Bll StatRangeVarVf::chkNextDynaLeft() const
{
	WatchError
	return eq<Flt,Bll>::iof(mValueRec->NextBuff, mStatLeftValue);
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Flt StatRangeVarVf::StatRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mStatLeftValue, mStatRightValue);
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Flt StatRangeVarVf::DynaRandValue(Rnd & theRnd) const
{
	WatchError
	return uniform(theRnd, mStatLeftValue, mStatRightValue);
	CatchError
}



/*!
	Random value chosen from the static domain.
*/
Wrp StatRangeVarVf::StatRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mStatLeftValue, mStatRightValue));
	CatchError
}


/*!
	Random value chosen from the dynamic domain.
*/
Wrp StatRangeVarVf::DynaRandWrap(Rnd & theRnd) const
{
	WatchError
	return Wrp(uniform(theRnd, mStatLeftValue, mStatRightValue));
	CatchError
}



/*!
	The static left value.
*/
Flt StatRangeVarVf::StatLeftValue() const
{
	WatchError
	return mStatLeftValue;
	CatchError
}


/*!
	The static right value.
*/
Flt StatRangeVarVf::StatRightValue() const
{
	WatchError
	return mStatRightValue;
	CatchError
}


/*!
	The dynamic left value.
*/
Flt StatRangeVarVf::DynaLeftValue() const
{
	WatchError
	return mStatLeftValue;
	CatchError
}


/*!
	The dynamic right value.
*/
Flt StatRangeVarVf::DynaRightValue() const
{
	WatchError
	return mStatRightValue;
	CatchError
}




/*!
	The step size value.
*/
Flt StatRangeVarVf::StepSizeValue() const
{
	WatchError
	return mStepSizeValue;
	CatchError
}



/*!
	Wrap for the static left value.
*/
Wrp StatRangeVarVf::StatLeftWrap() const
{
	WatchError
	return Wrp(mStatLeftValue);
	CatchError
}


/*!
	Wrap for the static right value.
*/
Wrp StatRangeVarVf::StatRightWrap() const
{
	WatchError
	return Wrp(mStatRightValue);
	CatchError
}


/*!
	Wrap for the dynamic left value.
*/
Wrp StatRangeVarVf::DynaLeftWrap() const
{
	WatchError
	return Wrp(mStatLeftValue);
	CatchError
}


/*!
	Wrap for the dynamic right value.
*/
Wrp StatRangeVarVf::DynaRightWrap() const
{
	WatchError
	return Wrp(mStatRightValue);
	CatchError
}




/*!
	Wrap for the step size value.
*/
Wrp StatRangeVarVf::StepSizeWrap() const
{
	WatchError
	return Wrp(mStepSizeValue);
	CatchError
}



/*!
	Perform anew execution with a value.
*/
void StatRangeVarVf::execAnewValue(Flt const & theFlt)
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
void StatRangeVarVf::execAnewWrap(Wrp const & theWrp)
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
void StatRangeVarVf::execAnewStatRand(Rnd & theRnd)
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
void StatRangeVarVf::execAnewDynaRand(Rnd & theRnd)
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
void StatRangeVarVf::execIncrValue(Flt const & theFlt)
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
void StatRangeVarVf::execIncrWrap(Wrp const & theWrp)
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
void StatRangeVarVf::execIncrStatRand(Rnd & theRnd)
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
void StatRangeVarVf::execIncrDynaRand(Rnd & theRnd)
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
void StatRangeVarVf::execIncrStatLeft()
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
void StatRangeVarVf::execIncrDynaLeft()
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
void StatRangeVarVf::execIncrSuccessor()
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
void StatRangeVarVf::execIncrPredecessor()
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
void StatRangeVarVf::execIncrStatRight()
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
void StatRangeVarVf::execIncrDynaRight()
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
void StatRangeVarVf::simulAnewStatRand(Rnd & theRnd)
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
void StatRangeVarVf::simulAnewDynaRand(Rnd & theRnd)
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
void StatRangeVarVf::simulAnewValue(Flt const & theFlt)
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
void StatRangeVarVf::simulAnewWrap(Wrp const & theWrp)
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
void StatRangeVarVf::simulIncrStatRand(Rnd & theRnd)
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
void StatRangeVarVf::simulIncrDynaRand(Rnd & theRnd)
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
void StatRangeVarVf::simulIncrValue(Flt const & theFlt)
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
void StatRangeVarVf::simulIncrWrap(Wrp const & theWrp)
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
void StatRangeVarVf::simulIncrStatLeft()
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
void StatRangeVarVf::simulIncrDynaLeft()
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
void StatRangeVarVf::simulIncrSuccessor()
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
void StatRangeVarVf::simulIncrPredecessor()
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
void StatRangeVarVf::simulIncrStatRight()
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
void StatRangeVarVf::simulIncrDynaRight()
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
