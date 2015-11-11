/*!
	@file flipvar.cpp
	@brief The implementation file for the FlipVar class.
	@details This is the implementation file for the FlipVar class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/vars/flipvar.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
FlipVar::FlipVar(FlipVar const & that) : Var(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
FlipVar const & FlipVar::operator = (FlipVar const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



closeKangarooSpace
