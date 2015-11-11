/*!
	@file dv0tabu.hpp
	@brief The prototype file for Dv0Tabu class.
	@details This is the prototype file for Dv0Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see tabu.cpp
*/



#ifndef Dv0TabuHppIncluded
#define Dv0TabuHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/tabus/dvtabu.hpp"
#include "cbls/tabus/reg.hh"



openKangarooSpace



/*!
	@class Dv0Tabu
	@brief A class to represent double tabu variables with no callback.
	@details This class represents double tabu variables with no callback.
		The pairs must be in ascending order of variable handles.
*/
class Dv0Tabu : public DvTabu
{
	public:

		//! @name Access
		//! @{

		static Dv0Tabu & refm(Hdl const hdlSys);				//!< Reference.
		static Dv0Tabu * ptrm(Hdl const hdlSys);				//!< Pointer.
		static Dv0Tabu const & refc(Hdl const hdlSys);		//!< Reference.
		static Dv0Tabu const * ptrc(Hdl const hdlSys);		//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static Dv0Tabu const & cast(Tabu const & theTabu);	//!< Perform casting.
		static Dv0Tabu const * cast(Tabu const * theTabu);	//!< Perform casting.
		static Dv0Tabu & cast(Tabu & theTabu);				//!< Perform casting.
		static Dv0Tabu * cast(Tabu * theTabu);				//!< Perform casting.

		static Bll suit(Tabu const & theTabu);				//!< Suits casting?
		static Bll suit(Tabu const * theTabu);				//!< Suits casting?
		static Bll suit(Tabu & theTabu);					//!< Suits casting?
		static Bll suit(Tabu * theTabu);					//!< Suits casting?

		//! @}

	protected:

		~Dv0Tabu();											//!< Destructor.
		Dv0Tabu(Dv0Tabu const & that);						//!< Duplicator.
		Dv0Tabu(Hdl const hdlSys);							//!< Initialiser.
		Dv0Tabu const & operator = (Dv0Tabu const & that);	//!< Assigner.
};



/*!
	The constructor.
*/
inline Dv0Tabu::Dv0Tabu(Hdl const hdlSys) : DvTabu(hdlSys)
{
	WatchError
	setTabuTyp(TabuStub<Dv0Tabu>::TabuTyp);
	CatchError
}



/*!
	The destructor.
*/
inline Dv0Tabu::~Dv0Tabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Dv0Tabu::suit(Tabu const & theTabu)
{
	WatchError
	return theTabu.TabuTyp == TabuStub< Dv0Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Dv0Tabu::suit(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuTyp == TabuStub< Dv0Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Dv0Tabu::suit(Tabu & theTabu)
{
	WatchError
	return theTabu.TabuTyp == TabuStub< Dv0Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Dv0Tabu::suit(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuTyp == TabuStub< Dv0Tabu >::TabuTyp;
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Dv0Tabu const & Dv0Tabu::cast(Tabu const & theTabu)
{
	WatchError
	Warn(theTabu.TabuTyp != TabuStub< Dv0Tabu >::TabuTyp, eWrongTyp);
	return scast<Dv0Tabu const &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Dv0Tabu const * Dv0Tabu::cast(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuTyp != TabuStub< Dv0Tabu >::TabuTyp, eWrongTyp);

	return scast<Dv0Tabu const *>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Dv0Tabu & Dv0Tabu::cast(Tabu & theTabu)
{
	WatchError
	Warn(theTabu.TabuTyp != TabuStub< Dv0Tabu >::TabuTyp, eWrongTyp);

	return scast<Dv0Tabu &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Dv0Tabu * Dv0Tabu::cast(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuTyp != TabuStub< Dv0Tabu >::TabuTyp, eWrongTyp);

	return scast<Dv0Tabu *>(theTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
inline Dv0Tabu & Dv0Tabu::refm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmTabu(TabuStub<Dv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline Dv0Tabu * Dv0Tabu::ptrm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmTabu(TabuStub<Dv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Refer to a tabu.
*/
inline Dv0Tabu const & Dv0Tabu::refc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcTabu(TabuStub<Dv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline Dv0Tabu const * Dv0Tabu::ptrc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcTabu(TabuStub<Dv0Tabu>::TabuTyp));
	CatchError
}



closeKangarooSpace



#endif // Dv0TabuHppIncluded
