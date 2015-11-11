/*!
	@file frh.cpp
	@brief The implementation file for the FrH class.
	@details This is the implementation file for the FrH class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see frh.hpp
*/



#include "cbls/funcs/frh.hpp"



openKangarooSpace




/*!
	The duplicator.
*/
FrH::FrH(FrH const & that) : Func(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
FrH const & FrH::operator = (FrH const & that)
{
	WatchError
	if (this == &that)
		return *this;

	Throw(eUndefAssigner);
	CatchError
}



/*!
	Set the given argument in the term.
*/
Lnk FrH::setArg(Arg const & theArg)
{
	WatchError
	Alert(&theArg, eUndefArgs);	//	no args allowed.
	return InvLnk;
	CatchError
}



#if CompLazy
/*!
	Set up hint parameters.
*/
void FrH::setupHintUndoPrms()
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	if (!mHintUndonePrms)
	{
		mHintUndonePrms = new rl< ll<Sqn,kmm>, nmm>(this->mPrmTerms.itemCount());
		for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
		{
			Dim tVarCount = this->PrmVars[tPos].itemCount();
			mHintUndonePrms->insert(tVarCount);
		}
	}
	CatchError
}
#endif //CompLazy



#if CompLazy
/*!
	Set up params for defered computation.
*/
void FrH::setupUndoPrms()
{
	WatchError
	setupHintUndoPrms();
	CatchError
}
#endif	//CompLazy




#if CompLazy
/*!
	Set up defered args.
*/
void FrH::setupUndoArgs()
{
	WatchError
	//	nothing to be done.
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	Perform uneval operation.
*/
void FrH::undoEval(Pos const thePos)
{
	WatchError
	Throw(eUndefEvalUndo);
	CatchError
}
#endif	//CompLazy


/*!
	Recompute the term in simulation anew mode.
*/
void FrH::simulAnew()
{
	WatchError
	#if SimulUpwd
	this->clearSimulChgdPrms();
	#endif
	CatchError
}



/*!
	Recompute the term in simulation incr mode.
*/
void FrH::simulIncr()
{
	WatchError
	#if SimulUpwd
	this->clearSimulChgdPrms();
	#endif
	CatchError
}


#if CompLazy
/*!
	Recompute the term in simulation diff mode.
*/
void FrH::emulBklg()
{
	WatchError
	Throw(eUndefEmulBklg);
	CatchError
}
#endif //CompLazy



#if CompLazyHalf
/*!
	Notify deferment to the parameters.
*/
void FrH::notifyDeferedPrms()
{
	WatchError
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		Term * const tPrmTerm = this->mPrmTerms[tPos];
		if (tPrmTerm->computable())
		{
			Func * const tFunc = Func::cast(tPrmTerm);
			unsetEnforcement(tFunc);
			Term::enlistHintUndoArg(tFunc, this->mPrmLinks[tPos]);
		}
	}
	this->reinitHintUndoPrms();
	CatchError
}
#endif //CompLazyHalf



#if CompLazyHalf
/*!
	Notify enforcement to the parameters.
*/
void FrH::notifyEnforcedPrms()
{
	WatchError
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		Term * const tPrmTerm = this->mPrmTerms[tPos];
		if (tPrmTerm->computable())
		{
			Func * const tFunc = Func::cast(tPrmTerm);
			setEnforcement(tFunc);
			Term::delistHintUndoArg(tFunc, this->mPrmLinks[tPos]);
		}
	}
	CatchError
}
#endif //CompLazyHalf



#if CompLazy
/*!
	Call parameters to list for uneval.
*/
void FrH::reinitHintUndoPrms()
{
	WatchError
	//	no mode anew mode checking because deferment would happen even
	//	when incr mode and still need this method to run.
	Warn(!mHintUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (defered())
	#endif
	{
		for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
		{
			this->mHintUndonePrms->list(tPos).sweep(this->mTermSys.ExecClk());
			Term::enlistHintUndoArg(this->mPrmTerms[tPos], this->mPrmLinks[tPos]);
		}
		mBacklogPrms.sweep(this->mTermSys.ExecClk());
	}
	CatchError
}
#endif //CompLazy


#if CompLazy
/*!
	Call parameters to relist for uneval.
*/
void FrH::reiterHintUndoPrms()
{
	WatchError
	Warn(!mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);
	Warn(!mHintUndonePrms, eNullPointer);
	#if CompLazyHalf
	if (this->defered())
	#endif
	{
		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			this->mHintUndonePrms->list(tPos).sweep(this->mTermSys.ExecClk());
		}
		mBacklogPrms.sweep(this->mTermSys.ExecClk());
	}
	CatchError
}
#endif //CompLazy


closeKangarooSpace
