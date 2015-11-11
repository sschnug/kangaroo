/**
 * Authors:
 *     Duc Nghia Pham <duc-nghia.pham@nicta.com.au>
 *     Hakim Newton   <hakim.newton@nicta.com.au>
 *
 * Modified from Gecode's flatzinc-skeleton-1.1 to work with Kangaroo
 */

/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Guido Tack <tack@gecode.org>
 *
 *  Copyright:
 *     Guido Tack, 2007
 *
 *  Last modified:
 *     $Date: 2010-07-02 11:18:43 +0200 (vr, 02 jul 2010) $ by $Author: tack $
 *     $Revision: 11149 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <iostream>
#include <queue>

#include "cbls/consts/idx.hh"
#include "cbls/vars/idx.hh"
#include "cbls/funcs/idx.hh"
#include "cbls/selcs/idx.hh"

#include "flatzinc.hpp"
#include "defs.hpp"
#include "registry.hpp"
#include "utils.hpp"

using namespace std;

namespace FlatZinc {

	#define eDefTerm(NAME)        "A term with the same name '" << NAME << "' has been defined !!!"
	#define eTermType(NAME)       "The type of term '" << NAME << "' isn't matched with its assigning type !!!"
	#define eTermsType(NAME,POS)  "The type of array_term '" << NAME << "' isn't matched with its assigning type at position " << castN(POS) << " !!!"
	#define eTermsSize(NAME)      "The size of term '" << NAME << "' isn't matched with its assigning size !!!"
	#define eExprVar(CNAME,VNAME) "Constraint " << CNAME << " contains no description to define the variable " << VNAME << " !!!"

	#define eUndefSolveMethod     "Undefined solving method !!!"
	#define eUndefObjFunc         "Undefined objective variable or function !!!"
	#define eUnregObjFunc         "Unrecognised type of objective function !!!"


	FlatZincModel::FlatZincModel(void) {
		/// Kangaroo CBLS system
		kSystem = kangaroo::Sys::def();

		kangaroo::EvalTi::def(kSystem);		// add support for integer type
		kangaroo::EvalTb::def(kSystem);		// add support for boolean type
		kangaroo::EvalTf::def(kSystem);		// add support for floating type

		kangaroo::HintTi::def(kSystem);		// add support for integer metric
		kangaroo::HintTf::def(kSystem);		// add support for floating metric

#if (PropagationAlgo == 0) || (PropagationAlgo > 2 )
		kangaroo::Sys::refm(kSystem).setMultiCandExec();
#endif

#if (PropagationAlgo == 0) || (PropagationAlgo == 2 ) || (PropagationAlgo == 4 )
		kangaroo::Sys::refm(kSystem).setMultiFixedSimul();
		kangaroo::Sys::refm(kSystem).setMultiFlexiSimul();
#endif

		kVarSelc      = InvHdl;
		kValSelc      = InvHdl;

		kVarConstraintSelc   = InvHdl;
		kValConstraintSelc   = InvHdl;

		kVarOptimisationSelc = InvHdl;
		kValOptimisationSelc = InvHdl;

		topConstraint   = Prm::InvPrm();
		topOptimisation = Prm::InvPrm();

		objFunction     = Prm::InvPrm();
		objBound        = Prm::InvPrm();

		objType         = KFZ_ANY;

		falsified       = true;
		objIntVal       = 0;
		objFltVal       = 0;

		nbVars          = 0;
		hasWeight       = false;
		useSwapSelc     = false;
		kTabuTenure     = -1;

//		CCNT = 0;

		/// Whether to solve as satisfaction or optimization problem
		method = KFZ_SAT;
	}

	FlatZincModel::~FlatZincModel(void) {
		for ( unsigned int i = 0; i < outputs.itemCount(); ++i )
			delete outputs.item(i);
	}

	void FlatZincModel::setRandomSeed(unsigned seed) {
		kRnd.seed(seed);
	}

	/**
	 * variables/constraints:
	 *     name
	 *
	 * variables:
	 *     Assuming that a "defined" or "introduced" var is not an "output" var,
	 *     also assuming that it is not an "alias" as well as not an array of vars.
	 *     Therefore only need to store the "TypeSpec *"
	 *
	 * constraints:
	 *     Store ExprSpec* and bool(define_a_var)
	 */

	/*
	 * Create a new constant from specification.
	 * Return true if success, false if a constant 'name' is already defined.
	 *
	 * par_type ::= bool
	 *	| float
	 *	| int
	 *	TBA:: | set of int
	 *	| array [index_set] of bool
	 *	| array [index_set] of float
	 *	| array [index_set] of int
	 *	TBA:: | array [index_set] of set of int
	 */
	bool FlatZincModel::declConstant(char* c_name, TypeSpec* tspec, ExprSpec* espec) {
		std::string name(c_name);
		Warn( defTerms.find(name), eDefTerm(c_name) );

		if ( tspec->simple() ) {
			Warn( tspec->valType != espec->type, eTermType(c_name) );

			defTerms.insertBllMem( name, newConstant(tspec, espec) );
#if ! defined(NDEBUG)
			cerr << "    declared..." << endl;
#endif
		} else {
			Warn( espec->size() != static_cast<size_t>(tspec->indexHigh - tspec->indexLow + 1), eTermsSize(c_name) );

			defArrays.insertBllMem( name, std::make_pair<int,int>(tspec->indexLow,tspec->indexHigh) );

			for ( int i = tspec->indexLow; i <= tspec->indexHigh; ++i ) {
				unsigned int _i = i - tspec->indexLow;

				Warn( tspec->valType != (*espec)[_i]->type, eTermsType(c_name, i) );
				defTerms.insertBllMem( elem_id(name, i), newConstant(tspec, (*espec)[_i]) );
			}

#if ! defined(NDEBUG)
			cerr << "    declared an array..." << endl;
#endif
		}

		return true;
	}

	Hdl FlatZincModel::newConstant(TypeSpec* tspec, ExprSpec* espec) {
		Hdl idx = InvIdx;
		switch ( tspec->valType ) {
			case KFZ_BOOL:
				idx = kangaroo::ConstVb::def(kSystem, espec->value.bval);	// bool as int
				break;
			case KFZ_FLOAT:
				idx = kangaroo::ConstVf::def(kSystem, espec->value.fval);
				break;
			case KFZ_INT:
				idx = kangaroo::ConstVi::def(kSystem, espec->value.ival);
				break;
			case KFZ_IRANGE:
				break;
			case KFZ_ISET:
				break;
			default:
				break;
		}
		return idx;
	}

	/*
	 * Create a new variable from specification.
	 * Return true if success, false if a variable 'name' is already defined.
	 *
	 * var_type ::= var bool
	 *	| var float
	 *	| var float_const..float_const
	 *	| var int
	 *	| var int_const..int_const
	 *	TBA:: | var {int const,...}
	 *	TBA:: | var set of int_const..int_const
	 *	TBA:: | var set of {int_const,...}
	 *	| array [index_set] of var bool
	 *	| array [index_set] of var float
	 *	| array [index_set] of var float_const..float_const
	 *	| array [index_set] of var int
	 *	| array [index_set] of var int_const..int_const
	 *	TBA:: | array [index_set] of var {int_const,...}
	 *	TBA:: | array [index_set] of var set of int_const..int_const
	 *	TBA:: | array [index_set] of var set of {int_const,...}
	 */
	bool FlatZincModel::declVariable(char* c_name, TypeSpec* tspec, Annotations *anns, ExprSpec* espec) {
		std::string name(c_name);
		Warn( defTerms.find(name), eDefTerm(c_name) );

//		if ( anns->hasAnn("is_defined_var") || anns->hasAnn("var_is_introduced") ) {
		if ( anns->hasAnn("is_defined_var") ) {
			assert( espec == NULL );
			undefTerms.insertBllMem( name, new VarSpec(name) );
#if ! defined(NDEBUG)
			cerr << "    postponed..." << endl;
#endif
			return true;
		};

		if ( tspec->simple() ) {	// a variable
			AnnSpec *ann = anns->findAnn("output_var");
			Hdl        h = InvHdl;
			std::string expr_name = "";
			if ( espec == NULL ) {
				h = newVariable(tspec);
			} else {
				if ( getHdl(espec, &h) ) {	// get the handle of 'espec'.
					delete espec;
				} else {
					expr_name = *(espec->value.sval);
					if ( ann )
						postponeExprVar( name, expr_name, espec, new OutSpec( name, tspec->valType) );
					else
						postponeExprVar( name, expr_name, espec );

#if ! defined(NDEBUG)
					cerr << "    postponed = " << expr_name << "..." << endl;
#endif
					return true;
				}
			}

			defTerms.insertBllMem( name, h );
			if ( ann )
				outputs.insertMem( new OutSpec( name, tspec->valType, h ) );
#if ! defined(NDEBUG)
			if ( expr_name.compare("") == 0 )
				cerr << "    declared..." << endl;
			else
				cerr << "    declared = " << expr_name << "..." << endl;
#endif
		} else {	// an array of variables
			AnnSpec *ann = anns->findAnn("output_array");

			if ( espec == NULL ) {
				defArrays.insertBllMem( name, std::make_pair<int,int>(tspec->indexLow,tspec->indexHigh) );
				for ( int i = tspec->indexLow; i <= tspec->indexHigh; ++i )
					defTerms.insertBllMem( elem_id(name, i), newVariable(tspec) );
			} else {
				size_t sz = tspec->indexHigh - tspec->indexLow + 1;
				Alert( espec->size() != sz, "Variable assignment :: size mismatch!!!" );

				Hdl h = InvHdl;
				b1<ExprSpec*,xmm>* undefs = new b1<ExprSpec*,xmm>();
				for ( unsigned i = 0; i < sz; ++i ) {
					ExprSpec* _e = (*espec)[i];
					std::string elem_name = elem_id(name, i + tspec->indexLow);

					if ( getHdl( _e, &h ) ) {
						defTerms.insertBllMem( elem_name, h );
					} else {
						std::string expr_name = *(_e->value.sval);
						postponeExprVar( elem_name, expr_name, new ExprSpec(expr_name) );

						undefs->insertMem( new ExprSpec(elem_name) );
						undefs->insertMem( (*espec)[i] );
					}
				}

				if ( !undefs->itemCount() ) {
					defArrays.insertBllMem( name, std::make_pair<int,int>(tspec->indexLow,tspec->indexHigh) );
#if ! defined(NDEBUG)
					cerr << "    declared an array = " << espec << "..." << endl;
#endif
					delete espec;	delete undefs;
				} else {
					ArrayVarsSpec* avs = new ArrayVarsSpec(name, std::make_pair<int,int>(tspec->indexLow,tspec->indexHigh),
														   "defined_var", espec, undefs);
					for ( unsigned i = 0; i < undefs->itemCount(); ++i ) {
						assert( undefTerms.findBll( *(undefs->item(i)->value.sval) ) );
						undefTerms.map( *(undefs->item(i)->value.sval) )->addDep( avs );
					}
					undefTerms.insertBllMem( name, avs );

					if ( ann )	avs->setOutSpec( new OutSpec( name, tspec->valType, ann ) );
#if ! defined(NDEBUG)
					cerr << "    postponed an array = " << espec << "..." << endl;
#endif
					return true;
				}
			}

			if ( ann ) {
				OutSpec *ospec = new OutSpec( name, tspec->valType, ann );
				for ( int i = tspec->indexLow; i <= tspec->indexHigh; ++i )
					ospec->handles.insertMem( defTerms.map(elem_id(name, i)) );
				outputs.insertMem(ospec);
			}
#if ! defined(NDEBUG)
			cerr << "    declared an array..." << endl;
#endif
		}

		return true;
	}

	void FlatZincModel::postponeExprVar(std::string &name, std::string &expr_name, ExprSpec* e, OutSpec* o) {
		b1<ExprSpec*,xmm>* undefs = new b1<ExprSpec*,xmm>(1);
		undefs->insert(e);

		VarSpec* v = new VarSpec(name, "defined_var", e, undefs);
		assert( undefTerms.findBll( expr_name ) );
		undefTerms.map( expr_name )->addDep(v);
		undefTerms.insertBllMem( name, v );
		if ( o )	v->setOutSpec(o);
	}

	bool FlatZincModel::getHdl(ExprSpec* e, Hdl* h) {
		bool defined = true;
		*h = InvHdl;
		switch ( e->type ) {
			case KFZ_BOOL:
			case KFZ_FLOAT:
			case KFZ_INT:
				*h = e->getHdl(kSystem, 0);
				break;
			case KFZ_HDL:
				*h = e->value.hdl;
				break;
			case KFZ_ID:
			{
				std::string _name = *(e->value.sval);
				if ( defTerms.findBll(_name) )
					*h = defTerms.map(_name);
				else
					defined = false;
			}
				break;
			case KFZ_IRANGE:
			case KFZ_ISET:
			default:
				Alert( true, "The variable assignment is not an identifier!!!" );
				break;
		}
		return defined;
	}

	Hdl FlatZincModel::newVariable(TypeSpec* tspec) {
		Hdl h      = InvHdl;
		bool isVar = true;
		switch ( tspec->valType ) {
			case KFZ_BOOL:
				h = kangaroo::StatRangeVarVi::def(kSystem, 0, 1);		// bool as int
				break;
			case KFZ_FLOAT:
			{
				FloatTypeSpec* fspec = static_cast<FloatTypeSpec*>(tspec);
				if ( fspec->finite ) {
					if ( eq<Flt>::iof(fspec->rangeLow, fspec->rangeHigh)) {
						h = kangaroo::ConstVf::def(kSystem, fspec->rangeLow);	// declare as a constant
						isVar = false;
					} else {
//						Alert( fspec->rangeHigh - fspec->rangeLow + 1 > 5000, "The domain size of a variable is too big!!!");
						h = kangaroo::StatRangeVarVf::def(kSystem, fspec->rangeLow, fspec->rangeHigh, fspec->rangeStep);
					}
				} else {
//					Alert( true, "The domain size of a variable is too big!!!");
					h = kangaroo::StatRangeVarVf::def(kSystem);
				}
			}
				break;
			case KFZ_INT:
			{
				IntTypeSpec* ispec = static_cast<IntTypeSpec*>(tspec);
				if ( ispec->finite ) {
					if ( ispec->rangeLow == ispec->rangeHigh ) {
						h = kangaroo::ConstVi::def(kSystem, ispec->rangeLow);	// declare as a constant
						isVar = false;
					} else {
//						Alert( ispec->rangeHigh - ispec->rangeLow + 1 > 5000, "The domain size of a variable is too big!!!");
						h = kangaroo::StatRangeVarVi::def(kSystem, ispec->rangeLow, ispec->rangeHigh);
					}
				} else {
//					Alert( true, "The domain size of a variable is too big!!!");
					h = kangaroo::StatRangeVarVi::def(kSystem);
				}
			}
				break;
			case KFZ_IRANGE:
				Warn( true, "Not yet support set variables !!!" );
				break;
			case KFZ_ISET:
				Warn( true, "Not yet support set variables !!!" );
				break;
			default:
				Warn( true, "Not yet support this type of variables !!!" );
				break;
		}
		if ( isVar ) ++nbVars;
		return h;
	}

	/*
	 * Post a constraint
	 */
	void FlatZincModel::postConstraint(char* c_name, ExprSpec* espec, Annotations* anns) {
		b1<ExprSpec*,xmm>* undefs = new b1<ExprSpec*,xmm>();

		unfoldExprs(espec, undefs);

		Hdl h = InvHdl;
		size_t nbUndefs = undefs->itemCount();
		if ( !nbUndefs ) {
			h = registry().post( kSystem, c_name, espec );
//			if ( registry().isConstraint(c_name) ) {
				if ( Func::refc(kSystem, h).EvalMinLoc() == InvLoc )
					defConstraints.insertMem( Prm(Tf, h, MasEn) );
				else
					defConstraints.insertMem( Prm(Tf, h, EnAsEn) );	// By default, Dd is turn on
				constraintWeights.insertMem( getConstraintWeight(anns, &hasWeight) );
//				cerr << "ADD " << ++CCNT << "th constraint: " << c_name << endl;
//			}
			delete espec;	delete undefs;
#if ! defined(NDEBUG)
			cerr << "    posted..." << endl;
#endif
		} else {
			AnnSpec* ann = anns->findAnn("defines_var");
			if ( !ann ) {
				CtrSpec* ctr = new CtrSpec( c_name, espec, undefs, getConstraintWeight(anns, &hasWeight) );
				for ( unsigned int i = 0; i < nbUndefs; ++i ) {
					undefTerms.map( *(undefs->item(i)->value.sval) )->addDep( ctr );
				}
#if ! defined(NDEBUG)
				cerr << "    postponed..." << endl;
#endif
			} else {
				std::string* dv = ann->getIDarg(0);
				VarSpec*      v = static_cast<VarSpec*>( undefTerms.map( *dv ) );
				ExprSpec*     e = NULL;
				for ( unsigned int i = 0; i < nbUndefs; ++i ) {
					e = undefs->item(i);
					if ( dv->compare( *(e->value.sval) ) == 0 ) {
						undefs->removePull(i);
						break;
					}
				}
				Warn( undefs->size() == nbUndefs, eExprVar(c_name, dv->c_str()) );

				if ( --nbUndefs ) {
					v->def( c_name, espec, undefs, e );
					for ( unsigned int i = 0; i < nbUndefs; ++i ) {
						undefTerms.map( *(undefs->item(i)->value.sval) )->addDep( v );
					}
#if ! defined(NDEBUG)
					cerr << "    postponed..." << endl;
#endif
				} else {
					h = registry().post( kSystem, c_name, espec, e );
					defTerms.insertBllMem( *dv, h );
					undefTerms.removeItr( *dv );
					if ( v->ospec ) {
						v->ospec->handles.insertMem(h);
						outputs.insertMem(v->ospec);
					}
					delete espec;	delete undefs;
#if ! defined(NDEBUG)
					cerr << "    posted..." << endl;
#endif

					std::queue<CtrSpec*> qTerms;
					for ( unsigned int i = 0; i < v->deps.itemCount(); ++i ) {
						CtrSpec* d = v->deps.item(i);
						d->remUndef( *dv, h );
						if ( d->nbUndefs() == 0 ) qTerms.push(d);
					}
					delete v;

					while ( !qTerms.empty() ) {
						CtrSpec* d = qTerms.front();	qTerms.pop();
						if ( d->type == KFZ_CONSTRAINT ) {
#if ! defined(NDEBUG)
							cerr << "        >>> constraint '" << d->func << "' ... ";
#endif
							h = registry().post( kSystem, d->func, d->expr );
//							if ( registry().isConstraint(d->func) ) {
								if ( Func::refc(kSystem, h).EvalMinLoc() == InvLoc )
									defConstraints.insertMem( Prm(Tf, h, MasEn) );
								else
									defConstraints.insertMem( Prm(Tf, h, EnAsEn) );	// By default, Dd is turn on
								constraintWeights.insertMem( d->weight );
//								cerr << "ADD " << ++CCNT << "th constraint: " << d->func << endl;

//							}
							delete d;
#if ! defined(NDEBUG)
							cerr << "posted" << endl;
#endif
						} else if ( d->type == KFZ_VARIABLE ) {
							v = static_cast<VarSpec*>(d);
#if ! defined(NDEBUG)
							cerr << "        >>> variable '" << v->name << "' ... ";
#endif
							h = registry().post( kSystem, v->func, v->expr, v->out );
							defTerms.insertBllMem( v->name, h );
							undefTerms.removeItr( v->name );
							if ( v->ospec ) {
								v->ospec->handles.insertMem(h);
								outputs.insertMem(v->ospec);
							}
#if ! defined(NDEBUG)
							cerr << "posted" << endl;
#endif

							for ( unsigned int i = 0; i < v->deps.itemCount(); ++i ) {
								CtrSpec* _d = v->deps.item(i);
								_d->remUndef( v->name, h );
								if ( _d->nbUndefs() == 0 ) qTerms.push(_d);
							}
							delete v;
						} else { // KFZ_ARRAYVARS
							ArrayVarsSpec *av = static_cast<ArrayVarsSpec*>(d);
#if ! defined(NDEBUG)
							cerr << "        >>> array of variables '" << av->name << "' ... ";
#endif
							defArrays.insertBllMem( av->name, av->indices );
							undefTerms.removeItr( av->name );
							if ( av->ospec ) {
								for ( int i = av->indices.first; i <= av->indices.second; ++i )
									av->ospec->handles.insertMem( defTerms.map(elem_id(av->name, i)) );
								outputs.insertMem(av->ospec);
							}
#if ! defined(NDEBUG)
							cerr << "posted" << endl;
#endif

							for ( unsigned int i = 0; i < av->deps.itemCount(); ++i ) {
								CtrSpec* _d = av->deps.item(i);
								_d->remUndef( av->name, InvHdl );
								if ( _d->nbUndefs() == 0 ) qTerms.push(_d);
							}
							delete av;
						}
					}
				}
			}
		}
	}

	void FlatZincModel::unfoldExprs(ExprSpec* es, b1<ExprSpec*,xmm>* undefs) {
		std::queue<ExprSpec*> qExprs;

		qExprs.push(es);
		while ( !qExprs.empty() ) {
			ExprSpec* e = qExprs.front();	qExprs.pop();
			if ( e->type == KFZ_ID ) {
				std::string name = *(e->value.sval);
				if ( defTerms.findBll(name) ) {
					e->setHandle( defTerms.map(name) );
				} else if ( defArrays.findBll(name) ) {
					std::pair<int,int> indices = defArrays.map(name);

					ExprSpec* _e = new ExprSpec();
					_e->setHandle( defTerms.map( elem_id(name, indices.first) ) );
					e->setArrayFirstVal( _e );
					for ( int i = indices.first + 1; i <= indices.second; ++i ) {
						_e = new ExprSpec();
						_e->setHandle( defTerms.map( elem_id(name, i) ) );
						e->setArrayNextVal( _e );
					}
				} else {
					undefs->insertMem(e);
				}
			} else if ( e->type == KFZ_ARRAY ) {
				for (unsigned int i = 0; i < e->size(); ++i )
					qExprs.push( (*e)[i] );
			}
		}
	}

	int FlatZincModel::getConstraintWeight(Annotations* anns, bool *flag) {
		AnnSpec* ann = anns->findAnn("weight");
		int w = 1;
		if ( ann ) ann->getInt(0, &w);
		if ( w != 1 ) *flag = true;
		return w;
	}

	void FlatZincModel::intLockVar(Hdl var, int val) {
		cerr << "IntLockVar needs to be fixed";
//		kangaroo::Sys::setVarLocked( kSystem, var, false );
//		kangaroo::Sys const& ss = kangaroo::Sys::ref(kSystem);
//		while ( ss.TabuVars().Status().item(kangaroo::Vi::ref(kSystem, var).VarSrl) )
//			kangaroo::Sys::setVarTabu( kSystem, var, false );
//		kangaroo::Sys::execAnewItrVal( kSystem, var, kangaroo::RngVi::ref(kSystem, var).ValItr(val) );
//		kangaroo::Sys::setVarTabu( kSystem, var, true );
//		kangaroo::Sys::setVarLocked( kSystem, var, true );
	}

	void FlatZincModel::initialiseRandomAssignment() {

		if ( useSwapSelc ) {
#if ! defined(NDEBUG)
			cerr << "Warning: swap selector assumes that all " << nbVars << " vars have the same domain of size " << nbVars << endl;
#endif
			cerr << "Initialisation of swap selectors needs to be fixed.";
//			b1<Wrp,kmm> vals( nbVars );
//			for ( Idx i = 0; i < nbVars; ++i )
//				vals[i] = Wrp(i);
//			shuffle<Wrp>(kRnd, vals.items(), nbVars);

//			Sys::execAnewVarsWrap(kSystem, vals.items() );
#if ! defined(NDEBUG)
			cerr << "assigned a random permutation" << endl;
#endif
		} else {
			Sys::refm(kSystem).initialiseVarsStatRand( kRnd);
#if ! defined(NDEBUG)
			cerr << "assigned a random assignment" << endl;
#endif
		}

	}

	void FlatZincModel::postSolver(method_t _method, std::string* objfn, Annotations* anns) {
#if ! defined(NDEBUG)
		cerr << "DONE parsing the model..." << endl << endl;
#endif

		useSwapSelc = false;

//		cerr << "THERE ARE " << defConstraints.size() << " CONSTRAINTS" << endl;

		method = _method;
		if ( method == KFZ_SAT ) {
			if ( hasWeight )
//				topConstraint = Prm(Tf,WghtSumKiXiEFcMiHn::def( Xm|El, kSystem, constraintWeights.items(), defConstraints.items(), defConstraints.itemCount() ));
				topConstraint = Prm(Tf,WghtSumKiXiOFcMiHn::def( Xm|On, kSystem, constraintWeights.items(), defConstraints.items(), defConstraints.itemCount() ));
			else
//				topConstraint = Prm(Tf,SumXiEFcMiHn::def( Xm|El, kSystem, defConstraints.items(), defConstraints.itemCount() ));
				topConstraint = Prm(Tf,SumXiOFcMiHn::def( Xm|On, kSystem, defConstraints.items(), defConstraints.itemCount() ));

			Prm _top   = Prm( topConstraint.TermGen, topConstraint.TermHdl, RoHn );

			// need to initialise the assignment as well
			if ( anns->hasAnn("greedy_maxmin") ) {
				Prm _heap   = Prm(Tf,MaxHeapHiFrHi::def(kSystem, _top ));
				kVarSelc    = RankedHintVar1Sp::def( kSystem, _heap);
				kValSelc    = MinVal1StatRangeSdViZi::def( Zm, kSystem, _top );
				//	the value selector above assumed that a variable is an integer variable.
				//	if the variable is of float type, we have to use a different selector.
				useSwapSelc = false;
			} else if ( anns->hasAnn("tabu_maxmin") ) {
				Prm _heap   = Prm(Tf, Sv2TabuMaxHeapHiFrHi::def(kSystem, _top ));
				kVarSelc    = RankedHintVar1Sp::def( kSystem, _heap);
				kValSelc    = MinVal1StatRangeSdViZi::def( Zm, kSystem, _top );
				//	the value selector above assumed that a variable is an integer variable.
				//	if the variable is of float type, we have to use a different selector.
				useSwapSelc = false;
				anns->findAnn("tabu_maxmin")->getInt(0, &kTabuTenure);
			} else if ( anns->hasAnn("greedy_minswap") ) {
				kVarSelc    = MinIdenSsZi::def( Zm, kSystem, _top );
				kValSelc    = kVarSelc;
				useSwapSelc = true;
			} else if ( anns->hasAnn("tabu_minswap") ) {
				kVarSelc    = SvTabuMinIdenSsZi::def( Zm, kSystem, _top, kTabuType );
				kValSelc    = kVarSelc;
				useSwapSelc = true;
				anns->findAnn("tabu_minswap")->getInt(0, &kTabuTenure);
			} else {
				Prm _heap   = Prm(Tf, MaxHeapHiFrHi::def(kSystem, _top ));
				kVarSelc    = RankedHintVar1Sp::def( kSystem, _heap);
				kValSelc    = MinVal1StatRangeSdViZi::def(Zm, kSystem, _top );
				//	the value selector above assumed that a variable is an integer variable.
				//	if the variable is of float type, we have to use a different selector.
				useSwapSelc = false;
			}
		} else if ( method == KFZ_MIN || method == KFZ_MAX ) {
			if ( !objfn )                    Alert( true, eUndefObjFunc );
			if ( !defTerms.findBll(*objfn) )    Alert( true, eUndefObjFunc );

			//======= Constraints ==============
			if ( hasWeight )
				topConstraint = Prm(Tf,WghtSumKiXiOFcMiHn::def( Xm|On, kSystem, constraintWeights.items(), defConstraints.items(), defConstraints.itemCount() ));
			else
				topConstraint = Prm(Tf,SumXiOFcMiHn::def( Xm|On, kSystem, defConstraints.items(), defConstraints.itemCount() ));

			Prm _topConstraint  = Prm(topConstraint.TermGen, topConstraint.TermHdl, RoHn );

			Prm _heap           = Prm(Tf, Sv2TabuMaxHeapHiFrHi::def(kSystem, _topConstraint ));
			kVarConstraintSelc  = RankedHintVar1Sp::def( kSystem, _heap);
			kValConstraintSelc  = MinVal1StatRangeSdViZi::def( Zm, kSystem, _topConstraint );

			//======= Optimisation ==============

			objFunction = Prm(Tf,defTerms.map( *objfn ));
			// Objective function is to be a function here. if it is a variable, we have to do something.
			Func const & _objTerm = Func::refc(kSystem, objFunction.TermHdl);
			switch ( _objTerm.ValueType() ) {	// clone a variable
				case DataStub<Flt>::DataTyp:
					objType = KFZ_FLOAT;
					if ( Var::suit(_objTerm) ) {
						StatRangeVarVf const & _objVar =  StatRangeVarVf::cast(_objTerm);
						objBound = Prm(Tf, kangaroo::StatRangeVarVf::def(kSystem, _objVar.StatLeftValue(), _objVar.StatRightValue()));
					} else
						objBound = Prm(Tf, kangaroo::StatRangeVarVf::def(kSystem));
					break;
				case DataStub<Bln>::DataTyp:
				case DataStub<Int>::DataTyp:
					objType = KFZ_INT;
					if ( Var::suit(_objTerm) ) {
						StatRangeVarVi const & _objVar = StatRangeVarVi::cast(_objTerm);
						objBound = Prm(Tf, kangaroo::StatRangeVarVi::def(kSystem, _objVar.StatLeftValue(), _objVar.StatRightValue()));
					} else
						objBound = Prm(Tf, kangaroo::StatRangeVarVi::def(kSystem));
					break;
				default:
					Alert( true, eUnregObjFunc);
					break;
			}

			Hdl h = InvHdl;
			if ( method == KFZ_MIN )
				h = BltuXiFcMi::def( Xv, kSystem, objFunction, objBound );
			else
				h = BgtuXiFcMi::def( Xv, kSystem, objFunction, objBound );

			if ( Term::refc(kSystem, h).MinHintLoc() == InvLoc )
				defConstraints.annex( Prm(h, Lm) );
			else
				defConstraints.annex( Prm(h, Dd) );	// By default, Dd is turn on
			constraintWeights.annex( 1 );

			if ( hasWeight )
				topOptimisation = WghtSumKiXiOFcMiD::def( Xm|On, kSystem, constraintWeights.items(), defConstraints.items(), defConstraints.size() );
			else
				topOptimisation = SumXiOFcMiD::def( Xm|On, kSystem, defConstraints.items(), defConstraints.size() );

			Prm _topOptimisation = Prm( topOptimisation, Rd );

			// CAN ONLY USE TABU_MAXMIN
			Prm __heap           = TabuMaxHeapHiFrHi::def(kSystem, _topOptimisation );
			kVarOptimisationSelc = RankVarSp::def( kSystem, __heap);
			if ( method == KFZ_MIN )
				kValOptimisationSelc = MinVal2SdXi::def( Xm, kSystem, _topOptimisation, Prm( objFunction, Mv ) );
			else
				kValOptimisationSelc = MinVal2SdXi::def( Xm, kSystem, _topOptimisation, Prm( UnegXiFeVi::def( Xv, kSystem, objFunction), Mv ) );

			useSwapSelc = false;
			if ( anns->hasAnn("tabu_maxmin") )	anns->findAnn("tabu_maxmin")->getInt(0, &kTabuTenure);
			else kTabuTenure = 1;

			kVarSelc = kVarConstraintSelc;
			kValSelc = kValConstraintSelc;
			useConstraintSelc = true;

		} else {
			Alert( true, eUndefSolveMethod );
		}

		if ( kTabuTenure > -1 )
			Sys::setVarTabuLimit(kSystem, kTabuTenure );

		generateRandomAssignment();

#if CompLazy
		Sys::setSelcActive( kSystem, kVarSelc, true );
		Sys::setSelcActive( kSystem, kValSelc, true );
#endif


		//		AnnSpec* ann = anns->findAnn("cutoff");
		//		if ( ann ) {
		//			int _runIters;
		//			if ( ann->getInt(0, &_runIters) ) runIters = _runIters;
		//		}
	}

	void FlatZincModel::run(std::ostream& os, unsigned runSeconds) {
/*
		os << endl;
		os << "SEED: " << kRnd.Seed() << endl;
		os << "timeout = " << runSeconds << " seconds" << endl << flush;

		os << "INITIAL ASSIGNMENT: " << endl;
		solution(os);
		os << endl;
*/
		cerr << endl;
		cerr << "SEED: " << kRnd.Seed() << endl;
		cerr << "timeout = " << runSeconds << " seconds" << endl << flush;

//		solution(os);
//		os << endl;


		initTimeCounter();
		switch (method) {
			case KFZ_MIN:
			case KFZ_MAX:
				optimise(os, runSeconds);
				break;
			case KFZ_SAT:
			default:
				satisfy(os, runSeconds);
				break;
		}
	}

	void FlatZincModel::optimise(std::ostream& os, unsigned runSeconds) {
#if ! defined(NDEBUG)
		if ( method == KFZ_MIN )
			cerr << "start minimization search\n";
		else
			cerr << "start maximization search\n";
#endif
		falsified = true;

		FcMDt<Int> const & Top = FcMDt<Int>::ref(kSystem, topConstraint);
		FcMDt<Int> const & Opt = FcMDt<Int>::ref(kSystem, topOptimisation);
		if ( method == KFZ_MIN )
			intLockVar( objBound, RngVi::ref(kSystem, objBound).RightValue() );
		else
			intLockVar( objBound, RngVi::ref(kSystem, objBound).LeftValue() );

		Sys const& ss = Sys::ref(kSystem);
		while ( elapsedTime() <= runSeconds ) {
			while ( elapsedTime() <= runSeconds && Opt.MetricRec().CurrData() ) {
				if ( Top.MetricRec().CurrData() < 10 ) {
					if ( useConstraintSelc ) {
#if CompLazy
						Sys::setSelcActive( kSystem, kVarConstraintSelc, false );
						Sys::setSelcActive( kSystem, kValConstraintSelc, false );

						Sys::setSelcActive( kSystem, kVarOptimisationSelc, true );
						Sys::setSelcActive( kSystem, kValOptimisationSelc, true );
#endif
						useConstraintSelc = false;
						kVarSelc = kVarOptimisationSelc;
						kValSelc = kValOptimisationSelc;
					}
				} else {
					if ( !useConstraintSelc ) {
#if CompLazy
						Sys::setSelcActive( kSystem, kVarConstraintSelc, true );
						Sys::setSelcActive( kSystem, kValConstraintSelc, true );

						Sys::setSelcActive( kSystem, kVarOptimisationSelc, false );
						Sys::setSelcActive( kSystem, kValOptimisationSelc, false );
#endif
						useConstraintSelc = true;
						kVarSelc = kVarConstraintSelc;
						kValSelc = kValConstraintSelc;
					}
				}
				Sys::doSelcPairExecDiff(kSystem, kVarSelc, kValSelc, kRnd);
			}

			if ( Opt.MetricRec().CurrData() == 0 ) {
				assert( objType == KFZ_INT );

				falsified = false;
				objIntVal = EvalTi::refCurrData( kSystem, Term::ref(kSystem, objFunction).ValueHdl() );
				intLockVar( objBound, objIntVal );

#if ! defined(NDEBUG)
				cerr << "New objective value: " << objIntVal << "\n";
#endif
			}
		}

		os << endl;
		os << "Final CPU time:   " << elapsedTime() << endl;
		os << "Final iterations: " << ss.ExecClk() << endl;
		os << "Final obj. value: " << objIntVal << endl << endl << flush;

		if ( falsified ) {
			os << "=====UNSATISFIABLE=====" << endl;
		} else {
			solution(os);
		}
		os << flush;
	}


	// Using one single selector
	void FlatZincModel::optimise2(std::ostream& os, unsigned runSeconds) {
#if ! defined(NDEBUG)
		if ( method == KFZ_MIN )
			cerr << "start minimization search\n";
		else
			cerr << "start maximization search\n";
#endif
		falsified = true;

		FcMDt<Int> const & Top = FcMDt<Int>::ref(kSystem, topConstraint);
		if ( method == KFZ_MIN )
			intLockVar( objBound, RngVi::ref(kSystem, objBound).RightValue() );
		else
			intLockVar( objBound, RngVi::ref(kSystem, objBound).LeftValue() );

		Sys const& ss = Sys::ref(kSystem);
		while ( elapsedTime() <= runSeconds ) {
			if ( useSwapSelc ) {
				while ( elapsedTime() <= runSeconds && Top.MetricRec().CurrData() ) {
					Sys::doSelcExecSwap(kSystem, kValSelc, kRnd);
				}
			} else {
				while ( elapsedTime() <= runSeconds && Top.MetricRec().CurrData() ) {
					Sys::doSelcPairExecDiff(kSystem, kVarSelc, kValSelc, kRnd);
				}
			}
			if ( Top.MetricRec().CurrData() == 0 ) {
				assert( objType == KFZ_INT );
				falsified = false;
				objIntVal = EvalTi::refCurrData( kSystem, Term::ref(kSystem, objFunction).ValueHdl() );
				intLockVar( objBound, objIntVal );

#if ! defined(NDEBUG)
				cerr << "New objective value: " << objIntVal << "\n";
#endif
			}
		}

		os << endl;
		os << "Final CPU time:   " << elapsedTime() << endl;
		os << "Final iterations: " << ss.ExecClk() << endl;
		os << "Final obj. value: " << objIntVal << endl << endl << flush;

		if ( falsified ) {
			os << "=====UNSATISFIABLE=====" << endl;
		} else {
			solution(os);
		}
		os << flush;
	}

	void FlatZincModel::satisfy(std::ostream& os, unsigned runSeconds) {
#if ! defined(NDEBUG)
		cerr << "start satisfiability search\n";
#endif
		FcMDt<Int> const & Top = FcMDt<Int>::ref(kSystem, topConstraint);

		long lIters = 0;
		Sys const& ss = Sys::ref(kSystem);
		if ( useSwapSelc ) {
			while ( elapsedTime() <= runSeconds && Top.MetricRec().CurrData() ) {
				Sys::doSelcExecSwap(kSystem, kValSelc, kRnd);
				++lIters;
			}
		} else {
//			cerr << "Iter: " << ss.ExecClk() << ", metric = " << Top.MetricRec().CurrData() << endl;
//			solution(cerr);

			while ( elapsedTime() <= runSeconds && Top.MetricRec().CurrData() ) {
//				cerr << "Iter: " << ss.ExecClk() << ", metric = " << Top.MetricRec().CurrData() << endl;
				Sys::doSelcPairExecDiff(kSystem, kVarSelc, kValSelc, kRnd);
				++lIters;
			}
		}

		os << endl;
		os << "Final CPU time:   " << elapsedTime() << endl;
		os << "Final iterations: " << lIters << endl;
		os << "Final exec clk:   " << ss.ExecClk() << endl;
		os << "Final metric is:  " << Top.MetricRec().CurrData() << endl << endl << flush;

		if ( Top.MetricRec().CurrData() ) {
			os << "=====UNSATISFIABLE=====" << endl;
		} else {
			solution(os);
		}
		os << flush;
	}

	void FlatZincModel::value(std::ostream& os, spec_t type, Hdl handle) {
		switch ( type ) {
			case KFZ_FLOAT:
				os << EvalTf::refCurrData( kSystem, Term::ref(kSystem, handle).ValueHdl() );
				break;
			case KFZ_BOOL:
			case KFZ_INT:
				os << EvalTi::refCurrData( kSystem, Term::ref(kSystem, handle).ValueHdl() );
				break;
			default:
				break;
		}
	}

	void FlatZincModel::solution(std::ostream& os) {
		for ( unsigned int i = 0; i < outputs.size(); ++i ) {
			OutSpec *out = outputs.item(i);
			os << out->name << " = ";
			if ( out->dimension ) {
				os << "array" << out->dimension << "d(";
				for ( unsigned int i = 0; i < out->dimension; ++i )
					os << out->l_indices.item(i) << ".." << out->r_indices.item(i) << ", ";
				os << "[";
				value( os, out->type, out->handles.item(0) );
				for ( unsigned int i = 1; i < out->handles.size(); ++i ) {
					os << ", ";
					value( os, out->type, out->handles.item(i) );
				}
				os << "]);" << endl;
			} else {
				value( os, out->type, out->handles.item(0) );
				os << ";" << endl;
			}
		}
		os << "----------" << endl;
	}

}
