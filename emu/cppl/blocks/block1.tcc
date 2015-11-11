/*!
	@file block1.tcc
	@brief The source file for block1 template class.
	@details This is the source file for block1 template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef Block1TccIncluded
#define Block1TccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class block1
	@brief A class to represent one dimensional arrays.
	@details This class represents one dimensional arrays.
*/
template <typename itm, typename mm>
class block1
{
	public:

		typedef mm MmTyp;							//!< Memory manager type.

		block1();									//!< Constructor.
		block1(mm const & theMm);					//!< Initialiser.
		block1(block1<itm,mm> const & that);		//!< Duplicator.
		block1(itm const * Items, Dim const Count);	//!< Duplicator.
		block1<itm,mm> const & operator =
				(block1<itm,mm> const & that);		//!< Assigner.
		~block1();									//!< Destructor.

		//! @name Synchronise
		//! @{

		void syncClk();							//!< Synchronise clock.

		//! @}

		//! @name Clear
		//! @{

		void clear();								//!< Clear items, retaining available memory.
		void clearMem();							//!< Clear items, releasing memory when deemed.

		//! @}

		//! @name Insert
		//! @{

		void insert();											//!< Insert a default item at the end, assuming memory available.
		void insert(itm const & Item);							//!< Insert the 'Item' at the end, assuming memory available.

		Itr insertItr();										//!< Insert a default item at the end and return the iterator, assuming memory available.
		Itr insertItr(itm const & Item);						//!< Insert the 'Item' at the end and return the iterator, assuming memory available.

		void insertMem();										//!< Insert a default item at the end, acquiring memory when needed. This function requires an expandable memory manager.
		void insertMem(itm const & Item);						//!< Insert the 'Item' at the end, acquiring memory when needed.  This function requires an expandable memory manager.

		Itr insertItrMem();										//!< Insert a default item at the end and return the iterator, acquiring memory available. This function requires an expandable memory manager.
		Itr insertItrMem(itm const & Item);						//!< Insert the 'Item' at the end and return the iterator, acquiring memory available. This function requires an expandable memory manager.

		void insert(Itr const theItr, itm const & Item);		//!< Insert the 'Item' at the given 'theItr' iterator, assuming memory available. This function requires an expandable memory manager.
		void insertMem(Itr const theItr, itm const & Item);		//!< Insert the 'Item' at the given 'theItr' iterator, acquiring memory when needed. This function requires an expandable memory manager.

		//! @}

		//! @name Remove
		//! @{

		void remove();								//!< Remove the last item, retaining available memory.
		void removeMem();							//!< Remove the last item, releasing memroy when deemed.
		void remove(itm & Item);					//!< Remove and return the last item, retaining available memory.
		void removeMem(itm & Item);					//!< Remove and return the last item, releasing memroy when deemed.
		void removePull(Itr const theItr);			//!< Remove an item from a given iterator and pull the trailing items to fill in the gap, retaining available memory.
		void removeFill(Itr const theItr);			//!< Remove an item from a given iterator and fill in the gap with the last item, retaining available memory.
		void removePullMem(Itr const theItr);		//!< Remove an item from a given iterator and pull the trailing items to fill in the gap, releasing memory when deemed.
		void removeFillMem(Itr const theItr);		//!< Remove an item from a given iterator and fill in the gap with the last item, releasing memory when deemed.

		//! @}

		//! @name Memory
		//! @{

		Dim itemCount() const;						//!< Get item count.
		mm const & MemMan() const;					//!< Memory manager.

		void reallocMemAuto();						//!< Reallocate memory automatically.
		void deallocMemAuto();						//!< Deallocate memory automatically.
		void adjustMemAuto();						//!< Adjust memory automatically.
		void allocateMem(Dim const Alloc);			//!< Allocate given extent of memory.

		//! @}

		//! @name Items
		//! @{

		itm * items();										//!< Get the items.
		itm const * items() const;							//!< Get the items.

		itm & operator[](Itr const theItr);					//!< Get an item.
		itm const & operator[](Itr const theItr) const;		//!< Get an item.

		itm & item(Itr const theItr);						//!< Get an item.
		itm const & item(Itr const theItr) const;			//!< Get an item.

		//! @}

		//! @name Last Item
		//! @{

		itm & itemFirst();				//!< Get the first item.
		itm const & itemFirst() const;	//!< Get the first item.
		Itr iteratorFirst() const;		//!< Get the first iterator.

		itm & itemLast();				//!< Get the last item.
		itm const & itemLast() const;	//!< Get the last item.
		Itr iteratorLast() const;		//!< Get the last iterator.

		//! @}

		//! @name Copy
		//! @{

		void copyDirect(itm const * Items, Dim const Count);		//!< Copy as is, assuming memory available.
		void copyDirectMem(itm const * Items, Dim const Count);		//!< Copy as is, acquiring memory when needed.
		void copyIndexed(itm const * Items,
						Itr const * Indexes, Dim const Count);		//!< Copy as indexed, assuming memory available.
		void copyIndexedMem(itm const * Items,
						Itr const * Indexes, Dim const Count);		//!< Copy as indexed, acquiring memory when needed.

		//! @}

	private:
		mm	   mMemMan;			//!< Memory manager.
		itm *  mItems;			//!< The items.
};



/*!
	@def b1
	@brief A macro to denote block1.
	@details This macro denotes block1.
*/
#define b1 block1



/*!
	The constructor.
*/
template<typename itm, typename mm>
block1<itm,mm>::block1()
{
	WatchError

	mItems = new itm [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = itm();

	CatchError
}



/*!
	The initialiser.
*/
template<typename itm, typename mm>
block1<itm,mm>::block1(mm const & theMm) : mMemMan(theMm)
{
	WatchError

	mItems = new itm [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = itm();

	CatchError
}



/*!
	The duplicator.
*/
template <typename itm, typename mm>
block1<itm,mm>::block1(block1<itm,mm> const & that) : mMemMan(that.mMemMan)
{
	WatchError

	mItems = new itm [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = that.mItems[tItr];

	CatchError
}



/*!
	The duplicator.
*/
template <typename itm, typename mm>
block1<itm,mm>::block1(itm const * Items, Dim const Count)
{
	WatchError

	mMemMan.reinitialise(Count, Count);
	mItems = new itm [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = Items[tItr];

	CatchError
}



/*!
	The destructor.
*/
template <typename itm, typename mm>
block1<itm,mm>::~block1()
{
	WatchError

	delete [] mItems;

	CatchError
}



/*!
	The assigner.
*/
template <typename itm, typename mm>
block1<itm,mm> const & block1<itm,mm>::operator = (block1<itm,mm> const & that)
{
	WatchError

	if (&that == this)
		return *this;

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		delete [] mItems;
		mItems = new itm [that.mMemMan.acquired()];
	}

	mMemMan = that.mMemMan;

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = that.mItems[tItr];

	return *this;

	CatchError
}



/*!
	Synchronise clock.
*/
template <typename itm, typename mm>
inline void block1<itm,mm>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}



/*!
	Clear items, retaining available memory.
*/
template<typename itm, typename mm>
inline void block1<itm,mm>::clear()
{
	WatchError

	mMemMan.resetOccupy();

	CatchError
}



/*!
	Clear items, releasing memory when deemed.
*/
template<typename itm, typename mm>
inline void block1<itm,mm>::clearMem()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}

	CatchError
}



/*!
	Insert an item at the end, assuming memory available.
*/
template <typename itm, typename mm>
inline void block1<itm,mm>::insert()
{
	WatchError

	mItems[mMemMan.reoccupyItr()] = itm();

	CatchError
}




/*!
	Insert an item at the end, assuming memory available.
*/
template <typename itm, typename mm>
inline void block1<itm,mm>::insert(itm const & Item)
{
	WatchError

	mItems[mMemMan.reoccupyItr()] = Item;

	CatchError
}



/*!
	Insert an item at the end and return the iterator, assuming memory available.
*/
template <typename itm, typename mm>
inline Itr block1<itm,mm>::insertItr()
{
	WatchError

	Itr const tItr = mMemMan.reoccupyItr();
	mItems[tItr] = itm();
	return tItr;

	CatchError
}



/*!
	Insert an item at the end and return the iterator, assuming memory available.
*/
template <typename itm, typename mm>
inline Itr block1<itm,mm>::insertItr(itm const & Item)
{
	WatchError

	Itr const tItr = mMemMan.reoccupyItr();
	mItems[tItr] = Item;
	return tItr;

	CatchError
}



/*!
	Insert an item at the end, acquiring memory when needed.
*/
template <typename itm, typename mm>
inline void block1<itm,mm>::insertMem()
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	mItems[mMemMan.reoccupyItr()] = itm();

	CatchError
}



/*!
	Insert an item at the end, acquiring memory when needed.
*/
template <typename itm, typename mm>
inline void block1<itm,mm>::insertMem(itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	mItems[mMemMan.reoccupyItr()] = Item;

	CatchError
}



/*!
	Insert an item at the end and return the iterator, acquiring memory when needed.
*/
template <typename itm, typename mm>
inline Itr block1<itm,mm>::insertItrMem()
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr const tItr = mMemMan.reoccupyItr();
	mItems[tItr] = itm();
	return tItr;

	CatchError
}



/*!
	Insert an item at the end and return the iterator, acquiring memory when needed.
*/
template <typename itm, typename mm>
inline Itr block1<itm,mm>::insertItrMem(itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr const tItr = mMemMan.reoccupyItr();
	mItems[tItr] = Item;
	return tItr;

	CatchError
}



/*!
	Insert an item at a given iterator, assuming memory available.
*/
template <typename itm, typename mm>
inline void block1<itm,mm>::insert(Itr const theItr, itm const & Item)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	for(Itr tItr = mMemMan.reoccupyItr(); tItr > theItr; --tItr)
		mItems[tItr] = mItems[tItr - 1];
	mItems[theItr] = Item;

	CatchError
}



/*!
	Insert an item at a given iterator, acquiring memory when needed.
*/
template <typename itm, typename mm>
inline void block1<itm,mm>::insertMem(Itr const theItr, itm const & Item)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	for(Itr tItr = mMemMan.reoccupyItr(); tItr > theItr; --tItr)
		mItems[tItr] = mItems[tItr - 1];
	mItems[theItr] = Item;

	CatchError
}



/*!
	Remove the last item, retaining available memory.
*/
template <typename itm, typename mm>
inline void block1<itm,mm>::remove()
{
	WatchError

	mMemMan.unoccupy();

	CatchError
}



/*!
	Remove and return the last item, retaining available memory.
*/
template <typename itm, typename mm>
inline void block1<itm,mm>::remove(itm & Item)
{
	WatchError

	Item = mItems[mMemMan.unoccupyItr()];

	CatchError
}


/*!
	Remove the last item, releasing memroy when deemed.
*/
template <typename itm, typename mm>
inline void block1<itm,mm>::removeMem()
{
	WatchError

	mMemMan.unoccupy();
	if (mMemMan.needAutoDealloc())
		deallocMemAuto();
	CatchError
}



/*!
	Remove and return the last item, releasing memroy when deemed.
*/
template <typename itm, typename mm>
inline void block1<itm,mm>::removeMem(itm & Item)
{
	WatchError

	Item = mItems[mMemMan.unoccupyItr()];
	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Remove an item from a given iterator and fill in the gap
	with the last item, retaining available memory.
 */
template <typename itm, typename mm>
inline void block1<itm,mm>::removeFill(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	Itr const tItr = mMemMan.unoccupyItr();

	if (tItr > theItr)
		mItems[theItr] = mItems[tItr];

	CatchError
}



/*!
	Remove an item from a given iterator and fill in the gap
	with the last item, releasing memory when deemed.
 */
template <typename itm, typename mm>
inline void block1<itm,mm>::removeFillMem(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	Itr const tItr = mMemMan.unoccupyItr();

	if (tItr > theItr)
		mItems[theItr] = mItems[tItr];

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Remove an item from a given iterator and pull the trailing
	items towards the gap, retaining available memory.
 */
template <typename itm, typename mm>
inline void block1<itm,mm>::removePull(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	Itr const sItr = mMemMan.unoccupyItr();

	for(Itr tItr = theItr; tItr < sItr; ++tItr)
		mItems[tItr] = mItems[tItr + 1];

	CatchError
}



/*!
	Remove an item from a given iterator and pull the trailing
	items towards the gap, releasing memory when deemed.
 */
template <typename itm, typename mm>
inline void block1<itm,mm>::removePullMem(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	Itr const sItr = mMemMan.unoccupyItr();

	for(Itr tItr = theItr; tItr < sItr; ++tItr)
		mItems[tItr] = mItems[tItr + 1];

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Reallocate more memory automatically.
*/
template<typename itm, typename mm>
void block1<itm,mm>::reallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);

	mMemMan.reallocAuto();

	itm * const tItems = mItems;
	mItems = new itm[mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = tItems[tItr];
	delete [] tItems;

	CatchError
}



/*!
	Deallocate some memory automatically.
*/
template<typename itm, typename mm>
void block1<itm,mm>::deallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);

	mMemMan.deallocAuto();

	itm * const tItems = mItems;
	mItems = new itm[mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = tItems[tItr];
	delete [] tItems;

	CatchError
}



/*!
	Adjust memory automatically.
*/
template<typename itm, typename mm>
void block1<itm,mm>::adjustMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);

	mMemMan.adjustAuto();

	itm * const tItems = mItems;
	mItems = new itm[mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = tItems[tItr];
	delete [] tItems;

	CatchError
}



/*!
	Allocate memory.
*/
template<typename itm, typename mm>
void block1<itm,mm>::allocateMem(Dim const Alloc)
{
	WatchError

	if (mMemMan.mismatchAlloc(Alloc))
	{
		mMemMan.allocate(Alloc);

		itm * const tItems = mItems;
		mItems = new itm[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
			mItems[tItr] = tItems[tItr];
		delete [] tItems;
	}

	CatchError
}


/*!
	Return the item count.
*/
template <typename itm, typename mm>
inline Dim block1<itm,mm>::itemCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the memory manager.
*/
template <typename itm, typename mm>
inline mm const & block1<itm,mm>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Return the items; do not free memory with this.
*/
template <typename itm, typename mm>
inline itm const * block1<itm,mm>::items() const
{
	WatchError

	return mItems;

	CatchError
}



/*!
	Return the items; do not free memory with this.
*/
template <typename itm, typename mm>
inline itm * block1<itm,mm>::items()
{
	WatchError

	return mItems;

	CatchError
}



/*!
	Return an item.
*/
template <typename itm, typename mm>
inline itm const & block1<itm,mm>::operator[](Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mItems[theItr];

	CatchError
}



/*!
	Return an item.
*/
template <typename itm, typename mm>
inline itm & block1<itm,mm>::operator[](Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mItems[theItr];

	CatchError
}



/*!
	Return an item.
*/
template <typename itm, typename mm>
inline itm const & block1<itm,mm>::item(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mItems[theItr];

	CatchError
}



/*!
	Return an item.
*/
template <typename itm, typename mm>
inline itm & block1<itm,mm>::item(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mItems[theItr];

	CatchError
}



/*!
	Return the first item.
*/
template <typename itm, typename mm>
inline itm const & block1<itm,mm>::itemFirst() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eOccupiedMemoryEmpty);

	return mItems[0];

	CatchError
}



/*!
	Return the first item
*/
template <typename itm, typename mm>
inline itm & block1<itm,mm>::itemFirst()
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eOccupiedMemoryEmpty);

	return mItems[0];

	CatchError
}



/*!
	Return the first iterator.
*/
template <typename itm, typename mm>
inline Itr block1<itm,mm>::iteratorFirst() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eOccupiedMemoryEmpty);

	return 0;

	CatchError
}



/*!
	Return the last item.
*/
template <typename itm, typename mm>
inline itm const & block1<itm,mm>::itemLast() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eOccupiedMemoryEmpty);

	return mItems[mMemMan.occupied() - 1];

	CatchError
}



/*!
	Return the last item
*/
template <typename itm, typename mm>
inline itm & block1<itm,mm>::itemLast()
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eOccupiedMemoryEmpty);

	return mItems[mMemMan.occupied() - 1];

	CatchError
}



/*!
	Return the last iterator.
*/
template <typename itm, typename mm>
inline Itr block1<itm,mm>::iteratorLast() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eOccupiedMemoryEmpty);

	return mMemMan.occupied() - 1;

	CatchError
}



/*!
	Copy from the given items, assuming memory available.
*/
template <typename itm, typename mm>
void block1<itm,mm>::copyDirect(itm const * Items, Dim const Count)
{
	WatchError

	Warn(mItems == Items, eSelfCopy);
	Warn(mMemMan.deficientAlloc(Count), eMemoryAllocation);

	mMemMan.occupy(Count);
	for(Itr tItr = 0; tItr < Count; ++tItr)
		mItems[tItr] = Items[tItr];

	CatchError
}



/*!
	Copy from the given items, acquiring memory when needed.
*/
template <typename itm, typename mm>
void block1<itm,mm>::copyDirectMem(itm const * Items, Dim const Count)
{
	WatchError

	Warn(mItems == Items, eSelfCopy);

	if (mMemMan.deficientAlloc(Count))
	{
		delete [] mItems;
		mMemMan.reinitialise(Count,Count);
		mItems = new itm [mMemMan.acquired()];
	}
	else
		mMemMan.occupy(Count);

	for(Itr tItr = 0; tItr < Count; ++tItr)
		mItems[tItr] = Items[tItr];

	CatchError
}



/*!
	Copy from the given items as they are indexed.
*/
template <typename itm, typename mm>
void block1<itm,mm>::copyIndexed(itm const * Items,
		Itr const * Indexes, Dim const Count)
{
	WatchError

	Warn(mItems == Items, eSelfCopy);

	Warn(mMemMan.deficientAlloc(Count), eMemoryAllocation);

	mMemMan.occupy(Count);
	for(Itr tItr = 0; tItr < Count; ++tItr)
		mItems[tItr] = Items[Indexes[tItr]];

	CatchError
}



/*!
	Copy from the given items as they are indexed.
*/
template <typename itm, typename mm>
void block1<itm,mm>::copyIndexedMem(itm const * Items,
		Itr const * Indexes, Dim const Count)
{
	WatchError

	Warn(mItems == Items, eSelfCopy);

	if (mMemMan.deficientAlloc(Count))
	{
		delete [] mItems;
		mMemMan.reinitialise(Count,Count);
		mItems = new itm [mMemMan.acquired()];
	}
	else
		mMemMan.occupy(Count);

	for(Itr tItr = 0; tItr < Count; ++tItr)
		mItems[tItr] = Items[Indexes[tItr]];

	CatchError
}



closeEmuSpace


#endif // Block1TccIncluded
