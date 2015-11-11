/*!
	@file fcmhn.cpp
	@brief The implementation file for the FcMHn class.
	@details This is the implementation file for the FcMHn class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see fcmhn.hpp
*/



#include "cbls/funcs/fcmhn.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
FcMHn::FcMHn(FcMHn const & that) : Func(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
FcMHn const & FcMHn::operator = (FcMHn const & that)
{
	WatchError
	if (this == &that)
		return *this;

	Throw(eUndefAssigner);
	CatchError
}


#if CompLazy
/*!
	Set up undo arguments.
*/
void FcMHn::setupUndoArgs()
{
	WatchError
	setupEvalUndoArgs();
	setupHintUndoArgs();
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	Perform hint undo operation.
*/
void FcMHn::undoHint(Pos const thePos)
{
	WatchError
	Throw(eUndefHintUndo);
	CatchError
}
#endif	//CompLazy



closeKangarooSpace
