/*!
	@file uaryxfevt.tcc
	@brief The prototype file for UaryXFeVt template class.
	@details This is the prototype file for UaryXFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef UaryXFeVtTccIncluded
#define UaryXFeVtTccIncluded


#include "cbls/funcs/fevs/segfevt.tcc"


openKangarooSpace



/*!
	@class UaryXFeVt
	@brief A template class to represent unary FeVs.
	@details This class represents unary FeVs.
*/
template<typename op>
class UaryXFeVt : public SegFeVt<typename op::OutTyp>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys, Prm const & Param);			//!< Definition.

		static UaryXFeVt<op> & refm(Hdl const hdlSys, Hdl const hdlFunc);				//!< Reference.
		static UaryXFeVt<op> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);				//!< Pointer.
		static UaryXFeVt<op> const & refc(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static UaryXFeVt<op> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.

		//! @name Casting
		//! @{

		static UaryXFeVt<op> const & cast(Term const & theTerm);		//!< Perform casting.
		static UaryXFeVt<op> const * cast(Term const * theTerm);		//!< Perform casting.
		static UaryXFeVt<op> & cast(Term & theTerm);					//!< Perform casting.
		static UaryXFeVt<op> * cast(Term * theTerm);					//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	private:

		UaryXFeVt(Fss const theFss, Hdl const hdlSys,
								Prm * thePrms, Dim const PrmCount);		//!< Constructor.
		UaryXFeVt const & operator = (UaryXFeVt<op> const & that);		//!< Assigner.
		UaryXFeVt(UaryXFeVt<op> const & that);							//!< Duplicator.
		~UaryXFeVt();													//!< Destructor.

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

		EvalRec<typename op::InxTyp> const * mPxRec;		//!< The parameter.
		#if SimulLazy
		Bll 					   			cSimulBklg;		//!< Simulation cache.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll UaryXFeVt<op>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< UaryXFeVt<op> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll UaryXFeVt<op>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< UaryXFeVt<op> >::TermCls;
	CatchError
}




/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll UaryXFeVt<op>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< UaryXFeVt<op> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll UaryXFeVt<op>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< UaryXFeVt<op> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline UaryXFeVt<op> & UaryXFeVt<op>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< UaryXFeVt<op> >::TermCls, eWrongCls);

	return scast<UaryXFeVt<op> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline UaryXFeVt<op> * UaryXFeVt<op>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub< UaryXFeVt<op> >::TermCls, eWrongCls);

	return scast<UaryXFeVt<op> *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline UaryXFeVt<op> const & UaryXFeVt<op>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< UaryXFeVt<op> >::TermCls, eWrongCls);

	return scast<UaryXFeVt<op> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline UaryXFeVt<op> const * UaryXFeVt<op>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub< UaryXFeVt<op> >::TermCls, eWrongCls);

	return scast<UaryXFeVt<op> const *>(theTerm);
	CatchError
}



/*!
	Refer to a unary FeV term.
*/
template<typename op>
inline UaryXFeVt<op> & UaryXFeVt<op>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a unary FeV term.
*/
template<typename op>
inline UaryXFeVt<op> * UaryXFeVt<op>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a unary FeV term.
*/
template<typename op>
inline UaryXFeVt<op> const & UaryXFeVt<op>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a unary FeV term.
*/
template<typename op>
inline UaryXFeVt<op> const * UaryXFeVt<op>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template<typename op>
inline UaryXFeVt<op>::~UaryXFeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	Define a ory for a unary FeV.
*/
template<typename op>
Hdl UaryXFeVt<op>::def(Fss const theFss, Hdl const hdlSys, Prm const & Param)
{
	WatchError
	Warn(op::Arity != 1, eParamCount1(1));

	Prm tPrms[op::Arity] = { Param };
	UaryXFeVt<op> * tFeV = new UaryXFeVt<op>(theFss, hdlSys, tPrms, op::Arity);
	Hdl const tHdl = tFeV->defSysFunc();
	if (tHdl != InvHdl) { delete tFeV; return tHdl; }

	EvalTbl<typename op::OutTyp> & tOutTbl =
				EvalTbl<typename op::OutTyp>::refm(hdlSys);
	EvalTbl<typename op::InxTyp> const & tInxTbl =
				EvalTbl<typename op::InxTyp>::refc(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFeV->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFeV->mPrmSpecs;

	Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[0],tPrmSpecs[0]);
	tFeV->mPxRec = tInxTbl.ptrcEvalRec(tPxLoc);

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
UaryXFeVt<op>::UaryXFeVt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) :
		SegFeVt<typename op::OutTyp>(hdlSys, PrmCount)
{
	WatchError
	this->setTermCls(TermStub< UaryXFeVt<op> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, op::Order);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template<typename op>
UaryXFeVt<op>::UaryXFeVt(UaryXFeVt<op> const & that) :
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
UaryXFeVt<op> const & UaryXFeVt<op>::operator = (UaryXFeVt<op> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template<typename op>
void UaryXFeVt<op>::compConst()
{
	WatchError
	if (this->updatable())
		this->setUpdatable(op::chk(this->mPrmTerms[0]->updatable(),
				mPxRec->CurrData()));

	if (!this->updatable())
		this->mValueRec->finalise(op::iof(mPxRec->CurrData()));
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename op>
void UaryXFeVt<op>::execAnew()
{
	WatchError
	#if ExecDnwd
	Term::performExecAnew(this->mPrmTerms[0]);
	#endif
	this->mValueRec->initCurr(op::iof(mPxRec->CurrData()));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template<typename op>
void UaryXFeVt<op>::simulAnew()
{
	WatchError
	#if SimulDnwd
	Term::performSimulAnew(this->mPrmTerms[0]);
	#endif
	this->mValueRec->updtNext(this->mTermSys.SimulClk(),
		op::iof(mPxRec->NextData(this->mTermSys.SimulClk())));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename op>
void UaryXFeVt<op>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		if (mPxRec->PrevDiff(this->mTermSys.ExecClk()))
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
				op::iof(mPxRec->CurrData()));
		this->runPostExecIncr();
	}
	#endif
	#if ExecDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//	CompLazy
		if (this->needExecCandComp()) this->listCandParams();
		if (this->mBlkCandPrms->itemCount())
		{
			Term::performExecIncr(this->mPrmTerms[0]);
			if (mPxRec->PrevDiff(this->mTermSys.ExecClk()))
				this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
					op::iof(mPxRec->CurrData()));
		}
	#if CompLazy
	}
	else	//	backlog
	{
		if (this->needExecCandComp()) this->listCandParams();
		if (this->mBlkCandPrms->itemCount())
		{
			Term::performExecIncr(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->PrevDiff(this->mTermSys.ExecClk()))
				this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
					op::iof(mPxRec->CurrData()));
		}
		else if (this->mBacklogPrms.tagCount())
		{
			Term::performExecBklg(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->PrevDiff(this->mTermSys.ExecClk()))
				this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
					op::iof(mPxRec->CurrData()));
		}
	}
	this->runPostExecIncr();
	#endif	//CompLazy
	#endif 	//ExecDnwd
	CatchError
}


#if CompLazy
/*!
	Compute the term in execution mode.
*/
template<typename op>
void UaryXFeVt<op>::execBklg()
{
	WatchError
	Term::performExecBklg(this->mPrmTerms[0]);
	if (this->mEvalUndonePrms->tagged(0) ||
			mPxRec->PrevDiff(this->mTermSys.ExecClk()))
		this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
				op::iof(mPxRec->CurrData()));
	this->runPostExecBklg();
	CatchError
}
#endif //CompLazy



/*!
	Compute the term in simulation mode.
*/
template<typename op>
void UaryXFeVt<op>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		if (mPxRec->NextDiff(this->mTermSys.SimulClk()))
			this->mValueRec->updtNext(this->mTermSys.SimulClk(),
				op::iof(mPxRec->NextData(this->mTermSys.SimulClk())));
		this->runPostSimulIncr();
	}
	#endif
	#if SimulDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif
		#if SimulFixed
		if (this->needSimulFixedComp())	this->listFixedParams();

		if (this->mBlkFixedPrms->itemCount())
		{
			Term::performSimulIncr(this->mPrmTerms[0]);
			if (mPxRec->NextDiff(this->mTermSys.SimulClk()))
				this->mValueRec->updtNext(this->mTermSys.SimulClk(),
					op::iof(mPxRec->NextData(this->mTermSys.SimulClk())));
			return;
		}
		#endif

		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->listFlexiParams();

		if(this->mBlkFlexiPrms->itemCount())
		{
			Term::performSimulIncr(this->mPrmTerms[0]);
			if (mPxRec->NextDiff(this->mTermSys.SimulClk()))
				this->mValueRec->updtNext(this->mTermSys.SimulClk(),
					op::iof(mPxRec->NextData(this->mTermSys.SimulClk())));
		}
		#endif
	#if CompLazy
	}
	else
	{
		#if SimulFixed
		if (this->needSimulFixedComp()) this->listFixedParams();
		if(this->mBlkFixedPrms->itemCount())
		{
			Term::performSimulIncr(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->NextDiff(this->mTermSys.SimulClk()))
				this->mValueRec->updtNext(this->mTermSys.SimulClk(),
					op::iof(mPxRec->NextData(this->mTermSys.SimulClk())));
			return;
		}
		#endif	//SimulFixed

		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->listFlexiParams();
		if (this->mBlkFlexiPrms->itemCount())
		{
			Term::performSimulIncr(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->NextDiff(this->mTermSys.SimulClk()))
				this->mValueRec->updtNext(this->mTermSys.SimulClk(),
					op::iof(mPxRec->NextData(this->mTermSys.SimulClk())));
			return;
		}
		#endif	//SimulFlexi

		if (this->needSimulCacheComp())
		{
			Term::performEmulBklg(this->mPrmTerms[0]);
			cSimulBklg = (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->LateDiff(this->mTermSys.EmulClk()));
		}

		if (cSimulBklg)
			this->mValueRec->updtNext(this->mTermSys.SimulClk(),
				op::iof(mPxRec->LateData(this->mTermSys.EmulClk())));
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
void UaryXFeVt<op>::emulBklg()
{
	WatchError
	Term::performEmulBklg(this->mPrmTerms[0]);
	if (this->mEvalUndonePrms->tagged(0) ||
			mPxRec->LateDiff(this->mTermSys.EmulClk()))
		this->mValueRec->updtLate(this->mTermSys.EmulClk(),
			op::iof(mPxRec->LateData(this->mTermSys.EmulClk())));
	CatchError
}
#endif //CompLazy


closeKangarooSpace


#endif //UaryXFeVtTccIncluded
