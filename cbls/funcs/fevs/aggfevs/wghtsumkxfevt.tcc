/*!
	@file wghtsumkxfevt.tcc
	@brief The prototype file for WghtSumKXFeVt template class.
	@details This is the prototype file for WghtSumKXFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef WghtSumKXFeVtTccIncluded
#define WghtSumKXFeVtTccIncluded



#include "cbls/funcs/fevs/aggfevt.tcc"



openKangarooSpace



/*!
	@class WghtSumKXFeVt
	@brief A class to represent weighted summation fev terms.
	@details This class represents weighted summation fev terms.
*/
template <typename pkt, typename pxt, typename fvt>
class WghtSumKXFeVt : public AggFeVt<fvt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys,
								pkt * theWghts, Prm * thePrms, Dim const PrmCount);			//!< Definition.

		static WghtSumKXFeVt<pkt,pxt,fvt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static WghtSumKXFeVt<pkt,pxt,fvt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static WghtSumKXFeVt<pkt,pxt,fvt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);//!< Reference.
		static WghtSumKXFeVt<pkt,pxt,fvt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);//!< Pointer.

		//! @name Casting
		//! @{

		static WghtSumKXFeVt<pkt,pxt,fvt> const & cast(Term const & theTerm);	//!< Perform casting.
		static WghtSumKXFeVt<pkt,pxt,fvt> const * cast(Term const * theTerm);	//!< Perform casting.
		static WghtSumKXFeVt<pkt,pxt,fvt> & cast(Term & theTerm);				//!< Perform casting.
		static WghtSumKXFeVt<pkt,pxt,fvt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);						//!< Suits casting?
		static Bll suit(Term const * theTerm);						//!< Suits casting?
		static Bll suit(Term & theTerm);							//!< Suits casting?
		static Bll suit(Term * theTerm);							//!< Suits casting?

		//! @}

	private:

		~WghtSumKXFeVt();															//!< Destructor.
		WghtSumKXFeVt(WghtSumKXFeVt<pkt,pxt,fvt> const & that);						//!< Duplicator.
		WghtSumKXFeVt(Fss const theFss, Hdl const hdlSys,
						pkt * theWghts, Prm * thePrms, Dim const PrmCount);			//!< Constructor.
		WghtSumKXFeVt const & operator = (WghtSumKXFeVt<pkt,pxt,fvt> const & that);	//!< Assigner.

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
		typedef typename DataBuff<TempType, fvt>::Type BuffType;//!< Data buff type.

		#if SimulDnwdCache
		BuffType	cSimulValue;	//!< Simulation cache value.
		#endif
		BuffType	cExecValue;		//!< Execution cache value.
		#if CompLazy
		BuffType	cEmulValue;		//!< Emulation cache value.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fvt>
inline Bll WghtSumKXFeVt<pkt,pxt,fvt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< WghtSumKXFeVt<pkt,pxt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fvt>
inline Bll WghtSumKXFeVt<pkt,pxt,fvt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< WghtSumKXFeVt<pkt,pxt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fvt>
inline Bll WghtSumKXFeVt<pkt,pxt,fvt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< WghtSumKXFeVt<pkt,pxt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fvt>
inline Bll WghtSumKXFeVt<pkt,pxt,fvt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< WghtSumKXFeVt<pkt,pxt,fvt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fvt>
inline WghtSumKXFeVt<pkt,pxt,fvt> const & WghtSumKXFeVt<pkt,pxt,fvt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< WghtSumKXFeVt<pkt,pxt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXFeVt<pkt,pxt,fvt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fvt>
inline WghtSumKXFeVt<pkt,pxt,fvt> const * WghtSumKXFeVt<pkt,pxt,fvt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< WghtSumKXFeVt<pkt,pxt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXFeVt<pkt,pxt,fvt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fvt>
inline WghtSumKXFeVt<pkt,pxt,fvt> & WghtSumKXFeVt<pkt,pxt,fvt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< WghtSumKXFeVt<pkt,pxt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXFeVt<pkt,pxt,fvt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fvt>
inline WghtSumKXFeVt<pkt,pxt,fvt> * WghtSumKXFeVt<pkt,pxt,fvt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< WghtSumKXFeVt<pkt,pxt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXFeVt<pkt,pxt,fvt> *>(theTerm);
	CatchError
}



/*!
	Refer to a summation fev term.
*/
template <typename pkt, typename pxt, typename fvt>
inline WghtSumKXFeVt<pkt,pxt,fvt> & WghtSumKXFeVt<pkt,pxt,fvt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a summation fev term.
*/
template <typename pkt, typename pxt, typename fvt>
inline WghtSumKXFeVt<pkt,pxt,fvt> * WghtSumKXFeVt<pkt,pxt,fvt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a summation fev term.
*/
template <typename pkt, typename pxt, typename fvt>
inline WghtSumKXFeVt<pkt,pxt,fvt> const & WghtSumKXFeVt<pkt,pxt,fvt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a summation fev term.
*/
template <typename pkt, typename pxt, typename fvt>
inline WghtSumKXFeVt<pkt,pxt,fvt> const * WghtSumKXFeVt<pkt,pxt,fvt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pkt, typename pxt, typename fvt>
inline WghtSumKXFeVt<pkt,pxt,fvt>::~WghtSumKXFeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Define a summation fev in the sys.
*/
template <typename pkt, typename pxt, typename fvt>
Hdl WghtSumKXFeVt<pkt,pxt,fvt>::def( Fss const theFss, Hdl const hdlSys,
				pkt * theWghts, Prm * thePrms, Dim const PrmCount)
{
	WatchError
	Wchk(PrmCount < 2 || PrmCount > MaxDim) Wtxt(eParamCount2(2, MaxDim));

	WghtSumKXFeVt<pkt,pxt,fvt> * tFeV = new WghtSumKXFeVt<pkt,pxt,fvt>(theFss, hdlSys, theWghts, thePrms, PrmCount);
	Hdl const tHdl = tFeV->defSysFunc();
	if (tHdl != InvHdl) { delete tFeV; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<fvt> & tFvtTbl = EvalTbl<fvt>::refm(hdlSys);

	b1<Term *, kmm> const & tPrmTerms = tFeV->mPrmTerms;
	b1<Pss, kmm> const & tPrmSpecs = tFeV->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFeV->mPxRecs[tPos] = tPxtTbl.ptrcEvalRec(tPxLoc);
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
template <typename pkt, typename pxt, typename fvt>
WghtSumKXFeVt<pkt,pxt,fvt>::WghtSumKXFeVt(Fss const theFss, Hdl const hdlSys,
			pkt * theWghts, Prm * thePrms, Dim const PrmCount) :
		AggFeVt<fvt>(hdlSys, PrmCount), mPxRecs(PrmCount), mPkWghts(PrmCount)
{
	WatchError
	this->setTermCls(TermStub< WghtSumKXFeVt<pkt,pxt,fvt> >::TermCls);
	b1<Idx,kmm> tBlkIdxs(PrmCount);
	this->setParams(theFss, thePrms, PrmCount, Unordered, tBlkIdxs.items());
	mPkWghts.copyIndexed(theWghts, tBlkIdxs.items(), PrmCount);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pkt, typename pxt, typename fvt>
WghtSumKXFeVt<pkt,pxt,fvt>::WghtSumKXFeVt(WghtSumKXFeVt const & that) :
		AggFeVt<fvt>(that), mPxRecs(0), mPkWghts(0)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename pkt, typename pxt, typename fvt>
WghtSumKXFeVt<pkt,pxt,fvt> const & WghtSumKXFeVt<pkt,pxt,fvt>::operator =
		(WghtSumKXFeVt<pkt,pxt,fvt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Calculate hash value of the term.
*/
template <typename pkt, typename pxt, typename fvt>
Hvl WghtSumKXFeVt<pkt,pxt,fvt>::calcTermHvl() const
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
template <typename pkt, typename pxt, typename fvt>
Bll WghtSumKXFeVt<pkt,pxt,fvt>::equate(Term const & theTerm) const
{
	WatchError
	if (this->TermCls != theTerm.TermCls) return false;
	WghtSumKXFeVt<pkt,pxt,fvt> const & tFunc = cast(theTerm);
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
template <typename pkt, typename pxt, typename fvt>
void WghtSumKXFeVt<pkt,pxt,fvt>::compConst()
{
	WatchError
	if (!this->updatable())
	{
		cExecValue = 0;
		for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
			cExecValue += mPkWghts[tPos] * mPxRecs[tPos]->CurrData();
		this->mValueRec->finalise(tc<BuffType,fvt>::iof(cExecValue));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pkt, typename pxt, typename fvt>
void WghtSumKXFeVt<pkt,pxt,fvt>::execAnew()
{
	WatchError
	cExecValue = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if ExecDnwd
		Term::performExecAnew(this->mPrmTerms[tPos]);
		#endif
		cExecValue += mPkWghts[tPos] * mPxRecs[tPos]->CurrData();
	}
	this->mValueRec->initCurr(tc<BuffType,fvt>::iof(cExecValue));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template <typename pkt, typename pxt, typename fvt>
void WghtSumKXFeVt<pkt,pxt,fvt>::simulAnew()
{
	WatchError
	BuffType tSimulValue = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if SimulDnwd
		Term::performSimulAnew(this->mPrmTerms[tPos]);
		#endif
		tSimulValue += mPkWghts[tPos] * mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
	}
	this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fvt>::iof(tSimulValue));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}


#if CompLazy
/*!
	Perform eval undo for the parameter.
*/
template <typename pkt, typename pxt, typename fvt>
void WghtSumKXFeVt<pkt,pxt,fvt>::undoEval(Pos const thePos)
{
	WatchError
	cExecValue -= mPkWghts[thePos] * mPxRecs[thePos]->PrevData(this->mTermSys.ExecClk());
	CatchError
}
#endif	//CompLazy


/*!
	Compute the term in execution mode.
*/
template <typename pkt, typename pxt, typename fvt>
void WghtSumKXFeVt<pkt,pxt,fvt>::execIncr()
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
				cExecValue += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);
		}
		this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fvt>::iof(cExecValue));
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
					cExecValue += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);
			}
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fvt>::iof(cExecValue));
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
				cExecValue += mPkWghts[tPos] * tPxRec->CurrData();
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				cExecValue += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);
		}

		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;

			Term::performExecBklg(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
				cExecValue += mPkWghts[tPos] * tPxRec->CurrData();
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				cExecValue += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);
		}

		this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fvt>::iof(cExecValue));
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
template <typename pkt, typename pxt, typename fvt>
void WghtSumKXFeVt<pkt,pxt,fvt>::execBklg()
{
	WatchError
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performExecBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			cExecValue += mPkWghts[tPos] * tPxRec->CurrData();
		else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			cExecValue += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);
	}

	this->mValueRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fvt>::iof(cExecValue));
	this->runPostExecBklg();
	CatchError
}
#endif	//CompLazy


/*!
	Compute the term in simulation mode.
*/
template <typename pkt, typename pxt, typename fvt>
void WghtSumKXFeVt<pkt,pxt,fvt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		BuffType tSimulValue = cExecValue;
		for(Idx tIdx = 0; tIdx < this->mSimulChgdPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mSimulChgdPrms.serial(tIdx);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
			if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
				tSimulValue += mPkWghts[tPos] * (tPxRec->NextBuff - tPxRec->CurrBuff);
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
			cSimulValue = cExecValue;
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				cSimulValue -= mPkWghts[tPos] * mPxRecs[tPos]->CurrData();
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
			BuffType tSimulValue = cSimulValue;
			#else
			BuffType tSimulValue = cExecValue;
			#endif

			#if SimulFixed
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				Term::performSimulIncr(this->mPrmTerms[tPos]);
				tSimulValue += mPkWghts[tPos] * mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
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
					tSimulValue += mPkWghts[tPos] * (tPxRec->NextBuff - tPxRec->CurrBuff);
			}
			#endif //SimulFlexi

			this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fvt>::iof(tSimulValue));
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
				cSimulValue = cEmulValue;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					cSimulValue -= mPkWghts[tPos] * mPxRecs[tPos]->LateData(this->mTermSys.EmulClk());
				}
				#endif//SimulFixed
			}
			else
			{
				cSimulValue = cExecValue;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					if (!this->mEvalUndonePrms->tagged(tPos))
						cSimulValue -= mPkWghts[tPos] * mPxRecs[tPos]->CurrData();
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
						cSimulValue += mPkWghts[tPos] * tPxRec->LateData(this->mTermSys.EmulClk());	//	late data, not buff.
					else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
						cSimulValue += mPkWghts[tPos] * (tPxRec->LateBuff - tPxRec->CurrBuff);
				}
			}
		}

		BuffType tSimulValue = cSimulValue;

		#if SimulFixed
		for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFixedPrms->item(tIdx);
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			tSimulValue += mPkWghts[tPos] * mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
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
				tSimulValue += mPkWghts[tPos] * (tPxRec->NextData(this->mTermSys.SimulClk()) -
							tPxRec->LateData(this->mTermSys.EmulClk()));
		}
		#endif//SimulFlexi

		this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fvt>::iof(tSimulValue));
	}
	#endif	//	CompLazy
	#endif	//	SimulDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in simulation mode.
*/
template <typename pkt, typename pxt, typename fvt>
void WghtSumKXFeVt<pkt,pxt,fvt>::emulBklg()
{
	WatchError
	cEmulValue = cExecValue;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			cEmulValue += mPkWghts[tPos] * tPxRec->LateData(this->mTermSys.EmulClk());
		else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
			cEmulValue += mPkWghts[tPos] * (tPxRec->LateBuff - tPxRec->CurrBuff);
	}
	this->mValueRec->updtLate(this->mTermSys.EmulClk(), tc<BuffType,fvt>::iof(cEmulValue));
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif//WghtSumKXFeVtTccIncluded
