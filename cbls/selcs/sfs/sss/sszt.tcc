/*!
	@file sszt.tcc
	@brief The source file for SsZt template class.
	@details This is the source file for SsZt template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SsZtTccIncluded
#define SsZtTccIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"


openKangarooSpace



/*!
	@class SsZt
	@brief A template class to represent swap selcs.
	@details This template class represents swap selcs.
*/
template<typename zt>
class SsZt : public Ss
{
	public:

		static SsZt<zt> const & refc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Reference
		static SsZt<zt> const * ptrc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Pointer.
		static SsZt<zt> & refm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Reference
		static SsZt<zt> * ptrm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Pointer.

		//! @name Casting
		//! @{

		static Bll suit(Selc & theSelc);						//!< Suits casting?
		static Bll suit(Selc * theSelc);						//!< Suits casting?
		static Bll suit(Selc const & theSelc);					//!< Suits casting?
		static Bll suit(Selc const * theSelc);					//!< Suits casting?

		static SsZt<zt> & cast(Selc & theSelc);						//!< Perform casting.
		static SsZt<zt> * cast(Selc * theSelc);						//!< Perform casting.
		static SsZt<zt> const & cast(Selc const & theSelc);			//!< Perform casting.
		static SsZt<zt> const * cast(Selc const * theSelc);			//!< Perform casting.

		//! @}

	protected:

		SsZt(Hdl const hdlSys, Dim const PrmCount);						//!< Constructor.
		SsZt(SsZt<zt> const & that);									//!< Duplicator.
		SsZt<zt> const & operator = (SsZt<zt> const & that);			//!< Assigner.
		~SsZt();														//!< Destructor.
};



/*!
	Whether a term is suitable for casting.
*/
template<typename zt>
inline Bln SsZt<zt>::suit(Selc const & theSelc)
{
	return theSelc.SelcTyp == SelcStub< SsZt<zt> >::SelcTyp;
}



/*!
	Whether a term is suitable for casting.
*/
template<typename zt>
inline Bln SsZt<zt>::suit(Selc const * theSelc)
{
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcTyp == SelcStub< SsZt<zt> >::SelcTyp;
}



/*!
	Whether a term is suitable for casting.
*/
template<typename zt>
inline Bln SsZt<zt>::suit(Selc & theSelc)
{
	return theSelc.SelcTyp == SelcStub< SsZt<zt> >::SelcTyp;
}



/*!
	Whether a term is suitable for casting.
*/
template<typename zt>
inline Bln SsZt<zt>::suit(Selc * theSelc)
{
	Warn(!theSelc, eNullPointer);

	return theSelc->SelcTyp == SelcStub< SsZt<zt> >::SelcTyp;
}



/*!
	Perform casting of a term.
*/
template<typename zt>
inline SsZt<zt> & SsZt<zt>::cast(Selc & theSelc)
{
	Warn(theSelc.SelcTyp != SelcStub< SsZt<zt> >::SelcTyp, eWrongTyp);

	return static_cast<SsZt<zt> &>(theSelc);
}



/*!
	Perform casting of a term.
*/
template<typename zt>
inline SsZt<zt> * SsZt<zt>::cast(Selc * theSelc)
{
	Warn(!theSelc, eNullPointer);
	Warn(theSelc->SelcTyp != SelcStub< SsZt<zt> >::SelcTyp, eWrongTyp);

	return static_cast<SsZt<zt> *>(theSelc);
}



/*!
	Perform casting of a term.
*/
template<typename zt>
inline SsZt<zt> const & SsZt<zt>::cast(Selc const & theSelc)
{
	Warn(theSelc.SelcTyp != SelcStub< SsZt<zt> >::SelcTyp, eWrongTyp);

	return static_cast<SsZt<zt> const &>(theSelc);
}



/*!
	Perform casting of a term.
*/
template<typename zt>
inline SsZt<zt> const * SsZt<zt>::cast(Selc const * theSelc)
{
	Warn(!theSelc, eNullPointer);
	Warn(theSelc->SelcTyp != SelcStub< SsZt<zt> >::SelcTyp, eWrongTyp);

	return static_cast<SsZt<zt> const *>(theSelc);
}



/*!
	Refer to a selc in the sys.
*/
template<typename zt>
inline SsZt<zt> const & SsZt<zt>::refc(Hdl const hdlSys, Hdl const hdlSelc)
{
	return cast(Sys::refc(hdlSys).refcSelc(hdlSelc));
}



/*!
	Point to a selc in the sys.
*/
template<typename zt>
inline SsZt<zt> const * SsZt<zt>::ptrc(Hdl const hdlSys, Hdl const hdlSelc)
{
	return cast(Sys::ptrc(hdlSys)->ptrcSelc(hdlSelc));
}



/*!
	Refer to a selc in the sys.
*/
template<typename zt>
inline SsZt<zt> & SsZt<zt>::refm(Hdl const hdlSys, Hdl const hdlSelc)
{
	return cast(Sys::refm(hdlSys).refmSelc(hdlSelc));
}



/*!
	Point to a selc in the sys.
*/
template<typename zt>
inline SsZt<zt> * SsZt<zt>::ptrm(Hdl const hdlSys, Hdl const hdlSelc)
{
	return cast(Sys::ptrm(hdlSys)->ptrmSelc(hdlSelc));
}



/*!
	The constructor.
*/
template<typename zt>
inline SsZt<zt>::SsZt(Hdl const hdlSys, Dim const PrmCount) :
		Ss(hdlSys, PrmCount)
{
	setSelcTyp(SelcStub< SsZt<zt> >::SelcTyp);
	setExecReady(true);
}



/*!
	The destructor.
*/
template<typename zt>
inline SsZt<zt>::~SsZt()
{
	//	nothing to be done.
}


/*!
	The duplicator.
*/
template<typename zt>
SsZt<zt>::SsZt(SsZt<zt> const & that) : Ss(that)
{
	Throw(eUndefDuplicator);
}



/*!
	The assigner.
*/
template<typename zt>
SsZt<zt> const & SsZt<zt>::operator = (SsZt<zt> const & that)
{
	Throw(eUndefAssigner);
}


closeKangarooSpace


#endif
