/*!
	@file qcdv2tabu.cpp
	@brief The implementation file for the QcDv2Tabu class.
	@details This is the implementation file for the QcDv2Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/tabus/dvtabus/qcdv2tabu.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
QcDv2Tabu::QcDv2Tabu(QcDv2Tabu const & that) : Dv2Tabu(that),
		mLength(that.mLength), mQueue(that.mQueue)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
QcDv2Tabu const & QcDv2Tabu::operator = (QcDv2Tabu const & that)
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
void QcDv2Tabu::reset()
{
	WatchError

	mUpdates.clear();
	Itr tItr = mQueue.beginQueue();
	while(tItr != mQueue.endQueue())
	{
		t2<Hdl,Hdl> tTwin = mQueue[tItr];
		if (unsetTabuState(tTwin))
			mUpdates.insertMem(tTwin);
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
void QcDv2Tabu::setLength(Dim const theLength)
{
	WatchError
	mUpdates.clear();
	mLength = theLength;
	mActive = castBll(theLength);
	t2<Hdl,Hdl> tTwin(InvHdl,InvHdl);
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tTwin);
		if (unsetTabuState(tTwin))
			mUpdates.insertMem(tTwin);
	}
	if (mUpdates.itemCount())
		callbackFuncs();
	CatchError
}



/*!
	Update the tabu variables and apply.
*/
void QcDv2Tabu::tabuVars(ll<Hdl,xmm> const & theAsgnVars)
{
	WatchError
	Warn(!mActive, eTabuNotActive);
	Warn(theAsgnVars.tagCount() % 2, eNotEnoughPairVars);

	mUpdates.clear();
	for(Idx tIdx = 0; tIdx < theAsgnVars.tagCount(); tIdx += 2)
	{
		t2<Hdl,Hdl> tTwin = convVarHdls(theAsgnVars[tIdx], theAsgnVars[tIdx + 1]);
		if (setTabuState(tTwin))
			mUpdates.insertMem(tTwin);
		mQueue.insertMem(tTwin);
	}
	t2<Hdl,Hdl> tTwin(InvHdl,InvHdl);
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tTwin);
		if (unsetTabuState(tTwin))
			mUpdates.insertMem(tTwin);
	}
	if (mUpdates.itemCount())
		callbackFuncs();
	CatchError
}



/*!
	Update the two tabu variables and apply.
*/
void QcDv2Tabu::tabuVar2(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(!mActive, eTabuNotActive);
	Warn(hdlVar1 == hdlVar2, eVarsNotDifferent);

	mUpdates.clear();
	t2<Hdl,Hdl> tTwin = convVarHdls(hdlVar1, hdlVar2);

	if (setTabuState(tTwin))
		mUpdates.insertMem(tTwin);
	mQueue.insertMem(tTwin);

	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tTwin);
		if (unsetTabuState(tTwin))
			mUpdates.insertMem(tTwin);
	}

	if (mUpdates.itemCount())
		callbackFuncs();
	CatchError
}



/*!
	Update the tabu variables and apply.
*/
void QcDv2Tabu::tabuVars(Hdl const * hdlVars, Dim const VarCount)
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	mUpdates.clear();
	for(Idx tIdx = 0; tIdx < VarCount; tIdx += 2)
	{
		#if CheckError
		for(Idx sIdx = tIdx + 1; sIdx < VarCount; ++sIdx)
			if (hdlVars[tIdx] == hdlVars[sIdx])
				Throw(eVarsNotDifferent);
		for(Idx sIdx = tIdx + 2; sIdx < VarCount; ++sIdx)
			if (hdlVars[tIdx + 1] == hdlVars[sIdx])
				Throw(eVarsNotDifferent);
		#endif

		t2<Hdl,Hdl> tTwin = convVarHdls(hdlVars[tIdx], hdlVars[tIdx + 1]);
		if (setTabuState(tTwin))
			mUpdates.insertMem(tTwin);
		mQueue.insertMem(tTwin);
	}
	t2<Hdl,Hdl> tTwin(InvHdl,InvHdl);
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tTwin);
		if (unsetTabuState(tTwin))
			mUpdates.insertMem(tTwin);
	}
	if (mUpdates.itemCount())
		callbackFuncs();
	CatchError
}



/*!
	Update tabu automatically.
*/
inline void QcDv2Tabu::updtTabuAuto()
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	ll<Hdl,xmm> const & tAsgnVars = mTabuSys.ExecAsgnVars();
	Warn(tAsgnVars.tagCount() % 2, eNotEnoughPairVars);

	mUpdates.clear();
	for(Idx tIdx = 0; tIdx < tAsgnVars.tagCount(); tIdx +=2 )
	{
		t2<Hdl,Hdl> tTwin = convVarHdls(tAsgnVars[tIdx], tAsgnVars[tIdx + 1]);
		if (setTabuState(tTwin))
			mUpdates.insertMem(tTwin);
		mQueue.insertMem(tTwin);
	}
	t2<Hdl,Hdl> tTwin(InvHdl,InvHdl);
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tTwin);
		if (unsetTabuState(tTwin))
			mUpdates.insertMem(tTwin);
	}
	if (mUpdates.itemCount())
		callbackFuncs();
	CatchError
}



closeKangarooSpace
