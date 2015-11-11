/*!
	@file labelp.tcc
	@brief The source file for labelp template class.
	@details This is the source file for labelp template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef LabelpTccIncluded
#define LabelpTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class labelp
	@brief A class to represent labels with *partitioning*.
	@details This class represents labels with *partitioning*.
		A label is a time-stamp. When time-stamp of a slot matches
		with the global time-stamp of the label, the slot is assumed
		to be tagged with a label. A label can be locked at some point
		and splitted into fixed and flexible part. After splitting,
		the fixed part can not be untagged, whereas flexible part could be.
*/
template <typename srl, typename mm>
class labelp
{
	public:

		typedef mm MmTyp;									//!< Memory manager type.

		labelp();											//!< Constructor.
		~labelp();											//!< Destructor.
		labelp(mm const & theMm);							//!< Initialiser.
		labelp(labelp<srl,mm> const & that);				//!< Duplicator.
		labelp<srl,mm> const & operator =
				(labelp<srl,mm> const & that);				//!< Assigner.

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
		/*! @name Modifiers */
		//! @{

		void split();											//!< Split for fixed/flexi segments.

		void sweep();											//!< Sweep the label with a new clock.
		void sweep(Clk const theClk);							//!< Sweep the label with a given clock.

		void sweepMust();										//!< Sweep the label with a new clock.
		void sweepMust(Clk const theClk);						//!< Sweep the label with a given clock.

		void tag(srl const theSrl);								//!< Tag the serial without checking.
		Bll tagBll(srl const theSrl);							//!< Flag the serial with checking.

		void doUntagTag(Itr const theItr, srl const theSrl);	//!< Alter the serial without checking.
		Bll doUntagTagBll(Itr const theItr, srl const theSrl); 	//!< Change the serial with checking.

		//! @}
		/*! @name Accessors */
		//! @{

		Dim tagCount() const;					//!< The number of current tags.
		Dim fixedCount() const;					//!< Fixed count of the label.
		Dim flexiCount() const;					//!< Flexi count of the label.
		Dim flexiVerge() const;					//!< Starting verge of flexi.
		Bll splitted() const;					//!< Whether splitted?

		srl operator[](Itr const theItr) const;	//!< Get the tagged serial.
		Bll operator()(srl const theSrl) const;	//!< Get the status of a serial.
		srl serial(Itr const theItr) const;		//!< Get the tagged serial.
		Bll tagged(srl const theSrl) const;		//!< Get the status of a serial.
		Clk clock(srl const theSrl) const;		//!< Get the clock of a serial.
		Clk clock() const;						//!< Get the clock of the label.

		//!@}

	private:
		mm     mMemMan;				//!< Memory manager.
		Dim    mTagCount;			//!< Tagged serials.
		Dim    mFixedCount;			//!< Fixed count.
		Dim    mFlexiCount;			//!< Flexi count.
		Bll    mSplitted;			//!< Split for fixed.
		Clk    mClk;				//!< Current clock.
		srl *  mSrls;				//!< Tagged serials.
		Clk *  mClks;				//!< Tag clocks.
};



/*!
	@def lp
	@brief A macro to denote labelp.
	@details This macro denotes labelp.
*/
#define lp labelp



/*!
	The constructor.
*/
template<typename srl, typename mm>
labelp<srl,mm>::labelp() : mTagCount(0), mFixedCount(0),
		mFlexiCount(0), mSplitted(false), mClk(NotClk)
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
labelp<srl,mm>::labelp(mm const & theMm) :
		mMemMan(theMm), mTagCount(0), mFixedCount(0),
		mFlexiCount(0), mSplitted(false), mClk(NotClk)
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
labelp<srl,mm>::labelp(labelp<srl,mm> const & that) :
		mMemMan(that.mMemMan), mTagCount(that.mTagCount),
		mFixedCount(that.mFixedCount), mFlexiCount(that.mFlexiCount),
		mSplitted(that.mSplitted), mClk(that.mClk)
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
inline labelp<srl,mm>::~labelp()
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
labelp<srl,mm> const & labelp<srl,mm>::operator =
		(labelp<srl,mm> const & that)
{
	WatchError
	if (&that == this)
		return *this;

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		delete [] mSrls;
		delete [] mClks;
		mSrls = new srl [mMemMan.acquired()];
		mClks = new Clk [mMemMan.acquired()];
	}

	mMemMan = that.mMemMan;
	mTagCount = that.mTagCount;
	mFixedCount = that.mFixedCount;
	mFlexiCount = that.mFlexiCount;
	mSplitted = that.mSplitted;
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
void labelp<srl,mm>::syncClk()
{
	WatchError
	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = (mClks[tSrl] == mClk) ? NotClk : EndClk;
	mClk = NotClk;
	CatchError
}



/*!
	Clear the serials, retaining available memory.
*/
template<typename srl, typename mm>
inline void labelp<srl,mm>::clear()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		mFixedCount = mFlexiCount = mTagCount = 0;
		mSplitted = false;
	}
	CatchError
}



/*!
	Clear the serials, releasing memory when deemed.
*/
template<typename srl, typename mm>
inline void labelp<srl,mm>::clearMem()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		mFixedCount = mFlexiCount = mTagCount = 0;
		mSplitted = false;
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}

	CatchError
}



/*!
	Insert a serial at the end, assuming memory available.
*/
template <typename srl, typename mm>
inline void labelp<srl,mm>::insert()
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
inline void labelp<srl,mm>::insertMem()
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
inline srl labelp<srl,mm>::insertSrl()
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
inline srl labelp<srl,mm>::insertSrlMem()
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
inline void labelp<srl,mm>::remove()
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
inline void labelp<srl,mm>::removeMem()
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
void labelp<srl,mm>::reallocMemAuto()
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
	Deallocate some memory automaticaly.
*/
template<typename srl, typename mm>
void labelp<srl,mm>::deallocMemAuto()
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
void labelp<srl,mm>::adjustMemAuto()
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
void labelp<srl,mm>::allocateMem(Dim const Alloc)
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
inline Dim labelp<srl,mm>::serialCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the memory manager
*/
template <typename srl, typename mm>
inline mm const & labelp<srl,mm>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Split into fixed and flexi segments.
*/
template <typename srl, typename mm>
inline void labelp<srl,mm>::split()
{
	WatchError
	mSplitted = true;
	CatchError
}




/*!
	Sweep the tags optionally, when needed.
*/
template <typename srl, typename mm>
void labelp<srl,mm>::sweep()
{
	WatchError
	if (mTagCount)
	{
		mFixedCount = mFlexiCount = mTagCount = 0;
		mSplitted = false;
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
	Sweep the tags optionally, when needed.
*/
template <typename srl, typename mm>
inline void labelp<srl,mm>::sweep(Clk const theClk)
{
	WatchError
	Warn(mClk == theClk, eClockConflict);

	if (mTagCount)
	{
		mFixedCount = mFlexiCount = mTagCount = 0;
		mSplitted = false;
		mClk = theClk;
	}
	CatchError
}



/*!
	Sweep the tags mandatorily, with a new clock.
*/
template <typename srl, typename mm>
void labelp<srl,mm>::sweepMust()
{
	WatchError

	if (mTagCount)
	{
		mFixedCount = mFlexiCount = mTagCount = 0;
		mSplitted = false;
	}
	if (++mClk == EndClk)
	{
		for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
			mClks[tSrl] = (mClks[tSrl] == mClk) ? NotClk : EndClk;
		mClk = MinClk;
	}
	CatchError
}



/*!
	Sweep the tags mandatorily, with the given clock.
*/
template <typename srl, typename mm>
inline void labelp<srl,mm>::sweepMust(Clk const theClk)
{
	WatchError
	Warn(mClk == theClk, eClockConflict);

	if (mTagCount)
	{
		mFixedCount = mFlexiCount = mTagCount = 0;
		mSplitted = false;
	}
	mClk = theClk;
	CatchError
}



/*!
	Tag the serial assuming untagged
*/
template <typename srl, typename mm>
inline void labelp<srl,mm>::tag(srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);
	Warn(mClks[theSrl] == mClk, eClockConflict);

	mClks[theSrl] = mClk;
	mSrls[mTagCount++] = theSrl;
	mSplitted ? ++mFlexiCount : ++mFixedCount;
	CatchError
}



/*!
	Tag the serial when untagged, return whether successful.
*/
template <typename srl, typename mm>
inline Bll labelp<srl,mm>::tagBll(srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	if (mClks[theSrl] == mClk)
		return false;

	mClks[theSrl] = mClk;
	mSrls[mTagCount++] = theSrl;
	mSplitted ? ++mFlexiCount : ++mFixedCount;
	return true;
	CatchError
}



/*!
	Untag first and tag the second, assuming they are not already so.
*/
template <typename srl, typename mm>
inline void labelp<srl,mm>::doUntagTag(Itr const theItr, srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);
	Warn(theItr >= mTagCount, eIteratorBeyondLimit);
	Warn(theItr < mFixedCount, eAlterFixedLabels);
	Warn(mClks[theSrl] == mClk, eClockConflict);

	srl & tSrl = mSrls[theItr];
	mClks[tSrl] = EndClk;
	tSrl = theSrl;
	mClks[theSrl] = mClk;
	CatchError
}



/*!
	Untag first and tag the second, return whether successful.
*/
template <typename srl, typename mm>
inline Bll labelp<srl,mm>::doUntagTagBll(Itr const theItr, srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);
	Warn(theItr >= mTagCount, eIteratorBeyondLimit);
	Warn(theItr < mFixedCount, eAlterFixedLabels);

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
inline Dim labelp<srl,mm>::tagCount() const
{
	WatchError
	return mTagCount;
	CatchError
}



/*!
	Return the fixed count.
*/
template <typename srl, typename mm>
inline Dim labelp<srl,mm>::fixedCount() const
{
	WatchError
	return mFixedCount;
	CatchError
}



/*!
	Return the flexi verge i.e. start.
*/
template <typename srl, typename mm>
inline Dim labelp<srl,mm>::flexiVerge() const
{
	WatchError
	return mFixedCount;
	CatchError
}



/*!
	Return the flexi count.
*/
template <typename srl, typename mm>
inline Dim labelp<srl,mm>::flexiCount() const
{
	WatchError
	return mFlexiCount;
	CatchError
}



/*!
	Return splitted?
*/
template <typename srl, typename mm>
inline Bll labelp<srl,mm>::splitted() const
{
	WatchError
	return mSplitted;
	CatchError
}




/*!
	Get the tagged serial for given iterator.
*/
template <typename srl, typename mm>
inline srl labelp<srl,mm>::operator[](Itr const theItr) const
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
inline srl labelp<srl,mm>::serial(Itr const theItr) const
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
inline Bll labelp<srl,mm>::tagged(srl const theSrl) const
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
inline Bll labelp<srl,mm>::operator()(srl const theSrl) const
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
inline Clk labelp<srl,mm>::clock(srl const theSrl) const
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
inline Clk labelp<srl,mm>::clock() const
{
	WatchError
	return mClk;
	CatchError
}




closeEmuSpace



#endif // LabelpTccIncluded
