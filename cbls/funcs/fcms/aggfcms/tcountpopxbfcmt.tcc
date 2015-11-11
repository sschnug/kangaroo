/*!
	@file tcountpopxbfcmt.tcc
	@brief The prototype file for TcountPopXBFcMt template class.
	@details This is the prototype file for TcountPopXBFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef TcountPopXBFcMtTccInlcluded
#define TcountPopXBFcMtTccInlcluded



#include "cbls/funcs/fcms/aggfcmt.tcc"



openKangarooSpace



/*!
	@class TcountPopXBFcMt
	@brief A class to represent true count pipe fcms.
	@details This class represents true count pipe fcms.
*/
template <typename pxt, typename pop>
class TcountPopXBFcMt : public AggFcMt<typename pop::OutTyp>
{
	public:

		typedef pop bind;		//!< The bound pipe operator.

		static Hdl def(Fss const theFss, Hdl const hdlSys,
							Prm * thePrms, Dim const PrmCount, bind const & theBind);		//!< Definition.
		static TcountPopXBFcMt<pxt,pop> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static TcountPopXBFcMt<pxt,pop> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static TcountPopXBFcMt<pxt,pop> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static TcountPopXBFcMt<pxt,pop> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static TcountPopXBFcMt<pxt,pop> const & cast(Term const & theTerm);	//!< Perform casting.
		static TcountPopXBFcMt<pxt,pop> const * cast(Term const * theTerm);	//!< Perform casting.
		static TcountPopXBFcMt<pxt,pop> & cast(Term & theTerm);				//!< Perform casting.
		static TcountPopXBFcMt<pxt,pop> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	private:

		~TcountPopXBFcMt();															//!< Destructor.
		TcountPopXBFcMt(TcountPopXBFcMt<pxt,pop> const & that);						//!< Duplicator.
		TcountPopXBFcMt(Fss const theFss, Hdl const hdlSys,
				Prm * thePrms, Dim const PrmCount, bind const & theBind);			//!< Constructor.
		TcountPopXBFcMt const & operator = (TcountPopXBFcMt<pxt,pop> const & that);	//!< Assigner.

		//! @name Identity
		//! @{

		Hvl calcTermHvl() const;				 				//!< Calculate term hash value.
		virtual Bll equate(Term const & theTerm) const; 		//!< Compare terms for equality.

		//! @}

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
		virtual void undoEval(Pos const thePos);	//!< Perform eval undo.
		#endif //CompLazy

		//! @}

	private:

		b1<EvalRec<pxt> const *,kmm> mPxRecs;		//!< Parameter records.

		typedef typename pop::InxTyp TempType;		//!< Temporary type.
		typedef Dim BuffType;						//!< Data buff type.

		#if SimulDnwdCache
		BuffType	cSimulTrue;		//!< Simulation cache true count.
		#endif
		BuffType	cExecTrue;		//!< Execution cache true count.
		#if CompLazy
		BuffType	cEmulTrue;		//!< Emulation cache true count.
		#endif //CompLazy
		bind const	mBind;			//!< The bind pop.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll TcountPopXBFcMt<pxt,pop>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< TcountPopXBFcMt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll TcountPopXBFcMt<pxt,pop>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< TcountPopXBFcMt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll TcountPopXBFcMt<pxt,pop>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< TcountPopXBFcMt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll TcountPopXBFcMt<pxt,pop>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< TcountPopXBFcMt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFcMt<pxt,pop> const & TcountPopXBFcMt<pxt,pop>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< TcountPopXBFcMt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<TcountPopXBFcMt<pxt,pop> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFcMt<pxt,pop> const * TcountPopXBFcMt<pxt,pop>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< TcountPopXBFcMt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<TcountPopXBFcMt<pxt,pop> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFcMt<pxt,pop> & TcountPopXBFcMt<pxt,pop>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< TcountPopXBFcMt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<TcountPopXBFcMt<pxt,pop> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFcMt<pxt,pop> * TcountPopXBFcMt<pxt,pop>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< TcountPopXBFcMt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<TcountPopXBFcMt<pxt,pop> *>(theTerm);
	CatchError
}



/*!
	Refer to an or fcm term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFcMt<pxt,pop> & TcountPopXBFcMt<pxt,pop>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to an or fcm term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFcMt<pxt,pop> * TcountPopXBFcMt<pxt,pop>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to an or fcm term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFcMt<pxt,pop> const & TcountPopXBFcMt<pxt,pop>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to an or fcm term.
*/
template <typename pxt, typename pop>
inline TcountPopXBFcMt<pxt,pop> const * TcountPopXBFcMt<pxt,pop>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pxt, typename pop>
inline TcountPopXBFcMt<pxt,pop>::~TcountPopXBFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Define an or fcm term.
*/
template <typename pxt, typename pop>
Hdl TcountPopXBFcMt<pxt,pop>::def(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, bind const & theBind)
{
	WatchError
	Warn(PrmCount < 2 || PrmCount > MaxDim, eParamCount2(2, MaxDim));

	TcountPopXBFcMt<pxt,pop> * tFcM =
			new TcountPopXBFcMt<pxt,pop>(theFss,hdlSys, thePrms, PrmCount, theBind);
	Hdl const tHdl = tFcM->defSysFunc();
	if (tHdl != InvHdl) { delete tFcM; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<typename pop::OutTyp> & tOutTbl =
					EvalTbl<typename pop::OutTyp>::refm(hdlSys);

	b1<Term *,kmm> const & tPrmTerms = tFcM->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFcM->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFcM->mPxRecs[tPos] = tPxtTbl.ptrcEvalRec(tPxLoc);
	}
	tOutTbl.setEvalRec(tFcM->mMetricRec, tFcM->mMetricLoc);

	tFcM->performCompConst();
	tFcM->defSysRoot();
	return tFcM->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
template <typename pxt, typename pop>
TcountPopXBFcMt<pxt,pop>::TcountPopXBFcMt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, bind const & theBind) :
		AggFcMt<typename pop::OutTyp>(hdlSys, PrmCount), mPxRecs(PrmCount), mBind(theBind)
{
	WatchError
	this->setTermCls(TermStub< TcountPopXBFcMt<pxt,pop> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Unordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename pop>
TcountPopXBFcMt<pxt,pop>::TcountPopXBFcMt(TcountPopXBFcMt const & that) :
		AggFcMt<typename pop::OutTyp>(that), mPxRecs(0), mBind(that.mBind)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename pxt, typename pop>
TcountPopXBFcMt<pxt,pop> const & TcountPopXBFcMt<pxt,pop>::operator =
		(TcountPopXBFcMt<pxt,pop> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}


/*!
	Calculate hash value of the term.
*/
template <typename pxt, typename pop>
Hvl TcountPopXBFcMt<pxt,pop>::calcTermHvl() const
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
Bll TcountPopXBFcMt<pxt,pop>::equate(Term const & theTerm) const
{
	WatchError
	if (this->TermCls != theTerm.TermCls) return false;
	TcountPopXBFcMt<pxt,pop> const & tTcountPopXBFcMt = cast(theTerm);
	if (this->FuncFss != tTcountPopXBFcMt.FuncFss) return false;
	if (this->mPrmTerms.itemCount() != tTcountPopXBFcMt.mPrmTerms.itemCount()) return false;

	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		if (this->mPrmTerms[tPos] != tTcountPopXBFcMt.mPrmTerms[tPos]) return false;
		if (this->mPrmSpecs[tPos] != tTcountPopXBFcMt.mPrmSpecs[tPos]) return false;
	}
	if (!mBind.equate(tTcountPopXBFcMt.mBind)) return false;
	return true;
	CatchError
}





/*!
	Compute the term.
*/
template <typename pxt, typename pop>
void TcountPopXBFcMt<pxt,pop>::compConst()
{
	WatchError
	if (!this->updatable())
	{
		cExecTrue = 0;
		for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
			if (tc<pxt,Bll>::iof(mPxRecs[tPos]->CurrData())) ++cExecTrue;
		this->mMetricRec->finalise(mBind.iof(tc<BuffType,TempType>::iof(cExecTrue)));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename pop>
void TcountPopXBFcMt<pxt,pop>::execAnew()
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
	this->mMetricRec->initCurr(mBind.iof(tc<BuffType,TempType>::iof(cExecTrue)));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename pop>
void TcountPopXBFcMt<pxt,pop>::simulAnew()
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
	this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
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
void TcountPopXBFcMt<pxt,pop>::undoEval(Pos const thePos)
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
void TcountPopXBFcMt<pxt,pop>::execIncr()
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
		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
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
			this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
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

		this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
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
void TcountPopXBFcMt<pxt,pop>::execBklg()
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

	this->mMetricRec->updtCurr(this->mTermSys.ExecClk(),
			mBind.iof(tc<BuffType,TempType>::iof(cExecTrue)));
	this->runPostExecBklg();
	CatchError
}
#endif //CompLazy



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename pop>
void TcountPopXBFcMt<pxt,pop>::simulIncr()
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
		this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
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

			this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
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

		this->mMetricRec->updtNext(this->mTermSys.SimulClk(),
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
void TcountPopXBFcMt<pxt,pop>::emulBklg()
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
	this->mMetricRec->updtLate(this->mTermSys.EmulClk(),
			mBind.iof(tc<BuffType,TempType>::iof(cEmulTrue)));
	CatchError
}
#endif //CompLazy


closeKangarooSpace


#endif//TcountPopXBFcMtTccIncluded
