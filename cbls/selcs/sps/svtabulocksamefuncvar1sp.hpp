/*!
	@file svtabulocksamefuncvar1sp.hpp
	@brief The header file for SvTabuLockSameFuncVar1Sp class.
	@details This is the header file for SvTabuLockSameFuncVar1Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SvTabuLockSameFuncVar1SpHppIncluded
#define SvTabuLockSameFuncVar1SpHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"
#include "cbls/selcs/reg.hh"
#include "cbls/selcs/sps/reg.hh"
#include "cbls/funcs/frhs/idx.hh"


openKangarooSpace



/*!
	@class SvTabuLockSameFuncVar1Sp
	@brief A template class to represent a tabu- and lock-aware prep selector to randomly choose a variable from a function.
	@details This template class represents a tabu- and lock-aware prep selector to randomly choose a variable from a function.
*/
class SvTabuLockSameFuncVar1Sp : public SpXn
{
	public:

		static Hdl def(Hdl const hdlSys, Prm const & prmTerm, Typ const typTabu);			//!< Define a selc.

		static SvTabuLockSameFuncVar1Sp & refm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Refer to a selc.
		static SvTabuLockSameFuncVar1Sp * ptrm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Point to a selc.
		static SvTabuLockSameFuncVar1Sp const & refc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Refer to a selc.
		static SvTabuLockSameFuncVar1Sp const * ptrc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Point to a selc.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);					//!< Suits casting?
		static Bll suit(Selc * theSelc);					//!< Suits casting?
		static Bll suit(Selc const & theSelc);				//!< Suits casting?
		static Bll suit(Selc const * theSelc);				//!< Suits casting?

		static SvTabuLockSameFuncVar1Sp & cast(Selc & theSelc);				//!< Perform casting.
		static SvTabuLockSameFuncVar1Sp * cast(Selc * theSelc);				//!< Perform casting.
		static SvTabuLockSameFuncVar1Sp const & cast(Selc const & theSelc);	//!< Perform casting.
		static SvTabuLockSameFuncVar1Sp const * cast(Selc const * theSelc);	//!< Perform casting.

		//! @}

	private:

		SvTabuLockSameFuncVar1Sp(Hdl const hdlSys, Prm * prmTerm,
												Dim const PrmCount, Typ const typTabu);		//!< Constructor.
		SvTabuLockSameFuncVar1Sp(SvTabuLockSameFuncVar1Sp const & that);					//!< Duplicator.
		SvTabuLockSameFuncVar1Sp const & operator = (SvTabuLockSameFuncVar1Sp const & that);//!< Assigner.
		~SvTabuLockSameFuncVar1Sp();														//!< Destructor.

		virtual Bll select(Rnd & theRnd);			//!< Run the selector, return whether successful.
		#if CompLazyHalf
		virtual void require(Bll const SetNotUnset);//!< Set requirement as per activation.
		#endif // CompLazyHalf

		SvTabu const &			mSysTabu;		//!< System's single tabu.
};



/*!
	Whether a term is suitable for casting.
*/
inline Bln SvTabuLockSameFuncVar1Sp::suit(Selc const & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< SvTabuLockSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln SvTabuLockSameFuncVar1Sp::suit(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< SvTabuLockSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln SvTabuLockSameFuncVar1Sp::suit(Selc & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< SvTabuLockSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln SvTabuLockSameFuncVar1Sp::suit(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< SvTabuLockSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline SvTabuLockSameFuncVar1Sp & SvTabuLockSameFuncVar1Sp::cast(Selc & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< SvTabuLockSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<SvTabuLockSameFuncVar1Sp &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline SvTabuLockSameFuncVar1Sp * SvTabuLockSameFuncVar1Sp::cast(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< SvTabuLockSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<SvTabuLockSameFuncVar1Sp *>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline SvTabuLockSameFuncVar1Sp const & SvTabuLockSameFuncVar1Sp::cast(Selc const & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< SvTabuLockSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<SvTabuLockSameFuncVar1Sp const &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline SvTabuLockSameFuncVar1Sp const * SvTabuLockSameFuncVar1Sp::cast(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< SvTabuLockSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<SvTabuLockSameFuncVar1Sp const *>(theSelc);
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
inline SvTabuLockSameFuncVar1Sp & SvTabuLockSameFuncVar1Sp::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline SvTabuLockSameFuncVar1Sp * SvTabuLockSameFuncVar1Sp::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc));
	CatchError
}




/*!
	Refer to a selc in the sys.
*/
inline SvTabuLockSameFuncVar1Sp const & SvTabuLockSameFuncVar1Sp::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline SvTabuLockSameFuncVar1Sp const * SvTabuLockSameFuncVar1Sp::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
	CatchError
}



/*!
	The destructor.
*/

inline SvTabuLockSameFuncVar1Sp::~SvTabuLockSameFuncVar1Sp()
{
	WatchError
	//	nothing to be done.
	CatchError
}


closeKangarooSpace


#endif	//SvTabuLockSameFuncVar1SpHppIncluded
