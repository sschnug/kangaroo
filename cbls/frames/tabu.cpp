/*!
	@file tabu.cpp
	@brief The implementation file for Tabu class.
	@details This is the implementation file for Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 23.12.2009 QRL NICTA www.nicta.com.au
	@see tabu.hpp
*/



#include "cbls/frames/tabu.hpp"
#include "cbls/frames/sys.hpp"
#include "cbls/frames/func.hpp"


openKangarooSpace




/*!
	The constructor.
*/
Tabu::Tabu(Hdl const hdlSys) : TabuCat(TabuCatNil), TabuTyp(TabuTypNil), TabuCls(TabuClsNil), Callback(false),
		mTabuSys(Sys::refm(hdlSys)), mAutomatic(true), mActive(false)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
Tabu::Tabu(Tabu const & that) : TabuCat(that.TabuCat), TabuTyp(that.TabuTyp), TabuCls(that.TabuCls),
		Callback(that.Callback), mTabuSys(that.mTabuSys), mAutomatic(that.mAutomatic),
		mActive(false)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The destructor.
*/
Tabu::~Tabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
Tabu const & Tabu::operator = (Tabu const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	return *this;
	CatchError
}



/*!
	Define a tabu tbf.
*/
Bll Tabu::defSysTabu()
{
	WatchError
	return mTabuSys.defTabu(this);
	CatchError
}



/*!
	Register a callback function.
*/
void Tabu::regCallback(Func * theFunc)
{
	WatchError
	Throw(eUndefTabuCallback);
	CatchError
}



/*!
	Update a function's var tabu.
*/
void Tabu::callbackFuncs()
{
	WatchError
	Throw(eUndefTabuCallback);
	CatchError
}



/*!
	Call back a function for tabu update.
*/
void Tabu::callbackFunc(Func * theFunc)
{
	WatchError
	theFunc->computeTabuEffect();
	CatchError
}



/*!
	Synchronise clock
*/
void Tabu::syncExecClk()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Refer to a tabu.
*/
Tabu const & Tabu::refc(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return Sys::refc(hdlSys).refcTabu(typTabu);
	CatchError
}



/*!
	Point to a tabu.
*/
Tabu const * Tabu::ptrc(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return Sys::ptrc(hdlSys)->ptrcTabu(typTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
Tabu & Tabu::refm(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return Sys::refm(hdlSys).refmTabu(typTabu);
	CatchError
}



/*!
	Point to a tabu.
*/
Tabu * Tabu::ptrm(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return Sys::ptrm(hdlSys)->ptrmTabu(typTabu);
	CatchError
}



closeKangarooSpace

