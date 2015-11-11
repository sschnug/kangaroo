/*!
	@file dvtabu.cpp
	@brief The implementation file for the DvTabu class.
	@details This is the implementation file for the DvTabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see tabu.hpp
*/



#include "cbls/tabus/dvtabu.hpp"



openKangarooSpace



/*!
	Return hash value for binary tuples of handles
*/
Hvl DvTabu::twinhash::iof(t2<Hdl,Hdl> const & theTwin)
{
	WatchError
	return mixHash(calcHash(theTwin.First), calcHash(theTwin.Second));
	CatchError
}



/*!
	Equal operator for terms.
*/
Bll DvTabu::twinequal::iof(t2<Hdl,Hdl> const & leftTerm, t2<Hdl,Hdl> const & rightTerm)
{
	WatchError
	return leftTerm.First == rightTerm.First && leftTerm.Second == rightTerm.Second;
	CatchError
}



/*!
	The duplicator.
*/
DvTabu::DvTabu(DvTabu const & that) : Tabu(that),
		mStates(that.mStates)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
DvTabu const & DvTabu::operator = (DvTabu const & that)
{
	WatchError
	if (this == &that)
		return *this;
	Throw(eUndefAssigner);
	return *this;
	CatchError
}



/*!
	Set up computation.
*/
void DvTabu::setupComputation()
{
	WatchError
	#if VarStateArray
	Warn(mTabuSys.varCount() < 2, eNotEnoughPairVars);
	Dim const tListCount = mTabuSys.varCount() - 1;
	mStates.allocateMem(tListCount);
	for(Itr tItr = 0; tItr < tListCount; ++tItr)
	{
		mStates.insert(kmm(tListCount - tItr));
		for(Itr sItr = 0; sItr < tListCount - tItr; ++sItr)
			mStates[tItr][sItr] = 0;
	}
	#endif
	CatchError
}





closeKangarooSpace
