/*!
	@file mth.hpp
	@brief The source file for mathmetical functions.
	@details This is the source file for mathmetical functions.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 19.03.2010 QRL NICTA www.nicta.com.au
*/



#ifndef MthHppIncluded
#define MthHppIncluded



#include "cppl/roots/idx.hpp"




openEmuSpace




/*!
	@brief A function to calculate power for integrals.
	@details This function calculates power for integrals.
*/
inline Z calcPow(Z const theBase, Z const theIndex)
{
	WatchError
	if (theBase == 1) return 1;
	Alert(!theBase && theIndex <= 0, ePowerOfZero);

	if (theIndex == 0) return 1;
	if (theIndex < 0) return 0;

	Z tResult = 1, sIndex = 0;
	while (sIndex < theIndex)
	{
		tResult *= theBase;
		++sIndex;
	}

	return tResult;
	CatchError
}





/*!
	@brief A function to calculate power for reals.
	@details This function calculates power for reals.
*/
inline R calcPow(R const theBase, R const theIndex)
{
	WatchError
	R tResult = pow(theBase, theIndex);
	Alert(errno, eMathLibrary);
	return tResult;
	CatchError
}




/*!
	@brief A function to calculate modulus for integrals.
	@details This function calculates modulus for integrals.
*/
inline Z calcMod(Z const theLeft, Z const theRight)
{
	WatchError
	Alert(!theRight, eModulusByZero);
	return theLeft % theRight;
	CatchError
}



/*!
	@brief A function to calculate modulus for reals.
	@details This function calculates modulus for reals.
*/
inline R calcMod(R const theLeft, R const theRight)
{
	WatchError
	R tResult = fmod(theLeft, theRight);
	Alert(errno, eMathLibrary);
	return tResult;
	CatchError
}



closeEmuSpace



#endif // MthHppIncluded
