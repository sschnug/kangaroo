/*!
	@file clusterl.tcc
	@brief The source file for clusterl template class.
	@details This is the source file for clusterl template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef ClusterlTccIncluded
#define ClusterlTccIncluded




#include "cppl/roots/idx.hpp"




openEmuSpace



/*!
	@class clusterl
	@brief A class to represent cluster of given serials
		representing clusters as *loops*.
	@details This class represents cluster of given serials.
			A serial is in its own cluster or in other's.
			The members in a cluster form a *loop* that can be
			traversed using predecessor and successor methods.
*/
template <typename srl, typename mm>
class clusterl
{
	public:

		typedef mm MmTyp;							//!< Memory manager type.

		clusterl();									//!< Constructor.
		clusterl(mm const & theMm);					//!< Initialiser.
		clusterl(clusterl<srl,mm> const & that);	//!< Duplicator.
		clusterl<srl,mm> const & operator =
					(clusterl<srl,mm> const & that);//!< Assigner.
		~clusterl();								//!< Destructor.

		//! @name Synchronise
		//! @{

		void syncClk();								//!< Synchronise clock.

		//! @}
		//! @name Clear
		//! @{

		void clear();								//!< Clear serials, retaining available memory.
		void clearMem();							//!< Clear serials, releasing memory when deemed.

		//! @}

		//! @name Memory
		//! @{

		Dim serialCount() const;					//!< Get the serial count.
		mm const & MemMan() const;					//!< Memory manager.

		void reallocMemAuto();						//!< Reallocate memory automatically.
		void deallocMemAuto();						//!< Deallocate memory automatically.
		void adjustMemAuto();						//!< Adjust memory automatically.
		void allocateMem(Dim const Alloc);			//!< Allocate given extent of memory.

		//! @}

		//! @name Insert
		//! @{

		void insert();								//!< Insert a serial at the end, assuming memory available.
		srl insertSrl();							//!< Insert a serial at the end and return the serial, assuming memory available.
		void insertMem();							//!< Insert a serial at the end, acquiring memory when needed.
		srl insertSrlMem();							//!< Insert a serial at the end and return the serial, acquiring memory available.

		//! @}

		//! @name Remove
		//! @{

		void remove();								//!< Remove the last serial, retaining available memory.
		void removeMem();							//!< Remove the last serial, releasing memroy when deemed.

		//! @}

		/*! @name Operations */
		//! @{

		void reinitialise();									//!< Reinitialise the clusterl into singletons.
		void alter(srl const Source, srl const Destination);	//!< Alter the clusterl of a given serial.

		//! @}
		/*! @name Accessors */
		//! @{

		srl successor(srl const theSrl) const;				//!< The successor.
		srl predecessor(srl const theSrl) const;			//!< The predecessor.

		//!@}

	private:
		mm    mMemMan;		//!< Memory manager.
		srl *  mSuccs;		//!< The successors.
		srl *  mPreds;		//!< The predecessors.
};



/*!
	@def cl
	@brief A macro to denote clusterl.
	@details This macro denotes clusterl.
*/
#define cl clusterl



/*!
	The constructor.
*/
template<typename srl, typename mm>
clusterl<srl,mm>::clusterl()
{
	WatchError

	mSuccs = new srl [mMemMan.acquired()];
	mPreds = new srl [mMemMan.acquired()];

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mSuccs[tSrl] = mPreds[tSrl] = tSrl;

	CatchError
}



/*!
	The initialiser.
*/
template<typename srl, typename mm>
clusterl<srl,mm>::clusterl(mm const & theMm) : mMemMan(theMm)
{
	WatchError

	mSuccs = new srl [mMemMan.acquired()];
	mPreds = new srl [mMemMan.acquired()];

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mSuccs[tSrl] = mPreds[tSrl] = tSrl;

	CatchError
}



/*!
	The duplicator.
*/
template <typename srl, typename mm>
clusterl<srl,mm>::clusterl(clusterl<srl,mm> const & that) : mMemMan(that.mMemMan)
{
	WatchError

	mSuccs = new srl [mMemMan.acquired()];
	mPreds = new srl [mMemMan.acquired()];

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
	{
		mSuccs[tSrl] = that.mSuccs[tSrl];
		mPreds[tSrl] = that.mPreds[tSrl];
	}

	CatchError
}



/*!
	The destructor.
*/
template <typename srl, typename mm>
clusterl<srl,mm>::~clusterl()
{
	WatchError

	delete [] mSuccs;
	delete [] mPreds;

	CatchError
}



/*!
	The assigner.
*/
template <typename srl, typename mm>
clusterl<srl,mm> const & clusterl<srl,mm>::operator =
			(clusterl<srl,mm> const & that)
{
	WatchError

	if (&that == this)
		return *this;

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		delete [] mSuccs;
		delete [] mPreds;

		mSuccs = new srl [that.mMemMan.acquired()];
		mPreds = new srl [that.mMemMan.acquired()];
	}

	mMemMan = that.mMemMan;

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
	{
		mSuccs[tSrl] = that.mSuccs[tSrl];
		mPreds[tSrl] = that.mPreds[tSrl];
	}

	return *this;

	CatchError
}



/*!
	Synchronise clock.
*/
template <typename srl, typename mm>
inline void clusterl<srl,mm>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}



/*!
	Clear serials, retaining available memory.
*/
template<typename srl, typename mm>
inline void clusterl<srl,mm>::clear()
{
	WatchError

	mMemMan.resetOccupy();

	CatchError
}



/*!
	Clear serials, releasing memory when deemed.
*/
template<typename srl, typename mm>
inline void clusterl<srl,mm>::clearMem()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}

	CatchError
}



/*!
	Insert a serial at the end, assuming memory available.
*/
template <typename srl, typename mm>
inline void clusterl<srl,mm>::insert()
{
	WatchError

	srl const tSrl = mMemMan.reoccupyItr();
	mSuccs[tSrl] = mPreds[tSrl] = tSrl;

	CatchError
}




/*!
	Insert a serial at the end and return the serial, assuming memory available.
*/
template <typename srl, typename mm>
inline srl clusterl<srl,mm>::insertSrl()
{
	WatchError

	srl const tSrl = mMemMan.reoccupyItr();
	mSuccs[tSrl] = mPreds[tSrl] = tSrl;
	return tSrl;

	CatchError
}



/*!
	Insert a serial at the end, acquiring memory when deemed.
*/
template <typename srl, typename mm>
inline void clusterl<srl,mm>::insertMem()
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	srl const tSrl = mMemMan.reoccupyItr();
	mSuccs[tSrl] = mPreds[tSrl] = tSrl;

	CatchError
}




/*!
	Insert a serial at the end and return the iterator, acquiring memory when deemed.
*/
template <typename srl, typename mm>
inline srl clusterl<srl,mm>::insertSrlMem()
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	srl const tSrl = mMemMan.reoccupyItr();
	mSuccs[tSrl] = mPreds[tSrl] = tSrl;
	return tSrl;

	CatchError
}



/*!
	Remove the last serial, retaining available memory.
*/
template <typename srl, typename mm>
inline void clusterl<srl,mm>::remove()
{
	WatchError

	Itr tItr = mMemMan.unoccupyItr();

	srl const tPred = mPreds[tItr];
	srl const tSucc = mSuccs[tItr];

	if (mMemMan.occupied() != tSucc
			|| mMemMan.occupied() != tPred)
	{
		mPreds[tSucc] = tPred;
		mSuccs[tPred] = tSucc;
	}

	CatchError
}



/*!
	Remove the last serial, release memory whenever deemed.
*/
template <typename srl, typename mm>
inline void clusterl<srl,mm>::removeMem()
{
	WatchError

	Itr tItr = mMemMan.unoccupyItr();

	srl const tPred = mPreds[tItr];
	srl const tSucc = mSuccs[tItr];

	if (mMemMan.occupied() != tSucc
			|| mMemMan.occupied() != tPred)
	{
		mPreds[tSucc] = tPred;
		mSuccs[tPred] = tSucc;
	}

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}




/*!
	Reinitialise the clusterl. Each serial has its own clusterl.
*/
template <typename srl, typename mm>
inline void clusterl<srl,mm>::reinitialise()
{
	WatchError

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mSuccs[tSrl] = mPreds[tSrl] = tSrl;

	CatchError
}



/*!
	Alter at the given srl. The source srl joins the clusterl of the destination srl.
*/
template <typename srl, typename mm>
inline 	void clusterl<srl,mm>::alter(srl const Source, srl const Destination)

{
	WatchError

	Warn(mMemMan.beyondOccupied(Source), eSerialBeyondLimit);
	Warn(mMemMan.beyondOccupied(Destination), eSerialBeyondLimit);

	srl & tPred = mPreds[Source];
	srl & tSucc = mSuccs[Source];

	if (Source != tSucc || Source != tPred)
	{
		mSuccs[tPred] = tSucc;
		mPreds[tSucc] = tPred;
	}

	if (Source == Destination)
		tPred = tSucc = Destination;
	else
	{
		tPred = Destination;
		tSucc = mSuccs[Destination];
		mSuccs[tPred] = Source;
		mPreds[tSucc] = Source;
	}

	CatchError
}



/*!
	Reallocate more memory automatically.
*/
template<typename srl, typename mm>
void clusterl<srl,mm>::reallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);

	mMemMan.reallocAuto();

	srl * const tSuccs = mSuccs;
	srl * const tPreds = mPreds;

	mSuccs = new srl [mMemMan.acquired()];
	mPreds = new srl [mMemMan.acquired()];

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
	{
		mSuccs[tSrl] = tSuccs[tSrl];
		mPreds[tSrl] = tPreds[tSrl];
	}
	delete [] tSuccs;
	delete [] tPreds;

	CatchError
}



/*!
	Deallocate some memory automatically.
*/
template<typename srl, typename mm>
void clusterl<srl,mm>::deallocMemAuto()
{
	WatchError
	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);

	mMemMan.deallocAuto();

	srl * const tSuccs = mSuccs;
	srl * const tPreds = mPreds;

	mSuccs = new srl [mMemMan.acquired()];
	mPreds = new srl [mMemMan.acquired()];

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
	{
		mSuccs[tSrl] = tSuccs[tSrl];
		mPreds[tSrl] = tPreds[tSrl];
	}
	delete [] tSuccs;
	delete [] tPreds;

	CatchError
}


/*!
	Adjust memory automatically.
*/
template<typename srl, typename mm>
void clusterl<srl,mm>::adjustMemAuto()
{
	WatchError
	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);

	mMemMan.adjustAuto();

	srl * const tSuccs = mSuccs;
	srl * const tPreds = mPreds;

	mSuccs = new srl [mMemMan.acquired()];
	mPreds = new srl [mMemMan.acquired()];

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
	{
		mSuccs[tSrl] = tSuccs[tSrl];
		mPreds[tSrl] = tPreds[tSrl];
	}
	delete [] tSuccs;
	delete [] tPreds;

	CatchError
}




/*!
	Allocate memory.
*/
template<typename srl, typename mm>
void clusterl<srl,mm>::allocateMem(Dim const Alloc)
{
	WatchError
	Warn(!mMemMan.mismatchAlloc(Alloc), eDimensionMismatch);

	mMemMan.allocate(Alloc);

	srl * const tSuccs = mSuccs;
	srl * const tPreds = mPreds;

	mSuccs = new srl [mMemMan.acquired()];
	mPreds = new srl [mMemMan.acquired()];

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
	{
		mSuccs[tSrl] = tSuccs[tSrl];
		mPreds[tSrl] = tPreds[tSrl];
	}
	delete [] tSuccs;
	delete [] tPreds;

	CatchError
}



/*!
	Return the serial count.
*/
template <typename srl, typename mm>
inline Dim clusterl<srl,mm>::serialCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the memory manager.
*/
template <typename srl, typename mm>
inline mm const & clusterl<srl,mm>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Return successor.
*/
template <typename srl, typename mm>
inline srl clusterl<srl,mm>::successor(srl const theSrl) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	return mSuccs[theSrl];

	CatchError
}



/*!
	Return predecessor.
*/
template <typename srl, typename mm>
inline srl clusterl<srl,mm>::predecessor(srl const theSrl) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	return mPreds[theSrl];

	CatchError
}



closeEmuSpace


#endif // ClusterlTccIncluded
