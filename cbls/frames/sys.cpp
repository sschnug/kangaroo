/*!
	@file sys.cpp
	@brief The implementation file for Sys class.
	@details This is the implementation file for Sys class.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see sys.hpp
*/



#include "cbls/frames/sys.hpp"
#include "cbls/frames/term.hpp"
#include "cbls/frames/var.hpp"
#include "cbls/frames/const.hpp"
#include "cbls/frames/func.hpp"
#include "cbls/frames/selc.hpp"
#include "cbls/frames/tabu.hpp"



openKangarooSpace



/*!
	Return pack of systems.
*/
pbd<Sys,xmm> & Sys::SysBase()
{
	WatchError
	static  pbd<Sys,xmm> mSys;
	return mSys;
	CatchError
}



/*!
	Return hash value for terms.
*/
Hvl Sys::thash::iof(Term const * theTerm)
{
	WatchError
	return theTerm->TermHvl;
	CatchError
}



/*!
	Equal operator for terms.
*/
Bll Sys::tequal::iof(Term const * leftTerm, Term const * rightTerm)
{
	WatchError
	return leftTerm->equate(*rightTerm);
	CatchError
}



/*!
	Return hash value for selectors.
*/
Hvl Sys::shash::iof(Selc const * theSelc)
{
	WatchError
	return theSelc->SelcHvl;
	CatchError
}




/*!
	Refer to a term in the system.
*/
Term & Sys::refmTerm(Gen const genTerm, Hdl const hdlTerm)
{
	WatchError
	switch(genTerm)
	{
		case Tc : return refmConst(hdlTerm);
		case Tv : return refmVar(hdlTerm);
		case Tf : return refmFunc(hdlTerm);
		default : Throw(eTermGenUndefined);
	}
	CatchError
}




/*!
	Point to a term in the system.
*/
Term * Sys::ptrmTerm(Gen const genTerm, Hdl const hdlTerm)
{
	WatchError
	switch(genTerm)
	{
		case Tc : return ptrmConst(hdlTerm);
		case Tv : return ptrmVar(hdlTerm);
		case Tf : return ptrmFunc(hdlTerm);
		default : Throw(eTermGenUndefined);
	}
	CatchError
}




/*!
	Refer to a term in the system.
*/
Term const & Sys::refcTerm(Gen const genTerm, Hdl const hdlTerm) const
{
	WatchError
	switch(genTerm)
	{
		case Tc : return refcConst(hdlTerm);
		case Tv : return refcVar(hdlTerm);
		case Tf : return refcFunc(hdlTerm);
		default : Throw(eTermGenUndefined);
	}
	CatchError
}




/*!
	Point to a term in the system.
*/
Term const * Sys::ptrcTerm(Gen const genTerm, Hdl const hdlTerm) const
{
	WatchError
	switch(genTerm)
	{
		case Tc : return ptrcConst(hdlTerm);
		case Tv : return ptrcVar(hdlTerm);
		case Tf : return ptrcFunc(hdlTerm);
		default : Throw(eTermGenUndefined);
	}
	CatchError
}



/*!
	Equal operator for selectors.
*/
Bll Sys::sequal::iof(Selc const * leftSelc, Selc const * rightSelc)
{
	WatchError
	return leftSelc->equate(*rightSelc);
	CatchError
}



/*!
	The constructor.
*/
Sys::Sys() :
		SysHdl(InvHdl),
		#if ExecDnwdMultiCand
			MultiCandExec(false),
		#endif
		#if SimulDnwdMultiFixed
			MultiFixedSimul(false),
		#endif
		#if SimulDnwdMultiFlexi
			MultiFlexiSimul(false),
		#endif
		mExecMode(NullComp),
		mSimulMode(NullComp),
		mExecClk(NotClk),
		mSimulClk(NotClk),
		mExecAsgnClk(NotClk),
		mSimulAsgnClk(NotClk),
		#if SimulDnwdFixed
			mSimulFixedClk(InvClk),
		#endif
		#if SimulDnwdFlexi
			mSimulFlexiClk(InvClk),
		#endif
		#if SimulDnwdCache
			mSimulCacheClk(NotClk),
		#endif
//		mTermSet(),
//		mConstTerm(),
//		mVarBlk(),
//		mDynUpdtVars(),
//		#if CompLazyHalf
//		mReqUpdtVars(),
//		#endif
//		mFuncBlk(),
//		mRootFuncs(),
//		#if CompLazyHalf
//			 mReqFuncs(),
//		#endif
		#if CompUpwd
			mMaxFuncLvl(0),
		#endif
//		#if ExecUpwd
//			#if (ScheduleQueue == SchQsIterAllLvls)
//				, mBlkExecFuncs(0)
//				, mRckExecFuncs(0)
//			#elif (ScheduleQueue == SchQsStdHeapLvls)
//				, mBlkExecFuncs(0)
//				, mRckExecFuncs(0)
//				, mHipExecFuncs(0)
//			#elif (ScheduleQueue == SchQsAltHeapLvls)
//				, mBlkExecFuncs(0)
//				, mRckExecFuncs(0)
//				, mHipExecFuncs(0)
//			#elif (ScheduleQueue == SchStdHeapLvls)
//				, mBlkExecFuncs(0)
//				, mHipExecFuncs(0)
//			#elif (ScheduleQueue == SchStdHeapHdls)
//				, mBlkExecFuncs(0)
//				, mHipExecFuncs(0)
//			#elif (ScheduleQueue == SchAltHeapLvls)
//				, mHipExecFuncs(0)
//			#elif (ScheduleQueue == SchAltHeapHdls)
//				, mHipExecFuncs(0)
//			#endif
//		#endif
//		#if SimulUpwd
//			#if (ScheduleQueue == SchQsIterAllLvls)
//				, mBlkSimulFuncs(0)
//				, mRckSimulFuncs(0)
//			#elif (ScheduleQueue == SchQsStdHeapLvls)
//				, mBlkSimulFuncs(0)
//				, mRckSimulFuncs(0)
//				, mHipSimulFuncs(0)
//			#elif (ScheduleQueue == SchQsAltHeapLvls)
//				, mBlkSimulFuncs(0)
//				, mRckSimulFuncs(0)
//				, mHipSimulFuncs(0)
//			#elif (ScheduleQueue == SchStdHeapLvls)
//				, mBlkSimulFuncs(0)
//				, mHipSimulFuncs(0)
//			#elif (ScheduleQueue == SchStdHeapHdls)
//				, mBlkSimulFuncs(0)
//				, mHipSimulFuncs(0)
//			#elif (ScheduleQueue == SchAltHeapLvls)
//				, mHipSimulFuncs(0)
//			#elif (ScheduleQueue == SchAltHeapHdls)
//				, mHipSimulFuncs(0)
//			#endif
//		#endif
//		mExecAsgnVars(),
//		mSimulAsgnVars(),
		mSysLock(mVarBlk),
		mEvalDbs(mDfltTbls),
		mHintDbs(mDfltTbls),
		mTabuDbs(mDfltTbls)//,
//		mSelcBlk(),
//		mSelcSet()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
Sys::Sys(Sys const & that) :
		SysHdl(InvHdl),
		#if ExecDnwdMultiCand
			MultiCandExec(that.MultiCandExec),
		#endif
		#if SimulDnwdMultiFixed
			MultiFixedSimul(that.MultiFixedSimul),
		#endif
		#if SimulDnwdMultiFlexi
			MultiFlexiSimul(that.MultiFlexiSimul),
		#endif
		mExecMode(NullComp),
		mSimulMode(NullComp),
		mExecClk(NotClk),
		mSimulClk(NotClk),
		mExecAsgnClk(NotClk),
		mSimulAsgnClk(NotClk),
		#if SimulDnwdFixed
			mSimulFixedClk(InvClk),
		#endif
		#if SimulDnwdFlexi
			mSimulFlexiClk(InvClk),
		#endif
		#if SimulDnwdCache
			mSimulCacheClk(NotClk),
		#endif
//		mTermSet(),
//		mConstBlk(),
//		mVarBlk(),
//		mDynUpdtVars(),
//		#if CompLazyHalf
//		mReqUpdtVars(),
//		#endif
//		mFuncTerm(),
//		mRootFuncs(),
//		#if CompLazyHalf
//			mReqFuncs(),
//		#endif
		#if CompUpwd
			mMaxFuncLvl(0),
		#endif
//		#if ExecUpwd
//			#if (ScheduleQueue == SchQsIterAllLvls)
//				, mBlkExecFuncs(0)
//				, mRckExecFuncs(0)
//			#elif (ScheduleQueue == SchQsStdHeapLvls)
//				, mBlkExecFuncs(0)
//				, mRckExecFuncs(0)
//				, mHipExecFuncs(0)
//			#elif (ScheduleQueue == SchQsAltHeapLvls)
//				, mBlkExecFuncs(0)
//				, mRckExecFuncs(0)
//				, mHipExecFuncs(0)
//			#elif (ScheduleQueue == SchStdHeapLvls)
//				, mBlkExecFuncs(0)
//				, mHipExecFuncs(0)
//			#elif (ScheduleQueue == SchStdHeapIdns)
//				, mBlkExecFuncs(0)
//				, mHipExecFuncs(0)
//			#elif (ScheduleQueue == SchAltHeapLvls)
//				, mHipExecFuncs(0)
//			#elif (ScheduleQueue == SchAltHeapIdns)
//				, mHipExecFuncs(0)
//			#endif
//		#endif
//		#if SimulUpwd
//			#if (ScheduleQueue == SchQsIterAllLvls)
//				, mBlkSimulFuncs(0)
//				, mRckSimulFuncs(0)
//			#elif (ScheduleQueue == SchQsStdHeapLvls)
//				, mBlkSimulFuncs(0)
//				, mRckSimulFuncs(0)
//				, mHipSimulFuncs(0)
//			#elif (ScheduleQueue == SchQsAltHeapLvls)
//				, mBlkSimulFuncs(0)
//				, mRckSimulFuncs(0)
//				, mHipSimulFuncs(0)
//			#elif (ScheduleQueue == SchStdHeapLvls)
//				, mBlkSimulFuncs(0)
//				, mHipSimulFuncs(0)
//			#elif (ScheduleQueue == SchStdHeapIdns)
//				, mBlkSimulFuncs(0)
//				, mHipSimulFuncs(0)
//			#elif (ScheduleQueue == SchAltHeapLvls)
//				, mHipSimulFuncs(0)
//			#elif (ScheduleQueue == SchAltHeapIdns)
//				, mHipSimulFuncs(0)
//			#endif
//		#endif
//		mExecAsgnVars(),
//		mSimulAsgnVars(),
		mSysLock(that.mVarBlk),
		mEvalDbs(mDfltTbls),
		mHintDbs(mDfltTbls),
		mTabuDbs(mDfltTbls)//,
//		mSelcBlk(),
//		mSelcSet()
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Sys const & Sys::operator = (Sys const & that)
{
	WatchError
	if (this == &that)
		return *this;
	Throw(eUndefAssigner);
	CatchError
}



/*!
	The destructor.
*/
Sys::~Sys()
{
	WatchError
	for(Hdl tHdl = 0; tHdl < mConstBlk.itemCount() ; ++tHdl)
		delete mConstBlk[tHdl];
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount() ; ++tHdl)
		delete mVarBlk[tHdl];
	for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount() ; ++tHdl)
		delete mFuncBlk[tHdl];
	for(Hdl tHdl = 0; tHdl < mSelcBlk.itemCount() ; ++tHdl)
		delete mSelcBlk[tHdl];
	CatchError
}



#if CompLazyHalf
/*!
	Set requirement of a function computation.
*/
void Sys::setFuncRequired(Func * theFunc, Bll const Require)
{
	WatchError
	Warn(chkExecMode(NullComp), eSysUninit);
	Warn(!theFunc->computable(), eTermNotComputable);
	Warn(mskExecMode(AsgnMode), eExecAsgnMode);

	if (Require)
	{
		if (!theFunc->enforced() && theFunc->ReqFuncLink() == InvLnk)
			theFunc->setReqFuncLink(mReqFuncs.insertItrMem(theFunc));
	}
	else
	{
		Lnk const & tLnk = theFunc->ReqFuncLink();
		if (!theFunc->required() && tLnk != InvLnk)
		{
			if (tLnk + 1 == mReqFuncs.itemCount())
				mReqFuncs.remove();
			else
			{
				mReqFuncs.remove(mReqFuncs[tLnk]);
				mReqFuncs[tLnk]->setReqFuncLink(tLnk);
			}
			theFunc->setReqFuncLink(InvLnk);
		}
	}
	CatchError
}
#endif	//CompLazyHalf




/*!
	Define a constant -- ownership is handed over.
	@return The handle where the constant is aleady found or InvHdl.
*/
Hdl Sys::defConst(Const * theConst)
{
	WatchError
	Warn(!theConst, eNullPointer);
	Warn(!chkExecMode(NullComp), eSysUninit);

	Itr tItr =mTermSet.insertItrIfOldMem(theConst);
	if (tItr != InvItr)
		return mTermSet[tItr]->TermHdl;
	Hdl tConstHdl = mConstBlk.insertItrMem(theConst);
	theConst->setTermHdl(tConstHdl);
	return InvHdl;
	CatchError
}



/*!
	Define a variable -- ownership is handed over.
	@return The handle where the variable is aleady found or InvHdl.
*/
Hdl Sys::defVar(Var * theVar)
{
	WatchError
	Warn(!theVar, eNullPointer);
	Warn(!chkExecMode(NullComp), eSysUninit);

	Hdl tVarHdl = mVarBlk.insertItrMem(theVar);
	theVar->setTermHdl(tVarHdl);
	if (theVar->DomainUpdateDefined())
	{
		Itr tItr = mDynUpdtVars.insertItrMem(theVar);
		theVar->setDynaUpdtLink(tItr);
		#if CompLazyHalf
		mReqUpdtVars.insertMem();
		#endif
	}

	return InvHdl;
	CatchError
}



#if CompLazyHalf
/*!
	Set a required dynamic variable update.
*/
void Sys::setVarUpdateRequired(Var * theVar, Bll const Update)
{
	WatchError
	Warn(chkExecMode(NullComp), eSysUninit);
	Warn(!theVar->DomainUpdateDefined(), eDomainNotUpdatable);
	if (Update)
	{
		if (mReqUpdtVars.tagBll(theVar->DynaUpdtLink()))
			theVar->updateDomain();
	}
	else
		mReqUpdtVars.untagBll(theVar->DynaUpdtLink());
	CatchError
}
#endif	//CompLazyHalf



#if CompLazyHalf
/*!
	Return whether var domain update is required.
*/
Bll Sys::VarUpdateRequired(Var const * theVar)
{
	WatchError
	Lnk tLink = theVar->DynaUpdtLink();
	Warn(tLink == InvLnk || !theVar->DomainUpdateDefined(), eDomainNotUpdatable);
	return mReqUpdtVars.tagged(tLink);
	CatchError
}
#endif //CompLazyHalf



/*!
	Define a function -- ownership is handed over.
	@return The handle where the function is aleady found or InvHdl.
*/
Hdl Sys::defFunc(Func * theFunc)
{
	WatchError
	Warn(!theFunc, eNullPointer);
	Warn(!chkExecMode(NullComp), eSysUninit);

	Itr tItr =mTermSet.insertItrIfOldMem(theFunc);
	if (tItr != InvItr)
		return mTermSet[tItr]->TermHdl;

	Hdl tFuncHdl = mFuncBlk.insertItrMem(theFunc);
	theFunc->setTermHdl(tFuncHdl);

	b1<Term *, kmm> const & tPrmTerms = theFunc->mPrmTerms;
	for(Pos tPos = 0; tPos < tPrmTerms.itemCount(); ++tPos)
	{
		Term * tPrmTerm = tPrmTerms[tPos];
		#if CompDnwd
		Lnk const tLnk = tPrmTerm->setArg(Arg(theFunc, tPos));
		theFunc->setParamLink(tPos, tLnk);
		#elif CompUpwd	//	This is different from other scenarios
		tPrmTerm->setArg(Arg(theFunc, tPos));
		#endif//CompUpwd
	}
	#if CompUpwd
	if (theFunc->FuncLvl > mMaxFuncLvl)
		mMaxFuncLvl = theFunc->FuncLvl;
	#endif
	if (theFunc->careLockEffect())
		mSysLock.regFunc(theFunc);
	Typ tTyp = theFunc->careTabuEffect();
	if (tTyp != TabuTypNil)
	{
		Tabu & tTabu = refmTabu(tTyp);
		if (tTabu.Callback) tTabu.regCallback(theFunc);
	}
	return InvHdl;
	CatchError
}



/*!
	Define a root term.
*/
void Sys::defRoot(Func * theFunc)
{
	WatchError
	Warn(!theFunc, eNullPointer);
	Warn(!chkExecMode(NullComp), eSysUninit);

	if (!theFunc->computable()) return;

	b1<Term *, kmm> const & tPrmTerms = theFunc->mPrmTerms;
	for(Pos tPos = 0; tPos < tPrmTerms.itemCount(); ++tPos)
	{
		Term * tPrmTerm = tPrmTerms[tPos];
		if (!tPrmTerm->computable()) continue;

		Func * tPrmFunc = Func::cast(tPrmTerm);
		Lnk const & tLnk = tPrmFunc->RootFuncLink();
		if (tLnk == InvLnk) continue;
		if (tLnk + 1 == mRootFuncs.itemCount())
			mRootFuncs.remove();
		else
		{
			mRootFuncs.remove(mRootFuncs[tLnk]);
			mRootFuncs[tLnk]->setRootFuncLink(tLnk);
		}
		tPrmFunc->setRootFuncLink(InvLnk);
	}
	Itr tItr = mRootFuncs.insertItrMem(theFunc);
	theFunc->setRootFuncLink(tItr);
	CatchError
}


#if ExecUpwd
/*!
	Schedule for execution.
*/
void Sys::scheduleExecQueue(Func * theFunc)
{
	WatchError
	Warn(!theFunc->computable(), eTermNotComputable);
	#if (ScheduleQueue == SchQsIterAllLvls)
		Bll & tBlkExecFunc = mBlkExecFuncs.item(theFunc->TermHdl);
		if (!tBlkExecFunc)
		{
			tBlkExecFunc = true;
			b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(theFunc->FuncLvl);
			tBlk.insert(theFunc->TermHdl);
		}
	#elif (ScheduleQueue == SchQsStdHeapLvls)
		Bll & tBlkExecFunc = mBlkExecFuncs.item(theFunc->TermHdl);
		if (!tBlkExecFunc)
		{
			tBlkExecFunc = true;
			b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(theFunc->FuncLvl);
			if (!tBlk.itemCount())
				mHipExecFuncs.insert(theFunc->FuncLvl);
			tBlk.insert(theFunc->TermHdl);
		}
	#elif (ScheduleQueue == SchQsAltHeapLvls)
		Bll & tBlkExecFunc = mBlkExecFuncs.item(theFunc->TermHdl);
		if (!tBlkExecFunc)
		{
			tBlkExecFunc = true;
			b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(theFunc->FuncLvl);
			if (!tBlk.itemCount())
				mHipExecFuncs.alter(theFunc->FuncLvl, theFunc->FuncLvl);
			tBlk.insert(theFunc->TermHdl);
		}
	#elif (ScheduleQueue == SchStdHeapLvls)
		Bll & tBlkExecFunc = mBlkExecFuncs.item(theFunc->TermHdl);
		if (!tBlkExecFunc)
		{
			tBlkExecFunc = true;
			mHipExecFuncs.insert(t2a<Lvl,Hdl>(theFunc->FuncLvl, theFunc->TermHdl));
		}
	#elif (ScheduleQueue == SchStdHeapHdls)
		Bll & tBlkExecFunc = mBlkExecFuncs.item(theFunc->TermHdl);
		if (!tBlkExecFunc)
		{
			tBlkExecFunc = true;
			mHipExecFuncs.insert(theFunc->TermHdl);
		}
	#elif (ScheduleQueue == SchAltHeapLvls)
			mHipExecFuncs.alter(theFunc->TermHdl, theFunc->FuncLvl);
	#elif (ScheduleQueue == SchAltHeapHdls)
			mHipExecFuncs.alter(theFunc->TermHdl, theFunc->TermHdl);
	#else
		#error eUnknownScheduleQueue
	#endif
	CatchError
}
#endif // ExecUpwd



#if SimulUpwd
/*!
	Schedule for simulation.
*/
void Sys::scheduleSimulQueue(Func * theFunc)
{
	WatchError
	Warn(!theFunc->computable(), eTermNotComputable);
	#if (ScheduleQueue == SchQsIterAllLvls)
		Bll & tBlkSimulFunc = mBlkSimulFuncs.item(theFunc->TermHdl);
		if (!tBlkSimulFunc)
		{
			tBlkSimulFunc = true;
			b1<Hdl, xmm> & tBlk = mRckSimulFuncs.list(theFunc->FuncLvl);
			tBlk.insert(theFunc->TermHdl);
		}
	#elif (ScheduleQueue == SchQsStdHeapLvls)
		Bll & tBlkSimulFunc = mBlkSimulFuncs.item(theFunc->TermHdl);
		if (!tBlkSimulFunc)
		{
			tBlkSimulFunc = true;
			b1<Hdl, xmm> & tBlk = mRckSimulFuncs.list(theFunc->FuncLvl);
			if (!tBlk.itemCount())
				mHipSimulFuncs.insert(theFunc->FuncLvl);
			tBlk.insert(theFunc->TermHdl);
		}
	#elif (ScheduleQueue == SchQsAltHeapLvls)
		Bll & tBlkSimulFunc = mBlkSimulFuncs.item(theFunc->TermHdl);
		if (!tBlkSimulFunc)
		{
			tBlkSimulFunc = true;
			b1<Hdl, xmm> & tBlk = mRckSimulFuncs.list(theFunc->FuncLvl);
			if (!tBlk.itemCount())
				mHipSimulFuncs.alter(theFunc->FuncLvl, theFunc->FuncLvl);
			tBlk.insert(theFunc->TermHdl);
		}
	#elif (ScheduleQueue == SchStdHeapLvls)
		Bll & tBlkSimulFunc = mBlkSimulFuncs.item(theFunc->TermHdl);
		if (!tBlkSimulFunc)
		{
			tBlkSimulFunc = true;
			mHipSimulFuncs.insert(t2a<Lvl,Hdl>(theFunc->FuncLvl, theFunc->TermHdl));
		}
	#elif (ScheduleQueue == SchStdHeapHdls)
		Bll & tBlkSimulFunc = mBlkSimulFuncs.item(theFunc->TermHdl);
		if (!tBlkSimulFunc)
		{
			tBlkSimulFunc = true;
			mHipSimulFuncs.insert(theFunc->TermHdl);
		}
	#elif (ScheduleQueue == SchAltHeapLvls)
			mHipSimulFuncs.alter(theFunc->TermHdl, theFunc->FuncLvl);
	#elif (ScheduleQueue == SchAltHeapHdls)
			mHipSimulFuncs.alter(theFunc->TermHdl, theFunc->TermHdl);
	#else
		#error eUnknownScheduleQueue
	#endif
	CatchError
}
#endif // SimulUpwd



/*!
	Propagate for exec anew at the system level.
*/
void Sys::initPropagation()
{
	WatchError
	Warn(!chkExecMode(AnewProp), eNotExecAnewProp);

	#if ExecDnwd
	for(Idx tIdx = 0; tIdx < mRootFuncs.itemCount(); ++tIdx)
		Term::performExecAnew(mRootFuncs[tIdx]);
	#endif//ExecDnwd

	#if ExecUpwd
		#if (ScheduleQueue == SchQsIterAllLvls)
			for(Lvl tLvl = 1; tLvl <= mMaxFuncLvl; ++tLvl)
			{
				b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(tLvl);
				for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
				{
					Hdl tHdl = tBlk.item(tIdx);
					Term::performExecAnew(mFuncBlk[tHdl]);
					mBlkExecFuncs[tHdl] = false;
				}
				tBlk.clear();
			}
		#elif (ScheduleQueue == SchQsStdHeapLvls)
			while (mHipExecFuncs.itemCount())
			{
				Lvl tLvl = mHipExecFuncs.itemPeak();
				b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(tLvl);
				for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
				{
					Hdl tHdl = tBlk.item(tIdx);
					Term::performExecAnew(mFuncBlk[tHdl]);
					mBlkExecFuncs[tHdl] = false;
				}
				tBlk.clear();
				mHipExecFuncs.remove();
			}
		#elif (ScheduleQueue == SchQsAltHeapLvls)
			while (mHipExecFuncs.itemPeak() != InvLvl)
			{
				Lvl tLvl = mHipExecFuncs.serialPeak();
				b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(tLvl);
				for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
				{
					Hdl tHdl = tBlk.item(tIdx);
					Term::performExecAnew(mFuncBlk[tHdl]);
					mBlkExecFuncs[tHdl] = false;
				}
				tBlk.clear();
				mHipExecFuncs.alter(tLvl, InvLvl);
			}
		#elif (ScheduleQueue == SchStdHeapLvls)
			while (mHipExecFuncs.itemCount())
			{
				Hdl tHdl = mHipExecFuncs.itemPeak().Second;
				Term::performExecAnew(mFuncBlk[tHdl]);
				mBlkExecFuncs[tHdl] = false;
				mHipExecFuncs.remove();
			}
		#elif (ScheduleQueue == SchStdHeapHdls)
			while (mHipExecFuncs.itemCount())
			{
				Hdl tHdl = mHipExecFuncs.itemPeak();
				Term::performExecAnew(mFuncBlk[tHdl]);
				mBlkExecFuncs[tHdl] = false;
				mHipExecFuncs.remove();
			}
		#elif (ScheduleQueue == SchAltHeapLvls)
			while (mHipExecFuncs.itemPeak() != InvLvl)
			{
				Hdl tHdl = mHipExecFuncs.serialPeak();
				Term::performExecAnew(mFuncBlk[tHdl]);
				mHipExecFuncs.alter(tHdl, InvLvl);
			}
		#elif (ScheduleQueue == SchAltHeapHdls)
			while (mHipExecFuncs.itemPeak() != InvHdl)
			{
				Hdl tHdl = mHipExecFuncs.serialPeak();
				Term::performExecAnew(mFuncBlk[tHdl]);
				mHipExecFuncs.alter(tHdl, InvHdl);
			}
		#else
			#error eUnknownScheduleQueue
		#endif
	#endif//ExecUpwd
	for(Idx tIdx = 0; tIdx < mDynUpdtVars.itemCount(); ++tIdx)
		mDynUpdtVars[tIdx]->updateDomain();
	CatchError
}



/*!
	Propagate for exec anew at the system level.
*/
void Sys::propagateExecAnew()
{
	WatchError
	Warn(!chkExecMode(AnewProp), eNotExecAnewProp);

	for(Idx tItr = 0; tItr < mTabuDbs.packCount(); ++tItr)
	{
		Tabu & tTabu = mTabuDbs.refmDefPack(tItr);
		if (tTabu.automatic() && tTabu.active())
			tTabu.updtTabuAuto();
	}

	#if ExecDnwd
		#if CompLazyHalf
			for(Idx tIdx = 0; tIdx < mReqFuncs.itemCount(); ++tIdx)
				Term::performExecAnew(mReqFuncs[tIdx]);
			for(Idx tIdx = 0; tIdx < mReqUpdtVars.tagCount(); ++tIdx)
				mDynUpdtVars[mReqUpdtVars.serial(tIdx)]->updateDomain();
		#elif !CompLazyFull
			for(Idx tIdx = 0; tIdx < mRootFuncs.itemCount(); ++tIdx)
				Term::performExecAnew(mRootFuncs[tIdx]);
			for(Idx tIdx = 0; tIdx < mDynUpdtVars.itemCount(); ++tIdx)
				mDynUpdtVars[tIdx]->updateDomain();
		#endif // CompLazy
	#endif//ExecDnwd

	#if ExecUpwd
		#if (ScheduleQueue == SchQsIterAllLvls)
			for(Lvl tLvl = 1; tLvl <= mMaxFuncLvl; ++tLvl)
			{
				b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(tLvl);
				for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
				{
					Hdl tHdl = tBlk.item(tIdx);
					Term::performExecAnew(mFuncBlk[tHdl]);
					mBlkExecFuncs[tHdl] = false;
				}
				tBlk.clear();
			}
		#elif (ScheduleQueue == SchQsStdHeapLvls)
			while (mHipExecFuncs.itemCount())
			{
				Lvl tLvl = mHipExecFuncs.itemPeak();
				b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(tLvl);
				for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
				{
					Hdl tHdl = tBlk.item(tIdx);
					Term::performExecAnew(mFuncBlk[tHdl]);
					mBlkExecFuncs[tHdl] = false;
				}
				tBlk.clear();
				mHipExecFuncs.remove();
			}
		#elif (ScheduleQueue == SchQsAltHeapLvls)
			while (mHipExecFuncs.itemPeak() != InvLvl)
			{
				Lvl tLvl = mHipExecFuncs.serialPeak();
				b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(tLvl);
				for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
				{
					Hdl tHdl = tBlk.item(tIdx);
					Term::performExecAnew(mFuncBlk[tHdl]);
					mBlkExecFuncs[tHdl] = false;
				}
				tBlk.clear();
				mHipExecFuncs.alter(tLvl, InvLvl);
			}
		#elif (ScheduleQueue == SchStdHeapLvls)
			while (mHipExecFuncs.itemCount())
			{
				Hdl tHdl = mHipExecFuncs.itemPeak().Second;
				Term::performExecAnew(mFuncBlk[tHdl]);
				mBlkExecFuncs[tHdl] = false;
				mHipExecFuncs.remove();
			}
		#elif (ScheduleQueue == SchStdHeapHdls)
			while (mHipExecFuncs.itemCount())
			{
				Hdl tHdl = mHipExecFuncs.itemPeak();
				Term::performExecAnew(mFuncBlk[tHdl]);
				mBlkExecFuncs[tHdl] = false;
				mHipExecFuncs.remove();
			}
		#elif (ScheduleQueue == SchAltHeapLvls)
			while (mHipExecFuncs.itemPeak() != InvLvl)
			{
				Hdl tHdl = mHipExecFuncs.serialPeak();
				Term::performExecAnew(mFuncBlk[tHdl]);
				mHipExecFuncs.alter(tHdl, InvLvl);
			}
		#elif (ScheduleQueue == SchAltHeapHdls)
			while (mHipExecFuncs.itemPeak() != InvHdl)
			{
				Hdl tHdl = mHipExecFuncs.serialPeak();
				Term::performExecAnew(mFuncBlk[tHdl]);
				mHipExecFuncs.alter(tHdl, InvHdl);
			}
		#else
			#error eUnknownScheduleQueue
		#endif
		for(Idx tIdx = 0; tIdx < mDynUpdtVars.itemCount(); ++tIdx)
			mDynUpdtVars[tIdx]->updateDomain();
	#endif//ExecUpwd
	CatchError
}


/*!
	Propagate for exec incr at the system level.
*/
void Sys::propagateExecIncr()
{
	WatchError
	Warn(!mskExecMode(IncrProp), eNotExecIncrProp);

	for(Idx tItr = 0; tItr < mTabuDbs.packCount(); ++tItr)
	{
		Tabu & tTabu = mTabuDbs.refmDefPack(tItr);
		if (tTabu.automatic() && tTabu.active())
			tTabu.updtTabuAuto();
	}

	#if ExecDnwd
		#if CompLazyHalf
			for(Idx tIdx = 0; tIdx < mReqFuncs.itemCount(); ++tIdx)
				Term::performExecIncr(mReqFuncs[tIdx]);
			for(Idx tIdx = 0; tIdx < mReqUpdtVars.tagCount(); ++tIdx)
				mDynUpdtVars[mReqUpdtVars.serial(tIdx)]->updateDomain();
		#elif !CompLazyFull
			for(Idx tIdx = 0; tIdx < mRootFuncs.itemCount(); ++tIdx)
				Term::performExecIncr(mRootFuncs[tIdx]);
			for(Idx tIdx = 0; tIdx < mDynUpdtVars.itemCount(); ++tIdx)
				mDynUpdtVars[tIdx]->updateDomain();
		#endif // CompLazy
	#endif//ExecDnwd

	#if ExecUpwd
		#if (ScheduleQueue == SchQsIterAllLvls)
			for(Lvl tLvl = 1; tLvl <= mMaxFuncLvl; ++tLvl)
			{
				b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(tLvl);
				for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
				{
					Hdl tHdl = tBlk.item(tIdx);
					Term::performExecIncr(mFuncBlk[tHdl]);
					mBlkExecFuncs[tHdl] = false;
				}
				tBlk.clear();
			}
		#elif (ScheduleQueue == SchQsStdHeapLvls)
			while (mHipExecFuncs.itemCount())
			{
				Lvl tLvl = mHipExecFuncs.itemPeak();
				b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(tLvl);
				for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
				{
					Hdl tHdl = tBlk.item(tIdx);
					Term::performExecIncr(mFuncBlk[tHdl]);
					mBlkExecFuncs[tHdl] = false;
				}
				tBlk.clear();
				mHipExecFuncs.remove();
			}
		#elif (ScheduleQueue == SchQsAltHeapLvls)
			while (mHipExecFuncs.itemPeak() != InvLvl)
			{
				Lvl tLvl = mHipExecFuncs.serialPeak();
				b1<Hdl, xmm> & tBlk = mRckExecFuncs.list(tLvl);
				for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
				{
					Hdl tHdl = tBlk.item(tIdx);
					Term::performExecIncr(mFuncBlk[tHdl]);
					mBlkExecFuncs[tHdl] = false;
				}
				tBlk.clear();
				mHipExecFuncs.alter(tLvl, InvLvl);
			}
		#elif (ScheduleQueue == SchStdHeapLvls)
			while (mHipExecFuncs.itemCount())
			{
				Hdl tHdl = mHipExecFuncs.itemPeak().Second;
				Term::performExecIncr(mFuncBlk[tHdl]);
				mBlkExecFuncs[tHdl] = false;
				mHipExecFuncs.remove();
			}
		#elif (ScheduleQueue == SchStdHeapHdls)
			while (mHipExecFuncs.itemCount())
			{
				Hdl tHdl = mHipExecFuncs.itemPeak();
				Term::performExecIncr(mFuncBlk[tHdl]);
				mBlkExecFuncs[tHdl] = false;
				mHipExecFuncs.remove();
			}
		#elif (ScheduleQueue == SchAltHeapLvls)
			while (mHipExecFuncs.itemPeak() != InvLvl)
			{
				Hdl tHdl = mHipExecFuncs.serialPeak();
				Term::performExecIncr(mFuncBlk[tHdl]);
				mHipExecFuncs.alter(tHdl, InvLvl);
			}
		#elif (ScheduleQueue == SchAltHeapHdls)
			while (mHipExecFuncs.itemPeak() != InvHdl)
			{
				Hdl tHdl = mHipExecFuncs.serialPeak();
				Term::performExecIncr(mFuncBlk[tHdl]);
				mHipExecFuncs.alter(tHdl, InvHdl);
			}
		#else
			#error eUnknownScheduleQueue
		#endif
		for(Idx tIdx = 0; tIdx < mDynUpdtVars.itemCount(); ++tIdx)
			mDynUpdtVars[tIdx]->updateDomain();
	#endif//ExecUpwd
	CatchError
}


#if SimulUpwd
/*!
	Propagate for simul anew at the system level.
*/
void Sys::propagateSimulAnew()
{
	WatchError
	Warn(!chkSimulMode(AnewProp), eNotSimulAnewProp);

	#if (ScheduleQueue == SchQsIterAllLvls)
		for(Lvl tLvl = 1; tLvl <= mMaxFuncLvl; ++tLvl)
		{
			b1<Hdl, xmm> & tBlk = mRckSimulFuncs.list(tLvl);
			for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
			{
				Hdl tHdl = tBlk.item(tIdx);
				Term::performSimulAnew(mFuncBlk[tHdl]);
				mBlkSimulFuncs[tHdl] = false;
			}
			tBlk.clear();
		}
	#elif (ScheduleQueue == SchQsStdHeapLvls)
		while (mHipSimulFuncs.itemCount())
		{
			Lvl tLvl = mHipSimulFuncs.itemPeak();
			b1<Hdl, xmm> & tBlk = mRckSimulFuncs.list(tLvl);
			for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
			{
				Hdl tHdl = tBlk.item(tIdx);
				Term::performSimulAnew(mFuncBlk[tHdl]);
				mBlkSimulFuncs[tHdl] = false;
			}
			tBlk.clear();
			mHipSimulFuncs.remove();
		}
	#elif (ScheduleQueue == SchQsAltHeapLvls)
		while (mHipSimulFuncs.itemPeak() != InvLvl)
		{
			Lvl tLvl = mHipSimulFuncs.serialPeak();
			b1<Hdl, xmm> & tBlk = mRckSimulFuncs.list(tLvl);
			for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
			{
				Hdl tHdl = tBlk.item(tIdx);
				Term::performSimulAnew(mFuncBlk[tHdl]);
				mBlkSimulFuncs[tHdl] = false;
			}
			tBlk.clear();
			mHipSimulFuncs.alter(tLvl, InvLvl);
		}
	#elif (ScheduleQueue == SchStdHeapLvls)
		while (mHipSimulFuncs.itemCount())
		{
			Hdl tHdl = mHipSimulFuncs.itemPeak().Second;
			Term::performSimulAnew(mFuncBlk[tHdl]);
			mBlkSimulFuncs[tHdl] = false;
			mHipSimulFuncs.remove();
		}
	#elif (ScheduleQueue == SchStdHeapHdls)
		while (mHipSimulFuncs.itemCount())
		{
			Hdl tHdl = mHipSimulFuncs.itemPeak();
			Term::performSimulAnew(mFuncBlk[tHdl]);
			mBlkSimulFuncs[tHdl] = false;
			mHipSimulFuncs.remove();
		}
	#elif (ScheduleQueue == SchAltHeapLvls)
		while (mHipSimulFuncs.itemPeak() != InvLvl)
		{
			Hdl tHdl = mHipSimulFuncs.serialPeak();
			Term::performSimulAnew(mFuncBlk[tHdl]);
			mHipSimulFuncs.alter(tHdl, InvLvl);
		}
	#elif (ScheduleQueue == SchAltHeapHdls)
		while (mHipSimulFuncs.itemPeak() != InvHdl)
		{
			Hdl tHdl = mHipSimulFuncs.serialPeak();
			Term::performSimulAnew(mFuncBlk[tHdl]);
			mHipSimulFuncs.alter(tHdl, InvHdl);
		}
	#else
		#error eUnknownScheduleQueue
	#endif
	CatchError
}
#endif//SimulUpwd



#if SimulUpwd
/*!
	Propagate for simul incr at the system level.
*/
void Sys::propagateSimulIncr()
{
	WatchError
	Warn(!mskSimulMode(IncrProp), eNotSimulIncrProp);

	#if (ScheduleQueue == SchQsIterAllLvls)
		for(Lvl tLvl = 1; tLvl <= mMaxFuncLvl; ++tLvl)
		{
			b1<Hdl, xmm> & tBlk = mRckSimulFuncs.list(tLvl);
			for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
			{
				Hdl tHdl = tBlk.item(tIdx);
				Term::performSimulIncr(mFuncBlk[tHdl]);
				mBlkSimulFuncs[tHdl] = false;
			}
			tBlk.clear();
		}
	#elif (ScheduleQueue == SchQsStdHeapLvls)
		while (mHipSimulFuncs.itemCount())
		{
			Lvl tLvl = mHipSimulFuncs.itemPeak();
			b1<Hdl, xmm> & tBlk = mRckSimulFuncs.list(tLvl);
			for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
			{
				Hdl tHdl = tBlk.item(tIdx);
				Term::performSimulIncr(mFuncBlk[tHdl]);
				mBlkSimulFuncs[tHdl] = false;
			}
			tBlk.clear();
			mHipSimulFuncs.remove();
		}
	#elif (ScheduleQueue == SchQsAltHeapLvls)
		while (mHipSimulFuncs.itemPeak() != InvLvl)
		{
			Lvl tLvl = mHipSimulFuncs.serialPeak();
			b1<Hdl, xmm> & tBlk = mRckSimulFuncs.list(tLvl);
			for (Idx tIdx = 0; tIdx < tBlk.itemCount(); ++tIdx)
			{
				Hdl tHdl = tBlk.item(tIdx);
				Term::performSimulIncr(mFuncBlk[tHdl]);
				mBlkSimulFuncs[tHdl] = false;
			}
			tBlk.clear();
			mHipSimulFuncs.alter(tLvl, InvLvl);
		}
	#elif (ScheduleQueue == SchStdHeapLvls)
		while (mHipSimulFuncs.itemCount())
		{
			Hdl tHdl = mHipSimulFuncs.itemPeak().Second;
			Term::performSimulIncr(mFuncBlk[tHdl]);
			mBlkSimulFuncs[tHdl] = false;
			mHipSimulFuncs.remove();
		}
	#elif (ScheduleQueue == SchStdHeapHdls)
		while (mHipSimulFuncs.itemCount())
		{
			Hdl tHdl = mHipSimulFuncs.itemPeak();
			Term::performSimulIncr(mFuncBlk[tHdl]);
			mBlkSimulFuncs[tHdl] = false;
			mHipSimulFuncs.remove();
		}
	#elif (ScheduleQueue == SchAltHeapLvls)
		while (mHipSimulFuncs.itemPeak() != InvLvl)
		{
			Hdl tHdl = mHipSimulFuncs.serialPeak();
			Term::performSimulIncr(mFuncBlk[tHdl]);
			mHipSimulFuncs.alter(tHdl, InvLvl);
		}
	#elif (ScheduleQueue == SchAltHeapHdls)
		while (mHipSimulFuncs.itemPeak() != InvHdl)
		{
			Hdl tHdl = mHipSimulFuncs.serialPeak();
			Term::performSimulIncr(mFuncBlk[tHdl]);
			mHipSimulFuncs.alter(tHdl, InvHdl);
		}
	#else
		#error eUnknownScheduleQueue
	#endif
	CatchError
}
#endif//SimulUpwd



/*!
	Set all system variables as assign variables.
*/
void Sys::setExecAsgnVars()
{
	WatchError
	Warn(!mVarBlk.itemCount(), eEmptyDimension);
	Warn(!mskExecMode(AsgnMode), eNotExecAsgnMode);

	tickExecAsgnClk();
	mExecAsgnVars.sweep(mExecAsgnClk);
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
	{
		mExecAsgnVars.tag(tHdl);

		#if CheckError
		mVarBlk[tHdl]->updtExecAsgnClk();
		#endif//CheckError
	}
	CatchError
}



/*!
	Set an assignment variable in the system.
*/
void Sys::setExecAsgnVar1(Hdl const hdlVar)
{
	WatchError
	Warn(!mskExecMode(AsgnMode), eNotExecAsgnMode);

	tickExecAsgnClk();
	mExecAsgnVars.sweep(mExecAsgnClk);
	mExecAsgnVars.tag(hdlVar);

	#if CheckError
	mVarBlk[hdlVar]->updtExecAsgnClk();
	#endif//CheckError
	CatchError
}



/*!
	Set a pair of assignment variables in the system.
*/
void Sys::setExecAsgnVar2(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(hdlVar1 == hdlVar2, eDuplicateAsgnVars);
	Warn(!mskExecMode(AsgnMode), eNotExecAsgnMode);

	tickExecAsgnClk();
	mExecAsgnVars.sweep(mExecAsgnClk);
	mExecAsgnVars.tag(hdlVar1);
	mExecAsgnVars.tag(hdlVar2);

	#if CheckError
	mVarBlk[hdlVar1]->updtExecAsgnClk();
	mVarBlk[hdlVar2]->updtExecAsgnClk();
	#endif//CheckError
	CatchError
}



/*!
	Set the assignment variables in the system.
*/
void Sys::setExecAsgnVars(Hdl const * hdlVars, Dim const VarCount)
{
	WatchError
	Warn(!mskExecMode(AsgnMode), eNotExecAsgnMode);
	Warn(!VarCount, eEmptyDimension);

	tickExecAsgnClk();
	mExecAsgnVars.sweep(mExecAsgnClk);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
	{
		Hdl tVarHdl = hdlVars[tIdx];

		#if CheckError
		for(Idx sIdx = tIdx + 1; sIdx < VarCount; ++sIdx)
			if (hdlVars[sIdx] == tVarHdl)
				Throw(eDuplicateAsgnVars);
		if (mExecAsgnVars.tagBll(tVarHdl))
			mVarBlk[tVarHdl]->updtExecAsgnClk();
		#else//CheckError
		mExecAsgnVars.tag(tVarHdl);
		#endif//CheckError
	}
	CatchError
}



#if SimulFixed
/*!
	Set a simul asgn variable in the system.
*/
void Sys::setSimulFixedVar1(Hdl const hdlVar)
{
	WatchError
	Warn(mskExecMode(AsgnMode), eExecAsgnMode);
							//	exec mode is checked not simul mode.
	tickSimulAsgnClk();
	#if SimulDnwd
	updtSimulFixedClk();
	#endif
	#if SimulDnwdCache
	tickSimulCacheClk();
	#endif
	#if SimulDnwdFlexi
	if (mSimulAsgnVars.flexiCount())
		updtSimulFlexiClk();
	#endif

	mSimulAsgnVars.sweep(mSimulAsgnClk);
	mSimulAsgnVars.tag(hdlVar);

	#if CheckError
	mVarBlk[hdlVar]->updtSimulAsgnClk();
	#endif//CheckError

	mSimulAsgnVars.split();
	CatchError
}
#endif//SimulFixed


#if SimulFixed
/*!
	Set a pair of simul asgn variables in the system.
*/
void Sys::setSimulFixedVar2(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(hdlVar1 == hdlVar2, eDuplicateAsgnVars);
	Warn(mskExecMode(AsgnMode), eExecAsgnMode);
							//	exec mode is checked not simul mode.

	tickSimulAsgnClk();
	#if SimulDnwd
	updtSimulFixedClk();
	#endif
	#if SimulDnwdCache
	tickSimulCacheClk();
	#endif
	#if SimulDnwdFlexi
	if (mSimulAsgnVars.flexiCount())
		updtSimulFlexiClk();
	#endif

	mSimulAsgnVars.sweep(mSimulAsgnClk);
	mSimulAsgnVars.tag(hdlVar1);
	mSimulAsgnVars.tag(hdlVar2);

	#if CheckError
	mVarBlk[hdlVar1]->updtSimulAsgnClk();
	mVarBlk[hdlVar2]->updtSimulAsgnClk();
	#endif//CheckError

	mSimulAsgnVars.split();
	CatchError
}
#endif//SimulFixed


#if SimulFixed
/*!
	Set the simul asgn variables in the system.
*/
void Sys::setSimulFixedVars(Hdl const * hdlVars, Dim const VarCount)
{
	WatchError
	Warn(mskExecMode(AsgnMode), eExecAsgnMode);
							//	exec mode is checked not simul mode.
	Warn(!VarCount, eEmptyDimension);

	tickSimulAsgnClk();
	#if SimulDnwd
	updtSimulFixedClk();
	#endif
	#if SimulDnwdCache
	tickSimulCacheClk();
	#endif
	#if SimulDnwdFlexi
	if (mSimulAsgnVars.flexiCount())
		updtSimulFlexiClk();
	#endif

	mSimulAsgnVars.sweep(mSimulAsgnClk);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
	{
		Hdl tVarHdl = hdlVars[tIdx];
		#if CheckError
		for(Idx sIdx = tIdx + 1; sIdx < VarCount; ++sIdx)
			if (hdlVars[sIdx] == tVarHdl)
				Throw(eDuplicateAsgnVars);
		if (mSimulAsgnVars.tagBll(tVarHdl))
			mVarBlk[tVarHdl]->updtSimulAsgnClk();
		#else//CheckError
		mSimulAsgnVars.tag(tVarHdl);
		#endif//CheckError
	}
	mSimulAsgnVars.split();
	CatchError
}
#endif//SimulFixed


#if SimulFlexi
/*!
	Set a simulation flexi variable in the system.
*/
void Sys::setSimulFlexiVar1(Hdl const hdlVar)
{
	WatchError
	Warn(mskExecMode(AsgnMode), eNotExecAsgnMode); 	//	exec mode is checked not simul mode.

	tickSimulAsgnClk();

	#if SimulDnwdFixed
	if (mSimulAsgnVars.fixedCount())
		updtSimulFixedClk();
	#endif
	#if SimulDnwd
	updtSimulFlexiClk();
	#endif
	#if SimulDnwdCache
	tickSimulCacheClk();
	#endif

	mSimulAsgnVars.sweep(mSimulAsgnClk);
	mSimulAsgnVars.split();
	mSimulAsgnVars.tag(hdlVar);
	#if CheckError
	mVarBlk[hdlVar]->updtSimulAsgnClk();
	#endif//CheckError
	CatchError
}
#endif //SimulFlexi



#if SimulFlexi
/*!
	Set a simulation flexi variable in the system.
*/
void Sys::setSimulFlexiVar2(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(mskExecMode(AsgnMode), eNotExecAsgnMode); 	//	exec mode is checked not simul mode.
	Warn(hdlVar1 == hdlVar2, eDuplicateAsgnVars);

	tickSimulAsgnClk();
	#if SimulDnwdFixed
	if (mSimulAsgnVars.fixedCount())
		updtSimulFixedClk();
	#endif
	#if SimulDnwd
	updtSimulFlexiClk();
	#endif
	#if SimulDnwdCache
	tickSimulCacheClk();
	#endif
	mSimulAsgnVars.sweep(mSimulAsgnClk);
	mSimulAsgnVars.split();
	mSimulAsgnVars.tag(hdlVar1);
	mSimulAsgnVars.tag(hdlVar2);
	#if CheckError
	mVarBlk[hdlVar1]->updtSimulAsgnClk();
	mVarBlk[hdlVar2]->updtSimulAsgnClk();
	#endif//CheckError
	CatchError
}
#endif //SimulFlexi



#if SimulFlexi
/*!
	Set a simulation flexi variable in the system.
*/
void Sys::setSimulFlexiVars(Hdl const * hdlVars, Dim const VarCount)
{
	WatchError
	Warn(mskExecMode(AsgnMode), eNotExecAsgnMode); 	//	exec mode is checked not simul mode.

	tickSimulAsgnClk();
	#if SimulDnwdFixed
	if (mSimulAsgnVars.fixedCount())
		updtSimulFixedClk();
	#endif

	#if SimulDnwd
	updtSimulFlexiClk();
	#endif
	#if SimulDnwdCache
	tickSimulCacheClk();
	#endif
	mSimulAsgnVars.sweep(mSimulAsgnClk);
	mSimulAsgnVars.split();
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
	{
		Hdl tVarHdl = hdlVars[tIdx];
		for(Idx sIdx = tIdx + 1; sIdx < VarCount; ++sIdx)
			if (hdlVars[sIdx] == tVarHdl)
				Throw(eDuplicateAsgnVars);

		mSimulAsgnVars.tag(tVarHdl);
		#if CheckError
		mVarBlk[tVarHdl]->updtSimulAsgnClk();
		#endif//CheckError
	}
	CatchError
}
#endif //SimulFlexi


#if SimulFixedFlexi
/*!
	Set a simulation flexi variable in the system.
*/
void Sys::altSimulFlexiVar1(Idx const theIdx, Hdl const hdlVar)
{
	WatchError
	Warn(mskExecMode(AsgnMode), eNotExecAsgnMode); 	//	exec mode is checked not simul mode.
	Warn(!mSimulAsgnVars.splitted(), eFixedVarsNotLocked);
	Warn(mSimulAsgnVars.tagged(hdlVar), eDuplicateAsgnVars);

	if (theIdx < mSimulAsgnVars.tagCount())
	{
		Warn(theIdx < mSimulAsgnVars.flexiVerge(), eFlexiIndexMismatch);
		Warn(theIdx + 1 > mSimulAsgnVars.tagCount(), eFlexiIndexMismatch);

		tickSimulAsgnClk();
		#if SimulDnwd
		updtSimulFlexiClk();
		#endif

		mSimulAsgnVars.doUntagTag(theIdx, hdlVar);
		#if CheckError
		for(Idx tIdx = 0; tIdx < mSimulAsgnVars.tagCount(); ++tIdx)
		{
			Hdl tVarHdl = mSimulAsgnVars[tIdx];
			mVarBlk[tVarHdl]->updtSimulAsgnClk();
		}
		#endif//CheckError
	}
	else
	{
		Warn(theIdx != mSimulAsgnVars.flexiVerge(), eFlexiIndexMismatch);
		#if SimulDnwd
		updtSimulFlexiClk();
		#endif
		mSimulAsgnVars.tag(hdlVar);
		#if CheckError
		mVarBlk[hdlVar]->updtSimulAsgnClk();
		#endif//CheckError
	}
	CatchError
}
#endif //SimulFixedFlexi



#if SimulFixedFlexi
/*!
	Set a simulation flexi variable in the system.
*/
void Sys::altSimulFlexiVar2(Idx const theIdx, Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(mskExecMode(AsgnMode), eNotExecAsgnMode); 	//	exec mode is checked not simul mode.
	Warn(hdlVar1 == hdlVar2, eDuplicateAsgnVars);
	Warn(!mSimulAsgnVars.splitted(), eFixedVarsNotLocked);
	Warn(mSimulAsgnVars.tagged(hdlVar1), eDuplicateAsgnVars);
	Warn(mSimulAsgnVars.tagged(hdlVar2), eDuplicateAsgnVars);

	if (theIdx < mSimulAsgnVars.tagCount())
	{
		Warn(theIdx < mSimulAsgnVars.flexiVerge(), eFlexiIndexMismatch);
		Warn(theIdx + 2 > mSimulAsgnVars.tagCount(), eFlexiIndexMismatch);

		tickSimulAsgnClk();
		#if SimulDnwd
		updtSimulFlexiClk();
		#endif
		mSimulAsgnVars.doUntagTag(theIdx, hdlVar1);
		mSimulAsgnVars.doUntagTag(theIdx + 1, hdlVar2);

		#if CheckError
		for(Idx tIdx = 0; tIdx < mSimulAsgnVars.tagCount(); ++tIdx)
		{
			Hdl tVarHdl = mSimulAsgnVars[tIdx];
			mVarBlk[tVarHdl]->updtSimulAsgnClk();
		}
		#endif//CheckError
	}
	else
	{
		Warn(theIdx != mSimulAsgnVars.flexiVerge(), eFlexiIndexMismatch);
		#if SimulDnwd
		updtSimulFlexiClk();
		#endif
		mSimulAsgnVars.tag(hdlVar1);
		mSimulAsgnVars.tag(hdlVar2);
		#if CheckError
		mVarBlk[hdlVar1]->updtSimulAsgnClk();
		mVarBlk[hdlVar2]->updtSimulAsgnClk();
		#endif//CheckError
	}
	CatchError
}
#endif //SimulFixedFlexi



#if SimulFixedFlexi
/*!
	Set a simulation flexi variable in the system.
*/
void Sys::altSimulFlexiVars(Idx const theIdx, Hdl const * hdlVars, Dim const VarCount)
{
	WatchError
	Warn(mskExecMode(AsgnMode), eNotExecAsgnMode); 	//	exec mode is checked not simul mode.
	Warn(!mSimulAsgnVars.splitted(), eFixedVarsNotLocked);

	if (theIdx < mSimulAsgnVars.tagCount())
	{
		Warn(theIdx < mSimulAsgnVars.flexiVerge(), eFlexiIndexMismatch);
		Warn(theIdx + VarCount > mSimulAsgnVars.tagCount(), eFlexiIndexMismatch);

		tickSimulAsgnClk();
		#if SimulDnwd
		updtSimulFlexiClk();
		#endif
		for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
			mSimulAsgnVars.doUntagTag(theIdx + tIdx, hdlVars[tIdx]);
		#if CheckError
		for(Idx tIdx = 0; tIdx < mSimulAsgnVars.tagCount(); ++tIdx)
		{
			Hdl tVarHdl = mSimulAsgnVars[tIdx];
			mVarBlk[tVarHdl]->updtSimulAsgnClk();
		}
		#endif//CheckError
	}
	else
	{
		Warn(theIdx != mSimulAsgnVars.flexiVerge(), eFlexiIndexMismatch);
		#if SimulDnwd
		updtSimulFlexiClk();
		#endif
		for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		{
			mSimulAsgnVars.tag(hdlVars[tIdx]);
			#if CheckError
			mVarBlk[hdlVars[tIdx]]->updtSimulAsgnClk();
			#endif//CheckError
		}
	}
	CatchError
}
#endif //SimulFixedFlexi



/*!
	Define a selector -- ownership is handed over.
	@return The handle where the selector is aleady found or InvHdl.
*/
Hdl Sys::defSelc(Selc * theSelc)
{
	WatchError
	Warn(!chkExecMode(NullComp), eSysNotUninit);

	Itr tItr = mSelcSet.insertItrIfOldMem(theSelc);
	if (tItr != InvItr)
		return mSelcSet[tItr]->SelcHdl;
	Hdl tSelcHdl = mSelcBlk.insertItrMem(theSelc);
	theSelc->setSelcHdl(tSelcHdl);
	return InvHdl;
	CatchError
}



/*!
	Tick the execution clock in the system.
*/
void Sys::tickExecClk()
{
	WatchError
	if (++mExecClk != InvClk) return;

	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
	{
		Var * tVar = mVarBlk[tHdl];
		if (tVar->updatable()) tVar->syncExecClk();
	}

	for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
	{
		Func * tFunc = mFuncBlk[tHdl];
		if (tFunc->updatable()) tFunc->syncExecClk();
	}

	for(Itr tItr = 0; tItr < mEvalDbs.packCount(); ++tItr)
		mEvalDbs.ptrmDefPack(tItr)->syncExecClk();

	for(Itr tItr = 0; tItr < mHintDbs.packCount(); ++tItr)
		mHintDbs.ptrmDefPack(tItr)->syncExecClk();

	for(Itr tItr = 0; tItr < mTabuDbs.packCount(); ++tItr)
		mTabuDbs.ptrmDefPack(tItr)->syncExecClk();

	mExecClk = MinClk;
	CatchError
}



/*!
	Tick the simulation clock in the system.
*/
void Sys::tickSimulClk()
{
	WatchError
	if (++mSimulClk != InvClk) return;

	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
	{
		Var * tVar = mVarBlk[tHdl];
		if (tVar->updatable()) tVar->syncSimulClk();
	}

	for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
	{
		Func * tFunc = mFuncBlk[tHdl];
		if (tFunc->updatable()) tFunc->syncSimulClk();
	}

	for(Itr tItr = 0; tItr < mEvalDbs.packCount(); ++tItr)
		mEvalDbs.ptrmDefPack(tItr)->syncSimulClk();

	mSimulClk = MinClk;
	CatchError
}



/*!
	Tick the assignment clock in the system.
*/
void Sys::tickExecAsgnClk()
{
	WatchError
	if (++mExecAsgnClk != InvClk) return;
	#if ExecDnwd

	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
	{
		Var * tVar = mVarBlk[tHdl];
		if (tVar->updatable()) tVar->syncExecAsgnClk();
	}

	for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
	{
		Func * tFunc = mFuncBlk[tHdl];
		if (tFunc->updatable()) tFunc->syncExecAsgnClk();
	}

	#endif
	mExecAsgnVars.syncClk();
	mExecAsgnClk = MinClk;
	CatchError
}



/*!
	Tick the assignment clock in the system.
*/
void Sys::tickSimulAsgnClk()
{
	WatchError
	if (++mSimulAsgnClk != InvClk) return;
	#if SimulDnwd
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
	{
		Var * tVar = mVarBlk[tHdl];
		if (tVar->updatable()) tVar->syncExecClk();
	}

	for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
	{
		Func * tFunc = mFuncBlk[tHdl];
		if (tFunc->updatable()) tFunc->syncExecClk();
	}
	#endif//SimulDnwd
	#if SimulDnwdFixed
	mSimulFixedClk = InvClk;
	#endif
	#if SimulDnwdFlexi
	mSimulFlexiClk = InvClk;
	#endif
	mSimulAsgnVars.syncClk();
	mSimulAsgnClk = MinClk;
	CatchError
}


#if SimulDnwdCache
/*!
	Tick the cache clock in the system.
*/
void Sys::tickSimulCacheClk()
{
	WatchError
	if (++mSimulCacheClk != InvClk) return;
	for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
	{
		Func * tFunc = mFuncBlk[tHdl];
		if (tFunc->updatable()) tFunc->syncSimulCacheClk();
	}
	mSimulCacheClk = MinClk;
	CatchError
}
#endif//SimulDnwdCache


#if DnwdSysMapFuncVar
void Sys::setSqn(Hdl const hdlFunc, Hdl const hdlVar, Sqn const theSqn)
{
	WatchError
	#if DnwdMapFuncVar == MfvSysArray2VarFunc
	ccast<b2<Sqn> *>(mMfvArray2VarFunc)->item(hdlVar, hdlFunc) = theSqn;
	#elif DnwdMapFuncVar == MfvSysArray2FuncVar
	ccast<b2<Sqn> *>(mMfvArray2FuncVar)->item(hdlFunc, hdlVar) = theSqn;
	#elif DnwdMapFuncVar == MfvSysArrayVarHashFunc
	ccast<rl<hm<Hdl,Sqn, xmmh>, kmm> *>(mMfvArrayVarHashFunc)->refList(hdlVar).insertMem(hdlFunc, theSqn);
	#elif DnwdMapFuncVar == MfvSysArrayFuncHashVar
	ccast<rl<hm<Hdl,Sqn, xmmh>, kmm> *>(mMfvArrayFuncHashVar)->refList(hdlFunc).insertMem(hdlVar, theSqn);
	#else
		#error Undefined function variable mapping.
	#endif
	CatchError
}
#endif // DnwdSysMapFuncVar


#if DnwdSysMapFuncVar
Sqn const Sys::findSqn(Hdl const hdlFunc, Hdl const hdlVar) const
{
	WatchError
	#if DnwdMapFuncVar == MfvSysArray2VarFunc
	return mMfvArray2VarFunc->item(hdlVar,hdlFunc);
	#elif DnwdMapFuncVar == MfvSysArray2FuncVar
	return mMfvArray2FuncVar->item(hdlFunc,hdlVar);
	#elif DnwdMapFuncVar == MfvSysArrayVarHashFunc
	hm<Hdl,Sqn, xmmh> const & tHash =
				mMfvArrayVarHashFunc->refList(hdlVar);
	Itr tItr = tHash.findItr(hdlFunc);
	if (tItr == InvItr)
		return InvSqn;
	else
		return tHash.item(tItr);
	#elif DnwdMapFuncVar == MfvSysArrayFuncHashVar
	hm<Hdl,Sqn, xmmh> const & tHash =
				mMfvArrayFuncHashVar->refList(hdlFunc);
	Itr tItr = tHash.findItr(hdlVar);
	if (tItr == InvItr)
		return InvSqn;
	else
		return tHash.item(tItr);
	#else
		#error Undefined function variable mapping.
	#endif
	CatchError
}
#endif // DnwdSysMapFuncVar



/*!
	InitialiseSys.
*/
void Sys::setupComputation()
{
	WatchError

	mExecAsgnVars.allocateMem(mVarBlk.itemCount());
	mSimulAsgnVars.allocateMem(mVarBlk.itemCount());
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
		mExecAsgnVars.insert(), mSimulAsgnVars.insert();

	for(Itr tItr = 0; tItr < mTabuDbs.packCount(); ++tItr)
	{
		Tabu & tTabu = mTabuDbs.refmDefPack(tItr);
		tTabu.setupComputation();
	}

	#if DnwdVarMapFunc
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
		mVarBlk[tHdl]->setupComputation();
	#endif

	#if DnwdSysMapFuncVar
		#if DnwdMapFuncVar == MfvSysArray2VarFunc
		mMfvArray2VarFunc = new b2<Sqn>(mVarBlk.itemCount(), mFuncBlk.itemCount());
		for(Hdl tVarHdl = 0; tVarHdl < mVarBlk.itemCount(); ++tVarHdl)
			for(Hdl tFuncHdl = 0; tFuncHdl < mFuncBlk.itemCount(); ++tFuncHdl)
				ccast<b2<Sqn> *>(mMfvArray2VarFunc)->item(tVarHdl, tFuncHdl) = InvSqn;
		#elif DnwdMapFuncVar == MfvSysArray2FuncVar
		mMfvArray2FuncVar = new b2<Sqn>(mFuncBlk.itemCount(), mVarBlk.itemCount());
		for(Hdl tFuncHdl = 0; tFuncHdl < mFuncBlk.itemCount(); ++tFuncHdl)
			for(Hdl tVarHdl = 0; tVarHdl < mVarBlk.itemCount(); ++tVarHdl)
				ccast<b2<Sqn> *>(mMfvArray2FuncVar)->item(tFuncHdl,tVarHdl) = InvSqn;
		#elif DnwdMapFuncVar == MfvSysArrayVarHashFunc
		mMfvArrayVarHashFunc = new rl<hm<Hdl,Sqn, xmmh>, kmm>(mVarBlk.itemCount());
		#elif DnwdMapFuncVar == MfvSysArrayFuncHashVar
		mMfvArrayFuncHashVar = new rl<hm<Hdl,Sqn, xmmh>, kmm>(mFuncBlk.itemCount());
		#else
			#error Undefined function variable mapping.
		#endif
	#endif

	for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
	{
		Func * tFunc = mFuncBlk[tHdl];
		if (tFunc->computable())
			tFunc->setupComputation();
	}

	#if CompLazy
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
		mVarBlk[tHdl]->setupUndoArgs();
	for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
	{
		Func * tFunc = mFuncBlk[tHdl];
		if (tFunc->updatable())
		{
			tFunc->setupUndoArgs();
			tFunc->setupUndoPrms();
		}
	}
	#endif // CompLazy
	#if ExecUpwd
		#if (ScheduleQueue == SchQsIterAllLvls)
			mRckExecFuncs.allocateMem(mMaxFuncLvl + 1);
			for(Idx tIdx = 0; tIdx < mMaxFuncLvl + 1; ++tIdx)
				mRckExecFuncs.insert();
			mBlkExecFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
			{
				mBlkExecFuncs.insert(false);
				Lvl tLvl = mFuncBlk[tHdl]->FuncLvl;
				mRckExecFuncs.list(tLvl).insertMem();
			}
			for(Idx tIdx = 1; tIdx < mMaxFuncLvl + 1; ++tIdx)
				mRckExecFuncs.list(tIdx).clear();
		#elif (ScheduleQueue == SchQsStdHeapLvls)
			mHipExecFuncs.allocateMem(mMaxFuncLvl + 1);
			mRckExecFuncs.allocateMem(mMaxFuncLvl + 1);
			for(Idx tIdx = 0; tIdx < mMaxFuncLvl + 1; ++tIdx)
				mRckExecFuncs.insert();
			mBlkExecFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
			{
				mBlkExecFuncs.insert(false);
				Lvl tLvl = mFuncBlk[tHdl]->FuncLvl;
				mRckExecFuncs.list(tLvl).insertMem();
			}
			for(Idx tIdx = 1; tIdx < mMaxFuncLvl + 1; ++tIdx)
				mRckExecFuncs.list(tIdx).clear();
		#elif (ScheduleQueue == SchQsAltHeapLvls)
			mHipExecFuncs.allocateMem(mMaxFuncLvl + 1);
			mRckExecFuncs.allocateMem(mMaxFuncLvl + 1);
			for(Idx tIdx = 0; tIdx < mMaxFuncLvl + 1; ++tIdx)
			{
				mHipExecFuncs.insert(InvLvl);
				mRckExecFuncs.insert();
			}
			mBlkExecFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
			{
				mBlkExecFuncs.insert(false);
				Lvl tLvl = mFuncBlk[tHdl]->FuncLvl;
				mRckExecFuncs.list(tLvl).insertMem();
			}
			for(Idx tIdx = 1; tIdx < mMaxFuncLvl + 1; ++tIdx)
				mRckExecFuncs.list(tIdx).clear();
		#elif (ScheduleQueue == SchStdHeapLvls)
			mHipExecFuncs.allocateMem(mFuncBlk.itemCount());
			mBlkExecFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
				mBlkExecFuncs.insert(false);
		#elif (ScheduleQueue == SchStdHeapHdls)
			mHipExecFuncs.allocateMem(mFuncBlk.itemCount());
			mBlkExecFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
				mBlkExecFuncs.insert(false);
		#elif (ScheduleQueue == SchAltHeapLvls)
			mHipExecFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
				mHipExecFuncs.insert(InvLvl);
		#elif (ScheduleQueue == SchAltHeapHdls)
			mHipExecFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
				mHipExecFuncs.insert(InvHdl);
		#endif
	#endif

	#if SimulUpwd
		#if (ScheduleQueue == SchQsIterAllLvls)
			mRckSimulFuncs.allocateMem(mMaxFuncLvl + 1);
			for(Idx tIdx = 0; tIdx < mMaxFuncLvl + 1; ++tIdx)
				mRckSimulFuncs.insert();
			mBlkSimulFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
			{
				mBlkSimulFuncs.insert(false);
				Lvl tLvl = mFuncBlk[tHdl]->FuncLvl;
				mRckSimulFuncs.list(tLvl).insertMem();
			}
			for(Idx tIdx = 1; tIdx < mMaxFuncLvl + 1; ++tIdx)
				mRckSimulFuncs.list(tIdx).clear();
		#elif (ScheduleQueue == SchQsStdHeapLvls)
			mHipSimulFuncs.allocateMem(mMaxFuncLvl + 1);
			mRckSimulFuncs.allocateMem(mMaxFuncLvl + 1);
			for(Idx tIdx = 0; tIdx < mMaxFuncLvl + 1; ++tIdx)
				mRckSimulFuncs.insert();
			mBlkSimulFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
			{
				mBlkSimulFuncs.insert(false);
				Lvl tLvl = mFuncBlk[tHdl]->FuncLvl;
				mRckSimulFuncs.list(tLvl).insertMem();
			}
			for(Idx tIdx = 1; tIdx < mMaxFuncLvl + 1; ++tIdx)
				mRckSimulFuncs.list(tIdx).clear();
		#elif (ScheduleQueue == SchQsAltHeapLvls)
			mHipSimulFuncs.allocateMem(mMaxFuncLvl + 1);
			mRckSimulFuncs.allocateMem(mMaxFuncLvl + 1);
			for(Idx tIdx = 0; tIdx < mMaxFuncLvl + 1; ++tIdx)
			{
				mHipSimulFuncs.insert(InvLvl);
				mRckSimulFuncs.insert();
			}
			mBlkSimulFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
			{
				mBlkSimulFuncs.insert(false);
				Lvl tLvl = mFuncBlk[tHdl]->FuncLvl;
				mRckSimulFuncs.list(tLvl).insertMem();
			}
			for(Idx tIdx = 1; tIdx < mMaxFuncLvl + 1; ++tIdx)
				mRckSimulFuncs.list(tIdx).clear();
		#elif (ScheduleQueue == SchStdHeapLvls)
			mHipSimulFuncs.allocateMem(mFuncBlk.itemCount());
			mBlkSimulFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
				mBlkSimulFuncs.insert(false);
		#elif (ScheduleQueue == SchStdHeapHdls)
			mHipSimulFuncs.allocateMem(mFuncBlk.itemCount());
			mBlkSimulFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
				mBlkSimulFuncs.insert(false);
		#elif (ScheduleQueue == SchAltHeapLvls)
			mHipSimulFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
				mHipSimulFuncs.insert(InvLvl);
		#elif (ScheduleQueue == SchAltHeapHdls)
			mHipSimulFuncs.allocateMem(mFuncBlk.itemCount());
			for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
				mHipSimulFuncs.insert(InvHdl);
		#endif
	#endif
	CatchError
}



/*!
	Adjust memory.
*/
void Sys::adjustMemAuto()
{
	WatchError
	mTermSet.adjustMemAuto();
	mConstBlk.adjustMemAuto();
	mVarBlk.adjustMemAuto();
	mDynUpdtVars.adjustMemAuto();
	#if CompLazyHalf
	mReqUpdtVars.adjustMemAuto();
	#endif
	mFuncBlk.adjustMemAuto();
	mRootFuncs.adjustMemAuto();
	#if CompLazyHalf
		mReqFuncs.adjustMemAuto();
	#endif // CompLazyHalf

	#if DnwdSysMapFuncVar
		#if DnwdMapFuncVar == MfvSysArrayVarHashFunc
		ccast<rl<hm<Hdl,Sqn, xmmh>, kmm> *>(mMfvArrayVarHashFunc)->adjustListsMemAuto();
		#elif DnwdMapFuncVar == MfvSysArrayFuncHashVar
		ccast<rl<hm<Hdl,Sqn, xmmh>, kmm> *>(mMfvArrayFuncHashVar)->adjustListsMemAuto();
		#endif
	#endif

	#if ExecUpwd
		#if (ScheduleQueue == SchQsIterAllLvls)
			mBlkExecFuncs.adjustMemAuto();
			mRckExecFuncs.adjustMemAuto();
			mRckExecFuncs.adjustListsMemAuto();
		#elif (ScheduleQueue == SchQsStdHeapLvls)
			mBlkExecFuncs.adjustMemAuto();
			mRckExecFuncs.adjustMemAuto();
			mRckExecFuncs.adjustListsMemAuto();
			mHipExecFuncs.adjustMemAuto();
		#elif (ScheduleQueue == SchQsAltHeapLvls)
			mBlkExecFuncs.adjustMemAuto();
			mRckExecFuncs.adjustMemAuto();
			mRckExecFuncs.adjustListsMemAuto();
			mHipExecFuncs.adjustMemAuto();
		#elif (ScheduleQueue == SchStdHeapLvls)
			mBlkExecFuncs.adjustMemAuto();
			mHipExecFuncs.adjustMemAuto();
		#elif (ScheduleQueue == SchStdHeapHdls)
			mBlkExecFuncs.adjustMemAuto();
			mHipExecFuncs.adjustMemAuto();
		#elif (ScheduleQueue == SchAltHeapLvls)
			mHipExecFuncs.adjustMemAuto();
		#elif (ScheduleQueue == SchAltHeapHdls)
			mHipExecFuncs.adjustMemAuto();
		#else
			#error eUnknownScheduleQueue
		#endif
	#endif
	#if SimulUpwd
		#if (ScheduleQueue == SchQsIterAllLvls)
			mBlkSimulFuncs.adjustMemAuto();
			mRckSimulFuncs.adjustMemAuto();
			mRckSimulFuncs.adjustListsMemAuto();
		#elif (ScheduleQueue == SchQsStdHeapLvls)
			mBlkSimulFuncs.adjustMemAuto();
			mRckSimulFuncs.adjustMemAuto();
			mRckSimulFuncs.adjustListsMemAuto();
			mHipSimulFuncs.adjustMemAuto();
		#elif (ScheduleQueue == SchQsAltHeapLvls)
			mBlkSimulFuncs.adjustMemAuto();
			mRckSimulFuncs.adjustMemAuto();
			mRckSimulFuncs.adjustListsMemAuto();
			mHipSimulFuncs.adjustMemAuto();
		#elif (ScheduleQueue == SchStdHeapLvls)
			mBlkSimulFuncs.adjustMemAuto();
			mHipSimulFuncs.adjustMemAuto();
		#elif (ScheduleQueue == SchStdHeapHdls)
			mBlkSimulFuncs.adjustMemAuto();
			mHipSimulFuncs.adjustMemAuto();
		#elif (ScheduleQueue == SchAltHeapLvls)
			mHipSimulFuncs.adjustMemAuto();
		#elif (ScheduleQueue == SchAltHeapHdls)
			mHipSimulFuncs.adjustMemAuto();
		#else
			#error eUnknownScheduleQueue
		#endif
	#endif

	mExecAsgnVars.adjustMemAuto();
	mSimulAsgnVars.adjustMemAuto();
	mSysLock.adjustMemAuto();

	mSelcBlk.adjustMemAuto();
	mSelcSet.adjustMemAuto();

	for(Hdl tHdl = 0; tHdl < mConstBlk.itemCount(); ++tHdl)
		mConstBlk[tHdl]->adjustMemAuto();

	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
		mVarBlk[tHdl]->adjustMemAuto();

	for(Hdl tHdl = 0; tHdl < mFuncBlk.itemCount(); ++tHdl)
		mFuncBlk[tHdl]->adjustMemAuto();

	for(Itr tItr = 0; tItr < mEvalDbs.packCount(); ++tItr)
		mEvalDbs.ptrmDefPack(tItr)->adjustMemAuto();

	for(Itr tItr = 0; tItr < mHintDbs.packCount(); ++tItr)
		mHintDbs.ptrmDefPack(tItr)->adjustMemAuto();

	for(Itr tItr = 0; tItr < mTabuDbs.packCount(); ++tItr)
		mTabuDbs.ptrmDefPack(tItr)->adjustMemAuto();

	CatchError
}



/*!
	Initialise all variables with values selected randomly from static domains.
*/
void Sys::initialiseVarsStatRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Alert(!chkExecMode(NullComp), eSysNotUninit);

	setupComputation();

	setExecMode(AnewAsgn);
	setExecAsgnVars();
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
		mVarBlk[tHdl]->execAnewStatRand(theRnd);

	setExecMode(AnewProp);
	initPropagation();
	CatchError
}



/*!
	Initialise all variables with values selected randomly from dynamic domains.
*/
void Sys::initialiseVarsDynaRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Alert(!chkExecMode(NullComp), eSysNotUninit);

	setupComputation();

	setExecMode(AnewAsgn);
	setExecAsgnVars();
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
		mVarBlk[tHdl]->execAnewDynaRand(theRnd);

	setExecMode(AnewProp);
	initPropagation();
	CatchError
}



/*!
	Initialise all variables with given values.
*/
void Sys::initialiseVarsWrap(Hdl const * hdlVars, Wrp const * theWraps)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Alert(!chkExecMode(NullComp), eSysNotUninit);

	setupComputation();

	setExecMode(AnewAsgn);
	setExecAsgnVars();

	for(Idx tIdx = 0; tIdx < mVarBlk.itemCount(); ++tIdx)
		mVarBlk[hdlVars[tIdx]]->execAnewWrap(theWraps[tIdx]);

	setExecMode(AnewProp);
	initPropagation();
	CatchError
}



/*!
	Initialise given variables with given values, all other variables randomly using their static domains.
*/
void Sys::initialiseVarsWrapStatRand(Hdl const * hdlVars, Wrp const * theWraps, Dim const VarCount, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Alert(!chkExecMode(NullComp), eSysNotUninit);
	Warn(VarCount > mVarBlk.itemCount(), eMoreVarsThanAvail);

	setupComputation();

	setExecMode(AnewAsgn);
	setExecAsgnVars();

	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[hdlVars[tIdx]]->execAnewWrap(theWraps[tIdx]);
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
	{
		Var * tVar = mVarBlk[tHdl];
		if (tVar->chgdExecClk())
			tVar->execAnewStatRand(theRnd);
	}
	setExecMode(AnewProp);
	initPropagation();
	CatchError
}




/*!
	Initialise given variables with given values, all other variables randomly using their dynamic domains.
*/
void Sys::initialiseVarsWrapDynaRand(Hdl const * hdlVars, Wrp const * theWraps, Dim const VarCount, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Alert(!chkExecMode(NullComp), eSysNotUninit);
	Warn(VarCount > mVarBlk.itemCount(), eMoreVarsThanAvail);

	setupComputation();

	setExecMode(AnewAsgn);
	setExecAsgnVars();

	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[hdlVars[tIdx]]->execAnewWrap(theWraps[tIdx]);
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
	{
		Var * tVar = mVarBlk[tHdl];
		if (tVar->chgdExecClk())
			tVar->execAnewDynaRand(theRnd);
	}
	setExecMode(AnewProp);
	initPropagation();
	CatchError
}




/*!
	Execute anew a random variable with a value randomly from static domain.
*/
void Sys::execAnewRandVar1StatRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	Hdl tHdl = uniform(theRnd, mVarBlk.itemCount());

	#if CheckError
	Idx tIdx = 0;
	while(mVarBlk[tHdl]->locked() && ++tIdx <= mVarBlk.itemCount())
		tHdl = uniform(theRnd, mVarBlk.itemCount());
	if (tIdx > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
	#else
	while(mVarBlk[tHdl]->locked())
		tHdl = uniform(theRnd, mVarBlk.itemCount());
	#endif

	setExecAsgnVar1(tHdl);
	mVarBlk[tHdl]->execAnewStatRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}



/*!
	Execute anew a random variable with a value randomly from static domain.
*/
void Sys::execAnewRandVar1DynaRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	Hdl tHdl = uniform(theRnd, mVarBlk.itemCount());

	#if CheckError
	Idx tIdx = 0;
	while(mVarBlk[tHdl]->locked() && ++tIdx <= mVarBlk.itemCount())
		tHdl = uniform(theRnd, mVarBlk.itemCount());
	if (tIdx > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
	#else
	while(mVarBlk[tHdl]->locked())
		tHdl = uniform(theRnd, mVarBlk.itemCount());
	#endif

	setExecAsgnVar1(tHdl);
	mVarBlk[tHdl]->execAnewDynaRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}



/*!
	Execute anew two random variables with values randomly from their static domains.
*/
void Sys::execAnewRandVar2StatRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	Hdl tVarHdl1, tVarHdl2;
	#if CheckError
	Idx tIdx = 0;
	do
	{
		do tVarHdl1 = uniform(theRnd, mVarBlk.itemCount());
		while (++tIdx <= mVarBlk.itemCount() && mVarBlk[tVarHdl1]->locked());
		do tVarHdl2 = uniform(theRnd, mVarBlk.itemCount());
		while (++tIdx <= mVarBlk.itemCount() && mVarBlk[tVarHdl2]->locked());
	}
	while(tIdx <= mVarBlk.itemCount() || tVarHdl1 == tVarHdl2);
	if (tIdx > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
	#else
	do
	{
		do tVarHdl1 = uniform(theRnd, mVarBlk.itemCount());
		while (mVarBlk[tVarHdl1]->locked());
		do tVarHdl2 = uniform(theRnd, mVarBlk.itemCount());
		while (mVarBlk[tVarHdl2]->locked());
	}
	while(tVarHdl1 == tVarHdl2);
	#endif

	setExecAsgnVar2(tVarHdl1, tVarHdl2);
	mVarBlk[tVarHdl1]->execAnewStatRand(theRnd);
	mVarBlk[tVarHdl2]->execAnewStatRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}



/*!
	Execute anew two random variables with values randomly from their dynamic domains.
*/
void Sys::execAnewRandVar2DynaRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	Hdl tVarHdl1, tVarHdl2;
	#if CheckError
	Idx tIdx = 0;
	do
	{
		do tVarHdl1 = uniform(theRnd, mVarBlk.itemCount());
		while (++tIdx <= mVarBlk.itemCount() && mVarBlk[tVarHdl1]->locked());
		do tVarHdl2 = uniform(theRnd, mVarBlk.itemCount());
		while (++tIdx <= mVarBlk.itemCount() && mVarBlk[tVarHdl2]->locked());
	}
	while(tIdx <= mVarBlk.itemCount() || tVarHdl1 == tVarHdl2);
	if (tIdx > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
	#else
	do
	{
		do tVarHdl1 = uniform(theRnd, mVarBlk.itemCount());
		while (mVarBlk[tVarHdl1]->locked());
		do tVarHdl2 = uniform(theRnd, mVarBlk.itemCount());
		while (mVarBlk[tVarHdl2]->locked());
	}
	while(tVarHdl1 == tVarHdl2);
	#endif

	setExecAsgnVar2(tVarHdl1, tVarHdl2);
	mVarBlk[tVarHdl1]->execAnewDynaRand(theRnd);
	mVarBlk[tVarHdl2]->execAnewDynaRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}




/*!
	Execute anew random variables with values randomly from their static domains.
*/
void Sys::execAnewRandVarsStatRand(Dim const VarCount, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);
	Warn(VarCount > mVarBlk.itemCount(), eMoreVarsThanAvail);

	setExecMode(AnewAsgn);

	Hdl tVarHdls[VarCount];
	hs<Hdl, xmmh> sVarHdls;
	for(Idx tIdx1 = 0; tIdx1 < VarCount; ++tIdx1)
	{
		Hdl tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		#if CheckError
		Idx tIdx2 = 0;
		while(++tIdx2 <= mVarBlk.itemCount() &&
				(mVarBlk[tVarHdl]->locked() || !sVarHdls.insertBllMem(tVarHdl)))
			tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		if (tIdx2 > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
		#else
		while(mVarBlk[tVarHdl]->locked() || !sVarHdls.insertBllMem(tVarHdl))
			tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		#endif
		tVarHdls[tIdx1] = tVarHdl;
	}

	setExecAsgnVars(tVarHdls, VarCount);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[tVarHdls[tIdx]]->execAnewStatRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}



/*!
	Execute anew random variables with values randomly from their dynamic domains.
*/
void Sys::execAnewRandVarsDynaRand(Dim const VarCount, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);
	Warn(VarCount > mVarBlk.itemCount(), eMoreVarsThanAvail);

	setExecMode(AnewAsgn);

	Hdl tVarHdls[VarCount];
	hs<Hdl, xmmh> sVarHdls;
	for(Idx tIdx1 = 0; tIdx1 < VarCount; ++tIdx1)
	{
		Hdl tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		#if CheckError
		Idx tIdx2 = 0;
		while(++tIdx2 <= mVarBlk.itemCount() &&
				(mVarBlk[tVarHdl]->locked() || !sVarHdls.insertBllMem(tVarHdl)))
			tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		if (tIdx2 > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
		#else
		while(mVarBlk[tVarHdl]->locked() || !sVarHdls.insertBllMem(tVarHdl))
			tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		#endif
		tVarHdls[tIdx1] = tVarHdl;
	}

	setExecAsgnVars(tVarHdls, VarCount);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[tVarHdls[tIdx]]->execAnewDynaRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}




/*!
	Execute anew all variables with values selected randomly from static domains.
*/
void Sys::execAnewVarsStatRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);
	setExecAsgnVars();
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
		mVarBlk[tHdl]->execAnewStatRand(theRnd);

	setExecMode(AnewProp);
	propagateExecAnew();
	CatchError
}



/*!
	Execute anew all variables with values selected randomly from dynamic domains.
*/
void Sys::execAnewVarsDynaRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);
	setExecAsgnVars();
	for(Hdl tHdl = 0; tHdl < mVarBlk.itemCount(); ++tHdl)
		mVarBlk[tHdl]->execAnewDynaRand(theRnd);

	setExecMode(AnewProp);
	propagateExecAnew();
	CatchError
}




/*!
	Execute anew a given variable with a value randomly from static domain.
*/
void Sys::execAnewVar1StatRand(Hdl const hdlVar, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	setExecAsgnVar1(hdlVar);
	mVarBlk[hdlVar]->execAnewStatRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}



/*!
	Execute anew a given variable with a value randomly from static domain.
*/
void Sys::execAnewVar1DynaRand(Hdl const hdlVar, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	setExecAsgnVar1(hdlVar);
	mVarBlk[hdlVar]->execAnewDynaRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}



/*!
	Execute anew two given variables with values randomly from their static domains.
*/
void Sys::execAnewVar2StatRand(Hdl const hdlVar1, Hdl const hdlVar2, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	setExecAsgnVar2(hdlVar1, hdlVar2);
	mVarBlk[hdlVar1]->execAnewStatRand(theRnd);
	mVarBlk[hdlVar1]->execAnewStatRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}



/*!
	Execute anew two given variables with values randomly from their static domains.
*/
void Sys::execAnewVar2DynaRand(Hdl const hdlVar1, Hdl const hdlVar2, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	setExecAsgnVar2(hdlVar1, hdlVar2);
	mVarBlk[hdlVar1]->execAnewDynaRand(theRnd);
	mVarBlk[hdlVar2]->execAnewDynaRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}



/*!
	Execute anew given variables with values randomly from their static domains.
*/
void Sys::execAnewVarsStatRand(Hdl const * hdlVars, Dim const VarCount, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	setExecAsgnVars(hdlVars,VarCount);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[hdlVars[tIdx]]->execAnewStatRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}



/*!
	Execute anew given variables with values randomly from their dynamic domains.
*/
void Sys::execAnewVarsDynaRand(Hdl const * hdlVars, Dim const VarCount, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	setExecAsgnVars(hdlVars,VarCount);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[hdlVars[tIdx]]->execAnewDynaRand(theRnd);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}




/*!
	Execute anew a given variable with given value.
*/
void Sys::execAnewVar1Wrap(Hdl const hdlVar, Wrp const & theWrap)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	setExecAsgnVar1(hdlVar);
	mVarBlk[hdlVar]->execAnewWrap(theWrap);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}


/*!
	Execute anew two given variables with given values.
*/
void Sys::execAnewVar2Wrap(Hdl const hdlVar1, Hdl const hdlVar2,
		Wrp const & theWrap1, Wrp const & theWrap2)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);

	setExecAsgnVar2(hdlVar1, hdlVar2);
	mVarBlk[hdlVar1]->execAnewWrap(theWrap1);
	mVarBlk[hdlVar2]->execAnewWrap(theWrap2);

	setExecMode(AnewProp);
	#if !CompLazyFull
	propagateExecAnew();
	#endif
	CatchError
}



/*!
	Execute anew all variables with given values.
*/
void Sys::execAnewVarsWrap(Hdl const * hdlVars, Wrp const * theWraps)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(AnewAsgn);
	setExecAsgnVars();
	for(Idx tIdx = 0; tIdx < mVarBlk.itemCount(); ++tIdx)
		mVarBlk[hdlVars[tIdx]]->execAnewWrap(theWraps[tIdx]);

	setExecMode(AnewProp);
	propagateExecAnew();
	CatchError
}



/*!
	Execute anew only given variables with given wrapped values.
*/
void Sys::execAnewVarsWrap(Hdl const * hdlVars,
					Wrp const * theWraps, Dim const VarCount)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);
	Warn(VarCount > mVarBlk.itemCount(), eMoreVarsThanAvail);

	setExecMode(AnewAsgn);
	setExecAsgnVars(hdlVars, VarCount);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[hdlVars[tIdx]]->execAnewWrap(theWraps[tIdx]);

	setExecMode(AnewProp);
	propagateExecAnew();
	CatchError
}



/*!
	Execute incremental difference of a random variable with a value randomly from static domain.
*/
void Sys::execIncrDiffRandVar1StatRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	Hdl tHdl = uniform(theRnd, mVarBlk.itemCount());

	#if CheckError
	Idx tIdx = 0;
	while(mVarBlk[tHdl]->locked() && ++tIdx <= mVarBlk.itemCount())
		tHdl = uniform(theRnd, mVarBlk.itemCount());
	if (tIdx > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
	#else
	while(mVarBlk[tHdl]->locked())
		tHdl = uniform(theRnd, mVarBlk.itemCount());
	#endif

	setExecAsgnVar1(tHdl);
	mVarBlk[tHdl]->execIncrStatRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental difference of a random variable with a value randomly from static domain.
*/
void Sys::execIncrDiffRandVar1DynaRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	Hdl tHdl = uniform(theRnd, mVarBlk.itemCount());

	#if CheckError
	Idx tIdx = 0;
	while(mVarBlk[tHdl]->locked() && ++tIdx <= mVarBlk.itemCount())
		tHdl = uniform(theRnd, mVarBlk.itemCount());
	if (tIdx > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
	#else
	while(mVarBlk[tHdl]->locked())
		tHdl = uniform(theRnd, mVarBlk.itemCount());
	#endif

	setExecAsgnVar1(tHdl);
	mVarBlk[tHdl]->execIncrDynaRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental difference of two random variables with values randomly from their static domains.
*/
void Sys::execIncrDiffRandVar2StatRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	Hdl tVarHdl1, tVarHdl2;
	#if CheckError
	Idx tIdx = 0;
	do
	{
		do tVarHdl1 = uniform(theRnd, mVarBlk.itemCount());
		while (++tIdx <= mVarBlk.itemCount() && mVarBlk[tVarHdl1]->locked());
		do tVarHdl2 = uniform(theRnd, mVarBlk.itemCount());
		while (++tIdx <= mVarBlk.itemCount() && mVarBlk[tVarHdl2]->locked());
	}
	while(tIdx <= mVarBlk.itemCount() || tVarHdl1 == tVarHdl2);
	if (tIdx > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
	#else
	do
	{
		do tVarHdl1 = uniform(theRnd, mVarBlk.itemCount());
		while (mVarBlk[tVarHdl1]->locked());
		do tVarHdl2 = uniform(theRnd, mVarBlk.itemCount());
		while (mVarBlk[tVarHdl2]->locked());
	}
	while(tVarHdl1 == tVarHdl2);
	#endif

	setExecAsgnVar2(tVarHdl1, tVarHdl2);
	mVarBlk[tVarHdl1]->execIncrStatRand(theRnd);
	mVarBlk[tVarHdl2]->execIncrStatRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental difference of two random variables with values randomly from their dynamic domains.
*/
void Sys::execIncrDiffRandVar2DynaRand(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	Hdl tVarHdl1, tVarHdl2;
	#if CheckError
	Idx tIdx = 0;
	do
	{
		do tVarHdl1 = uniform(theRnd, mVarBlk.itemCount());
		while (++tIdx <= mVarBlk.itemCount() && mVarBlk[tVarHdl1]->locked());
		do tVarHdl2 = uniform(theRnd, mVarBlk.itemCount());
		while (++tIdx <= mVarBlk.itemCount() && mVarBlk[tVarHdl2]->locked());
	}
	while(tIdx <= mVarBlk.itemCount() || tVarHdl1 == tVarHdl2);
	if (tIdx > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
	#else
	do
	{
		do tVarHdl1 = uniform(theRnd, mVarBlk.itemCount());
		while (mVarBlk[tVarHdl1]->locked());
		do tVarHdl2 = uniform(theRnd, mVarBlk.itemCount());
		while (mVarBlk[tVarHdl2]->locked());
	}
	while(tVarHdl1 == tVarHdl2);
	#endif

	setExecAsgnVar2(tVarHdl1, tVarHdl2);
	mVarBlk[tVarHdl1]->execIncrDynaRand(theRnd);
	mVarBlk[tVarHdl2]->execIncrDynaRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}




/*!
	Execute incremental difference of random variables with values randomly from their static domains.
*/
void Sys::execIncrDiffRandVarsStatRand(Dim const VarCount, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);
	Warn(VarCount > mVarBlk.itemCount(), eMoreVarsThanAvail);

	setExecMode(DiffAsgn);

	Hdl tVarHdls[VarCount];
	hs<Hdl, xmmh> sVarHdls;
	for(Idx tIdx1 = 0; tIdx1 < VarCount; ++tIdx1)
	{
		Hdl tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		#if CheckError
		Idx tIdx2 = 0;
		while(++tIdx2 <= mVarBlk.itemCount() &&
				(mVarBlk[tVarHdl]->locked() || !sVarHdls.insertBllMem(tVarHdl)))
			tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		if (tIdx2 > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
		#else
		while(mVarBlk[tVarHdl]->locked() || !sVarHdls.insertBllMem(tVarHdl))
			tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		#endif
		tVarHdls[tIdx1] = tVarHdl;
	}

	setExecAsgnVars(tVarHdls, VarCount);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[tVarHdls[tIdx]]->execIncrStatRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental difference of random variables with values randomly from their dynamic domains.
*/
void Sys::execIncrDiffRandVarsDynaRand(Dim const VarCount, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);
	Warn(VarCount > mVarBlk.itemCount(), eMoreVarsThanAvail);

	setExecMode(DiffAsgn);

	Hdl tVarHdls[VarCount];
	hs<Hdl, xmmh> sVarHdls;
	for(Idx tIdx1 = 0; tIdx1 < VarCount; ++tIdx1)
	{
		Hdl tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		#if CheckError
		Idx tIdx2 = 0;
		while(++tIdx2 <= mVarBlk.itemCount() &&
				(mVarBlk[tVarHdl]->locked() || !sVarHdls.insertBllMem(tVarHdl)))
			tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		if (tIdx2 > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
		#else
		while(mVarBlk[tVarHdl]->locked() || !sVarHdls.insertBllMem(tVarHdl))
			tVarHdl = uniform(theRnd, mVarBlk.itemCount());
		#endif
		tVarHdls[tIdx1] = tVarHdl;
	}

	setExecAsgnVars(tVarHdls, VarCount);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[tVarHdls[tIdx]]->execIncrDynaRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental difference of a given variable with a value randomly from static domain.
*/
void Sys::execIncrDiffVar1StatRand(Hdl const hdlVar, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	setExecAsgnVar1(hdlVar);
	mVarBlk[hdlVar]->execIncrStatRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental difference of a given variable with a value randomly from static domain.
*/
void Sys::execIncrDiffVar1DynaRand(Hdl const hdlVar, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	setExecAsgnVar1(hdlVar);
	mVarBlk[hdlVar]->execIncrDynaRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental difference of two given variables with values randomly from their static domains.
*/
void Sys::execIncrDiffVar2StatRand(Hdl const hdlVar1, Hdl const hdlVar2, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	setExecAsgnVar2(hdlVar1, hdlVar2);
	mVarBlk[hdlVar1]->execIncrStatRand(theRnd);
	mVarBlk[hdlVar1]->execIncrStatRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental difference of two given variables with values randomly from their static domains.
*/
void Sys::execIncrDiffVar2DynaRand(Hdl const hdlVar1, Hdl const hdlVar2, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	setExecAsgnVar2(hdlVar1, hdlVar2);
	mVarBlk[hdlVar1]->execIncrDynaRand(theRnd);
	mVarBlk[hdlVar2]->execIncrDynaRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental difference of given variables with values randomly from their static domains.
*/
void Sys::execIncrDiffVarsStatRand(Hdl const * hdlVars, Dim const VarCount, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	setExecAsgnVars(hdlVars,VarCount);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[hdlVars[tIdx]]->execIncrStatRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental difference of given variables with values randomly from their dynamic domains.
*/
void Sys::execIncrDiffVarsDynaRand(Hdl const * hdlVars, Dim const VarCount, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	setExecAsgnVars(hdlVars,VarCount);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[hdlVars[tIdx]]->execIncrDynaRand(theRnd);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental difference of a given variable with given value.
*/
void Sys::execIncrDiffVar1Wrap(Hdl const hdlVar, Wrp const & theWrap)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	setExecAsgnVar1(hdlVar);
	mVarBlk[hdlVar]->execIncrWrap(theWrap);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}


/*!
	Execute incremental difference of two given variables with given values.
*/
void Sys::execIncrDiffVar2Wrap(Hdl const hdlVar1, Hdl const hdlVar2,
		Wrp const & theWrap1, Wrp const & theWrap2)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	setExecAsgnVar2(hdlVar1, hdlVar2);
	mVarBlk[hdlVar1]->execIncrWrap(theWrap1);
	mVarBlk[hdlVar2]->execIncrWrap(theWrap2);

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}




/*!
	Execute incremental difference of given variables with given values.
*/
void Sys::execIncrDiffVarsWrap(Hdl const * hdlVars, Wrp const * theWraps, Dim const VarCount)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(DiffAsgn);

	setExecAsgnVars(hdlVars, VarCount);
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx){
		mVarBlk[hdlVars[tIdx]]->execIncrWrap(theWraps[tIdx]);
	}

	setExecMode(DiffProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental swap of two random variables.
*/
void Sys::execIncrSwapRandVar2(Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	Hdl tVarHdl1, tVarHdl2;
	#if CheckError
	Idx tIdx = 0;
	do
	{
		do tVarHdl1 = uniform(theRnd, mVarBlk.itemCount());
		while (++tIdx <= mVarBlk.itemCount() && mVarBlk[tVarHdl1]->locked());
		do tVarHdl2 = uniform(theRnd, mVarBlk.itemCount());
		while (++tIdx <= mVarBlk.itemCount() && mVarBlk[tVarHdl2]->locked());
	}
	while(tIdx <= mVarBlk.itemCount() || tVarHdl1 == tVarHdl2 ||
			!mVarBlk[tVarHdl1]->swappable(mVarBlk[tVarHdl2]));
	if (tIdx > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
	#else
	do
	{
		do tVarHdl1 = uniform(theRnd, mVarBlk.itemCount());
		while (mVarBlk[tVarHdl1]->locked());
		do tVarHdl2 = uniform(theRnd, mVarBlk.itemCount());
		while (mVarBlk[tVarHdl2]->locked());
	}
	while(tVarHdl1 == tVarHdl2 ||
			!mVarBlk[tVarHdl1]->swappable(mVarBlk[tVarHdl2]));
	#endif

	setExecMode(SwapAsgn);

	setExecAsgnVar2(tVarHdl1, tVarHdl2);
	mVarBlk[tVarHdl1]->execIncrSwap(mVarBlk[tVarHdl2]);

	setExecMode(SwapProp);
	propagateExecIncr();
	CatchError
}




/*!
	Execute incremental swap of a given variable with a random variable.
*/
void Sys::execIncrSwapRandVar1(Hdl const hdlVar, Rnd & theRnd)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	Hdl tVarHdl = uniform(theRnd, mVarBlk.itemCount());
	#if CheckError
	Idx tIdx = 0;
	while(++tIdx <= mVarBlk.itemCount() && (tVarHdl == hdlVar ||
			!mVarBlk[tVarHdl]->swappable(mVarBlk[hdlVar])));
	if (tIdx > mVarBlk.itemCount()) Throw(eRandVarSelectLoop);
	#else
	while(tVarHdl == hdlVar ||
			!mVarBlk[tVarHdl]->swappable(mVarBlk[hdlVar]));
	#endif

	setExecMode(SwapAsgn);

	setExecAsgnVar2(tVarHdl, hdlVar);
	mVarBlk[tVarHdl]->execIncrSwap(mVarBlk[hdlVar]);

	setExecMode(SwapProp);
	propagateExecIncr();
	CatchError
}



/*!
	Execute incremental swap of two given variables.
*/
void Sys::execIncrSwapVar2(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setExecMode(SwapAsgn);

	setExecAsgnVar2(hdlVar1, hdlVar2);
	mVarBlk[hdlVar1]->execIncrSwap(mVarBlk[hdlVar2]);

	setExecMode(SwapProp);
	propagateExecIncr();
	CatchError
}



/*!
	Simulate anew all variables with given wrappped values.
*/
void Sys::simulAnewVarsWrap(Hdl const * hdlVars, Wrp const * theWraps)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setSimulMode(AnewAsgn);
	#if SimulFixedFlexi
		#if SysSimulFixed
			setSimulFixedVars(hdlVars, mVarBlk.itemCount());
		#else//default or fixed
			setSimulFlexiVars(hdlVars, mVarBlk.itemCount());
		#endif//SysSimulFixed
	#elif SimulFixedOnly
		setSimulFixedVars(hdlVars, mVarBlk.itemCount());
	#elif SimulFlexiOnly
		setSimulFlexiVars(hdlVars, mVarBlk.itemCount());
	#endif

	for(Idx tIdx = 0; tIdx < mVarBlk.itemCount(); ++tIdx)
		mVarBlk[hdlVars[tIdx]]->simulAnewWrap(theWraps[tIdx]);

	setSimulMode(DiffProp);
	#if SimulUpwd
		propagateSimulAnew();
	#endif
	CatchError
}



/*!
	Execute anew only given variables with given wrapped values.
*/
void Sys::simulAnewVarsWrap(Hdl const * hdlVars, Wrp const * theWraps, Dim const VarCount)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);
	Warn(VarCount > mVarBlk.itemCount(), eMoreVarsThanAvail);

	setSimulMode(AnewAsgn);
	#if SimulFixedFlexi
		#if SysSimulFixed
			setSimulFixedVars(hdlVars, VarCount);
		#else//default or fixed
			setSimulFlexiVars(hdlVars, VarCount);
		#endif//SysSimulFixed
	#elif SimulFixedOnly
		setSimulFixedVars(hdlVars, VarCount);
	#elif SimulFlexiOnly
		setSimulFlexiVars(hdlVars, VarCount);
	#endif

	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[hdlVars[tIdx]]->simulAnewWrap(theWraps[tIdx]);

	setSimulMode(DiffProp);
	#if SimulUpwd
		propagateSimulAnew();
	#endif

	CatchError
}



/*!
	Simulate incremental difference of a given variable with given value.
*/
void Sys::simulIncrDiffVar1Wrap(Hdl const hdlVar, Wrp const & theWrap)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setSimulMode(DiffAsgn);
	#if SimulFixedFlexi
		#if SysSimulFixed
			setSimulFixedVar1(hdlVar);
		#else//default or fixed
			setSimulFlexiVar1(hdlVar);
		#endif//SysSimulFixed
	#elif SimulFixedOnly
		setSimulFixedVar1(hdlVar);
	#elif SimulFlexiOnly
		setSimulFlexiVar1(hdlVar);
	#endif
	mVarBlk[hdlVar]->simulIncrWrap(theWrap);

	setSimulMode(DiffProp);
	#if SimulUpwd
		propagateSimulAnew();
	#endif

	CatchError
}


#if SimulFixed
/*!
	Resimulate incremental difference of a given variable with given value.
*/
void Sys::resimulIncrDiffVar1Wrap(Wrp const & theWrap)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);
	Warn(mSimulAsgnVars.fixedCount() != 1, eDimensionMismatch);

	setSimulMode(DiffAsgn);
	mVarBlk[mSimulAsgnVars.serial(0)]->simulIncrWrap(theWrap);

	setSimulMode(DiffProp);
	#if SimulUpwd
		propagateSimulAnew();
	#endif

	CatchError
}
#endif	//SimulFixed


/*!
	Simulate incremental difference of two given variables with given values.
*/
void Sys::simulIncrDiffVar2Wrap(Hdl const hdlVar1, Hdl const hdlVar2,
		Wrp const & theWrap1, Wrp const & theWrap2)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setSimulMode(DiffAsgn);
	#if SimulFixedFlexi
		#if SysSimulFixed
			setSimulFixedVar2(hdlVar1, hdlVar2);
		#else//default or fixed
			setSimulFlexiVar2(hdlVar1, hdlVar2);
		#endif//SysSimulFixed
	#elif SimulFixedOnly
		setSimulFixedVar2(hdlVar1, hdlVar2);
	#elif SimulFlexiOnly
		setSimulFlexiVar2(hdlVar1, hdlVar2);
	#endif

	mVarBlk[hdlVar1]->simulIncrWrap(theWrap1);
	mVarBlk[hdlVar2]->simulIncrWrap(theWrap2);

	setSimulMode(DiffProp);
	#if SimulUpwd
	propagateSimulIncr();
	#endif

	CatchError
}


#if SimulFixed
/*!
	Resimulate incremental difference of two given variables with given values.
*/
void Sys::resimulIncrDiffVar2Wrap(Wrp const & theWrap1, Wrp const & theWrap2)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);
	Warn(mSimulAsgnVars.fixedCount() != 2, eDimensionMismatch);

	setSimulMode(DiffAsgn);

	mVarBlk[mSimulAsgnVars.serial(0)]->simulIncrWrap(theWrap1);
	mVarBlk[mSimulAsgnVars.serial(1)]->simulIncrWrap(theWrap2);

	setSimulMode(DiffProp);
	#if SimulUpwd
	propagateSimulIncr();
	#endif

	CatchError
}
#endif	//SimulFixed



/*!
	Simulate incremental difference of given variables with given values.
*/
void Sys::simulIncrDiffVarsWrap(Hdl const * hdlVars, Wrp const * theWraps, Dim const VarCount)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setSimulMode(DiffAsgn);
	#if SimulFixedFlexi
		#if SysSimulFixed
			setSimulFixedVars(hdlVars, VarCount);
		#else//default or fixed
			setSimulFlexiVars(hdlVars, VarCount);
		#endif//SysSimulFixed
	#elif SimulFixedOnly
		setSimulFixedVars(hdlVars, VarCount);
	#elif SimulFlexiOnly
		setSimulFlexiVars(hdlVars, VarCount);
	#endif

	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		mVarBlk[hdlVars[tIdx]]->simulIncrWrap(theWraps[tIdx]);

	setSimulMode(DiffProp);
	#if SimulUpwd
	propagateSimulIncr();
	#endif

	CatchError
}


#if SimulFixed
/*!
	Resimulate incremental difference of given variables with given values.
*/
void Sys::resimulIncrDiffVarsWrap(Wrp const * theWraps)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setSimulMode(DiffAsgn);
	for(Itr tItr = 0; tItr < mSimulAsgnVars.tagCount(); ++tItr)
		mVarBlk[mSimulAsgnVars.serial(tItr)]->simulIncrWrap(theWraps[tItr]);

	setSimulMode(DiffProp);
	#if SimulUpwd
	propagateSimulIncr();
	#endif

	CatchError
}
#endif //SimulFixed


/*!
	Simulate incremental swap of two given variables.
*/
void Sys::simulIncrSwapVar2(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(!mVarBlk.itemCount(), eNoVariableDefined);
	Warn(chkExecMode(NullComp), eSysUninit);

	setSimulMode(SwapAsgn);
	#if SimulFixedFlexi
		#if SysSimulFixed
			setSimulFixedVar2(hdlVar1, hdlVar2);
		#else//default or fixed
			setSimulFlexiVar2(hdlVar1, hdlVar2);
		#endif//SysSimulFixed
	#elif SimulFixedOnly
		setSimulFixedVar2(hdlVar1, hdlVar2);
	#elif SimulFlexiOnly
		setSimulFlexiVar2(hdlVar1, hdlVar2);
	#endif

	mVarBlk[hdlVar1]->simulIncrSwap(mVarBlk[hdlVar2]);

	setSimulMode(SwapProp);
	#if SimulUpwd
	propagateSimulIncr();
	#endif

	CatchError
}


#if SimulFixedFlexi
/*!
	Simulate incremental split swap with the given variable, which would form pair with the resimul variable.
*/
void Sys::simulIncrSplitSwapVar1(Hdl const hdlVar)
{
	Warn(chkExecMode(NullComp), eSysUninit);
	setSimulFixedVar1(hdlVar);
}
#endif //SimulFixedFlexi


#if SimulFixedFlexi
/*!
	Resimulate incremental split swap with the given variable, which would form pair with the simul variable.
*/
void Sys::resimulIncrSplitSwapVar1(Hdl const hdlVar)
{
	Warn(chkExecMode(NullComp), eSysUninit);
	Warn(mSimulAsgnVars.tagCount() != 1, eDimensionMismatch);
	setSimulMode(SwapAsgn);
	altSimulFlexiVar1(1, hdlVar);

	mVarBlk[mSimulAsgnVars.serial(0)]->simulIncrSwap(mVarBlk[hdlVar]);

	setSimulMode(SwapProp);
	#if SimulUpwd
	propagateSimulIncr();
	#endif
}
#endif //SimulFixedFlexi


closeKangarooSpace
