/*!
	@file baryxyfcmt.tcc
	@brief The prototype file for BaryXYFcMt template class.
	@details This is the prototype file for BaryXYFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef BaryXYFcMtTccIncluded
#define BaryXYFcMtTccIncluded


#include "cbls/funcs/fcms/segfcmt.tcc"


openKangarooSpace



/*!
	@class BaryXYFcMt
	@brief A template class to represent heterogenous binary FcM terms.
	@details This template class represents heterogenous binary FcM terms.
*/
template<typename op>
class BaryXYFcMt : public SegFcMt<typename op::OutTyp>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys,
												Prm * thePrms);							//!< Definition.
		static Hdl def(Fss const theFss, Hdl const hdlSys,
												Prm const & Left, Prm const & Right);	//!< Definition.

		static BaryXYFcMt<op> & refm(Hdl const hdlSys, Hdl const hdlFunc);				//!< Reference.
		static BaryXYFcMt<op> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);				//!< Pointer.
		static BaryXYFcMt<op> const & refc(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static BaryXYFcMt<op> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.

		//! @name Casting
		//! @{

		static BaryXYFcMt<op> const & cast(Term const & theTerm);		//!< Perform casting.
		static BaryXYFcMt<op> const * cast(Term const * theTerm);		//!< Perform casting.
		static BaryXYFcMt<op> & cast(Term & theTerm);					//!< Perform casting.
		static BaryXYFcMt<op> * cast(Term * theTerm);					//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	private:

		BaryXYFcMt(Fss const theFss, Hdl const hdlSys,
								Prm * thePrms, Dim const PrmCount);	//!< Constructor.
		BaryXYFcMt const & operator = (BaryXYFcMt<op> const & that);//!< Assigner.
		BaryXYFcMt(BaryXYFcMt<op> const & that);					//!< Duplicator.
		~BaryXYFcMt();												//!< Destructor.

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

		EvalRec<typename op::InxTyp> const * mPxRec;			//!< The parameter.
		EvalRec<typename op::InyTyp> const * mPyRec;			//!< The parameter.
		#if SimulLazy
		Bll 					   			cSimulBklg;			//!< Simulation cache.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BaryXYFcMt<op>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< BaryXYFcMt<op> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BaryXYFcMt<op>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< BaryXYFcMt<op> >::TermCls;
	CatchError
}




/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BaryXYFcMt<op>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< BaryXYFcMt<op> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BaryXYFcMt<op>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< BaryXYFcMt<op> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BaryXYFcMt<op> & BaryXYFcMt<op>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< BaryXYFcMt<op> >::TermCls, eWrongCls);

	return scast<BaryXYFcMt<op> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BaryXYFcMt<op> * BaryXYFcMt<op>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub< BaryXYFcMt<op> >::TermCls, eWrongCls);

	return scast<BaryXYFcMt<op> *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BaryXYFcMt<op> const & BaryXYFcMt<op>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< BaryXYFcMt<op> >::TermCls, eWrongCls);

	return scast<BaryXYFcMt<op> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BaryXYFcMt<op> const * BaryXYFcMt<op>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eWrongCls);
	Warn(theTerm->TermCls != TermStub< BaryXYFcMt<op> >::TermCls, eWrongCls);

	return scast<BaryXYFcMt<op> const *>(theTerm);
	CatchError
}



/*!
	Refer to a binary FcM term.
*/
template<typename op>
inline BaryXYFcMt<op> & BaryXYFcMt<op>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a binary FcM term.
*/
template<typename op>
inline BaryXYFcMt<op> * BaryXYFcMt<op>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a binary FcM term.
*/
template<typename op>
inline BaryXYFcMt<op> const & BaryXYFcMt<op>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a binary FcM term.
*/
template<typename op>
inline BaryXYFcMt<op> const * BaryXYFcMt<op>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template<typename op>
inline BaryXYFcMt<op>::~BaryXYFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	Define a binary FcM term.
*/
template<typename op>
inline Hdl BaryXYFcMt<op>::def(Fss const theFss, Hdl const hdlSys,
			Prm const & Left, Prm const & Right)
{
	WatchError
	Prm tPrms[op::Arity] = { Left, Right };
	return def(theFss, hdlSys, tPrms);
	CatchError
}



/*!
	Define a binary FcM term.
*/
template<typename op>
Hdl BaryXYFcMt<op>::def(Fss const theFss, Hdl const hdlSys, Prm * thePrms)
{
	WatchError
	Warn(op::Arity != 2, eParamCount1(2));

	BaryXYFcMt<op> * tFcM = new BaryXYFcMt<op>(theFss, hdlSys, thePrms, op::Arity);
	Hdl const tHdl = tFcM->defSysFunc();
	if (tHdl != InvHdl) { delete tFcM; return tHdl; }

	EvalTbl<typename op::OutTyp> & tOutTbl =
				EvalTbl<typename op::OutTyp>::refm(hdlSys);
	EvalTbl<typename op::InxTyp> const & tInxTbl =
				EvalTbl<typename op::InxTyp>::refc(hdlSys);
	EvalTbl<typename op::InyTyp> const & tInyTbl =
				EvalTbl<typename op::InyTyp>::refc(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFcM->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFcM->mPrmSpecs;

	Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[0],tPrmSpecs[0]);
	tFcM->mPxRec = tInxTbl.ptrcEvalRec(tPxLoc);

	Loc const tPyLoc = getPxLoc(theFss, tPrmTerms[1],tPrmSpecs[1]);
	tFcM->mPyRec = tInyTbl.ptrcEvalRec(tPyLoc);

	tOutTbl.setEvalRec(tFcM->mMetricRec, tFcM->mMetricLoc);

	tFcM->performCompConst();
	tFcM->defSysRoot();
	return tFcM->TermHdl;
	CatchError
}




/*!
	The constructor.
*/
template<typename op>
BaryXYFcMt<op>::BaryXYFcMt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) :
		SegFcMt<typename op::OutTyp>(hdlSys, PrmCount)
{
	WatchError
	this->setTermCls(TermStub< BaryXYFcMt<op> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Ordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template<typename op>
BaryXYFcMt<op>::BaryXYFcMt(BaryXYFcMt<op> const & that) :
		SegFcMt<typename op::OutTyp>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename op>
BaryXYFcMt<op> const & BaryXYFcMt<op>::operator = (BaryXYFcMt<op> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template<typename op>
void BaryXYFcMt<op>::compConst()
{
	WatchError
	if (this->updatable())
		this->setUpdatable(op::chk(this->mPrmTerms[0]->updatable(),
			this->mPrmTerms[1]->updatable(), mPxRec->CurrData(),
			mPyRec->CurrData()));
	if (!this->updatable())
		this->mMetricRec->finalise(op::iof(mPxRec->CurrData(),
				mPyRec->CurrData()));
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename op>
void BaryXYFcMt<op>::execAnew()
{
	WatchError
	#if ExecDnwd
	Term::performExecAnew(this->mPrmTerms[0]);
	Term::performExecAnew(this->mPrmTerms[1]);
	#endif
	this->mMetricRec->initCurr(op::iof(mPxRec->CurrData(),
				mPyRec->CurrData()));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template<typename op>
void BaryXYFcMt<op>::simulAnew()
{
	WatchError
	#if SimulDnwd
	Term::performSimulAnew(this->mPrmTerms[0]);
	Term::performSimulAnew(this->mPrmTerms[1]);
	#endif
	this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
		op::iof(mPxRec->NextData(this->mTermSys.SimulClk()),
					mPyRec->NextData(this->mTermSys.SimulClk())));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename op>
void BaryXYFcMt<op>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		if ((this->mExecChgdPrms.tagged(0) &&
				mPxRec->PrevDiff(this->mTermSys.ExecClk())) ||
			(this->mExecChgdPrms.tagged(1) &&
				mPyRec->PrevDiff(this->mTermSys.ExecClk())))
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
			op::iof(mPxRec->CurrData(), mPyRec->CurrData()));

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
			if (tPos ?
					mPyRec->PrevDiff(this->mTermSys.ExecClk()) :
					mPxRec->PrevDiff(this->mTermSys.ExecClk()))
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
			if (this->mEvalUndonePrms->tagged(tPos))
				tNeedRecomp = true;
			else if (tPos ?
					mPyRec->PrevDiff(this->mTermSys.ExecClk()) :
					mPxRec->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;
			Term::performExecBklg(this->mPrmTerms[tPos]);
			if (tNeedRecomp) continue;
			if (this->mEvalUndonePrms->tagged(tPos))
				tNeedRecomp = true;
			else if (tPos ?
					mPyRec->PrevDiff(this->mTermSys.ExecClk()) :
					mPxRec->PrevDiff(this->mTermSys.ExecClk()))
				tNeedRecomp = true;
		}
	}
	#endif	//CompLazy
	if (tNeedRecomp)
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
			op::iof(mPxRec->CurrData(), mPyRec->CurrData()));
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
void BaryXYFcMt<op>::execBklg()
{
	WatchError
	Bll tNeedRecomp = false;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performExecBklg(this->mPrmTerms[tPos]);
		if (tNeedRecomp) continue;
		if (this->mEvalUndonePrms->tagged(tPos))
			tNeedRecomp = true;
		else if (tPos ?
				mPyRec->PrevDiff(this->mTermSys.ExecClk()) :
				mPxRec->PrevDiff(this->mTermSys.ExecClk()))
			tNeedRecomp = true;
	}
	if (tNeedRecomp)
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
			op::iof(mPxRec->CurrData(), mPyRec->CurrData()));
	this->runPostExecBklg();
	CatchError
}
#endif //CompLazy



/*!
	Compute the term in simulation mode.
*/
template<typename op>
void BaryXYFcMt<op>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		if ((this->mSimulChgdPrms.tagged(0) &&
					mPxRec->NextDiff(this->mTermSys.SimulClk())) ||
				(this->mSimulChgdPrms.tagged(1) &&
					mPyRec->NextDiff(this->mTermSys.SimulClk())))
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
				op::iof(mPxRec->NextData(this->mTermSys.SimulClk()),
						mPyRec->NextData(this->mTermSys.SimulClk())));
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
			if (tNeedRecomp) continue;
			if (tPos ?
					mPyRec->NextDiff(this->mTermSys.SimulClk()) :
					mPxRec->NextDiff(this->mTermSys.SimulClk()))
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
			if (tNeedRecomp) continue;
			if (tPos ?
					mPyRec->NextDiff(this->mTermSys.SimulClk()) :
					mPxRec->NextDiff(this->mTermSys.SimulClk()))
				tNeedRecomp = true;
		}
		#endif//SimulFlexi

		if (tNeedRecomp)
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
				op::iof(mPxRec->NextData(this->mTermSys.SimulClk()),
							mPyRec->NextData(this->mTermSys.SimulClk())));
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
			if (this->mEvalUndonePrms->tagged(tPos))
				tNeedRecomp[tPos] = true;
			else if (tPos ?
					mPyRec->NextDiff(this->mTermSys.SimulClk()) :
					mPxRec->NextDiff(this->mTermSys.SimulClk()))
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
				if (cSimulBklg) continue;
				if (this->mEvalUndonePrms->tagged(tPos))
					cSimulBklg = true;
				else if (tPos ?
						mPyRec->LateDiff(this->mTermSys.EmulClk()) :
						mPxRec->LateDiff(this->mTermSys.EmulClk()))
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
			if (this->mEvalUndonePrms->tagged(tPos))
				tNeedRecomp[tPos] = true;
			else if (tPos ?
					mPyRec->NextDiff(this->mTermSys.SimulClk()) :
					mPxRec->NextDiff(this->mTermSys.SimulClk()))
				tNeedRecomp[tPos] = true;
		}
		#endif

		if (tNeedRecomp[0] || tNeedRecomp[1] || cSimulBklg)
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
				op::iof((tNeedRecomp[0] ? mPxRec->NextData(this->mTermSys.SimulClk()) :
											mPxRec->LateData(this->mTermSys.EmulClk())),
							(tNeedRecomp[1] ? mPyRec->NextData(this->mTermSys.SimulClk()) :
											mPyRec->LateData(this->mTermSys.EmulClk()))));
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
void BaryXYFcMt<op>::emulBklg()
{
	WatchError
	Bll tNeedRecomp = false;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		if (this->mEvalUndonePrms->tagged(tPos))
			tNeedRecomp = true;
		else if (tPos ?
				mPyRec->LateDiff(this->mTermSys.EmulClk()) :
				mPxRec->LateDiff(this->mTermSys.EmulClk()))
			tNeedRecomp = true;
	}
	if (tNeedRecomp)
		this->mMetricRec->updtLate(this->mTermSys.EmulClk(),
			op::iof(mPxRec->LateData(this->mTermSys.EmulClk()),
				mPyRec->LateData(this->mTermSys.EmulClk())));
	CatchError
}
#endif //CompLazy


closeKangarooSpace


#endif//BaryXYFcMtTccIncluded
