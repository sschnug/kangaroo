/*!
	@file locksamefuncvar1sp.hpp
	@brief The header file for LockSameFuncVar1Sp class.
	@details This is the header file for LockSameFuncVar1Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef LockSameFuncVar1SpHppIncluded
#define LockSameFuncVar1SpHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"
#include "cbls/selcs/reg.hh"
#include "cbls/selcs/sps/reg.hh"
#include "cbls/funcs/frhs/idx.hh"


openKangarooSpace



/*!
	@class LockSameFuncVar1Sp
	@brief A template class to represent a lock-aware prep selector to randomly choose a variable from a function.
	@details This template class represents a lock-aware prep selector to randomly choose a variable from a function.
*/
class LockSameFuncVar1Sp : public SpXn
{
	public:

		static Hdl def(Hdl const hdlSys, Prm const & prmTerm);						//!< Define a selc.

		static LockSameFuncVar1Sp & refm(Hdl const hdlSys, Hdl const hdlSelc);			//!< Refer to a selc.
		static LockSameFuncVar1Sp * ptrm(Hdl const hdlSys, Hdl const hdlSelc);			//!< Point to a selc.
		static LockSameFuncVar1Sp const & refc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Refer to a selc.
		static LockSameFuncVar1Sp const * ptrc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Point to a selc.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);					//!< Suits casting?
		static Bll suit(Selc * theSelc);					//!< Suits casting?
		static Bll suit(Selc const & theSelc);				//!< Suits casting?
		static Bll suit(Selc const * theSelc);				//!< Suits casting?

		static LockSameFuncVar1Sp & cast(Selc & theSelc);				//!< Perform casting.
		static LockSameFuncVar1Sp * cast(Selc * theSelc);				//!< Perform casting.
		static LockSameFuncVar1Sp const & cast(Selc const & theSelc);	//!< Perform casting.
		static LockSameFuncVar1Sp const * cast(Selc const * theSelc);	//!< Perform casting.

		//! @}

	private:

		LockSameFuncVar1Sp(Hdl const hdlSys, Prm * prmTerm, Dim const PrmCount);	//!< Constructor.
		LockSameFuncVar1Sp(LockSameFuncVar1Sp const & that);						//!< Duplicator.
		LockSameFuncVar1Sp const & operator = (LockSameFuncVar1Sp const & that);	//!< Assigner.
		~LockSameFuncVar1Sp();														//!< Destructor.

		virtual Bll select(Rnd & theRnd);			//!< Run the selector, return whether successful.
		#if CompLazyHalf
		virtual void require(Bll const SetNotUnset);//!< Set requirement as per activation.
		#endif // CompLazyHalf
};



/*!
	Whether a term is suitable for casting.
*/
inline Bln LockSameFuncVar1Sp::suit(Selc const & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< LockSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln LockSameFuncVar1Sp::suit(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< LockSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln LockSameFuncVar1Sp::suit(Selc & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< LockSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln LockSameFuncVar1Sp::suit(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< LockSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline LockSameFuncVar1Sp & LockSameFuncVar1Sp::cast(Selc & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< LockSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<LockSameFuncVar1Sp &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline LockSameFuncVar1Sp * LockSameFuncVar1Sp::cast(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< LockSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<LockSameFuncVar1Sp *>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline LockSameFuncVar1Sp const & LockSameFuncVar1Sp::cast(Selc const & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< LockSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<LockSameFuncVar1Sp const &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline LockSameFuncVar1Sp const * LockSameFuncVar1Sp::cast(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< LockSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<LockSameFuncVar1Sp const *>(theSelc);
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
inline LockSameFuncVar1Sp & LockSameFuncVar1Sp::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline LockSameFuncVar1Sp * LockSameFuncVar1Sp::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc));
	CatchError
}




/*!
	Refer to a selc in the sys.
*/
inline LockSameFuncVar1Sp const & LockSameFuncVar1Sp::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline LockSameFuncVar1Sp const * LockSameFuncVar1Sp::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
	CatchError
}



/*!
	The destructor.
*/

inline LockSameFuncVar1Sp::~LockSameFuncVar1Sp()
{
	WatchError
	//	nothing to be done.
	CatchError
}


closeKangarooSpace


#endif	//LockSameFuncVar1SpHppIncluded
