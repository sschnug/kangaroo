/*!
	@file qcsv0tabu.cpp
	@brief The implementation file for the QcSv0Tabu class.
	@details This is the implementation file for the QcSv0Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/tabus/svtabus/qcsv0tabu.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
QcSv0Tabu::QcSv0Tabu(QcSv0Tabu const & that) : Sv0Tabu(that),
		mLength(that.mLength), mQueue(that.mQueue)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
QcSv0Tabu const & QcSv0Tabu::operator = (QcSv0Tabu const & that)
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
void QcSv0Tabu::reset()
{
	WatchError
	Itr tItr = mQueue.beginQueue();
	while(tItr != mQueue.endQueue())
	{
		Hdl tHdl = mQueue[tItr];
		unsetTabuState(tHdl);
		tItr = mQueue.moveQueue(tItr);
	}
	mQueue.clear();
	CatchError
}



/*!
	Set the length of the tabu variables.
*/
void QcSv0Tabu::setLength(Dim const theLength)
{
	WatchError
	mLength = theLength;
	mActive = castBll(theLength);
	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		unsetTabuState(tHdl);
	}
	CatchError
}



/*!
	Update the tabu variables and apply.
*/
void QcSv0Tabu::tabuVars(ll<Hdl,xmm> const & theAsgnVars)
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	for(Idx tIdx = 0; tIdx < theAsgnVars.tagCount(); ++tIdx)
	{
		Hdl tHdl = theAsgnVars[tIdx];
		setTabuState(tHdl);
		mQueue.insertMem(tHdl);
	}
	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		unsetTabuState(tHdl);
	}
	CatchError
}



/*!
	Update the tabu variable and apply.
*/
void QcSv0Tabu::tabuVar(Hdl const hdlVar)
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	setTabuState(hdlVar);
	mQueue.insertMem(hdlVar);

	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		unsetTabuState(tHdl);
	}
	CatchError
}


/*!
	Update the two tabu variables and apply.
*/
void QcSv0Tabu::tabuVar2(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	Warn(hdlVar1 == hdlVar2, eVarsNotDifferent);

	setTabuState(hdlVar1);
	mQueue.insertMem(hdlVar1);

	setTabuState(hdlVar2);
	mQueue.insertMem(hdlVar2);

	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		unsetTabuState(tHdl);
	}
	CatchError
}



/*!
	Update the tabu variables and apply.
*/
void QcSv0Tabu::tabuVars(Hdl const * hdlVars, Dim const VarCount)
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	for(Idx tIdx = 0; tIdx < VarCount; ++tIdx)
	{
		#if CheckError
		for(Idx sIdx = tIdx + 1; sIdx < VarCount; ++sIdx)
			if (hdlVars[tIdx] == hdlVars[sIdx])
				Throw(eVarsNotDifferent);
		#endif

		Hdl tHdl = hdlVars[tIdx];
		setTabuState(tHdl);
		mQueue.insertMem(tHdl);
	}
	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		unsetTabuState(tHdl);
	}
	CatchError
}



/*!
	Update tabu automatically.
*/
inline void QcSv0Tabu::updtTabuAuto()
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	ll<Hdl,xmm> const & tAsgnVars = mTabuSys.ExecAsgnVars();
	for(Idx tIdx = 0; tIdx < tAsgnVars.tagCount(); ++tIdx)
	{
		Hdl tHdl = tAsgnVars[tIdx];
		setTabuState(tHdl);
		mQueue.insertMem(tHdl);
	}
	Hdl tHdl = InvHdl;
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tHdl);
		unsetTabuState(tHdl);
	}
	CatchError
}



closeKangarooSpace
