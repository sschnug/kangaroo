/*!
	@file mems/idx.hpp
	@brief The index header file for memory manager classes.
	@details This is the index header file for memory manager classes.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef MemsIdxHppIncluded
#define MemsIdxHppIncluded



#include "cppl/mems/kmm.hpp"		//	Fixed allocation fixed occupancy memory manager.
#include "cppl/mems/nmm.hpp"		//	Fixed allocation flexible occupancy memory manager.
#include "cppl/mems/xmm.hpp"		//	Extendable allocation flexible occupancy memory manager.
#include "cppl/mems/nmmm.hpp"	//	Fixed allocation flexible occupancy memory manager maintaining a *margin*, best suited for queues, and texts.
#include "cppl/mems/xmmm.hpp"	//	Extendable allocation flexible occupancy memory manager maintaining a *margin*, best suited for queues and texts.
#include "cppl/mems/nmmh.hpp"	//	Fixed allocation flexible occupancy memory manager, best suited for hash tables.
#include "cppl/mems/xmmh.hpp"	//	Extendable allocation flexible occupancy memory manager, best suited for hash tables.



#endif // MemsIdxHppIncluded

