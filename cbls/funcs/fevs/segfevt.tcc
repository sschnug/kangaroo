/*!
	@file segfevt.tcc
	@brief The prototype file for SegFeVt template class.
	@details This is the prototype file for SegFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SegFeVtTccIncluded
#define SegFeVtTccIncluded



#include "cbls/funcs/fevs/fevt.tcc"


openKangarooSpace



/*!
	@class SegFeVt
	@brief A template class to represent segregate FeV terms.
	@details This template class represents segregate FeV terms.
*/
template <typename fvt>
class SegFeVt : public FeVt<fvt>
{
	protected:

		virtual ~SegFeVt();											//!< Destructor.
		SegFeVt(SegFeVt<fvt> const & that);							//!< Duplicator.
		SegFeVt(Hdl const hdlSys, Dim const PrmCount);				//!< Constructor.
		SegFeVt<fvt> const & operator = (SegFeVt<fvt> const & that);//!< Assigner.

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
template <typename fvt>
inline SegFeVt<fvt>::SegFeVt(Hdl const hdlSys, Dim const PrmCount) :
		FeVt<fvt>(hdlSys, PrmCount)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
template <typename fvt>
inline SegFeVt<fvt>::~SegFeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}


#if ExecUpwdLazy
/*!
	Run postexection process in anew mode.
*/
template <typename fvt>
inline void SegFeVt<fvt>::runPostExecAnew()
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
template <typename fvt>
inline void SegFeVt<fvt>::runPostExecIncr()
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
#endif //ExecUpwdLazy


#if ExecLazy
/*!
	Run post execution process in backlog mode.
*/
template <typename fvt>
inline void SegFeVt<fvt>::runPostExecBklg()
{
	WatchError
	if (this->mValueRec->PrevDiff(this->mTermSys.ExecClk()))
		this->notifyEvalUndoArgs();
	this->reiterEvalUndoPrms();
	CatchError
}
#endif


#if SimulUpwd
/*!
	Run post simulation process in anew mode.
*/
template <typename fvt>
inline void SegFeVt<fvt>::runPostSimulAnew()
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
template <typename fvt>
inline void SegFeVt<fvt>::runPostSimulIncr()
{
	WatchError
	this->clearSimulChgdPrms();
	if (this->mValueRec->NextDiff(this->mTermSys.SimulClk()))
		this->scheduleSimulIncrArgs();
	CatchError
}
#endif //SimulUpwd


/*!
	The duplicator.
*/
template <typename fvt>
SegFeVt<fvt>::SegFeVt(SegFeVt<fvt> const & that) :
	FeVt<fvt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fvt>
SegFeVt<fvt> const & SegFeVt<fvt>::operator = (SegFeVt<fvt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



#if CompLazy
/*!
	Unevaluate the effect of the parameter.
*/
template <typename fvt>
void SegFeVt<fvt>::undoEval(Pos const thePos)
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
template <typename fvt>
void SegFeVt<fvt>::notifyDeferedPrms()
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
void SegFeVt<fvt>::notifyEnforcedPrms()
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
void SegFeVt<fvt>::reinitEvalUndoPrms()
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
template <typename fvt>
void SegFeVt<fvt>::reiterEvalUndoPrms()
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


#endif//SegVFeVtTccIncluded
