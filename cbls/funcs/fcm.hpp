/*!
	@file fcm.hpp
	@brief The prototype file for FcM class.
	@details This is the prototype file for FcM class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see fcm.cpp
	@see term.hpp
*/



#ifndef FcMHppIncluded
#define FcMHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/funcs/reg.hh"



openKangarooSpace



/*!
	@class FcM
	@brief A class to represent fcm terms that are constraints producing metrics.
	@details This class represents fcm terms that are constraints producing metrics.
*/
class FcM : public Func
{
	public:

		static FcM & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static FcM * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static FcM const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static FcM const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static FcM const & cast(Term const & theTerm);	//!< Perfom casting.
		static FcM const * cast(Term const * theTerm);	//!< Perfom casting.
		static FcM & cast(Term & theTerm);				//!< Perfom casting.
		static FcM * cast(Term * theTerm);				//!< Perfom casting.

		static Bll suit(Term const & theTerm);			//!< Suits casting?
		static Bll suit(Term const * theTerm);			//!< Suits casting?
		static Bll suit(Term & theTerm);				//!< Suits casting?
		static Bll suit(Term * theTerm);				//!< Suits casting?

		//! @}

	protected:

		FcM(Hdl const hdlSys, Dim const PrmCount);		//!< Constructor.
		FcM const & operator = (FcM const & that);		//!< Assigner.
		FcM(FcM const & that);							//!< Duplicator.
		virtual ~FcM();									//!< Destructor.

		//! @name Deferments
		//! @{

		#if CompLazy
		virtual void setupUndoArgs();					//!< Set up arguments for undo operation.
		virtual void setupUndoPrms();					//!< Set up parameters for undo operation.
		virtual void undoHint(Pos const thePos);		//!< Perform hint undo for a parameter.
		#endif

		//! @}
};



/*!
	Whether a term is suitable for casting.
*/
inline Bll FcM::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FcM>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FcM::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FcM>::TermCat;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
inline Bll FcM::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FcM>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FcM::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FcM>::TermCat;
	CatchError
}


/*!
	Perform casting of a term.
*/
inline FcM const & FcM::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FcM>::TermCat, eWrongCat);

	return scast<FcM const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FcM const * FcM::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FcM>::TermCat, eWrongCat);

	return scast<FcM const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FcM & FcM::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FcM>::TermCat, eWrongCat);

	return scast<FcM &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FcM * FcM::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FcM>::TermCat, eWrongCat);

	return scast<FcM *>(theTerm);
	CatchError
}



/*!
	Refer to a fcm term.
*/
inline FcM & FcM::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fcm term.
*/
inline FcM * FcM::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}




/*!
	Refer to a fcm term.
*/
inline FcM const & FcM::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fcm term.
*/
inline FcM const * FcM::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The constructor.
*/
inline FcM::FcM(Hdl const hdlSys, Dim const PrmCount) :
		Func(hdlSys, PrmCount)
{
	WatchError
	setTermCat(TermStub<FcM>::TermCat);
	CatchError
}



/*!
	The destructor.
*/
inline FcM::~FcM()
{
	WatchError
	//	nothing to be done.
	CatchError
}


closeKangarooSpace


#endif//FcMHppIncluded
