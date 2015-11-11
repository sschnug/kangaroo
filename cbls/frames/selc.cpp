/*!
	@file selc.cpp
	@brief The implementation file for the Selc class.
	@details This is the implementation file for the Selc class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see selc.hpp
*/



#include "cbls/frames/selc.hpp"
#include "cbls/frames/sys.hpp"
#include "cbls/frames/term.hpp"
#include "cbls/frames/var.hpp"
#include "cbls/frames/func.hpp"
#include "cbls/frames/prm.hpp"
#include "cbls/frames/reg.hh"


openKangarooSpace



/*!
	The constructor.
*/
Selc::Selc(Hdl const hdlSys, Dim const PrmCount) :
		SelcCls(SelcClsNil), SelcCat(SelcTypNil), SelcTyp(SelcTypNil),
		SelcHdl(InvHdl), SelcFss(DfltFsm), SelcHvl(0), ExecReady(false),
		HoldValue(false), mSelcSys(Sys::refm(hdlSys)), mSelcVars(),
		mSelcVals(), mPrmTerms(PrmCount), mPrmSpecs(PrmCount)
		#if CompLazyHalf
		, mActive(0)
		#endif
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
Selc::Selc(Selc const & that) : SelcCls(SelcClsNil), SelcCat(SelcTypNil),
		SelcTyp(SelcTypNil), SelcHdl(InvHdl), SelcFss(DfltFsm), SelcHvl(0),
		ExecReady(false), HoldValue(false), mSelcSys(that.mSelcSys),
		mSelcVars(), mSelcVals(), mPrmTerms(that.mPrmTerms), mPrmSpecs(that.mPrmSpecs)
		#if CompLazyHalf
		, mActive(0)
		#endif
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Selc const & Selc::operator = (Selc const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}






/*!
	Set the selc class.
*/
void Selc::setSelcCls(Cls const theSelcCls)
{
	WatchError
	Warn(!mSelcSys.chkExecMode(NullComp), eSysNotUninit);
	Warn(theSelcCls == SelcClsNil, eNilCls);

	ccast<Cls &>(SelcCls) = theSelcCls;
	CatchError
}



/*!
	Set the selc type.
*/
void Selc::setSelcCat(Typ const theSelcCat)
{
	WatchError
	Warn(!mSelcSys.chkExecMode(NullComp), eSysNotUninit);
	Warn(theSelcCat == SelcTypNil, eNilTyp);

	ccast<Typ &>(SelcCat) = theSelcCat;
	CatchError
}



/*!
	Set the selc subtype.
*/
void Selc::setSelcTyp(Typ const theSelcTyp)
{
	WatchError
	Warn(!mSelcSys.chkExecMode(NullComp), eSysNotUninit);
	Warn(theSelcTyp == SelcTypNil, eNilTyp);

	ccast<Typ &>(SelcTyp) = theSelcTyp;
	CatchError
}



/*!
	Set the selc handle.
*/
void Selc::setSelcHdl(Hdl const hdlSelc)
{
	WatchError
	Warn(!mSelcSys.chkExecMode(NullComp), eSysNotUninit);
	Warn(hdlSelc == InvHdl, eInvalidHandle);

	ccast<Hdl &>(SelcHdl) = hdlSelc;
	CatchError
}



/*!
	Set the hash value.
*/
void Selc::setSelcHvl(Hvl const theHvl)
{
	WatchError
	Warn(!mSelcSys.chkExecMode(NullComp), eSysNotUninit);

	ccast<Hvl &>(SelcHvl) = theHvl;
	CatchError
}



/*!
	Set whether selection is ready for execution.
*/
void Selc::setExecReady(Bll const SetNotUnset)
{
	WatchError
	Warn(!mSelcSys.chkExecMode(NullComp), eSysNotUninit);

	ccast<Bll &>(ExecReady) = SetNotUnset;
	CatchError
}



/*!
	Set select the vars
*/
void Selc::setHoldValue(Bll const SetNotUnset)
{
	WatchError
	Warn(!mSelcSys.chkExecMode(NullComp), eSysNotUninit);

	ccast<Bll &>(HoldValue) = SetNotUnset;
	CatchError
}



/*!
	Calculate hash value.
*/
Hvl Selc::calcSelcHvl() const
{
	WatchError
	Hvl tHvl = 0;
	tHvl = mixHash(tHvl, calcHash(SelcCls));
	tHvl = mixHash(tHvl, calcHash(SelcFss));

	for(Pos tPos = 0; tPos < mPrmTerms.itemCount(); ++tPos)
	{
		tHvl = mixHash(tHvl, calcHash(mPrmTerms[tPos]));
		tHvl = mixHash(tHvl, calcHash(mPrmSpecs[tPos]));
	}

	return tHvl;
	CatchError
}



/*!
	Compare two selects for equality.
*/
Bll Selc::equate(Selc const & that) const
{
	WatchError
	if (SelcCls != that.SelcCls) return false;
	if (SelcFss != that.SelcFss) return false;
	b1<Term *, kmm> const & tPrmTerms = that.mPrmTerms;
	b1<Pss, kmm> const & tPrmSpecs = that.mPrmSpecs;

	if (mPrmTerms.itemCount() != tPrmTerms.itemCount()) return false;
	for(Pos tPos = 0; tPos < mPrmTerms.itemCount(); ++tPos)
	{
		if (mPrmTerms[tPos] != tPrmTerms[tPos]) return false;
		if (mPrmSpecs[tPos] != tPrmSpecs[tPos]) return false;
	}
	return true;
	CatchError
}




/*!
	Define a selector.
*/
Hdl Selc::defSysSelc()
{
	WatchError
	return mSelcSys.defSelc(this);
	CatchError
}



/*!
	Refer to a selector.
*/
Selc & Selc::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return Sys::refm(hdlSys).refmSelc(hdlSelc);
	CatchError
}



/*!
	Point to a selector.
*/
Selc * Selc::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc);
	CatchError
}



/*!
	Refer to a selector.
*/
Selc const & Selc::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return Sys::refc(hdlSys).refcSelc(hdlSelc);
	CatchError
}



/*!
	Point to a selector.
*/
Selc const * Selc::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc);
	CatchError
}



/*!
	Set the parameters of the selector.
*/
void Selc::setParams(Fss const theFss, Prm * thePrms, Dim const PrmCount)
{
	WatchError
	Warn(!mSelcSys.chkExecMode(NullComp), eSysNotUninit);

	ccast<Fss &>(SelcFss) = theFss;

	b1<Term *, kmm> & tPrmTerms = ccast<b1<Term *, kmm> &>(mPrmTerms);
	b1<Pss, kmm> & tPrmSpecs = ccast<b1<Pss, kmm> &>(mPrmSpecs);

	for(Pos tPos = 0; tPos < PrmCount; ++tPos)
	{
		tPrmSpecs[tPos] = thePrms[tPos].PrmSpec;
		switch(thePrms[tPos].TermGen)
		{
			case Tf :
				tPrmTerms[tPos] = mSelcSys.ptrmFunc(thePrms[tPos].TermHdl);
				break;
			case Tv :
				tPrmTerms[tPos] = mSelcSys.ptrmVar(thePrms[tPos].TermHdl);
				break;
			default :
				Throw(eTermNotUpdatable);
				break;
		}
	}
	CatchError
}



/*!
	Set selected variable.
*/
void Selc::setSelcVar1(Hdl const hdlVar)
{
	WatchError
	mSelcVars.clear();
	mSelcVars.insertMem(hdlVar);
	CatchError
}


/*!
	Set selected variables.
*/
void Selc::setSelcVar2(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(hdlVar1 == hdlVar2, eVarsNotDifferent);
	mSelcVars.clear();
	mSelcVars.insertMem(hdlVar1);
	mSelcVars.insertMem(hdlVar1);
	CatchError
}


/*!
	Set selected variables.
*/
void Selc::setSelcVars(Hdl const * hdlVars, Dim const VarCount)
{
	WatchError
	#if CheckError
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
		for(Idx sIdx = tIdx + 1; sIdx < VarCount; ++sIdx)
			if (hdlVars[tIdx] == hdlVars[sIdx])
				Throw(eVarsNotDifferent);
	#endif
	mSelcVars.copyDirect(hdlVars, VarCount);
	CatchError
}



/*!
	Set selected value.
*/
void Selc::setSelcVal1(Wrp const & theWrp)
{
	WatchError
	mSelcVals.clear();
	mSelcVals.insertMem(theWrp);
	CatchError
}



/*!
	Set selected values.
*/
void Selc::setSelcVal2(Wrp const & theWrp1, Wrp const & theWrp2)
{
	WatchError
	mSelcVals.clear();
	mSelcVals.insertMem(theWrp1);
	mSelcVals.insertMem(theWrp2);
	CatchError
}



/*!
	Set selected values.
*/
void Selc::setSelcVals(Wrp const * theWrps, Dim const VarCount)
{
	WatchError
	mSelcVals.copyDirect(theWrps, VarCount);
	CatchError
}



/*!
	Copy selected variables from the source selector.
*/
void Selc::copySelcVarsVals(Selc const * srcSelc)
{
	WatchError
	Warn(!srcSelc, eNullPointer);
	Warn(!mSelcSys.mskExecMode(PropMode), eNotExecPropMode);

	b1<Hdl, xmm> const & tSelcVars = srcSelc->mSelcVars;
	mSelcVars.copyDirectMem(tSelcVars.items(), tSelcVars.itemCount());
	if (HoldValue && srcSelc->HoldValue)
	{
		b1<Wrp, xmm> const & tSelcVals = srcSelc->mSelcVals;
		Warn(tSelcVars.itemCount() < tSelcVals.itemCount(), eSelcMoreValsThanVars);
		mSelcVals.copyDirectMem(tSelcVals.items(), tSelcVals.itemCount());
	}

	CatchError
}



/*!
	Copy selected variables from the source selector.
*/
void Selc::copySelcVarsVals(Selc const & srcSelc)
{
	WatchError
	Warn(!mSelcSys.mskExecMode(PropMode), eNotExecPropMode);

	b1<Hdl, xmm> const & tSelcVars = srcSelc.mSelcVars;
	mSelcVars.copyDirectMem(tSelcVars.items(), tSelcVars.itemCount());
	if (HoldValue && srcSelc.HoldValue)
	{
		b1<Wrp, xmm> const & tSelcVals = srcSelc.mSelcVals;
		Warn(tSelcVars.itemCount() < tSelcVals.itemCount(), eSelcMoreValsThanVars);
		mSelcVals.copyDirectMem(tSelcVals.items(), tSelcVals.itemCount());
	}
	CatchError
}



/*!
	Copy selected variables from the source selector.
*/
void Selc::copySelcVars(Selc const * srcSelc)
{
	WatchError
	Warn(!srcSelc, eNullPointer);
	Warn(!mSelcSys.mskExecMode(PropMode), eNotExecPropMode);

	b1<Hdl, xmm> const & tSelcVars = srcSelc->mSelcVars;
	mSelcVars.copyDirectMem(tSelcVars.items(), tSelcVars.itemCount());
	CatchError
}



/*!
	Copy selected variables from the source selector.
*/
void Selc::copySelcVars(Selc const & srcSelc)
{
	WatchError
	Warn(!mSelcSys.mskExecMode(PropMode), eNotExecPropMode);
	b1<Hdl, xmm> const & tSelcVars = srcSelc.mSelcVars;
	mSelcVars.copyDirectMem(tSelcVars.items(), tSelcVars.itemCount());
	CatchError
}




/*!
	Copy selected values from the source selector.
*/
void Selc::copySelcVals(Selc const * srcSelc)
{
	WatchError
	Warn(!srcSelc, eNullPointer);
	Warn(!HoldValue, eSelcHoldsNoValue);
	Warn(!srcSelc->HoldValue, eSelcHoldsNoValue);
	Warn(!mSelcSys.mskExecMode(PropMode), eNotExecPropMode);

	b1<Wrp, xmm> const & tSelcVals = srcSelc->mSelcVals;

	Warn(srcSelc->mSelcVars.itemCount() < tSelcVals.itemCount(), eSelcMoreValsThanVars);

	mSelcVals.copyDirectMem(tSelcVals.items(), tSelcVals.itemCount());
	CatchError
}



/*!
	Set the selected values from the source selector.
*/
void Selc::copySelcVals(Selc const & srcSelc)
{
	WatchError
	Warn(!HoldValue, eSelcHoldsNoValue);
	Warn(!srcSelc.HoldValue, eSelcHoldsNoValue);
	Warn(!mSelcSys.mskExecMode(PropMode), eNotExecPropMode);

	b1<Wrp, xmm> const & tSelcVals = srcSelc.mSelcVals;
	Warn(srcSelc.mSelcVars.itemCount() < tSelcVals.itemCount(), eSelcMoreValsThanVars);
	mSelcVals.copyDirectMem(tSelcVals.items(), tSelcVals.itemCount());
	CatchError
}



/*!
	Perform selection.
*/
Bll Selc::performSelection(Rnd & theRnd)
{
	WatchError
	Warn(!mSelcSys.mskExecMode(PropMode), eNotExecPropMode);
	return select(theRnd);
	CatchError
}




#if CompLazyHalf
/*!
	Activate the selector.
*/
void Selc::activate(Bll const SetNotUnset)
{
	WatchError
	Warn(mSelcSys.chkExecMode(NullComp), eSysUninit);
	Warn(!SetNotUnset && !mActive, eSelcNotActive);
	if (SetNotUnset)
	{
		if (!mActive)
			require(true);
		++mActive;
	}
	else
	{
		--mActive;
		if (!mActive)
			require(false);
	}
	CatchError
}
#endif // CompLazyHalf


/*!
	Execute selections.
*/
void Selc::executeSelection()
{
	WatchError
	Warn(!ExecReady, eSelcNotExecReady);
	Warn(mSelcSys.chkExecMode(NullComp), eSysUninit);
	execute();
	CatchError
}


/*!
	Select and execute just one selector and return whether successful.
*/
Bll Selc::selectExecuteSelc1(Hdl const hdlSys, Hdl const hdlSelc, Rnd & theRnd)
{
	WatchError
	Selc & tSelc = refm(hdlSys, hdlSelc);
	if (!tSelc.performSelection(theRnd))
		return false;
	tSelc.executeSelection();
	return true;
	CatchError
}


/*!
	Select and execute two selectors and return whether successful.
*/
Bll Selc::selectExecuteSelc2(Hdl const hdlSys,
		Hdl const hdlSelc1, Hdl const hdlSelc2, Rnd & theRnd)
{
	WatchError
	Selc & tSelc1 = refm(hdlSys, hdlSelc1);
	if (!tSelc1.performSelection(theRnd))
		return false;
	Selc & tSelc2 = refm(hdlSys, hdlSelc2);
	tSelc2.copySelcVarsVals(tSelc1);
	if (!tSelc2.performSelection(theRnd))
		return false;
	tSelc2.executeSelection();
	return true;
	CatchError
}


/*!
	Select and execute a number of selectors and return whether successful.
*/
Bll Selc::selectExecuteSelcs(Hdl const hdlSys,
		Hdl const * hdlSelcs, Dim const SelcCount, Rnd & theRnd)
{
	WatchError
	Warn(!SelcCount, eEmptyCount);
	for(Idx tIdx = 0; tIdx < SelcCount - 1; ++tIdx)
	{
		Selc * tSelc1 = ptrm(hdlSys, hdlSelcs[tIdx]);
		if (!tSelc1->performSelection(theRnd))
			return false;
		Selc * tSelc2 = ptrm(hdlSys, hdlSelcs[tIdx + 1]);
		tSelc2->copySelcVarsVals(tSelc1);
	}
	Selc * tSelc = ptrm(hdlSys, hdlSelcs[SelcCount - 1]);
	if (!tSelc->performSelection(theRnd))
		return false;
	tSelc->executeSelection();
	return true;
	CatchError
}


closeKangarooSpace
