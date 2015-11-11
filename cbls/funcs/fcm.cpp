/*!
	@file fcm.cpp
	@brief The implementation file for the FcM class.
	@details This is the implementation file for the FcM class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see fcm.hpp
*/



#include "cbls/funcs/fcm.hpp"



openKangarooSpace




/*!
	The duplicator.
*/
FcM::FcM(FcM const & that) : Func(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
FcM const & FcM::operator = (FcM const & that)
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
void FcM::setupUndoArgs()
{
	WatchError
	setupEvalUndoArgs();
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	Set up undo parameters.
*/
void FcM::setupUndoPrms()
{
	WatchError
	setupEvalUndoPrms();
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	Perform hint undo operation.
*/
void FcM::undoHint(Pos const thePos)
{
	WatchError
	Throw(eUndefHintUndo);
	CatchError
}
#endif	//CompLazy


closeKangarooSpace
