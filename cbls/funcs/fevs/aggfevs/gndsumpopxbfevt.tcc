/*!
	@file gndsumpopxbfevt.tcc
	@brief The prototype file for GndSumPopXBFeVt template class.
	@details This is the prototype file for GndSumPopXBFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef GndSumPopXBFeVtIncluded
#define GndSumPopXBFeVtIncluded



#include "cbls/funcs/fevs/aggfevt.tcc"



openKangarooSpace



/*!
	@class GndSumPopXBFeVt
	@brief A class to represent grounded-summation pipe operator fev terms.
	@details This class represents grounded-summation pipe operator fev terms.
*/
template <typename pxt, typename pop>
class GndSumPopXBFeVt : public AggFeVt<typename pop::OutTyp>
{
	public:

		typedef pop bind;		//!< The bound pipe operator.

		static Hdl def(Fss const theFss, Hdl const hdlSys,
							Prm * thePrms, Dim const PrmCount, bind const & theBind);		//!< Definition.
		static GndSumPopXBFeVt<pxt,pop> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static GndSumPopXBFeVt<pxt,pop> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static GndSumPopXBFeVt<pxt,pop> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static GndSumPopXBFeVt<pxt,pop> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static GndSumPopXBFeVt<pxt,pop> const & cast(Term const & theTerm);		//!< Perform casting.
		static GndSumPopXBFeVt<pxt,pop> const * cast(Term const * theTerm);		//!< Perform casting.
		static GndSumPopXBFeVt<pxt,pop> & cast(Term & theTerm);					//!< Perform casting.
		static GndSumPopXBFeVt<pxt,pop> * cast(Term * theTerm);					//!< Perform casting.

		static Bll suit(Term const & theTerm);						//!< Suits casting?
		static Bll suit(Term const * theTerm);						//!< Suits casting?
		static Bll suit(Term & theTerm);								//!< Suits casting?
		static Bll suit(Term * theTerm);								//!< Suits casting?

		//! @}

	private:

		~GndSumPopXBFeVt();															//!< Destructor.
		GndSumPopXBFeVt(GndSumPopXBFeVt<pxt,pop> const & that);						//!< Duplicator.
		GndSumPopXBFeVt(Fss const theFss, Hdl const hdlSys,
						Prm * thePrms, Dim const PrmCount, bind const & theBind);	//!< Constructor.
		GndSumPopXBFeVt const & operator = (GndSumPopXBFeVt<pxt,pop> const & that);	//!< Assigner.

		//! @name Identity
		//! @{

		Hvl calcTermHvl() const;				 				//!< Calculate term hash value.
		virtual Bll equate(Term const & theTerm) const; 		//!< Compare terms for equality.

		//! @}

		//! @name Computations
		//! @{

		virtual void compConst();							//!< Compute the term.
		virtual void execAnew();							//!< Execute the term.
		virtual void simulAnew();							//!< Simulate the term.
		virtual void execIncr();							//!< Execute the term.
		virtual void simulIncr();							//!< Simulate the term.
		#if CompLazy
		virtual void execBklg();							//!< Execute the term.
		virtual void emulBklg();							//!< Emulate the term.
		virtual void undoEval(Pos const thePos);			//!< Perform eval undo.
		#endif

		//! @}

	private:

		b1<EvalRec<pxt> const *,kmm> mPxRecs;					//!< Parameter records.

		typedef typename pop::InxTyp TempType;					//!< Temporary type.
		typedef typename DataBuff<pxt,TempType>::Type BuffType;	//!< Data buff type.

		#if SimulDnwdCache
		BuffType		cSimulValue;//!< Simulation cache value.
		#endif
		BuffType		cExecValue;	//!< Execution cache value.
		#if CompLazy
		BuffType		cEmulValue;	//!< Emulation cache value.
		#endif
		bind const mBind;		//!< The bind pop.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll GndSumPopXBFeVt<pxt,pop>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< GndSumPopXBFeVt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll GndSumPopXBFeVt<pxt,pop>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< GndSumPopXBFeVt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll GndSumPopXBFeVt<pxt,pop>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< GndSumPopXBFeVt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename pop>
inline Bll GndSumPopXBFeVt<pxt,pop>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< GndSumPopXBFeVt<pxt,pop> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline GndSumPopXBFeVt<pxt,pop> const & GndSumPopXBFeVt<pxt,pop>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< GndSumPopXBFeVt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<GndSumPopXBFeVt<pxt,pop> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline GndSumPopXBFeVt<pxt,pop> const * GndSumPopXBFeVt<pxt,pop>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< GndSumPopXBFeVt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<GndSumPopXBFeVt<pxt,pop> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline GndSumPopXBFeVt<pxt,pop> & GndSumPopXBFeVt<pxt,pop>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< GndSumPopXBFeVt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<GndSumPopXBFeVt<pxt,pop> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename pop>
inline GndSumPopXBFeVt<pxt,pop> * GndSumPopXBFeVt<pxt,pop>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< GndSumPopXBFeVt<pxt,pop> >::TermCls) Wtxt(eWrongCls);

	return scast<GndSumPopXBFeVt<pxt,pop> *>(theTerm);
	CatchError
}



/*!
	Refer to a grounded summation fev term.
*/
template <typename pxt, typename pop>
inline GndSumPopXBFeVt<pxt,pop> & GndSumPopXBFeVt<pxt,pop>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a grounded summation fev term.
*/
template <typename pxt, typename pop>
inline GndSumPopXBFeVt<pxt,pop> * GndSumPopXBFeVt<pxt,pop>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a grounded summation fev term.
*/
template <typename pxt, typename pop>
inline GndSumPopXBFeVt<pxt,pop> const & GndSumPopXBFeVt<pxt,pop>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a grounded summation fev term.
*/
template <typename pxt, typename pop>
inline GndSumPopXBFeVt<pxt,pop> const * GndSumPopXBFeVt<pxt,pop>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pxt, typename pop>
inline GndSumPopXBFeVt<pxt,pop>::~GndSumPopXBFeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Define a grounded summation fev term.
*/
template <typename pxt, typename pop>
Hdl GndSumPopXBFeVt<pxt,pop>::def(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, bind const & theBind)
{
	WatchError
	Warn(PrmCount < 2 || PrmCount > MaxDim, eParamCount2(2, MaxDim));

	GndSumPopXBFeVt<pxt,pop> * tFeV = new GndSumPopXBFeVt<pxt,pop>(theFss, hdlSys, thePrms, PrmCount, theBind);
	Hdl const tHdl = tFeV->defSysFunc();
	if (tHdl != InvHdl) { delete tFeV; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);
	EvalTbl<typename pop::OutTyp> & tOutTbl =
				EvalTbl<typename pop::OutTyp>::refm(hdlSys);

	b1<Term *, kmm> const & tPrmTerms = tFeV->mPrmTerms;
	b1<Pss, kmm> const & tPrmSpecs = tFeV->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Warn(tPrmTerms[tPos]->TermGen == Tf, eTermNotGrounded);

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
GndSumPopXBFeVt<pxt,pop>::GndSumPopXBFeVt(Fss const theFss, Hdl const hdlSys,
				Prm * thePrms, Dim const PrmCount, bind const & theBind) :
		AggFeVt<typename pop::OutTyp>(hdlSys, PrmCount), mPxRecs(PrmCount), mBind(theBind)
{
	WatchError
	this->setTermCls(TermStub< GndSumPopXBFeVt<pxt,pop> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Unordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename pop>
GndSumPopXBFeVt<pxt,pop>::GndSumPopXBFeVt(GndSumPopXBFeVt const & that) :
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
GndSumPopXBFeVt<pxt,pop> const & GndSumPopXBFeVt<pxt,pop>::operator = (GndSumPopXBFeVt<pxt,pop> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Calculate hash value of the term.
*/
template <typename pxt, typename pop>
Hvl GndSumPopXBFeVt<pxt,pop>::calcTermHvl() const
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
Bll GndSumPopXBFeVt<pxt,pop>::equate(Term const & theTerm) const
{
	WatchError
	if (this->TermCls != theTerm.TermCls) return false;
	GndSumPopXBFeVt<pxt,pop> const & tGndSumPopXBFeVt = cast(theTerm);
	if (this->FuncFss != tGndSumPopXBFeVt.FuncFss) return false;
	if (this->mPrmTerms.itemCount() != tGndSumPopXBFeVt.mPrmTerms.itemCount()) return false;

	for(Pos tPos = 0; tPos < this->mPrmTerms.itemCount(); ++tPos)
	{
		if (this->mPrmTerms[tPos] != tGndSumPopXBFeVt.mPrmTerms[tPos]) return false;
		if (this->mPrmSpecs[tPos] != tGndSumPopXBFeVt.mPrmSpecs[tPos]) return false;
	}
	if (!mBind.equate(tGndSumPopXBFeVt.mBind)) return false;
	return true;
	CatchError
}



/*!
	Compute the term.
*/
template <typename pxt, typename pop>
void GndSumPopXBFeVt<pxt,pop>::compConst()
{
	WatchError
	if (!this->updatable())
	{
		cExecValue = 0;
		for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
			cExecValue += mPxRecs[tPos]->CurrData();
		this->mValueRec->finalise(mBind.iof(tc<BuffType,TempType>::iof(cExecValue)));
	}
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename pop>
void GndSumPopXBFeVt<pxt,pop>::execAnew()
{
	WatchError
	cExecValue = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
		cExecValue += mPxRecs[tPos]->CurrData();
	this->mValueRec->initCurr(mBind.iof(tc<BuffType,TempType>::iof(cExecValue)));
	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename pop>
void GndSumPopXBFeVt<pxt,pop>::simulAnew()
{
	WatchError
	BuffType tSimulValue = 0;
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
		tSimulValue += mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());
	this->mValueRec->updtNext(this->mTermSys.SimulClk(), mBind.iof(tc<BuffType,TempType>::iof(tSimulValue)));
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
void GndSumPopXBFeVt<pxt,pop>::undoEval(Pos const thePos)
{
	WatchError
	cExecValue -= mPxRecs[thePos]->PrevData(this->mTermSys.ExecClk());
	CatchError
}
#endif	//CompLazy



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename pop>
void GndSumPopXBFeVt<pxt,pop>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		if (!this->mTermSys.chkExecMode(SwapProp)
					|| this->mExecChgdPrms.tagCount() != this->mTermSys.ExecAsgnVars().tagCount())
		{
			for(Idx tIdx = 0; tIdx < this->mExecChgdPrms.tagCount(); ++tIdx)
			{
				Pos const tPos = this->mExecChgdPrms.serial(tIdx);
				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
					cExecValue += tPxRec->CurrBuff - tPxRec->PrevBuff;
			}
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(), mBind.iof(tc<BuffType,TempType>::iof(cExecValue)));
		}
		this->runPostExecIncr();
	}
	#endif	//ExecUpwd
	#if ExecDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif	//CompLazy
		if (this->needExecCandComp()) this->listCandParams();
		if (this->mBlkCandPrms->itemCount() && (!this->mTermSys.chkExecMode(SwapProp)
					|| this->mBlkCandPrms->itemCount() != this->mTermSys.ExecAsgnVars().tagCount()))
		{
			for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkCandPrms->item(tIdx);
				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
					cExecValue += tPxRec->CurrBuff - tPxRec->PrevBuff;
			}
			this->mValueRec->updtCurr(this->mTermSys.ExecClk(), mBind.iof(tc<BuffType,TempType>::iof(cExecValue)));
		}
	#if CompLazy
	}
	else
	{
		if (this->needExecCandComp()) this->markCandParams();
		for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkCandPrms->item(tIdx);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
				cExecValue += tPxRec->CurrData();
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				cExecValue += tPxRec->CurrBuff - tPxRec->PrevBuff;
		}

		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos))
				cExecValue += tPxRec->CurrData();
			else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				cExecValue += tPxRec->CurrBuff - tPxRec->PrevBuff;
		}

		this->mValueRec->updtCurr(this->mTermSys.ExecClk(), mBind.iof(tc<BuffType,TempType>::iof(cExecValue)));
	}
	this->runPostExecIncr();
	#endif	//CompLazy
	#endif	//ExecDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename pop>
void GndSumPopXBFeVt<pxt,pop>::execBklg()
{
	WatchError
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			cExecValue += tPxRec->CurrData();
		else if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			cExecValue += tPxRec->CurrBuff - tPxRec->PrevBuff;
	}

	this->mValueRec->updtCurr(this->mTermSys.ExecClk(), mBind.iof(tc<BuffType,TempType>::iof(cExecValue)));
	this->runPostExecBklg();
	CatchError
}
#endif	//CompLazy



/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename pop>
void GndSumPopXBFeVt<pxt,pop>::simulIncr()
{
	WatchError
	#if SimulUpwd
	if (this->mSimulChgdPrms.tagCount())
	{
		if (!this->mTermSys.chkSimulMode(SwapProp)
					|| this->mSimulChgdPrms.tagCount() != this->mTermSys.SimulAsgnVars().tagCount())
		{
			BuffType tSimulValue = cExecValue;
			for(Idx tIdx = 0; tIdx < this->mSimulChgdPrms.tagCount(); ++tIdx)
			{
				Pos const tPos = this->mSimulChgdPrms.serial(tIdx);
				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->NextDiff(this->mTermSys.SimulClk()))
					tSimulValue += tPxRec->NextBuff - tPxRec->CurrBuff;
			}
			this->mValueRec->updtNext(this->mTermSys.SimulClk(), mBind.iof(tc<BuffType,TempType>::iof(tSimulValue)));
		}
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

		if (this->mTermSys.chkSimulMode(SwapProp))
		{
			#if SimulFixedFlexi
			if (this->mBlkFixedPrms->itemCount() + this->mBlkFlexiPrms->itemCount() ==
					this->mTermSys.SimulAsgnVars().tagCount()) return;
			#elif SimulFixedOnly
			if (this->mBlkFixedPrms->itemCount() == this->mTermSys.SimulAsgnVars().tagCount())
				return;
			#elif SimulFlexiOnly
			if (this->mBlkFlexiPrms->itemCount() == this->mTermSys.SimulAsgnVars().tagCount())
				return;
			#endif
		}

		#if SimulFixed
		if (this->needSimulCacheComp())
		{
			cSimulValue = cExecValue;
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				cSimulValue -= mPxRecs[tPos]->CurrData();
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
			BuffType tSimulValue = cSimulValue;
			#else
			BuffType tSimulValue = cExecValue;
			#endif

			#if SimulFixed
			for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkFixedPrms->item(tIdx);
				Term::performSimulIncr(this->mPrmTerms[tPos]);
				tSimulValue += mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
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
					tSimulValue += tPxRec->NextBuff - tPxRec->CurrBuff;
			}
			#endif//SimulFlexi

			this->mValueRec->updtNext(this->mTermSys.SimulClk(), mBind.iof(tc<BuffType,TempType>::iof(tSimulValue)));
		}
	#if CompLazy
	}
	else	//	backlog
	{
		#if SimulFlexi
		if (this->needSimulFlexiComp()) this->listFlexiParams();
		#endif
		#if SimulFixed
		if (this->needSimulFixedComp())	this->markFixedParams();
		#endif

		if (this->needSimulCacheComp())
		{
			if (!this->chgdEmulClk())
			{
				cSimulValue = cEmulValue;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					cSimulValue -= mPxRecs[tPos]->LateData(this->mTermSys.EmulClk());
				}
				#endif//SimulFixed
			}
			else
			{
				cSimulValue = cExecValue;
				#if SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
				{
					Pos const tPos = this->mBlkFixedPrms->item(tIdx);
					if (!this->mEvalUndonePrms->tagged(tPos))
						cSimulValue -= mPxRecs[tPos]->CurrData();
				}
				#endif//SimulFixed
				for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
				{
					Pos const tPos = this->mBacklogPrms.serial(tIdx);
					#if SimulFixed
					if (this->mLblFixedPrms.tagged(tPos)) continue;
					#endif//SimulFixed
					Term::performEmulBklg(this->mPrmTerms[tPos]);
					EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

					if (this->mEvalUndonePrms->tagged(tPos))
						cSimulValue += tPxRec->LateData(this->mTermSys.EmulClk());	//	late data, not buff.
					else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
						cSimulValue += tPxRec->LateBuff - tPxRec->CurrBuff;
				}
			}
		}

		BuffType tSimulValue = cSimulValue;

		#if SimulFixed
		for(Idx tIdx = 0; tIdx < this->mBlkFixedPrms->itemCount(); ++tIdx)
		{
			Pos const tPos = this->mBlkFixedPrms->item(tIdx);
			Term::performSimulIncr(this->mPrmTerms[tPos]);
			tSimulValue += mPxRecs[tPos]->NextData(this->mTermSys.SimulClk());	//not NextBuff!
		}
		#endif //SimulFixed

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
				tSimulValue += tPxRec->NextData(this->mTermSys.SimulClk()) -
							tPxRec->LateData(this->mTermSys.EmulClk());
		}
		#endif//SimulFlexi

		this->mValueRec->updtNext(this->mTermSys.SimulClk(), mBind.iof(tc<BuffType,TempType>::iof(tSimulValue)));
	}
	#endif	//	CompLazy
	#endif	//	SimulDnwd
	CatchError
}



#if CompLazy
/*!
	Compute the term in simulation mode.
*/
template <typename pxt, typename pop>
void GndSumPopXBFeVt<pxt,pop>::emulBklg()
{
	WatchError
	cEmulValue = cExecValue;
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performEmulBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos))
			cEmulValue += tPxRec->LateData(this->mTermSys.EmulClk());
		else if (tPxRec->LateDiff(this->mTermSys.EmulClk()))
			cEmulValue += tPxRec->LateBuff - tPxRec->CurrBuff;
	}
	this->mValueRec->updtLate(this->mTermSys.EmulClk(), mBind.iof(tc<BuffType,TempType>::iof(cEmulValue)));
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif//GndSumPopXBFeVtTccIncluded
