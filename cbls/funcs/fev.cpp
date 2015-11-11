/*!
	@file fev.cpp
	@brief The implementation file for the FeV class.
	@details This is the implementation file for the FeV class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see fev.hpp
*/



#include "cbls/funcs/fev.hpp"



openKangarooSpace




/*!
	The duplicator.
*/
FeV::FeV(FeV const & that) : Func(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
FeV const & FeV::operator = (FeV const & that)
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
void FeV::setupUndoArgs()
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
void FeV::setupUndoPrms()
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
void FeV::undoHint(Pos const thePos)
{
	WatchError
	Throw(eUndefHintUndo);
	CatchError
}
#endif	//CompLazy



closeKangarooSpace
