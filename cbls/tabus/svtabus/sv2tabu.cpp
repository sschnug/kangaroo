/*!
	@file sv2tabu.cpp
	@brief The implementation file for the Sv2Tabu class.
	@details This is the implementation file for the Sv2Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see tabu.hpp
*/



#include "cbls/tabus/svtabus/sv2tabu.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
Sv2Tabu::Sv2Tabu(Sv2Tabu const & that) : SvTabu(that),
		mUpdates(that.mUpdates)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Sv2Tabu const & Sv2Tabu::operator = (Sv2Tabu const & that)
{
	WatchError
	if (this == &that)
		return *this;
	Throw(eUndefAssigner);
	return *this;
	CatchError
}



/*!
	Update a function's var tabu.
*/
void Sv2Tabu::callbackFuncs()
{
	WatchError
	for (Idx tIdx = 0; tIdx < mFuncs.itemCount(); ++tIdx)
		callbackFunc(mFuncs[tIdx]);
	CatchError
}



closeKangarooSpace
