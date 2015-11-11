/*!
	@file queuehp.tcc
	@brief The source file for queuehp template class.
	@details This is the source file for queuehp template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef QueuehpTccIncluded
#define QueuehpTccIncluded




#include "cppl/roots/idx.hpp"
#include "cppl/tuples/idx.hpp"
#include "cppl/opfns/idx.hpp"


openEmuSpace



/*!
	@class queuehp
	@brief A class to represent customised heaps that maintain number of *peak* items.
	@details This class represents customised heaps that maintain number of *peak* items.
		Heap elements can be accessed by their serials and vice versa. The heap
		nodes are logically pairs of the items and their serial number.
		Use lt for max heap and gt for min heap.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn = eq<itm> >
class queuehp
{
	public:

		typedef mm MmTyp;									//!< Memory manager.

		queuehp();											//!< Constructor.
		queuehp(mm const & theMm);							//!< Initiliser.
		queuehp(queuehp<itm,srl,cfn,mm,eqfn> const & that);	//!< Duplicator.
		queuehp<itm,srl,cfn,mm,eqfn> const & operator =
				(queuehp<itm,srl,cfn,mm,eqfn> const & that);//!< Assigner.
		~queuehp();											//!< Destructor.

		//! @name Synchronise
		//! @{

		void syncClk();									//!< Synchronise clock.

		//! @}

		//! @name Clear
		//! @{

		void clear();							//!< Clear items, retaining available memory.
		void clearMem();						//!< Clear items, releasing memory when deemed.

		//! @}
		//! @name Insert
		//! @{

		void insert(itm const & Item);			//!< Insert an item at the end, assuming memory available.
		void insertMem(itm const & Item);		//!< Insert an item at the end, acquiring memory when needed.

		//! @}
		//! @name Remove
		//! @{

		void remove();							//!< Remove the last item, retaining available memory.
		void removeMem();						//!< Remove the last item, releasing memroy when deemed.
		void remove(itm & Item);				//!< Remove and return the last item, retaining available memory.
		void removeMem(itm & Item);				//!< Remove and return the last item, releasing memroy when deemed.

		//! @}
		//! @name Memory
		//! @{

		Dim pairCount() const;						//!< Get the number of pairs in the heap.
		mm const & MemMan() const;					//!< Get the memory manager.

		void reallocMemAuto();						//!< Reallocate memory automatically.
		void deallocMemAuto();						//!< Deallocate memory automatically.
		void adjustMemAuto();						//!< Adjust memory automatically.
		void allocateMem(Dim const Alloc);			//!< Allocate given extent of memory.

		//! @}

		/*! @name Modifiers */
		//! @{

		void reinitialise(itm const & Item);			//!< Reinitialise the heap.
		void alter(srl const theSrl, itm const & Item);	//!< Alter an item in the heap.

		//! @}
		/*! @name Accessors */
		//! @{

		Itr findItr(srl const theSrl) const;				//!< Find the iterator for the serial.
		itm const & findItem(srl const theSrl) const;		//!< Find the item for the serial.

		srl const & operator[](Itr const theItr) const;		//!< Get the serial at the iterator.
		itm const & operator()(Itr const theItr) const;		//!< Get the item at the iterator.
		srl const & serial(Itr const theItr) const;			//!< Get the serial at the iterator.
		itm const & item(Itr const theItr) const;			//!< Get the item at the iterator.

		//!@}

		/*! @name Peaks */
		//! @{

		itm const & itemPeak() const;						//!< Get the peak item.
		Itr iteratorPeak() const;							//!< Get the peak iterator.
		srl serialPeak() const;								//!< Get the peak serial.

		Dim peakCount() const;								//!< Get the number of peak pairs.

		Itr beginPeak() const;								//!< Get the inclusive begin of the peak.
		Itr endPeak() const;								//!< Get the exclusive end of the peak.
		Itr movePeak(Itr const theItr) const;				//!< Move from one peak to another.
		Itr findPeakItr(Idx const theIdx) const;			//!< Find the iterator for a peak.

		Itr randPeakItr(Rnd & theRnd) const;				//!< Return a random peak iterator.
		srl randPeakSrl(Rnd & theRnd) const;				//!< Return a random peak serial.

		//! @}

		/*! @name Iterators */
		//! @{

		Itr childLeft(Itr const theItr) const;				//!< Get the left child of an iterator.
		Itr childRight(Itr const theItr) const;				//!< Get the right child of an iterator.
		Itr siblingLeft(Itr const theItr) const;			//!< Get the left sibling of an iterator.
		Itr siblingRight(Itr const theItr) const;			//!< Get the right sibling of an iterator.

		//! @}

	private:
		mm    mMemMan;										//!< Memory manager.
		Dim    mPeakCount;									//!< Peak count.
		#if ParallelArray
			itm *  mItems;									//!< The items.
			Itr *  mItrs;									//!< The iterators.
		#else
			t2<itm,Itr> * mItmItrs;							//!< The item-itr pairs.
		#endif
		srl *  mSrls;										//!< The serials.

		Dim calcPeakCount(Itr theItr = 0) const;				//!< Determine the count of the peak.
		Itr calcPeakItr(Idx & theIdx, Itr theItr = 0) const;	//!< Return the Itr of a peak at the index.
};



/*!
	@def qhp
	@brief A macro to denote queuehp.
	@details This macro denotes queuehp.
*/
#define qhp queuehp



/*!
	The constructor.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
queuehp<itm,srl,cfn,mm,eqfn>::queuehp()
{
	WatchError

	#if ParallelArray
		mItems = new itm [mMemMan.acquired()];
		mItrs = new Itr [mMemMan.acquired()];
	#else
		mItmItrs = new t2<itm,Itr>[mMemMan.acquired()];
	#endif
	mSrls = new srl [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
	{
		#if ParallelArray
			mItems[tItr] = itm();
			mItrs[tItr] = tItr;
		#else
			mItmItrs[tItr].First = itm();
			mItmItrs[tItr].Second = tItr;
		#endif
		mSrls[tItr] = tItr;
	}

	mPeakCount = mMemMan.occupied();

	CatchError
}



/*!
	The initialiser.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
queuehp<itm,srl,cfn,mm,eqfn>::queuehp(mm const & theMm) : mMemMan(theMm)
{
	WatchError

	#if ParallelArray
		mItems = new itm [mMemMan.acquired()];
		mItrs = new Itr [mMemMan.acquired()];
	#else
		mItmItrs = new t2<itm,Itr>[mMemMan.acquired()];
	#endif
	mSrls = new srl [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
	{
		#if ParallelArray
			mItems[tItr] = itm();
			mItrs[tItr] = tItr;
		#else
			mItmItrs[tItr].First = itm();
			mItmItrs[tItr].Second = tItr;
		#endif
		mSrls[tItr] = tItr;
	}

	mPeakCount = mMemMan.occupied();

	CatchError
}



/*!
	The duplicator.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
queuehp<itm,srl,cfn,mm,eqfn>::queuehp(queuehp<itm,srl,cfn,mm,eqfn> const & that) :
		mMemMan(that.mMemMan), mPeakCount(that.mPeakCount)
{
	WatchError

	#if ParallelArray
		mItems = new itm [mMemMan.acquired()];
		mItrs = new Itr [mMemMan.acquired()];
	#else
		mItmItrs = new t2<itm,Itr>[mMemMan.acquired()];
	#endif

	mSrls = new srl [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
	{
		#if ParallelArray
			mItems[tItr] = that.mItems[tItr];
			mItrs[tItr] = that.mItrs[tItr];
		#else
			mItmItrs[tItr] = that.mItmItrs[tItr];
		#endif

		mSrls[tItr] = that.mSrls[tItr];
	}

	CatchError
}



/*!
	The destructor.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
queuehp<itm,srl,cfn,mm,eqfn>::~queuehp()
{
	WatchError

	#if ParallelArray
		delete [] mItems;
		delete [] mItrs;
	#else
		delete [] mItmItrs;
	#endif

	delete [] mSrls;

	CatchError
}



/*!
	The assigner.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
queuehp<itm,srl,cfn,mm,eqfn> const & queuehp<itm,srl,cfn,mm,eqfn>::operator =
		(queuehp<itm,srl,cfn,mm,eqfn> const & that)
{
	WatchError

	if (&that == this)
		return *this;

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		#if ParallelArray
			delete [] mItems;
			delete [] mItrs;
		#else
			delete [] mItmItrs;
		#endif
		delete [] mSrls;

		#if ParallelArray
			mItems = new itm [that.mMemMan.acquired()];
			mItrs = new Itr [that.mMemMan.acquired()];
		#else
			mItmItrs = new t2<itm,Itr>[that.mMemMan.acquired()];
		#endif
		mSrls = new srl [that.mMemMan.acquired()];
	}

	mMemMan = that.mMemMan;
	mPeakCount = that.mPeakCount;

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
	{
		#if ParallelArray
			mItems[tItr] = that.mItems[tItr];
			mItrs[tItr] = that.mItrs[tItr];
		#else
			mItmItrs[tItr] = that.mItmItrs[tItr];
		#endif

		mSrls[tItr] = that.mSrls[tItr];
	}

	return *this;

	CatchError
}



/*!
	Synchronise clock.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline void queuehp<itm,srl,cfn,mm,eqfn>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}


/*!
	Clear items, retaining available memory.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline void queuehp<itm,srl,cfn,mm,eqfn>::clear()
{
	WatchError

	if (mMemMan.resetOccupyBll())
		mPeakCount = 0;

	CatchError
}



/*!
	Clear items, releasing memory when deemed.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline void queuehp<itm,srl,cfn,mm,eqfn>::clearMem()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		mPeakCount = 0;
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}

	CatchError
}



/*!
	Insert an item at the end, assuming memory available.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline void queuehp<itm,srl,cfn,mm,eqfn>::insert(itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	srl Srl1 = mMemMan.reoccupyItr();
	Itr Itr1 = Srl1;
	#if ParallelArray
		mItems[Srl1] = Item;
	#else
		mItmItrs[Srl1].First = Item;
	#endif

	while(Itr1)
	{
		Itr Itr2 = (Itr1 - 1) >> 1;
		srl Srl2 = mSrls[Itr2];
		#if ParallelArray
			if (!cfn::iof(mItems[Srl2], Item)) break;
			mItrs[Srl2] = Itr1;
		#else
			if (!cfn::iof(mItmItrs[Srl2].First, Item)) break;
			mItmItrs[Srl2].Second = Itr1;
		#endif

		mSrls[Itr1] = Srl2;
		Itr1 = Itr2;
	}

	mSrls[Itr1] = Srl1;
	#if ParallelArray
		mItrs[Srl1] = Itr1;
		if (!Itr1)
			mPeakCount = calcPeakCount(0);
		else if (eqfn::iof(mItems[mSrls[0]], Item))
			++mPeakCount;
	#else
		mItmItrs[Srl1].Second = Itr1;
		if (!Itr1)
			mPeakCount = calcPeakCount(0);
		else if (eqfn::iof(mItmItrs[mSrls[0]].First, Item))
			++mPeakCount;
	#endif

	CatchError
}



/*!
	Insert an item at the end, acquiring memory when deemed.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline void queuehp<itm,srl,cfn,mm,eqfn>::insertMem(itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	srl Srl1 = mMemMan.reoccupyItr();
	Itr Itr1 = Srl1;
	#if ParallelArray
		mItems[Srl1] = Item;
	#else
		mItmItrs[Srl1].First = Item;
	#endif

	while(Itr1)
	{
		Itr Itr2 = (Itr1 - 1) >> 1;
		srl Srl2 = mSrls[Itr2];
		#if ParallelArray
			if (!cfn::iof(mItems[Srl2], Item)) break;
			mItrs[Srl2] = Itr1;
		#else
			if (!cfn::iof(mItmItrs[Srl2].First, Item)) break;
			mItmItrs[Srl2].Second = Itr1;
		#endif

		mSrls[Itr1] = Srl2;
		Itr1 = Itr2;
	}

	mSrls[Itr1] = Srl1;
	#if ParallelArray
		mItrs[Srl1] = Itr1;
		if (!Itr1)
			mPeakCount = calcPeakCount(0);
		else if (eqfn::iof(mItems[mSrls[0]], Item))
			++mPeakCount;
	#else
		mItmItrs[Srl1].Second = Itr1;
		if (!Itr1)
			mPeakCount = calcPeakCount(0);
		else if (eqfn::iof(mItmItrs[mSrls[0]].First, Item))
			++mPeakCount;
	#endif

	CatchError
}



/*!
	Remove an item from the end of the heap, retaining available memory.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline void queuehp<itm,srl,cfn,mm,eqfn>::remove()
{
	WatchError

	srl Srl4 = mMemMan.unoccupyItr();
	#if ParallelArray
		Itr Itr4 = mItrs[Srl4];
	#else
		Itr Itr4 = mItmItrs[Srl4].Second;
	#endif

	Itr Itr1 = Itr4;
	if (Itr4 != Srl4)
	{
		srl Srl1 = mSrls[Srl4];
		#if ParallelArray
			itm const & tItm = mItems[Srl1];
		#else
			itm const & tItm = mItmItrs[Srl1].First;
		#endif

		while(Itr1)
		{
			Itr Itr2 = (Itr1 - 1) >> 1;
			srl Srl2 = mSrls[Itr2];

			#if ParallelArray
				if (!cfn::iof(mItems[Srl2], tItm)) break;
				mItrs[Srl2] = Itr1;
			#else
				if (!cfn::iof(mItmItrs[Srl2].First, tItm)) break;
				mItmItrs[Srl2].Second = Itr1;
			#endif

			mSrls[Itr1] = Srl2;
			Itr1 = Itr2;
		}

		if (Itr1 == Itr4)
			while(true)
			{
				Itr Itr2 = (Itr1 << 1) + 1;
				if (Itr2 >= mMemMan.occupied()) break;
				srl Srl2 = mSrls[Itr2];
				Itr Itr3 = Itr2 + 1;
				srl Srl3 = mSrls[Itr3];

				#if ParallelArray
					if (Itr3 < mMemMan.occupied() &&
							cfn::iof(mItems[Srl2], mItems[Srl3]))
						Itr2 = Itr3, Srl2 = Srl3;
					if (!cfn::iof(tItm, mItems[Srl2])) break;
					mItrs[Srl2] = Itr1;
				#else
					if (Itr3 < mMemMan.occupied() &&
							cfn::iof(mItmItrs[Srl2].First, mItmItrs[Srl3].First))
						Itr2 = Itr3, Srl2 = Srl3;
					if (!cfn::iof(tItm, mItmItrs[Srl2].First)) break;
					mItmItrs[Srl2].Second = Itr1;
				#endif
				mSrls[Itr1] = Srl2;
				Itr1 = Itr2;
			}
		mSrls[Itr1] = Srl1;
		#if ParallelArray
			mItrs[Srl1] = Itr1;
		#else
			mItmItrs[Srl1].Second = Itr1;
		#endif
	}

	if (!Itr1 || !Itr4)
		mPeakCount = calcPeakCount(0);
	#if ParallelArray
		else if (eqfn::iof(mItems[mSrls[0]], mItems[Srl4]))
			mPeakCount--;
	#else
		else if (eqfn::iof(mItmItrs[mSrls[0]].First, mItmItrs[Srl4].First))
			mPeakCount--;
	#endif

	CatchError
}



/*!
	Remove and return an item from the end of the heap, retaining available memory.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline void queuehp<itm,srl,cfn,mm,eqfn>::remove(itm & Item)
{
	WatchError

	srl Srl4 = mMemMan.unoccupyItr();
	#if ParallelArray
		Item = mItems[Srl4];
		Itr Itr4 = mItrs[Srl4];
	#else
		Item = mItmItrs[Srl4].First;
		Itr Itr4 = mItmItrs[Srl4].Second;
	#endif

	Itr Itr1 = Itr4;
	if (Itr4 != Srl4)
	{
		srl Srl1 = mSrls[Srl4];
		#if ParallelArray
			itm const & tItm = mItems[Srl1];
		#else
			itm const & tItm = mItmItrs[Srl1].First;
		#endif

		while(Itr1)
		{
			Itr Itr2 = (Itr1 - 1) >> 1;
			srl Srl2 = mSrls[Itr2];

			#if ParallelArray
				if (!cfn::iof(mItems[Srl2], tItm)) break;
				mItrs[Srl2] = Itr1;
			#else
				if (!cfn::iof(mItmItrs[Srl2].First, tItm)) break;
				mItmItrs[Srl2].Second = Itr1;
			#endif

			mSrls[Itr1] = Srl2;
			Itr1 = Itr2;
		}

		if (Itr1 == Itr4)
			while(true)
			{
				Itr Itr2 = (Itr1 << 1) + 1;
				if (Itr2 >= mMemMan.occupied()) break;
				srl Srl2 = mSrls[Itr2];
				Itr Itr3 = Itr2 + 1;
				srl Srl3 = mSrls[Itr3];

				#if ParallelArray
					if (Itr3 < mMemMan.occupied() &&
							cfn::iof(mItems[Srl2], mItems[Srl3]))
						Itr2 = Itr3, Srl2 = Srl3;
					if (!cfn::iof(tItm, mItems[Srl2])) break;
					mItrs[Srl2] = Itr1;
				#else
					if (Itr3 < mMemMan.occupied() &&
							cfn::iof(mItmItrs[Srl2].First, mItmItrs[Srl3].First))
						Itr2 = Itr3, Srl2 = Srl3;
					if (!cfn::iof(tItm, mItmItrs[Srl2].First)) break;
					mItmItrs[Srl2].Second = Itr1;
				#endif
				mSrls[Itr1] = Srl2;
				Itr1 = Itr2;
			}
		mSrls[Itr1] = Srl1;
		#if ParallelArray
			mItrs[Srl1] = Itr1;
		#else
			mItmItrs[Srl1].Second = Itr1;
		#endif
	}

	if (!Itr1 || !Itr4)
		mPeakCount = calcPeakCount(0);
	#if ParallelArray
		else if (eqfn::iof(mItems[mSrls[0]], Item))
			mPeakCount--;
	#else
		else if (eqfn::iof(mItmItrs[mSrls[0]].First, Item))
			mPeakCount--;
	#endif

	CatchError
}



/*!
	Remove an item from the end, releasing memory when deemed.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline void queuehp<itm,srl,cfn,mm,eqfn>::removeMem()
{
	WatchError

	srl Srl4 = mMemMan.unoccupyItr();
	#if ParallelArray
		Itr Itr4 = mItrs[Srl4];
	#else
		Itr Itr4 = mItmItrs[Srl4].Second;
	#endif

	Itr Itr1 = Itr4;
	if (Itr4 != Srl4)
	{
		srl Srl1 = mSrls[Srl4];
		#if ParallelArray
			itm const & tItm = mItems[Srl1];
		#else
			itm const & tItm = mItmItrs[Srl1].First;
		#endif

		while(Itr1)
		{
			Itr Itr2 = (Itr1 - 1) >> 1;
			srl Srl2 = mSrls[Itr2];

			#if ParallelArray
				if (!cfn::iof(mItems[Srl2], tItm)) break;
				mItrs[Srl2] = Itr1;
			#else
				if (!cfn::iof(mItmItrs[Srl2].First, tItm)) break;
				mItmItrs[Srl2].Second = Itr1;
			#endif

			mSrls[Itr1] = Srl2;
			Itr1 = Itr2;
		}

		if (Itr1 == Itr4)
			while(true)
			{
				Itr Itr2 = (Itr1 << 1) + 1;
				if (Itr2 >= mMemMan.occupied()) break;
				srl Srl2 = mSrls[Itr2];
				Itr Itr3 = Itr2 + 1;
				srl Srl3 = mSrls[Itr3];

				#if ParallelArray
					if (Itr3 < mMemMan.occupied() &&
							cfn::iof(mItems[Srl2], mItems[Srl3]))
						Itr2 = Itr3, Srl2 = Srl3;
					if (!cfn::iof(tItm, mItems[Srl2])) break;
					mItrs[Srl2] = Itr1;
				#else
					if (Itr3 < mMemMan.occupied() &&
							cfn::iof(mItmItrs[Srl2].First, mItmItrs[Srl3].First))
						Itr2 = Itr3, Srl2 = Srl3;
					if (!cfn::iof(tItm, mItmItrs[Srl2].First)) break;
					mItmItrs[Srl2].Second = Itr1;
				#endif
				mSrls[Itr1] = Srl2;
				Itr1 = Itr2;
			}
		mSrls[Itr1] = Srl1;
		#if ParallelArray
			mItrs[Srl1] = Itr1;
		#else
			mItmItrs[Srl1].Second = Itr1;
		#endif
	}

	if (!Itr1 || !Itr4)
		mPeakCount = calcPeakCount(0);
	#if ParallelArray
		else if (eqfn::iof(mItems[mSrls[0]], mItems[Srl4]))
			mPeakCount--;
	#else
		else if (eqfn::iof(mItmItrs[mSrls[0]].First, mItmItrs[Srl4].First))
			mPeakCount--;
	#endif

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}


/*!
	Remove an item from the end, releasing memory when deemed.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline void queuehp<itm,srl,cfn,mm,eqfn>::removeMem(itm & Item)
{
	WatchError

	srl Srl4 = mMemMan.unoccupyItr();
	#if ParallelArray
		Item = mItems[Srl4];
		Itr Itr4 = mItrs[Srl4];
	#else
		Item = mItmItrs[Srl4].First;
		Itr Itr4 = mItmItrs[Srl4].Second;
	#endif

	Itr Itr1 = Itr4;
	if (Itr4 != Srl4)
	{
		srl Srl1 = mSrls[Srl4];
		#if ParallelArray
			itm const & tItm = mItems[Srl1];
		#else
			itm const & tItm = mItmItrs[Srl1].First;
		#endif

		while(Itr1)
		{
			Itr Itr2 = (Itr1 - 1) >> 1;
			srl Srl2 = mSrls[Itr2];

			#if ParallelArray
				if (!cfn::iof(mItems[Srl2], tItm)) break;
				mItrs[Srl2] = Itr1;
			#else
				if (!cfn::iof(mItmItrs[Srl2].First, tItm)) break;
				mItmItrs[Srl2].Second = Itr1;
			#endif

			mSrls[Itr1] = Srl2;
			Itr1 = Itr2;
		}

		if (Itr1 == Itr4)
			while(true)
			{
				Itr Itr2 = (Itr1 << 1) + 1;
				if (Itr2 >= mMemMan.occupied()) break;
				srl Srl2 = mSrls[Itr2];
				Itr Itr3 = Itr2 + 1;
				srl Srl3 = mSrls[Itr3];

				#if ParallelArray
					if (Itr3 < mMemMan.occupied() &&
							cfn::iof(mItems[Srl2], mItems[Srl3]))
						Itr2 = Itr3, Srl2 = Srl3;
					if (!cfn::iof(tItm, mItems[Srl2])) break;
					mItrs[Srl2] = Itr1;
				#else
					if (Itr3 < mMemMan.occupied() &&
							cfn::iof(mItmItrs[Srl2].First, mItmItrs[Srl3].First))
						Itr2 = Itr3, Srl2 = Srl3;
					if (!cfn::iof(tItm, mItmItrs[Srl2].First)) break;
					mItmItrs[Srl2].Second = Itr1;
				#endif
				mSrls[Itr1] = Srl2;
				Itr1 = Itr2;
			}
		mSrls[Itr1] = Srl1;
		#if ParallelArray
			mItrs[Srl1] = Itr1;
		#else
			mItmItrs[Srl1].Second = Itr1;
		#endif
	}

	if (!Itr1 || !Itr4)
		mPeakCount = calcPeakCount(0);
	#if ParallelArray
		else if (eqfn::iof(mItems[mSrls[0]], Item))
			--mPeakCount;
	#else
		else if (eqfn::iof(mItmItrs[mSrls[0]].First, Item))
			--mPeakCount;
	#endif

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Reallocate more memory automatically.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
void queuehp<itm,srl,cfn,mm,eqfn>::reallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);
	mMemMan.reallocAuto();

	#if ParallelArray
		itm * const tItms = mItems;
		Itr * const tItrs = mItrs;
	#else
		t2<itm,Itr> * const tItmItrs = mItmItrs;
	#endif
	srl * const tSrls = mSrls;

	#if ParallelArray
		mItems = new itm[mMemMan.acquired()];
		mItrs = new Itr[mMemMan.acquired()];
	#else
		mItmItrs = new t2<itm,Itr>[mMemMan.acquired()];
	#endif
	mSrls = new srl[mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
	{
		#if ParallelArray
			mItems[tItr] = tItms[tItr];
			mItrs[tItr] = tItrs[tItr];
		#else
			mItmItrs[tItr] = tItmItrs[tItr];
		#endif
		mSrls[tItr] = tSrls[tItr];
	}
	#if ParallelArray
		delete [] tItms;
		delete [] tItrs;
	#else
		delete [] tItmItrs;
	#endif
	delete [] tSrls;

	CatchError
}



/*!
	Deallocate some memory automatically.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
void queuehp<itm,srl,cfn,mm,eqfn>::deallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);
	mMemMan.deallocAuto();

	#if ParallelArray
		itm * const tItms = mItems;
		Itr * const tItrs = mItrs;
	#else
		t2<itm,Itr> * const tItmItrs = mItmItrs;
	#endif
	srl * const tSrls = mSrls;

	#if ParallelArray
		mItems = new itm[mMemMan.acquired()];
		mItrs = new Itr[mMemMan.acquired()];
	#else
		mItmItrs = new t2<itm,Itr>[mMemMan.acquired()];
	#endif
	mSrls = new srl[mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
	{
		#if ParallelArray
			mItems[tItr] = tItms[tItr];
			mItrs[tItr] = tItrs[tItr];
		#else
			mItmItrs[tItr] = tItmItrs[tItr];
		#endif

		mSrls[tItr] = tSrls[tItr];
	}
	#if ParallelArray
		delete [] tItms;
		delete [] tItrs;
	#else
		delete [] tItmItrs;
	#endif
	delete [] tSrls;

	CatchError
}



/*!
	Adjust memory automatically.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
void queuehp<itm,srl,cfn,mm,eqfn>::adjustMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);
	mMemMan.adjustAuto();

	#if ParallelArray
		itm * const tItms = mItems;
		Itr * const tItrs = mItrs;
	#else
		t2<itm,Itr> * const tItmItrs = mItmItrs;
	#endif
	srl * const tSrls = mSrls;

	#if ParallelArray
		mItems = new itm[mMemMan.acquired()];
		mItrs = new Itr[mMemMan.acquired()];
	#else
		mItmItrs = new t2<itm,Itr>[mMemMan.acquired()];
	#endif

	mSrls = new srl[mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
	{
		#if ParallelArray
			mItems[tItr] = tItms[tItr];
			mItrs[tItr] = tItrs[tItr];
		#else
			mItmItrs[tItr] = tItmItrs[tItr];
		#endif
		mSrls[tItr] = tSrls[tItr];
	}
	#if ParallelArray
		delete [] tItms;
		delete [] tItrs;
	#else
		delete [] tItmItrs;
	#endif

	delete [] tSrls;

	CatchError
}



/*!
	Allocate memory automatically.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
void queuehp<itm,srl,cfn,mm,eqfn>::allocateMem(Dim const Alloc)
{
	WatchError

	Warn(!mMemMan.mismatchAlloc(Alloc), eDimensionMismatch);
	mMemMan.allocate(Alloc);

	#if ParallelArray
		itm * const tItms = mItems;
		Itr * const tItrs = mItrs;
	#else
		t2<itm,Itr> * const tItmItrs = mItmItrs;
	#endif
	srl * const tSrls = mSrls;

	#if ParallelArray
		mItems = new itm[mMemMan.acquired()];
		mItrs = new Itr[mMemMan.acquired()];
	#else
		mItmItrs = new t2<itm,Itr>[mMemMan.acquired()];
	#endif

	mSrls = new srl[mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
	{
		#if ParallelArray
			mItems[tItr] = tItms[tItr];
			mItrs[tItr] = tItrs[tItr];
		#else
			mItmItrs[tItr] = tItmItrs[tItr];
		#endif
		mSrls[tItr] = tSrls[tItr];
	}
	#if ParallelArray
		delete [] tItms;
		delete [] tItrs;
	#else
		delete [] tItmItrs;
	#endif

	delete [] tSrls;

	CatchError
}



/*!
	Return the pair-count of the heap.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Dim queuehp<itm,srl,cfn,mm,eqfn>::pairCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the memory manager.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline mm const & queuehp<itm,srl,cfn,mm,eqfn>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}


/*!
	The initialiser.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
void queuehp<itm,srl,cfn,mm,eqfn>::reinitialise(itm const & Item)
{
	WatchError

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
	{
		#if ParallelArray
			mItems[tItr] = Item;
			mItrs[tItr] = tItr;
		#else
			mItmItrs[tItr].First = Item;
			mItmItrs[tItr].Second = tItr;
		#endif
		mSrls[tItr] = tItr;

	}
	mPeakCount = mMemMan.occupied();

	CatchError
}



/*!
	Alter an item to the heap.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
void queuehp<itm,srl,cfn,mm,eqfn>::alter(srl const theSrl, itm const & Item)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	#if ParallelArray
		Itr Itr1 = mItrs[theSrl], Itr4 = Itr1;
		itm const & tItm = mItems[theSrl];
	#else
		Itr Itr1 = mItmItrs[theSrl].Second, Itr4 = Itr1;
		itm const & tItm = mItmItrs[theSrl].First;
	#endif

	while(Itr1)
	{
		Itr Itr2 = (Itr1 - 1) >> 1;
		srl Srl2 = mSrls[Itr2];
		#if ParallelArray
			if (!cfn::iof(mItems[Srl2], Item)) break;
			mItrs[Srl2] = Itr1;
		#else
			if (!cfn::iof(mItmItrs[Srl2].First, Item)) break;
			mItmItrs[Srl2].Second = Itr1;
		#endif
		mSrls[Itr1] = Srl2;
		Itr1 = Itr2;
	}
	if (Itr1 == Itr4)
		while(true)
		{
			Itr Itr2 = (Itr1 << 1) + 1;
			if (Itr2 >= mMemMan.occupied()) break;
			Itr Itr3 = Itr2 + 1;
			srl Srl2 = mSrls[Itr2];
			#if ParallelArray
				if (Itr3 < mMemMan.occupied())
				{
					srl Srl3 = mSrls[Itr3];
					if (cfn::iof(mItems[Srl2], mItems[Srl3]))
						Itr2 = Itr3, Srl2 = Srl3;
				}
				if (!cfn::iof(Item, mItems[Srl2])) break;
				mItrs[Srl2] = Itr1;
			#else
				if (Itr3 < mMemMan.occupied())
				{
					srl Srl3 = mSrls[Itr3];
					if (cfn::iof(mItmItrs[Srl2].First, mItmItrs[Srl3].First))
						Itr2 = Itr3, Srl2 = Srl3;
				}
				if (!cfn::iof(Item, mItmItrs[Srl2].First)) break;
				mItmItrs[Srl2].Second = Itr1;
			#endif
			mSrls[Itr1] = Srl2;
			Itr1 = Itr2;
		}
	mSrls[Itr1] = theSrl;
	#if ParallelArray
		mItrs[theSrl] = Itr1;
	#else
		mItmItrs[theSrl].Second = Itr1;
	#endif
	if (!Itr1 || !Itr4)
	{
		#if ParallelArray
			mItems[theSrl] = Item;
		#else
			mItmItrs[theSrl].First = Item;
		#endif
		mPeakCount = calcPeakCount(0);
	}
	else
	{
		#if ParallelArray
			if (eqfn::iof(mItems[mSrls[0]],Item)) ++mPeakCount;
			if (eqfn::iof(mItems[mSrls[0]], tItm)) --mPeakCount;
			mItems[theSrl] = Item;
		#else
			if (eqfn::iof(mItmItrs[mSrls[0]].First, Item)) ++mPeakCount;
			if (eqfn::iof(mItmItrs[mSrls[0]].First, tItm)) --mPeakCount;
			mItmItrs[theSrl].First = Item;
		#endif
	}

	CatchError
}



/*!
	Find the iterator for the given serial.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Itr queuehp<itm,srl,cfn,mm,eqfn>::findItr(srl const theSrl) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);
	#if ParallelArray
		return mItrs[theSrl];
	#else
		return mItmItrs[theSrl].Second;
	#endif

	CatchError
}



/*!
	Find the item for the given serial.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline itm const & queuehp<itm,srl,cfn,mm,eqfn>::findItem(srl const theSrl) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);
	#if ParallelArray
		return mItems[theSrl];
	#else
		return mItmItrs[theSrl].First;
	#endif

	CatchError
}



/*!
	Get the serial for given iterator.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline srl const & queuehp<itm,srl,cfn,mm,eqfn>::operator[](Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mSrls[theItr];

	CatchError
}



/*!
	Get the itm in the heap for the given iterator.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline itm const & queuehp<itm,srl,cfn,mm,eqfn>::operator()(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);
	#if ParallelArray
		return mItems[mSrls[theItr]];
	#else
		return mItmItrs[mSrls[theItr]].First;
	#endif

	CatchError
}


/*!
	Get the serial for given iterator.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline srl const & queuehp<itm,srl,cfn,mm,eqfn>::serial(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mSrls[theItr];

	CatchError
}



/*!
	Get the itm in the heap for the given iterator.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline itm const & queuehp<itm,srl,cfn,mm,eqfn>::item(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mItems[mSrls[theItr]];
	#else
		return mItmItrs[mSrls[theItr]].First;
	#endif

	CatchError
}



/*!
	Return the peak item of the heap.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline itm const & queuehp<itm,srl,cfn,mm,eqfn>::itemPeak() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eEmptyCount);

	#if ParallelArray
	return mItems[mSrls[0]];
	#else
	return mItmItrs[mSrls[0]].First;
	#endif

	CatchError
}



/*!
	Return the peak serial of the heap
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline srl queuehp<itm,srl,cfn,mm,eqfn>::serialPeak() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eEmptyCount);

	return mSrls[0];

	CatchError
}


/*!
	Return the peak iterator of the heap
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Itr queuehp<itm,srl,cfn,mm,eqfn>::iteratorPeak() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eEmptyCount);

	return 0;

	CatchError
}



/*!
	Return the count of the peak.
*/
template <typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Dim queuehp<itm,srl,cfn,mm,eqfn>::peakCount() const
{
	WatchError

	return mPeakCount;

	CatchError
}


/*!
	Return the inclusive begin of the peaks.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Itr queuehp<itm,srl,cfn,mm,eqfn>::beginPeak() const
{
	WatchError

	return mMemMan.occupied() ? 0 : InvItr;

	CatchError
}



/*!
	Return the exclusive end of the peaks
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Itr queuehp<itm,srl,cfn,mm,eqfn>::endPeak() const
{
	WatchError

	return InvItr;

	CatchError
}



/*!
	Move to from one peak to another peak.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
Itr queuehp<itm,srl,cfn,mm,eqfn>::movePeak(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		itm const & tItm = mItems[mSrls[0]];
	#else
		itm const & tItm = mItmItrs[mSrls[0]].First;
	#endif
	Itr tItr = theItr;
	tItr = (tItr << 1) + 1;

	if (tItr < mMemMan.occupied())
	{
		#if ParallelArray
			if (eqfn::iof(tItm, mItems[mSrls[tItr]]))
				return tItr;
			if (++tItr < mMemMan.occupied() &&
					eqfn::iof(tItm, mItems[mSrls[tItr]]))
				return tItr;
		#else
			if (eqfn::iof(tItm, mItmItrs[mSrls[tItr]].First))
				return tItr;
			if (++tItr < mMemMan.occupied() &&
					eqfn::iof(tItm, mItmItrs[mSrls[tItr]].First))
				return tItr;
		#endif
	}
	while(true)
	{	while (tItr && (~tItr & 1))
			tItr = (tItr - 1) >> 1;
		if (!tItr) break;
		#if ParallelArray
			if (++tItr < mMemMan.occupied() &&
					eqfn::iof(tItm, mItems[mSrls[tItr]]))
				return tItr;
		#else
			if (++tItr < mMemMan.occupied() &&
					eqfn::iof(tItm, mItmItrs[mSrls[tItr]].First))
				return tItr;
		#endif
	}

	return InvItr;

	CatchError
}



/*!
	Return the count of the current peak.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Itr queuehp<itm,srl,cfn,mm,eqfn>::findPeakItr(Idx const theIdx) const
{
	WatchError

	Idx tIdx = theIdx;
	return calcPeakItr(tIdx, castItr(0));

	CatchError
}


/*!
	Return a random peak iterator.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Itr queuehp<itm,srl,cfn,mm,eqfn>::randPeakItr(Rnd & theRnd) const
{
	WatchError

	Idx tIdx = uniform(theRnd, mPeakCount);
	return calcPeakItr(tIdx, castItr(0));

	CatchError
}



/*!
	Return a random peak serial.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline srl queuehp<itm,srl,cfn,mm,eqfn>::randPeakSrl(Rnd & theRnd) const
{
	WatchError

	Idx tIdx = uniform(theRnd, mPeakCount);
	return mSrls[calcPeakItr(tIdx, castItr(0))];

	CatchError
}



/*!
	Return the left child of an iterator.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Itr queuehp<itm,srl,cfn,mm,eqfn>::childLeft(Itr const theItr) const
{
	WatchError

	Itr tItr = (theItr << 1) + 1;
	return tItr < mMemMan.occupied() ? tItr : InvItr;

	CatchError
}



/*!
	Return the right child of an iterator.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Itr queuehp<itm,srl,cfn,mm,eqfn>::childRight(Itr const theItr) const
{
	WatchError

	Itr tItr = (theItr << 1) + 2;
	return tItr < mMemMan.occupied() ? tItr : InvItr;

	CatchError
}



/*!
	Return the left sibling of an iterator.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Itr queuehp<itm,srl,cfn,mm,eqfn>::siblingLeft(Itr const theItr) const
{
	WatchError

	return ((theItr & 1) || !theItr) ?  InvItr : theItr - 1;

	CatchError
}



/*!
	Return the right sibling of an iterator.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
inline Itr queuehp<itm,srl,cfn,mm,eqfn>::siblingRight(Itr const theItr) const
{
	WatchError

	return ((theItr & 1) && theItr + 1 < mMemMan.occupied()) ? theItr + 1 : InvItr;

	CatchError
}



/*!
	Return the count of the current peak.
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
Dim queuehp<itm,srl,cfn,mm,eqfn>::calcPeakCount(Itr theItr) const
{
	WatchError

	if (mMemMan.beyondOccupied(theItr)) return 0;
	#if ParallelArray
	if (theItr && !eqfn::iof(mItems[mSrls[theItr]], mItems[mSrls[0]]))
		return 0;
	#else
	if (theItr &&
			!eqfn::iof(mItmItrs[mSrls[theItr]].First, mItmItrs[mSrls[0]].First))
		return 0;
	#endif
	theItr = (theItr << 1) + 1;
	if (theItr + 1 < mMemMan.occupied())
		return 1 + calcPeakCount(theItr) + calcPeakCount(theItr + 1);
	if (theItr < mMemMan.occupied())
		return 1 + calcPeakCount(theItr);
	return 1;

	CatchError
}



/*!
	Return a peak item
*/
template<typename itm, typename srl, typename cfn, typename mm, typename eqfn>
Itr queuehp<itm,srl,cfn,mm,eqfn>::calcPeakItr(Idx & theIdx, Itr theItr) const
{
	WatchError

	if (mMemMan.beyondOccupied(theItr) || theIdx >= mPeakCount)
		return InvItr;
	#if ParallelArray
	if (theItr && !eqfn::iof(mItems[mSrls[theItr]], mItems[mSrls[0]]))
		return InvItr;
	#else
	if (theItr &&
			!eqfn::iof(mItmItrs[mSrls[theItr]].First, mItmItrs[mSrls[0]].First))
		return InvItr;
	#endif
	if (!theIdx)
		return theItr;

	--theIdx;
	theItr = (theItr << 1) + 1;
	if (mMemMan.beyondOccupied(theItr))
		return InvItr;

	Itr	tItr =  calcPeakItr(theIdx, theItr);

	if (!theIdx && tItr != InvItr)
		return tItr;
	if (mMemMan.beyondOccupied(++theItr))
		return InvItr;
	return calcPeakItr(theIdx, theItr);

	CatchError
}



closeEmuSpace



#endif // QueuehpTccIncluded
