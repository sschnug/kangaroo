/*!
	@file aggefcmhnt.tcc
	@brief The prototype file for AggEFcMHnT template class.
	@details This is the prototype file for AggEFcMHnT template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef AggEFcMHnTTccIncluded
#define AggEFcMHnTTccIncluded



#include "cbls/funcs/fcmhns/fcmhnt.tcc"


openKangarooSpace



/*!
	@class AggEFcMHnT
	@brief A template class to represent eval-only aggregate fcmhnts.
	@details This template class represents eval-only aggregate fcmhnts.
*/
template <typename fmt>
class AggEFcMHnT : public FcMHnT<fmt>
{
	protected:
		AggEFcMHnT(Hdl const hdlSys, Dim const PrmCount);					//!< Constructor.
		AggEFcMHnT(AggEFcMHnT<fmt> const & that);							//!< Duplicator.
		AggEFcMHnT<fmt> const & operator = (AggEFcMHnT<fmt> const & that);	//!< Assigner.
		virtual ~AggEFcMHnT();												//!< Destructor.

		#if CompLazy
		virtual void setupUndoPrms();		//!< Set up params for defered comp.
		void reinitEvalUndoPrms();			//!< Call params to list for eval undo.
		void reiterEvalUndoPrms();			//!< Call params to relist for eval undo.
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
inline AggEFcMHnT<fmt>::AggEFcMHnT(Hdl const hdlSys, Dim const PrmCount) :
		FcMHnT<fmt>(hdlSys, PrmCount)
{
	WatchError
	#if CompLazy
	this->setEvalUndoDefined(true);
	#endif // CompLazy
	CatchError
}



/*!
	The destructor.
*/
template <typename fmt>
inline AggEFcMHnT<fmt>::~AggEFcMHnT()
{
	WatchError
	//	Nothing to be done.
	CatchError
}



#if CompLazy
/*!
	Set up params for undo operation.
*/
template <typename fmt>
inline void AggEFcMHnT<fmt>::setupUndoPrms()
{
	WatchError
	this->setupEvalUndoPrms();
	CatchError
}
#endif //CompLazy


#if ExecUpwdLazy
/*!
	Run post exection process in anew mode.
*/
template <typename fmt>
inline void AggEFcMHnT<fmt>::runPostExecAnew()
{
	WatchError
	#if ExecUpwd
	this->clearExecChgdPrms();
	this->scheduleExecAnewArgs();
	#endif//ExecUpwd

	#if ExecLazy
	this->clearEvalUndoArgs();
	this->reinitEvalUndoPrms();
	#endif//ExecLazy
	CatchError
}
#endif //ExecUpwdLazy


#if ExecUpwdLazy
/*!
	Run post execution process in incr mode.
*/
template <typename fmt>
inline void AggEFcMHnT<fmt>::runPostExecIncr()
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
	this->reiterEvalUndoPrms();
	#endif//ExecLazy
	CatchError
}
#endif //ExecUpwdLazy


#if CompLazy
/*!
	Run post execution process in incr mode.
*/
template <typename fmt>
inline void AggEFcMHnT<fmt>::runPostExecBklg()
{
	WatchError
	if (this->mMetricRec->PrevDiff(this->mTermSys.ExecClk()))
		this->notifyEvalUndoArgs();
	if (this->mHintMinRec->HintDiff(this->mTermSys.ExecClk()))
		this->notifyHintUndoArgs();
	this->reiterEvalUndoPrms();
	CatchError
}
#endif // CompLazy




#if SimulUpwd
/*!
	Run post simulation process in anew mode.
*/
template <typename fmt>
inline void AggEFcMHnT<fmt>::runPostSimulAnew()
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
inline void AggEFcMHnT<fmt>::runPostSimulIncr()
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
AggEFcMHnT<fmt>::AggEFcMHnT(AggEFcMHnT<fmt> const & that) :
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
AggEFcMHnT<fmt> const & AggEFcMHnT<fmt>::operator = (AggEFcMHnT<fmt> const & that)
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
void AggEFcMHnT<fmt>::notifyDeferedPrms()
{
	WatchError
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		Term * const tPrmTerm = this->mPrmTerms[tPos];
		if (tPrmTerm->computable())
		{
			Func * tFunc = Func::cast(tPrmTerm);
			Func::unsetEnforcement(tFunc);
		}
	}
	this->reinitEvalUndoPrms();
	CatchError
}
#endif // CompLazyHalf



#if CompLazyHalf
/*!
	Notify enforcement to the params.
*/
template <typename fmt>
void AggEFcMHnT<fmt>::notifyEnforcedPrms()
{
	WatchError
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		Term * const tPrmTerm = this->mPrmTerms[tPos];
		if (tPrmTerm->computable())
		{
			Func * tFunc = Func::cast(tPrmTerm);
			Func::setEnforcement(tFunc);
		}
	}
	CatchError
}
#endif // CompLazyHalf



#if CompLazy
/*!
	Call params to list for eval undo.
*/
template <typename fmt>
void AggEFcMHnT<fmt>::reinitEvalUndoPrms()
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
#endif // CompLazy



#if CompLazy
/*!
	Call params to relist for eval undo.
*/
template <typename fmt>
void AggEFcMHnT<fmt>::reiterEvalUndoPrms()
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
#endif // CompLazy


closeKangarooSpace


#endif//AggrFcMHnTIncluded
