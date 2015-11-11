/*!
	@file propflipvarvi.hpp
	@brief The prototype file for PropFlipVarVi class.
	@details This is the prototype file for PropFlipVarVi class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see propflipvarvi.cpp
*/



#ifndef PropFlipVarViHppIncluded
#define PropFlipVarViHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/vars/reg.hh"



openKangarooSpace



/*!
	@class PropFlipVarVi
	@brief A class to represent integer propositional variables.
	@details This class represents integer proposition variables.
*/
class PropFlipVarVi : public FlipVarVi
{
	public:
		static Hdl def(Hdl const hdlSys);										//!< Definition.

		static PropFlipVarVi & refm(Hdl const hdlSys, Hdl const hdlVar);		//!< Reference.
		static PropFlipVarVi * ptrm(Hdl const hdlSys, Hdl const hdlVar);		//!< Pointer.
		static PropFlipVarVi const & refc(Hdl const hdlSys, Hdl const hdlVar);	//!< Reference.
		static PropFlipVarVi const * ptrc(Hdl const hdlSys, Hdl const hdlVar);	//!< Pointer.

		//! @name Casting
		//! @{

		static PropFlipVarVi const & cast(Term const & theTerm);	//!< Perform casting.
		static PropFlipVarVi const * cast(Term const * theTerm);	//!< Perform casting.
		static PropFlipVarVi & cast(Term & theTerm);				//!< Perform casting.
		static PropFlipVarVi * cast(Term * theTerm);				//!< Perform casting.

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

		virtual Bll validValue(Int const & theInt) const;		//!< Valid value?
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
		virtual Bll NextState() const;						//!< Next state of the var.
		virtual Bll RandState(Rnd & theRnd) const;			//!< Random state of the var.
		virtual Bll WrapState(Wrp const & theWrp) const;	//!< State for a given wrap value.

		//! @}
		//! @name Values
		//! @{

		virtual Int LeftValue() const;							//!< The left value.
		virtual Int RightValue() const;							//!< The right value.
		virtual Int RandValue(Rnd & theRnd) const;				//!< Randomly chosen value.
		virtual Int StateValue(Bll const RightNotLeft) const;	//!< The state value.

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

		virtual void execAnewValue(Int const & theInt);		//!< Execute anew with a given value.
		virtual void execAnewWrap(Wrp const & theWrp);		//!< Execute anew with a given value.
		virtual void execAnewStatRand(Rnd & theRnd);		//!< Execute anew with a random value form the static domain.
		virtual void execAnewDynaRand(Rnd & theRnd);		//!< Execute anew with a random value from the dynamic domain.

		virtual void execIncrValue(Int const & theInt);		//!< Execute incrementally with a given value.
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

		virtual void simulAnewValue(Int const & theInt);	//!< Simulate anew with a given value.
		virtual void simulAnewWrap(Wrp const & theWrp);		//!< Simulate anew with a given value.
		virtual void simulAnewStatRand(Rnd & theRnd);		//!< Simulate anew with a random value form the static domain.
		virtual void simulAnewDynaRand(Rnd & theRnd);		//!< Simulate anew with a random value from the dynamic domain.

		virtual void simulIncrValue(Int const & theInt);	//!< Simulate incrementally with a given value.
		virtual void simulIncrWrap(Wrp const & theWrp);		//!< Simulate incrementally with a given value.
		virtual void simulIncrStatRand(Rnd & theRnd);		//!< Simulate incrementally with a random value form the static domain.
		virtual void simulIncrDynaRand(Rnd & theRnd);		//!< Simulate incrementally with a random value from the dynamic domain.

		virtual void simulAnewState(Bll const RightNotLeft);//!< Simulate anew with truth value.
		virtual void simulIncrState(Bll const RightNotLeft);//!< Simulate incr with truth value.
		virtual void simulAnewFlip();						//!< Simulate anew flip.
		virtual void simulIncrFlip();						//!< Simulate incr flip.

		//! @}

	protected:

		~PropFlipVarVi();												//!< Destructor.
		PropFlipVarVi(PropFlipVarVi const & that);						//!< Duplicator.
		PropFlipVarVi const & operator = (PropFlipVarVi const & that);	//!< Assigner.
		PropFlipVarVi(Hdl const hdlSys);								//!< Constructor.
};



/*!
	Whether a term is suitable for casting.
*/
inline Bll PropFlipVarVi::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub<PropFlipVarVi>::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll PropFlipVarVi::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub<PropFlipVarVi>::TermCls;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
inline Bll PropFlipVarVi::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub<PropFlipVarVi>::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll PropFlipVarVi::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub<PropFlipVarVi>::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline PropFlipVarVi const & PropFlipVarVi::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub<PropFlipVarVi>::TermCls, eWrongCls);

	return scast<PropFlipVarVi const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline PropFlipVarVi const * PropFlipVarVi::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub<PropFlipVarVi>::TermCls, eWrongCls);

	return scast<PropFlipVarVi const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline PropFlipVarVi & PropFlipVarVi::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub<PropFlipVarVi>::TermCls, eWrongCls);

	return scast<PropFlipVarVi &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline PropFlipVarVi * PropFlipVarVi::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub<PropFlipVarVi>::TermCls, eWrongCls);

	return scast<PropFlipVarVi *>(theTerm);
	CatchError
}



/*!
	Refer to an integer propositional variable.
*/
inline PropFlipVarVi & PropFlipVarVi::refm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmVar(hdlVar));
	CatchError
}



/*!
	Point to an integer propositional variable.
*/
inline PropFlipVarVi * PropFlipVarVi::ptrm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmVar(hdlVar));
	CatchError
}



/*!
	Refer to an integer propositional variable.
*/
inline PropFlipVarVi const & PropFlipVarVi::refc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcVar(hdlVar));
	CatchError
}



/*!
	Point to an integer propositional variable.
*/
inline PropFlipVarVi const * PropFlipVarVi::ptrc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcVar(hdlVar));
	CatchError
}



closeKangarooSpace


#endif //PropFlipVarViHppIncluded
