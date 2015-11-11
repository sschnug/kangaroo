/*!
	@file xmmh.hpp
	@brief The source file for extendable-allocation flexible-occupancy memory manager, best suited for hash tables.
	@details This is the source file for extendable-allocation flexible-occupancy memory manager, best suited for hash tables.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef XmmhHppIncluded
#define XmmhHppIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace


/*!
	@class xmmh
	@brief A class to represent extendable-allocation flexible-occupancy memory manager, best suited for hash tables.
	@details This class represents extendable-allocation flexible-occupancy memory manager, best suited for hash tables.
*/
class xmmh : public mm
{
	public:

		/*! @name Dimensions */
		//! @{

		Dim threshold() const;		//!< Minimum threshold extent.
		Dim allocated() const;		//!< Extent logical allocated.
		Dim acquired() const;		//!< Actually acquired extent.
		Dim occupied() const;		//!< Number of occupied extent.
		Dim unoccupied() const;		//!< Number of unoccupied extent.

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
		Bll needAutoAdjust() const;					//!< Whether automatic adjustment is needed.
		Bll mismatchAlloc(Dim const Alloc) const;	//!< Whether current allocation mismatches with the given extent.
		Bll deficientAlloc(Dim const Occupy) const;	//!< Whether current allocation is deficient for the given extent.

		//! @}

		/*! @name Operations */
		//! @{

		void reallocAuto();				//!< Reallocate default extent of memory.
		void deallocAuto();				//!< Deallocate default extent of memory.
		void adjustAuto();				//!< Adjust allocation with occupied extent.
		void allocate(Dim const Alloc);	//!< Adjust Allocate given extent of memory.

		//! @}

		/*! @name Occupancy */
		//! @{

		void resetOccupy();				//!< Reset occupied extents.
		Bll resetOccupyBll();			//!< Reset occupied extents and return whether successful.
		void reoccupy();				//!< Reoccupy one extent.
		void unoccupy();				//!< Unoccupy one extent.
		Itr reoccupyItr();				//!< Reoccupy one extent and return the iterator.
		Itr unoccupyItr();				//!< Unoccupy one extent and return the iterator.
		void occupy(Dim const Occupy);	//!< Occupy given extent.

		//! @}

		/*! @name Reinitialisation */
		//! @{

		void reinitialise(Dim const Alloc, Dim const Occupy);	//!< Reinitialise memory manager.

		//! @}

	public:

		enum
		{
			LoadMargin = 1,			//!< Acquire additional extent.
			ReallocShift = 1,		//!< Reallocation shift.
			ReallocRatio = 2,		//!< Reallocation Ratio.
			LoadNumer 	 = 3,		//!< Numerator of the load factor.
			LoadDenom    = 4		//!< Denominator of the load factor.
		};

		xmmh();											//!< Constructor.
		~xmmh();										//!< Destructor.
		xmmh(Dim const Alloc);							//!< Initialiser.
		xmmh(Dim const Alloc, Dim const Occupy);		//!< Initialiser.
		xmmh(xmmh const & that);						//!< Duplicator.
		xmmh const & operator = (xmmh const & that);	//!< Assigner.

	private:

		Dim mAcquired;									//!< Number of acquired.
		Dim mAllocated;									//!< Number of allocated.
		Dim mOccupied;									//!< Number of occupied.
};



/*!
	The constructor.
*/
inline xmmh::xmmh() : mAcquired(LoadMargin),
		mAllocated(0), mOccupied(0)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
inline xmmh::~xmmh()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
inline xmmh::xmmh(Dim const Alloc) :
		mAcquired(Alloc * LoadDenom / LoadNumer + LoadMargin),
		mAllocated(Alloc), mOccupied(0)
{
	WatchError
	Warn(mAllocated > mAcquired, eMathOverflow);
	CatchError
}



/*!
	The initialiser.
*/
inline xmmh::xmmh(Dim const Alloc, Dim const Occupy) :
		mAcquired(Alloc * LoadDenom / LoadNumer + LoadMargin),
		mAllocated(Alloc), mOccupied(Occupy)
{
	WatchError
	if (Alloc < Occupy)
	{
		mAllocated = Occupy;
		mAcquired = mAllocated * LoadDenom / LoadNumer + LoadMargin;
	}
	Warn(mAllocated > mAcquired, eMathOverflow);
	CatchError
}



/*!
	The duplicator.
*/
inline xmmh::xmmh(xmmh const & that) : mm(that),
	mAcquired(that.mAcquired),
	mAllocated(that.mAllocated), mOccupied(that.mOccupied)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
inline xmmh const & xmmh::operator = (xmmh const & that)
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
inline Dim xmmh::threshold() const
{
	WatchError
	return mAcquired;
	CatchError
}



/*!
	Return logically allocated extent.
*/
inline Dim xmmh::allocated() const
{
	WatchError
	return mAllocated;
	CatchError
}



/*!
	Return actually acquired extent.
*/
inline Dim xmmh::acquired() const
{
	WatchError
	return mAcquired;
	CatchError
}



/*!
	Return the extent occupied.
*/
inline Dim xmmh::occupied() const
{
	WatchError
	return mOccupied;
	CatchError
}




/*!
	Return the extent unoccupied.
*/
inline Dim xmmh::unoccupied() const
{
	WatchError
	return mAllocated - mOccupied;
	CatchError
}



/*!
	Return whether the number of occupied is empty.
*/
inline Bll xmmh::emptyOccupied() const
{
	WatchError
	return !mOccupied;
	CatchError
}



/*!
	Return whether the number of occupied is non-empty.
*/
inline Bll xmmh::existOccupied() const
{
	WatchError
	return mOccupied;
	CatchError
}




/*!
	Return whether all allocated are fully occupied.
*/
inline Bll xmmh::fullyOccupied() const
{
	WatchError
	return mOccupied == mAllocated;
	CatchError
}



/*!
	Whether the iterator is beyond the allocated range.
*/
inline Bll xmmh::beyondAllocated(Itr const theItr) const
{
	WatchError
	return theItr >= mAllocated;
	CatchError
}



/*!
	Whether the iterator is beyond the occupied range.
*/
inline Bll xmmh::beyondOccupied(Itr const theItr) const
{
	WatchError
	return theItr >= mOccupied;
	CatchError
}



/*!
	Whether the iterator is beyond the acquired range.
*/
inline Bll xmmh::beyondAcquired(Itr const theItr) const
{
	WatchError
	return theItr >= mAcquired;
	CatchError
}



/*!
	Return whether automatic deallocation is needed.
*/
inline Bll xmmh::needAutoDealloc() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return whether automatic reallocation is needed.
*/
inline Bll xmmh::needAutoRealloc() const
{
	WatchError
	return mOccupied == mAllocated;
	CatchError
}




/*!
	Return whether automatic allocation is needed.
*/
inline Bll xmmh::needAutoAdjust() const
{
	WatchError
	return mOccupied != mAllocated;
	CatchError
}



/*!
	Return whether mismatching with the given extent.
*/
inline Bll xmmh::mismatchAlloc(Dim const Alloc) const
{
	WatchError
	return Alloc != mAllocated;
	CatchError
}



/*!
	Return whether deficient for the given extent.
*/
inline Bll xmmh::deficientAlloc(Dim const Occupy) const
{
	WatchError
	return Occupy > mAllocated;
	CatchError
}



/*!
	Reallocate the default extent.
*/
inline void xmmh::reallocAuto()
{
	WatchError
	Warn(mOccupied != mAllocated, eMemoryAllocation);

	#if CheckError
	Dim tAllocated = mAllocated;
	#endif

	mAllocated <<= ReallocShift;
	mAllocated += LoadMargin;
	mAcquired = mAllocated * LoadDenom / LoadNumer + LoadMargin;

	#if CheckError
	if (mAllocated < tAllocated)	// Overflow
		Throw(eMathOverflow);
	#endif
	Warn(mAllocated > mAcquired, eMathOverflow);
	CatchError
}



/*!
	Deallocate for the default extent.
*/
inline void xmmh::deallocAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Adjust allocation with the occupied extent.
*/
inline void xmmh::adjustAuto()
{
	WatchError
	Warn(mAllocated == mOccupied, eMemoryAllocation);

	mAllocated = mOccupied;
	mAcquired = mAllocated * LoadDenom / LoadNumer + LoadMargin;
	Warn(mAllocated > mAcquired, eMathOverflow);
	CatchError
}



/*!
	Allocate for the given extent.
*/
inline void xmmh::allocate(Dim const Alloc)
{
	WatchError
	Warn(Alloc <= mAllocated, eMemoryAllocation);
	Warn(Alloc < mOccupied, eInsuffMemoryAllocation);
	mAllocated = Alloc;
	mAcquired = mAllocated * LoadDenom / LoadNumer + LoadMargin;
	Warn(mAllocated > mAcquired, eMathOverflow);
	CatchError
}



/*!
	Reset the occupied extents.
*/
inline void xmmh::resetOccupy()
{
	WatchError
	if (mOccupied) mOccupied = 0;
	CatchError
}




/*!
	Reset the occupied extents and return whether successful.
*/
inline Bll xmmh::resetOccupyBll()
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
inline void xmmh::reoccupy()
{
	WatchError
	Warn(mOccupied == mAllocated, eAllocatedMemoryFull);

	++mOccupied;
	CatchError
}




/*!
	Unoccupy one extent.
*/
inline void xmmh::unoccupy()
{
	WatchError
	Warn(!mOccupied, eOccupiedMemoryEmpty);

	--mOccupied;
	CatchError
}



/*!
	Reoccupy one extent.
*/
inline Itr xmmh::reoccupyItr()
{
	WatchError
	Warn(mOccupied == mAllocated, eAllocatedMemoryFull);
	return mOccupied++;
	CatchError
}




/*!
	Unoccupy one extent.
*/
inline Itr xmmh::unoccupyItr()
{
	WatchError
	Warn(!mOccupied, eOccupiedMemoryEmpty);

	return --mOccupied;
	CatchError
}



/*!
	Occupy given extent.
*/
inline void xmmh::occupy(Dim const Occupy)
{
	WatchError
	Warn(Occupy > mAllocated, eInsuffMemoryAllocation);
	mOccupied = Occupy;
	CatchError
}



/*!
	Initialise memory manager.
*/
inline void xmmh::reinitialise(Dim const Alloc, Dim const Occupy)
{
	WatchError
	mOccupied = Occupy;
	mAllocated = Alloc >= Occupy ? Alloc : Occupy;
	mAcquired = mAllocated * LoadDenom / LoadNumer + LoadMargin;
	Warn(mAllocated > mAcquired, eMathOverflow);
	CatchError
}


closeEmuSpace



#endif // XmmhHppIncluded
