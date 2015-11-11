/*!
	@file const.hpp
	@brief The prototype file for Const class.
	@details This is the prototype file for Const class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see const.cpp
	@see term.hpp
*/



#ifndef ConstHppIncluded
#define ConstHppIncluded



#include "cbls/frames/dat.hpp"
#include "cbls/frames/term.hpp"



openKangarooSpace



/*!
	@class Const
	@brief A class to represent constants.
	@details This class represents constants.
*/
class Const : public Term
{
	public:

		static Const & refm(Hdl const hdlSys, Hdl const hdlConst);			//!< Reference.
		static Const * ptrm(Hdl const hdlSys, Hdl const hdlConst);			//!< Pointer.
		static Const const & refc(Hdl const hdlSys, Hdl const hdlConst);	//!< Reference.
		static Const const * ptrc(Hdl const hdlSys, Hdl const hdlConst);	//!< Pointer.

		//! @name Casting
		//! @{

		static Const const & cast(Term const & theTerm);	//!< Perform casting.
		static Const const * cast(Term const * theTerm);	//!< Perform casting.
		static Const & cast(Term & theTerm);				//!< Perform casting.
		static Const * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);				//!< Suits casting?
		static Bll suit(Term const * theTerm);				//!< Suits casting?
		static Bll suit(Term & theTerm);					//!< Suits casting?
		static Bll suit(Term * theTerm);					//!< Suits casting?

		//! @}

	protected:

		friend class Sys;

		virtual ~Const();									//!< Destructor.
		Const(Hdl const hdlSys);							//!< Constructor.
		Const(Const const & that);							//!< Duplicator.
		Const const & operator = (Const const & that);		//!< Assigner.

		Hdl defSysConst();				//!< Define the constant in the sys.

		//! @name Computation
		//! @{

		virtual void execAnew();		//!< Anew execution; throws error.
		virtual void simulAnew();		//!< Anew simulation; throws error.
		virtual void execIncr();		//!< Incrmental execution; throws error.
		virtual void simulIncr();		//!< Incrmental simulation; throws error.

		#if CompLazy
		virtual void execBklg();		//!< Backlog execution; throws error.
		virtual void emulBklg();		//!< Backlog emulation; throws error.
		#endif

		//! @}
};



/*!
	The constructor.
*/
inline Const::Const(Hdl const hdlSys) :
		Term(hdlSys)
{
	WatchError
	setTermGen(Tc);
	CatchError
}


/*!
	The destructor.
*/
inline Const::~Const()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Refer to a constant.
*/
inline Const const & Const::refc(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return Sys::refc(hdlSys).refcConst(hdlConst);
	CatchError
}



/*!
	Point to a constant.
*/
inline Const const * Const::ptrc(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return Sys::ptrc(hdlSys)->ptrcConst(hdlConst);
	CatchError
}



/*!
	Refer to a constant.
*/
inline Const & Const::refm(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return Sys::refm(hdlSys).refmConst(hdlConst);
	CatchError
}



/*!
	Point to a constant.
*/
inline Const * Const::ptrm(Hdl const hdlSys, Hdl const hdlConst)
{
	WatchError
	return Sys::ptrm(hdlSys)->ptrmConst(hdlConst);
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll Const::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermGen == Tc;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll Const::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermGen == Tc;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll Const::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermGen == Tc;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll Const::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermGen == Tc;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline Const const & Const::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermGen != Tc, eTermNotConstant);

	return scast<Const const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline Const const * Const::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(!theTerm->TermGen != Tc, eTermNotConstant);

	return scast<Const const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline Const & Const::cast(Term & theTerm)
{
	WatchError
	Warn(!theTerm.TermGen != Tc, eTermNotConstant);

	return scast<Const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline Const * Const::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(!theTerm->TermGen != Tc, eTermNotConstant);

	return scast<Const *>(theTerm);
	CatchError
}



/*!
	Define a const in the sys.
*/
inline Hdl Const::defSysConst()
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	return mTermSys.defConst(this);
	CatchError
}



closeKangarooSpace



#endif // ConstHppIncluded
