/*!
	@file lstidxxyfcmt.tcc
	@brief The prototype file for LstIdxXYFcMt template class.
	@details This is the prototype file for LstIdxXYFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef LstIdxXYFcMtTccIncluded
#define LstIdxXYFcMtTccIncluded



#include "cbls/funcs/fcms/muxfcmt.tcc"



openKangarooSpace



/*!
	@class LstIdxXYFcMt
	@brief A class to represent list element expressions.
	@details This class represents list element expressions.
*/
template<typename pxt, typename pyt, typename fmt>
class LstIdxXYFcMt : public MuxFcMt<fmt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys,
									Prm * thePrms, Dim const PrmCount);						//!< Definition.

		static LstIdxXYFcMt<pxt,pyt,fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static LstIdxXYFcMt<pxt,pyt,fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static LstIdxXYFcMt<pxt,pyt,fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static LstIdxXYFcMt<pxt,pyt,fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static LstIdxXYFcMt<pxt,pyt,fmt> const & cast(Term const & theTerm);	//!< Perform casting.
		static LstIdxXYFcMt<pxt,pyt,fmt> const * cast(Term const * theTerm);	//!< Perform casting.
		static LstIdxXYFcMt<pxt,pyt,fmt> & cast(Term & theTerm);				//!< Perform casting.
		static LstIdxXYFcMt<pxt,pyt,fmt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);			//!< Suits casting?
		static Bll suit(Term const * theTerm);			//!< Suits casting?
		static Bll suit(Term & theTerm);				//!< Suits casting?
		static Bll suit(Term * theTerm);				//!< Suits casting?

		//! @}

	protected:

		LstIdxXYFcMt(Fss const theFss, Hdl const hdlSys,
									Prm * thePrms, Dim const PrmCount);				//!< Constructor.
		LstIdxXYFcMt const & operator = (LstIdxXYFcMt<pxt,pyt,fmt> const & that);	//!< Assigner.
		LstIdxXYFcMt(LstIdxXYFcMt<pxt,pyt,fmt> const & that);						//!< Duplicator.
		virtual ~LstIdxXYFcMt();													//!< Destructor.

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
		void runPostExecAnew();				//!< Run post exection in anew mode.
		void runPostExecIncr();				//!< Run post execuiton in incr mode.
		#endif
		#if SimulUpwd
		void runPostSimulAnew();			//!< Run post simulation in anew mode.
		void runPostSimulIncr();			//!< Run post simulation in incr mode.
		#endif
		#if CompLazy
		void runPostExecBklg();				//!< Run post execuiton in bklg mode.
		#endif

		//! @}

		//! @name Computations
		//! @{

		virtual void compConst();			//!< Compute the term.
		virtual void execAnew();			//!< Execute the term.
		virtual void simulAnew();			//!< Simulate the term.
		virtual void execIncr();			//!< Execute the term.
		virtual void simulIncr();			//!< Simulate the term.
		#if CompLazy
		virtual void execBklg();			//!< Execute the term.
		virtual void emulBklg();			//!< Emulate the term.
		#endif

		//! @}

	protected:

		Pos const 			 	 		mCtlPos;	//!< The position of the index.
		EvalRec<pyt> const * 	  		mPyRec;		//!< The control parameter value.
		b1<EvalRec<pxt> const *,kmm>  	mPxRecs;	//!< Parameter value records.
};



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fmt>
inline Bll LstIdxXYFcMt<pxt,pyt,fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< LstIdxXYFcMt<pxt,pyt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fmt>
inline Bll LstIdxXYFcMt<pxt,pyt,fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< LstIdxXYFcMt<pxt,pyt,fmt> >::TermCls;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fmt>
inline Bll LstIdxXYFcMt<pxt,pyt,fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< LstIdxXYFcMt<pxt,pyt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fmt>
inline Bll LstIdxXYFcMt<pxt,pyt,fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< LstIdxXYFcMt<pxt,pyt,fmt> >::TermCls;
	CatchError
}



/*!
	Refer to an element in the sys.
*/
template<typename pxt, typename pyt, typename fmt>
inline LstIdxXYFcMt<pxt,pyt,fmt> const & LstIdxXYFcMt<pxt,pyt,fmt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< LstIdxXYFcMt<pxt,pyt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<LstIdxXYFcMt<pxt,pyt,fmt> const &>(theTerm);
	CatchError
}



/*!
	Point to an element in the sys.
*/
template<typename pxt, typename pyt, typename fmt>
inline LstIdxXYFcMt<pxt,pyt,fmt> const * LstIdxXYFcMt<pxt,pyt,fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< LstIdxXYFcMt<pxt,pyt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<LstIdxXYFcMt<pxt,pyt,fmt> const *>(theTerm);
	CatchError
}



/*!
	Refer to an element in the sys.
*/
template<typename pxt, typename pyt, typename fmt>
inline LstIdxXYFcMt<pxt,pyt,fmt> & LstIdxXYFcMt<pxt,pyt,fmt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< LstIdxXYFcMt<pxt,pyt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<LstIdxXYFcMt<pxt,pyt,fmt> &>(theTerm);
	CatchError
}



/*!
	Point to an element in the sys.
*/
template<typename pxt, typename pyt, typename fmt>
inline LstIdxXYFcMt<pxt,pyt,fmt> * LstIdxXYFcMt<pxt,pyt,fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< LstIdxXYFcMt<pxt,pyt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<LstIdxXYFcMt<pxt,pyt,fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to an element term.
*/
template<typename pxt, typename pyt, typename fmt>
inline LstIdxXYFcMt<pxt,pyt,fmt> & LstIdxXYFcMt<pxt,pyt,fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to an element term.
*/
template<typename pxt, typename pyt, typename fmt>
inline LstIdxXYFcMt<pxt,pyt,fmt> * LstIdxXYFcMt<pxt,pyt,fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an element term.
*/
template<typename pxt, typename pyt, typename fmt>
inline LstIdxXYFcMt<pxt,pyt,fmt> const & LstIdxXYFcMt<pxt,pyt,fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to an element term.
*/
template<typename pxt, typename pyt, typename fmt>
inline LstIdxXYFcMt<pxt,pyt,fmt> const * LstIdxXYFcMt<pxt,pyt,fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template<typename pxt, typename pyt, typename fmt>
inline LstIdxXYFcMt<pxt,pyt,fmt>::~LstIdxXYFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



#if ExecUpwdLazy
/*!
	Run post exection process in anew mode.
*/
template<typename pxt, typename pyt, typename fmt>
inline void LstIdxXYFcMt<pxt,pyt,fmt>::runPostExecAnew()
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
template<typename pxt, typename pyt, typename fmt>
inline void LstIdxXYFcMt<pxt,pyt,fmt>::runPostExecIncr()
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


#if CompLazy
/*!
	Run post execution process in bklg mode.
*/
template<typename pxt, typename pyt, typename fmt>
inline void LstIdxXYFcMt<pxt,pyt,fmt>::runPostExecBklg()
{
	WatchError
	if (this->mMetricRec->PrevDiff(this->mTermSys.ExecClk()))
		this->notifyEvalUndoArgs();
	this->reiterEvalUndoPrms();
	CatchError
}
#endif //CompLazy


#if SimulUpwd
/*!
	Run post simulation process in anew mode.
*/
template<typename pxt, typename pyt, typename fmt>
inline void LstIdxXYFcMt<pxt,pyt,fmt>::runPostSimulAnew()
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
template<typename pxt, typename pyt, typename fmt>
inline void LstIdxXYFcMt<pxt,pyt,fmt>::runPostSimulIncr()
{
	WatchError
	this->clearSimulChgdPrms();
	if (this->mMetricRec->NextDiff(this->mTermSys.SimulClk()))
		this->scheduleSimulIncrArgs();
	CatchError
}
#endif //SimulUpwd




/*!
	Define an ElemVCFcM in the sys.
*/
template<typename pxt, typename pyt, typename fmt>
Hdl LstIdxXYFcMt<pxt,pyt,fmt>::def(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount)
{
	WatchError
	Warn(PrmCount < 3 || PrmCount > MaxDim, eParamCount2(3, MaxDim));

	LstIdxXYFcMt<pxt,pyt,fmt> * tFcM = new LstIdxXYFcMt<pxt,pyt,fmt>(theFss, hdlSys, thePrms, PrmCount);
	Hdl const tHdl = tFcM->defSysFunc();
	if (tHdl != InvHdl) { delete tFcM; return tHdl; }

	EvalTbl<pyt> const & tPytTbl = EvalTbl<pyt>::refc(hdlSys);
	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<fmt> & tFmtTbl = EvalTbl<fmt>::refm(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFcM->mPrmTerms;
	b1<Bts,kmm> const & tPrmSpecs = tFcM->mPrmSpecs;

	for(Pos tPos = 0; tPos < tPrmTerms.iteratorLast(); ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFcM->mPxRecs[tPos] = tPxtTbl.ptrcEvalRec(tPxLoc);
	}
	Loc const tPyLoc = getPyLoc(theFss, tPrmTerms.itemLast(),tPrmSpecs.itemLast());
	tFcM->mPyRec = tPytTbl.ptrcEvalRec(tPyLoc);

	tFmtTbl.setEvalRec(tFcM->mMetricRec, tFcM->mMetricLoc);

	tFcM->performCompConst();
	tFcM->defSysRoot();
	return tFcM->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
template<typename pxt, typename pyt, typename fmt>
LstIdxXYFcMt<pxt,pyt,fmt>::LstIdxXYFcMt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) :
		MuxFcMt<fmt>(hdlSys, PrmCount), mCtlPos(PrmCount - 1), mPxRecs(PrmCount - 1)
{
	WatchError
	this->setTermCls(TermStub< LstIdxXYFcMt<pxt,pyt,fmt> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Ordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template<typename pxt, typename pyt, typename fmt>
LstIdxXYFcMt<pxt,pyt,fmt>::LstIdxXYFcMt(LstIdxXYFcMt<pxt,pyt,fmt> const & that) :
	MuxFcMt<fmt>(that), mCtlPos(that.mCtlPos), mPxRecs(0)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename pxt, typename pyt, typename fmt>
LstIdxXYFcMt<pxt,pyt,fmt> const & LstIdxXYFcMt<pxt,pyt,fmt>::operator = (LstIdxXYFcMt<pxt,pyt,fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



#if CompLazyHalf
/*!
	Notify deferment to the parameters.
*/
template<typename pxt, typename pyt, typename fmt>
void LstIdxXYFcMt<pxt,pyt,fmt>::notifyDeferedPrms()
{
	WatchError
	Term * const tCtrlTerm = this->mPrmTerms[mCtlPos];
	if (tCtrlTerm->computable())	//	not Updatable to exclude vars
		Func::unsetEnforcement(Func::cast(tCtrlTerm));
	this->reinitEvalUndoPrms();
	CatchError
}
#endif	//CompLazyHalf



#if CompLazyHalf
/*!
	Notify enforcement to the parameters.
*/
template<typename pxt, typename pyt, typename fmt>
void LstIdxXYFcMt<pxt,pyt,fmt>::notifyEnforcedPrms()
{
	WatchError
	Term * const tCtrlTerm = this->mPrmTerms[mCtlPos];
	if (tCtrlTerm->computable())	//	not Updatable to exclude vars
		Func::setEnforcement(Func::cast(tCtrlTerm));
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	Call parameters to list for eval undo.
*/
template<typename pxt, typename pyt, typename fmt>
void LstIdxXYFcMt<pxt,pyt,fmt>::reinitEvalUndoPrms()
{
	WatchError
	//	no mode anew mode checking because deferment would happen even
	//	when incr mode and still need this method to run.
	Warn(!this->mEvalUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (this->defered())
	#endif
	{
		Term * const tCtrlTerm = this->mPrmTerms[mCtlPos];
		if (tCtrlTerm->updatable())	//	include vars
			Term::relistEvalUndoArg(tCtrlTerm, this->mPrmLinks[mCtlPos]);

		Pos tMetricPos = mPyRec->CurrData();
		if (tMetricPos >= mCtlPos) tMetricPos = 0;

		Term * const tMetricTerm = this->mPrmTerms[tMetricPos];
		if (tMetricTerm->updatable())	//	include vars
			Term::relistEvalUndoArg(tMetricTerm, this->mPrmLinks[tMetricPos]);
	}
	this->mBacklogPrms.sweep(this->mTermSys.ExecClk());
	this->mEvalUndonePrms->sweep(this->mTermSys.ExecClk());
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	Call parameters to relist for eval undo
*/
template<typename pxt, typename pyt, typename fmt>
void LstIdxXYFcMt<pxt,pyt,fmt>::reiterEvalUndoPrms()
{
	WatchError
	Warn(!this->mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);
	Warn(!this->mEvalUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (this->defered())
	#endif
	{
		Term * const tCtrlTerm = this->mPrmTerms[mCtlPos];
		if (tCtrlTerm->updatable())
			Term::relistEvalUndoArg(tCtrlTerm, this->mPrmLinks[mCtlPos]);

		Pos tMetricPos = mPyRec->CurrData();
		if (tMetricPos >= mCtlPos) tMetricPos = 0;

		Term * const tMetricTerm = this->mPrmTerms[tMetricPos];
		if (tMetricTerm->updatable())
			Term::relistEvalUndoArg(tMetricTerm, this->mPrmLinks[tMetricPos]);
	}
	this->mBacklogPrms.sweep(this->mTermSys.ExecClk());
	this->mEvalUndonePrms->sweep(this->mTermSys.ExecClk());
	CatchError
}
#endif	//CompLazy


/*!
	Compute the term.
*/
template<typename pxt, typename pyt, typename fmt>
void LstIdxXYFcMt<pxt,pyt,fmt>::compConst()
{
	WatchError
	if (this->updatable() && !this->mPrmTerms[mCtlPos]->updatable())
	{
		Pos tMetricPos = mPyRec->CurrData();
		if (tMetricPos >= mCtlPos) tMetricPos = 0;

		if (!this->mPrmTerms[tMetricPos]->updatable())
			this->setUpdatable(false);
	}
	if (!this->updatable())
	{
		Pos tMetricPos = mPyRec->CurrData();
		if (tMetricPos >= mCtlPos) tMetricPos = 0;

		this->mMetricRec->finalise(tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->CurrData()));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename pxt, typename pyt, typename fmt>
void LstIdxXYFcMt<pxt,pyt,fmt>::execAnew()
{
	WatchError
	#if ExecDnwd
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
		Term::performExecAnew(this->mPrmTerms[tPos]);
	#endif

	Pos tMetricPos = mPyRec->CurrData();
	if (tMetricPos >= mCtlPos) tMetricPos = 0;

	this->mMetricRec->initCurr(tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->CurrData()));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fmt>
void LstIdxXYFcMt<pxt,pyt,fmt>::simulAnew()
{
	WatchError
	#if SimulDnwd
	Term::performSimulAnew(this->mPrmTerms[mCtlPos]);
	#endif

	Pos tMetricPos = mPyRec->NextData(this->mTermSys.SimulClk());
	if(tMetricPos >= mCtlPos) tMetricPos = 0;

	#if SimulDnwd
	Term::performSimulAnew(this->mPrmTerms[tMetricPos]);
	#endif

	this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
				tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->NextData(this->mTermSys.SimulClk())));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename pxt, typename pyt, typename fmt>
void LstIdxXYFcMt<pxt,pyt,fmt>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		Bll tNeedRecomp = this->mExecChgdPrms.tagged(mCtlPos) &&
			mPyRec->PrevDiff(this->mTermSys.ExecClk());

		Pos tMetricPos = mPyRec->CurrData();
		if(tMetricPos >= mCtlPos) tMetricPos = 0;

		if (tNeedRecomp || (this->mExecChgdPrms.tagged(tMetricPos) &&
					mPxRecs[tMetricPos]->PrevDiff(this->mTermSys.ExecClk())))
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
						tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->CurrData()));
		this->runPostExecIncr();
	}
	#endif
	#if ExecDnwd
	Bll tNeedRecomp = false;
	if (this->needExecCandComp()) this->markCandParams();
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//CompLazy
		#if !CompLazy
		for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkCandPrms->item(tIdx);
			Term::performExecIncr(this->mPrmTerms[tPos]);
		}
		#endif
		if (this->mLblCandPrms.tagged(mCtlPos))
		{
			#if CompLazy
			Term::performExecIncr(this->mPrmTerms[mCtlPos]);
			#endif
			if (this->mPyRec->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}

		Pos tMetricPos = mPyRec->CurrData();
		if(tMetricPos >= mCtlPos) tMetricPos = 0;

		if (this->mLblCandPrms.tagged(tMetricPos))
		{
			#if CompLazy
			Term::performExecIncr(this->mPrmTerms[tMetricPos]);
			#endif
			if (!tNeedRecomp && mPxRecs[tMetricPos]->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
		#if CompLazy
		else
		{
			Term::performExecBklg(this->mPrmTerms[tMetricPos]);
			if (!tNeedRecomp && mPxRecs[tMetricPos]->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
		#endif

		if (tNeedRecomp)
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
					tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->CurrData()));
	#if CompLazy
	}
	else
	{
		if (this->mLblCandPrms.tagged(mCtlPos))
		{
			Term::performExecIncr(this->mPrmTerms[mCtlPos]);
			if (this->mEvalUndonePrms->tagged(mCtlPos) ||
					mPyRec->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
		else if (this->mBacklogPrms.tagged(mCtlPos))
		{
			Term::performExecBklg(this->mPrmTerms[mCtlPos]);
			if (this->mEvalUndonePrms->tagged(mCtlPos) ||
					mPyRec->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
		Pos tMetricPos = mPyRec->CurrData();
		if (tMetricPos >= mCtlPos) tMetricPos = 0;

		if (this->mLblCandPrms.tagged(tMetricPos))
		{
			Term::performExecIncr(this->mPrmTerms[tMetricPos]);
			if (!tNeedRecomp && (this->mEvalUndonePrms->tagged(tMetricPos) ||
					mPxRecs[tMetricPos]->PrevDiff(this->mTermSys.ExecClk())))
				tNeedRecomp = true;
		}
		else //Param at tMetricPos is assumed to be defered.
		{
			Term::performExecBklg(this->mPrmTerms[tMetricPos]);
			if (!tNeedRecomp && (this->mEvalUndonePrms->tagged(tMetricPos) ||
					mPxRecs[tMetricPos]->PrevDiff(this->mTermSys.ExecClk())))
				tNeedRecomp = true;
		}
		if (tNeedRecomp)
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
					tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->CurrData()));
	}
	this->runPostExecIncr();
	#endif	//CompLazy
	#endif //ExecDnwd
	CatchError
}


#if CompLazy
/*!
	Compute the term in execution mode.
*/
template<typename pxt, typename pyt, typename fmt>
void LstIdxXYFcMt<pxt,pyt,fmt>::execBklg()
{
	WatchError
	Bll tNeedRecomp = false;
	if (this->mBacklogPrms.tagged(mCtlPos))
	{
		Term::performExecBklg(this->mPrmTerms[mCtlPos]);
		if (this->mEvalUndonePrms->tagged(mCtlPos) ||
				mPyRec->PrevDiff(this->mTermSys.ExecClk()))
			tNeedRecomp = true;
	}

	Pos tMetricPos = mPyRec->CurrData();
	if(tMetricPos >= mCtlPos) tMetricPos = 0;

	Term::performExecBklg(this->mPrmTerms[tMetricPos]);
	if (tNeedRecomp || this->mEvalUndonePrms->tagged(tMetricPos) ||
				mPxRecs[tMetricPos]->PrevDiff(this->mTermSys.ExecClk()))
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
				tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->CurrData()));
	this->runPostExecBklg();
	CatchError
}
#endif //CompLazy



/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fmt>
void LstIdxXYFcMt<pxt,pyt,fmt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		Bll tNeedRecomp = this->mSimulChgdPrms.tagged(mCtlPos) &&
				mPyRec->NextDiff(this->mTermSys.SimulClk());

		Pos tMetricPos = mPyRec->NextData(this->mTermSys.SimulClk());
		if(tMetricPos >= mCtlPos) tMetricPos = 0;

		if (tNeedRecomp || (this->mSimulChgdPrms.tagged(tMetricPos) &&
				mPxRecs[tMetricPos]->NextDiff(this->mTermSys.SimulClk())))
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
					tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->NextData(this->mTermSys.SimulClk())));
		this->runPostSimulIncr();
	}
	#endif	//SimulUpwd
	#if SimulDnwd
	Bll tNeedRecomp = false; Pos tMetricPos;
	#if SimulFixed
	if (this->needSimulFixedComp()) this->markFixedParams();
	#endif
	#if SimulFlexi
	if (this->needSimulFlexiComp()) this->markFlexiParams();
	#endif
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//CompLazy
		#if SimulFixedFlexi
		if (this->mLblFixedPrms.tagged(mCtlPos) ||
				this->mLblFlexiPrms->tagged(mCtlPos))
		#endif
		#if SimulFixedOnly
		if (this->mLblFixedPrms.tagged(mCtlPos))
		#endif
		#if SimulFlexiOnly
		if (this->mLblFlexiPrms->tagged(mCtlPos))
		#endif
		{
			Term::performSimulIncr(this->mPrmTerms[mCtlPos]);
			if (mPyRec->NextDiff(this->mTermSys.SimulClk()))
			{
				tNeedRecomp = true;
				tMetricPos = mPyRec->NextData(this->mTermSys.SimulClk());
			}
		}
		if (!tNeedRecomp)
			tMetricPos = mPyRec->NextData(this->mTermSys.SimulClk());

		if(tMetricPos >= mCtlPos) tMetricPos = 0;

		#if SimulFixedFlexi
		if (this->mLblFixedPrms.tagged(tMetricPos) ||
				this->mLblFlexiPrms->tagged(tMetricPos))
		#endif
		#if SimulFixedOnly
		if (this->mLblFixedPrms.tagged(tMetricPos))
		#endif
		#if SimulFlexiOnly
		if (this->mLblFlexiPrms->tagged(tMetricPos))
		#endif
		{
			Term::performSimulIncr(this->mPrmTerms[tMetricPos]);
			if (tNeedRecomp || mPxRecs[tMetricPos]->NextDiff(this->mTermSys.SimulClk()))
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
					tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->NextData(this->mTermSys.SimulClk())));
		}
		#if CompLazy
		else
		{
			Term::performEmulBklg(this->mPrmTerms[tMetricPos]);
			if (tNeedRecomp || mPxRecs[tMetricPos]->LateDiff(this->mTermSys.EmulClk()))
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
						tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->LateData(this->mTermSys.EmulClk())));
		}
		#else
		else
		{
			if (tNeedRecomp)
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
					mPxRecs[tMetricPos]->NextData(this->mTermSys.SimulClk()));
		}
		#endif
	#if CompLazy
	}
	else
	{
		#if SimulFixedFlexi
		if (this->mLblFixedPrms.tagged(mCtlPos) ||
				this->mLblFlexiPrms->tagged(mCtlPos))
		#endif
		#if SimulFixedOnly
		if (this->mLblFixedPrms.tagged(mCtlPos))
		#endif
		#if SimulFlexiOnly
		if (this->mLblFlexiPrms->tagged(mCtlPos))
		#endif
		{
			Term::performSimulIncr(this->mPrmTerms[mCtlPos]);
			if (this->mEvalUndonePrms->tagged(mCtlPos) ||
					mPyRec->NextDiff(this->mTermSys.SimulClk()))
			{
				tNeedRecomp = true;
				tMetricPos = mPyRec->NextData(this->mTermSys.SimulClk());
			}
		}
		else if (this->mBacklogPrms.tagged(mCtlPos))
		{
			Term::performEmulBklg(this->mPrmTerms[mCtlPos]);
			if (this->mEvalUndonePrms->tagged(mCtlPos) ||
					mPyRec->LateDiff(this->mTermSys.EmulClk()))
			{
				tNeedRecomp = true;
				tMetricPos = mPyRec->LateData(this->mTermSys.EmulClk());
			}
		}
		if (!tNeedRecomp)
			tMetricPos= mPyRec->NextData(this->mTermSys.SimulClk());

		if(tMetricPos >= mCtlPos) tMetricPos = 0;

		#if SimulFixedFlexi
		if (this->mLblFixedPrms.tagged(tMetricPos) ||
				this->mLblFlexiPrms->tagged(tMetricPos))
		#endif
		#if SimulFixedOnly
		if (this->mLblFixedPrms.tagged(tMetricPos))
		#endif
		#if SimulFlexiOnly
		if (this->mLblFlexiPrms->tagged(tMetricPos))
		#endif
		{
			Term::performSimulIncr(this->mPrmTerms[tMetricPos]);
			if (tNeedRecomp || this->mEvalUndonePrms->tagged(tMetricPos) ||
					mPxRecs[tMetricPos]->NextDiff(this->mTermSys.SimulClk()))
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
						tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->NextData(this->mTermSys.SimulClk())));
		}
		else //	Param at tMetricPos is assumed to be defered.
		{
			Term::performEmulBklg(this->mPrmTerms[tMetricPos]);
			if (tNeedRecomp || this->mEvalUndonePrms->tagged(tMetricPos) ||
					mPxRecs[tMetricPos]->LateDiff(this->mTermSys.SimulClk()))
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
						tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->LateData(this->mTermSys.EmulClk())));
		}
	}
	#endif	//CompLazy
	#endif 	//SimulDnwd
	CatchError
}


#if CompLazy
/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fmt>
void LstIdxXYFcMt<pxt,pyt,fmt>::emulBklg()
{
	WatchError
	Bll tNeedRecomp = false;
	if (this->mBacklogPrms.tagged(mCtlPos))
	{
		Term::performEmulBklg(this->mPrmTerms[mCtlPos]);
		if (this->mEvalUndonePrms->tagged(mCtlPos) ||
				mPyRec->LateDiff(this->mTermSys.EmulClk()))
			tNeedRecomp = true;
	}

	Pos tMetricPos = mPyRec->LateData(this->mTermSys.EmulClk());
	if(tMetricPos >= mCtlPos) tMetricPos = 0;

	Term::performEmulBklg(this->mPrmTerms[tMetricPos]);
	if (tNeedRecomp || this->mEvalUndonePrms->tagged(tMetricPos) ||
				mPxRecs[tMetricPos]->LateDiff(this->mTermSys.EmulClk()))
		this->mMetricRec->updtLate(this->mTermSys.EmulClk(),
			tc<pxt,fmt>::iof(mPxRecs[tMetricPos]->LateData(this->mTermSys.EmulClk())));
	CatchError
}
#endif //CompLazy



closeKangarooSpace


#endif//ElemYXFcMtTccIncluded
