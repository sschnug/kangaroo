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
 *     $Date: 2011-01-18 10:06:16 +0100 (di, 18 jan 2011) $ by $Author: tack $
 *     $Revision: 11538 $
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

#ifndef __KANGAROO_FLATZINC_PARSER_HH__
#define __KANGAROO_FLATZINC_PARSER_HH__

#include <iostream>
#include <algorithm>
#include <cstring>

// This is a workaround for a bug in flex that only shows up
// with the Microsoft C++ compiler
#if defined(_MSC_VER)
	#define YY_NO_UNISTD_H
	#ifdef __cplusplus
		extern "C" int isatty(int);
	#endif
#endif

// The Microsoft C++ compiler marks certain functions as deprecated,
// so let's take the alternative definitions
#if defined(_MSC_VER)
	#define strdup _strdup
	#define fileno _fileno
#endif

#include <string>

#include "flatzinc.hpp"
#include "defs.hpp"
#include "typespec.hpp"
#include "exprspec.hpp"

#include "parser.tab.hpp"

namespace FlatZinc {

	/// %State of the %FlatZinc parser
	class ParserState {
	public:
		ParserState(const std::string& b, std::ostream& _err, FlatZinc::FlatZincModel* _fzm)
			: buf(b.c_str()), pos(0), length(b.size()), fzm(_fzm),
			  hadError(false), annMode(false), err(_err)
		{}

		ParserState(char* _buf, int len, std::ostream& _err, FlatZinc::FlatZincModel* _fzm)
			: buf(_buf), pos(0), length(len), fzm(_fzm),
			  hadError(false), annMode(false), err(_err)
		{}

		void* yyscanner;
		const char* buf;
		unsigned int pos, length;
		FlatZinc::FlatZincModel* fzm;
		
		bool hadError;
		bool annMode;
		std::ostream& err;

		int fillBuffer(char* lexBuf, unsigned int lexBufSize) {
			if (pos >= length) return 0;
			int num = std::min(length - pos, lexBufSize);
			memcpy(lexBuf, buf + pos, num);
			pos += num;
			return num;
		}
	};

}

#endif
