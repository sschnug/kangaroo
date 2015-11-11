/*!
	@file sf.cpp
	@brief The implementation file for Sf class.
	@details This is the implementation file for Sf class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/selcs/sf.hpp"


openKangarooSpace



/*!
	The constructor.
*/
Sf::Sf(Hdl const hdlSys, Dim const PrmCount) :
		Selc(hdlSys, PrmCount)
{
	WatchError
	setSelcCat(SelcStub< Sf >::SelcCat);
	setExecReady(true);
	CatchError
}



/*!
	The destructor.
*/
Sf::~Sf()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
Sf::Sf(Sf const & that) : Selc(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Sf const & Sf::operator = (Sf const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



closeKangarooSpace
