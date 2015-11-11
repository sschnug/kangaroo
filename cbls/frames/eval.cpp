/*!
	@file eval.cpp
	@brief The implementation file for Eval class.
	@details This is the implementation file for Eval class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 23.12.2009 QRL NICTA www.nicta.com.au
	@see eval.hpp
*/



#include "cbls/frames/eval.hpp"
#include "cbls/frames/sys.hpp"



openKangarooSpace




/*!
	The constructor.
*/
Eval::Eval(Hdl const hdlSys, Srl const srlType) :
		TypeSrl(srlType), mEvalSys(Sys::refm(hdlSys))
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
Eval::Eval(Eval const & that) : TypeSrl(that.TypeSrl),
		mEvalSys(that.mEvalSys)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The destructor.
*/
Eval::~Eval()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
Eval const & Eval::operator = (Eval const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Define an eval table.
*/
Bll Eval::defSysEval()
{
	WatchError
	return mEvalSys.defEval(this);
	CatchError
}



/*!
	Refer to an eval.
*/
Eval const & Eval::refc(Hdl const hdlSys, Srl const srlType)
{
	WatchError
	return Sys::refc(hdlSys).refcEval(srlType);
	CatchError
}



/*!
	Point to an eval.
*/
Eval const * Eval::ptrc(Hdl const hdlSys, Srl const srlType)
{
	WatchError
	return Sys::ptrc(hdlSys)->ptrcEval(srlType);
	CatchError
}



/*!
	Refer to an eval.
*/
Eval & Eval::refm(Hdl const hdlSys, Srl const srlType)
{
	WatchError
	return Sys::refm(hdlSys).refmEval(srlType);
	CatchError
}



/*!
	Point to an eval.
*/
Eval * Eval::ptrm(Hdl const hdlSys, Srl const srlType)
{
	WatchError
	return Sys::ptrm(hdlSys)->ptrmEval(srlType);
	CatchError
}



closeKangarooSpace

