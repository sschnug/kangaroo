/*!
	@file fcmhn.hpp
	@brief The prototype file for FcMHn class.
	@details This is the prototype file for FcMHn class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see fcmhn.cpp
	@see term.hpp
*/



#ifndef FcMHnHppIncluded
#define FcMHnHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/funcs/reg.hh"


openKangarooSpace



/*!
	@class FcMHn
	@brief A class to represent fcmhn terms that are constraints having metric and hint mins.
	@details This class represents fcmhn terms that are constraints having metric and hint mins.
*/
class FcMHn : public Func
{
	public:

		static FcMHn & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static FcMHn * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static FcMHn const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static FcMHn const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static Bll suit(Term const & theTerm);		//!< Suits casting?
		static Bll suit(Term const * theTerm);		//!< Suits casting?
		static Bll suit(Term & theTerm);			//!< Suits casting?
		static Bll suit(Term * theTerm);			//!< Suits casting?

		static FcMHn const & cast(Term const & theTerm);	//!< Perform casting.
		static FcMHn const * cast(Term const * theTerm);	//!< Perform casting.
		static FcMHn & cast(Term & theTerm);				//!< Perform casting.
		static FcMHn * cast(Term * theTerm);				//!< Perform casting.

		//! @}

	protected:

		FcMHn(Hdl const hdlSys, Dim const PrmCount);		//!< Constructor.
		FcMHn const & operator = (FcMHn const & that);	//!< Assigner.
		FcMHn(FcMHn const & that);						//!< Duplicator.
		virtual ~FcMHn();								//!< Destructor.

		//! @name Deferments
		//! @{

		#if CompLazy
		virtual void setupUndoArgs();					//!< Set up undo arguments.
		virtual void undoHint(Pos const thePos);		//!< Perform hint undo operation.
		#endif // CompLazy

		//! @}
};



/*!
	Whether a term is suitable for casting.
*/
inline Bll FcMHn::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FcMHn>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FcMHn::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FcMHn>::TermCat;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
inline Bll FcMHn::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FcMHn>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FcMHn::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FcMHn>::TermCat;
	CatchError
}


/*!
	Perform casting of a term.
*/
inline FcMHn const & FcMHn::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FcMHn>::TermCat, eWrongCat);

	return scast<FcMHn const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FcMHn const * FcMHn::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FcMHn>::TermCat, eWrongCat);

	return scast<FcMHn const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FcMHn & FcMHn::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FcMHn>::TermCat, eWrongCat);

	return scast<FcMHn &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FcMHn * FcMHn::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FcMHn>::TermCat, eWrongCat);

	return scast<FcMHn *>(theTerm);
	CatchError
}



/*!
	Refer to a fcmhn term.
*/
inline FcMHn & FcMHn::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fcmhn term.
*/
inline FcMHn * FcMHn::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a fcmhn term.
*/
inline FcMHn const & FcMHn::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fcmhn term.
*/
inline FcMHn const * FcMHn::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The constructor.
*/
inline FcMHn::FcMHn(Hdl const hdlSys, Dim const PrmCount) :
		Func(hdlSys, PrmCount)
{
	WatchError
	setTermCat(TermStub<FcMHn>::TermCat);
	CatchError
}



/*!
	The destructor.
*/
inline FcMHn::~FcMHn()
{
	WatchError
	//	nothing to be done.
	CatchError
}



closeKangarooSpace


#endif//FcMHnHppIncluded
