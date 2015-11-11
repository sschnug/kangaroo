/*!
	@file fevt.tcc
	@brief The prototype file for FeVt template class.
	@details This is the prototype file for FeVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef FeVtTccIncluded
#define FeVtTccIncluded



#include "cbls/dbases/idx.hpp"
#include "cbls/frames/idx.hh"
#include "cbls/funcs/fev.hpp"

openKangarooSpace



/*!
	@class FeVt
	@brief A template class to represent fev terms.
	@details This template class represents fev terms.
*/
template <typename fvt>
class FeVt : public FeV
{
	public:

		static FeVt<fvt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static FeVt<fvt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static FeVt<fvt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static FeVt<fvt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static FeVt<fvt> const & cast(Term const & theTerm);	//!< Perform casting.
		static FeVt<fvt> const * cast(Term const * theTerm);	//!< Perform casting.
		static FeVt<fvt> & cast(Term & theTerm);				//!< Perform casting.
		static FeVt<fvt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	public:

		virtual Loc ValueLoc() const;							//!< The value locator.
		virtual Typ ValueType() const;							//!< The value type.
		EvalRec<fvt> const & ValueRec() const;					//!< The value record.

	protected:

		virtual ~FeVt();										//!< Destructor.
		FeVt(FeVt<fvt> const & that);							//!< Duplicator.
		FeVt(Hdl const hdlSys, Dim const PrmCount);				//!< Constructor.
		FeVt<fvt> const & operator = (FeVt<fvt> const & that);	//!< Assigner.

	protected:

		Loc mValueLoc;											//!< The value locator.
		EvalRec<fvt> * mValueRec;								//!< The value record.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename fvt>
inline Bll FeVt<fvt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FeVt<fvt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fvt>
inline Bll FeVt<fvt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FeVt<fvt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fvt>
inline Bll FeVt<fvt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FeVt<fvt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fvt>
inline Bll FeVt<fvt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FeVt<fvt> >::TermTyp;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fvt>
inline FeVt<fvt> const & FeVt<fvt>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FeVt<fvt> >::TermTyp, eWrongTyp);

	return scast<FeVt<fvt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fvt>
inline FeVt<fvt> const * FeVt<fvt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FeVt<fvt> >::TermTyp, eWrongTyp);

	return scast<FeVt<fvt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fvt>
inline FeVt<fvt> & FeVt<fvt>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FeVt<fvt> >::TermTyp, eWrongTyp);

	return scast<FeVt<fvt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fvt>
inline FeVt<fvt> * FeVt<fvt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FeVt<fvt> >::TermTyp, eWrongTyp);

	return scast<FeVt<fvt> *>(theTerm);
	CatchError
}



/*!
	Refer to a fevt term.
*/
template <typename fvt>
inline FeVt<fvt> & FeVt<fvt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fevt term.
*/
template <typename fvt>
inline FeVt<fvt> * FeVt<fvt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a fevt term.
*/
template <typename fvt>
inline FeVt<fvt> const & FeVt<fvt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fevt term.
*/
template <typename fvt>
inline FeVt<fvt> const * FeVt<fvt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The constructor.
*/
template <typename fvt>
inline FeVt<fvt>::FeVt(Hdl const hdlSys, Dim const PrmCount) :
		FeV(hdlSys, PrmCount), mValueLoc(InvLoc)
{
	WatchError
	this->setTermTyp(TermStub< FeVt<fvt> >::TermTyp);
	CatchError
}


/*!
	The destructor.
*/
template <typename fvt>
inline FeVt<fvt>::~FeVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Return value type.
*/
template<typename fvt>
Typ FeVt<fvt>::ValueType() const
{
	WatchError
	return DataStub< fvt >::DataTyp;
	CatchError
}



/*!
	Return the value locator.
*/
template<typename fvt>
inline Loc FeVt<fvt>::ValueLoc() const
{
	WatchError
	return mValueLoc;
	CatchError
}




/*!
	Return the value record.
*/
template <typename fvt>
inline EvalRec<fvt> const & FeVt<fvt>::ValueRec() const
{
	WatchError
	return *(this->mValueRec);
	CatchError
}



/*!
	The duplicator.
*/
template <typename fvt>
FeVt<fvt>::FeVt(FeVt<fvt> const & that) : FeV(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fvt>
FeVt<fvt> const & FeVt<fvt>::operator = (FeVt<fvt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



closeKangarooSpace


#endif//FeVtTccIncluded
