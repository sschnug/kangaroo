/**
 * Authors:
 *     Duc Nghia Pham <duc-nghia.pham@nicta.com.au>
 *     Hakim Newton   <hakim.newton@nicta.com.au>
 */


#ifndef __KANGAROO_FLATZINC_TYPESPEC__HH__
#define __KANGAROO_FLATZINC_TYPESPEC__HH__

//#include "cbls/globals/idx.hh"
//#include "cbls/structs/idx.hh"

#include "defs.hpp"

using namespace kangaroo;

namespace FlatZinc {

	/* Unsupported types */
/*
par_type:
	|	FZ_SET FZ_OF FZ_INT
	|	array_type FZ_SET FZ_OF FZ_INT

var_type:
	|	FZ_VAR int_set
	|	FZ_VAR FZ_SET FZ_OF int_range
	|	FZ_VAR FZ_SET FZ_OF int_set
	|	array_type FZ_VAR int_set
	|	array_type FZ_VAR FZ_SET FZ_OF int_range
	|	array_type FZ_VAR FZ_SET FZ_OF int_set
*/

	class TypeSpec {
	public:
		TypeSpec(obj_t _objType, spec_t _valType) :
			objType(_objType),
			valType(_valType),
			indexLow(-1), indexHigh(-1)
		{}

		TypeSpec(obj_t _objType, spec_t _valType, b1<Int,xmm>* idxSet) :
			objType(_objType),
			valType(_valType),
			indexLow(idxSet->item(0)), indexHigh(idxSet->item(1))
		{}

		virtual ~TypeSpec()
		{}

		bool simple()
		{
			return ( indexLow == -1 );
		}

		obj_t   objType;						// KFZ_PAR, KFZ_VAR
		spec_t  valType;						// KFZ_BOOL, KFZ_INT, KFZ_FLOAT, KFZ_IRANGE, KFZ_ISET
		Int     indexLow, indexHigh;			// indexLow = -1 : not an array type
	};

	class BoolTypeSpec : public TypeSpec {
	public:
		BoolTypeSpec(obj_t _objType) :
			TypeSpec(_objType, KFZ_BOOL)
		{}

		BoolTypeSpec(obj_t _objType, b1<Int,xmm>* idxSet) :
			TypeSpec(_objType, KFZ_BOOL, idxSet)
		{}

		~BoolTypeSpec() {}
	};

	class IntTypeSpec : public TypeSpec {
	public:
		IntTypeSpec(obj_t _objType) :
			TypeSpec(_objType, KFZ_INT),
			finite(false)
		{}

		IntTypeSpec(obj_t _objType, Int rngLow, Int rngHigh) :
			TypeSpec(_objType, KFZ_INT),
			finite(true),
			rangeLow(rngLow), rangeHigh(rngHigh)
		{}

		IntTypeSpec(obj_t _objType, b1<Int,xmm>* idxSet) :
			TypeSpec(_objType, KFZ_INT, idxSet),
			finite(false)
		{}

		IntTypeSpec(obj_t _objType, b1<Int,xmm>* idxSet, Int rngLow, Int rngHigh) :
			TypeSpec(_objType, KFZ_INT, idxSet),
			finite(true),
			rangeLow(rngLow), rangeHigh(rngHigh)
		{}

		~IntTypeSpec() {}

		bool finite;
		int  rangeLow, rangeHigh;
	};

	class FloatTypeSpec : public TypeSpec {
	public:
		FloatTypeSpec(obj_t _objType) :
			TypeSpec(_objType, KFZ_FLOAT),
			finite(false)
		{}

		FloatTypeSpec(obj_t _objType, Flt rngLow, Flt rngHigh, Flt rngStep = PrcFlt) :
			TypeSpec(_objType, KFZ_FLOAT),
			finite(true),
			rangeLow(rngLow), rangeHigh(rngHigh), rangeStep(rngStep)
		{}

		FloatTypeSpec(obj_t _objType, b1<Int,xmm>* idxSet) :
			TypeSpec(_objType, KFZ_FLOAT, idxSet),
			finite(false)
		{}

		FloatTypeSpec(obj_t _objType, b1<Int,xmm>* idxSet, Flt rngLow, Flt rngHigh, Flt rngStep = PrcFlt) :
			TypeSpec(_objType, KFZ_FLOAT, idxSet),
			finite(true),
			rangeLow(rngLow), rangeHigh(rngHigh), rangeStep(rngStep)
		{}

		~FloatTypeSpec() {}

		bool finite;
		Flt  rangeLow, rangeHigh, rangeStep;
	};

}

#endif
