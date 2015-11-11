/*!
	@file samefuncvar1sp.cpp
	@brief The implementation file for SameFuncVar1Sp class.
	@details This is the implementation file for SameFuncVar1Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/




#include "cbls/selcs/sps/samefuncvar1sp.hpp"


openKangarooSpace



/*!
	The duplicator.
*/
SameFuncVar1Sp::SameFuncVar1Sp(SameFuncVar1Sp const & that) : SpXn(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
SameFuncVar1Sp const & SameFuncVar1Sp::operator = (SameFuncVar1Sp const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Define a ranked varst value select in the solver.
*/
Hdl SameFuncVar1Sp::def(Hdl const hdlSys, Prm const & prmTerm)
{
	WatchError
	Prm tPrms[1] = { prmTerm };
	SameFuncVar1Sp * tSp = new SameFuncVar1Sp(hdlSys, tPrms, 1);
	Hdl const tHdl = tSp->defSysSelc();
	if (tHdl != InvHdl) { delete tSp; return tHdl; }

	Func * tFunc = Func::cast(tSp->mPrmTerms[0]);
	Alert(!tFunc->FuncVars.itemCount(), eNoVarsForSelection);

	return tSp->SelcHdl;
	CatchError
}



/*!
	The constructor.
*/
SameFuncVar1Sp::SameFuncVar1Sp(Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) : SpXn(hdlSys, PrmCount)
{
	WatchError
	this->setSelcCls(SelcStub< SameFuncVar1Sp >::SelcCls);
	this->setParams(DfltFsm, thePrms, PrmCount);
	this->setSelcHvl(this->calcSelcHvl());
	CatchError
}


#if CompLazyHalf
/*!
	Set the required terms for the selector.
*/
void SameFuncVar1Sp::require(Bln const SetNotUnset)
{
	WatchError
	//	nothing to be done.
	CatchError
}
#endif


/*!
	Perform selection.
*/
Bll SameFuncVar1Sp::select(Rnd & theRnd)
{
	WatchError
	this->mSelcVars.clear();
	Func* tFunc = Func::cast(this->mPrmTerms[0]);
	Sqn const tSqn = uniform(theRnd, tFunc->FuncVars.itemCount());
	Hdl const tHdl = tFunc->FuncVars[tSqn];
	this->mSelcVars.insertMem(tHdl);
	return this->mSelcVars.itemCount();
	CatchError
}


closeKangarooSpace
