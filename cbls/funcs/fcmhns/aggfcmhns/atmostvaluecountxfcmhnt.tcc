/*!
	@file atmostvaluecountxfcmhnt.tcc
	@brief The prototype file for AtmostValueCountXFcMHnT template class.
	@details This is the prototype file for AtmostValueCountXFcMHnT template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef AtmostValueCountXFcMHnTTccIncluded
#define AtmostValueCountXFcMHnTTccIncluded



#include "cbls/funcs/fcmhns/aggfcmhnt.tcc"
#include "cbls/frames/idx.hh"



openKangarooSpace



/*!
	@class AtmostValueCountXFcMHnT
	@brief A class to represent at most value count fcmhns.
	@details This class represents at most value count count fcmhns.
*/
template <typename pxt, typename fmt>
class AtmostValueCountXFcMHnT : public AggFcMHnT<fmt>
{
	public:
		static Hdl def(Fss const theFss, Hdl const hdlSys, Prm * thePrms,
											Dim const PrmCount, Dim const ValCountLimit);		//!< Definition.

		static AtmostValueCountXFcMHnT<pxt,fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static AtmostValueCountXFcMHnT<pxt,fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static AtmostValueCountXFcMHnT<pxt,fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static AtmostValueCountXFcMHnT<pxt,fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static AtmostValueCountXFcMHnT<pxt,fmt> const & cast(Term const & theTerm);	//!< Perform casting.
		static AtmostValueCountXFcMHnT<pxt,fmt> const * cast(Term const * theTerm);	//!< Perform casting.
		static AtmostValueCountXFcMHnT<pxt,fmt> & cast(Term & theTerm);				//!< Perform casting.
		static AtmostValueCountXFcMHnT<pxt,fmt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);						//!< Whether suits casting.
		static Bll suit(Term const * theTerm);						//!< Whether suits casting.
		static Bll suit(Term & theTerm);							//!< Whether suits casting.
		static Bll suit(Term * theTerm);							//!< Whether suits casting.

		//! @}

	private:

		AtmostValueCountXFcMHnT(Fss const theFss, Hdl const hdlSys,
								Prm * thePrms, Dim const PrmCount, Dim const ValCountLimit);		//!< Constructor.
		AtmostValueCountXFcMHnT(AtmostValueCountXFcMHnT<pxt,fmt> const & that);						//!< Duplicator.
		AtmostValueCountXFcMHnT const & operator = (AtmostValueCountXFcMHnT<pxt,fmt> const & that);	//!< Assigner.
		~AtmostValueCountXFcMHnT();																	//!< Destructor.

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
		#endif//CompLazy

		typedef typename DataStub<fmt>::TempBuff TempType;	//!< Temp buff type.
		typedef typename DataBuff<pxt,fmt>::Type BuffType;	//!< Data buff type.

		b1<EvalRec<pxt> const *,kmm> 	mPxRecs;	//!< Parameter records.
		Dim const mValCountLimit;					//!< Value count limit.

		#if SimulDnwdCache
		Dim	            cSimulValueCount;		//!< Simulation cache metric.
		#endif//SimulDnwd
		Dim         	cExecValueCount;		//!< Execution cache metric.
		#if CompLazy
		Dim         	cEmulValueCount;		//!< Emulation cache metric.
		#endif//CompLazy

		b1<BuffType,kmm> * cExecHintMin;	//!< Execution cache hint min.
		ll<Sqn,kmm>		 * sChgdHintMin;	//!< Hint mins that undergone changes.

		//	the number of possible values would be 2 * #params
		hsd<pxt,nmmh>			cExecXdats;		//!< Exec xdats for the parameters.
		b1<Pos,kmm>				cXdatRoots;		//!< Xdat to cluster-root mapping.
		b1<Dim,kmm> 			cCurrFreqs;		//!< Curr freqs of the xdats.
		b1<Dim,kmm>				cPrevFreqs;		//!< Prev freqs for changed Xdats.
		ll<Itr,kmm>				cXdatItrs;		//!< Idxs of Xdats with changes.

		//	maintained for each parameter and used in execution.
		cl<Pos,kmm> 			cXdatPrms;		//!< Parameters having the same Xdat.
		b1<Itr,kmm> 			cCurrPxItrs;	//!< Curr xdat indexes for params.
		b1<Itr,kmm> 			sPrevPxItrs;	//!< Prev Xdat indexes for params.

		hsc<pxt,nmmh>			sNextXdats;		//!< Simul xdats for the parameters.
		b1<Dim,kmm>				sNextFreqs;		//!< Simul xdats for the parameters.

		#if CompLazy
		hsc<pxt,nmmh>			cEmulXdats;		//!< Emulation xdats.
		b1<Dim,kmm>				cEmulFreqs;		//!< Emulation freqs.
		#endif

		#if SimulDnwdCache
		//	used in simulation
		hsc<pxt,nmmh>			cSimulXdats;	//!< Cache for simul xdats.
		b1<Dim,kmm>				cSimulFreqs;	//!< Cache for simul freqs.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AtmostValueCountXFcMHnT<pxt,fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< AtmostValueCountXFcMHnT<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AtmostValueCountXFcMHnT<pxt,fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< AtmostValueCountXFcMHnT<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AtmostValueCountXFcMHnT<pxt,fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< AtmostValueCountXFcMHnT<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AtmostValueCountXFcMHnT<pxt,fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< AtmostValueCountXFcMHnT<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AtmostValueCountXFcMHnT<pxt,fmt> const & AtmostValueCountXFcMHnT<pxt,fmt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< AtmostValueCountXFcMHnT<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AtmostValueCountXFcMHnT<pxt,fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AtmostValueCountXFcMHnT<pxt,fmt> const * AtmostValueCountXFcMHnT<pxt,fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< AtmostValueCountXFcMHnT<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AtmostValueCountXFcMHnT<pxt,fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AtmostValueCountXFcMHnT<pxt,fmt> & AtmostValueCountXFcMHnT<pxt,fmt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< AtmostValueCountXFcMHnT<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AtmostValueCountXFcMHnT<pxt,fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AtmostValueCountXFcMHnT<pxt,fmt> * AtmostValueCountXFcMHnT<pxt,fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< AtmostValueCountXFcMHnT<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AtmostValueCountXFcMHnT<pxt,fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to an at most value count.
*/
template <typename pxt, typename fmt>
inline AtmostValueCountXFcMHnT<pxt,fmt> & AtmostValueCountXFcMHnT<pxt,fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an at most value count.
*/
template <typename pxt, typename fmt>
inline AtmostValueCountXFcMHnT<pxt,fmt> * AtmostValueCountXFcMHnT<pxt,fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an at most value count.
*/
template <typename pxt, typename fmt>
inline AtmostValueCountXFcMHnT<pxt,fmt> const & AtmostValueCountXFcMHnT<pxt,fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an at most value count.
*/
template <typename pxt, typename fmt>
inline AtmostValueCountXFcMHnT<pxt,fmt> const * AtmostValueCountXFcMHnT<pxt,fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pxt, typename fmt>
inline AtmostValueCountXFcMHnT<pxt,fmt>::~AtmostValueCountXFcMHnT()
{
	WatchError
	if (cExecHintMin) delete cExecHintMin;
	if (sChgdHintMin) delete sChgdHintMin;
	CatchError
}


/*!
	Define an at most value count fcmhn in the sys.
*/
template <typename pxt, typename fmt>
Hdl AtmostValueCountXFcMHnT<pxt,fmt>::def(Fss const theFss, Hdl const hdlSys, Prm * thePrms,
					Dim const PrmCount, Dim const ValCountLimit)
{
	WatchError
	Warn(PrmCount < 1 || PrmCount > MaxDim, eParamCount2(PrmCount, MaxDim));

	AtmostValueCountXFcMHnT<pxt,fmt> * tFcMHn = new
			AtmostValueCountXFcMHnT<pxt,fmt>(theFss, hdlSys, thePrms, PrmCount, ValCountLimit);
	Hdl const tHdl = tFcMHn->defSysFunc();
	if (tHdl != InvHdl) { delete tFcMHn; return tHdl; }

	EvalTbl<pxt> const & tPxTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<fmt> & tFmTbl = EvalTbl<fmt>::refm(hdlSys);
	HintTbl<fmt> & tFdTbl = HintTbl<fmt>::refm(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFcMHn->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFcMHn->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFcMHn->mPxRecs[tPos] = tPxTbl.ptrcEvalRec(tPxLoc);
	}

	tFmTbl.setEvalRec(tFcMHn->mMetricRec, tFcMHn->mMetricLoc);
	tFdTbl.setHintRec(tFcMHn->mHintMinRec, tFcMHn->mHintMinLoc, tFcMHn->FuncVars.itemCount());

	tFcMHn->cExecHintMin = new b1<BuffType,kmm>(tFcMHn->FuncVars.itemCount());
	tFcMHn->sChgdHintMin = new ll<Sqn,kmm>(tFcMHn->FuncVars.itemCount());

	tFcMHn->performCompConst();
	tFcMHn->defSysRoot();
	return tFcMHn->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
template <typename pxt, typename fmt>
AtmostValueCountXFcMHnT<pxt,fmt>::AtmostValueCountXFcMHnT(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, Dim const ValCountLimit) : AggFcMHnT<fmt>(hdlSys, PrmCount), mPxRecs(PrmCount),
		mValCountLimit(ValCountLimit), cExecHintMin(Null), sChgdHintMin(Null), cExecXdats(PrmCount << 1),
		cXdatRoots(cExecXdats.slotCount()), cCurrFreqs(cExecXdats.slotCount()), cPrevFreqs(cExecXdats.slotCount()),
		cXdatItrs(cExecXdats.slotCount()), cXdatPrms(PrmCount), cCurrPxItrs(PrmCount),
		sPrevPxItrs(PrmCount), sNextXdats(PrmCount << 1), sNextFreqs(sNextXdats.slotCount())
		#if CompLazy
		, cEmulXdats(PrmCount), cEmulFreqs(cEmulXdats.slotCount())
		#endif
		#if SimulDnwdCache
		, cSimulXdats(PrmCount), cSimulFreqs(cSimulXdats.slotCount())
		#endif
{
	WatchError
	this->setTermCls(TermStub< AtmostValueCountXFcMHnT<pxt,fmt> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Unordered);
	this->setTermHvl(this->calcTermHvl());
	Warn(!mValCountLimit, eEmptyDimension);
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename fmt>
AtmostValueCountXFcMHnT<pxt,fmt>::AtmostValueCountXFcMHnT(AtmostValueCountXFcMHnT const & that) : AggFcMHnT<fmt>(that), mPxRecs(0),
		mValCountLimit(0), cExecXdats(0), cXdatRoots(0), cCurrFreqs(0), cPrevFreqs(0), cXdatItrs(0),
		cXdatPrms(0), cCurrPxItrs(0), sPrevPxItrs(0), sNextXdats(0), sNextFreqs(0)
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
AtmostValueCountXFcMHnT<pxt,fmt> const & AtmostValueCountXFcMHnT<pxt,fmt>::operator = (AtmostValueCountXFcMHnT<pxt,fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template <typename pxt, typename fmt>
void AtmostValueCountXFcMHnT<pxt,fmt>::compConst()
{
	WatchError
	IncompleteCode
//	Needs to think about this
//	if (this->Updatable())
//	{
//		for(Pos tPos = 1; tPos < this->mPrmTerms.itemCount(); ++tPos)
//			if (this->mPrmTerms[tPos] == this->mPrmTerms[tPos - 1] &&
//					this->mPrmSpecs[tPos] == this->mPrmSpecs[tPos - 1])
//				{ this->setUpdatable(false); break;}
//	}

	if (this->updatable()) return;

	cExecValueCount = 0;
	for(Sqn tSqn = 0; tSqn < this->FuncVars.itemCount(); ++tSqn)
		cExecHintMin->item(tSqn) = 0;

	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		Itr tCurrItr;

		pxt const & tCurrX = mPxRecs[tPos]->CurrData();
		if (cExecXdats.insertBll(tCurrX, tCurrItr))
		{
			++cExecValueCount;
			cXdatRoots[tCurrItr] = tPos;
			cCurrFreqs[tCurrItr] = 1;
			cXdatPrms.alter(tPos, tPos);
		}
		else
		{
			++cCurrFreqs[tCurrItr];
			cXdatPrms.alter(tPos, cXdatRoots[tCurrItr]);
		}
		cCurrPxItrs[tPos] = tCurrItr;
	}

	for(Pos tPos = 0; tPos < this->PrmVars.listCount(); ++tPos)
	{
		b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tPos];
		Itr const tPxItr = cCurrPxItrs[tPos];
		Dim tFreq = this->PrmVars.listCount() - cCurrFreqs[tPxItr];

		for(Idx tIdx = 0; tIdx < tPrmVars.itemCount(); ++tIdx)
		{
			Sqn const tSqn = tPrmVars[tIdx];
			cExecHintMin->item(tSqn) += tFreq;
		}
	}

	if (cExecValueCount > mValCountLimit)
		this->mMetricRec->finalise(cExecValueCount - mValCountLimit);
	else
		this->mMetricRec->finalise(0);
	for(Sqn tSqn = 0; tSqn < this->FuncVars.itemCount(); ++tSqn)
		this->mHintMinRec->HintFlds[tSqn].finalise(tc<BuffType,fmt>::iof(cExecHintMin->item(tSqn)));
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void AtmostValueCountXFcMHnT<pxt,fmt>::execAnew()
{
	WatchError
	cExecValueCount = 0;
	for(Sqn tSqn = 0; tSqn < this->FuncVars.itemCount(); ++tSqn)
		cExecHintMin->item(tSqn) = 0;

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
			++cExecValueCount;
			cCurrFreqs[tCurrItr] = 1;
			cXdatRoots[tCurrItr] = tPos;
			cXdatPrms.alter(tPos, tPos);
		}
		else
		{
			++cCurrFreqs[tCurrItr];
			cXdatPrms.alter(tPos, cXdatRoots[tCurrItr]);
		}
		cCurrPxItrs[tPos] = tCurrItr;
	}

	for(Pos tPos = 0; tPos < this->PrmVars.listCount(); ++tPos)
	{
		b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tPos];
		Itr const tPxItr = cCurrPxItrs[tPos];
		Dim tFreq = this->PrmVars.listCount() - cCurrFreqs[tPxItr];

		for(Idx tIdx = 0; tIdx < tPrmVars.itemCount(); ++tIdx)
		{
			Sqn const tSqn = tPrmVars[tIdx];
			cExecHintMin->item(tSqn) += tFreq;
		}
	}

	cXdatItrs.sweep(this->mTermSys.ExecClk());	// this help uneval

	if (cExecValueCount > mValCountLimit)
		this->mMetricRec->initCurr(cExecValueCount - mValCountLimit);
	else
		this->mMetricRec->initCurr(0);
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
template <typename pxt, typename fmt>
void AtmostValueCountXFcMHnT<pxt,fmt>::simulAnew()
{
	WatchError
	sNextXdats.clear(this->mTermSys.SimulClk());
	Dim tSimulValCount = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if SimulDnwd
		Term::performSimulAnew(this->mPrmTerms[tPos]);
		#endif//SimulDnwd
		pxt const & tNextX = mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
		if (sNextXdats.insertBll(tNextX))
			++tSimulValCount;
	}
	if (tSimulValCount > mValCountLimit)
		this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulValCount - mValCountLimit);
	else
		this->mMetricRec->updtNext(this->mTermSys.SimulClk(), 0);
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



#if CompLazy
/*!
	Perform unevaluation for the parameter.
*/
template <typename pxt, typename fmt>
void AtmostValueCountXFcMHnT<pxt,fmt>::undoEval(Pos const thePos)
{
	WatchError
	// delete prev value
	Itr tXdatItr = cCurrPxItrs[thePos];
	if (cXdatItrs.tagBll(tXdatItr))
		cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
	--cCurrFreqs[tXdatItr];
	if (!cCurrFreqs[tXdatItr])
	{
		--cExecValueCount;
		cXdatRoots[tXdatItr] = InvPos;
	}
	else
	{
		//	delete from cycles
		if (cXdatPrms.successor(thePos) != thePos)
		{
			if (cXdatRoots[tXdatItr] == thePos)
				cXdatRoots[tXdatItr] = cXdatPrms.successor(thePos);
			cXdatPrms.alter(thePos, thePos);
		}
		else
			cXdatRoots[tXdatItr] = InvPos;
	}
	CatchError
}
#endif//CompLazy



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void AtmostValueCountXFcMHnT<pxt,fmt>::execIncr()
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
			{
				// delete prev value
				Itr tXdatItr = cCurrPxItrs[tPos];
				if (cXdatItrs.tagBll(tXdatItr))
					cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
				--cCurrFreqs[tXdatItr];
				if (!cCurrFreqs[tXdatItr])
				{
					--cExecValueCount;
					cXdatRoots[tXdatItr] = InvPos;
				}
				else
				{
					//	delete from cycles
					if (cXdatPrms.successor(tPos) != tPos)
					{
						if (cXdatRoots[tXdatItr] == tPos)
							cXdatRoots[tXdatItr] = cXdatPrms.successor(tPos);
						cXdatPrms.alter(tPos, tPos);
					}
					else
						cXdatRoots[tXdatItr] = InvPos;
				}

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;

				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
				{
					++cExecValueCount;
					cXdatRoots[tXdatItr] = InvPos;
				}
				if (cXdatItrs.tagBll(tXdatItr))
					cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
				++cCurrFreqs[tXdatItr];
			}
		}

		for(Idx tIdx = 0; tIdx < cXdatItrs.tagCount(); ++tIdx)
		{
			Itr tXdatItr = cXdatItrs[tIdx];
			Num tHintMin1 = cCurrFreqs[tXdatItr];
			Num tHintMin2 = cPrevFreqs[tXdatItr];

			if (!tHintMin1)	//	new freq == 0
				cExecXdats.removeWithItr(tXdatItr);
				//	after elimination, the index is stll assumed to be valid
				//	for the properties that use the index such as XdatRoots, CurrFreqs
				//	PrevFreqs, and XdatIdxs.

			Num tHintMin = tHintMin1 - tHintMin2;

			if (!tHintMin) continue;

			Pos tCurrPos = cXdatRoots[tXdatItr], tSentPos = tCurrPos;
			if (tCurrPos != InvPos)
				do
				{
					b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tCurrPos];
					for(Sqn tPrmSqn = 0; tPrmSqn < tPrmVars.itemCount(); ++tPrmSqn)
					{
						Sqn const tSqn = tPrmVars[tPrmSqn];
						sChgdHintMin->tagBll(tSqn);
						cExecHintMin->item(tSqn) -= tHintMin;
					}
					tCurrPos = cXdatPrms.successor(tCurrPos);
				}
				while (tCurrPos != tSentPos);
		}

		for(Idx tIdx = 0; tIdx < this->mExecChgdPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mExecChgdPrms.serial(tIdx);
			if (mPxRecs[tPos]->PrevDiff(this->mTermSys.ExecClk()))
			{
				if (cXdatRoots[cCurrPxItrs[tPos]] == InvPos)
					cXdatRoots[cCurrPxItrs[tPos]] = tPos;
				cXdatPrms.alter(tPos, cXdatRoots[cCurrPxItrs[tPos]]);
				Num tHintMin1 = cCurrFreqs[cCurrPxItrs[tPos]];
				Num tHintMin2 = cPrevFreqs[sPrevPxItrs[tPos]];

				Num tHintMin = tHintMin1 - tHintMin2;
				if (!tHintMin) continue;

				b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tPos];
				for(Sqn tPrmSqn = 0; tPrmSqn < tPrmVars.itemCount(); ++tPrmSqn)
				{
					Sqn const tSqn = tPrmVars[tPrmSqn];
					sChgdHintMin->tagBll(tSqn);
					cExecHintMin->item(tSqn) -= tHintMin;
				}
			}
		}

		cXdatItrs.sweep(this->mTermSys.ExecClk());
		if (cExecValueCount > mValCountLimit)
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecValueCount - mValCountLimit);
		else
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), 0);
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
	#endif//CompLazy
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
				{
					// delete prev value
					Itr tXdatItr = cCurrPxItrs[tPos];
					if (cXdatItrs.tagBll(tXdatItr))
						cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
					--cCurrFreqs[tXdatItr];
					if (!cCurrFreqs[tXdatItr])
					{
						--cExecValueCount;
						cXdatRoots[tXdatItr] = InvPos;
					}
					else
					{
						//	delete from cycles
						if (cXdatPrms.successor(tPos) != tPos)
						{
							if (cXdatRoots[tXdatItr] == tPos)
								cXdatRoots[tXdatItr] = cXdatPrms.successor(tPos);
							cXdatPrms.alter(tPos, tPos);
						}
						else
							cXdatRoots[tXdatItr] = InvPos;
					}

					//	add new value
					pxt const & tCurrX = mPxRecs[tPos]->CurrData();
					if (cExecXdats.insertBll(tCurrX, tXdatItr))
						cCurrFreqs[tXdatItr] = 0;
					sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
					cCurrPxItrs[tPos] = tXdatItr;

					if (!cCurrFreqs[tXdatItr])
					{
						++cExecValueCount;
						cXdatRoots[tXdatItr] = InvPos;
					}
					if (cXdatItrs.tagBll(tXdatItr))
						cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
					++cCurrFreqs[tXdatItr];
				}
			}

			for(Idx tIdx = 0; tIdx < cXdatItrs.tagCount(); ++tIdx)
			{
				Itr tXdatItr = cXdatItrs[tIdx];
				Num tHintMin1 = cCurrFreqs[tXdatItr];
				Num tHintMin2 = cPrevFreqs[tXdatItr];

				if (!tHintMin1)	//	new freq == 0
					cExecXdats.removeWithItr(tXdatItr);

				Num tHintMin = tHintMin1 - tHintMin2;
				if (!tHintMin) continue;

				Pos tCurrPos = cXdatRoots[tXdatItr], tSentPos = tCurrPos;
				if (tCurrPos != InvPos)
					do
					{
						b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tCurrPos];
						for(Sqn tPrmSqn = 0; tPrmSqn < tPrmVars.itemCount(); ++tPrmSqn)
						{
							Sqn const tSqn = tPrmVars[tPrmSqn];
							sChgdHintMin->tagBll(tSqn);
							cExecHintMin->item(tSqn) -= tHintMin;
						}
						tCurrPos = cXdatPrms.successor(tCurrPos);
					}
					while (tCurrPos != tSentPos);
			}

			for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkCandPrms->item(tIdx);
				if (mPxRecs[tPos]->PrevDiff(this->mTermSys.ExecClk()))
				{
					if (cXdatRoots[cCurrPxItrs[tPos]] == InvPos)
						cXdatRoots[cCurrPxItrs[tPos]] = tPos;
					cXdatPrms.alter(tPos, cXdatRoots[cCurrPxItrs[tPos]]);
					Num tHintMin1 = cCurrFreqs[cCurrPxItrs[tPos]];
					Num tHintMin2 = cPrevFreqs[sPrevPxItrs[tPos]];

					Num tHintMin = tHintMin1 - tHintMin2;
					if (!tHintMin) continue;

					b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tPos];
					for(Sqn tPrmSqn = 0; tPrmSqn < tPrmVars.itemCount(); ++tPrmSqn)
					{
						Sqn const tSqn = tPrmVars[tPrmSqn];
						sChgdHintMin->tagBll(tSqn);
						cExecHintMin->item(tSqn) -= tHintMin;
					}
				}
			}

			cXdatItrs.sweep(this->mTermSys.ExecClk());
			if (cExecValueCount > mValCountLimit)
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecValueCount - mValCountLimit);
			else
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), 0);
			this->mHintMinRec->resetHintDiff(this->mTermSys.ExecClk());
			for(Idx tIdx = 0; tIdx < sChgdHintMin->tagCount(); ++tIdx)
			{
				Sqn const tSqn = sChgdHintMin->serial(tIdx);
				if (this->mHintMinRec->HintFlds[tSqn].updtCurr(this->mTermSys.ExecClk(),
								tc<BuffType,fmt>::iof(cExecHintMin->item(tSqn))))
					 this->mHintMinRec->DiffSqns.insert(tSqn);
			}
		}	//	mBlkCandPrms
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
			{
				//	add new value
				Itr tXdatItr;
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;
				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
				{
					++cExecValueCount;
					cXdatRoots[tXdatItr] = InvPos;
				}
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
				{
					--cExecValueCount;
					cXdatRoots[tXdatItr] = InvPos;
				}
				else
				{
					//	delete from cycles
					if (cXdatPrms.successor(tPos) != tPos)
					{
						if (cXdatRoots[tXdatItr] == tPos)
							cXdatRoots[tXdatItr] = cXdatPrms.successor(tPos);
						cXdatPrms.alter(tPos, tPos);
					}
					else
						cXdatRoots[tXdatItr] = InvPos;
				}

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;
				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
				{
					++cExecValueCount;
					cXdatRoots[tXdatItr] = InvPos;
				}
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
				{
					++cExecValueCount;
					cXdatRoots[tXdatItr] = InvPos;
				}

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
				{
					--cExecValueCount;
					cXdatRoots[tXdatItr] = InvPos;
				}
				else
				{
					//	delete from cycles
					if (cXdatPrms.successor(tPos) != tPos)
					{
						if (cXdatRoots[tXdatItr] == tPos)
							cXdatRoots[tXdatItr] = cXdatPrms.successor(tPos);
						cXdatPrms.alter(tPos, tPos);
					}
					else
						cXdatRoots[tXdatItr] = InvPos;
				}

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;
				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
				{
					++cExecValueCount;
					cXdatRoots[tXdatItr] = InvPos;
				}
				if (cXdatItrs.tagBll(tXdatItr))
					cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
				++cCurrFreqs[tXdatItr];
			}
		}
		for(Idx tIdx = 0; tIdx < cXdatItrs.tagCount(); ++tIdx)
		{
			Itr tXdatItr = cXdatItrs[tIdx];
			Num tHintMin1 = cCurrFreqs[tXdatItr];
			Num tHintMin2 = cPrevFreqs[tXdatItr];

			if (!tHintMin1)	//	new freq == 0
				cExecXdats.removeWithItr(tXdatItr);

			Num tHintMin = tHintMin1 - tHintMin2;
			if (!tHintMin) continue;

			Pos tCurrPos = cXdatRoots[tXdatItr], tSentPos = tCurrPos;
			if (tCurrPos != InvPos)
				do
				{
					b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tCurrPos];
					for(Sqn tPrmSqn = 0; tPrmSqn < tPrmVars.itemCount(); ++tPrmSqn)
					{
						Sqn const tSqn = tPrmVars[tPrmSqn];
						sChgdHintMin->tagBll(tSqn);
						cExecHintMin->item(tSqn) -= tHintMin;
					}
					tCurrPos = cXdatPrms.successor(tCurrPos);
				}
				while (tCurrPos != tSentPos);
		}

		for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkCandPrms->item(tIdx);
			if (this->mEvalUndonePrms->tagged(tPos) ||
					mPxRecs[tPos]->PrevDiff(this->mTermSys.ExecClk()))
			{
				if (cXdatRoots[cCurrPxItrs[tPos]] == InvPos)
					cXdatRoots[cCurrPxItrs[tPos]] = tPos;
				cXdatPrms.alter(tPos, cXdatRoots[cCurrPxItrs[tPos]]);
				Num tHintMin1 = cCurrFreqs[cCurrPxItrs[tPos]];
				Num tHintMin2 = cPrevFreqs[sPrevPxItrs[tPos]];
				Num tHintMin = tHintMin1 - tHintMin2;
				if (!tHintMin) continue;

				b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tPos];
				for(Sqn tPrmSqn = 0; tPrmSqn < tPrmVars.itemCount(); ++tPrmSqn)
				{
					Sqn const tSqn = tPrmVars[tPrmSqn];
					sChgdHintMin->tagBll(tSqn);
					cExecHintMin->item(tSqn) -= tHintMin;
				}
			}
		}

		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;
			if (this->mEvalUndonePrms->tagged(tPos) ||
					mPxRecs[tPos]->PrevDiff(this->mTermSys.ExecClk()))
			{
				if (cXdatRoots[cCurrPxItrs[tPos]] == InvPos)
					cXdatRoots[cCurrPxItrs[tPos]] = tPos;
				cXdatPrms.alter(tPos, cXdatRoots[cCurrPxItrs[tPos]]);
				Num tHintMin1 = cCurrFreqs[cCurrPxItrs[tPos]];
				Num tHintMin2 = cPrevFreqs[sPrevPxItrs[tPos]];
				Num tHintMin = tHintMin1 - tHintMin2;
				if (!tHintMin) continue;

				b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tPos];
				for(Sqn tPrmSqn = 0; tPrmSqn < tPrmVars.itemCount(); ++tPrmSqn)
				{
					Sqn const tSqn = tPrmVars[tPrmSqn];
					sChgdHintMin->tagBll(tSqn);
					cExecHintMin->item(tSqn) -= tHintMin;
				}
			}
		}

		cXdatItrs.sweep(this->mTermSys.ExecClk());
		if (cExecValueCount > mValCountLimit)
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecValueCount - mValCountLimit);
		else
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), 0);
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
	#endif//CompLazy
	#endif//ExecDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void AtmostValueCountXFcMHnT<pxt,fmt>::execBklg()
{
	WatchError
	sChgdHintMin->sweep(this->mTermSys.ExecClk());
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
			{
				++cExecValueCount;
				cXdatRoots[tXdatItr] = InvPos;
			}

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
			{
				--cExecValueCount;
				cXdatRoots[tXdatItr] = InvPos;
			}
			else
			{
				//	delete from cycles
				if (cXdatPrms.successor(tPos) != tPos)
				{
					if (cXdatRoots[tXdatItr] == tPos)
						cXdatRoots[tXdatItr] = cXdatPrms.successor(tPos);
					cXdatPrms.alter(tPos, tPos);
				}
				else
					cXdatRoots[tXdatItr] = InvPos;
			}

			//	add new value
			pxt const & tCurrX = mPxRecs[tPos]->CurrData();
			if (cExecXdats.insertBll(tCurrX, tXdatItr))
				cCurrFreqs[tXdatItr] = 0;
			sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
			cCurrPxItrs[tPos] = tXdatItr;

			if (!cCurrFreqs[tXdatItr])
			{
				++cExecValueCount;
				cXdatRoots[tXdatItr] = InvPos;
			}

			if (cXdatItrs.tagBll(tXdatItr))
				cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
			++cCurrFreqs[tXdatItr];
		}
	}

	for(Idx tIdx = 0; tIdx < cXdatItrs.tagCount(); ++tIdx)
	{
		Itr tXdatItr = cXdatItrs[tIdx];
		Num tHintMin1 = cCurrFreqs[tXdatItr];
		Num tHintMin2 = cPrevFreqs[tXdatItr];

		if (!tHintMin1)	//	new freq == 0
			cExecXdats.removeWithItr(tXdatItr);

		Num tHintMin = tHintMin1 - tHintMin2;
		if (!tHintMin) continue;

		Pos tCurrPos = cXdatRoots[tXdatItr], tSentPos = tCurrPos;
		if (tCurrPos != InvPos)
			do
			{
				b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tCurrPos];
				for(Sqn tPrmSqn = 0; tPrmSqn < tPrmVars.itemCount(); ++tPrmSqn)
				{
					Sqn const tSqn = tPrmVars[tPrmSqn];
					sChgdHintMin->tagBll(tSqn);
					cExecHintMin->item(tSqn) -= tHintMin;
				}
				tCurrPos = cXdatPrms.successor(tCurrPos);
			}
			while (tCurrPos != tSentPos);
	}

	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		if (this->mEvalUndonePrms->tagged(tPos) ||
				mPxRecs[tPos]->PrevDiff(this->mTermSys.ExecClk()))
		{
			if (cXdatRoots[cCurrPxItrs[tPos]] == InvPos)
				cXdatRoots[cCurrPxItrs[tPos]] = tPos;
			cXdatPrms.alter(tPos, cXdatRoots[cCurrPxItrs[tPos]]);
			Num tHintMin1 = cCurrFreqs[cCurrPxItrs[tPos]];
			Num tHintMin2 = cPrevFreqs[sPrevPxItrs[tPos]];
			Num tHintMin = tHintMin1 - tHintMin2;
			if (!tHintMin) continue;

			b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tPos];
			for(Sqn tPrmSqn = 0; tPrmSqn < tPrmVars.itemCount(); ++tPrmSqn)
			{
				Sqn const tSqn = tPrmVars[tPrmSqn];
				sChgdHintMin->tagBll(tSqn);
				cExecHintMin->item(tSqn) -= tHintMin;
			}
		}
	}

	cXdatItrs.sweep(this->mTermSys.ExecClk());
	if (cExecValueCount > mValCountLimit)
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecValueCount - mValCountLimit);
	else
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), 0);
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
#endif//CompLazy



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename fmt>
void AtmostValueCountXFcMHnT<pxt,fmt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		Dim tSimulValCount = cExecValueCount;
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
				if (!sNextFreqs[tNextItr]) --tSimulValCount;

				//	add next xdat
				pxt const & tNextX = mPxRecs[tPos]->NextBuff;
				if (sNextXdats.insertBll(tNextX, tNextItr))
				{
					Itr tCurrItr = cExecXdats.findItr(tNextX);
					if (tCurrItr == InvItr) sNextFreqs[tNextItr] = 0;
					else sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
				}
				if (!sNextFreqs[tNextItr]) ++tSimulValCount;
				++sNextFreqs[tNextItr];
			}
		}
		if (tSimulValCount > mValCountLimit)
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulValCount - mValCountLimit);
		else
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(), 0);
		this->runPostSimulIncr();
	}
	#endif	//SimulUpwd
	#if SimulDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif//CompLazy
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
			cSimulValueCount = cExecValueCount;
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
				if (!cSimulFreqs[tSimulItr]) --cSimulValueCount;
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
			Dim tSimulValCount = cSimulValueCount;
			#else
			Dim tSimulValCount = cExecValueCount;
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

				if (!sNextFreqs[tNextItr]) ++tSimulValCount;
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
					if (!sNextFreqs[tNextItr]) --tSimulValCount;

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
					if (!sNextFreqs[tNextItr]) ++tSimulValCount;
					++sNextFreqs[tNextItr];
				}
			}
			#endif //SimulFlexi
			if (tSimulValCount > mValCountLimit)
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulValCount - mValCountLimit);
			else
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(), 0);
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
				cSimulValueCount = cEmulValueCount;
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
					if (!cSimulFreqs[tSimulItr]) --cSimulValueCount;
				}
				#endif //SimulFixed
			}
			else
			{
				cSimulValueCount = cExecValueCount;
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
						if (!cSimulFreqs[tSimulItr]) --cSimulValueCount;
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
						if (!cSimulFreqs[tSimulItr]) ++cSimulValueCount;
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
						if (!cSimulFreqs[tSimulItr]) --cSimulValueCount;

						//	add late value
						pxt const & tLateX = mPxRecs[tPos]->LateBuff;
						if (cSimulXdats.insertBll(tLateX, tSimulItr))
						{
							Itr tCurrItr = cExecXdats.findItr(tLateX);
							if (tCurrItr == InvItr) cSimulFreqs[tSimulItr] = 0;
							else cSimulFreqs[tSimulItr] = cCurrFreqs[tCurrItr];
						}
						if (!cSimulFreqs[tSimulItr]) ++cSimulValueCount;
						++cSimulFreqs[tSimulItr];
					}
				}
			}
		}
		sNextXdats.clear(this->mTermSys.SimulClk());
		Dim tSimulValCount = cSimulValueCount;

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
					if (tEmulItr == InvIdx)
					{
						Itr tCurrItr = cExecXdats.findItr(tNextX);
						if (tCurrItr == InvItr) sNextFreqs[tNextItr] = 0;
						else sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
					}
				}
			}
			if (!sNextFreqs[tNextItr]) ++tSimulValCount;
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
				tSimulValCount += tPxRec->NextData(this->mTermSys.SimulClk()) -
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
						if (tEmulItr == InvIdx)
						{
							Itr tCurrItr = cExecXdats.findItr(tLateX);
							sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
						}
					}
				}
				--sNextFreqs[tNextItr];
				if (!sNextFreqs[tNextItr]) --tSimulValCount;

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
						if (tEmulItr == InvIdx)
						{
							Itr tCurrItr = cExecXdats.findItr(tNextX);
							if (tCurrItr == InvItr) sNextFreqs[tNextItr] = 0;
							else sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
						}
					}
				}
				if (!sNextFreqs[tNextItr]) ++tSimulValCount;
				++sNextFreqs[tNextItr];
			}
		}
		#endif
		if (tSimulValCount > mValCountLimit)
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulValCount - mValCountLimit);
		else
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(), 0);
	}
	#endif//CompLazy
	#endif//SimulDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in emulation mode.
*/
template <typename pxt, typename fmt>
void AtmostValueCountXFcMHnT<pxt,fmt>::emulBklg()
{
	WatchError
	cEmulValueCount = cExecValueCount;
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
				Itr tCurrItr = cExecXdats.findItr(tLateX);
				if (tCurrItr == InvItr) cEmulFreqs[tLateItr] = 0;
				else cEmulFreqs[tLateItr] = cCurrFreqs[tCurrItr];
			}
			if (!cEmulFreqs[tLateItr]) ++cEmulValueCount;
			++cEmulFreqs[tLateItr];
		}
		else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
		{
			// drop curr xdat
			Itr tLateItr;
			pxt const & tCurrX = mPxRecs[tPos]->CurrBuff;
			if (cEmulXdats.insertBll(tCurrX, tLateItr))
			{
				Itr tCurrItr = cCurrPxItrs[tPos];
				cEmulFreqs[tLateItr] = cCurrFreqs[tCurrItr];
			}
			--cEmulFreqs[tLateItr];
			if (!cEmulFreqs[tLateItr]) --cEmulValueCount;

			//	add late xdat
			pxt const & tLateX = mPxRecs[tPos]->LateBuff;
			if (cEmulXdats.insertBll(tLateX, tLateItr))
			{
				Itr tCurrItr = cExecXdats.findItr(tLateX);
				if (tCurrItr == InvItr) cEmulFreqs[tLateItr] = 0;
				else cEmulFreqs[tLateItr] = cCurrFreqs[tCurrItr];
			}
			if (!cEmulFreqs[tLateItr]) ++cEmulValueCount;
			++cEmulFreqs[tLateItr];
		}
	}

	if (cEmulValueCount > mValCountLimit)
		this->mMetricRec->updtLate(this->mTermSys.EmulClk(), cEmulValueCount - mValCountLimit);
	else
		this->mMetricRec->updtLate(this->mTermSys.EmulClk(), 0);
	CatchError
}
#endif//CompLazy



/*!
	Sync the exec clock.
*/
template <typename pxt, typename fmt>
void AtmostValueCountXFcMHnT<pxt,fmt>::syncExecClk()
{
	WatchError
	cXdatItrs.syncClk();
	#if CompLazy
	cEmulXdats.syncClk();
	#endif
	AggFcMHnT<fmt>::syncExecClk();
	CatchError
}


/*!
	Sync the simul clock.
*/
template <typename pxt, typename fmt>
void AtmostValueCountXFcMHnT<pxt,fmt>::syncSimulClk()
{
	WatchError
	sNextXdats.syncClk();
	AggFcMHnT<fmt>::syncSimulClk();
	CatchError
}


#if SimulDnwdCache
/*!
	Sync the simul cache clock.
*/
template <typename pxt, typename fmt>
void AtmostValueCountXFcMHnT<pxt,fmt>::syncSimulCacheClk()
{
	WatchError
	cSimulXdats.syncClk();
	AggFcMHnT<fmt>::syncSimulCacheClk();
	CatchError
}
#endif//SimulDnwdCache

closeKangarooSpace


#endif//AtmostValueCountXFcMHnT
