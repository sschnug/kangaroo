/*!
	@file hintrec.tcc
	@brief The source file for HintRec template class.
	@details This is the source file for HintRec template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef HintRecTccIncluded
#define HintRecTccIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/hintfld.tcc"



openKangarooSpace


/*!
	@class HintRec
	@brief A template class to represent hint records.
	@details This is a class to represent hint records.
*/
template<typename dat>
class HintRec
{
	public:
		~HintRec();														//!< Destructor.
		HintRec(Dim const VarCount);										//!< Constructor.
		HintRec(HintRec<dat> const & that);								//!< Duplicator.
		HintRec<dat> const & operator = (HintRec<dat> const & that);	//!< Assigner.

		//! @name Synchronisation
		//! @{

		void syncExecClk();												//!< Synchronise.

		//! @}

		//! @name Modification
		//! @{

		void resetHintDiff();											//!< Reset hint diff.
		void resetHintDiff(Clk const execClk);							//!< Reset hint diff.

		//! @}

		//! @name Data
		//! @{

		Bll HintDiff(Clk const execClk);								//!< Return diff valid.

		//! @}

	public:

		b1< HintFld<dat>,kmm > 	HintFlds;								//!< Hint fields.
		b1<Sqn, nmm> 			DiffSqns;								//!< Diff serials.
		Clk			 			DiffClk;								//!< Diff clock.
};



/*!
	The constructor.
*/
template<typename dat>
HintRec<dat>::HintRec(Dim const VarCount) :
		HintFlds(VarCount), DiffSqns(VarCount), DiffClk(NotClk)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
template<typename dat>
HintRec<dat>::HintRec(HintRec const & that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}





/*!
	The assigner.
*/
template<typename dat>
HintRec<dat> const & HintRec<dat>::operator = (HintRec const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}




/*!
	The destructor.
*/
template<typename dat>
HintRec<dat>::~HintRec()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Synchronise the execution clock.
*/
template<typename dat>
inline void HintRec<dat>::syncExecClk()
{
	WatchError
	if (DiffClk != InfClk)
		DiffClk = NotClk;
	for(Sqn tSqn = 0; tSqn < HintFlds.itemCount(); ++tSqn)
		HintFlds[tSqn].syncExecClk();
	CatchError
}



/*!
	Reset hint diff to false.
*/
template<typename dat>
inline void HintRec<dat>::resetHintDiff()
{
	WatchError
	DiffClk = NotClk;
	DiffSqns.clear();
	CatchError
}



/*!
	Reset hint diff to false.
*/
template<typename dat>
inline void HintRec<dat>::resetHintDiff(Clk const execClk)
{
	WatchError
	if (DiffClk != execClk)
		DiffClk = execClk;
	DiffSqns.clear();
	CatchError
}



/*!
	Return hint diff valid?
*/
template<typename dat>
inline Bll HintRec<dat>::HintDiff(Clk const execClk)
{
	WatchError
	return DiffClk == execClk && DiffSqns.itemCount();
	CatchError
}



closeKangarooSpace



#endif//HintRecTccIncluded
