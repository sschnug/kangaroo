/*!
	@file svtabulocksamefuncvar1sp.cpp
	@brief The implementation file for SvTabuLockSameFuncVar1Sp class.
	@details This is the implementation file for SvTabuLockSameFuncVar1Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/




#include "cbls/selcs/sps/svtabulocksamefuncvar1sp.hpp"


openKangarooSpace



/*!
	The duplicator.
*/
SvTabuLockSameFuncVar1Sp::SvTabuLockSameFuncVar1Sp(SvTabuLockSameFuncVar1Sp const & that) :
		SpXn(that), mSysTabu(that.mSysTabu)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
SvTabuLockSameFuncVar1Sp const & SvTabuLockSameFuncVar1Sp::operator = (SvTabuLockSameFuncVar1Sp const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Define a ranked varst value select in the solver.
*/
Hdl SvTabuLockSameFuncVar1Sp::def(Hdl const hdlSys, Prm const & prmTerm, Typ const typTabu)
{
	WatchError
	Prm tPrms[1] = { prmTerm };
	SvTabuLockSameFuncVar1Sp * tSp = new SvTabuLockSameFuncVar1Sp(hdlSys, tPrms, 1, typTabu);
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
SvTabuLockSameFuncVar1Sp::SvTabuLockSameFuncVar1Sp(Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, Typ const typTabu) :
		SpXn(hdlSys, PrmCount), mSysTabu(SvTabu::refc(hdlSys,typTabu))
{
	WatchError
	this->setSelcCls(SelcStub< SvTabuLockSameFuncVar1Sp >::SelcCls);
	this->setParams(DfltFsm, thePrms, PrmCount);
	this->setSelcHvl(this->calcSelcHvl());
	CatchError
}


#if CompLazyHalf
/*!
	Set the required terms for the selector.
*/
void SvTabuLockSameFuncVar1Sp::require(Bln const SetNotUnset)
{
	WatchError
	//	nothing to be done.
	CatchError
}
#endif


/*!
	Perform selection.
*/
Bll SvTabuLockSameFuncVar1Sp::select(Rnd & theRnd)
{
	WatchError
	this->mSelcVars.clear();
	Func* tFunc = Func::cast(this->mPrmTerms[0]);
	Dim tCount = tFunc->FuncVars.itemCount();
	Sqn tSqn = uniform(theRnd, tCount);
	Hdl tHdl = tFunc->FuncVars[tSqn];
	#if CheckError
		Idx tIdx = 0;
		while (++tIdx <= tCount &&
			(mSelcSys.refcVar(tHdl).locked() || mSysTabu.state(tHdl)))
		{
			tSqn = uniform(theRnd, tCount);
			tHdl = tFunc->FuncVars[tSqn];
		}
		if (tIdx > tCount) Throw(eRandVarSelectLoop);
	#else
		while (mSelcSys.refcVar(tHdl).locked() || mSysTabu.state(tHdl))
			tHdl = tFunc->FuncVars[uniform(theRnd, tFunc->FuncVars.itemCount())];
	#endif
	this->mSelcVars.insertMem(tHdl);
	return this->mSelcVars.itemCount();
	CatchError
}


closeKangarooSpace
