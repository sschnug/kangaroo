/*!
	@file tuple4.tcc
	@brief The source file for tuple4 template class.
	@details This is the source file for tuple4 template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
	@see tuple4.tcc
*/



#ifndef Tuple4TccIncluded
#define Tuple4TccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class tuple4
	@brief A class to represent quaternary tuples.
	@details This class represents quaternary tuples.
		This class has no operators or methods.
*/
template <typename dat1, typename dat2, typename dat3, typename dat4>
class tuple4
{
	public:
		tuple4();													//!< Constructor.
		~tuple4();													//!< Destructor.
		tuple4(tuple4<dat1,dat2,dat3,dat4> const & that);			//!< Duplicator.
		tuple4(dat1 const & theDat1, dat2 const & theDat2,
					dat3 const & theDat3, dat4 const & theDat4);	//!< Initialiser.
		tuple4<dat1,dat2,dat3,dat4> const & operator =
					(tuple4<dat1,dat2,dat3,dat4> const & that);		//!< Assigner.

		dat1 First;		//!< First component.
		dat2 Second;	//!< Second component.
		dat3 Third;		//!< Third component.
		dat4 Fourth;	//!< Fourth component.
};



/*!
	@def t4
	@brief A macro to denote tuple4.
	@details This macro denotes tuple4.
*/
#define t4 tuple4



/*!
	The constructor.
*/
template <typename dat1, typename dat2, typename dat3, typename dat4>
inline tuple4<dat1,dat2,dat3,dat4>::tuple4()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
template <typename dat1, typename dat2, typename dat3, typename dat4>
inline tuple4<dat1,dat2,dat3,dat4>::tuple4(dat1 const & theDat1,
		dat2 const & theDat2, dat3 const & theDat3, dat4 const & theDat4) :
			First(theDat1), Second(theDat2), Third(theDat3), Fourth(theDat4)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
template <typename dat1, typename dat2, typename dat3, typename dat4>
inline tuple4<dat1,dat2,dat3,dat4>::tuple4(tuple4<dat1,dat2,dat3,dat4> const & that) :
		First(that.First), Second(that.Second), Third(that.Third), Fourth(that.Fourth)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
template <typename dat1, typename dat2, typename dat3, typename dat4>
inline tuple4<dat1,dat2,dat3,dat4> const & tuple4<dat1,dat2,dat3,dat4>::operator =
			(tuple4<dat1,dat2,dat3,dat4> const & that)
{
	WatchError
	if (this == &that)
		return *this;

	First = that.First;
	Second = that.Second;
	Third = that.Third;
	Fourth = that.Fourth;

	return *this;
	CatchError
}



/*!
	The destructor.
*/
template <typename dat1, typename dat2, typename dat3, typename dat4>
inline tuple4<dat1,dat2,dat3,dat4>::~tuple4()
{
	WatchError
	//	nothing to be done.
	CatchError
}



closeEmuSpace



#endif // Tuple4TccIncluded
