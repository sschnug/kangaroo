/*!
	@file rankedratevar1sp.cpp
	@brief The implementation file for RankedRateVar1Sp class.
	@details This is the implementation file for RankedRateVar1Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/




#include "cbls/selcs/sps/rankedratevar1sp.hpp"


openKangarooSpace



/*!
	The duplicator.
*/
RankedRateVar1Sp::RankedRateVar1Sp(RankedRateVar1Sp const & that) : SpXn(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
RankedRateVar1Sp const & RankedRateVar1Sp::operator = (RankedRateVar1Sp const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Define a ranked varst value select in the solver.
*/
Hdl RankedRateVar1Sp::def(Hdl const hdlSys, Prm const & prmTerm)
{
	WatchError
	Prm tPrms[1] = { prmTerm };
	RankedRateVar1Sp * tSp = new RankedRateVar1Sp(hdlSys, tPrms, 1);
	Hdl const tHdl = tSp->defSysSelc();
	if (tHdl != InvHdl) { delete tSp; return tHdl; }

	FrR * tFrR = FrR::cast(tSp->mPrmTerms[0]);
	Alert(!tFrR->FuncVars.itemCount(), eNoVarsForSelection);

	return tSp->SelcHdl;
	CatchError
}



/*!
	The constructor.
*/
RankedRateVar1Sp::RankedRateVar1Sp(Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) : SpXn(hdlSys, PrmCount)
{
	WatchError
	this->setSelcCls(SelcStub< RankedRateVar1Sp >::SelcCls);
	this->setParams(DfltFsm, thePrms, PrmCount);
	this->setSelcHvl(this->calcSelcHvl());
	CatchError
}


#if CompLazyHalf
/*!
	Set the required terms for the selector.
*/
void RankedRateVar1Sp::require(Bln const SetNotUnset)
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
Bll RankedRateVar1Sp::select(Rnd & theRnd)
{
	WatchError
	#if CompLazy
		#if CompLazyHalf
		if (!active())
		#endif
			Term::performExec(this->mPrmTerms[0]);
	#endif
	this->mSelcVars.clear();
	FrR * tFrR = FrR::cast(this->mPrmTerms[0]);
	#if ConsistentRandom
		Pos tPos = tFrR->beginRank();
		while(tPos != tFrR->endRank())
		{
			Hdl tHdl = tFrR->findHdl(tPos);
			Itr tItr1 = this->mSelcVars.insertItrMem(tHdl);
			Itr tItr2 = tItr1;
			while(tItr2)
			{
				if (this->mSelcVars[tItr2 - 1] < tHdl)
					break;
				this->mSelcVars[tItr2] = this->mSelcVars[tItr2 - 1];
				--tItr2;
			}
			if (tItr1 != tItr2)
				this->mSelcVars[tItr2] = tHdl;
			tPos = tFrR->moveRank(tPos);
		}
		if (this->mSelcVars.itemCount() > 1)
		{
			Hdl tHdl = this->mSelcVars.item(uniform(theRnd,this->mSelcVars.itemCount()));
			this->mSelcVars.clear();
			this->mSelcVars.insert(tHdl);
		}
	#else
		Pos tPos = tFrR->randRank(theRnd);
		if (tPos != tFrR->endRank())
			this->mSelcVars.insertMem(tFrR->findHdl(tPos));
	#endif
	return this->mSelcVars.itemCount();
	CatchError
}


closeKangarooSpace
