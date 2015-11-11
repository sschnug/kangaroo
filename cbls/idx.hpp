/*!
	@file cbls/idx.hpp
	@brief The main header file for cbls.
	@details This the main header file for cbls.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 01.12.2011 QRL NICTA www.nicta.com.au
*/



#ifndef CblsIdxHppIncluded
#define CblsIdxHppIncluded



/*
	The idx header files list the files in their container directories
	and recursively include other idx header files in the subdirectories.
*/



/*
	Project setup
*/

#include "cbls/prj.hpp"	// Project
#include "cbls/opt.hpp"	// Options
#include "cbls/lib.hpp"	// Libraries
#include "cbls/msg.hpp"	// Messages



/*
	Generic modules
*/

#include "cbls/frames/idx.hh"	// Frames
#include "cbls/dbases/idx.hpp"	// Databases
#include "cbls/tabus/idx.hh"	// Tabus


/*
	Specific modules
*/

#include "cbls/consts/idx.hpp"	// Constants
#include "cbls/vars/idx.hh"		// Variables
#include "cbls/funcs/idx.hh"	// Functions
#include "cbls/selcs/idx.hh"	// Selectors



/*
	Interface macros and functions
	Need to be developed further
*/
#include "cbls/hlm.hpp"			// High level macros
//#include "cbls/hlf.hpp"		// High level functions


#endif // CblsIdxHppIncluded
