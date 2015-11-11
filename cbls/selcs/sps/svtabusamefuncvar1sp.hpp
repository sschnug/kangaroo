/*!
	@file svtabusamefuncvar1sp.hpp
	@brief The header file for SvTabuSameFuncVar1Sp class.
	@details This is the header file for SvTabuSameFuncVar1Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SvTabuSameFuncVar1SpHppIncluded
#define SvTabuSameFuncVar1SpHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"
#include "cbls/selcs/reg.hh"
#include "cbls/selcs/sps/reg.hh"
#include "cbls/funcs/frhs/idx.hh"


openKangarooSpace



/*!
	@class SvTabuSameFuncVar1Sp
	@brief A template class to represent a tabu-aware prep selector to randomly choose a variable from a function.
	@details This template class represents a tabu-aware prep selector to randomly choose a variable from a function.
*/
class SvTabuSameFuncVar1Sp : public SpXn
{
	public:

		static Hdl def(Hdl const hdlSys, Prm const & prmTerm, Typ const typTabu);		//!< Define a selc.

		static SvTabuSameFuncVar1Sp & refm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Refer to a selc.
		static SvTabuSameFuncVar1Sp * ptrm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Point to a selc.
		static SvTabuSameFuncVar1Sp const & refc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Refer to a selc.
		static SvTabuSameFuncVar1Sp const * ptrc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Point to a selc.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);					//!< Suits casting?
		static Bll suit(Selc * theSelc);					//!< Suits casting?
		static Bll suit(Selc const & theSelc);				//!< Suits casting?
		static Bll suit(Selc const * theSelc);				//!< Suits casting?

		static SvTabuSameFuncVar1Sp & cast(Selc & theSelc);				//!< Perform casting.
		static SvTabuSameFuncVar1Sp * cast(Selc * theSelc);				//!< Perform casting.
		static SvTabuSameFuncVar1Sp const & cast(Selc const & theSelc);	//!< Perform casting.
		static SvTabuSameFuncVar1Sp const * cast(Selc const * theSelc);	//!< Perform casting.

		//! @}

	private:

		SvTabuSameFuncVar1Sp(Hdl const hdlSys, Prm * prmTerm,
										Dim const PrmCount, Typ const typTabu);			//!< Constructor.
		SvTabuSameFuncVar1Sp(SvTabuSameFuncVar1Sp const & that);						//!< Duplicator.
		SvTabuSameFuncVar1Sp const & operator = (SvTabuSameFuncVar1Sp const & that);	//!< Assigner.
		~SvTabuSameFuncVar1Sp();														//!< Destructor.

		virtual Bll select(Rnd & theRnd);			//!< Run the selector, return whether successful.
		#if CompLazyHalf
		virtual void require(Bll const SetNotUnset);//!< Set requirement as per activation.
		#endif // CompLazyHalf

		SvTabu const &			mSysTabu;		//!< System's single tabu.
};



/*!
	Whether a term is suitable for casting.
*/
inline Bln SvTabuSameFuncVar1Sp::suit(Selc const & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< SvTabuSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln SvTabuSameFuncVar1Sp::suit(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< SvTabuSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln SvTabuSameFuncVar1Sp::suit(Selc & theSelc)
{
	WatchError
	return theSelc.SelcCls == SelcStub< SvTabuSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bln SvTabuSameFuncVar1Sp::suit(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCls == SelcStub< SvTabuSameFuncVar1Sp >::SelcCls;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline SvTabuSameFuncVar1Sp & SvTabuSameFuncVar1Sp::cast(Selc & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< SvTabuSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<SvTabuSameFuncVar1Sp &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline SvTabuSameFuncVar1Sp * SvTabuSameFuncVar1Sp::cast(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< SvTabuSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<SvTabuSameFuncVar1Sp *>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline SvTabuSameFuncVar1Sp const & SvTabuSameFuncVar1Sp::cast(Selc const & theSelc)
{
	WatchError
	Wchk(theSelc.SelcCls != SelcStub< SvTabuSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<SvTabuSameFuncVar1Sp const &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline SvTabuSameFuncVar1Sp const * SvTabuSameFuncVar1Sp::cast(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Wchk(theSelc->SelcCls != SelcStub< SvTabuSameFuncVar1Sp >::SelcCls) Wtxt(eWrongCls);

	return scast<SvTabuSameFuncVar1Sp const *>(theSelc);
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
inline SvTabuSameFuncVar1Sp & SvTabuSameFuncVar1Sp::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline SvTabuSameFuncVar1Sp * SvTabuSameFuncVar1Sp::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc));
	CatchError
}




/*!
	Refer to a selc in the sys.
*/
inline SvTabuSameFuncVar1Sp const & SvTabuSameFuncVar1Sp::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline SvTabuSameFuncVar1Sp const * SvTabuSameFuncVar1Sp::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
	CatchError
}



/*!
	The destructor.
*/

inline SvTabuSameFuncVar1Sp::~SvTabuSameFuncVar1Sp()
{
	WatchError
	//	nothing to be done.
	CatchError
}


closeKangarooSpace


#endif	//SvTabuSameFuncVar1SpHppIncluded
