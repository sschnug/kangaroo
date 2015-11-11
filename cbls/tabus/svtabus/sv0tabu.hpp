/*!
	@file sv0tabu.hpp
	@brief The prototype file for Sv0Tabu class.
	@details This is the prototype file for Sv0Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see tabu.cpp
*/



#ifndef Sv0TabuHppIncluded
#define Sv0TabuHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/tabus/svtabu.hpp"
#include "cbls/tabus/reg.hh"



openKangarooSpace



/*!
	@class Sv0Tabu
	@brief A class to represent single tabu variables with no call back.
	@details This class represents single tabu variables with no call back.
*/
class Sv0Tabu : public SvTabu
{
	public:

		//! @name Access
		//! @{

		static Sv0Tabu & refm(Hdl const hdlSys);			//!< Reference.
		static Sv0Tabu * ptrm(Hdl const hdlSys);			//!< Pointer.
		static Sv0Tabu const & refc(Hdl const hdlSys);		//!< Reference.
		static Sv0Tabu const * ptrc(Hdl const hdlSys);		//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static Sv0Tabu const & cast(Tabu const & theTabu);	//!< Perform casting.
		static Sv0Tabu const * cast(Tabu const * theTabu);	//!< Perform casting.
		static Sv0Tabu & cast(Tabu & theTabu);				//!< Perform casting.
		static Sv0Tabu * cast(Tabu * theTabu);				//!< Perform casting.

		static Bll suit(Tabu const & theTabu);				//!< Suits casting?
		static Bll suit(Tabu const * theTabu);				//!< Suits casting?
		static Bll suit(Tabu & theTabu);					//!< Suits casting?
		static Bll suit(Tabu * theTabu);					//!< Suits casting?

		//! @}

	protected:

		~Sv0Tabu();											//!< Destructor.
		Sv0Tabu(Sv0Tabu const & that);						//!< Duplicator.
		Sv0Tabu(Hdl const hdlSys);							//!< Initialiser.
		Sv0Tabu const & operator = (Sv0Tabu const & that);	//!< Assigner.
};




/*!
	The constructor.
*/
inline Sv0Tabu::Sv0Tabu(Hdl const hdlSys) : SvTabu(hdlSys)
{
	WatchError
	setTabuTyp(TabuStub<Sv0Tabu>::TabuTyp);
	CatchError
}



/*!
	The destructor.
*/
inline Sv0Tabu::~Sv0Tabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Sv0Tabu::suit(Tabu const & theTabu)
{
	WatchError
	return theTabu.TabuTyp == TabuStub< Sv0Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Sv0Tabu::suit(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuTyp == TabuStub< Sv0Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Sv0Tabu::suit(Tabu & theTabu)
{
	WatchError
	return theTabu.TabuTyp == TabuStub< Sv0Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Sv0Tabu::suit(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuTyp == TabuStub< Sv0Tabu >::TabuTyp;
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Sv0Tabu const & Sv0Tabu::cast(Tabu const & theTabu)
{
	WatchError
	Warn(theTabu.TabuTyp != TabuStub< Sv0Tabu >::TabuTyp, eWrongTyp);
	return scast<Sv0Tabu const &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Sv0Tabu const * Sv0Tabu::cast(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuTyp != TabuStub< Sv0Tabu >::TabuTyp, eWrongTyp);

	return scast<Sv0Tabu const *>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Sv0Tabu & Sv0Tabu::cast(Tabu & theTabu)
{
	WatchError
	Warn(theTabu.TabuTyp != TabuStub< Sv0Tabu >::TabuTyp, eWrongTyp);

	return scast<Sv0Tabu &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Sv0Tabu * Sv0Tabu::cast(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuTyp != TabuStub< Sv0Tabu >::TabuTyp, eWrongTyp);

	return scast<Sv0Tabu *>(theTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
inline Sv0Tabu & Sv0Tabu::refm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmTabu(TabuStub<Sv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline Sv0Tabu * Sv0Tabu::ptrm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmTabu(TabuStub<Sv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Refer to a tabu.
*/
inline Sv0Tabu const & Sv0Tabu::refc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcTabu(TabuStub<Sv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline Sv0Tabu const * Sv0Tabu::ptrc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcTabu(TabuStub<Sv0Tabu>::TabuTyp));
	CatchError
}



closeKangarooSpace



#endif // Sv0TabuHppIncluded
