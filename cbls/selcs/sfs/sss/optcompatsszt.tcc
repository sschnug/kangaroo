/*!
	@file optcompatsszt.tcc
	@brief The source file for OptCompatSsZt template class.
	@details This is the source file for OptCompatSsZt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef OptCompatSsZtTccIncluded
#define OptCompatSsZtTccIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"


openKangarooSpace



/*!
	@class OptCompatSsZt
	@brief A template class to represent optimal compatible swap selcs.
	@details This template class represents optimal compatible swap selcs.
*/
template<typename zt, Ord theOrd>
class OptCompatSsZt : public SsZt<zt>
{
	public:

		static Hdl def(Fss const theFss, Hdl const hdlSys, Prm const & prmTerm);			//!< Define a full swap.
		static OptCompatSsZt<zt,theOrd> const & refc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Refer to a selc.
		static OptCompatSsZt<zt,theOrd> const * ptrc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Point to a selc.
		static OptCompatSsZt<zt,theOrd> & refm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Refer to a selc.
		static OptCompatSsZt<zt,theOrd> * ptrm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Point to a selc.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);					//!< Suits casting?
		static Bll suit(Selc * theSelc);					//!< Suits casting?
		static Bll suit(Selc const & theSelc);				//!< Suits casting?
		static Bll suit(Selc const * theSelc);				//!< Suits casting?

		static OptCompatSsZt<zt,theOrd> & cast(Selc & theSelc);				//!< Perform casting.
		static OptCompatSsZt<zt,theOrd> * cast(Selc * theSelc);				//!< Perform casting.
		static OptCompatSsZt<zt,theOrd> const & cast(Selc const & theSelc);	//!< Perform casting.
		static OptCompatSsZt<zt,theOrd> const * cast(Selc const * theSelc);	//!< Perform casting.

		//! @}

	private:

		OptCompatSsZt(Fss const theFss, Hdl const hdlSys, Prm * prmTerm, Dim const PrmCount);	//!< Constructor.
		OptCompatSsZt(OptCompatSsZt<zt,theOrd> const & that);									//!< Duplicator.
		OptCompatSsZt<zt,theOrd> const & operator = (OptCompatSsZt<zt,theOrd> const & that);	//!< Assigner.
		~OptCompatSsZt();																		//!< Destructor.

		virtual Bll select(Rnd & theRnd);									//!< Run the selc in the sys.
		#if CompLazyHalf
		virtual void require(Bln const Active);								//!< Activate the selc in the sys.
		#endif

		EvalRec<zt> const * mPzRec;											//!< Point to the metric.
};



/*!
	Whether a term is suitable for casting.
*/
template<typename zt, Ord theOrd>
inline Bln OptCompatSsZt<zt,theOrd>::suit(Selc const & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< OptCompatSsZt<zt,theOrd> >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename zt, Ord theOrd>
inline Bln OptCompatSsZt<zt,theOrd>::suit(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< OptCompatSsZt<zt,theOrd> >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename zt, Ord theOrd>
inline Bln OptCompatSsZt<zt,theOrd>::suit(Selc & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< OptCompatSsZt<zt,theOrd> >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename zt, Ord theOrd>
inline Bln OptCompatSsZt<zt,theOrd>::suit(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< OptCompatSsZt<zt,theOrd> >::SelcCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename zt, Ord theOrd>
inline OptCompatSsZt<zt,theOrd> & OptCompatSsZt<zt,theOrd>::cast(Selc & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< OptCompatSsZt<zt,theOrd> >::SelcCls) Wtxt(eWrongCls);

	return scast<OptCompatSsZt<zt,theOrd> &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename zt, Ord theOrd>
inline OptCompatSsZt<zt,theOrd> * OptCompatSsZt<zt,theOrd>::cast(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< OptCompatSsZt<zt,theOrd> >::SelcCls) Wtxt(eWrongCls);

	return scast<OptCompatSsZt<zt,theOrd> *>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename zt, Ord theOrd>
inline OptCompatSsZt<zt,theOrd> const & OptCompatSsZt<zt,theOrd>::cast(Selc const & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< OptCompatSsZt<zt,theOrd> >::SelcCls) Wtxt(eWrongCls);

	return scast<OptCompatSsZt<zt,theOrd> const &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename zt, Ord theOrd>
inline OptCompatSsZt<zt,theOrd> const * OptCompatSsZt<zt,theOrd>::cast(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< OptCompatSsZt<zt,theOrd> >::SelcCls) Wtxt(eWrongCls);

	return scast<OptCompatSsZt<zt,theOrd> const *>(theSelc);
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
template<typename zt, Ord theOrd>
inline OptCompatSsZt<zt,theOrd> const &
OptCompatSsZt<zt,theOrd>::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
template<typename zt, Ord theOrd>
inline OptCompatSsZt<zt,theOrd> const *
OptCompatSsZt<zt,theOrd>::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
template<typename zt, Ord theOrd>
inline OptCompatSsZt<zt,theOrd> &
OptCompatSsZt<zt,theOrd>::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
template<typename zt, Ord theOrd>
inline OptCompatSsZt<zt,theOrd> *
OptCompatSsZt<zt,theOrd>::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc));
	CatchError
}



/*!
	The destructor.
*/
template<typename zt, Ord theOrd>
inline OptCompatSsZt<zt,theOrd>::~OptCompatSsZt()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	The duplicator.
*/
template<typename zt, Ord theOrd>
OptCompatSsZt<zt,theOrd>::OptCompatSsZt(OptCompatSsZt<zt,theOrd> const & that) : SsZt<zt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename zt, Ord theOrd>
OptCompatSsZt<zt,theOrd> const & OptCompatSsZt<zt,theOrd>::operator = (OptCompatSsZt<zt,theOrd> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Define a compatible swap select in the solver.
*/
template<typename zt, Ord theOrd>
Hdl OptCompatSsZt<zt,theOrd>::def(Fss const theFss, Hdl const hdlSys, Prm const & prmTerm)
{
	WatchError
	Prm tPrms[1] = { prmTerm };
	OptCompatSsZt<zt,theOrd> * tSsX = new OptCompatSsZt<zt,theOrd>(theFss, hdlSys, tPrms, 1);
	Hdl const tHdl = tSsX->defSysSelc();
	if (tHdl != InvHdl) { delete tSsX; return tHdl; }

	EvalTbl<zt> const & tPztTbl = EvalTbl<zt>::refc(hdlSys);

	Func * tFunc = Func::cast(tSsX->mPrmTerms[0]);
	Loc const tPzLoc = getPzLoc(theFss, tFunc, prmTerm.PrmSpec);
	tSsX->mPzRec = tPztTbl.ptrcEvalRec(tPzLoc);

	Warn(tFunc->FuncVars.itemCount() < 2, eFewerSwapVars);

	return tSsX->SelcHdl;
	CatchError
}


/*!
	The constructor.
*/
template<typename zt, Ord theOrd>
OptCompatSsZt<zt,theOrd>::OptCompatSsZt(Fss const theFss, Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) : SsZt<zt>(hdlSys, PrmCount)
{
	WatchError
	this->setSelcCls(SelcStub< OptCompatSsZt<zt,theOrd> >::SelcCls);
	this->setParams(theFss, thePrms, PrmCount);
	this->setSelcHvl(this->calcSelcHvl());
	CatchError
}


#if CompLazyHalf
/*!
	Activate the select in the solver.
*/
template<typename zt, Ord theOrd>
void OptCompatSsZt<zt,theOrd>::require(Bll const SetNotUnset)
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
template<typename zt, Ord theOrd>
Bll OptCompatSsZt<zt,theOrd>::select(Rnd & theRnd)
{
	WatchError
	Func * tFunc = Func::cast(this->mPrmTerms[0]);
	b1<Hdl, xmm> const & tFuncVars = tFunc->FuncVars;
	Dim tVarCount = tFuncVars.itemCount();

	zt tCurr = OrdStub<theOrd,zt,Bln>::Last0;
	for(Sqn tSqn1 = 0; tSqn1 < tVarCount - 1; ++tSqn1)
	{
		Hdl tVarHdl1 = tFuncVars[tSqn1];
		Var * tVarTerm1 = this->mSelcSys.ptrmVar(tVarHdl1);

		#if SimulFixedFlexi
		this->mSelcSys.setSimulFixedVar1(tVarHdl1);
		#endif

		for(Sqn tSqn2 = tSqn1 + 1; tSqn2 < tVarCount; ++tSqn2)
		{
			Hdl tVarHdl2 = tFuncVars[tSqn2];
			Var * tVarTerm2 = this->mSelcSys.ptrmVar(tVarHdl2);

			if (!tVarTerm1->swappable(tVarTerm2)) continue;

			this->mSelcSys.setSimulMode(SwapAsgn);

			#if SimulFixedFlexi
			this->mSelcSys.altSimulFlexiVar1(1, tVarHdl2);
			#elif SimulFixedOnly
			this->mSelcSys.setSimulFixedVar2(tVarHdl1, tVarHdl2);
			#elif SimulFlexiOnly
			this->mSelcSys.setSimulFlexiVar2(tVarHdl1, tVarHdl2);
			#endif

			tVarTerm1->simulIncrSwap(tVarTerm2);

			this->mSelcSys.setSimulMode(SwapProp);

			#if SimulUpwd
			this->mSelcSys.propagateSimulIncr();
			#endif
			#if SimulDnwd
			Term::performSimulIncr(this->mPrmTerms[0]);
			#endif

			zt tNext = mPzRec->NextData(this->mSelcSys.SimulClk());

//			//Magic Square test
//			#define N1 15
//			#define NS (N1*N1)
//			#define NN (N1 * (N1*N1 + 1) / 2)
//			Int vars[NS];
//			for(int i = 0; i < NS; i++)
//				vars[i] = Vi::cast(ptrVar(this->mSelcSys, i))->ValueRec().NextData(this->mSelcSys.SimulClk());
//			int ss = 0, sd1 = 0, sd2 = 0;
//			for(int i = 0; i < N1; i++)
//			{
//				int sr = 0;
//				for(int j = 0; j < N1; j++)
//					sr += vars[i * N1 + j];
//				ss += labs(sr - NN);
//				int sc = 0;
//				for(int j = 0; j < N1; j++)
//					sc += vars[j * N1 + i];
//				ss += labs(sc - NN);
//				sd1 += vars[i * N1 + i];
//				sd2 += vars[i * N1 + N1 - i - 1];
//			}
//			ss += labs(sd1 - NN) + labs(sd2 - NN);
//			if (ss != tNext) cerr << "X";

			if (OrdStub<theOrd,zt,Bln>::RegOp::iof(tNext, tCurr))
			{
				tCurr = tNext;
				this->mSelcVars.clear();
				this->mSelcVars.insertMem(tVarHdl1);
				this->mSelcVars.insertMem(tVarHdl2);
			}
			else if (eq<zt,Bll>::iof(tNext, tCurr))
			{
				this->mSelcVars.insertMem(tVarHdl1);
				this->mSelcVars.insertMem(tVarHdl2);
			}
		}
	}

	if (this->mSelcVars.itemCount() > 2)
	{
		Idx tIdx = uniform(theRnd, 0u, this->mSelcVars.itemCount() - 2);
		if (tIdx & 1) ++tIdx;
		Hdl tHdl1 = this->mSelcVars[tIdx];
		Hdl tHdl2 = this->mSelcVars[tIdx + 1];
		this->mSelcVars.clear();
		this->mSelcVars.insert(tHdl1);
		this->mSelcVars.insert(tHdl2);
	}
	return this->mSelcVars.itemCount();
	CatchError
}


closeKangarooSpace


#endif	//OptCompatSsZtTccIncluded
