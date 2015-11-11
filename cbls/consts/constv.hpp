/*!
	@file constv.hpp
	@brief The source file for ConstV class.
	@details This is the source file for ConstV class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see constv.cpp
*/



#ifndef ConstVHppIncluded
#define ConstVHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"



openKangarooSpace


dec tctn(ConstV, 20);	//!< Declare constant values.



/*!
	@class ConstV
	@brief A class to represent constant values.
	@details This class represents constant values.
*/
class ConstV : public Const
{
	public:

		static ConstV & refm(Hdl const hdlSys, Hdl const hdlConst);			//!< Reference.
		static ConstV * ptrm(Hdl const hdlSys, Hdl const hdlConst);			//!< Pointer.
		static ConstV const & refc(Hdl const hdlSys, Hdl const hdlConst);	//!< Reference.
		static ConstV const * ptrc(Hdl const hdlSys, Hdl const hdlConst);	//!< Pointer.

		//! @name Casting
		//! @{

		static ConstV const & cast(Term const & theTerm);	//!< Perform casting.
		static ConstV const * cast(Term const * theTerm);	//!< Perform casting.
		static ConstV & cast(Term & theTerm);				//!< Perform casting.
		static ConstV * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);				//!< Suits casting?
		static Bll suit(Term const * theTerm);				//!< Suits casting?
		static Bll suit(Term & theTerm);					//!< Suits casting?
		static Bll suit(Term * theTerm);					//!< Suits casting?

		//! @}

	protected:

		virtual ~ConstV();									//!< Destructor.
		ConstV(Hdl const hdlSys);							//!< Constructor.
		ConstV(ConstV const & that);						//!< Duplicator.
		ConstV const & operator = (ConstV const & that);	//!< Assigner.
};



/*!
	The constructor.
*/
inline ConstV::ConstV(Hdl const hdlSys) :
		Const(hdlSys)
{
	WatchError
	setTermCat(TermStub<ConstV>::TermCat);
	CatchError
}


/*!
	The destructor.
*/
inline ConstV::~ConstV()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Refer to a normal constant.
*/
inline ConstV const & ConstV::refc(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcConst(hdlConst));
	CatchError
}



/*!
	Point to a normal constant.
*/
inline ConstV const * ConstV::ptrc(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcConst(hdlConst));
	CatchError
}



/*!
	Refer to a normal constant.
*/
inline ConstV & ConstV::refm(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmConst(hdlConst));
	CatchError
}



/*!
	Point to a normal constant.
*/
inline ConstV * ConstV::ptrm(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmConst(hdlConst));
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll ConstV::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<ConstV>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll ConstV::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<ConstV>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll ConstV::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<ConstV>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll ConstV::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<ConstV>::TermCat;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline ConstV const & ConstV::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<ConstV>::TermCat, eWrongCat);

	return scast<ConstV const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline ConstV const * ConstV::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<ConstV>::TermCat, eWrongCat);

	return scast<ConstV const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline ConstV & ConstV::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<ConstV>::TermCat, eWrongCat);

	return scast<ConstV &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline ConstV * ConstV::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<ConstV>::TermCat, eWrongCat);

	return scast<ConstV *>(theTerm);
	CatchError
}



/*!
	The duplicator.
*/
inline ConstV::ConstV(ConstV const & that) : Const(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
inline ConstV const & ConstV::operator = (ConstV const & that)
{
	WatchError
	if (this == &that) return *this;
	Throw(eUndefAssigner);
	CatchError
}



closeKangarooSpace



#endif // ConstVHppIncluded
