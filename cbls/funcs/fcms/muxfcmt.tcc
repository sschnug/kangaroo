/*!
	@file muxfcmt.tcc
	@brief The prototype file for MuxFcMt template class.
	@details This is the prototype file for MuxFcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef MuxFcMtTccIncluded
#define MuxFcMtTccIncluded



#include "cbls/funcs/fcms/fcmt.tcc"


openKangarooSpace



/*!
	@class MuxFcMt
	@brief A template class to represent MuxFcMs.
	@details This template class represents MuxFcMs.
*/
template <typename fmt>
class MuxFcMt : public FcMt<fmt>
{
	protected:

		virtual ~MuxFcMt();												//!< Destructor.
		MuxFcMt(MuxFcMt<fmt> const & that);								//!< Duplicator.
		MuxFcMt(Hdl const hdlSys, Dim const PrmCount);					//!< Constructor.
		MuxFcMt<fmt> const & operator = (MuxFcMt<fmt> const & that);	//!< Assigner.

	protected:

		#if CompLazy
		virtual void undoEval(Pos const thePos);	//!< Eval undo for the parameter.
		#endif
};



/*!
	The constructor.
*/
template <typename fmt>
inline MuxFcMt<fmt>::MuxFcMt(Hdl const hdlSys, Dim const PrmCount) :
		FcMt<fmt>(hdlSys, PrmCount)
{
	WatchError
	#if SimulDnwdFlexi
	this->setupFlexiLabels();
	#endif
	CatchError
}



/*!
	The destructor.
*/
template <typename fmt>
inline MuxFcMt<fmt>::~MuxFcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
template <typename fmt>
MuxFcMt<fmt>::MuxFcMt(MuxFcMt<fmt> const & that) :
	FcMt<fmt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fmt>
MuxFcMt<fmt> const & MuxFcMt<fmt>::operator = (MuxFcMt<fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



#if CompLazy
/*!
	Unevaluate the effect of the parameter.
*/
template <typename fmt>
void MuxFcMt<fmt>::undoEval(Pos const thePos)
{
	WatchError
	Throw(eUndefEvalUndo);
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif	//MuxFcMtTccIncluded
