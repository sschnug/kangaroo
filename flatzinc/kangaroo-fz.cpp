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

#include <iostream>
#include <fstream>
#include <cstring>

#include "flatzinc.hpp"
#include "cbls/opt.hh"

using namespace std;

#define usage \
{ \
	cerr << "Usage: " << argv[0] << " <file> [-seed <seed>] [-timeout <seconds>]" << endl; \
	exit(EXIT_FAILURE); \
}

#define getInt(N, ARGS, IDX, VAR) \
{ \
	if ( IDX>=N || sscanf(ARGS[IDX], "%i", &VAR) != 1 ) { \
		usage; \
	} \
}

int main(int argc, char** argv) {
	if ( argc < 2 ) usage;

	unsigned runSeed    = 0;
	unsigned runSeconds = 10;

	const char* filename = argv[1];
	for ( int i = 2; i < argc; ++i ) {
		if ( strcmp(argv[i], "-seed") == 0 ) {
			++i;
			getInt(argc, argv, i, runSeed);
//			runSeed = 1313031311u;
		} else if (strcmp(argv[i],"-timeout") == 0) {
			++i;
			getInt(argc, argv, i, runSeconds);
		} else {
			usage;
		}
	}	

	cout << endl;
	cout << "Kangaroo with the propagation modes: " << endl
	     << "    " << PropagationType << endl
	     << "    CheckError(" << CheckError << "), ParallelArray(" << ParallelArray << "), VarMapArray(" << VarMapArray << ")" << endl
	     << endl;

	try {
		FlatZinc::FlatZincModel* fzModel = NULL;
		if ( !strcmp(filename, "-") ) {
			fzModel = FlatZinc::parse(cin, cerr, runSeed);
		} else {
			fzModel = FlatZinc::parse(filename, cerr, runSeed);
		}

		if ( fzModel ) {
			fzModel->run(std::cout, runSeconds);
		} else {
			exit(EXIT_FAILURE);    
		}
		delete fzModel;
	} catch ( Err & theErr ) {
		cerr << endl << "========= ERROR ========" << endl;
		cerr << "  Error Code: " << theErr() << endl << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

//void scanInt(int argc, char *argv[], int i, int *varptr) {
//	if ( i>=argc || sscanf(argv[i], "%i", varptr) != 1 ) {
//		cerr, "Bad argument %s\n", i<argc ? argv[i] : argv[argc-1]);
//		exit(-1);
//	}
//}

