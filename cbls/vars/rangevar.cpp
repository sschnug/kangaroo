/*!
	@file rangevar.cpp
	@brief The implementation file for the RangeVar class.
	@details This is the implementation file for the RangeVar class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/vars/rangevar.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
RangeVar::RangeVar(RangeVar const & that) : Var(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
RangeVar const & RangeVar::operator = (RangeVar const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



closeKangarooSpace
