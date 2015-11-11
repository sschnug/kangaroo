/*!
	@file tuple2a.tcc
	@brief The source file for tuple2a template class.
	@details This is the source file for tuple2a template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
	@see biple.tcc
*/



#ifndef Tuple2aTccIncluded
#define Tuple2aTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class tuple2a
	@brief A class to represent binary tuples having relational operators that consider only the first component.
	@details This class represents binary tuples having relational operators that consider only the first component.
*/
template <typename dat1, typename dat2>
class tuple2a : public tuple2<dat1,dat2>
{
	public:
		~tuple2a();												//!< Destructor.
		tuple2a();												//!< Constructor.
		tuple2a(dat1 const & theDat1, dat2 const & theDat2);	//!< Initialiser.
		tuple2a(tuple2a<dat1,dat2> const & that);				//!< Duplicator.
		tuple2a<dat1,dat2> const & operator =
							(tuple2a<dat1,dat2> const & that);	//!< Assigner.

		/*! @name Relations */
		//! @{

		Bll operator == (tuple2a<dat1,dat2> const & that) const;	//!< Equal-to.
		Bll operator != (tuple2a<dat1,dat2> const & that) const;	//!< Not equal.
		Bll operator < (tuple2a<dat1,dat2> const & that) const;		//!< Less-than.
		Bll operator <= (tuple2a<dat1,dat2> const & that) const;	//!< Less-equal.
		Bll operator > (tuple2a<dat1,dat2> const & that) const;		//!< Greater-than.
		Bll operator >= (tuple2a<dat1,dat2> const & that) const;	//!< Greater-equal.

		//! @}
};



/*!
	@def t2a
	@brief A macro to denote tuple2a.
	@details This macro denotes tuple2a.
*/
#define t2a tuple2a



/*!
	The constructor.
*/
template <typename dat1, typename dat2>
inline tuple2a<dat1,dat2>::tuple2a()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
template <typename dat1, typename dat2>
inline tuple2a<dat1,dat2>::tuple2a(dat1 const & theDat1, dat2 const & theDat2) :
		tuple2<dat1,dat2>(theDat1, theDat2)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
template <typename dat1, typename dat2>
inline tuple2a<dat1,dat2>::tuple2a(tuple2a<dat1,dat2> const & that) :
		tuple2<dat1,dat2>(that)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
template <typename dat1, typename dat2>
inline tuple2a<dat1,dat2> const & tuple2a<dat1,dat2>::operator =
			(tuple2a<dat1,dat2> const & that)
{
	WatchError
	if (this == &that)
		return *this;

	tuple2<dat1,dat2>::operator =(that);

	return *this;
	CatchError
}



/*!
	The destructor.
*/
template <typename dat1, typename dat2>
inline tuple2a<dat1,dat2>::~tuple2a()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The equal-to operator that considers only the first component.
*/
template <typename dat1, typename dat2>
inline Bll tuple2a<dat1,dat2>::operator == (tuple2a<dat1,dat2> const & that) const
{
	WatchError
	return this->First == that.First;
	CatchError
}



/*!
	The not-equal operator that considers only the first component.
*/
template <typename dat1, typename dat2>
inline Bll tuple2a<dat1,dat2>::operator != (tuple2a<dat1,dat2> const & that) const
{
	WatchError
	return this->First != that.First;
	CatchError
}



/*!
	The less-than operator that considers only the first component.
*/
template <typename dat1, typename dat2>
inline Bll tuple2a<dat1,dat2>::operator < (tuple2a<dat1,dat2> const & that) const
{
	WatchError
	return this->First < that.First;
	CatchError
}



/*!
	The less-equal operator that considers only the first component.
*/
template <typename dat1, typename dat2>
inline Bll tuple2a<dat1,dat2>::operator <= (tuple2a<dat1,dat2> const & that) const
{
	WatchError
	return this->First <= that.First;
	CatchError
}



/*!
	The greater-than operator that considers only the first component.
*/
template <typename dat1, typename dat2>
inline Bll tuple2a<dat1,dat2>::operator > (tuple2a<dat1,dat2> const & that) const
{
	WatchError
	return this->First > that.First;
	CatchError
}



/*!
	The greater-equal operator that considers only the first component.
*/
template <typename dat1, typename dat2>
inline Bll tuple2a<dat1,dat2>::operator >= (tuple2a<dat1,dat2> const & that) const
{
	WatchError
	return this->First >= that.First;
	CatchError
}



closeEmuSpace



#endif // Tuple2aTccIncluded
