/*!
	@file gndsumxfcmt.tcc
	@brief The prototype file for GndSumXFcMt template class.
	@details This is the prototype file for GndSumXFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef GndSumXFcMtIncluded
#define GndSumXFcMtIncluded



#include "cbls/funcs/fcms/aggfcmt.tcc"



openKangarooSpace



/*!
	@class GndSumXFcMt
	@brief A class to represent grounded-summation fcm terms.
	@details This class represents grounded-summation fcm terms.
*/
template <typename pxt, typename fmt>
class GndSumXFcMt : public AggFcMt<fmt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys,
													Prm * thePrms, Dim const PrmCount);	//!< Definition.
		static GndSumXFcMt<pxt,fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static GndSumXFcMt<pxt,fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static GndSumXFcMt<pxt,fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static GndSumXFcMt<pxt,fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static GndSumXFcMt<pxt,fmt> const & cast(Term const & theTerm);		//!< Perform casting.
		static GndSumXFcMt<pxt,fmt> const * cast(Term const * theTerm);		//!< Perform casting.
		static GndSumXFcMt<pxt,fmt> & cast(Term & theTerm);					//!< Perform casting.
		static GndSumXFcMt<pxt,fmt> * cast(Term * theTerm);					//!< Perform casting.

		static Bll suit(Term const & theTerm);							//!< Suits casting?
		static Bll suit(Term const * theTerm);							//!< Suits casting?
		static Bll suit(Term & theTerm);								//!< Suits casting?
		static Bll suit(Term * theTerm);								//!< Suits casting?

		//! @}

	private:

		~GndSumXFcMt();														//!< Destructor.
		GndSumXFcMt(GndSumXFcMt<pxt,fmt> const & that);						//!< Duplicator.
		GndSumXFcMt(Fss const theFss, Hdl const hdlSys,
										Prm * thePrms, Dim const PrmCount);	//!< Constructor.
		GndSumXFcMt const & operator = (GndSumXFcMt<pxt,fmt> const & that);	//!< Assigner.

		//! @name Computations
		//! @{

		virtual void compConst();							//!< Compute the term.
		virtual void execAnew();							//!< Execute the term.
		virtual void simulAnew();							//!< Simulate the term.
		virtual void execIncr();							//!< Execute the term.
		virtual void simulIncr();							//!< Simulate the term.
		#if CompLazy
		virtual void execBklg();							//!< Execute the term.
		virtual void emulBklg();							//!< Emulate the term.
		virtual void undoEval(Pos const thePos);			//!< Perform eval undo.
		#endif

		//! @}

	private:

		b1<EvalRec<pxt> const *,kmm> mPxRecs;				//!< Parameter records.
		typedef typename DataBuff<pxt,fmt>::Type BuffType;	//!< Data buffer type.
		#if SimulDnwdCache
		BuffType	cSimulMetric;								//!< Simulation cache metric.
		#endif
		BuffType	cExecMetric;								//!< Execution cache metric.
		#if CompLazy
		BuffType	cEmulMetric;								//!< Emulation cache metric.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll GndSumXFcMt<pxt,fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< GndSumXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll GndSumXFcMt<pxt,fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< GndSumXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll GndSumXFcMt<pxt,fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< GndSumXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll GndSumXFcMt<pxt,fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< GndSumXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline GndSumXFcMt<pxt,fmt> const & GndSumXFcMt<pxt,fmt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< GndSumXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<GndSumXFcMt<pxt,fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline GndSumXFcMt<pxt,fmt> const * GndSumXFcMt<pxt,fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< GndSumXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<GndSumXFcMt<pxt,fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline GndSumXFcMt<pxt,fmt> & GndSumXFcMt<pxt,fmt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< GndSumXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<GndSumXFcMt<pxt,fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline GndSumXFcMt<pxt,fmt> * GndSumXFcMt<pxt,fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< GndSumXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<GndSumXFcMt<pxt,fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to a grounded summation fcm term.
*/
template <typename pxt, typename fmt>
inline GndSumXFcMt<pxt,fmt> & GndSumXFcMt<pxt,fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a grounded summation fcm term.
*/
template <typename pxt, typename fmt>
inline GndSumXFcMt<pxt,fmt> * GndSumXFcMt<pxt,fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a grounded summation fcm term.
*/
template <typename pxt, typename fmt>
inline GndSumXFcMt<pxt,fmt> const & GndSumXFcMt<pxt,fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a grounded summation fcm term.
*/
template <typename pxt, typename fmt>
inline GndSumXFcMt<pxt,fmt> const * GndSumXFcMt<pxt,fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}




/*!
	The destructor.
*/
template <typename pxt, typename fmt>
inline GndSumXFcMt<pxt,fmt>::~GndSumXFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Define a grounded summation fcm term.
*/
template <typename pxt, typename fmt>
Hdl GndSumXFcMt<pxt,fmt>::def(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount)
{
	WatchError
	Warn(PrmCount < 2 || PrmCount > MaxDim, eParamCount2(2, MaxDim));

	GndSumXFcMt<pxt,fmt> * tFcM = new GndSumXFcMt<pxt,fmt>(theFss, hdlSys, thePrms, PrmCount);
	Hdl const tHdl = tFcM->defSysFunc();
	if (tHdl != InvHdl) { delete tFcM; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<fmt> & tFmtTbl = EvalTbl<fmt>::refm(hdlSys);

	b1<Term *, kmm> const & tPrmTerms = tFcM->mPrmTerms;
	b1<Pss, kmm> const & tPrmSpecs = tFcM->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Warn(tPrmTerms[tPos]->TermGen == Tf, eTermNotGrounded);

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
GndSumXFcMt<pxt,fmt>::GndSumXFcMt(Fss const theFss, Hdl const hdlSys,
				Prm * thePrms, Dim const PrmCount) :
		AggFcMt<fmt>(hdlSys, PrmCount), mPxRecs(PrmCount)
{
	WatchError
	this->setTermCls(TermStub< GndSumXFcMt<pxt,fmt> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Unordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename fmt>
GndSumXFcMt<pxt,fmt>::GndSumXFcMt(GndSumXFcMt const & that) : AggFcMt<fmt>(that), mPxRecs(0)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename pxt, typename fmt>
GndSumXFcMt<pxt,fmt> const & GndSumXFcMt<pxt,fmt>::operator = (GndSumXFcMt<pxt,fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template <typename pxt, typename fmt>
void GndSumXFcMt<pxt,fmt>::compConst()
{
	WatchError
	if (!this->updatable())
	{
		cExecMetric = 0;
		for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
			cExecMetric += mPxRecs[tPos]->CurrData();
		this->mMetricRec->finalise(tc<BuffType,fmt>::iof(cExecMetric));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void GndSumXFcMt<pxt,fmt>::execAnew()
{
	WatchError
	cExecMetric = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
		cExecMetric += mPxRecs[tPos]->CurrData();
	this->mMetricRec->initCurr(tc<BuffType,fmt>::iof(cExecMetric));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename fmt>
void GndSumXFcMt<pxt,fmt>::simulAnew()
{
	WatchError
	BuffType tSimulMetric = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
		tSimulMetric += mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
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
template <typename pxt, typename fmt>
void GndSumXFcMt<pxt,fmt>::undoEval(Pos const thePos)
{
	WatchError
	cExecMetric -= mPxRecs[thePos]->PrevData(this->mTermSys.ExecClk());
	CatchError
}
#endif	//CompLazy



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void GndSumXFcMt<pxt,fmt>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		if (!this->mTermSys.chkExecMode(SwapProp)
					|| this->mExecChgdPrms.tagCount() != this->mTermSys.ExecAsgnVars().tagCount())
		{
			for(Idx tIdx = 0; tIdx < this->mExecChgdPrms.tagCount(); ++tIdx)
			{
				Pos const tPos = this->mExecChgdPrms.serial(tIdx);
				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
					cExecMetric += tPxRec->CurrBuff - tPxRec->PrevBuff;
			}
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fmt>::iof(cExecMetric));
		}
		this->runPostExecIncr();
	}
	#endif	//ExecUpwd
	#if ExecDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//CompLazy
		if (this->needExecCandComp()) this->listCandParams();
		if (this->mBlkCandPrms->itemCount() && (!this->mTermSys.chkExecMode(SwapProp)
					|| this->mBlkCandPrms->itemCount() != this->mTermSys.ExecAsgnVars().tagCount()))
		{
			for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkCandPrms->item(tIdx);
				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
					cExecMetric += tPxRec->CurrBuff - tPxRec->PrevBuff;
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
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
				cExecMetric += tPxRec->CurrData();
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				cExecMetric += tPxRec->CurrBuff - tPxRec->PrevBuff;
		}

		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fmt>::iof(cExecMetric));
	}
	this->runPostExecIncr();
	#endif	//CompLazy
	#endif	//ExecDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void GndSumXFcMt<pxt,fmt>::execBklg()
{
	WatchError
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			cExecMetric += tPxRec->CurrData();
		else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			cExecMetric += tPxRec->CurrBuff - tPxRec->PrevBuff;
	}

	this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), tc<BuffType,fmt>::iof(cExecMetric));
	this->runPostExecBklg();
	CatchError
}
#endif	//CompLazy



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename fmt>
void GndSumXFcMt<pxt,fmt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		if (!this->mTermSys.chkSimulMode(SwapProp)
					|| this->mSimulChgdPrms.tagCount() != this->mTermSys.SimulAsgnVars().tagCount())
		{
			BuffType tSimulMetric = cExecMetric;
			for(Idx tIdx = 0; tIdx < this->mSimulChgdPrms.tagCount(); ++tIdx)
			{
				Pos const tPos = this->mSimulChgdPrms.serial(tIdx);
				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
					tSimulMetric += tPxRec->NextBuff - tPxRec->CurrBuff;
			}
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fmt>::iof(tSimulMetric));
		}
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

		if (this->mTermSys.chkSimulMode(SwapProp))
		{
			#if SimulFixedFlexi
			if (this->mBlkFixedPrms->itemCount() + this->mBlkFlexiPrms->itemCount() ==
					this->mTermSys.SimulAsgnVars().tagCount()) return;
			#elif SimulFixedOnly
			if (this->mBlkFixedPrms->itemCount() == this->mTermSys.SimulAsgnVars().tagCount())
				return;
			#elif SimulFlexiOnly
			if (this->mBlkFlexiPrms->itemCount() == this->mTermSys.SimulAsgnVars().tagCount())
				return;
			#endif
		}

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
					tSimulMetric += tPxRec->NextBuff - tPxRec->CurrBuff;
			}
			#endif//SimulFlexi

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
		if (this->needSimulFixedComp())	this->markFixedParams();
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
		#endif //SimulFixed

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
template <typename pxt, typename fmt>
void GndSumXFcMt<pxt,fmt>::emulBklg()
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
	this->mMetricRec->updtLate(this->mTermSys.EmulClk(), tc<BuffType,fmt>::iof(cEmulMetric));
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif//GndSumXFcMtTccIncluded
