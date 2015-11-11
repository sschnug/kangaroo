/*!
	@file qcdv0tabu.hpp
	@brief The prototype file for QcDv0Tabu class.
	@details This is the prototype file for QcDv0Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
*/



#ifndef QcDv0TabuHppIncluded
#define QcDv0TabuHppIncluded



#include "cbls/tabus/reg.hh"
#include "cbls/tabus/dvtabus/dv0tabu.hpp"


openKangarooSpace



/*!
	@class QcDv0Tabu
	@brief A class to represent double tabu variables with no callbacks by using circular queues.
	@details This class represents double tabu variables with no callbacks by using circular queues.
*/
class QcDv0Tabu : public Dv0Tabu
{
	public:

		static Typ def(Hdl const hdlSys, Dim const theLength);	//!< Definition.

		//! @name Access
		//! @{

		static QcDv0Tabu & refm(Hdl const hdlSys);				//!< Reference.
		static QcDv0Tabu * ptrm(Hdl const hdlSys);				//!< Pointer.
		static QcDv0Tabu const & refc(Hdl const hdlSys);		//!< Reference.
		static QcDv0Tabu const * ptrc(Hdl const hdlSys);		//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static QcDv0Tabu const & cast(Tabu const & theTabu);	//!< Perform casting.
		static QcDv0Tabu const * cast(Tabu const * theTabu);	//!< Perform casting.
		static QcDv0Tabu & cast(Tabu & theTabu);				//!< Perform casting.
		static QcDv0Tabu * cast(Tabu * theTabu);				//!< Perform casting.

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

		~QcDv0Tabu();											//!< Destructor.
		QcDv0Tabu(QcDv0Tabu const & that);						//!< Duplicator.
		QcDv0Tabu(Hdl const hdlSys, Dim const theLength);		//!< Initialiser.
		QcDv0Tabu const & operator = (QcDv0Tabu const & that);	//!< Assigner.

		void adjustMemAuto();			//!< Adjust memory automatically.
		void updtTabuAuto();			//!< Update tabu automatically.

	private:

		Dim 	mLength;				//!< Length of the tabu.
		qc<t2<Hdl,Hdl>,xmmm> mQueue;	//!< Queue of tabu vars.
};



/*!
	Define an eval table.
*/
inline Typ QcDv0Tabu::def(Hdl const hdlSys, Dim const theLength)
{
	WatchError
	QcDv0Tabu * tTabu = new QcDv0Tabu(hdlSys, theLength);
	if (tTabu->defSysTabu()) return tTabu->TabuTyp;
	delete tTabu;
	return TabuTypNil;
	CatchError
}



/*!
	The constructor.
*/
inline QcDv0Tabu::QcDv0Tabu(Hdl const hdlSys, Dim const theLength) :
	Dv0Tabu(hdlSys), mLength(theLength), mQueue(theLength)
{
	WatchError
	setTabuCls(TabuStub<QcDv0Tabu>::TabuCls);
	mActive = castBll(theLength);
	CatchError
}



/*!
	The destructor.
*/
inline QcDv0Tabu::~QcDv0Tabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	Return the current tabu length.
*/
inline Dim const & QcDv0Tabu::Length() const
{
	WatchError
	return mLength;
	CatchError
}


/*!
	Adjust dynamic memory
*/
inline void QcDv0Tabu::adjustMemAuto()
{
	WatchError
	mQueue.adjustMemAuto();
	Dv0Tabu::adjustMemAuto();
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcDv0Tabu::suit(Tabu const & theTabu)
{
	WatchError
	return theTabu.TabuCls == TabuStub< QcDv0Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcDv0Tabu::suit(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCls == TabuStub< QcDv0Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcDv0Tabu::suit(Tabu & theTabu)
{
	WatchError
	return theTabu.TabuCls == TabuStub< QcDv0Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcDv0Tabu::suit(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCls == TabuStub< QcDv0Tabu >::TabuCls;
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcDv0Tabu const & QcDv0Tabu::cast(Tabu const & theTabu)
{
	WatchError
	Warn(theTabu.TabuCls != TabuStub< QcDv0Tabu >::TabuCls, eWrongCls);
	return scast<QcDv0Tabu const &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcDv0Tabu const * QcDv0Tabu::cast(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCls != TabuStub< QcDv0Tabu >::TabuCls, eWrongCls);

	return scast<QcDv0Tabu const *>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcDv0Tabu & QcDv0Tabu::cast(Tabu & theTabu)
{
	WatchError
	Warn(theTabu.TabuCls != TabuStub< QcDv0Tabu >::TabuCls, eWrongCls);

	return scast<QcDv0Tabu &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcDv0Tabu * QcDv0Tabu::cast(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCls != TabuStub< QcDv0Tabu >::TabuCls, eWrongCls);

	return scast<QcDv0Tabu *>(theTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
inline QcDv0Tabu & QcDv0Tabu::refm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmTabu(TabuStub<Dv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline QcDv0Tabu * QcDv0Tabu::ptrm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmTabu(TabuStub<Dv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Refer to a tabu.
*/
inline QcDv0Tabu const & QcDv0Tabu::refc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcTabu(TabuStub<Dv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline QcDv0Tabu const * QcDv0Tabu::ptrc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcTabu(TabuStub<Dv0Tabu>::TabuTyp));
	CatchError
}



closeKangarooSpace



#endif // QcDv0TabuHppIncluded
