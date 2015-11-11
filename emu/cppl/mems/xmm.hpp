/*!
	@file xmm.hpp
	@brief The source file for extendable-allocation flexible-occupancy memory manager.
	@details This is the source file for extendable-allocation flexible-occupancy memory manager.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef XmmHppIncluded
#define XmmHppIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace


/*!
	@class xmm
	@brief A class to represent extendable-allocation flexible-occupancy memory manager.
	@details This class represents extendable-allocation flexible-occupancy memory manager.
*/
class xmm : public mm
{
	public:

		/*! @name Dimensions */
		//! @{

		Dim threshold() const;	//!< Minimum threshold extent.
		Dim allocated() const;	//!< Extent logical allocated.
		Dim acquired() const;	//!< Actually acquired extent.
		Dim occupied() const;	//!< Number of occupied extent.
		Dim unoccupied() const;	//!< Number of unoccupied extent.

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
			ReallocShift = 1,	//!< Reallocation shift.
			ReallocRatio = 2	//!< Reallocation Ratio.
		};

		xmm();										//!< Constructor.
		~xmm();										//!< Destructor.
		xmm(Dim const Alloc);						//!< Initialiser.
		xmm(Dim const Alloc, Dim const Occupy);		//!< Initialiser.
		xmm(xmm const & that);						//!< Duplicator.
		xmm const & operator = (xmm const & that);	//!< Assigner.

	private:

		Dim mAllocated;	//!< Number of allocated.
		Dim mOccupied;	//!< Number of occupied.
};



/*!
	The constructor.
*/
inline xmm::xmm() : mAllocated(0), mOccupied(0)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
inline xmm::~xmm()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
inline xmm::xmm(Dim const Alloc) :
		mAllocated(Alloc), mOccupied(0)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
inline xmm::xmm(Dim const Alloc, Dim const Occupy) :
		mAllocated(Alloc), mOccupied(Occupy)
{
	WatchError
	if (Alloc < Occupy) mAllocated = Occupy;
	CatchError
}



/*!
	The duplicator.
*/
inline xmm::xmm(xmm const & that) : mm(that),
	mAllocated(that.mAllocated), mOccupied(that.mOccupied)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
inline xmm const & xmm::operator = (xmm const & that)
{
	WatchError
	if (this != &that)
	{
		mAllocated = that.mAllocated;
		mOccupied = that.mOccupied;
	}
	return *this;
	CatchError
}



/*!
	Return the threshold extent.
*/
inline Dim xmm::threshold() const
{
	WatchError
	return mAllocated;
	CatchError
}



/*!
	Return the logically allocated extent.
*/
inline Dim xmm::allocated() const
{
	WatchError
	return mAllocated;
	CatchError
}



/*!
	Return the actually acquired extent.
*/
inline Dim xmm::acquired() const
{
	WatchError
	return mAllocated;
	CatchError
}



/*!
	Return the extent occupied.
*/
inline Dim xmm::occupied() const
{
	WatchError
	return mOccupied;
	CatchError
}




/*!
	Return the extent unoccupied.
*/
inline Dim xmm::unoccupied() const
{
	WatchError
	return mAllocated - mOccupied;
	CatchError
}



/*!
	Return whether the number of occupied is empty.
*/
inline Bll xmm::emptyOccupied() const
{
	WatchError
	return !mOccupied;
	CatchError
}




/*!
	Return whether the number of occupied is non-empty.
*/
inline Bll xmm::existOccupied() const
{
	WatchError
	return mOccupied;
	CatchError
}



/*!
	Return whether alll allocated are occupied.
*/
inline Bll xmm::fullyOccupied() const
{
	WatchError
	return mOccupied == mAllocated;
	CatchError
}



/*!
	Whether the iterator is beyond the allocated range.
*/
inline Bll xmm::beyondAllocated(Itr const theItr) const
{
	WatchError
	return theItr >= mAllocated;
	CatchError
}



/*!
	Whether the iterator is beyond the occupied range.
*/
inline Bll xmm::beyondOccupied(Itr const theItr) const
{
	WatchError
	return theItr >= mOccupied;
	CatchError
}



/*!
	Whether the iterator is beyond the acquired range.
*/
inline Bll xmm::beyondAcquired(Itr const theItr) const
{
	WatchError
	return theItr >= mAllocated;
	CatchError
}



/*!
	Return whether automatic deallocation is needed.
*/
inline Bll xmm::needAutoDealloc() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return whether automatic reallocation is needed.
*/
inline Bll xmm::needAutoRealloc() const
{
	WatchError
	return mOccupied == mAllocated;
	CatchError
}




/*!
	Return whether automatic allocation adjustment is needed.
*/
inline Bll xmm::needAutoAdjust() const
{
	WatchError
	return mOccupied != mAllocated;
	CatchError
}



/*!
	Return whether is current allocation mismatches with the given extent.
*/
inline Bll xmm::mismatchAlloc(Dim const Alloc) const
{
	WatchError
	return Alloc != mAllocated;
	CatchError
}



/*!
	Return whether the current allocation is deficient for the given extent.
*/
inline Bll xmm::deficientAlloc(Dim const Occupy) const
{
	WatchError
	return Occupy > mAllocated;
	CatchError
}



/*!
	Reallocate the default extent.
*/
inline void xmm::reallocAuto()
{
	WatchError
	Warn(mOccupied != mAllocated, eMemoryAllocation);

	#if CheckError
	Dim tAllocated = mAllocated;
	#endif

	mAllocated <<= ReallocShift;
	++mAllocated;

	#if CheckError
	if (mAllocated < tAllocated)	// Overflow
		Throw(eMathOverflow);
	#endif

	CatchError
}




/*!
	Deallocate for the default extent.
*/
inline void xmm::deallocAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Allocate for the occupied extent, preserving occupied.
*/
inline void xmm::adjustAuto()
{
	WatchError
	Warn(mAllocated == mOccupied, eMemoryAllocation);

	mAllocated = mOccupied;
	CatchError
}



/*!
	Allocate for the given extent.
*/
inline void xmm::allocate(Dim const Alloc)
{
	WatchError
	Warn(Alloc <= mAllocated, eMemoryAllocation);
	Warn(Alloc < mOccupied, eInsuffMemoryAllocation);

	mAllocated = Alloc;
	CatchError
}



/*!
	Reset the occupied extents.
*/
inline void xmm::resetOccupy()
{
	WatchError
	if (mOccupied) mOccupied = 0;
	CatchError
}




/*!
	Reset the occupied extents and return whether successful.
*/
inline Bll xmm::resetOccupyBll()
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
inline void xmm::reoccupy()
{
	WatchError
	Warn(mOccupied == mAllocated, eAllocatedMemoryFull);

	++mOccupied;
	CatchError
}




/*!
	Unoccupy one extent.
*/
inline void xmm::unoccupy()
{
	WatchError
	Warn(!mOccupied, eOccupiedMemoryEmpty);

	--mOccupied;
	CatchError
}



/*!
	Reoccupy one extent.
*/
inline Itr xmm::reoccupyItr()
{
	WatchError
	Warn(mOccupied == mAllocated, eAllocatedMemoryFull);
	return mOccupied++;
	CatchError
}




/*!
	Unoccupy one extent.
*/
inline Itr xmm::unoccupyItr()
{
	WatchError
	Warn(!mOccupied, eOccupiedMemoryEmpty);

	return --mOccupied;
	CatchError
}



/*!
	Occupy given extent.
*/
inline void xmm::occupy(Dim const Occupy)
{
	WatchError
	Warn(Occupy > mAllocated, eInsuffMemoryAllocation);
	mOccupied = Occupy;
	CatchError
}



/*!
	Initialise memory manager.
*/
inline void xmm::reinitialise(Dim const Alloc, Dim const Occupy)
{
	WatchError
	mOccupied = Occupy;
	mAllocated = Alloc >= Occupy ? Alloc : Occupy;
	CatchError
}


closeEmuSpace



#endif // XmmHppIncluded
