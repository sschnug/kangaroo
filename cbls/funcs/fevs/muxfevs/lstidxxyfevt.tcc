/*!
	@file lstidxxyfevt.tcc
	@brief The prototype file for LstIdxXYFeVt template class.
	@details This is the prototype file for LstIdxXYFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef LstIdxXYFeVtTccIncluded
#define LstIdxXYFeVtTccIncluded



#include "cbls/funcs/fevs/muxfevt.tcc"



openKangarooSpace



/*!
	@class LstIdxXYFeVt
	@brief A class to represent list element expressions.
	@details This class represents list element expressions.
*/
template<typename pxt, typename pyt, typename fvt>
class LstIdxXYFeVt : public MuxFeVt<fvt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys,
									Prm * thePrms, Dim const PrmCount);						//!< Definition.

		static LstIdxXYFeVt<pxt,pyt,fvt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static LstIdxXYFeVt<pxt,pyt,fvt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static LstIdxXYFeVt<pxt,pyt,fvt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static LstIdxXYFeVt<pxt,pyt,fvt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static LstIdxXYFeVt<pxt,pyt,fvt> const & cast(Term const & theTerm);	//!< Perform casting.
		static LstIdxXYFeVt<pxt,pyt,fvt> const * cast(Term const * theTerm);	//!< Perform casting.
		static LstIdxXYFeVt<pxt,pyt,fvt> & cast(Term & theTerm);				//!< Perform casting.
		static LstIdxXYFeVt<pxt,pyt,fvt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);			//!< Suits casting?
		static Bll suit(Term const * theTerm);			//!< Suits casting?
		static Bll suit(Term & theTerm);				//!< Suits casting?
		static Bll suit(Term * theTerm);				//!< Suits casting?

		//! @}

	protected:

		LstIdxXYFeVt(Fss const theFss, Hdl const hdlSys,
									Prm * thePrms, Dim const PrmCount);				//!< Constructor.
		LstIdxXYFeVt const & operator = (LstIdxXYFeVt<pxt,pyt,fvt> const & that);	//!< Assigner.
		LstIdxXYFeVt(LstIdxXYFeVt<pxt,pyt,fvt> const & that);						//!< Duplicator.
		virtual ~LstIdxXYFeVt();													//!< Destructor.

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
template<typename pxt, typename pyt, typename fvt>
inline Bll LstIdxXYFeVt<pxt,pyt,fvt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< LstIdxXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fvt>
inline Bll LstIdxXYFeVt<pxt,pyt,fvt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< LstIdxXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fvt>
inline Bll LstIdxXYFeVt<pxt,pyt,fvt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< LstIdxXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fvt>
inline Bll LstIdxXYFeVt<pxt,pyt,fvt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< LstIdxXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}



/*!
	Refer to an element in the sys.
*/
template<typename pxt, typename pyt, typename fvt>
inline LstIdxXYFeVt<pxt,pyt,fvt> const & LstIdxXYFeVt<pxt,pyt,fvt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< LstIdxXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<LstIdxXYFeVt<pxt,pyt,fvt> const &>(theTerm);
	CatchError
}



/*!
	Point to an element in the sys.
*/
template<typename pxt, typename pyt, typename fvt>
inline LstIdxXYFeVt<pxt,pyt,fvt> const * LstIdxXYFeVt<pxt,pyt,fvt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< LstIdxXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<LstIdxXYFeVt<pxt,pyt,fvt> const *>(theTerm);
	CatchError
}



/*!
	Refer to an element in the sys.
*/
template<typename pxt, typename pyt, typename fvt>
inline LstIdxXYFeVt<pxt,pyt,fvt> & LstIdxXYFeVt<pxt,pyt,fvt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< LstIdxXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<LstIdxXYFeVt<pxt,pyt,fvt> &>(theTerm);
	CatchError
}



/*!
	Point to an element in the sys.
*/
template<typename pxt, typename pyt, typename fvt>
inline LstIdxXYFeVt<pxt,pyt,fvt> * LstIdxXYFeVt<pxt,pyt,fvt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< LstIdxXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<LstIdxXYFeVt<pxt,pyt,fvt> *>(theTerm);
	CatchError
}



/*!
	Refer to an element term.
*/
template<typename pxt, typename pyt, typename fvt>
inline LstIdxXYFeVt<pxt,pyt,fvt> & LstIdxXYFeVt<pxt,pyt,fvt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to an element term.
*/
template<typename pxt, typename pyt, typename fvt>
inline LstIdxXYFeVt<pxt,pyt,fvt> * LstIdxXYFeVt<pxt,pyt,fvt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an element term.
*/
template<typename pxt, typename pyt, typename fvt>
inline LstIdxXYFeVt<pxt,pyt,fvt> const & LstIdxXYFeVt<pxt,pyt,fvt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to an element term.
*/
template<typename pxt, typename pyt, typename fvt>
inline LstIdxXYFeVt<pxt,pyt,fvt> const * LstIdxXYFeVt<pxt,pyt,fvt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template<typename pxt, typename pyt, typename fvt>
inline LstIdxXYFeVt<pxt,pyt,fvt>::~LstIdxXYFeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



#if ExecUpwdLazy
/*!
	Run post exection process in anew mode.
*/
template<typename pxt, typename pyt, typename fvt>
inline void LstIdxXYFeVt<pxt,pyt,fvt>::runPostExecAnew()
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
template<typename pxt, typename pyt, typename fvt>
inline void LstIdxXYFeVt<pxt,pyt,fvt>::runPostExecIncr()
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


#if CompLazy
/*!
	Run post execution process in bklg mode.
*/
template<typename pxt, typename pyt, typename fvt>
inline void LstIdxXYFeVt<pxt,pyt,fvt>::runPostExecBklg()
{
	WatchError
	if (this->mValueRec->PrevDiff(this->mTermSys.ExecClk()))
		this->notifyEvalUndoArgs();
	this->reiterEvalUndoPrms();
	CatchError
}
#endif //CompLazy


#if SimulUpwd
/*!
	Run post simulation process in anew mode.
*/
template<typename pxt, typename pyt, typename fvt>
inline void LstIdxXYFeVt<pxt,pyt,fvt>::runPostSimulAnew()
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
template<typename pxt, typename pyt, typename fvt>
inline void LstIdxXYFeVt<pxt,pyt,fvt>::runPostSimulIncr()
{
	WatchError
	this->clearSimulChgdPrms();
	if (this->mValueRec->NextDiff(this->mTermSys.SimulClk()))
		this->scheduleSimulIncrArgs();
	CatchError
}
#endif //SimulUpwd




/*!
	Define an ElemVCFeV in the sys.
*/
template<typename pxt, typename pyt, typename fvt>
Hdl LstIdxXYFeVt<pxt,pyt,fvt>::def(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount)
{
	WatchError
	Warn(PrmCount < 3 || PrmCount > MaxDim, eParamCount2(3, MaxDim));

	LstIdxXYFeVt<pxt,pyt,fvt> * tFeV = new LstIdxXYFeVt<pxt,pyt,fvt>(theFss, hdlSys, thePrms, PrmCount);
	Hdl const tHdl = tFeV->defSysFunc();
	if (tHdl != InvHdl) { delete tFeV; return tHdl; }

	EvalTbl<pyt> const & tPytTbl = EvalTbl<pyt>::refc(hdlSys);
	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<fvt> & tFvtTbl = EvalTbl<fvt>::refm(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFeV->mPrmTerms;
	b1<Bts,kmm> const & tPrmSpecs = tFeV->mPrmSpecs;

	for(Pos tPos = 0; tPos < tPrmTerms.iteratorLast(); ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFeV->mPxRecs[tPos] = tPxtTbl.ptrcEvalRec(tPxLoc);
	}
	Loc const tPyLoc = getPyLoc(theFss, tPrmTerms.itemLast(),tPrmSpecs.itemLast());
	tFeV->mPyRec = tPytTbl.ptrcEvalRec(tPyLoc);

	tFvtTbl.setEvalRec(tFeV->mValueRec, tFeV->mValueLoc);

	tFeV->performCompConst();
	tFeV->defSysRoot();
	return tFeV->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
template<typename pxt, typename pyt, typename fvt>
LstIdxXYFeVt<pxt,pyt,fvt>::LstIdxXYFeVt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) :
		MuxFeVt<fvt>(hdlSys, PrmCount), mCtlPos(PrmCount - 1), mPxRecs(PrmCount - 1)
{
	WatchError
	this->setTermCls(TermStub< LstIdxXYFeVt<pxt,pyt,fvt> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Ordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template<typename pxt, typename pyt, typename fvt>
LstIdxXYFeVt<pxt,pyt,fvt>::LstIdxXYFeVt(LstIdxXYFeVt<pxt,pyt,fvt> const & that) :
	MuxFeVt<fvt>(that), mCtlPos(that.mCtlPos), mPxRecs(0)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename pxt, typename pyt, typename fvt>
LstIdxXYFeVt<pxt,pyt,fvt> const & LstIdxXYFeVt<pxt,pyt,fvt>::operator = (LstIdxXYFeVt<pxt,pyt,fvt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



#if CompLazyHalf
/*!
	Notify deferment to the parameters.
*/
template<typename pxt, typename pyt, typename fvt>
void LstIdxXYFeVt<pxt,pyt,fvt>::notifyDeferedPrms()
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
template<typename pxt, typename pyt, typename fvt>
void LstIdxXYFeVt<pxt,pyt,fvt>::notifyEnforcedPrms()
{
	WatchError
	Term * const tCtrlTerm = this->mPrmTerms[mCtlPos];
	if (tCtrlTerm->computable())	//	not Updatable to exclude vars
		Func::setEnforcement(Func::cast(tCtrlTerm));
	CatchError
}
#endif	//CompLazyHalf



#if CompLazy
/*!
	Call parameters to list for eval undo.
*/
template<typename pxt, typename pyt, typename fvt>
void LstIdxXYFeVt<pxt,pyt,fvt>::reinitEvalUndoPrms()
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

		Pos tValuePos = mPyRec->CurrData();
		if (tValuePos >= mCtlPos) tValuePos = 0;

		Term * const tValueTerm = this->mPrmTerms[tValuePos];
		if (tValueTerm->updatable())	//	include vars
			Term::relistEvalUndoArg(tValueTerm, this->mPrmLinks[tValuePos]);
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
template<typename pxt, typename pyt, typename fvt>
void LstIdxXYFeVt<pxt,pyt,fvt>::reiterEvalUndoPrms()
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

		Pos tValuePos = mPyRec->CurrData();
		if (tValuePos >= mCtlPos) tValuePos = 0;

		Term * const tValueTerm = this->mPrmTerms[tValuePos];
		if (tValueTerm->updatable())
			Term::relistEvalUndoArg(tValueTerm, this->mPrmLinks[tValuePos]);
	}
	this->mBacklogPrms.sweep(this->mTermSys.ExecClk());
	this->mEvalUndonePrms->sweep(this->mTermSys.ExecClk());
	CatchError
}
#endif	//CompLazy


/*!
	Compute the term.
*/
template<typename pxt, typename pyt, typename fvt>
void LstIdxXYFeVt<pxt,pyt,fvt>::compConst()
{
	WatchError
	if (this->updatable() && !this->mPrmTerms[mCtlPos]->updatable())
	{
		Pos tValuePos = mPyRec->CurrData();
		if (tValuePos >= mCtlPos) tValuePos = 0;

		if (!this->mPrmTerms[tValuePos]->updatable())
			this->setUpdatable(false);
	}
	if (!this->updatable())
	{
		Pos tValuePos = mPyRec->CurrData();
		if (tValuePos >= mCtlPos) tValuePos = 0;

		this->mValueRec->finalise(tc<pxt,fvt>::iof(mPxRecs[tValuePos]->CurrData()));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename pxt, typename pyt, typename fvt>
void LstIdxXYFeVt<pxt,pyt,fvt>::execAnew()
{
	WatchError
	#if ExecDnwd
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
		Term::performExecAnew(this->mPrmTerms[tPos]);
	#endif

	Pos tValuePos = mPyRec->CurrData();
	if (tValuePos >= mCtlPos) tValuePos = 0;

	this->mValueRec->initCurr(tc<pxt,fvt>::iof(mPxRecs[tValuePos]->CurrData()));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fvt>
void LstIdxXYFeVt<pxt,pyt,fvt>::simulAnew()
{
	WatchError
	#if SimulDnwd
	Term::performSimulAnew(this->mPrmTerms[mCtlPos]);
	#endif

	Pos tValuePos = mPyRec->NextData(this->mTermSys.SimulClk());
	if(tValuePos >= mCtlPos) tValuePos = 0;

	#if SimulDnwd
	Term::performSimulAnew(this->mPrmTerms[tValuePos]);
	#endif

	this->mValueRec->updtNext(this->mTermSys.SimulClk(),
				tc<pxt,fvt>::iof(mPxRecs[tValuePos]->NextData(this->mTermSys.SimulClk())));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename pxt, typename pyt, typename fvt>
void LstIdxXYFeVt<pxt,pyt,fvt>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		Bll tNeedRecomp = this->mExecChgdPrms.tagged(mCtlPos) &&
			mPyRec->PrevDiff(this->mTermSys.ExecClk());

		Pos tValuePos = mPyRec->CurrData();
		if(tValuePos >= mCtlPos) tValuePos = 0;

		if (tNeedRecomp || (this->mExecChgdPrms.tagged(tValuePos) &&
					mPxRecs[tValuePos]->PrevDiff(this->mTermSys.ExecClk())))
				this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
						tc<pxt,fvt>::iof(mPxRecs[tValuePos]->CurrData()));
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

		Pos tValuePos = mPyRec->CurrData();
		if(tValuePos >= mCtlPos) tValuePos = 0;

		if (this->mLblCandPrms.tagged(tValuePos))
		{
			#if CompLazy
			Term::performExecIncr(this->mPrmTerms[tValuePos]);
			#endif
			if (!tNeedRecomp && mPxRecs[tValuePos]->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
		#if CompLazy
		else
		{
			Term::performExecBklg(this->mPrmTerms[tValuePos]);
			if (!tNeedRecomp && mPxRecs[tValuePos]->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
		#endif

		if (tNeedRecomp)
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
					tc<pxt,fvt>::iof(mPxRecs[tValuePos]->CurrData()));
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
		Pos tValuePos = mPyRec->CurrData();
		if (tValuePos >= mCtlPos) tValuePos = 0;

		if (this->mLblCandPrms.tagged(tValuePos))
		{
			Term::performExecIncr(this->mPrmTerms[tValuePos]);
			if (!tNeedRecomp && (this->mEvalUndonePrms->tagged(tValuePos) ||
					mPxRecs[tValuePos]->PrevDiff(this->mTermSys.ExecClk())))
				tNeedRecomp = true;
		}
		else //Param at tValuePos is assumed to be defered.
		{
			Term::performExecBklg(this->mPrmTerms[tValuePos]);
			if (!tNeedRecomp && (this->mEvalUndonePrms->tagged(tValuePos) ||
					mPxRecs[tValuePos]->PrevDiff(this->mTermSys.ExecClk())))
				tNeedRecomp = true;
		}
		if (tNeedRecomp)
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
					tc<pxt,fvt>::iof(mPxRecs[tValuePos]->CurrData()));
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
template<typename pxt, typename pyt, typename fvt>
void LstIdxXYFeVt<pxt,pyt,fvt>::execBklg()
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

	Pos tValuePos = mPyRec->CurrData();
	if(tValuePos >= mCtlPos) tValuePos = 0;

	Term::performExecBklg(this->mPrmTerms[tValuePos]);
	if (tNeedRecomp || this->mEvalUndonePrms->tagged(tValuePos) ||
				mPxRecs[tValuePos]->PrevDiff(this->mTermSys.ExecClk()))
		this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
				tc<pxt,fvt>::iof(mPxRecs[tValuePos]->CurrData()));
	this->runPostExecBklg();
	CatchError
}
#endif //CompLazy



/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fvt>
void LstIdxXYFeVt<pxt,pyt,fvt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		Bll tNeedRecomp = this->mSimulChgdPrms.tagged(mCtlPos) &&
				mPyRec->NextDiff(this->mTermSys.SimulClk());

		Pos tValuePos = mPyRec->NextData(this->mTermSys.SimulClk());
		if(tValuePos >= mCtlPos) tValuePos = 0;

		if (tNeedRecomp || (this->mSimulChgdPrms.tagged(tValuePos) &&
				mPxRecs[tValuePos]->NextDiff(this->mTermSys.SimulClk())))
			this->mValueRec->updtNext(this->mTermSys.SimulClk(),
					tc<pxt,fvt>::iof(mPxRecs[tValuePos]->NextData(this->mTermSys.SimulClk())));
		this->runPostSimulIncr();
	}
	#endif	//SimulUpwd
	#if SimulDnwd
	Bll tNeedRecomp = false; Pos tValuePos;
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
				tValuePos = mPyRec->NextData(this->mTermSys.SimulClk());
			}
		}
		if (!tNeedRecomp)
			tValuePos = mPyRec->NextData(this->mTermSys.SimulClk());

		if(tValuePos >= mCtlPos) tValuePos = 0;

		#if SimulFixedFlexi
		if (this->mLblFixedPrms.tagged(tValuePos) ||
				this->mLblFlexiPrms->tagged(tValuePos))
		#endif
		#if SimulFixedOnly
		if (this->mLblFixedPrms.tagged(tValuePos))
		#endif
		#if SimulFlexiOnly
		if (this->mLblFlexiPrms->tagged(tValuePos))
		#endif
		{
			Term::performSimulIncr(this->mPrmTerms[tValuePos]);
			if (tNeedRecomp || mPxRecs[tValuePos]->NextDiff(this->mTermSys.SimulClk()))
				this->mValueRec->updtNext(this->mTermSys.SimulClk(),
					tc<pxt,fvt>::iof(mPxRecs[tValuePos]->NextData(this->mTermSys.SimulClk())));
		}
		#if CompLazy
		else
		{
			Term::performEmulBklg(this->mPrmTerms[tValuePos]);
			if (tNeedRecomp || mPxRecs[tValuePos]->LateDiff(this->mTermSys.EmulClk()))
				this->mValueRec->updtNext(this->mTermSys.SimulClk(),
						tc<pxt,fvt>::iof(mPxRecs[tValuePos]->LateData(this->mTermSys.EmulClk())));
		}
		#else
		else
		{
			if (tNeedRecomp)
				this->mValueRec->updtNext(this->mTermSys.SimulClk(),
					mPxRecs[tValuePos]->NextData(this->mTermSys.SimulClk()));
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
				tValuePos = mPyRec->NextData(this->mTermSys.SimulClk());
			}
		}
		else if (this->mBacklogPrms.tagged(mCtlPos))
		{
			Term::performEmulBklg(this->mPrmTerms[mCtlPos]);
			if (this->mEvalUndonePrms->tagged(mCtlPos) ||
					mPyRec->LateDiff(this->mTermSys.EmulClk()))
			{
				tNeedRecomp = true;
				tValuePos = mPyRec->LateData(this->mTermSys.EmulClk());
			}
		}
		if (!tNeedRecomp)
			tValuePos= mPyRec->NextData(this->mTermSys.SimulClk());

		if(tValuePos >= mCtlPos) tValuePos = 0;

		#if SimulFixedFlexi
		if (this->mLblFixedPrms.tagged(tValuePos) ||
				this->mLblFlexiPrms->tagged(tValuePos))
		#endif
		#if SimulFixedOnly
		if (this->mLblFixedPrms.tagged(tValuePos))
		#endif
		#if SimulFlexiOnly
		if (this->mLblFlexiPrms->tagged(tValuePos))
		#endif
		{
			Term::performSimulIncr(this->mPrmTerms[tValuePos]);
			if (tNeedRecomp || this->mEvalUndonePrms->tagged(tValuePos) ||
					mPxRecs[tValuePos]->NextDiff(this->mTermSys.SimulClk()))
				this->mValueRec->updtNext(this->mTermSys.SimulClk(),
						tc<pxt,fvt>::iof(mPxRecs[tValuePos]->NextData(this->mTermSys.SimulClk())));
		}
		else //	Param at tValuePos is assumed to be defered.
		{
			Term::performEmulBklg(this->mPrmTerms[tValuePos]);
			if (tNeedRecomp || this->mEvalUndonePrms->tagged(tValuePos) ||
					mPxRecs[tValuePos]->LateDiff(this->mTermSys.SimulClk()))
				this->mValueRec->updtNext(this->mTermSys.SimulClk(),
						tc<pxt,fvt>::iof(mPxRecs[tValuePos]->LateData(this->mTermSys.EmulClk())));
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
template<typename pxt, typename pyt, typename fvt>
void LstIdxXYFeVt<pxt,pyt,fvt>::emulBklg()
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

	Pos tValuePos = mPyRec->LateData(this->mTermSys.EmulClk());
	if(tValuePos >= mCtlPos) tValuePos = 0;

	Term::performEmulBklg(this->mPrmTerms[tValuePos]);
	if (tNeedRecomp || this->mEvalUndonePrms->tagged(tValuePos) ||
				mPxRecs[tValuePos]->LateDiff(this->mTermSys.EmulClk()))
		this->mValueRec->updtLate(this->mTermSys.EmulClk(),
			tc<pxt,fvt>::iof(mPxRecs[tValuePos]->LateData(this->mTermSys.EmulClk())));
	CatchError
}
#endif //CompLazy



closeKangarooSpace


#endif//ElemYXFeVtTccIncluded
