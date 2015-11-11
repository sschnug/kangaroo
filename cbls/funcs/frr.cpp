/*!
	@file frr.cpp
	@brief The implementation file for the FrR class.
	@details This is the implementation file for the FrR class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see frr.hpp
*/



#include "cbls/funcs/frr.hpp"



openKangarooSpace




/*!
	The duplicator.
*/
FrR::FrR(FrR const & that) : Func(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
FrR const & FrR::operator = (FrR const & that)
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
Lnk FrR::setArg(Arg const & theArg)
{
	WatchError
	Alert(&theArg, eUndefArgs);	//	no args allowed.
	return InvLnk;
	CatchError
}



#if CompLazy
/*!
	Set up undo arguments.
*/
void FrR::setupUndoArgs()
{
	WatchError
	setupEvalUndoArgs();
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	Set up undo parameters.
*/
void FrR::setupUndoPrms()
{
	WatchError
	setupEvalUndoPrms();
	CatchError
}
#endif	//CompLazy


#if CompLazy
/*!
	Perform hint undo operation.
*/
void FrR::undoHint(Pos const thePos)
{
	WatchError
	Throw(eUndefHintUndo);
	CatchError
}
#endif	//CompLazy



/*!
	Recompute the term in simulation anew mode.
*/
void FrR::simulAnew()
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
void FrR::simulIncr()
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
void FrR::emulBklg()
{
	WatchError
	Throw(eUndefEmulBklg);
	CatchError
}
#endif //CompLazy


#if CompLazy
/*!
	Call parameters to list for eval undo.
*/
void FrR::reinitEvalUndoPrms()
{
	WatchError
	//	no mode anew mode checking because deferment would happen even
	//	when incr mode and still need this method to run.
	Warn(!this->mEvalUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (this->defered())
	#endif
	{
		for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
		{
			Term * const tPrmTerm = this->mPrmTerms[tPos];
			if (tPrmTerm->updatable())
				Term::relistEvalUndoArg(tPrmTerm, this->mPrmLinks[tPos]);
		}
		this->mBacklogPrms.sweep(this->mTermSys.ExecClk());
		this->mEvalUndonePrms->sweep(this->mTermSys.ExecClk());
	}
	CatchError
}
#endif //CompLazy



#if CompLazy
/*!
	Call parameters to relist for unreck.
*/
void FrR::reiterEvalUndoPrms()
{
	WatchError
	Warn(!this->mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);
	Warn(!this->mEvalUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (this->defered())
	#endif
	{
		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			Term * const tPrmTerm = this->mPrmTerms[tPos];
			Term::relistEvalUndoArg(tPrmTerm, this->mPrmLinks[tPos]);
		}
		this->mBacklogPrms.sweep(this->mTermSys.ExecClk());
		this->mEvalUndonePrms->sweep(this->mTermSys.ExecClk());
	}
	CatchError
}
#endif //CompLazy



#if CompLazyHalf
/*!
	Notify deferment to the parameters.
*/
void FrR::notifyDeferedPrms()
{
	WatchError
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		Term * const tPrmTerm = this->mPrmTerms[tPos];
		if (tPrmTerm->computable())
			Func::unsetEnforcement(Func::cast(tPrmTerm));
	}
	this->reinitEvalUndoPrms();
	CatchError
}
#endif //CompLazyHalf



#if CompLazyHalf
/*!
	Notify enforcement to the parameters.
*/
void FrR::notifyEnforcedPrms()
{
	WatchError
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		Term * const tPrmTerm = this->mPrmTerms[tPos];
		if (tPrmTerm->computable())
			Func::setEnforcement(Func::cast(tPrmTerm));
	}
	CatchError
}
#endif //CompLazyHalf




closeKangarooSpace
