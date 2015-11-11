/*!
	@file hmapc.tcc
	@brief The source file for hmapc template class.
	@details This is the source file for hmapc template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef HmapcTccIncluded
#define HmapcTccIncluded



#include "cppl/roots/idx.hpp"
#include "cppl/opfns/idx.hpp"
#include "cppl/tuples/idx.hpp"


openEmuSpace



/*!
	@class hmapc
	@brief A class to represent hash hmapc with *clocks* to have efficient clearning.
	@details This class represents hash hmapc with *clocks* to have efficient clearing.
*/
template <typename kye, typename itm, typename mm,
	typename hfn = hv<kye>, typename eqfn = eq<kye> >
class hmapc
{
	public:

		typedef mm MmTyp;										//!< Memory manager type.

		hmapc();												//!< Constructor.
		~hmapc();												//!< Destructor.
		hmapc(mm const & theMm);								//!< Initialiser.
		hmapc(hmapc<kye,itm,mm,hfn,eqfn> const & that);			//!< Duplicator.
		hmapc<kye,itm,mm,hfn,eqfn> const & operator =
					(hmapc<kye,itm,mm,hfn,eqfn> const & that);	//!< Assigner.

		//! @name Synchronise
		//! @{

		void syncClk();	//!< Synchronise clock.

		//! @}

		//! @name Clear
		//! @{

		void clear();							//!< Clear items only when needed, retaining available memory.
		void clear(Clk const theClk);			//!< Clear items only when needed, retaining available memory.
		void clearMust();						//!< Clear item mandatorily, retaining available memory.
		void clearMust(Clk const theClk);		//!< Clear item mandatorily, retaining available memory.

		void clearMem();						//!< Clear items only when needed, releasing memory when deemed.
		void clearMem(Clk const theClk);		//!< Clear items only when needed, releasing memory when deemed.
		void clearMustMem();					//!< Clear item mandatorily, releasing memory when deemed.
		void clearMustMem(Clk const theClk);	//!< Clear item mandatorily, releasing memory when deemed.

		//! @}

		//! @name Insert
		//! @{

		void insert(kye const & theKye, itm const & Item);						//!< Insert a key-item pair, assuming memory available.
		Bll insertBll(kye const & theKye, itm const & Item);					//!< Insert a key-item pair, return whether successful, assuming memory available.
		Bll insertBll(kye const & theKye, itm const & Item, Itr & theItr);		//!< Insert a key-item pair, return whether successful and the iterator, assuming memory available.
		Itr insertItr(kye const & theKey, itm const & Item);					//!< Insert a key-item pair and return the iterator, assuming memory available.
		Itr insertItrIfNew(kye const & theKey, itm const & Item);				//!< Insert a key-item pair and return the iterator if the key is new else InvItr, assuming memory available.
		Itr insertItrIfOld(kye const & theKey, itm const & Item);				//!< Insert a key-item pair and return the iterator if the key is old else InvItr, assuming memory available.

		void insertMem(kye const & theKye, itm const & Item);					//!< Insert a key-item pair, acquiring memory when needed.
		Bll insertBllMem(kye const & theKye, itm const & Item);					//!< Insert a key-item pair, return whether successful, acquiring memory when needed.
		Bll insertBllMem(kye const & theKye, itm const & Item, Itr & theItr);	//!< Insert a key-item pair, return whether successful and the iterator, acquiring memory when needed.
		Itr insertItrMem(kye const & theKey, itm const & Item);					//!< Insert a key-item pair and return the iterator, acquiring memory when needed.
		Itr insertItrIfNewMem(kye const & theKey, itm const & Item);			//!< Insert a key-item pair and return the iterator if the key is new else InvItr, acquiring memory when needed.
		Itr insertItrIfOldMem(kye const & theKey, itm const & Item);			//!< Insert a key-item pair and return the iterator if the key is old else InvItr, acquiring memory when needed.

		//! @}

		/*! @name Remove */
		//! @{

		void remove(kye const & theKey);						//!< Remove a key, retaining memory available.
		Bll removeBll(kye const & theKey);						//!< Remove a key and return whether successful, retaining memory available.
		Itr removeItr(kye const & theKey);						//!< Remove a key and return the iterator when found, else InvItr, retaining memory available.
		Itr removeItr(kye const & theKey, itm & Item);			//!< Remove a key and return the iterator and item when found, else return InvItr, retaining memory available.

		void removeMem(kye const & theKey);						//!< Remove a key, releasing memory when deemed.
		Bll removeBllMem(kye const & theKey);					//!< Remove a key and return whether successful, releasing memory when deemed.
		Itr removeItrMem(kye const & theKey);					//!< Remove a key and return the iterator when found, else InvItr, releasing memory when deemed.
		Itr removeItrMem(kye const & theKey, itm & Item);		//!< Remove a key and return the iterator and item when found, else return InvItr, releasing memory when deemed.

		//! @}

		//! @name Memory
		//! @{

		Dim keyCount() const;					//!< Get key count.
		Dim slotCount() const;					//!< Get slot count.
		mm const & MemMan() const;				//!< Memory manager.

		void reallocMemAuto();					//!< Reallocate memory automatically.
		void deallocMemAuto();					//!< Deallocate memory automatically.
		void adjustMemAuto();					//!< Adjust memory automatically.
		void allocateMem(Dim const Alloc);		//!< Allocate given extent of memory.

		//! @}

		/*! @name Accessors */
		//! @{

		Bll occupiedSlot(Itr const theItr) const;			//!< Whether the slot for the iterator is occupied.

		Itr findItr(kye const & theKey) const;				//!< Find a key and return the iterator if found, else return InvItr.
		Bll findBll(kye const & theKey) const;				//!< Find a key and return whether found.

		kye const & operator[](Itr const theItr) const;		//!< Get the key at the given iterator.
		kye const & key(Itr const theItr) const;			//!< Get the key at the given iterator.

		itm const & map(kye const & theKey) const;			//!< Get the item for the given key.
		itm & map(kye const & theKey);						//!< Get the item for the given key.

		itm const & operator()(Itr const theItr) const;		//!< Get the item at the given iterator.
		itm & operator()(Itr const theItr);					//!< Get the item at the given iterator.
		itm const & item(Itr const theItr) const;			//!< Get the item at the given iterator.
		itm & item(Itr const theItr);						//!< Get the item at the given iterator.

		//! @}

	private:

		mm	  mMemMan;							//!< Memory manager.

		Dim mClk;								//!< Clock of the hmap.
		Itr * mHome;							//!< Itr of home keys.
		#if ParallelArray
			Itr * mMore;						//!< Itr of successor keys.
			kye * mKeys;						//!< The array of keys.
			itm * mItems;						//!< The array of items.
			Clk * mClkHs;						//!< The clocks for home.
			Clk * mClkKs;						//!< The clocks for keys.
		#else
			t3<Itr,kye,itm> * mMoreKeyItms;	//!< The array of idx, key, items.
			t2<Clk,Clk> * mClkHKs;				//!< The clocks for home and keys.
		#endif
};



/*!
	@def hmc
	@brief A macro to denote hmapc.
	@details This macro denotes hmapc.
*/
#define hmc hmapc



/*!
	The constructor.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmapc<kye,itm,mm,hfn,eqfn>::hmapc() : mClk(NotClk)
{
	WatchError
	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];

		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHs[tItr] = mClkKs[tItr] = EndClk;
	#else
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHKs[tItr].First = mClkHKs[tItr].Second = EndClk;
	#endif

	CatchError
}



/*!
	The initialiser.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmapc<kye,itm,mm,hfn,eqfn>::hmapc(mm const & theMm) : mMemMan(theMm), mClk(NotClk)
{
	WatchError
	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];

		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHs[tItr] = mClkKs[tItr] = EndClk;
	#else
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHKs[tItr].First = mClkHKs[tItr].Second = EndClk;
	#endif

	CatchError
}



/*!
	The duplicator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmapc<kye,itm,mm,hfn,eqfn>::hmapc(hmapc<kye,itm,mm,hfn,eqfn> const & that) :
		mMemMan(that.mMemMan), mClk(NotClk)
{
	WatchError

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mMore[tItr] = that.mMore[tItr];
			mKeys[tItr] = that.mKeys[tItr];
			mItems[tItr] = that.mItems[tItr];
			mClkKs[tItr] = that.mClkKs[tItr];
			mClkHs[tItr] = that.mClkHs[tItr];
		}
	#else
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mMoreKeyItms[tItr] = that.mMoreKeyItms[tItr];
			mClkHKs[tItr] = that.mClkHKs[tItr];
		}
	#endif

	CatchError
}



/*!
	The assigner.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmapc<kye,itm,mm,hfn,eqfn> const & hmapc<kye,itm,mm,hfn,eqfn>::operator =
		(hmapc<kye,itm,mm,hfn,eqfn> const & that)
{
	WatchError

	if (this == &that)
		return *this;

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		delete [] mHome;
		#if ParallelArray
			delete [] mMore;
			delete [] mKeys;
			delete [] mItems;
			delete [] mClkHs;
			delete [] mClkKs;
		#else
			delete [] mMoreKeyItms;
			delete [] mClkHKs;
		#endif

		mHome = new Itr[mMemMan.acquired()];
		#if ParallelArray
			mMore = new Itr[that.mMemMan.acquired()];
			mKeys = new kye[that.mMemMan.acquired()];
			mItems = new itm[that.mMemMan.acquired()];
			mClkHs = new Clk[that.mMemMan.acquired()];
			mClkKs = new Clk[that.mMemMan.acquired()];
		#else
			mMoreKeyItms = new t3<Itr,kye,itm>[that.mMemMan.acquired()];
			mClkHKs = new t2<Clk,Clk>[that.mMemMan.acquired()];
		#endif
	}

	mMemMan = that.mMemMan;
	mClk = that.mClk;

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	{
		mHome[tItr] = that.mHome[tItr];
		#if ParallelArray
			mMore[tItr] = that.mMore[tItr];
			mKeys[tItr] = that.mKeys[tItr];
			mItems[tItr] = that.mItems[tItr];
			mClkHs[tItr] = that.mClkHs[tItr];
			mClkKs[tItr] = that.mClkKs[tItr];
		#else
			mMoreKeyItms[tItr] = that.mMoreKeyItms[tItr];
			mClkHKs[tItr] = that.mClkHKs[tItr];
		#endif
	}
	return *this;

	CatchError
}



/*!
	The destructor.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmapc<kye,itm,mm,hfn,eqfn>::~hmapc()
{
	WatchError

	delete [] mHome;
	#if ParallelArray
		delete [] mMore;
		delete [] mKeys;
		delete [] mItems;
		delete [] mClkHs;
		delete [] mClkKs;
	#else
		delete [] mMoreKeyItms;
		delete [] mClkHKs;
	#endif

	CatchError
}



/*!
	Synchronize the clock.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::syncClk()
{
	WatchError

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	{
	#if ParallelArray
		mClkHs[tItr] = (mClkHs[tItr] == mClk) ? NotClk : EndClk;
		mClkKs[tItr] = (mClkKs[tItr] == mClk) ? NotClk : EndClk;
	#else
		mClkHKs[tItr].First = (mClkHKs[tItr].First == mClk) ? NotClk : EndClk;
		mClkHKs[tItr].Second = (mClkHKs[tItr].Second == mClk) ? NotClk : EndClk;
	#endif
	}
	mClk = NotClk;

	CatchError
}



/*!
	Clear the map only when needed, retaining available memory.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::clear()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		if (++mClk == EndClk)
		{
			for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			{
			#if ParallelArray
				mClkHs[tItr] = (mClkHs[tItr] == mClk) ? NotClk : EndClk;
				mClkKs[tItr] = (mClkKs[tItr] == mClk) ? NotClk : EndClk;
			#else
				mClkHKs[tItr].First = (mClkHKs[tItr].First == mClk) ? NotClk : EndClk;
				mClkHKs[tItr].Second = (mClkHKs[tItr].Second == mClk) ? NotClk : EndClk;
			#endif
			}
			mClk = MinClk;
		}
	}

	CatchError
}



/*!
	Clear the map mandatorily, retaining available memory.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::clearMust()
{
	WatchError

	mMemMan.resetOccupy();
	if (++mClk == EndClk)
	{
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
		#if ParallelArray
			mClkHs[tItr] = (mClkHs[tItr] == mClk) ? NotClk : EndClk;
			mClkKs[tItr] = (mClkKs[tItr] == mClk) ? NotClk : EndClk;
		#else
			mClkHKs[tItr].First = (mClkHKs[tItr].First == mClk) ? NotClk : EndClk;
			mClkHKs[tItr].Second = (mClkHKs[tItr].Second == mClk) ? NotClk : EndClk;
		#endif
		}
		mClk = MinClk;
	}

	CatchError
}



/*!
	Clear the map only when needed, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::clearMem()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		if (++mClk == EndClk)
		{
			for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			{
			#if ParallelArray
				mClkHs[tItr] = (mClkHs[tItr] == mClk) ? NotClk : EndClk;
				mClkKs[tItr] = (mClkKs[tItr] == mClk) ? NotClk : EndClk;
			#else
				mClkHKs[tItr].First = (mClkHKs[tItr].First == mClk) ? NotClk : EndClk;
				mClkHKs[tItr].Second = (mClkHKs[tItr].Second == mClk) ? NotClk : EndClk;
			#endif
			}
			mClk = MinClk;
		}

		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}

	CatchError
}



/*!
	Clear the map only when needed, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::clearMustMem()
{
	WatchError

	if (++mClk == EndClk)
	{
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
		#if ParallelArray
			mClkHs[tItr] = (mClkHs[tItr] == mClk) ? NotClk : EndClk;
			mClkKs[tItr] = (mClkKs[tItr] == mClk) ? NotClk : EndClk;
		#else
			mClkHKs[tItr].First = (mClkHKs[tItr].First == mClk) ? NotClk : EndClk;
			mClkHKs[tItr].Second = (mClkHKs[tItr].Second == mClk) ? NotClk : EndClk;
		#endif
		}
		mClk = MinClk;
	}

	if (mMemMan.resetOccupyBll())
	{
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}
	CatchError
}



/*!
	Clear the map only when needed, retaining available memory.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::clear(Clk const theClk)
{
	WatchError

	Warn(mClk == theClk, eClockConflict);
	if (mMemMan.resetOccupyBll())
		mClk = theClk;

	CatchError
}



/*!
	Clear the map only mandatorily, retaining available memory.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::clearMust(Clk const theClk)
{
	WatchError

	Warn(mClk == theClk, eClockConflict);
	mMemMan.resetOccupy();
	mClk = theClk;

	CatchError
}



/*!
	Clear the map only when needed, releasing memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::clearMem(Clk const theClk)
{
	WatchError

	Warn(mClk == theClk, eClockConflict);
	if (mMemMan.resetOccupyBll())
	{
		mClk = theClk;
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}

	CatchError
}



/*!
	Clear the map mandatorily, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::clearMustMem(Clk const theClk)
{
	WatchError

	Warn(mClk == theClk, eClockConflict);

	mMemMan.resetOccupy();
	mClk = theClk;
	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Insert a key-item pair, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::insert(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return;
				if (mMore[tItr2] == mMemMan.acquired()) break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
					return;
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif
	mMemMan.reoccupy();
	CatchError
}



/*!
	Insert a key-item pair and return whether successful, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapc<kye,itm,mm,hfn,eqfn>::insertBll(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return false;
				if (mMore[tItr2] == mMemMan.acquired()) break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
					return false;
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif
	mMemMan.reoccupy();
	return true;

	CatchError
}



/*!
	Insert a key-item pair and return whether successful and the iterator, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapc<kye,itm,mm,hfn,eqfn>::insertBll(kye const & theKey, itm const & Item, Itr & theItr)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mMore[tItr2] == mMemMan.acquired()) break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif
	mMemMan.reoccupy();
	theItr = tItr3;
	return true;

	CatchError
}



/*!
	Insert a key-item pair and return the iterator, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapc<kye,itm,mm,hfn,eqfn>::insertItr(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return tItr2;
				if (mMore[tItr2] == mMemMan.acquired())
					break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
					return tItr2;
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif

	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key-item pair and return the iterator if the key is old else InvItr, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapc<kye,itm,mm,hfn,eqfn>::insertItrIfOld(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return tItr2;
				if (mMore[tItr2] == mMemMan.acquired())
					break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
					return tItr2;
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif
	mMemMan.reoccupy();
	return InvItr;

	CatchError
}



/*!
	Insert a key-item pair and return the iterator if the key is new else InvItr, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapc<kye,itm,mm,hfn,eqfn>::insertItrIfNew(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return InvItr;
				if (mMore[tItr2] == mMemMan.acquired())
					break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
					return InvItr;
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key-item pair and return whether successful, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::insertMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return;
				if (mMore[tItr2] == mMemMan.acquired()) break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
					return;
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif
	mMemMan.reoccupy();

	CatchError
}



/*!
	Insert a key-item pair and return whether successful, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapc<kye,itm,mm,hfn,eqfn>::insertBllMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return false;
				if (mMore[tItr2] == mMemMan.acquired()) break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
					return false;
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif
	mMemMan.reoccupy();
	return true;

	CatchError
}



/*!
	Insert a key-item pair and return whether successful and the iterator, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapc<kye,itm,mm,hfn,eqfn>::insertBllMem(kye const & theKey, itm const & Item, Itr & theItr)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mMore[tItr2] == mMemMan.acquired()) break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif
	mMemMan.reoccupy();
	theItr = tItr3;
	return true;

	CatchError
}



/*!
	Insert a key-item pair and return the iterator, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapc<kye,itm,mm,hfn,eqfn>::insertItrMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return tItr2;
				if (mMore[tItr2] == mMemMan.acquired())
					break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
					return tItr2;
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif

	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key-item pair and return the iterator if the key is old else InvItr, acquring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapc<kye,itm,mm,hfn,eqfn>::insertItrIfOldMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return tItr2;
				if (mMore[tItr2] == mMemMan.acquired())
					break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
					return tItr2;
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif
	mMemMan.reoccupy();
	return InvItr;

	CatchError
}



/*!
	Insert a key-item pair and return the iterator if the key is new else InvItr, acquiring memory when need.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapc<kye,itm,mm,hfn,eqfn>::insertItrIfNewMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	#if ParallelArray
		if (mClkHs[tItr1] != mClk)
	#else
		if (mClkHKs[tItr1].First != mClk)
	#endif
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return InvItr;
				if (mMore[tItr2] == mMemMan.acquired())
					break;
				tItr2 = mMore[tItr2];
			#else
				if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
					return InvItr;
				if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeyItms[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
			mHome[tItr1] = tItr3;
		else
			mMoreKeyItms[tItr2].First = tItr3;

		mMoreKeyItms[tItr3].First = mMemMan.acquired();
		mMoreKeyItms[tItr3].Second = theKey;
		mMoreKeyItms[tItr3].Third = Item;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Remove a key in the map, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::remove(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return;
	#else
		if (mClkHKs[tItr1].First != mClk) return;
	#endif
	Itr tItr3 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mMore[tItr2] == mMemMan.acquired())
				return;
			tItr3 = tItr2;
			tItr2 = mMore[tItr2];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
				break;
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				return;
			tItr3 = tItr2;
			tItr2 = mMoreKeyItms[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (tItr2 == tItr3)
			if (mMore[tItr2] == mMemMan.acquired())
				mClkHs[tItr1] = NotClk;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mClkKs[tItr2] = NotClk;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mClkHKs[tItr1].First = NotClk;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mClkHKs[tItr2].Second = NotClk;
	#endif
	mMemMan.unoccupy();

	CatchError
}


/*!
	Remove a key in the map and return whether successful, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapc<kye,itm,mm,hfn,eqfn>::removeBll(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return false;
	#else
		if (mClkHKs[tItr1].First != mClk) return false;
	#endif
	Itr tItr3 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mMore[tItr2] == mMemMan.acquired())
				return false;
			tItr3 = tItr2;
			tItr2 = mMore[tItr2];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
				break;
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				return false;
			tItr3 = tItr2;
			tItr2 = mMoreKeyItms[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (tItr2 == tItr3)
			if (mMore[tItr2] == mMemMan.acquired())
				mClkHs[tItr1] = NotClk;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mClkKs[tItr2] = NotClk;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mClkHKs[tItr1].First = NotClk;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mClkHKs[tItr2].Second = NotClk;
	#endif
	mMemMan.unoccupy();
	return true;

	CatchError
}



/*!
	Remove a key in the map and return the iterator when found else return InvItr, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapc<kye,itm,mm,hfn,eqfn>::removeItr(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return InvItr;
	#else
		if (mClkHKs[tItr1].First != mClk) return InvItr;
	#endif
	Itr tItr3 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mMore[tItr2] == mMemMan.acquired())
				return InvItr;
			tItr3 = tItr2;
			tItr2 = mMore[tItr2];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
				break;
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				return InvItr;
			tItr3 = tItr2;
			tItr2 = mMoreKeyItms[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (tItr2 == tItr3)
			if (mMore[tItr2] == mMemMan.acquired())
				mClkHs[tItr1] = NotClk;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mClkKs[tItr2] = NotClk;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mClkHKs[tItr1].First = NotClk;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mClkHKs[tItr2].Second = NotClk;
	#endif
	mMemMan.unoccupy();
	return tItr2;

	CatchError
}



/*!
	Remove a key in the map and return the iterator and the item when found else return InvItr, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapc<kye,itm,mm,hfn,eqfn>::removeItr(kye const & theKey, itm & Item)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
	if (mClkHs[tItr1] != mClk) return InvItr;
	#else
	if (mClkHKs[tItr1].First != mClk) return InvItr;
	#endif
	Itr tItr3 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mMore[tItr2] == mMemMan.acquired())
				return false;
			tItr3 = tItr2;
			tItr2 = mMore[tItr2];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
				break;
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				return false;
			tItr3 = tItr2;
			tItr2 = mMoreKeyItms[tItr2].First;
		#endif
	}
	#if ParallelArray
		Item = mItems[tItr2];
		if (tItr2 == tItr3)
			if (mMore[tItr2] == mMemMan.acquired())
				mClkHs[tItr1] = NotClk;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mClkKs[tItr2] = NotClk;
	#else
		Item = mMoreKeyItms[tItr2].Third;
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mClkHKs[tItr1].First = NotClk;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mClkHKs[tItr2].Second = NotClk;
	#endif

	mMemMan.unoccupy();
	return tItr2;

	CatchError
}



/*!
	Remove a key in the map, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::removeMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return;
	#else
		if (mClkHKs[tItr1].First != mClk) return;
	#endif
	Itr tItr3 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mMore[tItr2] == mMemMan.acquired())
				return;
			tItr3 = tItr2;
			tItr2 = mMore[tItr2];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
				break;
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				return;
			tItr3 = tItr2;
			tItr2 = mMoreKeyItms[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (tItr2 == tItr3)
			if (mMore[tItr2] == mMemMan.acquired())
				mClkHs[tItr1] = NotClk;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mClkKs[tItr2] = NotClk;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mClkHKs[tItr1].First = NotClk;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mClkHKs[tItr2].Second = NotClk;
	#endif
	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Remove a key in the map and return whether successful, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapc<kye,itm,mm,hfn,eqfn>::removeBllMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return false;
	#else
		if (mClkHKs[tItr1].First != mClk) return false;
	#endif
	Itr tItr3 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mMore[tItr2] == mMemMan.acquired())
				return false;
			tItr3 = tItr2;
			tItr2 = mMore[tItr2];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
				break;
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				return false;
			tItr3 = tItr2;
			tItr2 = mMoreKeyItms[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (tItr2 == tItr3)
			if (mMore[tItr2] == mMemMan.acquired())
				mClkHs[tItr1] = NotClk;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mClkKs[tItr2] = NotClk;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mClkHKs[tItr1].First = NotClk;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mClkHKs[tItr2].Second = NotClk;
	#endif
	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	return true;

	CatchError
}



/*!
	Remove a key in the map and return the iterator when found else return InvItr, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapc<kye,itm,mm,hfn,eqfn>::removeItrMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return InvItr;
	#else
		if (mClkHKs[tItr1].First != mClk) return InvItr;
	#endif
	Itr tItr3 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mMore[tItr2] == mMemMan.acquired())
				return InvItr;
			tItr3 = tItr2;
			tItr2 = mMore[tItr2];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
				break;
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				return InvItr;
			tItr3 = tItr2;
			tItr2 = mMoreKeyItms[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (tItr2 == tItr3)
			if (mMore[tItr2] == mMemMan.acquired())
				mClkHs[tItr1] = NotClk;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mClkKs[tItr2] = NotClk;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mClkHKs[tItr1].First = NotClk;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mClkHKs[tItr2].Second = NotClk;
	#endif
	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	return tItr2;

	CatchError
}



/*!
	Remove a key in the map and return the iterator and the item when found else return InvItr, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapc<kye,itm,mm,hfn,eqfn>::removeItrMem(kye const & theKey, itm & Item)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
	if (mClkHs[tItr1] != mClk) return InvItr;
	#else
	if (mClkHKs[tItr1].First != mClk) return InvItr;
	#endif
	Itr tItr3 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mMore[tItr2] == mMemMan.acquired())
				return false;
			tItr3 = tItr2;
			tItr2 = mMore[tItr2];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr2].Second, theKey))
				break;
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				return false;
			tItr3 = tItr2;
			tItr2 = mMoreKeyItms[tItr2].First;
		#endif
	}
	#if ParallelArray
		Item = mItems[tItr2];
		if (tItr2 == tItr3)
			if (mMore[tItr2] == mMemMan.acquired())
				mClkHs[tItr1] = NotClk;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mClkKs[tItr2] = NotClk;
	#else
		Item = mMoreKeyItms[tItr2].Third;
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mClkHKs[tItr1].First = NotClk;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mClkHKs[tItr2].Second = NotClk;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	return tItr2;

	CatchError
}



/*!
	Reallocate memory automatically.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::reallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);

	Dim tAcquired = mMemMan.acquired();
	Itr * const tHome = mHome;

	mMemMan.reallocAuto();

	mHome = new Itr[mMemMan.acquired()];

	#if ParallelArray
		Itr * const tMore = mMore;
		kye * const tKeys = mKeys;
		itm * const tItms = mItems;
		Clk * const tClkHs = mClkHs;
		Clk * const tClkKs = mClkKs;

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];
	#else
		t3<Itr,kye,itm> * const tMoreKeyItms = mMoreKeyItms;
		t2<Clk,Clk> * const tClkHKs = mClkHKs;
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	#if ParallelArray
		mClkHs[tItr] = mClkKs[tItr] = EndClk;
	#else
		mClkHKs[tItr].First = mClkHKs[tItr].Second = EndClk;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tClkKs[tItr] != mClk) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tClkHKs[tItr].Second != mClk) continue;
			Itr tItr1 = hfn::iof(tMoreKeyItms[tItr].Second) % mMemMan.acquired();
		#endif

		#if ParallelArray
		if (mClkHs[tItr] != mClk)
		#else
		if (mClkHKs[tItr].First != mClk)
		#endif
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkKs[tItr2] == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHs[tItr1] = mClk;
				mClkKs[tItr2] = mClk;
				mMore[tItr2] = mMemMan.acquired();
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkHKs[tItr2].Second == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHKs[tItr1].First = mClk;
				mClkHKs[tItr2].Second = mClk;
				mMoreKeyItms[tItr2].First = mMemMan.acquired();
				mMoreKeyItms[tItr2].Second = tMoreKeyItms[tItr].Second;
				mMoreKeyItms[tItr2].Third = tMoreKeyItms[tItr].Third;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];

		#if ParallelArray
			while(mMore[tItr1] != mMemMan.acquired())
				tItr1 = mMore[tItr1];

			Itr tDiff = 1;
			Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

			while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkKs[tItr2] == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkKs[tItr2] = mClk;
			mMore[tItr1] = tItr2;
			mMore[tItr2] = mMemMan.acquired();
			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mMoreKeyItms[tItr1].First != mMemMan.acquired())
				tItr1 = mMoreKeyItms[tItr1].First;

			Itr tDiff = 1;
			Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

			while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkHKs[tItr2].Second == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkHKs[tItr2].Second = mClk;
			mMoreKeyItms[tItr1].First = tItr2;
			mMoreKeyItms[tItr2].First = mMemMan.acquired();
			mMoreKeyItms[tItr2].Second = tMoreKeyItms[tItr].Second;
			mMoreKeyItms[tItr2].Third = tMoreKeyItms[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tMore;
		delete [] tKeys;
		delete [] tItms;
		delete [] tClkHs;
		delete [] tClkKs;
	#else
		delete [] tMoreKeyItms;
		delete [] tClkHKs;
	#endif

	CatchError
}



/*!
	Deallocate memory automatically.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::deallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);

	Dim tAcquired = mMemMan.acquired();
	Itr * const tHome = mHome;

	mMemMan.deallocAuto();

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		Itr * const tMore = mMore;
		kye * const tKeys = mKeys;
		itm * const tItms = mItems;
		Clk * const tClkHs = mClkHs;
		Clk * const tClkKs = mClkKs;

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];
	#else
		t3<Itr,kye,itm> * const tMoreKeyItms = mMoreKeyItms;
		t2<Clk,Clk> * const tClkHKs = mClkHKs;
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	#if ParallelArray
		mClkHs[tItr] = mClkKs[tItr] = EndClk;
	#else
		mClkHKs[tItr].First = mClkHKs[tItr].Second = EndClk;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tClkKs[tItr] != mClk) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tClkHKs[tItr].Second != mClk) continue;
			Itr tItr1 = hfn::iof(tMoreKeyItms[tItr].Second) % mMemMan.acquired();
		#endif

		#if ParallelArray
		if (mClkHs[tItr] != mClk)
		#else
		if (mClkHKs[tItr].First != mClk)
		#endif
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkKs[tItr2] == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHs[tItr1] = mClk;
				mClkKs[tItr2] = mClk;
				mMore[tItr2] = mMemMan.acquired();
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkHKs[tItr2].Second == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHKs[tItr1].First = mClk;
				mClkHKs[tItr2].Second = mClk;
				mMoreKeyItms[tItr2].First = mMemMan.acquired();
				mMoreKeyItms[tItr2].Second = tMoreKeyItms[tItr].Second;
				mMoreKeyItms[tItr2].Third = tMoreKeyItms[tItr].Third;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		#if ParallelArray
			while(mMore[tItr1] != mMemMan.acquired())
				tItr1 = mMore[tItr1];
		#else
			while(mMoreKeyItms[tItr1].First != mMemMan.acquired())
				tItr1 = mMoreKeyItms[tItr1].First;
		#endif

		Itr tDiff = 1;
		Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

		#if ParallelArray
			while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkKs[tItr2] == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkKs[tItr2] = mClk;
			mMore[tItr1] = tItr2;
			mMore[tItr2] = mMemMan.acquired();
			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkHKs[tItr2].Second == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkHKs[tItr2].Second = mClk;
			mMoreKeyItms[tItr1].First = tItr2;
			mMoreKeyItms[tItr2].First = mMemMan.acquired();
			mMoreKeyItms[tItr2].Second = tMoreKeyItms[tItr].Second;
			mMoreKeyItms[tItr2].Third = tMoreKeyItms[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tMore;
		delete [] tKeys;
		delete [] tItms;
		delete [] tClkHs;
		delete [] tClkKs;
	#else
		delete [] tMoreKeyItms;
		delete [] tClkHKs;
	#endif

	CatchError
}



/*!
	Adjust memory automatically.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::adjustMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);

	Dim tAcquired = mMemMan.acquired();
	Itr * const tHome = mHome;

	mMemMan.adjustAuto();

	mHome = new Itr[mMemMan.acquired()];

	#if ParallelArray
		Itr * const tMore = mMore;
		kye * const tKeys = mKeys;
		itm * const tItms = mItems;
		Clk * const tClkHs = mClkHs;
		Clk * const tClkKs = mClkKs;

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];
	#else
		t3<Itr,kye,itm> * const tMoreKeyItms = mMoreKeyItms;
		t2<Clk,Clk> * const tClkHKs = mClkHKs;
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	#if ParallelArray
		mClkHs[tItr] = mClkKs[tItr] = EndClk;
	#else
		mClkHKs[tItr].First = mClkHKs[tItr].Second = EndClk;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tClkKs[tItr] != mClk) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tClkHKs[tItr].Second != mClk) continue;
			Itr tItr1 = hfn::iof(tMoreKeyItms[tItr].Second) % mMemMan.acquired();
		#endif

		#if ParallelArray
		if (mClkHs[tItr] != mClk)
		#else
		if (mClkHKs[tItr].First != mClk)
		#endif
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkKs[tItr2] == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHs[tItr1] = mClk;
				mClkKs[tItr2] = mClk;
				mMore[tItr2] = mMemMan.acquired();
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkHKs[tItr2].Second == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHKs[tItr1].First = mClk;
				mClkHKs[tItr2].Second = mClk;
				mMoreKeyItms[tItr2].First = mMemMan.acquired();
				mMoreKeyItms[tItr2].Second = tMoreKeyItms[tItr].Second;
				mMoreKeyItms[tItr2].Third = tMoreKeyItms[tItr].Third;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		#if ParallelArray
			while(mMore[tItr1] != mMemMan.acquired())
				tItr1 = mMore[tItr1];
		#else
			while(mMoreKeyItms[tItr1].First != mMemMan.acquired())
				tItr1 = mMoreKeyItms[tItr1].First;
		#endif

		Itr tDiff = 1;
		Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

		#if ParallelArray
			while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkKs[tItr2] == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkKs[tItr2] = mClk;
			mMore[tItr1] = tItr2;
			mMore[tItr2] = mMemMan.acquired();
			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkHKs[tItr2].Second == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkHKs[tItr2].Second = mClk;
			mMoreKeyItms[tItr1].First = tItr2;
			mMoreKeyItms[tItr2].First = mMemMan.acquired();
			mMoreKeyItms[tItr2].Second = tMoreKeyItms[tItr].Second;
			mMoreKeyItms[tItr2].Third = tMoreKeyItms[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tMore;
		delete [] tKeys;
		delete [] tItms;
		delete [] tClkHs;
		delete [] tClkKs;
	#else
		delete [] tMoreKeyItms;
		delete [] tClkHKs;
	#endif

	CatchError
}



/*!
	Allocate memory.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapc<kye,itm,mm,hfn,eqfn>::allocateMem(Dim const Alloc)
{
	WatchError

	if (!mMemMan.mismatchAlloc(Alloc)) return;

	Dim tAcquired = mMemMan.acquired();
	Itr * const tHome = mHome;

	mMemMan.allocate(Alloc);

	mHome = new Itr[mMemMan.acquired()];

	#if ParallelArray
		Itr * const tMore = mMore;
		kye * const tKeys = mKeys;
		itm * const tItms = mItems;
		Clk * const tClkHs = mClkHs;
		Clk * const tClkKs = mClkKs;

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];
	#else
		t3<Itr,kye,itm> * const tMoreKeyItms = mMoreKeyItms;
		t2<Clk,Clk> * const tClkHKs = mClkHKs;
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	#if ParallelArray
		mClkHs[tItr] = mClkKs[tItr] = EndClk;
	#else
		mClkHKs[tItr].First = mClkHKs[tItr].Second = EndClk;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tClkKs[tItr] != mClk) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tClkHKs[tItr].Second != mClk) continue;
			Itr tItr1 = hfn::iof(tMoreKeyItms[tItr].Second) % mMemMan.acquired();
		#endif

		#if ParallelArray
		if (mClkHs[tItr] != mClk)
		#else
		if (mClkHKs[tItr].First != mClk)
		#endif
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkKs[tItr2] == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHs[tItr1] = mClk;
				mClkKs[tItr2] = mClk;
				mMore[tItr2] = mMemMan.acquired();
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkHKs[tItr2].Second == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHKs[tItr1].First = mClk;
				mClkHKs[tItr2].Second = mClk;
				mMoreKeyItms[tItr2].First = mMemMan.acquired();
				mMoreKeyItms[tItr2].Second = tMoreKeyItms[tItr].Second;
				mMoreKeyItms[tItr2].Third = tMoreKeyItms[tItr].Third;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		#if ParallelArray
			while(mMore[tItr1] != mMemMan.acquired())
				tItr1 = mMore[tItr1];
		#else
			while(mMoreKeyItms[tItr1].First != mMemMan.acquired())
				tItr1 = mMoreKeyItms[tItr1].First;
		#endif

		Itr tDiff = 1;
		Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

		#if ParallelArray
			while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkKs[tItr2] == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkKs[tItr2] = mClk;
			mMore[tItr1] = tItr2;
			mMore[tItr2] = mMemMan.acquired();
			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkHKs[tItr2].Second == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkHKs[tItr2].Second = mClk;
			mMoreKeyItms[tItr1].First = tItr2;
			mMoreKeyItms[tItr2].First = mMemMan.acquired();
			mMoreKeyItms[tItr2].Second = tMoreKeyItms[tItr].Second;
			mMoreKeyItms[tItr2].Third = tMoreKeyItms[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tMore;
		delete [] tKeys;
		delete [] tItms;
		delete [] tClkHs;
		delete [] tClkKs;
	#else
		delete [] tMoreKeyItms;
		delete [] tClkHKs;
	#endif

	CatchError
}



/*!
	Return the key count.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline Dim hmapc<kye,itm,mm,hfn,eqfn>::keyCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the slot count.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline Dim hmapc<kye,itm,mm,hfn,eqfn>::slotCount() const
{
	WatchError

	return mMemMan.acquired();

	CatchError
}



/*!
	Return the memory manager.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline mm const & hmapc<kye,itm,mm,hfn,eqfn>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Return whether the slot at a given iterator is valid.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline Bll hmapc<kye,itm,mm,hfn,eqfn>::occupiedSlot(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mClkKs[theItr] == mClk;
	#else
		return mClkHKs[theItr].Second == mClk;
	#endif

	CatchError
}



/*!
	Find a key in the map and return the iterator if found, else return InvItr.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapc<kye,itm,mm,hfn,eqfn>::findItr(kye const & theKey) const
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();
	#if ParallelArray
		if (mClkHs[tItr] != mClk) return InvItr;
	#else
		if (mClkHKs[tItr].First != mClk) return InvItr;
	#endif
	tItr = mHome[tItr];
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr], theKey))
				return tItr;
			if (mMore[tItr] == mMemMan.acquired())
				return InvItr;
			tItr = mMore[tItr];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr].Second, theKey))
				return tItr;
			if (mMoreKeyItms[tItr].First == mMemMan.acquired())
				return InvItr;
			tItr = mMoreKeyItms[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Find a key in the map and return whether found.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapc<kye,itm,mm,hfn,eqfn>::findBll(kye const & theKey) const
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();
	#if ParallelArray
	if (mClkHs[tItr] != mClk) return false;
	#else
	if (mClkHKs[tItr].First != mClk) return false;
	#endif

	tItr = mHome[tItr];
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr], theKey))
				return true;
			if (mMore[tItr] == mMemMan.acquired())
				return false;
			tItr = mMore[tItr];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr].Second, theKey))
				return true;
			if (mMoreKeyItms[tItr].First == mMemMan.acquired())
				return false;
			tItr = mMoreKeyItms[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Return a key at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline kye const & hmapc<kye,itm,mm,hfn,eqfn>::operator[](Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		Warn(mMore[theItr] == InvItr, eMemorySlotUnoccupied);
		return mKeys[theItr];
	#else
		Warn(mMoreKeyItms[theItr].First == InvItr, eMemorySlotUnoccupied);
		return mMoreKeyItms[theItr].Second;
	#endif

	CatchError
}



/*!
	Return a key at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline kye const & hmapc<kye,itm,mm,hfn,eqfn>::key(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		Warn(mMore[theItr] == InvItr, eMemorySlotUnoccupied);
		return mKeys[theItr];
	#else
		Warn(mMoreKeyItms[theItr].First == InvItr, eMemorySlotUnoccupied);
		return mMoreKeyItms[theItr].Second;
	#endif

	CatchError
}



/*!
	Return data for the key, or throw an error if not exists.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
itm const & hmapc<kye,itm,mm,hfn,eqfn>::map(kye const & theKey) const
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();

	#if ParallelArray
		Warn(mClkHs[tItr] != mClk, eKeyNotFound);
	#else
		Warn(mClkHKs[tItr].First != mClk, eKeyNotFound);
	#endif

	tItr = mHome[tItr];
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr], theKey))
				return mItems[tItr];

			Warn(mMore[tItr] == mMemMan.acquired(), eKeyNotFound);

			tItr = mMore[tItr];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr].Second, theKey))
				return mMoreKeyItms[tItr].Third;

			Warn(mMoreKeyItms[tItr].First == mMemMan.acquired(), eKeyNotFound);

			tItr = mMoreKeyItms[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Return data for the key, or throw an error if not exists.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
itm & hmapc<kye,itm,mm,hfn,eqfn>::map(kye const & theKey)
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();

	#if ParallelArray
	Warn(mClkHs[tItr] != mClk, eKeyNotFound);
	#else
	Warn(mClkHKs[tItr].First != mClk, eKeyNotFound);
	#endif

	tItr = mHome[tItr];
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr], theKey))
				return mItems[tItr];

			Warn(mMore[tItr] == mMemMan.acquired(), eKeyNotFound);

			tItr = mMore[tItr];
		#else
			if (eqfn::iof(mMoreKeyItms[tItr].Second, theKey))
				return mMoreKeyItms[tItr].Third;

			Warn(mMoreKeyItms[tItr].First == mMemMan.acquired(), eKeyNotFound);

			tItr = mMoreKeyItms[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Return the item at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline itm const & hmapc<kye,itm,mm,hfn,eqfn>::operator()(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		Warn(mMore[theItr] == InvItr, eMemorySlotUnoccupied);
		return mItems[theItr];
	#else
		Warn(mMoreKeyItms[theItr].First == InvItr, eMemorySlotUnoccupied);
		return mMoreKeyItms[theItr].Third;
	#endif

	CatchError
}



/*!
	Return the item at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline itm & hmapc<kye,itm,mm,hfn,eqfn>::operator()(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		Warn(mMore[theItr] == InvItr, eMemorySlotUnoccupied);
		return mItems[theItr];
	#else
		Warn(mMoreKeyItms[theItr].First == InvItr, eMemorySlotUnoccupied);
		return mMoreKeyItms[theItr].Third;
	#endif

	CatchError
}



/*!
	Return the item at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline itm const & hmapc<kye,itm,mm,hfn,eqfn>::item(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		Warn(mMore[theItr] == InvItr, eMemorySlotUnoccupied);
		return mItems[theItr];
	#else
		Warn(mMoreKeyItms[theItr].First == InvItr, eMemorySlotUnoccupied);
		return mMoreKeyItms[theItr].Third;
	#endif

	CatchError
}



/*!
	Return the item at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline itm & hmapc<kye,itm,mm,hfn,eqfn>::item(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		Warn(mMore[theItr] == InvItr, eMemorySlotUnoccupied);
		return mItems[theItr];
	#else
		Warn(mMoreKeyItms[theItr].First == InvItr, eMemorySlotUnoccupied);
		return mMoreKeyItms[theItr].Third;
	#endif

	CatchError
}



closeEmuSpace



#endif // HmapcTccIncluded
