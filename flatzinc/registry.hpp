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

#ifndef __KANGAROO_FLATZINC_REGISTRY_HH__
#define __KANGAROO_FLATZINC_REGISTRY_HH__

#include <string>
#include <map>
#include <set>

//#include "cbls/globals/idx.hh"

#include "exprspec.hpp"

namespace FlatZinc {

	/// Map from constraint identifier to constraint posting functions
	class Registry {
	public:
		/// Type of constraint posting function
		typedef kangaroo::Hdl (*poster) (kangaroo::Hdl&, ExprSpec*, ExprSpec*);

		/// Add posting function \a p with identifier \a id
		void add(const std::string& id, poster p);
		
		/// Mark a function as non-constraint
		void exclude(const std::string& id);
		
		/// Check whether a function is a constraint
		bool isConstraint(const std::string& id);

		/// Post constraint specified by \a ce
		kangaroo::Hdl post(kangaroo::Hdl& kSystem, std::string name, ExprSpec* es, ExprSpec* output = NULL);

	private:
		/// The actual registry
		std::map<std::string, poster> r;
		/// The non-constraint set
		std::set<std::string> exprs;
	};

	/// Return global registry object
	Registry& registry(void);

}

#endif

