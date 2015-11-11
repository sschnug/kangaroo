/*!
	@file prm.cpp
	@brief The implementation file for the Prm class.
	@details This is the implementation file for the Prm class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see prm.hpp
*/



#include "cbls/frames/prm.hpp"
#include "cbls/frames/term.hpp"


openKangarooSpace




/*!
	The duplicator.
*/
Prm::Prm(Prm const & that) : TermGen(that.TermGen),
		TermHdl(that.TermHdl), PrmSpec(that.PrmSpec)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
Prm const & Prm::operator = (Prm const & that)
{
	WatchError
	if (this == &that) return *this;
	ccast<Gen &>(TermGen) = that.TermGen;
	ccast<Hdl &>(TermHdl) = that.TermHdl;
	ccast<Pss &>(PrmSpec) = that.PrmSpec;
	return *this;
	CatchError
}



closeKangarooSpace
