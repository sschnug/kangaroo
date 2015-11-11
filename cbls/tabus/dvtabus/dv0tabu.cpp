/*!
	@file dv0tabu.cpp
	@brief The implementation file for the Dv0Tabu class.
	@details This is the implementation file for the Dv0Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see tabu.hpp
*/



#include "cbls/tabus/dvtabus/dv0tabu.hpp"



openKangarooSpace




/*!
	The duplicator.
*/
Dv0Tabu::Dv0Tabu(Dv0Tabu const & that) : DvTabu(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Dv0Tabu const & Dv0Tabu::operator = (Dv0Tabu const & that)
{
	WatchError
	if (this == &that)
		return *this;
	Throw(eUndefAssigner);
	return *this;
	CatchError
}




closeKangarooSpace
