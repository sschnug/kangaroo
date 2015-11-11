/*!
	@file arg.hpp
	@brief The prototype file for Arg class.
	@details This is the prototype file for Arg class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 03.01.2010 QRL NICTA www.nicta.com.au
	@see arg.cpp
*/



#ifndef ArgHppIncluded
#define ArgHppIncluded



#include "cbls/frames/dat.hpp"



openKangarooSpace



/*
	Forward declaration.
*/
class Func;



/*!
	@class Arg
	@brief A class to represent arguments.
	@details This class represents arguments. An argument is an
		appearance of a term as a parameter in its dependent term.
		The appearance comprises the dependent term and the position
		of the term as a parameter in the dependent.
*/
class Arg
{
	public:

		~Arg();										//!< Destructor.
		Arg();										//!< Constructor.
		Arg(Arg const & that);						//!< Duplicator.
		Arg(Func * theFunc, Pos const thePos);		//!< Initialiser.
		Arg const & operator = (Arg const & that);	//!< Assigner.

		Bll valid() const;							//!< Valid?

	public:

		Func * const ArgFunc;						//!< Function.
		Pos const ArgPos;							//!< Position.
};



/*!
	The constructor.
*/
inline Arg::Arg() : ArgFunc(Null), ArgPos(0)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
inline Arg::Arg(Func * theFunc, Pos const thePos) :
		ArgFunc(theFunc), ArgPos(thePos)
{
	WatchError
	Warn(!theFunc, eNullPointer);
	CatchError
}



/*!
	The destructor.
*/
inline Arg::~Arg()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Return whether valid. An argument is invalid when its function component is null.
*/
inline Bll Arg::valid() const
{
	WatchError
	return ArgFunc;
	CatchError
}



closeKangarooSpace



#endif // ArgHppIncluded
