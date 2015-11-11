/*!
	@file atmostserialcountxfcmhnt.tcc
	@brief The prototype file for AtmostSerialCountXFcMHnT template class.
	@details This is the prototype file for AtmostSerialCountXFcMHnT template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef AtmostSerialCountXFcMHnTTccIncluded
#define AtmostSerialCountXFcMHnTTccIncluded



#include "cbls/funcs/fcmhns/aggfcmhnt.tcc"
#include "cbls/frames/idx.hh"



openKangarooSpace



/*!
	@class AtmostSerialCountXFcMHnT
	@brief A class to represent at most serial count fcmhns.
	@details This class represents at most serial count fcmhns.
*/
template <typename pxt, typename fmt>
class AtmostSerialCountXFcMHnT : public AggFcMHnT<fmt>
{
	public:
		static Hdl def(Fss const theFss, Hdl const hdlSys, Prm * thePrms, Dim const PrmCount,
												Dim const SerialCount, Dim const CountLimit);		//!< Definition.

		static AtmostSerialCountXFcMHnT<pxt,fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static AtmostSerialCountXFcMHnT<pxt,fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static AtmostSerialCountXFcMHnT<pxt,fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static AtmostSerialCountXFcMHnT<pxt,fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static AtmostSerialCountXFcMHnT<pxt,fmt> const & cast(Term const & theTerm);	//!< Perform casting.
		static AtmostSerialCountXFcMHnT<pxt,fmt> const * cast(Term const * theTerm);	//!< Perform casting.
		static AtmostSerialCountXFcMHnT<pxt,fmt> & cast(Term & theTerm);				//!< Perform casting.
		static AtmostSerialCountXFcMHnT<pxt,fmt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);						//!< Whether suits casting.
		static Bll suit(Term const * theTerm);						//!< Whether suits casting.
		static Bll suit(Term & theTerm);							//!< Whether suits casting.
		static Bll suit(Term * theTerm);							//!< Whether suits casting.

		//! @}

	private:

		AtmostSerialCountXFcMHnT(Fss const theFss, Hdl const hdlSys, Prm * thePrms,
									Dim const PrmCount,	Dim const SerialCount, Dim const CountLimit);	//!< Constructor.
		AtmostSerialCountXFcMHnT(AtmostSerialCountXFcMHnT<pxt,fmt> const & that);						//!< Duplicator.
		AtmostSerialCountXFcMHnT const & operator = (AtmostSerialCountXFcMHnT<pxt,fmt> const & that);	//!< Assigner.
		~AtmostSerialCountXFcMHnT();																	//!< Destructor.

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
		Dim const mSerialCount;						//!< Serial count.
		Dim const mCountLimit;						//!< Value count limit.

		#if SimulDnwdCache
		Dim	            cSimulSerialCount;		//!< Simulation cache metric.
		#endif//SimulDnwd
		Dim         	cExecSerialCount;		//!< Execution cache metric.
		#if CompLazy
		Dim         	cEmulSerialCount;		//!< Emulation cache metric.
		#endif//CompLazy

		b1<BuffType,kmm> * cExecHintMin;	//!< Execution cache hint min.
		ll<Sqn,kmm>		 * sChgdHintMin;	//!< Hint mins that undergone changes.

		//	the number of possible values would be serial count
		lu<Srl,kmm>				cExecXdats;		//!< Exec xdats for the parameters.
		b1<Pos,kmm>				cXdatRoots;		//!< Xdat to cluster-root mapping.
		b1<Dim,kmm> 			cCurrFreqs;		//!< Curr freqs of the xdats.
		b1<Dim,kmm>				cPrevFreqs;		//!< Prev freqs for changed Xdats.
		ll<Srl,kmm>				cXdatSrls;		//!< Idxs of Xdats with changes.

		//	maintained for each parameter and used in execution.
		cl<Pos,kmm> 			cXdatPrms;		//!< Parameters having the same Xdat.
		b1<Srl,kmm> 			cCurrPxSrls;	//!< Curr xdat indexes for params.
		b1<Srl,kmm> 			sPrevPxSrls;	//!< Prev Xdat indexes for params.

		lu<Srl,kmm>				sNextXdats;		//!< Simul xdats for the parameters.
		b1<Dim,kmm>				sNextFreqs;		//!< Simul xdats for the parameters.

		#if CompLazy
		lu<Srl,kmm>				cEmulXdats;		//!< Emulation xdats.
		b1<Dim,kmm>				cEmulFreqs;		//!< Emulation freqs.
		#endif

		#if SimulDnwdCache
		//	used in simulation
		lu<Srl,kmm>				cSimulXdats;	//!< Cache for simul xdats.
		b1<Dim,kmm>				cSimulFreqs;	//!< Cache for simul freqs.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AtmostSerialCountXFcMHnT<pxt,fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< AtmostSerialCountXFcMHnT<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AtmostSerialCountXFcMHnT<pxt,fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< AtmostSerialCountXFcMHnT<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AtmostSerialCountXFcMHnT<pxt,fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< AtmostSerialCountXFcMHnT<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt>
inline Bll AtmostSerialCountXFcMHnT<pxt,fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< AtmostSerialCountXFcMHnT<pxt,fmt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AtmostSerialCountXFcMHnT<pxt,fmt> const & AtmostSerialCountXFcMHnT<pxt,fmt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< AtmostSerialCountXFcMHnT<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AtmostSerialCountXFcMHnT<pxt,fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AtmostSerialCountXFcMHnT<pxt,fmt> const * AtmostSerialCountXFcMHnT<pxt,fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< AtmostSerialCountXFcMHnT<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AtmostSerialCountXFcMHnT<pxt,fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AtmostSerialCountXFcMHnT<pxt,fmt> & AtmostSerialCountXFcMHnT<pxt,fmt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< AtmostSerialCountXFcMHnT<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AtmostSerialCountXFcMHnT<pxt,fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt>
inline AtmostSerialCountXFcMHnT<pxt,fmt> * AtmostSerialCountXFcMHnT<pxt,fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< AtmostSerialCountXFcMHnT<pxt,fmt> >::TermCls) Wtxt(eWrongCls);

	return scast<AtmostSerialCountXFcMHnT<pxt,fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to an at most serial count.
*/
template <typename pxt, typename fmt>
inline AtmostSerialCountXFcMHnT<pxt,fmt> & AtmostSerialCountXFcMHnT<pxt,fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an at most serial count.
*/
template <typename pxt, typename fmt>
inline AtmostSerialCountXFcMHnT<pxt,fmt> * AtmostSerialCountXFcMHnT<pxt,fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an at most serial count.
*/
template <typename pxt, typename fmt>
inline AtmostSerialCountXFcMHnT<pxt,fmt> const & AtmostSerialCountXFcMHnT<pxt,fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an at most serial count.
*/
template <typename pxt, typename fmt>
inline AtmostSerialCountXFcMHnT<pxt,fmt> const * AtmostSerialCountXFcMHnT<pxt,fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pxt, typename fmt>
inline AtmostSerialCountXFcMHnT<pxt,fmt>::~AtmostSerialCountXFcMHnT()
{
	WatchError
	if (cExecHintMin) delete cExecHintMin;
	if (sChgdHintMin) delete sChgdHintMin;
	CatchError
}


/*!
	Define an at most serial count fcmhn in the sys.
*/
template <typename pxt, typename fmt>
Hdl AtmostSerialCountXFcMHnT<pxt,fmt>::def(Fss const theFss, Hdl const hdlSys, Prm * thePrms,
					Dim const PrmCount, Dim const SerialCount, Dim const CountLimit)
{
	WatchError
	Warn(PrmCount < 1 || PrmCount > MaxDim, eParamCount2(PrmCount, MaxDim));

	AtmostSerialCountXFcMHnT<pxt,fmt> * tFcMHn = new
			AtmostSerialCountXFcMHnT<pxt,fmt>(theFss, hdlSys, thePrms, PrmCount, SerialCount, CountLimit);
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
AtmostSerialCountXFcMHnT<pxt,fmt>::AtmostSerialCountXFcMHnT(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, Dim const SerialCount, Dim const CountLimit) :
		AggFcMHnT<fmt>(hdlSys, PrmCount), mPxRecs(PrmCount), mSerialCount(SerialCount),
		mCountLimit(CountLimit), cExecHintMin(Null), sChgdHintMin(Null), cExecXdats(SerialCount),
		cXdatRoots(SerialCount), cCurrFreqs(SerialCount), cPrevFreqs(SerialCount),
		cXdatSrls(SerialCount), cXdatPrms(PrmCount), cCurrPxSrls(PrmCount),
		sPrevPxSrls(PrmCount), sNextXdats(SerialCount), sNextFreqs(SerialCount)
		#if CompLazy
		, cEmulXdats(PrmCount), cEmulFreqs(PrmCount)
		#endif
		#if SimulDnwdCache
		, cSimulXdats(PrmCount), cSimulFreqs(PrmCount)
		#endif
{
	WatchError
	this->setTermCls(TermStub< AtmostSerialCountXFcMHnT<pxt,fmt> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Unordered);
	this->setTermHvl(this->calcTermHvl());
	Warn(!mCountLimit, eEmptyDimension);
	Warn(!mSerialCount, mEmptyCount);
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename fmt>
AtmostSerialCountXFcMHnT<pxt,fmt>::AtmostSerialCountXFcMHnT(AtmostSerialCountXFcMHnT const & that) :
		AggFcMHnT<fmt>(that), mPxRecs(0), mSerialCount(0), mCountLimit(0), cExecXdats(0), cXdatRoots(0),
		cCurrFreqs(0), cPrevFreqs(0), cXdatSrls(0), cXdatPrms(0), cCurrPxSrls(0),
		sPrevPxSrls(0), sNextXdats(0), sNextFreqs(0)
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
AtmostSerialCountXFcMHnT<pxt,fmt> const & AtmostSerialCountXFcMHnT<pxt,fmt>::operator = (AtmostSerialCountXFcMHnT<pxt,fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template <typename pxt, typename fmt>
void AtmostSerialCountXFcMHnT<pxt,fmt>::compConst()
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

	cExecSerialCount = 0;
	for(Sqn tSqn = 0; tSqn < this->FuncVars.itemCount(); ++tSqn)
		cExecHintMin->item(tSqn) = 0;

	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		pxt const & tCurrX = mPxRecs[tPos]->CurrData();
		Srl const tCurrSrl = castSrl(tCurrX);
		if (cExecXdats.tagBll(tCurrSrl))
		{
			++cExecSerialCount;
			cXdatRoots[tCurrSrl] = tPos;
			cCurrFreqs[tCurrSrl] = 1;
			cXdatPrms.alter(tPos, tPos);
		}
		else
		{
			++cCurrFreqs[tCurrSrl];
			cXdatPrms.alter(tPos, cXdatRoots[tCurrSrl]);
		}
		cCurrPxSrls[tPos] = tCurrSrl;
	}

	for(Pos tPos = 0; tPos < this->PrmVars.listCount(); ++tPos)
	{
		b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tPos];
		Srl const tPxSrl = cCurrPxSrls[tPos];
		Dim tFreq = this->PrmVars.listCount() - cCurrFreqs[tPxSrl];

		for(Idx tIdx = 0; tIdx < tPrmVars.itemCount(); ++tIdx)
		{
			Sqn const tSqn = tPrmVars[tIdx];
			cExecHintMin->item(tSqn) += tFreq;
		}
	}

	if (cExecSerialCount > mCountLimit)
		this->mMetricRec->finalise(cExecSerialCount - mCountLimit);
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
void AtmostSerialCountXFcMHnT<pxt,fmt>::execAnew()
{
	WatchError
	cExecSerialCount = 0;
	for(Sqn tSqn = 0; tSqn < this->FuncVars.itemCount(); ++tSqn)
		cExecHintMin->item(tSqn) = 0;

	cExecXdats.sweep(this->mTermSys.ExecClk());

	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if ExecDnwd
		Term::performExecAnew(this->mPrmTerms[tPos]);
		#endif//ExecDnwd

		pxt const & tCurrX = mPxRecs[tPos]->CurrData();
		Srl const tCurrSrl = castSrl(tCurrX);
		if (cExecXdats.tagBll(tCurrSrl))
		{
			++cExecSerialCount;
			cCurrFreqs[tCurrSrl] = 1;
			cXdatRoots[tCurrSrl] = tPos;
			cXdatPrms.alter(tPos, tPos);
		}
		else
		{
			++cCurrFreqs[tCurrSrl];
			cXdatPrms.alter(tPos, cXdatRoots[tCurrSrl]);
		}
		cCurrPxSrls[tPos] = tCurrSrl;
	}

	for(Pos tPos = 0; tPos < this->PrmVars.listCount(); ++tPos)
	{
		b1<Sqn,xmm> const & tPrmVars = this->PrmVars[tPos];
		Srl const tPxSrl = cCurrPxSrls[tPos];
		Dim tFreq = this->PrmVars.listCount() - cCurrFreqs[tPxSrl];

		for(Idx tIdx = 0; tIdx < tPrmVars.itemCount(); ++tIdx)
		{
			Sqn const tSqn = tPrmVars[tIdx];
			cExecHintMin->item(tSqn) += tFreq;
		}
	}

	cXdatSrls.sweep(this->mTermSys.ExecClk());	// this help uneval

	if (cExecSerialCount > mCountLimit)
		this->mMetricRec->initCurr(cExecSerialCount - mCountLimit);
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
void AtmostSerialCountXFcMHnT<pxt,fmt>::simulAnew()
{
	WatchError
	sNextXdats.sweep(this->mTermSys.SimulClk());
	Dim tSimulSerialCount = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if SimulDnwd
		Term::performSimulAnew(this->mPrmTerms[tPos]);
		#endif//SimulDnwd
		pxt const & tNextX = mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
		Srl const tNextSrl = castSrl(tNextX);
		if (sNextXdats.tagBll(tNextSrl))
			++tSimulSerialCount;
	}
	if (tSimulSerialCount > mCountLimit)
		this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulSerialCount - mCountLimit);
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
void AtmostSerialCountXFcMHnT<pxt,fmt>::undoEval(Pos const thePos)
{
	WatchError
	// delete prev value
	Srl const tXdatSrl = cCurrPxSrls[thePos];
	if (cXdatSrls.tagBll(tXdatSrl))
		cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
	--cCurrFreqs[tXdatSrl];
	if (!cCurrFreqs[tXdatSrl])
	{
		--cExecSerialCount;
		cXdatRoots[tXdatSrl] = InvPos;
	}
	else
	{
		//	delete from cycles
		if (cXdatPrms.successor(thePos) != thePos)
		{
			if (cXdatRoots[tXdatSrl] == thePos)
				cXdatRoots[tXdatSrl] = cXdatPrms.successor(thePos);
			cXdatPrms.alter(thePos, thePos);
		}
		else
			cXdatRoots[tXdatSrl] = InvPos;
	}
	CatchError
}
#endif//CompLazy



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt>
void AtmostSerialCountXFcMHnT<pxt,fmt>::execIncr()
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
				Srl tXdatSrl = cCurrPxSrls[tPos];
				if (cXdatSrls.tagBll(tXdatSrl))
					cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
				--cCurrFreqs[tXdatSrl];
				if (!cCurrFreqs[tXdatSrl])
				{
					--cExecSerialCount;
					cXdatRoots[tXdatSrl] = InvPos;
				}
				else
				{
					//	delete from cycles
					if (cXdatPrms.successor(tPos) != tPos)
					{
						if (cXdatRoots[tXdatSrl] == tPos)
							cXdatRoots[tXdatSrl] = cXdatPrms.successor(tPos);
						cXdatPrms.alter(tPos, tPos);
					}
					else
						cXdatRoots[tXdatSrl] = InvPos;
				}

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				tXdatSrl = castSrl(tCurrX);
				if (cExecXdats.tagBll(tXdatSrl))
					cCurrFreqs[tXdatSrl] = 0;

				sPrevPxSrls[tPos] = cCurrPxSrls[tPos];
				cCurrPxSrls[tPos] = tXdatSrl;

				if (!cCurrFreqs[tXdatSrl])
				{
					++cExecSerialCount;
					cXdatRoots[tXdatSrl] = InvPos;
				}
				if (cXdatSrls.tagBll(tXdatSrl))
					cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
				++cCurrFreqs[tXdatSrl];
			}
		}

		for(Idx tIdx = 0; tIdx < cXdatSrls.tagCount(); ++tIdx)
		{
			Srl tXdatSrl = cXdatSrls[tIdx];
			Num tHintMin1 = cCurrFreqs[tXdatSrl];
			Num tHintMin2 = cPrevFreqs[tXdatSrl];

			if (!tHintMin1)	//	new freq == 0
				cExecXdats.untagBll(tXdatSrl);
				//	after elimination, the index is stll assumed to be valid
				//	for the properties that use the index such as XdatRoots, CurrFreqs
				//	PrevFreqs, and XdatIdxs.

			Num tHintMin = tHintMin1 - tHintMin2;

			if (!tHintMin) continue;

			Pos tCurrPos = cXdatRoots[tXdatSrl], tSentPos = tCurrPos;
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
				if (cXdatRoots[cCurrPxSrls[tPos]] == InvPos)
					cXdatRoots[cCurrPxSrls[tPos]] = tPos;
				cXdatPrms.alter(tPos, cXdatRoots[cCurrPxSrls[tPos]]);
				Num tHintMin1 = cCurrFreqs[cCurrPxSrls[tPos]];
				Num tHintMin2 = cPrevFreqs[sPrevPxSrls[tPos]];

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

		cXdatSrls.sweep(this->mTermSys.ExecClk());
		if (cExecSerialCount > mCountLimit)
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecSerialCount - mCountLimit);
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
					Srl tXdatSrl = cCurrPxSrls[tPos];
					if (cXdatSrls.tagBll(tXdatSrl))
						cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
					--cCurrFreqs[tXdatSrl];
					if (!cCurrFreqs[tXdatSrl])
					{
						--cExecSerialCount;
						cXdatRoots[tXdatSrl] = InvPos;
					}
					else
					{
						//	delete from cycles
						if (cXdatPrms.successor(tPos) != tPos)
						{
							if (cXdatRoots[tXdatSrl] == tPos)
								cXdatRoots[tXdatSrl] = cXdatPrms.successor(tPos);
							cXdatPrms.alter(tPos, tPos);
						}
						else
							cXdatRoots[tXdatSrl] = InvPos;
					}

					//	add new value
					pxt const & tCurrX = mPxRecs[tPos]->CurrData();
					tXdatSrl = castSrl(tCurrX);
					if (cExecXdats.tagBll(tXdatSrl))
						cCurrFreqs[tXdatSrl] = 0;
					sPrevPxSrls[tPos] = cCurrPxSrls[tPos];
					cCurrPxSrls[tPos] = tXdatSrl;

					if (!cCurrFreqs[tXdatSrl])
					{
						++cExecSerialCount;
						cXdatRoots[tXdatSrl] = InvPos;
					}
					if (cXdatSrls.tagBll(tXdatSrl))
						cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
					++cCurrFreqs[tXdatSrl];
				}
			}

			for(Idx tIdx = 0; tIdx < cXdatSrls.tagCount(); ++tIdx)
			{
				Srl tXdatSrl = cXdatSrls[tIdx];
				Num tHintMin1 = cCurrFreqs[tXdatSrl];
				Num tHintMin2 = cPrevFreqs[tXdatSrl];

				if (!tHintMin1)	//	new freq == 0
					cExecXdats.untagBll(tXdatSrl);

				Num tHintMin = tHintMin1 - tHintMin2;
				if (!tHintMin) continue;

				Pos tCurrPos = cXdatRoots[tXdatSrl], tSentPos = tCurrPos;
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
					if (cXdatRoots[cCurrPxSrls[tPos]] == InvPos)
						cXdatRoots[cCurrPxSrls[tPos]] = tPos;
					cXdatPrms.alter(tPos, cXdatRoots[cCurrPxSrls[tPos]]);
					Num tHintMin1 = cCurrFreqs[cCurrPxSrls[tPos]];
					Num tHintMin2 = cPrevFreqs[sPrevPxSrls[tPos]];

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

			cXdatSrls.sweep(this->mTermSys.ExecClk());
			if (cExecSerialCount > mCountLimit)
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecSerialCount - mCountLimit);
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
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				Srl const tXdatSrl = castSrl(tCurrX);
				if (cExecXdats.tagBll(tXdatSrl))
					cCurrFreqs[tXdatSrl] = 0;
				sPrevPxSrls[tPos] = cCurrPxSrls[tPos];
				cCurrPxSrls[tPos] = tXdatSrl;

				if (!cCurrFreqs[tXdatSrl])
				{
					++cExecSerialCount;
					cXdatRoots[tXdatSrl] = InvPos;
				}
				if (cXdatSrls.tagBll(tXdatSrl))
					cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
				++cCurrFreqs[tXdatSrl];
			}
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			{
				// delete prev value
				Srl tXdatSrl = cCurrPxSrls[tPos];
				if (cXdatSrls.tagBll(tXdatSrl))
					cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
				--cCurrFreqs[tXdatSrl];
				if (!cCurrFreqs[tXdatSrl])
				{
					--cExecSerialCount;
					cXdatRoots[tXdatSrl] = InvPos;
				}
				else
				{
					//	delete from cycles
					if (cXdatPrms.successor(tPos) != tPos)
					{
						if (cXdatRoots[tXdatSrl] == tPos)
							cXdatRoots[tXdatSrl] = cXdatPrms.successor(tPos);
						cXdatPrms.alter(tPos, tPos);
					}
					else
						cXdatRoots[tXdatSrl] = InvPos;
				}

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				tXdatSrl = castSrl(tCurrX);
				if (cExecXdats.tagBll(tXdatSrl))
					cCurrFreqs[tXdatSrl] = 0;
				sPrevPxSrls[tPos] = cCurrPxSrls[tPos];
				cCurrPxSrls[tPos] = tXdatSrl;

				if (!cCurrFreqs[tXdatSrl])
				{
					++cExecSerialCount;
					cXdatRoots[tXdatSrl] = InvPos;
				}
				if (cXdatSrls.tagBll(tXdatSrl))
					cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
				++cCurrFreqs[tXdatSrl];
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
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				Srl const tXdatSrl = castSrl(tCurrX);
				if (cExecXdats.tagBll(tXdatSrl))
					cCurrFreqs[tXdatSrl] = 0;
				sPrevPxSrls[tPos] = cCurrPxSrls[tPos];
				cCurrPxSrls[tPos] = tXdatSrl;

				if (!cCurrFreqs[tXdatSrl])
				{
					++cExecSerialCount;
					cXdatRoots[tXdatSrl] = InvPos;
				}

				if (cXdatSrls.tagBll(tXdatSrl))
					cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
				++cCurrFreqs[tXdatSrl];
			}
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			{
				// delete prev value
				Srl tXdatSrl = cCurrPxSrls[tPos];
				if (cXdatSrls.tagBll(tXdatSrl))
					cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
				--cCurrFreqs[tXdatSrl];
				if (!cCurrFreqs[tXdatSrl])
				{
					--cExecSerialCount;
					cXdatRoots[tXdatSrl] = InvPos;
				}
				else
				{
					//	delete from cycles
					if (cXdatPrms.successor(tPos) != tPos)
					{
						if (cXdatRoots[tXdatSrl] == tPos)
							cXdatRoots[tXdatSrl] = cXdatPrms.successor(tPos);
						cXdatPrms.alter(tPos, tPos);
					}
					else
						cXdatRoots[tXdatSrl] = InvPos;
				}

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				tXdatSrl = castSrl(tCurrX);
				if (cExecXdats.tagBll(tXdatSrl))
					cCurrFreqs[tXdatSrl] = 0;
				sPrevPxSrls[tPos] = cCurrPxSrls[tPos];
				cCurrPxSrls[tPos] = tXdatSrl;

				if (!cCurrFreqs[tXdatSrl])
				{
					++cExecSerialCount;
					cXdatRoots[tXdatSrl] = InvPos;
				}
				if (cXdatSrls.tagBll(tXdatSrl))
					cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
				++cCurrFreqs[tXdatSrl];
			}
		}
		for(Idx tIdx = 0; tIdx < cXdatSrls.tagCount(); ++tIdx)
		{
			Srl tXdatSrl = cXdatSrls[tIdx];
			Num tHintMin1 = cCurrFreqs[tXdatSrl];
			Num tHintMin2 = cPrevFreqs[tXdatSrl];

			if (!tHintMin1)	//	new freq == 0
				cExecXdats.untagBll(tXdatSrl);

			Num tHintMin = tHintMin1 - tHintMin2;
			if (!tHintMin) continue;

			Pos tCurrPos = cXdatRoots[tXdatSrl], tSentPos = tCurrPos;
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
				if (cXdatRoots[cCurrPxSrls[tPos]] == InvPos)
					cXdatRoots[cCurrPxSrls[tPos]] = tPos;
				cXdatPrms.alter(tPos, cXdatRoots[cCurrPxSrls[tPos]]);
				Num tHintMin1 = cCurrFreqs[cCurrPxSrls[tPos]];
				Num tHintMin2 = cPrevFreqs[sPrevPxSrls[tPos]];
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
				if (cXdatRoots[cCurrPxSrls[tPos]] == InvPos)
					cXdatRoots[cCurrPxSrls[tPos]] = tPos;
				cXdatPrms.alter(tPos, cXdatRoots[cCurrPxSrls[tPos]]);
				Num tHintMin1 = cCurrFreqs[cCurrPxSrls[tPos]];
				Num tHintMin2 = cPrevFreqs[sPrevPxSrls[tPos]];
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

		cXdatSrls.sweep(this->mTermSys.ExecClk());
		if (cExecSerialCount > mCountLimit)
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecSerialCount - mCountLimit);
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
void AtmostSerialCountXFcMHnT<pxt,fmt>::execBklg()
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
			pxt const & tCurrX = mPxRecs[tPos]->CurrData();
			Srl const tXdatSrl = castSrl(tCurrX);
			if (cExecXdats.tagBll(tCurrX))
				cCurrFreqs[tXdatSrl] = 0;
			sPrevPxSrls[tPos] = cCurrPxSrls[tPos];
			cCurrPxSrls[tPos] = tXdatSrl;

			if (!cCurrFreqs[tXdatSrl])
			{
				++cExecSerialCount;
				cXdatRoots[tXdatSrl] = InvPos;
			}

			if (cXdatSrls.tagBll(tXdatSrl))
				cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
			++cCurrFreqs[tXdatSrl];
		}
		else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
		{
			// delete prev value
			Srl tXdatSrl = cCurrPxSrls[tPos];
			if (cXdatSrls.tagBll(tXdatSrl))
				cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
			--cCurrFreqs[tXdatSrl];
			if (!cCurrFreqs[tXdatSrl])
			{
				--cExecSerialCount;
				cXdatRoots[tXdatSrl] = InvPos;
			}
			else
			{
				//	delete from cycles
				if (cXdatPrms.successor(tPos) != tPos)
				{
					if (cXdatRoots[tXdatSrl] == tPos)
						cXdatRoots[tXdatSrl] = cXdatPrms.successor(tPos);
					cXdatPrms.alter(tPos, tPos);
				}
				else
					cXdatRoots[tXdatSrl] = InvPos;
			}

			//	add new value
			pxt const & tCurrX = mPxRecs[tPos]->CurrData();
			tXdatSrl = castSrl(tCurrX);
			if (cExecXdats.tagBll(tXdatSrl))
				cCurrFreqs[tXdatSrl] = 0;
			sPrevPxSrls[tPos] = cCurrPxSrls[tPos];
			cCurrPxSrls[tPos] = tXdatSrl;

			if (!cCurrFreqs[tXdatSrl])
			{
				++cExecSerialCount;
				cXdatRoots[tXdatSrl] = InvPos;
			}

			if (cXdatSrls.tagBll(tXdatSrl))
				cPrevFreqs[tXdatSrl] = cCurrFreqs[tXdatSrl];
			++cCurrFreqs[tXdatSrl];
		}
	}

	for(Idx tIdx = 0; tIdx < cXdatSrls.tagCount(); ++tIdx)
	{
		Srl tXdatSrl = cXdatSrls[tIdx];
		Num tHintMin1 = cCurrFreqs[tXdatSrl];
		Num tHintMin2 = cPrevFreqs[tXdatSrl];

		if (!tHintMin1)	//	new freq == 0
			cExecXdats.untagBll(tXdatSrl);

		Num tHintMin = tHintMin1 - tHintMin2;
		if (!tHintMin) continue;

		Pos tCurrPos = cXdatRoots[tXdatSrl], tSentPos = tCurrPos;
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
			if (cXdatRoots[cCurrPxSrls[tPos]] == InvPos)
				cXdatRoots[cCurrPxSrls[tPos]] = tPos;
			cXdatPrms.alter(tPos, cXdatRoots[cCurrPxSrls[tPos]]);
			Num tHintMin1 = cCurrFreqs[cCurrPxSrls[tPos]];
			Num tHintMin2 = cPrevFreqs[sPrevPxSrls[tPos]];
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

	cXdatSrls.sweep(this->mTermSys.ExecClk());
	if (cExecSerialCount > mCountLimit)
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(), cExecSerialCount - mCountLimit);
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
void AtmostSerialCountXFcMHnT<pxt,fmt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		Dim tSimulSerialCount = cExecSerialCount;
		sNextXdats.sweep(this->mTermSys.SimulClk());
		for(Idx tIdx = 0; tIdx < this->mSimulChgdPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mSimulChgdPrms.serial(tIdx);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
			if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
			{
				// drop curr xdat
				pxt const & tCurrX = mPxRecs[tPos]->CurrBuff;
				Srl const tNextSrl = castSrl(tCurrX);
				if (sNextXdats.tagBll(tNextSrl))
				{
					Srl tCurrSrl = cCurrPxSrls[tPos];
					sNextFreqs[tNextSrl] = cCurrFreqs[tCurrSrl];
				}
				--sNextFreqs[tNextSrl];
				if (!sNextFreqs[tNextSrl]) --tSimulSerialCount;

				//	add next xdat
				pxt const & tNextX = mPxRecs[tPos]->NextBuff;
				tNextSrl = castSrl(tNextX);
				if (sNextXdats.tagBll(tNextSrl))
				{
					Srl tCurrSrl = cExecXdats.findSrl(tNextX);
					if (tCurrSrl == InvSrl) sNextFreqs[tNextSrl] = 0;
					else sNextFreqs[tNextSrl] = cCurrFreqs[tCurrSrl];
				}
				if (!sNextFreqs[tNextSrl]) ++tSimulSerialCount;
				++sNextFreqs[tNextSrl];
			}
		}
		if (tSimulSerialCount > mCountLimit)
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulSerialCount - mCountLimit);
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
			cSimulSerialCount = cExecSerialCount;
			cSimulXdats.sweep(this->mTermSys.SimulCacheClk());
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				Srl const tSimulSrl = castSrl(tCurrX);
				if (cSimulXdats.tagBll(tSimulSrl))
				{
					Srl tCurrSrl = cCurrPxSrls[tPos];
					cSimulFreqs[tSimulSrl] = cCurrFreqs[tCurrSrl];
				}
				--cSimulFreqs[tSimulSrl];
				if (!cSimulFreqs[tSimulSrl]) --cSimulSerialCount;
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
			sNextXdats.sweep(this->mTermSys.SimulClk());

			#if SimulFixed
			Dim tSimulSerialCount = cSimulSerialCount;
			#else
			Dim tSimulSerialCount = cExecSerialCount;
			#endif
			#if SimulFixed
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				Term::performSimulIncr(this->mPrmTerms[tPos]);

				pxt const & tNextX = mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
				Srl const tNextSrl = castSrl(tNextX);
				if (sNextXdats.tagBll(tNextSrl))
				{
					Srl tSimulSrl = cSimulXdats.findSrl(tNextX);
					if (tSimulSrl != InvSrl)
						sNextFreqs[tNextSrl] = cSimulFreqs[tSimulSrl];
					else
					{
						Srl tCurrSrl = cExecXdats.findSrl(tNextX);
						if (tCurrSrl == InvSrl) sNextFreqs[tNextSrl] = 0;
						else sNextFreqs[tNextSrl] = cCurrFreqs[tCurrSrl];
					}
				}

				if (!sNextFreqs[tNextSrl]) ++tSimulSerialCount;
				++sNextFreqs[tNextSrl];
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
					pxt const & tCurrX = mPxRecs[tPos]->CurrBuff;
					Srl tNextSrl = castSrl(tCurrX);
					if (sNextXdats.tagBll(tNextSrl))
					{
						#if SimulFixed
						Srl tSimulSrl = cSimulXdats.findSrl(tCurrX);
						if (tSimulSrl != InvSrl)
							sNextFreqs[tNextSrl] = cSimulFreqs[tSimulSrl];
						else
						#endif
						{
							Srl tCurrSrl = cCurrPxSrls[tPos];
							sNextFreqs[tNextSrl] = cCurrFreqs[tCurrSrl];
						}
					}
					--sNextFreqs[tNextSrl];
					if (!sNextFreqs[tNextSrl]) --tSimulSerialCount;

					//	add next xdat
					pxt const & tNextX = mPxRecs[tPos]->NextBuff;
					tNextSrl = castSrl(tNextX);
					if (sNextXdats.tagBll(tNextSrl))
					{
						#if SimulFixed
						Srl tSimulSrl = cSimulXdats.findSrl(tNextX);
						if (tSimulSrl != InvSrl)
							sNextFreqs[tNextSrl] = cSimulFreqs[tSimulSrl];
						else
						#endif
						{
							Srl tCurrSrl = cExecXdats.findSrl(tNextX);
							if (tCurrSrl == InvSrl) sNextFreqs[tNextSrl] = 0;
							else sNextFreqs[tNextSrl] = cCurrFreqs[tCurrSrl];
						}
					}
					if (!sNextFreqs[tNextSrl]) ++tSimulSerialCount;
					++sNextFreqs[tNextSrl];
				}
			}
			#endif //SimulFlexi
			if (tSimulSerialCount > mCountLimit)
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulSerialCount - mCountLimit);
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
			cSimulXdats.sweep(this->mTermSys.SimulCacheClk());
			if (!this->chgdEmulClk())
			{
				cSimulSerialCount = cEmulSerialCount;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);

					pxt const & tLateX = mPxRecs[tPos]->LateData(this->mTermSys.EmulClk());
					Srl const tSimulSrl = castSrl(tLateX);

					if (cSimulXdats.tagBll(tSimulSrl))
					{
						Srl tEmulSrl = cEmulXdats.findSrl(tLateX);
						if (tEmulSrl != InvSrl)
							cSimulFreqs[tSimulSrl] = cEmulFreqs[tEmulSrl];
						else
						{
							Srl tCurrSrl = cCurrPxSrls[tPos];
							cSimulFreqs[tSimulSrl] = cCurrFreqs[tCurrSrl];
						}
					}
					--cSimulFreqs[tSimulSrl];
					if (!cSimulFreqs[tSimulSrl]) --cSimulSerialCount;
				}
				#endif //SimulFixed
			}
			else
			{
				cSimulSerialCount = cExecSerialCount;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					if (!this->mEvalUndonePrms->tagged(tPos))
					{
						pxt const & tCurrX = mPxRecs[tPos]->CurrData();
						Srl tSimulSrl = castSrl(tCurrX);
						if (cSimulXdats.tagBll(tSimulSrl))
						{
							Srl tCurrSrl = cCurrPxSrls[tPos];
							cSimulFreqs[tSimulSrl] = cCurrFreqs[tCurrSrl];
						}
						--cSimulFreqs[tSimulSrl];
						if (!cSimulFreqs[tSimulSrl]) --cSimulSerialCount;
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
						pxt const & tLateX = tPxRec->LateData(this->mTermSys.EmulClk());
						Srl tSimulSrl = castSrl(tLateX);

						if (cSimulXdats.tagBll(tSimulSrl))
						{
							Srl tCurrSrl = cExecXdats.findSrl(tLateX);
							if (tCurrSrl == InvSrl) cSimulFreqs[tSimulSrl] = 0;
							else cSimulFreqs[tSimulSrl] = cCurrFreqs[tCurrSrl];
						}
						if (!cSimulFreqs[tSimulSrl]) ++cSimulSerialCount;
						++cSimulFreqs[tSimulSrl];
					}
					else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
					{
						// drop curr value
						pxt const & tCurrX = mPxRecs[tPos]->CurrBuff;
						Srl tSimulSrl = castSrl(tCurrX);
						if (cSimulXdats.tagBll(tSimulSrl))
						{
							Srl tCurrSrl = cCurrPxSrls[tPos];
							cSimulFreqs[tSimulSrl] = cCurrFreqs[tCurrSrl];
						}
						--cSimulFreqs[tSimulSrl];
						if (!cSimulFreqs[tSimulSrl]) --cSimulSerialCount;

						//	add late value
						pxt const & tLateX = mPxRecs[tPos]->LateBuff;
						tSimulSrl = castSrl(tLateX);
						if (cSimulXdats.tagBll(tSimulSrl))
						{
							Srl tCurrSrl = cExecXdats.findSrl(tLateX);
							if (tCurrSrl == InvSrl) cSimulFreqs[tSimulSrl] = 0;
							else cSimulFreqs[tSimulSrl] = cCurrFreqs[tCurrSrl];
						}
						if (!cSimulFreqs[tSimulSrl]) ++cSimulSerialCount;
						++cSimulFreqs[tSimulSrl];
					}
				}
			}
		}
		sNextXdats.sweep(this->mTermSys.SimulClk());
		Dim tSimulSerialCount = cSimulSerialCount;

		#if SimulFixed
		for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFixedPrms->item(tIdx);
			Term::performSimulIncr(this->mPrmTerms[tPos]);

			pxt const & tNextX = mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
			Srl tNextSrl = castSrl(tNextX);
			if (sNextXdats.tagBll(tNextSrl))
			{
				Srl tSimulSrl = cSimulXdats.findSrl(tNextX);
				if (tSimulSrl != InvSrl)
					sNextFreqs[tNextSrl] = cSimulFreqs[tSimulSrl];
				else
				{
					Srl tEmulSrl = InvSrl;
					if (!this->chgdEmulClk())
					{
						tEmulSrl = cEmulXdats.findSrl(tNextX);
						if (tEmulSrl != InvSrl)
							sNextFreqs[tNextSrl] = cEmulFreqs[tEmulSrl];
					}
					if (tEmulSrl == InvIdx)
					{
						Srl tCurrSrl = cExecXdats.findSrl(tNextX);
						if (tCurrSrl == InvSrl) sNextFreqs[tNextSrl] = 0;
						else sNextFreqs[tNextSrl] = cCurrFreqs[tCurrSrl];
					}
				}
			}
			if (!sNextFreqs[tNextSrl]) ++tSimulSerialCount;
			++sNextFreqs[tNextSrl];
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
				tSimulSerialCount += tPxRec->NextData(this->mTermSys.SimulClk()) -
							tPxRec->LateData(this->mTermSys.EmulClk());

				// drop curr value
				pxt const & tLateX = tPxRec->LateData(this->mTermSys.EmulClk());
				Srl tNextSrl = castSrl(tLateX);
				if (sNextXdats.tagBll(tNextSrl))
				{
					Srl tSimulSrl = cSimulXdats.findSrl(tLateX);
					if (tSimulSrl != InvSrl)
						sNextFreqs[tNextSrl] = cSimulFreqs[tSimulSrl];
					else
					{
						Srl tEmulSrl = InvSrl;
						if (!this->chgdEmulClk())
						{
							tEmulSrl = cEmulXdats.findSrl(tLateX);
							if (tEmulSrl != InvSrl)
								sNextFreqs[tNextSrl] = cEmulFreqs[tEmulSrl];
						}
						if (tEmulSrl == InvIdx)
						{
							Srl tCurrSrl = cExecXdats.findSrl(tLateX);
							sNextFreqs[tNextSrl] = cCurrFreqs[tCurrSrl];
						}
					}
				}
				--sNextFreqs[tNextSrl];
				if (!sNextFreqs[tNextSrl]) --tSimulSerialCount;

				//	add next xdat
				pxt const & tNextX = mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
				tNextSrl = castSrl(tNextX);
				if (sNextXdats.tagBll(tNextSrl))
				{
					Srl tSimulSrl = cSimulXdats.findSrl(tNextX);
					if (tSimulSrl != InvSrl)
						sNextFreqs[tNextSrl] = cSimulFreqs[tSimulSrl];
					else
					{
						Srl tEmulSrl = InvSrl;
						if (!this->chgdEmulClk())
						{
							tEmulSrl = cEmulXdats.findSrl(tNextX);
							if (tEmulSrl != InvSrl)
								sNextFreqs[tNextSrl] = cEmulFreqs[tEmulSrl];
						}
						if (tEmulSrl == InvIdx)
						{
							Srl tCurrSrl = cExecXdats.findSrl(tNextX);
							if (tCurrSrl == InvSrl) sNextFreqs[tNextSrl] = 0;
							else sNextFreqs[tNextSrl] = cCurrFreqs[tCurrSrl];
						}
					}
				}
				if (!sNextFreqs[tNextSrl]) ++tSimulSerialCount;
				++sNextFreqs[tNextSrl];
			}
		}
		#endif
		if (tSimulSerialCount > mCountLimit)
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(), tSimulSerialCount - mCountLimit);
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
void AtmostSerialCountXFcMHnT<pxt,fmt>::emulBklg()
{
	WatchError
	cEmulSerialCount = cExecSerialCount;
	cEmulXdats.sweep(this->mTermSys.EmulClk());
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
		{
			pxt const & tLateX = mPxRecs[tPos]->LateData(this->mTermSys.EmulClk());
			Srl tLateSrl = castSrl(tLateSrl);
			if (cEmulXdats.tagBll(tLateSrl))
			{
				Srl tCurrSrl = cExecXdats.findSrl(tLateX);
				if (tCurrSrl == InvSrl) cEmulFreqs[tLateSrl] = 0;
				else cEmulFreqs[tLateSrl] = cCurrFreqs[tCurrSrl];
			}
			if (!cEmulFreqs[tLateSrl]) ++cEmulSerialCount;
			++cEmulFreqs[tLateSrl];
		}
		else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
		{
			// drop curr xdat
			pxt const & tCurrX = mPxRecs[tPos]->CurrBuff;
			Srl tLateSrl = castSrl(tCurrX);
			if (cEmulXdats.tagBll(tLateSrl))
			{
				Srl tCurrSrl = cCurrPxSrls[tPos];
				cEmulFreqs[tLateSrl] = cCurrFreqs[tCurrSrl];
			}
			--cEmulFreqs[tLateSrl];
			if (!cEmulFreqs[tLateSrl]) --cEmulSerialCount;

			//	add late xdat
			pxt const & tLateX = mPxRecs[tPos]->LateBuff;
			tLateSrl = castSrl(tLateX);
			if (cEmulXdats.tagBll(tLateSrl))
			{
				Srl tCurrSrl = cExecXdats.findSrl(tLateX);
				if (tCurrSrl == InvSrl) cEmulFreqs[tLateSrl] = 0;
				else cEmulFreqs[tLateSrl] = cCurrFreqs[tCurrSrl];
			}
			if (!cEmulFreqs[tLateSrl]) ++cEmulSerialCount;
			++cEmulFreqs[tLateSrl];
		}
	}

	if (cEmulSerialCount > mCountLimit)
		this->mMetricRec->updtLate(this->mTermSys.EmulClk(), cEmulSerialCount - mCountLimit);
	else
		this->mMetricRec->updtLate(this->mTermSys.EmulClk(), 0);
	CatchError
}
#endif//CompLazy



/*!
	Sync the exec clock.
*/
template <typename pxt, typename fmt>
void AtmostSerialCountXFcMHnT<pxt,fmt>::syncExecClk()
{
	WatchError
	cXdatSrls.syncClk();
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
void AtmostSerialCountXFcMHnT<pxt,fmt>::syncSimulClk()
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
void AtmostSerialCountXFcMHnT<pxt,fmt>::syncSimulCacheClk()
{
	cSimulXdats.syncClk();
	AggFcMHnT<fmt>::syncSimulCacheClk();
	CatchError
}
#endif//SimulDnwdCache

closeKangarooSpace


#endif//AtmostSerialCountXFcMHnT
