/*!
	@file xorsxfcmt.tcc
	@brief The prototype file for XorsXFcMt template class.
	@details This is the prototype file for XorsXFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef XorsXFcMtTccInlcluded
#define XorsXFcMtTccInlcluded



#include "cbls/funcs/fcms/aggfcmt.tcc"



openKangarooSpace



/*!
	@class XorsXFcMt
	@brief A class to represent xor (satisfaction) fcms.
	@details This class represents xor (satisfaction) fcms.
*/
template <typename pxt, typename fmt>
class XorsXFcMt : public AggFcMt<fmt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys,
												Prm * thePrms, Dim const PrmCount);		//!< Definition.
		static XorsXFcMt<pxt,fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static XorsXFcMt<pxt,fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static XorsXFcMt<pxt,fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static XorsXFcMt<pxt,fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static XorsXFcMt<pxt,fmt> const & cast(Term const & theTerm);	//!< Perform casting.
		static XorsXFcMt<pxt,fmt> const * cast(Term const * theTerm);	//!< Perform casting.
		static XorsXFcMt<pxt,fmt> & cast(Term & theTerm);				//!< Perform casting.
		static XorsXFcMt<pxt,fmt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	private:

		~XorsXFcMt();													//!< Destructor.
		XorsXFcMt(XorsXFcMt<pxt,fmt> const & that);						//!< Duplicator.
		XorsXFcMt(Fss const theFss, Hdl const hdlSys,
									Prm * thePrms, Dim const PrmCount);	//!< Constructor.
		XorsXFcMt const & operator = (XorsXFcMt<pxt,fmt> const & that);	//!< Assigner.

		//! @name Computation
		//! @{

		virtual void compConst();					//!< Compute the term.
		virtual void execAnew();					//!< Execute the term.
		virtual void simulAnew();					//!< Simulate the term.
		virtual void execIncr();					//!< Execute the term.
		virtual void simulIncr();					//!< Simulate the term.
		#if CompLazy
		virtual void execBklg();					//!< Execute the term.
		virtual void emulBklg();					//!< Emulate the term.
		virtual void undoEval(Pos const thePos);	//!< Perform eval undo.
		#endif //CompLazy

		//! @}

	private:

		b1<EvalRec<pxt> const *,kmm> mPxRecs;		//!< Parameter records.
		#if SimulDnwdCache
		Dim						cSimulTrue;			//!< Simulation cache true count.
		#endif
		Dim						cExecTrue;			//!< Execution cache true count.
		#if CompLazy
		Dim						cEmulTrue;			//!< Emulation cache true count.
		#endif //CompLazy
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll XorsXFcMt<pxt,fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< XorsXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll XorsXFcMt<pxt,fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< XorsXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll XorsXFcMt<pxt,fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< XorsXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll XorsXFcMt<pxt,fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< XorsXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline XorsXFcMt<pxt,fmt> const & XorsXFcMt<pxt,fmt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< XorsXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<XorsXFcMt<pxt,fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline XorsXFcMt<pxt,fmt> const * XorsXFcMt<pxt,fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< XorsXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<XorsXFcMt<pxt,fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline XorsXFcMt<pxt,fmt> & XorsXFcMt<pxt,fmt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< XorsXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<XorsXFcMt<pxt,fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline XorsXFcMt<pxt,fmt> * XorsXFcMt<pxt,fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< XorsXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<XorsXFcMt<pxt,fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to an or fcm term.
*/
template <typename pxt, typename fmt>
inline XorsXFcMt<pxt,fmt> & XorsXFcMt<pxt,fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to an or fcm term.
*/
template <typename pxt, typename fmt>
inline XorsXFcMt<pxt,fmt> * XorsXFcMt<pxt,fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an or fcm term.
*/
template <typename pxt, typename fmt>
inline XorsXFcMt<pxt,fmt> const & XorsXFcMt<pxt,fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to an or fcm term.
*/
template <typename pxt, typename fmt>
inline XorsXFcMt<pxt,fmt> const * XorsXFcMt<pxt,fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pxt, typename fmt>
inline XorsXFcMt<pxt,fmt>::~XorsXFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Define an or fcm term.
*/
template <typename pxt, typename fmt>
Hdl XorsXFcMt<pxt,fmt>::def(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount)
{
	WatchError
	Warn(PrmCount < 2 || PrmCount > MaxDim, eParamCount2(2, MaxDim));

	XorsXFcMt<pxt,fmt> * tFcM = new XorsXFcMt<pxt,fmt>(theFss,hdlSys, thePrms, PrmCount);
	Hdl const tHdl = tFcM->defSysFunc();
	if (tHdl != InvHdl) { delete tFcM; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<fmt> & tFmtTbl = EvalTbl<fmt>::refm(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFcM->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFcM->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFcM->mPxRecs[tPos] = tPxtTbl.ptrcEvalRec(tPxLoc);
	}
	tFmtTbl.setEvalRec(tFcM->mMetricRec, tFcM->mMetricLoc);

	tFcM->performCompConst();
	tFcM->defSysRoot();
	return tFcM->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
template <typename pxt, typename fmt>
XorsXFcMt<pxt,fmt>::XorsXFcMt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) :
		AggFcMt<fmt>(hdlSys, PrmCount), mPxRecs(PrmCount)
{
	WatchError
	this->setTermCls(TermStub< XorsXFcMt<pxt,fmt> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Unordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename fmt>
XorsXFcMt<pxt,fmt>::XorsXFcMt(XorsXFcMt const & that) : AggFcMt<fmt>(that), mPxRecs(0)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename pxt, typename fmt>
XorsXFcMt<pxt,fmt> const & XorsXFcMt<pxt,fmt>::operator = (XorsXFcMt<pxt,fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template <typename pxt, typename fmt>
void XorsXFcMt<pxt,fmt>::compConst()
{
	WatchError
	if (!this->updatable())
	{
		cExecTrue = 0;
		for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
			if (tc<pxt,Bll>::iof(mPxRecs[tPos]->CurrData())) ++cExecTrue;
		this->mMetricRec->finalise(cExecTrue & 1);
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void XorsXFcMt<pxt,fmt>::execAnew()
{
	WatchError
	cExecTrue = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if ExecDnwd
		Term::performExecAnew(this->mPrmTerms[tPos]);
		#endif
		if (tc<pxt,Bll>::iof(mPxRecs[tPos]->CurrData())) ++cExecTrue;
	}
	this->mMetricRec->initCurr(cExecTrue & 1);
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename fmt>
void XorsXFcMt<pxt,fmt>::simulAnew()
{
	WatchError
	Dim tSimulTrue = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if SimulDnwd
		Term::performSimulAnew(this->mPrmTerms[tPos]);
		#endif
		if (tc<pxt,Bll>::iof(mPxRecs[tPos]->NextData(this->mTermSys.SimulClk())))
			++tSimulTrue;
	}
	this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulTrue & 1);
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



#if CompLazy
/*!
	Perform eval undo for the parameter.
*/
template <typename pxt, typename fmt>
void XorsXFcMt<pxt,fmt>::undoEval(Pos const thePos)
{
	WatchError
	if (tc<pxt,Bll>::iof(mPxRecs[thePos]->PrevData(this->mTermSys.ExecClk())))
		--cExecTrue;
	CatchError
}
#endif



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void XorsXFcMt<pxt,fmt>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		for(Idx tIdx = 0; tIdx < this->mExecChgdPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mExecChgdPrms.serial(tIdx);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
			if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				(tc<pxt,Bll>::iof(tPxRec->CurrBuff)) ? ++cExecTrue : --cExecTrue;
		}
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecTrue & 1);
		this->runPostExecIncr();
	}
	#endif	//ExecUpwd
	#if ExecDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//	CompLazy
		if (this->needExecCandComp()) this->listCandParams();
		if (this->mBlkCandPrms->itemCount())
		{
			for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkCandPrms->item(tIdx);
				Term::performExecIncr(this->mPrmTerms[tPos]);
				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
					(tc<pxt,Bll>::iof(tPxRec->CurrBuff)) ? ++cExecTrue : --cExecTrue;
			}
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecTrue & 1);
		}
	#if CompLazy
	}
	else
	{
		if (this->needExecCandComp()) this->markCandParams();
		for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkCandPrms->item(tIdx);
			Term::performExecIncr(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
				{ if (tc<pxt,Bll>::iof(tPxRec->CurrData())) ++cExecTrue; }
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				(tc<pxt,Bll>::iof(tPxRec->CurrBuff)) ? ++cExecTrue : --cExecTrue;
		}

		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;
			Term::performExecBklg(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
				{ if (tc<pxt,Bll>::iof(tPxRec->CurrData())) ++cExecTrue; }
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				(tc<pxt,Bll>::iof(tPxRec->CurrBuff)) ? ++cExecTrue : --cExecTrue;
		}

		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecTrue & 1);
	}
	this->runPostExecIncr();
	#endif //CompLazy
	#endif //ExecDnwd
	CatchError
}


#if CompLazy
/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void XorsXFcMt<pxt,fmt>::execBklg()
{
	WatchError
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performExecBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			{ if (tc<pxt,Bll>::iof(tPxRec->CurrData())) ++cExecTrue; }
		else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			(tc<pxt,Bll>::iof(tPxRec->CurrBuff)) ? ++cExecTrue : --cExecTrue;
	}

	this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecTrue & 1);
	this->runPostExecBklg();
	CatchError
}
#endif //CompLazy



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename fmt>
void XorsXFcMt<pxt,fmt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		Dim tSimulTrue = cExecTrue;
		for(Idx tIdx = 0; tIdx < this->mSimulChgdPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mSimulChgdPrms.serial(tIdx);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
			if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
				(tc<pxt,Bll>::iof(tPxRec->NextBuff)) ? ++tSimulTrue : --tSimulTrue;
		}
		this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulTrue & 1);
		this->runPostSimulIncr();
	}
	#endif	//SimulUpwd
	#if SimulDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//CompLazy
		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->listFlexiParams();
		#endif
		#if SimulFixedFlexi
		if (this->needSimulFixedComp())
			this->enumFixedParams(this->mBlkFlexiPrms->itemCount());
		#elif SimulFixedOnly
		if (this->needSimulFixedComp()) this->listFixedParams();
		#endif

		#if SimulFixed
		if (this->needSimulCacheComp())
		{
			cSimulTrue = cExecTrue;
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				if (tc<pxt,Bll>::iof(mPxRecs[tPos]->CurrData())) --cSimulTrue;
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
			Dim tSimulTrue = cSimulTrue;
			#else
			Dim tSimulTrue = cExecTrue;
			#endif

			#if SimulFixed
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				Term::performSimulIncr(this->mPrmTerms[tPos]);
				if (tc<pxt,Bll>::iof(mPxRecs[tPos]->NextData(this->mTermSys.SimulClk()))) ++tSimulTrue;
			}
			#endif//SimulFixed

			#if SimulFlexi
			for(Idx tIdx = 0; tIdx < this->mBlkFlexiPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFlexiPrms->item(tIdx);

				#if SimulFixed
				if (this->mLblFixedPrms.tagged(tPos)) continue;
				#endif

				Term::performSimulIncr(this->mPrmTerms[tPos]);

				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
					(tc<pxt,Bll>::iof(tPxRec->NextBuff)) ? ++tSimulTrue : --tSimulTrue;
			}
			#endif//SimulFlexi

			this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulTrue & 1);
		}
	#if CompLazy
	}
	else	//	backlog
	{
		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->listFlexiParams();
		#endif
		#if SimulFixed
		if (this->needSimulFixedComp())	this->markFixedParams();
		#endif

		if (this->needSimulCacheComp())
		{
			if (!this->chgdEmulClk())
			{
				cSimulTrue = cEmulTrue;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					if (tc<pxt,Bll>::iof(mPxRecs[tPos]->LateData(this->mTermSys.EmulClk())))
						--cSimulTrue;
				}
				#endif//SimulFixed
			}
			else
			{
				cSimulTrue = cExecTrue;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					if (!this->mEvalUndonePrms->tagged(tPos))
						if (tc<pxt,Bll>::iof(mPxRecs[tPos]->CurrData())) --cSimulTrue;
				}
				#endif
				for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
				{
					Pos const tPos = this->mBacklogPrms.serial(tIdx);
					#if SimulFixed
					if (this->mLblFixedPrms.tagged(tPos)) continue;
					#endif
					Term::performEmulBklg(this->mPrmTerms[tPos]);
					EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

					if (this->mEvalUndonePrms->tagged(tPos))
					{
						if (tc<pxt,Bll>::iof(tPxRec->LateData(this->mTermSys.EmulClk())))
							++cSimulTrue;
					}
					else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
						(tc<pxt,Bll>::iof(tPxRec->LateBuff)) ? ++cSimulTrue : --cSimulTrue;
				}
			}
		}

		Dim tSimulTrue = cSimulTrue;

		#if SimulFixed
		for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFixedPrms->item(tIdx);
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			if (tc<pxt,Bll>::iof(mPxRecs[tPos]->NextData(this->mTermSys.SimulClk()))) ++tSimulTrue;
		}
		#endif//SimulFixed

		#if SimulFlexi
		for(Idx tIdx = 0; tIdx < this->mBlkFlexiPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFlexiPrms->item(tIdx);

			#if SimulFixed
			if (this->mLblFixedPrms.tagged(tPos)) continue;
			#endif

			Term::performEmulBklg(this->mPrmTerms[tPos]);
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
			if (tPxRec->LtNxDiff(this->mTermSys.EmulClk(), this->mTermSys.SimulClk()))
			 (tc<pxt,Bll>::iof(tPxRec->NextData(this->mTermSys.SimulClk()))) ? ++tSimulTrue : --tSimulTrue;
		}
		#endif//SimulFlexi

		this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulTrue & 1);
	}
	#endif	//	CompLazy
	#endif 	//	SimulDnwd
	CatchError
}


#if CompLazy
/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename fmt>
void XorsXFcMt<pxt,fmt>::emulBklg()
{
	WatchError
	 cEmulTrue = cExecTrue;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			{ if (tc<pxt,Bll>::iof(tPxRec->LateData(this->mTermSys.EmulClk()))) ++cEmulTrue; }
		else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
			(tc<pxt,Bll>::iof(tPxRec->LateBuff)) ? ++cEmulTrue : --cEmulTrue;
	}
	this->mMetricRec->updtLate(this->mTermSys.EmulClk(), cEmulTrue & 1);
	CatchError
}
#endif //CompLazy


closeKangarooSpace


#endif//XorsXFcMtTccIncluded
