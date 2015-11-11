/*!
	@file niftxyfcmt.tcc
	@brief The prototype file for NiftXYFcMt template class.
	@details This is the prototype file for NiftXYFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef NiftXYFcMtTccIncluded
#define NiftXYFcMtTccIncluded



#include "cbls/funcs/fcms/muxfcmt.tcc"



openKangarooSpace



/*!
	@class NiftXYFcMt
	@brief A template class to represent nif-then expressions.
	@details This template class represents nif-then expressions.
*/
template<typename pxt, typename pyt, typename fmt>
class NiftXYFcMt : public MuxFcMt<fmt>
{
	public:
		static Hdl def(Fss const theFss, Hdl const hdlSys,
									Prm const & Cond, Prm const & Then, pyt const & Else);	//!< Definition.

		static NiftXYFcMt<pxt,pyt,fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static NiftXYFcMt<pxt,pyt,fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static NiftXYFcMt<pxt,pyt,fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static NiftXYFcMt<pxt,pyt,fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static NiftXYFcMt<pxt,pyt,fmt> const & cast(Term const & theTerm);		//!< Perform casting.
		static NiftXYFcMt<pxt,pyt,fmt> const * cast(Term const * theTerm);		//!< Perform casting.
		static NiftXYFcMt<pxt,pyt,fmt> & cast(Term & theTerm);					//!< Perform casting.
		static NiftXYFcMt<pxt,pyt,fmt> * cast(Term * theTerm);					//!< Perform casting.

		static Bll suit(Term const & theTerm);								//!< Suits casting?
		static Bll suit(Term const * theTerm);								//!< Suits casting?
		static Bll suit(Term & theTerm);									//!< Suits casting?
		static Bll suit(Term * theTerm);									//!< Suits casting?

		//! @}

	protected:
		NiftXYFcMt(Fss const theFss, Hdl const hdlSys,
									Prm * thePrms, Dim const PrmCount, pyt const & Else);	//!< Constructor.
		NiftXYFcMt const & operator = (NiftXYFcMt<pxt,pyt,fmt> const & that);				//!< Assigner.
		NiftXYFcMt(NiftXYFcMt<pxt,pyt,fmt> const & that);									//!< Duplicator.
		virtual ~NiftXYFcMt();																//!< Destructor.

		//! @name Identity
		//! @{

		Hvl calcTermHvl() const;			 				//!< Calculate term hash value.
		virtual Bll equate(Term const & theTerm) const; 	//!< Compare terms for equality.

		//! @}

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
		void runPostExecAnew();		//!< Run post exection in anew mode.
		void runPostExecIncr();		//!< Run post execuiton in incr mode.
		#endif
		#if SimulUpwd
		void runPostSimulAnew();	//!< Run post simulation in anew mode.
		void runPostSimulIncr();	//!< Run post simulation in incr mode.
		#endif
		#if CompLazy
		void runPostExecBklg();		//!< Run post execuiton in bklg mode.
		#endif

		//! @}

		//! @name Computations
		//! @{

		virtual void compConst();	//!< Compute the term.
		virtual void execAnew();	//!< Execute the term.
		virtual void simulAnew();	//!< Simulate the term.
		virtual void execIncr();	//!< Execute the term.
		virtual void simulIncr();	//!< Simulate the term.
		#if CompLazy
		virtual void execBklg();	//!< Execute the term.
		virtual void emulBklg();	//!< Emulate the term.
		#endif

		//! @}

	private:

		EvalRec<pxt> const * mPxRec;			//!< Cond parameter value.
		EvalRec<pyt> const * mTyRec;			//!< Then parameter value.
		pyt const mEy;							//!< Else parameter value.
};



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fmt>
inline Bll NiftXYFcMt<pxt,pyt,fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< NiftXYFcMt<pxt,pyt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fmt>
inline Bll NiftXYFcMt<pxt,pyt,fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< NiftXYFcMt<pxt,pyt,fmt> >::TermCls;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fmt>
inline Bll NiftXYFcMt<pxt,pyt,fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< NiftXYFcMt<pxt,pyt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fmt>
inline Bll NiftXYFcMt<pxt,pyt,fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< NiftXYFcMt<pxt,pyt,fmt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fmt>
inline NiftXYFcMt<pxt,pyt,fmt> const &
NiftXYFcMt<pxt,pyt,fmt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< NiftXYFcMt<pxt,pyt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<NiftXYFcMt<pxt,pyt,fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fmt>
inline NiftXYFcMt<pxt,pyt,fmt> const * NiftXYFcMt<pxt,pyt,fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< NiftXYFcMt<pxt,pyt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<NiftXYFcMt<pxt,pyt,fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fmt>
inline NiftXYFcMt<pxt,pyt,fmt> & NiftXYFcMt<pxt,pyt,fmt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< NiftXYFcMt<pxt,pyt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<NiftXYFcMt<pxt,pyt,fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fmt>
inline NiftXYFcMt<pxt,pyt,fmt> * NiftXYFcMt<pxt,pyt,fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< NiftXYFcMt<pxt,pyt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<NiftXYFcMt<pxt,pyt,fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to an nif-then term.
*/
template<typename pxt, typename pyt, typename fmt>
inline NiftXYFcMt<pxt,pyt,fmt> &
NiftXYFcMt<pxt,pyt,fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to an nif-then term.
*/
template<typename pxt, typename pyt, typename fmt>
inline NiftXYFcMt<pxt,pyt,fmt> *
NiftXYFcMt<pxt,pyt,fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an nif-then term.
*/
template<typename pxt, typename pyt, typename fmt>
inline NiftXYFcMt<pxt,pyt,fmt> const &
NiftXYFcMt<pxt,pyt,fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to an nif-then term.
*/
template<typename pxt, typename pyt, typename fmt>
inline NiftXYFcMt<pxt,pyt,fmt> const *
NiftXYFcMt<pxt,pyt,fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template<typename pxt, typename pyt, typename fmt>
inline NiftXYFcMt<pxt,pyt,fmt>::~NiftXYFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Calculate hash value of the term.
*/
template<typename pxt, typename pyt, typename fmt>
Hvl NiftXYFcMt<pxt,pyt,fmt>::calcTermHvl() const
{
	WatchError
	Hvl tHvl = 0;
	tHvl = mixHash(tHvl, calcHash(this->TermCls));
	tHvl = mixHash(tHvl, calcHash(this->FuncFss));
	tHvl = mixHash(tHvl, calcHash(this->mPrmTerms[0]));
	tHvl = mixHash(tHvl, calcHash(this->mPrmSpecs[0]));
	tHvl = mixHash(tHvl, calcHash(this->mPrmTerms[1]));
	tHvl = mixHash(tHvl, calcHash(this->mPrmSpecs[1]));
	tHvl = mixHash(tHvl, calcHash(mEy));
	return tHvl;
	CatchError
}



/*!
	Compare two terms for equality.
*/
template<typename pxt, typename pyt, typename fmt>
Bll NiftXYFcMt<pxt,pyt,fmt>::equate(Term const & theTerm) const
{
	WatchError
	if (this->TermCls != theTerm.TermCls) return false;
	NiftXYFcMt<pxt,pyt,fmt> const & tFcM = cast(theTerm);
	if (this->FuncFss != tFcM.FuncFss) return false;

	if (this->mPrmTerms.itemCount() != tFcM.mPrmTerms.itemCount()) return false;
	if (this->mPrmTerms[0] != tFcM.mPrmTerms[0]) return false;
	if (this->mPrmSpecs[0] != tFcM.mPrmSpecs[0]) return false;
	if (this->mPrmTerms[1] != tFcM.mPrmTerms[1]) return false;
	if (this->mPrmSpecs[1] != tFcM.mPrmSpecs[1]) return false;
	if (ne<pyt,Bll>::iof(mEy, tFcM.mEy)) return false;
	return true;
	CatchError
}



#if ExecUpwdLazy
/*!
	Run post exection process in anew mode.
*/
template<typename pxt, typename pyt, typename fmt>
inline void NiftXYFcMt<pxt,pyt,fmt>::runPostExecAnew()
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
inline void NiftXYFcMt<pxt,pyt,fmt>::runPostExecIncr()
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
inline void NiftXYFcMt<pxt,pyt,fmt>::runPostExecBklg()
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
inline void NiftXYFcMt<pxt,pyt,fmt>::runPostSimulAnew()
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
inline void NiftXYFcMt<pxt,pyt,fmt>::runPostSimulIncr()
{
	WatchError
	this->clearSimulChgdPrms();
	if (this->mMetricRec->NextDiff(this->mTermSys.SimulClk()))
		this->scheduleSimulIncrArgs();
	CatchError
}
#endif //SimulUpwd



/*!
	Define an nif-then expression in the sys.
*/
template<typename pxt, typename pyt, typename fmt>
inline Hdl NiftXYFcMt<pxt,pyt,fmt>::def(Fss const theFss, Hdl const hdlSys,
		Prm const & Cond, Prm const & Then, pyt const & Else)
{
	WatchError
	Prm tPrms[2] = { Cond, Then};
	NiftXYFcMt<pxt,pyt,fmt> * tFcM = new NiftXYFcMt<pxt,pyt,fmt>(theFss, hdlSys, tPrms, 2, Else);
	Hdl const tHdl = tFcM->defSysFunc();
	if (tHdl != InvHdl) { delete tFcM; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<pyt> const & tPytTbl = EvalTbl<pyt>::refc(hdlSys);
	EvalTbl<fmt> & tFmtTbl = EvalTbl<fmt>::refm(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFcM->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFcM->mPrmSpecs;

	Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[0], tPrmSpecs[0]);
	tFcM->mPxRec = tPxtTbl.ptrcEvalRec(tPxLoc);

	Loc const tTyLoc = getPyLoc(theFss,tPrmTerms[1], tPrmSpecs[1]);
	tFcM->mTyRec = tPytTbl.ptrcEvalRec(tTyLoc);

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
NiftXYFcMt<pxt,pyt,fmt>::NiftXYFcMt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, pyt const & Else) :
		MuxFcMt<fmt>(hdlSys, PrmCount), mEy(Else)
{
	WatchError
	this->setTermCls(TermStub< NiftXYFcMt<pxt,pyt,fmt> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Ordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template<typename pxt, typename pyt, typename fmt>
NiftXYFcMt<pxt,pyt,fmt>::NiftXYFcMt(NiftXYFcMt<pxt,pyt,fmt> const & that) :
	MuxFcMt<fmt>(that), mEy(that.mEy)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename pxt, typename pyt, typename fmt>
NiftXYFcMt<pxt,pyt,fmt> const & NiftXYFcMt<pxt,pyt,fmt>::operator = (NiftXYFcMt<pxt,pyt,fmt> const & that)
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
void NiftXYFcMt<pxt,pyt,fmt>::notifyDeferedPrms()
{
	WatchError
	Term * const tPrmTerm = this->mPrmTerms[0];
	if (tPrmTerm->computable())	//	not updatable to exclude vars
		Func::unsetEnforcement(Func::cast(tPrmTerm));

	this->reinitEvalUndoPrms();
	CatchError
}
#endif //CompLazyHalf


#if CompLazyHalf
/*!
	Notify enforcement to the parameters.
*/
template<typename pxt, typename pyt, typename fmt>
void NiftXYFcMt<pxt,pyt,fmt>::notifyEnforcedPrms()
{
	WatchError
	Term * const tPrmTerm = this->mPrmTerms[0];
	if (tPrmTerm->computable())	//	not updatable to exclude vars
		Func::setEnforcement(Func::cast(tPrmTerm));
	CatchError
}
#endif //CompLazyHalf


#if CompLazy
/*!
	Call parameters to list for eval undo.
*/
template<typename pxt, typename pyt, typename fmt>
void NiftXYFcMt<pxt,pyt,fmt>::reinitEvalUndoPrms()
{
	WatchError
	//	no mode anew mode checking because deferment would happen even
	//	when incr mode and still need this method to run.
	Warn(!this->mEvalUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (this->defered())
	#endif
	{
		Term * const tCondTerm = this->mPrmTerms[0];
		if (tCondTerm->updatable())	//	include vars
			Term::relistEvalUndoArg(tCondTerm, this->mPrmLinks[0]);

		if (!tc<pxt,Bll>::iof(mPxRec->CurrData()))
		{
			Term * const tMetricTerm = this->mPrmTerms[1];
			if (tMetricTerm->updatable())	//	include vars
				Term::relistEvalUndoArg(tMetricTerm, this->mPrmLinks[1]);
		}
	}
	this->mBacklogPrms.sweep(this->mTermSys.ExecClk());
	this->mEvalUndonePrms->sweep(this->mTermSys.ExecClk());
	CatchError
}
#endif //CompLazy


#if CompLazy
/*!
	Call parameters to relist for unreck.
*/
template<typename pxt, typename pyt, typename fmt>
void NiftXYFcMt<pxt,pyt,fmt>::reiterEvalUndoPrms()
{
	WatchError
	Warn(!this->mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);
	Warn(!this->mEvalUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (this->defered())
	#endif
	{
		Term * const tCondTerm = this->mPrmTerms[0];
		if (tCondTerm->updatable())
			Term::relistEvalUndoArg(tCondTerm, this->mPrmLinks[0]);

		if (!tc<pxt,Bll>::iof(mPxRec->CurrData()))
		{
			Term * const tMetricTerm = this->mPrmTerms[1];
			if (tMetricTerm->updatable())
				Term::relistEvalUndoArg(tMetricTerm, this->mPrmLinks[1]);
		}
	}
	this->mBacklogPrms.sweep(this->mTermSys.ExecClk());
	this->mEvalUndonePrms->sweep(this->mTermSys.ExecClk());
	CatchError
}
#endif //CompLazy


/*!
	Compute the term.
*/
template<typename pxt, typename pyt, typename fmt>
void NiftXYFcMt<pxt,pyt,fmt>::compConst()
{
	WatchError
	if (this->updatable() && !this->mPrmTerms[0]->updatable())
	{
		if (!tc<pxt,Bll>::iof(mPxRec->CurrData()))
		{
			if (!this->mPrmTerms[1]->updatable())
				this->setUpdatable(false);
		}
		else
			this->setUpdatable(false);
	}
	if (!this->updatable())
	{
		if (!tc<pxt,Bll>::iof(mPxRec->CurrData()))
			this->mMetricRec->finalise(tc<pyt,fmt>::iof(mTyRec->CurrData()));
		else
			this->mMetricRec->finalise(tc<pyt,fmt>::iof(mEy));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename pxt, typename pyt, typename fmt>
void NiftXYFcMt<pxt,pyt,fmt>::execAnew()
{
	WatchError
	#if ExecDnwd
	Term::performExecAnew(this->mPrmTerms[0]);
	Term::performExecAnew(this->mPrmTerms[1]);
	#endif

	if (!tc<pxt,Bll>::iof(mPxRec->CurrData()))
		this->mMetricRec->initCurr(tc<pyt,fmt>::iof(mTyRec->CurrData()));
	else
		this->mMetricRec->initCurr(tc<pyt,fmt>::iof(mEy));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fmt>
void NiftXYFcMt<pxt,pyt,fmt>::simulAnew()
{
	WatchError
	#if SimulDnwd
	Term::performSimulAnew(this->mPrmTerms[0]);
	#endif
	if (!tc<pxt,Bll>::iof(mPxRec->NextData(this->mTermSys.SimulClk())))
	{
		#if SimulDnwd
		Term::performSimulAnew(this->mPrmTerms[1]);
		#endif
		this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
				tc<pyt,fmt>::iof(mTyRec->NextData(this->mTermSys.SimulClk())));
	}
	else
		this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<pyt,fmt>::iof(mEy));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename pxt, typename pyt, typename fmt>
void NiftXYFcMt<pxt,pyt,fmt>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		Bll tNeedRecomp = this->mExecChgdPrms.tagged(0) &&
				mPxRec->PrevDiff(this->mTermSys.ExecClk());
		if (!tc<pxt,Bll>::iof(mPxRec->CurrData()))
		{
			if (tNeedRecomp || (this->mExecChgdPrms.tagged(1) &&
					mTyRec->PrevDiff(this->mTermSys.ExecClk())))
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
						tc<pyt,fmt>::iof(mTyRec->CurrData()));
		}
		else if (tNeedRecomp)
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<pyt,fmt>::iof(mEy));

		this->runPostExecIncr();
	}
	#endif	//ExecUpwd
	#if ExecDnwd
	Bll tNeedRecomp = false;
	if (this->needExecCandComp()) this->markCandParams();
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//CompLazy
		if (this->mLblCandPrms.tagged(0))
		{
			Term::performExecIncr(this->mPrmTerms[0]);
			if (mPxRec->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
		if (!tc<pxt,Bll>::iof(mPxRec->CurrData()))
		{
			if (this->mLblCandPrms.tagged(1))
			{
				Term::performExecIncr(this->mPrmTerms[1]);
				if (!tNeedRecomp && mTyRec->PrevDiff(this->mTermSys.ExecClk()))
					tNeedRecomp = true;
			}
			#if CompLazy
			else
			{
				Term::performExecBklg(this->mPrmTerms[1]);
				if (!tNeedRecomp && mTyRec->PrevDiff(this->mTermSys.ExecClk()))
					tNeedRecomp = true;
			}
			#endif

			if (tNeedRecomp)
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
						tc<pyt,fmt>::iof(mTyRec->CurrData()));
		}
		else
		{
			if (tNeedRecomp)
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<pyt,fmt>::iof(mEy));
			#if !CompLazy
			if (this->mLblCandPrms.tagged(1))	// Required in non-lazy mode.
				Term::performExecIncr(this->mPrmTerms[1]);
			#endif
		}
	#if CompLazy
	}
	else
	{
		if (this->mLblCandPrms.tagged(0))
		{
			Term::performExecIncr(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
		else if (this->mBacklogPrms.tagged(0))
		{
			Term::performExecBklg(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
		if (!tc<pxt,Bll>::iof(mPxRec->CurrData()))
		{
			if (this->mLblCandPrms.tagged(1))
			{
				Term::performExecIncr(this->mPrmTerms[1]);
				if (!tNeedRecomp && (this->mEvalUndonePrms->tagged(1) ||
						mTyRec->PrevDiff(this->mTermSys.ExecClk())))
					tNeedRecomp = true;
			}
			else //	no backlog checking, param1 is assumed to be defered.
			{
				Term::performExecBklg(this->mPrmTerms[1]);
				if (!tNeedRecomp && (this->mEvalUndonePrms->tagged(1) ||
						mTyRec->PrevDiff(this->mTermSys.ExecClk())))
					tNeedRecomp = true;
			}
			if (tNeedRecomp)
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
						tc<pyt,fmt>::iof(mTyRec->CurrData()));
		}
		else if (tNeedRecomp)
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<pyt,fmt>::iof(mEy));
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
void NiftXYFcMt<pxt,pyt,fmt>::execBklg()
{
	WatchError
	Bll tNeedRecomp = false;
	if (this->mBacklogPrms.tagged(0))
	{
		Term::performExecBklg(this->mPrmTerms[0]);
		if (this->mEvalUndonePrms->tagged(0) ||
				mPxRec->PrevDiff(this->mTermSys.ExecClk()))
			tNeedRecomp = true;
	}
	if (!tc<pxt,Bll>::iof(mPxRec->CurrData()))
	{
		Term::performExecBklg(this->mPrmTerms[1]);
		if (tNeedRecomp || this->mEvalUndonePrms->tagged(1) ||
					mTyRec->PrevDiff(this->mTermSys.ExecClk()))
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
					tc<pyt,fmt>::iof(mTyRec->CurrData()));
	}
	else if (tNeedRecomp)
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<pyt,fmt>::iof(mEy));
	this->runPostExecBklg();
	CatchError
}
#endif



/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fmt>
void NiftXYFcMt<pxt,pyt,fmt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		Bll tNeedRecomp = this->mSimulChgdPrms.tagged(0) &&
				mPxRec->NextDiff(this->mTermSys.SimulClk());
		if (!tc<pxt,Bll>::iof(mPxRec->NextData(this->mTermSys.SimulClk())))
		{
			if (tNeedRecomp || (this->mSimulChgdPrms.tagged(1) &&
					mTyRec->NextDiff(this->mTermSys.SimulClk())))
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
						tc<pyt,fmt>::iof(mTyRec->NextData(this->mTermSys.SimulClk())));
		}
		else if (tNeedRecomp)
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<pyt,fmt>::iof(mEy));
		this->runPostSimulIncr();
	}
	#endif	//SimulUpwd
	#if SimulDnwd
	Bll tNeedRecomp = false, tCondMetric;

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
		if (this->mLblFixedPrms.tagged(0) || this->mLblFlexiPrms->tagged(0))
		#endif
		#if SimulFixedOnly
		if (this->mLblFixedPrms.tagged(0))
		#endif
		#if SimulFlexiOnly
		if (this->mLblFlexiPrms->tagged(0))
		#endif
		{
			Term::performSimulIncr(this->mPrmTerms[0]);
			if (mPxRec->NextDiff(this->mTermSys.SimulClk()))
			{
				tNeedRecomp = true;
				tCondMetric = tc<pxt,Bll>::iof(mPxRec->NextData(this->mTermSys.SimulClk()));
			}
		}
		if (!tNeedRecomp)
			tCondMetric = tc<pxt,Bll>::iof(mPxRec->NextData(this->mTermSys.SimulClk()));
		if (!tCondMetric)
		{
			#if SimulFixedFlexi
			if (this->mLblFixedPrms.tagged(1) || this->mLblFlexiPrms->tagged(1))
			#endif
			#if SimulFixedOnly
			if (this->mLblFixedPrms.tagged(1))
			#endif
			#if SimulFlexiOnly
			if (this->mLblFlexiPrms->tagged(1))
			#endif
			{
				Term::performSimulIncr(this->mPrmTerms[1]);
				if (tNeedRecomp || mTyRec->NextDiff(this->mTermSys.SimulClk()))
					this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
							tc<pyt,fmt>::iof(mTyRec->NextData(this->mTermSys.SimulClk())));

			}
			#if CompLazy
			else
			{
				Term::performEmulBklg(this->mPrmTerms[1]);
				if (tNeedRecomp || mTyRec->LateDiff(this->mTermSys.EmulClk()))
					this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
							tc<pyt,fmt>::iof(mTyRec->LateData(this->mTermSys.EmulClk())));
			}
			#else
			else
			{
				if (tNeedRecomp)
					this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
							mTyRec->NextData(this->mTermSys.SimulClk()));
			}
			#endif
		}
		else if (tNeedRecomp)
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<pyt,fmt>::iof(mEy));
	#if CompLazy
	}
	else
	{
		#if SimulFixedFlexi
		if (this->mLblFixedPrms.tagged(0) || this->mLblFlexiPrms->tagged(0))
		#endif
		#if SimulFixedOnly
		if (this->mLblFixedPrms.tagged(0))
		#endif
		#if SimulFlexiOnly
		if (this->mLblFlexiPrms->tagged(0))
		#endif
		{
			Term::performSimulIncr(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->NextDiff(this->mTermSys.SimulClk()))
			{
				tNeedRecomp = true;
				tCondMetric = tc<pxt,Bll>::iof(mPxRec->NextData(this->mTermSys.SimulClk()));
			}
		}
		else if (this->mBacklogPrms.tagged(0))
		{
			Term::performEmulBklg(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->LateDiff(this->mTermSys.EmulClk()))
			{
				tNeedRecomp = true;
				tCondMetric = tc<pxt,Bll>::iof(mPxRec->LateData(this->mTermSys.EmulClk()));
			}
		}
		if (!tNeedRecomp)
			tCondMetric = tc<pxt,Bll>::iof(mPxRec->NextData(this->mTermSys.SimulClk()));
		if (!tCondMetric)
		{
			#if SimulFixedFlexi
			if (this->mLblFixedPrms.tagged(1) || this->mLblFlexiPrms->tagged(1))
			#endif
			#if SimulFixedOnly
			if (this->mLblFixedPrms.tagged(1))
			#endif
			#if SimulFlexiOnly
			if (this->mLblFlexiPrms->tagged(1))
			#endif
			{
				Term::performSimulIncr(this->mPrmTerms[1]);
				if (tNeedRecomp || this->mEvalUndonePrms->tagged(1) ||
						mTyRec->NextDiff(this->mTermSys.SimulClk()))
					this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
							tc<pyt,fmt>::iof(mTyRec->NextData(this->mTermSys.SimulClk())));
			}
			else //	no backlog checking, param1 is assumed to be defered.
			{
				Term::performEmulBklg(this->mPrmTerms[1]);
				if (tNeedRecomp || this->mEvalUndonePrms->tagged(1) ||
						mTyRec->LateDiff(this->mTermSys.SimulClk()))
					this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
							tc<pyt,fmt>::iof(mTyRec->LateData(this->mTermSys.EmulClk())));
			}
		}
		else if (tNeedRecomp)
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<pyt,fmt>::iof(mEy));
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
void NiftXYFcMt<pxt,pyt,fmt>::emulBklg()
{
	WatchError
	Bll tNeedRecomp = false;
	if (this->mBacklogPrms.tagged(0))
	{
		Term::performEmulBklg(this->mPrmTerms[0]);
		if (this->mEvalUndonePrms->tagged(0) ||
				mPxRec->LateDiff(this->mTermSys.EmulClk()))
			tNeedRecomp = true;
	}

	if (!tc<pxt,Bll>::iof(mPxRec->LateData(this->mTermSys.EmulClk())))
	{
		Term::performEmulBklg(this->mPrmTerms[1]);
		if (tNeedRecomp || this->mEvalUndonePrms->tagged(1) ||
				mTyRec->LateDiff(this->mTermSys.EmulClk()))
			this->mMetricRec->updtLate(this->mTermSys.EmulClk(),
				tc<pyt,fmt>::iof(mTyRec->LateData(this->mTermSys.EmulClk())));
	}
	else if (tNeedRecomp)
			this->mMetricRec->updtLate(this->mTermSys.EmulClk(), tc<pyt,fmt>::iof(mEy));
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif//NiftXYFcMtIncluded
