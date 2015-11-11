/*!
	@file tcountpopxbfevt.tcc
	@brief The prototype file for TcountPopXBFeVt template class.
	@details This is the prototype file for TcountPopXBFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef TcountPopXBFeVtTccIncluded
#define TcountPopXBFeVtTccIncluded



#include "cbls/funcs/fevs/aggfevt.tcc"



openKangarooSpace



/*!
	@class TcountPopXBFeVt
	@brief A class to represent true count pipe fevs.
	@details This class represents true count pipe fevs.
*/
template <typename pxt, typename pop>
class TcountPopXBFeVt : public AggFeVt<typename pop::OutTyp>
{
	public:

		typedef pop bind;		//!< The bound pipe operator.

		static Hdl def(Fss const theFss, Hdl const hdlSys,
							Prm * thePrms, Dim const PrmCount, bind const & theBind);		//!< Definition.
		static TcountPopXBFeVt<pxt,pop> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static TcountPopXBFeVt<pxt,pop> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static TcountPopXBFeVt<pxt,pop> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static TcountPopXBFeVt<pxt,pop> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static TcountPopXBFeVt<pxt,pop> const & cast(Term const & theTerm);	//!< Perform casting.
		static TcountPopXBFeVt<pxt,pop> const * cast(Term const * theTerm);	//!< Perform casting.
		static TcountPopXBFeVt<pxt,pop> & cast(Term & theTerm);				//!< Perform casting.
		static TcountPopXBFeVt<pxt,pop> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	private:

		~TcountPopXBFeVt();															//!< Destructor.
		TcountPopXBFeVt(TcountPopXBFeVt<pxt,pop> const & that);						//!< Duplicator.
		TcountPopXBFeVt(Fss const theFss, Hdl const hdlSys,
					Prm * thePrms, Dim const PrmCount, bind const & theBind);		//!< Constructor.
		TcountPopXBFeVt const & operator = (TcountPopXBFeVt<pxt,pop> const & that);	//!< Assigner.

		//! @name Computation
		//! @{

		virtual void compConst();					//!< Compute the term.
		virtual void execAnew();					//!< Execute the term.
		virtual void simulAnew();					//!< Simulate the term.
		virtual void execIncr();					//!< Execute the term.
		virtual void simulIncr();					//!< Simulate the term.
		#if CompLazy
		virtual void execBklg();					//!< Execute the term.
		virtual void emulBklg();					//!< Emulate the term.
		virtual void undoEval(Pos const thePos);		//!< Perform eval undo.
		#endif //CompLazy

		//! @}
		//! @name Identity
		//! @{

		Hvl calcTermHvl() const;				 				//!< Calculate term hash value.
		virtual Bll equate(Term const & theTerm) const; 		//!< Compare terms for equality.

		//! @}

	private:

		b1<EvalRec<pxt> const *,kmm> mPxRecs;		//!< Parameter records.

		typedef typename pop::InxTyp TempType;		//!< Temporary type.
		typedef Dim BuffType;						//!< Data buff type.

		#if SimulDnwdCache
		BuffType	cSimulTrue;						//!< Simulation cache true count.
		#endif
		BuffType	cExecTrue;						//!< Execution cache true count.
		#if CompLazy
		BuffType	cEmulTrue;						//!< Emulation cache true count.
		#endif //CompLazy
		bind const	mBind;							//!< The bind pop.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll TcountPopXBFeVt<pxt,pop>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< TcountPopXBFeVt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll TcountPopXBFeVt<pxt,pop>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< TcountPopXBFeVt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll TcountPopXBFeVt<pxt,pop>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< TcountPopXBFeVt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll TcountPopXBFeVt<pxt,pop>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< TcountPopXBFeVt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFeVt<pxt,pop> const & TcountPopXBFeVt<pxt,pop>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< TcountPopXBFeVt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<TcountPopXBFeVt<pxt,pop> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFeVt<pxt,pop> const * TcountPopXBFeVt<pxt,pop>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< TcountPopXBFeVt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<TcountPopXBFeVt<pxt,pop> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFeVt<pxt,pop> & TcountPopXBFeVt<pxt,pop>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< TcountPopXBFeVt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<TcountPopXBFeVt<pxt,pop> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFeVt<pxt,pop> * TcountPopXBFeVt<pxt,pop>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< TcountPopXBFeVt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<TcountPopXBFeVt<pxt,pop> *>(theTerm);
	CatchError
}



/*!
	Refer to an or fev term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFeVt<pxt,pop> & TcountPopXBFeVt<pxt,pop>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to an or fev term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFeVt<pxt,pop> * TcountPopXBFeVt<pxt,pop>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an or fev term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFeVt<pxt,pop> const & TcountPopXBFeVt<pxt,pop>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to an or fev term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFeVt<pxt,pop> const * TcountPopXBFeVt<pxt,pop>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pxt, typename pop>
inline TcountPopXBFeVt<pxt,pop>::~TcountPopXBFeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Define an or fev term.
*/
template <typename pxt, typename pop>
Hdl TcountPopXBFeVt<pxt,pop>::def(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, bind const & theBind)
{
	WatchError
	Warn(PrmCount < 2 || PrmCount > MaxDim, eParamCount2(2, MaxDim));

	TcountPopXBFeVt<pxt,pop> * tFeV =
		new TcountPopXBFeVt<pxt,pop>(theFss,hdlSys, thePrms, PrmCount, theBind);
	Hdl const tHdl = tFeV->defSysFunc();
	if (tHdl != InvHdl) { delete tFeV; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<typename pop::OutTyp> & tOutTbl =
					EvalTbl<typename pop::OutTyp>::refm(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFeV->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFeV->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFeV->mPxRecs[tPos] = tPxtTbl.ptrcEvalRec(tPxLoc);
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
template <typename pxt, typename pop>
TcountPopXBFeVt<pxt,pop>::TcountPopXBFeVt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, bind const & theBind) :
		AggFeVt<typename pop::OutTyp>(hdlSys, PrmCount), mPxRecs(PrmCount), mBind(theBind)
{
	WatchError
	this->setTermCls(TermStub< TcountPopXBFeVt<pxt,pop> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Unordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename pop>
TcountPopXBFeVt<pxt,pop>::TcountPopXBFeVt(TcountPopXBFeVt const & that) :
		AggFeVt<typename pop::OutTyp>(that), mPxRecs(0), mBind(that.mBind)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename pxt, typename pop>
TcountPopXBFeVt<pxt,pop> const & TcountPopXBFeVt<pxt,pop>::operator =
		(TcountPopXBFeVt<pxt,pop> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Calculate hash value of the term.
*/
template <typename pxt, typename pop>
Hvl TcountPopXBFeVt<pxt,pop>::calcTermHvl() const
{
	WatchError
	Hvl tHvl = 0;
	tHvl = mixHash(tHvl, calcHash(this->TermCls));
	tHvl = mixHash(tHvl, calcHash(this->FuncFss));

	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		tHvl = mixHash(tHvl, calcHash(this->mPrmTerms[tPos]));
		tHvl = mixHash(tHvl, calcHash(this->mPrmSpecs[tPos]));
	}

	tHvl = mixHash(tHvl, this->mBind.hashval());
	return tHvl;
	CatchError
}



/*!
	Compare two terms for equality.
*/
template <typename pxt, typename pop>
Bll TcountPopXBFeVt<pxt,pop>::equate(Term const & theTerm) const
{
	WatchError
	if (this->TermCls != theTerm.TermCls) return false;
	TcountPopXBFeVt<pxt,pop> const & tTcountPopXBFeVt = cast(theTerm);
	if (this->FuncFss != tTcountPopXBFeVt.FuncFss) return false;
	if (this->mPrmTerms.itemCount() != tTcountPopXBFeVt.mPrmTerms.itemCount()) return false;

	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		if (this->mPrmTerms[tPos] != tTcountPopXBFeVt.mPrmTerms[tPos]) return false;
		if (this->mPrmSpecs[tPos] != tTcountPopXBFeVt.mPrmSpecs[tPos]) return false;
	}
	if (!mBind.equate(tTcountPopXBFeVt.mBind)) return false;
	return true;
	CatchError
}




/*!
	Compute the term.
*/
template <typename pxt, typename pop>
void TcountPopXBFeVt<pxt,pop>::compConst()
{
	WatchError
	if (!this->updatable())
	{
		cExecTrue = 0;
		for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
			if (tc<pxt,Bll>::iof(mPxRecs[tPos]->CurrData())) ++cExecTrue;
		this->mValueRec->finalise(mBind.iof(tc<BuffType,TempType>::iof(cExecTrue)));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename pop>
void TcountPopXBFeVt<pxt,pop>::execAnew()
{
	WatchError
	cExecTrue = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if ExecDnwd
		Term::performExecAnew(this->mPrmTerms[tPos]);
		#endif
		if (tc<pxt,Bll>::iof(mPxRecs[tPos]->CurrData())) ++cExecTrue;
	}
	this->mValueRec->initCurr(mBind.iof(tc<BuffType,TempType>::iof(cExecTrue)));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename pop>
void TcountPopXBFeVt<pxt,pop>::simulAnew()
{
	WatchError
	Dim tSimulTrue = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if SimulDnwd
		Term::performSimulAnew(this->mPrmTerms[tPos]);
		#endif
		if (tc<pxt,Bll>::iof(mPxRecs[tPos]->NextData(this->mTermSys.SimulClk())))
			++tSimulTrue;
	}
	this->mValueRec->updtNext(this->mTermSys.SimulClk(),
		mBind.iof(tc<BuffType,TempType>::iof(tSimulTrue)));
	#if SimulUpwd
	this->runPostSimulAnew();
	#endif
	CatchError
}



#if CompLazy
/*!
	Perform eval undo for the parameter.
*/
template <typename pxt, typename pop>
void TcountPopXBFeVt<pxt,pop>::undoEval(Pos const thePos)
{
	WatchError
	if (tc<pxt,Bll>::iof(mPxRecs[thePos]->PrevData(this->mTermSys.ExecClk())))
		--cExecTrue;
	CatchError
}
#endif



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename pop>
void TcountPopXBFeVt<pxt,pop>::execIncr()
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
				(tc<pxt,Bll>::iof(tPxRec->CurrBuff)) ? ++cExecTrue : --cExecTrue;
		}
		this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
				mBind.iof(tc<BuffType,TempType>::iof(cExecTrue)));
		this->runPostExecIncr();
	}
	#endif	//ExecUpwd
	#if ExecDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//	CompLazy
		if (this->needExecCandComp()) this->listCandParams();
		if (this->mBlkCandPrms->itemCount())
		{
			for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkCandPrms->item(tIdx);
				Term::performExecIncr(this->mPrmTerms[tPos]);
				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
					(tc<pxt,Bll>::iof(tPxRec->CurrBuff)) ? ++cExecTrue : --cExecTrue;
			}
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
				mBind.iof(tc<BuffType,TempType>::iof(cExecTrue)));
		}
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
				{ if (tc<pxt,Bll>::iof(tPxRec->CurrData())) ++cExecTrue; }
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				(tc<pxt,Bll>::iof(tPxRec->CurrBuff)) ? ++cExecTrue : --cExecTrue;
		}

		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;
			Term::performExecBklg(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
				{ if (tc<pxt,Bll>::iof(tPxRec->CurrData())) ++cExecTrue; }
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				(tc<pxt,Bll>::iof(tPxRec->CurrBuff)) ? ++cExecTrue : --cExecTrue;
		}

		this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
			mBind.iof(tc<BuffType,TempType>::iof(cExecTrue)));
	}
	this->runPostExecIncr();
	#endif //CompLazy
	#endif //ExecDnwd
	CatchError
}


#if CompLazy
/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename pop>
void TcountPopXBFeVt<pxt,pop>::execBklg()
{
	WatchError
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performExecBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			{ if (tc<pxt,Bll>::iof(tPxRec->CurrData())) ++cExecTrue; }
		else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			(tc<pxt,Bll>::iof(tPxRec->CurrBuff)) ? ++cExecTrue : --cExecTrue;
	}

	this->mValueRec->updtCurr(this->mTermSys.ExecClk(),
		mBind.iof(tc<BuffType,TempType>::iof(cExecTrue)));
	this->runPostExecBklg();
	CatchError
}
#endif //CompLazy



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename pop>
void TcountPopXBFeVt<pxt,pop>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		Dim tSimulTrue = cExecTrue;
		for(Idx tIdx = 0; tIdx < this->mSimulChgdPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mSimulChgdPrms.serial(tIdx);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
			if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
				(tc<pxt,Bll>::iof(tPxRec->NextBuff)) ? ++tSimulTrue : --tSimulTrue;
		}
		this->mValueRec->updtNext(this->mTermSys.SimulClk(),
			mBind.iof(tc<BuffType,TempType>::iof(tSimulTrue)));
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

		#if SimulFixed
		if (this->needSimulCacheComp())
		{
			cSimulTrue = cExecTrue;
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				if (tc<pxt,Bll>::iof(mPxRecs[tPos]->CurrData())) --cSimulTrue;
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
			Dim tSimulTrue = cSimulTrue;
			#else
			Dim tSimulTrue = cExecTrue;
			#endif

			#if SimulFixed
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				Term::performSimulIncr(this->mPrmTerms[tPos]);
				if (tc<pxt,Bll>::iof(mPxRecs[tPos]->NextData(this->mTermSys.SimulClk()))) ++tSimulTrue;
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

				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
					(tc<pxt,Bll>::iof(tPxRec->NextBuff)) ? ++tSimulTrue : --tSimulTrue;
			}
			#endif//SimulFlexi

			this->mValueRec->updtNext(this->mTermSys.SimulClk(),
				mBind.iof(tc<BuffType,TempType>::iof(tSimulTrue)));
		}
	#if CompLazy
	}
	else	//	backlog
	{
		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->listFlexiParams();
		#endif
		#if SimulFixed
		if (this->needSimulFixedComp()) this->markFixedParams();
		#endif

		if (this->needSimulCacheComp())
		{
			if (!this->chgdEmulClk())
			{
				cSimulTrue = cEmulTrue;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					if (tc<pxt,Bll>::iof(mPxRecs[tPos]->LateData(this->mTermSys.EmulClk())))
						--cSimulTrue;
				}
				#endif//SimulFixed
			}
			else
			{
				cSimulTrue = cExecTrue;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					if (!this->mEvalUndonePrms->tagged(tPos))
						if (tc<pxt,Bll>::iof(mPxRecs[tPos]->CurrData()))
							--cSimulTrue;
				}
				#endif
				for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
				{
					Pos const tPos = this->mBacklogPrms.serial(tIdx);
					#if SimulFixed
					if (this->mLblFixedPrms.tagged(tPos)) continue;
					#endif
					Term::performEmulBklg(this->mPrmTerms[tPos]);
					EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

					if (this->mEvalUndonePrms->tagged(tPos))
					{
						if (tc<pxt,Bll>::iof(tPxRec->LateData(this->mTermSys.EmulClk())))
							++cSimulTrue;
					}
					else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
						(tc<pxt,Bll>::iof(tPxRec->LateBuff)) ? ++cSimulTrue : --cSimulTrue;
				}
			}
		}

		Dim tSimulTrue = cSimulTrue;

		#if SimulFixed
		for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFixedPrms->item(tIdx);
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			if (tc<pxt,Bll>::iof(mPxRecs[tPos]->NextData(this->mTermSys.SimulClk()))) ++tSimulTrue;
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
			 (tc<pxt,Bll>::iof(tPxRec->NextData(this->mTermSys.SimulClk()))) ? ++tSimulTrue : --tSimulTrue;
		}
		#endif

		this->mValueRec->updtNext(this->mTermSys.SimulClk(),
			mBind.iof(tc<BuffType,TempType>::iof(tSimulTrue)));
	}
	#endif	//	CompLazy
	#endif 	//	SimulDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename pop>
void TcountPopXBFeVt<pxt,pop>::emulBklg()
{
	WatchError
	 cEmulTrue = cExecTrue;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			{ if (tc<pxt,Bll>::iof(tPxRec->LateData(this->mTermSys.EmulClk()))) ++cEmulTrue; }
		else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
			(tc<pxt,Bll>::iof(tPxRec->LateBuff)) ? ++cEmulTrue : --cEmulTrue;
	}
	this->mValueRec->updtLate(this->mTermSys.EmulClk(),
			mBind.iof(tc<BuffType,TempType>::iof(cEmulTrue)));
	CatchError
}
#endif //CompLazy


closeKangarooSpace


#endif//TcountPopXBFeVtTccIncluded
