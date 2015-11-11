/*!
	@file qcdv0tabu.cpp
	@brief The implementation file for the QcDv0Tabu class.
	@details This is the implementation file for the QcDv0Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/tabus/dvtabus/qcdv0tabu.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
QcDv0Tabu::QcDv0Tabu(QcDv0Tabu const & that) : Dv0Tabu(that),
		mLength(that.mLength), mQueue(that.mQueue)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
QcDv0Tabu const & QcDv0Tabu::operator = (QcDv0Tabu const & that)
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
void QcDv0Tabu::reset()
{
	WatchError

	Itr tItr = mQueue.beginQueue();
	while(tItr != mQueue.endQueue())
	{
		t2<Hdl,Hdl> tTwin = mQueue[tItr];
		unsetTabuState(tTwin);
		tItr = mQueue.moveQueue(tItr);
	}
	mQueue.clear();

	CatchError
}



/*!
	Set the length of the tabu variables.
*/
void QcDv0Tabu::setLength(Dim const theLength)
{
	WatchError
	mLength = theLength;
	mActive = castBll(theLength);
	t2<Hdl,Hdl> tTwin(InvHdl,InvHdl);
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tTwin);
		unsetTabuState(tTwin);
	}
	CatchError
}



/*!
	Update the tabu variables and apply.
*/
void QcDv0Tabu::tabuVars(ll<Hdl,xmm> const & theAsgnVars)
{
	WatchError
	Warn(!mActive, eTabuNotActive);
	Warn(theAsgnVars.tagCount() % 2, eNotEnoughPairVars);

	for(Idx tIdx = 0; tIdx < theAsgnVars.tagCount(); tIdx += 2)
	{
		t2<Hdl,Hdl> tTwin = convVarHdls(theAsgnVars[tIdx], theAsgnVars[tIdx + 1]);
		setTabuState(tTwin);
		mQueue.insertMem(tTwin);
	}
	t2<Hdl,Hdl> tTwin(InvHdl,InvHdl);
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tTwin);
		unsetTabuState(tTwin);
	}
	CatchError
}



/*!
	Update the two tabu variables and apply.
*/
void QcDv0Tabu::tabuVar2(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(!mActive, eTabuNotActive);
	Warn(hdlVar1 == hdlVar2, eVarsNotDifferent);

	t2<Hdl,Hdl> tTwin = convVarHdls(hdlVar1, hdlVar2);

	setTabuState(tTwin);
	mQueue.insertMem(tTwin);

	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tTwin);
		unsetTabuState(tTwin);
	}
	CatchError
}



/*!
	Update the tabu variables and apply.
*/
void QcDv0Tabu::tabuVars(Hdl const * hdlVars, Dim const VarCount)
{
	WatchError
	Warn(!mActive, eTabuNotActive);

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
		setTabuState(tTwin);
		mQueue.insertMem(tTwin);
	}
	t2<Hdl,Hdl> tTwin(InvHdl,InvHdl);
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tTwin);
		unsetTabuState(tTwin);
	}
	CatchError
}



/*!
	Update tabu automatically.
*/
inline void QcDv0Tabu::updtTabuAuto()
{
	WatchError
	Warn(!mActive, eTabuNotActive);

	ll<Hdl,xmm> const & tAsgnVars = mTabuSys.ExecAsgnVars();
	Warn(tAsgnVars.tagCount() % 2, eNotEnoughPairVars);

	for(Idx tIdx = 0; tIdx < tAsgnVars.tagCount(); tIdx +=2 )
	{
		t2<Hdl,Hdl> tTwin = convVarHdls(tAsgnVars[tIdx], tAsgnVars[tIdx + 1]);
		setTabuState(tTwin);
		mQueue.insertMem(tTwin);
	}
	t2<Hdl,Hdl> tTwin(InvHdl,InvHdl);
	while(mQueue.itemCount() > mLength)
	{
		mQueue.remove(tTwin);
		unsetTabuState(tTwin);
	}
	CatchError
}



closeKangarooSpace
