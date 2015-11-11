/*!
	@file aggfcmt.tcc
	@brief The prototype file for AggFcMt template class.
	@details This is the prototype file for AggFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef AggFcMtTccIncluded
#define AggFcMtTccIncluded



#include "cbls/funcs/fcms/fcmt.tcc"


openKangarooSpace



/*!
	@class AggFcMt
	@brief A template class to represent aggregate fcm terms.
	@details This template class represents aggregate fcm terms.
*/
template <typename fmt>
class AggFcMt : public FcMt<fmt>
{
	protected:

		virtual ~AggFcMt();												//!< Destructor.
		AggFcMt(AggFcMt<fmt> const & that);								//!< Duplicator.
		AggFcMt(Hdl const hdlSys, Dim const PrmCount);					//!< Constructor.
		AggFcMt<fmt> const & operator = (AggFcMt<fmt> const & that);	//!< Assigner.

		//! @name Deferments
		//! @{

		#if CompLazy
		void reinitEvalUndoPrms();			//!< Call parameters to list for eval undo.
		void reiterEvalUndoPrms();			//!< Call parameters to relist for eval undo.
		#endif
		#if CompLazyHalf
		virtual void notifyDeferedPrms();	//!< Notify deferment to the parameters.
		virtual void notifyEnforcedPrms();	//!< Notify enforcement to the parameters.
		#endif

		//! @}

		//! @name Postprocessing
		//! @{

		#if ExecUpwdLazy
		void runPostExecAnew();				//!< Run postprocessing for anew execution
		void runPostExecIncr();				//!< Run postprocessing for incremental execution.
		#endif
		#if SimulUpwd
		void runPostSimulAnew();			//!< Run postprocessing for anew simulation.
		void runPostSimulIncr();			//!< Run postprocessing for incremental simulation.
		#endif
		#if CompLazy
		void runPostExecBklg();				//!< Run postexecution for backlog execution.
		#endif

		//! @}
};



/*!
	The constructor.
*/
template <typename fmt>
inline AggFcMt<fmt>::AggFcMt(Hdl const hdlSys, Dim const PrmCount) :
		FcMt<fmt>(hdlSys, PrmCount)
{
	WatchError
	#if CompLazy
	this->setEvalUndoDefined(true);
	#endif
	CatchError
}



/*!
	The destructor.
*/
template <typename fmt>
inline AggFcMt<fmt>::~AggFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
template <typename fmt>
AggFcMt<fmt>::AggFcMt(AggFcMt<fmt> const & that) : FcMt<fmt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fmt>
AggFcMt<fmt> const & AggFcMt<fmt>::operator = (AggFcMt<fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}


#if ExecUpwdLazy
/*!
	Run post exection process in anew mode.
*/
template <typename fmt>
inline void AggFcMt<fmt>::runPostExecAnew()
{
	WatchError
	#if ExecUpwd
	this->clearExecChgdPrms();
	this->scheduleExecAnewArgs();
	#endif
	#if ExecLazy
	this->clearEvalUndoArgs();
	this->reinitEvalUndoPrms();
	#endif
	CatchError
}
#endif//ExecUpwdLazy

#if ExecUpwdLazy
/*!
	Run post execution process in incr mode.
*/
template <typename fmt>
inline void AggFcMt<fmt>::runPostExecIncr()
{
	WatchError
	#if ExecUpwd
	this->clearExecChgdPrms();
	if (this->mMetricRec->PrevDiff(this->mTermSys.ExecClk()))
		this->scheduleExecIncrArgs();
	#endif
	#if ExecLazy
	if (this->mMetricRec->PrevDiff(this->mTermSys.ExecClk()))
		this->notifyEvalUndoArgs();
	this->reiterEvalUndoPrms();
	#endif
	CatchError
}
#endif//ExecUpwdLazy


#if ExecLazy
/*!
	Run post execution process in incr mode.
*/
template <typename fmt>
inline void AggFcMt<fmt>::runPostExecBklg()
{
	WatchError
	if (this->mMetricRec->PrevDiff(this->mTermSys.ExecClk()))
		this->notifyEvalUndoArgs();
	this->reiterEvalUndoPrms();
	CatchError
}
#endif	//CompLazy


#if SimulUpwd
/*!
	Run post simulation process in anew mode.
*/
template <typename fmt>
inline void AggFcMt<fmt>::runPostSimulAnew()
{
	WatchError
	this->clearSimulChgdPrms();
	this->scheduleSimulAnewArgs();
	CatchError
}
#endif	//SimulUpwd



#if SimulUpwd
/*!
	Run post simulation process in incr mode.
*/
template <typename fmt>
inline void AggFcMt<fmt>::runPostSimulIncr()
{
	WatchError
	this->clearSimulChgdPrms();
	if (this->mMetricRec->NextDiff(this->mTermSys.SimulClk()))
		this->scheduleSimulIncrArgs();
	CatchError
}
#endif	//SimulUpwd



#if CompLazyHalf
/*!
	Notify deferment to the parameters.
*/
template <typename fmt>
void AggFcMt<fmt>::notifyDeferedPrms()
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
template <typename fmt>
void AggFcMt<fmt>::notifyEnforcedPrms()
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
#endif //CompLazy



#if CompLazy
/*!
	Call parameters to list for eval undo.
*/
template <typename fmt>
void AggFcMt<fmt>::reinitEvalUndoPrms()
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
template <typename fmt>
void AggFcMt<fmt>::reiterEvalUndoPrms()
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


closeKangarooSpace


#endif	//AggFcMtTccIncluded
