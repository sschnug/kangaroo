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

#ifndef __KANGAROO_FLATZINC_HH__
#define __KANGAROO_FLATZINC_HH__

#include <iostream>
#include <cassert>

//#include "cbls/globals/idx.hh"
//#include "cbls/structs/idx.hh"
#include "cbls/frames/idx.hh"
#include "emu/cppl/idx.hh"
using namespace emu;

#include "defs.hpp"
#include "typespec.hpp"
#include "exprspec.hpp"
#include "defspec.hpp"
#include "outspec.hpp"

/**
 * \namespace FlatZinc
 * \brief Interpreter for the %FlatZinc language
 *
 * The FlatZinc namespace contains all functionality required
 * to parse and solve constraint models written in the %FlatZinc language.
 *
 */

namespace FlatZinc {

	/**
	 * \brief A space that can be initialized with
	 a %FlatZinc model
	 *
	 */
	class FlatZincModel {
	protected:
		static const
		unsigned int defSeconds = 10;

		static const
		unsigned int defIters = 10000;

//		int CCNT;
	public:
		FlatZincModel();

		~FlatZincModel();

		void setRandomSeed(unsigned seed);

		/*
		 * Create a new constant from specification.
		 * Return true if success, false if a constant 'name' is already defined.
		 */
		bool declConstant(char* c_name, TypeSpec* tspec, ExprSpec* espec);

		/*
		 * Create a new variable from specification.
		 * Return true if success, false if a variable 'name' is already defined.
		 */
		bool declVariable(char* c_name, TypeSpec* tspec, Annotations *anns, ExprSpec* espec = NULL);

		/*
		 * Post a constraint
		 */
		void postConstraint(char* c_name, ExprSpec* espec, Annotations* anns);

		/*
		 * post a solver
		 */
		void postSolver(method_t _method, std::string* objfn, Annotations* anns = NULL);
		void postSolver2(method_t _method, std::string* objfn, Annotations* anns = NULL);

		/*
		 * Run the search
		 */
		void run(std::ostream& os, unsigned runSeconds = defSeconds);

	private:
		Hdl  newConstant(TypeSpec* tspec, ExprSpec* espec);

		Hdl  newVariable(TypeSpec* tspec);
		bool getHdl(ExprSpec* e, Hdl* h);
		void postponeExprVar(std::string &name, std::string &expr_name, ExprSpec* e, OutSpec* o = NULL);

		void unfoldExprs(ExprSpec* es, b1<ExprSpec*,xmm>* undefs);
		int  getConstraintWeight(Annotations* anns, bool *flag);

		void intLockVar(Hdl var, int val);
		void initialiseRandomAssignment();

		void satisfy( std::ostream& os, unsigned runSeconds);
		void optimise(std::ostream& os, unsigned runSeconds);
		void optimise2(std::ostream& os, unsigned runSeconds);

		void value(std::ostream& os, spec_t t, Hdl h);
		void solution(std::ostream& os);

	protected:
		// Kangaroo CBLS system
		kangaroo::Hdl kSystem;
		kangaroo::Typ kTabuType;

		// Variable/value selector
		kangaroo::Hdl kVarSelc;
		kangaroo::Hdl kValSelc;

		bool useConstraintSelc;

		kangaroo::Hdl kVarConstraintSelc;
		kangaroo::Hdl kValConstraintSelc;

		kangaroo::Hdl kVarOptimisationSelc;
		kangaroo::Hdl kValOptimisationSelc;

		kangaroo::Prm topConstraint;
		kangaroo::Prm topOptimisation;

		kangaroo::Prm objFunction;
		kangaroo::Prm objBound;

		spec_t objType;
		Int    objIntVal;
		Flt    objFltVal;

		bool   falsified;	// used in optimisation

		bool useSwapSelc;

		int  kTabuTenure;

		Rnd  kRnd;

		template <typename value_t>
		struct strmap {
			typedef emu::hmap<std::string, value_t, xmm, emu::hashval<std::string>, emu::eqstr> type;
		};

		// List of defined terms: constants and variables
		strmap<kangaroo::Hdl>::type defTerms;

		// List of undefined variables
		strmap<CtrSpec*>::type undefTerms;

		// List of defined constraints
		emu::b1<kangaroo::Prm,xmm> defConstraints;

		// Weights of defined constraints
		emu::b1<kangaroo::Int,xmm> constraintWeights;

		bool hasWeight;

		// List of defined arrays of constants/variables
		strmap< std::pair<int,int> >::type defArrays;

		// Variable counter
		unsigned int nbVars;

		// List of output variables
		emu::b1<OutSpec*,xmm> outputs;

		// Whether to solve as satisfaction or optimization problem
		method_t method;
	};

	/*
	 * \brief Parse FlatZinc file \a fileName into \a fzs and return it.
	 *
	 * Creates a new empty FlatZincModel if \a fzs is NULL.
	 */
	FlatZincModel* parse(const std::string& fileName,
						 std::ostream& err = std::cerr,
						 unsigned int rndSeed = 0,
						 FlatZincModel* fzs=NULL);

	/*
	 * \brief Parse FlatZinc from \a is into \a fzs and return it.
	 *
	 * Creates a new empty FlatZincModel if \a fzs is NULL.
	 */
	FlatZincModel* parse(std::istream& is,
						 std::ostream& err = std::cerr,
						 unsigned int rndSeed = 0,
						 FlatZincModel* fzs=NULL);

}

#endif
