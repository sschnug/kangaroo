/*!
	@file cppl/lib.hpp
	@brief The header file to list external libraries.
	@details This is the header file to list external libraries.
		All external links are to be included in this file in
		order to track them easily. Do not include external
		dependency links at any other files of the project.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 01.01.2013 QRL NICTA www.nicta.com.au
*/



#ifndef CpplLibHppIncluded
#define CpplLibHppIncluded



/*
	Standard iostream.
*/
#include <cstdio>
#include <iostream>
using std::cout;		//	Console output.
using std::cin;			//	Console input.
using std::cerr;		//	Console error.
using std::endl;		//	End of line.



/*
	String class from the Standard Template Library.
	The use of std::string class is discouraged.
	Whenever possible, pass char * and size as
	parameters at any interface points.
*/
#include <string>
#include <cstring>
using std::string;



/*
	String stream class from the Standard Template Library.
*/
#include <sstream>
/*!
	@def sstream
	@brief String stream.
	@details The string stream.
*/
#define sstream std::stringstream



/*
	File stream class from the Standard Template Library.
*/
#include <fstream>




/*
	Standard library from c.
*/
#include <cstdlib>
#include <cstdint>


/*!
	@def ExitOnSuccess
	@brief Exit from program on success.
	@details Exit from the program on success.
*/
#define ExitOnSuccess EXIT_SUCCESS



/*!
	@def ExitOnFailure
	@brief Exit from program on failure.
	@details Exit from the program on failure.
*/
#define ExitOnFailure EXIT_FAILURE



/*
	Various data type limits.
	These files are included to
	use them in defining limits
	for emu defined types.
*/
#include <cfloat>
#include <climits>



/*
	Math functions from standard c library.
*/
#include <cmath>
using std::pow;				//	Power function.
using std::abs;				//	Absolute function.
using std::sin;				//	Sine function.
using std::asin;			//	Arc-sine function.
using std::sinh;			//	Hyperbolic sine function.
//using std::asinh;			//	Hyperbolic arc-sine function.
using std::cos;				//	Cosine function.
using std::acos;			//	Arc-cosine function.
using std::cosh;			//	Hyperbolic cosine function.
//using std::acosh;			//	Hyperbolic arc-cosine function.
using std::tan;				//	Tangent function.
using std::atan;			//	Arc-tangent function.
using std::tanh;			//	Hyperbolic tangent function.
//using std::atanh;			//	Hyperbolic arc-tangent function.
using std::exp;				//	Exponential function.
using std::log;				//	Logarithm function.
using std::log10;			//	Logarithm10 function.
//using std::log2;			//	Logarithm2 function.
using std::sqrt;			//	Square-root function.



/*
	Error functions from standard c library.
	Emu has its own assert mechansim through
	Alert and Warn defined in cppl/err.hpp.
	Usage of these things are discouraged.
*/
#include <cerrno>
#include <cassert>



/*
	Various algorithms from the Standard Template Library.
*/
#include <algorithm>
using std::min;				//	Find the minimum of two values.
using std::max;				//	Find the maximum of two values.
using std::sort;			//	Sort items in a given sized array.



/*
	Required in time functions.
*/
#include "sys/resource.h"
#include "sys/times.h"
#include "sys/time.h"
#include <ctime>
#include <unistd.h>



#endif // CpplLibHppIncluded
