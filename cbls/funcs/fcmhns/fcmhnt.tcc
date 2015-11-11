/*!
	@file fcmhnt.tcc
	@brief The prototype file for FcMHnT template class.
	@details This is the prototype file for FcMHnT template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef FcMHnTTccIncluded
#define FcMHnTTccIncluded



#include "cbls/dbases/idx.hpp"
#include "cbls/frames/idx.hh"
#include "cbls/funcs/fcmhn.hpp"


openKangarooSpace



/*!
	@class FcMHnT
	@brief A class to represent fcmhnts.
	@details This class represents fcmhnts.
*/
template <typename fmt>
class FcMHnT : public FcMHn
{
	public:
		static FcMHnT<fmt> & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static FcMHnT<fmt> * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static FcMHnT<fmt> const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static FcMHnT<fmt> const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static Bll suit(Term & theTerm);						//!< Suits casting?
		static Bll suit(Term * theTerm);						//!< Suits casting?
		static Bll suit(Term const & theTerm);					//!< Suits casting?
		static Bll suit(Term const * theTerm);					//!< Suits casting?

		static FcMHnT<fmt> & cast(Term & theTerm);				//!< Perform casting.
		static FcMHnT<fmt> * cast(Term * theTerm);				//!< Perform casting.
		static FcMHnT<fmt> const & cast(Term const & theTerm);	//!< Perform casting.
		static FcMHnT<fmt> const * cast(Term const * theTerm);	//!< Perform casting.

		//! @}

	public:

		virtual Loc MetricLoc() const;				//!< Metric locator.
		virtual Loc HintMinLoc() const;				//!< Hint min locator.
		EvalRec<fmt> const & MetricRec() const;		//!< Get the metric record.
		HintRec<fmt> const & HintMinRec() const;	//!< Get the hint min record.

	protected:

		FcMHnT(Hdl const hdlSys, Dim const PrmCount);				//!< Constructor.
		FcMHnT<fmt> const & operator = (FcMHnT<fmt> const & that);	//!< Assigner.
		FcMHnT(FcMHnT<fmt> const & that);							//!< Duplicator.
		virtual ~FcMHnT();											//!< Destructor.

		virtual Typ MetricType() const;								//!< Metric type.

		Loc mMetricLoc;												//!< Metric locator.
		Loc mHintMinLoc;											//!< Hint min locator.
		EvalRec<fmt> * mMetricRec;									//!< Metric record.
		HintRec<fmt> * mHintMinRec;									//!< Hint min  record.
};



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FcMHnT<fmt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FcMHnT<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FcMHnT<fmt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FcMHnT<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FcMHnT<fmt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermTyp == TermStub< FcMHnT<fmt> >::TermTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template <typename fmt>
inline Bll FcMHnT<fmt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermTyp == TermStub< FcMHnT<fmt> >::TermTyp;
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FcMHnT<fmt> const & FcMHnT<fmt>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FcMHnT<fmt> >::TermTyp, eWrongTyp);

	return scast<FcMHnT<fmt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FcMHnT<fmt> const * FcMHnT<fmt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FcMHnT<fmt> >::TermTyp, eWrongTyp);

	return scast<FcMHnT<fmt> const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FcMHnT<fmt> & FcMHnT<fmt>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermTyp != TermStub< FcMHnT<fmt> >::TermTyp, eWrongTyp);

	return scast<FcMHnT<fmt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template <typename fmt>
inline FcMHnT<fmt> * FcMHnT<fmt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermTyp != TermStub< FcMHnT<fmt> >::TermTyp, eWrongTyp);

	return scast<FcMHnT<fmt> *>(theTerm);
	CatchError
}



/*!
	Refer to a fcmhnt term.
*/
template <typename fmt>
inline FcMHnT<fmt> & FcMHnT<fmt>::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fcmhnt term.
*/
template <typename fmt>
inline FcMHnT<fmt> * FcMHnT<fmt>::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to a fcmhnt term.
*/
template <typename fmt>
inline FcMHnT<fmt> const & FcMHnT<fmt>::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a fcmhnt term.
*/
template <typename fmt>
inline FcMHnT<fmt> const * FcMHnT<fmt>::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The constructor.
*/
template <typename fmt>
inline FcMHnT<fmt>::FcMHnT(Hdl const hdlSys, Dim const PrmCount) :
		FcMHn(hdlSys, PrmCount), mMetricLoc(InvLoc), mHintMinLoc(InvLoc)
{
	WatchError
	this->setTermTyp(TermStub< FcMHnT<fmt> >::TermTyp);
	CatchError
}


/*!
	The destructor.
*/
template <typename fmt>
inline FcMHnT<fmt>::~FcMHnT()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Return metric type.
*/
template<typename fmt>
Typ FcMHnT<fmt>::MetricType() const
{
	WatchError
	return DataStub< fmt >::DataTyp;
	CatchError
}



/*!
	Return metric locator.
*/
template<typename fmt>
inline Loc FcMHnT<fmt>::MetricLoc() const
{
	WatchError
	return mMetricLoc;
	CatchError
}



/*!
	Return hint min locator.
*/
template<typename fmt>
inline Loc FcMHnT<fmt>::HintMinLoc() const
{
	WatchError
	return mHintMinLoc;
	CatchError
}



/*!
	Return the metric record.
*/
template <typename fmt>
inline EvalRec<fmt> const & FcMHnT<fmt>::MetricRec() const
{
	WatchError
	return *(this->mMetricRec);
	CatchError
}



/*!
	Return the hint min record.
*/
template <typename fmt>
inline HintRec<fmt> const & FcMHnT<fmt>::HintMinRec() const
{
	WatchError
	return *(this->mHintMinRec);
	CatchError
}



/*!
	The duplicator.
*/
template <typename fmt>
FcMHnT<fmt>::FcMHnT(FcMHnT<fmt> const & that) : FcMHn(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template <typename fmt>
FcMHnT<fmt> const & FcMHnT<fmt>::operator = (FcMHnT<fmt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}




closeKangarooSpace


#endif//FcMHnTTccIncluded
