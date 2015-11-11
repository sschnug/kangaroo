/*!
	@file labell.tcc
	@brief The source file for labell template class.
	@details This is the source file for labell template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef LabellTccIncluded
#define LabellTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class labell
	@brief A class to represent labels with *list* of tagged serials.
	@details This class represents labels with *list* of tagged serials.
		A label is a time-stamp. When time-stamp of a slot matches
		with the global time-stamp of the label, the slot is assumed
		to be tagged with a label.
*/
template <typename srl, typename mm>
class labell
{
	public:

		typedef mm MmTyp;								//!< Memory manager type.

		labell();										//!< Constructor.
		~labell();										//!< Destructor.
		labell(mm const & theMm);						//!< Initialiser.
		labell(labell<srl,mm> const & that);			//!< Duplicator.
		labell<srl,mm> const & operator =
					(labell<srl,mm> const & that);		//!< Assigner.

		//! @name Synchronise
		//! @{

		void syncClk();							//!< Synchronise clock.

		//! @}

		//! @name Clear
		//! @{

		void clear();								//!< Clear serials, retaining available memory.
		void clearMem();							//!< Clear serials, releasing memory when deemed.

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
		//! @name Memory
		//! @{

		Dim serialCount() const;					//!< Get serial count.
		mm const & MemMan() const;					//!< Memory manager.

		void reallocMemAuto();						//!< Reallocate memory automatically.
		void deallocMemAuto();						//!< Deallocate memory automatically.
		void adjustMemAuto();						//!< Adjust memory automatically.
		void allocateMem(Dim const Alloc);			//!< Allocate given extent of memory.

		//! @}

		/*! @name Operations */
		//! @{

		void sweep();									//!< Sweep tags optionally, only when required.
		void sweepMust();								//!< Sweep tags mandatorily, with a new clock.
		void sweep(Clk const theClk);					//!< Sweep tags optionally, only when requied.
		void sweepMust(Clk const theClk);				//!< Sweep tags mandatorily, with a new clock.

		void tag(srl const theSrl);							//!< Tag the serial, assuming untagged.
		Bll tagBll(srl const theSrl);						//!< Tag the serial when not tagged and return whether successful.

		void doUntagTag(Itr const theItr, srl const theSrl);	//!< Untag the first and tag the second, assuming they are not already so.
		Bll doUntagTagBll(Itr const theItr, srl const theSrl);	//!< Untag the first and tag the second, return whether successful.

		//! @}
		/*! @name Accessors */
		//! @{

		Dim tagCount() const;					//!< The number of current tags.
		Bll tagged(srl const theSrl) const;		//!< Whether the serial is tagged?
		Bll operator()(srl const theSrl) const;	//!< Whether the serial is tagged?
		srl operator[](Itr const theItr) const;	//!< Get the tagged serial.
		srl serial(Itr const theItr) const;		//!< Get the tagged serial.
		Clk clock(srl const theSrl) const;		//!< Get the clock of a serial.
		Clk clock() const;						//!< Get the clock of the label.

		//!@}

	private:
		mm    mMemMan;				//!< Memory manager.
		Dim	   mTagCount;			//!< Tagged serial count.
		Clk    mClk;				//!< Current clock.
		srl *  mSrls;				//!< Tagged serials.
		Clk *  mClks;				//!< Tag clocks.
};



/*!
	@def ll
	@brief A macro to denote labell.
	@details This macro denotes labell.
*/
#define ll labell



/*!
	The constructor.
*/
template<typename srl, typename mm>
inline labell<srl,mm>::labell() :
		mTagCount(0), mClk(NotClk)
{
	WatchError
	mSrls = new srl [mMemMan.acquired()];
	mClks = new Clk [mMemMan.acquired()];
	for (srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = EndClk;
	CatchError
}



/*!
	The initialiser.
*/
template<typename srl, typename mm>
inline labell<srl,mm>::labell(mm const & theMm) :
		mMemMan(theMm), mTagCount(0), mClk(NotClk)
{
	WatchError
	mSrls = new srl [mMemMan.acquired()];
	mClks = new Clk [mMemMan.acquired()];
	for (srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = EndClk;
	CatchError
}



/*!
	The duplicator.
*/
template <typename srl, typename mm>
labell<srl,mm>::labell(labell<srl,mm> const & that) :
		mMemMan(that.mMemMan), mTagCount(that.mTagCount), mClk(that.mClk)
{
	WatchError
	mSrls = new srl [mMemMan.acquired()];
	mClks = new Clk [mMemMan.acquired()];

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = that.mClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
		mSrls[tItr] = that.mSrls[tItr];
	CatchError
}



/*!
	The destructor.
*/
template <typename srl, typename mm>
inline labell<srl,mm>::~labell()
{
	WatchError
	delete [] mSrls;
	delete [] mClks;
	CatchError
}



/*!
	The assigner.
*/
template <typename srl, typename mm>
labell<srl,mm> const & labell<srl,mm>::operator =
		(labell<srl,mm> const & that)
{
	WatchError
	if (&that == this)
		return *this;

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		delete [] mSrls;
		delete [] mClks;

		mSrls = new srl [that.mMemMan.acquired()];
		mClks = new Clk [that.mMemMan.acquired()];
	}

	mMemMan = that.mMemMan;
	mTagCount = that.mTagCount;
	mClk = that.mClk;

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = that.mClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
		mSrls[tItr] = that.mSrls[tItr];

	return *this;
	CatchError
}



/*!
	Synchronize the clock.
*/
template<typename srl, typename mm>
void labell<srl,mm>::syncClk()
{
	WatchError
	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = (mClks[tSrl] == mClk) ? NotClk : EndClk;
	mClk = NotClk;
	CatchError
}



/*!
	Clear serials, retaining available memory.
*/
template<typename srl, typename mm>
inline void labell<srl,mm>::clear()
{
	WatchError

	if (mMemMan.resetOccupyBll())
		mTagCount = 0;

	CatchError
}




/*!
	Clear serials, releasing memory when deemed.
*/
template<typename srl, typename mm>
inline void labell<srl,mm>::clearMem()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		mTagCount = 0;
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}

	CatchError
}



/*!
	Insert a serial at the end, assuming memory available.
*/
template <typename srl, typename mm>
inline void labell<srl,mm>::insert()
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);
	mClks[mMemMan.reoccupyItr()] = EndClk;

	CatchError
}



/*!
	Insert a serial at the end, assuming memory available.
*/
template <typename srl, typename mm>
inline void labell<srl,mm>::insertMem()
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	mClks[mMemMan.reoccupyItr()] = EndClk;

	CatchError
}



/*!
	Insert and return a serial at the end, assuming memory available.
*/
template <typename srl, typename mm>
inline srl labell<srl,mm>::insertSrl()
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);
	srl const tSrl = mMemMan.reoccupyItr();
	mClks[tSrl] = EndClk;
	return tSrl;

	CatchError
}




/*!
	Insert and return a serial at the end, acquiring memory when deemed.
*/
template <typename srl, typename mm>
inline srl labell<srl,mm>::insertSrlMem()
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	srl const tSrl = mMemMan.reoccupyItr();
	mClks[tSrl] = EndClk;
	return tSrl;

	CatchError
}



/*!
	Remove a serial from the end, retaining available memory.
*/
template <typename srl, typename mm>
inline void labell<srl,mm>::remove()
{
	WatchError
	Warn(mTagCount, eNonEmptyCount);

	mMemMan.unoccupy();
	CatchError
}



/*!
	Remove a serial from the end, releasing memory when deemed.
*/
template <typename srl, typename mm>
inline void labell<srl,mm>::removeMem()
{
	WatchError
	Warn(mTagCount, eNonEmptyCount);

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();
	CatchError
}



/*!
	Reallocate more memory automatically.
*/
template<typename srl, typename mm>
void labell<srl,mm>::reallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);
	mMemMan.reallocAuto();

	srl * tSrls = mSrls;
	Clk * tClks = mClks;

	mSrls = new srl[mMemMan.acquired()];
	mClks = new Clk[mMemMan.acquired()];

	for(srl tSrl= 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = tClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
		mSrls[tItr] = tSrls[tItr];

	delete [] tSrls;
	delete [] tClks;

	CatchError
}



/*!
	Deallocate some memory automatically.
*/
template<typename srl, typename mm>
void labell<srl,mm>::deallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);
	mMemMan.deallocAuto();

	srl * const tSrls = mSrls;
	Clk * const tClks = mClks;

 	mSrls = new srl[mMemMan.acquired()];
	mClks = new Clk[mMemMan.acquired()];

	for(srl tSrl= 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = tClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
		mSrls[tItr] = tSrls[tItr];

	delete [] tSrls;
	delete [] tClks;

	CatchError
}



/*!
	Adjust the memory automatically.
*/
template<typename srl, typename mm>
void labell<srl,mm>::adjustMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);
	mMemMan.adjustAuto();

	srl * const tSrls = mSrls;
	Clk * const tClks = mClks;

	mSrls = new srl[mMemMan.acquired()];
	mClks = new Clk[mMemMan.acquired()];

	for(srl tSrl= 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = tClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
		mSrls[tItr] = tSrls[tItr];

	delete [] tSrls;
	delete [] tClks;

	CatchError
}



/*!
	Allocate memory.
*/
template<typename srl, typename mm>
void labell<srl,mm>::allocateMem(Dim const Alloc)
{
	WatchError

	Warn(!mMemMan.mismatchAlloc(Alloc), eDimensionMismatch);
	mMemMan.allocate(Alloc);

	srl * const tSrls = mSrls;
	Clk * const tClks = mClks;

	mSrls = new srl[mMemMan.acquired()];
	mClks = new Clk[mMemMan.acquired()];

	for(srl tSrl= 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = tClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
		mSrls[tItr] = tSrls[tItr];

	delete [] tSrls;
	delete [] tClks;

	CatchError
}


/*!
	Return the number of serial.
*/
template <typename srl, typename mm>
inline Dim labell<srl,mm>::serialCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the memory manager
*/
template <typename srl, typename mm>
inline mm const & labell<srl,mm>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Sweep tags optionally, only when required.
*/
template <typename srl, typename mm>
void labell<srl,mm>::sweep()
{
	WatchError
	if (mTagCount)
	{
		mTagCount = 0;
		if (++mClk == EndClk)
		{
			for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
				mClks[tSrl] = (mClks[tSrl] == mClk) ? NotClk : EndClk;
			mClk = MinClk;
		}
	}
	CatchError
}



/*!
	Sweep tags mandatorily, with a new clock.
*/
template <typename srl, typename mm>
void labell<srl,mm>::sweepMust()
{
	WatchError
	if (mTagCount) mTagCount = 0;
	if (++mClk == EndClk)
	{
		for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
			mClks[tSrl] = (mClks[tSrl] == mClk) ? NotClk : EndClk;
		mClk = MinClk;
	}
	CatchError
}


/*!
	Sweep the tags optionally, with a given clock.
*/
template <typename srl, typename mm>
inline void labell<srl,mm>::sweep(Clk const theClk)
{
	WatchError
	Warn(mClk == theClk, eClockConflict);

	if (mTagCount)
	{
		mTagCount = 0;
		mClk = theClk;
	}
	CatchError
}



/*!
	Sweep tags mandatorily, with a given clock.
*/
template <typename srl, typename mm>
inline void labell<srl,mm>::sweepMust(Clk const theClk)
{
	WatchError
	Warn(mClk == theClk, eClockConflict);

	if (mTagCount)
		mTagCount = 0;
	mClk = theClk;
	CatchError
}



/*!
	Tag the serial, assuming untagged.
*/
template <typename srl, typename mm>
inline void labell<srl,mm>::tag(srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);
	Warn(mClks[theSrl] == mClk, eClockConflict);

	mClks[theSrl] = mClk;
	mSrls[mTagCount++] = theSrl;
	CatchError
}



/*!
	Tag the serial when untagged and return whether successful.
*/
template <typename srl, typename mm>
inline Bll labell<srl,mm>::tagBll(srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	if (mClks[theSrl] == mClk)
		return false;

	mClks[theSrl] = mClk;
	mSrls[mTagCount++] = theSrl;
	return true;
	CatchError
}



/*!
	Untag the first and tag the second, assuming they are not already so.
*/
template <typename srl, typename mm>
inline void labell<srl,mm>::doUntagTag(Itr const theItr, srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);
	Warn(theItr >= mTagCount, eIteratorBeyondLimit);
	Warn(mClks[theSrl] == mClk, eClockConflict);

	srl & tSrl = mSrls[theItr];
	mClks[tSrl] = EndClk;
	tSrl = theSrl;
	mClks[theSrl] = mClk;
	CatchError
}



/*!
	Untag the first and tag the second, return whether successful.
*/
template <typename srl, typename mm>
inline Bll labell<srl,mm>::doUntagTagBll(Itr const theItr, srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);
	Warn(theItr >= mTagCount, eIteratorBeyondLimit);

	if (mClks[theSrl] == mClk)
		return false;

	srl & tSrl = mSrls[theItr];
	mClks[tSrl] = EndClk;
	tSrl = theSrl;
	mClks[theSrl] = mClk;
	return true;
	CatchError
}



/*!
	Return the tag count.
*/
template <typename srl, typename mm>
inline Dim labell<srl,mm>::tagCount() const
{
	WatchError
	return mTagCount;
	CatchError
}


/*!
	Get the tagged serial for given iterator.
*/
template <typename srl, typename mm>
inline srl labell<srl,mm>::operator[](Itr const theItr) const
{
	WatchError
	Warn(theItr >= mTagCount, eIteratorBeyondLimit);

	return mSrls[theItr];
	CatchError
}


/*!
	Get the tagged serial for given iterator.
*/
template <typename srl, typename mm>
inline srl labell<srl,mm>::serial(Itr const theItr) const
{
	WatchError
	Warn(theItr >= mTagCount, eIteratorBeyondLimit);

	return mSrls[theItr];
	CatchError
}



/*!
	Return the status of the given serial .
*/
template <typename srl, typename mm>
inline Bll labell<srl,mm>::tagged(srl const theSrl) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	return mClks[theSrl] == mClk;
	CatchError
}



/*!
	Return the status of the given serial .
*/
template <typename srl, typename mm>
inline Bll labell<srl,mm>::operator()(srl const theSrl) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	return mClks[theSrl] == mClk;
	CatchError
}




/*!
	Return the clock of the given serial.
*/
template <typename srl, typename mm>
inline Clk labell<srl,mm>::clock(srl const theSrl) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	return mClks[theSrl];
	CatchError
}




/*!
	Return the clock.
*/
template <typename srl, typename mm>
inline Clk labell<srl,mm>::clock() const
{
	WatchError
	return mClk;
	CatchError
}




closeEmuSpace



#endif // LabellTccIncluded
