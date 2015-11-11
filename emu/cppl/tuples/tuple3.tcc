/*!
	@file tuple3.tcc
	@brief The source file for tuple3 template class.
	@details This is the source file for tuple3 template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
	@see tuple3.tcc
*/



#ifndef Tuple3TccIncluded
#define Tuple3TccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class tuple3
	@brief A class to represent ternary tuples.
	@details This class represents ternary tuples.
		This class has no operators or methods.
*/
template <typename dat1, typename dat2, typename dat3>
class tuple3
{
	public:
		tuple3();											//!< Constructor.
		~tuple3();											//!< Destructor.
		tuple3(tuple3<dat1,dat2,dat3> const & that);		//!< Duplicator.
		tuple3(dat1 const & theDat1, dat2 const & theDat2,
					dat3 const & theDat3);					//!< Initialiser.
		tuple3<dat1,dat2,dat3> const & operator =
					(tuple3<dat1,dat2,dat3> const & that);	//!< Assigner.

		dat1 First;		//!< First component.
		dat2 Second;	//!< Second component.
		dat3 Third;		//!< Third component.
};



/*!
	@def t3
	@brief A macro to denote tuple3.
	@details This macro denotes tuple3.
*/
#define t3 tuple3



/*!
	The constructor.
*/
template <typename dat1, typename dat2, typename dat3>
inline tuple3<dat1,dat2,dat3>::tuple3()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
template <typename dat1, typename dat2, typename dat3>
inline tuple3<dat1,dat2,dat3>::tuple3(dat1 const & theDat1, dat2 const & theDat2,
		dat3 const & theDat3) : First(theDat1), Second(theDat2), Third(theDat3)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
template <typename dat1, typename dat2, typename dat3>
inline tuple3<dat1,dat2,dat3>::tuple3(tuple3<dat1,dat2,dat3> const & that) :
		First(that.First), Second(that.Second), Third(that.Third)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
template <typename dat1, typename dat2, typename dat3>
inline tuple3<dat1,dat2,dat3> const & tuple3<dat1,dat2,dat3>::operator =
			(tuple3<dat1,dat2,dat3> const & that)
{
	WatchError
	if (this == &that)
		return *this;

	First = that.First;
	Second = that.Second;
	Third = that.Third;

	return *this;
	CatchError
}



/*!
	The destructor.
*/
template <typename dat1, typename dat2, typename dat3>
inline tuple3<dat1,dat2,dat3>::~tuple3()
{
	WatchError
	//	nothing to be done.
	CatchError
}



closeEmuSpace



#endif // Tuple3TccIncluded
