/*!
	@file vvtabu.cpp
	@brief The implementation file for the VvTabu class.
	@details This is the implementation file for the VvTabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see tabu.hpp
*/



#include "cbls/tabus/vvtabu.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
VvTabu::VvTabu(VvTabu const & that) : Tabu(that),
		mStates(that.mStates)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
VvTabu const & VvTabu::operator = (VvTabu const & that)
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
void VvTabu::setupComputation()
{
	WatchError
	#if VarStateArray
	mStates.allocateMem(mTabuSys.varCount());
	for(Hdl tHdl = 0; tHdl < mTabuSys.varCount(); ++tHdl)
		mStates.insert(0);
	#endif
	CatchError
}



closeKangarooSpace
