/*!
	@file sdzt.tcc
	@brief The source file for SdZt template class.
	@details This is the source file for SdZt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SdZtTccIncluded
#define SdZtTccIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"
#include "cbls/selcs/sfs/sd.hpp"


openKangarooSpace



/*!
	@class SdZt
	@brief A template class to represent differential selcs.
	@details This template class represents differential selcs.
*/
template<typename zt>
class SdZt : public Sd
{
	public:

		static SdZt<zt> & refm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Reference
		static SdZt<zt> * ptrm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Pointer.
		static SdZt<zt> const & refc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Reference
		static SdZt<zt> const * ptrc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Pointer.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);							//!< Suits casting?
		static Bll suit(Selc * theSelc);							//!< Suits casting?
		static Bll suit(Selc const & theSelc);						//!< Suits casting?
		static Bll suit(Selc const * theSelc);						//!< Suits casting?

		static SdZt<zt> & cast(Selc & theSelc);						//!< Perform casting.
		static SdZt<zt> * cast(Selc * theSelc);						//!< Perform casting.
		static SdZt<zt> const & cast(Selc const & theSelc);			//!< Perform casting.
		static SdZt<zt> const * cast(Selc const * theSelc);			//!< Perform casting.

		//! @}

	protected:

		SdZt(Hdl const hdlSys, Dim const PrmSize);						//!< Constructor.
		SdZt(SdZt<zt> const & that);									//!< Duplicator.
		SdZt<zt> const & operator = (SdZt<zt> const & that);			//!< Assigner.
		~SdZt();														//!< Destructor.
};



/*!
	Whether a term is suitable for casting.
*/
template<typename zt>
inline Bln SdZt<zt>::suit(Selc const & theSelc)
{
	return theSelc.SelcTyp == SelcStub< SdZt<zt> >::SelcTyp;
}



/*!
	Whether a term is suitable for casting.
*/
template<typename zt>
inline Bln SdZt<zt>::suit(Selc const * theSelc)
{
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcTyp == SelcStub< SdZt<zt> >::SelcTyp;
}



/*!
	Whether a term is suitable for casting.
*/
template<typename zt>
inline Bln SdZt<zt>::suit(Selc & theSelc)
{
	return theSelc.SelcTyp == SelcStub< SdZt<zt> >::SelcTyp;
}



/*!
	Whether a term is suitable for casting.
*/
template<typename zt>
inline Bln SdZt<zt>::suit(Selc * theSelc)
{
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcTyp == SelcStub< SdZt<zt> >::SelcTyp;
}



/*!
	Perform casting of a term.
*/
template<typename zt>
inline SdZt<zt> & SdZt<zt>::cast(Selc & theSelc)
{
	Warn(theSelc.SelcTyp != SelcStub< SdZt<zt> >::SelcTyp, eWrongTyp);

	return static_cast<SdZt<zt> &>(theSelc);
}



/*!
	Perform casting of a term.
*/
template<typename zt>
inline SdZt<zt> * SdZt<zt>::cast(Selc * theSelc)
{
	Warn(!theSelc, eNullPointer);
	Warn(theSelc->SelcTyp != SelcStub< SdZt<zt> >::SelcTyp, eWrongTyp);

	return static_cast<SdZt<zt> *>(theSelc);
}



/*!
	Perform casting of a term.
*/
template<typename zt>
inline SdZt<zt> const & SdZt<zt>::cast(Selc const & theSelc)
{
	Warn(theSelc.SelcTyp != SelcStub< SdZt<zt> >::SelcTyp, eWrongTyp);

	return static_cast<SdZt<zt> const &>(theSelc);
}



/*!
	Perform casting of a term.
*/
template<typename zt>
inline SdZt<zt> const * SdZt<zt>::cast(Selc const * theSelc)
{
	Warn(!theSelc, eNullPointer);
	Warn(theSelc->SelcTyp != SelcStub< SdZt<zt> >::SelcTyp, eWrongTyp);

	return static_cast<SdZt<zt> const *>(theSelc);
}



/*!
	Refer to a selc in the sys.
*/
template<typename zt>
inline SdZt<zt> & SdZt<zt>::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
}



/*!
	Point to a selc in the sys.
*/
template<typename zt>
inline SdZt<zt> * SdZt<zt>::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	return cast(Sys::ptrm(hdlSys)->ptrcSelc(hdlSelc));
}



/*!
	Refer to a selc in the sys.
*/
template<typename zt>
inline SdZt<zt> const & SdZt<zt>::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
}



/*!
	Point to a selc in the sys.
*/
template<typename zt>
inline SdZt<zt> const * SdZt<zt>::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
}



/*!
	The constructor.
*/
template<typename zt>
inline SdZt<zt>::SdZt(Hdl const hdlSys, Dim const PrmSize) :
		Sd(hdlSys, PrmSize)
{
	setSelcTyp(SelcStub< SdZt<zt> >::SelcTyp);
	setExecReady(true);
	setHoldValue(true);
}



/*!
	The destructor.
*/
template<typename zt>
inline SdZt<zt>::~SdZt()
{
	//	nothing to be done.
}


/*!
	The duplicator.
*/
template<typename zt>
SdZt<zt>::SdZt(SdZt<zt> const & that) : Sd(that)
{
	Throw(eUndefDuplicator);
}



/*!
	The assigner.
*/
template<typename zt>
SdZt<zt> const & SdZt<zt>::operator = (SdZt<zt> const & that)
{
	Throw(eUndefAssigner);
}


closeKangarooSpace


#endif
