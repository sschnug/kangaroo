/*!
	@file nmmm.hpp
	@brief The source file for fixed-allocation flexible-occupancy memory manager maintaining a margin, best suited for queues and texts.
	@details This is the source file for fixed-allocation flexible-occupancy memory manager maintaining a margin, best suited for queues and texts.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef NmmmHppIncluded
#define NmmmHppIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace


/*!
	@class nmmm
	@brief A class to represent fixed-allocation flexible-occupancy memory manager maintaining a margin, best suited for queues and texts.
	@details This class represents fixed-allocation flexible-occupancy memory manager maintaining a margin, best suited for queues and texts.
*/
class nmmm : public mm
{
	public:

		/*! @name Dimensions */
		//! @{

		Dim threshold() const;			//!< Minimum threshold extent.
		Dim acquired() const;			//!< Actually acquired extent.
		Dim allocated() const;			//!< Extent logical allocated.
		Dim occupied() const;			//!< Number of occupied extent.
		Dim unoccupied() const;			//!< Number of unoccupied extent.

		//! @}

		/*! @name States */
		//! @{

		Bll emptyOccupied() const;	//!< Whether the number of occupied is empty.
		Bll existOccupied() const;	//!< Whether the number of occupied non-zero.
		Bll fullyOccupied() const;	//!< Whether all allocated are fully occupied.

		//! @}

		/*! @name Iterators */
		//! @{

		Bll beyondAllocated(Itr const theItr) const;	//!< Whether the iterator is beyond the allocated range.
		Bll beyondOccupied(Itr const theItr) const;		//!< Whether the iterator is beyond the occupied range.
		Bll beyondAcquired(Itr const theItr) const;		//!< Whether the iterator is beyond the acquired range.

		//! @}

		/*! @name Checkings */
		//! @{

		Bll needAutoDealloc() const;				//!< Whether automatic deallocation is needed.
		Bll needAutoRealloc() const;				//!< Whether automatic reallocation is needed.
		Bll needAutoAdjust() const;					//!< Whether automatic memory adjustment is needed.
		Bll mismatchAlloc(Dim const Alloc) const;	//!< Whether current allocation mismatches with the given extent.
		Bll deficientAlloc(Dim const Occupy) const;	//!< Whether current allocation is deficient for the given extent.

		//! @}

		/*! @name Operations */
		//! @{

		void reallocAuto();							//!< Reallocate default extent of memory.
		void deallocAuto();							//!< Deallocate default extent of memory.
		void adjustAuto();							//!< Adjust allocation with occupied extent.
		void allocate(Dim const Alloc);				//!< Adjust Allocate given extent of memory.

		//! @}

		/*! @name Occupancy */
		//! @{

		void resetOccupy();						//!< Reset occupied extents.
		Bll resetOccupyBll();					//!< Reset occupied extents and return whether successful.
		void reoccupy();						//!< Reoccupy one extent.
		void unoccupy();						//!< Unoccupy one extent.
		void occupy(Dim const Occupy);			//!< Occupy given extent.
		Itr reoccupyItr();						//!< Reoccupy one extent and return the iterator.
		Itr unoccupyItr();						//!< Unoccupy one extent and return the iterator.

		//! @}

		/*! @name Reinitialisation */
		//! @{

		void reinitialise(Dim const Alloc, Dim const Occupy);	//!< Reinitialise memory manager.

		//! @}

	public:

		enum
		{
			LoadMargin = 1								//!< Acquire additional extent.
		};

		nmmm();											//!< Constructor.
		~nmmm();										//!< Destructor.
		nmmm(Dim const Alloc);							//!< Initialiser.
		nmmm(Dim const Alloc, Dim const Occupy);		//!< Initialiser.
		nmmm(nmmm const & that);						//!< Duplicator.
		nmmm const & operator = (nmmm const & that);	//!< Assigner.

	private:

		Dim mAcquired;									//!< Number of acquired.
		Dim mAllocated;									//!< Number of allocated.
		Dim mOccupied;									//!< Number of occupied.
};



/*!
	The constructor.
*/
inline nmmm::nmmm() : mAcquired(LoadMargin),
		mAllocated(0), mOccupied(0)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
inline nmmm::~nmmm()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
inline nmmm::nmmm(Dim const Alloc) :
		mAcquired(Alloc + LoadMargin),
		mAllocated(Alloc), mOccupied(0)
{
	WatchError
	Warn(mAllocated > mAcquired, eMathOverflow);
	CatchError
}



/*!
	The initialiser.
*/
inline nmmm::nmmm(Dim const Alloc, Dim const Occupy) :
		mAcquired(Alloc + LoadMargin),
		mAllocated(Alloc), mOccupied(Occupy)
{
	WatchError
	if (Alloc < Occupy)
	{
		mAllocated = Occupy;
		mAcquired = mAllocated + LoadMargin;
	}
	Warn(mAllocated > mAcquired, eMathOverflow);
	CatchError
}



/*!
	The duplicator.
*/
inline nmmm::nmmm(nmmm const & that) : mm(that),
	mAcquired(that.mAcquired), mAllocated(that.mAllocated),
	mOccupied(that.mOccupied)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
inline nmmm const & nmmm::operator = (nmmm const & that)
{
	WatchError
	if (this != &that)
	{
		mAcquired = that.mAcquired;
		mAllocated = that.mAllocated;
		mOccupied = that.mOccupied;
	}
	return *this;
	CatchError
}



/*!
	Return threshold extent.
*/
inline Dim nmmm::threshold() const
{
	WatchError
	return mAcquired;
	CatchError
}



/*!
	Return logically allocated extent.
*/
inline Dim nmmm::allocated() const
{
	WatchError
	return mAllocated;
	CatchError
}



/*!
	Return actually acquired extent.
*/
inline Dim nmmm::acquired() const
{
	WatchError
	return mAcquired;
	CatchError
}



/*!
	Return the extent occupied.
*/
inline Dim nmmm::occupied() const
{
	WatchError
	return mOccupied;
	CatchError
}




/*!
	Return the extent unoccupied.
*/
inline Dim nmmm::unoccupied() const
{
	WatchError
	return mAllocated - mOccupied;
	CatchError
}



/*!
	Return whether the number of occupied is empty.
*/
inline Bll nmmm::emptyOccupied() const
{
	WatchError
	return !mOccupied;
	CatchError
}




/*!
	Return whether the number of occupied is non-zero.
*/
inline Bll nmmm::existOccupied() const
{
	WatchError
	return mOccupied;
	CatchError
}



/*!
	Return whether all allocated are occupied.
*/
inline Bll nmmm::fullyOccupied() const
{
	WatchError
	return mOccupied == mAllocated;
	CatchError
}



/*!
	Whether the iterator is beyond the allocated range.
*/
inline Bll nmmm::beyondAllocated(Itr const theItr) const
{
	WatchError
	return theItr >= mAllocated;
	CatchError
}



/*!
	Whether the iterator is beyond the occupied range.
*/
inline Bll nmmm::beyondOccupied(Itr const theItr) const
{
	WatchError
	return theItr >= mOccupied;
	CatchError
}



/*!
	Whether the iterator is beyond the acquired range.
*/
inline Bll nmmm::beyondAcquired(Itr const theItr) const
{
	WatchError
	return theItr >= mAcquired;
	CatchError
}


/*!
	Return whether automatic deallocation is needed.
*/
inline Bll nmmm::needAutoDealloc() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return whether automatic reallocation is needed.
*/
inline Bll nmmm::needAutoRealloc() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return whether automatic allocation adjustment is needed.
*/
inline Bll nmmm::needAutoAdjust() const
{
	WatchError
	return false;
	CatchError
}



/*!
	Return whether the current allocation mismatches with the given extent.
*/
inline Bll nmmm::mismatchAlloc(Dim const Alloc) const
{
	WatchError
	return Alloc != mAllocated;
	CatchError
}



/*!
	Return whether the current allocation is deficient for the given occupied.
*/
inline Bll nmmm::deficientAlloc(Dim const Occupy) const
{
	WatchError
	return Occupy > mAllocated;
	CatchError
}



/*!
	Reallocate for the default extent.
*/
inline void nmmm::reallocAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Deallocate for the default extent.
*/
inline void nmmm::deallocAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Allocate for the occupied extent.
*/
inline void nmmm::adjustAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Allocate for the given extent.
*/
inline void nmmm::allocate(Dim const Alloc)
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Reset the occupied extents.
*/
inline void nmmm::resetOccupy()
{
	WatchError
	if (mOccupied) mOccupied = 0;
	CatchError
}




/*!
	Reset the occupied extents and return whether successful.
*/
inline Bll nmmm::resetOccupyBll()
{
	WatchError
	if (mOccupied)
	{
		mOccupied = 0;
		return true;
	}
	return false;
	CatchError
}



/*!
	Reoccupy one extent.
*/
inline void nmmm::reoccupy()
{
	WatchError
	Warn(mOccupied == mAllocated, eAllocatedMemoryFull);

	++mOccupied;
	CatchError
}




/*!
	Unoccupy one extent.
*/
inline void nmmm::unoccupy()
{
	WatchError
	Warn(!mOccupied, eOccupiedMemoryEmpty);

	--mOccupied;
	CatchError
}



/*!
	Reoccupy one extent.
*/
inline Itr nmmm::reoccupyItr()
{
	WatchError
	Warn(mOccupied == mAllocated, eAllocatedMemoryFull);
	return mOccupied++;
	CatchError
}




/*!
	Unoccupy one extent.
*/
inline Itr nmmm::unoccupyItr()
{
	WatchError
	Warn(!mOccupied, eOccupiedMemoryEmpty);

	return --mOccupied;
	CatchError
}




/*!
	Occupy given extent.
*/
inline void nmmm::occupy(Dim const Occupy)
{
	WatchError
	Warn(Occupy > mAllocated, eInsuffMemoryAllocation);
	mOccupied = Occupy;
	CatchError
}



/*!
	Initialise memory manager.
*/
inline void nmmm::reinitialise(Dim const Alloc, Dim const Occupy)
{
	WatchError
	mOccupied = Occupy;
	mAllocated = Alloc >= Occupy ? Alloc : Occupy;
	mAcquired = mAllocated + LoadMargin;

	Warn(mAllocated > mAcquired, eMathOverflow);
	CatchError
}


closeEmuSpace



#endif // NmmmHppIncluded
