/*!
	@file hsh.hpp
	@brief The source file for hash functions.
	@details This is the source file for hash functions.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef HshHppIncluded
#define HshHppIncluded



#include "cppl/roots/typ.hpp"
#include "cppl/roots/err.hpp"



openEmuSpace



/*!
	@var typedef Hvl
	@brief A type to represent hash values.
	@details This type represents hash values.
*/
typedef Q Hvl;	// changing this may require changing all hash related codes.



/*!
	@def castHvl(theHvl)
	@brief A macro to cast to Hvl.
	@details This macro casts to Hvl.
*/
#define castHvl(theHvl) (scast<Hvl>(theHvl))




/*!
	@brief Mix the two given hash values.
	@details This function mixes two given hash values.
*/
inline Hvl mixHash(Hvl const theSeed, Hvl const theValue)
{
	WatchError
	return theSeed ^ (theValue + 0x9e3779b9 + (theSeed << 6) + (theSeed >> 2));
	CatchError
}



/*!
	@brief Calculate hash value for C.
	@details This function calculates hash values for C.
*/
inline Hvl calcHash(C const theC)
{
	WatchError
	return castHvl(theC);
	CatchError
}



/*!
	@brief Calculate hash value for B.
	@details This function calculates hash values for B.
*/
inline Hvl calcHash(B const theB)
{
	WatchError
	return castHvl(theB);
	CatchError
}



/*!
	@brief Calculate hash value for S.
	@details This function calculates hash values for S.
*/
inline Hvl calcHash(S const theS)
{
	WatchError
	return castHvl(theS);
	CatchError
}



/*!
	@brief Calculate hash value for D.
	@details This function calculates hash values for D.
*/
inline Hvl calcHash(D const theD)
{
	WatchError
	return castHvl(theD);
	CatchError
}



/*!
	@brief Calculate hash value for Q.
	@details This function calculates hash values for Q.
*/
inline Hvl calcHash(Q const theQ)
{
	WatchError
	return castHvl(theQ);
	CatchError
}




/*!
	@brief Calculate hash value for O.
	@details This function calculates hash values for O.
*/
inline Hvl calcHash(O const theO)
{
	WatchError
	return castHvl(theO);
	CatchError
}




/*!
	@brief Calculate hash value for Z.
	@details This function calculates hash values for Z.
*/
inline Hvl calcHash(Z const theZ)
{
	WatchError
	return castHvl(theZ);
	CatchError
}



/*!
	@brief Calculate hash value for R.
	@details This function calculates hash values for R.
*/
inline Hvl calcHash(R const theR)
{
	WatchError
	union { Hvl mHvl; R mR; } tUnion;
	tUnion.mR = theR;
	return tUnion.mHvl;
	CatchError
}



/*!
	@brief Calculate hash value for cstrings.
	@details This function calculates hash values for cstrings.
*/

inline Hvl calcHash(C const * theCs)
{
	WatchError
	Hvl tHvl = 0;
	while(*theCs)
	{
		tHvl = mixHash(tHvl, calcHash(*theCs));
		++theCs;
	}
	return tHvl;
	CatchError
}



/*!
 @brief Calculate hash value for c++ strings.
 @details This function calculates hash values for c++ strings.
 */

inline Hvl calcHash(string const * theStr)
{
	WatchError
	return calcHash( theStr->c_str() );
	CatchError
}



/*!
 @brief Calculate hash value for c++ strings.
 @details This function calculates hash values for c++ strings.
 */

inline Hvl calcHash(string const & theStr)
{
	WatchError
	return calcHash( theStr.c_str() );
	CatchError
}



/*!
	@brief Calculate hash value for pointers.
	@details This function calculates hash values for pointers.
*/

inline Hvl calcHash(Nil * thePtr)
{
	WatchError
	union { Hvl tHvl; Nil * tPtr; };
	tPtr = thePtr;
	return tHvl;
	CatchError
}




/*!
	@class hashval
	@brief A class to represent hash functions.
	@details This class represents hash functions.
*/
template <typename elem> class hashval
{
	public:
		/*!
			@brief A function to implement the hash function.
			@details This function implements the hash function.
		*/
		static Hvl iof(elem const theElem)
		{
			WatchError
			return calcHash(theElem);
			CatchError
		}
};



/*!
	@def hv
	@brief A macro to denote hashval.
	@details This macro denotes hashval.
*/
#define hv hashval



closeEmuSpace



#endif // HshHppIncluded
