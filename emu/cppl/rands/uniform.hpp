/*!
	@file uniform.hpp
	@brief The source file for uniform random variate functions.
	@details This is the source file for uniform random variate functions.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 23.1.2009 QRL NICTA www.nicta.com.au
*/



#ifndef UniformHppIncluded
#define UniformHppIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	Return a random boolean value.
*/
inline Bll uniform(Rnd & theRnd)
{
	WatchError
	return theRnd() & 1;
	CatchError
}



/*!
	Return a random countable from [0, OpenLimit).
	If OpenLimit is Zero, return from the whole range possible.
*/
inline N uniform(Rnd & theRnd, N const OpenLimit)
{
	WatchError
	if (!OpenLimit) return theRnd();

	Rns const tLimit = DnzLim<Rns>::Max - (DnzLim<Rns>::Max % OpenLimit);
	Rns tCurr = theRnd();
	while (tCurr >= tLimit)
		tCurr = theRnd();
	return tCurr % OpenLimit;
	CatchError
}



/*!
	Return a random countable from [CloseLeft, ClosedRight].
	If the resultant range is Zero due to wrap-around,
	return from the whole range possible.
*/
inline N uniform(Rnd & theRnd, N const ClosedLeft, N const ClosedRight)
{
	WatchError
	Warn(ClosedLeft > ClosedRight, eInvalidRange);

	Rns const tRange = ClosedRight - ClosedLeft + 1;
	if (!tRange) return theRnd() + ClosedLeft;

	Rns const tLimit = DnzLim<Rns>::Max - (DnzLim<Rns>::Max % tRange);
	Rns tCurr = theRnd();
	while (tCurr >= tLimit)
		tCurr = theRnd();
	return tCurr % tRange + ClosedLeft;

	CatchError
}




/*!
	Return a random integer from [CloseLeft, ClosedRight].
	If the resultant range is Zero due to wrap-around,
	return from the whole range possible.
*/
inline Z uniform(Rnd & theRnd, Z const ClosedLeft, Z const ClosedRight)
{
	WatchError
	Warn(ClosedLeft > ClosedRight, eInvalidRange);

	Rns const tRange = ClosedRight - ClosedLeft + 1;
	if (!tRange) return theRnd() + ClosedLeft;

	Rns const tLimit = DnzLim<Rns>::Max - (DnzLim<Rns>::Max % tRange);
	Rns tCurr = theRnd();
	while (tCurr >= tLimit)
		tCurr = theRnd();
	return tCurr % tRange + ClosedLeft;
	CatchError
}




/*!
	Return a random real from [CloseLeft, ClosedRight].
*/
inline R uniform(Rnd & theRnd, R const ClosedLeft, R const ClosedRight)
{
	WatchError
	Warn(ClosedLeft > ClosedRight, eInvalidRange);
	return ClosedLeft + (ClosedRight - ClosedLeft) / DnzLim<Rns>::Max * theRnd();
	CatchError
}



closeEmuSpace



#endif // UniformHppIncluded
