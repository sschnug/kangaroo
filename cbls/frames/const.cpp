/*!
	@file const.cpp
	@brief The implementation file for the Const class.
	@details This is the implementation file for the Const class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see const.hpp
*/



#include "cbls/frames/const.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
Const::Const(Const const & that) : Term(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Const const & Const::operator = (Const const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Perform anew execution.
*/
void Const::execAnew()
{
	WatchError
	Throw(eUndefExecAnew);
	CatchError
}



/*!
	Perform anew simulation.
*/
void Const::simulAnew()
{
	WatchError
	Throw(eUndefSimulAnew);
	CatchError
}



/*!
	Perform incremental execution.
*/
void Const::execIncr()
{
	WatchError
	Throw(eUndefExecIncr);
	CatchError
}



/*!
	Perform incremental simulation.
*/
void Const::simulIncr()
{
	WatchError
	Throw(eUndefSimulIncr);
	CatchError
}



#if CompLazy
/*!
	Perform backlog execution.
*/
void Const::execBklg()
{
	WatchError
	Throw(eUndefExecBklg);
	CatchError
}
#endif



#if CompLazy
/*!
	Perform backlog emulation.
*/
void Const::emulBklg()
{
	WatchError
	Throw(eUndefEmulBklg);
	CatchError
}
#endif



closeKangarooSpace
