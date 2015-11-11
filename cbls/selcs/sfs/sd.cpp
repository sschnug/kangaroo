/*!
	@file sd.cpp
	@brief The implementation file for Sd class.
	@details This is the implementation file for Sd class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/selcs/sfs/sd.hpp"


openKangarooSpace



/*!
	The constructor.
*/
Sd::Sd(Hdl const hdlSys, Dim const PrmCount) :
		Sf(hdlSys, PrmCount)
{
	WatchError
	setHoldValue(true);
	CatchError
}



/*!
	The destructor.
*/
Sd::~Sd()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
Sd::Sd(Sd const & that) : Sf(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Sd const & Sd::operator = (Sd const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Execute selection.
*/
void Sd::execute()
{
	WatchError
	Warn(mSelcVars.itemCount() != mSelcVals.itemCount(), eDimensionMismatch);
	mSelcSys.setExecMode(DiffAsgn);
	mSelcSys.setExecAsgnVars(mSelcVars.items(), mSelcVars.itemCount());

	for(Idx tIdx = 0; tIdx < mSelcVals.itemCount(); ++tIdx)
	{
//		cerr << " Selc vars " <<  mSelcVars[tIdx] << " " << mSelcVals[tIdx].itemInt() << endl;

		mSelcSys.refmVar(mSelcVars[tIdx]).execIncrWrap(mSelcVals[tIdx]);
	}
	mSelcSys.setExecMode(DiffProp);
	mSelcSys.propagateExecIncr();
	CatchError
}


closeKangarooSpace
