/*!
	@file kmm.hpp
	@brief The source file for constant memory manager class.
	@details This is the source file for constant memory manager class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef KmmHppIncluded
#define KmmHppIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace


/*!
	@class kmm
	@brief A class to represent constant memory manager.
	@details This class represents constant memory manager.
		Allocation is fixed and occupancy is fixed. For a
		better interfac edescription see the superclass.
*/
class kmm : public mm
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

		kmm();											//!< Constructor.
		~kmm();											//!< Destructor.
		kmm(Dim const Occupy);							//!< Initialiser.
		kmm(kmm const & that);							//!< Duplicator.
		kmm const & operator = (kmm const & that);		//!< Assigner.

	private:

		Dim mOccupied;									//!< Number of occupied.
};



/*!
	The constructor.
*/
inline kmm::kmm() : mOccupied(0)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
inline kmm::~kmm()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
inline kmm::kmm(Dim const Occupy) : mOccupied(Occupy)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
inline kmm::kmm(kmm const & that) :
	mm(that), mOccupied(that.mOccupied)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
inline kmm const & kmm::operator = (kmm const & that)
{
	WatchError
	if (this != &that)
		mOccupied = that.mOccupied;
	return *this;
	CatchError
}



/*!
	Return the threshold extent.
*/
inline Dim kmm::threshold() const
{
	WatchError
	return mOccupied;
	CatchError
}



/*!
	Return the logically allocated extent.
*/
inline Dim kmm::allocated() const
{
	WatchError
	return mOccupied;
	CatchError
}



/*!
	Return the actually acquired extent.
*/
inline Dim kmm::acquired() const
{
	WatchError
	return mOccupied;
	CatchError
}



/*!
	Return the extent occupied.
*/
inline Dim kmm::occupied() const
{
	WatchError
	return mOccupied;
	CatchError
}




/*!
	Return the extent unoccupied.
*/
inline Dim kmm::unoccupied() const
{
	WatchError
	return 0;
	CatchError
}



/*!
	Return whether the number of occupied is empty.
*/
inline Bll kmm::emptyOccupied() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return whether the number of occupied is non-zero.
*/
inline Bll kmm::existOccupied() const
{
	WatchError
	return mOccupied;
	CatchError
}




/*!
	Return whether all allocated are fully occupied.
*/
inline Bll kmm::fullyOccupied() const
{
	WatchError
	return true;
	CatchError
}


/*!
	Whether the iterator is beyond the allocated range.
*/
inline Bll kmm::beyondAllocated(Itr const theItr) const
{
	WatchError
	return theItr >= mOccupied;
	CatchError
}



/*!
	Whether the iterator is beyond the occupied range.
*/
inline Bll kmm::beyondOccupied(Itr const theItr) const
{
	WatchError
	return theItr >= mOccupied;
	CatchError
}



/*!
	Whether the iterator is beyond the acquired range.
*/
inline Bll kmm::beyondAcquired(Itr const theItr) const
{
	WatchError
	return theItr >= mOccupied;
	CatchError
}



/*!
	Return whether automatic deallocation is needed.
*/
inline Bll kmm::needAutoDealloc() const
{
	WatchError
	return false;
	CatchError
}



/*!
	Return whether automatic reallocation is needed.
*/
inline Bll kmm::needAutoRealloc() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return whether automatic memory adjustment is needed.
*/
inline Bll kmm::needAutoAdjust() const
{
	WatchError
	return false;
	CatchError
}




/*!
	Return current allocation mismatches with the given extent.
*/
inline Bll kmm::mismatchAlloc(Dim const Alloc) const
{
	WatchError
	return Alloc != mOccupied;
	CatchError
}



/*!
	Return whether current allocation is deficient for the given extent.
*/
inline Bll kmm::deficientAlloc(Dim const Occupy) const
{
	WatchError
	return Occupy > mOccupied;
	CatchError
}



/*!
	Reallocate for the default extent.
*/
inline void kmm::reallocAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Deallocate for the default extent.
*/
inline void kmm::deallocAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Allocate for the default extent.
*/
inline void kmm::adjustAuto()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Allocate for the given extent.
*/
inline void kmm::allocate(Dim const Alloc)
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Reset the occupied extents.
*/
inline void kmm::resetOccupy()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}




/*!
	Reset the occupied extents and return whether successful.
*/
inline Bll kmm::resetOccupyBll()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}



/*!
	Reoccupy one extent.
*/
inline void kmm::reoccupy()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}




/*!
	Unoccupy one extent.
*/
inline void kmm::unoccupy()
{
	WatchError
	Throw(eUndefMemoryOperation);
	CatchError
}




/*!
	Reoccupy one extent.
*/
inline Itr kmm::reoccupyItr()
{
	WatchError
	Throw(eUndefMemoryOperation);
	return InvItr;
	CatchError
}




/*!
	Unoccupy one extent.
*/
inline Itr kmm::unoccupyItr()
{
	WatchError
	Throw(eUndefMemoryOperation);
	return InvItr;
	CatchError
}



/*!
	Occupy given extent.
*/
inline void kmm::occupy(Dim const Occupy)
{
	WatchError
	Warn(Occupy != mOccupied, eDimensionMismatch);
	CatchError
}





/*!
	Initialise memory manager.
*/
inline void kmm::reinitialise(Dim const Alloc, Dim const Occupy)
{
	WatchError
	mOccupied = Occupy;
	Warn(Alloc != Occupy, eDimensionMismatch);
	CatchError
}


closeEmuSpace



#endif // KmmHppIncluded
