/*!
	@file mode.hh
	@brief The header file to list various modes.
	@details This is the header file to list various modes.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef ModeHhIncluded
#define ModeHhIncluded


#include "cbls/frames/dat.hpp"


openKangarooSpace



/*!
	@enum Srm
	@brief An enum to represent system running modes.
	@details This enum represents system running modes.
		Besides unitialised mode, there are anew and incremental modes.
		Incremental modes are two types: differential and swapping modes.
		Anew and incremental modes
*/
enum Srm
{
	NullComp	= 1,	//!< Null Comp: uninitialised mode.
	AnewAsgn	= 2,	//!< Anew Asgn: anew assignment mode.
	AnewProp	= 4,	//!< Anew Prop: anew propagation mode.
	DiffAsgn	= 8,	//!< Diff Asgn: differential assignment mode.
	DiffProp	= 16,	//!< Diff Prop: differential propagation mode.
	SwapAsgn	= 32, 	//!< Swap Asgn: swapping assignment mode.
	SwapProp	= 64	//!< Swap Prop: swapping propagation mode.
};


/*!
	@enum Srb
	@brief An enum to represent system running mode bit-masks.
	@details This enum represents system running mode bit-masks.
*/
enum Srb
{
	AnewMode = AnewAsgn + AnewProp,	//!< Anew Mode: anew assignment or propagation mode.
	DiffMode = DiffAsgn + DiffProp,	//!< Diff Mode: differential assignment or propgation mode.
	SwapMode = SwapAsgn + SwapProp,	//!< Swap Mode: swapping assignment or propagation mode.
	IncrMode = DiffMode + SwapMode,	//!< Incr Mode: incremental (differential or swapping) assignment or propagation mode.
	IncrAsgn = DiffAsgn + SwapAsgn,	//!< Incr Asgn: incremental (differential or swapping) assignment mode.
	IncrProp = DiffProp + SwapProp,	//!< Incr Prop: incremental (differential or swapping) propagation mode.
	AsgnMode = AnewAsgn + IncrAsgn,	//!< Asgn Mode: anew or incremental (differential or swapping) assignment mode.
	PropMode = AnewProp + IncrProp	//!< Prop Mode: anew or incremental (differential or swapping) propagation mode.
};



/*!
	@typedef Srs
	@brief A type to denote system running mode strings.
	@details This type denotes system running mode strings.
*/
typedef Bts Srs;


closeKangarooSpace


#endif // ModeHhIncluded
