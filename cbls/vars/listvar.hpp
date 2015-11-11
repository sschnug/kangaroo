/*!
	@file listvar.hpp
	@brief The prototype file for ListVar class.
	@details This is the prototype file for ListVar class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see listvar.cpp
*/



#ifndef ListVarHppIncluded
#define ListVarHppIncluded


#include "cbls/frames/idx.hh"


openKangarooSpace


dec tctn(ListVar, 23);	//!< Declare list variables.



/*!
	@class ListVar
	@brief A class to represent list variables
	@details This class represents list variables.
*/
class ListVar : public Var
{
	public:

		static ListVar & refm(Hdl const hdlSys, Hdl const hdlVar);			//!< Reference.
		static ListVar * ptrm(Hdl const hdlSys, Hdl const hdlVar);			//!< Pointer.
		static ListVar const & refc(Hdl const hdlSys, Hdl const hdlVar);	//!< Reference.
		static ListVar const * ptrc(Hdl const hdlSys, Hdl const hdlVar);	//!< Pointer.

		//! @name Casting
		//! @{

		static ListVar const & cast(Term const & theTerm);	//!< Perform casting.
		static ListVar const * cast(Term const * theTerm);	//!< Perform casting.
		static ListVar & cast(Term & theTerm);				//!< Perform casting.
		static ListVar * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);				//!< Suits casting?
		static Bll suit(Term const * theTerm);				//!< Suits casting?
		static Bll suit(Term & theTerm);					//!< Suits casting?
		static Bll suit(Term * theTerm);					//!< Suits casting?

		//! @}

	protected:

		virtual ~ListVar();									//!< Destructor.
		ListVar(Hdl const hdlSys);							//!< ListVarructor.
		ListVar(ListVar const & that);						//!< Duplicator.
		ListVar const & operator = (ListVar const & that);	//!< Assigner.
};



/*!
	The constructor.
*/
inline ListVar::ListVar(Hdl const hdlSys) :
		Var(hdlSys)
{
	WatchError
	setTermCat(TermStub<ListVar>::TermCat);
	CatchError
}


/*!
	The destructor.
*/
inline ListVar::~ListVar()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Refer to a list variable.
*/
inline ListVar const & ListVar::refc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcVar(hdlVar));
	CatchError
}



/*!
	Point to a list variable.
*/
inline ListVar const * ListVar::ptrc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcVar(hdlVar));
	CatchError
}



/*!
	Refer to a list variable.
*/
inline ListVar & ListVar::refm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmVar(hdlVar));
	CatchError
}



/*!
	Point to a list variable.
*/
inline ListVar * ListVar::ptrm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmVar(hdlVar));
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll ListVar::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<ListVar>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll ListVar::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<ListVar>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll ListVar::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<ListVar>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll ListVar::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<ListVar>::TermCat;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline ListVar const & ListVar::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<ListVar>::TermCat, eWrongCat);

	return scast<ListVar const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline ListVar const * ListVar::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<ListVar>::TermCat, eWrongCat);

	return scast<ListVar const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline ListVar & ListVar::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<ListVar>::TermCat, eWrongCat);

	return scast<ListVar &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline ListVar * ListVar::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<ListVar>::TermCat, eWrongCat);

	return scast<ListVar *>(theTerm);
	CatchError
}



closeKangarooSpace



#endif // ListVarHppIncluded
