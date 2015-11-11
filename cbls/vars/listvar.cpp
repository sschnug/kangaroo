/*!
	@file listvar.cpp
	@brief The implementation file for the ListVar class.
	@details This is the implementation file for the ListVar class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/vars/listvar.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
ListVar::ListVar(ListVar const & that) : Var(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
ListVar const & ListVar::operator = (ListVar const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



closeKangarooSpace
