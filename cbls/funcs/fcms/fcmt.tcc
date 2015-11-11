/*!
	@file fcmt.tcc
	@brief The prototype file for FcMt template class.
	@details This is the prototype file for FcMt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef FcMtTccIncluded
#define FcMtTccIncluded



#include "cbls/dbases/idx.hpp"
#include "cbls/frames/idx.hh"
#include "cbls/funcs/fcm.hpp"

openKangarooSpace



/*!
	@class FcMt
	@brief A template class to represent fcm terms.
	@details This template class represents fcm terms.
*/
template <typename fmt>
class FcMt : public FcM
{
	public:

		static FcMt<fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static FcMt<fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static FcMt<fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static FcMt<fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static FcMt<fmt> const & cast(Term const & theTerm);	//!< Perform casting.
		static FcMt<fmt> const * cast(Term const * theTerm);	//!< Perform casting.
		static FcMt<fmt> & cast(Term & theTerm);				//!< Perform casting.
		static FcMt<fmt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?
		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?

		//! @}

	public:

		virtual Loc MetricLoc() const;							//!< The metric locator.
		virtual Typ MetricType() const;							//!< The metric type.
		EvalRec<fmt> const & MetricRec() const;					//!< The metric record.

	protected:

		virtual ~FcMt();										//!< Destructor.
		FcMt(FcMt<fmt> const & that);							//!< Duplicator.
		FcMt(Hdl const hdlSys, Dim const PrmCount);				//!< Constructor.
		FcMt<fmt> const & operator = (FcMt<fmt> const & that);	//!< Assigner.

	protected:

		Loc mMetricLoc;											//!< The metric locator.
		EvalRec<fmt> * mMetricRec;								//!< The metric record.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FcMt<fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FcMt<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FcMt<fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FcMt<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FcMt<fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FcMt<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FcMt<fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FcMt<fmt> >::TermTyp;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FcMt<fmt> const & FcMt<fmt>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FcMt<fmt> >::TermTyp, eWrongTyp);

	return scast<FcMt<fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FcMt<fmt> const * FcMt<fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FcMt<fmt> >::TermTyp, eWrongTyp);

	return scast<FcMt<fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FcMt<fmt> & FcMt<fmt>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FcMt<fmt> >::TermTyp, eWrongTyp);

	return scast<FcMt<fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FcMt<fmt> * FcMt<fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FcMt<fmt> >::TermTyp, eWrongTyp);

	return scast<FcMt<fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to a fcmt term.
*/
template <typename fmt>
inline FcMt<fmt> & FcMt<fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fcmt term.
*/
template <typename fmt>
inline FcMt<fmt> * FcMt<fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a fcmt term.
*/
template <typename fmt>
inline FcMt<fmt> const & FcMt<fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fcmt term.
*/
template <typename fmt>
inline FcMt<fmt> const * FcMt<fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The constructor.
*/
template <typename fmt>
inline FcMt<fmt>::FcMt(Hdl const hdlSys, Dim const PrmCount) :
		FcM(hdlSys, PrmCount), mMetricLoc(InvLoc)
{
	WatchError
	this->setTermTyp(TermStub< FcMt<fmt> >::TermTyp);
	CatchError
}


/*!
	The destructor.
*/
template <typename fmt>
inline FcMt<fmt>::~FcMt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Return metric type.
*/
template<typename fmt>
Typ FcMt<fmt>::MetricType() const
{
	WatchError
	return DataStub< fmt >::DataTyp;
	CatchError
}



/*!
	Return the metric locator.
*/
template<typename fmt>
inline Loc FcMt<fmt>::MetricLoc() const
{
	WatchError
	return mMetricLoc;
	CatchError
}




/*!
	Return the metric record.
*/
template <typename fmt>
inline EvalRec<fmt> const & FcMt<fmt>::MetricRec() const
{
	WatchError
	return *(this->mMetricRec);
	CatchError
}



/*!
	The duplicator.
*/
template <typename fmt>
FcMt<fmt>::FcMt(FcMt<fmt> const & that) : FcM(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fmt>
FcMt<fmt> const & FcMt<fmt>::operator = (FcMt<fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



closeKangarooSpace


#endif//FcMtTccIncluded
