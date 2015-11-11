/*!
	@file svtabusamefuncvar1sp.cpp
	@brief The implementation file for SvTabuSameFuncVar1Sp class.
	@details This is the implementation file for SvTabuSameFuncVar1Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/




#include "cbls/selcs/sps/svtabusamefuncvar1sp.hpp"


openKangarooSpace



/*!
	The duplicator.
*/
SvTabuSameFuncVar1Sp::SvTabuSameFuncVar1Sp(SvTabuSameFuncVar1Sp const & that) :
	SpXn(that), mSysTabu(that.mSysTabu)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
SvTabuSameFuncVar1Sp const & SvTabuSameFuncVar1Sp::operator = (SvTabuSameFuncVar1Sp const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Define a ranked varst value select in the solver.
*/
Hdl SvTabuSameFuncVar1Sp::def(Hdl const hdlSys, Prm const & prmTerm, Typ const typTabu)
{
	WatchError
	Prm tPrms[1] = { prmTerm };
	SvTabuSameFuncVar1Sp * tSp = new SvTabuSameFuncVar1Sp(hdlSys, tPrms, 1, typTabu);
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
SvTabuSameFuncVar1Sp::SvTabuSameFuncVar1Sp(Hdl const hdlSys,
		Prm * thePrms, Dim const PrmCount, Typ const typTabu) :
		SpXn(hdlSys, PrmCount), mSysTabu(SvTabu::refc(hdlSys,typTabu))
{
	WatchError
	this->setSelcCls(SelcStub< SvTabuSameFuncVar1Sp >::SelcCls);
	this->setParams(DfltFsm, thePrms, PrmCount);
	this->setSelcHvl(this->calcSelcHvl());
	CatchError
}


#if CompLazyHalf
/*!
	Set the required terms for the selector.
*/
void SvTabuSameFuncVar1Sp::require(Bln const SetNotUnset)
{
	WatchError
	//	nothing to be done.
	CatchError
}
#endif


/*!
	Perform selection.
*/
Bll SvTabuSameFuncVar1Sp::select(Rnd & theRnd)
{
	WatchError
	this->mSelcVars.clear();
	Func* tFunc = Func::cast(this->mPrmTerms[0]);
	Dim tCount = tFunc->FuncVars.itemCount();
	Sqn tSqn = uniform(theRnd, tCount);
	Hdl tHdl = tFunc->FuncVars[tSqn];
	#if CheckError
		Idx tIdx = 0;
		while (++tIdx <= tCount && mSysTabu.state(tHdl))
		{
			tSqn = uniform(theRnd, tCount);
			tHdl = tFunc->FuncVars[tSqn];
		}
		if (tIdx > tCount) Throw(eRandVarSelectLoop);
	#else
		while (mSysTabu.state(tHdl))
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
