/*!
	@file constvt.tcc
	@brief The source file for ConstVt template class.
	@details This is the source file for ConstVt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef ConstVtTccIncluded



#include "cbls/consts/constv.hpp"


openKangarooSpace



/*!
	@class ConstVt
	@brief A template class to represent constants.
	@details This template class represents constants.
*/
template<typename vt>
class ConstVt : public ConstV
{
	public:

		static Hdl def(Hdl const hdlSys, vt const theValue);					//!< Definition.

		//! @name Access
		//! @{

		static ConstVt<vt> & refm(Hdl const hdlSys, Hdl const hdlConst);		//!< Reference.
		static ConstVt<vt> * ptrm(Hdl const hdlSys, Hdl const hdlConst);		//!< Pointer.
		static ConstVt<vt> const & refc(Hdl const hdlSys, Hdl const hdlConst);	//!< Reference.
		static ConstVt<vt> const * ptrc(Hdl const hdlSys, Hdl const hdlConst);	//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static ConstVt<vt> const & cast(Term const & theTerm);	//!< Perform casting.
		static ConstVt<vt> const * cast(Term const * theTerm);	//!< Perform casting.
		static ConstVt<vt> & cast(Term & theTerm);				//!< Perform casting.
		static ConstVt<vt> * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);			//!< Suits casting?
		static Bll suit(Term const * theTerm);			//!< Suits casting?
		static Bll suit(Term & theTerm);				//!< Suits casting?
		static Bll suit(Term * theTerm);				//!< Suits casting?

		//! @}

	public:

		vt const & Value() const;				//!< The value.
		vt const & ExecValue() const;			//!< Executed value.
		vt const & SimulValue() const;			//!< Simulated value.
		virtual Loc ValueLoc() const;			//!< Value locator.
		virtual Typ ValueType() const;			//!< Value type.
		EvalRec<vt> const & ValueRec() const;	//!< Value record.

	private:

		~ConstVt();													//!< Destructor.
		ConstVt(ConstVt<vt> const & that);							//!< Duplicator.
		ConstVt(Hdl const hdlSys, vt const theValue);				//!< Constructor.
		ConstVt<vt> const & operator = (ConstVt<vt> const & that);	//!< Assigner.

		//! @name Identity
		//! @{

		virtual Bll equate(Term const & theTerm) const;		//!< Check equality.
		Hvl calcTermHvl() const;							//!< Calculate hash.

		//! @}

	private:

	/*
		Although the value record below holds the value, a separate value
		holder is required for equality checking and hash value calculation.
	*/

		EvalRec<vt> * 	mValueRec;		//!< Value record.
		vt				mValue;			//!< Value holder.
		Loc 			mValueLoc;		//!< Value locator.
};



/*!
	Define a constant.
*/
template<typename vt>
Hdl ConstVt<vt>::def(Hdl const hdlSys, vt const theValue)
{
	WatchError
	ConstVt<vt> * tConstVt = new ConstVt<vt>(hdlSys, theValue);
	Hdl const tHdl = tConstVt->defSysConst();
	if (tHdl != InvHdl) { delete tConstVt; return tHdl; }

	EvalTbl<vt> & tValueTbl = EvalTbl<vt>::refm(hdlSys);

	tValueTbl.setEvalRec(tConstVt->mValueRec, tConstVt->mValueLoc);
	tConstVt->mValueRec->finalise(theValue);

	return tConstVt->TermHdl;
	CatchError
}



/*!
	Refer to a constant.
*/
template<typename vt>
inline ConstVt<vt> & ConstVt<vt>::refm(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmConst(hdlConst));
	CatchError
}



/*!
	Point to a constant.
*/
template<typename vt>
inline ConstVt<vt> * ConstVt<vt>::ptrm(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmConst(hdlConst));
	CatchError
}



/*!
	Refer to a constant.
*/
template<typename vt>
inline ConstVt<vt> const & ConstVt<vt>::refc(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcConst(hdlConst));
	CatchError
}



/*!
	Point to a constant.
*/
template<typename vt>
inline ConstVt<vt> const * ConstVt<vt>::ptrc(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcConst(hdlConst));
	CatchError
}



/*!
	The constructor.
*/
template<typename vt>
inline ConstVt<vt>::ConstVt(Hdl const hdlSys, vt const theValue) :
		ConstV(hdlSys), mValue(theValue), mValueLoc(InvLoc)
{
	WatchError
	setTermTyp(TermStub< ConstVt<vt> >::TermTyp);
	setTermCls(TermStub< ConstVt<vt> >::TermCls);
	setTermHvl(calcTermHvl());
	CatchError
}



/*!
	The destructor.
*/
template<typename vt>
inline ConstVt<vt>::~ConstVt()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
template<typename vt>
ConstVt<vt>::ConstVt(ConstVt<vt> const & that) : ConstV(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename vt>
ConstVt<vt> const & ConstVt<vt>::operator = (ConstVt<vt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename vt>
inline Bll ConstVt<vt>::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< ConstVt<vt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename vt>
inline Bll ConstVt<vt>::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< ConstVt<vt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename vt>
inline Bll ConstVt<vt>::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCls == TermStub< ConstVt<vt> >::TermCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename vt>
inline Bll ConstVt<vt>::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCls == TermStub< ConstVt<vt> >::TermCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt>
inline ConstVt<vt> & ConstVt<vt>::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< ConstVt<vt> >::TermCls, eWrongCls);

	return scast<ConstVt<vt> &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt>
inline ConstVt<vt> * ConstVt<vt>::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub< ConstVt<vt> >::TermCls, eWrongCls);

	return scast<ConstVt<vt> *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt>
inline ConstVt<vt> const & ConstVt<vt>::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCls != TermStub< ConstVt<vt> >::TermCls, eWrongCls);

	return scast<ConstVt<vt> const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename vt>
inline ConstVt<vt> const * ConstVt<vt>::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCls != TermStub< ConstVt<vt> >::TermCls, eWrongCls);

	return scast<ConstVt<vt> const *>(theTerm);
	CatchError
}



/*!
	Return the value record.
*/
template <typename vt>
inline EvalRec<vt> const & ConstVt<vt>::ValueRec() const
{
	WatchError
	return *mValueRec;
	CatchError
}



/*!
	Return the value locator.
*/
template<typename vt>
inline Loc ConstVt<vt>::ValueLoc() const
{
	WatchError
	return mValueLoc;
	CatchError
}



/*!
	Return the value.
*/
template<typename vt>
inline vt const & ConstVt<vt>::Value() const
{
	WatchError
	return mValue;
	CatchError
}



/*!
	Return the value type.
*/
template<typename vt>
Typ ConstVt<vt>::ValueType() const
{
	WatchError
	return DataStub< vt >::DataTyp;
	CatchError
}


/*!
	Return executed value.
*/
template<typename vt>
vt const & ConstVt<vt>::ExecValue() const
{
	WatchError
	return mValue;
	CatchError
}


/*!
	Return simulated value.
*/
template<typename vt>
vt const & ConstVt<vt>::SimulValue() const
{
	WatchError
	return mValue;
	CatchError
}



/*!
	Calculate the hash value.
*/
template<typename vt>
inline Hvl ConstVt<vt>::calcTermHvl() const
{
	WatchError
	Hvl tHvl = 0;
	mixHash(tHvl, calcHash(this->TermCls));
	mixHash(tHvl, calcHash(mValue));
	return tHvl;
	CatchError
}



/*!
	Check equality of two terms.
*/
template<typename vt>
Bll ConstVt<vt>::equate(Term const & theTerm) const
{
	WatchError
	return theTerm.TermCls == this->TermCls && eq<vt>::iof(mValue, cast(theTerm).mValue);
	CatchError
}



closeKangarooSpace


#endif//ConstVtTccIncluded
