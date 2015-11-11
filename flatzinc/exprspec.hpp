/**
 * Authors:
 *     Duc Nghia Pham <duc-nghia.pham@nicta.com.au>
 *     Hakim Newton   <hakim.newton@nicta.com.au>
 */


#ifndef __KANGAROO_FLATZINC_EXPRSPEC__HH__
#define __KANGAROO_FLATZINC_EXPRSPEC__HH__

#include <iostream>
#include <string>
#include <cassert>

//#include "cbls/globals/idx.hh"
//#include "cbls/structs/idx.hh"
#include "cbls/consts/idx.hh"

#include "defs.hpp"

namespace FlatZinc {

	/**********************************************
	 * class IExprSpec :: declaration             *
	 **********************************************/

	class IExprSpec {
	public:
		IExprSpec()
		{}

		virtual
		~IExprSpec()
		{}

		virtual
		void print(std::ostream& os) const = 0;
	};


	/**********************************************
	 * class AnnSpec :: declaration               *
	 **********************************************/

	/*
	 * Describe the specification of an annotation
	 */
	class AnnSpec {
	public:
		AnnSpec() :
			name("KFZ_ANNOTATION"), args(NULL)
		{}

		AnnSpec(std::string _name) :
			name(_name), args(NULL)
		{}

		AnnSpec(std::string _name, IExprSpec* _args) :
			name(_name), args(_args)
		{}

		~AnnSpec() {
			if ( args ) delete args;
		}

		size_t        size();

		std::string*  getIDarg(unsigned int i);

		bool          getInt(unsigned int i, int* val);

		void print(std::ostream& os) const;

	public:
		std::string  name;
		IExprSpec*   args;
	};

	template<class charT, class traits>
	std::basic_ostream<charT, traits>&
	operator <<(std::basic_ostream<charT, traits>& os, const AnnSpec* ann) {
		if ( ann != NULL )
			ann->print(os);
		return os;
	}


	/**********************************************
	 * class Annotations :: declaration           *
	 **********************************************/

	/*
	 * Implement a dynamic list of annotations.
	 *   Allow querying and finding an annotation by its name
	 */
	class Annotations {
	public:
		Annotations() :
			anns(NULL)
		{}

		~Annotations() {
			if ( !anns ) return;
			for ( unsigned int i = 0; i < anns->itemCount(); ++i ) {
				if ( anns->item(i) ) delete anns->item(i);
			}
			delete anns;
		}

		bool empty() {
			return (anns == NULL);
		}

		void addAnn(AnnSpec *ann);

		bool hasAnn(std::string name);

		AnnSpec* findAnn(std::string name);

		void print(std::ostream& os) const;

	public:
		emu::b1<AnnSpec*,xmm>* anns;
	};

	template<class charT, class traits>
	std::basic_ostream<charT, traits>&
	operator <<(std::basic_ostream<charT, traits>& os, const Annotations* anns) {
		if ( anns != NULL )
			anns->print(os);
		return os;
	}


	/**********************************************
	 * class ExprSpec :: declaration              *
	 **********************************************/

	typedef emu::b1<IExprSpec*,xmm> ArrayIExprSpec;

	union exprValType {
		bool                              bval;
		double                            fval;
		int                               ival;
		std::string*                      sval;
		emu::b1<kangaroo::Int,xmm>*  	  iset;
		AnnSpec*                          ann;
		ArrayIExprSpec*                   aval;
		kangaroo::Hdl                     hdl;
	};

	/*
	 * Describe the specification of an expression
	 */
	class ExprSpec : public IExprSpec {
	public:
		ExprSpec() :
			type(KFZ_ANY)
		{}

		ExprSpec(std::string _idval) :
			type(KFZ_ID)
		{
			value.sval = new std::string(_idval);
		}

		~ExprSpec() {
			destroy();
		}

		bool   empty();
		size_t size();

		void setBoolVal(bool _val);
		void setFloatVal(double _val);
		void setIntVal(int _val);
		void setIntRange(emu::b1<kangaroo::Int,xmm>* _range);
		void setIntSet(emu::b1<kangaroo::Int,xmm>* _set);

		void setIdVal(std::string const & _val);
		void setIdVal(std::string* _val);
		void setIdVal(const char* _val);

		void setHandle(kangaroo::Hdl const & _val);

		void setStringVal(std::string const & _val);
		void setStringVal(const char* _val);

		void setAnnVal(AnnSpec* ann);

		void setArrayEmptyVal();
		void setArrayFirstVal(ExprSpec* _val);
		void setArrayNextVal(ExprSpec* _val);

		ExprSpec* operator[](unsigned int i) const;

		kangaroo::Hdl getHdl(kangaroo::Hdl& kSystem, unsigned int i = 0);

		void print(std::ostream& os) const;

	public:
		spec_t      type;
		exprValType value;

	private:
		void destroy();
	};

	template<class charT, class traits>
	std::basic_ostream<charT, traits>&
	operator <<(std::basic_ostream<charT, traits>& os, const ExprSpec* espec) {
		if ( espec != NULL )
			espec->print(os);
		return os;
	}


	ExprSpec* getAnnArg(AnnSpec* ann, unsigned int i);


	/**********************************************
	 * AnnSpec :: functions                       *
	 **********************************************/

	inline
	void AnnSpec::print(std::ostream& os) const {
		os << name;
		if ( !args ) return;
		os << "(";
		args->print(os);
		os << ")";
	}

	inline
	size_t AnnSpec::size() {
		ExprSpec* expr = static_cast<ExprSpec*>(args);

		return expr->size();
	}

	inline
	std::string* AnnSpec::getIDarg(unsigned int i) {
		ExprSpec* expr  = static_cast<ExprSpec*>(args);
		assert( expr->type == KFZ_ARRAY );

		if ( i >= expr->value.aval->itemCount() )
			return NULL;
		ExprSpec* _expr = static_cast<ExprSpec*>( expr->value.aval->item(i) );
		if ( _expr->type == KFZ_ID )
			return _expr->value.sval;

		return NULL;
	}

	inline
	bool AnnSpec::getInt(unsigned int i, int* val) {
		ExprSpec* expr  = static_cast<ExprSpec*>(args);
		assert( expr->type == KFZ_ARRAY );

		if ( i >= expr->value.aval->itemCount() )
			return false;
		ExprSpec* _expr = static_cast<ExprSpec*>( expr->value.aval->item(i) );
		if ( _expr->type == KFZ_INT ) {
			*val = _expr->value.ival;
			return true;
		}

		return false;
	}

	inline
	ExprSpec* getAnnArg(AnnSpec* ann, unsigned int i) {
		ExprSpec* expr  = static_cast<ExprSpec*>(ann->args);

		return (*expr)[i];
	}



	/**********************************************
	 * Annotations :: functions                   *
	 **********************************************/

	inline
	void Annotations::addAnn(AnnSpec *ann) {
		if ( !anns ) {
			anns = new emu::b1<AnnSpec*,xmm>();
		}
		anns->insertMem(ann);
	}

	inline
	bool Annotations::hasAnn(std::string name) {
		if ( !anns ) return false;

		for ( unsigned int i = 0; i < anns->itemCount(); ++i ) {
			if ( name.compare( anns->item(i)->name ) == 0 ) return true;
		}

		return false;
	}

	inline
	AnnSpec* Annotations::findAnn(std::string name) {
		if ( !anns ) return NULL;

		for ( unsigned int i = 0; i < anns->itemCount(); ++i ) {
			if ( name.compare( anns->item(i)->name ) == 0 ) return anns->item(i);
		}

		return NULL;
	}

	inline
	void Annotations::print(std::ostream& os) const {
		if ( !anns ) return;

		for ( unsigned int i = 0; i < anns->itemCount(); ++i ) {
			os << " :: ";
			(anns->item(i))->print(os);
		}
	}

	/**********************************************
	 * ExprSpec :: functions                      *
	 **********************************************/

	inline
	void ExprSpec::destroy() {
		if ( type == KFZ_ID || type == KFZ_STRING ) {
			delete value.sval;
		} else if ( type == KFZ_IRANGE || type == KFZ_ISET ) {
			delete value.iset;
		} else if ( type == KFZ_ANNOTATION ) {
			delete value.ann;
		} else if ( type == KFZ_ARRAY ) {
			for ( unsigned int i = 0; i < value.aval->itemCount(); ++i ) {
				if ( value.aval->item(i) ) delete value.aval->item(i);
			}
			delete value.aval;
		}
		type = KFZ_ANY;
	}

	inline
	bool ExprSpec::empty() {
		if ( type == KFZ_ANY ) {
			return true;
		} else if ( type == KFZ_ARRAY ) {
			return ( value.aval->itemCount() == 0 );
		}
		return false;
	}

	inline
	size_t ExprSpec::size() {
		if ( type == KFZ_ANY ) {
			return 0;
		} else if ( type == KFZ_ARRAY) {
			return value.aval->itemCount();
		}

		return 1;
	}

	inline
	void ExprSpec::setBoolVal(bool _val) {
		destroy();

		type       = KFZ_BOOL;
		value.bval = _val;
	}

	inline
	void ExprSpec::setFloatVal(double _val) {
		destroy();

		type       = KFZ_FLOAT;
		value.fval = _val;
	}

	inline
	void ExprSpec::setIntVal(int _val) {
		destroy();

		type       = KFZ_INT;
		value.ival = _val;
	}

	inline
	void ExprSpec::setIntRange(emu::b1<kangaroo::Int,xmm>* _range) {
		destroy();

		type       = KFZ_IRANGE;
		value.iset = _range;
	}

	inline
	void ExprSpec::setIntSet(emu::b1<kangaroo::Int,xmm>* _set) {
		destroy();

		type       = KFZ_ISET;
		value.iset = _set;
	}

	inline
	void ExprSpec::setIdVal(std::string const & _val) {
		destroy();

		type       = KFZ_ID;
		value.sval = new std::string(_val);
	}

	inline
	void ExprSpec::setIdVal(std::string* _val) {
		destroy();

		type       = KFZ_ID;
		value.sval = _val;
	}

	inline
	void ExprSpec::setIdVal(const char* _val) {
		destroy();

		type       = KFZ_ID;
		value.sval = new std::string(_val);
	}

	inline
	void ExprSpec::setHandle(kangaroo::Hdl const & _val) {
		destroy();

		type       = KFZ_HDL;
		value.hdl  = _val;
	}

	inline
	void ExprSpec::setStringVal(std::string const & _val) {
		destroy();

		type       = KFZ_STRING;
		value.sval = new std::string(_val);
	}

	inline
	void ExprSpec::setStringVal(const char* _val) {
		destroy();

		type       = KFZ_STRING;
		value.sval = new std::string(_val);
	}

	inline
	void ExprSpec::setAnnVal(AnnSpec* _val) {
		destroy();

		type       = KFZ_ANNOTATION;
		value.ann  = _val;
	}

	inline
	void ExprSpec::setArrayEmptyVal() {
		destroy();

		type       = KFZ_ARRAY;
		value.aval = new ArrayIExprSpec(0);
	}

	inline
	void ExprSpec::setArrayFirstVal(ExprSpec* _val) {
		destroy();

		type       = KFZ_ARRAY;
		value.aval = new ArrayIExprSpec();
		value.aval->insertMem(_val);
	}

	inline
	void ExprSpec::setArrayNextVal(ExprSpec* _val) {
		if ( type != KFZ_ARRAY )
			setArrayFirstVal(_val);
		else
			value.aval->insertMem(_val);
	}

	inline
	ExprSpec* ExprSpec::operator[](unsigned int i) const {
		if ( type != KFZ_ARRAY )
			return NULL;
		if ( i >= value.aval->itemCount() )
			return NULL;
		return static_cast<ExprSpec*>( value.aval->item(i) );
	}

	inline
	kangaroo::Hdl ExprSpec::getHdl(kangaroo::Hdl& kSystem, unsigned int i) {
		kangaroo::Hdl h = kangaroo::InvHdl;
		if ( i < size() ) {
			if ( type == KFZ_ARRAY )
				h = static_cast<ExprSpec*>( value.aval->item(i) )->getHdl(kSystem, 0);
			else {
				switch ( type ) {
					case KFZ_BOOL:
						h = kangaroo::ConstVb::def(kSystem, value.bval);
						break;
					case KFZ_FLOAT:
						h = kangaroo::ConstVf::def(kSystem, value.fval);
						break;
					case KFZ_INT:
						h = kangaroo::ConstVi::def(kSystem, value.ival);
						break;
					case KFZ_IRANGE:
						break;
					case KFZ_ISET:
						break;
					case KFZ_HDL:
						h = value.hdl;
						break;
					default:
						break;
				}
			}
		}
		return h;
	}

	inline
	void ExprSpec::print(std::ostream& os) const {
		switch ( type ) {
			case KFZ_BOOL:
				os << value.bval;
				break;
			case KFZ_FLOAT:
				os << value.fval;
				break;
			case KFZ_INT:
				os << value.ival;
				break;
			case KFZ_IRANGE:
				os << ( value.iset->item(0) ) << ".." << ( value.iset->item(1) );
				break;
			case KFZ_ISET:
				os << "{ ";
				for ( unsigned int i = 0; i < value.iset->itemCount(); ) {
					os << ( value.iset->item(i) );
					if ( ++i < value.iset->itemCount() ) os << ", ";
				}
				os << " }";
				break;
			case KFZ_ID:
				os << *(value.sval);
				break;
			case KFZ_ANNOTATION:
				value.ann->print(os);
				break;
			case KFZ_ARRAY:
				os << "[ ";
				for ( unsigned int i = 0; i < value.aval->itemCount(); ) {
					ExprSpec* es = static_cast<ExprSpec*>(value.aval->item(i));
					es->print(os);
					if ( ++i < value.aval->itemCount() ) os << ", ";
				}
				os << " ]";
				break;
			case KFZ_HDL:
				os << "h(" << value.hdl << ")";
				break;
			default:
				break;
		}
	}

}

#endif
