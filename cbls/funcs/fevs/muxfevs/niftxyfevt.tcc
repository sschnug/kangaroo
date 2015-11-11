/*!
	@file niftxyfevt.tcc
	@brief The prototype file for NiftXYFeVt template class.
	@details This is the prototype file for NiftXYFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef NiftXYFeVtTccIncluded
#define NiftXYFeVtTccIncluded



#include "cbls/funcs/fevs/muxfevt.tcc"



openKangarooSpace



/*!
	@class NiftXYFeVt
	@brief A template class to represent nif-then expressions.
	@details This template class represents nif-then expressions.
*/
template<typename pxt, typename pyt, typename fvt>
class NiftXYFeVt : public MuxFeVt<fvt>
{
	public:
		static Hdl def(Fss const theFss, Hdl const hdlSys,
									Prm const & Cond, Prm const & Then, pyt const & Else);	//!< Definition.

		static NiftXYFeVt<pxt,pyt,fvt> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static NiftXYFeVt<pxt,pyt,fvt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static NiftXYFeVt<pxt,pyt,fvt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static NiftXYFeVt<pxt,pyt,fvt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static NiftXYFeVt<pxt,pyt,fvt> const & cast(Term const & theTerm);		//!< Perform casting.
		static NiftXYFeVt<pxt,pyt,fvt> const * cast(Term const * theTerm);		//!< Perform casting.
		static NiftXYFeVt<pxt,pyt,fvt> & cast(Term & theTerm);					//!< Perform casting.
		static NiftXYFeVt<pxt,pyt,fvt> * cast(Term * theTerm);					//!< Perform casting.

		static Bll suit(Term const & theTerm);								//!< Suits casting?
		static Bll suit(Term const * theTerm);								//!< Suits casting?
		static Bll suit(Term & theTerm);									//!< Suits casting?
		static Bll suit(Term * theTerm);									//!< Suits casting?

		//! @}

	protected:
		NiftXYFeVt(Fss const theFss, Hdl const hdlSys,
									Prm * thePrms, Dim const PrmCount, pyt const & Else);	//!< Constructor.
		NiftXYFeVt const & operator = (NiftXYFeVt<pxt,pyt,fvt> const & that);				//!< Assigner.
		NiftXYFeVt(NiftXYFeVt<pxt,pyt,fvt> const & that);									//!< Duplicator.
		virtual ~NiftXYFeVt();																//!< Destructor.

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
template<typename pxt, typename pyt, typename fvt>
inline Bll NiftXYFeVt<pxt,pyt,fvt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< NiftXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fvt>
inline Bll NiftXYFeVt<pxt,pyt,fvt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< NiftXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fvt>
inline Bll NiftXYFeVt<pxt,pyt,fvt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< NiftXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fvt>
inline Bll NiftXYFeVt<pxt,pyt,fvt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< NiftXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fvt>
inline NiftXYFeVt<pxt,pyt,fvt> const &
NiftXYFeVt<pxt,pyt,fvt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< NiftXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<NiftXYFeVt<pxt,pyt,fvt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fvt>
inline NiftXYFeVt<pxt,pyt,fvt> const * NiftXYFeVt<pxt,pyt,fvt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< NiftXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<NiftXYFeVt<pxt,pyt,fvt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fvt>
inline NiftXYFeVt<pxt,pyt,fvt> & NiftXYFeVt<pxt,pyt,fvt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< NiftXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<NiftXYFeVt<pxt,pyt,fvt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fvt>
inline NiftXYFeVt<pxt,pyt,fvt> * NiftXYFeVt<pxt,pyt,fvt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< NiftXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<NiftXYFeVt<pxt,pyt,fvt> *>(theTerm);
	CatchError
}



/*!
	Refer to an nif-then term.
*/
template<typename pxt, typename pyt, typename fvt>
inline NiftXYFeVt<pxt,pyt,fvt> &
NiftXYFeVt<pxt,pyt,fvt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to an nif-then term.
*/
template<typename pxt, typename pyt, typename fvt>
inline NiftXYFeVt<pxt,pyt,fvt> *
NiftXYFeVt<pxt,pyt,fvt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an nif-then term.
*/
template<typename pxt, typename pyt, typename fvt>
inline NiftXYFeVt<pxt,pyt,fvt> const &
NiftXYFeVt<pxt,pyt,fvt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to an nif-then term.
*/
template<typename pxt, typename pyt, typename fvt>
inline NiftXYFeVt<pxt,pyt,fvt> const *
NiftXYFeVt<pxt,pyt,fvt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template<typename pxt, typename pyt, typename fvt>
inline NiftXYFeVt<pxt,pyt,fvt>::~NiftXYFeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Calculate hash value of the term.
*/
template<typename pxt, typename pyt, typename fvt>
Hvl NiftXYFeVt<pxt,pyt,fvt>::calcTermHvl() const
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
template<typename pxt, typename pyt, typename fvt>
Bll NiftXYFeVt<pxt,pyt,fvt>::equate(Term const & theTerm) const
{
	WatchError
	if (this->TermCls != theTerm.TermCls) return false;
	NiftXYFeVt<pxt,pyt,fvt> const & tFeV = cast(theTerm);
	if (this->FuncFss != tFeV.FuncFss) return false;

	if (this->mPrmTerms.itemCount() != tFeV.mPrmTerms.itemCount()) return false;
	if (this->mPrmTerms[0] != tFeV.mPrmTerms[0]) return false;
	if (this->mPrmSpecs[0] != tFeV.mPrmSpecs[0]) return false;
	if (this->mPrmTerms[1] != tFeV.mPrmTerms[1]) return false;
	if (this->mPrmSpecs[1] != tFeV.mPrmSpecs[1]) return false;
	if (ne<pyt,Bll>::iof(mEy, tFeV.mEy)) return false;
	return true;
	CatchError
}



#if ExecUpwdLazy
/*!
	Run post exection process in anew mode.
*/
template<typename pxt, typename pyt, typename fvt>
inline void NiftXYFeVt<pxt,pyt,fvt>::runPostExecAnew()
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
inline void NiftXYFeVt<pxt,pyt,fvt>::runPostExecIncr()
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
inline void NiftXYFeVt<pxt,pyt,fvt>::runPostExecBklg()
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
inline void NiftXYFeVt<pxt,pyt,fvt>::runPostSimulAnew()
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
inline void NiftXYFeVt<pxt,pyt,fvt>::runPostSimulIncr()
{
	WatchError
	this->clearSimulChgdPrms();
	if (this->mValueRec->NextDiff(this->mTermSys.SimulClk()))
		this->scheduleSimulIncrArgs();
	CatchError
}
#endif //SimulUpwd



/*!
	Define an nif-then expression in the sys.
*/
template<typename pxt, typename pyt, typename fvt>
inline Hdl NiftXYFeVt<pxt,pyt,fvt>::def(Fss const theFss, Hdl const hdlSys,
		Prm const & Cond, Prm const & Then, pyt const & Else)
{
	WatchError
	Prm tPrms[2] = { Cond, Then};
	NiftXYFeVt<pxt,pyt,fvt> * tFeV = new NiftXYFeVt<pxt,pyt,fvt>(theFss, hdlSys, tPrms, 2, Else);
	Hdl const tHdl = tFeV->defSysFunc();
	if (tHdl != InvHdl) { delete tFeV; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<pyt> const & tPytTbl = EvalTbl<pyt>::refc(hdlSys);
	EvalTbl<fvt> & tFvtTbl = EvalTbl<fvt>::refm(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFeV->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFeV->mPrmSpecs;

	Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[0], tPrmSpecs[0]);
	tFeV->mPxRec = tPxtTbl.ptrcEvalRec(tPxLoc);

	Loc const tTyLoc = getPyLoc(theFss,tPrmTerms[1], tPrmSpecs[1]);
	tFeV->mTyRec = tPytTbl.ptrcEvalRec(tTyLoc);

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
NiftXYFeVt<pxt,pyt,fvt>::NiftXYFeVt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, pyt const & Else) :
		MuxFeVt<fvt>(hdlSys, PrmCount), mEy(Else)
{
	WatchError
	this->setTermCls(TermStub< NiftXYFeVt<pxt,pyt,fvt> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Ordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template<typename pxt, typename pyt, typename fvt>
NiftXYFeVt<pxt,pyt,fvt>::NiftXYFeVt(NiftXYFeVt<pxt,pyt,fvt> const & that) :
	MuxFeVt<fvt>(that), mEy(that.mEy)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename pxt, typename pyt, typename fvt>
NiftXYFeVt<pxt,pyt,fvt> const & NiftXYFeVt<pxt,pyt,fvt>::operator = (NiftXYFeVt<pxt,pyt,fvt> const & that)
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
void NiftXYFeVt<pxt,pyt,fvt>::notifyDeferedPrms()
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
template<typename pxt, typename pyt, typename fvt>
void NiftXYFeVt<pxt,pyt,fvt>::notifyEnforcedPrms()
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
template<typename pxt, typename pyt, typename fvt>
void NiftXYFeVt<pxt,pyt,fvt>::reinitEvalUndoPrms()
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
			Term * const tValueTerm = this->mPrmTerms[1];
			if (tValueTerm->updatable())	//	include vars
				Term::relistEvalUndoArg(tValueTerm, this->mPrmLinks[1]);
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
template<typename pxt, typename pyt, typename fvt>
void NiftXYFeVt<pxt,pyt,fvt>::reiterEvalUndoPrms()
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
			Term * const tValueTerm = this->mPrmTerms[1];
			if (tValueTerm->updatable())
				Term::relistEvalUndoArg(tValueTerm, this->mPrmLinks[1]);
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
template<typename pxt, typename pyt, typename fvt>
void NiftXYFeVt<pxt,pyt,fvt>::compConst()
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
			this->mValueRec->finalise(tc<pyt,fvt>::iof(mTyRec->CurrData()));
		else
			this->mValueRec->finalise(tc<pyt,fvt>::iof(mEy));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename pxt, typename pyt, typename fvt>
void NiftXYFeVt<pxt,pyt,fvt>::execAnew()
{
	WatchError
	#if ExecDnwd
	Term::performExecAnew(this->mPrmTerms[0]);
	Term::performExecAnew(this->mPrmTerms[1]);
	#endif

	if (!tc<pxt,Bll>::iof(mPxRec->CurrData()))
		this->mValueRec->initCurr(tc<pyt,fvt>::iof(mTyRec->CurrData()));
	else
		this->mValueRec->initCurr(tc<pyt,fvt>::iof(mEy));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fvt>
void NiftXYFeVt<pxt,pyt,fvt>::simulAnew()
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
		this->mValueRec->updtNext(this->mTermSys.SimulClk(),
				tc<pyt,fvt>::iof(mTyRec->NextData(this->mTermSys.SimulClk())));
	}
	else
		this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<pyt,fvt>::iof(mEy));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename pxt, typename pyt, typename fvt>
void NiftXYFeVt<pxt,pyt,fvt>::execIncr()
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
				this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
						tc<pyt,fvt>::iof(mTyRec->CurrData()));
		}
		else if (tNeedRecomp)
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<pyt,fvt>::iof(mEy));

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
				this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
						tc<pyt,fvt>::iof(mTyRec->CurrData()));
		}
		else
		{
			if (tNeedRecomp)
				this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<pyt,fvt>::iof(mEy));
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
				this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
						tc<pyt,fvt>::iof(mTyRec->CurrData()));
		}
		else if (tNeedRecomp)
				this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<pyt,fvt>::iof(mEy));
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
void NiftXYFeVt<pxt,pyt,fvt>::execBklg()
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
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
					tc<pyt,fvt>::iof(mTyRec->CurrData()));
	}
	else if (tNeedRecomp)
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<pyt,fvt>::iof(mEy));
	this->runPostExecBklg();
	CatchError
}
#endif



/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fvt>
void NiftXYFeVt<pxt,pyt,fvt>::simulIncr()
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
				this->mValueRec->updtNext(this->mTermSys.SimulClk(),
						tc<pyt,fvt>::iof(mTyRec->NextData(this->mTermSys.SimulClk())));
		}
		else if (tNeedRecomp)
				this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<pyt,fvt>::iof(mEy));
		this->runPostSimulIncr();
	}
	#endif	//SimulUpwd
	#if SimulDnwd
	Bll tNeedRecomp = false, tCondValue;

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
				tCondValue = tc<pxt,Bll>::iof(mPxRec->NextData(this->mTermSys.SimulClk()));
			}
		}
		if (!tNeedRecomp)
			tCondValue = tc<pxt,Bll>::iof(mPxRec->NextData(this->mTermSys.SimulClk()));
		if (!tCondValue)
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
					this->mValueRec->updtNext(this->mTermSys.SimulClk(),
							tc<pyt,fvt>::iof(mTyRec->NextData(this->mTermSys.SimulClk())));

			}
			#if CompLazy
			else
			{
				Term::performEmulBklg(this->mPrmTerms[1]);
				if (tNeedRecomp || mTyRec->LateDiff(this->mTermSys.EmulClk()))
					this->mValueRec->updtNext(this->mTermSys.SimulClk(),
							tc<pyt,fvt>::iof(mTyRec->LateData(this->mTermSys.EmulClk())));
			}
			#else
			else
			{
				if (tNeedRecomp)
					this->mValueRec->updtNext(this->mTermSys.SimulClk(),
							mTyRec->NextData(this->mTermSys.SimulClk()));
			}
			#endif
		}
		else if (tNeedRecomp)
				this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<pyt,fvt>::iof(mEy));
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
				tCondValue = tc<pxt,Bll>::iof(mPxRec->NextData(this->mTermSys.SimulClk()));
			}
		}
		else if (this->mBacklogPrms.tagged(0))
		{
			Term::performEmulBklg(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->LateDiff(this->mTermSys.EmulClk()))
			{
				tNeedRecomp = true;
				tCondValue = tc<pxt,Bll>::iof(mPxRec->LateData(this->mTermSys.EmulClk()));
			}
		}
		if (!tNeedRecomp)
			tCondValue = tc<pxt,Bll>::iof(mPxRec->NextData(this->mTermSys.SimulClk()));
		if (!tCondValue)
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
					this->mValueRec->updtNext(this->mTermSys.SimulClk(),
							tc<pyt,fvt>::iof(mTyRec->NextData(this->mTermSys.SimulClk())));
			}
			else //	no backlog checking, param1 is assumed to be defered.
			{
				Term::performEmulBklg(this->mPrmTerms[1]);
				if (tNeedRecomp || this->mEvalUndonePrms->tagged(1) ||
						mTyRec->LateDiff(this->mTermSys.SimulClk()))
					this->mValueRec->updtNext(this->mTermSys.SimulClk(),
							tc<pyt,fvt>::iof(mTyRec->LateData(this->mTermSys.EmulClk())));
			}
		}
		else if (tNeedRecomp)
				this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<pyt,fvt>::iof(mEy));
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
void NiftXYFeVt<pxt,pyt,fvt>::emulBklg()
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
			this->mValueRec->updtLate(this->mTermSys.EmulClk(),
				tc<pyt,fvt>::iof(mTyRec->LateData(this->mTermSys.EmulClk())));
	}
	else if (tNeedRecomp)
			this->mValueRec->updtLate(this->mTermSys.EmulClk(), tc<pyt,fvt>::iof(mEy));
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif//NiftXYFeVtIncluded
