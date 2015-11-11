/*!
	@file rankedhintvar1sp.cpp
	@brief The implementation file for RankedHintVar1Sp class.
	@details This is the implementation file for RankedHintVar1Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/




#include "cbls/selcs/sps/rankedhintvar1sp.hpp"


openKangarooSpace



/*!
	The duplicator.
*/
RankedHintVar1Sp::RankedHintVar1Sp(RankedHintVar1Sp const & that) : SpXn(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
RankedHintVar1Sp const & RankedHintVar1Sp::operator = (RankedHintVar1Sp const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Define a ranked varst value select in the solver.
*/
Hdl RankedHintVar1Sp::def(Hdl const hdlSys, Prm const & prmTerm)
{
	WatchError
	Prm tPrms[1] = { prmTerm };
	RankedHintVar1Sp * tSp = new RankedHintVar1Sp(hdlSys, tPrms, 1);
	Hdl const tHdl = tSp->defSysSelc();
	if (tHdl != InvHdl) { delete tSp; return tHdl; }

	FrH * tFrH = FrH::cast(tSp->mPrmTerms[0]);
	Alert(!tFrH->FuncVars.itemCount(), eNoVarsForSelection);

	return tSp->SelcHdl;
	CatchError
}



/*!
	The constructor.
*/
RankedHintVar1Sp::RankedHintVar1Sp(Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) : SpXn(hdlSys, PrmCount)
{
	WatchError
	this->setSelcCls(SelcStub< RankedHintVar1Sp >::SelcCls);
	this->setParams(DfltFsm, thePrms, PrmCount);
	this->setSelcHvl(this->calcSelcHvl());
	CatchError
}


#if CompLazyHalf
/*!
	Set the required terms for the selector.
*/
void RankedHintVar1Sp::require(Bln const SetNotUnset)
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
Bll RankedHintVar1Sp::select(Rnd & theRnd)
{
	WatchError
	#if CompLazy
		#if CompLazyHalf
		if (!active())
		#endif
			Term::performExec(this->mPrmTerms[0]);
	#endif
	this->mSelcVars.clear();
	FrH * tFrH = FrH::cast(this->mPrmTerms[0]);
	#if ConsistentRandom
		Sqn tSqn = tFrH->beginRank();
		while(tSqn != tFrH->endRank())
		{
			Hdl tHdl = tFrH->FuncVars[tSqn];
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
			tSqn = tFrH->moveRank(tSqn);
		}

		if (this->mSelcVars.itemCount() > 1)
		{
			Hdl tHdl = this->mSelcVars.item(uniform(theRnd,this->mSelcVars.itemCount()));
			this->mSelcVars.clear();
			this->mSelcVars.insert(tHdl);
		}
	#else
		Sqn tSqn = tFrH->randRank(theRnd);
		if (tSqn != tFrH->endRank())
			this->mSelcVars.insertMem(tFrH->FuncVars[tSqn]);
	#endif
	return this->mSelcVars.itemCount();
	CatchError
}


closeKangarooSpace
