/*!
	@file rackl.tcc
	@brief The source file for rackl template class.
	@details This is the source file for rackl template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef RacklTccIncluded
#define RacklTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class rackl
	@brief A class to represent one-dimensional arrays of lists.
	@details This class represents one-dimensional arrays of lists.
*/
template <typename lst, typename mm>
class rackl
{
	public:

		rackl();									//!< Constructor.
		rackl(mm const & theMm);					//!< Initialiser.
		rackl(rackl<lst,mm> const & that);			//!< Duplicator.
		rackl<lst,mm> const & operator =
				(rackl<lst,mm> const & that);		//!< Assigner.
		~rackl();									//!< Destructor.

		//! @name Clear
		//! @{

		void clear();								//!< Clear lists, retaining available memory.
		void clearMem();							//!< Clear lists, releasing memory when deemed.

		//! @}
		//! @name Insert
		//! @{

		void insert();												//!< Insert a list at the end, assuming memory available.
		void insert(lst const & theList);							//!< Insert a list at the end, assuming memory available.
		void insert(typename lst::MmTyp const & theListMem);		//!< Insert a list at the end, assuming memory available.

		void insertMem();											//!< Insert a list at the end, assuming memory available.
		void insertMem(lst const & theList);						//!< Insert a list at the end, assuming memory available.
		void insertMem(typename lst::MmTyp const & theListMem);		//!< Insert a list at the end, assuming memory available.

		Itr insertItr();											//!< Insert a list at the end and return the iterator, assuming memory available.
		Itr insertItr(lst const & theList);							//!< Insert a list at the end and return the iterator, assuming memory available.
		Itr insertItr(typename lst::MmTyp const & theListMem);		//!< Insert a list at the end and return the iterator, assuming memory available.

		Itr insertItrMem();											//!< Insert a list at the end and return the iterator, acquiring memory available.
		Itr insertItrMem(lst const & theList);						//!< Insert a list at the end and return the iterator, acquiring memory available.
		Itr insertItrMem(typename lst::MmTyp const & theListMem);	//!< Insert a list at the end and return the iterator, acquiring memory available.

		//! @}
		//! @name Remove
		//! @{

		void remove();								//!< Remove the last list, retaining available memory.
		void removeMem();							//!< Remove the last list, releasing memroy when deemed.

		//! @}

		//! @name Memory
		//! @{

		Dim listCount() const;						//!< Get list count.
		mm const & MemMan() const;					//!< Memory manager.

		void reallocMemAuto();						//!< Reallocate memory automatically.
		void deallocMemAuto();						//!< Deallocate memory automatically.
		void adjustMemAuto();						//!< Adjust memory automatically.
		void allocateMem(Dim const Alloc);			//!< Allocate given extent of memory.

		//! @}

		/*! @name Operations */
		//! @{

		void adjustListsMemAuto();					//!< Automatically adjust lists' memory.
		void syncListsClock();						//!< Synchronise lists' clock.

		//! @}
		/*! @name Accessors */
		//! @{

		lst & operator[](Itr const theItr);					//!< Get a list at a given iterator.
		lst const & operator[](Itr const theItr) const;		//!< Get a list at a given iterator.
		lst & list(Itr const theItr);						//!< Get a list at a given iterator.
		lst const & list(Itr const theItr) const;			//!< Get a list at a given iterator.

		lst & refList(Itr const theItr);					//!< Get a list at a given iterator.
		lst const & refList(Itr const theItr) const;		//!< Get a list at a given iterator.
		lst * ptrList(Itr const theItr);					//!< Get a list at a given iterator.
		lst const * ptrList(Itr const theItr) const;		//!< Get a list at a given iterator.

		//! @}

	private:
		mm    mMemMan;		//!< Memory manager.
		lst ** mLists;		//!< The lists.
};



/*!
	@def rl
	@brief A macro to denote rackl.
	@details This macro denotes rackl.
*/
#define rl rackl



/*!
	The constructor.
*/
template<typename lst, typename mm>
rackl<lst,mm>::rackl()
{
	WatchError
	mLists = new lst * [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mLists[tItr] = new lst();

	CatchError
}



/*!
	The initialiser.
*/
template<typename lst, typename mm>
rackl<lst,mm>::rackl(mm const & theMm) : mMemMan(theMm)
{
	WatchError
	mLists = new lst * [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mLists[tItr] = new lst();
	CatchError
}



/*!
	The duplicator.
*/
template <typename lst, typename mm>
rackl<lst,mm>::rackl(rackl<lst,mm> const & that) :
		mMemMan(that.mMemMan)
{
	WatchError
	mLists = new lst * [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mLists[tItr] = new lst(*that.mLists[tItr]);
	CatchError
}



/*!
	The destructor.
*/
template <typename lst, typename mm>
rackl<lst,mm>::~rackl()
{
	WatchError
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		delete mLists[tItr];
	delete [] mLists;
	CatchError
}



/*!
	The assigner.
*/
template <typename lst, typename mm>
rackl<lst,mm> const & rackl<lst,mm>::operator =
		(rackl<lst,mm> const & that)
{
	WatchError
	if (&that == this)
		return *this;

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		delete mLists[tItr];

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		delete [] mLists;
		mLists = new lst * [that.mMemMan.acquired()];
	}

	mMemMan = that.mMemMan;

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mLists[tItr] = new lst(*that.mLists[tItr]);

	return *this;
	CatchError
}



/*!
	Clear lists, retaining available memory.
*/
template<typename lst, typename mm>
inline void rackl<lst,mm>::clear()
{
	WatchError

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		delete mLists[tItr];
	mMemMan.resetOccupy();

	CatchError
}



/*!
	Clear lists, releasing memory when deemed.
*/
template<typename lst, typename mm>
inline void rackl<lst,mm>::clearMem()
{
	WatchError

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		delete mLists[tItr];

	if (mMemMan.resetOccupyBll())
	{
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}

	CatchError
}



/*!
	Insert a list at the end of the rackl, assuming memory available.
*/
template <typename lst, typename mm>
inline void rackl<lst,mm>::insert()
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	mLists[mMemMan.reoccupyItr()] = new lst;
	CatchError
}




/*!
	Insert a list at the end of the rackl, assuming memory available.
*/
template <typename lst, typename mm>
inline void rackl<lst,mm>::insert(lst const & theList)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	mLists[mMemMan.reoccupyItr()] = new lst(theList);
	CatchError
}



/*!
	Insert a list at the end of the rackl, assuming memory available.
*/
template <typename lst, typename mm>
inline void rackl<lst,mm>::insert(typename lst::MmTyp const & theListMem)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	mLists[mMemMan.reoccupyItr()] = new lst(theListMem);
	CatchError
}



/*!
	Insert a list at the end of the rackl and return the iterator, assuming memory available.
*/
template <typename lst, typename mm>
inline Itr rackl<lst,mm>::insertItr()
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);
	Itr const tItr = mMemMan.reoccupyItr();
	mLists[tItr] = new lst;
	return tItr;

	CatchError
}



/*!
	Insert a list at the end of the rackl and return the iterator, assuming memory available.
*/
template <typename lst, typename mm>
inline Itr rackl<lst,mm>::insertItr(lst const & theList)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);
	Itr const tItr = mMemMan.reoccupyItr();
	mLists[tItr] = new lst(theList);
	return tItr;

	CatchError
}



/*!
	Insert a list at the end of the rackl and return the iterator, assuming memory available.
*/
template <typename lst, typename mm>
inline Itr rackl<lst,mm>::insertItr(typename lst::MmTyp const & theListMem)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);
	Itr const tItr = mMemMan.reoccupyItr();
	mLists[tItr] = new lst(theListMem);
	return tItr;

	CatchError
}



/*!
	Insert a list at the end of the rackl, acquiring memory when deemed.
*/
template <typename lst, typename mm>
inline void rackl<lst,mm>::insertMem()
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	mLists[mMemMan.reoccupyItr()] = new lst;
	CatchError
}




/*!
	Insert a list at the end of the rackl, acquiring memory when deemed.
*/
template <typename lst, typename mm>
inline void rackl<lst,mm>::insertMem(lst const & theList)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	mLists[mMemMan.reoccupyItr()] = new lst(theList);
	CatchError
}



/*!
	Insert a list at the end of the rackl, acquiring memory when deemed.
*/
template <typename lst, typename mm>
inline void rackl<lst,mm>::insertMem(typename lst::MmTyp const & theListMem)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	mLists[mMemMan.reoccupyItr()] = new lst(theListMem);
	CatchError
}



/*!
	Insert a list at the end of the rackl and return the iterator, acquiring memory when deemed.
*/
template <typename lst, typename mm>
inline Itr rackl<lst,mm>::insertItrMem()
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr const tItr = mMemMan.reoccupyItr();
	mLists[tItr] = new lst;
	return tItr;

	CatchError
}



/*!
	Insert a list at the end of the rackl and return the iterator, acquiring memory when deemed.
*/
template <typename lst, typename mm>
inline Itr rackl<lst,mm>::insertItrMem(lst const & theList)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr const tItr = mMemMan.reoccupyItr();
	mLists[tItr] = new lst(theList);
	return tItr;

	CatchError
}




/*!
	Insert a list at the end of the rackl and return the iterator, acquiring memory when deemed.
*/
template <typename lst, typename mm>
inline Itr rackl<lst,mm>::insertItrMem(typename lst::MmTyp const & theListMem)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr const tItr = mMemMan.reoccupyItr();
	mLists[tItr] = new lst(theListMem);
	return tItr;

	CatchError
}



/*!
	Remove a list from the end of the rackl, retaining available memory.
*/
template <typename lst, typename mm>
inline void rackl<lst,mm>::remove()
{
	WatchError

	delete mLists[mMemMan.unoccupyItr()];
	CatchError
}



/*!
	Remove a list from the end of the rackl, releasing memory when deemed.
*/
template <typename lst, typename mm>
inline void rackl<lst,mm>::removeMem()
{
	WatchError

	delete mLists[mMemMan.unoccupyItr()];

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Acquire more memory automatically.
*/
template<typename lst, typename mm>
void rackl<lst,mm>::reallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);
	mMemMan.reallocAuto();

	lst ** const tLsts = mLists;
	mLists = new lst * [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mLists[tItr] = tLsts[tItr];
	delete [] tLsts;

	CatchError
}



/*!
	Release some memory automatically.
*/
template<typename lst, typename mm>
void rackl<lst,mm>::deallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);
	mMemMan.deallocAuto();

	lst ** const tLsts = mLists;
	mLists = new lst * [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mLists[tItr] = tLsts[tItr];
	delete [] tLsts;

	CatchError
}



/*!
	Adjust the memory automatically.
*/
template<typename lst, typename mm>
void rackl<lst,mm>::adjustMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);
	mMemMan.adjustAuto();

	lst ** const tLsts = mLists;
	mLists = new lst * [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mLists[tItr] = tLsts[tItr];
	delete [] tLsts;

	CatchError
}



/*!
	Allocate memory.
*/
template<typename lst, typename mm>
void rackl<lst,mm>::allocateMem(Dim const Alloc)
{
	WatchError

	Warn(!mMemMan.mismatchAlloc(Alloc), eDimensionMismatch);
	mMemMan.allocate(Alloc);

	lst ** const tLsts = mLists;
	mLists = new lst * [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mLists[tItr] = tLsts[tItr];
	delete [] tLsts;

	CatchError
}



/*!
	Adjust lists' memory.
*/
template<typename lst, typename mm>
void rackl<lst,mm>::adjustListsMemAuto()
{
	WatchError
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
	{
		if (mLists[tItr]->MemMan().needAutoAdjust())
			mLists[tItr]->adjustMemAuto();
	}
	CatchError
}



/*!
	Synchronise lists' clock.
*/
template<typename lst, typename mm>
void rackl<lst,mm>::syncListsClock()
{
	WatchError
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mLists[tItr]->syncClk();
	CatchError
}



/*!
	Return the list count.
*/
template <typename lst, typename mm>
inline Dim rackl<lst,mm>::listCount() const
{
	WatchError
	return mMemMan.occupied();
	CatchError
}



/*!
	Return a list at a given iterator.
*/
template <typename lst, typename mm>
inline lst const & rackl<lst,mm>::operator[](Itr const theItr) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mLists[theItr];
	CatchError
}



/*!
	Return a list at a given iterator.
*/
template <typename lst, typename mm>
inline lst & rackl<lst,mm>::operator[](Itr const theItr)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mLists[theItr];
	CatchError
}



/*!
	Return a list at a given iterator.
*/
template <typename lst, typename mm>
inline lst const & rackl<lst,mm>::list(Itr const theItr) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mLists[theItr];
	CatchError
}



/*!
	Return a list at a given iterator.
*/
template <typename lst, typename mm>
inline lst & rackl<lst,mm>::list(Itr const theItr)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mLists[theItr];
	CatchError
}



/*!
	Refer to a list at a given iterator.
*/
template <typename lst, typename mm>
inline lst const & rackl<lst,mm>::refList(Itr const theItr) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mLists[theItr];
	CatchError
}



/*!
	Refer to a list at a given iterator.
*/
template <typename lst, typename mm>
inline lst & rackl<lst,mm>::refList(Itr const theItr)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return *mLists[theItr];
	CatchError
}



/*!
	Point to a list at a given iterator; do not release with this.
*/
template <typename lst, typename mm>
inline lst const * rackl<lst,mm>::ptrList(Itr const theItr) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mLists[theItr];
	CatchError
}



/*!
	Point to a list at a given iterator, do not release with this.
*/
template <typename lst, typename mm>
inline lst * rackl<lst,mm>::ptrList(Itr const theItr)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mLists[theItr];
	CatchError
}



closeEmuSpace


#endif	//	RacklTccIncluded
