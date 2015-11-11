/*!
	@file sp.cpp
	@brief The implementation file for Sp class.
	@details This is the implementation file for Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/




#include "cbls/selcs/sp.hpp"


openKangarooSpace



/*!
	The constructor.
*/
Sp::Sp(Hdl const hdlSys, Dim const PrmCount) :
		Selc(hdlSys, PrmCount)
{
	WatchError
	setSelcCat(SelcStub< Sp >::SelcCat);
	CatchError
}



/*!
	The destructor.
*/
Sp::~Sp()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
Sp::Sp(Sp const & that) : Selc(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Sp const & Sp::operator = (Sp const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}


/*!
	Execute selection.
*/
void Sp::execute()
{
	WatchError
	Throw(eSelcNotExecReady);
	CatchError
}


closeKangarooSpace
