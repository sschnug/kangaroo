/*!
	@file queueh.tcc
	@brief The source file for queueh template class.
	@details This is the source file for queueh template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef QueuehTccIncluded
#define QueuehTccIncluded



#include "cppl/roots/idx.hpp"
#include "cppl/algos/idx.hpp"



openEmuSpace



/*!
	@class queueh
	@brief A class to represent standard max or min heap-based queues.
	@details This class represents standard max or min heap-based queues.
			Use lt for max and gt for min heap-based queues.
*/
template <typename itm, typename cfn, typename mm>
class queueh
{
	public:

		typedef mm MmTyp;							//!< Memory manager.

		queueh();									//!< Constructor.
		queueh(mm const & theMm);					//!< Initialiser.
		queueh(queueh<itm,cfn,mm> const & that);	//!< Duplicator.
		queueh<itm,cfn,mm> const & operator =
				(queueh<itm,cfn,mm> const & that);	//!< Assigner.
		~queueh();									//!< Destructor.

		//! @name Synchronise
		//! @{

		void syncClk();							//!< Synchronise clock.

		//! @}

		//! @name Clear
		//! @{

		void clear();							//!< Clear items, retaining available memory.
		void clearMem();						//!< Clear items, releasing memory when deemed.

		//! @}
		//! @name Insert
		//! @{

		void insert(itm const & Item);			//!< Insert an item at the end, assuming memory available.
		void insertMem(itm const & Item);		//!< Insert an item at the end, acquiring memory when needed.

		//! @}
		//! @name Remove
		//! @{

		void remove();							//!< Remove the first item, retaining available memory.
		void removeMem();						//!< Remove the first item, releasing memroy when deemed.
		void remove(itm & Item);				//!< Remove and return the first item, retaining available memory.
		void removeMem(itm & Item);				//!< Remove and return the first item, releasing memroy when deemed.

		//! @}

		//! @name Memory
		//! @{

		Dim itemCount() const;						//!< Get the item count.
		mm const & MemMan() const;					//!< Get the memory manager.

		void reallocMemAuto();						//!< Reallocate memory automatically.
		void deallocMemAuto();						//!< Deallocate memory automatically.
		void adjustMemAuto();						//!< Adjust memory automatically.
		void allocateMem(Dim const Alloc);			//!< Allocate given extent of memory.

		//! @}

		//! @name Items
		//! @{

		itm const * items() const;							//!< Get the items.
		itm const & operator[](Itr const theItr) const;		//!< Get an item.
		itm const & item(Itr const theItr) const;			//!< Get an item.

		//! @}

		//! @name Peak
		//! @{

		itm const & itemPeak() const;	//!< Get the peak item.
		Itr iteratorPeak() const;		//!< Get the peak iterator.

		//! @}

		/*! @name Iterators */
		//! @{

		Itr childLeft(Itr const theItr) const;				//!< Get the left child of an iterator.
		Itr childRight(Itr const theItr) const;				//!< Get the right child of an iterator.
		Itr siblingLeft(Itr const theItr) const;			//!< Get the left sibling of an iterator.
		Itr siblingRight(Itr const theItr) const;			//!< Get the right sibling of an iterator.

		//! @}

	private:
		mm    mMemMan;		//!< Memory manager.
		itm *  mItems;		//!< The items.
};



/*!
	@def qh
	@brief A macro to denote queueh.
	@details This macro denotes queueh.
*/
#define qh queueh



/*!
	The constructor.
*/
template<typename itm, typename cfn, typename mm>
queueh<itm,cfn,mm>::queueh()
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
template<typename itm, typename cfn, typename mm>
queueh<itm,cfn,mm>::queueh(mm const & theMm) : mMemMan(theMm)
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
template <typename itm, typename cfn, typename mm>
queueh<itm,cfn,mm>::queueh(queueh<itm,cfn,mm> const & that) :
		mMemMan(that.mMemMan)
{
	WatchError

	mItems = new itm [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = that.mItems[tItr];

	CatchError
}




/*!
	The destructor.
*/
template <typename itm, typename cfn, typename mm>
queueh<itm,cfn,mm>::~queueh()
{
	WatchError

	delete [] mItems;

	CatchError
}



/*!
	The assigner.
*/
template <typename itm, typename cfn, typename mm>
queueh<itm,cfn,mm> const & queueh<itm,cfn,mm>::operator =
		(queueh<itm,cfn,mm> const & that)
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
template <typename itm, typename cfn, typename mm>
inline void queueh<itm,cfn,mm>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}



/*!
	Clear items, retaining available memory.
*/
template<typename itm, typename cfn, typename mm>
inline void queueh<itm,cfn,mm>::clear()
{
	WatchError

	mMemMan.resetOccupy();

	CatchError
}



/*!
	Clear items, releasing memory when deemed.
*/
template <typename itm, typename cfn, typename mm>
inline void queueh<itm,cfn,mm>::clearMem()
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
template <typename itm, typename cfn, typename mm>
inline void queueh<itm,cfn,mm>::insert(itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	mItems[mMemMan.reoccupyItr()] = Item;
	heappush<itm,cfn>(mItems, mMemMan.occupied());

	CatchError
}



/*!
	Insert an item at the end, acquiring memory when deemed.
*/
template <typename itm, typename cfn, typename mm>
inline void queueh<itm,cfn,mm>::insertMem(itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	mItems[mMemMan.reoccupyItr()] = Item;
	heappush<itm,cfn>(mItems, mMemMan.occupied());

	CatchError
}



/*!
	Remove the last item, retaining available memory.
*/
template <typename itm, typename cfn, typename mm>
inline void queueh<itm,cfn,mm>::remove()
{
	WatchError

	Itr const tItr = mMemMan.unoccupyItr();

	if (tItr)
	{
		mItems[0] = mItems[tItr];
		heapdown<itm,cfn>(mItems, tItr, 0);
	}

	CatchError
}



/*!
	Remove and return the last item, retaining available memory.
*/
template <typename itm, typename cfn, typename mm>
inline void queueh<itm,cfn,mm>::remove(itm & Item)
{
	WatchError

	Itr const tItr = mMemMan.unoccupyItr();

	Item = mItems[0];

	if (tItr)
	{
		mItems[0] = mItems[tItr];
		heapdown<itm,cfn>(mItems, tItr, 0);
	}

	CatchError
}



/*!
	Remove the last item, releasing memory when deemed.
*/
template <typename itm, typename cfn, typename mm>
inline void queueh<itm,cfn,mm>::removeMem()
{
	WatchError

	Itr const tItr = mMemMan.unoccupyItr();

	if (tItr)
	{
		mItems[0] = mItems[tItr];
		heapdown<itm,cfn>(mItems, tItr, 0);
	}

	if (mMemMan.needAutoDealloc())
	deallocMemAuto();

	CatchError
}



/*!
	Remove and return the last item, releasing memory when deemed.
*/
template <typename itm, typename cfn, typename mm>
inline void queueh<itm,cfn,mm>::removeMem(itm & Item)
{
	WatchError

	Itr const tItr = mMemMan.unoccupyItr();

	Item = mItems[0];

	if (tItr)
	{
		mItems[0] = mItems[tItr];
		heapdown<itm,cfn>(mItems, tItr, 0);
	}

	if (mMemMan.needAutoDealloc())
	deallocMemAuto();

	CatchError
}




/*!
	Reallocate more memory automatically.
*/
template<typename itm, typename cfn, typename mm>
void queueh<itm,cfn,mm>::reallocMemAuto()
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
template<typename itm, typename cfn, typename mm>
void queueh<itm,cfn,mm>::deallocMemAuto()
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
template<typename itm, typename cfn, typename mm>
void queueh<itm,cfn,mm>::adjustMemAuto()
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
template<typename itm, typename cfn, typename mm>
void queueh<itm,cfn,mm>::allocateMem(Dim const Alloc)
{
	WatchError

	Warn(!mMemMan.mismatchAlloc(Alloc), eDimensionMismatch);
	mMemMan.allocate(Alloc);

	itm * const tItems = mItems;
	mItems = new itm[mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = tItems[tItr];
	delete [] tItems;

	CatchError
}



/*!
	Return the item count.
*/
template <typename itm, typename cfn, typename mm>
inline Dim queueh<itm,cfn,mm>::itemCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the memory manager.
*/
template <typename itm, typename cfn, typename mm>
inline mm const & queueh<itm,cfn,mm>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Return the items, do not free memory with this.
*/
template <typename itm, typename cfn, typename mm>
inline itm const * queueh<itm,cfn,mm>::items() const
{
	WatchError

	return mItems;

	CatchError
}



/*!
	Return an item.
*/
template <typename itm, typename cfn, typename mm>
inline itm const & queueh<itm,cfn,mm>::operator[](Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mItems[theItr];

	CatchError
}



/*!
	Return an item.
*/
template <typename itm, typename cfn, typename mm>
inline itm const & queueh<itm,cfn,mm>::item(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mItems[theItr];

	CatchError
}



/*!
	Return the peak item.
*/
template <typename itm, typename cfn, typename mm>
inline itm const & queueh<itm,cfn,mm>::itemPeak() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eEmptyCount);

	return mItems[0];

	CatchError
}



/*!
	Return the peak iterator.
*/
template <typename itm, typename cfn, typename mm>
inline Itr queueh<itm,cfn,mm>::iteratorPeak() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eEmptyCount);

	return 0;

	CatchError
}



/*!
	Return the left child of an iterator.
*/
template<typename itm, typename cfn, typename mm>
inline Itr queueh<itm,cfn,mm>::childLeft(Itr const theItr) const
{
	WatchError

	Itr tItr = (theItr << 1) + 1;
	return tItr < mMemMan.occupied() ? tItr : InvItr;

	CatchError
}



/*!
	Return the right child of an iterator.
*/
template<typename itm, typename cfn, typename mm>
inline Itr queueh<itm,cfn,mm>::childRight(Itr const theItr) const
{
	WatchError

	Itr tItr = (theItr << 1) + 2;
	return tItr < mMemMan.occupied() ? tItr : InvItr;

	CatchError
}



/*!
	Return the left sibling of an iterator.
*/
template<typename itm, typename cfn, typename mm>
inline Itr queueh<itm,cfn,mm>::siblingLeft(Itr const theItr) const
{
	WatchError

	return ((theItr & 1) || !theItr) ?  InvItr : theItr - 1;

	CatchError
}



/*!
	Return the right sibling of an iterator.
*/
template<typename itm, typename cfn, typename mm>
inline Itr queueh<itm,cfn,mm>::siblingRight(Itr const theItr) const
{
	WatchError

	return ((theItr & 1) && (theItr + 1) < mMemMan.occupied()) ?
			theItr + 1 : InvItr;

	CatchError
}



closeEmuSpace


#endif // QueuehTccIncluded
