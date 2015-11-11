/*!
	@file heaphfrh.tcc
	@brief The prototype file for HeapHFrH template class.
	@details This is the prototype file for HeapHFrH template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef HeapHFrHTccIncluded
#define HeapHFrHTccIncluded



#include "cbls/funcs/frhs/frht.tcc"
#include "cbls/funcs/opfns/idx.hh"



openKangarooSpace



/*!
	@class HeapHFrH
	@brief A class to represent heaps of variable and hints.
	@details This class represents heaps variable and hints.
*/
template <typename pmt, typename fmt, Ord theOrd>
class HeapHFrH : public FrHt<fmt>
{
	public:
		static Hdl def(Hdl const hdlSys, Prm const & thePrm);								//!< Definition.

		static HeapHFrH<pmt,fmt,theOrd> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static HeapHFrH<pmt,fmt,theOrd> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static HeapHFrH<pmt,fmt,theOrd> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static HeapHFrH<pmt,fmt,theOrd> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static HeapHFrH<pmt,fmt,theOrd> const & cast(Term const & theTerm);	//!< Perform casting.
		static HeapHFrH<pmt,fmt,theOrd> const * cast(Term const * theTerm);	//!< Perform casting.
		static HeapHFrH<pmt,fmt,theOrd> & cast(Term & theTerm);				//!< Perform casting.
		static HeapHFrH<pmt,fmt,theOrd> * cast(Term * theTerm);				//!< Perform casting.

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

	private:

		HeapHFrH(Hdl const hdlSys, Prm & thePrm);			//!< Constructor.
		HeapHFrH(HeapHFrH<pmt,fmt,theOrd> const & that);	//!< Duplicator.
		HeapHFrH<pmt,fmt,theOrd> const & operator =
					(HeapHFrH<pmt,fmt,theOrd> const & that);//!< Assigner.
		~HeapHFrH();										//!< Destructor.

		virtual void compConst();				//!< Compute the term.
		virtual void execAnew();				//!< Execute the term.
		virtual void execIncr();				//!< Execute the term.
		#if CompLazy
		virtual void execBklg();				//!< Execute the term.
		virtual void undoHint(Pos const thePos);//!< Perform hint undo.
		#endif

		typedef OrdStub<theOrd,fmt,Bll> hos;	//!< Heap ordering stub.
		typedef typename hos::InvOp hop;		//!< Heap ordering operator.

		qhp<fmt, Sqn, hop, kmm> *   mVarHeap; 	//!< The heap holding metrics.
		HintRec<pmt> const * 		mPhRec;		//!< The parameter hint.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Bll HeapHFrH<pmt,fmt,theOrd>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< HeapHFrH<pmt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Bll HeapHFrH<pmt,fmt,theOrd>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< HeapHFrH<pmt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Bll HeapHFrH<pmt,fmt,theOrd>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< HeapHFrH<pmt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Bll HeapHFrH<pmt,fmt,theOrd>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< HeapHFrH<pmt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline HeapHFrH<pmt,fmt,theOrd> const & HeapHFrH<pmt,fmt,theOrd>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< HeapHFrH<pmt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<HeapHFrH<pmt,fmt,theOrd> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline HeapHFrH<pmt,fmt,theOrd> const * HeapHFrH<pmt,fmt,theOrd>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< HeapHFrH<pmt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<HeapHFrH<pmt,fmt,theOrd> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline HeapHFrH<pmt,fmt,theOrd> & HeapHFrH<pmt,fmt,theOrd>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< HeapHFrH<pmt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<HeapHFrH<pmt,fmt,theOrd> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline HeapHFrH<pmt,fmt,theOrd> * HeapHFrH<pmt,fmt,theOrd>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< HeapHFrH<pmt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<HeapHFrH<pmt,fmt,theOrd> *>(theTerm);
	CatchError
}



/*!
	Refer to a heaphfrh
*/
template <typename pmt, typename fmt, Ord theOrd>
inline HeapHFrH<pmt,fmt,theOrd> & HeapHFrH<pmt,fmt,theOrd>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a heaphfrh.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline HeapHFrH<pmt,fmt,theOrd> * HeapHFrH<pmt,fmt,theOrd>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a heaphfrh
*/
template <typename pmt, typename fmt, Ord theOrd>
inline HeapHFrH<pmt,fmt,theOrd> const & HeapHFrH<pmt,fmt,theOrd>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a heaphfrh.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline HeapHFrH<pmt,fmt,theOrd> const * HeapHFrH<pmt,fmt,theOrd>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline HeapHFrH<pmt,fmt,theOrd>::~HeapHFrH()
{
	WatchError
	if (mVarHeap) delete mVarHeap;
	CatchError
}



/*!
	Get the begin rank var.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sqn HeapHFrH<pmt,fmt,theOrd>::beginRank() const
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
inline Sqn HeapHFrH<pmt,fmt,theOrd>::endRank() const
{
	WatchError
	return InvSqn;
	CatchError
}


/*!
	Get the next var of the heap.
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sqn HeapHFrH<pmt,fmt,theOrd>::moveRank(Sqn const theSqn) const
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
inline Dim HeapHFrH<pmt,fmt,theOrd>::rankCount() const
{
	WatchError
	return mVarHeap->peakCount();
	CatchError
}



/*!
	Find a given peak of the heap
*/
template <typename pmt, typename fmt, Ord theOrd>
inline Sqn HeapHFrH<pmt,fmt,theOrd>::findRank(Idx const theIdx) const
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
inline Sqn HeapHFrH<pmt,fmt,theOrd>::randRank(Rnd & theRnd) const
{
	WatchError
	Itr tItr = mVarHeap->randPeakItr(theRnd);
	return (tItr == mVarHeap->endPeak() ? InvSqn : mVarHeap->serial(tItr));
	CatchError
}




/*!
	Define a heaphfrh.
*/
template <typename pmt, typename fmt, Ord theOrd>
Hdl HeapHFrH<pmt,fmt,theOrd>::def(Hdl const hdlSys, Prm const & thePrm)
{
	WatchError
	Prm tPrm = thePrm;
	HeapHFrH<pmt,fmt,theOrd> * tFrH = new HeapHFrH<pmt,fmt,theOrd>(hdlSys, tPrm);
	Hdl const tHdl = tFrH->defSysFunc();
	if (tHdl != InvHdl) { delete tFrH; return tHdl; }

	tFrH->mVarHeap = new qhp<fmt, Sqn, hop,kmm>(tFrH->FuncVars.itemCount());

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
HeapHFrH<pmt,fmt,theOrd>::HeapHFrH(Hdl const hdlSys, Prm & thePrm) : FrHt<fmt>(hdlSys, 1),
	mVarHeap(Null)
{
	WatchError
	this->setTermCls(TermStub< HeapHFrH<pmt,fmt,theOrd> >::TermCls);
	this->setParams(DfltFsm, thePrm.ptrm(), 1, Ordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pmt, typename fmt, Ord theOrd>
HeapHFrH<pmt,fmt,theOrd>::HeapHFrH(HeapHFrH<pmt,fmt,theOrd> const & that) : FrHt<fmt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename pmt, typename fmt, Ord theOrd>
HeapHFrH<pmt,fmt,theOrd> const & HeapHFrH<pmt,fmt,theOrd>::operator = (HeapHFrH<pmt,fmt,theOrd> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template <typename pmt, typename fmt, Ord theOrd>
void HeapHFrH<pmt,fmt,theOrd>::compConst()
{
	WatchError
	if (!this->updatable())
		for(Sqn tPrmSqn = 0; tPrmSqn < mPhRec->HintFlds.itemCount(); ++tPrmSqn)
			mVarHeap->alter( this->PrmVars[0][tPrmSqn],
					tc<pmt,fmt>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
	CatchError
}



/*!
	Compute the term in execution mode.
*/
template <typename pmt, typename fmt, Ord theOrd>
void HeapHFrH<pmt,fmt,theOrd>::execAnew()
{
	WatchError
	#if ExecDnwd
	Term::performExecAnew(this->mPrmTerms[0]);
	#endif

	for(Sqn tPrmSqn = 0; tPrmSqn < mPhRec->HintFlds.itemCount(); ++tPrmSqn)
		mVarHeap->alter(this->PrmVars[0][tPrmSqn],
				tc<pmt,fmt>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));

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
void HeapHFrH<pmt,fmt,theOrd>::undoHint(Pos const thePos)
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
void HeapHFrH<pmt,fmt,theOrd>::execIncr()
{
	WatchError
	#if ExecUpwd
	if (this->mExecChgdPrms.tagCount())
	{
		for (Idx tIdx = 0; tIdx < mPhRec->DiffSqns.itemCount(); ++tIdx)
		{
			Sqn const tPrmSqn =  mPhRec->DiffSqns[tIdx];
			mVarHeap->alter(this->PrmVars[0][tPrmSqn],
					tc<pmt,fmt>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
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
				mVarHeap->alter(this->PrmVars[0][tPrmSqn],
					tc<pmt,fmt>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
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
				Sqn const tPrmSqn =  mPhRec->DiffSqns[tIdx];
				Sqn const tSqn = this->PrmVars[0][tPrmSqn];
				if (!this->mHintUndonePrms->list(0).tagged(tPrmSqn))
					mVarHeap->alter(tSqn, tc<pmt,fmt>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
			}
		}
		else //if (backlog())
		{
			Term::performExecBklg(this->mPrmTerms[0]);
			for (Idx tIdx = 0; tIdx < mPhRec->DiffSqns.itemCount(); ++tIdx)
			{
				Sqn const tPrmSqn =  mPhRec->DiffSqns[tIdx];
				Sqn const tSqn = this->PrmVars[0][tPrmSqn];
				if (!this->mHintUndonePrms->list(0).tagged(tPrmSqn))
					mVarHeap->alter(tSqn, tc<pmt,fmt>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
			}
		}
		for(Idx tIdx = 0; tIdx < this->mHintUndonePrms->list(0).tagCount(); ++tIdx)
		{
			Sqn const tPrmSqn = this->mHintUndonePrms->list(0)[tIdx];
			Sqn const tSqn = this->PrmVars[0][tPrmSqn];
			mVarHeap->alter(tSqn, tc<pmt,fmt>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
		}
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
void HeapHFrH<pmt,fmt,theOrd>::execBklg()
{
	WatchError
	Term::performExecBklg(this->mPrmTerms[0]);
	for (Idx tIdx = 0; tIdx < mPhRec->DiffSqns.itemCount(); ++tIdx)
	{
		Sqn const tPrmSqn =  mPhRec->DiffSqns[tIdx];
		Sqn const tSqn = this->PrmVars[0][tPrmSqn];
		if (!this->mHintUndonePrms->list(0).tagged(tPrmSqn))
			mVarHeap->alter(tSqn, tc<pmt,fmt>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
	}
	for(Idx tIdx = 0; tIdx < this->mHintUndonePrms->list(0).tagCount(); ++tIdx)
	{
		Sqn const tPrmSqn = this->mHintUndonePrms->list(0)[tIdx];
		Sqn const tSqn = this->PrmVars[0][tPrmSqn];
		mVarHeap->alter(tSqn, tc<pmt,fmt>::iof(mPhRec->HintFlds[tPrmSqn].CurrData()));
	}
	this->runPostExecBklg();
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif //HeapHFrHTccIncluded
