/*!
	@file queuec.tcc
	@brief The source file for queuec template class.
	@details This is the source file for queuec template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef QueuecTccIncluded
#define QueuecTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class queuec
	@brief A class to represent circular queues.
	@details This class represents circular queues.
		The iterators are invalid under relocation of items
		due to memory management operations.
*/
template <typename itm, typename mm>
class queuec
{
	public:
		typedef mm MmTyp;								//!< Memory manager.

		queuec();										//!< Constructor.
		queuec(mm const & theMm);						//!< Initialiser.
		queuec(queuec<itm,mm> const & that);			//!< Duplicator.
		queuec<itm,mm> const & operator =
				(queuec<itm,mm> const & that);			//!< Assigner.
		~queuec();										//!< Destructor.

		//! @name Synchronise
		//! @{

		void syncClk();								//!< Synchronise clock.

		//! @}

		//! @name Clear
		//! @{

		void clear();								//!< Clear items, retaining available memory.
		void clearMem();							//!< Clear items, releasing memory when deemed.

		//! @}
		//! @name Insert
		//! @{

		void insert();								//!< Insert an item at the end, assuming memory available.
		void insertMem();							//!< Insert an item at the end, acquiring memory when needed.
		void insert(itm const & Item);				//!< Insert an item at the end, assuming memory available.
		void insertMem(itm const & Item);			//!< Insert an item at the end, acquiring memory when needed.

		//! @}

		//! @name Remove
		//! @{

		void remove();								//!< Remove the last item, retaining available memory.
		void removeMem();							//!< Remove the last item, releasing memroy when deemed.
		void remove(itm & Item);					//!< Remove and return the last item, retaining available memory.
		void removeMem(itm & Item);					//!< Remove and return the last item, releasing memroy when deemed.

		//! @}
		//! @name Memory
		//! @{

		Dim itemCount() const;						//!< Get item count.
		Dim slotCount() const;						//!< Get slot count.
		mm const & MemMan() const;					//!< Memory manager.

		void reallocMemAuto();						//!< Reallocate memory automatically.
		void deallocMemAuto();						//!< Deallocate memory automatically.
		void adjustMemAuto();						//!< Adjust memory automatically.
		void allocateMem(Dim const Alloc);			//!< Allocate given extent of memory.

		//! @}

		/*! @name Accessors */
		//! @{

		Bll occupiedSlot(Itr const theItr) const;		//!< Slot occupied?
		itm & operator[](Itr const theItr);				//!< Get an item.
		itm const & operator[](Itr const theItr) const;	//!< Get an item.
		itm & item(Itr const theItr);					//!< Get an item.
		itm const & item(Itr const theItr) const;		//!< Get an item.

		//!@}
		/*! @name Iterators */
		//! @{

		Itr beginQueue() const;						//!< Get the inclusive begin.
		Itr endQueue() const;						//!< Get the exclusive end.
		Itr moveQueue(Itr const theItr) const;		//!< Get the next iterator.

		//!@}

		//! @name Last Item
		//! @{

		itm & beginItem();						//!< Get the begin item.
		itm const & beginItem() const;			//!< Get the begin item.

		//! @}

	private:

		mm	   mMemMan;				//!< The memory manager.
		Itr    mBegin;				//!< Begin inclusive iterator.
		Itr    mEnd;				//!< End exclusive iterator.
		itm *  mItems;				//!< The queuec items.
};



/*!
	@def qc
	@brief A macro to denote queuec.
	@details This macro denotes queuec.
*/
#define qc queuec



/*!
	The constructor.
*/
template<typename itm, typename mm>
queuec<itm,mm>::queuec()
{
	WatchError
	Alert(mMemMan.LoadMargin < 1, eUnsuitMemoryManager);

	mBegin = 0;
	mEnd = mBegin + mMemMan.occupied();
	mItems = new itm [mMemMan.acquired()];

	for(Itr tItr1 = 0, tItr2 = mBegin;
			tItr1 < mMemMan.occupied(); ++tItr1)
	{
		mItems[tItr2] = itm();
		tItr2 = (tItr2 + 1) % mMemMan.acquired();
	}

	CatchError
}



/*!
	The initialiser.
*/
template<typename itm, typename mm>
queuec<itm,mm>::queuec(mm const & theMm) :
		mMemMan(theMm)
{
	WatchError
	Alert(mMemMan.LoadMargin < 1, eUnsuitMemoryManager);

	mBegin = 0;
	mEnd = mBegin + mMemMan.occupied();
	mItems = new itm [mMemMan.acquired()];

	for(Itr tItr1 = 0, tItr2 = mBegin;
			tItr1 < mMemMan.occupied(); ++tItr1)
	{
		mItems[tItr2] = itm();
		tItr2 = (tItr2 + 1) % mMemMan.acquired();
	}

	CatchError
}



/*!
	The duplicator.
*/
template <typename itm, typename mm>
queuec<itm,mm>::queuec(queuec<itm,mm> const & that) :
		mMemMan(that.mMemMan), mBegin(that.mBegin), mEnd(that.mEnd)
{
	WatchError

	mItems = new itm [mMemMan.acquired()];
	for(Itr tItr1 = 0, tItr2 = mBegin; tItr1 < mMemMan.occupied(); ++tItr1)
	{
		mItems[tItr2] = that.mItems[tItr2];
		tItr2 = (tItr2 + 1) % mMemMan.acquired();
	}

	CatchError
}



/*!
	The destructor.
*/
template <typename itm, typename mm>
queuec<itm,mm>::~queuec()
{
	WatchError

	delete [] mItems;

	CatchError
}



/*!
	The assigner.
*/
template <typename itm, typename mm>
queuec<itm,mm> const & queuec<itm,mm>::operator =
		(queuec<itm,mm> const & that)
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
	mBegin = that.mBegin;
	mEnd = that.mEnd;

	for(Itr tItr1 = 0, tItr2 = mBegin;
			tItr1 < that.mMemMan.occupied(); ++tItr1)
	{
		mItems[tItr2] = that.mItems[tItr2];
		tItr2 = (tItr2 + 1) % that.mMemMan.occupied();
	}

	return *this;

	CatchError
}



/*!
	Synchronise clock.
*/
template <typename itm, typename mm>
inline void queuec<itm,mm>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}



/*!
	Clear items, retaining available memory.
*/
template<typename itm, typename mm>
inline void queuec<itm,mm>::clear()
{
	WatchError

	if (mMemMan.resetOccupyBll())
		mBegin = mEnd = 0;

	CatchError
}



/*!
	Clear items, releasing memory when deemed.
*/
template<typename itm, typename mm>
inline void queuec<itm,mm>::clearMem()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		mBegin = mEnd = 0;
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}

	CatchError
}



/*!
	Insert an item at the end of the queuec, assuming memory available.
*/
template <typename itm, typename mm>
inline void queuec<itm,mm>::insert()
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	mMemMan.reoccupy();
	mItems[mEnd++] = itm();
	mEnd %= mMemMan.acquired();

	CatchError
}



/*!
	Insert an item at the end of the queuec, assuming memory available.
*/
template <typename itm, typename mm>
inline void queuec<itm,mm>::insert(itm const & theItem)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	mMemMan.reoccupy();
	mItems[mEnd++] = theItem;
	 mEnd %= mMemMan.acquired();

	CatchError
}


/*!
	Insert an item at the end of the queuec, acquiring memory when deemed.
*/
template <typename itm, typename mm>
inline void queuec<itm,mm>::insertMem()
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	mMemMan.reoccupy();
	mItems[mEnd++] = itm();
	 mEnd %= mMemMan.acquired();

	CatchError
}



/*!
	Insert an item at the end of the queuec, acquiring memory when deemed.
*/
template <typename itm, typename mm>
inline void queuec<itm,mm>::insertMem(itm const & theItem)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	mMemMan.reoccupy();
	mItems[mEnd++] = theItem;
	 mEnd %= mMemMan.acquired();

	CatchError
}



/*!
	Remove an item from the begin of the circle, retaining available memory.
*/
template <typename itm, typename mm>
inline void queuec<itm,mm>::remove()
{
	WatchError

	mMemMan.unoccupy();
	mBegin = (mBegin + 1) % mMemMan.acquired();

	CatchError
}



/*!
	Remove an item from the begining of the queuec, retaining available memory.
*/
template <typename itm, typename mm>
inline void queuec<itm,mm>::remove(itm & theItem)
{
	WatchError

	mMemMan.unoccupy();
	theItem = mItems[mBegin++];
	mBegin %= mMemMan.acquired();

	CatchError
}




/*!
	Remove an item from the begining of the queuec, releasing memory when deemed.
*/
template <typename itm, typename mm>
inline void queuec<itm,mm>::removeMem()
{
	WatchError

	mMemMan.unoccupy();
	mBegin = (mBegin + 1) % mMemMan.acquired();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Remove an item from the begining of the queuec, releasing memory when deemed.
*/
template <typename itm, typename mm>
inline void queuec<itm,mm>::removeMem(itm & theItem)
{
	WatchError

	mMemMan.unoccupy();
	theItem = mItems[mBegin++];
	mBegin %= mMemMan.acquired();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Acquire more memory automatically.
*/
template<typename itm, typename mm>
void queuec<itm,mm>::reallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);
	Dim tAcquired = mMemMan.acquired();
	itm * const tItms = mItems;
	mMemMan.reallocAuto();

	mItems = new itm[mMemMan.acquired()];
	for(Itr tItr1 = 0, tItr2 = mBegin;
		tItr1 < mMemMan.occupied(); ++tItr1)
	{
		mItems[tItr1] = tItms[tItr2];
		tItr2 = (tItr2 + 1) % tAcquired;
	}
	mBegin = 0, mEnd = mMemMan.occupied();
	delete [] tItms;

	CatchError
}



/*!
	Release some memory automatically.
*/
template<typename itm, typename mm>
void queuec<itm,mm>::deallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);
	Dim tAcquired = mMemMan.acquired();
	itm * const tItms = mItems;
	mMemMan.deallocAuto();

	mItems = new itm[mMemMan.acquired()];
	for(Itr tItr1 = 0, tItr2 = mBegin;
		tItr1 < mMemMan.occupied(); ++tItr1)
	{
		mItems[tItr1] = tItms[tItr2];
		tItr2 = (tItr2 + 1) % tAcquired;
	}
	mBegin = 0, mEnd = mMemMan.occupied();
	delete [] tItms;

	CatchError
}



/*!
	Adjust the memory automatically.
*/
template<typename itm, typename mm>
void queuec<itm,mm>::adjustMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);
	Dim tAcquired = mMemMan.acquired();
	itm * const tItms = mItems;
	mMemMan.adjustAuto();

	mItems = new itm[mMemMan.acquired()];
	for(Itr tItr1 = 0, tItr2 = mBegin;
		tItr1 < mMemMan.occupied(); ++tItr1)
	{
		mItems[tItr1] = tItms[tItr2];
		tItr2 = (tItr2 + 1) % tAcquired;
	}
	mBegin = 0, mEnd = mMemMan.occupied();
	delete [] tItms;

	CatchError
}




/*!
	Allocate the memory.
*/
template<typename itm, typename mm>
void queuec<itm,mm>::allocateMem(Dim const Alloc)
{
	WatchError

	Warn(!mMemMan.mismatchAlloc(Alloc), eDimensionMismatch);
	Dim tAcquired = mMemMan.acquired();
	itm * const tItms = mItems;
	mMemMan.allocate(Alloc);

	mItems = new itm[mMemMan.acquired()];
	for(Itr tItr1 = 0, tItr2 = mBegin;
		tItr1 < mMemMan.occupied(); ++tItr1)
	{
		mItems[tItr1] = tItms[tItr2];
		tItr2 = (tItr2 + 1) % tAcquired;
	}
	mBegin = 0, mEnd = mMemMan.occupied();
	delete [] tItms;

	CatchError
}




/*!
	Return the item count.
*/
template <typename itm, typename mm>
inline Dim queuec<itm,mm>::itemCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the slot count.
*/
template <typename itm, typename mm>
inline Dim queuec<itm,mm>::slotCount() const
{
	WatchError

	return mMemMan.acquired();

	CatchError
}



/*!
	Whether the item at the given iterator is valid.
*/
template <typename itm, typename mm>
inline Bll queuec<itm,mm>::occupiedSlot(Itr const theItr) const
{
	WatchError

	Warn(theItr >= mMemMan.acquired(), eIteratorBeyondLimit);

	if (mBegin == mEnd)
		return false;
	else if (mBegin < mEnd)
		return (theItr >= mBegin && theItr < mEnd);
	else
		return (theItr >= mBegin || theItr < mEnd);

	CatchError
}



/*!
	Return an item from the queuec.
*/
template <typename itm, typename mm>
inline itm const & queuec<itm,mm>::operator[](Itr const theItr) const
{
	WatchError

	Warn(theItr >= mMemMan.acquired() || mBegin == mEnd || (mBegin < mEnd &&
		(theItr < mBegin || theItr >= mEnd)) || (mBegin > mEnd &&
		(theItr < mBegin && theItr >= mEnd)), eIteratorBeyondLimit);

	return mItems[theItr];

	CatchError
}



/*!
	Return an item from the queuec.
*/
template <typename itm, typename mm>
inline itm & queuec<itm,mm>::operator[](Itr const theItr)
{
	WatchError

	Warn(theItr >= mMemMan.acquired() || mBegin == mEnd || (mBegin < mEnd &&
		(theItr < mBegin || theItr >= mEnd)) ||	(mBegin > mEnd &&
		(theItr < mBegin && theItr >= mEnd)), eIteratorBeyondLimit);

	return mItems[theItr];

	CatchError
}



/*!
	Return an item from the queuec.
*/
template <typename itm, typename mm>
inline itm const & queuec<itm,mm>::item(Itr const theItr) const
{
	WatchError

	Warn(theItr >= mMemMan.acquired() || mBegin == mEnd || (mBegin < mEnd &&
		(theItr < mBegin || theItr >= mEnd)) || (mBegin > mEnd &&
		(theItr < mBegin && theItr >= mEnd)), eIteratorBeyondLimit);

	return mItems[theItr];

	CatchError
}



/*!
	Return an item from the queuec.
*/
template <typename itm, typename mm>
inline itm & queuec<itm,mm>::item(Itr const theItr)
{
	WatchError

	Warn(theItr >= mMemMan.acquired() || mBegin == mEnd || (mBegin < mEnd &&
		(theItr < mBegin || theItr >= mEnd)) || (mBegin > mEnd &&
		(theItr < mBegin && theItr >= mEnd)), eIteratorBeyondLimit);

	return mItems[theItr];

	CatchError
}



/*!
	Return the inclusive begin.
*/
template <typename itm, typename mm>
inline Itr queuec<itm,mm>::beginQueue() const
{
	WatchError

	return mBegin;

	CatchError
}



/*!
	Return the exclusive end.
*/
template <typename itm, typename mm>
inline Itr queuec<itm,mm>::endQueue() const
{
	WatchError

	return mEnd;

	CatchError
}



/*!
	Return the next iterator or the end.
*/
template <typename itm, typename mm>
inline Itr queuec<itm,mm>::moveQueue(Itr const theItr) const
{
	WatchError

	Warn(theItr >= mMemMan.acquired() || mBegin == mEnd ||
		(mBegin < mEnd && (theItr < mBegin ||
		theItr >= mEnd)) || (mBegin > mEnd &&
		(theItr < mBegin && theItr >= mEnd)),
		eIteratorBeyondLimit);

	return (theItr + 1) % mMemMan.acquired();

	CatchError
}



/*!
	Return an item from the queuec.
*/
template <typename itm, typename mm>
inline itm const & queuec<itm,mm>::beginItem() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eEmptyDimension);

	return mItems[mBegin];

	CatchError
}



/*!
	Return an item from the queuec.
*/
template <typename itm, typename mm>
inline itm & queuec<itm,mm>::beginItem()
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eEmptyDimension);

	return mItems[mBegin];

	CatchError
}



closeEmuSpace


#endif // QueuecTccIncluded
