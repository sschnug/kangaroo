/*!
	@file tabu.hpp
	@brief The prototype file for Tabu class.
	@details This is the prototype file for Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 23.1.2009 QRL NICTA www.nicta.com.au
	@see tabu.cpp
*/



#ifndef TabuHppIncluded
#define TabuHppIncluded



#include "cbls/frames/dat.hpp"
#include "cbls/frames/pbs.tcc"



openKangarooSpace



/*
	Forward declarations.
*/
class Sys;
class Func;


/*!
	@class Tabu
	@brief A class to represent tabu files.
	@details This class represents tabu files.
		Tube type determines the number of variables in the tuple,
		such as single, double, triple, etc.
*/
class Tabu
{
	public:

		Cat const TabuCat;								//!< Tabu category.
		Typ const TabuTyp;								//!< Tabu type.
		Cls const TabuCls;								//!< Tabu class.

		Bll const Callback;								//!< Supports callback.

		Bll automatic() const;							//!< Tabu automatically?
		Bll active() const;								//!< Tabu active?

		void setAutomatic(Bll const SetNotUnset);		//!< Set automatic tabu.

		//! @name Accesss
		//! @{

		static Tabu & refm(Hdl const hdlSys, Typ const typTabu);		//!< Reference.
		static Tabu * ptrm(Hdl const hdlSys, Typ const typTabu);		//!< Pointer.
		static Tabu const & refc(Hdl const hdlSys, Typ const typTabu);	//!< Reference.
		static Tabu const * ptrc(Hdl const hdlSys, Typ const typTabu);	//!< Pointer.

		//! @}

	protected:

		friend class Sys;
		friend class pbs<Tabu>;

		virtual ~Tabu();								//!< Destructor.
		Tabu(Tabu const & that);						//!< Duplicator.
		Tabu(Hdl const hdlSys);							//!< Constructor.
		Tabu const & operator = (Tabu const & that);	//!< Assigner.

		void setTabuCat(Cat const theTabuCat);			//!< Set tabu category.
		void setTabuTyp(Typ const theTabuTyp);			//!< Set tabu type.
		void setTabuCls(Cls const theTabuCls);			//!< Set tabu class.
		void setCallback(Bll const SetNotUnset);		//!< Set callback support.

		Bll defSysTabu();								//!< Define in the sys.
		virtual void syncExecClk();						//!< Synchronise execution clock.
		virtual void callbackFuncs();					//!< Callback functions.
		virtual void regCallback(Func * theFunc);		//!< Register a function.
		virtual void updtTabuAuto() = 0;				//!< Update tabu automatically.
		virtual void adjustMemAuto() = 0;				//!< Adjust memory automatically.
		virtual void setupComputation() = 0;			//!< Setup for computation.

		static void callbackFunc(Func * theFunc);		//!< Call back a function.

	protected:

		Sys & mTabuSys;									//!< The sys.
		Bll mAutomatic;									//!< Tabu automatic.
		Bll mActive;									//!< Tabu active.
};



/*!
	Set callback support.
*/
inline void Tabu::setCallback(Bll const SetNotUnset)
{
	WatchError
	ccast<Bll &>(Callback) = SetNotUnset;
	CatchError
}



/*!
	Set tabu automatically.
*/
inline void Tabu::setAutomatic(Bll const SetNotUnset)
{
	WatchError
	mAutomatic = SetNotUnset;
	CatchError
}



/*!
	Set tabu class.
*/
inline void Tabu::setTabuCls(Cls const theTabuCls)
{
	WatchError
	ccast<Cls &>(TabuCls) = theTabuCls;
	CatchError
}



/*!
	Set tabu category.
*/
inline void Tabu::setTabuCat(Cat const theTabuCat)
{
	WatchError
	ccast<Cat &>(TabuCat) = theTabuCat;
	CatchError
}



/*!
	Set tabu type.
*/
inline void Tabu::setTabuTyp(Typ const theTabuTyp)
{
	WatchError
	ccast<Typ &>(TabuTyp) = theTabuTyp;
	CatchError
}



/*!
	Return whether automatic?
*/
inline Bll Tabu::automatic() const
{
	WatchError
	return mAutomatic;
	CatchError
}



/*!
	Return whether active?
*/
inline Bll Tabu::active() const
{
	WatchError
	return mActive;
	CatchError
}


closeKangarooSpace



#endif // TabuHppIncluded

