/*!
	@file shuffle.tcc
	@brief The source file for shuffle function templates.
	@details This is the source file for shuffle function templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef ShuffleTccIncluded
#define ShuffleTccIncluded



#include "cppl/roots/idx.hpp"
#include "cppl/rands/idx.hpp"
#include "cppl/algos/idx.hpp"
#include "cppl/rands/uniform.hpp"



openEmuSpace



/*!
	@brief Generate a random shuffling of the items.
	@details This function generates a random shuffling of the items.
			Note that the underlying distribution would be truely
			uniform only when the items provided are all unique.
*/
template<typename itm>
void shuffle(Rnd & theRnd, itm * Items, Dim const Count)
{
	WatchError
	Warn(!Count, eEmptyCount);
	for(Itr tItr = Count - 1; tItr; --tItr)
		exchange<itm>(Items[tItr], Items[uniform(theRnd, tItr)]);
	CatchError
}



closeEmuSpace



#endif // ShuffleTccIncluded
