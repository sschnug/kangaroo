/*!
	@file lock.cpp
	@brief The implementation file for the Lock class.
	@details This is the implementation file for the Lock class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see lock.hpp
*/



#include "cbls/frames/lock.hpp"
#include "cbls/frames/func.hpp"
#include "cbls/frames/var.hpp"


openKangarooSpace




/*!
	The duplicator.
*/
Lock::Lock(Lock const & that) : mUpdates(that.mUpdates),
		mFuncs(that.mFuncs), mVars(that.mVars)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Lock const & Lock::operator = (Lock const & that)
{
	WatchError
	if (this == &that)
		return *this;
	Throw(eUndefAssigner);
	return *this;
	CatchError
}



/*!
	Refer to a lock.
*/
Lock & Lock::refm(Hdl const hdlSys)
{
	WatchError
	return Sys::refm(hdlSys).refmLock();
	CatchError
}



/*!
	Point to a lock.
*/
Lock * Lock::ptrm(Hdl const hdlSys)
{
	WatchError
	return Sys::ptrm(hdlSys)->ptrmLock();
	CatchError
}



/*!
	Refer to a lock.
*/
Lock const & Lock::refc(Hdl const hdlSys)
{
	WatchError
	return Sys::refc(hdlSys).refcLock();
	CatchError
}



/*!
	Point to a lock.
*/
Lock const * Lock::ptrc(Hdl const hdlSys)
{
	WatchError
	return Sys::ptrc(hdlSys)->ptrcLock();
	CatchError
}



/*!
	The States of the lock variables.
*/
Bll Lock::Status(Hdl const hdlVar) const
{
	WatchError
	return mVars.item(hdlVar)->locked();
	CatchError
}



/*!
	Reset the locking states of the variables.
*/
void Lock::reset()
{
	WatchError

	mUpdates.clear();
	for(Hdl tHdl = 0; tHdl < mVars.itemCount(); ++tHdl)
	{
		Var * tVar = mVars.item(tHdl);
		if (tVar->locked())
		{
			mUpdates.insertMem(tHdl);
			tVar->lock(false);
			// the above also ensures when reset operation is allowed.
		}
	}
	if (mUpdates.itemCount())
		for (Idx tIdx = 0; tIdx < mFuncs.itemCount(); ++tIdx)
			mFuncs[tIdx]->computeLockEffect();
	CatchError
}



/*!
	Set the locking state of the variable.
*/
void Lock::set(Hdl const hdlVar, Bll const SetNotUnset)
{
	WatchError
	mUpdates.clear();
	Var * tVar = mVars.item(hdlVar);
	if (tVar->locked() != SetNotUnset)
	{
		tVar->lock(SetNotUnset);
		// the above also ensures when set operation is allowed.
		mUpdates.insertMem(hdlVar);
		if (mUpdates.itemCount())
			for (Idx tIdx = 0; tIdx < mFuncs.itemCount(); ++tIdx)
				mFuncs[tIdx]->computeLockEffect();
	}
	CatchError
}



/*!
	Set the locking states of the variables.
*/
void Lock::set(Hdl const hdlVar1,
		Hdl const hdlVar2, Bll const SetNotUnset)
{
	WatchError
	Warn(hdlVar1 == hdlVar2, eVarsNotDifferent);

	mUpdates.clear();
	Var * tVar1 = mVars.item(hdlVar1);
	if (tVar1->locked() != SetNotUnset)
	{
		mVars.item(hdlVar1)->lock(SetNotUnset);
		// the above also ensures when set operation is allowed.
		mUpdates.insertMem(hdlVar1);
	}
	Var * tVar2 = mVars.item(hdlVar1);
	if (tVar2->locked() != SetNotUnset)
	{
		mVars.item(hdlVar2)->lock(SetNotUnset);
		mUpdates.insertMem(hdlVar2);
	}
	if (mUpdates.itemCount())
		for (Idx tIdx = 0; tIdx < mFuncs.itemCount(); ++tIdx)
			mFuncs[tIdx]->computeLockEffect();
	CatchError
}



/*!
	Set the locking states of the variables.
*/
void Lock::set(Hdl const * hdlVars,
		Dim const VarCount, Bll const SetNotUnset)
{
	WatchError

	mUpdates.clear();
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
	{
		Hdl tHdl = hdlVars[tIdx];
		#if CheckError
			for(Idx sIdx = tIdx + 1; sIdx < VarCount; ++sIdx)
				if (hdlVars[sIdx] == tHdl)
					Throw(eVarsNotDifferent);
		#endif
		Var * tVar = mVars.item(tHdl);
		if (tVar->locked() != SetNotUnset)
		{
			mVars.item(tHdl)->lock(SetNotUnset);
			// the above also ensures when set operation is allowed.
			mUpdates.insertMem(tHdl);
		}
	}
	if (mUpdates.itemCount())
		for (Idx tIdx = 0; tIdx < mFuncs.itemCount(); ++tIdx)
			mFuncs[tIdx]->computeLockEffect();
	CatchError
}




closeKangarooSpace
