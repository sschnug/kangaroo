/*!
	@file baryxfevt.tcc
	@brief The prototype file for BaryXFeVt template class.
	@details This is the prototype file for BaryXFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef BaryXFeVtTccIncluded
#define BaryXFeVtTccIncluded


#include "cbls/funcs/fevs/segfevt.tcc"


openKangarooSpace



/*!
	@class BaryXFeVt
	@brief A template class to represent binary FeV terms.
	@details This template class represents binary FeV terms.
*/
template<typename op>
class BaryXFeVt : public SegFeVt<typename op::OutTyp>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys,
												Prm * thePrms);							//!< Definition.
		static Hdl def(Fss const theFss, Hdl const hdlSys,
												Prm const & Left, Prm const & Right);	//!< Definition.

		static BaryXFeVt<op> & refm(Hdl const hdlSys, Hdl const hdlFunc);				//!< Reference.
		static BaryXFeVt<op> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);				//!< Pointer.
		static BaryXFeVt<op> const & refc(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static BaryXFeVt<op> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.

		//! @name Casting
		//! @{

		static BaryXFeVt<op> const & cast(Term const & theTerm);		//!< Perform casting.
		static BaryXFeVt<op> const * cast(Term const * theTerm);		//!< Perform casting.
		static BaryXFeVt<op> & cast(Term & theTerm);					//!< Perform casting.
		static BaryXFeVt<op> * cast(Term * theTerm);					//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	private:

		BaryXFeVt(Fss const theFss, Hdl const hdlSys,
								Prm * thePrms, Dim const PrmCount);	//!< Constructor.
		BaryXFeVt const & operator = (BaryXFeVt<op> const & that);	//!< Assigner.
		BaryXFeVt(BaryXFeVt<op> const & that);						//!< Duplicator.
		~BaryXFeVt();												//!< Destructor.

		//! @name Computations
		//! @{

		virtual void compConst();	//!< Compute the term.
		virtual void execAnew();	//!< Execute the term.
		virtual void simulAnew();	//!< Simulate the term.
		virtual void execIncr();	//!< Execute the term.
		virtual void simulIncr();	//!< Simulate the term.
		#if CompLazy
		virtual void execBklg();	//!< Execute the term.
		virtual void emulBklg();	//!< Emulate the term.
		#endif

		//! @}

	private:

		EvalRec<typename op::InxTyp> const * mPxRecs[op::Arity];	//!< The parameter.
		#if SimulLazy
		Bll 					   			cSimulBklg;				//!< Simulation cache.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BaryXFeVt<op>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< BaryXFeVt<op> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BaryXFeVt<op>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< BaryXFeVt<op> >::TermCls;
	CatchError
}




/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BaryXFeVt<op>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< BaryXFeVt<op> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BaryXFeVt<op>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< BaryXFeVt<op> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BaryXFeVt<op> & BaryXFeVt<op>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< BaryXFeVt<op> >::TermCls, eWrongCls);

	return scast<BaryXFeVt<op> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BaryXFeVt<op> * BaryXFeVt<op>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub< BaryXFeVt<op> >::TermCls, eWrongCls);

	return scast<BaryXFeVt<op> *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BaryXFeVt<op> const & BaryXFeVt<op>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< BaryXFeVt<op> >::TermCls, eWrongCls);

	return scast<BaryXFeVt<op> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BaryXFeVt<op> const * BaryXFeVt<op>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eWrongCls);
	Warn(theTerm->TermCls != TermStub< BaryXFeVt<op> >::TermCls, eWrongCls);

	return scast<BaryXFeVt<op> const *>(theTerm);
	CatchError
}



/*!
	Refer to a binary FeV term.
*/
template<typename op>
inline BaryXFeVt<op> & BaryXFeVt<op>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a binary FeV term.
*/
template<typename op>
inline BaryXFeVt<op> * BaryXFeVt<op>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a binary FeV term.
*/
template<typename op>
inline BaryXFeVt<op> const & BaryXFeVt<op>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a binary FeV term.
*/
template<typename op>
inline BaryXFeVt<op> const * BaryXFeVt<op>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template<typename op>
inline BaryXFeVt<op>::~BaryXFeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	Define a binary FeV term.
*/
template<typename op>
inline Hdl BaryXFeVt<op>::def(Fss const theFss, Hdl const hdlSys,
			Prm const & Left, Prm const & Right)
{
	WatchError
	Prm tPrms[op::Arity] = { Left, Right };
	return def(theFss, hdlSys, tPrms);
	CatchError
}



/*!
	Define a binary FeV term.
*/
template<typename op>
Hdl BaryXFeVt<op>::def(Fss const theFss, Hdl const hdlSys, Prm * thePrms)
{
	WatchError
	Warn(op::Arity != 2, eParamCount1(2));

	BaryXFeVt<op> * tFeV = new BaryXFeVt<op>(theFss, hdlSys, thePrms, op::Arity);
	Hdl const tHdl = tFeV->defSysFunc();
	if (tHdl != InvHdl) { delete tFeV; return tHdl; }

	EvalTbl<typename op::OutTyp> & tOutTbl =
				EvalTbl<typename op::OutTyp>::refm(hdlSys);
	EvalTbl<typename op::InxTyp> const & tInxTbl =
				EvalTbl<typename op::InxTyp>::refc(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFeV->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFeV->mPrmSpecs;

	for(Pos tPos = 0; tPos < op::Arity; ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFeV->mPxRecs[tPos] = tInxTbl.ptrcEvalRec(tPxLoc);
	}

	tOutTbl.setEvalRec(tFeV->mValueRec, tFeV->mValueLoc);

	tFeV->performCompConst();
	tFeV->defSysRoot();
	return tFeV->TermHdl;
	CatchError
}




/*!
	The constructor.
*/
template<typename op>
BaryXFeVt<op>::BaryXFeVt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) :
		SegFeVt<typename op::OutTyp>(hdlSys, PrmCount)
{
	WatchError
	this->setTermCls(TermStub< BaryXFeVt<op> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, op::Order);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template<typename op>
BaryXFeVt<op>::BaryXFeVt(BaryXFeVt<op> const & that) :
		SegFeVt<typename op::OutTyp>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename op>
BaryXFeVt<op> const & BaryXFeVt<op>::operator = (BaryXFeVt<op> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template<typename op>
void BaryXFeVt<op>::compConst()
{
	WatchError
	if (this->updatable())
		this->setUpdatable(op::chk(this->mPrmTerms[0]->updatable(),
			this->mPrmTerms[1]->updatable(), mPxRecs[0]->CurrData(),
			mPxRecs[1]->CurrData()));
	if (!this->updatable())
		this->mValueRec->finalise(op::iof(mPxRecs[0]->CurrData(),
				mPxRecs[1]->CurrData()));
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename op>
void BaryXFeVt<op>::execAnew()
{
	WatchError
	#if ExecDnwd
	Term::performExecAnew(this->mPrmTerms[0]);
	Term::performExecAnew(this->mPrmTerms[1]);
	#endif
	this->mValueRec->initCurr(op::iof(mPxRecs[0]->CurrData(),
				mPxRecs[1]->CurrData()));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template<typename op>
void BaryXFeVt<op>::simulAnew()
{
	WatchError
	#if SimulDnwd
	Term::performSimulAnew(this->mPrmTerms[0]);
	Term::performSimulAnew(this->mPrmTerms[1]);
	#endif
	this->mValueRec->updtNext(this->mTermSys.SimulClk(),
		op::iof(mPxRecs[0]->NextData(this->mTermSys.SimulClk()),
					mPxRecs[1]->NextData(this->mTermSys.SimulClk())));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename op>
void BaryXFeVt<op>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		if ((this->mExecChgdPrms.tagged(0) &&
				mPxRecs[0]->PrevDiff(this->mTermSys.ExecClk())) ||
			(this->mExecChgdPrms.tagged(1) &&
				mPxRecs[1]->PrevDiff(this->mTermSys.ExecClk())))
		this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
			op::iof(mPxRecs[0]->CurrData(), mPxRecs[1]->CurrData()));

		this->runPostExecIncr();
	}
	#endif
	#if ExecDnwd
	Bll tNeedRecomp = false;
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//	CompLazy
		if (this->needExecCandComp()) this->listCandParams();
		for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkCandPrms->item(tIdx);
			Term::performExecIncr(this->mPrmTerms[tPos]);
			if (tNeedRecomp) continue;
			if (mPxRecs[tPos]->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
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

			if (tNeedRecomp) continue;
			if (this->mEvalUndonePrms->tagged(tPos) ||
					mPxRecs[tPos]->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;
			Term::performExecBklg(this->mPrmTerms[tPos]);
			if (tNeedRecomp) continue;
			if (this->mEvalUndonePrms->tagged(tPos) ||
					mPxRecs[tPos]->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
	}
	#endif	//CompLazy
	if (tNeedRecomp)
		this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
			op::iof(mPxRecs[0]->CurrData(), mPxRecs[1]->CurrData()));
	#if CompLazy
	this->runPostExecIncr();
	#endif //CompLazy
	#endif 	//ExecDnwd
	CatchError
}


#if CompLazy
/*!
	Compute the term in execution mode.
*/
template<typename op>
void BaryXFeVt<op>::execBklg()
{
	WatchError
	Bll tNeedRecomp = false;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performExecBklg(this->mPrmTerms[tPos]);
		if (tNeedRecomp) continue;
		if (this->mEvalUndonePrms->tagged(tPos) ||
				mPxRecs[tPos]->PrevDiff(this->mTermSys.ExecClk()))
			tNeedRecomp = true;
	}
	if (tNeedRecomp)
		this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
			op::iof(mPxRecs[0]->CurrData(), mPxRecs[1]->CurrData()));
	this->runPostExecBklg();
	CatchError
}
#endif //CompLazy



/*!
	Compute the term in simulation mode.
*/
template<typename op>
void BaryXFeVt<op>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		if ((this->mSimulChgdPrms.tagged(0) &&
					mPxRecs[0]->NextDiff(this->mTermSys.SimulClk())) ||
				(this->mSimulChgdPrms.tagged(1) &&
					mPxRecs[1]->NextDiff(this->mTermSys.SimulClk())))
			this->mValueRec->updtNext(this->mTermSys.SimulClk(),
				op::iof(mPxRecs[0]->NextData(this->mTermSys.SimulClk()),
						mPxRecs[1]->NextData(this->mTermSys.SimulClk())));
		this->runPostSimulIncr();
	}
	#endif
	#if SimulDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif
		Bll tNeedRecomp = false;
		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->listFlexiParams();
		#endif
		#if SimulFixedFlexi
		if (this->needSimulFixedComp())
			this->enumFixedParams(this->mBlkFlexiPrms->itemCount());
		#endif
		#if SimulFixedOnly
		if (this->needSimulFixedComp())
			this->listFixedParams();
		#endif
		#if SimulFixed
		for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFixedPrms->item(tIdx);
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			if (!tNeedRecomp && mPxRecs[tPos]->NextDiff(this->mTermSys.SimulClk()))
				tNeedRecomp = true;
		}
		#endif //SimulFixed

		#if SimulFlexi
		for(Idx tIdx = 0; tIdx < this->mBlkFlexiPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFlexiPrms->item(tIdx);
			#if SimulFixed
			if (this->mLblFixedPrms.tagged(tPos)) continue;
			#endif
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			if (!tNeedRecomp && mPxRecs[tPos]->NextDiff(this->mTermSys.SimulClk()))
				tNeedRecomp = true;
		}
		#endif//SimulFlexi

		if (tNeedRecomp)
			this->mValueRec->updtNext(this->mTermSys.SimulClk(),
				op::iof(mPxRecs[0]->NextData(this->mTermSys.SimulClk()),
							mPxRecs[1]->NextData(this->mTermSys.SimulClk())));
	#if CompLazy
	}
	else
	{
		Bll tNeedRecomp[op::Arity] = { false, false };
		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->listFlexiParams();
		#endif
		#if SimulFixed
		if (this->needSimulFixedComp()) this->markFixedParams();
		#endif
		#if SimulFixed
		for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFixedPrms->item(tIdx);
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			if (this->mEvalUndonePrms->tagged(tPos) ||
					mPxRecs[tPos]->NextDiff(this->mTermSys.SimulClk()))
				tNeedRecomp[tPos] = true;
		}
		#endif//SimulFixed

		if (this->needSimulCacheComp())
		{
			cSimulBklg = false;
			for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
			{
				Pos const tPos = this->mBacklogPrms.serial(tIdx);
				#if SimulFixed
				if (this->mLblFixedPrms.tagged(tPos)) continue;
				#endif
				Term::performEmulBklg(this->mPrmTerms[tPos]);
				if (!cSimulBklg && (this->mEvalUndonePrms->tagged(tPos) ||
						mPxRecs[tPos]->LateDiff(this->mTermSys.EmulClk())))
					cSimulBklg = true;
			}
		}
		#if SimulFlexi
		for(Idx tIdx = 0; tIdx < this->mBlkFlexiPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFlexiPrms->item(tIdx);
			#if SimulFixed
			if (this->mLblFixedPrms.tagged(tPos)) continue;
			#endif
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			if (this->mEvalUndonePrms->tagged(tPos) ||
					mPxRecs[tPos]->NextDiff(this->mTermSys.SimulClk()))
				tNeedRecomp[tPos] = true;
		}
		#endif

		if (tNeedRecomp[0] || tNeedRecomp[1] || cSimulBklg)
			this->mValueRec->updtNext(this->mTermSys.SimulClk(),
				op::iof((tNeedRecomp[0] ? mPxRecs[0]->NextData(this->mTermSys.SimulClk()) :
											mPxRecs[0]->LateData(this->mTermSys.EmulClk())),
							(tNeedRecomp[1] ? mPxRecs[1]->NextData(this->mTermSys.SimulClk()) :
											mPxRecs[1]->LateData(this->mTermSys.EmulClk()))));
	}
	#endif	//	CompLazy
	#endif	//	SimulDnwd
	CatchError
}


#if CompLazy
/*!
	Compute the term in simulation mode.
*/
template<typename op>
void BaryXFeVt<op>::emulBklg()
{
	WatchError
	Bll tNeedRecomp = false;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		if (this->mEvalUndonePrms->tagged(tPos) ||
				mPxRecs[tPos]->LateDiff(this->mTermSys.EmulClk()))
			tNeedRecomp = true;
	}
	if (tNeedRecomp)
		this->mValueRec->updtLate(this->mTermSys.EmulClk(),
			op::iof(mPxRecs[0]->LateData(this->mTermSys.EmulClk()),
				mPxRecs[1]->LateData(this->mTermSys.EmulClk())));
	CatchError
}
#endif //CompLazy


closeKangarooSpace


#endif//BaryXFeVtTccIncluded
