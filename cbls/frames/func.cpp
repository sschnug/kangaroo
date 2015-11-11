/*!
	@file func.cpp
	@brief The implementation file for the Func class.
	@details This is the implementation file for the Func class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see func.hpp
*/



#include "cbls/frames/func.hpp"
#include "cbls/frames/var.hpp"
#include "cbls/frames/const.hpp"


openKangarooSpace



#if CompDnwd
/*!
	Static variables.
*/
b1<Pos, xmm> const Func::mProxyPrmBlk;
#endif


/*!
	The constructor.
*/
Func::Func(Hdl const hdlSys, Dim const PrmCount) :
		Term(hdlSys)
		, FuncFss(DfltFsm)
		#if CompUpwd
			, FuncLvl(0)
		#endif
		, FuncVars(PrmCount)
		, PrmVars(PrmCount)
		, mPrmTerms(PrmCount)
		, mPrmSpecs(PrmCount)
		#if CompDnwd
			, mPrmLinks(PrmCount)
			, mVarUpdtPrms(PrmCount)
		#endif
		#if CompUpwd
			#if UpwdMapFuncVarArray
				, mVarHdlSqns(Null)
			#else
				, mVarHdlSqns(PrmCount)
			#endif
		#endif
		#if CompDnwd
			#if DnwdMapFuncVar == MfvFuncArrayVar
				, mVarHdlSqns(Null)
			#elif DnwdMapFuncVar == MfvFuncHashVar
				, mVarHdlSqns(PrmCount)
			#endif
		#endif
		#if CompLazy
			, mBacklogPrms(PrmCount)
			, mEvalUndonePrms(Null)
		#endif
		#if CompLazyHalf
			, mRequired(0)
			, mEnforced(0)
			, mDefered(true)
			, mReqFuncLnk(InvLnk)
		#endif
		, mRootFuncLnk(InvLnk)
		#if ExecDnwd
			, mExecAsgnClk(NotClk)
		#endif
		#if SimulDnwdFixed
			, mSimulFixedClk(NotClk)
		#endif
		#if SimulDnwdFlexi
			#if FuncFlexiClk
			,mSimulFlexiClk(NotClk)
			#endif
		#endif
		#if SimulDnwdCache
			, mSimulCacheClk(NotClk)
		#endif
		#if ExecDnwd
			, mLblCandPrms(PrmCount)
			, mBlkCandPrms(&mProxyPrmBlk)
		#endif
		#if SimulDnwdFixed
			, mLblFixedPrms(PrmCount)
			, mBlkFixedPrms(&mProxyPrmBlk)
		#endif
		#if SimulDnwdFlexi
			, mLblFlexiPrms(Null)
			, mBlkFlexiPrms(&mProxyPrmBlk)
		#endif
		#if ExecUpwd
			, mExecChgdPrms(PrmCount)
		#endif	//ExecUpwd
		#if SimulUpwd
			, mSimulChgdPrms(PrmCount)
		#endif	//SimulUpwd
		#if CompLazy
			, mEvalUndoDefined(false)
			, mHintUndoDefined(false)
		#endif	//CompLazy
		#if ExecDnwdMultiCand
			, mCandMrgBlk(Null)
		#endif
		#if SimulDnwdMultiFixed
			, mFixedMrgBlk(Null)
		#endif
		#if SimulDnwdMultiFlexi
			, mFlexiMrgBlk(Null)
		#endif
{
	WatchError
	setTermGen(Tf);
	CatchError
}



/*!
	The duplicator.
*/
Func::Func(Func const & that) : Term(that), FuncFss(DfltFsm)
	#if CompUpwd
		, FuncLvl(0)
	#endif	//CompUpwd
	, FuncVars()
	, PrmVars()
	, mPrmTerms(0)
	, mPrmSpecs(0)
	#if CompDnwd
		, mPrmLinks(0)
		, mVarUpdtPrms()
	#endif	//CompDnwd
	#if CompUpwd
		#if UpwdMapFuncVarArray
			, mVarHdlSqns(Null)
		#else
			, mVarHdlSqns()
		#endif
	#endif
	#if CompDnwd
		#if DnwdMapFuncVar == MfvFuncArrayVar
			, mVarHdlSqns(Null)
		#elif DnwdMapFuncVar == MfvFuncHashVar
			, mVarHdlSqns()
		#endif
	#endif
	#if CompLazy
		, mBacklogPrms(0)
		, mEvalUndonePrms(Null)
	#endif
	#if CompLazyHalf
		, mRequired(0)
		, mEnforced(0)
		, mDefered(true)
		, mReqFuncLnk(InvLnk)
	#endif	//CompLazy
		, mRootFuncLnk(InvLnk)
	#if ExecDnwd
		,mExecAsgnClk(NotClk)
	#endif
	#if SimulDnwdFixed
		, mSimulFixedClk(NotClk)
	#endif
	#if SimulDnwdFlexi
		#if FuncFlexiClk
			, mSimulFlexiClk(NotClk)
		#endif
	#endif
	#if SimulDnwdCache
		, mSimulCacheClk(NotClk)
	#endif
	#if ExecDnwd
		,mLblCandPrms(0)
	#endif	//ExecDnwd
	#if SimulDnwdFixed
		, mLblFixedPrms(0)
	#endif
	#if SimulDnwdFlexi
		, mLblFlexiPrms(Null)
	#endif
	#if ExecUpwd
		, mExecChgdPrms(0)
	#endif	//ExecUpwd
	#if SimulUpwd
		, mSimulChgdPrms(0)
	#endif	//SimulUpwd
	#if CompLazy
		, mEvalUndoDefined(false)
		, mHintUndoDefined(false)
	#endif	//CompLazy
	#if ExecDnwdMultiCand
		, mCandMrgBlk(Null)
	#endif	//ExecDnwd
	#if SimulDnwdMultiFixed
		, mFixedMrgBlk(Null)
	#endif
	#if SimulDnwdMultiFlexi
		, mFlexiMrgBlk(Null)
	#endif
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Func const & Func::operator = (Func const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Calculate hash value.
*/
Hvl Func::calcTermHvl() const
{
	WatchError
	Hvl tHvl = 0;
	tHvl = mixHash(tHvl, calcHash(TermCls));
	tHvl = mixHash(tHvl, calcHash(FuncFss));

	for(Pos tPos = 0; tPos < mPrmTerms.itemCount(); ++tPos)
	{
		tHvl = mixHash(tHvl, calcHash(mPrmTerms[tPos]));
		tHvl = mixHash(tHvl, calcHash(mPrmSpecs[tPos]));
	}

	return tHvl;
	CatchError
}



/*!
	Compare two terms for equality.
*/
Bll Func::equate(Term const & theTerm) const
{
	WatchError
	if (TermCls != theTerm.TermCls) return false;
	Func const & tFunc = cast(theTerm);
	b1<Term *, kmm> const & tPrmTerms = tFunc.mPrmTerms;
	b1<Pss, kmm> const & tPrmSpecs = tFunc.mPrmSpecs;

	if (FuncFss != tFunc.FuncFss) return false;
	if (mPrmTerms.itemCount() != tPrmTerms.itemCount()) return false;
	for(Pos tPos = 0; tPos < mPrmTerms.itemCount(); ++tPos)
	{
		if (mPrmTerms[tPos] != tPrmTerms[tPos]) return false;
		if (mPrmSpecs[tPos] != tPrmSpecs[tPos]) return false;
	}

	return true;
	CatchError
}



/*!
	Set the parameters of the term.
*/
void Func::setParams(Fss const theFss, Prm * thePrms,
		Dim const PrmCount, Pso const theOrder, Idx * theIdxs)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	ccast<Fss &>(FuncFss) = theFss;

	#if CompUpwd
	Lvl & tFuncLvl = ccast<Lvl &>(FuncLvl);
	#endif//CompUpwd

	b1<Pss, kmm> & tPrmSpecs = ccast<b1<Pss, kmm> &>(mPrmSpecs);
	b1<Hdl, xmm> & tFuncVars = ccast<b1<Hdl,xmm> &>(FuncVars);
	#if CompUpwd
		#if UpwdMapFuncVarArray
		hm<Hdl,Sqn, xmmh> & tVarHdlSqns = ccast<hm<Hdl,Sqn,xmmh> &>(mVarHdlSqns);
		#else
		hm<Hdl,Sqn, xmmh> tVarHdlSqns(PrmCount);
		#endif
	#endif
	#if CompDnwd
		#if DnwdMapFuncVar == MfvFuncHashVar
		hm<Hdl,Sqn, xmmh> & tVarHdlSqns = ccast<hm<Hdl,Sqn,xmmh> &>(mVarHdlSqns);
		#else // in all other cases
		hm<Hdl,Sqn, xmmh> tVarHdlSqns(PrmCount);
		#endif
	#endif
	rl< b1<Sqn, xmm>, nmm > & tPrmVars = ccast<rl< b1<Sqn,xmm>, nmm > &>(PrmVars);
	b1<Term *, kmm> & tPrmTerms = ccast<b1<Term *, kmm> &>(mPrmTerms);

	#if CompDnwd
	rl< b1<Pos, xmm>, xmm > & tVarUpdtPrms = ccast<rl< b1<Pos, xmm>, xmm > &>(mVarUpdtPrms);
	#endif//CompDnwd

	if (theOrder == Unordered)
	{
		if (theIdxs)
		{
			for(Idx tIdx = 0; tIdx < PrmCount; ++tIdx)
				theIdxs[tIdx] = tIdx;
			idxsort<Prm, lt<Prm> >(thePrms, theIdxs, PrmCount);
		}
		else
			itemsort<Prm, lt<Prm> >(thePrms, PrmCount);
	}

	#if CompUpwd
	tFuncLvl = 0;
	#endif//CompUpwd

	Bll tUpdatable = false;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{

		tPrmSpecs[tPos] = thePrms[tPos].PrmSpec;
		tPrmVars.insert();

		switch(thePrms[tPos].TermGen)
		{
			case Tv :
				{
					Hdl tHdl = thePrms[tPos].TermHdl;
					tPrmTerms[tPos] = mTermSys.ptrmVar(tHdl);

					tUpdatable = true;
					Sqn tSqn = tFuncVars.itemCount();
					Itr tItr = tVarHdlSqns.findItr(tHdl);
					if (tItr == InvItr)
					{
						tVarHdlSqns.insertMem(tHdl, tSqn);
						tFuncVars.insertMem(tHdl);

						#if CompDnwd
						tVarUpdtPrms.insertMem();
						#endif//CompDnwd
					}
					else
						tSqn = tVarHdlSqns.item(tItr);

					#if CompDnwd
					tVarUpdtPrms[tSqn].insertMem(tPos);	//	the order of params pushed is the order of params in tFuncPrms.
					#endif//CompDnwd
					tPrmVars[tPos].insertMem(tSqn);	//	the above order is important for non-commutative funcs.
				}
				break;
			case Tf :
				{
					Func * tPrmFunc = mTermSys.ptrmFunc(thePrms[tPos].TermHdl);
					tPrmTerms[tPos] = tPrmFunc;

					if (tPrmFunc->updatable()) tUpdatable = true;

					#if CompUpwd
					tFuncLvl = max(tFuncLvl, tPrmFunc->FuncLvl);
					#endif//CompUpwd

					b1<Hdl,xmm> const & tPrmFuncVars = tPrmFunc->FuncVars;
					for (Sqn tPrmSqn = 0; tPrmSqn < tPrmFuncVars.itemCount(); ++tPrmSqn)
					{
						Hdl tHdl = tPrmFuncVars[tPrmSqn];
						Sqn tSqn = tFuncVars.itemCount();
						Itr tItr = tVarHdlSqns.findItr(tHdl);
						if (tItr == InvItr)
						{
							tVarHdlSqns.insertMem(tHdl, tSqn);
							tFuncVars.insertMem(tHdl);

							#if CompDnwd
							tVarUpdtPrms.insertMem();
							#endif//CompDnwd
						}
						else
							tSqn = tVarHdlSqns.item(tItr);
						#if CompDnwd
						if (tPrmFunc->updatable())
							tVarUpdtPrms[tSqn].insertMem(tPos);	//	the order of params pushed is the order of params in tFuncPrms.
						#endif//CompDnwd
						tPrmVars[tPos].insertMem(tSqn);	//	the above order is important for non-commutative funcs.
					}
				}
				break;
			case Tc :
				tPrmTerms[tPos] = mTermSys.ptrmConst(thePrms[tPos].TermHdl);
				break;
			default :
				Throw(eTermGenUndefined);
				break;
		}
	}
	#if CompUpwd
	++tFuncLvl;
	#endif//CompUpwd

	setUpdatable(tUpdatable);
	CatchError
}



/*!
	Set up for downward computation.
*/
void Func::setupComputation()
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);
	Warn(!updatable(), eTermNotUpdatable);

	#if ExecDnwdMultiCand
		if (mTermSys.MultiCandExec && !mCandMrgBlk)
			mCandMrgBlk = new b1<Pos, xmm>;
	#endif

	#if SimulDnwdMultiFixed
		if (mTermSys.MultiFixedSimul && !mFixedMrgBlk)
			mFixedMrgBlk = new b1<Pos, xmm>;
	#endif

	#if SimulDnwdMultiFlexi
		if (mTermSys.MultiFlexiSimul)
		{
			if (!mFlexiMrgBlk)
				mFlexiMrgBlk = new b1<Pos, xmm>;
			if (!mLblFlexiPrms)
				mLblFlexiPrms = new lf<Pos, kmm>(mPrmTerms.itemCount());
		}
	#endif

	#if CompUpwd && UpwdMapFuncVarArray
		if (!mVarHdlSqns && careFuncVarSqn())
		{
			mVarHdlSqns = new b1<Sqn, kmm>(mTermSys.varCount());
			for(Hdl tHdl = 0; tHdl < mTermSys.varCount(); ++tHdl)
				ccast<b1<Sqn, kmm> *>(mVarHdlSqns)->item(tHdl) = InvSqn;
			for(Sqn tSqn = 0; tSqn < FuncVars.itemCount(); ++tSqn)
				ccast<b1<Sqn, kmm> *>(mVarHdlSqns)->item(FuncVars[tSqn]) = tSqn;
		}
	#endif

	#if CompDnwd
		#if DnwdMapFuncVar == MfvFuncArrayVar
			if (!mVarHdlSqns)
			{
				mVarHdlSqns = new b1<Sqn, kmm>(mTermSys.varCount());
				for(Hdl tHdl = 0; tHdl < mTermSys.varCount(); ++tHdl)
					ccast<b1<Sqn, kmm> *>(mVarHdlSqns)->item(tHdl) = InvSqn;
				for(Sqn tSqn = 0; tSqn < FuncVars.itemCount(); ++tSqn)
					ccast<b1<Sqn, kmm> *>(mVarHdlSqns)->item(FuncVars[tSqn]) = tSqn;
			}
		#elif DnwdVarMapFunc
			for(Sqn tSqn = 0; tSqn < FuncVars.itemCount(); ++tSqn)
				mTermSys.refmVar(FuncVars[tSqn]).setFuncHdlSqn(this->TermHdl, tSqn);
		#elif DnwdSysMapFuncVar
			for(Sqn tSqn = 0; tSqn < FuncVars.itemCount(); ++tSqn)
				mTermSys.setSqn(this->TermHdl, FuncVars[tSqn], tSqn);
		#endif
	#endif
	CatchError
}



/*!
	Find sqn for a given variable.
*/
Sqn Func::findVarSqn(Hdl const hdlVar) const
{
	WatchError
	#if CompUpwd
		Warn(!careFuncVarSqn(),eDontCareFuncVarSqn);
		#if UpwdMapFuncVarArray
			return mVarHdlSqns->item(hdlVar);
		#else
			Itr tItr = mVarHdlSqns.findItr(hdlVar);
			if (tItr == InvItr)
				return InvSqn;
			else
				return mVarHdlSqns.item(tItr);
		#endif
	#endif
	#if CompDnwd
		#if DnwdMapFuncVar == MfvFuncArrayVar
			return mVarHdlSqns->item(hdlVar);
		#elif DnwdMapFuncVar == MfvFuncHashVar
			Itr tItr = mVarHdlSqns.findItr(hdlVar);
			if (tItr == InvItr)
				return InvSqn;
			else
				return mVarHdlSqns.item(tItr);
		#elif DnwdVarMapFunc
			return mTermSys.refcVar(hdlVar).findFuncSqn(this->TermHdl);
		#elif DnwdSysMapFuncVar
			return mTermSys.findSqn(this->TermHdl, hdlVar);
		#endif
	#endif
	CatchError
}



#if ExecDnwd
/*!
	List the candidate parameters for execIncr.
*/
void Func::listCandParams()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);

	ll<Hdl, xmm> const & tExecAsgnVars = mTermSys.ExecAsgnVars();

	Warn(!tExecAsgnVars.tagCount(), eNoExecAsgnVars);

	#if ExecDnwdMultiCand
	if (tExecAsgnVars.tagCount() == 1)
	{
	#else
	Warn(tExecAsgnVars.tagCount() != 1, eMultiAsgnVars);
	#endif
		Sqn tSqn = findVarSqn(tExecAsgnVars[0]);
		if (tSqn == InvSqn)
			mBlkCandPrms = &mProxyPrmBlk;
		else
			mBlkCandPrms = &mVarUpdtPrms[tSqn];
	#if ExecDnwdMultiCand
	}
	else
	{
		Warn(!mCandMrgBlk, eNullPointer);

		mCandMrgBlk->clear();
		mLblCandPrms.sweep(mTermSys.ExecAsgnClk());
		for(Itr tItrVar = 0; tItrVar != tExecAsgnVars.tagCount(); ++tItrVar)
		{
			Sqn tSqn = findVarSqn(tExecAsgnVars[tItrVar]);
			if (tSqn == InvSqn) continue;
			b1<Pos, xmm> const & tVarUpdtPrms = mVarUpdtPrms[tSqn];
			for(Itr tItrPrm = 0; tItrPrm < tVarUpdtPrms.itemCount(); ++tItrPrm)
			{
				Pos const tPos = tVarUpdtPrms[tItrPrm];
				if (mLblCandPrms.tagBll(tPos))
					mCandMrgBlk->insertMem(tPos);
			}
		}
		mBlkCandPrms = mCandMrgBlk;
	}
	#endif	//	ExecDnwdMultiCand
	CatchError
}
#endif//ExecDnwd



#if ExecDnwd
/*!
	Mark the candidate parameters for execIncr.
*/
void Func::markCandParams()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);

	ll<Hdl, xmm> const & tExecAsgnVars = mTermSys.ExecAsgnVars();

	Warn(!tExecAsgnVars.tagCount(), eNoExecAsgnVars);

	#if ExecDnwdMultiCand
	if (tExecAsgnVars.tagCount() == 1)
	{
	#else
	Warn(tExecAsgnVars.tagCount() != 1, eMultiAsgnVars);
	#endif
		mLblCandPrms.sweep(mTermSys.ExecAsgnClk());
		Sqn tSqn = findVarSqn(tExecAsgnVars[0]);
		if (tSqn == InvSqn)
			mBlkCandPrms = &mProxyPrmBlk;
		else
		{
			mBlkCandPrms = &mVarUpdtPrms[tSqn];
			for(Itr tItrPrm = 0; tItrPrm < mBlkCandPrms->itemCount(); ++tItrPrm)
				mLblCandPrms.tag(mBlkCandPrms->item(tItrPrm));
		}
	#if ExecDnwdMultiCand
	}
	else
	{
		Warn(!mCandMrgBlk, eNullPointer);

		mCandMrgBlk->clear();
		mLblCandPrms.sweep(mTermSys.ExecAsgnClk());
		for(Itr tItrVar = 0; tItrVar != tExecAsgnVars.tagCount(); ++tItrVar)
		{
			Sqn tSqn = findVarSqn(tExecAsgnVars[tItrVar]);
			if (tSqn == InvSqn) continue;
			b1<Pos,xmm> const & tVarUpdtPrms = mVarUpdtPrms[tSqn];
			for(Itr tItrPrm = 0; tItrPrm < tVarUpdtPrms.itemCount(); ++tItrPrm)
			{
				Pos const tPos = tVarUpdtPrms[tItrPrm];
				if (mLblCandPrms.tagBll(tPos))
					mCandMrgBlk->insertMem(tPos);
			}
		}
		mBlkCandPrms = mCandMrgBlk;
	}
	#endif	//	ExecDnwdMultiCand
	CatchError
}
#endif//ExecDnwd



#if SimulDnwdFixed
/*!
	List the fixed parameters for simulIncr.
*/
void Func::listFixedParams()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskSimulMode(IncrProp), eNotSimulIncrProp);

	lp<Hdl, xmm> const & tSimulAsgnVars = mTermSys.SimulAsgnVars();
	switch(tSimulAsgnVars.fixedCount())
	{
		case 0: mBlkFixedPrms = &mProxyPrmBlk; break;
		case 1:
			{
				Sqn tSqn = findVarSqn(tSimulAsgnVars[0]);
				if (tSqn == InvSqn)
					mBlkFixedPrms = &mProxyPrmBlk;
				else
					mBlkFixedPrms = &mVarUpdtPrms[tSqn];
			}
			break;
		default:
			#if SimulDnwdMultiFixed
				Warn(!mFixedMrgBlk, eNullPointer);

				mFixedMrgBlk->clear();
				mLblFixedPrms.sweep(mTermSys.SimulAsgnClk());
				for(Itr tItrVar = 0; tItrVar < tSimulAsgnVars.fixedCount(); ++tItrVar)
				{
					Sqn tSqn = findVarSqn(tSimulAsgnVars[tItrVar]);
					if (tSqn == InvSqn) continue;
					b1<Pos,xmm> const & tVarUpdtPrms = mVarUpdtPrms[tSqn];
					for(Itr tItrPrm = 0; tItrPrm < tVarUpdtPrms.itemCount(); ++tItrPrm)
					{
						Pos const tPos = tVarUpdtPrms[tItrPrm];
						if (mLblFixedPrms.tagBll(tPos))
							mFixedMrgBlk->insertMem(tPos);
					}
				}
				mBlkFixedPrms = mFixedMrgBlk;
			#else	//	SimulDnwdMultiFixed
				Warn(tSimulAsgnVars.fixed() != 1, eMultiAsgnVars);
			#endif	//	SimulDnwdMultiFixed
			break;
	}
	CatchError
}
#endif	//SimulDnwdFixed



#if SimulDnwdFixed
/*!
	Mark the fixed parameters for simulIncr.
*/
void Func::markFixedParams()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskSimulMode(IncrProp), eNotSimulIncrProp);

	lp<Hdl, xmm> const & tSimulAsgnVars = mTermSys.SimulAsgnVars();
	switch(tSimulAsgnVars.fixedCount())
	{
		case 0:
			mLblFixedPrms.sweep(mTermSys.SimulAsgnClk());
			mBlkFixedPrms = &mProxyPrmBlk;
			break;
		case 1:
			{
				mLblFixedPrms.sweep(mTermSys.SimulAsgnClk());
				Sqn tSqn = findVarSqn(tSimulAsgnVars[0]);
				if (tSqn == InvSqn)
					mBlkFixedPrms = &mProxyPrmBlk;
				else
				{
					mBlkFixedPrms = &mVarUpdtPrms[tSqn];
					for(Itr tItrPrm = 0; tItrPrm < mBlkFixedPrms->itemCount(); ++tItrPrm)
							mLblFixedPrms.tag(mBlkFixedPrms->item(tItrPrm));
				}
			}
			break;
		default:
			#if SimulDnwdMultiFixed
				Warn(!mFixedMrgBlk, eNullPointer);

				mFixedMrgBlk->clear();
				mLblFixedPrms.sweep(mTermSys.SimulAsgnClk());
				for(Itr tItrVar = 0; tItrVar < tSimulAsgnVars.fixedCount(); ++tItrVar)
				{
					Sqn tSqn = findVarSqn(tSimulAsgnVars[tItrVar]);
					if (tSqn == InvSqn) continue;
					b1<Pos,xmm> const & tVarUpdtPrms = mVarUpdtPrms[tSqn];
					for(Itr tItrPrm = 0; tItrPrm < tVarUpdtPrms.itemCount(); ++tItrPrm)
					{
						Pos const tPos = tVarUpdtPrms[tItrPrm];
						if (mLblFixedPrms.tagBll(tPos))
							mFixedMrgBlk->insertMem(tPos);
					}
				}
				mBlkFixedPrms = mFixedMrgBlk;
			#else	//	SimulDnwdMultiFixed
				Warn(tSimulAsgnVars.fixed() != 1, eMultiAsgnVars);
			#endif	//	SimulDnwdMultiFixed
			break;
	}
	CatchError
}
#endif	//SimulDnwdFixed




#if SimulDnwdFlexi
/*!
	List the flexible parameters for simulIncr.
*/
void Func::listFlexiParams()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskSimulMode(IncrProp), eNotSimulIncrProp);

	lp<Hdl, xmm> const & tSimulAsgnVars = mTermSys.SimulAsgnVars();
	switch(tSimulAsgnVars.flexiCount())
	{
		case 0: mBlkFlexiPrms = &mProxyPrmBlk; return;
		case 1:
			{
				Sqn tSqn = findVarSqn(tSimulAsgnVars[tSimulAsgnVars.flexiVerge()]);
				if (tSqn == InvSqn)
					mBlkFlexiPrms = &mProxyPrmBlk;
				else
					mBlkFlexiPrms = &mVarUpdtPrms[tSqn];
				return;
			}
		default:
			#if SimulDnwdMultiFlexi
				Warn(!mFlexiMrgBlk, eNullPointer);
				Warn(!mLblFlexiPrms, eNullPointer);

				mFlexiMrgBlk->clear();
				mLblFlexiPrms->sweep(mTermSys.SimulAsgnClk());
				for(Itr tItrVar = tSimulAsgnVars.flexiVerge();
						tItrVar < tSimulAsgnVars.tagCount(); ++tItrVar)
				{
					Sqn tSqn = findVarSqn(tSimulAsgnVars[tItrVar]);
					if (tSqn == InvSqn) continue;
					b1<Pos,xmm> const & tVarUpdtPrms = mVarUpdtPrms[tSqn];
					for(Itr tItrPrm = 0; tItrPrm < tVarUpdtPrms.itemCount(); ++tItrPrm)
					{
						Pos const tPos = tVarUpdtPrms[tItrPrm];
						if (mLblFlexiPrms->tagBll(tPos))
							mFlexiMrgBlk->insertMem(tPos);
					}
				}
				mBlkFlexiPrms = mFlexiMrgBlk;
			#else	//	SimulDnwdMultiFlexi
				Warn(tSimulAsgnVars.flexi() != 1, eMultiAsgnVars);
			#endif	//	SimulDnwdMultiFlexi
			return;
	}
	CatchError
}
#endif	//SimulDnwdFlexi



#if SimulDnwdFlexi
/*!
	Mark the flexible parameters for simulIncr.
*/
void Func::markFlexiParams()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskSimulMode(IncrProp), eNotSimulIncrProp);
	Warn(!mLblFlexiPrms, eNullPointer);

	lp<Hdl, xmm> const & tSimulAsgnVars = mTermSys.SimulAsgnVars();
	switch(tSimulAsgnVars.flexiCount())
	{
		case 0:
			mLblFlexiPrms->sweep(mTermSys.SimulAsgnClk());
			mBlkFlexiPrms = &mProxyPrmBlk;
			return;
		case 1:
			{
				mLblFlexiPrms->sweep(mTermSys.SimulAsgnClk());
				Sqn tSqn = findVarSqn(tSimulAsgnVars[tSimulAsgnVars.flexiVerge()]);
				if (tSqn == InvSqn)
					mBlkFlexiPrms = &mProxyPrmBlk;
				else
				{
					mBlkFlexiPrms = &mVarUpdtPrms[tSqn];
					for(Itr tItrPrm = 0; tItrPrm < mBlkFlexiPrms->itemCount(); ++tItrPrm)
							mLblFlexiPrms->tag(mBlkFlexiPrms->item(tItrPrm));
				}
				return;
			}
		default:
			#if SimulDnwdMultiFlexi
				Warn(!mFlexiMrgBlk, eNullPointer);

				mFlexiMrgBlk->clear();
				mLblFlexiPrms->sweep(mTermSys.SimulAsgnClk());
				for(Itr tItrVar = tSimulAsgnVars.flexiVerge();
						tItrVar < tSimulAsgnVars.tagCount(); ++tItrVar)
				{
					Sqn tSqn = findVarSqn(tSimulAsgnVars[tItrVar]);
					if (tSqn == InvSqn) continue;
					b1<Pos,xmm> const & tVarUpdtPrms = mVarUpdtPrms[tSqn];
					for(Itr tItrPrm = 0; tItrPrm < tVarUpdtPrms.itemCount(); ++tItrPrm)
					{
						Pos const tPos = tVarUpdtPrms[tItrPrm];
						if (mLblFlexiPrms->tagBll(tPos))
							mFlexiMrgBlk->insertMem(tPos);
					}
				}
				mBlkFlexiPrms = mFlexiMrgBlk;
			#else	//	SimulDnwdMultiFlexi
				Warn(tSimulAsgnVars.flexi() != 1, eMultiAsgnVars);
			#endif	//	SimulDnwdMultiFlexi
			return;
	}
	CatchError
}
#endif	//SimulDnwdFlexi



/*!
	Care for tabu effect
*/
Typ Func::careTabuEffect() const
{
	WatchError
	return TabuTypNil;
	CatchError
}


/*!
	Compute tabu effect.
*/
void Func::computeTabuEffect()
{
	WatchError
	Throw(eUndefTabuEffect);
	CatchError
}



/*!
	Care for lock effect?
*/
Bll Func::careLockEffect() const
{
	WatchError
	return false;
	CatchError
}


/*!
	Compute lock effect.
*/
void Func::computeLockEffect()
{
	WatchError
	Throw(eUndefLockEffect);
	CatchError
}



/*!
	Care for function variable sequent mapping?
*/
Bll Func::careFuncVarSqn() const
{
	WatchError
	#if CompUpwd
	return false;
	#endif
	#if CompDnwd
	return true;
	#endif
	CatchError
}



closeKangarooSpace
