/*!
	@file frrt.tcc
	@brief The prototype file for FrRt template class.
	@details This is the prototype file for FrRt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef FrRtTccIncluded
#define FrRtTccIncluded



#include "cbls/dbases/idx.hpp"
#include "cbls/frames/idx.hh"
#include "cbls/funcs/frr.hpp"

openKangarooSpace



/*!
	@class FrRt
	@brief A template class to represent frr terms.
	@details This template class represents frr terms.
*/
template <typename fmt>
class FrRt : public FrR
{
	public:

		static FrRt<fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static FrRt<fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static FrRt<fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static FrRt<fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static FrRt<fmt> const & cast(Term const & theTerm);	//!< Perform casting.
		static FrRt<fmt> const * cast(Term const * theTerm);	//!< Perform casting.
		static FrRt<fmt> & cast(Term & theTerm);				//!< Perform casting.
		static FrRt<fmt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	public:

		virtual Typ MetricType() const;							//!< The metric type.

	protected:

		virtual ~FrRt();										//!< Destructor.
		FrRt(FrRt<fmt> const & that);							//!< Duplicator.
		FrRt(Hdl const hdlSys, Dim const PrmCount);				//!< Constructor.
		FrRt<fmt> const & operator = (FrRt<fmt> const & that);	//!< Assigner.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FrRt<fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FrRt<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FrRt<fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FrRt<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FrRt<fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FrRt<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FrRt<fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FrRt<fmt> >::TermTyp;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FrRt<fmt> const & FrRt<fmt>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FrRt<fmt> >::TermTyp, eWrongTyp);

	return scast<FrRt<fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FrRt<fmt> const * FrRt<fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FrRt<fmt> >::TermTyp, eWrongTyp);

	return scast<FrRt<fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FrRt<fmt> & FrRt<fmt>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FrRt<fmt> >::TermTyp, eWrongTyp);

	return scast<FrRt<fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FrRt<fmt> * FrRt<fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FrRt<fmt> >::TermTyp, eWrongTyp);

	return scast<FrRt<fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to a frrt term.
*/
template <typename fmt>
inline FrRt<fmt> & FrRt<fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a frrt term.
*/
template <typename fmt>
inline FrRt<fmt> * FrRt<fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a frrt term.
*/
template <typename fmt>
inline FrRt<fmt> const & FrRt<fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a frrt term.
*/
template <typename fmt>
inline FrRt<fmt> const * FrRt<fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The constructor.
*/
template <typename fmt>
inline FrRt<fmt>::FrRt(Hdl const hdlSys, Dim const PrmCount) :
		FrR(hdlSys, PrmCount)
{
	WatchError
	this->setTermTyp(TermStub< FrRt<fmt> >::TermTyp);
	CatchError
}


/*!
	The destructor.
*/
template <typename fmt>
inline FrRt<fmt>::~FrRt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Return metric type.
*/
template<typename fmt>
Typ FrRt<fmt>::MetricType() const
{
	WatchError
	return DataStub< fmt >::DataTyp;
	CatchError
}



/*!
	The duplicator.
*/
template <typename fmt>
FrRt<fmt>::FrRt(FrRt<fmt> const & that) : FrR(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fmt>
FrRt<fmt> const & FrRt<fmt>::operator = (FrRt<fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



closeKangarooSpace


#endif//FrRtTccIncluded
