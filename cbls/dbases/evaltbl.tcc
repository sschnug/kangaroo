/*!
	@file evaltbl.tcc
	@brief The source file for EvalTbl template class.
	@details This is the source file for EvalTbl template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef EvalTblTccIncluded
#define EvalTblTccIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/evalrec.tcc"



openKangarooSpace


/*!
	@class EvalTbl
	@brief A template class to represent eval tables
	@details This template class represents eval tables.
*/
template<typename dat>
class EvalTbl : public Eval
{
	public:

		static Bll def(Hdl const hdlSys);						//!< Definition.

		//! @name Access
		//! @{

		static EvalTbl<dat> & refm(Hdl const hdlSys);			//!< Reference.
		static EvalTbl<dat> * ptrm(Hdl const hdlSys);			//!< Pointer.
		static EvalTbl<dat> const & refc(Hdl const hdlSys);		//!< Reference.
		static EvalTbl<dat> const * ptrc(Hdl const hdlSys);		//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static EvalTbl<dat> const & cast(Eval const & theEval);	//!< Perform casting.
		static EvalTbl<dat> const * cast(Eval const * theEval);	//!< Perform casting.
		static EvalTbl<dat> & cast(Eval & theEval);				//!< Perform casting.
		static EvalTbl<dat> * cast(Eval * theEval);				//!< Perform casting.

		static Bll suit(Eval const & theEval);				//!< Suits casting?
		static Bll suit(Eval const * theEval);				//!< Suits casting?
		static Bll suit(Eval & theEval);					//!< Suits casting?
		static Bll suit(Eval * theEval);					//!< Suits casting?

		//! @}

		void setEvalRec(EvalRec<dat> * & theEvalRec, Hdl & hdlEval);	//!< Define a record

		EvalRec<dat> const * ptrcEvalRec(Hdl const hdlEval) const;		//!< Point to a record
		EvalRec<dat> const & refcEvalRec(Hdl const hdlEval) const;		//!< Refer to a record.

	private:

		~EvalTbl();														//!< Destructor.
		EvalTbl(Hdl const hdlSys);										//!< Constructor.
		EvalTbl(EvalTbl const & that);									//!< Duplicator.
		EvalTbl const & operator = (EvalTbl const & that);				//!< Assigner.

		virtual void syncExecClk();										//!< Synchronise.
		virtual void syncSimulClk();									//!< Synchronise.
		virtual void adjustMemAuto();									//!< Adjust memory.

	private:

		pbd< EvalRec<dat>, xmm> mEvalTbl;								//!< The eval table
};



/*!
	Define an eval table.
*/
template<typename dat>
inline Bll EvalTbl<dat>::def(Hdl const hdlSys)
{
	WatchError
	EvalTbl<dat> * tEvalTbl = new EvalTbl<dat>(hdlSys);
	if (tEvalTbl->defSysEval()) return true;
	delete tEvalTbl;
	return false;
	CatchError
}



/*!
	Whether an eval is suitable for casting.
*/
template<typename dat>
inline Bll EvalTbl<dat>::suit(Eval const & theEval)
{
	WatchError
	return theEval.TypeSrl == DataStub<dat>::DataTyp;
	CatchError
}



/*!
	Whether an eval is suitable for casting.
*/
template<typename dat>
inline Bll EvalTbl<dat>::suit(Eval const * theEval)
{
	WatchError
	Warn(!theEval, eNullPointer);

	return theEval->TypeSrl == DataStub<dat>::DataTyp;
	CatchError
}



/*!
	Whether an eval is suitable for casting.
*/
template<typename dat>
inline Bll EvalTbl<dat>::suit(Eval & theEval)
{
	WatchError
	return theEval.TypeSrl == DataStub<dat>::DataTyp;
	CatchError
}



/*!
	Whether an eval is suitable for casting.
*/
template<typename dat>
inline Bll EvalTbl<dat>::suit(Eval * theEval)
{
	WatchError
	Warn(!theEval, eNullPointer);

	return theEval->TypeSrl == DataStub<dat>::DataTyp;
	CatchError
}



/*!
	Perform casting of an eval.
*/
template<typename dat>
inline EvalTbl<dat> const & EvalTbl<dat>::cast(Eval const & theEval)
{
	WatchError
	Warn(theEval.TypeSrl != DataStub<dat>::DataTyp, eTypeMismatch);
	return scast<EvalTbl<dat> const &>(theEval);
	CatchError
}



/*!
	Perform casting of an eval.
*/
template<typename dat>
inline EvalTbl<dat> const * EvalTbl<dat>::cast(Eval const * theEval)
{
	WatchError
	Warn(!theEval, eNullPointer);
	Warn(theEval->TypeSrl != DataStub<dat>::DataTyp, eTypeMismatch);

	return scast<EvalTbl<dat> const *>(theEval);
	CatchError
}



/*!
	Perform casting of an eval.
*/
template<typename dat>
inline EvalTbl<dat> & EvalTbl<dat>::cast(Eval & theEval)
{
	WatchError
	Warn(theEval.TypeSrl != DataStub<dat>::DataTyp, eTypeMismatch);

	return scast<EvalTbl<dat> &>(theEval);
	CatchError
}



/*!
	Perform casting of an eval.
*/
template<typename dat>
inline EvalTbl<dat> * EvalTbl<dat>::cast(Eval * theEval)
{
	WatchError
	Warn(!theEval, eNullPointer);
	Warn(theEval->TypeSrl != DataStub<dat>::DataTyp, eTypeMismatch);

	return scast<EvalTbl<dat> *>(theEval);
	CatchError
}



/*!
	Refer to an eval table.
*/
template<typename dat>
inline EvalTbl<dat> & EvalTbl<dat>::refm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmEval(DataStub<dat>::DataTyp));
	CatchError
}



/*!
	Point to an eval table.
*/
template<typename dat>
inline EvalTbl<dat> * EvalTbl<dat>::ptrm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmEval(DataStub<dat>::DataTyp));
	CatchError
}



/*!
	Refer to an eval table.
*/
template<typename dat>
inline EvalTbl<dat> const & EvalTbl<dat>::refc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcEval(DataStub<dat>::DataTyp));
	CatchError
}



/*!
	Point to an eval table.
*/
template<typename dat>
inline EvalTbl<dat> const * EvalTbl<dat>::ptrc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcEval(DataStub<dat>::DataTyp));
	CatchError
}



/*!
	The constructor.
*/
template<typename dat>
inline EvalTbl<dat>::EvalTbl(Hdl const hdlSys) : Eval(hdlSys, DataStub<dat>::DataTyp)
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	The duplicator.
*/
template<typename dat>
inline EvalTbl<dat>::EvalTbl(EvalTbl const & that) : Eval(that),
		mEvalTbl(that.mEvalTbl)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
template<typename dat>
inline EvalTbl<dat>::~EvalTbl()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
template<typename dat>
inline EvalTbl<dat> const & EvalTbl<dat>::operator = (EvalTbl<dat> const & that)
{
	WatchError
	if (this == &that)
		return *this;
	Eval::operator=(that);
	mEvalTbl = that.mEvalTbl;
	return *this;
	CatchError
}



/*!
	Synchronise the execution clock.
*/
template<typename dat>
void EvalTbl<dat>::syncExecClk()
{
	WatchError
	for(Hdl tHdl = 0; tHdl < mEvalTbl.packCount(); ++tHdl)
		mEvalTbl.refmPack(tHdl).syncExecClk();
	CatchError
}


/*!
	Synchronise the simulation clock.
*/
template<typename dat>
void EvalTbl<dat>::syncSimulClk()
{
	WatchError
	for(Hdl tHdl = 0; tHdl < mEvalTbl.packCount(); ++tHdl)
		mEvalTbl.refmPack(tHdl).syncSimulClk();
	CatchError
}



/*!
	Adjust memory automatically.
*/
template<typename dat>
void EvalTbl<dat>::adjustMemAuto()
{
	WatchError
	mEvalTbl.adjustMemAuto();
	CatchError
}




/*!
	Define and point to a value record.
*/
template<typename dat>
inline void EvalTbl<dat>::setEvalRec(EvalRec<dat> * & theEvalRec, Hdl & hdlEval)
{
	WatchError
	if (hdlEval >= mEvalTbl.packCount())
		hdlEval = mEvalTbl.defPack(new EvalRec<dat>);
	theEvalRec = mEvalTbl.ptrmPack(hdlEval);
	CatchError
}



/*!
	Refer to the value rec.
*/
template<typename dat>
inline EvalRec<dat> const & EvalTbl<dat>::refcEvalRec(Hdl const hdlEval) const
{
	WatchError
	Warn(hdlEval >= mEvalTbl.packCount(), eInvalidIndex);

	return mEvalTbl.refcPack(hdlEval);
	CatchError
}



/*!
	Point to the value rec.
*/
template<typename dat>
inline EvalRec<dat> const * EvalTbl<dat>::ptrcEvalRec(Hdl const hdlEval) const
{
	WatchError
	Warn(hdlEval >= mEvalTbl.packCount(), eInvalidIndex);

	return mEvalTbl.ptrcPack(hdlEval);
	CatchError
}




closeKangarooSpace



#endif//EvalTblTccIncluded
