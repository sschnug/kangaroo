/*!
	@file labelu.tcc
	@brief The source file for labelu template class.
	@details This is the source file for labelu template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef LabeluTccIncluded
#define LabeluTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class labelu
	@brief A class to represent labels with listing and *untagging*.
	@details This class represents labels with listing and *untagging*.
		A label is a time-stamp. When time-stamp of a slot matches
		with the global time-stamp of the label, the slot is assumed
		to be tagged with a label. Untagging operation invalidates
		the ordering of the tagged serial in the list.
*/
template <typename srl, typename mm>
class labelu
{
	public:

		typedef mm MmTyp;							//!< Memory manager type.

		~labelu();									//!< Destructor.
		labelu();									//!< Constructor.
		labelu(mm const & theMm);					//!< Initialiser.
		labelu(labelu<srl,mm> const & that);		//!< Duplicator.
		labelu<srl,mm> const & operator =
				(labelu<srl,mm> const & that);		//!< Assigner.

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
		Bll tagBll(srl const theSrl);						//!< Tag the serial when untagged and return whether successful.

		void untag(srl const theSrl);						//!< Untag the serial, assuming tagged.
		Bll untagBll(srl const theSrl);						//!< Untag the serial when tagged and return whether successful.

		void doUntagTag(srl const theSrl1, srl const theSrl2);		//!< Untag the first and tag the second, assuming they are not already so.
		Bll doUntagTagBll(srl const theSrl1, srl const theSrl2);	//!< Untag the first and tag the second, return whether successful.

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

		mm	   mMemMan;				//!< Memory manager.
		Dim	   mTagCount;			//!< Tagged serial count.
		Clk    mClk;				//!< Current clock.
		srl *  mSrls;				//!< Tagged serials.
		Clk *  mClks;				//!< Tag clocks.
		Itr *  mItrs;				//!< Tagged iterators.
};



/*!
	@def lu
	@brief A macro to denote labelu.
	@details This macro denotes labelu.
*/
#define lu labelu



/*!
	The constructor.
*/
template<typename srl, typename mm>
inline labelu<srl,mm>::labelu() : mTagCount(0), mClk(NotClk)
{
	WatchError
	mSrls = new srl [mMemMan.acquired()];
	mClks = new Clk [mMemMan.acquired()];
	mItrs = new Itr [mMemMan.acquired()];

	for (srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = EndClk;
	CatchError
}



/*!
	The initialiser.
*/
template<typename srl, typename mm>
inline labelu<srl,mm>::labelu(mm const & theMm) :
		mMemMan(theMm), mTagCount(0), mClk(NotClk)
{
	WatchError
	mSrls = new srl [mMemMan.acquired()];
	mClks = new Clk [mMemMan.acquired()];
	mItrs = new Itr [mMemMan.acquired()];
	for (srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = EndClk;
	CatchError
}



/*!
	The duplicator.
*/
template <typename srl, typename mm>
labelu<srl,mm>::labelu(labelu<srl,mm> const & that) : mMemMan(that.mMemMan),
		mTagCount(that.mTagCount), mClk(that.mClk)
{
	WatchError
	mSrls = new srl [mMemMan.acquired()];
	mClks = new Clk [mMemMan.acquired()];
	mItrs = new Itr [mMemMan.acquired()];

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = that.mClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
	{
		srl & tSrl = mSrls[tItr];
		tSrl = that.mSrls[tItr];
		mItrs[tSrl] = that.mItrs[tSrl];
	}
	CatchError
}



/*!
	The destructor.
*/
template <typename srl, typename mm>
inline labelu<srl,mm>::~labelu()
{
	WatchError
	delete [] mSrls;
	delete [] mClks;
	delete [] mItrs;
	CatchError
}



/*!
	The assigner.
*/
template <typename srl, typename mm>
labelu<srl,mm> const & labelu<srl,mm>::operator = (labelu<srl,mm> const & that)
{
	WatchError
	if (&that == this)
		return *this;

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		delete [] mSrls;
		delete [] mClks;
		delete [] mItrs;

		mSrls = new srl [that.mMemMan.acquired()];
		mClks = new Clk [that.mMemMan.acquired()];
		mItrs = new Itr [that.mMemMan.acquired()];
	}

	mMemMan = that.mMemMan;
	mTagCount = that.mTagCount;
	mClk = that.mClk;

	for(srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = that.mClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
	{
		srl & tSrl = mSrls[tItr];
		tSrl = that.mSrls[tItr];
		mItrs[tSrl] = that.mItrs[tSrl];
	}

	return *this;
	CatchError
}



/*!
	Synchronize the clock.
*/
template<typename srl, typename mm>
void labelu<srl,mm>::syncClk()
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
inline void labelu<srl,mm>::clear()
{
	WatchError

	if (mMemMan.resetOccupyBll())
		mTagCount = 0;

	CatchError
}



/*!
	Clear the serial, releasing memory when deemed.
*/
template<typename srl, typename mm>
inline void labelu<srl,mm>::clearMem()
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
inline void labelu<srl,mm>::insert()
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
inline void labelu<srl,mm>::insertMem()
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
inline srl labelu<srl,mm>::insertSrl()
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
inline srl labelu<srl,mm>::insertSrlMem()
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
	Remove from the end, retaining available memory.
*/
template <typename srl, typename mm>
inline void labelu<srl,mm>::remove()
{
	WatchError

	srl const tSrl0 = mMemMan.unoccupyItr();

	if (mClks[tSrl0] == mClk)
	{
		Itr const tItr = mItrs[tSrl0];
		if (--mTagCount && tItr != mTagCount)
		{
			srl & tSrl1 = mSrls[tItr];
			tSrl1 = mSrls[mTagCount];
			mItrs[tSrl1] = tItr;
		}
	}
	CatchError
}



/*!
	Remove from the end, releasing memory when deemed.
*/
template <typename srl, typename mm>
inline void labelu<srl,mm>::removeMem()
{
	WatchError
	srl const tSrl0 = mMemMan.unoccupyItr();

	if (mClks[tSrl0] == mClk)
	{
		Itr const tItr = mItrs[tSrl0];
		if (--mTagCount && tItr != mTagCount)
		{
			srl & tSrl1 = mSrls[tItr];
			tSrl1 = mSrls[mTagCount];
			mItrs[tSrl1] = tItr;
		}
	}

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();
	CatchError
}



/*!
	Allocate more memory automatically.
*/
template<typename srl, typename mm>
void labelu<srl,mm>::reallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);
	mMemMan.reallocAuto();

	srl * tSrls = mSrls;
	Clk * tClks = mClks;
	Itr * tItrs = mItrs;

	mSrls = new srl[mMemMan.acquired()];
	mClks = new Clk[mMemMan.acquired()];
	mItrs = new Itr[mMemMan.acquired()];

	for(srl tSrl= 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = tClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
	{
		srl & tSrl = mSrls[tItr];
		tSrl = tSrls[tItr];
		mItrs[tSrl] = tItrs[tSrl];
	}

	delete [] tSrls;
	delete [] tClks;
	delete [] tItrs;
	CatchError
}



/*!
	Deallocate some memory automatically.
*/
template<typename srl, typename mm>
void labelu<srl,mm>::deallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);
	mMemMan.deallocAuto();

	srl * tSrls = mSrls;
	Clk * tClks = mClks;
	Itr * tItrs = mItrs;

	mSrls = new srl[mMemMan.acquired()];
	mClks = new Clk[mMemMan.acquired()];
	mItrs = new Itr[mMemMan.acquired()];

	for(srl tSrl= 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = tClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
	{
		srl & tSrl = mSrls[tItr];
		tSrl = tSrls[tItr];
		mItrs[tSrl] = tItrs[tSrl];
	}

	delete [] tSrls;
	delete [] tClks;
	delete [] tItrs;
	CatchError
}



/*!
	Adjust the memory automatically.
*/
template<typename srl, typename mm>
void labelu<srl,mm>::adjustMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);
	mMemMan.adjustAuto();

	srl * tSrls = mSrls;
	Clk * tClks = mClks;
	Itr * tItrs = mItrs;

	mSrls = new srl[mMemMan.acquired()];
	mClks = new Clk[mMemMan.acquired()];
	mItrs = new Itr[mMemMan.acquired()];

	for(srl tSrl= 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = tClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
	{
		srl & tSrl = mSrls[tItr];
		tSrl = tSrls[tItr];
		mItrs[tSrl] = tItrs[tSrl];
	}

	delete [] tSrls;
	delete [] tClks;
	delete [] tItrs;

	CatchError
}



/*!
	Allocate memory.
*/
template<typename srl, typename mm>
void labelu<srl,mm>::allocateMem(Dim const Alloc)
{
	WatchError

	Warn(!mMemMan.mismatchAlloc(Alloc), eDimensionMismatch);
	mMemMan.allocate(Alloc);

	srl * tSrls = mSrls;
	Clk * tClks = mClks;
	Itr * tItrs = mItrs;

	mSrls = new srl[mMemMan.acquired()];
	mClks = new Clk[mMemMan.acquired()];
	mItrs = new Itr[mMemMan.acquired()];

	for(srl tSrl= 0; tSrl < mMemMan.occupied(); ++tSrl)
		mClks[tSrl] = tClks[tSrl];

	for(Itr tItr = 0; tItr < mTagCount; ++tItr)
	{
		srl & tSrl = mSrls[tItr];
		tSrl = tSrls[tItr];
		mItrs[tSrl] = tItrs[tSrl];
	}

	delete [] tSrls;
	delete [] tClks;
	delete [] tItrs;

	CatchError
}



/*!
	Sweep the tags optionally, only when needed
*/
template <typename srl, typename mm>
inline void labelu<srl,mm>::sweep()
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
	Sweep the tags optionally, only when needed.
*/
template <typename srl, typename mm>
inline void labelu<srl,mm>::sweep(Clk const theClk)
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
	Sweep the tags mandatorily, with a new clock.
*/
template <typename srl, typename mm>
inline void labelu<srl,mm>::sweepMust()
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
	Sweep the tags mandatorily, with a given clock.
*/
template <typename srl, typename mm>
inline void labelu<srl,mm>::sweepMust(Clk const theClk)
{
	WatchError
	Warn(mClk == theClk, eClockConflict);

	if (mTagCount) mTagCount = 0;
	mClk = theClk;
	CatchError
}



/*!
	Tag the serial assuming untagged
*/
template <typename srl, typename mm>
inline void labelu<srl,mm>::tag(srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);
	Warn(mClks[theSrl] == mClk, eClockConflict);

	mClks[theSrl] = mClk;
	Itr & tItr = mItrs[theSrl];
	tItr = mTagCount++;
	mSrls[tItr] = theSrl;
	CatchError
}



/*!
	Tag the serial when untagged, return whether successful.
*/
template <typename srl, typename mm>
inline Bll labelu<srl,mm>::tagBll(srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	if (mClks[theSrl] == mClk)
		return false;

	mClks[theSrl] = mClk;
	Itr & tItr = mItrs[theSrl];
	tItr = mTagCount++;
	mSrls[tItr] = theSrl;
	return true;
	CatchError
}



/*!
	Untag the serial assuming tagged; invalidates the order in the tagged list.
*/
template <typename srl, typename mm>
inline void labelu<srl,mm>::untag(srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);
	Warn(mClks[theSrl] != mClk, eClockConflict);

	Itr const tItr = mItrs[theSrl];
	if (--mTagCount && tItr != mTagCount)
	{
		srl & tSrl = mSrls[tItr];
		tSrl = mSrls[mTagCount];
		mItrs[tSrl] = tItr;
	}
	mClks[theSrl] = EndClk;
	CatchError
}




/*!
	Untag the serial when tagged and return whether success; invalidates the order in the tagged list.
*/
template <typename srl, typename mm>
inline Bll labelu<srl,mm>::untagBll(srl const theSrl)
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	if (mClks[theSrl] != mClk)
		return false;

	Itr const tItr = mItrs[theSrl];
	if (--mTagCount && tItr != mTagCount)
	{
		srl & tSrl = mSrls[tItr];
		tSrl = mSrls[mTagCount];
		mItrs[tSrl] = tItr;
	}
	mClks[theSrl] = EndClk;
	return true;
	CatchError
}



/*!
	Untag the first and tag the second, assuming they are not so.
*/
template <typename srl, typename mm>
inline void labelu<srl,mm>::doUntagTag(srl const theSrl1, srl const theSrl2)
{
	WatchError
	Warn(theSrl1 >= mMemMan.occupied(), eSerialBeyondLimit);
	Warn(theSrl2 >= mMemMan.occupied(), eSerialBeyondLimit);
	Warn(mClks[theSrl1] != mClk, eClockConflict);
	Warn(mClks[theSrl2] == mClk, eClockConflict);

	Itr const tItr = mItrs[theSrl1];
	mItrs[theSrl2] = tItr;
	mSrls[tItr] = theSrl2;

	mClks[theSrl1] = EndClk;
	mClks[theSrl2] = mClk;
	CatchError
}



/*!
	Untag the first and tag the second when they are not so, return whether successful.
*/
template <typename srl, typename mm>
inline Bll labelu<srl,mm>::doUntagTagBll(srl const theSrl1, srl const theSrl2)
{
	WatchError
	Warn(theSrl1 >= mMemMan.occupied(), eSerialBeyondLimit);
	Warn(theSrl2 >= mMemMan.occupied(), eSerialBeyondLimit);

	if (mClks[theSrl1] != mClk || mClks[theSrl2] == mClk)
		return false;

	Itr const tItr = mItrs[theSrl1];
	mItrs[theSrl2] = tItr;
	mSrls[tItr] = theSrl2;

	mClks[theSrl1] = EndClk;
	mClks[theSrl2] = mClk;
	return true;
	CatchError
}



/*!
	Return the tagged serial count.
*/
template <typename srl, typename mm>
inline Dim labelu<srl,mm>::tagCount() const
{
	WatchError
	return mTagCount;
	CatchError
}



/*!
	Return the flagged serial for given iterator.
*/
template <typename srl, typename mm>
inline srl labelu<srl,mm>::operator[](Itr const theItr) const
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
inline srl labelu<srl,mm>::serial(Itr const theItr) const
{
	WatchError
	Warn(theItr >= mTagCount, eIteratorBeyondLimit);

	return mSrls[theItr];
	CatchError
}



/*!
	Return the status of the given serial.
*/
template <typename srl, typename mm>
inline Bll labelu<srl,mm>::tagged(srl const theSrl) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	return mClks[theSrl] == mClk;
	CatchError
}



/*!
	Return the status of the given serial.
*/
template <typename srl, typename mm>
inline Bll labelu<srl,mm>::operator()(srl const theSrl) const
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
inline Clk labelu<srl,mm>::clock(srl const theSrl) const
{
	WatchError
	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	return mClks[theSrl];
	CatchError
}




/*!
	Return the clock of the label.
*/
template <typename srl, typename mm>
inline Clk labelu<srl,mm>::clock() const
{
	WatchError
	return mClk;

	CatchError
}



closeEmuSpace



#endif // LabeluTccIncluded
