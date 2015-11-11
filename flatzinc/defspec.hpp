/**
 * Authors:
 *     Duc Nghia Pham <duc-nghia.pham@nicta.com.au>
 *     Hakim Newton   <hakim.newton@nicta.com.au>
 */


#ifndef __KANGAROO_FLATZINC_DEFSPEC__HH__
#define __KANGAROO_FLATZINC_DEFSPEC__HH__

#include <iostream>
#include <string>

//#include "cbls/structs/idx.hh"

#include "defs.hpp"
#include "exprspec.hpp"
#include "typespec.hpp"
#include "outspec.hpp"

using namespace kangaroo;

namespace FlatZinc {

	class CtrSpec;

	/**********************************************
	 * class CtrSpec :: declaration               *
	 **********************************************/

	/*
	 * Describe the specification of an undefined constraint
	 */
	class CtrSpec {
	public:
		CtrSpec(std::string _func, ExprSpec* _expr, b1<ExprSpec*,xmm>* _undefs, int _weight = 1, term_t _type = KFZ_CONSTRAINT) :
			type(_type), func(_func), expr(_expr), undefs(_undefs), weight(_weight)
		{}

		virtual
		~CtrSpec() {
			if ( expr )   delete expr;
			if ( undefs ) delete undefs;
		}

		void   addDep(CtrSpec* d);

		size_t nbUndefs();
		void   remUndef(std::string name, Hdl h);

		virtual
		void print(std::ostream& os) const;

	public:
		term_t              type;
		std::string         func;
		ExprSpec*           expr;
		b1<ExprSpec*,xmm>*  undefs;
		int                 weight;

		b1<CtrSpec*,xmm>    deps;
	};

	template<class charT, class traits>
	std::basic_ostream<charT, traits>&
	operator <<(std::basic_ostream<charT, traits>& os, const CtrSpec* ctr) {
		if ( ctr != NULL )
			ctr->print(os);
		return os;
	}


	/**********************************************
	 * class VarSpec :: declaration               *
	 **********************************************/

	/*
	 * Describe the specification of an undefined variable
	 */
	class VarSpec : public CtrSpec {
	public:
		VarSpec(std::string _name) :
			CtrSpec("", NULL, NULL, 1, KFZ_VARIABLE),
			name(_name), ospec(NULL)
		{}

		VarSpec(std::string _name,
				std::string _func, ExprSpec* _expr, b1<ExprSpec*,xmm>* _undefs, ExprSpec* _out = NULL) :
			CtrSpec(_func, _expr, _undefs, 1, KFZ_VARIABLE),
			name(_name), out(_out), ospec(NULL)
		{}

		~VarSpec() {
			// 'out' is part of 'CtrSpec::expr' so no need to dealloc
		}

		void def(std::string _func, ExprSpec* _expr, b1<ExprSpec*,xmm>* _undefs, ExprSpec* _out);
		void setOutSpec(OutSpec* _ospec);

		void print(std::ostream& os) const;

	public:
		std::string         name;
		ExprSpec*           out;
		OutSpec*            ospec;
	};

	template<class charT, class traits>
	std::basic_ostream<charT, traits>&
	operator <<(std::basic_ostream<charT, traits>& os, const VarSpec* var) {
		if ( var != NULL )
			var->print(os);
		return os;
	}


	/**********************************************
	 * class ArrayVarsSpec :: declaration         *
	 **********************************************/

	/*
	 * Describe the specification of an undefined array of variables
	 */
	class ArrayVarsSpec : public CtrSpec {
	public:
		ArrayVarsSpec(std::string _name, std::pair<int,int> _indices,
					  std::string _func, ExprSpec* _expr, b1<ExprSpec*,xmm>* _undefs) :
			CtrSpec(_func, _expr, _undefs, 1, KFZ_ARRAYVARS),
			name(_name), indices(_indices), ospec(NULL)
		{}

		~ArrayVarsSpec() {
		}

		void setOutSpec(OutSpec* _ospec);

		void print(std::ostream& os) const;

	public:
		std::string         name;
		std::pair<int,int>  indices;
		OutSpec*            ospec;
	};

	template<class charT, class traits>
	std::basic_ostream<charT, traits>&
	operator <<(std::basic_ostream<charT, traits>& os, const ArrayVarsSpec* vars) {
		if ( vars != NULL )
			vars->print(os);
		return os;
	}


	/**********************************************
	 * CtrSpec :: functions                       *
	 **********************************************/

	inline
	void CtrSpec::addDep(CtrSpec* d) {
		deps.insertMem(d);
	}

	inline
	size_t CtrSpec::nbUndefs() {
		if ( !undefs ) return -1;
		return undefs->itemCount();
	}

	inline
	void CtrSpec::remUndef(std::string name, Hdl h) {
		for ( unsigned int i = 0; i < undefs->itemCount(); ++i ) {
			ExprSpec* e = undefs->item(i);
			if ( name.compare( *(e->value.sval) ) == 0 ) {
				if ( h != InvHdl ) e->setHandle(h);
				undefs->removePull(i);
				break;
			}
		}
	}

	inline
	void CtrSpec::print(std::ostream& os) const {
		os << "constraint '" << func << "'";
	}


	/**********************************************
	 * VarSpec :: functions                       *
	 **********************************************/

	inline
	void VarSpec::def(std::string _func, ExprSpec* _expr, b1<ExprSpec*,xmm>* _undefs, ExprSpec* _out) {
		func   = _func;
		expr   = _expr;
		undefs = _undefs;
		out    = _out;
	}

	inline
	void VarSpec::setOutSpec(OutSpec* _ospec) {
		ospec = _ospec;
	}

	inline
	void VarSpec::print(std::ostream& os) const {
		if ( out )
			os << "variable '" << name << "' defined by function '" << func << "'";
		else
			os << "variable '" << name << "' defined by an expression '" << expr << "'";
	}


	/**********************************************
	 * ArrayVarsSpec :: functions                 *
	 **********************************************/

	inline
	void ArrayVarsSpec::setOutSpec(OutSpec* _ospec) {
		ospec = _ospec;
	}

	inline
	void ArrayVarsSpec::print(std::ostream& os) const {
		os << "array [" << indices.first << "," << indices.second << "] of variables '"
			<< name << "' defined by an expression '" << expr << "'";
	}


}

#endif
