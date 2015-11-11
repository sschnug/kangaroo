/*!
	@file alldiffxfevt.tcc
	@brief The prototype file for AllDiffXFeVt template class.
	@details This is the prototype file for AllDiffXFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef AllDiffXFeVtTccIncluded
#define AllDiffXFeVtTccIncluded



#include "cbls/funcs/fevs/aggfevt.tcc"
#include "cbls/frames/idx.hh"



openKangarooSpace



/*!
	@class AllDiffXFeVt
	@brief A class to represent all different fevs.
	@details This class represents all different fevs.
*/
template <typename pxt, typename fvt>
class AllDiffXFeVt : public AggFeVt<fvt>
{
	public:
		static Hdl def(Fss const theFss, Hdl const hdlSys, Prm * thePrms, Dim const PrmCount);	//!< Definition.

		static AllDiffXFeVt<pxt,fvt> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static AllDiffXFeVt<pxt,fvt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static AllDiffXFeVt<pxt,fvt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static AllDiffXFeVt<pxt,fvt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static AllDiffXFeVt<pxt,fvt> const & cast(Term const & theTerm);	//!< Perform casting.
		static AllDiffXFeVt<pxt,fvt> const * cast(Term const * theTerm);	//!< Perform casting.
		static AllDiffXFeVt<pxt,fvt> & cast(Term & theTerm);				//!< Perform casting.
		static AllDiffXFeVt<pxt,fvt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);							//!< Suits casting?
		static Bll suit(Term const * theTerm);							//!< Suits casting?
		static Bll suit(Term & theTerm);								//!< Suits casting?
		static Bll suit(Term * theTerm);								//!< Suits casting?

		//! @}

	private:

		AllDiffXFeVt(Fss const theFss, Hdl const hdlSys,
											Prm * thePrms, Dim const PrmCount);	//!< Constructor.
		AllDiffXFeVt(AllDiffXFeVt<pxt,fvt> const & that);						//!< Duplicator.
		AllDiffXFeVt const & operator = (AllDiffXFeVt<pxt,fvt> const & that);	//!< Assigner.
		~AllDiffXFeVt();														//!< Destructor.

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

		typedef typename DataStub<fvt>::TempBuff TempType;	//!< Temp buff type.
		typedef typename DataBuff<pxt,fvt>::Type BuffType;	//!< Data buff type.

		b1<EvalRec<pxt> const *,kmm> 	mPxRecs;			//!< Parameter records.

		#if SimulDnwdCache
		Num	cSimulValue;		//!< Simulation cache value.
		#endif//SimulDnwd

		Num	cExecValue;		//!< Execution cache value.

		#if CompLazy
		Num	cEmulValue;		//!< Emulation cache value.
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
template <typename pxt, typename fvt>
inline Bll AllDiffXFeVt<pxt,fvt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< AllDiffXFeVt<pxt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fvt>
inline Bll AllDiffXFeVt<pxt,fvt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< AllDiffXFeVt<pxt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fvt>
inline Bll AllDiffXFeVt<pxt,fvt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< AllDiffXFeVt<pxt,fvt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fvt>
inline Bll AllDiffXFeVt<pxt,fvt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< AllDiffXFeVt<pxt,fvt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fvt>
inline AllDiffXFeVt<pxt,fvt> const & AllDiffXFeVt<pxt,fvt>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< AllDiffXFeVt<pxt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<AllDiffXFeVt<pxt,fvt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fvt>
inline AllDiffXFeVt<pxt,fvt> const * AllDiffXFeVt<pxt,fvt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< AllDiffXFeVt<pxt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<AllDiffXFeVt<pxt,fvt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fvt>
inline AllDiffXFeVt<pxt,fvt> & AllDiffXFeVt<pxt,fvt>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< AllDiffXFeVt<pxt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<AllDiffXFeVt<pxt,fvt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fvt>
inline AllDiffXFeVt<pxt,fvt> * AllDiffXFeVt<pxt,fvt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< AllDiffXFeVt<pxt,fvt> >::TermCls) Wtxt(eWrongCls);

	return scast<AllDiffXFeVt<pxt,fvt> *>(theTerm);
	CatchError
}



/*!
	Refer to an all different.
*/
template <typename pxt, typename fvt>
inline AllDiffXFeVt<pxt,fvt> & AllDiffXFeVt<pxt,fvt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an all different.
*/
template <typename pxt, typename fvt>
inline AllDiffXFeVt<pxt,fvt> * AllDiffXFeVt<pxt,fvt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an all different.
*/
template <typename pxt, typename fvt>
inline AllDiffXFeVt<pxt,fvt> const & AllDiffXFeVt<pxt,fvt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an all different.
*/
template <typename pxt, typename fvt>
inline AllDiffXFeVt<pxt,fvt> const * AllDiffXFeVt<pxt,fvt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pxt, typename fvt>
inline AllDiffXFeVt<pxt,fvt>::~AllDiffXFeVt()
{
	WatchError
	CatchError
}


/*!
	Define an all different fev in the sys.
*/
template <typename pxt, typename fvt>
Hdl AllDiffXFeVt<pxt,fvt>::def(Fss const theFss, Hdl const hdlSys, Prm * thePrms, Dim const PrmCount)
{
	WatchError
	Warn(PrmCount < 2 || PrmCount > MaxDim, eParamCount2(2, MaxDim));

	AllDiffXFeVt<pxt,fvt> * tFeV = new AllDiffXFeVt<pxt,fvt>(theFss, hdlSys, thePrms, PrmCount);
	Hdl const tHdl = tFeV->defSysFunc();
	if (tHdl != InvHdl) { delete tFeV; return tHdl; }

	EvalTbl<pxt> const & tPxTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<fvt> & tFvTbl = EvalTbl<fvt>::refm(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFeV->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFeV->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFeV->mPxRecs[tPos] = tPxTbl.ptrcEvalRec(tPxLoc);
	}

	tFvTbl.setEvalRec(tFeV->mValueRec, tFeV->mValueLoc);

	tFeV->performCompConst();
	tFeV->defSysRoot();
	return tFeV->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
template <typename pxt, typename fvt>
AllDiffXFeVt<pxt,fvt>::AllDiffXFeVt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) : AggFeVt<fvt>(hdlSys, PrmCount), mPxRecs(PrmCount),
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
	this->setTermCls(TermStub< AllDiffXFeVt<pxt,fvt> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Unordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename fvt>
AllDiffXFeVt<pxt,fvt>::AllDiffXFeVt(AllDiffXFeVt const & that) : AggFeVt<fvt>(that), mPxRecs(0),
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
template <typename pxt, typename fvt>
AllDiffXFeVt<pxt,fvt> const & AllDiffXFeVt<pxt,fvt>::operator = (AllDiffXFeVt<pxt,fvt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template <typename pxt, typename fvt>
void AllDiffXFeVt<pxt,fvt>::compConst()
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

	cExecValue = mPxRecs.itemCount();	//	violation = n - #unique-value

	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		Itr tCurrItr;

		pxt const & tCurrX = mPxRecs[tPos]->CurrData();
		if (cExecXdats.insertBll(tCurrX, tCurrItr))
		{
			--cExecValue;
			cCurrFreqs[tCurrItr] = 1;
		}
		else
			++cCurrFreqs[tCurrItr];
		cCurrPxItrs[tPos] = tCurrItr;
	}

	this->mValueRec->finalise(cExecValue);
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fvt>
void AllDiffXFeVt<pxt,fvt>::execAnew()
{
	WatchError
	cExecValue = mPxRecs.itemCount();

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
			--cExecValue;
			cCurrFreqs[tCurrItr] = 1;
		}
		else
			++cCurrFreqs[tCurrItr];
		cCurrPxItrs[tPos] = tCurrItr;
	}

	cXdatItrs.sweep(this->mTermSys.ExecClk());	// this help uneval

	this->mValueRec->initCurr(cExecValue);
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename fvt>
void AllDiffXFeVt<pxt,fvt>::simulAnew()
{
	WatchError
	sNextXdats.clear(this->mTermSys.SimulClk());
	BuffType tSimulValue = mPxRecs.itemCount();
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if SimulDnwd
		Term::performSimulAnew(this->mPrmTerms[tPos]);
		#endif//SimulDnwd
		pxt const & tNextX = mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
		if (sNextXdats.insertBll(tNextX))
			--tSimulValue;
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
template <typename pxt, typename fvt>
void AllDiffXFeVt<pxt,fvt>::undoEval(Pos const thePos)
{
	WatchError
	// delete prev value
	Itr tXdatItr = cCurrPxItrs[thePos];
	if (cXdatItrs.tagBll(tXdatItr))
		cPrevFreqs[tXdatItr] = cCurrFreqs[tXdatItr];
	--cCurrFreqs[tXdatItr];
	if (!cCurrFreqs[tXdatItr])
		++cExecValue;
	CatchError
}
#endif // CompLazy



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fvt>
void AllDiffXFeVt<pxt,fvt>::execIncr()
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
					++cExecValue;

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;

				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
					--cExecValue;
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
		this->mValueRec->updtCurr(this->mTermSys.ExecClk(), cExecValue);
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
						++cExecValue;

					//	add new value
					pxt const & tCurrX = mPxRecs[tPos]->CurrData();
					if (cExecXdats.insertBll(tCurrX, tXdatItr))
						cCurrFreqs[tXdatItr] = 0;
					sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
					cCurrPxItrs[tPos] = tXdatItr;

					if (!cCurrFreqs[tXdatItr])
						--cExecValue;
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
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(), cExecValue);
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
					--cExecValue;
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
					++cExecValue;

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;
				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
					--cExecValue;
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
					--cExecValue;

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
					++cExecValue;

				//	add new value
				pxt const & tCurrX = mPxRecs[tPos]->CurrData();
				if (cExecXdats.insertBll(tCurrX, tXdatItr))
					cCurrFreqs[tXdatItr] = 0;
				sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
				cCurrPxItrs[tPos] = tXdatItr;

				if (!cCurrFreqs[tXdatItr])
					--cExecValue;
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
		this->mValueRec->updtCurr(this->mTermSys.ExecClk(), cExecValue);
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
template <typename pxt, typename fvt>
void AllDiffXFeVt<pxt,fvt>::execBklg()
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
				--cExecValue;

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
				++cExecValue;

			//	add new value
			pxt const & tCurrX = mPxRecs[tPos]->CurrData();
			if (cExecXdats.insertBll(tCurrX, tXdatItr))
				cCurrFreqs[tXdatItr] = 0;
			sPrevPxItrs[tPos] = cCurrPxItrs[tPos];
			cCurrPxItrs[tPos] = tXdatItr;

			if (!cCurrFreqs[tXdatItr])
				--cExecValue;

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
	this->mValueRec->updtCurr(this->mTermSys.ExecClk(), cExecValue);
	this->runPostExecBklg();
	CatchError
}
#endif // CompLazy



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename fvt>
void AllDiffXFeVt<pxt,fvt>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		BuffType tSimulValue = cExecValue;
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
				if (!sNextFreqs[tNextItr]) ++tSimulValue;

				//	add next xdat
				pxt const & tNextX = mPxRecs[tPos]->NextBuff;
				if (sNextXdats.insertBll(tNextX, tNextItr))
				{
					Itr tCurrItr = cExecXdats.findItr(tNextX);
					if (tCurrItr == InvItr) sNextFreqs[tNextItr] = 0;
					else sNextFreqs[tNextItr] = cCurrFreqs[tCurrItr];
				}
				if (!sNextFreqs[tNextItr]) --tSimulValue;
				++sNextFreqs[tNextItr];
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
			cSimulValue = cExecValue;
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
				if (!cSimulFreqs[tSimulItr]) ++cSimulValue;
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
			BuffType tSimulValue = cSimulValue;
			#else
			BuffType tSimulValue = cExecValue;
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

				if (!sNextFreqs[tNextItr]) --tSimulValue;
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
					if (!sNextFreqs[tNextItr]) ++tSimulValue;

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
					if (!sNextFreqs[tNextItr]) --tSimulValue;
					++sNextFreqs[tNextItr];
				}
			}
			#endif //SimulFlexi
			this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fvt>::iof(tSimulValue));
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
				cSimulValue = cEmulValue;
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
					if (!cSimulFreqs[tSimulItr]) ++cSimulValue;
				}
				#endif //SimulFixed
			}
			else
			{
				cSimulValue = cExecValue;
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
						if (!cSimulFreqs[tSimulItr]) ++cSimulValue;
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
						if (!cSimulFreqs[tSimulItr]) --cSimulValue;
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
						if (!cSimulFreqs[tSimulItr]) ++cSimulValue;

						//	add late value
						pxt const & tLateX = mPxRecs[tPos]->LateBuff;
						if (cSimulXdats.insertBll(tLateX, tSimulItr))
						{
							Itr tCurrItr = cExecXdats.findItr(tLateX);
							if (tCurrItr == InvItr) cSimulFreqs[tSimulItr] = 0;
							else cSimulFreqs[tSimulItr] = cCurrFreqs[tCurrItr];
						}
						if (!cSimulFreqs[tSimulItr]) --cSimulValue;
						++cSimulFreqs[tSimulItr];
					}
				}
			}
		}

		sNextXdats.clear(this->mTermSys.SimulClk());
		BuffType tSimulValue = cSimulValue;

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
			if (!sNextFreqs[tNextItr]) --tSimulValue;
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
				tSimulValue += tPxRec->NextData(this->mTermSys.SimulClk()) -
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
				if (!sNextFreqs[tNextItr]) ++tSimulValue;

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
				if (!sNextFreqs[tNextItr]) --tSimulValue;
				++sNextFreqs[tNextItr];
			}
		}
		#endif
		this->mValueRec->updtNext(this->mTermSys.SimulClk(), tc<BuffType,fvt>::iof(tSimulValue));
	}
	#endif // CompLazy
	#endif//SimulDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in emulation mode.
*/
template <typename pxt, typename fvt>
void AllDiffXFeVt<pxt,fvt>::emulBklg()
{
	WatchError
	cEmulValue = cExecValue;
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
			if (!cEmulFreqs[tLateItr]) --cEmulValue;
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
			if (!cEmulFreqs[tLateItr]) ++cEmulValue;

			//	add late xdat
			pxt const & tLateX = mPxRecs[tPos]->LateBuff;
			if (cEmulXdats.insertBll(tLateX, tLateItr))
			{
				Itr tCurrItr = cExecXdats.findItr(tLateX);
				if (tCurrItr == InvItr) cEmulFreqs[tLateItr] = 0;
				else cEmulFreqs[tLateItr] = cCurrFreqs[tCurrItr];
			}
			if (!cEmulFreqs[tLateItr]) --cEmulValue;
			++cEmulFreqs[tLateItr];
		}
	}

	this->mValueRec->updtLate(this->mTermSys.EmulClk(), cEmulValue);
	CatchError
}
#endif // CompLazy



/*!
	Sync the exec clock.
*/
template <typename pxt, typename fvt>
void AllDiffXFeVt<pxt,fvt>::syncExecClk()
{
	WatchError
	cXdatItrs.syncClk();
	#if CompLazy
	cEmulXdats.syncClk();
	#endif
	AggFeVt<fvt>::syncExecClk();
	CatchError
}


/*!
	Sync the simul clock.
*/
template <typename pxt, typename fvt>
void AllDiffXFeVt<pxt,fvt>::syncSimulClk()
{
	WatchError
	sNextXdats.syncClk();
	AggFeVt<fvt>::syncSimulClk();
	CatchError
}


#if SimulDnwdCache
/*!
	Sync the simul cache clock.
*/
template <typename pxt, typename fvt>
void AllDiffXFeVt<pxt,fvt>::syncSimulCacheClk()
{
	WatchError
	cSimulXdats.syncClk();
	AggFeVt<fvt>::syncSimulCacheClk();
	CatchError
}
#endif//SimulDnwdCache

closeKangarooSpace


#endif//AllDiffXFeVt
