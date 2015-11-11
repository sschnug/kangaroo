/*!
	@file mm.hpp
	@brief The source file for memory manager class.
	@details This is the source file for memory manager class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef MmHppIncluded
#define MmHppIncluded



#include "cppl/roots/typ.hpp"
#include "cppl/roots/err.hpp"



openEmuSpace


/*!
	@class mm
	@brief A class to represent memory manager.
	@details This class represents memory manager.
*/
class mm
{
	public:

		/*! @name Dimensions */
		//! @{

		virtual Dim threshold() const = 0;	//!< Minimum threshold extent. Allocation never falls below this.
		virtual Dim allocated() const = 0;	//!< Extent logically allocated. Occupied extent cannot exceed this.
		virtual Dim acquired() const = 0;	//!< Actually acquired extent, meaningful when sentinel or loading factor.
		virtual Dim occupied() const = 0;	//!< Number of occupied extent. This cannot exceed allocated extent.
		virtual Dim unoccupied() const = 0;	//!< Number of unoccupied extent. This is allocated minus occupied.

		//! @}

		/*! @name States */
		//! @{

		virtual Bll emptyOccupied() const = 0;	//!< Whether the number of occupied is empty.
		virtual Bll existOccupied() const = 0;	//!< Whether the number of occupied non-zero.
		virtual Bll fullyOccupied() const = 0;	//!< Whether all allocated are fully occupied.

		//! @}

		/*! @name Iterators */
		//! @{

		virtual Bll beyondAllocated(Itr const theItr) const = 0;	//!< Whether the iterator is beyond the allocated range.
		virtual Bll beyondOccupied(Itr const theItr) const = 0;		//!< Whether the iterator is beyond the occupied range.
		virtual Bll beyondAcquired(Itr const theItr) const = 0;		//!< Whether the iterator is beyond the acquired range.

		//! @}

		/*! @name Checkings */
		//! @{

		virtual Bll needAutoDealloc() const = 0;				//!< Whether automatic deallocation is needed.
		virtual Bll needAutoRealloc() const = 0;				//!< Whether automatic reallocation is needed.
		virtual Bll needAutoAdjust() const = 0;					//!< Whether automatic memory adjustment is needed.
		virtual Bll mismatchAlloc(Dim const Alloc) const = 0;	//!< Whether current allocation mismatches with the given extent.
		virtual Bll deficientAlloc(Dim const Occupy) const = 0;	//!< Whether current allocation is deficient for given extent.

		//! @}

		/*! @name Operations */
		//! @{

		virtual void reallocAuto() = 0;				//!< Reallocate default extent of memory.
		virtual void deallocAuto() = 0;				//!< Deallocate default extent of memory.
		virtual void adjustAuto() = 0;				//!< Adjust allocation with occupied extent.
		virtual void allocate(Dim const Alloc) = 0;	//!< Allocate memory preserving the occupied.

		//! @}

		/*! @name Occupancy */
		//! @{

		virtual void resetOccupy() = 0;				//!< Reset occupied extents.
		virtual Bll resetOccupyBll() =0;			//!< Reset occupied extents and return whether successful.
		virtual void reoccupy() = 0;				//!< Reoccupy one extent.
		virtual void unoccupy() = 0;				//!< Unoccupy one extent.
		virtual Itr reoccupyItr() = 0;				//!< Reoccupy one extent and return the iterator.
		virtual Itr unoccupyItr() = 0;				//!< Unoccupy one extent and return the iterator.
		virtual void occupy(Dim const Occupy) = 0;	//!< Occupy given extent

		//! @}

		/*! @name Reinitialisation */
		//! @{

		virtual void reinitialise(Dim const Alloc, Dim const Occupy) = 0;//!< Reinitialise memory manager.

		//! @}

	protected:

		mm();										//!< Constructor.
		virtual ~mm() = 0;							//!< Destructor.
		mm(mm const & that);						//!< Duplicator.
		mm const & operator = (mm const & that);	//!< Assigner.
};



/*!
	The constructor.
*/
inline mm::mm()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
inline mm::~mm()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
inline mm::mm(mm const & that)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
inline mm const & mm::operator = (mm const & that)
{
	WatchError
	return *this;
	CatchError
}




closeEmuSpace



#endif // MmHppIncluded
