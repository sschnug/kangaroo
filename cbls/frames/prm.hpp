/*!
	@file prm.hpp
	@brief The prototype file for Prm class.
	@details This is the prototype file for Prm class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 03.01.2010 QRL NICTA www.nicta.com.au
	@see prm.cpp
*/



#ifndef PrmHppIncluded
#define PrmHppIncluded



#include "cbls/frames/dat.hpp"
#include "cbls/frames/spec.hpp"


openKangarooSpace


/*
	Forward declaration.
*/
class Term;



/*!
	@class Prm
	@brief A class to represent term prms.
	@details This class represents parameters.
*/
class Prm
{
	public:
		Prm();											//!< Constructor.
		Prm(Prm const & that);							//!< Duplicator.
		Prm(Gen const genTerm, Hdl const hdlTerm);		//!< Initialiser.
		Prm(Gen const genTerm, Hdl const hdlTerm,
								Pss const thePss);		//!< Initialiser.
		Prm const & operator = (Prm const & that);		//!< Assigner.
		~Prm();											//!< Destructor.

		static Prm InvPrm();							//!< Return an 'invalid' param

		Bll valid() const;								//!< Valid?
		Prm const & refc() const;						//!< Reference.
		Prm const * ptrc() const;						//!< Pointer.
		Prm & refm();									//!< Reference.
		Prm * ptrm();									//!< Pointer.

		Bll operator == (Prm const & that) const;		//!< Equal.
		Bll operator != (Prm const & that) const;		//!< Not equal.
		Bll operator < (Prm const & that) const;		//!< Less than.
		Bll operator > (Prm const & that) const;		//!< Greater than.
		Bll operator <= (Prm const & that) const;		//!< Less equal.
		Bll operator >= (Prm const & that) const;		//!< Greater equal.

		Gen const TermGen;								//!< Term genus.
		Hdl const TermHdl;								//!< Term handle.
		Pss const PrmSpec;								//!< Parameter specification.
};



/*!
	The constructor.
*/
inline Prm::Prm() : TermGen(Tv), TermHdl(InvHdl), PrmSpec(DfltPsm)
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	The initialiser.
*/
inline Prm::Prm(Gen const genTerm, Hdl const hdlTerm) :
		TermGen(genTerm), TermHdl(hdlTerm), PrmSpec(DfltPsm)
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	The initialiser.
*/
inline Prm::Prm(Gen const genTerm, Hdl const hdlTerm, Pss const thePrmSpec) :
		TermGen(genTerm), TermHdl(hdlTerm), PrmSpec(thePrmSpec)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
inline Prm::~Prm()
{
	WatchError
	//	nothing to be done.
	CatchError
}

/*!
	Return an 'invalid' param
*/
inline Prm Prm::InvPrm()
{
	WatchError
	return Prm(Tu, InvHdl);
	CatchError
}

/*!
	The equal-to operator.
*/
inline Bll Prm::operator == (Prm const & that) const
{
	WatchError
	return TermGen == that.TermGen &&
		TermHdl == that.TermHdl && PrmSpec == that.PrmSpec;
	CatchError
}



/*!
	The not-equal operator.
*/
inline Bll Prm::operator != (Prm const & that) const
{
	WatchError
	return TermGen != that.TermGen ||
			TermHdl != that.TermHdl || PrmSpec != that.PrmSpec;
	CatchError
}



/*!
	The less-than operator.
*/
inline Bll Prm::operator < (Prm const & that) const
{
	WatchError
	return TermGen <  that.TermGen ||
		(TermGen == that.TermGen && (TermHdl < that.TermHdl ||
			(TermHdl == that.TermHdl && PrmSpec < that.PrmSpec)));
	CatchError
}



/*!
	The greater-than operator.
*/
inline Bll Prm::operator > (Prm const & that) const
{
	WatchError
	return TermGen >  that.TermGen ||
		(TermGen == that.TermGen && (TermHdl > that.TermHdl ||
			(TermHdl == that.TermHdl && PrmSpec > that.PrmSpec)));
	CatchError
}



/*!
	The less-equal operator.
*/
inline Bll Prm::operator <= (Prm const & that) const
{
	WatchError
	return TermGen <  that.TermGen ||
		(TermGen == that.TermGen && (TermHdl < that.TermHdl ||
			(TermHdl == that.TermHdl && PrmSpec <= that.PrmSpec)));
	CatchError
}



/*!
	The greater-equal operator.
*/
inline Bll Prm::operator >= (Prm const & that) const
{
	WatchError
	return TermGen >  that.TermGen ||
		(TermGen == that.TermGen && (TermHdl > that.TermHdl ||
			(TermHdl == that.TermHdl && PrmSpec >= that.PrmSpec)));
	CatchError
}



/*!
	Whether valid?
*/
inline Bll Prm::valid() const
{
	WatchError
	return (TermHdl != InvHdl) || (TermGen == Tu);
	CatchError
}


/*!
	Return pointer.
*/
inline Prm const * Prm::ptrc() const
{
	WatchError
	return this;
	CatchError
}



/*!
	Return reference.
*/
inline Prm const & Prm::refc() const
{
	WatchError
	return *this;
	CatchError
}




/*!
	Return pointer.
*/
inline Prm * Prm::ptrm()
{
	WatchError
	return this;
	CatchError
}



/*!
	Return reference.
*/
inline Prm & Prm::refm()
{
	WatchError
	return *this;
	CatchError
}



closeKangarooSpace



#endif // PrmHppIncluded
