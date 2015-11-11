/*!
	@file tuple2.tcc
	@brief The source file for tuple2 template class.
	@details This is the source file for tuple2 template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
	@see tuple2.tcc
*/



#ifndef Tuple2TccIncluded
#define Tuple2TccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class tuple2
	@brief A class to represent binary tuples.
	@details This class represents binary tuples.
*/
template <typename dat1, typename dat2>
class tuple2
{
	public:


		~tuple2();												//!< Destructor.
		tuple2();												//!< Constructor.
		tuple2(dat1 const & theDat1, dat2 const & theDat2);		//!< Initialiser.
		tuple2(tuple2<dat1,dat2> const & that);					//!< Duplicator.
		tuple2<dat1,dat2> const & operator =
							(tuple2<dat1,dat2> const & that);	//!< Assigner.

		/*! @name Copying */
		//! @{

		void copy(dat1 const & theDat1, dat2 const & theDat2);	//!< Copy data.

		//! @}

		dat1 First;		//!< First component.
		dat2 Second;	//!< Second component.
};



/*!
	@def t2
	@brief A macro to denote tuple2.
	@details This macro denotes tuple2.
*/
#define t2 tuple2




/*!
	The constructor.
*/
template <typename dat1, typename dat2>
inline tuple2<dat1,dat2>::tuple2()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
template <typename dat1, typename dat2>
inline tuple2<dat1,dat2>::tuple2(dat1 const & theDat1, dat2 const & theDat2) :
		First(theDat1), Second(theDat2)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
template <typename dat1, typename dat2>
inline tuple2<dat1,dat2>::tuple2(tuple2<dat1,dat2> const & that) :
		First(that.First), Second(that.Second)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
template <typename dat1, typename dat2>
inline tuple2<dat1,dat2> const & tuple2<dat1,dat2>::operator =
		(tuple2<dat1,dat2> const & that)
{
	WatchError
	if (this == &that)
		return *this;

	First = that.First;
	Second = that.Second;

	return *this;
	CatchError
}



/*!
	The destructor.
*/
template <typename dat1, typename dat2>
inline tuple2<dat1,dat2>::~tuple2()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Copy given data to the tuple2.
*/
template <typename dat1, typename dat2>
inline void tuple2<dat1,dat2>::copy(dat1 const & theDat1, dat2 const & theDat2)
{
	WatchError
	First = theDat1;
	Second = theDat2;
	CatchError
}



closeEmuSpace



#endif // Tuple2TccIncluded
