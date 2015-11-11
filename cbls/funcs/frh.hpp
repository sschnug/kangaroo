/*!
	@file frh.hpp
	@brief The prototype file for FrH class.
	@details This is the prototype file for FrH class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see frh.cpp
	@see term.hpp
*/



#ifndef FrHHppIncluded
#define FrHHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/funcs/reg.hh"


openKangarooSpace


/*!
	@class FrH
	@brief A class to represent hint ranking functions.
	@details This class represents hint ranking functions.
*/
class FrH : public Func
{
	public:

		static FrH & refm(Hdl const hdlSys, Hdl const hdlFunc);				//!< Reference.
		static FrH * ptrm(Hdl const hdlSys, Hdl const hdlFunc);				//!< Pointer.
		static FrH const & refc(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static FrH const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.

		//! @name Casting
		//! @{

		static Bll suit(Term const & theTerm);			//!< Suits casting?
		static Bll suit(Term const * theTerm);			//!< Suits casting?
		static Bll suit(Term & theTerm);				//!< Suits casting?
		static Bll suit(Term * theTerm);				//!< Suits casting?

		static FrH const & cast(Term const & theTerm);	//!< Perform casting.
		static FrH const * cast(Term const * theTerm);	//!< Perform casting.
		static FrH & cast(Term & theTerm);				//!< Perform casting.
		static FrH * cast(Term * theTerm);				//!< Perform casting.

		//! @}

		//! @name Ranks
		//! @{

		virtual Sqn beginRank() const = 0;					//!< Get the begin var.
		virtual Sqn endRank() const = 0;					//!< Get the end var.
		virtual Dim rankCount() const = 0;					//!< Get the rank var count.
		virtual Sqn moveRank(Sqn const theSqn) const = 0;	//!< Get the next var.
		virtual Sqn findRank(Idx const theIdx) const = 0;	//!< Get the indexed rank.
		virtual Sqn randRank(Rnd & theRand) const = 0;		//!< Get a random rank.

		//! @}

	protected:

		FrH(Hdl const hdlSys, Dim const PrmCount);		//!< Constructor.
		FrH const & operator = (FrH const & theFrH);	//!< Assigner.
		FrH(FrH const & theFrH);						//!< Duplicator.
		virtual ~FrH();									//!< Destructor.

		//! @name Simulations
		//! @{

		virtual void simulAnew();					//!< Compute in anew simulation mode.
		virtual void simulIncr();					//!< Compute in incr simulation mode.
		#if CompLazy
		virtual void emulBklg();					//!< Compute in bklg emulation mode.
		#endif

		//! @}

		#if ExecUpwdLazy
		void runPostExecAnew();						//!< Run post exection in anew mode.
		void runPostExecIncr();						//!< Run post execuiton in incr mode.
		#endif
		#if CompLazy
		void runPostExecBklg();						//!< Run post execution in bklg mode.
		#endif

		#if CompLazy
		rl< ll<Sqn,kmm>,nmm > * mHintUndonePrms;	//!< The unhinted params; allocated by derivatives.
		void setupHintUndoPrms();					//!< Set up unhinted parameters.

		virtual void setupUndoPrms();				//!< Set up parameters for undo.
		virtual void setupUndoArgs();				//!< Set up arguments for undo.
		virtual void undoEval(Pos const thePos);	//!< Perform eval undo for the param.
		void reinitHintUndoPrms();					//!< Call parameters to list for eval undo.
		void reiterHintUndoPrms();					//!< Call parameters to relist for eval undo.
		#endif	//CompLazy
		#if CompLazyHalf
		virtual void notifyDeferedPrms();			//!< Notify deferment to the parameters.
		virtual void notifyEnforcedPrms();			//!< Notify enforcement to the parameters.
		#endif
		virtual Lnk setArg(Arg const & theArg);		//!< Set an argument in the term.
};



/*!
	Whether a term is suitable for casting.
*/
inline Bll FrH::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FrH>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FrH::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FrH>::TermCat;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
inline Bll FrH::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FrH>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FrH::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FrH>::TermCat;
	CatchError
}


/*!
	Perform casting of a term.
*/
inline FrH const & FrH::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FrH>::TermCat, eWrongCat);

	return scast<FrH const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FrH const * FrH::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FrH>::TermCat, eWrongCat);

	return scast<FrH const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FrH & FrH::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FrH>::TermCat, eWrongCat);

	return scast<FrH &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FrH * FrH::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FrH>::TermCat, eWrongCat);

	return scast<FrH *>(theTerm);
	CatchError
}



/*!
	Refer to the frh.
*/
inline FrH & FrH::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to the frh.
*/
inline FrH * FrH::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}



/*!
	Refer to the frh.
*/
inline FrH const & FrH::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to the frh.
*/
inline FrH const * FrH::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The constructor.
*/
inline FrH::FrH(Hdl const hdlSys, Dim const PrmCount) :
		Func(hdlSys, PrmCount)
		#if CompLazy
		, mHintUndonePrms(Null)
		#endif
{
	WatchError
	setTermCat(TermStub<FrH>::TermCat);
	CatchError
}



/*!
	The destructor.
*/
inline FrH::~FrH()
{
	WatchError
	#if CompLazy
	if (mHintUndonePrms)
		delete mHintUndonePrms;
	#endif
	CatchError
}



#if ExecUpwdLazy
/*!
	Run post exection process in anew mode.
*/
inline void FrH::runPostExecAnew()
{
	WatchError
	#if ExecUpwd
	this->clearExecChgdPrms();
	#endif//ExecUpwd

	#if ExecLazy
	this->reinitHintUndoPrms();
	#endif//ExecLazy
	CatchError
}
#endif //ExecUpwdLazy


#if ExecUpwdLazy
/*!
	Run post execution process in incr mode.
*/
inline void FrH::runPostExecIncr()
{
	WatchError
	#if ExecUpwd
	this->clearExecChgdPrms();
	#endif//ExecUpwd

	#if ExecLazy
	this->reiterHintUndoPrms();
	#endif//ExecLazy
	CatchError
}
#endif //ExecUpwdLazy


#if CompLazy
/*!
	Run post execution process in backlog mode.
*/
inline void FrH::runPostExecBklg()
{
	WatchError
	this->reiterHintUndoPrms();
	CatchError
}
#endif



closeKangarooSpace


#endif //FrHHppIncluded
