/*!
	@file wghtsumkxhfcmhnt.tcc
	@brief The prototype file for WghtSumKXHFcMHnT template class.
	@details This is the prototype file for WghtSumKXHFcMHnT template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef WghtSumKXHFcMHnTTccIncluded
#define WghtSumKXHFcMHnTTccIncluded



#include "cbls/funcs/fcmhns/agghfcmhnt.tcc"
#include "cbls/frames/idx.hh"



openKangarooSpace



/*!
	@class WghtSumKXHFcMHnT
	@brief A class to represent sum fcmhns.
	@details This class represents sum fcmhns.
*/
template <typename pkt, typename pxt, typename fmt>
class WghtSumKXHFcMHnT : public AggHFcMHnT<fmt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys,
								pkt * theWghts, Prm * thePrms, Dim const PrmCount);				//!< Define a sum fcmhn.

		static WghtSumKXHFcMHnT<pkt,pxt,fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static WghtSumKXHFcMHnT<pkt,pxt,fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static WghtSumKXHFcMHnT<pkt,pxt,fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static WghtSumKXHFcMHnT<pkt,pxt,fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static WghtSumKXHFcMHnT<pkt,pxt,fmt> const & cast(Term const & theTerm);	//!< Perform casting.
		static WghtSumKXHFcMHnT<pkt,pxt,fmt> const * cast(Term const * theTerm);	//!< Perform casting.
		static WghtSumKXHFcMHnT<pkt,pxt,fmt> & cast(Term & theTerm);				//!< Perform casting.
		static WghtSumKXHFcMHnT<pkt,pxt,fmt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);							//!< Suits casting?
		static Bll suit(Term * theTerm);							//!< Suits casting?

		//! @}

	private:

		WghtSumKXHFcMHnT(Fss const theFss, Hdl const hdlSys,
					pkt * theWghts, Prm * thePrms, Dim const PrmCount);						//!< Constructor.
		WghtSumKXHFcMHnT(WghtSumKXHFcMHnT<pkt,pxt,fmt> const & that);						//!< Duplicator.
		WghtSumKXHFcMHnT const & operator = (WghtSumKXHFcMHnT<pkt,pxt,fmt> const & that);	//!< Assigner.
		~WghtSumKXHFcMHnT();																//!< Destructor.

		//! @name Identity
		//! @{

		Hvl calcTermHvl() const;				 				//!< Calculate term hash value.
		virtual Bln equate(Term const & theTerm) const; 		//!< Compare terms for equality.

		//! @}

		virtual void compConst();				//!< Compute the term.
		virtual void execAnew();				//!< Execute the term.
		virtual void simulAnew();				//!< Simulate the term.
		virtual void execIncr();				//!< Execute the term.
		virtual void simulIncr();				//!< Simulate the term.

		#if CompLazy
		virtual void execBklg();					//!< Execute the term.
		virtual void emulBklg();					//!< Emulate the term.
		virtual void undoEval(Pos const thePos);	//!< Uneval the param.
		virtual void undoHint(Pos const thePos);	//!< Unhint the param.
		#endif // CompLazy

		typedef typename DataTemp<pkt,pxt>::Type TempType;			//!< Data temp type.
		typedef typename DataBuff<TempType, fmt>::Type BuffType;	//!< Data buff type.

		b1<EvalRec<pxt> const *, kmm> 			mPxRecs;	//!< Parameter records.
		b1<HintRec<pxt> const *, kmm> 			mPhRecs;	//!< Parameter hint records.
		b1< Conv<pxt,BuffType>, kmm> 			mPrOpfs;	//!< Parameter conv operators.
		b1<pkt, kmm>							mPkWghts;	//!< Parameter weights.

		#if SimulDnwd
		BuffType	cSimulMetric;	//!< Simulation cache metric.
		#endif//SimulDnwd

		BuffType	cExecMetric;	//!< Execution cache metric.

		#if CompLazy
		BuffType	cEmulMetric;	//!< Emulation cache metric.
		#endif // CompLazy

		b1<BuffType, kmm> * cExecHintMin;	//!< Execution cache hint min.
		ll<Sqn, kmm>	 * sChgdHintMin;	//!< Hint mins that undergone changes.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fmt>
inline Bll WghtSumKXHFcMHnT<pkt,pxt,fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< WghtSumKXHFcMHnT<pkt,pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fmt>
inline Bll WghtSumKXHFcMHnT<pkt,pxt,fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< WghtSumKXHFcMHnT<pkt,pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fmt>
inline Bll WghtSumKXHFcMHnT<pkt,pxt,fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< WghtSumKXHFcMHnT<pkt,pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pkt, typename pxt, typename fmt>
inline Bll WghtSumKXHFcMHnT<pkt,pxt,fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< WghtSumKXHFcMHnT<pkt,pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXHFcMHnT<pkt,pxt,fmt> const & WghtSumKXHFcMHnT<pkt,pxt,fmt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< WghtSumKXHFcMHnT<pkt,pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXHFcMHnT<pkt,pxt,fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXHFcMHnT<pkt,pxt,fmt> const * WghtSumKXHFcMHnT<pkt,pxt,fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< WghtSumKXHFcMHnT<pkt,pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXHFcMHnT<pkt,pxt,fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXHFcMHnT<pkt,pxt,fmt> & WghtSumKXHFcMHnT<pkt,pxt,fmt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< WghtSumKXHFcMHnT<pkt,pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXHFcMHnT<pkt,pxt,fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXHFcMHnT<pkt,pxt,fmt> * WghtSumKXHFcMHnT<pkt,pxt,fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< WghtSumKXHFcMHnT<pkt,pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<WghtSumKXHFcMHnT<pkt,pxt,fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to a sum.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXHFcMHnT<pkt,pxt,fmt> & WghtSumKXHFcMHnT<pkt,pxt,fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a sum.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXHFcMHnT<pkt,pxt,fmt> * WghtSumKXHFcMHnT<pkt,pxt,fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a sum.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXHFcMHnT<pkt,pxt,fmt> const & WghtSumKXHFcMHnT<pkt,pxt,fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a sum.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXHFcMHnT<pkt,pxt,fmt> const * WghtSumKXHFcMHnT<pkt,pxt,fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pkt, typename pxt, typename fmt>
inline WghtSumKXHFcMHnT<pkt,pxt,fmt>::~WghtSumKXHFcMHnT()
{
	WatchError
	if (cExecHintMin) delete cExecHintMin;
	if (sChgdHintMin) delete sChgdHintMin;
	CatchError
}


/*!
	Define a sum fcmhn in the sys.
*/
template <typename pkt, typename pxt, typename fmt>
Hdl WghtSumKXHFcMHnT<pkt,pxt,fmt>::def(Fss const theFss, Hdl const hdlSys, pkt * theWghts, Prm * thePrms, Dim const PrmCount)
{
	WatchError
	Warn(PrmCount < 1 || PrmCount > MaxDim, eParamCount2(1, MaxDim));

	WghtSumKXHFcMHnT<pkt,pxt,fmt> * tFcMHn = new WghtSumKXHFcMHnT<pkt,pxt,fmt>(theFss, hdlSys, theWghts, thePrms, PrmCount);
	Hdl const tHdl = tFcMHn->defSysFunc();
	if (tHdl != InvHdl) { delete tFcMHn; return tHdl; }

	EvalTbl<pxt> const & tPxTbl = EvalTbl<pxt>::refc(hdlSys);
	HintTbl<pxt> const & tPhTbl = HintTbl<pxt>::refc(hdlSys);
	EvalTbl<fmt> & tFmTbl = EvalTbl<fmt>::refm(hdlSys);
	HintTbl<fmt> & tFdTbl = HintTbl<fmt>::refm(hdlSys);

	b1<Term *, kmm> const & tPrmTerms = tFcMHn->mPrmTerms;
	b1<Pss, kmm> const & tPrmSpecs = tFcMHn->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFcMHn->mPxRecs[tPos] = tPxTbl.ptrcEvalRec(tPxLoc);

		Loc const tPhLoc = getPhLoc(theFss, tPrmTerms[tPos], tPrmSpecs[tPos]);
		tFcMHn->mPhRecs[tPos] = tPhTbl.ptrcHintRec(tPhLoc);

		tFcMHn->mPrOpfs[tPos] = Conv<pxt,BuffType>(theFss, tPrmSpecs[tPos]);
	}

	tFmTbl.setEvalRec(tFcMHn->mMetricRec, tFcMHn->mMetricLoc);
	tFdTbl.setHintRec(tFcMHn->mHintMinRec, tFcMHn->mHintMinLoc, tFcMHn->FuncVars.itemCount());

	tFcMHn->cExecHintMin = new b1<BuffType, kmm>(tFcMHn->FuncVars.itemCount());
	tFcMHn->sChgdHintMin = new ll<Sqn, kmm>(tFcMHn->FuncVars.itemCount());

	tFcMHn->performCompConst();
	tFcMHn->defSysRoot();
	return tFcMHn->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
template <typename pkt, typename pxt, typename fmt>
WghtSumKXHFcMHnT<pkt,pxt,fmt>::WghtSumKXHFcMHnT(Fss const theFss, Hdl const hdlSys,
		pkt * theWghts, Prm * thePrms, Dim const PrmCount) :
		AggHFcMHnT<fmt>(hdlSys, PrmCount), mPxRecs(PrmCount),
		mPhRecs(PrmCount), mPrOpfs(PrmCount), mPkWghts(PrmCount),
		cExecHintMin(Null), sChgdHintMin(Null)
{
	WatchError
	this->setTermCls(TermStub< WghtSumKXHFcMHnT<pkt,pxt,fmt> >::TermCls);
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
WghtSumKXHFcMHnT<pkt,pxt,fmt>::WghtSumKXHFcMHnT(WghtSumKXHFcMHnT const & that) : AggHFcMHnT<fmt>(that),
		mPxRecs(0), mPhRecs(0), mPrOpfs(0), mPkWghts(0)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}


/*!
	The assigner.
*/
template <typename pkt, typename pxt, typename fmt>
WghtSumKXHFcMHnT<pkt,pxt,fmt> const & WghtSumKXHFcMHnT<pkt,pxt,fmt>::operator = (WghtSumKXHFcMHnT<pkt,pxt,fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Calculate hash value of the term.
*/
template <typename pkt, typename pxt, typename fmt>
Hvl WghtSumKXHFcMHnT<pkt,pxt,fmt>::calcTermHvl() const
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
Bln WghtSumKXHFcMHnT<pkt,pxt,fmt>::equate(Term const & theTerm) const
{
	WatchError
	if (this->TermCls != theTerm.TermCls) return false;
	WghtSumKXHFcMHnT<pkt,pxt,fmt> const & tFunc = cast(theTerm);
	b1<Term *, kmm> const & tPrmTerms = tFunc.mPrmTerms;
	b1<Pss, kmm> const & tPrmSpecs = tFunc.mPrmSpecs;
	b1<pkt, kmm> const & tPkWghts = tFunc.mPkWghts;

	if (this->FuncFss != tFunc.FuncFss) return false;
	if (this->mPrmTerms.itemCount() != tPrmTerms.itemCount()) return false;
	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		if (this->mPrmTerms[tPos] != tPrmTerms[tPos]) return false;
		if (this->mPrmSpecs[tPos] != tPrmSpecs[tPos]) return false;
		if (ne<pkt,Bll>::iof(this->mPkWghts[tPos], tPkWghts[tPos])) return false;
	}
	return true;
	CatchError
}



/*!
	Compute the term.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXHFcMHnT<pkt,pxt,fmt>::compConst()
{
	WatchError
	if (!this->updatable())
	{
		cExecMetric = 0;
		for(Sqn tSqn = 0; tSqn < this->FuncVars.itemCount(); ++tSqn)
			cExecHintMin->item(tSqn) = 0;

		for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
		{
			cExecMetric += mPkWghts[tPos] * mPxRecs[tPos]->CurrData();

			for(Sqn tPrmSqn = 0; tPrmSqn < this->PrmVars[tPos].itemCount(); ++tPrmSqn)
			{
				Sqn const tSqn = this->PrmVars[tPos][tPrmSqn];
				cExecHintMin->item(tSqn) += mPkWghts[tPos] *
						mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].CurrData());
			}
		}
		this->mMetricRec->finalise(tc<BuffType,fmt>::iof(cExecMetric));
		for(Sqn tSqn = 0; tSqn < this->FuncVars.itemCount(); ++tSqn)
			this->mHintMinRec->HintFlds[tSqn].finalise(tc<BuffType,fmt>::iof(cExecHintMin->item(tSqn)));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXHFcMHnT<pkt,pxt,fmt>::execAnew()
{
	WatchError
	cExecMetric = 0;
	for(Sqn tSqn = 0; tSqn < this->FuncVars.itemCount(); ++tSqn)
		cExecHintMin->item(tSqn) = 0;

	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if ExecDnwd
		Term::performExecAnew(this->mPrmTerms[tPos]);
		#endif//ExecDnwd

		cExecMetric += mPkWghts[tPos] * mPxRecs[tPos]->CurrData();

		for(Sqn tPrmSqn = 0; tPrmSqn < this->PrmVars[tPos].itemCount(); ++tPrmSqn)
		{
			Sqn const tSqn = this->PrmVars[tPos][tPrmSqn];
			cExecHintMin->item(tSqn) += mPkWghts[tPos] *
				mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].CurrData());
		}
	}

	this->mMetricRec->initCurr(tc<BuffType,fmt>::iof(cExecMetric));
	for(Sqn tSqn = 0; tSqn < this->FuncVars.itemCount(); ++tSqn)
		this->mHintMinRec->HintFlds[tSqn].initCurr(tc<BuffType,fmt>::iof(cExecHintMin->item(tSqn)));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXHFcMHnT<pkt,pxt,fmt>::simulAnew()
{
	WatchError
	BuffType tSimulMetric = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if SimulDnwd
		Term::performSimulAnew(this->mPrmTerms[tPos]);
		#endif//SimulDnwd

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
void WghtSumKXHFcMHnT<pkt,pxt,fmt>::undoEval(Pos const thePos)
{
	WatchError
	cExecMetric -= mPkWghts[thePos] * mPxRecs[thePos]->PrevData(this->mTermSys.ExecClk());
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Perform hint undo for the parameter.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXHFcMHnT<pkt,pxt,fmt>::undoHint(Pos const thePos)
{
	WatchError
	for (Idx tIdx = 0; tIdx < mPhRecs[thePos]->DiffSqns.itemCount(); ++tIdx)
	{
		Sqn const tPrmSqn =  mPhRecs[thePos]->DiffSqns[tIdx];
		Sqn const tSqn = this->PrmVars[thePos][tPrmSqn];
		if (this->mHintUndonePrms->list(thePos).tagged(tPrmSqn))
			cExecHintMin->item(tSqn) -= mPkWghts[thePos] *
					mPrOpfs[thePos](mPhRecs[thePos]->HintFlds[tPrmSqn].PrevBuff);
	}
	CatchError
}
#endif // CompLazy


/*!
	Compute the term in execution mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXHFcMHnT<pkt,pxt,fmt>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		sChgdHintMin->sweep(this->mTermSys.ExecClk());
		for(Idx tIdx = 0; tIdx < this->mExecChgdPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mExecChgdPrms.serial(tIdx);

			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
			if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				cExecMetric += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);

			for (Idx sIdx = 0; sIdx < mPhRecs[tPos]->DiffSqns.itemCount(); ++sIdx)
			{
				Sqn const tPrmSqn =  mPhRecs[tPos]->DiffSqns[sIdx];
				Sqn const tSqn = this->PrmVars[tPos][tPrmSqn];
				cExecHintMin->item(tSqn) += mPkWghts[tPos] * (
						mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].CurrBuff) -
						mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].PrevBuff));
				sChgdHintMin->tagBll(tSqn);
			}
		}
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fmt>::iof(cExecMetric));

		this->mHintMinRec->resetHintDiff(this->mTermSys.ExecClk());
		for(Idx tIdx = 0; tIdx < sChgdHintMin->tagCount(); ++tIdx)
		{
			Sqn const tSqn = sChgdHintMin->serial(tIdx);
			if (this->mHintMinRec->HintFlds[tSqn].updtCurr(this->mTermSys.ExecClk(),
						tc<BuffType,fmt>::iof(cExecHintMin->item(tSqn))))
				 this->mHintMinRec->DiffSqns.insert(tSqn);
		}
		this->runPostExecIncr();
	}
	#endif//ExecUpwd
	#if ExecDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif // CompLazy
		if (this->needExecCandComp()) this->listCandParams();
		if (this->mBlkCandPrms->itemCount())
		{
			sChgdHintMin->sweep(this->mTermSys.ExecClk());
			for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkCandPrms->item(tIdx);
				Term::performExecIncr(this->mPrmTerms[tPos]);
				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
					cExecMetric += mPkWghts[tPos] * (tPxRec->CurrBuff - tPxRec->PrevBuff);

				for (Idx sIdx = 0; sIdx < mPhRecs[tPos]->DiffSqns.itemCount(); ++sIdx)
				{
					Sqn const tPrmSqn =  mPhRecs[tPos]->DiffSqns[sIdx];
					Sqn const tSqn = this->PrmVars[tPos][tPrmSqn];
					cExecHintMin->item(tSqn) += mPkWghts[tPos] * (
							mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].CurrBuff) -
							mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].PrevBuff));
					sChgdHintMin->tagBll(tSqn);
				}
			}
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fmt>::iof(cExecMetric));

			this->mHintMinRec->resetHintDiff(this->mTermSys.ExecClk());
			for(Idx tIdx = 0; tIdx < sChgdHintMin->tagCount(); ++tIdx)
			{
				Sqn const tSqn = sChgdHintMin->serial(tIdx);
				if (this->mHintMinRec->HintFlds[tSqn].updtCurr(this->mTermSys.ExecClk(),
								tc<BuffType,fmt>::iof(cExecHintMin->item(tSqn))))
					 this->mHintMinRec->DiffSqns.insert(tSqn);
			}
		}
	#if CompLazy
	}
	else
	{
		if (this->needExecCandComp()) this->markCandParams();
		sChgdHintMin->sweep(this->mTermSys.ExecClk());
		for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkCandPrms->item(tIdx);
			Term::performExecIncr(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
				cExecMetric += mPkWghts[tPos] * tPxRec->CurrData();
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
					cExecMetric += mPkWghts[tPos] *
						(tPxRec->CurrBuff - tPxRec->PrevBuff);

			if (mPhRecs[tPos]->DiffSqns.itemCount())
				for (Idx sIdx = 0; sIdx < mPhRecs[tPos]->DiffSqns.itemCount(); ++sIdx)
				{
					Sqn const tPrmSqn =  mPhRecs[tPos]->DiffSqns[sIdx];
					Sqn const tSqn = this->PrmVars[tPos][tPrmSqn];
					if (!this->mHintUndonePrms->list(tPos).tagged(tPrmSqn))
					{
						cExecHintMin->item(tSqn) += mPkWghts[tPos] * (
								mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].CurrBuff) -
								mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].PrevBuff));
						sChgdHintMin->tagBll(tSqn);
					}
				}
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
				cExecMetric += mPkWghts[tPos] *
						(tPxRec->CurrBuff - tPxRec->PrevBuff);

			for (Idx sIdx = 0; sIdx < mPhRecs[tPos]->DiffSqns.itemCount(); ++sIdx)
			{
				Sqn const tPrmSqn = mPhRecs[tPos]->DiffSqns[sIdx];
				Sqn const tSqn = this->PrmVars[tPos][tPrmSqn];
				if (!this->mHintUndonePrms->list(tPos).tagged(tPrmSqn))
				{
					cExecHintMin->item(tSqn) += mPkWghts[tPos] * (
						mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].CurrBuff) -
						mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].PrevBuff));
					sChgdHintMin->tagBll(tSqn);
				}
			}
			for(Idx sIdx = 0; sIdx < this->mHintUndonePrms->list(tPos).tagCount(); ++sIdx)
			{
				Sqn const tPrmSqn = this->mHintUndonePrms->list(tPos).serial(sIdx);
				Sqn const tSqn = this->PrmVars[tPos][tPrmSqn];
				cExecHintMin->item(tSqn) += mPkWghts[tPos] *
						mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].CurrData());
				sChgdHintMin->tagBll(tSqn);
			}
		}

		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fmt>::iof(cExecMetric));
		this->mHintMinRec->resetHintDiff(this->mTermSys.ExecClk());
		for(Idx tIdx = 0; tIdx < sChgdHintMin->tagCount(); ++tIdx)
		{
			Sqn const tSqn = sChgdHintMin->serial(tIdx);
			if (this->mHintMinRec->HintFlds[tSqn].updtCurr(this->mTermSys.ExecClk(),
						tc<BuffType,fmt>::iof(cExecHintMin->item(tSqn))))
				 this->mHintMinRec->DiffSqns.insert(tSqn);
		}
	}
	this->runPostExecIncr();
	#endif // CompLazy
	#endif//ExecDnwd
	CatchError
}


#if CompLazy
/*!
	Compute the term in execution mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXHFcMHnT<pkt,pxt,fmt>::execBklg()
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
			cExecMetric += mPkWghts[tPos] *
				(tPxRec->CurrBuff - tPxRec->PrevBuff);

		for (Idx sIdx = 0; sIdx < mPhRecs[tPos]->DiffSqns.itemCount(); ++sIdx)
		{
			Sqn const tPrmSqn =  mPhRecs[tPos]->DiffSqns[sIdx];
			Sqn const tSqn = this->PrmVars[tPos][tPrmSqn];
			if (!this->mHintUndonePrms->list(tPos).tagged(tPrmSqn))
			{
				cExecHintMin->item(tSqn) += mPkWghts[tPos] * (
					mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].CurrBuff) -
					mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].PrevBuff));
				sChgdHintMin->tagBll(tSqn);
			}
		}
		for(Idx sIdx = 0; sIdx < this->mHintUndonePrms->list(tPos).tagCount(); ++sIdx)
		{
			Sqn const tPrmSqn = this->mHintUndonePrms->list(tPos).serial(sIdx);
			Sqn const tSqn = this->PrmVars[tPos][tPrmSqn];
			cExecHintMin->item(tSqn) += mPkWghts[tPos] *
					mPrOpfs[tPos](mPhRecs[tPos]->HintFlds[tPrmSqn].CurrData());
			sChgdHintMin->tagBll(tSqn);
		}
	}

	this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fmt>::iof(cExecMetric));
	this->mHintMinRec->resetHintDiff(this->mTermSys.ExecClk());
	for(Idx tIdx = 0; tIdx < sChgdHintMin->tagCount(); ++tIdx)
	{
		Sqn const tSqn = sChgdHintMin->serial(tIdx);
		if (this->mHintMinRec->HintFlds[tSqn].updtCurr(this->mTermSys.ExecClk(),
					tc<BuffType,fmt>::iof(cExecHintMin->item(tSqn))))
			 this->mHintMinRec->DiffSqns.insert(tSqn);
	}
	this->runPostExecBklg();
	CatchError
}
#endif // CompLazy



/*!
	Compute the term in simulation mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXHFcMHnT<pkt,pxt,fmt>::simulIncr()
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
				tSimulMetric += mPkWghts[tPos] *
					(tPxRec->NextBuff - tPxRec->CurrBuff);
		}
		this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fmt>::iof(tSimulMetric));
		this->runPostSimulIncr();
	}
	#endif	//SimulUpwd
	#if SimulDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif // CompLazy
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
				tSimulMetric += mPkWghts[tPos] *
						mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
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
					tSimulMetric += mPkWghts[tPos] *
						(tPxRec->NextBuff - tPxRec->CurrBuff);
			}
			#endif//SimulFlexi

			this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fmt>::iof(tSimulMetric));
		}
	#if CompLazy
	}
	else	//	defered
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
					cSimulMetric -= mPkWghts[tPos] *
								mPxRecs[tPos]->LateData(this->mTermSys.EmulClk());
				}
				#endif //SimulFixed
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
				#endif //SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
				{
					Pos const tPos = this->mBacklogPrms.serial(tIdx);
					#if SimulFixed
					if (this->mLblFixedPrms.tagged(tPos)) continue;
					#endif //SimulFixed
					Term::performEmulBklg(this->mPrmTerms[tPos]);
					EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

					if (this->mEvalUndonePrms->tagged(tPos))
						cSimulMetric += mPkWghts[tPos] *
							tPxRec->LateData(this->mTermSys.EmulClk());	//	late data, not buff.
					else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
						cSimulMetric += mPkWghts[tPos] *
							(tPxRec->LateBuff - tPxRec->CurrBuff);
				}
			}
		}

		BuffType tSimulMetric = cSimulMetric;

		#if SimulFixed
		for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFixedPrms->item(tIdx);
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			tSimulMetric += mPkWghts[tPos] *
					mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
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
				tSimulMetric += mPkWghts[tPos] * (
							tPxRec->NextData(this->mTermSys.SimulClk()) -
							tPxRec->LateData(this->mTermSys.EmulClk()));
		}
		#endif //SimulFlexi

		this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fmt>::iof(tSimulMetric));
	}
	#endif // CompLazy
	#endif//SimulDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in simulation mode.
*/
template <typename pkt, typename pxt, typename fmt>
void WghtSumKXHFcMHnT<pkt,pxt,fmt>::emulBklg()
{
	WatchError
	cEmulMetric = cExecMetric;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			cEmulMetric += mPkWghts[tPos] *
						tPxRec->LateData(this->mTermSys.EmulClk());
		else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
			cEmulMetric += mPkWghts[tPos] *
					(tPxRec->LateBuff - tPxRec->CurrBuff);
	}
	this->mMetricRec->updtLate(this->mTermSys.EmulClk(), tc<BuffType,fmt>::iof(cEmulMetric));
	CatchError
}
#endif // CompLazy

closeKangarooSpace


#endif//WghtSumKXHFcMHnT
