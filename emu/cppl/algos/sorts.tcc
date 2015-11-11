/*!
	@file sorts.tcc
	@brief The source file for sorting function templates.
	@details This is the source file for sorting function templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef SortsTccIncluded
#define SortsTccIncluded



#include "cppl/roots/idx.hpp"
#include "cppl/algos/idx.hpp"


openEmuSpace



/*!
	@brief A function to implement heap-sort.
	@details This function implements heap-sort.
		Use lt for ascending, gt for descending order sorting.
*/
template<typename itm, typename cfn>
void heapsort(itm * Items, Dim const Count)
{
	WatchError
	Warn(!Items, eNullPointer);

	if (Count < 2) return;

	for(Itr tItr = (Count >> 1) - 1; tItr; --tItr)
		heapdown<itm,cfn>(Items, Count, tItr);
	heapdown<itm,cfn>(Items, Count, 0);

	for(Itr tItr = Count - 1; tItr; --tItr)
	{
		exchange<itm>(Items[0], Items[tItr]);
		heapdown<itm,cfn>(Items, tItr, 0);
	}
	CatchError
}



/*!
	@brief A function to implement the insertion sort.
	@details This function implements the insertion sort.
		Use lt for ascending, gt for descending order sorting.
*/
template<typename itm, typename cfn>
void inssort(itm * Items, Dim const Count)
{
	WatchError
	Warn(!Items, eNullPointer);

	for(Itr Itr1 = 1, Itr2; Itr1 < Count; ++Itr1)
	{
		itm Item = Items[Itr1];
		Itr2 = Itr1;
		while(Itr2)
		{
			itm const & tItem = Items[Itr2 - 1];
			if (cfn::iof(tItem, Item)) break;
			Items[Itr2] = tItem;
			--Itr2;
		}
		Items[Itr2] = Item;
	}
	CatchError
}



/*!
	@brief A function to implement the introsort.
	@details This function implements the introsort.
		Use lt for ascending, gt for descending order sorting.
*/
template<typename itm, typename cfn>
void introsort(itm * Items, Dim const Count, Dim const Depth)
{
	WatchError
	Warn(!Items, eNullPointer);

	Dim tCount = Count;
	while (tCount > 16)
	{
		if (!Depth)
		{
			heapsort<itm, cfn>(Items, tCount);
			return;
		}

		Itr Forth = 1, Mid = tCount - (tCount >> 1), Back = tCount - 1;
		if (cfn::iof(Items[0], Items[Mid]))
		{
			if (cfn::iof(Items[Back], Items[0]))	Mid = 0;
			else if (cfn::iof(Items[Back], Items[Mid])) Mid = Back;
		}
		else
		{
			if (cfn::iof(Items[0], Items[Back])) Mid = 0;
			else if (cfn::iof(Items[Mid], Items[Back])) Mid = Back;
		}
		if (Mid) exchange<itm>(Items[0], Items[Mid]);
		while(Forth <= Back)
		{
			while (Forth < tCount && cfn::iof(Items[Forth], Items[0])) ++Forth;
			while (Back > 0 && !cfn::iof(Items[Back], Items[0])) --Back;
			if (Forth < Back) exchange<itm>(Items[Forth], Items[Back]);
		}
		exchange<itm>(Items[0], Items[Back]);
		introsort<itm,cfn>(Items + Forth, tCount - Forth, Depth - 1);
		tCount = Back;
	}

	inssort<itm, cfn>(Items, tCount);
	CatchError
}



/*!
	@brief A function to implement the quick sort.
	@details This function implements the quick sort.
		Use lt for ascending, gt for descending order sorting.
*/
template<typename itm, typename cfn>
void qcksort(itm * Items, Dim const Count)
{
	WatchError
	Warn(!Items, eNullPointer);

	if (Count <= 32)	//	insertion sort
	{
		itm Item;
		for(Itr Itr1 = 1, Itr2; Itr1 < Count; ++Itr1)
		{
			Item = Items[Itr1];
			Itr2 = Itr1;
			while(Itr2)
			{
				itm const & tItem = Items[Itr2 -1];
				if (cfn::iof(tItem, Item)) break;
				Items[Itr2] = tItem;
				--Itr2;
			}
			Items[Itr2] = Item;
		}
		return;
	}

	Itr Forth = 1, Mid = Count - (Count >> 1), Back = Count - 1;

	if (cfn::iof(Items[0], Items[Mid]))
	{
		if (cfn::iof(Items[Back], Items[0]))	Mid = 0;
		else if (cfn::iof(Items[Back], Items[Mid])) Mid = Back;
	}
	else
	{
		if (cfn::iof(Items[0], Items[Back])) Mid = 0;
		else if (cfn::iof(Items[Mid], Items[Back])) Mid = Back;
	}
	if (Mid) exchange<itm>(Items[0], Items[Mid]);

	while(Forth <= Back)
	{
		while (Forth < Count && cfn::iof(Items[Forth], Items[0])) ++Forth;
		while (Back > 0 && !cfn::iof(Items[Back], Items[0])) --Back;
		if (Forth < Back) exchange<itm>(Items[Forth], Items[Back]);
	}

	exchange<itm>(Items[0], Items[Back]);
	qcksort<itm,cfn>(Items, Back);
	qcksort<itm,cfn>(Items + Forth, Count - Forth);
	CatchError
}



/*!
	@brief A function to implement the itmsort.
	@details This function implements the itmsort. This function is a wrapper.
		Use lt for ascending, gt for descending order sorting.
*/
template<typename itm, typename cfn>
void itemsort(itm * Items, Dim const Count)
{
	WatchError
	Warn(!Items, eNullPointer);

	if (Count < 2) return;
	inssort<itm, cfn>(Items, Count);
	CatchError
}



/*!
	@brief A function to implement the index sort.
	@details This function implements the index sort.
		Besides the items, this function sorts an array of iterators called indexes.
		Sorting is done based on the items. Use lt for ascending, gt for descending order sorting.
*/
template<typename itm, typename cfn>
void idxsort(itm * Items, Itr * Indexes, Dim const Count)
{
	WatchError
	Warn(!Items, eNullPointer);
	Warn(!Indexes, eNullPointer);

	if (Count <= 16)	//	insertion sort.
	{
		itm Item; Itr Iterator;
		for(Itr Itr1 = 1, Itr2, Itr3; Itr1 < Count; ++Itr1)
		{
			Item = Items[Itr1];
			Iterator = Indexes[Itr1];
			Itr2 = Itr1, Itr3 = Itr1 - 1;
			while(Itr2)
			{
				itm const & tItem = Items[Itr3];
				if (cfn::iof(tItem, Item)) break;
				Items[Itr2] = tItem;
				Indexes[Itr2] = Indexes[Itr3];
				--Itr2, --Itr3;
			}
			Items[Itr2] = Item;
			Indexes[Itr2] = Iterator;
		}
		return;
	}
	Itr Forth = 1, Mid = Count - (Count >> 1), Back = Count - 1;

	if (cfn::iof(Items[0], Items[Mid]))
	{
		if (cfn::iof(Items[Back], Items[0]))	Mid = 0;
		else if (cfn::iof(Items[Back], Items[Mid])) Mid = Back;
	}
	else
	{
		if (cfn::iof(Items[0], Items[Back])) Mid = 0;
		else if (cfn::iof(Items[Mid], Items[Back])) Mid = Back;
	}
	if (Mid)
	{
		exchange<itm>(Items[0], Items[Mid]);
		exchange<Itr>(Indexes[0], Indexes[Mid]);
	}
	while(Forth <= Back)
	{
		while (Forth < Count && cfn::iof(Items[Forth], Items[0])) ++Forth;
		while (Back > 0 && !cfn::iof(Items[Back], Items[0])) --Back;
		if (Forth < Back)
		{
			exchange<itm>(Items[Forth], Items[Back]);
			exchange<Itr>(Indexes[Forth], Indexes[Back]);
		}
	}
	exchange<itm>(Items[0], Items[Back]);
	exchange<Itr>(Indexes[0], Indexes[Back]);
	idxsort<itm,cfn>(Items, Indexes, Back);
	idxsort<itm,cfn>(Items + Forth, Indexes + Forth, Count - Forth);
	CatchError
}



closeEmuSpace



#endif // SortsTccIncluded
