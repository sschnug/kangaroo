/*!
	@file sv2tabu.hpp
	@brief The prototype file for Sv2Tabu class.
	@details This is the prototype file for Sv2Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see tabu.cpp
*/



#ifndef Sv2TabuHppIncluded
#define Sv2TabuHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/tabus/svtabu.hpp"
#include "cbls/tabus/reg.hh"



openKangarooSpace



/*!
	@class Sv2Tabu
	@brief A class to represent single tabu variables with call back for both tabu and untabu events.
	@details This class represents single tabu variables with call back for both tabu and untabu events.
*/
class Sv2Tabu : public SvTabu
{
	public:

		//! @name Access
		//! @{

		static Sv2Tabu & refm(Hdl const hdlSys);			//!< Reference.
		static Sv2Tabu * ptrm(Hdl const hdlSys);			//!< Pointer.
		static Sv2Tabu const & refc(Hdl const hdlSys);		//!< Reference.
		static Sv2Tabu const * ptrc(Hdl const hdlSys);		//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static Sv2Tabu const & cast(Tabu const & theTabu);	//!< Perform casting.
		static Sv2Tabu const * cast(Tabu const * theTabu);	//!< Perform casting.
		static Sv2Tabu & cast(Tabu & theTabu);				//!< Perform casting.
		static Sv2Tabu * cast(Tabu * theTabu);				//!< Perform casting.

		static Bll suit(Tabu const & theTabu);				//!< Suits casting?
		static Bll suit(Tabu const * theTabu);				//!< Suits casting?
		static Bll suit(Tabu & theTabu);					//!< Suits casting?
		static Bll suit(Tabu * theTabu);					//!< Suits casting?

		//! @}

		b1<Hdl,xmm> const & Updates() const;				//!< Get the updated variables.

	protected:

		~Sv2Tabu();											//!< Destructor.
		Sv2Tabu(Sv2Tabu const & that);						//!< Duplicator.
		Sv2Tabu(Hdl const hdlSys);							//!< Initialiser.
		Sv2Tabu const & operator = (Sv2Tabu const & that);	//!< Assigner.

		void adjustMemAuto();				//!< Adjust memory automatically.
		void regCallback(Func * theFunc);	//!< Register a function.
		void callbackFuncs();				//!< Call back functions.

		b1<Func *,xmm> mFuncs;			//!< Funcs requiring updates.
		b1<Hdl,xmm> mUpdates;			//!< The vars with new status.
};




/*!
	The constructor.
*/
inline Sv2Tabu::Sv2Tabu(Hdl const hdlSys) : SvTabu(hdlSys)
{
	WatchError
	setTabuTyp(TabuStub<Sv2Tabu>::TabuTyp);
	setCallback(true);
	CatchError
}



/*!
	The destructor.
*/
inline Sv2Tabu::~Sv2Tabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Return the Updates variables.
*/
inline b1<Hdl,xmm> const & Sv2Tabu::Updates() const
{
	WatchError
	return mUpdates;
	CatchError
}



/*!
	Adjust dynamic memory
*/
inline void Sv2Tabu::adjustMemAuto()
{
	WatchError
	mFuncs.adjustMemAuto();
	mUpdates.adjustMemAuto();
	SvTabu::adjustMemAuto();
	CatchError
}



/*!
	Register a callback function.
*/
inline void Sv2Tabu::regCallback(Func * theFunc)
{
	WatchError
	mFuncs.insertMem(theFunc);
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Sv2Tabu::suit(Tabu const & theTabu)
{
	WatchError
	return theTabu.TabuTyp == TabuStub< Sv2Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Sv2Tabu::suit(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuTyp == TabuStub< Sv2Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Sv2Tabu::suit(Tabu & theTabu)
{
	WatchError
	return theTabu.TabuTyp == TabuStub< Sv2Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Sv2Tabu::suit(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuTyp == TabuStub< Sv2Tabu >::TabuTyp;
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Sv2Tabu const & Sv2Tabu::cast(Tabu const & theTabu)
{
	WatchError
	Warn(theTabu.TabuTyp != TabuStub< Sv2Tabu >::TabuTyp, eWrongTyp);
	return scast<Sv2Tabu const &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Sv2Tabu const * Sv2Tabu::cast(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuTyp != TabuStub< Sv2Tabu >::TabuTyp, eWrongTyp);

	return scast<Sv2Tabu const *>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Sv2Tabu & Sv2Tabu::cast(Tabu & theTabu)
{
	WatchError
	Warn(theTabu.TabuTyp != TabuStub< Sv2Tabu >::TabuTyp, eWrongTyp);

	return scast<Sv2Tabu &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Sv2Tabu * Sv2Tabu::cast(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuTyp != TabuStub< Sv2Tabu >::TabuTyp, eWrongTyp);

	return scast<Sv2Tabu *>(theTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
inline Sv2Tabu & Sv2Tabu::refm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmTabu(TabuStub<Sv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline Sv2Tabu * Sv2Tabu::ptrm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmTabu(TabuStub<Sv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Refer to a tabu.
*/
inline Sv2Tabu const & Sv2Tabu::refc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcTabu(TabuStub<Sv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline Sv2Tabu const * Sv2Tabu::ptrc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcTabu(TabuStub<Sv2Tabu>::TabuTyp));
	CatchError
}



closeKangarooSpace



#endif // Sv2TabuHppIncluded
