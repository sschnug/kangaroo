/*!
	@file muxfevt.tcc
	@brief The prototype file for MuxFeVt template class.
	@details This is the prototype file for MuxFeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef MuxFeVtTccIncluded
#define MuxFeVtTccIncluded



#include "cbls/funcs/fevs/fevt.tcc"


openKangarooSpace



/*!
	@class MuxFeVt
	@brief A template class to represent MuxFeVs.
	@details This template class represents MuxFeVs.
*/
template <typename fvt>
class MuxFeVt : public FeVt<fvt>
{
	protected:

		virtual ~MuxFeVt();												//!< Destructor.
		MuxFeVt(MuxFeVt<fvt> const & that);								//!< Duplicator.
		MuxFeVt(Hdl const hdlSys, Dim const PrmCount);					//!< Constructor.
		MuxFeVt<fvt> const & operator = (MuxFeVt<fvt> const & that);	//!< Assigner.

	protected:

		#if CompLazy
		virtual void undoEval(Pos const thePos);	//!< Eval undo for the parameter.
		#endif
};



/*!
	The constructor.
*/
template <typename fvt>
inline MuxFeVt<fvt>::MuxFeVt(Hdl const hdlSys, Dim const PrmCount) :
		FeVt<fvt>(hdlSys, PrmCount)
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
template <typename fvt>
inline MuxFeVt<fvt>::~MuxFeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
template <typename fvt>
MuxFeVt<fvt>::MuxFeVt(MuxFeVt<fvt> const & that) :
	FeVt<fvt>(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fvt>
MuxFeVt<fvt> const & MuxFeVt<fvt>::operator = (MuxFeVt<fvt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



#if CompLazy
/*!
	Unevaluate the effect of the parameter.
*/
template <typename fvt>
void MuxFeVt<fvt>::undoEval(Pos const thePos)
{
	WatchError
	Throw(eUndefEvalUndo);
	CatchError
}
#endif	//CompLazy


closeKangarooSpace


#endif	//MuxFeVtTccIncluded
