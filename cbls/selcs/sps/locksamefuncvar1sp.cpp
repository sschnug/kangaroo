/*!
	@file locksamefuncvar1sp.cpp
	@brief The implementation file for LockSameFuncVar1Sp class.
	@details This is the implementation file for LockSameFuncVar1Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/




#include "cbls/selcs/sps/locksamefuncvar1sp.hpp"


openKangarooSpace



/*!
	The duplicator.
*/
LockSameFuncVar1Sp::LockSameFuncVar1Sp(LockSameFuncVar1Sp const & that) : SpXn(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
LockSameFuncVar1Sp const & LockSameFuncVar1Sp::operator = (LockSameFuncVar1Sp const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Define a ranked varst value select in the solver.
*/
Hdl LockSameFuncVar1Sp::def(Hdl const hdlSys, Prm const & prmTerm)
{
	WatchError
	Prm tPrms[1] = { prmTerm };
	LockSameFuncVar1Sp * tSp = new LockSameFuncVar1Sp(hdlSys, tPrms, 1);
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
LockSameFuncVar1Sp::LockSameFuncVar1Sp(Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount) : SpXn(hdlSys, PrmCount)
{
	WatchError
	this->setSelcCls(SelcStub< LockSameFuncVar1Sp >::SelcCls);
	this->setParams(DfltFsm, thePrms, PrmCount);
	this->setSelcHvl(this->calcSelcHvl());
	CatchError
}


#if CompLazyHalf
/*!
	Set the required terms for the selector.
*/
void LockSameFuncVar1Sp::require(Bln const SetNotUnset)
{
	WatchError
	//	nothing to be done.
	CatchError
}
#endif


/*!
	Perform selection.
*/
Bll LockSameFuncVar1Sp::select(Rnd & theRnd)
{
	WatchError
	this->mSelcVars.clear();
	Func* tFunc = Func::cast(this->mPrmTerms[0]);
	Dim tCount = tFunc->FuncVars.itemCount();
	Sqn tSqn = uniform(theRnd, tCount);
	Hdl tHdl = tFunc->FuncVars[tSqn];
	#if CheckError
		Idx tIdx = 0;
		while (++tIdx <= tCount && mSelcSys.refcVar(tHdl).locked())
		{
			tSqn = uniform(theRnd, tCount);
			tHdl = tFunc->FuncVars[tSqn];
		}
		if (tIdx > tCount) Throw(eRandVarSelectLoop);
	#else
		while (mSelcSys.refcVar(tHdl).locked())
		{
			tSqn = uniform(theRnd, tCount);
			tHdl = tFunc->FuncVars[tSqn];
		}
	#endif
	this->mSelcVars.insertMem(tHdl);
	return this->mSelcVars.itemCount();
	CatchError
}


closeKangarooSpace
