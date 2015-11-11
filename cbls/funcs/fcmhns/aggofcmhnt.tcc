/*!
	@file aggofcmhnt.tcc
	@brief The prototype file for AggOFcMHnT template class.
	@details This is the prototype file for AggOFcMHnT template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef AggOFcMHnTTccIncluded
#define AggOFcMHnTTccIncluded



#include "cbls/funcs/fcmhns/fcmhnt.tcc"


openKangarooSpace



/*!
	@class AggOFcMHnT
	@brief A template class to represent fcmhnts that deals with an optimisation segment.
	@details This template class represents fcmhnts that deals with an optimisation segment.
*/
template <typename fmt>
class AggOFcMHnT : public FcMHnT<fmt>
{
	protected:
		AggOFcMHnT(Hdl const hdlSys, Dim const PrmCount);					//!< Constructor.
		AggOFcMHnT(AggOFcMHnT<fmt> const & that);							//!< Duplicator.
		AggOFcMHnT<fmt> const & operator = (AggOFcMHnT<fmt> const & that);	//!< Assigner.
		virtual ~AggOFcMHnT();												//!< Destructor.

		void syncExecClk();	//!< Synchronise exec clock.

		b1<Bll,kmm> mHintNotEvals;					//!< Whether optimisation segment is a hint or an eval.

		#if CompLazy
		rl< ll<Sqn,kmm>, nmm> * mHintUndonePrms;	//!< The hint undone params; allocated by derivatives.

		void setupHintUndoPrms();			//!< Set up hint undo parameters.
		virtual void setupUndoPrms();		//!< Set up params for defered comp.
		void reinitUndoPrms();				//!< Call params to list for undo.
		void reiterUndoPrms();				//!< Call params to relist for undo.
		#endif // CompLazy
		#if CompLazyHalf
		virtual void notifyDeferedPrms();	//!< Notify deferment to the params.
		virtual void notifyEnforcedPrms();	//!< Notify enforcement to the params.
		#endif
		#if ExecUpwdLazy
		void runPostExecAnew();				//!< Run post execution in anew mode.
		void runPostExecIncr();				//!< Run post execution in incr mode.
		#endif
		#if SimulUpwd
		void runPostSimulAnew();			//!< Run post simulation in anew mode.
		void runPostSimulIncr();			//!< Run post simulation in incr mode.
		#endif
		#if CompLazy
		void runPostExecBklg();				//!< Run post execution in bklg mode.
		#endif // CompLazy
};



/*!
	The constructor.
*/
template <typename fmt>
inline AggOFcMHnT<fmt>::AggOFcMHnT(Hdl const hdlSys, Dim const PrmCount) :
		FcMHnT<fmt>(hdlSys, PrmCount), mHintNotEvals(PrmCount)
		#if CompLazy
		, mHintUndonePrms(Null)
		#endif
{
	WatchError
	#if CompLazy
	this->setEvalUndoDefined(true);
	this->setHintUndoDefined(true);
	#endif // CompLazy
	CatchError
}



/*!
	The destructor.
*/
template <typename fmt>
inline AggOFcMHnT<fmt>::~AggOFcMHnT()
{
	WatchError
	#if CompLazy
	if (mHintUndonePrms)
		delete mHintUndonePrms;
	#endif // CompLazy
	CatchError
}



#if CompLazy
/*!
	Set up unhinted params.
*/
template <typename fmt>
void AggOFcMHnT<fmt>::setupHintUndoPrms()
{
	WatchError
	Warn(!this->mTermSys.chkExecMode(NullComp), eSysNotUninit);

	if (!mHintUndonePrms)
	{
		mHintUndonePrms = new rl< ll<Sqn,kmm>,nmm >(this->mPrmTerms.itemCount());
		for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
		{
			if (EvalAsOpt(this->FuncFss, this->mPrmSpecs[tPos]))	// no var unhint tracing is required.
				mHintUndonePrms->insert(0);
			else
			{
				Dim tVarCount = this->PrmVars[tPos].itemCount();
				mHintUndonePrms->insert(tVarCount);
			}
		}
	}
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Set up params for defered computation.
*/
template <typename fmt>
inline void AggOFcMHnT<fmt>::setupUndoPrms()
{
	WatchError
	this->setupEvalUndoPrms();
	this->setupHintUndoPrms();
	CatchError
}
#endif //CompLazy


#if ExecUpwdLazy
/*!
	Run post exection process in anew mode.
*/
template <typename fmt>
inline void AggOFcMHnT<fmt>::runPostExecAnew()
{
	WatchError
	#if ExecUpwd
	this->clearExecChgdPrms();
	this->scheduleExecAnewArgs();
	#endif//ExecUpwd

	#if ExecLazy
	this->clearEvalUndoArgs();
	this->reinitUndoPrms();
	#endif//ExecLazy
	CatchError
}
#endif //ExecUpwdLazy


#if ExecUpwdLazy
/*!
	Run post execution process in incr mode.
*/
template <typename fmt>
inline void AggOFcMHnT<fmt>::runPostExecIncr()
{
	WatchError
	#if ExecUpwd
	this->clearExecChgdPrms();
	if (this->mMetricRec->PrevDiff(this->mTermSys.ExecClk()) ||
			this->mHintMinRec->HintDiff(this->mTermSys.ExecClk()))
		this->scheduleExecIncrArgs();
	#endif//ExecUpwd

	#if ExecLazy
	if (this->mMetricRec->PrevDiff(this->mTermSys.ExecClk()))
		this->notifyEvalUndoArgs();
	if (this->mHintMinRec->HintDiff(this->mTermSys.ExecClk()))
		this->notifyHintUndoArgs();
	this->reiterUndoPrms();
	#endif//ExecLazy
	CatchError
}
#endif //ExecUpwdLazy


#if CompLazy
/*!
	Run post execution process in incr mode.
*/
template <typename fmt>
inline void AggOFcMHnT<fmt>::runPostExecBklg()
{
	WatchError
	if (this->mMetricRec->PrevDiff(this->mTermSys.ExecClk()))
		this->notifyEvalUndoArgs();
	if (this->mHintMinRec->HintDiff(this->mTermSys.ExecClk()))
		this->notifyHintUndoArgs();
	this->reiterUndoPrms();
	CatchError
}
#endif // CompLazy




#if SimulUpwd
/*!
	Run post simulation process in anew mode.
*/
template <typename fmt>
inline void AggOFcMHnT<fmt>::runPostSimulAnew()
{
	WatchError
	this->clearSimulChgdPrms();
	this->scheduleSimulAnewArgs();
	CatchError
}
#endif//SimulUpwd



#if SimulUpwd
/*!
	Run post simulation process in incr mode.
*/
template <typename fmt>
inline void AggOFcMHnT<fmt>::runPostSimulIncr()
{
	WatchError
	this->clearSimulChgdPrms();
	if (this->mMetricRec->NextDiff(this->mTermSys.SimulClk()))
		this->scheduleSimulIncrArgs();
	CatchError
}
#endif//SimulUpwd


/*!
	The duplicator.
*/
template <typename fmt>
AggOFcMHnT<fmt>::AggOFcMHnT(AggOFcMHnT<fmt> const & that) :
	FcMHnT<fmt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fmt>
AggOFcMHnT<fmt> const & AggOFcMHnT<fmt>::operator = (AggOFcMHnT<fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}


#if CompLazyHalf
/*!
	Notify deferment to the params.
*/
template <typename fmt>
void AggOFcMHnT<fmt>::notifyDeferedPrms()
{
	WatchError
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		Term * const tPrmTerm = this->mPrmTerms[tPos];
		if (tPrmTerm->computable())
		{
			Func * tFunc = Func::cast(tPrmTerm);
			Func::unsetEnforcement(tFunc);
			if (mHintUndonePrms->list(tPos).serialCount())
				Term::enlistHintUndoArg(tFunc, this->mPrmLinks[tPos]);
		}
	}
	this->reinitUndoPrms();
	CatchError
}
#endif // CompLazyHalf



#if CompLazyHalf
/*!
	Notify enforcement to the params.
*/
template <typename fmt>
void AggOFcMHnT<fmt>::notifyEnforcedPrms()
{
	WatchError
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		Term * const tPrmTerm = this->mPrmTerms[tPos];
		if (tPrmTerm->computable())
		{
			Func * tFunc = Func::cast(tPrmTerm);
			Func::setEnforcement(tFunc);
			if (mHintUndonePrms->list(tPos).serialCount())
				Term::delistHintUndoArg(tFunc, this->mPrmLinks[tPos]);
		}
	}
	CatchError
}
#endif // CompLazyHalf



#if CompLazy
/*!
	Call params to list for undo.
*/
template <typename fmt>
void AggOFcMHnT<fmt>::reinitUndoPrms()
{
	WatchError
	//	no mode anew mode checking because deferment would happen even
	//	when incr mode and still need this method to run.
	Warn(!this->mEvalUndonePrms, eNullPointer);
	Warn(!this->mHintUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (this->defered())
	#endif
	{
		for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
		{
			Term * const tPrmTerm = this->mPrmTerms[tPos];
			if (tPrmTerm->updatable())
			{
				Term::relistEvalUndoArg(tPrmTerm, this->mPrmLinks[tPos]);
				ll<Pos,kmm> & tUnhintedPrms = this->mHintUndonePrms->list(tPos);
				if (tUnhintedPrms.serialCount())
					tUnhintedPrms.sweep(this->mTermSys.ExecClk());
				if (mHintNotEvals[tPos])
					Term::enlistHintUndoArg(tPrmTerm, this->mPrmLinks[tPos]);
			}
		}
		this->mBacklogPrms.sweep(this->mTermSys.ExecClk());
		this->mEvalUndonePrms->sweep(this->mTermSys.ExecClk());
	}
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Call params to relist for undo.
*/
template <typename fmt>
void AggOFcMHnT<fmt>::reiterUndoPrms()
{
	WatchError
	Warn(!this->mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);
	Warn(!this->mEvalUndonePrms, eNullPointer);
	Warn(!this->mHintUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (this->defered())
	#endif
	{
		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			Term * const tPrmTerm = this->mPrmTerms[tPos];
			Term::relistEvalUndoArg(tPrmTerm, this->mPrmLinks[tPos]);
			this->mHintUndonePrms->list(tPos).sweep(this->mTermSys.ExecClk());
		}
		this->mBacklogPrms.sweep(this->mTermSys.ExecClk());
		this->mEvalUndonePrms->sweep(this->mTermSys.ExecClk());
	}
	CatchError
}
#endif // CompLazy


/*!
	Synchronize with assign clock of the sys.
*/
template <typename fmt>
inline void AggOFcMHnT<fmt>::syncExecClk()
{
	WatchError
	#if CompLazy
	if (mHintUndonePrms) mHintUndonePrms->syncListsClock();
	#endif // CompLazy

	FcMHnT<fmt>::syncExecClk();
	CatchError
}



closeKangarooSpace


#endif//AggrFcMHnTIncluded
