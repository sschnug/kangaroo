/*!
	@file hinttbl.tcc
	@brief The source file for HintTbl template class.
	@details This is the source file for HintTbl template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef HintTblTccIncluded
#define HintTblTccIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/hintrec.tcc"



openKangarooSpace



/*!
	@class HintTbl
	@brief A template class to represent hint tables.
	@details This is a template class represent hint tables.
*/
template<typename dat>
class HintTbl : public Hint
{
	public:
		static Bll def(Hdl const hdlSys);						//!< Define a hint table.

		//! @name Access
		//! @{

		static HintTbl<dat> & refm(Hdl const hdlSys);			//!< Reference.
		static HintTbl<dat> * ptrm(Hdl const hdlSys);			//!< Pointer.
		static HintTbl<dat> const & refc(Hdl const hdlSys);		//!< Reference.
		static HintTbl<dat> const * ptrc(Hdl const hdlSys);		//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static HintTbl<dat> const & cast(Hint const & theHint);	//!< Perform casting.
		static HintTbl<dat> const * cast(Hint const * theHint);	//!< Perform casting.
		static HintTbl<dat> & cast(Hint & theHint);				//!< Perform casting.
		static HintTbl<dat> * cast(Hint * theHint);				//!< Perform casting.

		static Bll suit(Hint const & theHint);				//!< Suits casting?
		static Bll suit(Hint const * theHint);				//!< Suits casting?
		static Bll suit(Hint & theHint);					//!< Suits casting?
		static Bll suit(Hint * theHint);					//!< Suits casting?

		//! @}


		void setHintRec(HintRec<dat> * & theHintRec,
						Hdl & hdlHint, Dim const VarCount);			//!< Define and point to a record.
		HintRec<dat> const & refcHintRec(Hdl const hdlHint) const;	//!< Refer to a record.
		HintRec<dat> const * ptrcHintRec(Hdl const hdlHint) const;	//!< Point to a record.

	private:
		~HintTbl();													//!< Destructor.
		HintTbl(Hdl const hdlSys);									//!< Constructor.
		HintTbl(HintTbl<dat> const & that);							//!< Duplicator.
		HintTbl const & operator = (HintTbl<dat> const & that);		//!< Assigner.

		virtual void syncExecClk();									//!< Synchronise.
		virtual void adjustMemAuto();								//!< Adjust memory.

	private:

		pbd<HintRec<dat>,xmm > mHintTbl;							//!< The hint table.
};




/*!
	Define a hint table
*/
template<typename dat>
inline Bll HintTbl<dat>::def(Hdl const hdlSys)
{
	WatchError
	HintTbl<dat> * tHintTbl = new HintTbl<dat>(hdlSys);
	if (tHintTbl->defSysHint()) return true;
	delete tHintTbl;
	return false;
	CatchError
}



/*!
	Whether a hint is suitable for casting.
*/
template<typename dat>
inline Bll HintTbl<dat>::suit(Hint const & theHint)
{
	WatchError
	return theHint.TypeSrl == DataStub<dat>::DataTyp;
	CatchError
}



/*!
	Whether a hint is suitable for casting.
*/
template<typename dat>
inline Bll HintTbl<dat>::suit(Hint const * theHint)
{
	WatchError
	Warn(!theHint, eNullPointer);

	return theHint->TypeSrl == DataStub<dat>::DataTyp;
	CatchError
}



/*!
	Whether a hint is suitable for casting.
*/
template<typename dat>
inline Bll HintTbl<dat>::suit(Hint & theHint)
{
	WatchError
	return theHint.TypeSrl == DataStub<dat>::DataTyp;
	CatchError
}



/*!
	Whether a hint is suitable for casting.
*/
template<typename dat>
inline Bll HintTbl<dat>::suit(Hint * theHint)
{
	WatchError
	Warn(!theHint, eNullPointer);

	return theHint->TypeSrl == DataStub<dat>::DataTyp;
	CatchError
}



/*!
	Perform casting of a hint.
*/
template<typename dat>
inline HintTbl<dat> const & HintTbl<dat>::cast(Hint const & theHint)
{
	WatchError
	Warn(theHint.TypeSrl != DataStub<dat>::DataTyp, eTypeMismatch);
	return scast<HintTbl<dat> const &>(theHint);
	CatchError
}



/*!
	Perform casting of a hint.
*/
template<typename dat>
inline HintTbl<dat> const * HintTbl<dat>::cast(Hint const * theHint)
{
	WatchError
	Warn(!theHint, eNullPointer);
	Warn(theHint->TypeSrl != DataStub<dat>::DataTyp, eTypeMismatch);

	return scast<HintTbl<dat> const *>(theHint);
	CatchError
}



/*!
	Perform casting of a hint.
*/
template<typename dat>
inline HintTbl<dat> & HintTbl<dat>::cast(Hint & theHint)
{
	WatchError
	Warn(theHint.TypeSrl != DataStub<dat>::DataTyp, eTypeMismatch);

	return scast<HintTbl<dat> &>(theHint);
	CatchError
}



/*!
	Perform casting of a hint.
*/
template<typename dat>
inline HintTbl<dat> * HintTbl<dat>::cast(Hint * theHint)
{
	WatchError
	Warn(!theHint, eNullPointer);
	Warn(theHint->TypeSrl != DataStub<dat>::DataTyp, eTypeMismatch);

	return scast<HintTbl<dat> *>(theHint);
	CatchError
}



/*!
	Refer to a hint table.
*/
template<typename dat>
inline HintTbl<dat> & HintTbl<dat>::refm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmHint(DataStub<dat>::DataTyp));
	CatchError
}



/*!
	Point to a hint table.
*/
template<typename dat>
inline HintTbl<dat> * HintTbl<dat>::ptrm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmHint(DataStub<dat>::DataTyp));
	CatchError
}



/*!
	Refer to a hint table.
*/
template<typename dat>
inline HintTbl<dat> const & HintTbl<dat>::refc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcHint(DataStub<dat>::DataTyp));
	CatchError
}



/*!
	Point to a hint table.
*/
template<typename dat>
inline HintTbl<dat> const * HintTbl<dat>::ptrc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcHint(DataStub<dat>::DataTyp));
	CatchError
}



/*!
	Define and point to a hint record.
*/
template<typename dat>
inline void HintTbl<dat>::setHintRec(HintRec<dat> * & theHintRec,
									Hdl & hdlHint, Dim const VarCount)
{
	WatchError
	if (hdlHint >= mHintTbl.packCount())
		hdlHint = mHintTbl.defPack(new HintRec<dat>(VarCount));
	theHintRec = mHintTbl.ptrmPack(hdlHint);
	CatchError
}



/*!
	Refer to the hint record.
*/
template<typename dat>
inline HintRec<dat> const & HintTbl<dat>::refcHintRec(Hdl const hdlHint) const
{
	WatchError
	Warn(hdlHint >= mHintTbl.packCount(), eInvalidIndex);

	return mHintTbl.refcPack(hdlHint);
	CatchError
}



/*!
	Point to the hint record.
*/
template<typename dat>
inline HintRec<dat> const * HintTbl<dat>::ptrcHintRec(Hdl const hdlHint) const
{
	WatchError
	Warn(hdlHint >= mHintTbl.packCount(), eInvalidIndex);

	return mHintTbl.ptrcPack(hdlHint);
	CatchError
}



/*!
	The constructor.
*/
template<typename dat>
HintTbl<dat>::HintTbl(Hdl const hdlSys) : Hint(hdlSys,  DataStub<dat>::DataTyp)
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	The duplicator.
*/
template<typename dat>
HintTbl<dat>::HintTbl(HintTbl<dat> const & that) : Hint(that),
		mHintTbl(that.mHintTbl)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
template<typename dat>
HintTbl<dat>::~HintTbl()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
template<typename dat>
HintTbl<dat> const & HintTbl<dat>::operator = (HintTbl<dat> const & that)
{
	WatchError
	if (this == &that)
		return *this;
	Hint::operator=(that);
	mHintTbl = that.mHintTbl;
	return *this;
	CatchError
}



/*!
	Synchronise the execution clock.
*/
template<typename dat>
void HintTbl<dat>::syncExecClk()
{
	WatchError
	for(Hdl tHdl = 0; tHdl < mHintTbl.packCount(); ++tHdl)
		mHintTbl.refmPack(tHdl).syncExecClk();
	CatchError
}




/*!
	Adjust memory automatically.
*/
template<typename dat>
void HintTbl<dat>::adjustMemAuto()
{
	WatchError
	mHintTbl.adjustMemAuto();
	CatchError
}



closeKangarooSpace



#endif//HintTblTccIncluded
