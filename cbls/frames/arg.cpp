/*!
	@file arg.cpp
	@brief The implementation file for the Arg class.
	@details This is the implementation file for the Arg class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see arg.hpp
*/



#include "cbls/frames/arg.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
Arg::Arg(Arg const & that) : ArgFunc(that.ArgFunc),
			ArgPos(that.ArgPos)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
Arg const & Arg::operator = (Arg const & that)
{
	WatchError
	if (this == &that) return *this;
	ccast<Func * &>(ArgFunc) = that.ArgFunc;
	ccast<Pos &>(ArgPos) = that.ArgPos;
	return *this;
	CatchError
}



closeKangarooSpace
