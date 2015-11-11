/*!
	@file propflipvarvb.hpp
	@brief The prototype file for PropFlipVarVb class.
	@details This is the prototype file for PropFlipVarVb class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see propflipvarvb.cpp
*/



#ifndef PropFlipVarVbHppIncluded
#define PropFlipVarVbHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/vars/reg.hh"



openKangarooSpace



/*!
	@class PropFlipVarVb
	@brief A class to represent boolean propositional variables.
	@details This class represents boolean proposition variables.
*/
class PropFlipVarVb : public FlipVarVb
{
	public:
		static Hdl def(Hdl const hdlSys);										//!< Definition.

		static PropFlipVarVb & refm(Hdl const hdlSys, Hdl const hdlVar);		//!< Reference.
		static PropFlipVarVb * ptrm(Hdl const hdlSys, Hdl const hdlVar);		//!< Pointer.
		static PropFlipVarVb const & refc(Hdl const hdlSys, Hdl const hdlVar);	//!< Reference.
		static PropFlipVarVb const * ptrc(Hdl const hdlSys, Hdl const hdlVar);	//!< Pointer.

		//! @name Casting
		//! @{

		static PropFlipVarVb const & cast(Term const & theTerm);	//!< Perform casting.
		static PropFlipVarVb const * cast(Term const * theTerm);	//!< Perform casting.
		static PropFlipVarVb & cast(Term & theTerm);				//!< Perform casting.
		static PropFlipVarVb * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);			//!< Suits casting?
		static Bll suit(Term const * theTerm);			//!< Suits casting?
		static Bll suit(Term & theTerm);				//!< Suits casting?
		static Bll suit(Term * theTerm);				//!< Suits casting?

		//! @}

	public:

		//! @name Compatibility
		//!	@{

		virtual Bll identical(Var const * that) const;	//!< Whether identical?
		virtual Bll identical(Var const & that) const;	//!< Whether identical?
		virtual Bll assignable(Var const * that) const;	//!< Whether assignable?
		virtual Bll assignable(Var const & that) const;	//!< Whether assignable?
		virtual Bll swappable(Var const * that) const;	//!< Whether swappable?
		virtual Bll swappable(Var const & that) const;	//!< Whether swappable?

		//!	@}

		//! @name Validity
		//! @{

		virtual Bll validValue(Bln const & theBln) const;		//!< Valid value?
		virtual Bll validStat(Wrp const & theWrp) const;		//!< Valid with respect to the static domain?
		virtual Bll validDyna(Wrp const & theWrp) const;		//!< Valid with respect to the dynamic domain?

		//! @}

		//! @name Probing
		//! @{

		virtual Bll chkCurrRight() const;			//!< Whether the current value is the static right value.
		virtual Bll chkCurrLeft() const;			//!< Whether the current value is the static left value.
		virtual Bll chkNextRight() const;			//!< Whether the next value is the static right value.
		virtual Bll chkNextLeft() const;			//!< Whether the next value is the static left value.

		//! @}

		//! @name States
		//! @{

		virtual Bll CurrState() const;						//!< Current state of the var.
		virtual Bll NextState() const;						//!< Current state of the var.
		virtual Bll RandState(Rnd & theRnd) const;			//!< Random state of the var.
		virtual Bll WrapState(Wrp const & theWrp) const;	//!< State for a given wrap value.

		//! @}

		//! @name Values
		//! @{

		virtual Bln LeftValue() const;							//!< The left value.
		virtual Bln RightValue() const;							//!< The right value.
		virtual Bln RandValue(Rnd & theRnd) const;				//!< Randomly chosen value.
		virtual Bln StateValue(Bll const RightNotLeft) const;	//!< The state value.

		//! @}
		//! @name Wrappers
		//! @{

		virtual Wrp StatRandWrap(Rnd & theRnd) const;			//!< Random value chosen from the static domain.
		virtual Wrp DynaRandWrap(Rnd & theRnd) const;			//!< Random value chosen from the dynamic domain.

		virtual Wrp LeftWrap() const;							//!< Wrap for the static left value.
		virtual Wrp RightWrap() const;							//!< Wrap for the static right value.
		virtual Wrp StateWrap(Bll const RightNotLeft) const;	//!< Wrap of a given state.

		//! @}

		//! @name Executions
		//! @{

		virtual void execAnewValue(Bln const & theBln);		//!< Execute anew with a given value.
		virtual void execAnewWrap(Wrp const & theWrp);		//!< Execute anew with a given value.
		virtual void execAnewStatRand(Rnd & theRnd);		//!< Execute anew with a random value form the static domain.
		virtual void execAnewDynaRand(Rnd & theRnd);		//!< Execute anew with a random value from the dynamic domain.

		virtual void execIncrValue(Bln const & theBln);		//!< Execute incrementally with a given value.
		virtual void execIncrWrap(Wrp const & theWrp);		//!< Execute incrementally with a given value.
		virtual void execIncrStatRand(Rnd & theRnd);		//!< Execute incrementally with a random value form the static domain.
		virtual void execIncrDynaRand(Rnd & theRnd);		//!< Execute incrementally with a random value from the dynamic domain.

		virtual void execAnewState(Bll const RightNotLeft);	//!< Execute anew with truth value.
		virtual void execIncrState(Bll const RightNotLeft);	//!< Execute incr with truth value.
		virtual void execAnewFlip();						//!< Execute anew flip.
		virtual void execIncrFlip();						//!< Execute incr flip.

		//! @}

		//! @name Simulations
		//! @{

		virtual void simulAnewValue(Bln const & theBln);	//!< Simulate anew with a given value.
		virtual void simulAnewWrap(Wrp const & theWrp);		//!< Simulate anew with a given value.
		virtual void simulAnewStatRand(Rnd & theRnd);		//!< Simulate anew with a random value form the static domain.
		virtual void simulAnewDynaRand(Rnd & theRnd);		//!< Simulate anew with a random value from the dynamic domain.

		virtual void simulIncrValue(Bln const & theBln);	//!< Simulate incrementally with a given value.
		virtual void simulIncrWrap(Wrp const & theWrp);		//!< Simulate incrementally with a given value.
		virtual void simulIncrStatRand(Rnd & theRnd);		//!< Simulate incrementally with a random value form the static domain.
		virtual void simulIncrDynaRand(Rnd & theRnd);		//!< Simulate incrementally with a random value from the dynamic domain.

		virtual void simulAnewState(Bll const RightNotLeft);//!< Simulate anew with truth value.
		virtual void simulIncrState(Bll const RightNotLeft);//!< Simulate incr with truth value.
		virtual void simulAnewFlip();						//!< Simulate anew flip.
		virtual void simulIncrFlip();						//!< Simulate incr flip.

		//! @}

	protected:

		~PropFlipVarVb();												//!< Destructor.
		PropFlipVarVb(PropFlipVarVb const & that);						//!< Duplicator.
		PropFlipVarVb const & operator = (PropFlipVarVb const & that);	//!< Assigner.
		PropFlipVarVb(Hdl const hdlSys);								//!< Constructor.
};



/*!
	Whether a term is suitable for casting.
*/
inline Bll PropFlipVarVb::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub<PropFlipVarVb>::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll PropFlipVarVb::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub<PropFlipVarVb>::TermCls;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
inline Bll PropFlipVarVb::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub<PropFlipVarVb>::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll PropFlipVarVb::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub<PropFlipVarVb>::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline PropFlipVarVb const & PropFlipVarVb::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub<PropFlipVarVb>::TermCls, eWrongCls);

	return scast<PropFlipVarVb const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline PropFlipVarVb const * PropFlipVarVb::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub<PropFlipVarVb>::TermCls, eWrongCls);

	return scast<PropFlipVarVb const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline PropFlipVarVb & PropFlipVarVb::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub<PropFlipVarVb>::TermCls, eWrongCls);

	return scast<PropFlipVarVb &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline PropFlipVarVb * PropFlipVarVb::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub<PropFlipVarVb>::TermCls, eWrongCls);

	return scast<PropFlipVarVb *>(theTerm);
	CatchError
}



/*!
	Refer to a boolean propositional variable.
*/
inline PropFlipVarVb & PropFlipVarVb::refm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmVar(hdlVar));
	CatchError
}



/*!
	Point to a boolean propositional variable.
*/
inline PropFlipVarVb * PropFlipVarVb::ptrm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmVar(hdlVar));
	CatchError
}



/*!
	Refer to a boolean propositional variable.
*/
inline PropFlipVarVb const & PropFlipVarVb::refc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcVar(hdlVar));
	CatchError
}



/*!
	Point to a boolean propositional variable.
*/
inline PropFlipVarVb const * PropFlipVarVb::ptrc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcVar(hdlVar));
	CatchError
}



closeKangarooSpace


#endif //PropFlipVarVbHppIncluded
