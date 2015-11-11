/*!
	@file frr.hpp
	@brief The prototype file for FrR class.
	@details This is the prototype file for FrR class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see frr.cpp
	@see term.hpp
*/



#ifndef FrRHppIncluded
#define FrRHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/funcs/reg.hh"



openKangarooSpace



/*!
	@class FrR
	@brief A class to represent ranking functions based on ratings.
	@details This class represents ranking functions based on ratings.
*/
class FrR : public Func
{
	public:

		static FrR & refm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Reference.
		static FrR * ptrm(Hdl const hdlSys, Hdl const hdlFunc);			//!< Pointer.
		static FrR const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static FrR const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//! @{

		static FrR const & cast(Term const & theTerm);	//!< Perfom casting.
		static FrR const * cast(Term const * theTerm);	//!< Perfom casting.
		static FrR & cast(Term & theTerm);				//!< Perfom casting.
		static FrR * cast(Term * theTerm);				//!< Perfom casting.

		static Bll suit(Term const & theTerm);			//!< Suits casting?
		static Bll suit(Term const * theTerm);			//!< Suits casting?
		static Bll suit(Term & theTerm);				//!< Suits casting?
		static Bll suit(Term * theTerm);				//!< Suits casting?

		//! @}
		//! @name Ranks
		//! @{

		virtual Hdl findHdl(Pos const thePos) const = 0;	//!< Get the handle for the pos.
		virtual Pos beginRank() const = 0;					//!< Get the begin pos.
		virtual Pos endRank() const = 0;					//!< Get the end pos.
		virtual Dim rankCount() const = 0;					//!< Get the rank var pos.
		virtual Pos moveRank(Pos const thePos) const = 0;	//!< Get the next pos.
		virtual Pos findRank(Idx const theIdx) const = 0;	//!< Get the indexed pos.
		virtual Pos randRank(Rnd & theRand) const = 0;		//!< Get a random pos.

		//! @}

	protected:

		FrR(Hdl const hdlSys, Dim const PrmCount);		//!< Constructor.
		FrR const & operator = (FrR const & that);		//!< Assigner.
		FrR(FrR const & that);							//!< Duplicator.
		virtual ~FrR();									//!< Destructor.

		//! @name Simulations
		//! @{

		virtual void simulAnew();					//!< Compute in anew simulation mode.
		virtual void simulIncr();					//!< Compute in incr simulation mode.
		#if CompLazy
		virtual void emulBklg();					//!< Compute in bklg emulation mode.
		#endif

		#if ExecUpwdLazy
		void runPostExecAnew();						//!< Run post exection in anew mode.
		void runPostExecIncr();						//!< Run post execuiton in incr mode.
		#endif
		#if CompLazy
		void runPostExecBklg();						//!< Run post execution in bklg mode.
		#endif

		//! @}

		#if CompLazy
		virtual void setupUndoPrms();				//!< Set up parameters for undo.
		virtual void setupUndoArgs();				//!< Set up arguments for undo.
		virtual void undoHint(Pos const thePos);	//!< Perform hint undo for the param.

		void reinitEvalUndoPrms();					//!< Call parameters to list for eval undo.
		void reiterEvalUndoPrms();					//!< Call parameters to relist for eval undo.
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
inline Bll FrR::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FrR>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FrR::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FrR>::TermCat;
	CatchError
}


/*!
	Whether a term is suitable for casting.
*/
inline Bll FrR::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermCat == TermStub<FrR>::TermCat;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll FrR::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermCat == TermStub<FrR>::TermCat;
	CatchError
}


/*!
	Perform casting of a term.
*/
inline FrR const & FrR::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FrR>::TermCat, eWrongCat);

	return scast<FrR const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FrR const * FrR::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FrR>::TermCat, eWrongCat);

	return scast<FrR const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FrR & FrR::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermCat != TermStub<FrR>::TermCat, eWrongCat);

	return scast<FrR &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline FrR * FrR::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermCat != TermStub<FrR>::TermCat, eWrongCat);

	return scast<FrR *>(theTerm);
	CatchError
}



/*!
	Refer to a frr term.
*/
inline FrR & FrR::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmFunc(hdlFunc));
	CatchError
}



/*!
	Point to a frr term.
*/
inline FrR * FrR::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc));
	CatchError
}




/*!
	Refer to a frr term.
*/
inline FrR const & FrR::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcFunc(hdlFunc));
	CatchError
}



/*!
	Point to a frr term.
*/
inline FrR const * FrR::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc));
	CatchError
}



/*!
	The constructor.
*/
inline FrR::FrR(Hdl const hdlSys, Dim const PrmCount) :
		Func(hdlSys, PrmCount)
{
	WatchError
	setTermCat(TermStub<FrR>::TermCat);
	CatchError
}



/*!
	The destructor.
*/
inline FrR::~FrR()
{
	WatchError
	//	nothing to be done.
	CatchError
}



#if ExecUpwdLazy
/*!
	Run post exection process in anew mode.
*/
inline void FrR::runPostExecAnew()
{
	WatchError
	#if ExecUpwd
	this->clearExecChgdPrms();
	#endif//ExecUpwd

	#if ExecLazy
	this->reinitEvalUndoPrms();
	#endif//ExecLazy
	CatchError
}
#endif //ExecUpwdLazy


#if ExecUpwdLazy
/*!
	Run post execution process in incr mode.
*/
inline void FrR::runPostExecIncr()
{
	WatchError
	#if ExecUpwd
	this->clearExecChgdPrms();
	#endif//ExecUpwd

	#if ExecLazy
	this->reiterEvalUndoPrms();
	#endif//ExecLazy
	CatchError
}
#endif //ExecUpwdLazy



#if CompLazy
/*!
	Run post execution process in backlog mode.
*/
inline void FrR::runPostExecBklg()
{
	WatchError
	this->reiterEvalUndoPrms();
	CatchError
}
#endif


closeKangarooSpace


#endif//FrRHppIncluded
