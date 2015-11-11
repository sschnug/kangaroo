/*!
	@file segfcmt.tcc
	@brief The prototype file for SegFcMt template class.
	@details This is the prototype file for SegFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SegFcMtTccIncluded
#define SegFcMtTccIncluded



#include "cbls/funcs/fcms/fcmt.tcc"


openKangarooSpace



/*!
	@class SegFcMt
	@brief A template class to represent segregate FcM terms.
	@details This template class represents segregate FcM terms.
*/
template <typename fmt>
class SegFcMt : public FcMt<fmt>
{
	protected:

		virtual ~SegFcMt();											//!< Destructor.
		SegFcMt(SegFcMt<fmt> const & that);							//!< Duplicator.
		SegFcMt(Hdl const hdlSys, Dim const PrmCount);				//!< Constructor.
		SegFcMt<fmt> const & operator = (SegFcMt<fmt> const & that);//!< Assigner.

		//! @name Deferments
		//! @{

		#if CompLazy
		virtual void undoEval(Pos const thePos);//!< Perform eval undo for the parameter.

		void reinitEvalUndoPrms();				//!< Call parameters to list for eval undo.
		void reiterEvalUndoPrms();				//!< Call parameters to relist for eval undo.
		#endif	//CompLazy
		#if CompLazyHalf
		virtual void notifyDeferedPrms();		//!< Notify deferment to the parameters.
		virtual void notifyEnforcedPrms();		//!< Notify enforcement to the parameters.
		#endif

		//! @}

		//! @name Computations
		//! @{

		#if ExecUpwdLazy
		void runPostExecAnew();		//!< Run post exection in anew mode.
		void runPostExecIncr();		//!< Run post execuiton in incr mode.
		#endif
		#if SimulUpwd
		void runPostSimulAnew();	//!< Run post simulation in anew mode.
		void runPostSimulIncr();	//!< Run post simulation in incr mode.
		#endif
		#if CompLazy
		void runPostExecBklg();		//!< Run post execution in bklg mode.
		#endif

		//! @}
};



/*!
	The constructor.
*/
template <typename fmt>
inline SegFcMt<fmt>::SegFcMt(Hdl const hdlSys, Dim const PrmCount) :
		FcMt<fmt>(hdlSys, PrmCount)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
template <typename fmt>
inline SegFcMt<fmt>::~SegFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}


#if ExecUpwdLazy
/*!
	Run postexection process in anew mode.
*/
template <typename fmt>
inline void SegFcMt<fmt>::runPostExecAnew()
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
#endif //ExecUpwdLazy


#if ExecUpwdLazy
/*!
	Run post execution process in incr mode.
*/
template <typename fmt>
inline void SegFcMt<fmt>::runPostExecIncr()
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
#endif //ExecUpwdLazy


#if ExecLazy
/*!
	Run post execution process in backlog mode.
*/
template <typename fmt>
inline void SegFcMt<fmt>::runPostExecBklg()
{
	WatchError
	if (this->mMetricRec->PrevDiff(this->mTermSys.ExecClk()))
		this->notifyEvalUndoArgs();
	this->reiterEvalUndoPrms();
	CatchError
}
#endif


#if SimulUpwd
/*!
	Run post simulation process in anew mode.
*/
template <typename fmt>
inline void SegFcMt<fmt>::runPostSimulAnew()
{
	WatchError
	this->clearSimulChgdPrms();
	this->scheduleSimulAnewArgs();
	CatchError
}
#endif //SimulUpwd


#if SimulUpwd
/*!
	Run post simulation process in incr mode.
*/
template <typename fmt>
inline void SegFcMt<fmt>::runPostSimulIncr()
{
	WatchError
	this->clearSimulChgdPrms();
	if (this->mMetricRec->NextDiff(this->mTermSys.SimulClk()))
		this->scheduleSimulIncrArgs();
	CatchError
}
#endif //SimulUpwd


/*!
	The duplicator.
*/
template <typename fmt>
SegFcMt<fmt>::SegFcMt(SegFcMt<fmt> const & that) :
	FcMt<fmt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fmt>
SegFcMt<fmt> const & SegFcMt<fmt>::operator = (SegFcMt<fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



#if CompLazy
/*!
	Unevaluate the effect of the parameter.
*/
template <typename fmt>
void SegFcMt<fmt>::undoEval(Pos const thePos)
{
	WatchError
	Alert(thePos == thePos, eUndefEvalUndo);
	CatchError
}
#endif //CompLazy



#if CompLazyHalf
/*!
	Notify deferment to the parameters.
*/
template <typename fmt>
void SegFcMt<fmt>::notifyDeferedPrms()
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
void SegFcMt<fmt>::notifyEnforcedPrms()
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
void SegFcMt<fmt>::reinitEvalUndoPrms()
{
	WatchError
	//	no anew mode checking because deferment would happen even
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
	Call parameters to relist for eval undo.
*/
template <typename fmt>
void SegFcMt<fmt>::reiterEvalUndoPrms()
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


#endif//SegFcMtTccIncluded
