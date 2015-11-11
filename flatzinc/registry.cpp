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
 *  Contributing authors:
 *     Mikael Lagerkvist <lagerkvist@gmail.com>
 *
 *  Copyright:
 *     Guido Tack, 2007
 *     Mikael Lagerkvist, 2009
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

#include "cbls/funcs/idx.hh"

#include "registry.hpp"
#include "defs.hpp"

using namespace std;
using namespace kangaroo;

namespace FlatZinc {

	#define eDefConstraint(FUNC) "Constraint '" << FUNC << "' is not yet supported !!!"
	#define eDefVar(FUNC) "Only support defined_var = '" << FUNC << "' !!!"
	#define	eParamUeqSize(FUNC) "In constraint '" << FUNC << "': size mismatch between 'as' and 'bs' !!!"
	
	Registry& registry(void) {
		static Registry r;
		return r;
	}

	Hdl Registry::post(Hdl& kSystem, std::string name, ExprSpec* es, ExprSpec* output) {
		std::map<std::string,poster>::iterator i = r.find(name);
		
		Warn( i == r.end(), eDefConstraint(name.c_str()) );

		return i->second(kSystem, es, output);
	}

	void Registry::add(const std::string& id, poster p) {
		r[id] = p;
	}
	
	void Registry::exclude(const std::string& id) {
		cerr << " Add " << id << " to exclusive" << endl;
		exprs.insert(id);
		cerr << " new set: ";
		for (set<std::string>::iterator it=exprs.begin(); it!=exprs.end(); it++)
			cerr << " " << *it;
		cerr << endl;
	}
	
	bool Registry::isConstraint(const std::string& id) {
		cerr << "HHHHH " << id << "  " << ( exprs.find(id) == exprs.end() ) << " HHH";
		return ( exprs.find(id) == exprs.end() );
	}


	namespace {
		/**
		 * int comparisons
		 */
		
		/* a == b */
		Hdl p_int_eq(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BequXiFcMi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* a != b */
		Hdl p_int_ne(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BneuXiFcMi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* a <= b */
		Hdl p_int_le(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BleuXiFcMi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* a < b */
		Hdl p_int_lt(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BltuXiFcMi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* a >= b */
		Hdl p_int_ge(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BgeuXiFcMi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* a > b */
		Hdl p_int_gt(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BgtuXiFcMi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}

		/* (a == b) == r */
		Hdl p_int_eq_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in int_eq_reif(a,b,r)") );

			Hdl op = BeqsXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a != b) == r */
		Hdl p_int_ne_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in int_ne_reif(a,b,r)") );

			Hdl op = BnesXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a <= b) == r */
		Hdl p_int_le_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in int_le_reif(a,b,r)") );

			Hdl op = BlesXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a < b) == r */
		Hdl p_int_lt_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in int_lt_reif(a,b,r)") );

			Hdl op = BltsXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a >= b) == r */
		Hdl p_int_ge_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in int_ge_reif(a,b,r)") );

			Hdl op = BgesXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a > b) == r */
		Hdl p_int_gt_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in int_gt_reif(a,b,r)") );
			
			Hdl op = BgtsXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}

		/* sum(as[i]*bs[i]) */
		Hdl int_lin(Hdl& kSystem, ExprSpec* as, ExprSpec* bs) {
			Warn( as->size() != bs->size(), eParamUeqSize("int_lin_*") );

			size_t sz = as->size();
			if ( sz == 1 ) {
				return UmultXiFeVi::def(Xv, kSystem, bs->getHdl(kSystem, 0), (*as)[0]->value.ival);
			}
			kblock<Prm> params(sz);
			kblock<Int> coefs(sz);
			for ( unsigned int i = 0; i < sz; ++i ) {
				params[i] = bs->getHdl(kSystem, i);
				coefs[i]  = (*as)[i]->value.ival;
			}
			return WghtSumKiXiFeVi::def(Xv, kSystem, coefs.items(), params.items(), sz);
		}
		/* sum(as[i]*bs[i]) : replace the (bs[i]==out) with c */
		Hdl int_lin_swap(Hdl& kSystem, ExprSpec* as, ExprSpec* bs, ExprSpec* c, ExprSpec* o) {
			Warn( as->size() != bs->size(), eParamUeqSize("int_lin_*") );
			
			size_t sz = as->size();
			kblock<Prm> params(sz);
			kblock<Int> coefs(sz);
			int sgn = 1;
			for ( unsigned int i = 0; i < sz; ++i ) {
				if ( (*bs)[i] == o ) {
					int coef = (*as)[i]->value.ival;
					Warn( abs(coef) != 1, "Constraint int_lin_*: The coefficient of defined_var must be -1 or 1!!!");
					sgn       = ( coef == -1 ? 1 : -1 );
					params[i] = c->getHdl(kSystem, 0);
				} else
					params[i] = bs->getHdl(kSystem, i);
			}
			for ( unsigned int i = 0; i < sz; ++i ) 
				coefs[i]  = sgn * ( (*as)[i]->value.ival );

//			cerr << "     int_lin_swap*" << endl;
//			cerr << "         as = [ ";
//			for ( unsigned int i = 0; i < sz - 1; ++i ) cerr << coefs[i] << ", ";
//			cerr << coefs[sz - 1] << " ]" << endl;
//			cerr << "         bs = [ ";
//			for ( unsigned int i = 0; i < sz - 1; ++i ) cerr << params[i].TermHdl << ", ";
//			cerr << params[sz - 1].TermHdl << " ]" << endl;
//			cerr << endl;

			return WghtSumKiXiFeVi::def(Xv, kSystem, coefs.items(), params.items(), sz);
		}

		/* sum(as[i]*bs[i]) == c */
		Hdl p_int_lin_eq(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			if ( output ) {
				if ( (*es)[2] == output ) 
					return int_lin( kSystem, (*es)[0], (*es)[1] );
				else 
					return int_lin_swap( kSystem, (*es)[0], (*es)[1], (*es)[2], output );
			}
			
			Hdl sum = int_lin( kSystem, (*es)[0], (*es)[1] );
			return BequXiFcMi::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}
		/* sum(as[i]*bs[i]) != c */
		Hdl p_int_lin_ne(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Hdl sum = int_lin( kSystem, (*es)[0], (*es)[1] );
			return BneuXiFcMi::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}
		/* sum(as[i]*bs[i]) <= c */
		Hdl p_int_lin_le(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Hdl sum = int_lin( kSystem, (*es)[0], (*es)[1] );
			return BleuXiFcMi::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}
		/* sum(as[i]*bs[i]) < c */
		Hdl p_int_lin_lt(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Hdl sum = int_lin( kSystem, (*es)[0], (*es)[1] );
			return BltuXiFcMi::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}
		/* sum(as[i]*bs[i]) >= c */
		Hdl p_int_lin_ge(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Hdl sum = int_lin( kSystem, (*es)[0], (*es)[1] );
			return BgeuXiFcMi::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}
		/* sum(as[i]*bs[i]) > c */
		Hdl p_int_lin_gt(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Hdl sum = int_lin( kSystem, (*es)[0], (*es)[1] );
			return BgtuXiFcMi::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}

		/* ( sum(as[i]*bs[i]) == c ) == r */
		Hdl p_int_lin_eq_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in int_lin_eq_reif(as,bs,c,r)") );

			Hdl op = BeqsXiFeVi::def( Xv, kSystem, int_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}
		/* ( sum(as[i]*bs[i]) != c ) == r */
		Hdl p_int_lin_ne_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in int_lin_ne_reif(as,bs,c,r)") );

			Hdl op = BnesXiFeVi::def( Xv, kSystem, int_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}
		/* ( sum(as[i]*bs[i]) <= c ) == r */
		Hdl p_int_lin_le_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in int_lin_le_reif(as,bs,c,r)") );
			
			Hdl op = BlesXiFeVi::def( Xv, kSystem, int_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}
		/* ( sum(as[i]*bs[i]) < c ) == r */
		Hdl p_int_lin_lt_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in int_lin_lt_reif(as,bs,c,r)") );

			Hdl op = BltsXiFeVi::def( Xv, kSystem, int_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}
		/* ( sum(as[i]*bs[i]) >= c ) == r */
		Hdl p_int_lin_ge_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in int_lin_ge_reif(as,bs,c,r)") );
			
			Hdl op = BgesXiFeVi::def( Xv, kSystem, int_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}
		/* ( sum(as[i]*bs[i]) > c ) == r */
		Hdl p_int_lin_gt_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in int_lin_gt_reif(as,bs,c,r)") );
			
			Hdl op = BgtsXiFeVi::def( Xv, kSystem, int_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}

		/**
		 * int arithmetic constraints
		 */

		/* a + b == c */
		Hdl p_int_plus(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("int_plus(a, b)") );
			
			Hdl op = BaddXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BequXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* a - b == c */
		Hdl p_int_minus(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("int_minus(a, b)") );
			
			Hdl op = BsubXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BequXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* a * b == c */
		Hdl p_int_times(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("int_times(a, b)") );
			
			Hdl op = BmultXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;

			return BequXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* a / b == c */
		Hdl p_int_div(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("int_div(a, b)") );

			Hdl op = BdivXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BequXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* a % b == c */
		Hdl p_int_mod(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("int_mod(a, b)") );
			
			Hdl op = BmodXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BequXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* min(a, b) == c */
		Hdl p_int_min(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("int_min(a, b)") );
			
			Hdl op = es->getHdl(kSystem, 0);
			Hdl h1 = es->getHdl(kSystem, 1);
			if ( op != h1 )
				op = BminXiFeVi::def( Xv, kSystem, op, h1 );
			if ( output ) return op;
			
			return BequXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* max(a, b) == c */
		Hdl p_int_max(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("int_max(a, b)") );
			
			Hdl op = es->getHdl(kSystem, 0);
			Hdl h1 = es->getHdl(kSystem, 1);
			if ( op != h1 )
				op = BmaxXiFeVi::def( Xv, kSystem, op, h1 );
			if ( output ) return op;
			
			return BequXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}

		/* abs(a) */
		Hdl p_int_abs(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return UabsXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0) );
		}

		Hdl p_int2float(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return UcastXiFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
		}
		
		/**
		 * bool comparisons
		 */
		
		/* a == b */
		Hdl p_bool_eq(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BxnoruXiFcMi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* a != b */
		Hdl p_bool_ne(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BxoruXiFcMi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* -a v b */
		Hdl p_bool_le(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BimplyuXiFcMi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* -a ^ b */
		Hdl p_bool_lt(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BnimplyuXiFcMi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}

		/* (a == b) == r */
		Hdl p_bool_eq_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in ( bool_eq(a, b) == r )") );

			Hdl op = BxnorsXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a != b) == r */
		Hdl p_bool_ne_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in ( bool_ne(a, b) == r )") );
			
			Hdl op = BxorsXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (-a v b) == r */
		Hdl p_bool_le_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in ( bool_le(a, b) == r )") );
			
			Hdl op = BimplysXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (-a ^ b) == r */
		Hdl p_bool_lt_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in ( bool_lt(a, b) == r )") );
			
			Hdl op = BnimplysXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}

		/* (a ^ b) == r */
		Hdl p_bool_and(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in ( bool_and(a, b) == r )") );
			
			Hdl op = BandsXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a v b) == r */
		Hdl p_bool_or(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in ( bool_or(a, b) == r )") );
			
			Hdl op = BorsXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a != b) == r */
		Hdl p_bool_xor(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in ( bool_xor(a, b) == r )") );
			
			Hdl op = BxorsXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* -a == b */
		Hdl p_bool_not(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("b in ( bool_not(a) == r )") );
			
			if ( output ) return UnotsXiFeVi::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			
			return BxoruXiFcMi::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}

		/* array_or(as) v array_or(-bs) */
		/* TODO: update once 'array_nand' is implemented */
		Hdl p_bool_clause(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			ExprSpec* pos = (*es)[0];
			ExprSpec* neg = (*es)[1];
			nblock<Prm> prm( pos->size() + neg->size() );
			for ( unsigned i = 0; i < pos->size(); ++i )
				prm.append( Prm( pos->getHdl(kSystem, i) ) );
			for ( unsigned i = 0; i < pos->size(); ++i )
				prm.append( Prm( UnotsXiFeVi::def( Xv, kSystem, neg->getHdl(kSystem, i) ) ) );
			
			return OruXiFcMi::def( Xv, kSystem, prm.items(), prm.size() );
		}

		/* array_and(as) == r */
		Hdl p_array_bool_and(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("r in ( array_bool_and(as) == r )") );
			
			ExprSpec* as = (*es)[0];
			nblock<Prm> prm( as->size() );
			for ( unsigned i = 0; i < as->size(); ++i )
				prm.append( Prm( as->getHdl(kSystem, i) ) );

			Hdl op = AndsXiFeVi::def( Xv, kSystem, prm.items(), prm.size() );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* array_or(as) == r */
		Hdl p_array_bool_or(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("r in ( array_bool_or(as) == r )") );
			
			ExprSpec* as = (*es)[0];
			nblock<Prm> prm( as->size() );
			for ( unsigned i = 0; i < as->size(); ++i )
				prm.append( Prm( as->getHdl(kSystem, i) ) );
			
			Hdl op = OrsXiFeVi::def( Xv, kSystem, prm.items(), prm.size() );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}

		/* ( sum(as[i]) mod 2 ) == 1 */
		Hdl p_array_bool_xor(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("r in ( array_bool_xor(as) == r )") );
			
//			ExprSpec* as = (*es)[0];
//			nblock<Prm> prm( as->size() );
//			for ( unsigned i = 0; i < as->size(); ++i )
//				prm.append( Prm( as->getHdl(kSystem, i) ) );
//
//			Hdl op = XorsXiFeVi::def( Xv, kSystem, prm.items(), prm.size() );
//			if ( output ) return op;
//			
//			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
			cerr << "array_bool_xor(" << (*es)[0] <<  ", " << (*es)[1] << ")" << endl;
			return InvHdl;
		}
		
		Hdl p_bool2int(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return es->getHdl(kSystem, 0);
		}
		

		/* element constraints */
		Hdl p_array_int_element(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("c in ( array_int_element(as[b]) == c )") );
			
			ExprSpec* as = (*es)[1];
			nblock<Prm> prm( as->size() + 1 );
			for ( unsigned i = 0; i < as->size(); ++i )
				prm.append( Prm( as->getHdl(kSystem, i) ) );
			prm.append( Prm( (*es)[0]->getHdl(kSystem, 0) ) );
			
			Hdl op = LstIdxXiYiFeVi::def( Xv, kSystem, prm.items(), prm.size() );
			if ( output ) return op;
			
			return BequXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		Hdl p_array_bool_element(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("c in ( array_bool_element(as[b]) == c )") );
			
			ExprSpec* as = (*es)[1];
			nblock<Prm> prm( as->size() + 1 );
			for ( unsigned i = 0; i < as->size(); ++i )
				prm.append( Prm( as->getHdl(kSystem, i) ) );
			prm.append( Prm( (*es)[0]->getHdl(kSystem, 0) ) );

			Hdl op = LstIdxXiYiFeVi::def( Xv, kSystem, prm.items(), prm.size() );
			if ( output ) return op;
			
			return BxnoruXiFcMi::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}

		class IntPoster {
		public:
			IntPoster(void) {
				registry().add("int_eq", &p_int_eq);
				registry().add("int_ne", &p_int_ne);
				registry().add("int_le", &p_int_le);
				registry().add("int_lt", &p_int_lt);
				registry().add("int_ge", &p_int_ge);
				registry().add("int_gt", &p_int_gt);
				registry().add("int_eq_reif", &p_int_eq_reif);
				registry().add("int_ne_reif", &p_int_ne_reif);
				registry().add("int_le_reif", &p_int_le_reif);
				registry().add("int_lt_reif", &p_int_lt_reif);
				registry().add("int_ge_reif", &p_int_ge_reif);
				registry().add("int_gt_reif", &p_int_gt_reif);
				registry().add("int_lin_eq", &p_int_lin_eq);
				registry().add("int_lin_eq_reif", &p_int_lin_eq_reif);
				registry().add("int_lin_ne", &p_int_lin_ne);
				registry().add("int_lin_ne_reif", &p_int_lin_ne_reif);
				registry().add("int_lin_le", &p_int_lin_le);
				registry().add("int_lin_le_reif", &p_int_lin_le_reif);
				registry().add("int_lin_lt", &p_int_lin_lt);
				registry().add("int_lin_lt_reif", &p_int_lin_lt_reif);
				registry().add("int_lin_ge", &p_int_lin_ge);
				registry().add("int_lin_ge_reif", &p_int_lin_ge_reif);
				registry().add("int_lin_gt", &p_int_lin_gt);
				registry().add("int_lin_gt_reif", &p_int_lin_gt_reif);
				registry().add("int_plus", &p_int_plus);
				registry().add("int_minus", &p_int_minus);
				registry().add("int_times", &p_int_times);
				registry().add("int_div", &p_int_div);
				registry().add("int_mod", &p_int_mod);
				registry().add("int_min", &p_int_min);
				registry().add("int_max", &p_int_max);
				registry().add("int_abs", &p_int_abs);
				registry().add("int2float", &p_int2float);
				registry().add("bool_eq", &p_bool_eq);
				registry().add("bool_ne", &p_bool_ne);
				registry().add("bool_le", &p_bool_le);
				registry().add("bool_lt", &p_bool_lt);
				registry().add("bool_eq_reif", &p_bool_eq_reif);
				registry().add("bool_ne_reif", &p_bool_ne_reif);
				registry().add("bool_le_reif", &p_bool_le_reif);
				registry().add("bool_lt_reif", &p_bool_lt_reif);
				registry().add("bool_or", &p_bool_or);
				registry().add("bool_and", &p_bool_and);
				registry().add("bool_xor", &p_bool_xor);
				registry().add("array_bool_and", &p_array_bool_and);
				registry().add("array_bool_or", &p_array_bool_or);
				registry().add("array_bool_xor", &p_array_bool_xor);
				registry().add("bool_clause", &p_bool_clause);
				registry().add("bool_not", &p_bool_not);
				registry().add("array_int_element", &p_array_int_element);
				registry().add("array_var_int_element", &p_array_int_element);
				registry().add("array_bool_element", &p_array_bool_element);
				registry().add("array_var_bool_element", &p_array_bool_element);
				registry().add("bool2int", &p_bool2int);
				
//				registry().exclude("int2float");
//				registry().exclude("bool2int");
			}
		};
		IntPoster __int_poster;

		
		/**
		 * float comparisons
		 */
		
		/* a == b */
		Hdl p_float_eq(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BequXfFcMf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* a != b */
		Hdl p_float_ne(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BneuXfFcMf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* a <= b */
		Hdl p_float_le(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BleuXfFcMf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* a < b */
		Hdl p_float_lt(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BltuXfFcMf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* a >= b */
		Hdl p_float_ge(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BgeuXfFcMf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		/* a > b */
		Hdl p_float_gt(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return BgtuXfFcMf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
		}
		
		/* (a == b) == r */
		Hdl p_float_eq_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in float_eq_reif(a, b, r)") );
			
			Hdl op = BeqsXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a != b) == r */
		Hdl p_float_ne_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in float_ne_reif(a, b, r)") );
			
			Hdl op = BnesXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a <= b) == r */
		Hdl p_float_le_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in float_le_reif(a, b, r)") );
			
			Hdl op = BlesXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a < b) == r */
		Hdl p_float_lt_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in float_lt_reif(a, b, r)") );
			
			Hdl op = BltsXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a >= b) == r */
		Hdl p_float_ge_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in float_ge_reif(a, b, r)") );
			
			Hdl op = BgesXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* (a > b) == r */
		Hdl p_float_gt_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("r in float_gt_reif(a, b, r)") );
			
			Hdl op = BgtsXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		
		/* sum(as[i]*bs[i]) */
		Hdl float_lin(Hdl& kSystem, ExprSpec* as, ExprSpec* bs) {
			Warn( as->size() != bs->size(), eParamUeqSize("float_lin_*") );
		
			size_t sz = as->size();
			if ( sz == 1 ) {
				return UmultXfFeVf::def(Xv, kSystem, bs->getHdl(kSystem, 0), (*as)[0]->value.ival);
			}

			kblock<Prm> params(sz);
			kblock<Flt> coefs(sz);
			for ( unsigned int i = 0; i < sz; ++i ) {
				params[i] = bs->getHdl(kSystem, i);
				coefs[i]  = (*as)[i]->value.fval;
			}
			return WghtSumKfXfFeVf::def(Xv, kSystem, coefs.items(), params.items(), sz);
		}
		/* sum(as[i]*bs[i]) == c */
		Hdl p_float_lin_eq(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("c in float_lin_eq(a, b, c)") );
			
			Hdl sum = float_lin( kSystem, (*es)[0], (*es)[1] );
			if ( output ) return sum;
			
			return BequXfFcMf::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}
		/* sum(as[i]*bs[i]) != c */
		Hdl p_float_lin_ne(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Hdl sum = float_lin( kSystem, (*es)[0], (*es)[1] );
			return BneuXfFcMf::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}
		/* sum(as[i]*bs[i]) <= c */
		Hdl p_float_lin_le(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Hdl sum = float_lin( kSystem, (*es)[0], (*es)[1] );
			return BleuXfFcMf::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}
		/* sum(as[i]*bs[i]) < c */
		Hdl p_float_lin_lt(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Hdl sum = float_lin( kSystem, (*es)[0], (*es)[1] );
			return BltuXfFcMf::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}
		/* sum(as[i]*bs[i]) >= c */
		Hdl p_float_lin_ge(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Hdl sum = float_lin( kSystem, (*es)[0], (*es)[1] );
			return BgeuXfFcMf::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}
		/* sum(as[i]*bs[i]) > c */
		Hdl p_float_lin_gt(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Hdl sum = float_lin( kSystem, (*es)[0], (*es)[1] );
			return BgtuXfFcMf::def( Xv, kSystem, sum, es->getHdl(kSystem, 2) );
		}
		
		/* ( sum(as[i]*bs[i]) == c ) == r */
		Hdl p_float_lin_eq_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in float_lin_eq_reif(a, b, c, r)") );
			
			Hdl op = BeqsXfFeVf::def( Xv, kSystem, float_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}
		/* ( sum(as[i]*bs[i]) != c ) == r */
		Hdl p_float_lin_ne_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in float_lin_ne_reif(a, b, c, r)") );
			
			Hdl op = BnesXfFeVf::def( Xv, kSystem, float_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}
		/* ( sum(as[i]*bs[i]) <= c ) == r */
		Hdl p_float_lin_le_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in float_lin_le_reif(a, b, c, r)") );
			
			Hdl op = BlesXfFeVf::def( Xv, kSystem, float_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}
		/* ( sum(as[i]*bs[i]) < c ) == r */
		Hdl p_float_lin_lt_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in float_lin_lt_reif(a, b, c, r)") );
			
			Hdl op = BltsXfFeVf::def( Xv, kSystem, float_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}
		/* ( sum(as[i]*bs[i]) >= c ) == r */
		Hdl p_float_lin_ge_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in float_lin_ge_reif(a, b, c, r)") );
			
			Hdl op = BgesXfFeVf::def( Xv, kSystem, float_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}
		/* ( sum(as[i]*bs[i]) > c ) == r */
		Hdl p_float_lin_gt_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[3] != output ), eDefVar("r in float_lin_gt_reif(a, b, c, r)") );
			
			Hdl op = BgtsXfFeVf::def( Xv, kSystem, float_lin( kSystem, (*es)[0], (*es)[1] ), es->getHdl(kSystem, 2) );
			if ( output ) return op;
			
			return BxnoruXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 3) );
		}
		
		/**
		 * float arithmetic constraints
		 */
		
		/* a + b == c */
		Hdl p_float_plus(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("float_plus(a, b)") );
			
			Hdl op = BaddXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* a - b == c */
		Hdl p_float_minus(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("float_minus(a, b)") );
			
			Hdl op = BsubXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* a * b == c */
		Hdl p_float_times(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("float_times(a, b)") );
			
			Hdl op = BmultXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* a / b == c */
		Hdl p_float_div(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("float_div(a, b)") );
			
			Hdl op = BdivXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* a % b == c */
		Hdl p_float_mod(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("float_mod(a, b)") );
			
			Hdl op = BmodXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0), es->getHdl(kSystem, 1) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* min(a, b) == c */
		Hdl p_float_min(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("float_min(a, b)") );
			
			Hdl op = es->getHdl(kSystem, 0);
			Hdl h1 = es->getHdl(kSystem, 1);
			if ( op != h1 )
				op = BminXfFeVf::def( Xv, kSystem, op, h1 );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}
		/* max(a, b) == c */
		Hdl p_float_max(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("float_max(a, b)") );
			
			Hdl op = es->getHdl(kSystem, 0);
			Hdl h1 = es->getHdl(kSystem, 1);
			if ( op != h1 )
				op = BmaxXfFeVf::def( Xv, kSystem, op, h1 );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}

		/* acos(a) == b */
		Hdl p_float_acos(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_acos(a)") );
			
			Hdl op = UacosXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* asin(a) == b */
		Hdl p_float_asin(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_asin(a)") );
			
			Hdl op = UasinXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* atan(a) == b */
		Hdl p_float_atan(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_atan(a)") );
			
			Hdl op = UatanXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* cos(a) == b */
		Hdl p_float_cos(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_cos(a)") );
			
			Hdl op = UcosXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* sin(a) == b */
		Hdl p_float_sin(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_sin(a)") );
			
			Hdl op = UsinXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* tan(a) == b */
		Hdl p_float_tan(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_tan(a)") );
			
			Hdl op = UtanXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* cosh(a) == b */
		Hdl p_float_cosh(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_cosh(a)") );
			
			Hdl op = UcoshXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* sinh(a) == b */
		Hdl p_float_sinh(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_sinh(a)") );
			
			Hdl op = UsinhXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* tanh(a) == b */
		Hdl p_float_tanh(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_tanh(a)") );
			
			Hdl op = UtanhXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* exp(a) == b */
		Hdl p_float_exp(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_exp(a)") );
			
			Hdl op = UexpXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* ln(a) == b */
		Hdl p_float_ln(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_ln(a)") );
			
			Hdl op = UlogXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* log_10(a) == b */
		Hdl p_float_log10(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_log10(a)") );
			
			Hdl op = Ulog10XfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* log_2(a) == b */
		Hdl p_float_log2(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_log2(a)") );
			
			Hdl op = Ulog2XfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		/* sqrt(a) == b */
		Hdl p_float_sqrt(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("float_sqrt(a)") );
			
			Hdl op = UsqrtXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 1) );
		}
		
		/* abs(a) */
		Hdl p_float_abs(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return UabsXfFeVf::def( Xv, kSystem, es->getHdl(kSystem, 0) );
		}
		
		/* element constraints */
		Hdl p_array_float_element(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[2] != output ), eDefVar("c in ( array_float_element(as[b]) == c )") );
			
			ExprSpec* as = (*es)[1];
			nblock<Prm> prm( as->size() + 1 );
			for ( unsigned i = 0; i < as->size(); ++i )
				prm.append( Prm( as->getHdl(kSystem, i) ) );
			prm.append( Prm( (*es)[0]->getHdl(kSystem, 0) ) );
			
			Hdl op = LstIdxXfYiFeVf::def( Xv, kSystem, prm.items(), prm.size() );
			if ( output ) return op;
			
			return BequXfFcMf::def( Xv, kSystem, op, es->getHdl(kSystem, 2) );
		}

		class FloatPoster {
		public:
			FloatPoster(void) {
				registry().add("float_eq", &p_float_eq);
				registry().add("float_ne", &p_float_ne);
				registry().add("float_le", &p_float_le);
				registry().add("float_lt", &p_float_lt);
				registry().add("float_ge", &p_float_ge);
				registry().add("float_gt", &p_float_gt);
				registry().add("float_eq_reif", &p_float_eq_reif);
				registry().add("float_ne_reif", &p_float_ne_reif);
				registry().add("float_le_reif", &p_float_le_reif);
				registry().add("float_lt_reif", &p_float_lt_reif);
				registry().add("float_ge_reif", &p_float_ge_reif);
				registry().add("float_gt_reif", &p_float_gt_reif);
				registry().add("float_lin_eq", &p_float_lin_eq);
				registry().add("float_lin_eq_reif", &p_float_lin_eq_reif);
				registry().add("float_lin_ne", &p_float_lin_ne);
				registry().add("float_lin_ne_reif", &p_float_lin_ne_reif);
				registry().add("float_lin_le", &p_float_lin_le);
				registry().add("float_lin_le_reif", &p_float_lin_le_reif);
				registry().add("float_lin_lt", &p_float_lin_lt);
				registry().add("float_lin_lt_reif", &p_float_lin_lt_reif);
				registry().add("float_lin_ge", &p_float_lin_ge);
				registry().add("float_lin_ge_reif", &p_float_lin_ge_reif);
				registry().add("float_lin_gt", &p_float_lin_gt);
				registry().add("float_lin_gt_reif", &p_float_lin_gt_reif);
				registry().add("float_plus", &p_float_plus);
				registry().add("float_minus", &p_float_minus);
				registry().add("float_times", &p_float_times);
				registry().add("float_div", &p_float_div);
				registry().add("float_mod", &p_float_mod);
				registry().add("float_min", &p_float_min);
				registry().add("float_max", &p_float_max);
				registry().add("float_cos", &p_float_cos);
				registry().add("float_sin", &p_float_sin);
				registry().add("float_tan", &p_float_tan);
				registry().add("float_acos", &p_float_acos);
				registry().add("float_asin", &p_float_asin);
				registry().add("float_atan", &p_float_atan);
				registry().add("float_cosh", &p_float_cosh);
				registry().add("float_sinh", &p_float_sinh);
				registry().add("float_tanh", &p_float_tanh);
				registry().add("float_exp", &p_float_exp);
				registry().add("float_ln", &p_float_ln);
				registry().add("float_log10", &p_float_log10);
				registry().add("float_log2", &p_float_log2);
				registry().add("float_sqrt", &p_float_sqrt);
				registry().add("float_abs", &p_float_abs);
				registry().add("array_float_element", &p_array_float_element);
				registry().add("array_var_float_element", &p_array_float_element);
			}
		};
		FloatPoster __float_poster;
		

		Hdl p_set_union(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_union(" << (*es)[0] <<  ", " << (*es)[1] <<  ", " << (*es)[2] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_intersect(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_intersect(" << (*es)[0] <<  ", " << (*es)[1] <<  ", " << (*es)[2] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_diff(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_diff(" << (*es)[0] <<  ", " << (*es)[1] <<  ", " << (*es)[2] << ")" << endl;
			return InvHdl;
		}

		Hdl p_set_symdiff(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_symdiff(" << (*es)[0] <<  ", " << (*es)[1] <<  ", " << (*es)[2] << ")" << endl;
			return InvHdl;
		}

		Hdl p_set_eq(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_eq(" << (*es)[0] <<  ", " << (*es)[1] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_ne(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_ne(" << (*es)[0] <<  ", " << (*es)[1] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_subset(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_subset(" << (*es)[0] <<  ", " << (*es)[1] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_superset(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_superset(" << (*es)[0] <<  ", " << (*es)[1] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_card(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_card(" << (*es)[0] <<  ", " << (*es)[1] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_in(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_in(" << (*es)[0] <<  ", " << (*es)[1] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_eq_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_eq_reif(" << (*es)[0] <<  ", " << (*es)[1] <<  ", " << (*es)[2] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_ne_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_ne_reif(" << (*es)[0] <<  ", " << (*es)[1] <<  ", " << (*es)[2] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_subset_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_subset_reif(" << (*es)[0] <<  ", " << (*es)[1] <<  ", " << (*es)[2] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_superset_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_superset_reif(" << (*es)[0] <<  ", " << (*es)[1] <<  ", " << (*es)[2] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_in_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_in_reif(" << (*es)[0] <<  ", " << (*es)[1] <<  ", " << (*es)[2] << ")" << endl;
			return InvHdl;
		}
		Hdl p_set_disjoint(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "set_disjoint(" << (*es)[0] <<  ", " << (*es)[1] << ")" << endl;
			return InvHdl;
		}

		Hdl p_array_set_element(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			cerr << "array_set_element(" << (*es)[0] <<  ", " << (*es)[1] <<  ", " << (*es)[2] << ")" << endl;
			return InvHdl;
		}


		class SetPoster {
		public:
			SetPoster(void) {
				registry().add("set_eq", &p_set_eq);
				registry().add("set_ne", &p_set_ne);
				registry().add("set_union", &p_set_union);
				registry().add("array_set_element", &p_array_set_element);
				registry().add("array_var_set_element", &p_array_set_element);
				registry().add("set_intersect", &p_set_intersect);
				registry().add("set_diff", &p_set_diff);
				registry().add("set_symdiff", &p_set_symdiff);
				registry().add("set_subset", &p_set_subset);
				registry().add("set_superset", &p_set_superset);
				registry().add("set_card", &p_set_card);
				registry().add("set_in", &p_set_in);
				registry().add("set_eq_reif", &p_set_eq_reif);
				registry().add("equal_reif", &p_set_eq_reif);
				registry().add("set_ne_reif", &p_set_ne_reif);
				registry().add("set_subset_reif", &p_set_subset_reif);
				registry().add("set_superset_reif", &p_set_superset_reif);
				registry().add("set_in_reif", &p_set_in_reif);
				registry().add("disjoint", &p_set_disjoint);
			}
		};
//		SetPoster __set_poster;

		
		/* defined_var(a) */
		Hdl p_defined_var(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			return es->getHdl(kSystem, 0);
		}
		
		/* int_all_different(as) */
		Hdl p_int_all_different(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			ExprSpec* as = (*es)[0];
			size_t sz = as->size(); 
			kblock<Prm> params(sz);
			for ( unsigned int i = 0; i < sz; ++i ) {
				params[i] = as->getHdl(kSystem, i);
			}
			return AllDiffXiFcMiD::def(Xv, kSystem, params.items(), sz);
		}

		Hdl p_int_all_different_reif(Hdl& kSystem, ExprSpec* es, ExprSpec* output) {
			Warn( output && ( (*es)[1] != output ), eDefVar("kangaroo_int_all_different_reif(a)") );
			
			ExprSpec* as = (*es)[0];
			size_t sz = as->size(); 
			kblock<Prm> params(sz);
			for ( unsigned int i = 0; i < sz; ++i ) {
				params[i] = as->getHdl(kSystem, i);
			}
			Hdl op = AllDiffXiFcMiD::def(Xv, kSystem, params.items(), sz);
			
			if ( output ) return op;
			
			return BequXiFcMi::def( Xv, kSystem, Prm(op, Vm), es->getHdl(kSystem, 1) );
		}
		

		class GlobalPoster {
		public:
			GlobalPoster(void) {
				registry().add("defined_var", &p_defined_var);
				registry().add("kangaroo_int_all_different", &p_int_all_different);
				registry().add("kangaroo_int_all_different_reif", &p_int_all_different_reif);
			}
		};
		GlobalPoster __global_poster;


	}
}

