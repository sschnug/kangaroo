/*!
	@file wghtsumkxfcmt.tcc
	@brief The prototype file for WghtSumKXFcMt template class.
	@details This is the prototype file for WghtSumKXFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef WghtSumKXFcMtTccIncluded
#define WghtSumKXFcMtTccIncluded



#include "cbls/funcs/fcms/aggfcmt.tcc"



openKangarooSpace



/*!
	@class WghtSumKXFcMt
	@brief A class to represent weighted summation fcm terms.
	@details This class represents weighted summation fcm terms.
*/
template <typename pkt, typename pxt, typename fmt>
class WghtSumKXFcMt : public AggFcMt<fmt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys,
								pkt * theWghts, Prm * thePrms, Dim const PrmCount);			//!< Definition.

		static WghtSumKXFcMt<pkt,pxt,fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static WghtSumKXFcMt<pkt,pxt,fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static WghtSumKXFcMt<pkt,pxt,fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);//!< Reference.
		static WghtSumKXFcMt<pkt,pxt,fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);//!< Pointer.

		//! @name Casting
		//! @{

		static WghtSumKXFcMt<pkt,pxt,fmt> const & cast(Term const & theTerm);	//!< Perform casting.
		static WghtSumKXFcMt<pkt,pxt,fmt> const * cast(Term const * theTerm);	//!< Perform casting.
		static WghtSumKXFcMt<pkt,pxt,fmt> & cast(Term & theTerm);				//!< Perform casting.
		static WghtSumKXFcMt<pkt,pxt,fmt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);						//!< Suits casting?
		static Bll suit(Term const * theTerm);						//!< Suits casting?
		static Bll suit(Term & theTerm);							//!< Suits casting?
		static Bll suit(Term * theTerm);							//!< Suits casting?

		//! @}

	private:

		~WghtSumKXFcMt();															//!< Destructor.
		WghtSumKXFcMt(WghtSumKXFcMt<pkt,pxt,fmt> const & that);						//!< Duplicator.
		WghtSumKXFcMt(Fss const theFss, Hdl const hdlSys,
						pkt * theWghts, Prm * thePrms, Dim const PrmCount);			//!< Constructor.
		WghtSumKXFcMt const & operator = (WghtSumKXFcMt<pkt,pxt,fmt> const & that);	//!< Assigner.

		//! @name Identity
		//! @{

		Hvl calcTermHvl() const;				 				//!< Calculate term hash value.
		virtual Bll equate(Term const & theTerm) const; 		//!< Compare terms for equality.

		//! @}

		//! @name Computation
		//! @{

		virtual void compConst();				//!< Compute the term.
		virtual void execAnew();				//!< Execute the term.
		virtual void simulAnew();				//!< Simulate the term.
		virtual void execIncr();				//!< Execute the term.
		virtual void simulIncr();				//!< Simulate the term.
		#if CompLazy
		virtual void execBklg();				//!< Execute the term.
		virtual void emulBklg();				//!< Emulate the term.
		virtual void undoEval(Pos const thePos);//!< Perform eval undo.
		#endif

		//! @}

		b1<EvalRec<pxt> const *,kmm> 			mPxRecs;		//!< Parameter records.
		b1<pkt,kmm>								mPkWghts;		//!< Parameter weights.

		typedef typename DataTemp<pkt,pxt>::Type TempType;		//!< Data temp type.
		typedef typename DataBuff<TempType, fmt>::Type BuffType;//!< Data buff type.

		#if SimulDnwdCache
		BuffType	cSimulMetric;		//!< Simulation cache metric.
		#endif
		BuffType	cExecMetric;		//!< Execution cache metric.
		#if CompLazy
		BuffType	cEmulMetric;		//!< Emulation cache metric.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fmt>
inline Bll WghtSumKXFcMt<pkt,pxt,fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< WghtSumKXFcMt<pkt,pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fmt>
inline Bll WghtSumKXFcMt<pkt,pxt,fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< WghtSumKXFcMt<pkt,pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fmt>
inline Bll WghtSumKXFcMt<pkt,pxt,fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< WghtSumKXFcMt<pkt,pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fmt>
inline Bll WghtSumKXFcMt<pkt,pxt,fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< WghtSumKXFcMt<pkt,pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXFcMt<pkt,pxt,fmt> const & WghtSumKXFcMt<pkt,pxt,fmt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< WghtSumKXFcMt<pkt,pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXFcMt<pkt,pxt,fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXFcMt<pkt,pxt,fmt> const * WghtSumKXFcMt<pkt,pxt,fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< WghtSumKXFcMt<pkt,pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXFcMt<pkt,pxt,fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXFcMt<pkt,pxt,fmt> & WghtSumKXFcMt<pkt,pxt,fmt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< WghtSumKXFcMt<pkt,pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXFcMt<pkt,pxt,fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXFcMt<pkt,pxt,fmt> * WghtSumKXFcMt<pkt,pxt,fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< WghtSumKXFcMt<pkt,pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXFcMt<pkt,pxt,fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to a summation fcm term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXFcMt<pkt,pxt,fmt> & WghtSumKXFcMt<pkt,pxt,fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a summation fcm term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXFcMt<pkt,pxt,fmt> * WghtSumKXFcMt<pkt,pxt,fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a summation fcm term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXFcMt<pkt,pxt,fmt> const & WghtSumKXFcMt<pkt,pxt,fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a summation fcm term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXFcMt<pkt,pxt,fmt> const * WghtSumKXFcMt<pkt,pxt,fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXFcMt<pkt,pxt,fmt>::~WghtSumKXFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Define a summation fcm in the sys.
*/
template <typename pkt, typename pxt, typename fmt>
Hdl WghtSumKXFcMt<pkt,pxt,fmt>::def( Fss const theFss, Hdl const hdlSys,
				pkt * theWghts, Prm * thePrms, Dim const PrmCount)
{
	WatchError
	Wchk(PrmCount < 2 || PrmCount > MaxDim) Wtxt(eParamCount2(2, MaxDim));

	WghtSumKXFcMt<pkt,pxt,fmt> * tFcM = new WghtSumKXFcMt<pkt,pxt,fmt>(theFss, hdlSys, theWghts, thePrms, PrmCount);
	Hdl const tHdl = tFcM->defSysFunc();
	if (tHdl != InvHdl) { delete tFcM; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<fmt> & tFmtTbl = EvalTbl<fmt>::refm(hdlSys);

	b1<Term *, kmm> const & tPrmTerms = tFcM->mPrmTerms;
	b1<Pss, kmm> const & tPrmSpecs = tFcM->mPrmSpecs;

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
template <typename pkt, typename pxt, typename fmt>
WghtSumKXFcMt<pkt,pxt,fmt>::WghtSumKXFcMt(Fss const theFss, Hdl const hdlSys,
			pkt * theWghts, Prm * thePrms, Dim const PrmCount) :
		AggFcMt<fmt>(hdlSys, PrmCount), mPxRecs(PrmCount), mPkWghts(PrmCount)
{
	WatchError
	this->setTermCls(TermStub< WghtSumKXFcMt<pkt,pxt,fmt> >::TermCls);
	b1<Idx,kmm> tBlkIdxs(PrmCount);
	this->setParams(theFss, thePrms, PrmCount, Unordered, tBlkIdxs.items());
	mPkWghts.copyIndexed(theWghts, tBlkIdxs.items(), PrmCount);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pkt, typename pxt, typename fmt>
WghtSumKXFcMt<pkt,pxt,fmt>::WghtSumKXFcMt(WghtSumKXFcMt const & that) :
		AggFcMt<fmt>(that), mPxRecs(0), mPkWghts(0)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename pkt, typename pxt, typename fmt>
WghtSumKXFcMt<pkt,pxt,fmt> const & WghtSumKXFcMt<pkt,pxt,fmt>::operator =
		(WghtSumKXFcMt<pkt,pxt,fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Calculate hash value of the term.
*/
template <typename pkt, typename pxt, typename fmt>
Hvl WghtSumKXFcMt<pkt,pxt,fmt>::calcTermHvl() const
{
	WatchError
	Hvl tHvl = 0;
	tHvl = mixHash(tHvl, calcHash(this->TermCls));
	tHvl = mixHash(tHvl, calcHash(this->FuncFss));

	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		tHvl = mixHash(tHvl, calcHash(this->mPrmTerms[tPos]));
		tHvl = mixHash(tHvl, calcHash(this->mPrmSpecs[tPos]));
		tHvl = mixHash(tHvl, calcHash(this->mPkWghts[tPos]));
	}
	return tHvl;
	CatchError
}



/*!
	Compare two terms for equality.
*/
template <typename pkt, typename pxt, typename fmt>
Bll WghtSumKXFcMt<pkt,pxt,fmt>::equate(Term const & theTerm) const
{
	WatchError
	if (this->TermCls != theTerm.TermCls) return false;
	WghtSumKXFcMt<pkt,pxt,fmt> const & tFunc = cast(theTerm);
	b1<Term *, kmm> const & tPrmTerms = tFunc.mPrmTerms;
	b1<Pss, kmm> const & tPrmSpecs = tFunc.mPrmSpecs;
	b1<pkt,kmm> const & tPxWghts = tFunc.mPkWghts;

	if (this->FuncFss != tFunc.FuncFss) return false;
	if (this->mPrmTerms.itemCount() != tPrmTerms.itemCount()) return false;
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		if (this->mPrmTerms[tPos] != tPrmTerms[tPos]) return false;
		if (this->mPrmSpecs[tPos] != tPrmSpecs[tPos]) return false;
		if (ne<pkt,Bll>::iof(this->mPkWghts[tPos], tPxWghts[tPos])) return false;
	}
	return true;
	CatchError
}



/*!
	Compute the term.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXFcMt<pkt,pxt,fmt>::compConst()
{
	WatchError
	if (!this->updatable())
	{
		cExecMetric = 0;
		for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
			cExecMetric += mPkWghts[tPos] * mPxRecs[tPos]->CurrData();
		this->mMetricRec->finalise(tc<BuffType,fmt>::iof(cExecMetric));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXFcMt<pkt,pxt,fmt>::execAnew()
{
	WatchError
	cExecMetric = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if ExecDnwd
		Term::performExecAnew(this->mPrmTerms[tPos]);
		#endif
		cExecMetric += mPkWghts[tPos] * mPxRecs[tPos]->CurrData();
	}
	this->mMetricRec->initCurr(tc<BuffType,fmt>::iof(cExecMetric));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXFcMt<pkt,pxt,fmt>::simulAnew()
{
	WatchError
	BuffType tSimulMetric = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if SimulDnwd
		Term::performSimulAnew(this->mPrmTerms[tPos]);
		#endif
		tSimulMetric += mPkWghts[tPos] * mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
	}
	this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fmt>::iof(tSimulMetric));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}


#if CompLazy
/*!
	Perform eval undo for the parameter.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXFcMt<pkt,pxt,fmt>::undoEval(Pos const thePos)
{
	WatchError
	cExecMetric -= mPkWghts[thePos] * mPxRecs[thePos]->PrevData(this->mTermSys.ExecClk());
	CatchError
}
#endif	//CompLazy


/*!
	Compute the term in execution mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXFcMt<pkt,pxt,fmt>::execIncr()
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
				cExecMetric += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);
		}
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fmt>::iof(cExecMetric));
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
					cExecMetric += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);
			}
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fmt>::iof(cExecMetric));
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
				cExecMetric += mPkWghts[tPos] * tPxRec->CurrData();
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				cExecMetric += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);
		}

		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;

			Term::performExecBklg(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
				cExecMetric += mPkWghts[tPos] * tPxRec->CurrData();
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				cExecMetric += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);
		}

		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fmt>::iof(cExecMetric));
	}
	this->runPostExecIncr();
	#endif	//	CompLazy
	#endif	//	ExecDnwd
	CatchError
}


#if CompLazy
/*!
	Compute the term in execution mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXFcMt<pkt,pxt,fmt>::execBklg()
{
	WatchError
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performExecBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			cExecMetric += mPkWghts[tPos] * tPxRec->CurrData();
		else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			cExecMetric += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);
	}

	this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fmt>::iof(cExecMetric));
	this->runPostExecBklg();
	CatchError
}
#endif	//CompLazy


/*!
	Compute the term in simulation mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXFcMt<pkt,pxt,fmt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		BuffType tSimulMetric = cExecMetric;
		for(Idx tIdx = 0; tIdx < this->mSimulChgdPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mSimulChgdPrms.serial(tIdx);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
			if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
				tSimulMetric += mPkWghts[tPos] * (tPxRec->NextBuff - tPxRec->CurrBuff);
		}
		this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fmt>::iof(tSimulMetric));
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
			cSimulMetric = cExecMetric;
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				cSimulMetric -= mPkWghts[tPos] * mPxRecs[tPos]->CurrData();
			}
		}
		#endif

		#if SimulFixedFlexi
		if (this->mBlkFixedPrms->itemCount() || this->mBlkFlexiPrms->itemCount())
		#elif SimulFixedOnly
		if (this->mBlkFixedPrms->itemCount())
		#elif SimulFlexiOnly
		if (this->mBlkFlexiPrms->itemCount())
		#endif
		{
			#if SimulFixed
			BuffType tSimulMetric = cSimulMetric;
			#else
			BuffType tSimulMetric = cExecMetric;
			#endif

			#if SimulFixed
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				Term::performSimulIncr(this->mPrmTerms[tPos]);
				tSimulMetric += mPkWghts[tPos] * mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
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
					tSimulMetric += mPkWghts[tPos] * (tPxRec->NextBuff - tPxRec->CurrBuff);
			}
			#endif //SimulFlexi

			this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fmt>::iof(tSimulMetric));
		}
	#if CompLazy
	}
	else	//	backlog
	{
		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->listFlexiParams();
		#endif
		#if SimulFixed
		if (this->needSimulFixedComp()) this->markFixedParams();
		#endif

		if (this->needSimulCacheComp())
		{
			if (!this->chgdEmulClk())
			{
				cSimulMetric = cEmulMetric;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					cSimulMetric -= mPkWghts[tPos] * mPxRecs[tPos]->LateData(this->mTermSys.EmulClk());
				}
				#endif//SimulFixed
			}
			else
			{
				cSimulMetric = cExecMetric;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					if (!this->mEvalUndonePrms->tagged(tPos))
						cSimulMetric -= mPkWghts[tPos] * mPxRecs[tPos]->CurrData();
				}
				#endif//SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
				{
					Pos const tPos = this->mBacklogPrms.serial(tIdx);
					#if SimulFixed
					if (this->mLblFixedPrms.tagged(tPos)) continue;
					#endif//SimulFixed
					Term::performEmulBklg(this->mPrmTerms[tPos]);
					EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

					if (this->mEvalUndonePrms->tagged(tPos))
						cSimulMetric += mPkWghts[tPos] * tPxRec->LateData(this->mTermSys.EmulClk());	//	late data, not buff.
					else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
						cSimulMetric += mPkWghts[tPos] * (tPxRec->LateBuff - tPxRec->CurrBuff);
				}
			}
		}

		BuffType tSimulMetric = cSimulMetric;

		#if SimulFixed
		for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFixedPrms->item(tIdx);
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			tSimulMetric += mPkWghts[tPos] * mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
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
				tSimulMetric += mPkWghts[tPos] * (tPxRec->NextData(this->mTermSys.SimulClk()) -
							tPxRec->LateData(this->mTermSys.EmulClk()));
		}
		#endif//SimulFlexi

		this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fmt>::iof(tSimulMetric));
	}
	#endif	//	CompLazy
	#endif	//	SimulDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in simulation mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXFcMt<pkt,pxt,fmt>::emulBklg()
{
	WatchError
	cEmulMetric = cExecMetric;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			cEmulMetric += mPkWghts[tPos] * tPxRec->LateData(this->mTermSys.EmulClk());
		else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
			cEmulMetric += mPkWghts[tPos] * (tPxRec->LateBuff - tPxRec->CurrBuff);
	}
	this->mMetricRec->updtLate(this->mTermSys.EmulClk(), tc<BuffType,fmt>::iof(cEmulMetric));
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif//WghtSumKXFcMtTccIncluded
