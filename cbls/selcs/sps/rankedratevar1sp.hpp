/*!
	@file rankedratevar1sp.hpp
	@brief The header file for RankedRateVar1Sp class.
	@details This is the header file for RankedRateVar1Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef RankedRateVar1SpHppIncluded
#define RankedRateVar1SpHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"
#include "cbls/selcs/reg.hh"
#include "cbls/selcs/sps/reg.hh"
#include "cbls/funcs/frrs/idx.hh"


openKangarooSpace



/*!
	@class RankedRateVar1Sp
	@brief A template class to represent ranked rate single variable prep selcs.
	@details This template class represents ranked rate single variable prep selcs.
*/
class RankedRateVar1Sp : public SpXn
{
	public:

		static Hdl def(Hdl const hdlSys, Prm const & prmTerm);						//!< Define a selc.

		static RankedRateVar1Sp & refm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Refer to a selc.
		static RankedRateVar1Sp * ptrm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Point to a selc.
		static RankedRateVar1Sp const & refc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Refer to a selc.
		static RankedRateVar1Sp const * ptrc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Point to a selc.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);					//!< Suits casting?
		static Bll suit(Selc * theSelc);					//!< Suits casting?
		static Bll suit(Selc const & theSelc);				//!< Suits casting?
		static Bll suit(Selc const * theSelc);				//!< Suits casting?

		static RankedRateVar1Sp & cast(Selc & theSelc);				//!< Perform casting.
		static RankedRateVar1Sp * cast(Selc * theSelc);				//!< Perform casting.
		static RankedRateVar1Sp const & cast(Selc const & theSelc);	//!< Perform casting.
		static RankedRateVar1Sp const * cast(Selc const * theSelc);	//!< Perform casting.

		//! @}

	private:

		RankedRateVar1Sp(Hdl const hdlSys, Prm * prmTerm, Dim const PrmCount);	//!< Constructor.
		RankedRateVar1Sp(RankedRateVar1Sp const & that);						//!< Duplicator.
		RankedRateVar1Sp const & operator = (RankedRateVar1Sp const & that);	//!< Assigner.
		~RankedRateVar1Sp();													//!< Destructor.

		virtual Bll select(Rnd & theRnd);			//!< Run the selector, return whether successful.
		#if CompLazyHalf
		virtual void require(Bll const SetNotUnset);//!< Set requirement as per activation.
		#endif // CompLazyHalf
};



/*!
	Whether a term is suitable for casting.
*/
inline Bln RankedRateVar1Sp::suit(Selc const & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< RankedRateVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln RankedRateVar1Sp::suit(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< RankedRateVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln RankedRateVar1Sp::suit(Selc & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< RankedRateVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln RankedRateVar1Sp::suit(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< RankedRateVar1Sp >::SelcCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline RankedRateVar1Sp & RankedRateVar1Sp::cast(Selc & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< RankedRateVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<RankedRateVar1Sp &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline RankedRateVar1Sp * RankedRateVar1Sp::cast(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< RankedRateVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<RankedRateVar1Sp *>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline RankedRateVar1Sp const & RankedRateVar1Sp::cast(Selc const & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< RankedRateVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<RankedRateVar1Sp const &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline RankedRateVar1Sp const * RankedRateVar1Sp::cast(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< RankedRateVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<RankedRateVar1Sp const *>(theSelc);
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
inline RankedRateVar1Sp & RankedRateVar1Sp::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline RankedRateVar1Sp * RankedRateVar1Sp::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc));
	CatchError
}




/*!
	Refer to a selc in the sys.
*/
inline RankedRateVar1Sp const & RankedRateVar1Sp::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline RankedRateVar1Sp const * RankedRateVar1Sp::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
	CatchError
}



/*!
	The destructor.
*/

inline RankedRateVar1Sp::~RankedRateVar1Sp()
{
	WatchError
	//	nothing to be done.
	CatchError
}


closeKangarooSpace


#endif	//RankedRateVar1SpHppIncluded
