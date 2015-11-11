/*!
	@file rangevar.hpp
	@brief The prototype file for RangeVar class.
	@details This is the prototype file for RangeVar class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see rangevar.cpp
*/



#ifndef RangeVarHppIncluded
#define RangeVarHppIncluded


#include "cbls/frames/idx.hh"


openKangarooSpace


dec tctn(RangeVar, 22);	//!< Declare range variables.



/*!
	@class RangeVar
	@brief A class to represent range variables
	@details This class represents range variables.
*/
class RangeVar : public Var
{
	public:

		static RangeVar & refm(Hdl const hdlSys, Hdl const hdlVar);			//!< Reference.
		static RangeVar * ptrm(Hdl const hdlSys, Hdl const hdlVar);			//!< Pointer.
		static RangeVar const & refc(Hdl const hdlSys, Hdl const hdlVar);	//!< Reference.
		static RangeVar const * ptrc(Hdl const hdlSys, Hdl const hdlVar);	//!< Pointer.

		//! @name Casting
		//! @{

		static RangeVar const & cast(Term const & theTerm);	//!< Perform casting.
		static RangeVar const * cast(Term const * theTerm);	//!< Perform casting.
		static RangeVar & cast(Term & theTerm);				//!< Perform casting.
		static RangeVar * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);				//!< Suits casting?
		static Bll suit(Term const * theTerm);				//!< Suits casting?
		static Bll suit(Term & theTerm);					//!< Suits casting?
		static Bll suit(Term * theTerm);					//!< Suits casting?

		//! @}

		//! @name Wrappers
		//! @{

		virtual Wrp StepSizeWrap() const = 0;				//!< Wrap for the step size value.
		virtual Wrp StatLeftWrap() const = 0;				//!< Wrap for the static left value.
		virtual Wrp StatRightWrap() const = 0;				//!< Wrap for the static right value.
		virtual Wrp DynaLeftWrap() const = 0;				//!< Wrap for the dynamic right value.
		virtual Wrp DynaRightWrap() const = 0;				//!< Wrap for the dynamic right value.

		//! @}

		//! @name Probing
		//! @{

		virtual Bll chkCurrStatRight() const = 0;			//!< Whether the current value is the static right value.
		virtual Bll chkCurrStatLeft() const = 0;			//!< Whether the current value is the static left value.
		virtual Bll chkCurrDynaRight() const = 0;			//!< Whether the current value is the static right value.
		virtual Bll chkCurrDynaLeft() const = 0;			//!< Whether the current value is the static left value.
		virtual Bll chkNextStatRight() const = 0;			//!< Whether the next value is the static right value.
		virtual Bll chkNextStatLeft() const = 0;			//!< Whether the next value is the static left value.
		virtual Bll chkNextDynaRight() const = 0;			//!< Whether the next value is the dynamic right value.
		virtual Bll chkNextDynaLeft() const = 0;			//!< Whether the next value is the dynamic left value.

		//! @}

		//! @name Executions
		//! @{

		virtual void execIncrStatLeft() = 0;					//!< Execute with the static left value.
		virtual void execIncrDynaLeft() = 0;					//!< Execute with the dynamic left value.
		virtual void execIncrSuccessor() = 0;					//!< Execute with the succeeding value.
		virtual void execIncrPredecessor() = 0;					//!< Execute with the preceding value.
		virtual void execIncrStatRight() = 0;					//!< Execute with the static right value.
		virtual void execIncrDynaRight() = 0;					//!< Execute with the dynamic right value.

		//! @}

		//! @name Simulations
		//! @{

		virtual void simulIncrStatLeft() = 0;					//!< Simulate with the static left value.
		virtual void simulIncrDynaLeft() = 0;					//!< Simulate with the dynamic left value.
		virtual void simulIncrSuccessor() = 0;					//!< Simulate with the succeeding value.
		virtual void simulIncrPredecessor() = 0;				//!< Simulate with the preceding value.
		virtual void simulIncrStatRight() = 0;					//!< Simulate with the static right value.
		virtual void simulIncrDynaRight() = 0;					//!< Simulate with the dynamic right value.

		//! @}

	protected:

		virtual ~RangeVar();									//!< Destructor.
		RangeVar(Hdl const hdlSys);								//!< Constructor.
		RangeVar(RangeVar const & that);						//!< Duplicator.
		RangeVar const & operator = (RangeVar const & that);	//!< Assigner.
};



/*!
	The constructor.
*/
inline RangeVar::RangeVar(Hdl const hdlSys) :
		Var(hdlSys)
{
	WatchError
	setTermCat(TermStub<RangeVar>::TermCat);
	CatchError
}


/*!
	The destructor.
*/
inline RangeVar::~RangeVar()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Refer to a range variable.
*/
inline RangeVar const & RangeVar::refc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcVar(hdlVar));
	CatchError
}



/*!
	Point to a range variable.
*/
inline RangeVar const * RangeVar::ptrc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcVar(hdlVar));
	CatchError
}



/*!
	Refer to a range variable.
*/
inline RangeVar & RangeVar::refm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmVar(hdlVar));
	CatchError
}



/*!
	Point to a range variable.
*/
inline RangeVar * RangeVar::ptrm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmVar(hdlVar));
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll RangeVar::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<RangeVar>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll RangeVar::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<RangeVar>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll RangeVar::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<RangeVar>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll RangeVar::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<RangeVar>::TermCat;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline RangeVar const & RangeVar::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<RangeVar>::TermCat, eWrongCat);

	return scast<RangeVar const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline RangeVar const * RangeVar::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<RangeVar>::TermCat, eWrongCat);

	return scast<RangeVar const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline RangeVar & RangeVar::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<RangeVar>::TermCat, eWrongCat);

	return scast<RangeVar &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline RangeVar * RangeVar::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<RangeVar>::TermCat, eWrongCat);

	return scast<RangeVar *>(theTerm);
	CatchError
}



closeKangarooSpace



#endif // RangeVarHppIncluded
