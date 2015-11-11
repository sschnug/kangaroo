/*!
	@file queuehf.tcc
	@brief The source file for queuehf template class.
	@details This is the source file for queuehf template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef QueuehfTccIncluded
#define QueuehfTccIncluded



#include "cppl/roots/idx.hpp"
#include "cppl/tuples/idx.hpp"



openEmuSpace



/*!
	@class queuehf
	@brief A class to represent customised heaps that support *find* operation.
	@details This class represents customised heaps that support *find* operation.
		Heap elements can be accessed by their serials and vice versa. The heap
		nodes are logically pairs of the items and their serial number.
		Use lt for max heap and gt for min heap.
*/
template <typename itm, typename srl, typename cfn, typename mm>
class queuehf
{
	public:

		typedef mm MmTyp;								//!< Memory manager.

		queuehf();										//!< Constructor.
		queuehf(mm const & theMm);						//!< Initialser.
		queuehf(queuehf<itm,srl,cfn,mm> const & that);	//!< Duplicator.
		queuehf<itm,srl,cfn,mm> const & operator =
			(queuehf<itm,srl,cfn,mm> const & that);		//!< Assigner.
		~queuehf();										//!< Destructor.

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
		srl insertSrl(itm const & Item);		//!< Insert an item at the end and return the serial, assuming memory available.
		srl insertSrlMem(itm const & Item);		//!< Insert an item at the end and return the serial, acquiring memory when needed.

		//! @}
		//! @name Remove
		//! @{

		void remove();							//!< Remove the last item, retaining available memory.
		void removeMem();						//!< Remove the last item, releasing available memory.
		void remove(itm & Item);				//!< Remove and return the last item, retaining available memory.
		void removeMem(itm & Item);				//!< Remove and return the last item, releasing memroy when deemed.

		//! @}
		//! @name Memory
		//! @{

		Dim pairCount() const;						//!< Get the number of serial-item pair.
		mm const & MemMan() const;					//!< Get the memory manager.

		void reallocMemAuto();						//!< Reallocate memory automatically.
		void deallocMemAuto();						//!< Deallocate memory automatically.
		void adjustMemAuto();						//!< Adjust memory automatically.
		void allocateMem(Dim const Alloc);			//!< Allocate given extent of memory.

		//! @}

		/*! @name Modifiers */
		//! @{

		void reinitialise(itm const & Item);				//!< Reinitialise the heap.
		void alter(srl const theSrl, itm const & Item);		//!< Alter an item in the heap.

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
		/*! @name Iterators */
		//! @{

		Itr childLeft(Itr const theItr) const;				//!< Get the left child of an iterator.
		Itr childRight(Itr const theItr) const;				//!< Get the right child of an iterator.
		Itr siblingLeft(Itr const theItr) const;			//!< Get the left sibling of an iterator.
		Itr siblingRight(Itr const theItr) const;			//!< Get the right sibling of an iterator.

		//! @}

		//! @name Peak
		//! @{

		itm const & itemPeak() const;	//!< Get the peak item.
		Itr iteratorPeak() const;		//!< Get the peak iterator.
		srl serialPeak() const;			//!< Get the peak serial.

		//! @}

	private:
		mm    mMemMan;									//!< Memory manager.
		#if ParallelArray
			itm *  mItems;								//!< The items.
			Itr *  mItrs;								//!< The iterators.
		#else
			t2<itm,Itr> * mItmItrs;						//!< The itm-itrs.
		#endif
		srl *  mSrls;									//!< The serials.


};



/*!
	@def qhf
	@brief A macro to denote queuehf.
	@details This macro denotes queuehf.
*/
#define qhf queuehf



/*!
	The constructor.
*/
template<typename itm, typename srl, typename cfn, typename mm>
queuehf<itm,srl,cfn,mm>::queuehf()
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

	CatchError
}



/*!
	The initialiser.
*/
template<typename itm, typename srl, typename cfn, typename mm>
queuehf<itm,srl,cfn,mm>::queuehf(mm const & theMm) : mMemMan(theMm)
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

	CatchError
}



/*!
	The duplicator.
*/
template <typename itm, typename srl, typename cfn, typename mm>
queuehf<itm,srl,cfn,mm>::queuehf(queuehf<itm,srl,cfn,mm> const & that) :
		mMemMan(that.mMemMan)
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
template <typename itm, typename srl, typename cfn, typename mm>
queuehf<itm,srl,cfn,mm>::~queuehf()
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
template <typename itm, typename srl, typename cfn, typename mm>
queuehf<itm,srl,cfn,mm> const & queuehf<itm,srl,cfn,mm>::operator =
		(queuehf<itm,srl,cfn,mm> const & that)
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
template<typename itm, typename srl, typename cfn, typename mm>
inline void queuehf<itm,srl,cfn,mm>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}



/*!
	Clear items, retaining available memory.
*/
template<typename itm, typename srl, typename cfn, typename mm>
inline void queuehf<itm,srl,cfn,mm>::clear()
{
	WatchError

	mMemMan.resetOccupy();

	CatchError
}



/*!
	Clear items, releasing memory when deemed.
*/
template<typename itm, typename srl, typename cfn, typename mm>
inline void queuehf<itm,srl,cfn,mm>::clearMem()
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
	Insert an item at the end, assuming memory available.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline void queuehf<itm,srl,cfn,mm>::insert(itm const & Item)
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
	#else
		mItmItrs[Srl1].Second = Itr1;
	#endif

	CatchError
}



/*!
	Insert an item at the end, acquiring memory when deemed.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline void queuehf<itm,srl,cfn,mm>::insertMem(itm const & Item)
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
	#else
		mItmItrs[Srl1].Second = Itr1;
	#endif

	CatchError
}



/*!
	Insert an item at the end and return the serial, assuming memory available.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline srl queuehf<itm,srl,cfn,mm>::insertSrl(itm const & Item)
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
	#else
		mItmItrs[Srl1].Second = Itr1;
	#endif
	return Srl1;

	CatchError
}




/*!
	Insert an item at the end and return the serial, acquiring memory when deemed.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline srl queuehf<itm,srl,cfn,mm>::insertSrlMem(itm const & Item)
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
	#else
		mItmItrs[Srl1].Second = Itr1;
	#endif

	return Srl1;

	CatchError
}



/*!
	Remove the item from the end of the heap, retaining available memory.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline void queuehf<itm,srl,cfn,mm>::remove()
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

	CatchError
}



/*!
	Remove and return an item from the end of the heap, retaining available memory.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline void queuehf<itm,srl,cfn,mm>::remove(itm & Item)
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

	CatchError
}



/*!
	Remove the item from the end of the heap, releasing memory when deemed.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline void queuehf<itm,srl,cfn,mm>::removeMem()
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

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Remove and return an item from the end of the heap, releasing memory when deemed.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline void queuehf<itm,srl,cfn,mm>::removeMem(itm & Item)
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

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Allocate memory automatically.
*/
template<typename itm, typename srl, typename cfn, typename mm>
void queuehf<itm,srl,cfn,mm>::reallocMemAuto()
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
template<typename itm, typename srl, typename cfn, typename mm>
void queuehf<itm,srl,cfn,mm>::deallocMemAuto()
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
template<typename itm, typename srl, typename cfn, typename mm>
void queuehf<itm,srl,cfn,mm>::adjustMemAuto()
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
	Allocate memory.
*/
template<typename itm, typename srl, typename cfn, typename mm>
void queuehf<itm,srl,cfn,mm>::allocateMem(Dim const Alloc)
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
	Return the number of serial-item pair.
*/
template<typename itm, typename srl, typename cfn, typename mm>
inline Dim queuehf<itm,srl,cfn,mm>::pairCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the memory manager
*/
template<typename itm, typename srl, typename cfn, typename mm>
inline mm const & queuehf<itm,srl,cfn,mm>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	The initialiser.
*/
template<typename itm, typename srl, typename cfn, typename mm>
void queuehf<itm,srl,cfn,mm>::reinitialise(itm const & Item)
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

	CatchError
}



/*!
	Alter an item associated with a serial.
*/
template <typename itm, typename srl, typename cfn, typename mm>
void queuehf<itm,srl,cfn,mm>::alter(srl const theSrl, itm const & Item)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theSrl), eSerialBeyondLimit);

	#if ParallelArray
		mItems[theSrl] = Item;
		Itr Itr1 = mItrs[theSrl], Itr4 = Itr1;
	#else
		mItmItrs[theSrl].First = Item;
		Itr Itr1 = mItmItrs[theSrl].Second, Itr4 = Itr1;
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

	CatchError
}



/*!
	Find the iterator for the serial.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline Itr queuehf<itm,srl,cfn,mm>::findItr(srl const theSrl) const
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
	Get the item in the heap for the serial.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline itm const & queuehf<itm,srl,cfn,mm>::findItem(srl const theSrl) const
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
	Get the serial for a given iterator.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline srl const & queuehf<itm,srl,cfn,mm>::operator[](Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mSrls[theItr];

	CatchError
}



/*!
	Get the item in the heap for the given iterator.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline itm const & queuehf<itm,srl,cfn,mm>::operator()(Itr const theItr) const
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
	Get the serial for a given iterator.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline srl const & queuehf<itm,srl,cfn,mm>::serial(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mSrls[theItr];

	CatchError
}



/*!
	Get the item in the heap for the given iterator.
*/
template <typename itm, typename srl, typename cfn, typename mm>
inline itm const & queuehf<itm,srl,cfn,mm>::item(Itr const theItr) const
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
template<typename itm, typename srl, typename cfn, typename mm>
inline itm const & queuehf<itm,srl,cfn,mm>::itemPeak() const
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
template<typename itm, typename srl, typename cfn, typename mm>
inline srl queuehf<itm,srl,cfn,mm>::serialPeak() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eEmptyCount);

	return mSrls[0];

	CatchError
}


/*!
	Return the peak iterator of the heap
*/
template<typename itm, typename srl, typename cfn, typename mm>
inline Itr queuehf<itm,srl,cfn,mm>::iteratorPeak() const
{
	WatchError

	Warn(mMemMan.emptyOccupied(), eEmptyCount);

	return 0;

	CatchError
}



/*!
	Return the left child of an iterator.
*/
template<typename itm, typename srl, typename cfn, typename mm>
inline Itr queuehf<itm,srl,cfn,mm>::childLeft(Itr const theItr) const
{
	WatchError

	Itr tItr = (theItr << 1) + 1;
	return tItr < mMemMan.occupied() ? tItr : InvItr;

	CatchError
}



/*!
	Return the right child of an iterator.
*/
template<typename itm, typename srl, typename cfn, typename mm>
inline Itr queuehf<itm,srl,cfn,mm>::childRight(Itr const theItr) const
{
	WatchError

	Itr tItr = (theItr << 1) + 2;
	return tItr < mMemMan.occupied() ? tItr : InvItr;

	CatchError
}



/*!
	Return the left sibling of an iterator.
*/
template<typename itm, typename srl, typename cfn, typename mm>
inline Itr queuehf<itm,srl,cfn,mm>::siblingLeft(Itr const theItr) const
{
	WatchError

	return ((theItr & 1) || !theItr) ?  InvItr : theItr - 1;

	CatchError
}



/*!
	Return the right sibling of an iterator.
*/
template<typename itm, typename srl, typename cfn, typename mm>
inline Itr queuehf<itm,srl,cfn,mm>::siblingRight(Itr const theItr) const
{
	WatchError

	return ((theItr & 1) && (theItr + 1) < mMemMan.occupied()) ? theItr + 1 : InvItr;

	CatchError
}



closeEmuSpace



#endif // QueuehfTccIncluded
