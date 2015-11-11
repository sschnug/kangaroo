/*!
	@file ss.cpp
	@brief The implementation file for Ss class.
	@details This is the implementation file for Ss class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/selcs/sfs/ss.hpp"


openKangarooSpace



/*!
	The constructor.
*/
Ss::Ss(Hdl const hdlSys, Dim const PrmCount) :
		Sf(hdlSys, PrmCount)
{
	WatchError
	setHoldValue(false);
	CatchError
}



/*!
	The destructor.
*/
Ss::~Ss()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
Ss::Ss(Ss const & that) : Sf(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Ss const & Ss::operator = (Ss const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}




/*!
	Execute selection.
*/
void Ss::execute()
{
	WatchError
	Warn(mSelcVars.itemCount() % 2, eOddSwapVars);
	Warn(mSelcVals.itemCount(), eValuesForSwap);
	Warn(HoldValue, eValuesForSwap);

	mSelcSys.setExecMode(SwapAsgn);
	mSelcSys.setExecAsgnVars(mSelcVars.items(), mSelcVars.itemCount());

	for(Idx tIdx = 0; tIdx < mSelcVars.itemCount(); tIdx+=2)
	{
		Var * tVar1 = mSelcSys.ptrmVar(mSelcVars[tIdx]);
		Var * tVar2 = mSelcSys.ptrmVar(mSelcVars[tIdx + 1]);
		tVar1->execIncrSwap(tVar2);
	}

	mSelcSys.setExecMode(SwapProp);
	mSelcSys.propagateExecIncr();
	CatchError
}



closeKangarooSpace
