/*!
	@file qcdv2tabu.hpp
	@brief The prototype file for QcDv2Tabu class.
	@details This is the prototype file for QcDv2Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
*/



#ifndef QcDv2TabuHppIncluded
#define QcDv2TabuHppIncluded



#include "cbls/tabus/reg.hh"
#include "cbls/tabus/dvtabus/dv2tabu.hpp"


openKangarooSpace



/*!
	@class QcDv2Tabu
	@brief A class to represent double tabu variables with both callbacks by using circular queues.
	@details This class represents double tabu variables with both callbacks by using circular queues.
*/
class QcDv2Tabu : public Dv2Tabu
{
	public:

		static Typ def(Hdl const hdlSys, Dim const theLength);	//!< Definition.

		//! @name Access
		//! @{

		static QcDv2Tabu & refm(Hdl const hdlSys);				//!< Reference.
		static QcDv2Tabu * ptrm(Hdl const hdlSys);				//!< Pointer.
		static QcDv2Tabu const & refc(Hdl const hdlSys);		//!< Reference.
		static QcDv2Tabu const * ptrc(Hdl const hdlSys);		//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static QcDv2Tabu const & cast(Tabu const & theTabu);	//!< Perform casting.
		static QcDv2Tabu const * cast(Tabu const * theTabu);	//!< Perform casting.
		static QcDv2Tabu & cast(Tabu & theTabu);				//!< Perform casting.
		static QcDv2Tabu * cast(Tabu * theTabu);				//!< Perform casting.

		static Bll suit(Tabu const & theTabu);				//!< Suits casting?
		static Bll suit(Tabu const * theTabu);				//!< Suits casting?
		static Bll suit(Tabu & theTabu);					//!< Suits casting?
		static Bll suit(Tabu * theTabu);					//!< Suits casting?

		//! @}

		//! @name Status
		//! @{

		Dim const & Length() const;							//!< Get the current length of the tabu.

		//! @}
		//! @name Manipulation
		//! @{

		void reset();											//!< Reset the var tabu states.
		void setLength(Dim const theLength);					//!< Set the length of the tabu.
		void tabuVars(ll<Hdl,xmm> const & theAsgnVars);			//!< Tabu the assignment vars.
		void tabuVar2(Hdl const hdlVar1, Hdl const hdlVar2);	//!< Tabu the two variables.
		void tabuVars(Hdl const * hdlVars, Dim const VarCount);	//!< Tabu the variables.

		//! @}

	protected:

		~QcDv2Tabu();											//!< Destructor.
		QcDv2Tabu(QcDv2Tabu const & that);						//!< Duplicator.
		QcDv2Tabu(Hdl const hdlSys, Dim const theLength);		//!< Initialiser.
		QcDv2Tabu const & operator = (QcDv2Tabu const & that);	//!< Assigner.

		void adjustMemAuto();			//!< Adjust memory automatically.
		void updtTabuAuto();			//!< Update tabu automatically.

	private:

		Dim 	mLength;					//!< Length of the tabu.
		qc<t2<Hdl,Hdl>,xmmm> mQueue;		//!< Queue of tabu vars.
};



/*!
	Define an eval table.
*/
inline Typ QcDv2Tabu::def(Hdl const hdlSys, Dim const theLength)
{
	WatchError
	QcDv2Tabu * tTabu = new QcDv2Tabu(hdlSys, theLength);
	if (tTabu->defSysTabu()) return tTabu->TabuTyp;
	delete tTabu;
	return TabuTypNil;
	CatchError
}



/*!
	The constructor.
*/
inline QcDv2Tabu::QcDv2Tabu(Hdl const hdlSys, Dim const theLength) :
	Dv2Tabu(hdlSys), mLength(theLength), mQueue(theLength)
{
	WatchError
	setTabuCls(TabuStub<QcDv2Tabu>::TabuCls);
	mActive = castBll(theLength);
	CatchError
}



/*!
	The destructor.
*/
inline QcDv2Tabu::~QcDv2Tabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	Return the current tabu length.
*/
inline Dim const & QcDv2Tabu::Length() const
{
	WatchError
	return mLength;
	CatchError
}


/*!
	Adjust dynamic memory
*/
inline void QcDv2Tabu::adjustMemAuto()
{
	WatchError
	mQueue.adjustMemAuto();
	Dv2Tabu::adjustMemAuto();
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcDv2Tabu::suit(Tabu const & theTabu)
{
	WatchError
	return theTabu.TabuCls == TabuStub< QcDv2Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcDv2Tabu::suit(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCls == TabuStub< QcDv2Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcDv2Tabu::suit(Tabu & theTabu)
{
	WatchError
	return theTabu.TabuCls == TabuStub< QcDv2Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcDv2Tabu::suit(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCls == TabuStub< QcDv2Tabu >::TabuCls;
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcDv2Tabu const & QcDv2Tabu::cast(Tabu const & theTabu)
{
	WatchError
	Warn(theTabu.TabuCls != TabuStub< QcDv2Tabu >::TabuCls, eWrongCls);
	return scast<QcDv2Tabu const &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcDv2Tabu const * QcDv2Tabu::cast(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCls != TabuStub< QcDv2Tabu >::TabuCls, eWrongCls);

	return scast<QcDv2Tabu const *>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcDv2Tabu & QcDv2Tabu::cast(Tabu & theTabu)
{
	WatchError
	Warn(theTabu.TabuCls != TabuStub< QcDv2Tabu >::TabuCls, eWrongCls);

	return scast<QcDv2Tabu &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcDv2Tabu * QcDv2Tabu::cast(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCls != TabuStub< QcDv2Tabu >::TabuCls, eWrongCls);

	return scast<QcDv2Tabu *>(theTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
inline QcDv2Tabu & QcDv2Tabu::refm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmTabu(TabuStub<Dv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline QcDv2Tabu * QcDv2Tabu::ptrm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmTabu(TabuStub<Dv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Refer to a tabu.
*/
inline QcDv2Tabu const & QcDv2Tabu::refc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcTabu(TabuStub<Dv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline QcDv2Tabu const * QcDv2Tabu::ptrc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcTabu(TabuStub<Dv2Tabu>::TabuTyp));
	CatchError
}



closeKangarooSpace



#endif // QcDv2TabuHppIncluded
