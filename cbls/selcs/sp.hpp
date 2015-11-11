/*!
	@file sp.hpp
	@brief The header file for Sp class.
	@details This is the header file for Sp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SpHppIncluded
#define SpHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"
#include "cbls/selcs/reg.hh"


openKangarooSpace



/*!
	@class Sp
	@brief A template class to represent part selcs.
	@details This template class represents part selcs.
*/
class Sp : public Selc
{
	public:

		static Sp & refm(Hdl const hdlSys, Hdl const hdlSelc);			//!< Reference.
		static Sp * ptrm(Hdl const hdlSys, Hdl const hdlSelc);			//!< Pointer.
		static Sp const & refc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Reference.
		static Sp const * ptrc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Pointer.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);					//!< Suits casting?
		static Bll suit(Selc * theSelc);					//!< Suits casting?
		static Bll suit(Selc const & theSelc);				//!< Suits casting?
		static Bll suit(Selc const * theSelc);				//!< Suits casting?

		static Sp & cast(Selc & theSelc);				//!< Perform casting.
		static Sp * cast(Selc * theSelc);				//!< Perform casting.
		static Sp const & cast(Selc const & theSelc);	//!< Perform casting.
		static Sp const * cast(Selc const * theSelc);	//!< Perform casting.

		//! @}

	protected:

		~Sp();										//!< Destructor.
		Sp(Hdl const hdlSys, Dim const PrmCount);	//!< Constructor.
		Sp(Sp const & that);						//!< Duplicator.
		Sp const & operator = (Sp const & that);	//!< Assigner.

		virtual void execute();						//!< Execute selection.
};



/*!
	Whether a selector is suitable for casting.
*/
inline Bln Sp::suit(Selc const & theSelc)
{
	WatchError
	return theSelc.SelcCat == SelcStub< Sp >::SelcCat;
	CatchError
}



/*!
	Whether a selector is suitable for casting.
*/
inline Bln Sp::suit(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCat == SelcStub< Sp >::SelcCat;
	CatchError
}



/*!
	Whether a selector is suitable for casting.
*/
inline Bln Sp::suit(Selc & theSelc)
{
	WatchError
	return theSelc.SelcCat == SelcStub< Sp >::SelcCat;
	CatchError
}



/*!
	Whether a selector is suitable for casting.
*/
inline Bln Sp::suit(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCat == SelcStub< Sp >::SelcCat;
	CatchError
}



/*!
	Perform casting of a selector.
*/
inline Sp & Sp::cast(Selc & theSelc)
{
	WatchError
	Warn(theSelc.SelcCat != SelcStub< Sp >::SelcCat, eWrongCat);

	return scast<Sp &>(theSelc);
	CatchError
}



/*!
	Perform casting of a selector.
*/
inline Sp * Sp::cast(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Warn(theSelc->SelcCat != SelcStub< Sp >::SelcCat, eWrongCat);

	return scast<Sp *>(theSelc);
	CatchError
}



/*!
	Perform casting of a selector.
*/
inline Sp const & Sp::cast(Selc const & theSelc)
{
	WatchError
	Warn(theSelc.SelcCat != SelcStub< Sp >::SelcCat, eWrongCat);

	return scast<Sp const &>(theSelc);
	CatchError
}



/*!
	Perform casting of a selector.
*/
inline Sp const * Sp::cast(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Warn(theSelc->SelcCat != SelcStub< Sp >::SelcCat, eWrongCat);

	return scast<Sp const *>(theSelc);
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
inline Sp & Sp::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline Sp * Sp::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc));
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
inline Sp const & Sp::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline Sp const * Sp::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
	CatchError
}



closeKangarooSpace


#endif	//SpTccIncluded
