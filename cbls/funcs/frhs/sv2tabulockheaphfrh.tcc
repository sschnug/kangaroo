/*!
	@file s2tabulockheaphfrh.tcc
	@brief The prototype file for Sv2TabuLockHeapHFrH template class.
	@details This is the prototype file for Sv2TabuLockHeapHFrH template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef Sv2TabuLockHeapHFrHTccIncluded
#define Sv2TabuLockHeapHFrHTccIncluded



#include "cbls/funcs/frhs/frht.tcc"
#include "cbls/funcs/opfns/idx.hh"
#include "cbls/tabus/idx.hh"



openKangarooSpace



/*!
	@class Sv2TabuLockHeapHFrH
	@brief A class to represent heaps of variable and hints respecting both lock and single tabu.
	@details This class represents heaps variable and hints respecting both lock and single tabu.
*/
template <typename pmt, typename fmt, Ord theOrd>
class Sv2TabuLockHeapHFrH : public FrHt<fmt>
{
	public:
		static Hdl def(Hdl const hdlSys, Prm const & thePrm);											//!< Definition.

		static Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const & cast(Term const & theTerm);	//!< Perform casting.
		static Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const * cast(Term const * theTerm);	//!< Perform casting.
		static Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> & cast(Term & theTerm);				//!< Perform casting.
		static Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);				//!< Suits casting?
		static Bll suit(Term const * theTerm);				//!< Suits casting?
		static Bll suit(Term & theTerm);					//!< Suits casting?
		static Bll suit(Term * theTerm);					//!< Suits casting?

		//! @}

		virtual Sqn beginRank() const;						//!< Get the begin var.
		virtual Sqn endRank() const;						//!< Get the end var.
		virtual Dim rankCount() const;						//!< Get the rank var count.
		virtual Sqn moveRank(Sqn const theSqn) const;		//!< Get the next var.
		virtual Sqn findRank(Idx const theIdx) const;		//!< Get the indexed rank.
		virtual Sqn randRank(Rnd & theRand) const;			//!< Get a random rank.

		virtual void computeLockEffect();					//!< Compute lock effect.
		virtual Bll careLockEffect() const;					//!< Care for lock effect.
		virtual void computeTabuEffect();					//!< Compute tabu effect.
		virtual Typ careTabuEffect() const;					//!< Care for tabu effect.
		#if ExecUpwd
		virtual Bll careFuncVarSqn() const;					//!< Care func var sqn mapping?
		#endif

	private:

		Sv2TabuLockHeapHFrH(Hdl const hdlSys, Prm & thePrm);					//!< Constructor.
		Sv2TabuLockHeapHFrH(Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const & that);//!< Duplicator.
		Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const & operator =
					(Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const & that);		//!< Assigner.
		~Sv2TabuLockHeapHFrH();												//!< Destructor.

		virtual void compConst();				//!< Compute the term.
		virtual void execAnew();				//!< Execute the term.
		virtual void execIncr();				//!< Execute the term.
		#if CompLazy
		virtual void execBklg();				//!< Execute the term.
		virtual void undoHint(Pos const thePos);//!< Perform hint undo.
		#endif

		#if CompLazy
		ll<Sqn,kmm>	*			mLazyTabuLock;	//!< Defered tabu and lock updates.
		#endif
		Lock const & 			mSysLock;		//!< System's lock.
		Sv2Tabu const &			mSysTabu;		//!< System's single tabu.

		typedef typename DataStub<fmt>::TempBuff  htp;	//!< Heap data type.

		typedef OrdStub<theOrd,htp,Bll> hos;	//!< Heap ordering stub.
		typedef typename hos::InvOp hop;		//!< Heap ordering operator.

		qhp<htp, Sqn, hop, kmm> *   mVarHeap; 	//!< The heap holding metrics.
		HintRec<pmt> const * 		mPhRec;		//!< The parameter hint.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Bll Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Bll Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Bll Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Bll Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const & Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const * Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> & Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> * Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> *>(theTerm);
	CatchError
}



/*!
	Refer to a s2tabulockheaphfrh
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> & Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a s2tabulockheaphfrh.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> * Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a s2tabulockheaphfrh
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const & Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a s2tabulockheaphfrh.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const * Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::~Sv2TabuLockHeapHFrH()
{
	WatchError
	#if CompLazy
	if (mLazyTabuLock) delete mLazyTabuLock;
	#endif
	if (mVarHeap) delete mVarHeap;
	CatchError
}



/*!
	Get the begin rank var.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sqn Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::beginRank() const
{
	WatchError
	Itr tItr = mVarHeap->beginPeak();
	return (tItr == mVarHeap->endPeak() ? InvSqn : mVarHeap->serial(tItr));
	CatchError
}


/*!
	Get the end rank var.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sqn Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::endRank() const
{
	WatchError
	return InvSqn;
	CatchError
}


/*!
	Get the next var of the heap.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sqn Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::moveRank(Sqn const theSqn) const
{
	WatchError
	Itr tItr = mVarHeap->movePeak(mVarHeap->findItr(theSqn));
	return (tItr == mVarHeap->endPeak() ? InvSqn : mVarHeap->serial(tItr));
	CatchError
}


/*!
	Return the number of peaks in the heap.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Dim Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::rankCount() const
{
	WatchError
	return mVarHeap->peakCount();
	CatchError
}



/*!
	Find a given peak of the heap
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sqn Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::findRank(Idx const theIdx) const
{
	WatchError
	Itr tItr = mVarHeap->findPeakItr(theIdx);
	return (tItr == mVarHeap->endPeak() ? InvSqn : mVarHeap->serial(tItr));
	CatchError
}



/*!
	Return a random peak of the heap.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sqn Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::randRank(Rnd & theRnd) const
{
	WatchError
	Itr tItr = mVarHeap->randPeakItr(theRnd);
	return (tItr == mVarHeap->endPeak() ? InvSqn : mVarHeap->serial(tItr));
	CatchError
}



/*!
	Define a s2tabulockheaphfrh.
*/
template <typename pmt, typename fmt, Ord theOrd>
Hdl Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::def(Hdl const hdlSys, Prm const & thePrm)
{
	WatchError
	Prm tPrm = thePrm;
	Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> * tFrH = new Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>(hdlSys, tPrm);
	Hdl const tHdl = tFrH->defSysFunc();
	if (tHdl != InvHdl) { delete tFrH; return tHdl; }

	#if CompLazy
	tFrH->mLazyTabuLock = new ll<Sqn,kmm>(tFrH->FuncVars.itemCount());
	#endif

	tFrH->mVarHeap = new qhp<htp, Sqn, hop,kmm>(tFrH->FuncVars.itemCount());

	HintTbl<pmt> const & tPhTbl = HintTbl<pmt>::refc(hdlSys);

	b1<Term *, kmm> const & tPrmTerms = tFrH->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFrH->mPrmSpecs;

	Loc const tRankLoc = getRankLoc(tPrmTerms[0],tPrmSpecs[0]);
	tFrH->mPhRec = tPhTbl.ptrcHintRec(tRankLoc);

	tFrH->performCompConst();
	tFrH->defSysRoot();
	return tFrH->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
template <typename pmt, typename fmt, Ord theOrd>
Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::Sv2TabuLockHeapHFrH(Hdl const hdlSys, Prm & thePrm) : FrHt<fmt>(hdlSys, 1)
		#if CompLazy
		, mLazyTabuLock(Null)
		#endif
		, mSysLock(Lock::refc(hdlSys))
		, mSysTabu(Sv2Tabu::refc(hdlSys))
		, mVarHeap(Null)
{
	WatchError
	this->setTermCls(TermStub< Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> >::TermCls);
	this->setParams(DfltFsm, thePrm.ptrm(), 1, Ordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pmt, typename fmt, Ord theOrd>
Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::Sv2TabuLockHeapHFrH(Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const & that) :
	FrHt<fmt>(that), mSysLock(that.mSysLock), mSysTabu(that.mSysTabu)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename pmt, typename fmt, Ord theOrd>
Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const & Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::operator =
		(Sv2TabuLockHeapHFrH<pmt,fmt,theOrd> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template <typename pmt, typename fmt, Ord theOrd>
void Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::compConst()
{
	WatchError
	if (!this->updatable())
		for(Sqn tPrmSqn = 0; tPrmSqn < mPhRec->HintFlds.itemCount(); ++tPrmSqn)
			mVarHeap->alter( this->PrmVars[0][tPrmSqn],
					tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pmt, typename fmt, Ord theOrd>
void Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::execAnew()
{
	WatchError
	#if ExecDnwd
	Term::performExecAnew(this->mPrmTerms[0]);
	#endif

	for(Sqn tPrmSqn = 0; tPrmSqn < mPhRec->HintFlds.itemCount(); ++tPrmSqn)
	{
		Sqn const tSqn = this->PrmVars[0][tPrmSqn];
		Warn(tSqn != tPrmSqn, eIndexMismatch);	// because only one parameter

		Hdl tVarHdl = this->FuncVars[tSqn];
		if (this->mTermSys.refcVar(tVarHdl).locked())
			mVarHeap->alter(tSqn, hos::Last0);
		else if (mSysTabu.state(tVarHdl))
			mVarHeap->alter(tSqn, hos::Last1);
		else
			mVarHeap->alter(tSqn,
				tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
	}
	#if CompLazy
	mLazyTabuLock->sweep(this->mTermSys.ExecClk());
	#endif

	#if ExecUpwdLazy
	this->runPostExecAnew();
	#endif
	CatchError
}



#if CompLazy
/*!
	Perform eval undo operation.
*/
template <typename pmt, typename fmt, Ord theOrd>
void Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::undoHint(Pos const thePos)
{
	WatchError
	//	there is only one parameter
	for (Idx tIdx = 0; tIdx < mPhRec->DiffSqns.itemCount(); ++tIdx)
	{
		Sqn tPrmSqn =  mPhRec->DiffSqns[tIdx];
		this->mHintUndonePrms->list(thePos).tagBll(tPrmSqn);
	}
	CatchError
}
#endif


/*!
	Compute the term in execution mode.
*/
template <typename pmt, typename fmt, Ord theOrd>
void Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		for (Idx tIdx = 0; tIdx < mPhRec->DiffSqns.itemCount(); ++tIdx)
		{
			Sqn const tPrmSqn =  mPhRec->DiffSqns[tIdx];
			Sqn const tSqn = this->PrmVars[0][tPrmSqn];
			Warn(tSqn != tPrmSqn, eIndexMismatch);	// because only one parameter

			Hdl tVarHdl = this->FuncVars[tSqn];
			if (this->mTermSys.refcVar(tVarHdl).locked())
				mVarHeap->alter(tSqn, hos::Last0);
			else if (mSysTabu.state(tVarHdl))
				mVarHeap->alter(tSqn, hos::Last1);
			else
				mVarHeap->alter(tSqn, tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
		}

		this->runPostExecIncr();
	}
	#endif
	#if ExecDnwd
	#if CompLazy
	if (!this->backlog())
	{
	#endif
		if (this->needExecCandComp()) this->listCandParams();
		if (this->mBlkCandPrms->itemCount())
		{
			Term::performExecIncr(this->mPrmTerms[0]);
			for (Idx tIdx = 0; tIdx < mPhRec->DiffSqns.itemCount(); ++tIdx)
			{
				Sqn const tPrmSqn =  mPhRec->DiffSqns[tIdx];
				Sqn const tSqn = this->PrmVars[0][tPrmSqn];
				Warn(tSqn != tPrmSqn, eIndexMismatch);	// because only one parameter

				Hdl tVarHdl = this->FuncVars[tSqn];
				if (this->mTermSys.refcVar(tVarHdl).locked())
					mVarHeap->alter(tSqn, hos::Last0);
				else if (mSysTabu.state(tVarHdl))
					mVarHeap->alter(tSqn, hos::Last1);
				else
					mVarHeap->alter(tSqn, tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
			}
		}
	#if CompLazy
	}
	else	//	backlog
	{
		if (this->needExecCandComp()) this->listCandParams();
		if (this->mBlkCandPrms->itemCount())
		{
			Term::performExecIncr(this->mPrmTerms[0]);
			for (Idx tIdx = 0; tIdx < mPhRec->DiffSqns.itemCount(); ++tIdx)
			{
				Sqn tPrmSqn =  mPhRec->DiffSqns[tIdx];
				Sqn tSqn = this->PrmVars[0][tPrmSqn];
				Warn(tSqn != tPrmSqn, eIndexMismatch);	// because only one parameter

				if (mLazyTabuLock->tagged(tSqn)) continue;
				if (!this->mHintUndonePrms->list(0).tagged(tPrmSqn))
				{
					Hdl tVarHdl = this->FuncVars[tSqn];
					if (this->mTermSys.refcVar(tVarHdl).locked())
						mVarHeap->alter(tSqn, hos::Last0);
					else if (mSysTabu.state(tVarHdl))
						mVarHeap->alter(tSqn, hos::Last1);
					else
						mVarHeap->alter(tSqn, tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
				}
			}
		}
		else //if (backlog())
		{
			Term::performExecBklg(this->mPrmTerms[0]);
			for (Idx tIdx = 0; tIdx < mPhRec->DiffSqns.itemCount(); ++tIdx)
			{
				Sqn tPrmSqn =  mPhRec->DiffSqns[tIdx];
				Sqn tSqn = this->PrmVars[0][tPrmSqn];
				Warn(tSqn != tPrmSqn, eIndexMismatch);	// because only one parameter

				if (mLazyTabuLock->tagged(tSqn)) continue;
				if (!this->mHintUndonePrms->list(0).tagged(tPrmSqn))
				{
					Hdl tVarHdl = this->FuncVars[tSqn];
					if (this->mTermSys.refcVar(tVarHdl).locked())
						mVarHeap->alter(tSqn, hos::Last0);
					else if (mSysTabu.state(tVarHdl))
						mVarHeap->alter(tSqn, hos::Last1);
					else
						mVarHeap->alter(tSqn, tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
				}
			}
		}
		for(Idx tIdx = 0; tIdx < this->mHintUndonePrms->list(0).tagCount(); ++tIdx)
		{
			Sqn const tPrmSqn = this->mHintUndonePrms->list(0)[tIdx];
			Sqn tSqn = this->PrmVars[0][tPrmSqn];
			Warn(tSqn != tPrmSqn, eIndexMismatch);	// because only one parameter

			if (mLazyTabuLock->tagged(tSqn)) continue;
			Hdl tVarHdl = this->FuncVars[tSqn];
			if (this->mTermSys.refcVar(tVarHdl).locked())
				mVarHeap->alter(tSqn, hos::Last0);
			else if (mSysTabu.state(tVarHdl))
				mVarHeap->alter(tSqn, hos::Last1);
			else
				mVarHeap->alter(tSqn, tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
		}
		for(Idx tIdx = 0; tIdx < mLazyTabuLock->tagCount(); ++tIdx)
		{
			Sqn const tSqn = mLazyTabuLock->serial(tIdx);
			Sqn tPrmSqn = tSqn;	//
			Warn(this->PrmVars[0][tSqn] != tPrmSqn, eIndexMismatch);	// because only one parameter

			Hdl tVarHdl = this->FuncVars[tSqn];
			if (this->mTermSys.refcVar(tVarHdl).locked())
				mVarHeap->alter(tSqn, hos::Last0);
			else if (mSysTabu.state(tVarHdl))
				mVarHeap->alter(tSqn, hos::Last1);
			else
				mVarHeap->alter(tSqn, tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
		}
		mLazyTabuLock->sweep(this->mTermSys.ExecClk());
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
template <typename pmt, typename fmt, Ord theOrd>
void Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::execBklg()
{
	WatchError
	Term::performExecBklg(this->mPrmTerms[0]);
	for (Idx tIdx = 0; tIdx < mPhRec->DiffSqns.itemCount(); ++tIdx)
	{
		Sqn tPrmSqn =  mPhRec->DiffSqns[tIdx];
		Sqn tSqn = this->PrmVars[0][tPrmSqn];
		Warn(tSqn != tPrmSqn, eIndexMismatch);	// because only one parameter

		if (mLazyTabuLock->tagged(tSqn)) continue;
		if (!this->mHintUndonePrms->list(0).tagged(tPrmSqn))
		{
			Hdl tVarHdl = this->FuncVars[tSqn];
			if (this->mTermSys.refcVar(tVarHdl).locked())
				mVarHeap->alter(tSqn, hos::Last0);
			else if (mSysTabu.state(tVarHdl))
				mVarHeap->alter(tSqn, hos::Last1);
			else
				mVarHeap->alter(tSqn, tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
		}
	}
	for(Idx tIdx = 0; tIdx < this->mHintUndonePrms->list(0).tagCount(); ++tIdx)
	{
		Sqn const tPrmSqn = this->mHintUndonePrms->list(0)[tIdx];
		Sqn tSqn = this->PrmVars[0][tPrmSqn];
		Warn(tSqn != tPrmSqn, eIndexMismatch);	// because only one parameter

		if (mLazyTabuLock->tagged(tSqn)) continue;
		Hdl tVarHdl = this->FuncVars[tSqn];
		if (this->mTermSys.refcVar(tVarHdl).locked())
			mVarHeap->alter(tSqn, hos::Last0);
		else if (mSysTabu.state(tVarHdl))
			mVarHeap->alter(tSqn, hos::Last1);
		else
			mVarHeap->alter(tSqn, tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
	}
	for(Idx tIdx = 0; tIdx < mLazyTabuLock->tagCount(); ++tIdx)
	{
		Sqn const tSqn = mLazyTabuLock->serial(tIdx);
		Sqn tPrmSqn = tSqn;	//
		Warn(this->PrmVars[0][tSqn] != tPrmSqn, eIndexMismatch);	// because only one parameter

		Hdl tVarHdl = this->FuncVars[tSqn];
		if (this->mTermSys.refcVar(tVarHdl).locked())
			mVarHeap->alter(tSqn, hos::Last0);
		else if (mSysTabu.state(tVarHdl))
			mVarHeap->alter(tSqn, hos::Last1);
		else
			mVarHeap->alter(tSqn, tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
	}
	mLazyTabuLock->sweep(this->mTermSys.ExecClk());
	this->runPostExecBklg();
	CatchError
}
#endif	//CompLazy


/*!
	Apply the effect of the locked variables on the varorder.
*/
template <typename pmt, typename fmt, Ord theOrd>
void Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::computeLockEffect()
{
	WatchError
	b1<Hdl, xmm> const & tLockUpdates = mSysLock.Updates();
	for(Idx tIdx = 0; tIdx < tLockUpdates.itemCount(); tIdx++)
	{
		Hdl const tVarHdl = tLockUpdates[tIdx];
		Sqn const tSqn = this->findVarSqn(tVarHdl);
		if (tSqn == InvSqn) continue;
		Sqn const tPrmSqn = tSqn;
		Warn(tSqn != this->PrmVars[0][tPrmSqn], eIndexMismatch);

		#if CompLazy
		if (this->backlog())
			mLazyTabuLock->tagBll(tSqn);
		else
		#endif
			if (this->mTermSys.refcVar(tVarHdl).locked())
				mVarHeap->alter(tSqn, hos::Last0);
			else if (mSysTabu.state(tVarHdl))
				mVarHeap->alter(tSqn, hos::Last1);
			else
				mVarHeap->alter(tSqn, tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
	}
	CatchError
}


/*!
	Care lock effect.
*/
template <typename pmt, typename fmt, Ord theOrd>
Bll Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::careLockEffect() const
{
	WatchError
	return true;
	CatchError
}



/*!
	Apply the effect of the tabooed variables on the varorder.
*/
template <typename pmt, typename fmt, Ord theOrd>
void Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::computeTabuEffect()
{
	WatchError
	b1<Hdl, xmm> const & tTabuUpdates = mSysTabu.Updates();
	for(Idx tIdx = 0; tIdx < tTabuUpdates.itemCount(); tIdx++)
	{
		Hdl const tVarHdl = tTabuUpdates[tIdx];
		Sqn const tSqn = this->findVarSqn(tVarHdl);
		if (tSqn == InvSqn) continue;
		Sqn const tPrmSqn = tSqn;
		Warn(tSqn != this->PrmVars[0][tPrmSqn], eIndexMismatch);

		#if CompLazy
		if (this->backlog())
			mLazyTabuLock->tagBll(tSqn);
		else
		#endif
			if (this->mTermSys.refcVar(tVarHdl).locked())
				mVarHeap->alter(tSqn, hos::Last0);
			else if (mSysTabu.state(tVarHdl))
				mVarHeap->alter(tSqn, hos::Last1);
			else
				mVarHeap->alter(tSqn, tc<pmt,htp>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
	}
	CatchError
}


/*!
	Care tabu effect.
*/
template <typename pmt, typename fmt, Ord theOrd>
Typ Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::careTabuEffect() const
{
	WatchError
	return TabuStub<Sv2Tabu>::TabuTyp;
	CatchError
}


#if ExecUpwd
/*!
	Care function variable sequent mapping.
*/
template <typename pmt, typename fmt, Ord theOrd>
Bll Sv2TabuLockHeapHFrH<pmt,fmt,theOrd>::careFuncVarSqn() const
{
	WatchError
	return true;
	CatchError
}
#endif


closeKangarooSpace


#endif //Sv2TabuLockHeapHFrHTccIncluded
