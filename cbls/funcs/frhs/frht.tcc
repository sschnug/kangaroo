/*!
	@file frht.tcc
	@brief The prototype file for FrHt template class.
	@details This is the prototype file for FrHt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef FrHtTccIncluded
#define FrHtTccIncluded



#include "cbls/dbases/idx.hpp"
#include "cbls/frames/idx.hh"
#include "cbls/funcs/frh.hpp"

openKangarooSpace



/*!
	@class FrHt
	@brief A template class to represent frh terms.
	@details This template class represents frh terms.
*/
template <typename fmt>
class FrHt : public FrH
{
	public:

		static FrHt<fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static FrHt<fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static FrHt<fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static FrHt<fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static FrHt<fmt> const & cast(Term const & theTerm);	//!< Perform casting.
		static FrHt<fmt> const * cast(Term const * theTerm);	//!< Perform casting.
		static FrHt<fmt> & cast(Term & theTerm);				//!< Perform casting.
		static FrHt<fmt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	public:

		virtual Typ MetricType() const;							//!< The metric type.

	protected:

		virtual ~FrHt();										//!< Destructor.
		FrHt(FrHt<fmt> const & that);							//!< Duplicator.
		FrHt(Hdl const hdlSys, Dim const PrmCount);				//!< Constructor.
		FrHt<fmt> const & operator = (FrHt<fmt> const & that);	//!< Assigner.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FrHt<fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FrHt<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FrHt<fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FrHt<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FrHt<fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FrHt<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FrHt<fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FrHt<fmt> >::TermTyp;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FrHt<fmt> const & FrHt<fmt>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FrHt<fmt> >::TermTyp, eWrongTyp);

	return scast<FrHt<fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FrHt<fmt> const * FrHt<fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FrHt<fmt> >::TermTyp, eWrongTyp);

	return scast<FrHt<fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FrHt<fmt> & FrHt<fmt>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FrHt<fmt> >::TermTyp, eWrongTyp);

	return scast<FrHt<fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FrHt<fmt> * FrHt<fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FrHt<fmt> >::TermTyp, eWrongTyp);

	return scast<FrHt<fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to a frht term.
*/
template <typename fmt>
inline FrHt<fmt> & FrHt<fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a frht term.
*/
template <typename fmt>
inline FrHt<fmt> * FrHt<fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a frht term.
*/
template <typename fmt>
inline FrHt<fmt> const & FrHt<fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a frht term.
*/
template <typename fmt>
inline FrHt<fmt> const * FrHt<fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The constructor.
*/
template <typename fmt>
inline FrHt<fmt>::FrHt(Hdl const hdlSys, Dim const PrmCount) :
		FrH(hdlSys, PrmCount)
{
	WatchError
	this->setTermTyp(TermStub< FrHt<fmt> >::TermTyp);
	CatchError
}


/*!
	The destructor.
*/
template <typename fmt>
inline FrHt<fmt>::~FrHt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Return metric type.
*/
template<typename fmt>
Typ FrHt<fmt>::MetricType() const
{
	WatchError
	return DataStub< fmt >::DataTyp;
	CatchError
}



/*!
	The duplicator.
*/
template <typename fmt>
FrHt<fmt>::FrHt(FrHt<fmt> const & that) : FrH(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fmt>
FrHt<fmt> const & FrHt<fmt>::operator = (FrHt<fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



closeKangarooSpace


#endif//FrHtTccIncluded
