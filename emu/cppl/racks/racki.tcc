/*!
	@file racki.tcc
	@brief The source file for racki template class.
	@details This is the source file for racki template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef RackiTccIncluded
#define RackiTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class racki
	@brief A class to represent one-dimensional arrays of items.
	@details This class represents one-dimensional arrays of items.
*/
template <typename itm, typename mm>
class racki
{
	public:

		racki();									//!< Constructor.
		racki(mm const & theMm);					//!< Initialiser.
		racki(racki<itm,mm> const & that);			//!< Duplicator.
		racki<itm,mm> const & operator =
				(racki<itm,mm> const & that);		//!< Assigner.
		~racki();									//!< Destructor.

		//! @name Clear
		//! @{

		void clear();								//!< Clear items, retaining available memory.
		void clearMem();							//!< Clear items, releasing memory when deemed.

		//! @}
		//! @name Insert
		//! @{

		void insert();								//!< Insert an item at the end, assuming memory available.
		void insert(itm const & theItem);			//!< Insert an item at the end, assuming memory available.

		void insertMem();							//!< Insert an item at the end, acquiring memory when deemed.
		void insertMem(itm const & theItem);		//!< Insert an item at the end, acquiring memory when deemed.

		Itr insertItr();							//!< Insert an item at the end and return the iterator, assuming memory available.
		Itr insertItr(itm const & theItem);			//!< Insert an item at the end and return the iterator, assuming memory available.

		Itr insertItrMem();							//!< Insert an item at the end and return the iterator, acquiring memory available.
		Itr insertItrMem(itm const & theItem);		//!< Insert an item at the end and return the iterator, acquiring memory available.

		//! @}
		//! @name Remove
		//! @{

		void remove();								//!< Remove the last item, retaining available memory.
		void removeMem();							//!< Remove the last item, releasing memroy when deemed.

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

		/*! @name Accessors */
		//! @{

		itm & operator[](Itr const theItr);					//!< Get an item at a given iterator.
		itm const & operator[](Itr const theItr) const;		//!< Get an item at a given iterator.
		itm & item(Itr const theItr);						//!< Get an item at a given iterator.
		itm const & item(Itr const theItr) const;			//!< Get an item at a given iterator.

		itm & refItem(Itr const theItr);					//!< Get an item at a given iterator.
		itm const & refItem(Itr const theItr) const;		//!< Get an item at a given iterator.
		itm * ptrItem(Itr const theItr);					//!< Get an item at a given iterator.
		itm const * ptrItem(Itr const theItr) const;		//!< Get an item at a given iterator.

		//! @}

	private:
		mm    mMemMan;		//!< Memory manager.
		itm ** mItems;		//!< The items.
};



/*!
	@def ri
	@brief A macro to denote racki.
	@details This macro denotes racki.
*/
#define ri racki



/*!
	The constructor.
*/
template<typename itm, typename mm>
racki<itm,mm>::racki()
{
	WatchError
	mItems = new itm * [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = new itm();

	CatchError
}



/*!
	The initialiser.
*/
template<typename itm, typename mm>
racki<itm,mm>::racki(mm const & theMm) : mMemMan(theMm)
{
	WatchError
	mItems = new itm * [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = new itm();
	CatchError
}



/*!
	The duplicator.
*/
template <typename itm, typename mm>
racki<itm,mm>::racki(racki<itm,mm> const & that) :
		mMemMan(that.mMemMan)
{
	WatchError
	mItems = new itm * [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = new itm(*that.mItems[tItr]);
	CatchError
}



/*!
	The destructor.
*/
template <typename itm, typename mm>
racki<itm,mm>::~racki()
{
	WatchError
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		delete mItems[tItr];
	delete [] mItems;
	CatchError
}



/*!
	The assigner.
*/
template <typename itm, typename mm>
racki<itm,mm> const & racki<itm,mm>::operator =
		(racki<itm,mm> const & that)
{
	WatchError
	if (&that == this)
		return *this;

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		delete mItems[tItr];

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		delete [] mItems;
		mItems = new itm * [that.mMemMan.acquired()];
	}

	mMemMan = that.mMemMan;

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = new itm(*that.mItems[tItr]);

	return *this;
	CatchError
}



/*!
	Clear items, retaining available memory.
*/
template<typename itm, typename mm>
inline void racki<itm,mm>::clear()
{
	WatchError

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		delete mItems[tItr];
	mMemMan.resetOccupy();

	CatchError
}



/*!
	Clear items, releasing memory when deemed.
*/
template<typename itm, typename mm>
inline void racki<itm,mm>::clearMem()
{
	WatchError

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		delete mItems[tItr];
	if (mMemMan.resetOccupyBll())
	{
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}

	CatchError
}



/*!
	Insert an item at the end of the racki, assuming memory available.
*/
template <typename itm, typename mm>
inline void racki<itm,mm>::insert()
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	mItems[mMemMan.reoccupyItr()] = new itm;
	CatchError
}




/*!
	Insert an item at the end of the racki, assuming memory available.
*/
template <typename itm, typename mm>
inline void racki<itm,mm>::insert(itm const & theItem)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	mItems[mMemMan.reoccupyItr()] = new itm(theItem);
	CatchError
}



/*!
	Insert an item at the end of the racki and return the iterator, assuming memory available.
*/
template <typename itm, typename mm>
inline Itr racki<itm,mm>::insertItr()
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);
	Itr const tItr = mMemMan.reoccupyItr();
	mItems[tItr] = new itm;
	return tItr;

	CatchError
}



/*!
	Insert an item at the end of the racki and return the iterator, assuming memory available.
*/
template <typename itm, typename mm>
inline Itr racki<itm,mm>::insertItr(itm const & theItem)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);
	Itr const tItr = mMemMan.reoccupyItr();
	mItems[tItr] = new itm(theItem);
	return tItr;

	CatchError
}



/*!
	Insert an item at the end of the racki, acquiring memory when deemed.
*/
template <typename itm, typename mm>
inline void racki<itm,mm>::insertMem()
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	mItems[mMemMan.reoccupyItr()] = new itm;
	CatchError
}




/*!
	Insert an item at the end of the racki, acquiring memory when deemed.
*/
template <typename itm, typename mm>
inline void racki<itm,mm>::insertMem(itm const & theItem)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	mItems[mMemMan.reoccupyItr()] = new itm(theItem);
	CatchError
}



/*!
	Insert an item at the end of the racki and return the iterator, acquiring memory when deemed.
*/
template <typename itm, typename mm>
inline Itr racki<itm,mm>::insertItrMem()
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr const tItr = mMemMan.reoccupyItr();
	mItems[tItr] = new itm;
	return tItr;

	CatchError
}



/*!
	Insert an item at the end of the racki and return the iterator, acquiring memory when deemed.
*/
template <typename itm, typename mm>
inline Itr racki<itm,mm>::insertItrMem(itm const & theItem)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr const tItr = mMemMan.reoccupyItr();
	mItems[tItr] = new itm(theItem);
	return tItr;

	CatchError
}




/*!
	Remove an item from the end of the racki, retaining available memory.
*/
template <typename itm, typename mm>
inline void racki<itm,mm>::remove()
{
	WatchError

	delete mItems[mMemMan.unoccupyItr()];
	CatchError
}



/*!
	Remove an item from the end of the racki, releasing memory when deemed.
*/
template <typename itm, typename mm>
inline void racki<itm,mm>::removeMem()
{
	WatchError

	delete mItems[mMemMan.unoccupyItr()];

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Acquire more memory automatically.
*/
template<typename itm, typename mm>
void racki<itm,mm>::reallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);
	mMemMan.reallocAuto();

	itm ** const tLsts = mItems;
	mItems = new itm * [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = tLsts[tItr];
	delete [] tLsts;

	CatchError
}



/*!
	Release some memory automatically.
*/
template<typename itm, typename mm>
void racki<itm,mm>::deallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);
	mMemMan.deallocAuto();

	itm ** const tLsts = mItems;
	mItems = new itm * [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = tLsts[tItr];
	delete [] tLsts;

	CatchError
}



/*!
	Adjust the memory automatically.
*/
template<typename itm, typename mm>
void racki<itm,mm>::adjustMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);
	mMemMan.adjustAuto();

	itm ** const tLsts = mItems;
	mItems = new itm * [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = tLsts[tItr];
	delete [] tLsts;

	CatchError
}



/*!
	Adjust the memory automatically.
*/
template<typename itm, typename mm>
void racki<itm,mm>::allocateMem(Dim const Alloc)
{
	WatchError

	Warn(!mMemMan.mismatchAlloc(Alloc), eDimensionMismatch);
	mMemMan.allocate(Alloc);

	itm ** const tLsts = mItems;
	mItems = new itm * [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mItems[tItr] = tLsts[tItr];
	delete [] tLsts;

	CatchError
}



/*!
	Return the item count.
*/
template <typename itm, typename mm>
inline Dim racki<itm,mm>::itemCount() const
{
	WatchError
	return mMemMan.occupied();
	CatchError
}



/*!
	Return an item at a given iterator.
*/
template <typename itm, typename mm>
inline itm const & racki<itm,mm>::operator[](Itr const theItr) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mItems[theItr];
	CatchError
}



/*!
	Return an item at a given iterator.
*/
template <typename itm, typename mm>
inline itm & racki<itm,mm>::operator[](Itr const theItr)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mItems[theItr];
	CatchError
}



/*!
	Return an item at a given iterator.
*/
template <typename itm, typename mm>
inline itm const & racki<itm,mm>::item(Itr const theItr) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mItems[theItr];
	CatchError
}



/*!
	Return an item at a given iterator.
*/
template <typename itm, typename mm>
inline itm & racki<itm,mm>::item(Itr const theItr)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mItems[theItr];
	CatchError
}



/*!
	Refer to an item at a given iterator.
*/
template <typename itm, typename mm>
inline itm const & racki<itm,mm>::refItem(Itr const theItr) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mItems[theItr];
	CatchError
}



/*!
	Refer to an item at a given iterator.
*/
template <typename itm, typename mm>
inline itm & racki<itm,mm>::refItem(Itr const theItr)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mItems[theItr];
	CatchError
}



/*!
	Point to an item at a given iterator; do not release with this.
*/
template <typename itm, typename mm>
inline itm const * racki<itm,mm>::ptrItem(Itr const theItr) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mItems[theItr];
	CatchError
}



/*!
	Point to an item at a given iterator, do not release with this.
*/
template <typename itm, typename mm>
inline itm * racki<itm,mm>::ptrItem(Itr const theItr)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mItems[theItr];
	CatchError
}



closeEmuSpace


#endif	//	RackiTccIncluded
