/*!
	@file opt1val1statrangesdvzt.tcc
	@brief The source file for Opt1Val1StatRangeSdVZt template class.
	@details This is the source file for Opt1Val1StatRangeSdVZt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef Opt1Val1StatRangeSdVZtTccIncluded
#define Opt1Val1StatRangeSdVZtTccIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"


openKangarooSpace



/*!
	@class Opt1Val1StatRangeSdVZt
	@brief A template class to represent optimum value static range single variable selcs.
	@details This template class represents optimum value static range single variable selcs.
*/
template<typename vt, typename zt, Ord theOrd>
class Opt1Val1StatRangeSdVZt : public SdZt<zt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys, Prm const & prmTerm);	//!< Define a selc.

		static Opt1Val1StatRangeSdVZt<vt,zt,theOrd> &
							refm(Hdl const hdlSys, Hdl const hdlSelc);				//!< Refer to a selc.
		static Opt1Val1StatRangeSdVZt<vt,zt,theOrd> *
							ptrm(Hdl const hdlSys, Hdl const hdlSelc);				//!< Point to a selc.
		static Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const &
							refc(Hdl const hdlSys, Hdl const hdlSelc);				//!< Refer to a selc.
		static Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const *
							ptrc(Hdl const hdlSys, Hdl const hdlSelc);				//!< Point to a selc.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);				//!< Suits casting?
		static Bll suit(Selc * theSelc);				//!< Suits casting?
		static Bll suit(Selc const & theSelc);			//!< Suits casting?
		static Bll suit(Selc const * theSelc);			//!< Suits casting?

		static Opt1Val1StatRangeSdVZt<vt,zt,theOrd> & cast(Selc & theSelc);				//!< Perform casting.
		static Opt1Val1StatRangeSdVZt<vt,zt,theOrd> * cast(Selc * theSelc);				//!< Perform casting.
		static Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const & cast(Selc const & theSelc);	//!< Perform casting.
		static Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const * cast(Selc const * theSelc);	//!< Perform casting.

		//! @}

		void includeCurrValue(Bll const SetNotUnset);		//!< Include current value in search.

	private:

		Opt1Val1StatRangeSdVZt(Fss const theFss, Hdl const hdlSys,
										Prm * prmTerm, Dim const PrmCount);					//!< Constructor.
		Opt1Val1StatRangeSdVZt(Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const & that);		//!< Duplicator.
		Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const & operator =
									(Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const & that);	//!< Assigner.
		~Opt1Val1StatRangeSdVZt();															//!< Destructor.

		virtual Bll select(Rnd & theRnd);					//!< Run the selc in the sys.
		#if CompLazyHalf
		virtual void require(Bll const SetNotUnset);		//!< Requirement for the selector.
		#endif
		EvalRec<zt> const * mPzRec;							//!< Point to the metric.
		Bll					mIncludeCurr;					//!< Include current value.
};



/*!
	Whether a selector for casting.
*/
template<typename vt, typename zt, Ord theOrd>
inline Bll Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::suit(Selc const & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< Opt1Val1StatRangeSdVZt<vt,zt,theOrd> >::SelcCls;
	CatchError
}



/*!
	Whether a selector for casting.
*/
template<typename vt, typename zt, Ord theOrd>
inline Bll Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::suit(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< Opt1Val1StatRangeSdVZt<vt,zt,theOrd> >::SelcCls;
	CatchError
}



/*!
	Whether a selector for casting.
*/
template<typename vt, typename zt, Ord theOrd>
inline Bll Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::suit(Selc & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< Opt1Val1StatRangeSdVZt<vt,zt,theOrd> >::SelcCls;
	CatchError
}



/*!
	Whether a selector for casting.
*/
template<typename vt, typename zt, Ord theOrd>
inline Bll Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::suit(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< Opt1Val1StatRangeSdVZt<vt,zt,theOrd> >::SelcCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt, typename zt, Ord theOrd>
inline Opt1Val1StatRangeSdVZt<vt,zt,theOrd> &
Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::cast(Selc & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< Opt1Val1StatRangeSdVZt<vt,zt,theOrd> >::SelcCls) Wtxt(eWrongCls);

	return scast<Opt1Val1StatRangeSdVZt<vt,zt,theOrd> &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt, typename zt, Ord theOrd>
inline Opt1Val1StatRangeSdVZt<vt,zt,theOrd> *
Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::cast(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< Opt1Val1StatRangeSdVZt<vt,zt,theOrd> >::SelcCls) Wtxt(eWrongCls);

	return scast<Opt1Val1StatRangeSdVZt<vt,zt,theOrd> *>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt, typename zt, Ord theOrd>
inline Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const &
Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::cast(Selc const & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< Opt1Val1StatRangeSdVZt<vt,zt,theOrd> >::SelcCls) Wtxt(eWrongCls);

	return scast<Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt, typename zt, Ord theOrd>
inline Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const *
Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::cast(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< Opt1Val1StatRangeSdVZt<vt,zt,theOrd> >::SelcCls) Wtxt(eWrongCls);

	return scast<Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const *>(theSelc);
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
template<typename vt, typename zt, Ord theOrd>
inline Opt1Val1StatRangeSdVZt<vt,zt,theOrd> &
Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
template<typename vt, typename zt, Ord theOrd>
inline Opt1Val1StatRangeSdVZt<vt,zt,theOrd> *
Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc));
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
template<typename vt, typename zt, Ord theOrd>
inline Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const &
Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
template<typename vt, typename zt, Ord theOrd>
inline Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const *
Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
	CatchError
}




/*!
	The destructor.
*/
template<typename vt, typename zt, Ord theOrd>
inline Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::~Opt1Val1StatRangeSdVZt()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	The duplicator.
*/
template<typename vt, typename zt, Ord theOrd>
Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::Opt1Val1StatRangeSdVZt
		(Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const & that) : SdZt<zt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename vt, typename zt, Ord theOrd>
Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const &
Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::operator =
		(Opt1Val1StatRangeSdVZt<vt,zt,theOrd> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Define an optimum value select in the solver.
*/
template<typename vt, typename zt, Ord theOrd>
Hdl Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::def(Fss const theFss, Hdl const hdlSys, Prm const & prmTerm)
{
	WatchError
	Prm tPrms[1] = { prmTerm };
	Opt1Val1StatRangeSdVZt<vt,zt,theOrd> * tSdXF =
		new Opt1Val1StatRangeSdVZt<vt,zt,theOrd>(theFss, hdlSys, tPrms, 1);
	Hdl const tHdl = tSdXF->defSysSelc();
	if (tHdl != InvHdl) { delete tSdXF; return tHdl; }

	EvalTbl<zt> const & tPztTbl = EvalTbl<zt>::refc(hdlSys);

	Loc const tPzLoc = getPzLoc(theFss, tSdXF->mPrmTerms[0], prmTerm.PrmSpec);
	tSdXF->mPzRec = tPztTbl.ptrcEvalRec(tPzLoc);

	return tSdXF->SelcHdl;
	CatchError
}



/*!
	The constructor.
*/
template<typename vt, typename zt, Ord theOrd>
Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::Opt1Val1StatRangeSdVZt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) : SdZt<zt>(hdlSys, PrmCount), mIncludeCurr(false)
{
	WatchError
	this->setSelcCls(SelcStub< Opt1Val1StatRangeSdVZt<vt,zt,theOrd> >::SelcCls);
	this->setParams(theFss, thePrms, PrmCount);
	this->setSelcHvl(this->calcSelcHvl());
	CatchError
}


#if CompLazyHalf
/*!
	Set requirement for the selector.
*/
template<typename vt, typename zt, Ord theOrd>
void Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::require(Bll const SetNotUnset)
{
	WatchError
	Warn(this->mSelcSys.chkExecMode(NullComp), eSysUninit);
	Func::cast(this->mPrmTerms[0])->require(SetNotUnset);
	CatchError
}
#endif


/*!
	Perform selection.
*/
template<typename vt, typename zt, Ord theOrd>
Bll Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::select(Rnd & theRnd)
{
	WatchError
	Warn(this->mSelcVars.itemCount() != 1, eSelcVarCount(1));

	Hdl tVarHdl = this->mSelcVars[0];
	RangeVarVt<vt> & tRangeVar = RangeVarVt<vt>::cast(this->mSelcSys.refmVar(tVarHdl));
	Warn(tRangeVar.ValueType() != DataStub<vt>::DataTyp, eWrongTyp);

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
	zt tRunZ = OrdStub<theOrd,zt,Bll>::Last0;

	vt tCurrV = tRangeVar.CurrValue();
	vt tLeftV = tRangeVar.StatLeftValue();
	vt tRightV = tRangeVar.StatRightValue();
	vt tStepV = tRangeVar.StepSizeValue();

	if (mIncludeCurr)
	{
		this->mSelcVals.insertMem(Wrp(tCurrV));
		#if CompLazy
			#if CompLazyHalf
			if (!this->active())
			#endif
				Term::performExec(this->mPrmTerms[0]);
		#endif
		tRunZ = mPzRec->CurrData();
	}

	for(vt tNextV = tLeftV; tNextV < tCurrV; nexta<vt>::iof(tNextV, tStepV))
	{
		this->mSelcSys.setSimulMode(DiffAsgn);
		tRangeVar.simulIncrValue(tNextV);
		this->mSelcSys.setSimulMode(DiffProp);
		#if SimulUpwd
		this->mSelcSys.propagateSimulIncr();
		#endif
		#if SimulDnwd
		Term::performSimulIncr(this->mPrmTerms[0]);
		#endif

//		//Queens
//		Int a = RangeVarVi::refc(0, 0).ValueRec().NextData(this->mSelcSys.SimulClk());
//		Int b = RangeVarVi::refc(0, 1).ValueRec().NextData(this->mSelcSys.SimulClk());
//		Int c = RangeVarVi::refc(0, 2).ValueRec().NextData(this->mSelcSys.SimulClk());
//		Int d = RangeVarVi::refc(0, 3).ValueRec().NextData(this->mSelcSys.SimulClk());
//		if (a + 1 != FeVi::refc(0, 0).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "a";
//		if (b + 2 != FeVi::refc(0, 2).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "b";
//		if (c + 3 != FeVi::refc(0, 4).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "c";
//		if (d + 4 != FeVi::refc(0, 6).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "d";
//		if (a - 1 != FeVi::refc(0, 1).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "e";
//		if (b - 2 != FeVi::refc(0, 3).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "f";
//		if (c - 3 != FeVi::refc(0, 5).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "g";
//		if (d - 4 != FeVi::refc(0, 7).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "h";
//		Int e = 0, f = 0, g = 0;
//		e = 3 - (b != a) - (c != b && c != a) - (d != c && d != b && d != a);
//		f = 3 - (b+2 != a+1) - (c+3 != b+2 && c+3 != a+1) - (d+4 != c+3 && d+4 != b+2 && d+4 != a+1);
//		g = 3 - (b-2 != a-1) - (c-3 != b-2 && c-3 != a-1) - (d-4 != c-3 && d-4 != b-2 && d-4 != a-1);
//		if (e != FcMiHn::refc(0, 8).MetricRec().NextData(this->mSelcSys.SimulClk())) cerr << "i";
//		if (f != FcMiHn::refc(0, 9).MetricRec().NextData(this->mSelcSys.SimulClk())) cerr << "j";
//		if (g != FcMiHn::refc(0, 10).MetricRec().NextData(this->mSelcSys.SimulClk())) cerr << "k";
//		if (e+f+g != FcMiHn::refc(0, 11).MetricRec().NextData(this->mSelcSys.SimulClk())) cerr << "l";
//		cout << tNextV << " " << FcMiHn::refc(0, 11).MetricRec().NextData(this->mSelcSys.SimulClk()) <<" ";
//		cout << endl;

		zt tNextZ = mPzRec->NextData(this->mSelcSys.SimulClk());
		if (OrdStub<theOrd,zt,Bll>::RegOp::iof(tNextZ, tRunZ))
		{
			this->mSelcVals.clear();
			this->mSelcVals.insertMem(Wrp(tRangeVar.NextValue()));
			tRunZ = tNextZ;
		}
		else if (eq<zt,Bll>::iof(tNextZ, tRunZ))
			this->mSelcVals.insertMem(Wrp(tRangeVar.NextValue()));
	}

	for(vt tNextV = tRightV; tNextV > tCurrV; preva<vt>::iof(tNextV, tStepV))
	{
		this->mSelcSys.setSimulMode(DiffAsgn);
		tRangeVar.simulIncrValue(tNextV);
		this->mSelcSys.setSimulMode(DiffProp);
		#if SimulUpwd
		this->mSelcSys.propagateSimulIncr();
		#endif
		#if SimulDnwd
		Term::performSimulIncr(this->mPrmTerms[0]);
		#endif
//		//Queens
//		Int a = RangeVarVi::refc(0, 0).ValueRec().NextData(this->mSelcSys.SimulClk());
//		Int b = RangeVarVi::refc(0, 1).ValueRec().NextData(this->mSelcSys.SimulClk());
//		Int c = RangeVarVi::refc(0, 2).ValueRec().NextData(this->mSelcSys.SimulClk());
//		Int d = RangeVarVi::refc(0, 3).ValueRec().NextData(this->mSelcSys.SimulClk());
//		if (a + 1 != FeVi::refc(0, 0).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "a";
//		if (b + 2 != FeVi::refc(0, 2).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "b";
//		if (c + 3 != FeVi::refc(0, 4).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "c";
//		if (d + 4 != FeVi::refc(0, 6).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "d";
//		if (a - 1 != FeVi::refc(0, 1).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "e";
//		if (b - 2 != FeVi::refc(0, 3).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "f";
//		if (c - 3 != FeVi::refc(0, 5).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "g";
//		if (d - 4 != FeVi::refc(0, 7).ValueRec().NextData(this->mSelcSys.SimulClk())) cerr << "h";
//		Int e = 0, f = 0, g = 0;
//		e = 3 - (b != a) - (c != b && c != a) - (d != c && d != b && d != a);
//		f = 3 - (b+2 != a+1) - (c+3 != b+2 && c+3 != a+1) - (d+4 != c+3 && d+4 != b+2 && d+4 != a+1);
//		g = 3 - (b-2 != a-1) - (c-3 != b-2 && c-3 != a-1) - (d-4 != c-3 && d-4 != b-2 && d-4 != a-1);
//		if (e != FcMiHn::refc(0, 8).MetricRec().NextData(this->mSelcSys.SimulClk())) cerr << "i";
//		if (f != FcMiHn::refc(0, 9).MetricRec().NextData(this->mSelcSys.SimulClk())) cerr << "j";
//		if (g != FcMiHn::refc(0, 10).MetricRec().NextData(this->mSelcSys.SimulClk())) cerr << "k";
//		if (e+f+g != FcMiHn::refc(0, 11).MetricRec().NextData(this->mSelcSys.SimulClk())) cerr << "l";
//		cout << tNextV << " " << FcMiHn::refc(0, 11).MetricRec().NextData(this->mSelcSys.SimulClk()) <<" ";
//		cout << endl;

		zt tNextZ = mPzRec->NextData(this->mSelcSys.SimulClk());
		if (OrdStub<theOrd,zt,Bll>::RegOp::iof(tNextZ, tRunZ))
		{
			this->mSelcVals.clear();
			this->mSelcVals.insertMem(Wrp(tRangeVar.NextValue()));
			tRunZ = tNextZ;
		}
		else if (eq<zt,Bll>::iof(tNextZ, tRunZ))
			this->mSelcVals.insertMem(Wrp(tRangeVar.NextValue()));
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
	Include current value.
*/
template<typename vt, typename zt, Ord theOrd>
inline void Opt1Val1StatRangeSdVZt<vt,zt,theOrd>::includeCurrValue(Bll const SetNotUnset)
{
	WatchError
	mIncludeCurr = SetNotUnset;
	CatchError
}



closeKangarooSpace


#endif	//Opt1Val1StatRangeSdVZtTccIncluded
