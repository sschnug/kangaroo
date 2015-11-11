/*!
	@file kmmm.hpp
	@brief The source file for constant memory manager class maintaining a margin, best suited for queues and texts.
	@details This is the source file for constant memory manager class maintaining a margin, best suited for queues and texts.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef KmmmHppIncluded
#define KmmmHppIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace


/*!
	@class kmmm
	@brief A class to represent constant memory manager
		maintaining a margin, best suited for queues and texts.
	@details This class represents constant memory manager
		maintaining a margin, best suited for queues and texts.
		Allocation is fixed and occupancy is fixed. For a
		better interface description see the superclass.
*/
class kmmm : public mm
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
		void allocate(Dim const Alloc);				//!< Allocate memory preserving the occupied.

		//! @}

		/*! @name Occupancy */
		//! @{

		void resetOccupy();						//!< Reset occupied extents.
		Bll resetOccupyBll();					//!< Reset occupied extents and return whether successful.
		void reoccupy();						//!< Reoccupy one extent.
		void unoccupy();						//!< Unoccupy one extent.
		Itr reoccupyItr();						//!< Reoccupy one extent and return the iterator.
		Itr unoccupyItr();						//!< Unoccupy one extent and return the iterator.
		void occupy(Dim const Occupy);			//!< Occupy given extent

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

		kmmm();											//!< Constructor.
		~kmmm();										//!< Destructor.
		kmmm(Dim const Occupy);							//!< Initialiser.
		kmmm(kmmm const & that);						//!< Duplicator.
		kmmm const & operator = (kmmm const & that);	//!< Assigner.

	private:

		Dim mAcquired;									//!< Number of acquired.
		Dim mOccupied;									//!< Number of occupied.
};



/*!
	The constructor.
*/
inline kmmm::kmmm() : mAcquired(LoadMargin), mOccupied(0)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
inline kmmm::~kmmm()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
inline kmmm::kmmm(Dim const Occupy) :
	mAcquired(Occupy + LoadMargin), mOccupied(Occupy)
{
	WatchError
	Warn(mAllocated > mAcquired, eMathOverflow);
	CatchError
}



/*!
	The duplicator.
*/
inline kmmm::kmmm(kmmm const & that) :
	mm(that), mAcquired(that.mAcquired), mOccupied(that.mOccupied)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
inline kmmm const & kmmm::operator = (kmmm const & that)
{
	WatchError
	if (this != &that)
	{
		mAcquried = that.mAcquired;
		mOccupied = that.mOccupied;
	}
	return *this;
	CatchError
}



/*!
	Return the threshold extent.
*/
inline Dim kmmm::threshold() const
{
	WatchError
	return mAcquired;
	CatchError
}



/*!
	Return the logically allocated extent.
*/
inline Dim kmmm::allocated() const
{
	WatchError
	return mOccupied;
	CatchError
}



/*!
	Return the actually acquired extent.
*/
inline Dim kmmm::acquired() const
{
	WatchError
	return mAcquired;
	CatchError
}



/*!
	Return the extent occupied.
*/
inline Dim kmmm::occupied() const
{
	WatchError
	return mOccupied;
	CatchError
}




/*!
	Return the extent unoccupied.
*/
inline Dim kmmm::unoccupied() const
{
	WatchError
	return 0;
	CatchError
}



/*!
	Return whether the number of occupied is empty.
*/
inline Bll kmmm::emptyOccupied() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return whether the number of occupied is non-zero.
*/
inline Bll kmmm::existOccupied() const
{
	WatchError
	return mOccupied;
	CatchError
}




/*!
	Return whether all allocated are fully occupied.
*/
inline Bll kmmm::fullyOccupied() const
{
	WatchError
	return true;
	CatchError
}


/*!
	Whether the iterator is beyond the allocated range.
*/
inline Bll kmmm::beyondAllocated(Itr const theItr) const
{
	WatchError
	return theItr >= mOccupied;
	CatchError
}



/*!
	Whether the iterator is beyond the occupied range.
*/
inline Bll kmmm::beyondOccupied(Itr const theItr) const
{
	WatchError
	return theItr >= mOccupied;
	CatchError
}



/*!
	Whether the iterator is beyond the acquired range.
*/
inline Bll kmmm::beyondAcquired(Itr const theItr) const
{
	WatchError
	return theItr >= mAcquired;
	CatchError
}



/*!
	Return whether automatic deallocation is needed.
*/
inline Bll kmmm::needAutoDealloc() const
{
	WatchError
	return false;
	CatchError
}



/*!
	Return whether automatic reallocation is needed.
*/
inline Bll kmmm::needAutoRealloc() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return whether automatic memory adjustment is needed.
*/
inline Bll kmmm::needAutoAdjust() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return current allocation mismatches with the given extent.
*/
inline Bll kmmm::mismatchAlloc(Dim const Alloc) const
{
	WatchError
	return Alloc != mOccupied;
	CatchError
}



/*!
	Return whether current allocation is deficient for the given extent.
*/
inline Bll kmmm::deficientAlloc(Dim const Occupy) const
{
	WatchError
	return Occupy > mOccupied;
	CatchError
}



/*!
	Reallocate for the default extent.
*/
inline void kmmm::reallocAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Deallocate for the default extent.
*/
inline void kmmm::deallocAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Allocate for the default extent.
*/
inline void kmmm::adjustAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Allocate for the given extent.
*/
inline void kmmm::allocate(Dim const Alloc)
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Reset the occupied extents.
*/
inline void kmmm::resetOccupy()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}




/*!
	Reset the occupied extents and return whether successful.
*/
inline Bll kmmm::resetOccupyBll()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Reoccupy one extent.
*/
inline void kmmm::reoccupy()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}




/*!
	Unoccupy one extent.
*/
inline void kmmm::unoccupy()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}




/*!
	Reoccupy one extent.
*/
inline Itr kmmm::reoccupyItr()
{
	WatchError
	Throw(eUndefMemoryOperation);
	return InvItr;
	CatchError
}




/*!
	Unoccupy one extent.
*/
inline Itr kmmm::unoccupyItr()
{
	WatchError
	Throw(eUndefMemoryOperation);
	return InvItr;
	CatchError
}



/*!
	Occupy given extent.
*/
inline void kmmm::occupy(Dim const Occupy)
{
	WatchError
	Warn(Occupy != mOccupied, eDimensionMismatch);
	CatchError
}





/*!
	Initialise memory manager.
*/
inline void kmmm::reinitialise(Dim const Alloc, Dim const Occupy)
{
	WatchError
	mOccupied = Occupy;
	Warn(Alloc != Occupy, eDimensionMismatch);

	mAcquired = mAllocated + LoadMargin;
	Warn(mAllocated > mAcquired, eMathOverflow);

	CatchError
}


closeEmuSpace



#endif // KmmmHppIncluded
