/*!
	@file bindxfevt.tcc
	@brief The prototype file for BindXFeVt template class.
	@details This is the prototype file for BindXFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef BindXFeVtTccIncluded
#define BindXFeVtTccIncluded


#include "cbls/funcs/fevs/segfevt.tcc"


openKangarooSpace



/*!
	@class BindXFeVt
	@brief A template class to represent bounded operator FeVs.
	@details This template class represents bounded operator FeVs.
*/
template<typename op>
class BindXFeVt : public SegFeVt<typename op::OutTyp>
{
	public:
		typedef op bind;	//!< Function class to bind operand values.

		static Hdl def(Fss const theFss, Hdl const hdlSys,
										Prm const & Param, bind const & theBind);	//!< Definiton.

		static BindXFeVt<op> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static BindXFeVt<op> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static BindXFeVt<op> const & refc(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static BindXFeVt<op> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.

		//! @name Casting
		//! @{

		static BindXFeVt<op> const & cast(Term const & theTerm);	//!< Perform casting.
		static BindXFeVt<op> const * cast(Term const * theTerm);	//!< Perform casting.
		static BindXFeVt<op> & cast(Term & theTerm);				//!< Perform casting.
		static BindXFeVt<op> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	private:

		BindXFeVt(Fss const theFss, Hdl const hdlSys, Prm * thePrms,
								Dim const PrmCount, bind const & theBind);	//!< Constructor.
		BindXFeVt const & operator = (BindXFeVt<op> const & that);			//!< Assigner.
		BindXFeVt(BindXFeVt<op> const & that);								//!< Duplicator.
		~BindXFeVt();														//!< Destructor.

		//! @name Identity
		//! @{

		Hvl calcTermHvl() const;				 				//!< Calculate term hash value.
		virtual Bll equate(Term const & theTerm) const; 		//!< Compare terms for equality.

		//! @}

		//! @name Computations
		//! @{

		virtual void compConst();									//!< Compute the term.
		virtual void execAnew();									//!< Execute the term.
		virtual void simulAnew();									//!< Simulate the term.
		virtual void execIncr();									//!< Execute the term.
		virtual void simulIncr();									//!< Simulate the term.
		#if CompLazy
		virtual void execBklg();									//!< Execute the term.
		virtual void emulBklg();									//!< Emulate the term.
		#endif

		//! @}

	private:

		EvalRec<typename op::InxTyp> const * mPxRec;			//!< The parameter.
		bind const 							mBind;			//!< The bind.
		#if SimulLazy
		Bll 					   			cSimulBklg;		//!< Simulation cache.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BindXFeVt<op>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< BindXFeVt<op> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BindXFeVt<op>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< BindXFeVt<op> >::TermCls;
	CatchError
}




/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BindXFeVt<op>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< BindXFeVt<op> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BindXFeVt<op>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< BindXFeVt<op> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BindXFeVt<op> & BindXFeVt<op>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< BindXFeVt<op> >::TermCls, eWrongCls);

	return scast<BindXFeVt<op> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BindXFeVt<op> * BindXFeVt<op>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub< BindXFeVt<op> >::TermCls, eWrongCls);

	return scast<BindXFeVt<op> *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BindXFeVt<op> const & BindXFeVt<op>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< BindXFeVt<op> >::TermCls, eWrongCls);

	return scast<BindXFeVt<op> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BindXFeVt<op> const * BindXFeVt<op>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub< BindXFeVt<op> >::TermCls, eWrongCls);

	return scast<BindXFeVt<op> const *>(theTerm);
	CatchError
}



/*!
	Refer to a bind FeV term.
*/
template<typename op>
inline BindXFeVt<op> & BindXFeVt<op>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a bind FeV term.
*/
template<typename op>
inline BindXFeVt<op> * BindXFeVt<op>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a bind FeV term.
*/
template<typename op>
inline BindXFeVt<op> const & BindXFeVt<op>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a bind FeV term.
*/
template<typename op>
inline BindXFeVt<op> const * BindXFeVt<op>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template<typename op>
inline BindXFeVt<op>::~BindXFeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Define a unary2 FeV.
*/
template<typename op>
Hdl BindXFeVt<op>::def(Fss const theFss, Hdl const hdlSys,
								Prm const & theParam, bind const & theBind)
{
	WatchError
	Warn(op::Arity != 1, eParamCount1(1));

	Prm tPrms[1] = { theParam };
	BindXFeVt<op> * tFeV = new BindXFeVt<op>(theFss, hdlSys, tPrms, 1, theBind);
	Hdl const tHdl = tFeV->defSysFunc();
	if (tHdl != InvHdl) { delete tFeV; return tHdl; }

	EvalTbl<typename op::OutTyp> & tOutTbl =
				EvalTbl<typename op::OutTyp>::refm(hdlSys);
	EvalTbl<typename op::InxTyp> const & tInxTbl =
				EvalTbl<typename op::InxTyp>::refc(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFeV->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFeV->mPrmSpecs;

	Loc const tPxLoc = getPxLoc(theFss,tPrmTerms[0],tPrmSpecs[0]);
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
BindXFeVt<op>::BindXFeVt(Fss const theFss, Hdl const hdlSys, Prm * thePrms,
		Dim const PrmCount, bind const & theBind) :
		SegFeVt<typename op::OutTyp>(hdlSys, PrmCount), mBind(theBind)
{
	WatchError
	this->setTermCls(TermStub< BindXFeVt<op> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, op::Order);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template<typename op>
BindXFeVt<op>::BindXFeVt(BindXFeVt<op> const & that) :
		SegFeVt<typename op::OutTyp>(that), mBind(that.mBind)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename op>
BindXFeVt<op> const & BindXFeVt<op>::operator = (BindXFeVt<op> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}


/*!
	Calculate hash value of the term.
*/
template<typename op>
Hvl BindXFeVt<op>::calcTermHvl() const
{
	WatchError
	Hvl tHvl = 0;
	tHvl = mixHash(tHvl, calcHash(this->TermCls));
	tHvl = mixHash(tHvl, calcHash(this->FuncFss));
	tHvl = mixHash(tHvl, calcHash(this->mPrmTerms[0]));
	tHvl = mixHash(tHvl, calcHash(this->mPrmSpecs[0]));
	tHvl = mixHash(tHvl, this->mBind.hashval());
	return tHvl;
	CatchError
}



/*!
	Compare two terms for equality.
*/
template<typename op>
Bll BindXFeVt<op>::equate(Term const & theTerm) const
{
	WatchError
	if (this->TermCls != theTerm.TermCls) return false;
	BindXFeVt<op> const & tBindXFeVt = cast(theTerm);
	if (this->FuncFss != tBindXFeVt.FuncFss) return false;
	if (this->mPrmTerms.itemCount() != tBindXFeVt.mPrmTerms.itemCount()) return false;
	if (this->mPrmTerms[0] != tBindXFeVt.mPrmTerms[0]) return false;
	if (this->mPrmSpecs[0] != tBindXFeVt.mPrmSpecs[0]) return false;
	if (!mBind.equate(tBindXFeVt.mBind)) return false;
	return true;
	CatchError
}



/*!
	Compute the term.
*/
template<typename op>
void BindXFeVt<op>::compConst()
{
	WatchError
	if (this->updatable())
		this->setUpdatable(mBind.chk(this->mPrmTerms[0]->updatable(), mPxRec->CurrData()));

	if (!this->updatable())
		this->mValueRec->finalise(mBind.iof(mPxRec->CurrData()));
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename op>
void BindXFeVt<op>::execAnew()
{
	WatchError
	#if ExecDnwd
	Term::performExecAnew(this->mPrmTerms[0]);
	#endif
	this->mValueRec->initCurr(mBind.iof(mPxRec->CurrData()));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template<typename op>
void BindXFeVt<op>::simulAnew()
{
	WatchError
	#if SimulDnwd
	Term::performSimulAnew(this->mPrmTerms[0]);
	#endif
	this->mValueRec->updtNext(this->mTermSys.SimulClk(),
		mBind.iof(mPxRec->NextData(this->mTermSys.SimulClk())));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename op>
void BindXFeVt<op>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		if (mPxRec->PrevDiff(this->mTermSys.ExecClk()))
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
				mBind.iof(mPxRec->CurrData()));
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
					mBind.iof(mPxRec->CurrData()));
		}
	#if CompLazy
	}
	else	//	defered
	{
		if (this->needExecCandComp()) this->listCandParams();
		if (this->mBlkCandPrms->itemCount())
		{
			Term::performExecIncr(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->PrevDiff(this->mTermSys.ExecClk()))
				this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
					mBind.iof(mPxRec->CurrData()));
		}
		else if (this->mBacklogPrms.tagCount())
		{
			Term::performExecBklg(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->PrevDiff(this->mTermSys.ExecClk()))
				this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
					mBind.iof(mPxRec->CurrData()));
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
void BindXFeVt<op>::execBklg()
{
	WatchError
	Term::performExecBklg(this->mPrmTerms[0]);
	if (this->mEvalUndonePrms->tagged(0) ||
			mPxRec->PrevDiff(this->mTermSys.ExecClk()))
		this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
				mBind.iof(mPxRec->CurrData()));
	this->runPostExecBklg();
	CatchError
}
#endif //CompLazy



/*!
	Compute the term in simulation mode.
*/
template<typename op>
void BindXFeVt<op>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		if (mPxRec->NextDiff(this->mTermSys.SimulClk()))
			this->mValueRec->updtNext(this->mTermSys.SimulClk(),
				mBind.iof(mPxRec->NextData(this->mTermSys.SimulClk())));
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
					mBind.iof(mPxRec->NextData(this->mTermSys.SimulClk())));
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
					mBind.iof(mPxRec->NextData(this->mTermSys.SimulClk())));
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
					mBind.iof(mPxRec->NextData(this->mTermSys.SimulClk())));
			return;
		}
		#endif

		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->listFlexiParams();
		if (this->mBlkFlexiPrms->itemCount())
		{
			Term::performSimulIncr(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->NextDiff(this->mTermSys.SimulClk()))
				this->mValueRec->updtNext(this->mTermSys.SimulClk(),
					mBind.iof(mPxRec->NextData(this->mTermSys.SimulClk())));
			return;
		}
		#endif

		if (this->needSimulCacheComp())
		{
			Term::performEmulBklg(this->mPrmTerms[0]);
			cSimulBklg = (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->LateDiff(this->mTermSys.EmulClk()));
		}

		if (cSimulBklg)
			this->mValueRec->updtNext(this->mTermSys.SimulClk(),
				mBind.iof(mPxRec->LateData(this->mTermSys.EmulClk())));
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
void BindXFeVt<op>::emulBklg()
{
	WatchError
	Term::performEmulBklg(this->mPrmTerms[0]);
	if (this->mEvalUndonePrms->tagged(0) ||
			mPxRec->LateDiff(this->mTermSys.EmulClk()))
		this->mValueRec->updtLate(this->mTermSys.EmulClk(),
			mBind.iof(mPxRec->LateData(this->mTermSys.EmulClk())));
	CatchError
}
#endif //CompLazy


closeKangarooSpace


#endif //BindXFeVtTccIncluded
