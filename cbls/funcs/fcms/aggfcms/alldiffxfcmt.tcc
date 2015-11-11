/*!
	@file alldiffxfcmt.tcc
	@brief The prototype file for AllDiffXFcMt template class.
	@details This is the prototype file for AllDiffXFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef AllDiffXFcMtTccIncluded
#define AllDiffXFcMtTccIncluded



#include "cbls/funcs/fcms/aggfcmt.tcc"
#include "cbls/frames/idx.hh"



openKangarooSpace



/*!
	@class AllDiffXFcMt
	@brief A class to represent all different fcms.
	@details This class represents all different fcms.
*/
template <typename pxt, typename fmt>
class AllDiffXFcMt : public AggFcMt<fmt>
{
	public:
		static Hdl def(Fss const theFss, Hdl const hdlSys, Prm * thePrms, Dim const PrmCount);	//!< Definition.

		static AllDiffXFcMt<pxt,fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static AllDiffXFcMt<pxt,fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static AllDiffXFcMt<pxt,fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static AllDiffXFcMt<pxt,fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static AllDiffXFcMt<pxt,fmt> const & cast(Term const & theTerm);	//!< Perform casting.
		static AllDiffXFcMt<pxt,fmt> const * cast(Term const * theTerm);	//!< Perform casting.
		static AllDiffXFcMt<pxt,fmt> & cast(Term & theTerm);				//!< Perform casting.
		static AllDiffXFcMt<pxt,fmt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);							//!< Suits casting?
		static Bll suit(Term const * theTerm);							//!< Suits casting?
		static Bll suit(Term & theTerm);								//!< Suits casting?
		static Bll suit(Term * theTerm);								//!< Suits casting?

		//! @}

	private:

		AllDiffXFcMt(Fss const theFss, Hdl const hdlSys,
											Prm * thePrms, Dim const PrmCount);	//!< Constructor.
		AllDiffXFcMt(AllDiffXFcMt<pxt,fmt> const & that);						//!< Duplicator.
		AllDiffXFcMt const & operator = (AllDiffXFcMt<pxt,fmt> const & that);	//!< Assigner.
		~AllDiffXFcMt();														//!< Destructor.

		virtual void syncExecClk();				//!< Sync the exec clock.
		virtual void syncSimulClk();			//!< Sync the simul clock.
		#if SimulDnwdCache
		virtual void syncSimulCacheClk();		//!< Sync the simul cache clock.
		#endif

		virtual void compConst();				//!< Compute the term.
		virtual void execAnew();				//!< Execute the term.
		virtual void simulAnew();				//!< Simulate the term.
		virtual void execIncr();				//!< Execute the term.
		virtual void simulIncr();				//!< Simulate the term.

		#if CompLazy
		virtual void execBklg();				//!< Execute the term.
		virtual void emulBklg();				//!< Emulate the term.
		virtual void undoEval(Pos const thePos);//!< Perform eval undo.
		#endif // CompLazy

		typedef typename DataStub<fmt>::TempBuff TempType;	//!< Temp buff type.
		typedef typename DataBuff<pxt,fmt>::Type BuffType;	//!< Data buff type.

		b1<EvalRec<pxt> const *,kmm> 	mPxRecs;			//!< Parameter records.

		#if SimulDnwdCache
		Num	cSimulMetric;		//!< Simulation cache metric.
		#endif//SimulDnwd

		Num	cExecMetric;		//!< Execution cache metric.

		#if CompLazy
		Num	cEmulMetric;		//!< Emulation cache metric.
		#endif // CompLazy

		//	the number of possible values would be 2 * #params
		hsd<pxt,nmmh>		cExecXdats;		//!< Exec xdats for the parameters.
		b1<Dim,kmm>			cCurrFreqs;		//!< Curr freqs of the xdats.
		b1<Dim,kmm>			cPrevFreqs;		//!< Prev freqs for changed Xdats.
		ll<Itr,kmm>			cXdatItrs;		//!< Itrs of Xdats with changes.

		//	maintained for each parameter and used in execution.
		b1<Itr,kmm> 		cCurrPxItrs;	//!< Curr xdat iterators for params.
		b1<Itr,kmm> 		sPrevPxItrs;	//!< Prev Xdat iterators for params.

		hsc<pxt,nmmh>		sNextXdats;		//!< Simul xdats for the parameters.
		b1<Dim,kmm>			sNextFreqs;		//!< Simul xdats for the parameters.

		#if CompLazy
		hsc<pxt,nmmh>		cEmulXdats;		//!< Emulation xdats.
		b1<Dim,kmm>			cEmulFreqs;		//!< Emulation freqs.
		#endif

		#if SimulDnwdCache
		//	used in simulation
		hsc<pxt,nmmh>		cSimulXdats;	//!< Cache for simul xdats.
		b1<Dim,kmm>			cSimulFreqs;	//!< Cache for simul freqs.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AllDiffXFcMt<pxt,fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< AllDiffXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AllDiffXFcMt<pxt,fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< AllDiffXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AllDiffXFcMt<pxt,fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< AllDiffXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AllDiffXFcMt<pxt,fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< AllDiffXFcMt<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AllDiffXFcMt<pxt,fmt> const & AllDiffXFcMt<pxt,fmt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< AllDiffXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AllDiffXFcMt<pxt,fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AllDiffXFcMt<pxt,fmt> const * AllDiffXFcMt<pxt,fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< AllDiffXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AllDiffXFcMt<pxt,fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AllDiffXFcMt<pxt,fmt> & AllDiffXFcMt<pxt,fmt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< AllDiffXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AllDiffXFcMt<pxt,fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AllDiffXFcMt<pxt,fmt> * AllDiffXFcMt<pxt,fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< AllDiffXFcMt<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AllDiffXFcMt<pxt,fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to an all different.
*/
template <typename pxt, typename fmt>
inline AllDiffXFcMt<pxt,fmt> & AllDiffXFcMt<pxt,fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an all different.
*/
template <typename pxt, typename fmt>
inline AllDiffXFcMt<pxt,fmt> * AllDiffXFcMt<pxt,fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an all different.
*/
template <typename pxt, typename fmt>
inline AllDiffXFcMt<pxt,fmt> const & AllDiffXFcMt<pxt,fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an all different.
*/
template <typename pxt, typename fmt>
inline AllDiffXFcMt<pxt,fmt> const * AllDiffXFcMt<pxt,fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pxt, typename fmt>
inline AllDiffXFcMt<pxt,fmt>::~AllDiffXFcMt()
{
	WatchError
	CatchError
}


/*!
	Define an all different fcm in the sys.
*/
template <typename pxt, typename fmt>
Hdl AllDiffXFcMt<pxt,fmt>::def(Fss const theFss, Hdl const hdlSys, Prm * thePrms, Dim const PrmCount)
{
	WatchError
	Warn(PrmCount < 2 || PrmCount > MaxDim, eParamCount2(2, MaxDim));

	AllDiffXFcMt<pxt,fmt> * tFcM = new AllDiffXFcMt<pxt,fmt>(theFss, hdlSys, thePrms, PrmCount);
	Hdl const tHdl = tFcM->defSysFunc();
	if (tHdl != InvHdl) { delete tFcM; return tHdl; }

	EvalTbl<pxt> const & tPxTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<fmt> & tFmTbl = EvalTbl<fmt>::refm(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFcM->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFcM->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFcM->mPxRecs[tPos] = tPxTbl.ptrcEvalRec(tPxLoc);
	}

	tFmTbl.setEvalRec(tFcM->mMetricRec, tFcM->mMetricLoc);

	tFcM->performCompConst();
	tFcM->defSysRoot();
	return tFcM->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
template <typename pxt, typename fmt>
AllDiffXFcMt<pxt,fmt>::AllDiffXFcMt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) : AggFcMt<fmt>(hdlSys, PrmCount), mPxRecs(PrmCount),
		cExecXdats(PrmCount << 1), cCurrFreqs(cExecXdats.slotCount()), cPrevFreqs(cExecXdats.slotCount()),
		cXdatItrs(cExecXdats.slotCount()), cCurrPxItrs(PrmCount), sPrevPxItrs(PrmCount),
		sNextXdats(PrmCount << 1), sNextFreqs(sNextXdats.slotCount())
		#if CompLazy
		, cEmulXdats(PrmCount), cEmulFreqs(cEmulXdats.slotCount())
		#endif
		#if SimulDnwdCache
		, cSimulXdats(PrmCount), cSimulFreqs(cSimulXdats.slotCount())
		#endif
{
	WatchError
	this->setTermCls(TermStub< AllDiffXFcMt<pxt,fmt> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Unordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename fmt>
AllDiffXFcMt<pxt,fmt>::AllDiffXFcMt(AllDiffXFcMt const & that) : AggFcMt<fmt>(that), mPxRecs(0),
		cExecXdats(0), cCurrFreqs(0), cPrevFreqs(0), cXdatItrs(0), cCurrPxItrs(0),
		sPrevPxItrs(0), sNextXdats(0), sNextFreqs(0)
		#if CompLazy
		, cEmulXdats(0), cEmulFreqs(0)
		#endif
		#if SimulDnwdCache
		, cSimulXdats(0), cSimulFreqs(0)
		#endif
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}


/*!
	The assigner.
*/
template <typename pxt, typename fmt>
AllDiffXFcMt<pxt,fmt> const & AllDiffXFcMt<pxt,fmt>::operator = (AllDiffXFcMt<pxt,fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template <typename pxt, typename fmt>
void AllDiffXFcMt<pxt,fmt>::compConst()
{
	WatchError
	if (this->updatable())
	{
		for(Pos tPos = 1; tPos < this->mPrmTerms.itemCount(); ++tPos)
			if (this->mPrmTerms[tPos] == this->mPrmTerms[tPos - 1] &&
					this->mPrmSpecs[tPos] == this->mPrmSpecs[tPos - 1])
				{ this->setUpdatable(false); break;}
	}

	if (this->updatable()) return;

	cExecMetric = mPxRecs.itemCount();	//	violation = n - #unique-value

	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		Itr tCurrItr;

		pxt const & tCurrX = mPxRecs[tPos]->CurrData();
		if (cExecXdats.insertBll(tCurrX, tCurrItr))
		{
			--cExecMetric;
			cCurrFreqs[tCurrItr] = 1;
		}
		else
			++cCurrFreqs[tCurrItr];
		cCurrPxItrs[tPos] = tCurrItr;
	}

	this->mMetricRec->finalise(cExecMetric);
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void AllDiffXFcMt<pxt,fmt>::execAnew()
{
	WatchError
	cExecMetric = mPxRecs.itemCount();

	cExecXdats.clear();
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if ExecDnwd
		Term::performExecAnew(this->mPrmTerms[tPos]);
		#endif//ExecDnwd

		Itr tCurrItr;
		pxt const & tCurrX = mPxRecs[tPos]->CurrData();
		if (cExecXdats.insertBll(tCurrX, tCurrItr))
		{
			--cExecMetric;
			cCurrFreqs[tCurrItr] = 1;
		}
		else
			++cCurrFreqs[tCurrItr];
		cCurrPxItrs[tPos] = tCurrItr;
	}

	cXdatItrs.sweep(this->mTermSys.ExecClk());	// this help uneval

	this->mMetricRec->initCurr(cExecMetric);
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename fmt>
void AllDiffXFcMt<pxt,fmt>::simulAnew()
{
	WatchError
	sNextXdats.clear(this->mTermSys.SimulClk());
	BuffType tSimulMetric = mPxRecs.itemCount();
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if SimulDnwd
		Term::performSimulAnew(this->mPrmTerms[tPos]);
		#endif//SimulDnwd
		pxt const & tNextX = mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
		if (sNextXdats.insertBll(tNextX))
			--tSimulMetric;
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
template <typename pxt, typename fmt>
void AllDiffXFcMt<pxt,fmt>::undoEval(Pos const thePos)
{
	WatchError
	// delete prev value
	Itr tXdatItr = cCurrPxItrs[thePos];
	if (cXdatItrs.tagBll(tXdatItr))
		cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
	--cCurrFreqs[tXdatItr];
	if (!cCurrFreqs[tXdatItr])
		++cExecMetric;
	CatchError
}
#endif // CompLazy



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void AllDiffXFcMt<pxt,fmt>::execIncr()
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
			{
				// delete prev value
				Itr tXdatItr = cCurrPxItrs[tPos];
				if (cXdatItrs.tagBll(tXdatItr))
					cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
				--cCurrFreqs[tXdatItr];
				if (!cCurrFreqs[tXdatItr])
					++cExecMetric;

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;

				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
					--cExecMetric;
				if (cXdatItrs.tagBll(tXdatItr))
					cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
				++cCurrFreqs[tXdatItr];
			}
		}

		for(Idx tIdx = 0; tIdx < cXdatItrs.tagCount(); ++tIdx)
		{
			Itr tXdatItr = cXdatItrs[tIdx];

			if (!cCurrFreqs[tXdatItr])	//	new freq == 0
				cExecXdats.removeWithItr(tXdatItr);
				//	after elimination, the index is stll assumed to be valid
				//	for the properties that use the index such as XdatRoots, CurrFreqs
				//	PrevFreqs, and XdatIdxs.
		}

		cXdatItrs.sweep(this->mTermSys.ExecClk());
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecMetric);
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
			for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkCandPrms->item(tIdx);
				Term::performExecIncr(this->mPrmTerms[tPos]);
				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				{
					// delete prev value
					Itr tXdatItr = cCurrPxItrs[tPos];
					if (cXdatItrs.tagBll(tXdatItr))
						cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
					--cCurrFreqs[tXdatItr];
					if (!cCurrFreqs[tXdatItr])
						++cExecMetric;

					//	add new value
					pxt const & tCurrX = mPxRecs[tPos]->CurrData();
					if (cExecXdats.insertBll(tCurrX, tXdatItr))
						cCurrFreqs[tXdatItr] = 0;
					sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
					cCurrPxItrs[tPos] = tXdatItr;

					if (!cCurrFreqs[tXdatItr])
						--cExecMetric;
					if (cXdatItrs.tagBll(tXdatItr))
						cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
					++cCurrFreqs[tXdatItr];
				}
			}

			for(Idx tIdx = 0; tIdx < cXdatItrs.tagCount(); ++tIdx)
			{
				Itr tXdatItr = cXdatItrs[tIdx];

				if (!cCurrFreqs[tXdatItr])	//	new freq == 0
					cExecXdats.removeWithItr(tXdatItr);
			}

			cXdatItrs.sweep(this->mTermSys.ExecClk());
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecMetric);
		}	//	mBlkCandPrms
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
			{
				//	add new value
				Itr tXdatItr;
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;
				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
					--cExecMetric;
				if (cXdatItrs.tagBll(tXdatItr))
					cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
				++cCurrFreqs[tXdatItr];
			}
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			{
				// delete prev value
				Itr tXdatItr = cCurrPxItrs[tPos];
				if (cXdatItrs.tagBll(tXdatItr))
					cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
				--cCurrFreqs[tXdatItr];
				if (!cCurrFreqs[tXdatItr])
					++cExecMetric;

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;
				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
					--cExecMetric;
				if (cXdatItrs.tagBll(tXdatItr))
					cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
				++cCurrFreqs[tXdatItr];
			}
		}

		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;

			Term::performExecBklg(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
			{
				//	add new value
				Itr tXdatItr;
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;
				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
					--cExecMetric;

				if (cXdatItrs.tagBll(tXdatItr))
					cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
				++cCurrFreqs[tXdatItr];
			}
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			{
				// delete prev value
				Itr tXdatItr = cCurrPxItrs[tPos];
				if (cXdatItrs.tagBll(tXdatItr))
					cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
				--cCurrFreqs[tXdatItr];
				if (!cCurrFreqs[tXdatItr])
					++cExecMetric;

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;
				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
					--cExecMetric;
				if (cXdatItrs.tagBll(tXdatItr))
					cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
				++cCurrFreqs[tXdatItr];
			}
		}
		for(Idx tIdx = 0; tIdx < cXdatItrs.tagCount(); ++tIdx)
		{
			Itr tXdatItr = cXdatItrs[tIdx];

			if (!cCurrFreqs[tXdatItr])	//	new freq == 0
				cExecXdats.removeWithItr(tXdatItr);
		}

		cXdatItrs.sweep(this->mTermSys.ExecClk());
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecMetric);
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
template <typename pxt, typename fmt>
void AllDiffXFcMt<pxt,fmt>::execBklg()
{
	WatchError
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);

		Term::performExecBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
		{
			//	add new value
			Itr tXdatItr;
			pxt const & tCurrX = mPxRecs[tPos]->CurrData();
			if (cExecXdats.insertBll(tCurrX, tXdatItr))
				cCurrFreqs[tXdatItr] = 0;
			sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
			cCurrPxItrs[tPos] = tXdatItr;

			if (!cCurrFreqs[tXdatItr])
				--cExecMetric;

			if (cXdatItrs.tagBll(tXdatItr))
				cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
			++cCurrFreqs[tXdatItr];
		}
		else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
		{
			// delete prev value
			Itr tXdatItr = cCurrPxItrs[tPos];
			if (cXdatItrs.tagBll(tXdatItr))
				cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
			--cCurrFreqs[tXdatItr];
			if (!cCurrFreqs[tXdatItr])
				++cExecMetric;

			//	add new value
			pxt const & tCurrX = mPxRecs[tPos]->CurrData();
			if (cExecXdats.insertBll(tCurrX, tXdatItr))
				cCurrFreqs[tXdatItr] = 0;
			sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
			cCurrPxItrs[tPos] = tXdatItr;

			if (!cCurrFreqs[tXdatItr])
				--cExecMetric;

			if (cXdatItrs.tagBll(tXdatItr))
				cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
			++cCurrFreqs[tXdatItr];
		}
	}

	for(Idx tIdx = 0; tIdx < cXdatItrs.tagCount(); ++tIdx)
	{
		Itr tXdatItr = cXdatItrs[tIdx];

		if (!cCurrFreqs[tXdatItr])	//	new freq == 0
			cExecXdats.removeWithItr(tXdatItr);
	}

	cXdatItrs.sweep(this->mTermSys.ExecClk());
	this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecMetric);
	this->runPostExecBklg();
	CatchError
}
#endif // CompLazy



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename fmt>
void AllDiffXFcMt<pxt,fmt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		BuffType tSimulMetric = cExecMetric;
		sNextXdats.clear(this->mTermSys.SimulClk());
		for(Idx tIdx = 0; tIdx < this->mSimulChgdPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mSimulChgdPrms.serial(tIdx);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
			if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
			{
				// drop curr xdat
				Itr tNextItr;
				pxt const & tCurrX = mPxRecs[tPos]->CurrBuff;
				if (sNextXdats.insertBll(tCurrX, tNextItr))
				{
					Itr tCurrItr = cCurrPxItrs[tPos];
					sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
				}
				--sNextFreqs[tNextItr];
				if (!sNextFreqs[tNextItr]) ++tSimulMetric;

				//	add next xdat
				pxt const & tNextX = mPxRecs[tPos]->NextBuff;
				if (sNextXdats.insertBll(tNextX, tNextItr))
				{
					Itr tCurrItr = cExecXdats.findItr(tNextX);
					if (tCurrItr == InvItr) sNextFreqs[tNextItr] = 0;
					else sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
				}
				if (!sNextFreqs[tNextItr]) --tSimulMetric;
				++sNextFreqs[tNextItr];
			}
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
		if (this->needSimulFlexiComp())	this->listFlexiParams();
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
			cSimulXdats.clear(this->mTermSys.SimulCacheClk());
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Itr tSimulItr;
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cSimulXdats.insertBll(tCurrX, tSimulItr))
				{
					Itr tCurrItr = cCurrPxItrs[tPos];
					cSimulFreqs[tSimulItr] = cCurrFreqs[tCurrItr];
				}
				--cSimulFreqs[tSimulItr];
				if (!cSimulFreqs[tSimulItr]) ++cSimulMetric;
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
			sNextXdats.clear(this->mTermSys.SimulClk());

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

				Itr tNextItr;
				pxt const & tNextX = mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
				if (sNextXdats.insertBll(tNextX, tNextItr))
				{
					Itr tSimulItr = cSimulXdats.findItr(tNextX);
					if (tSimulItr != InvItr)
						sNextFreqs[tNextItr] = cSimulFreqs[tSimulItr];
					else
					{
						Itr tCurrItr = cExecXdats.findItr(tNextX);
						if (tCurrItr == InvItr) sNextFreqs[tNextItr] = 0;
						else sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
					}
				}

				if (!sNextFreqs[tNextItr]) --tSimulMetric;
				++sNextFreqs[tNextItr];
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
				{
					// drop curr xdat
					Itr tNextItr;
					pxt const & tCurrX = mPxRecs[tPos]->CurrBuff;
					if (sNextXdats.insertBll(tCurrX, tNextItr))
					{
						#if SimulFixed
						Itr tSimulItr = cSimulXdats.findItr(tCurrX);
						if (tSimulItr != InvItr)
							sNextFreqs[tNextItr] = cSimulFreqs[tSimulItr];
						else
						#endif
						{
							Itr tCurrItr = cCurrPxItrs[tPos];
							sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
						}
					}
					--sNextFreqs[tNextItr];
					if (!sNextFreqs[tNextItr]) ++tSimulMetric;

					//	add next xdat
					pxt const & tNextX = mPxRecs[tPos]->NextBuff;
					if (sNextXdats.insertBll(tNextX, tNextItr))
					{
						#if SimulFixed
						Itr tSimulItr = cSimulXdats.findItr(tNextX);
						if (tSimulItr != InvItr)
							sNextFreqs[tNextItr] = cSimulFreqs[tSimulItr];
						else
						#endif
						{
							Itr tCurrItr = cExecXdats.findItr(tNextX);
							if (tCurrItr == InvItr) sNextFreqs[tNextItr] = 0;
							else sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
						}
					}
					if (!sNextFreqs[tNextItr]) --tSimulMetric;
					++sNextFreqs[tNextItr];
				}
			}
			#endif //SimulFlexi
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
			cSimulXdats.clear(this->mTermSys.SimulCacheClk());
			if (!this->chgdEmulClk())
			{
				cSimulMetric = cEmulMetric;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);

					Itr tSimulItr;
					pxt const & tLateX = mPxRecs[tPos]->LateData(this->mTermSys.EmulClk());
					if (cSimulXdats.insertBll(tLateX, tSimulItr))
					{
						Itr tEmulItr = cEmulXdats.findItr(tLateX);
						if (tEmulItr != InvItr)
							cSimulFreqs[tSimulItr] = cEmulFreqs[tEmulItr];
						else
						{
							Itr tCurrItr = cCurrPxItrs[tPos];
							cSimulFreqs[tSimulItr] = cCurrFreqs[tCurrItr];
						}
					}
					--cSimulFreqs[tSimulItr];
					if (!cSimulFreqs[tSimulItr]) ++cSimulMetric;
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
					{
						Itr tSimulItr;
						pxt const & tCurrX = mPxRecs[tPos]->CurrData();
						if (cSimulXdats.insertBll(tCurrX, tSimulItr))
						{
							Itr tCurrItr = cCurrPxItrs[tPos];
							cSimulFreqs[tSimulItr] = cCurrFreqs[tCurrItr];
						}
						--cSimulFreqs[tSimulItr];
						if (!cSimulFreqs[tSimulItr]) ++cSimulMetric;
					}
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
					{
						Itr tSimulItr;
						pxt const & tLateX = tPxRec->LateData(this->mTermSys.EmulClk());
						if (cSimulXdats.insertBll(tLateX, tSimulItr))
						{
							Itr tCurrItr = cExecXdats.findItr(tLateX);
							if (tCurrItr == InvItr) cSimulFreqs[tSimulItr] = 0;
							else cSimulFreqs[tSimulItr] = cCurrFreqs[tCurrItr];
						}
						if (!cSimulFreqs[tSimulItr]) --cSimulMetric;
						++cSimulFreqs[tSimulItr];
					}
					else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
					{
						// drop curr value
						Itr tSimulItr;
						pxt const & tCurrX = mPxRecs[tPos]->CurrBuff;
						if (cSimulXdats.insertBll(tCurrX, tSimulItr))
						{
							Itr tCurrItr = cCurrPxItrs[tPos];
							cSimulFreqs[tSimulItr] = cCurrFreqs[tCurrItr];
						}
						--cSimulFreqs[tSimulItr];
						if (!cSimulFreqs[tSimulItr]) ++cSimulMetric;

						//	add late value
						pxt const & tLateX = mPxRecs[tPos]->LateBuff;
						if (cSimulXdats.insertBll(tLateX, tSimulItr))
						{
							Itr tCurrItr = cExecXdats.findItr(tLateX);
							if (tCurrItr == InvItr) cSimulFreqs[tSimulItr] = 0;
							else cSimulFreqs[tSimulItr] = cCurrFreqs[tCurrItr];
						}
						if (!cSimulFreqs[tSimulItr]) --cSimulMetric;
						++cSimulFreqs[tSimulItr];
					}
				}
			}
		}

		sNextXdats.clear(this->mTermSys.SimulClk());
		BuffType tSimulMetric = cSimulMetric;

		#if SimulFixed
		for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFixedPrms->item(tIdx);
			Term::performSimulIncr(this->mPrmTerms[tPos]);

			Itr tNextItr;
			pxt const & tNextX = mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
			if (sNextXdats.insertBll(tNextX, tNextItr))
			{
				Itr tSimulItr = cSimulXdats.findItr(tNextX);
				if (tSimulItr != InvItr)
					sNextFreqs[tNextItr] = cSimulFreqs[tSimulItr];
				else
				{
					Itr tEmulItr = InvItr;
					if (!this->chgdEmulClk())
					{
						tEmulItr = cEmulXdats.findItr(tNextX);
						if (tEmulItr != InvItr)
							sNextFreqs[tNextItr] = cEmulFreqs[tEmulItr];
					}
					if (tEmulItr == InvItr)
					{
						Itr tCurrItr = cExecXdats.findItr(tNextX);
						if (tCurrItr == InvItr) sNextFreqs[tNextItr] = 0;
						else sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
					}
				}
			}
			if (!sNextFreqs[tNextItr]) --tSimulMetric;
			++sNextFreqs[tNextItr];
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
			{
				tSimulMetric += tPxRec->NextData(this->mTermSys.SimulClk()) -
							tPxRec->LateData(this->mTermSys.EmulClk());

				// drop curr value
				Itr tNextItr;
				pxt const & tLateX = tPxRec->LateData(this->mTermSys.EmulClk());
				if (sNextXdats.insertBll(tLateX, tNextItr))
				{
					Itr tSimulItr = cSimulXdats.findItr(tLateX);
					if (tSimulItr != InvItr)
						sNextFreqs[tNextItr] = cSimulFreqs[tSimulItr];
					else
					{
						Itr tEmulItr = InvItr;
						if (!this->chgdEmulClk())
						{
							tEmulItr = cEmulXdats.findItr(tLateX);
							if (tEmulItr != InvItr)
								sNextFreqs[tNextItr] = cEmulFreqs[tEmulItr];
						}
						if (tEmulItr == InvItr)
						{
							Itr tCurrItr = cExecXdats.findItr(tLateX);
							sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
						}
					}
				}
				--sNextFreqs[tNextItr];
				if (!sNextFreqs[tNextItr]) ++tSimulMetric;

				//	add next xdat
				pxt const & tNextX = mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
				if (sNextXdats.insertBll(tNextX, tNextItr))
				{
					Itr tSimulItr = cSimulXdats.findItr(tNextX);
					if (tSimulItr != InvItr)
						sNextFreqs[tNextItr] = cSimulFreqs[tSimulItr];
					else
					{
						Itr tEmulItr = InvItr;
						if (!this->chgdEmulClk())
						{
							tEmulItr = cEmulXdats.findItr(tNextX);
							if (tEmulItr != InvItr)
								sNextFreqs[tNextItr] = cEmulFreqs[tEmulItr];
						}
						if (tEmulItr == InvItr)
						{
							Itr tCurrItr = cExecXdats.findItr(tNextX);
							if (tCurrItr == InvItr) sNextFreqs[tNextItr] = 0;
							else sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
						}
					}
				}
				if (!sNextFreqs[tNextItr]) --tSimulMetric;
				++sNextFreqs[tNextItr];
			}
		}
		#endif
		this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fmt>::iof(tSimulMetric));
	}
	#endif // CompLazy
	#endif//SimulDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in emulation mode.
*/
template <typename pxt, typename fmt>
void AllDiffXFcMt<pxt,fmt>::emulBklg()
{
	WatchError
	cEmulMetric = cExecMetric;
	cEmulXdats.clear(this->mTermSys.EmulClk());
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
		{
			Itr tLateItr;
			pxt const & tLateX = mPxRecs[tPos]->LateData(this->mTermSys.EmulClk());
			if (cEmulXdats.insertBll(tLateX, tLateItr))
			{
				Idx tCurrItr = cExecXdats.findItr(tLateX);
				if (tCurrItr == InvItr) cEmulFreqs[tLateItr] = 0;
				else cEmulFreqs[tLateItr] = cCurrFreqs[tCurrItr];
			}
			if (!cEmulFreqs[tLateItr]) --cEmulMetric;
			++cEmulFreqs[tLateItr];
		}
		else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
		{
			// drop curr xdat
			Itr tLateItr;
			pxt const & tCurrX = mPxRecs[tPos]->CurrBuff;
			if (cEmulXdats.insertBll(tCurrX, tLateItr))
			{
				Idx tCurrItr = cCurrPxItrs[tPos];
				cEmulFreqs[tLateItr] = cCurrFreqs[tCurrItr];
			}
			--cEmulFreqs[tLateItr];
			if (!cEmulFreqs[tLateItr]) ++cEmulMetric;

			//	add late xdat
			pxt const & tLateX = mPxRecs[tPos]->LateBuff;
			if (cEmulXdats.insertBll(tLateX, tLateItr))
			{
				Itr tCurrItr = cExecXdats.findItr(tLateX);
				if (tCurrItr == InvItr) cEmulFreqs[tLateItr] = 0;
				else cEmulFreqs[tLateItr] = cCurrFreqs[tCurrItr];
			}
			if (!cEmulFreqs[tLateItr]) --cEmulMetric;
			++cEmulFreqs[tLateItr];
		}
	}

	this->mMetricRec->updtLate(this->mTermSys.EmulClk(), cEmulMetric);
	CatchError
}
#endif // CompLazy



/*!
	Sync the exec clock.
*/
template <typename pxt, typename fmt>
void AllDiffXFcMt<pxt,fmt>::syncExecClk()
{
	WatchError
	cXdatItrs.syncClk();
	#if CompLazy
	cEmulXdats.syncClk();
	#endif
	AggFcMt<fmt>::syncExecClk();
	CatchError
}


/*!
	Sync the simul clock.
*/
template <typename pxt, typename fmt>
void AllDiffXFcMt<pxt,fmt>::syncSimulClk()
{
	WatchError
	sNextXdats.syncClk();
	AggFcMt<fmt>::syncSimulClk();
	CatchError
}


#if SimulDnwdCache
/*!
	Sync the simul cache clock.
*/
template <typename pxt, typename fmt>
void AllDiffXFcMt<pxt,fmt>::syncSimulCacheClk()
{
	WatchError
	cSimulXdats.syncClk();
	AggFcMt<fmt>::syncSimulCacheClk();
	CatchError
}
#endif//SimulDnwdCache

closeKangarooSpace


#endif//AllDiffXFcMt
