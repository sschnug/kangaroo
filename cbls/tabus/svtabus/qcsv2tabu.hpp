/*!
	@file qcsv2tabu.hpp
	@brief The prototype file for QcSv2Tabu class.
	@details This is the prototype file for QcSv2Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
*/



#ifndef QcSv2TabuHppIncluded
#define QcSv2TabuHppIncluded



#include "cbls/tabus/reg.hh"
#include "cbls/tabus/svtabus/sv2tabu.hpp"



openKangarooSpace



/*!
	@class QcSv2Tabu
	@brief A class to represent single tabu variables with both callbacks by using circular queues.
	@details This class represents single tabu variable with both callbacks by using circular queues.
*/
class QcSv2Tabu : public Sv2Tabu
{
	public:

		static Typ def(Hdl const hdlSys, Dim const theLength);	//!< Definition.

		//! @name Access
		//! @{

		static QcSv2Tabu & refm(Hdl const hdlSys);			//!< Reference.
		static QcSv2Tabu * ptrm(Hdl const hdlSys);			//!< Pointer.
		static QcSv2Tabu const & refc(Hdl const hdlSys);	//!< Reference.
		static QcSv2Tabu const * ptrc(Hdl const hdlSys);	//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static QcSv2Tabu const & cast(Tabu const & theTabu);	//!< Perform casting.
		static QcSv2Tabu const * cast(Tabu const * theTabu);	//!< Perform casting.
		static QcSv2Tabu & cast(Tabu & theTabu);				//!< Perform casting.
		static QcSv2Tabu * cast(Tabu * theTabu);				//!< Perform casting.

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
		void tabuVar(Hdl const hdlVar);							//!< Tabu the variable.
		void tabuVars(ll<Hdl,xmm> const & theAsgnVars);			//!< Tabu the assignment vars.
		void tabuVar2(Hdl const hdlVar1, Hdl const hdlVar2);	//!< Tabu the two variables.
		void tabuVars(Hdl const * hdlVars, Dim const VarCount);	//!< Tabu the variables.

		//! @}

	protected:

		~QcSv2Tabu();											//!< Destructor.
		QcSv2Tabu(QcSv2Tabu const & that);						//!< Duplicator.
		QcSv2Tabu(Hdl const hdlSys, Dim const theLength);		//!< Initialiser.
		QcSv2Tabu const & operator = (QcSv2Tabu const & that);	//!< Assigner.

		void adjustMemAuto();			//!< Adjust memory automatically.
		void updtTabuAuto();			//!< Update tabu automatically.

	private:

		Dim 	mLength;			//!< Length of the tabu.
		qc<Hdl,xmmm> mQueue;	//!< Queue of tabu vars.
};



/*!
	Define a tabu.
*/
inline Typ QcSv2Tabu::def(Hdl const hdlSys, Dim const theLength)
{
	WatchError
	QcSv2Tabu * tTabu = new QcSv2Tabu(hdlSys, theLength);
	if (tTabu->defSysTabu()) return tTabu->TabuTyp;
	delete tTabu;
	return TabuTypNil;
	CatchError
}



/*!
	The constructor.
*/
inline QcSv2Tabu::QcSv2Tabu(Hdl const hdlSys, Dim const theLength) :
	Sv2Tabu(hdlSys), mLength(theLength), mQueue(theLength)
{
	WatchError
	setTabuCls(TabuStub<QcSv2Tabu>::TabuCls);
	mActive = castBll(theLength);
	CatchError
}



/*!
	The destructor.
*/
inline QcSv2Tabu::~QcSv2Tabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	Return the current tabu length.
*/
inline Dim const & QcSv2Tabu::Length() const
{
	WatchError
	return mLength;
	CatchError
}


/*!
	Adjust dynamic memory
*/
inline void QcSv2Tabu::adjustMemAuto()
{
	WatchError
	mQueue.adjustMemAuto();
	Sv2Tabu::adjustMemAuto();
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcSv2Tabu::suit(Tabu const & theTabu)
{
	WatchError
	return theTabu.TabuCls == TabuStub< QcSv2Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcSv2Tabu::suit(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCls == TabuStub< QcSv2Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcSv2Tabu::suit(Tabu & theTabu)
{
	WatchError
	return theTabu.TabuCls == TabuStub< QcSv2Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcSv2Tabu::suit(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCls == TabuStub< QcSv2Tabu >::TabuCls;
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcSv2Tabu const & QcSv2Tabu::cast(Tabu const & theTabu)
{
	WatchError
	Warn(theTabu.TabuCls != TabuStub< QcSv2Tabu >::TabuCls, eWrongCls);
	return scast<QcSv2Tabu const &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcSv2Tabu const * QcSv2Tabu::cast(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCls != TabuStub< QcSv2Tabu >::TabuCls, eWrongCls);

	return scast<QcSv2Tabu const *>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcSv2Tabu & QcSv2Tabu::cast(Tabu & theTabu)
{
	WatchError
	Warn(theTabu.TabuCls != TabuStub< QcSv2Tabu >::TabuCls, eWrongCls);

	return scast<QcSv2Tabu &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcSv2Tabu * QcSv2Tabu::cast(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCls != TabuStub< QcSv2Tabu >::TabuCls, eWrongCls);

	return scast<QcSv2Tabu *>(theTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
inline QcSv2Tabu & QcSv2Tabu::refm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmTabu(TabuStub<Sv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline QcSv2Tabu * QcSv2Tabu::ptrm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmTabu(TabuStub<Sv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Refer to a tabu.
*/
inline QcSv2Tabu const & QcSv2Tabu::refc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcTabu(TabuStub<Sv2Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline QcSv2Tabu const * QcSv2Tabu::ptrc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcTabu(TabuStub<Sv2Tabu>::TabuTyp));
	CatchError
}



closeKangarooSpace



#endif // QcSv2TabuHppIncluded

