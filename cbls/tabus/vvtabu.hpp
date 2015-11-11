/*!
	@file vvtabu.hpp
	@brief The prototype file for VvTabu class.
	@details This is the prototype file for VvTabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see tabu.cpp
*/



#ifndef VvTabuHppIncluded
#define VvTabuHppIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace


dec tabuctn(VvTabu, 3);		//	Single variable value tabu.

/*This class has to be finalised. */


/*!
	@class VvTabu
	@brief A class to represent single variable value tabu.
	@details This class represents single variable value tabu.
*/
class VvTabu : public Tabu
{
	public:

		//! @name Access
		//! @{

		static VvTabu & refm(Hdl const hdlSys, Typ const typTabu);			//!< Reference.
		static VvTabu * ptrm(Hdl const hdlSys, Typ const typTabu);			//!< Pointer.
		static VvTabu const & refc(Hdl const hdlSys, Typ const typTabu);	//!< Reference.
		static VvTabu const * ptrc(Hdl const hdlSys, Typ const typTabu);	//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static VvTabu const & cast(Tabu const & theTabu);	//!< Perform casting.
		static VvTabu const * cast(Tabu const * theTabu);	//!< Perform casting.
		static VvTabu & cast(Tabu & theTabu);				//!< Perform casting.
		static VvTabu * cast(Tabu * theTabu);				//!< Perform casting.

		static Bll suit(Tabu const & theTabu);				//!< Suits casting?
		static Bll suit(Tabu const * theTabu);				//!< Suits casting?
		static Bll suit(Tabu & theTabu);					//!< Suits casting?
		static Bll suit(Tabu * theTabu);					//!< Suits casting?

		//! @}

		Bll state(Hdl const hdlVar) const;					//!< Get the state.

	protected:

		~VvTabu();											//!< Destructor.
		VvTabu(VvTabu const & that);						//!< Duplicator.
		VvTabu(Hdl const hdlSys);							//!< Initialiser.
		VvTabu const & operator = (VvTabu const & that);	//!< Assigner.

		void adjustMemAuto();			//!< Adjust memory automatically.
		void setupComputation();		//!< Setup for computation.

		Bll setTabuState(Hdl const hdlVar);		//!< Set tabu state.
		Bll unsetTabuState(Hdl const hdlVar);	//!< Unset tabu state.

		#if VarStateArray
		b1<Dim,xmm> mStates;			//!< Count/state of the vars.
		#else
		hmd<Hdl, Dim, xmmh> mStates;	//!< Count/state of the vars.
		#endif
};




/*!
	The constructor.
*/
inline VvTabu::VvTabu(Hdl const hdlSys) : Tabu(hdlSys)
{
	WatchError
	setTabuCat(TabuStub<VvTabu>::TabuCat);
	CatchError
}



/*!
	The destructor.
*/
inline VvTabu::~VvTabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Set tabu state.
*/
inline Bll VvTabu::setTabuState(Hdl const hdlVar)
{
	WatchError
	#if VarStateArray
	return (++mStates[hdlVar] == 1);
	#else
	Itr sItr = mStates.insertItrMem(hdlVar, 0);
	return (++mStates.item(sItr) == 1);
	#endif
	CatchError
}


/*!
	Unset tabu state.
*/
inline Bll VvTabu::unsetTabuState(Hdl const hdlVar)
{
	WatchError
	#if VarStateArray
	Warn(!mStates[hdlVar], eTabuInconsistent);
	return (--mStates[hdlVar] == 0);
	#else
	Itr sItr = mStates.findItr(hdlVar);
	Warn(!mStates.item(sItr), eTabuInconsistent);
	if (--mStates.item(sItr))
		return false;
	mStates.removeWithItr(sItr);
	return true;
	#endif
	CatchError
}


/*!
	Return the tabu state of a variable.
*/
inline Bll VvTabu::state(Hdl const hdlVar) const
{
	WatchError
	#if VarStateArray
	return mStates[hdlVar];
	#else
	return mStates.findBll(hdlVar);
	#endif
	CatchError
}



/*!
	Adjust dynamic memory
*/
inline void VvTabu::adjustMemAuto()
{
	WatchError
	mStates.adjustMemAuto();
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll VvTabu::suit(Tabu const & theTabu)
{
	WatchError
	return theTabu.TabuCat == TabuStub< VvTabu >::TabuCat;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll VvTabu::suit(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCat == TabuStub< VvTabu >::TabuCat;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll VvTabu::suit(Tabu & theTabu)
{
	WatchError
	return theTabu.TabuCat == TabuStub< VvTabu >::TabuCat;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll VvTabu::suit(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCat == TabuStub< VvTabu >::TabuCat;
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline VvTabu const & VvTabu::cast(Tabu const & theTabu)
{
	WatchError
	Warn(theTabu.TabuCat != TabuStub< VvTabu >::TabuCat, eWrongCat);
	return scast<VvTabu const &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline VvTabu const * VvTabu::cast(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCat != TabuStub< VvTabu >::TabuCat, eWrongCat);

	return scast<VvTabu const *>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline VvTabu & VvTabu::cast(Tabu & theTabu)
{
	WatchError
	Warn(theTabu.TabuCat != TabuStub< VvTabu >::TabuCat, eWrongCat);

	return scast<VvTabu &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline VvTabu * VvTabu::cast(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCat != TabuStub< VvTabu >::TabuCat, eWrongCat);

	return scast<VvTabu *>(theTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
inline VvTabu & VvTabu::refm(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmTabu(typTabu));
	CatchError
}



/*!
	Point to a tabu.
*/
inline VvTabu * VvTabu::ptrm(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmTabu(typTabu));
	CatchError
}



/*!
	Refer to a tabu.
*/
inline VvTabu const & VvTabu::refc(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcTabu(typTabu));
	CatchError
}



/*!
	Point to a tabu.
*/
inline VvTabu const * VvTabu::ptrc(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcTabu(typTabu));
	CatchError
}



closeKangarooSpace



#endif // VvTabuHppIncluded
