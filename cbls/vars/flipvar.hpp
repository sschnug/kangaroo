/*!
	@file flipvar.hpp
	@brief The prototype file for FlipVar class.
	@details This is the prototype file for FlipVar class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see flipvar.cpp
*/



#ifndef FlipVarHppIncluded
#define FlipVarHppIncluded


#include "cbls/frames/idx.hh"


openKangarooSpace


dec tctn(FlipVar, 21);	//!< Declare flip variables.



/*!
	@class FlipVar
	@brief A class to represent flip variables
	@details This class represents flip variables.
*/
class FlipVar : public Var
{
	public:

		static FlipVar & refm(Hdl const hdlSys, Hdl const hdlVar);			//!< Reference.
		static FlipVar * ptrm(Hdl const hdlSys, Hdl const hdlVar);			//!< Pointer.
		static FlipVar const & refc(Hdl const hdlSys, Hdl const hdlVar);	//!< Reference.
		static FlipVar const * ptrc(Hdl const hdlSys, Hdl const hdlVar);	//!< Pointer.

		//! @name Casting
		//! @{

		static FlipVar const & cast(Term const & theTerm);	//!< Perform casting.
		static FlipVar const * cast(Term const * theTerm);	//!< Perform casting.
		static FlipVar & cast(Term & theTerm);				//!< Perform casting.
		static FlipVar * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);				//!< Suits casting?
		static Bll suit(Term const * theTerm);				//!< Suits casting?
		static Bll suit(Term & theTerm);					//!< Suits casting?
		static Bll suit(Term * theTerm);					//!< Suits casting?

		//! @}

		//! @name States
		//! @{

		virtual Bll CurrState() const = 0;						//!< Current state of the var.
		virtual Bll NextState() const = 0;						//!< Next state of the var.
		virtual Bll RandState(Rnd & theRnd) const = 0;			//!< Random state of the var.
		virtual Bll WrapState(Wrp const & theWrp) const = 0;	//!< State for a given wrap value.

		//! @}

		//! @name Wrappers
		//! @{

		virtual Wrp LeftWrap() const = 0;						//!< Wrap for the left state.
		virtual Wrp RightWrap() const = 0;						//!< Wrap for the right state.
		virtual Wrp StateWrap(Bll const RightNotLeft) const = 0;//!< Wrap of a given state.

		//! @}

		//! @name Flips
		//! @{

		virtual void execAnewState(Bll const RightNotLeft) = 0;		//!< Execute anew with truth value.
		virtual void execIncrState(Bll const RightNotLeft) = 0;		//!< Execute incr with truth value.
		virtual void simulAnewState(Bll const RightNotLeft) = 0;	//!< Simulate anew with truth value.
		virtual void simulIncrState(Bll const RightNotLeft) = 0;	//!< Simulate incr with truth value.

		virtual void execAnewFlip() = 0;					//!< Execute anew flip.
		virtual void execIncrFlip() = 0;					//!< Execute incr flip.
		virtual void simulAnewFlip() = 0;					//!< Simulate anew flip.
		virtual void simulIncrFlip() = 0;					//!< Simulate incr flip.

		//! @}

		//! @name Probing
		//! @{

		virtual Bll chkCurrRight() const = 0;			//!< Whether the current value is the static right value.
		virtual Bll chkCurrLeft() const = 0;			//!< Whether the current value is the static left value.
		virtual Bll chkNextRight() const = 0;			//!< Whether the next value is the static right value.
		virtual Bll chkNextLeft() const = 0;			//!< Whether the next value is the static left value.

		//! @}

	protected:

		virtual ~FlipVar();									//!< Destructor.
		FlipVar(Hdl const hdlSys);							//!< Constructor.
		FlipVar(FlipVar const & that);						//!< Duplicator.
		FlipVar const & operator = (FlipVar const & that);	//!< Assigner.
};



/*!
	The constructor.
*/
inline FlipVar::FlipVar(Hdl const hdlSys) :
		Var(hdlSys)
{
	WatchError
	setTermCat(TermStub<FlipVar>::TermCat);
	CatchError
}


/*!
	The destructor.
*/
inline FlipVar::~FlipVar()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Refer to a flip variable.
*/
inline FlipVar const & FlipVar::refc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcVar(hdlVar));
	CatchError
}



/*!
	Point to a flip variable.
*/
inline FlipVar const * FlipVar::ptrc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcVar(hdlVar));
	CatchError
}



/*!
	Refer to a flip variable.
*/
inline FlipVar & FlipVar::refm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmVar(hdlVar));
	CatchError
}



/*!
	Point to a flip variable.
*/
inline FlipVar * FlipVar::ptrm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmVar(hdlVar));
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FlipVar::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FlipVar>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FlipVar::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FlipVar>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FlipVar::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FlipVar>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FlipVar::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FlipVar>::TermCat;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FlipVar const & FlipVar::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FlipVar>::TermCat, eWrongCat);

	return scast<FlipVar const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FlipVar const * FlipVar::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FlipVar>::TermCat, eWrongCat);

	return scast<FlipVar const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FlipVar & FlipVar::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FlipVar>::TermCat, eWrongCat);

	return scast<FlipVar &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FlipVar * FlipVar::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FlipVar>::TermCat, eWrongCat);

	return scast<FlipVar *>(theTerm);
	CatchError
}



closeKangarooSpace



#endif // FlipVarHppIncluded
