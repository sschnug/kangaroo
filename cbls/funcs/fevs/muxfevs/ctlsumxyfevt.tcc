/*!
	@file ctlsumxyfevt.tcc
	@brief The prototype file for CtlSumXYFeVt template class.
	@details This is the prototype file for CtlSumXYFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef CtlSumXYFeVtTccIncluded
#define CtlSumXYFeVtTccIncluded



#include "cbls/funcs/fevs/muxfevt.tcc"



openKangarooSpace



/*!
	@class CtlSumXYFeVt
	@brief A template class to represent controlled sum expressions (sum_i (if x_i then y_i else 0); even positions x_i, odd positions y_i.
	@details This template class represents controlled sum expressions (sum_i (if x_i then y_i else 0; even positions x_i, odd positions y_i).
*/
template<typename pxt, typename pyt, typename fvt>
class CtlSumXYFeVt : public MuxFeVt<fvt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys, Prm * thePrms, Dim const PrmCount);	//!< Definition.

		static CtlSumXYFeVt<pxt,pyt,fvt> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static CtlSumXYFeVt<pxt,pyt,fvt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static CtlSumXYFeVt<pxt,pyt,fvt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static CtlSumXYFeVt<pxt,pyt,fvt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.

		//! @name Casting
		//! @{

		static CtlSumXYFeVt<pxt,pyt,fvt> const & cast(Term const & theTerm);		//!< Perform casting.
		static CtlSumXYFeVt<pxt,pyt,fvt> const * cast(Term const * theTerm);		//!< Perform casting.
		static CtlSumXYFeVt<pxt,pyt,fvt> & cast(Term & theTerm);					//!< Perform casting.
		static CtlSumXYFeVt<pxt,pyt,fvt> * cast(Term * theTerm);					//!< Perform casting.

		static Bll suit(Term const & theTerm);						//!< Suits casting?
		static Bll suit(Term const * theTerm);						//!< Suits casting?
		static Bll suit(Term & theTerm);							//!< Suits casting?
		static Bll suit(Term * theTerm);							//!< Suits casting?

		//! @}

	protected:
		CtlSumXYFeVt(Fss const theFss, Hdl const hdlSys,
							Prm * thePrms, Dim const PrmCount);		//!< Constructor.
		CtlSumXYFeVt const & operator =
						(CtlSumXYFeVt<pxt,pyt,fvt> const & that);	//!< Assigner.
		CtlSumXYFeVt(CtlSumXYFeVt<pxt,pyt,fvt> const & that);		//!< Duplicator.
		virtual ~CtlSumXYFeVt();									//!< Destructor.

		//! @name Deferment
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
		void runPostExecAnew();		//!< Run post execution in anew mode.
		void runPostExecIncr();		//!< Run post execution in incr mode.
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
		virtual void undoEval(Pos const thePos);//!< Perform eval undo.
		#endif

		//! @}

	private:

		b1<EvalRec<pxt> const *,kmm> 		mPxRecs;		//!< Parameter records for conditions
		b1<EvalRec<pyt> const *,kmm> 		mPyRecs;		//!< Parameter records for values.

		typedef typename DataBuff<pyt,fvt>::Type BuffType;	//!< Buffer type.
		#if SimulDnwdCache
		BuffType	cSimulValue;							//!< Simulation cache value.
		#endif
		BuffType	cExecValue;								//!< Execution cache value.
		#if CompLazy
		BuffType	cEmulValue;								//!< Emulation cache value.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fvt>
inline Bll CtlSumXYFeVt<pxt,pyt,fvt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< CtlSumXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fvt>
inline Bll CtlSumXYFeVt<pxt,pyt,fvt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< CtlSumXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fvt>
inline Bll CtlSumXYFeVt<pxt,pyt,fvt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< CtlSumXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename pxt, typename pyt, typename fvt>
inline Bll CtlSumXYFeVt<pxt,pyt,fvt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< CtlSumXYFeVt<pxt,pyt,fvt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fvt>
inline CtlSumXYFeVt<pxt,pyt,fvt> const & CtlSumXYFeVt<pxt,pyt,fvt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< CtlSumXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<CtlSumXYFeVt<pxt,pyt,fvt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fvt>
inline CtlSumXYFeVt<pxt,pyt,fvt> const * CtlSumXYFeVt<pxt,pyt,fvt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< CtlSumXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<CtlSumXYFeVt<pxt,pyt,fvt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fvt>
inline CtlSumXYFeVt<pxt,pyt,fvt> & CtlSumXYFeVt<pxt,pyt,fvt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< CtlSumXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<CtlSumXYFeVt<pxt,pyt,fvt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename pxt, typename pyt, typename fvt>
inline CtlSumXYFeVt<pxt,pyt,fvt> * CtlSumXYFeVt<pxt,pyt,fvt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< CtlSumXYFeVt<pxt,pyt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<CtlSumXYFeVt<pxt,pyt,fvt> *>(theTerm);
	CatchError
}



/*!
	Refer to an if-then term.
*/
template<typename pxt, typename pyt, typename fvt>
inline CtlSumXYFeVt<pxt,pyt,fvt> &
CtlSumXYFeVt<pxt,pyt,fvt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to an if-then term.
*/
template<typename pxt, typename pyt, typename fvt>
inline CtlSumXYFeVt<pxt,pyt,fvt> *
CtlSumXYFeVt<pxt,pyt,fvt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an if-then term.
*/
template<typename pxt, typename pyt, typename fvt>
inline CtlSumXYFeVt<pxt,pyt,fvt> const &
CtlSumXYFeVt<pxt,pyt,fvt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to an if-then term.
*/
template<typename pxt, typename pyt, typename fvt>
inline CtlSumXYFeVt<pxt,pyt,fvt> const *
CtlSumXYFeVt<pxt,pyt,fvt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template<typename pxt, typename pyt, typename fvt>
inline CtlSumXYFeVt<pxt,pyt,fvt>::~CtlSumXYFeVt()
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
inline void CtlSumXYFeVt<pxt,pyt,fvt>::runPostExecAnew()
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
inline void CtlSumXYFeVt<pxt,pyt,fvt>::runPostExecIncr()
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
inline void CtlSumXYFeVt<pxt,pyt,fvt>::runPostExecBklg()
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
inline void CtlSumXYFeVt<pxt,pyt,fvt>::runPostSimulAnew()
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
inline void CtlSumXYFeVt<pxt,pyt,fvt>::runPostSimulIncr()
{
	WatchError
	this->clearSimulChgdPrms();
	if (this->mValueRec->NextDiff(this->mTermSys.SimulClk()))
		this->scheduleSimulIncrArgs();
	CatchError
}
#endif //SimulUpwd



/*!
	Define an if-then expression.
*/
template<typename pxt, typename pyt, typename fvt>
Hdl CtlSumXYFeVt<pxt,pyt,fvt>::def(Fss const theFss, Hdl const hdlSys,
				Prm * thePrms, Dim const PrmCount)
{
	WatchError
	Wchk(PrmCount < 2 || PrmCount > MaxDim) Wtxt(eParamCount2(2, MaxDim));
	Warn(PrmCount % 2, eEvenParamsRequired);

	CtlSumXYFeVt<pxt,pyt,fvt> * tFeV =
		new CtlSumXYFeVt<pxt,pyt,fvt>(theFss, hdlSys, thePrms, PrmCount);

	Hdl const tHdl = tFeV->defSysFunc();
	if (tHdl != InvHdl) { delete tFeV; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<pyt> const & tPytTbl = EvalTbl<pyt>::refc(hdlSys);
	EvalTbl<fvt> & tFvtTbl = EvalTbl<fvt>::refm(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFeV->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFeV->mPrmSpecs;

	for (Pos sPos = 0, tPos = 0; tPos < PrmCount; ++sPos, ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos], tPrmSpecs[tPos]);
		tFeV->mPxRecs[sPos] = tPxtTbl.ptrcEvalRec(tPxLoc);

		++tPos;

		Loc const tPyLoc = getPyLoc(theFss, tPrmTerms[tPos], tPrmSpecs[tPos]);
		tFeV->mPyRecs[sPos] = tPytTbl.ptrcEvalRec(tPyLoc);
	}

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
CtlSumXYFeVt<pxt,pyt,fvt>::CtlSumXYFeVt(Fss const theFss, Hdl const hdlSys, Prm * thePrms,
		Dim const PrmCount) : MuxFeVt<fvt>(hdlSys, PrmCount), mPxRecs(PrmCount >> 1), mPyRecs(PrmCount >> 1)
{
	WatchError
	this->setTermCls(TermStub< CtlSumXYFeVt<pxt,pyt,fvt> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Ordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template<typename pxt, typename pyt, typename fvt>
CtlSumXYFeVt<pxt,pyt,fvt>::CtlSumXYFeVt(CtlSumXYFeVt<pxt,pyt,fvt> const & that) :
	MuxFeVt<fvt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename pxt, typename pyt, typename fvt>
CtlSumXYFeVt<pxt,pyt,fvt> const & CtlSumXYFeVt<pxt,pyt,fvt>::operator =
		(CtlSumXYFeVt<pxt,pyt,fvt> const & that)
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
void CtlSumXYFeVt<pxt,pyt,fvt>::notifyDeferedPrms()
{
	WatchError
	//	only conditional terms are defered.
	for (Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); tPos +=2)
	{
		Term * const tPrmTerm = this->mPrmTerms[tPos];
		if (tPrmTerm->computable())	//	not Updatable to exclude vars
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
template<typename pxt, typename pyt, typename fvt>
void CtlSumXYFeVt<pxt,pyt,fvt>::notifyEnforcedPrms()
{
	WatchError
	//	only conditional terms are enforced.
	for (Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); tPos +=2)
	{
		Term * const tPrmTerm = this->mPrmTerms[tPos];
		if (tPrmTerm->computable())	//	not Updatable to exclude vars
			Func::setEnforcement(Func::cast(tPrmTerm));
	}
	CatchError
}
#endif //CompLazyHalf



#if CompLazy
/*!
	Call parameters to list for eval undo.
*/
template<typename pxt, typename pyt, typename fvt>
void CtlSumXYFeVt<pxt,pyt,fvt>::reinitEvalUndoPrms()
{
	WatchError
	//	no mode anew mode checking because deferment would happen even
	//	when incr mode and still need this method to run.
	Warn(!this->mEvalUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (this->defered())
	#endif
	{
		for(Pos sPos = 0, tPos = 0; tPos < this->mPrmTerms.itemCount(); ++sPos, ++tPos)
		{
			Term * const tCondTerm = this->mPrmTerms[tPos];
			if (tCondTerm->updatable())	//	include vars
				Term::relistEvalUndoArg(tCondTerm, this->mPrmLinks[tPos]);

			++tPos;

			if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
			{
				Term * const tValueTerm = this->mPrmTerms[tPos];
				if (tValueTerm->updatable())	//	include vars
					Term::relistEvalUndoArg(tValueTerm, this->mPrmLinks[tPos]);
			}
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
void CtlSumXYFeVt<pxt,pyt,fvt>::reiterEvalUndoPrms()
{
	WatchError
	Warn(!this->mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);
	Warn(!this->mEvalUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (this->defered())
	#endif
	{
		for(Pos sPos = 0, tPos = 0; tPos < this->mPrmTerms.itemCount(); ++sPos, ++tPos)
		{
			Term * const tCondTerm = this->mPrmTerms[tPos];
			if (tCondTerm->updatable())
				Term::relistEvalUndoArg(tCondTerm, this->mPrmLinks[tPos]);

			++tPos;

			if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
			{
				Term * const tValueTerm = this->mPrmTerms[tPos];
				if (tValueTerm->updatable())
					Term::relistEvalUndoArg(tValueTerm, this->mPrmLinks[tPos]);
			}
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
void CtlSumXYFeVt<pxt,pyt,fvt>::compConst()
{
	WatchError
	if (!this->updatable())
	{
		cExecValue = 0;
		for(Pos sPos = 0; sPos < mPxRecs.itemCount(); ++sPos)
			if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
				cExecValue += mPyRecs[sPos]->CurrData();
		this->mValueRec->finalise(tc<BuffType, fvt>::iof(cExecValue));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename pxt, typename pyt, typename fvt>
void CtlSumXYFeVt<pxt,pyt,fvt>::execAnew()
{
	WatchError
	cExecValue = 0;
	#if ExecDnwd
	for(Pos sPos = 0, tPos = 0; tPos < this->mPrmTerms.itemCount(); ++sPos, ++tPos)
	{
		Term::performExecAnew(this->mPrmTerms[tPos]);
		++tPos;
		Term::performExecAnew(this->mPrmTerms[tPos]);
		if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
			cExecValue += mPyRecs[sPos]->CurrData();
	}
	#endif
	#if ExecUpwd
	for(Pos sPos = 0; sPos < mPxRecs.itemCount(); ++sPos)
		if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
			cExecValue += mPyRecs[sPos]->CurrData();
	#endif
	this->mValueRec->initCurr(tc<BuffType, fvt>::iof(cExecValue));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fvt>
void CtlSumXYFeVt<pxt,pyt,fvt>::simulAnew()
{
	WatchError
	BuffType tSimulValue = 0;
	#if SimulDnwd
	for(Pos sPos = 0, tPos = 0; tPos < this->mPrmTerms.itemCount(); ++sPos, ++tPos)
	{
		Term::performSimulAnew(this->mPrmTerms[tPos]);
		++tPos;
		if (tc<pxt,Bll>::iof(mPxRecs[sPos]->NextData(this->mTermSys.SimulClk())))
		{
			Term::performSimulAnew(this->mPrmTerms[tPos]);
			tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());
		}
	}
	#endif
	#if SimulUpwd
	for(Pos sPos = 0; sPos < this->mPxRecs.itemCount(); ++sPos)
		if (tc<pxt,Bll>::iof(mPxRecs[sPos]->NextData(this->mTermSys.SimulClk())))
			tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());
	#endif
	this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType, fvt>::iof(tSimulValue));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



#if CompLazy
/*!
	Perform eval undo for the parameter.
*/
template <typename pxt, typename pyt, typename fvt>
void CtlSumXYFeVt<pxt,pyt,fvt>::undoEval(Pos const thePos)
{
	WatchError
	Pos sPos = thePos >> 1;
	if (thePos & 1)	//	data
	{
		if (!this->mEvalUndonePrms->tagged(thePos - 1) &&
				tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
			cExecValue -= mPyRecs[sPos]->PrevData(this->mTermSys.ExecClk());
	}
	else	// condition
	{
		if (!this->mEvalUndonePrms->tagged(thePos + 1) &&
				tc<pxt,Bll>::iof(mPxRecs[sPos]->PrevData(this->mTermSys.ExecClk())))
			cExecValue -= mPyRecs[sPos]->CurrData();
	}
	CatchError
}
#endif	//CompLazy



/*!
	Compute the term in execution mode.
*/
template<typename pxt, typename pyt, typename fvt>
void CtlSumXYFeVt<pxt,pyt,fvt>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		for(Idx tIdx = 0; tIdx < this->mExecChgdPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mExecChgdPrms.serial(tIdx);
			//	avoid double counting when both cond and data are modified.
			if (tPos & 1) && this->mExecChgdPrms.tagged(tPos - 1)) continue;
			Pos const sPos = tPos >> 1;
			if (mPxRecs[sPos]->PrevDiff(this->mTermSys.ExecClk()))
			{
				if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
					cExecValue += tPyRecs[sPos]->CurrData();
				else
					cExecValue -= tPyRecs[sPos]->PrevData(this->mTermSys.ExecClk());
			}
			else if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
			{
				EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
				if (mPyRec->PrevDiff(this->mTermSys.ExecClk()))
					cExecValue += tPyRec->CurrBuff - tPyRec->PrevBuff;
			}
		}
		this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fvt>::iof(cExecValue));
		this->runPostExecIncr();
	}
	#endif	//ExecUpwd
	#if ExecDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//CompLazy
		if (this->needExecCandComp()) this->markCandParams();
		if (this->mBlkCandPrms->itemCount())
		{
			for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
			{
				Pos tPos = this->mBlkCandPrms->item(tIdx), sPos = tPos >> 1;
				if (tPos & 1)	//	data
				{
					//(if cond too, avoid double counting)
					if (this->mLblCandPrms.tagged(tPos - 1)) continue;
					if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
					{
						Term::performExecIncr(this->mPrmTerms[tPos]);
						EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
						if (tPyRec->PrevDiff(this->mTermSys.ExecClk()))
							cExecValue += tPyRec->CurrBuff - tPyRec->PrevBuff;
					}
					#if !CompLazy
					else Term::performExecIncr(this->mPrmTerms[tPos]);
					#endif
					continue;
				}
				//	condition
				Term::performExecIncr(this->mPrmTerms[tPos]);
				EvalRec<pxt> const * tPxRec = mPxRecs[sPos];
				if (tc<pxt,Bll>::iof(tPxRec->CurrData()))
				{
					if (this->mLblCandPrms.tagged(++tPos))
						Term::performExecIncr(this->mPrmTerms[tPos]);
					#if CompLazy
					else Term::performExecBklg(this->mPrmTerms[tPos]);
					#endif
					EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
					if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
						cExecValue += tPyRec->CurrData();
					else if (tPyRec->PrevDiff(this->mTermSys.ExecClk()))
						cExecValue += tPyRec->CurrBuff - tPyRec->PrevBuff;
				}
				else
				{
					#if !CompLazy
					if (this->mLblCandPrms.tagged(++tPos))
						Term::performExecIncr(this->mPrmTerms[tPos]);
					#endif
					if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
						cExecValue -= mPyRecs[sPos]->PrevData(this->mTermSys.ExecClk());
				}
			}
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType, fvt>::iof(cExecValue));
		}
	#if CompLazy
	}
	else
	{
		if (this->needExecCandComp()) this->markCandParams();
		for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
		{
			Pos tPos = this->mBlkCandPrms->item(tIdx), sPos = tPos >> 1;
			if (tPos & 1)	//	data
			{
				//(if cond too, avoid double counting)
				if (this->mLblCandPrms.tagged(tPos - 1)) continue;
				if (this->mBacklogPrms.tagged(tPos - 1)) continue;

				if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
				{
					Term::performExecIncr(this->mPrmTerms[tPos]);
					EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
					if (this->mEvalUndonePrms->tagged(tPos))
						cExecValue += tPyRec->CurrData();
					else if (tPyRec->PrevDiff(this->mTermSys.ExecClk()))
						cExecValue += tPyRec->CurrBuff - tPyRec->PrevBuff;
				}
				continue;
			}
			//	condition
			Term::performExecIncr(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[sPos];
			if (tc<pxt,Bll>::iof(tPxRec->CurrData()))
			{
				if (this->mLblCandPrms.tagged(++tPos))
					Term::performExecIncr(this->mPrmTerms[tPos]);
				else
					Term::performExecBklg(this->mPrmTerms[tPos]);

				EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
				if (tPxRec->PrevDiff(this->mTermSys.ExecClk()) ||
						this->mEvalUndonePrms->tagged(tPos) ||
						this->mEvalUndonePrms->tagged(tPos - 1))
					cExecValue += tPyRec->CurrData();
				else if (tPyRec->PrevDiff(this->mTermSys.ExecClk()))
					cExecValue += tPyRec->CurrBuff - tPyRec->PrevBuff;
			}
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()) &&
					!this->mEvalUndonePrms->tagged(tPos) &&
					!this->mEvalUndonePrms->tagged(tPos + 1))
				cExecValue -= mPyRecs[sPos]->PrevData(this->mTermSys.ExecClk());
		}

		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos tPos = this->mBacklogPrms.serial(tIdx), sPos = tPos >> 1;
			if (this->mLblCandPrms.tagged(tPos)) continue;
			if (tPos & 1)	//	data
			{
				//(if cond too, avoid double counting)
				if (this->mLblCandPrms.tagged(tPos - 1)) continue;
				if (this->mBacklogPrms.tagged(tPos - 1)) continue;
				if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
				{
					Term::performExecBklg(this->mPrmTerms[tPos]);
					EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
					if (this->mEvalUndonePrms->tagged(tPos))
						cExecValue += tPyRec->CurrData();
					else if (tPyRec->PrevDiff(this->mTermSys.ExecClk()))
						cExecValue += tPyRec->CurrBuff - tPyRec->PrevBuff;
				}
				continue;
			}
			//	condition
			if (this->mLblCandPrms.tagged(tPos + 1)) continue;
			Term::performExecBklg(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[sPos];
			if (tc<pxt,Bll>::iof(tPxRec->CurrData()))
			{
				Term::performExecBklg(this->mPrmTerms[++tPos]);
				EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
				if (tPxRec->PrevDiff(this->mTermSys.ExecClk()) ||
						this->mEvalUndonePrms->tagged(tPos - 1) ||
						this->mEvalUndonePrms->tagged(tPos))
					cExecValue += tPyRec->CurrData();
				else if (tPyRec->PrevDiff(this->mTermSys.ExecClk()))
					cExecValue += tPyRec->CurrBuff - tPyRec->PrevBuff;
			}
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()) &&
					!this->mEvalUndonePrms->tagged(tPos) &&
					!this->mEvalUndonePrms->tagged(tPos + 1))
				cExecValue -= mPyRecs[sPos]->PrevData(this->mTermSys.ExecClk());
		}

		this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType, fvt>::iof(cExecValue));
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
void CtlSumXYFeVt<pxt,pyt,fvt>::execBklg()
{
	WatchError
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos tPos = this->mBacklogPrms.serial(tIdx), sPos = tPos >> 1;
		if (tPos & 1)	//	data
		{
			//(if cond too, avoid double counting)
			if (this->mBacklogPrms.tagged(tPos - 1)) continue;
			if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
			{
				Term::performExecBklg(this->mPrmTerms[tPos]);
				EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
				if (this->mEvalUndonePrms->tagged(tPos))
					cExecValue += tPyRec->CurrData();
				else if (tPyRec->PrevDiff(this->mTermSys.ExecClk()))
					cExecValue += tPyRec->CurrBuff - tPyRec->PrevBuff;
			}
			continue;
		}
		//	condition
		Term::performExecBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[sPos];
		if (tc<pxt,Bll>::iof(tPxRec->CurrData()))
		{
			Term::performExecBklg(this->mPrmTerms[++tPos]);
			EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
			if (tPxRec->PrevDiff(this->mTermSys.ExecClk()) ||
					this->mEvalUndonePrms->tagged(tPos - 1) ||
					this->mEvalUndonePrms->tagged(tPos))
				cExecValue += tPyRec->CurrData();
			else if (tPyRec->PrevDiff(this->mTermSys.ExecClk()))
				cExecValue += tPyRec->CurrBuff - tPyRec->PrevBuff;
		}
		else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()) &&
				!this->mEvalUndonePrms->tagged(tPos) &&
				!this->mEvalUndonePrms->tagged(tPos + 1))
			cExecValue -= mPyRecs[sPos]->PrevData(this->mTermSys.ExecClk());
	}
	this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType, fvt>::iof(cExecValue));
	this->runPostExecBklg();
	CatchError
}
#endif



/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fvt>
void CtlSumXYFeVt<pxt,pyt,fvt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		BuffType tSimulValue = cExecValue;
		for(Idx tIdx = 0; tIdx < this->mSimulChgdPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mSimulChgdPrms.serial(tIdx);
			//	avoid double counting when both cond and data are modified.
			if ((tPos & 1) && this->mSimulChgdPrms.tagged(tPos - 1))
				continue;
			Pos const sPos = tPos >> 1;
			EvalRec<pxt> const * tPxRec = mPxRecs[sPos];
			if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
			{
				if (tc<pxt,Bll>::iof(tPxRec->CurrData()))
					tSimulValue -= tPyRecs[sPos]->CurrData();
				else
					tSimulValue += tPyRecs[sPos]->NextData(this->mTermSys.SimulClk());
			}
			else if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
			{
				EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
				if (mPyRec->NextDiff(this->mTermSys.SimulClk()))
					tSimulValue += tPyRec->NextBuff - tPyRec->PrevBuff;
			}
		}
		this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fvt>::iof(tSimulValue));
		this->runPostSimulIncr();
	}
	#endif	//SimulUpwd
	#if SimulDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//CompLazy
		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->markFlexiParams();
		#endif
		#if SimulFixed
		if (this->needSimulFixedComp()) this->markFixedParams();
		#endif

		#if SimulFixed
		if (this->needSimulCacheComp())
		{
			cSimulValue = cExecValue;
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				if ((tPos & 1) && this->mLblFixedPrms.tagged(tPos - 1))
				{	//	undo when both of them are fixed and the pos is data.
					//	We cannot undo when both are fixed, because non-fixed
					//	cond or data might not be modified in the flexi.
					//	We want to cache only those that must be undone.
					Pos sPos = tPos >> 1;
					if (mPxRecs[sPos]->CurrData())
						cSimulValue -= mPyRecs[sPos]->CurrData();
				}
			}
		}
		#endif//SimulFixed

		#if SimulFixedFlexi
		if (this->mBlkFixedPrms->itemCount() || this->mBlkFlexiPrms->itemCount())
		#elif SimulFixedOnly
		if (this->mBlkFixedPrms->itemCount())
		#elif SimulFlexiOnly
		if (this->mBlkFlexiPrms->itemCount())
		#endif
		{
			#if SimulFixed
			BuffType tSimulValue = cSimulValue;
			#else
			BuffType tSimulValue = cExecValue;
			#endif

			#if SimulFixed
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos tPos = this->mBlkFixedPrms->item(tIdx);
				if ((tPos & 1))	//	data
				{
					//	if control is also modifed in flexi or fixed
					//	just skip this. this will be handled there.
					#if SimulFlexi
					if (this->mLblFlexiPrms->tagged(tPos - 1))
						continue;
					#endif
					if (this->mLblFixedPrms.tagged(tPos - 1))
						continue;
					Pos sPos = tPos >> 1;
					if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
					{
						Term::performSimulIncr(this->mPrmTerms[tPos]);
						EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
						if (tPyRec->NextDiff(this->mTermSys.SimulClk()))
							tSimulValue += tPyRec->NextBuff - tPyRec->CurrBuff;
					}
					continue;
				}
				//	condition below
				#if SimulFlexi
				if (!this->mLblFixedPrms.tagged(tPos + 1) &&
						this->mLblFlexiPrms->tagged(tPos + 1))
					continue;
				#endif
				//	if data either fixed or not flexi then process cond below
				Pos sPos = tPos >> 1;
				Term::performSimulIncr(this->mPrmTerms[tPos]);
				EvalRec<pxt> const * tPxRec = mPxRecs[sPos];

				if (tPxRec->NextDiff(this->mTermSys.SimulClk()))	//	this is a change
				{
					if (tc<pxt,Bll>::iof(tPxRec->NextBuff))	//	new cond is true
					{
						if (this->mLblFixedPrms.tagged(++tPos))	//	if data is fixed
						{
							Term::performSimulIncr(this->mPrmTerms[tPos]);
							tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());
						}
						else
						#if CompLazy
						{
							Term::performEmulBklg(this->mPrmTerms[tPos]);
							tSimulValue += mPyRecs[sPos]->LateData(this->mTermSys.EmulClk());
						}
						#else
							tSimulValue += mPyRecs[sPos]->CurrData();
						#endif
					}
					else // new cond is false
					{
						if (!this->mLblFixedPrms.tagged(++tPos))
							//	this was active but no backlog, so deduct current
							tSimulValue -= mPyRecs[sPos]->CurrData();
					}
				}
				else if (tc<pxt,Bll>::iof(tPxRec->CurrData()))
				{
					if (this->mLblFixedPrms.tagged(++tPos))
					{	//	already undone in cache
						Term::performSimulIncr(this->mPrmTerms[tPos]);
						tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());
					}
					#if CompLazy
					else
					{
						Term::performEmulBklg(this->mPrmTerms[tPos]);
						EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
						if (tPyRec->LateDiff(this->mTermSys.EmulClk()))
							tSimulValue += tPyRec->LateBuff - tPyRec->CurrBuff;
					}
					#endif
				}
			}
			#endif

			#if SimulFlexi
			for(Idx tIdx = 0; tIdx < this->mBlkFlexiPrms->itemCount(); ++tIdx)
			{
				Pos tPos = this->mBlkFlexiPrms->item(tIdx);

				if (tPos & 1)	//	data
				{
					if (this->mLblFlexiPrms->tagged(tPos - 1))
						continue;
					//	if cond is flexi skip else process below
					//	no cache interaction involves here.
					#if SimulFixed
					if (this->mLblFixedPrms.tagged(tPos - 1))
					{
						Term::performSimulIncr(this->mPrmTerms[tPos - 1]);
						Pos sPos = tPos >> 1;
						EvalRec<pxt> const * tPxRec = mPxRecs[sPos];

						if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
						{
							if (tc<pxt,Bll>::iof(tPxRec->NextBuff))
							{
								Term::performSimulIncr(this->mPrmTerms[tPos]);
								tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());
							}
							else
								tSimulValue -= mPyRecs[sPos]->CurrData();
						}
						else if (tc<pxt,Bll>::iof(tPxRec->CurrData()))
						{
							Term::performSimulIncr(this->mPrmTerms[tPos]);
							EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
							if (tPyRec->NextDiff(this->mTermSys.SimulClk()))
								tSimulValue += tPyRec->NextBuff - tPyRec->CurrBuff;
						}
					}
					else
					#endif
					{
						Pos sPos = tPos >> 1;
						if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
						{
							Term::performSimulIncr(this->mPrmTerms[tPos]);
							EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
							if (tPyRec->NextDiff(this->mTermSys.SimulClk()))
								tSimulValue += tPyRec->NextBuff - tPyRec->CurrBuff;
						}
					}
					continue;
				}

				Term::performSimulIncr(this->mPrmTerms[tPos]);
				Pos sPos = tPos >> 1;
				EvalRec<pxt> const * tPxRec = mPxRecs[sPos];
				if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
				{
					if (tc<pxt,Bll>::iof(mPxRecs[sPos]->NextBuff))
					{
						#if SimulFixed
						if (this->mLblFixedPrms.tagged(tPos + 1))
						{
							Term::performSimulIncr(this->mPrmTerms[++tPos]);
							tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
						}
						else
						#endif
						if (this->mLblFlexiPrms->tagged(tPos + 1))
						{
							Term::performSimulIncr(this->mPrmTerms[++tPos]);
							tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
						}
						else
						#if CompLazy
						{
							Term::performEmulBklg(this->mPrmTerms[++tPos]);
							tSimulValue += mPyRecs[sPos]->LateData(this->mTermSys.EmulClk());	//not LateBuff!
						}
						#else
							tSimulValue += mPyRecs[sPos]->CurrData();
						#endif
					}
					else
						tSimulValue -= mPyRecs[sPos]->CurrData();
				}
				else if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
				{
					#if SimulFixed
					if (this->mLblFixedPrms.tagged(tPos + 1))
					{
						Term::performSimulIncr(this->mPrmTerms[++tPos]);
						EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
						if (tPyRec->NextDiff(this->mTermSys.SimulClk()))
							tSimulValue += tPyRec->NextBuff - tPyRec->CurrBuff;
					}
					else
					#endif
					if (this->mLblFlexiPrms->tagged(tPos + 1))
					{
						Term::performSimulIncr(this->mPrmTerms[++tPos]);
						EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
						if (tPyRec->NextDiff(this->mTermSys.SimulClk()))
							tSimulValue += tPyRec->NextBuff - tPyRec->CurrBuff;
					}
					#if CompLazy
					else
					{
						Term::performEmulBklg(this->mPrmTerms[tPos]);
						EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
						if (tPyRec->LateDiff(this->mTermSys.EmulClk()))
							tSimulValue += tPyRec->LateBuff - tPyRec->CurrBuff;
					}
					#endif
				}
			}
			#endif

			this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType, fvt>::iof(tSimulValue));
		}
	#if CompLazy
	}
	else	//	backlog
	{
		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->markFlexiParams();
		#endif
		#if SimulFixed
		if (this->needSimulFixedComp()) this->markFixedParams();
		#endif

		if (this->needSimulCacheComp())
		{
			if (!this->chgdEmulClk())
			{
				cSimulValue = cEmulValue;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					if ((tPos & 1) && this->mLblFixedPrms.tagged(tPos - 1))
					{
						//	Undo when both of them are fixed and the pos is data
						Pos sPos = tPos >> 1;
						if (tc<pxt,Bll>::iof(mPxRecs[sPos]->LateData(this->mTermSys.EmulClk())))
							cSimulValue -= mPyRecs[sPos]->LateData(this->mTermSys.EmulClk());
					}
				}
				#endif//SimulFixed
			}
			else
			{
				cSimulValue = cExecValue;
				for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
				{
					Pos tPos = this->mBacklogPrms.serial(tIdx);
					if ((tPos & 1))
					{
						if (this->mBacklogPrms.tagged(tPos - 1)) continue;
						if (tc<pxt,Bll>::iof(this->mPxRecs[tPos - 1]->CurrData()))
						{
							Term::performEmulBklg(this->mPrmTerms[tPos]);
							Pos sPos = tPos >> 1;
							EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
							if (this->mEvalUndonePrms->tagged(tPos))
								cSimulValue += tPyRec->LateData(this->mTermSys.EmulClk());
							else if (tPyRec->LateDiff(this->mTermSys.EmulClk()))
								cSimulValue += tPyRec->LateBuff - tPyRec->CurrBuff;
						}
					}
					else	//	condition
					{
						Term::performEmulBklg(this->mPrmTerms[tPos]);
						Pos sPos = tPos >> 1;
						EvalRec<pxt> const * tPxRec = mPxRecs[sPos];
						if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
						{
							if (tc<pxt,Bll>::iof(tPxRec->LateBuff))
							{
								Term::performEmulBklg(this->mPrmTerms[++tPos]);
								EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
								cSimulValue += tPyRec->LateData(this->mTermSys.EmulClk());
							}
							else // false
							{
//								Term::performEmulBklg(this->mPrmTerms[++tPos]);
								EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
								if (!this->mEvalUndonePrms->tagged(tPos) &&
											!this->mEvalUndonePrms->tagged(tPos - 1))
									cSimulValue -= tPyRec->CurrData();
							}
						}
						else if (tc<pxt,Bll>::iof(tPxRec->CurrData()))
						{
							Term::performEmulBklg(this->mPrmTerms[++tPos]);
							EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
							if (this->mEvalUndonePrms->tagged(tPos) ||
										this->mEvalUndonePrms->tagged(tPos - 1))
								cSimulValue += tPyRec->LateData(this->mTermSys.EmulClk());
							else if (tPyRec->LateDiff(this->mTermSys.EmulClk()))
								cSimulValue += tPxRec->LateBuff - tPxRec->CurrBuff;
						}
					}
				}
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					if ((tPos & 1) && this->mLblFixedPrms.tagged(tPos - 1))
					{
						Pos sPos = tPos >> 1;
						if (tc<pxt,Bll>::iof(mPxRecs[sPos]->LateData(this->mTermSys.EmulClk())))
							cSimulValue -= mPyRecs[sPos]->LateData(this->mTermSys.EmulClk());
//						//	Undo when both of them are fixed and do it when data
//						if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()) &&
//								!this->mEvalUndonePrms->tagged(tPos) &&
//								!this->mEvalUndonePrms->tagged(tPos - 1))
//							cSimulValue -= mPyRecs[sPos]->CurrData();
					}
				}
				#endif //SimulFixed
			}
		}

		#if SimulFixedFlexi
		if (this->mBlkFixedPrms->itemCount() || this->mBlkFlexiPrms->itemCount())
		#elif SimulFixedOnly
		if (this->mBlkFixedPrms->itemCount())
		#elif SimulFlexiOnly
		if (this->mBlkFlexiPrms->itemCount())
		#endif
		{
			#if SimulFixed
			BuffType tSimulValue = cSimulValue;
			#else
			BuffType tSimulValue = cExecValue;
			#endif

			#if SimulFixed
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos tPos = this->mBlkFixedPrms->item(tIdx);
				if ((tPos & 1))	//	data
				{
					//	if control is also modifed in flexi or fixed
					//	just skip this. this will be handled there.
					#if SimulFlexi
					if (this->mLblFlexiPrms->tagged(tPos - 1))
						continue;
					#endif
					if (this->mLblFixedPrms.tagged(tPos - 1))
						continue;
					Pos sPos = tPos >> 1;
					if (tc<pxt,Bll>::iof(mPxRecs[sPos]->LateData(this->mTermSys.EmulClk())))
					{
						Term::performSimulIncr(this->mPrmTerms[tPos]);
						EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
						if (tPyRec->LtNxDiff(this->mTermSys.EmulClk(), this->mTermSys.SimulClk()))
							tSimulValue += tPyRec->NextData(this->mTermSys.SimulClk()) -
									tPyRec->LateData(this->mTermSys.SimulClk());
					}
					continue;
				}
				//	condition below
				#if SimulFlexi
				if (!this->mLblFixedPrms.tagged(tPos + 1) &&
						this->mLblFlexiPrms->tagged(tPos + 1))
					continue;
				#endif
				//	if data either fixed or not flexi then process cond below
				Pos sPos = tPos >> 1;
				Term::performSimulIncr(this->mPrmTerms[tPos]);
				EvalRec<pxt> const * tPxRec = mPxRecs[sPos];

				if (tPxRec->LtNxDiff(this->mTermSys.EmulClk(), this->mTermSys.SimulClk()))	//	this is a change
				{
					if (tc<pxt,Bll>::iof(tPxRec->NextData(this->mTermSys.SimulClk())))	//	new cond is true
					{
						if (this->mLblFixedPrms.tagged(++tPos))	//	if data is fixed
						{
							Term::performSimulIncr(this->mPrmTerms[tPos]);
							tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());
						}
						else
						{
							Term::performEmulBklg(this->mPrmTerms[tPos]);
							tSimulValue += mPyRecs[sPos]->LateData(this->mTermSys.EmulClk());
						}
					}
					else // new cond is false
					{
						if (!this->mLblFixedPrms.tagged(++tPos))
							//	this was active but no backlog, so deduct current
							tSimulValue -= mPyRecs[sPos]->LateData(this->mTermSys.EmulClk());
					}
				}
				else if (tc<pxt,Bll>::iof(tPxRec->LateData(this->mTermSys.EmulClk())))
				{
					if (this->mLblFixedPrms.tagged(++tPos))
					{	//	already undone in cache
						Term::performSimulIncr(this->mPrmTerms[tPos]);
						tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());
					}
				}
			}
			#endif

			#if SimulFlexi
			for(Idx tIdx = 0; tIdx < this->mBlkFlexiPrms->itemCount(); ++tIdx)
			{
				Pos tPos = this->mBlkFlexiPrms->item(tIdx);

				if (tPos & 1)	//	data
				{
					if (this->mLblFlexiPrms->tagged(tPos - 1))
						continue;
					//	if cond is flexi skip else process below
					//	no cache interaction involves here.
					#if SimulFixed
					if (this->mLblFixedPrms.tagged(tPos - 1))
					{
						Term::performSimulIncr(this->mPrmTerms[tPos - 1]);
						Pos sPos = tPos >> 1;
						EvalRec<pxt> const * tPxRec = mPxRecs[sPos];

						if (tPxRec->LtNxDiff(this->mTermSys.EmulClk(), this->mTermSys.SimulClk()))
						{
							if (tc<pxt,Bll>::iof(tPxRec->NextData(this->mTermSys.SimulClk())))
							{
								Term::performSimulIncr(this->mPrmTerms[tPos]);
								tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());
							}
							else
								tSimulValue -= mPyRecs[sPos]->LateData(this->mTermSys.EmulClk());
						}
						else if (tc<pxt,Bll>::iof(tPxRec->LateData(this->mTermSys.EmulClk())))
						{
							Term::performSimulIncr(this->mPrmTerms[tPos]);
							EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
							if (tPyRec->LtNxDiff(this->mTermSys.EmulClk(), this->mTermSys.SimulClk()))
								tSimulValue += tPyRec->NextData(this->mTermSys.SimulClk()) -
												tPyRec->LateData(this->mTermSys.EmulClk());
						}
					}
					else
					#endif
					{
						Pos sPos = tPos >> 1;
						if (tc<pxt,Bll>::iof(mPxRecs[sPos]->LateData(this->mTermSys.EmulClk())))
						{
							Term::performSimulIncr(this->mPrmTerms[tPos]);
							EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
							if (tPyRec->LtNxDiff(this->mTermSys.EmulClk(), this->mTermSys.SimulClk()))
								tSimulValue += tPyRec->NextData(this->mTermSys.SimulClk()) -
										tPyRec->LateData(this->mTermSys.EmulClk());
						}
					}
					continue;
				}

				Term::performSimulIncr(this->mPrmTerms[tPos]);
				Pos sPos = tPos >> 1;
				EvalRec<pxt> const * tPxRec = mPxRecs[sPos];
				if (tPxRec->LtNxDiff(this->mTermSys.SimulClk(), this->mTermSys.SimulClk()))
				{
					if (tc<pxt,Bll>::iof(mPxRecs[sPos]->NextData(this->mTermSys.SimulClk())))
					{
						#if SimulFixed
						if (this->mLblFixedPrms.tagged(tPos + 1))
						{
							Term::performSimulIncr(this->mPrmTerms[++tPos]);
							tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
						}
						else
						#endif
						if (this->mLblFlexiPrms->tagged(tPos + 1))
						{
							Term::performSimulIncr(this->mPrmTerms[++tPos]);
							tSimulValue += mPyRecs[sPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
						}
						else
						{
							Term::performEmulBklg(this->mPrmTerms[++tPos]);
							tSimulValue += mPyRecs[sPos]->LateData(this->mTermSys.EmulClk());	//not LateBuff!
						}
					}
					else
						tSimulValue -= mPyRecs[sPos]->LateData(this->mTermSys.EmulClk());
				}
				else if (tc<pxt,Bll>::iof(mPxRecs[sPos]->LateData(this->mTermSys.EmulClk())))
				{
					#if SimulFixed
					if (this->mLblFixedPrms.tagged(tPos + 1))
					{
						Term::performSimulIncr(this->mPrmTerms[++tPos]);
						EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
						if (tPyRec->LtNxDiff(this->mTermSys.EmulClk(), this->mTermSys.SimulClk()))
							tSimulValue += tPyRec->NextData(this->mTermSys.SimulClk()) -
									tPyRec->LateData(this->mTermSys.EmulClk());
					}
					else
					#endif
					if (this->mLblFlexiPrms->tagged(tPos + 1))
					{
						Term::performSimulIncr(this->mPrmTerms[++tPos]);
						EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
						if (tPyRec->LtNxDiff(this->mTermSys.EmulClk(), this->mTermSys.SimulClk()))
							tSimulValue += tPyRec->NextData(this->mTermSys.SimulClk()) -
									tPyRec->LateData(this->mTermSys.EmulClk());
					}
				}
			}
			#endif

			this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType, fvt>::iof(tSimulValue));
		}
	}
	#endif	//	CompLazy
	#endif	//	SimulDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in simulation mode.
*/
template<typename pxt, typename pyt, typename fvt>
void CtlSumXYFeVt<pxt,pyt,fvt>::emulBklg()
{
	WatchError
	cEmulValue = cExecValue;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos tPos = this->mBacklogPrms.serial(tIdx), sPos = tPos >> 1;
		if (tPos & 1)	//	data
		{
			//(if cond too, avoid double counting)
			if (this->mBacklogPrms.tagged(tPos - 1)) continue;
			if (tc<pxt,Bll>::iof(mPxRecs[sPos]->CurrData()))
			{
				Term::performEmulBklg(this->mPrmTerms[tPos]);
				EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
				if (this->mEvalUndonePrms->tagged(tPos))
					cEmulValue += tPyRec->LateData(this->mTermSys.EmulClk());
				else if (tPyRec->LateDiff(this->mTermSys.EmulClk()))
					cEmulValue += tPyRec->LateBuff - tPyRec->CurrBuff;
			}
			continue;
		}

		//	condition
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[sPos];
		if (tc<pxt,Bll>::iof(tPxRec->LateData(this->mTermSys.EmulClk())))
		{
			Term::performExecBklg(this->mPrmTerms[++tPos]);
			EvalRec<pyt> const * tPyRec = mPyRecs[sPos];
			if (tPxRec->LateDiff(this->mTermSys.EmulClk()) ||
					this->mEvalUndonePrms->tagged(tPos - 1) ||
					this->mEvalUndonePrms->tagged(tPos))
				cEmulValue += tPyRec->LateData(this->mTermSys.EmulClk());
			else if (tPyRec->LateDiff(this->mTermSys.EmulClk()))
				cEmulValue += tPyRec->CurrBuff - tPyRec->PrevBuff;
		}
		else if (tPxRec->LateDiff(this->mTermSys.EmulClk()) &&
				!this->mEvalUndonePrms->tagged(tPos) &&
				!this->mEvalUndonePrms->tagged(tPos + 1))
			cEmulValue -= tPxRec->CurrData();
	}
	this->mValueRec->updtLate(this->mTermSys.EmulClk(), tc<BuffType, fvt>::iof(cEmulValue));
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif//CtlSumXYFeVtTccIncluded
