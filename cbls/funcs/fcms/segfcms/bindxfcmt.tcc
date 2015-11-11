/*!
	@file bindxfcmt.tcc
	@brief The prototype file for BindXFcMt template class.
	@details This is the prototype file for BindXFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef BindXFcMtTccIncluded
#define BindXFcMtTccIncluded


#include "cbls/funcs/fcms/segfcmt.tcc"


openKangarooSpace



/*!
	@class BindXFcMt
	@brief A template class to represent bounded operator FcMs.
	@details This template class represents bounded operator FcMs.
*/
template<typename op>
class BindXFcMt : public SegFcMt<typename op::OutTyp>
{
	public:
		typedef op bind;	//!< Function class to bind operand values.

		static Hdl def(Fss const theFss, Hdl const hdlSys,
										Prm const & Param, bind const & theBind);	//!< Definiton.

		static BindXFcMt<op> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static BindXFcMt<op> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static BindXFcMt<op> const & refc(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static BindXFcMt<op> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.

		//! @name Casting
		//! @{

		static BindXFcMt<op> const & cast(Term const & theTerm);	//!< Perform casting.
		static BindXFcMt<op> const * cast(Term const * theTerm);	//!< Perform casting.
		static BindXFcMt<op> & cast(Term & theTerm);				//!< Perform casting.
		static BindXFcMt<op> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	private:

		BindXFcMt(Fss const theFss, Hdl const hdlSys, Prm * thePrms,
								Dim const PrmCount, bind const & theBind);	//!< Constructor.
		BindXFcMt const & operator = (BindXFcMt<op> const & that);			//!< Assigner.
		BindXFcMt(BindXFcMt<op> const & that);								//!< Duplicator.
		~BindXFcMt();														//!< Destructor.

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

		EvalRec<typename op::InxTyp> const * mPxRec;		//!< The parameter.
		bind const 							mBind;			//!< The bind.
		#if SimulLazy
		Bll 					   			cSimulBklg;		//!< Simulation cache.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BindXFcMt<op>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< BindXFcMt<op> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BindXFcMt<op>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< BindXFcMt<op> >::TermCls;
	CatchError
}




/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BindXFcMt<op>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< BindXFcMt<op> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename op>
inline Bll BindXFcMt<op>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< BindXFcMt<op> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BindXFcMt<op> & BindXFcMt<op>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< BindXFcMt<op> >::TermCls, eWrongCls);

	return scast<BindXFcMt<op> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BindXFcMt<op> * BindXFcMt<op>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub< BindXFcMt<op> >::TermCls, eWrongCls);

	return scast<BindXFcMt<op> *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BindXFcMt<op> const & BindXFcMt<op>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< BindXFcMt<op> >::TermCls, eWrongCls);

	return scast<BindXFcMt<op> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename op>
inline BindXFcMt<op> const * BindXFcMt<op>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub< BindXFcMt<op> >::TermCls, eWrongCls);

	return scast<BindXFcMt<op> const *>(theTerm);
	CatchError
}



/*!
	Refer to a bind FcM term.
*/
template<typename op>
inline BindXFcMt<op> & BindXFcMt<op>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a bind FcM term.
*/
template<typename op>
inline BindXFcMt<op> * BindXFcMt<op>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a bind FcM term.
*/
template<typename op>
inline BindXFcMt<op> const & BindXFcMt<op>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a bind FcM term.
*/
template<typename op>
inline BindXFcMt<op> const * BindXFcMt<op>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template<typename op>
inline BindXFcMt<op>::~BindXFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Define a unary2 FcM.
*/
template<typename op>
Hdl BindXFcMt<op>::def(Fss const theFss, Hdl const hdlSys,
								Prm const & theParam, bind const & theBind)
{
	WatchError
	Warn(op::Arity != 1, eParamCount1(1));

	Prm tPrms[1] = { theParam };
	BindXFcMt<op> * tFcM = new BindXFcMt<op>(theFss, hdlSys, tPrms, 1, theBind);
	Hdl const tHdl = tFcM->defSysFunc();
	if (tHdl != InvHdl) { delete tFcM; return tHdl; }

	EvalTbl<typename op::OutTyp> & tOutTbl =
				EvalTbl<typename op::OutTyp>::refm(hdlSys);
	EvalTbl<typename op::InxTyp> const & tInxTbl =
				EvalTbl<typename op::InxTyp>::refc(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFcM->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFcM->mPrmSpecs;

	Loc const tPxLoc = getPxLoc(theFss,tPrmTerms[0],tPrmSpecs[0]);
	tFcM->mPxRec = tInxTbl.ptrcEvalRec(tPxLoc);

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
BindXFcMt<op>::BindXFcMt(Fss const theFss, Hdl const hdlSys, Prm * thePrms,
		Dim const PrmCount, bind const & theBind) :
		SegFcMt<typename op::OutTyp>(hdlSys, PrmCount), mBind(theBind)
{
	WatchError
	this->setTermCls(TermStub< BindXFcMt<op> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, op::Order);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template<typename op>
BindXFcMt<op>::BindXFcMt(BindXFcMt<op> const & that) :
		SegFcMt<typename op::OutTyp>(that), mBind(that.mBind)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename op>
BindXFcMt<op> const & BindXFcMt<op>::operator = (BindXFcMt<op> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}


/*!
	Calculate hash value of the term.
*/
template<typename op>
Hvl BindXFcMt<op>::calcTermHvl() const
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
Bll BindXFcMt<op>::equate(Term const & theTerm) const
{
	WatchError
	if (this->TermCls != theTerm.TermCls) return false;
	BindXFcMt<op> const & tBindXFcMt = cast(theTerm);
	if (this->FuncFss != tBindXFcMt.FuncFss) return false;
	if (this->mPrmTerms.itemCount() != tBindXFcMt.mPrmTerms.itemCount()) return false;
	if (this->mPrmTerms[0] != tBindXFcMt.mPrmTerms[0]) return false;
	if (this->mPrmSpecs[0] != tBindXFcMt.mPrmSpecs[0]) return false;
	if (!mBind.equate(tBindXFcMt.mBind)) return false;
	return true;
	CatchError
}



/*!
	Compute the term.
*/
template<typename op>
void BindXFcMt<op>::compConst()
{
	WatchError
	if (this->updatable())
		this->setUpdatable(mBind.chk(this->mPrmTerms[0]->updatable(), mPxRec->CurrData()));

	if (!this->updatable())
		this->mMetricRec->finalise(mBind.iof(mPxRec->CurrData()));
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template<typename op>
void BindXFcMt<op>::execAnew()
{
	WatchError
	#if ExecDnwd
	Term::performExecAnew(this->mPrmTerms[0]);
	#endif
	this->mMetricRec->initCurr(mBind.iof(mPxRec->CurrData()));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template<typename op>
void BindXFcMt<op>::simulAnew()
{
	WatchError
	#if SimulDnwd
	Term::performSimulAnew(this->mPrmTerms[0]);
	#endif
	this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
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
void BindXFcMt<op>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		if (mPxRec->PrevDiff(this->mTermSys.ExecClk()))
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
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
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
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
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
					mBind.iof(mPxRec->CurrData()));
		}
		else if (this->mBacklogPrms.tagCount())
		{
			Term::performExecBklg(this->mPrmTerms[0]);
			if (this->mEvalUndonePrms->tagged(0) ||
					mPxRec->PrevDiff(this->mTermSys.ExecClk()))
				this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
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
void BindXFcMt<op>::execBklg()
{
	WatchError
	Term::performExecBklg(this->mPrmTerms[0]);
	if (this->mEvalUndonePrms->tagged(0) ||
			mPxRec->PrevDiff(this->mTermSys.ExecClk()))
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
				mBind.iof(mPxRec->CurrData()));
	this->runPostExecBklg();
	CatchError
}
#endif //CompLazy



/*!
	Compute the term in simulation mode.
*/
template<typename op>
void BindXFcMt<op>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		if (mPxRec->NextDiff(this->mTermSys.SimulClk()))
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
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
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
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
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
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
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
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
				this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
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
			this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
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
void BindXFcMt<op>::emulBklg()
{
	WatchError
	Term::performEmulBklg(this->mPrmTerms[0]);
	if (this->mEvalUndonePrms->tagged(0) ||
			mPxRec->LateDiff(this->mTermSys.EmulClk()))
		this->mMetricRec->updtLate(this->mTermSys.EmulClk(),
			mBind.iof(mPxRec->LateData(this->mTermSys.EmulClk())));
	CatchError
}
#endif //CompLazy


closeKangarooSpace


#endif //BindXFcMtTccIncluded
