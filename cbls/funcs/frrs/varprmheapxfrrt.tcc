/*!
	@file varprmheapxfrrt.tcc
	@brief The prototype file for VarPrmHeapXFrRt template class.
	@details This is the prototype file for VarPrmHeapXFrRt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef VarPrmHeapXFrRtTccIncluded
#define VarPrmHeapXFrRtTccIncluded



#include "cbls/funcs/frrs/frrt.tcc"
#include "cbls/funcs/opfns/idx.hh"



openKangarooSpace



/*!
	@class VarPrmHeapXFrRt
	@brief A class to represent heaps of variables mapped to parameter values/metrics.
	@details This class represents heaps of variables mapped to parameter values/metrics.
*/
template <typename pxt, typename fmt, Ord theOrd>
class VarPrmHeapXFrRt : public FrRt<fmt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys, Prm * thePrms,
															Hdl * varHdls, Dim const PrmCount);		//!< Definition.

		static VarPrmHeapXFrRt<pxt,fmt,theOrd> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static VarPrmHeapXFrRt<pxt,fmt,theOrd> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static VarPrmHeapXFrRt<pxt,fmt,theOrd> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static VarPrmHeapXFrRt<pxt,fmt,theOrd> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static VarPrmHeapXFrRt<pxt,fmt,theOrd> const & cast(Term const & theTerm);	//!< Perform casting.
		static VarPrmHeapXFrRt<pxt,fmt,theOrd> const * cast(Term const * theTerm);	//!< Perform casting.
		static VarPrmHeapXFrRt<pxt,fmt,theOrd> & cast(Term & theTerm);				//!< Perform casting.
		static VarPrmHeapXFrRt<pxt,fmt,theOrd> * cast(Term * theTerm);				//!< Perform casting.

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

	private:

		VarPrmHeapXFrRt(Fss const theFss, Hdl const hdlSys,
					Prm * thePrms, Hdl * varHdls, Dim const PrmCount);	//!< Constructor.
		VarPrmHeapXFrRt(VarPrmHeapXFrRt<pxt,fmt,theOrd> const & that);	//!< Duplicator.
		VarPrmHeapXFrRt<pxt,fmt,theOrd> const & operator =
					(VarPrmHeapXFrRt<pxt,fmt,theOrd> const & that);		//!< Assigner.
		~VarPrmHeapXFrRt();												//!< Destructor.

		virtual void compConst();				//!< Compute the term.
		virtual void execAnew();				//!< Execute the term.
		virtual void execIncr();				//!< Execute the term.
		#if CompLazy
		virtual void execBklg();				//!< Execute the term.
		virtual void undoEval(Pos const thePos);//!< Perform eval undo.
		#endif

		typedef OrdStub<theOrd,fmt,Bll> hos;	//!< Heap ordering stub.
		typedef typename hos::InvOp hop;		//!< Heap ordering operator.

		b1<Hdl, kmm>				 mVarHdls;	//!< Variable handles.
		b1<EvalRec<pxt> const *,kmm> mPxRecs;	//!< Parameter records.
		qhp<fmt, Pos, hop, kmm>     mPrmHeap; 	//!< The heap holding metrics.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Bll VarPrmHeapXFrRt<pxt,fmt,theOrd>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< VarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Bll VarPrmHeapXFrRt<pxt,fmt,theOrd>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< VarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Bll VarPrmHeapXFrRt<pxt,fmt,theOrd>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< VarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Bll VarPrmHeapXFrRt<pxt,fmt,theOrd>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< VarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline VarPrmHeapXFrRt<pxt,fmt,theOrd> const & VarPrmHeapXFrRt<pxt,fmt,theOrd>::cast(Term const & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< VarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<VarPrmHeapXFrRt<pxt,fmt,theOrd> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline VarPrmHeapXFrRt<pxt,fmt,theOrd> const * VarPrmHeapXFrRt<pxt,fmt,theOrd>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< VarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<VarPrmHeapXFrRt<pxt,fmt,theOrd> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline VarPrmHeapXFrRt<pxt,fmt,theOrd> & VarPrmHeapXFrRt<pxt,fmt,theOrd>::cast(Term & theTerm)
{
	WatchError
	Wchk(theTerm.TermCls != TermStub< VarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<VarPrmHeapXFrRt<pxt,fmt,theOrd> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline VarPrmHeapXFrRt<pxt,fmt,theOrd> * VarPrmHeapXFrRt<pxt,fmt,theOrd>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Wchk(theTerm->TermCls != TermStub< VarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls) Wtxt(eWrongCls);

	return scast<VarPrmHeapXFrRt<pxt,fmt,theOrd> *>(theTerm);
	CatchError
}



/*!
	Refer to a varprmheapxfrrt
*/
template <typename pxt, typename fmt, Ord theOrd>
inline VarPrmHeapXFrRt<pxt,fmt,theOrd> & VarPrmHeapXFrRt<pxt,fmt,theOrd>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a varprmheapxfrrt.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline VarPrmHeapXFrRt<pxt,fmt,theOrd> * VarPrmHeapXFrRt<pxt,fmt,theOrd>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a varprmheapxfrrt
*/
template <typename pxt, typename fmt, Ord theOrd>
inline VarPrmHeapXFrRt<pxt,fmt,theOrd> const & VarPrmHeapXFrRt<pxt,fmt,theOrd>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a varprmheapxfrrt.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline VarPrmHeapXFrRt<pxt,fmt,theOrd> const * VarPrmHeapXFrRt<pxt,fmt,theOrd>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The destructor.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline VarPrmHeapXFrRt<pxt,fmt,theOrd>::~VarPrmHeapXFrRt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Find the handle for the parameter position.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Hdl VarPrmHeapXFrRt<pxt,fmt,theOrd>::findHdl(Pos const thePos) const
{
	WatchError
	return this->mVarHdls[thePos];
	CatchError
}



/*!
	Get the begin rank var.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Pos VarPrmHeapXFrRt<pxt,fmt,theOrd>::beginRank() const
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
inline Pos VarPrmHeapXFrRt<pxt,fmt,theOrd>::endRank() const
{
	WatchError
	return InvPos;
	CatchError
}


/*!
	Get the next var of the heap.
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Pos VarPrmHeapXFrRt<pxt,fmt,theOrd>::moveRank(Pos const thePos) const
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
inline Dim VarPrmHeapXFrRt<pxt,fmt,theOrd>::rankCount() const
{
	WatchError
	return mPrmHeap.peakCount();
	CatchError
}



/*!
	Find a given peak of the heap
*/
template <typename pxt, typename fmt, Ord theOrd>
inline Pos VarPrmHeapXFrRt<pxt,fmt,theOrd>::findRank(Idx const theIdx) const
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
inline Pos VarPrmHeapXFrRt<pxt,fmt,theOrd>::randRank(Rnd & theRnd) const
{
	WatchError
	Itr tItr = mPrmHeap.randPeakItr(theRnd);
	return (tItr == mPrmHeap.endPeak() ? InvPos : mPrmHeap.serial(tItr));
	CatchError
}




/*!
	Define a varprmheapxfrrt.
*/
template <typename pxt, typename fmt, Ord theOrd>
Hdl VarPrmHeapXFrRt<pxt,fmt,theOrd>::def(Fss const theFss, Hdl const hdlSys,
				Prm * thePrms, Hdl * varHdls, Dim const PrmCount)
{
	WatchError
	Wchk(PrmCount < 2 || PrmCount > MaxDim) Wtxt(eParamCount2(2, MaxDim));

	VarPrmHeapXFrRt<pxt,fmt,theOrd> * tFrR =
		new VarPrmHeapXFrRt<pxt,fmt,theOrd>(theFss, hdlSys, thePrms, varHdls, PrmCount);
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
VarPrmHeapXFrRt<pxt,fmt,theOrd>::VarPrmHeapXFrRt(Fss const theFss, Hdl const hdlSys,
			Prm * thePrms, Hdl * varHdls, Dim const PrmCount) : FrRt<fmt>(hdlSys, PrmCount),
			mVarHdls(varHdls, PrmCount), mPxRecs(PrmCount), mPrmHeap(PrmCount)
{
	WatchError
	this->setTermCls(TermStub< VarPrmHeapXFrRt<pxt,fmt,theOrd> >::TermCls);
	this->setParams(theFss, thePrms, PrmCount, Ordered);
	this->setTermHvl(this->calcTermHvl());
	CatchError
}



/*!
	The duplicator.
*/
template <typename pxt, typename fmt, Ord theOrd>
VarPrmHeapXFrRt<pxt,fmt,theOrd>::VarPrmHeapXFrRt(VarPrmHeapXFrRt<pxt,fmt,theOrd> const & that) : FrRt<fmt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename pxt, typename fmt, Ord theOrd>
VarPrmHeapXFrRt<pxt,fmt,theOrd> const & VarPrmHeapXFrRt<pxt,fmt,theOrd>::operator = (VarPrmHeapXFrRt<pxt,fmt,theOrd> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Compute the term.
*/
template <typename pxt, typename fmt, Ord theOrd>
void VarPrmHeapXFrRt<pxt,fmt,theOrd>::compConst()
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
void VarPrmHeapXFrRt<pxt,fmt,theOrd>::execAnew()
{
	WatchError
	for(Pos tPos = 0; tPos < mPxRecs.itemCount(); ++tPos)
	{
		#if ExecDnwd
		Term::performExecAnew(this->mPrmTerms[tPos]);
		#endif
		mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
	}

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
void VarPrmHeapXFrRt<pxt,fmt,theOrd>::undoEval(Pos const thePos)
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
void VarPrmHeapXFrRt<pxt,fmt,theOrd>::execIncr()
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
				mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
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
					mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
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
				mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
		}

		for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
		{
			Pos const tPos = this->mBacklogPrms.serial(tIdx);
			if (this->mLblCandPrms.tagged(tPos)) continue;

			Term::performExecBklg(this->mPrmTerms[tPos]);
			EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

			if (this->mEvalUndonePrms->tagged(tPos) ||
					tPxRec->PrevDiff(this->mTermSys.ExecClk()))
				mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
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
template <typename pxt, typename fmt, Ord theOrd>
void VarPrmHeapXFrRt<pxt,fmt,theOrd>::execBklg()
{
	WatchError
	for(Idx tIdx = 0; tIdx < this->mBacklogPrms.tagCount(); ++tIdx)
	{
		Pos const tPos = this->mBacklogPrms.serial(tIdx);
		Term::performExecBklg(this->mPrmTerms[tPos]);
		EvalRec<pxt> const * tPxRec = mPxRecs[tPos];

		if (this->mEvalUndonePrms->tagged(tPos) ||
				tPxRec->PrevDiff(this->mTermSys.ExecClk()))
			mPrmHeap.alter(tPos, tc<pxt,fmt>::iof(mPxRecs[tPos]->CurrData()));
	}
	this->runPostExecBklg();
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif //VarPrmHeapXFrRtTccIncluded
