/*!
	@file sv0tabu.cpp
	@brief The implementation file for the Sv0Tabu class.
	@details This is the implementation file for the Sv0Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see tabu.hpp
*/



#include "cbls/tabus/svtabus/sv0tabu.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
Sv0Tabu::Sv0Tabu(Sv0Tabu const & that) : SvTabu(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Sv0Tabu const & Sv0Tabu::operator = (Sv0Tabu const & that)
{
	WatchError
	if (this == &that)
		return *this;
	Throw(eUndefAssigner);
	return *this;
	CatchError
}



closeKangarooSpace
