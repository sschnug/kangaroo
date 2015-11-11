/*!
	@file hmaps/idx.hpp
	@brief The index header file for template hash maps.
	@details This is the index header file for template hash maps.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef HmapsIdxHppIncluded
#define HmapsIdxHppIncluded


#include "cppl/hmaps/hmap.tcc"		//	Standard hash maps with closed chain.
#include "cppl/hmaps/hmapc.tcc"		//	Hash maps with clocks to enable efficient clear.
#include "cppl/hmaps/hmapd.tcc"		//	Hash maps with doubly linked-list to enable fast removal.
#include "cppl/hmaps/hmapf.tcc"		//	Hash maps with clocks and doubly linked-list to enable both efficient clear and fast removal.


#endif // HmapsIdxHppIncluded
