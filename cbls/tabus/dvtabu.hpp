/*!
	@file dvtabu.hpp
	@brief The prototype file for DvTabu class.
	@details This is the prototype file for DvTabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see tabu.cpp
*/



#ifndef DvTabuHppIncluded
#define DvTabuHppIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace


dec tabuctn(DvTabu, 2);		//	Double variable tabu.


/*!
	@class DvTabu
	@brief A class to represent double tabu variables.
	@details This class represents double tabu variables.
		The pairs must be in ascending order of variable handles.
*/
class DvTabu : public Tabu
{
	public:

		//! @name Access
		//! @{

		static DvTabu & refm(Hdl const hdlSys, Typ const typTabu);			//!< Reference.
		static DvTabu * ptrm(Hdl const hdlSys, Typ const typTabu);			//!< Pointer.
		static DvTabu const & refc(Hdl const hdlSys, Typ const typTabu);	//!< Reference.
		static DvTabu const * ptrc(Hdl const hdlSys, Typ const typTabu);	//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static DvTabu const & cast(Tabu const & theTabu);	//!< Perform casting.
		static DvTabu const * cast(Tabu const * theTabu);	//!< Perform casting.
		static DvTabu & cast(Tabu & theTabu);				//!< Perform casting.
		static DvTabu * cast(Tabu * theTabu);				//!< Perform casting.

		static Bll suit(Tabu const & theTabu);				//!< Suits casting?
		static Bll suit(Tabu const * theTabu);				//!< Suits casting?
		static Bll suit(Tabu & theTabu);					//!< Suits casting?
		static Bll suit(Tabu * theTabu);					//!< Suits casting?

		//! @}

		Bll state(Hdl const hdlVar1, Hdl const hdlVar2) const;	//!< Get the states.

	protected:

		/*!
			@class twinhash
			@brief A class to represent hash of handle binary tuples
			@details This class represents hash of handle binary tuples.
		*/
		class twinhash
		{
			public:
				static Hvl iof(t2<Hdl,Hdl> const & theTwin);	//!< Calculate hash value.
		};

		/*!
			@class twinequal
			@brief A class to represent equality of handle binary tuples
			@details This class represents equality of handle binary tuples.
		*/
		class twinequal
		{
			public:
				static Bll iof(t2<Hdl,Hdl> const & Left, t2<Hdl,Hdl> const & Right);	//!< Equal operator.
		};

		static t2<Hdl,Hdl> convVarHdls(Hdl const hdlVar1, Hdl const hdlVar2);	//!< Convert variable handles to respect ordering.
		#if VarStateArray
		static Hdl convVarHdl2(t2<Hdl,Hdl> const & theTwin);					//!< Covert second variable handle for array access.
		#endif

		~DvTabu();											//!< Destructor.
		DvTabu(DvTabu const & that);						//!< Duplicator.
		DvTabu(Hdl const hdlSys);							//!< Initialiser.
		DvTabu const & operator = (DvTabu const & that);	//!< Assigner.

		void adjustMemAuto();								//!< Adjust memory automatically.
		void setupComputation();							//!< Setup for computation.

		Bll setTabuState(t2<Hdl,Hdl> const & hdlTwin);					//!< Set tabu state.
		Bll unsetTabuState(t2<Hdl,Hdl> const & hdlTwin);				//!< Unset tabu state.
		Bll setTabuState(Hdl const hdlVar1, Hdl const hdlVar2);			//!< Set tabu state.
		Bll unsetTabuState(Hdl const hdlVar1, Hdl const hdlVar2);		//!< Unset tabu state.

		#if VarStateArray
		rl<b1<Dim,kmm>,xmm> mStates;									//!< Count/status of the vars.
		#else
		hmd<t2<Hdl,Hdl>, Dim, xmmh, twinhash, twinequal> mStates;		//!< Count/status of the vars.
		#endif
};




/*!
	The constructor.
*/
inline DvTabu::DvTabu(Hdl const hdlSys) : Tabu(hdlSys)
{
	WatchError
	setTabuCat(TabuStub<DvTabu>::TabuCat);
	CatchError
}



/*!
	The destructor.
*/
inline DvTabu::~DvTabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Convert the var handles to respect ascending ordering.
*/
inline t2<Hdl,Hdl> DvTabu::convVarHdls(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	Warn(hdlVar1 == hdlVar2, eVarsNotDifferent);
	if (hdlVar1 < hdlVar2)
		return t2<Hdl,Hdl>(hdlVar1,hdlVar2);
	else
		return t2<Hdl,Hdl>(hdlVar2,hdlVar1);
	CatchError
}



#if VarStateArray
/*!
	Convert the second handle for array access.
*/
inline Hdl DvTabu::convVarHdl2(t2<Hdl,Hdl> const & theTwin)
{
	WatchError
	Warn(theTwin.First >= theTwin.Second, eNotVarPairAscend);
	return theTwin.Second - theTwin.First - 1;
	CatchError
}
#endif



/*!
	Return the States of all the tabu variables.
*/
inline Bll DvTabu::state(Hdl const hdlVar1, Hdl const hdlVar2) const
{
	WatchError
	t2<Hdl,Hdl> tTwin = convVarHdls(hdlVar1, hdlVar2);
	#if VarStateArray
	return mStates[tTwin.First][convVarHdl2(tTwin)];
	#else
	return mStates.findBll(tTwin);
	#endif
	CatchError
}



/*!
	Set tabu state.
*/
inline Bll DvTabu::setTabuState(t2<Hdl,Hdl> const & hdlTwin)
{
	WatchError
	#if VarStateArray
	return (++mStates[hdlTwin.First][convVarHdl2(hdlTwin)] == 1);
	#else
	Itr sItr = mStates.insertItrMem(hdlTwin, 0);
	return (++mStates.item(sItr) == 1);
	#endif
	CatchError
}



/*!
	Set tabu state.
*/
inline Bll DvTabu::setTabuState(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	t2<Hdl,Hdl> tTwin = convVarHdls(hdlVar1, hdlVar2);
	#if VarStateArray
	return (++mStates[tTwin.First][convVarHdl2(tTwin)] == 1);
	#else
	Itr sItr = mStates.insertItrMem(tTwin, 0);
	return (++mStates.item(sItr) == 1);
	#endif
	CatchError
}



/*!
	Unset tabu state.
*/
inline Bll DvTabu::unsetTabuState(t2<Hdl,Hdl> const & hdlTwin)
{
	WatchError
	#if VarStateArray
	Warn(!mStates[hdlTwin.First][convVarHdl2(hdlTwin)], eTabuInconsistent);
	return (--mStates[hdlTwin.First][convVarHdl2(hdlTwin)] == 0);
	#else
	Itr sItr = mStates.findItr(hdlTwin);
	Warn(!mStates.item(sItr), eTabuInconsistent);
	if (--mStates.item(sItr))
		return false;
	mStates.removeWithItr(sItr);
	return true;
	#endif
	CatchError
}




/*!
	Unset tabu state.
*/
inline Bll DvTabu::unsetTabuState(Hdl const hdlVar1, Hdl const hdlVar2)
{
	WatchError
	t2<Hdl,Hdl> tTwin = convVarHdls(hdlVar1, hdlVar2);
	#if VarStateArray
	Warn(!mStates[tTwin.First][convVarHdl2(tTwin)], eTabuInconsistent);
	return (--mStates[tTwin.First][convVarHdl2(tTwin)] == 0);
	#else
	Itr sItr = mStates.findItr(tTwin);
	Warn(!mStates.item(sItr), eTabuInconsistent);
	if (--mStates.item(sItr))
		return false;
	mStates.removeWithItr(sItr);
	return true;
	#endif
	CatchError
}



/*!
	Adjust dynamic memory
*/
inline void DvTabu::adjustMemAuto()
{
	WatchError
	mStates.adjustMemAuto();
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll DvTabu::suit(Tabu const & theTabu)
{
	WatchError
	return theTabu.TabuCat == TabuStub< DvTabu >::TabuCat;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll DvTabu::suit(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCat == TabuStub< DvTabu >::TabuCat;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll DvTabu::suit(Tabu & theTabu)
{
	WatchError
	return theTabu.TabuCat == TabuStub< DvTabu >::TabuCat;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll DvTabu::suit(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCat == TabuStub< DvTabu >::TabuCat;
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline DvTabu const & DvTabu::cast(Tabu const & theTabu)
{
	WatchError
	Warn(theTabu.TabuCat != TabuStub< DvTabu >::TabuCat, eWrongCat);
	return scast<DvTabu const &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline DvTabu const * DvTabu::cast(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCat != TabuStub< DvTabu >::TabuCat, eWrongCat);

	return scast<DvTabu const *>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline DvTabu & DvTabu::cast(Tabu & theTabu)
{
	WatchError
	Warn(theTabu.TabuCat != TabuStub< DvTabu >::TabuCat, eWrongCat);

	return scast<DvTabu &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline DvTabu * DvTabu::cast(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCat != TabuStub< DvTabu >::TabuCat, eWrongCat);

	return scast<DvTabu *>(theTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
inline DvTabu & DvTabu::refm(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmTabu(typTabu));
	CatchError
}



/*!
	Point to a tabu.
*/
inline DvTabu * DvTabu::ptrm(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmTabu(typTabu));
	CatchError
}



/*!
	Refer to a tabu.
*/
inline DvTabu const & DvTabu::refc(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcTabu(typTabu));
	CatchError
}



/*!
	Point to a tabu.
*/
inline DvTabu const * DvTabu::ptrc(Hdl const hdlSys, Typ const typTabu)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcTabu(typTabu));
	CatchError
}



closeKangarooSpace



#endif // DvTabuHppIncluded
