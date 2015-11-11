/*!
	@file hsets/idx.hpp
	@brief The index header file for template hash sets.
	@details This is the index header file for template hash sets.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef HsetsIdxHppIncluded
#define HsetsIdxHppIncluded


#include "cppl/hsets/hset.tcc"		//	Standard hash sets with closed chain.
#include "cppl/hsets/hsetc.tcc"		//	Hash sets with clocks to enable efficient clear.
#include "cppl/hsets/hsetd.tcc"		//	Hash sets with doubly linked-list to enable fast removal.
#include "cppl/hsets/hsetf.tcc"		//	Hash sets with clocks and doubly linked-list to enable both efficient clear and fast removal.


#endif // HsetsIdxHppIncluded
