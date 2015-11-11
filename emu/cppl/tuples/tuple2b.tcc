/*!
	@file tuple2b.tcc
	@brief The source file for tuple2b template class.
	@details This is the source file for tuple2b template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
	@see tuple2b.tcc
*/



#ifndef Tuple2bTccIncluded
#define Tuple2bTccIncluded



#include "cppl/roots/idx.hpp"
#include "cppl/tuples/tuple2.tcc"



openEmuSpace



/*!
	@class tuple2b
	@brief A class to represent binary tuples having relational operators that consider both of the components.
	@details This class represents binary tuples having relational operators that consider both of the components.
*/
template <typename dat1, typename dat2>
class tuple2b : public tuple2<dat1,dat2>
{
	public:
		~tuple2b();												//!< Destructor.
		tuple2b();												//!< Constructor.
		tuple2b(dat1 const & theDat1, dat2 const & theDat2);	//!< Initialiser.
		tuple2b(tuple2b<dat1,dat2> const & that);				//!< Duplicator.
		tuple2b<dat1,dat2> const & operator =
							(tuple2b<dat1,dat2> const & that);	//!< Assigner.

		/*! @name Relations */
		//! @{

		Bll operator == (tuple2b<dat1,dat2> const & that) const;//!< Equal-to.
		Bll operator != (tuple2b<dat1,dat2> const & that) const;//!< Not-equal.
		Bll operator < (tuple2b<dat1,dat2> const & that) const;	//!< Less-than.
		Bll operator <= (tuple2b<dat1,dat2> const & that) const;//!< Less-equal.
		Bll operator > (tuple2b<dat1,dat2> const & that) const;	//!< Greater-than.
		Bll operator >= (tuple2b<dat1,dat2> const & that) const;//!< Greater-equal.

		//! @}
};



/*!
	@def t2b
	@brief A macro to denote tuple2b.
	@details This macro denotes tuple2b.
*/
#define t2b tuple2b



/*!
	The constructor.
*/
template <typename dat1, typename dat2>
inline tuple2b<dat1,dat2>::tuple2b()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
template <typename dat1, typename dat2>
inline tuple2b<dat1,dat2>::tuple2b(dat1 const & theDat1, dat2 const & theDat2) :
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
inline tuple2b<dat1,dat2>::tuple2b(tuple2b<dat1,dat2> const & that) :
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
inline tuple2b<dat1,dat2> const & tuple2b<dat1,dat2>::operator =
		(tuple2b<dat1,dat2> const & that)
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
inline tuple2b<dat1,dat2>::~tuple2b()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The equal-to operator that considers both components.
*/
template <typename dat1, typename dat2>
inline Bll tuple2b<dat1,dat2>::operator == (tuple2b<dat1,dat2> const & that) const
{
	WatchError
	return this->First == that.First && this->Second == that.Second;
	CatchError
}



/*!
	The not-equal operator that considers both components.
*/
template <typename dat1, typename dat2>
inline Bll tuple2b<dat1,dat2>::operator != (tuple2b<dat1,dat2> const & that) const
{
	WatchError
	return this->First != that.First || this->Second != that.Second;
	CatchError
}



/*!
	The less-than operator that considers both components.
*/
template <typename dat1, typename dat2>
inline Bll tuple2b<dat1,dat2>::operator < (tuple2b<dat1,dat2> const & that) const
{
	WatchError
	return this->First < that.First || (this->First == that.First && this->Second < that.Second);
	CatchError
}



/*!
	The less-equal operator that considers both components.
*/
template <typename dat1, typename dat2>
inline Bll tuple2b<dat1,dat2>::operator <= (tuple2b<dat1,dat2> const & that) const
{
	WatchError
	return this->First < that.First || (this->First == that.First && this->Second <= that.Second);
	CatchError
}



/*!
	The greater-than operator that considers both components.
*/
template <typename dat1, typename dat2>
inline Bll tuple2b<dat1,dat2>::operator > (tuple2b<dat1,dat2> const & that) const
{
	WatchError
	return this->First > that.First || (this->First == that.First && this->Second > that.Second);
	CatchError
}



/*!
	The greater-equal operator that considers both components.
*/
template <typename dat1, typename dat2>
inline Bll tuple2b<dat1,dat2>::operator >= (tuple2b<dat1,dat2> const & that) const
{
	WatchError
	return this->First > that.First || (this->First == that.First && this->Second >= that.Second);
	CatchError
}



closeEmuSpace



#endif // Tuple2bTccIncluded
