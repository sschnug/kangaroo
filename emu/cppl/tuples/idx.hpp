/*!
	@file tuples/idx.hpp
	@brief The index header file for template tuples.
	@details This is the index header file for template tuples.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef TuplesIdxHppIncluded
#define TuplesIdxHppIncluded



#include "cppl/tuples/tuple2.tcc"		//	Binary tuples with no operators or mehtods.
#include "cppl/tuples/tuple2a.tcc"		//	Binary tuples with relational operators that consider only the first(a) component.
#include "cppl/tuples/tuple2b.tcc"		//	Binary tuples with relational operators that consider (b)oth of the components.

#include "cppl/tuples/tuple3.tcc"		//	Ternary tuples with no operators or methods.
#include "cppl/tuples/tuple4.tcc"		//	Quaternary tuples with no operators or methods.



#endif // TuplesIdxHppIncluded
