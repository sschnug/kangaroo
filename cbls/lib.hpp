/*!
	@file cbls/lib.hpp
	@brief The header file for standard libraries.
	@details This is the header file for standard libraries.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 01.12.2011 QRL NICTA www.nicta.com.au
*/



#ifndef CblsLibHppIncluded
#define CblsLibHppIncluded



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
	Include emu library.
*/
#include "cppl/idx.hpp"
using namespace emu;



#endif // CblsLibHppIncluded
