/*!
	@file mcopt2val1rangesdvzt.tcc
	@brief The source file for McOpt2Val1RangeSdVZt template class.
	@details This is the source file for McOpt2Val1RangeSdVZt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef McOpt2Val1RangeSdVZtTccIncluded
#define McOpt2Val1RangeSdVZtTccIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"


openKangarooSpace



/*!
	@class McOpt2Val1RangeSdVZt
	@brief A template class to represent 2 criteria Monte Carlo optimum value static range single variable selcs.
	@details This template class represents 2 criteria Monte Carlo optimum value static range single variable selcs.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
class McOpt2Val1RangeSdVZt : public SdZt<zt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys,
			Prm const & prmTerm0, Prm const & prmTerm1, Dim const SamplePercent);	//!< Define a selc.

		static McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> &
							refm(Hdl const hdlSys, Hdl const hdlSelc);				//!< Refer to a selc.
		static McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> *
							ptrm(Hdl const hdlSys, Hdl const hdlSelc);				//!< Point to a selc.
		static McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const &
							refc(Hdl const hdlSys, Hdl const hdlSelc);				//!< Refer to a selc.
		static McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const *
							ptrc(Hdl const hdlSys, Hdl const hdlSelc);				//!< Point to a selc.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);				//!< Suits casting?
		static Bll suit(Selc * theSelc);				//!< Suits casting?
		static Bll suit(Selc const & theSelc);			//!< Suits casting?
		static Bll suit(Selc const * theSelc);			//!< Suits casting?

		static McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> & cast(Selc & theSelc);				//!< Perform casting.
		static McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> * cast(Selc * theSelc);				//!< Perform casting.
		static McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const & cast(Selc const & theSelc);	//!< Perform casting.
		static McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const * cast(Selc const * theSelc);	//!< Perform casting.

		//! @}

		void setDynaRange(Bll const SetNotUnset);		//!< Set dynamic range.

	private:

		McOpt2Val1RangeSdVZt(Fss const theFss, Hdl const hdlSys,
				Prm * prmTerm, Dim const PrmCount, Dim const SamplePercent);					//!< Constructor.
		McOpt2Val1RangeSdVZt(McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const & that);			//!< Duplicator.
		McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const & operator =
									(McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const & that);	//!< Assigner.
		~McOpt2Val1RangeSdVZt();																//!< Destructor.

		virtual Bll select(Rnd & theRnd);					//!< Run the selc in the sys.
		#if CompLazyHalf
		virtual void require(Bll const SetNotUnset);		//!< Requirement for the selector.
		#endif
		EvalRec<zt> const * mPzRecs[2];						//!< Point to the metrics.
		Bll 				mDynaRange;						//!< Whether dynamic range.
		Dim 	 			mSamplePercent;					//!< Sample percentage.
};



/*!
	Whether a selector for casting.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline Bll McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::suit(Selc const & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> >::SelcCls;
	CatchError
}



/*!
	Whether a selector for casting.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline Bll McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::suit(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> >::SelcCls;
	CatchError
}



/*!
	Whether a selector for casting.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline Bll McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::suit(Selc & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> >::SelcCls;
	CatchError
}



/*!
	Whether a selector for casting.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline Bll McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::suit(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> >::SelcCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> &
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::cast(Selc & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> >::SelcCls) Wtxt(eWrongCls);

	return scast<McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> *
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::cast(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> >::SelcCls) Wtxt(eWrongCls);

	return scast<McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> *>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const &
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::cast(Selc const & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> >::SelcCls) Wtxt(eWrongCls);

	return scast<McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const *
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::cast(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> >::SelcCls) Wtxt(eWrongCls);

	return scast<McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const *>(theSelc);
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> &
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> *
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc));
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const &
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const *
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
	CatchError
}




/*!
	The destructor.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::~McOpt2Val1RangeSdVZt()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	The duplicator.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::McOpt2Val1RangeSdVZt
		(McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const & that) : SdZt<zt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const &
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::operator =
		(McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Define a select in the solver.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
Hdl McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::def(Fss const theFss, Hdl const hdlSys,
		Prm const & prmTerm0, Prm const & prmTerm1, Dim const SamplePercent)
{
	WatchError
	Prm tPrms[2] = { prmTerm0, prmTerm1 };
	McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> * tSdXF =
		new McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>(theFss, hdlSys, tPrms, 2, SamplePercent);
	Hdl const tHdl = tSdXF->defSysSelc();
	if (tHdl != InvHdl) { delete tSdXF; return tHdl; }

	EvalTbl<zt> const & tPztTbl = EvalTbl<zt>::refc(hdlSys);

	Loc const tPzLoc0 = getPzLoc(theFss, tSdXF->mPrmTerms[0], prmTerm0.PrmSpec);
	tSdXF->mPzRecs[0] = tPztTbl.ptrcEvalRec(tPzLoc0);

	Loc const tPzLoc1 = getPzLoc(theFss, tSdXF->mPrmTerms[1], prmTerm1.PrmSpec);
	tSdXF->mPzRecs[1] = tPztTbl.ptrcEvalRec(tPzLoc1);

	return tSdXF->SelcHdl;
	CatchError
}



/*!
	The constructor.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::McOpt2Val1RangeSdVZt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, Dim const SamplePercent) : SdZt<zt>(hdlSys, PrmCount),
			mDynaRange(false), mSamplePercent(SamplePercent)
{
	WatchError
	Warn(!SamplePercent, eEmptyDimension);
	this->setSelcCls(SelcStub< McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1> >::SelcCls);
	this->setParams(theFss, thePrms, PrmCount);
	this->setSelcHvl(this->calcSelcHvl());
	CatchError
}



#if CompLazyHalf
/*!
	Set requirement for the selector.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
void McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::require(Bll const SetNotUnset)
{
	WatchError
	Warn(this->mSelcSys.chkExecMode(NullComp), eSysUninit);
	Func::cast(this->mPrmTerms[0])->require(SetNotUnset);
	//	the other term remains defered.
	CatchError
}
#endif



/*!
	Perform selection.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
Bll McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::select(Rnd & theRnd)
{
	WatchError
	Warn(this->mSelcVars.itemCount() != 1, eSelcVarCount(1));

	Hdl tVarHdl = this->mSelcVars[0];
	RangeVarVt<vt> & tRangeVar = RangeVarVt<vt>::cast(this->mSelcSys.refmVar(tVarHdl));
	Warn(tRangeVar.ValueType() != DataStub<vt>::DataTyp, eWrongTyp);

	if (mDynaRange)
	{
		#if CompLazy
		if (tRangeVar.DomainUpdateDefined())
		{
			#if CompLazyHalf
			if (!tRangeVar.DomainUpdateRequired())
			#endif
				tRangeVar.updateDomain();
		}
		#endif
	}

	#if SimulFixedFlexi
		#if SelcSimulFlexi
		this->mSelcSys.setSimulFlexiVar1(tVarHdl);
		#else
		this->mSelcSys.setSimulFixedVar1(tVarHdl);
		#endif
	#elif SimulFixedOnly
	this->mSelcSys.setSimulFixedVar1(tVarHdl);
	#elif SimulFlexiOnly
	this->mSelcSys.setSimulFlexiVar1(tVarHdl);
	#endif

	this->mSelcVals.clear();
	zt tRunZ0 = OrdStub<theOrd0,zt,Bll>::Last0;
	zt tRunZ1 = OrdStub<theOrd1,zt,Bll>::Last0;

	vt tLeftV = mDynaRange ? tRangeVar.DynaLeftValue() : tRangeVar.StatLeftValue();
	vt tRightV = mDynaRange ? tRangeVar.DynaRightValue() : tRangeVar.StatRightValue();
	vt tStepV = tRangeVar.StepSizeValue();

	Dim tSampleCount = (tRightV - tLeftV + 1) / tStepV * mSamplePercent / 100;

	for(Idx tIdx = 0; tIdx < tSampleCount; ++tIdx)
	{
		this->mSelcSys.setSimulMode(DiffAsgn);
		if (mDynaRange)
			tRangeVar.simulIncrDynaRand(theRnd);
		else
			tRangeVar.simulIncrStatRand(theRnd);
		this->mSelcSys.setSimulMode(DiffProp);
		#if SimulUpwd
		this->mSelcSys.propagateSimulIncr();
		#endif
		#if SimulDnwd
		Term::performSimulIncr(this->mPrmTerms[0]);
		#endif

		zt tNextZ0 = mPzRecs[0]->NextData(this->mSelcSys.SimulClk());
		if (OrdStub<theOrd0,zt,Bll>::RegOp::iof(tNextZ0, tRunZ0))
		{
			this->mSelcVals.clear();
			this->mSelcVals.insertMem(Wrp(tRangeVar.NextValue()));
			tRunZ0 = tNextZ0;
			#if SimulDnwd
			Term::performSimulIncr(this->mPrmTerms[1]);
			#endif
			tRunZ1 = mPzRecs[1]->NextData(this->mSelcSys.SimulClk());
		}
		else if (eq<zt,Bll>::iof(tNextZ0, tRunZ0))
		{
			#if SimulDnwd
			Term::performSimulIncr(this->mPrmTerms[1]);
			#endif
			zt tNextZ1 = mPzRecs[1]->NextData(this->mSelcSys.SimulClk());
			if (OrdStub<theOrd1,zt,Bll>::RegOp::iof(tNextZ1, tRunZ1))
			{
				this->mSelcVals.clear();
				this->mSelcVals.insertMem(Wrp(tRangeVar.NextValue()));
				tRunZ1 = tNextZ1;
			}
			else if (eq<zt,Bll>::iof(tNextZ1, tRunZ1))
				this->mSelcVals.insertMem(Wrp(tRangeVar.NextValue()));
		}
	}
	if (this->mSelcVals.itemCount() > 1)
	{
		Itr tItr = uniform(theRnd, this->mSelcVals.itemCount());
		Wrp tWrap = this->mSelcVals.item(tItr);
		this->mSelcVals.clear();
		this->mSelcVals.insertMem(tWrap);
	}
	return this->mSelcVals.itemCount();
	CatchError
}




/*!
	Set dynamic range.
*/
template<typename vt, typename zt, Ord theOrd0, Ord theOrd1>
inline void McOpt2Val1RangeSdVZt<vt,zt,theOrd0,theOrd1>::setDynaRange(Bll const SetNotUnset)
{
	WatchError
	mDynaRange = SetNotUnset;
	CatchError
}



closeKangarooSpace


#endif	//McOpt2Val1RangeSdVZtTccIncluded
