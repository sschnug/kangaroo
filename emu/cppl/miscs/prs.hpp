/*!
	@file prs.hpp
	@brief The prototype file for parsers.
	@details This is the prototype file for parsers.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 19.03.2010 QRL NICTA www.nicta.com.au
*/



#ifndef PrsHppIncluded
#define PrsHppIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@fn B parseB(Cs const theCs)
	@brief A function to parse a string to get a boolean value.
	@details This function parses a string to get a boolean value.
*/
inline B parseB(Cs const theCs)
{
	WatchError
	Warn(!theCs || *theCs || *(theCs + 1), eParseBoolean);

	switch(*theCs)
	{
		case '1' : case 't' : case 'y' :
		case 'T' : case 'Y' : return true;

		case '0' : case 'f' : case 'n' :
		case 'F' : case 'N' : return false;

		default: Throw(eParseBoolean);
	}
	CatchError
}






/*!
	@fn N parseN(Cs const theCs)
	@brief A function to parse a string to get a natural number.
	@details This function parses a string to get a natural number.
*/
inline N parseN(Cs const theCs)
{
	WatchError
	#if CheckError
		Warn(!theCs || !*theCs, eParseNatural);

		C const * tStr = theCs;
		while(*tStr && *tStr >= '0' && *tStr <= '9') ++tStr;

		Warn(*tStr, eParseNatural);
	#endif
	return prsfN(theCs);
	CatchError
}






/*!
	@fn Z parseZ(Cs const theCs)
	@brief A function to parse a string to get an integer value.
	@details This function parses a string to get an integer value.
*/
inline Z parseZ(Cs const theCs)
{
	WatchError
	#if CheckError
		Warn(!theCs || !*theCs, eParseIntegral);

		C const * tStr = theCs;
		if (*tStr && (*tStr == '-' || *tStr == '+')) ++tStr;
		while(*tStr && *tStr >= '0' && *tStr <= '9') ++tStr;

		Warn(*tStr, eParseIntegral);
	#endif
	return prsfZ(theCs);
	CatchError
}



/*!
	@fn R parseR(Cs const theCs)
	@brief A function to parse a string to get a real value.
	@details This function parses a string to get a real value.
*/
inline R parseR(Cs const theCs)
{
	WatchError
	#if CheckError
		Warn(!theCs || !*theCs, eParseReal);

		C const * tStr = theCs;
		if (*tStr && (*tStr == '-' || *tStr == '+')) ++tStr;
		while(*tStr && *tStr >= '0' && *tStr <= '9') ++tStr;
		if (*tStr && *tStr == '.') ++tStr;
		while(*tStr && *tStr >= '0' && *tStr <= '9') ++tStr;

		Warn(tStr == theCs, eParseReal);

		if (*tStr && *tStr == 'e')
		{
			++tStr;
			if (*tStr && (*tStr == '-' || *tStr == '+')) ++tStr;
			while(*tStr && *tStr >= '0' && *tStr <= '9') ++tStr;
		}

		Warn(*tStr,  eParseReal);
	#endif

	return prsfR(theCs);
	CatchError
}


closeEmuSpace



#endif // PrsHppIncluded
