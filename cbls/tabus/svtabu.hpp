/*!
	@file svtabu.hpp
	@brief The prototype file for SvTabu class.
	@details This is the prototype file for SvTabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see tabu.cpp
*/



#ifndef SvTabuHppIncluded
#define SvTabuHppIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace


dec tabuctn(SvTabu, 1);		//	Single variable tabu.


/*!
	@class SvTabu
	@brief A class to represent single variable tabu.
	@details This class represents single variable tabu.
*/
class SvTabu : public Tabu
{
	public:

		//! @name Access
		//! @{

		static SvTabu & refm(Hdl const hdlSys, Typ const typTabu);			//!< Reference.
		static SvTabu * ptrm(Hdl const hdlSys, Typ const typTabu);			//!< Pointer.
		static SvTabu const & refc(Hdl const hdlSys, Typ const typTabu);	//!< Reference.
		static SvTabu const * ptrc(Hdl const hdlSys, Typ const typTabu);	//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static SvTabu const & cast(Tabu const & theTabu);	//!< Perform casting.
		static SvTabu const * cast(Tabu const * theTabu);	//!< Perform casting.
		static SvTabu & cast(Tabu & theTabu);				//!< Perform casting.
		static SvTabu * cast(Tabu * theTabu);				//!< Perform casting.

		static Bll suit(Tabu const & theTabu);				//!< Suits casting?
		static Bll suit(Tabu const * theTabu);				//!< Suits casting?
		static Bll suit(Tabu & theTabu);					//!< Suits casting?
		static Bll suit(Tabu * theTabu);					//!< Suits casting?

		//! @}

		Bll state(Hdl const hdlVar) const;					//!< Get the state.

	protected:

		~SvTabu();											//!< Destructor.
		SvTabu(SvTabu const & that);						//!< Duplicator.
		SvTabu(Hdl const hdlSys);							//!< Initialiser.
		SvTabu const & operator = (SvTabu const & that);	//!< Assigner.

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
inline SvTabu::SvTabu(Hdl const hdlSys) : Tabu(hdlSys)
{
	WatchError
	setTabuCat(TabuStub<SvTabu>::TabuCat);
	CatchError
}



/*!
	The destructor.
*/
inline SvTabu::~SvTabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Set tabu state.
*/
inline Bll SvTabu::setTabuState(Hdl const hdlVar)
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
inline Bll SvTabu::unsetTabuState(Hdl const hdlVar)
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
inline Bll SvTabu::state(Hdl const hdlVar) const
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
inline void SvTabu::adjustMemAuto()
{
	WatchError
	mStates.adjustMemAuto();
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll SvTabu::suit(Tabu const & theTabu)
{
	WatchError
	return theTabu.TabuCat == TabuStub< SvTabu >::TabuCat;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll SvTabu::suit(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCat == TabuStub< SvTabu >::TabuCat;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll SvTabu::suit(Tabu & theTabu)
{
	WatchError
	return theTabu.TabuCat == TabuStub< SvTabu >::TabuCat;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll SvTabu::suit(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCat == TabuStub< SvTabu >::TabuCat;
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline SvTabu const & SvTabu::cast(Tabu const & theTabu)
{
	WatchError
	Warn(theTabu.TabuCat != TabuStub< SvTabu >::TabuCat, eWrongCat);
	return scast<SvTabu const &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline SvTabu const * SvTabu::cast(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCat != TabuStub< SvTabu >::TabuCat, eWrongCat);

	return scast<SvTabu const *>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline SvTabu & SvTabu::cast(Tabu & theTabu)
{
	WatchError
	Warn(theTabu.TabuCat != TabuStub< SvTabu >::TabuCat, eWrongCat);

	return scast<SvTabu &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline SvTabu * SvTabu::cast(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCat != TabuStub< SvTabu >::TabuCat, eWrongCat);

	return scast<SvTabu *>(theTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
inline SvTabu & SvTabu::refm(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmTabu(typTabu));
	CatchError
}



/*!
	Point to a tabu.
*/
inline SvTabu * SvTabu::ptrm(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmTabu(typTabu));
	CatchError
}



/*!
	Refer to a tabu.
*/
inline SvTabu const & SvTabu::refc(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcTabu(typTabu));
	CatchError
}



/*!
	Point to a tabu.
*/
inline SvTabu const * SvTabu::ptrc(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcTabu(typTabu));
	CatchError
}



closeKangarooSpace



#endif // SvTabuHppIncluded
