/*!
	@file sumpopxbfcmt.tcc
	@brief The prototype file for SumPopXBFcMt template class.
	@details This is the prototype file for SumPopXBFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SumPopXBFcMtTccIncluded
#define SumPopXBFcMtTccIncluded



#include "cbls/funcs/fcms/aggfcmt.tcc"



openKangarooSpace



/*!
	@class SumPopXBFcMt
	@brief A class to represent summation pipe operator fcm terms.
	@details This class represents summation pipe operator fcm terms.
*/
template <typename pxt, typename pop>
class SumPopXBFcMt : public AggFcMt<typename pop::OutTyp>
{
	public:
		typedef pop bind;		//!< The bound pipe operator.

		static Hdl def(Fss const theFss, Hdl const hdlSys,
							Prm * thePrms, Dim const PrmCount, bind const & theBind);	//!< Definition.

		static SumPopXBFcMt<pxt,pop> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static SumPopXBFcMt<pxt,pop> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static SumPopXBFcMt<pxt,pop> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static SumPopXBFcMt<pxt,pop> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static SumPopXBFcMt<pxt,pop> const & cast(Term const & theTerm);	//!< Perform casting.
		static SumPopXBFcMt<pxt,pop> const * cast(Term const * theTerm);	//!< Perform casting.
		static SumPopXBFcMt<pxt,pop> & cast(Term & theTerm);				//!< Perform casting.
		static SumPopXBFcMt<pxt,pop> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);						//!< Suits casting?
		static Bll suit(Term const * theTerm);						//!< Suits casting?
		static Bll suit(Term & theTerm);							//!< Suits casting?
		static Bll suit(Term * theTerm);							//!< Suits casting?

		//! @}

	private:

		~SumPopXBFcMt();														//!< Destructor.
		SumPopXBFcMt(SumPopXBFcMt<pxt,pop> const & that);						//!< Duplicator.
		SumPopXBFcMt(Fss const theFss, Hdl const hdlSys,
					Prm * thePrms, Dim const PrmCount, bind const & theBind);	//!< Constructor.
		SumPopXBFcMt const & operator = (SumPopXBFcMt<pxt,pop> const & that);	//!< Assigner.

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

		typedef typename pop::InxTyp TempType;					//!< Temporary type.
		typedef typename DataBuff<pxt,TempType>::Type BuffType;	//!< Data buff type.

		#if SimulDnwdCache
		BuffType					cSimulMetric;	//!< Simulation cache metric.
		#endif
		BuffType					cExecMetric;	//!< Execution cache metric.
		#if CompLazy
		BuffType					cEmulMetric;	//!< Emulation cache metric.
		#endif
		bind const					mBind;			//!< The bind pop.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll SumPopXBFcMt<pxt,pop>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< SumPopXBFcMt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll SumPopXBFcMt<pxt,pop>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< SumPopXBFcMt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll SumPopXBFcMt<pxt,pop>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< SumPopXBFcMt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll SumPopXBFcMt<pxt,pop>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< SumPopXBFcMt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline SumPopXBFcMt<pxt,pop> const & SumPopXBFcMt<pxt,pop>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< SumPopXBFcMt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<SumPopXBFcMt<pxt,pop> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline SumPopXBFcMt<pxt,pop> const * SumPopXBFcMt<pxt,pop>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< SumPopXBFcMt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<SumPopXBFcMt<pxt,pop> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline SumPopXBFcMt<pxt,pop> & SumPopXBFcMt<pxt,pop>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< SumPopXBFcMt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<SumPopXBFcMt<pxt,pop> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline SumPopXBFcMt<pxt,pop> * SumPopXBFcMt<pxt,pop>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< SumPopXBFcMt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<SumPopXBFcMt<pxt,pop> *>(theTerm);
	CatchError
}



/*!
	Refer to a summation fcm term.
*/
template <typename pxt, typename pop>
inline SumPopXBFcMt<pxt,pop> & SumPopXBFcMt<pxt,pop>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a summation fcm term.
*/
template <typename pxt, typename pop>
inline SumPopXBFcMt<pxt,pop> * SumPopXBFcMt<pxt,pop>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a summation fcm term.
*/
template <typename pxt, typename pop>
inline SumPopXBFcMt<pxt,pop> const & SumPopXBFcMt<pxt,pop>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a summation fcm term.
*/
template <typename pxt, typename pop>
inline SumPopXBFcMt<pxt,pop> const * SumPopXBFcMt<pxt,pop>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pxt, typename pop>
inline SumPopXBFcMt<pxt,pop>::~SumPopXBFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Define a summation fcm in the sys.
*/
template <typename pxt, typename pop>
Hdl SumPopXBFcMt<pxt,pop>::def( Fss const theFss, Hdl const hdlSys,
				Prm * thePrms, Dim const PrmCount, bind const & theBind)
{
	WatchError
	Wchk(PrmCount < 2 || PrmCount > MaxDim) Wtxt(eParamCount2(2, MaxDim));

	SumPopXBFcMt<pxt,pop> * tFcM =
			new SumPopXBFcMt<pxt,pop>(theFss, hdlSys, thePrms, PrmCount, theBind);
	Hdl const tHdl = tFcM->defSysFunc();
	if (tHdl != InvHdl) { delete tFcM; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<typename pop::OutTyp> & tOutTbl =
			EvalTbl<typename pop::OutTyp>::refm(hdlSys);

	b1<Term *, kmm> const & tPrmTerms = tFcM->mPrmTerms;
	b1<Pss, kmm> const & tPrmSpecs = tFcM->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFcM->mPxRecs[tPos] = tPxtTbl.ptrcEvalRec(tPxLoc);
	}
	tOutTbl.setEvalRec(tFcM->mMetricRec, tFcM->mMetricLoc);

	tFcM->performCompConst();
	tFcM->defSysRoot();
	return tFcM->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
template <typename pxt, typename pop>
SumPopXBFcMt<pxt,pop>::SumPopXBFcMt(Fss const theFss, Hdl const hdlSys,
			Prm * thePrms, Dim const PrmCount, bind const & theBind) :
		AggFcMt<typename pop::OutTyp>(hdlSys, PrmCount), mPxRecs(PrmCount), mBind(theBind)
{
	WatchError
	this->setTermCls(TermStub< SumPopXBFcMt<pxt,pop> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Unordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename pop>
SumPopXBFcMt<pxt,pop>::SumPopXBFcMt(SumPopXBFcMt const & that) :
		AggFcMt<typename pop::OutTyp>(that), mPxRecs(0), mBind(that.mBind)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename pxt, typename pop>
SumPopXBFcMt<pxt,pop> const &
SumPopXBFcMt<pxt,pop>::operator =
	(SumPopXBFcMt<pxt,pop> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Calculate hash value of the term.
*/
template <typename pxt, typename pop>
Hvl SumPopXBFcMt<pxt,pop>::calcTermHvl() const
{
	WatchError
	Hvl tHvl = 0;
	tHvl = mixHash(tHvl, calcHash(this->TermCls));
	tHvl = mixHash(tHvl, calcHash(this->FuncFss));

	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		tHvl = mixHash(tHvl, calcHash(this->mPrmTerms[tPos]));
		tHvl = mixHash(tHvl, calcHash(this->mPrmSpecs[tPos]));
	}

	tHvl = mixHash(tHvl, this->mBind.hashval());
	return tHvl;
	CatchError
}



/*!
	Compare two terms for equality.
*/
template <typename pxt, typename pop>
Bll SumPopXBFcMt<pxt,pop>::equate(Term const & theTerm) const
{
	WatchError
	if (this->TermCls != theTerm.TermCls) return false;
	SumPopXBFcMt<pxt,pop> const & tSumPopXBFcMt = cast(theTerm);
	if (this->FuncFss != tSumPopXBFcMt.FuncFss) return false;
	if (this->mPrmTerms.itemCount() != tSumPopXBFcMt.mPrmTerms.itemCount())
		return false;

	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		if (this->mPrmTerms[tPos] != tSumPopXBFcMt.mPrmTerms[tPos]) return false;
		if (this->mPrmSpecs[tPos] != tSumPopXBFcMt.mPrmSpecs[tPos]) return false;
	}
	if (!mBind.equate(tSumPopXBFcMt.mBind)) return false;
	return true;
	CatchError
}



/*!
	Compute the term.
*/
template <typename pxt, typename pop>
void SumPopXBFcMt<pxt,pop>::compConst()
{
	WatchError
	if (!this->updatable())
	{
		cExecMetric = 0;
		for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
			cExecMetric += mPxRecs[tPos]->CurrData();
		this->mMetricRec->finalise(mBind.iof(tc<BuffType,TempType>::iof(cExecMetric)));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename pop>
void SumPopXBFcMt<pxt,pop>::execAnew()
{
	WatchError
	cExecMetric = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if ExecDnwd
		Term::performExecAnew(this->mPrmTerms[tPos]);
		#endif
		cExecMetric += mPxRecs[tPos]->CurrData();
	}
	this->mMetricRec->initCurr(mBind.iof(tc<BuffType,TempType>::iof(cExecMetric)));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename pop>
void SumPopXBFcMt<pxt,pop>::simulAnew()
{
	WatchError
	BuffType tSimulMetric = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if SimulDnwd
		Term::performSimulAnew(this->mPrmTerms[tPos]);
		#endif
		tSimulMetric += mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
	}
	this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
			mBind.iof(tc<BuffType,TempType>::iof(tSimulMetric)));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}


#if CompLazy
/*!
	Perform eval undo for the parameter.
*/
template <typename pxt, typename pop>
void SumPopXBFcMt<pxt,pop>::undoEval(Pos const thePos)
{
	WatchError
	cExecMetric -= mPxRecs[thePos]->PrevData(this->mTermSys.ExecClk());
	CatchError
}
#endif	//CompLazy


/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename pop>
void SumPopXBFcMt<pxt,pop>::execIncr()
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
				cExecMetric += tPxRec->CurrBuff - tPxRec->PrevBuff;
		}
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
			mBind.iof(tc<BuffType,TempType>::iof(cExecMetric)));
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
					cExecMetric += tPxRec->CurrBuff - tPxRec->PrevBuff;
			}
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
				mBind.iof(tc<BuffType,TempType>::iof(cExecMetric)));
		}
	#if CompLazy
	}
	else	//	backlog
	{
		if (this->needExecCandComp()) this->markCandParams();
		for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkCandPrms->item(tIdx);
			Term::performExecIncr(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
				cExecMetric += tPxRec->CurrData();
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				cExecMetric += tPxRec->CurrBuff - tPxRec->PrevBuff;
		}

		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;

			Term::performExecBklg(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
				cExecMetric += tPxRec->CurrData();
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				cExecMetric += tPxRec->CurrBuff - tPxRec->PrevBuff;
		}

		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
			mBind.iof(tc<BuffType,TempType>::iof(cExecMetric)));
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
template <typename pxt, typename pop>
void SumPopXBFcMt<pxt,pop>::execBklg()
{
	WatchError
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performExecBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			cExecMetric += tPxRec->CurrData();
		else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			cExecMetric += tPxRec->CurrBuff - tPxRec->PrevBuff;
	}

	this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
		mBind.iof(tc<BuffType,TempType>::iof(cExecMetric)));
	this->runPostExecBklg();
	CatchError
}
#endif	//CompLazy


/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename pop>
void SumPopXBFcMt<pxt,pop>::simulIncr()
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
				tSimulMetric += tPxRec->NextBuff - tPxRec->CurrBuff;
		}
		this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
				mBind.iof(tc<BuffType,TempType>::iof(tSimulMetric)));
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
				cSimulMetric -= mPxRecs[tPos]->CurrData();
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
			BuffType tSimulMetric = cSimulMetric;
			#else
			BuffType tSimulMetric = cExecMetric;
			#endif

			#if SimulFixed
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				Term::performSimulIncr(this->mPrmTerms[tPos]);
				tSimulMetric += mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
			}
			#endif

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
					tSimulMetric += tPxRec->NextBuff - tPxRec->CurrBuff;
			}
			#endif

			this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
				mBind.iof(tc<BuffType,TempType>::iof(tSimulMetric)));
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
					cSimulMetric -= mPxRecs[tPos]->LateData(this->mTermSys.EmulClk());
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
						cSimulMetric -= mPxRecs[tPos]->CurrData();
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
						cSimulMetric += tPxRec->LateData(this->mTermSys.EmulClk());	//	late data, not buff.
					else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
						cSimulMetric += tPxRec->LateBuff - tPxRec->CurrBuff;
				}
			}
		}

		BuffType tSimulMetric = cSimulMetric;

		#if SimulFixed
		for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFixedPrms->item(tIdx);
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			tSimulMetric += mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
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
				tSimulMetric += tPxRec->NextData(this->mTermSys.SimulClk()) -
							tPxRec->LateData(this->mTermSys.EmulClk());
		}
		#endif//SimulFlexi

		this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
				mBind.iof(tc<BuffType,TempType>::iof(tSimulMetric)));
	}
	#endif	//	CompLazy
	#endif	//	SimulDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename pop>
void SumPopXBFcMt<pxt,pop>::emulBklg()
{
	WatchError
	cEmulMetric = cExecMetric;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			cEmulMetric += tPxRec->LateData(this->mTermSys.EmulClk());
		else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
			cEmulMetric += tPxRec->LateBuff - tPxRec->CurrBuff;
	}
	this->mMetricRec->updtLate(this->mTermSys.EmulClk(), mBind.iof(tc<BuffType,TempType>::iof(cEmulMetric)));
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif//SumPopXBFcMtTccIncluded
