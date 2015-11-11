/*!
	@file dynarangechgvarvf.hpp
	@brief The prototype file for DynaRangeChgVarVf class.
	@details This is the prototype file for DynaRangeChgVarVf class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see dynarangechgvarvf.cpp
*/



#ifndef DynaRangeChgVarVfHppIncluded
#define DynaRangeChgVarVfHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/vars/reg.hh"



openKangarooSpace



/*!
	@class DynaRangeChgVarVf
	@brief A class to represent float dynamic range change variables.
	@details This class represents float dynamic rangechange variables.
*/
class DynaRangeChgVarVf : public RangeVarVf
{
	public:
		static Hdl def(Hdl const hdlSys, Flt const & StatLeft = MinFlt,
			Flt const & StatRight = MaxFlt, Flt const & StepSize = HopFlt);				//!< Definition.

		static DynaRangeChgVarVf & refm(Hdl const hdlSys, Hdl const hdlVar);			//!< Reference.
		static DynaRangeChgVarVf * ptrm(Hdl const hdlSys, Hdl const hdlVar);			//!< Pointer.
		static DynaRangeChgVarVf const & refc(Hdl const hdlSys, Hdl const hdlVar);		//!< Reference.
		static DynaRangeChgVarVf const * ptrc(Hdl const hdlSys, Hdl const hdlVar);		//!< Pointer.

		//! @name Casting
		//! @{

		static DynaRangeChgVarVf const & cast(Term const & theTerm);	//!< Perform casting.
		static DynaRangeChgVarVf const * cast(Term const * theTerm);	//!< Perform casting.
		static DynaRangeChgVarVf & cast(Term & theTerm);				//!< Perform casting.
		static DynaRangeChgVarVf * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);			//!< Suits casting?
		static Bll suit(Term const * theTerm);			//!< Suits casting?
		static Bll suit(Term & theTerm);				//!< Suits casting?
		static Bll suit(Term * theTerm);				//!< Suits casting?

		//! @}

		void setDynaRange(Flt const LeftValue, Flt const RightValue); 	//!< Range change.
		void setDynaLeft(Flt const LeftValue); 							//!< Range change.
		void setDynaRight(Flt const RightValue); 						//!< Range change.

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

		virtual Bll validStat(Flt const & theFlt) const;		//!< Valid with respect to the static domain?
		virtual Bll validDyna(Flt const & theFlt) const;		//!< Valid with respect to the dynamic domain?
		virtual Bll validStat(Wrp const & theWrp) const;		//!< Valid with respect to the static domain?
		virtual Bll validDyna(Wrp const & theWrp) const;		//!< Valid with respect to the dynamic domain?

		//! @}

		//! @name Probing
		//! @{

		virtual Bll chkCurrStatRight() const;			//!< Whether the current value is the static right value.
		virtual Bll chkCurrStatLeft() const;			//!< Whether the current value is the static left value.
		virtual Bll chkCurrDynaRight() const;			//!< Whether the current value is the static right value.
		virtual Bll chkCurrDynaLeft() const;			//!< Whether the current value is the static left value.
		virtual Bll chkNextStatRight() const;			//!< Whether the next value is the static right value.
		virtual Bll chkNextStatLeft() const;			//!< Whether the next value is the static left value.
		virtual Bll chkNextDynaRight() const;			//!< Whether the next value is the dynamic right value.
		virtual Bll chkNextDynaLeft() const;			//!< Whether the next value is the dynamic left value.

		//! @}

		//! @name Values
		//! @{

		virtual Flt StatRandValue(Rnd & theRnd) const;	//!< Random value chosen from the static domain.
		virtual Flt DynaRandValue(Rnd & theRnd) const;	//!< Random value chosen from the dynamic domain.

		virtual Flt StatLeftValue() const;				//!< The static left value.
		virtual Flt StatRightValue() const;				//!< The static right value.
		virtual Flt DynaLeftValue() const;				//!< The dynamic right value.
		virtual Flt DynaRightValue() const;				//!< The dynamic right value.
		virtual Flt StepSizeValue() const;				//!< The step size value.

		//! @}

		//! @name Wrappers
		//! @{

		virtual Wrp StatRandWrap(Rnd & theRnd) const;	//!< Random value chosen from the static domain.
		virtual Wrp DynaRandWrap(Rnd & theRnd) const;	//!< Random value chosen from the dynamic domain.

		virtual Wrp StatLeftWrap() const;				//!< Wrap for the static left value.
		virtual Wrp StatRightWrap() const;				//!< Wrap for the static right value.
		virtual Wrp DynaLeftWrap() const;				//!< Wrap for the dynamic right value.
		virtual Wrp DynaRightWrap() const;				//!< Wrap for the dynamic right value.
		virtual Wrp StepSizeWrap() const;				//!< Wrap for the step size value.

		//! @}

		//! @name Executions
		//! @{

		virtual void execAnewValue(Flt const & theFlt);		//!< Execute anew with a given value.
		virtual void execAnewWrap(Wrp const & theWrp);		//!< Execute anew with a given value.
		virtual void execAnewStatRand(Rnd & theRnd);		//!< Execute anew with a random value form the static domain.
		virtual void execAnewDynaRand(Rnd & theRnd);		//!< Execute anew with a random value from the dynamic domain.

		virtual void execIncrValue(Flt const & theFlt);		//!< Execute incrementally with a given value.
		virtual void execIncrWrap(Wrp const & theWrp);		//!< Execute incrementally with a given value.
		virtual void execIncrStatRand(Rnd & theRnd);		//!< Execute incrementally with a random value form the static domain.
		virtual void execIncrDynaRand(Rnd & theRnd);		//!< Execute incrementally with a random value from the dynamic domain.

		virtual void execIncrStatLeft();					//!< Execute with the static left value.
		virtual void execIncrDynaLeft();					//!< Execute with the dynamic left value.
		virtual void execIncrSuccessor();					//!< Execute with the succeeding value.
		virtual void execIncrPredecessor();					//!< Execute with the preceding value.
		virtual void execIncrStatRight();					//!< Execute with the static right value.
		virtual void execIncrDynaRight();					//!< Execute with the dynamic right value.

		//! @}

		//! @name Simulations
		//! @{

		virtual void simulAnewValue(Flt const & theFlt);	//!< Simulate anew with a given value.
		virtual void simulAnewWrap(Wrp const & theWrp);		//!< Simulate anew with a given value.
		virtual void simulAnewStatRand(Rnd & theRnd);		//!< Simulate anew with a random value form the static domain.
		virtual void simulAnewDynaRand(Rnd & theRnd);		//!< Simulate anew with a random value from the dynamic domain.

		virtual void simulIncrValue(Flt const & theFlt);	//!< Simulate incrementally with a given value.
		virtual void simulIncrWrap(Wrp const & theWrp);		//!< Simulate incrementally with a given value.
		virtual void simulIncrStatRand(Rnd & theRnd);		//!< Simulate incrementally with a random value form the static domain.
		virtual void simulIncrDynaRand(Rnd & theRnd);		//!< Simulate incrementally with a random value from the dynamic domain.

		virtual void simulIncrStatLeft();					//!< Simulate with the static left value.
		virtual void simulIncrDynaLeft();					//!< Simulate with the dynamic left value.
		virtual void simulIncrSuccessor();					//!< Simulate with the succeeding value.
		virtual void simulIncrPredecessor();				//!< Simulate with the preceding value.
		virtual void simulIncrStatRight();					//!< Simulate with the static right value.
		virtual void simulIncrDynaRight();					//!< Simulate with the dynamic right value.

		//! @}

	protected:

		~DynaRangeChgVarVf();													//!< Destructor.
		DynaRangeChgVarVf(DynaRangeChgVarVf const & that);						//!< Duplicator.
		DynaRangeChgVarVf const & operator = (DynaRangeChgVarVf const & that);	//!< Assigner.
		DynaRangeChgVarVf(Hdl const hdlSys, Flt const & StatLeft,
							Flt const & StatRight, Flt const & StepSize);		//!< Constructor.

		Flt 			mStatLeftValue;			//!< The static left value.
		Flt 			mStatRightValue;		//!< The static right value.
		Flt 			mStepSizeValue;			//!< the step size value.
		Flt 			mDynaLeftValue;			//!< Holds the dynamic left value.
		Flt 			mDynaRightValue;		//!< Holds the dynamic right value.
};



/*!
	Whether a term is suitable for casting.
*/
inline Bll DynaRangeChgVarVf::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub<DynaRangeChgVarVf>::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll DynaRangeChgVarVf::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub<DynaRangeChgVarVf>::TermCls;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
inline Bll DynaRangeChgVarVf::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub<DynaRangeChgVarVf>::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll DynaRangeChgVarVf::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub<DynaRangeChgVarVf>::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline DynaRangeChgVarVf const & DynaRangeChgVarVf::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub<DynaRangeChgVarVf>::TermCls, eWrongCls);

	return scast<DynaRangeChgVarVf const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline DynaRangeChgVarVf const * DynaRangeChgVarVf::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub<DynaRangeChgVarVf>::TermCls, eWrongCls);

	return scast<DynaRangeChgVarVf const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline DynaRangeChgVarVf & DynaRangeChgVarVf::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub<DynaRangeChgVarVf>::TermCls, eWrongCls);

	return scast<DynaRangeChgVarVf &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline DynaRangeChgVarVf * DynaRangeChgVarVf::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub<DynaRangeChgVarVf>::TermCls, eWrongCls);

	return scast<DynaRangeChgVarVf *>(theTerm);
	CatchError
}



/*!
	Refer to an float range variable.
*/
inline DynaRangeChgVarVf & DynaRangeChgVarVf::refm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmVar(hdlVar));
	CatchError
}



/*!
	Point to an float range variable.
*/
inline DynaRangeChgVarVf * DynaRangeChgVarVf::ptrm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmVar(hdlVar));
	CatchError
}



/*!
	Refer to an float range variable.
*/
inline DynaRangeChgVarVf const & DynaRangeChgVarVf::refc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcVar(hdlVar));
	CatchError
}



/*!
	Point to an float range variable.
*/
inline DynaRangeChgVarVf const * DynaRangeChgVarVf::ptrc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcVar(hdlVar));
	CatchError
}



closeKangarooSpace


#endif //DynaRangeChgVarVfHppIncluded
