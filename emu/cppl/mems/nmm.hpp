/*!
	@file nmm.hpp
	@brief The source file for fixed-allocation flexible-occupancy memory manager.
	@details This is the source file for fixed-allocation flexible-occupancy memory manager.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef NmmHppIncluded
#define NmmHppIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace


/*!
	@class nmm
	@brief A class to represent fixed-allocation flexible-occupancy memory manager.
	@details This class represents fixed-allocation flexible-occupancy memory manager.
*/
class nmm : public mm
{
	public:

		/*! @name Dimensions */
		//! @{

		Dim threshold() const;			//!< Minimum threshold extent.
		Dim allocated() const;			//!< Extent logical allocated.
		Dim acquired() const;			//!< Actually acquired extent.
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

		nmm();										//!< Constructor.
		~nmm();										//!< Destructor.
		nmm(Dim const Alloc);						//!< Initialiser.
		nmm(Dim const Alloc, Dim const Occupy);		//!< Initialiser.
		nmm(nmm const & that);						//!< Duplicator.
		nmm const & operator = (nmm const & that);	//!< Assigner.

	private:

		Dim mAllocated;		//!< Number of allocated.
		Dim mOccupied;		//!< Number of occupied.
};



/*!
	The constructor.
*/
inline nmm::nmm() : mAllocated(0), mOccupied(0)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
inline nmm::~nmm()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
inline nmm::nmm(Dim const Alloc) : mAllocated(Alloc), mOccupied(0)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
inline nmm::nmm(Dim const Alloc, Dim const Occupy) :
		mAllocated(Alloc), mOccupied(Occupy)
{
	WatchError
	if (Alloc < Occupy) mAllocated = Occupy;
	CatchError
}



/*!
	The duplicator.
*/
inline nmm::nmm(nmm const & that) : mm(that),
	mAllocated(that.mAllocated), mOccupied(that.mOccupied)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
inline nmm const & nmm::operator = (nmm const & that)
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
inline Dim nmm::threshold() const
{
	WatchError
	return mAllocated;
	CatchError
}



/*!
	Return the actually acquired extent.
*/
inline Dim nmm::acquired() const
{
	WatchError
	return mAllocated;
	CatchError
}



/*!
	Return the logically allocated extent.
*/
inline Dim nmm::allocated() const
{
	WatchError
	return mAllocated;
	CatchError
}



/*!
	Return the extent occupied.
*/
inline Dim nmm::occupied() const
{
	WatchError
	return mOccupied;
	CatchError
}




/*!
	Return the extent unoccupied.
*/
inline Dim nmm::unoccupied() const
{
	WatchError
	return mAllocated - mOccupied;
	CatchError
}



/*!
	Return whether the number of occupied is empty.
*/
inline Bll nmm::emptyOccupied() const
{
	WatchError
	return !mOccupied;
	CatchError
}




/*!
	Return whether the number of occupied is non-zero.
*/
inline Bll nmm::existOccupied() const
{
	WatchError
	return mOccupied;
	CatchError
}



/*!
	Return whether all allocated are occupied.
*/
inline Bll nmm::fullyOccupied() const
{
	WatchError
	return mOccupied == mAllocated;
	CatchError
}



/*!
	Whether the iterator is beyond the allocated range.
*/
inline Bll nmm::beyondAllocated(Itr const theItr) const
{
	WatchError
	return theItr >= mAllocated;
	CatchError
}



/*!
	Whether the iterator is beyond the occupied range.
*/
inline Bll nmm::beyondOccupied(Itr const theItr) const
{
	WatchError
	return theItr >= mOccupied;
	CatchError
}



/*!
	Whether the iterator is beyond the acquired range.
*/
inline Bll nmm::beyondAcquired(Itr const theItr) const
{
	WatchError
	return theItr >= mAllocated;
	CatchError
}



/*!
	Return whether automatic deallocation is needed.
*/
inline Bll nmm::needAutoDealloc() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return whether automatic reallocation is needed.
*/
inline Bll nmm::needAutoRealloc() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return whether automatic memory adjustment is needed.
*/
inline Bll nmm::needAutoAdjust() const
{
	WatchError
	return false;
	CatchError
}



/*!
	Return whether current allocation mismatches with given extent.
*/
inline Bll nmm::mismatchAlloc(Dim const Alloc) const
{
	WatchError
	return Alloc != mAllocated;
	CatchError
}



/*!
	Return whether current allocation is deficient for the given extent.
*/
inline Bll nmm::deficientAlloc(Dim const Occupy) const
{
	WatchError
	return Occupy > mAllocated;
	CatchError
}



/*!
	Reallocate for the default extent.
*/
inline void nmm::reallocAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Deallocate for the default extent.
*/
inline void nmm::deallocAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Adjust allocation with the occupied extent.
*/
inline void nmm::adjustAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Allocate for the given extent.
*/
inline void nmm::allocate(Dim const Alloc)
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Reset the occupied extents.
*/
inline void nmm::resetOccupy()
{
	WatchError
	if (mOccupied) mOccupied = 0;
	CatchError
}




/*!
	Reset the occupied extents and return whether successful.
*/
inline Bll nmm::resetOccupyBll()
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
inline void nmm::reoccupy()
{
	WatchError
	Warn(mOccupied == mAllocated, eAllocatedMemoryFull);

	++mOccupied;
	CatchError
}




/*!
	Unoccupy one extent.
*/
inline void nmm::unoccupy()
{
	WatchError
	Warn(!mOccupied, eOccupiedMemoryEmpty);

	--mOccupied;
	CatchError
}



/*!
	Reoccupy one extent.
*/
inline Itr nmm::reoccupyItr()
{
	WatchError
	Warn(mOccupied == mAllocated, eAllocatedMemoryFull);
	return mOccupied++;
	CatchError
}



/*!
	Unoccupy one extent.
*/
inline Itr nmm::unoccupyItr()
{
	WatchError
	Warn(!mOccupied, eOccupiedMemoryEmpty);

	return --mOccupied;
	CatchError
}



/*!
	Occupy given extent.
*/
inline void nmm::occupy(Dim const Occupy)
{
	WatchError
	Warn(Occupy > mAllocated, eInsuffMemoryAllocation);
	mOccupied = Occupy;
	CatchError
}



/*!
	Initialise memory manager.
*/
inline void nmm::reinitialise(Dim const Alloc, Dim const Occupy)
{
	WatchError
	mOccupied = Occupy;
	mAllocated = Alloc >= Occupy ? Alloc : Occupy;
	CatchError
}


closeEmuSpace



#endif // NmmHppIncluded
