/**
 * Authors:
 *     Duc Nghia Pham <duc-nghia.pham@nicta.com.au>
 *     Hakim Newton   <hakim.newton@nicta.com.au>
 */


#ifndef __KANGAROO_FLATZINC_OUTSPEC__HH__
#define __KANGAROO_FLATZINC_OUTSPEC__HH__

#include <iostream>
#include <string>

//#include "cbls/structs/idx.hh"

#include "defs.hpp"
#include "exprspec.hpp"

using namespace kangaroo;

namespace FlatZinc {

	/**********************************************
	 * class OutSpec :: declaration               *
	 **********************************************/

	/*
	 * Describe the specification of an output variable
	 *   or an array of output variables
	 */
	class OutSpec {
	public:
		OutSpec(std::string _name, spec_t _type);

		OutSpec(std::string _name, spec_t _type, Hdl h);

		OutSpec(std::string _name, spec_t _type, AnnSpec* ann);

		~OutSpec() {
		}

		void print(std::ostream& os) const;

	public:
		std::string    name;
		spec_t         type;
		size_t         dimension;	// 0: means a non-array variable
		b1<int,xmm>    l_indices, r_indices;
		b1<Hdl,xmm>    handles;
	};

	template<class charT, class traits>
	std::basic_ostream<charT, traits>&
	operator <<(std::basic_ostream<charT, traits>& os, const OutSpec* out) {
		if ( out != NULL )
			out->print(os);
		return os;
	}


	/**********************************************
	 * OutSpec :: functions                       *
	 **********************************************/

	inline
	OutSpec::OutSpec(std::string _name, spec_t _type) {
		name      = _name;
		type      = _type;
		dimension = 0;
	}

	inline
	OutSpec::OutSpec(std::string _name, spec_t _type, Hdl h) {
		name      = _name;
		type      = _type;
		dimension = 0;
		handles.insertMem(h);
	}

	inline
	OutSpec::OutSpec(std::string _name, spec_t _type, AnnSpec* ann) {
		name      = _name;
		type      = _type;

		ExprSpec *es = getAnnArg(ann, 0);
		dimension = es->size();
		for ( unsigned int i = 0; i < dimension; ++i ) {
			ExprSpec *e = (*es)[i];
			Warn( e->type != KFZ_IRANGE, "Invalid output indices for array variable " << _name.c_str() );
			l_indices.insertMem( e->value.iset->item(0) );
			r_indices.insertMem( e->value.iset->item(1) );
		}
	}

	inline
	void OutSpec::print(std::ostream& os) const {
		if ( dimension == 0 ) {
			os << "output_var( " << name << ", " << type << " ) = [ " << handles.item(0) << " ]";
		} else {
			os << "output_array( " << name << ", " << type << ", " << dimension << " :: ";
			os << l_indices.item(0) << ".." << r_indices.item(0);
			for ( unsigned int i = 1; i < dimension; ++i )
				os << ", " << l_indices.item(i) << ".." << r_indices.item(i);
			os << " ) = [ ";
			os << handles.item(0);
			for ( unsigned int i = 1; i < handles.itemCount(); ++i )
				os << ", " << handles.item(i);
			os << " ]";
		}
	}

}

#endif
