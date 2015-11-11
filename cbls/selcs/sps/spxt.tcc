/*!
	@file spxt.tcc
	@brief The source file for SpXt template class.
	@details This is the source file for SpXt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SpXtTccIncluded
#define SpXtTccIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"
#include "cbls/selcs/sp.hpp"


openKangarooSpace



/*!
	@class SpXt
	@brief A template class to represent prep selcs.
	@details This template class represents prep selcs.
*/
template<typename xt>
class SpXt : public Sp
{
	public:

		static SpXt<xt> & refm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Reference
		static SpXt<xt> * ptrm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Pointer.
		static SpXt<xt> const & refc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Reference
		static SpXt<xt> const * ptrc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Pointer.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);						//!< Suits casting?
		static Bll suit(Selc * theSelc);						//!< Suits casting?
		static Bll suit(Selc const & theSelc);					//!< Suits casting?
		static Bll suit(Selc const * theSelc);					//!< Suits casting?

		static SpXt<xt> & cast(Selc & theSelc);						//!< Perform casting.
		static SpXt<xt> * cast(Selc * theSelc);						//!< Perform casting.
		static SpXt<xt> const & cast(Selc const & theSelc);			//!< Perform casting.
		static SpXt<xt> const * cast(Selc const * theSelc);			//!< Perform casting.

		//! @}

	protected:

		SpXt(Hdl const hdlSys, Dim const PrmCount);						//!< Constructor.
		SpXt(SpXt<xt> const & that);									//!< Duplicator.
		SpXt<xt> const & operator = (SpXt<xt> const & that);			//!< Assigner.
		~SpXt();														//!< Destructor.
};



/*!
	Whether a term is suitable for casting.
*/
template<typename xt>
inline Bln SpXt<xt>::suit(Selc const & theSelc)
{
	WatchError
	return theSelc.SelcTyp == SelcStub< SpXt<xt> >::SelcTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename xt>
inline Bln SpXt<xt>::suit(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcTyp == SelcStub< SpXt<xt> >::SelcTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename xt>
inline Bln SpXt<xt>::suit(Selc & theSelc)
{
	WatchError
	return theSelc.SelcTyp == SelcStub< SpXt<xt> >::SelcTyp;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
template<typename xt>
inline Bln SpXt<xt>::suit(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcTyp == SelcStub< SpXt<xt> >::SelcTyp;
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename xt>
inline SpXt<xt> & SpXt<xt>::cast(Selc & theSelc)
{
	WatchError
	Warn(theSelc.SelcTyp != SelcStub< SpXt<xt> >::SelcTyp, eWrongTyp);

	return static_cast<SpXt<xt> &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename xt>
inline SpXt<xt> * SpXt<xt>::cast(Selc * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Warn(theSelc->SelcTyp != SelcStub< SpXt<xt> >::SelcTyp, eWrongTyp);

	return static_cast<SpXt<xt> *>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename xt>
inline SpXt<xt> const & SpXt<xt>::cast(Selc const & theSelc)
{
	WatchError
	Warn(theSelc.SelcTyp != SelcStub< SpXt<xt> >::SelcTyp, eWrongTyp);

	return static_cast<SpXt<xt> const &>(theSelc);
	CatchError
}



/*!
	Perform casting of a term.
*/
template<typename xt>
inline SpXt<xt> const * SpXt<xt>::cast(Selc const * theSelc)
{
	WatchError
	Warn(!theSelc, eNullPointer);
	Warn(theSelc->SelcTyp != SelcStub< SpXt<xt> >::SelcTyp, eWrongTyp);

	return static_cast<SpXt<xt> const *>(theSelc);
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
template<typename xt>
inline SpXt<xt> & SpXt<xt>::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
template<typename xt>
inline SpXt<xt> * SpXt<xt>::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc));
	CatchError
}



/*!
	Refer to a selc in the sys.
*/
template<typename xt>
inline SpXt<xt> const & SpXt<xt>::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
	CatchError
}



/*!
	Point to a selc in the sys.
*/
template<typename xt>
inline SpXt<xt> const * SpXt<xt>::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
	CatchError
}



/*!
	The constructor.
*/
template<typename xt>
inline SpXt<xt>::SpXt(Hdl const hdlSys, Dim const PrmCount) :
		Sp(hdlSys, PrmCount)
{
	WatchError
	setSelcTyp(SelcStub< SpXt<xt> >::SelcTyp);
	setExecReady(false);
	CatchError
}



/*!
	The destructor.
*/
template<typename xt>
inline SpXt<xt>::~SpXt()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	The duplicator.
*/
template<typename xt>
SpXt<xt>::SpXt(SpXt<xt> const & that) : Sp(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
template<typename xt>
SpXt<xt> const & SpXt<xt>::operator = (SpXt<xt> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



closeKangarooSpace


#endif
