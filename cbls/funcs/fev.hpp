/*!
	@file fev.hpp
	@brief The prototype file for FeV class.
	@details This is the prototype file for FeV class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see fev.cpp
	@see term.hpp
*/



#ifndef FeVHppIncluded
#define FeVHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/funcs/reg.hh"



openKangarooSpace


/*!
	@class FeV
	@brief A class to represent fev terms.
	@details This class represents fev terms.
*/
class FeV : public Func
{
	public:

		static FeV & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static FeV * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static FeV const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static FeV const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static FeV const & cast(Term const & theTerm);	//!< Perfom casting.
		static FeV const * cast(Term const * theTerm);	//!< Perfom casting.
		static FeV & cast(Term & theTerm);				//!< Perfom casting.
		static FeV * cast(Term * theTerm);				//!< Perfom casting.

		static Bll suit(Term const & theTerm);		//!< Suits casting?
		static Bll suit(Term const * theTerm);		//!< Suits casting?
		static Bll suit(Term & theTerm);			//!< Suits casting?
		static Bll suit(Term * theTerm);			//!< Suits casting?

		//! @}

	protected:

		FeV(Hdl const hdlSys, Dim const PrmCount);	//!< Constructor.
		FeV const & operator = (FeV const & that);	//!< Assigner.
		FeV(FeV const & that);						//!< Duplicator.
		virtual ~FeV();								//!< Destructor.

		//! @name Deferments
		//! @{

		#if CompLazy
		virtual void setupUndoArgs();				//!< Set up arguments for undo operation.
		virtual void setupUndoPrms();				//!< Set up parameters for undo operation.
		virtual void undoHint(Pos const thePos);	//!< Undo the hint effect of the parameter.
		#endif

		//! @}

	protected:

};



/*!
	Whether a term is suitable for casting.
*/
inline Bll FeV::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FeV>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FeV::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FeV>::TermCat;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
inline Bll FeV::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FeV>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FeV::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FeV>::TermCat;
	CatchError
}


/*!
	Perform casting of a term.
*/
inline FeV const & FeV::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FeV>::TermCat, eWrongCat);

	return scast<FeV const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FeV const * FeV::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FeV>::TermCat, eWrongCat);

	return scast<FeV const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FeV & FeV::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FeV>::TermCat, eWrongCat);

	return scast<FeV &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FeV * FeV::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FeV>::TermCat, eWrongCat);

	return scast<FeV *>(theTerm);
	CatchError
}



/*!
	Refer to a fev term.
*/
inline FeV & FeV::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fev term.
*/
inline FeV * FeV::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a fev term.
*/
inline FeV const & FeV::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fev term.
*/
inline FeV const * FeV::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The constructor.
*/
inline FeV::FeV(Hdl const hdlSys, Dim const PrmCount) :
		Func(hdlSys, PrmCount)
{
	WatchError
	setTermCat(TermStub<FeV>::TermCat);
	CatchError
}



/*!
	The destructor.
*/
inline FeV::~FeV()
{
	WatchError
	//	nothing to be done.
	CatchError
}



closeKangarooSpace


#endif//FeVHppIncluded
