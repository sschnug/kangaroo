/*!
	@file dv2tabu.hpp
	@brief The prototype file for Dv2Tabu class.
	@details This is the prototype file for Dv2Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see tabu.cpp
*/



#ifndef Dv2TabuHppIncluded
#define Dv2TabuHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/tabus/dvtabu.hpp"
#include "cbls/tabus/reg.hh"



openKangarooSpace



/*!
	@class Dv2Tabu
	@brief A class to represent double tabu variables with callback for both tabu and untabu events.
	@details This class represents double tabu variables with callback for both tabu and untabu events.
		The pairs must be in ascending order of variable handles.
*/
class Dv2Tabu : public DvTabu
{
	public:

		//! @name Access
		//! @{

		static Dv2Tabu & refm(Hdl const hdlSys);				//!< Reference.
		static Dv2Tabu * ptrm(Hdl const hdlSys);				//!< Pointer.
		static Dv2Tabu const & refc(Hdl const hdlSys);		//!< Reference.
		static Dv2Tabu const * ptrc(Hdl const hdlSys);		//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static Dv2Tabu const & cast(Tabu const & theTabu);	//!< Perform casting.
		static Dv2Tabu const * cast(Tabu const * theTabu);	//!< Perform casting.
		static Dv2Tabu & cast(Tabu & theTabu);				//!< Perform casting.
		static Dv2Tabu * cast(Tabu * theTabu);				//!< Perform casting.

		static Bll suit(Tabu const & theTabu);				//!< Suits casting?
		static Bll suit(Tabu const * theTabu);				//!< Suits casting?
		static Bll suit(Tabu & theTabu);					//!< Suits casting?
		static Bll suit(Tabu * theTabu);					//!< Suits casting?

		//! @}

		b1<t2<Hdl,Hdl>,xmm> const & Updates() const;			//!< Get the updated variable pairs.

	protected:

		~Dv2Tabu();											//!< Destructor.
		Dv2Tabu(Dv2Tabu const & that);						//!< Duplicator.
		Dv2Tabu(Hdl const hdlSys);							//!< Initialiser.
		Dv2Tabu const & operator = (Dv2Tabu const & that);	//!< Assigner.

		void adjustMemAuto();								//!< Adjust memory automatically.
		void regCallback(Func * theFunc);					//!< Register a function.
		void callbackFuncs();								//!< Call back functions.

		b1<Func *,xmm> mFuncs;											//!< Funcs requiring updates.
		b1<t2<Hdl,Hdl>,xmm> mUpdates;									//!< The vars with new status.
};



/*!
	The constructor.
*/
inline Dv2Tabu::Dv2Tabu(Hdl const hdlSys) : DvTabu(hdlSys)
{
	WatchError
	setTabuTyp(TabuStub<Dv2Tabu>::TabuTyp);
	setCallback(true);
	CatchError
}



/*!
	The destructor.
*/
inline Dv2Tabu::~Dv2Tabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Return the Updates variables.
*/
inline b1<t2<Hdl,Hdl>,xmm> const & Dv2Tabu::Updates() const
{
	WatchError
	return mUpdates;
	CatchError
}



/*!
	Register a callback function.
*/
inline void Dv2Tabu::regCallback(Func * theFunc)
{
	WatchError
	mFuncs.insertMem(theFunc);
	CatchError
}



/*!
	Adjust dynamic memory
*/
inline void Dv2Tabu::adjustMemAuto()
{
	WatchError
	mFuncs.adjustMemAuto();
	mUpdates.adjustMemAuto();
	DvTabu::adjustMemAuto();
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Dv2Tabu::suit(Tabu const & theTabu)
{
	WatchError
	return theTabu.TabuTyp == TabuStub< Dv2Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Dv2Tabu::suit(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuTyp == TabuStub< Dv2Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Dv2Tabu::suit(Tabu & theTabu)
{
	WatchError
	return theTabu.TabuTyp == TabuStub< Dv2Tabu >::TabuTyp;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll Dv2Tabu::suit(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuTyp == TabuStub< Dv2Tabu >::TabuTyp;
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Dv2Tabu const & Dv2Tabu::cast(Tabu const & theTabu)
{
	WatchError
	Warn(theTabu.TabuTyp != TabuStub< Dv2Tabu >::TabuTyp, eWrongTyp);
	return scast<Dv2Tabu const &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Dv2Tabu const * Dv2Tabu::cast(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuTyp != TabuStub< Dv2Tabu >::TabuTyp, eWrongTyp);

	return scast<Dv2Tabu const *>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Dv2Tabu & Dv2Tabu::cast(Tabu & theTabu)
{
	WatchError
	Warn(theTabu.TabuTyp != TabuStub< Dv2Tabu >::TabuTyp, eWrongTyp);

	return scast<Dv2Tabu &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline Dv2Tabu * Dv2Tabu::cast(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuTyp != TabuStub< Dv2Tabu >::TabuTyp, eWrongTyp);

	return scast<Dv2Tabu *>(theTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
inline Dv2Tabu & Dv2Tabu::refm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmTabu(TabuStub<Dv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline Dv2Tabu * Dv2Tabu::ptrm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmTabu(TabuStub<Dv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Refer to a tabu.
*/
inline Dv2Tabu const & Dv2Tabu::refc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcTabu(TabuStub<Dv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline Dv2Tabu const * Dv2Tabu::ptrc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcTabu(TabuStub<Dv2Tabu>::TabuTyp));
	CatchError
}



closeKangarooSpace



#endif // Dv2TabuHppIncluded
