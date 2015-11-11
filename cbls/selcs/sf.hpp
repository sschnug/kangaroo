/*!
	@file sf.hpp
	@brief The header file for Sf class.
	@details This is the header file for Sf class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SfHppIncluded
#define SfHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"
#include "cbls/selcs/reg.hh"


openKangarooSpace



/*!
	@class Sf
	@brief A template class to represent full selcs.
	@details This template class represents full selcs.
*/
class Sf : public Selc
{
	public:

		static Sf & refm(Hdl const hdlSys, Hdl const hdlSelc);			//!< Reference.
		static Sf * ptrm(Hdl const hdlSys, Hdl const hdlSelc);			//!< Pointer.
		static Sf const & refc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Reference.
		static Sf const * ptrc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Pointer.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);					//!< Suits casting?
		static Bll suit(Selc * theSelc);					//!< Suits casting?
		static Bll suit(Selc const & theSelc);				//!< Suits casting?
		static Bll suit(Selc const * theSelc);				//!< Suits casting?

		static Sf & cast(Selc & theSelc);				//!< Perform casting.
		static Sf * cast(Selc * theSelc);				//!< Perform casting.
		static Sf const & cast(Selc const & theSelc);	//!< Perform casting.
		static Sf const * cast(Selc const * theSelc);	//!< Perform casting.

		//! @}

	protected:

		~Sf();										//!< Destructor.
		Sf(Hdl const hdlSys, Dim const PrmCount);	//!< Constructor.
		Sf(Sf const & that);						//!< Duplicator.
		Sf const & operator = (Sf const & that);	//!< Assigner.
};



/*!
	Whether a selector is suitable for casting.
*/
inline Bln Sf::suit(Selc const & theSelc)
{
	WatchError
	return theSelc.SelcCat == SelcStub< Sf >::SelcCat;
	CatchError
}



/*!
	Whether a selector is suitable for casting.
*/
inline Bln Sf::suit(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCat == SelcStub< Sf >::SelcCat;
	CatchError
}



/*!
	Whether a selector is suitable for casting.
*/
inline Bln Sf::suit(Selc & theSelc)
{
	WatchError
	return theSelc.SelcCat == SelcStub< Sf >::SelcCat;
	CatchError
}



/*!
	Whether a selector is suitable for casting.
*/
inline Bln Sf::suit(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcCat == SelcStub< Sf >::SelcCat;
	CatchError
}



/*!
	Perform casting of a selector.
*/
inline Sf & Sf::cast(Selc & theSelc)
{
	WatchError
	Warn(theSelc.SelcCat != SelcStub< Sf >::SelcCat, eWrongCat);

	return scast<Sf &>(theSelc);
	CatchError
}



/*!
	Perform casting of a selector.
*/
inline Sf * Sf::cast(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Warn(theSelc->SelcCat != SelcStub< Sf >::SelcCat, eWrongCat);

	return scast<Sf *>(theSelc);
	CatchError
}



/*!
	Perform casting of a selector.
*/
inline Sf const & Sf::cast(Selc const & theSelc)
{
	WatchError
	Warn(theSelc.SelcCat != SelcStub< Sf >::SelcCat, eWrongCat);

	return scast<Sf const &>(theSelc);
	CatchError
}



/*!
	Perform casting of a selector.
*/
inline Sf const * Sf::cast(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Warn(theSelc->SelcCat != SelcStub< Sf >::SelcCat, eWrongCat);

	return scast<Sf const *>(theSelc);
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
inline Sf & Sf::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline Sf * Sf::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc));
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
inline Sf const & Sf::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
inline Sf const * Sf::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
	CatchError
}



closeKangarooSpace


#endif	//SfTccIncluded
