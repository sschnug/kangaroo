/*!
	@file aggfevt.tcc
	@brief The prototype file for AggFeVt template class.
	@details This is the prototype file for AggFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef AggFeVtTccIncluded
#define AggFeVtTccIncluded



#include "cbls/funcs/fevs/fevt.tcc"


openKangarooSpace



/*!
	@class AggFeVt
	@brief A template class to represent aggregate fev terms.
	@details This template class represents aggregate fev terms.
*/
template <typename fvt>
class AggFeVt : public FeVt<fvt>
{
	protected:

		virtual ~AggFeVt();												//!< Destructor.
		AggFeVt(AggFeVt<fvt> const & that);								//!< Duplicator.
		AggFeVt(Hdl const hdlSys, Dim const PrmCount);					//!< Constructor.
		AggFeVt<fvt> const & operator = (AggFeVt<fvt> const & that);	//!< Assigner.

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
template <typename fvt>
inline AggFeVt<fvt>::AggFeVt(Hdl const hdlSys, Dim const PrmCount) :
		FeVt<fvt>(hdlSys, PrmCount)
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
template <typename fvt>
inline AggFeVt<fvt>::~AggFeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
template <typename fvt>
AggFeVt<fvt>::AggFeVt(AggFeVt<fvt> const & that) : FeVt<fvt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fvt>
AggFeVt<fvt> const & AggFeVt<fvt>::operator = (AggFeVt<fvt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}


#if ExecUpwdLazy
/*!
	Run post exection process in anew mode.
*/
template <typename fvt>
inline void AggFeVt<fvt>::runPostExecAnew()
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
template <typename fvt>
inline void AggFeVt<fvt>::runPostExecIncr()
{
	WatchError
	#if ExecUpwd
	this->clearExecChgdPrms();
	if (this->mValueRec->PrevDiff(this->mTermSys.ExecClk()))
		this->scheduleExecIncrArgs();
	#endif
	#if ExecLazy
	if (this->mValueRec->PrevDiff(this->mTermSys.ExecClk()))
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
template <typename fvt>
inline void AggFeVt<fvt>::runPostExecBklg()
{
	WatchError
	if (this->mValueRec->PrevDiff(this->mTermSys.ExecClk()))
		this->notifyEvalUndoArgs();
	this->reiterEvalUndoPrms();
	CatchError
}
#endif	//CompLazy


#if SimulUpwd
/*!
	Run post simulation process in anew mode.
*/
template <typename fvt>
inline void AggFeVt<fvt>::runPostSimulAnew()
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
template <typename fvt>
inline void AggFeVt<fvt>::runPostSimulIncr()
{
	WatchError
	this->clearSimulChgdPrms();
	if (this->mValueRec->NextDiff(this->mTermSys.SimulClk()))
		this->scheduleSimulIncrArgs();
	CatchError
}
#endif	//SimulUpwd



#if CompLazyHalf
/*!
	Notify deferment to the parameters.
*/
template <typename fvt>
void AggFeVt<fvt>::notifyDeferedPrms()
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
template <typename fvt>
void AggFeVt<fvt>::notifyEnforcedPrms()
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



#if CompLazy
/*!
	Call parameters to list for eval undo.
*/
template <typename fvt>
void AggFeVt<fvt>::reinitEvalUndoPrms()
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
template <typename fvt>
void AggFeVt<fvt>::reiterEvalUndoPrms()
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


#endif	//AggFeVtTccIncluded
