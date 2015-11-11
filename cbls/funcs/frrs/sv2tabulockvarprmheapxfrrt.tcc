/*!
	@file sv2tabulockvarprmheapxfrrt.tcc
	@brief The prototype file for Sv2TabuLockVarPrmHeapXFrRt template class.
	@details This is the prototype file for Sv2TabuLockVarPrmHeapXFrRt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef Sv2TabuLockVarPrmHeapXFrRtTccIncluded
#define Sv2TabuLockVarPrmHeapXFrRtTccIncluded



#include "cbls/funcs/frrs/frrt.tcc"
#include "cbls/funcs/opfns/idx.hh"
#include "cbls/tabus/idx.hh"



openKangarooSpace



/*!
	@class Sv2TabuLockVarPrmHeapXFrRt
	@brief A class to represent heaps of variables mapped to parameter values/metrics.
	@details This class represents heaps of variables mapped to parameter values/metrics.
*/
template <typename pxt, typename fmt, Ord theOrd>
class Sv2TabuLockVarPrmHeapXFrRt : public FrRt<fmt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys, Prm * thePrms, Hdl * varHdls, Dim const PrmCount);	//!< Definition.

		static Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const & cast(Term const & theTerm);	//!< Perform casting.
		static Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const * cast(Term const * theTerm);	//!< Perform casting.
		static Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> & cast(Term & theTerm);				//!< Perform casting.
		static Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);				//!< Suits casting?
		static Bll suit(Term const * theTerm);				//!< Suits casting?
		static Bll suit(Term & theTerm);					//!< Suits casting?
		static Bll suit(Term * theTerm);					//!< Suits casting?

		//! @}

		virtual Hdl findHdl(Pos const thePos) const;		//!< Get the handle for the pos.
		virtual Pos beginRank() const;						//!< Get the begin var.
		virtual Pos endRank() const;						//!< Get the end var.
		virtual Dim rankCount() const;						//!< Get the rank var count.
		virtual Pos moveRank(Pos const thePos) const;		//!< Get the next var.
		virtual Pos findRank(Idx const theIdx) const;		//!< Get the indexed rank.
		virtual Pos randRank(Rnd & theRand) const;			//!< Get a random rank.

		virtual void computeLockEffect();					//!< Compute lock effect.
		virtual Bll careLockEffect() const;					//!< Care for lock effect.
		virtual void computeTabuEffect();					//!< Compute tabu effect.
		virtual Typ careTabuEffect() const;					//!< Care for tabu effect.

	private:

		Sv2TabuLockVarPrmHeapXFrRt(Fss const theFss, Hdl const hdlSys,
					Prm * thePrms, Hdl * varHdls, Dim const PrmCount);							//!< Constructor.
		Sv2TabuLockVarPrmHeapXFrRt(Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const & that);	//!< Duplicator.
		Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const & operator =
					(Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const & that);					//!< Assigner.
		~Sv2TabuLockVarPrmHeapXFrRt();															//!< Destructor.

		virtual void compConst();				//!< Compute the term.
		virtual void execAnew();				//!< Execute the term.
		virtual void execIncr();				//!< Execute the term.
		#if CompLazy
		virtual void execBklg();				//!< Execute the term.
		virtual void undoEval(Pos const thePos);//!< Perform eval undo.
		#endif

		#if VarStateArray
		virtual void setupComputation();		//!< Set up for computation.
		b1<Pos, kmm> const * 	mVarHdlPoss;	//!< Variable handle to position array mapping.
		#else
		hmap<Hdl, Pos, nmmh> const	mVarHdlPoss;//!< Variable handle to parameter position mapping.
		#endif

		#if CompLazy
		ll<Pos,kmm>				mLazyTabuLock;	//!< Defered tabu and lock updates.
		#endif //CompLazy
		Lock const & 			mSysLock;		//!< System's lock.
		Sv2Tabu const &			mSysTabu;		//!< System's single tabu.

		typedef typename DataStub<fmt>::TempBuff  htp;	//!< Heap data type.

		typedef OrdStub<theOrd,htp,Bll> hos;	//!< Heap ordering stub.
		typedef typename hos::InvOp hop;		//!< Heap ordering operator.

		b1<Hdl, kmm>				 mVarHdls;	//!< Variable handles.
		b1<EvalRec<pxt> const *,kmm> mPxRecs;	//!< Parameter records.
		qhp<htp, Pos, hop, kmm>      mPrmHeap; 	//!< The heap holding metrics.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Bll Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Bll Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Bll Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Bll Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const &
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const *
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> &
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> *
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> *>(theTerm);
	CatchError
}



/*!
	Refer to a sv2tabulockvarprmheapxfrrt
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> &
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a sv2tabulockvarprmheapxfrrt.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> *
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a sv2tabulockvarprmheapxfrrt
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const &
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a sv2tabulockvarprmheapxfrrt.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const *
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	Find the handle for the parameter position.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Hdl Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::findHdl(Pos const thePos) const
{
	WatchError
	return this->mVarHdls[thePos];
	CatchError
}



/*!
	Get the begin rank var.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Pos Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::beginRank() const
{
	WatchError
	Itr tItr = mPrmHeap.beginPeak();
	return (tItr == mPrmHeap.endPeak() ? InvPos : mPrmHeap.serial(tItr));
	CatchError
}


/*!
	Get the end rank var.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Pos Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::endRank() const
{
	WatchError
	return InvPos;
	CatchError
}


/*!
	Get the next var of the heap.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Pos Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::moveRank(Pos const thePos) const
{
	WatchError
	Itr tItr = mPrmHeap.movePeak(mPrmHeap.findItr(thePos));
	return (tItr == mPrmHeap.endPeak() ? InvPos : mPrmHeap.serial(tItr));
	CatchError
}


/*!
	Return the number of peaks in the heap.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Dim Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::rankCount() const
{
	WatchError
	return mPrmHeap.peakCount();
	CatchError
}



/*!
	Find a given peak of the heap
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Pos Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::findRank(Idx const theIdx) const
{
	WatchError
	Itr tItr = mPrmHeap.findPeakItr(theIdx);
	return (tItr == mPrmHeap.endPeak() ? InvPos : mPrmHeap.serial(tItr));
	CatchError
}



/*!
	Return a random peak of the heap.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Pos Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::randRank(Rnd & theRnd) const
{
	WatchError
	Itr tItr = mPrmHeap.randPeakItr(theRnd);
	return (tItr == mPrmHeap.endPeak() ? InvPos : mPrmHeap.serial(tItr));
	CatchError
}




/*!
	Define a sv2tabulockvarprmheapxfrrt.
*/
template <typename pxt, typename fmt, Ord theOrd>
Hdl Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::def(Fss const theFss, Hdl const hdlSys,
				Prm * thePrms, Hdl * varHdls, Dim const PrmCount)
{
	WatchError
	Wchk(PrmCount < 2 || PrmCount > MaxDim) Wtxt(eParamCount2(2, MaxDim));

	Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> * tFrR =
		new Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>(theFss, hdlSys, thePrms, varHdls, PrmCount);
	Hdl const tHdl = tFrR->defSysFunc();
	if (tHdl != InvHdl) { delete tFrR; return tHdl; }

	EvalTbl<pxt> const & tPxtTbl = EvalTbl<pxt>::refc(hdlSys);

	b1<Term *, kmm> const & tPrmTerms = tFrR->mPrmTerms;
	b1<Pss,kmm> const & tPrmSpecs = tFrR->mPrmSpecs;

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		Loc const tPxLoc = getPxLoc(theFss, tPrmTerms[tPos],tPrmSpecs[tPos]);
		tFrR->mPxRecs[tPos] = tPxtTbl.ptrcEvalRec(tPxLoc);
	}

	tFrR->performCompConst();
	tFrR->defSysRoot();
	return tFrR->TermHdl;
	CatchError
}



/*!
	The constructor.
*/
template <typename pxt, typename fmt, Ord theOrd>
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::Sv2TabuLockVarPrmHeapXFrRt(Fss const theFss, Hdl const hdlSys,
			Prm * thePrms, Hdl * varHdls, Dim const PrmCount) : FrRt<fmt>(hdlSys, PrmCount)
			#if VarStateArray
			, mVarHdlPoss(Null)
			#else
			, mVarHdlPoss(PrmCount)
			#endif
			#if CompLazy
			, mLazyTabuLock(PrmCount)
			#endif
			, mSysLock(Lock::refc(hdlSys))
			, mSysTabu(Sv2Tabu::refc(hdlSys))
			, mVarHdls(varHdls, PrmCount), mPxRecs(PrmCount)
			, mPrmHeap(PrmCount)
{
	WatchError
	this->setTermCls(TermStub< Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Ordered);
	this->setTermHvl(this->calcTermHvl());
	#if !VarStateArray
	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
		ccast<hmap<Hdl, Pos, nmmh> &>(mVarHdlPoss).insert(varHdls[tPos], tPos);
	#endif
	CatchError
}



/*!
	The destructor.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::~Sv2TabuLockVarPrmHeapXFrRt()
{
	WatchError
	#if VarStateArray
	if (mVarHdlPoss) delete mVarHdlPoss;
	#endif
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename fmt, Ord theOrd>
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::Sv2TabuLockVarPrmHeapXFrRt
		(Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const & that) : FrRt<fmt>(that),
		mSysLock(that.mSysLock), mSysTabu(that.mSysTabu)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename pxt, typename fmt, Ord theOrd>
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const &
Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::operator =
	(Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}


#if VarStateArray
/*!
	Set up for downward computation.
*/
template <typename pxt, typename fmt, Ord theOrd>
void Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::setupComputation()
{
	WatchError
		if (!mVarHdlPoss)
		{
			mVarHdlPoss = new b1<Pos, kmm>(this->mTermSys.varCount());
			for(Hdl tHdl = 0; tHdl < this->mTermSys.varCount(); ++tHdl)
				ccast<b1<Pos, kmm> *>(mVarHdlPoss)->item(tHdl) = InvPos;
			for(Pos tPos = 0; tPos < mVarHdls.itemCount(); ++tPos)
				ccast<b1<Pos, kmm> *>(mVarHdlPoss)->item(mVarHdls[tPos]) = tPos;
		}
		FrRt<fmt>::setupComputation();
	CatchError
}
#endif



/*!
	Compute the term.
*/
template <typename pxt, typename fmt, Ord theOrd>
void Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::compConst()
{
	WatchError
	if (!this->updatable())
		for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
			mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt, Ord theOrd>
void Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::execAnew()
{
	WatchError
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if ExecDnwd
		Term::performExecAnew(this->mPrmTerms[tPos]);
		#endif
		Hdl tVarHdl = mVarHdls[tPos];
		if (this->mTermSys.refcVar(tVarHdl).locked())
			mPrmHeap.alter(tPos, hos::Last0);
		else if (mSysTabu.state(tVarHdl))
			mPrmHeap.alter(tPos, hos::Last1);
		else
			mPrmHeap.alter(tPos,
				tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
	}
	#if CompLazy
	mLazyTabuLock.sweep(this->mTermSys.ExecClk());
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
template <typename pxt, typename fmt, Ord theOrd>
void Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::undoEval(Pos const thePos)
{
	WatchError
	//	nothing to be done.
	CatchError
}
#endif


/*!
	Compute the term in execution mode.
*/
template <typename pxt, typename fmt, Ord theOrd>
void Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::execIncr()
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
				Hdl tVarHdl = mVarHdls[tPos];
				if (this->mTermSys.refcVar(tVarHdl).locked())
					mPrmHeap.alter(tPos, hos::Last0);
				else if (mSysTabu.state(tVarHdl))
					mPrmHeap.alter(tPos, hos::Last1);
				else
					mPrmHeap.alter(tPos,
						tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
			}
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
			for(Idx tIdx = 0; tIdx < this->mBlkCandPrms->itemCount(); ++tIdx)
			{
				Pos const tPos = this->mBlkCandPrms->item(tIdx);
				Term::performExecIncr(this->mPrmTerms[tPos]);
				EvalRec<pxt> const * tPxRec = mPxRecs[tPos];
				if (tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				{
					Hdl tVarHdl = mVarHdls[tPos];
					if (this->mTermSys.refcVar(tVarHdl).locked())
						mPrmHeap.alter(tPos, hos::Last0);
					else if (mSysTabu.state(tVarHdl))
						mPrmHeap.alter(tPos, hos::Last1);
					else
						mPrmHeap.alter(tPos,
							tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
				}
			}
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
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos) ||
					tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			{
				Hdl tVarHdl = mVarHdls[tPos];
				if (this->mTermSys.refcVar(tVarHdl).locked())
					mPrmHeap.alter(tPos, hos::Last0);
				else if (mSysTabu.state(tVarHdl))
					mPrmHeap.alter(tPos, hos::Last1);
				else
					mPrmHeap.alter(tPos,
						tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
			}
		}

		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;

			Term::performExecBklg(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos) ||
					tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			{
				Hdl tVarHdl = mVarHdls[tPos];
				if (this->mTermSys.refcVar(tVarHdl).locked())
					mPrmHeap.alter(tPos, hos::Last0);
				else if (mSysTabu.state(tVarHdl))
					mPrmHeap.alter(tPos, hos::Last1);
				else
					mPrmHeap.alter(tPos,
						tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
			}
		}
		for(Idx tIdx = 0; tIdx < mLazyTabuLock.tagCount(); ++tIdx)
		{
			Pos const tPos = mLazyTabuLock.serial(tIdx);

			Hdl tVarHdl = mVarHdls[tPos];
			if (this->mTermSys.refcVar(tVarHdl).locked())
				mPrmHeap.alter(tPos, hos::Last0);
			else if (mSysTabu.state(tVarHdl))
				mPrmHeap.alter(tPos, hos::Last1);
			else
				mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
		}
		mLazyTabuLock.sweep(this->mTermSys.ExecClk());
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
template <typename pxt, typename fmt, Ord theOrd>
void Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::execBklg()
{
	WatchError
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performExecBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos) ||
				tPxRec->PrevDiff(this->mTermSys.ExecClk()))
		{
			Hdl tVarHdl = mVarHdls[tPos];
			if (this->mTermSys.refcVar(tVarHdl).locked())
				mPrmHeap.alter(tPos, hos::Last0);
			else if (mSysTabu.state(tVarHdl))
				mPrmHeap.alter(tPos, hos::Last1);
			else
				mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
		}
	}
	for(Idx tIdx = 0; tIdx < mLazyTabuLock.tagCount(); ++tIdx)
	{
		Pos const tPos = mLazyTabuLock.serial(tIdx);

		Hdl tVarHdl = mVarHdls[tPos];
		if (this->mTermSys.refcVar(tVarHdl).locked())
			mPrmHeap.alter(tPos, hos::Last0);
		else if (mSysTabu.state(tVarHdl))
			mPrmHeap.alter(tPos, hos::Last1);
		else
			mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
	}
	mLazyTabuLock.sweep(this->mTermSys.ExecClk());
	this->runPostExecBklg();
	CatchError
}
#endif	//CompLazy


/*!
	Apply the effect of the locked variables on the varorder.
*/
template <typename pxt, typename fmt, Ord theOrd>
void Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::computeLockEffect()
{
	WatchError
	b1<Hdl, xmm> const & tLockUpdates = mSysLock.Updates();
	for(Idx tIdx = 0; tIdx < tLockUpdates.itemCount(); tIdx++)
	{
		Hdl const tVarHdl = tLockUpdates[tIdx];
		#if VarStateArray
		Pos tPos = mVarHdlPoss->item(tVarHdl);
		if (tPos == InvPos) continue;
		#else
		Itr tItr = mVarHdlPoss.findItr(tVarHdl);
		if (tItr == InvItr) continue;
		Pos tPos = mVarHdlPoss.item(tItr);
		#endif

		#if CompLazy
		if (this->backlog())
			mLazyTabuLock.tagBll(tPos);
		else
		#endif
			if (this->mTermSys.refcVar(tVarHdl).locked())
				mPrmHeap.alter(tPos, hos::Last0);
			else if (mSysTabu.state(tVarHdl))
				mPrmHeap.alter(tPos, hos::Last1);
			else
				mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
	}
	CatchError
}


/*!
	Care lock effect.
*/
template <typename pxt, typename fmt, Ord theOrd>
Bll Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::careLockEffect() const
{
	WatchError
	return true;
	CatchError
}



/*!
	Apply the effect of the tabooed variables on the varorder.
*/
template <typename pxt, typename fmt, Ord theOrd>
void Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::computeTabuEffect()
{
	WatchError
	b1<Hdl, xmm> const & tTabuUpdates = mSysTabu.Updates();
	for(Idx tIdx = 0; tIdx < tTabuUpdates.itemCount(); tIdx++)
	{
		Hdl const tVarHdl = tTabuUpdates[tIdx];
		#if VarStateArray
		Pos tPos = mVarHdlPoss->item(tVarHdl);
		if (tPos == InvPos) continue;
		#else
		Itr tItr = mVarHdlPoss.findItr(tVarHdl);
		if (tItr == InvItr) continue;
		Pos tPos = mVarHdlPoss.item(tItr);
		#endif

		#if CompLazy
		if (this->backlog())
			mLazyTabuLock.tagBll(tPos);
		else
		#endif
			if (this->mTermSys.refcVar(tVarHdl).locked())
				mPrmHeap.alter(tPos, hos::Last0);
			else if (mSysTabu.state(tVarHdl))
				mPrmHeap.alter(tPos, hos::Last1);
			else
				mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
	}
	CatchError
}


/*!
	Care tabu effect.
*/
template <typename pxt, typename fmt, Ord theOrd>
Typ Sv2TabuLockVarPrmHeapXFrRt<pxt,fmt,theOrd>::careTabuEffect() const
{
	WatchError
	return TabuStub<Sv2Tabu>::TabuTyp;
	CatchError
}



closeKangarooSpace


#endif //Sv2TabuLockVarPrmHeapXFrRtTccIncluded
