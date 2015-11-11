/*!
	@file heaps.tcc
	@brief The source file for heap function templates.
	@details This is the source file for heap function templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef HeapsTccIncluded
#define HeapsTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@brief A function to implement heap down.
	@details This function implements heap down.
			Use lt for maxheap and gt for minheap.
	@return The iterator where the element is placed.
*/
template<typename itm, typename cfn>
Itr heapdown(itm * Items, Dim const Count, Itr const Iterator)
{
	WatchError
	Warn(!Items, eNullPointer);
	Warn(Iterator >= Count, eIteratorBeyondLimit);

	itm Item = Items[Iterator];
	Itr Itr1 = Iterator;

	while(true)
	{
		Itr Itr2 = (Itr1 << 1) + 1;
		if (Itr2 >= Count) break;

		Itr Itr3 = Itr2 + 1;
		if (Itr3 < Count && cfn::iof(Items[Itr2], Items[Itr3])) ++Itr2;
		if (!cfn::iof(Item, Items[Itr2])) break;
		Items[Itr1] = Items[Itr2];
		Itr1 = Itr2;
	}

	Items[Itr1] = Item;
	return Itr1;
	CatchError
}



/*!
	@brief A function to implement heap up.
	@details This function implements heap up.
			Use lt for maxheap and gt for minheap.
	@return The iterator where the element is placed.
*/
template<typename itm, typename cfn>
Itr heapup(itm * Items, Dim const Count, Itr const Iterator)
{
	WatchError
	Warn(!Items, eNullPointer);
	Warn(Iterator >= Count, eIteratorBeyondLimit);

	itm Item = Items[Iterator];
	Itr Itr1 = Iterator;

	while(Itr1)
	{
		Itr Itr2 = (Itr1 - 1) >> 1;
		if (!cfn::iof(Items[Itr2], Item)) break;
		Items[Itr1] = Items[Itr2];
		Itr1 = Itr2;
	}

	Items[Itr1] = Item;
	return Itr1;
	CatchError
}


/*!
	@brief A function to implement heapify.
	@details This function implements heapify.
		Use lt for maxheap and gt for minheap.
*/
template<typename itm, typename cfn>
void heapify(itm * Items, Dim const Count)
{
	WatchError
	Warn(!Items, eNullPointer);

	if (Count < 2) return;

	for(Itr tItr = (Count >> 1) - 1; tItr; --tItr)
		heapdown<itm,cfn>(Items, Count, tItr);
	heapdown<itm,cfn>(Items, Count, 0);
	CatchError
}



/*!
	@brief A function to implement heap-push.
	@details This function implements heap-push.
		Use lt for maxheap and gt for minheap.
		Count includes the last element added.
*/
template<typename itm, typename cfn>
void heappush(itm * Items, Dim const Count)
{
	WatchError
	Warn(!Items, eNullPointer);
	Warn(!Count, eEmptyCount);

	heapup<itm,cfn>(Items, Count, Count - 1);
	CatchError
}



/*!
	@brief A function to implement heap-pop.
	@details This function implements heap-pop.
		 Use lt for maxheap and gt for minheap.
		Count includes the last element dropped.
*/
template<typename itm, typename cfn>
void heappop(itm * Items, Dim const Count)
{
	WatchError
	Warn(!Items, eNullPointer);
	Warn(!Count, eEmptyCount);

	exchange<itm>(Items[0], Items[Count - 1]);
	heapdown<itm,cfn>(Items, Count - 1, 0);
	CatchError
}



/*!
	@brief A function to implement heap-alter.
	@details This function implements heap-alter.
			 Use lt for maxheap and gt for minheap.
*/
template<typename itm, typename cfn>
void heapalter(itm * Items, Dim const Count, Itr const Iterator)
{
	WatchError
	Warn(!Items, eNullPointer);
	Warn(!Count, eEmptyCount);

	Itr tItr = heapup<itm, cfn>(Items, Count, Iterator);
	if (tItr == Iterator) heapdown<itm,cfn>(Items, Count, tItr);
	CatchError
}



/*!
	@brief A function to implement heap-drop.
	@details This function implements heap-drop.
			 Use lt for maxheap and gt for minheap.
*/
template<typename itm, typename cfn> inline
void heapdrop(itm * Items, Dim const Count, Itr const Iterator)
{
	WatchError
	Warn(!Items, eNullPointer);
	Warn(!Count, eEmptyCount);

	exchange<itm>(Items[Iterator], Items[Count - 1]);
	Itr tItr = heapup<itm, cfn>(Items, Count - 1, Iterator);
	if (tItr == Iterator) heapdown<itm,cfn>(Items, Count - 1, tItr);
	CatchError
}



closeEmuSpace



#endif // HeapsTccIncluded
