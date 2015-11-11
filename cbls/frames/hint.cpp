/*!
	@file hint.cpp
	@brief The implementation file for Hint class.
	@details This is the implementation file for Hint class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 23.12.2009 QRL NICTA www.nicta.com.au
	@see hint.hpp
*/



#include "cbls/frames/hint.hpp"
#include "cbls/frames/sys.hpp"



openKangarooSpace




/*!
	The constructor.
*/
Hint::Hint(Hdl const hdlSys, Srl const srlType) :
	TypeSrl(srlType), mHintSys(Sys::refm(hdlSys))
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
Hint::Hint(Hint const & that) : TypeSrl(that.TypeSrl),
		mHintSys(that.mHintSys)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The destructor.
*/
Hint::~Hint()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
Hint const & Hint::operator = (Hint const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}




/*!
	Define a hint.
*/
Bll Hint::defSysHint()
{
	WatchError
	return mHintSys.defHint(this);
	CatchError
}



/*!
	Refer to a hint.
*/
Hint const & Hint::refc(Hdl const hdlSys, Srl const srlType)
{
	WatchError
	return Sys::refc(hdlSys).refcHint(srlType);
	CatchError
}



/*!
	Point to a hint.
*/
Hint const * Hint::ptrc(Hdl const hdlSys, Srl const srlType)
{
	WatchError
	return Sys::ptrc(hdlSys)->ptrcHint(srlType);
	CatchError
}



/*!
	Refer to a hint.
*/
Hint & Hint::refm(Hdl const hdlSys, Srl const srlType)
{
	WatchError
	return Sys::refm(hdlSys).refmHint(srlType);
	CatchError
}



/*!
	Point to a hint.
*/
Hint * Hint::ptrm(Hdl const hdlSys, Srl const srlType)
{
	WatchError
	return Sys::ptrm(hdlSys)->ptrmHint(srlType);
	CatchError
}



closeKangarooSpace

