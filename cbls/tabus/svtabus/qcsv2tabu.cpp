/*!
	@file qcsv2tabu.cpp
	@brief The implementation file for the QcSv2Tabu class.
	@details This is the implementation file for the QcSv2Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/tabus/svtabus/qcsv2tabu.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
QcSv2Tabu::QcSv2Tabu(QcSv2Tabu const & that) : Sv2Tabu(that),
		mLength(that.mLength), mQueue(that.mQueue)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
QcSv2Tabu const & QcSv2Tabu::operator = (QcSv2Tabu const & that)
{
	WatchError
	if (this == &that)
		return *this;
	Throw(eUndefAssigner);
	return *this;
	CatchError
}



/*!
	Reset the states of the tabu vars.
*/
void QcSv2Tabu::reset()
{
	WatchError

	mUpdates.clear();
	Itr tItr = mQueue.beginQueue();
	while(tItr != mQueue.endQueue())
	{
		Hdl tHdl = mQueue[tItr];
		if (unsetTabuState(tHdl))
			mUpdates.insertMem(tHdl);
		tItr = mQueue.moveQueue(tItr);
	}
	mQueue.clear();
	if (mUpdates.itemCount())
		callbackFuncs();

	CatchError
}



/*!
	Set the length of the tabu variables.
*/
void QcSv2Tabu::setLength(Dim const theLength)
{
	WatchError
	mUpdates.clear();
	mLength = theLength;
	mActive = castBll(theLength);
	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		if (unsetTabuState(tHdl))
			mUpdates.insertMem(tHdl);
	}
	if (mUpdates.itemCount())
		callbackFuncs();
	CatchError
}



/*!
	Update the tabu variables and apply.
*/
void QcSv2Tabu::tabuVars(ll<Hdl,xmm> const & theAsgnVars)
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	mUpdates.clear();
	for(Idx tIdx = 0; tIdx < theAsgnVars.tagCount(); ++tIdx)
	{
		Hdl tHdl = theAsgnVars[tIdx];
		if (setTabuState(tHdl))
			mUpdates.insertMem(tHdl);
		mQueue.insertMem(tHdl);
	}
	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		if (unsetTabuState(tHdl))
			mUpdates.insertMem(tHdl);
	}
	if (mUpdates.itemCount())
		callbackFuncs();
	CatchError
}



/*!
	Update the tabu variable and apply.
*/
void QcSv2Tabu::tabuVar(Hdl const hdlVar)
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	mUpdates.clear();

	if (setTabuState(hdlVar))
		mUpdates.insertMem(hdlVar);
	mQueue.insertMem(hdlVar);

	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		if (unsetTabuState(tHdl))
			mUpdates.insertMem(tHdl);
	}
	if (mUpdates.itemCount())
		callbackFuncs();
	CatchError
}


/*!
	Update the two tabu variables and apply.
*/
void QcSv2Tabu::tabuVar2(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	Warn(hdlVar1 == hdlVar2, eVarsNotDifferent);

	mUpdates.clear();

	if (setTabuState(hdlVar1))
		mUpdates.insertMem(hdlVar1);
	mQueue.insertMem(hdlVar1);

	if (setTabuState(hdlVar2))
		mUpdates.insertMem(hdlVar2);
	mQueue.insertMem(hdlVar2);

	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		if (unsetTabuState(tHdl))
			mUpdates.insertMem(tHdl);
	}
	if (mUpdates.itemCount())
		callbackFuncs();
	CatchError
}



/*!
	Update the tabu variables and apply.
*/
void QcSv2Tabu::tabuVars(Hdl const * hdlVars, Dim const VarCount)
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	mUpdates.clear();
	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
	{
		#if CheckError
		for(Idx sIdx = tIdx + 1; sIdx < VarCount; ++sIdx)
			if (hdlVars[tIdx] == hdlVars[sIdx])
				Throw(eVarsNotDifferent);
		#endif

		Hdl tHdl = hdlVars[tIdx];
		if (setTabuState(tHdl))
			mUpdates.insertMem(tHdl);
		mQueue.insertMem(tHdl);
	}
	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		if (unsetTabuState(tHdl))
			mUpdates.insertMem(tHdl);
	}
	if (mUpdates.itemCount())
		callbackFuncs();
	CatchError
}



/*!
	Update tabu automatically.
*/
inline void QcSv2Tabu::updtTabuAuto()
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	ll<Hdl,xmm> const & tAsgnVars = mTabuSys.ExecAsgnVars();
	mUpdates.clear();
	for(Idx tIdx = 0; tIdx < tAsgnVars.tagCount(); ++tIdx)
	{
		Hdl tHdl = tAsgnVars[tIdx];
		if (setTabuState(tHdl))
			mUpdates.insertMem(tHdl);
		mQueue.insertMem(tHdl);
	}
	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		if (unsetTabuState(tHdl))
			mUpdates.insertMem(tHdl);
	}
	if (mUpdates.itemCount())
		callbackFuncs();
	CatchError
}



closeKangarooSpace
