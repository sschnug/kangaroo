/**
 * Authors: 
 *     Duc Nghia Pham <duc-nghia.pham@nicta.com.au>
 *     Hakim Newton   <hakim.newton@nicta.com.au>
 */


#ifndef __KANGAROO_FLATZINC_DEFS__HH__
#define __KANGAROO_FLATZINC_DEFS__HH__

#include <sstream>
#include <string>
#include <cstring>

namespace FlatZinc {

	enum obj_t {
		KFZ_PAR,
		KFZ_VAR
	};
	
	enum spec_t {
		KFZ_ANY,
		KFZ_BOOL,
		KFZ_INT,
		KFZ_FLOAT,
		KFZ_IRANGE,
		KFZ_ISET,
		KFZ_ID,
		KFZ_ARRAY,
		KFZ_ANNOTATION,
		KFZ_STRING,
		KFZ_HDL
	};
	
	enum term_t {
		KFZ_VARIABLE,
		KFZ_ARRAYVARS,
		KFZ_CONSTRAINT
	};
	
	enum method_t {
		KFZ_SAT, //< Solve as satisfaction problem
		KFZ_MIN, //< Solve as minimization problem
		KFZ_MAX  //< Solve as maximization problem
	};
	
	inline
	std::string* elem_id(char* st, int n) {
		std::stringstream ss;
		ss << st << "[" << n << "]";
		return ( new std::string(ss.str()) );
	}
	
	inline
	std::string elem_id(std::string& st, int n) {
		std::stringstream ss;
		ss << st << "[" << n << "]";
		return ss.str();
	}
	
}

#endif
			