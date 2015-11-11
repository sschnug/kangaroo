/*!
	@file qcsv0tabu.hpp
	@brief The prototype file for QcSv0Tabu class.
	@details This is the prototype file for QcSv0Tabu class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
*/



#ifndef QcSv0TabuHppIncluded
#define QcSv0TabuHppIncluded



#include "cbls/tabus/reg.hh"
#include "cbls/tabus/svtabus/sv0tabu.hpp"



openKangarooSpace



/*!
	@class QcSv0Tabu
	@brief A class to represent single tabu variables with no callbacks by using circular queues.
	@details This class represents single tabu variable with no callbacks by using circular queues.
*/
class QcSv0Tabu : public Sv0Tabu
{
	public:

		static Typ def(Hdl const hdlSys, Dim const theLength);	//!< Definition.

		//! @name Access
		//! @{

		static QcSv0Tabu & refm(Hdl const hdlSys);			//!< Reference.
		static QcSv0Tabu * ptrm(Hdl const hdlSys);			//!< Pointer.
		static QcSv0Tabu const & refc(Hdl const hdlSys);	//!< Reference.
		static QcSv0Tabu const * ptrc(Hdl const hdlSys);	//!< Pointer.

		//! @}

		//! @name Casting
		//! @{

		static QcSv0Tabu const & cast(Tabu const & theTabu);	//!< Perform casting.
		static QcSv0Tabu const * cast(Tabu const * theTabu);	//!< Perform casting.
		static QcSv0Tabu & cast(Tabu & theTabu);				//!< Perform casting.
		static QcSv0Tabu * cast(Tabu * theTabu);				//!< Perform casting.

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

		~QcSv0Tabu();											//!< Destructor.
		QcSv0Tabu(QcSv0Tabu const & that);						//!< Duplicator.
		QcSv0Tabu(Hdl const hdlSys, Dim const theLength);		//!< Initialiser.
		QcSv0Tabu const & operator = (QcSv0Tabu const & that);	//!< Assigner.

		void adjustMemAuto();			//!< Adjust memory automatically.
		void updtTabuAuto();			//!< Update tabu automatically.

	private:

		Dim 	mLength;				//!< Length of the tabu.
		qc<Hdl,xmmm> mQueue;			//!< Queue of tabu vars.
};



/*!
	Define a tabu.
*/
inline Typ QcSv0Tabu::def(Hdl const hdlSys, Dim const theLength)
{
	WatchError
	QcSv0Tabu * tTabu = new QcSv0Tabu(hdlSys, theLength);
	if (tTabu->defSysTabu()) return tTabu->TabuTyp;
	delete tTabu;
	return TabuTypNil;
	CatchError
}



/*!
	The constructor.
*/
inline QcSv0Tabu::QcSv0Tabu(Hdl const hdlSys, Dim const theLength) :
			Sv0Tabu(hdlSys), mLength(theLength), mQueue(mLength)
{
	WatchError
	setTabuCls(TabuStub<QcSv0Tabu>::TabuCls);
	mActive = castBll(theLength);
	CatchError
}



/*!
	The destructor.
*/
inline QcSv0Tabu::~QcSv0Tabu()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	Return the current tabu length.
*/
inline Dim const & QcSv0Tabu::Length() const
{
	WatchError
	return mLength;
	CatchError
}


/*!
	Adjust dynamic memory
*/
inline void QcSv0Tabu::adjustMemAuto()
{
	WatchError
	mQueue.adjustMemAuto();
	Sv0Tabu::adjustMemAuto();
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcSv0Tabu::suit(Tabu const & theTabu)
{
	WatchError
	return theTabu.TabuCls == TabuStub< QcSv0Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcSv0Tabu::suit(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCls == TabuStub< QcSv0Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcSv0Tabu::suit(Tabu & theTabu)
{
	WatchError
	return theTabu.TabuCls == TabuStub< QcSv0Tabu >::TabuCls;
	CatchError
}



/*!
	Whether a tabu is suitable for casting.
*/
inline Bll QcSv0Tabu::suit(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);

	return theTabu->TabuCls == TabuStub< QcSv0Tabu >::TabuCls;
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcSv0Tabu const & QcSv0Tabu::cast(Tabu const & theTabu)
{
	WatchError
	Warn(theTabu.TabuCls != TabuStub< QcSv0Tabu >::TabuCls, eWrongCls);
	return scast<QcSv0Tabu const &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcSv0Tabu const * QcSv0Tabu::cast(Tabu const * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCls != TabuStub< QcSv0Tabu >::TabuCls, eWrongCls);

	return scast<QcSv0Tabu const *>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcSv0Tabu & QcSv0Tabu::cast(Tabu & theTabu)
{
	WatchError
	Warn(theTabu.TabuCls != TabuStub< QcSv0Tabu >::TabuCls, eWrongCls);

	return scast<QcSv0Tabu &>(theTabu);
	CatchError
}



/*!
	Perform casting of a tabu.
*/
inline QcSv0Tabu * QcSv0Tabu::cast(Tabu * theTabu)
{
	WatchError
	Warn(!theTabu, eNullPointer);
	Warn(theTabu->TabuCls != TabuStub< QcSv0Tabu >::TabuCls, eWrongCls);

	return scast<QcSv0Tabu *>(theTabu);
	CatchError
}



/*!
	Refer to a tabu.
*/
inline QcSv0Tabu & QcSv0Tabu::refm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refm(hdlSys).refmTabu(TabuStub<Sv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline QcSv0Tabu * QcSv0Tabu::ptrm(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrm(hdlSys)->ptrmTabu(TabuStub<Sv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Refer to a tabu.
*/
inline QcSv0Tabu const & QcSv0Tabu::refc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::refc(hdlSys).refcTabu(TabuStub<Sv0Tabu>::TabuTyp));
	CatchError
}



/*!
	Point to a tabu.
*/
inline QcSv0Tabu const * QcSv0Tabu::ptrc(Hdl const hdlSys)
{
	WatchError
	return cast(Sys::ptrc(hdlSys)->ptrcTabu(TabuStub<Sv0Tabu>::TabuTyp));
	CatchError
}



closeKangarooSpace



#endif // QcSv0TabuHppIncluded
