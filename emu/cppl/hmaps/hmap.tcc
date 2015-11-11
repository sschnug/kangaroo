/*!
	@file hmap.tcc
	@brief The source file for hmap template class.
	@details This is the source file for hmap template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef HmapTccIncluded
#define HmapTccIncluded



#include "cppl/roots/idx.hpp"
#include "cppl/opfns/idx.hpp"
#include "cppl/tuples/idx.hpp"



openEmuSpace



/*!
	@class hmap
	@brief A class to represent standard hash maps that use closed hashing.
	@details This class represents standard hash maps that use closed hashing.
*/
template <typename kye, typename itm, typename mm,
	typename hfn = hv<kye>, typename eqfn = eq<kye> >
class hmap
{
	public:

		typedef mm MmTyp;									//!< Memory manager type.

		hmap();												//!< Constructor.
		~hmap();											//!< Destructor.
		hmap(mm const & theMm);								//!< Initialiser.
		hmap(hmap<kye,itm,mm,hfn,eqfn> const & that);		//!< Duplicator.
		hmap<kye,itm,mm,hfn,eqfn> const & operator =
				(hmap<kye,itm,mm,hfn,eqfn> const & that);	//!< Assigner.

		//! @name Synchronise
		//! @{

		void syncClk();	//!< Synchronise clock.

		//! @}

		//! @name Clear
		//! @{

		void clear();		//!< Clear key-items, retaining available memory.
		void clearMem();	//!< Clear key-items, releasing memory when deemed.

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

		void remove(kye const & theKey);						//!< Remove a key retaining memory available.
		Bll removeBll(kye const & theKey);						//!< Remove a key and return whether removed or not, retaining memory available.
		Itr removeItr(kye const & theKey);						//!< Remove a key and return the iterator when found, else InvItr, retaining memory available.
		Itr removeItr(kye const & theKey, itm & Item);			//!< Remove a key and return the iterator and item when found, else return InvItr, retaining memory available.

		void removeMem(kye const & theKey);						//!< Remove a key releasing memory when deemed.
		Bll removeBllMem(kye const & theKey);					//!< Remove a key and return whether removed or not, releasing memory when deemed.
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
		Itr * mHome;							//!< Itr of home keys.
		#if ParallelArray
			Itr * mMore;						//!< Itr of successor keys.
			kye * mKeys;						//!< The array of keys.
			itm * mItems;						//!< The array of items.
		#else
			t3<Itr,kye,itm> * mMoreKeyItms;	//!< The array of idx, key, items.
		#endif
};




/*!
	@def hm
	@brief A macro to denote hmap.
	@details This macro denotes hmap.
*/
#define hm hmap



/*!
	The constructor.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmap<kye,itm,mm,hfn,eqfn>::hmap()
{
	WatchError

	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMore[tItr] = InvItr;
	#else
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMoreKeyItms[tItr].First = InvItr;
	#endif

	CatchError
}



/*!
	The initialiser.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmap<kye,itm,mm,hfn,eqfn>::hmap(mm const & theMm) : mMemMan(theMm)
{
	WatchError

	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMore[tItr] = InvItr;
	#else
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMoreKeyItms[tItr].First = InvItr;
	#endif

	CatchError
}




/*!
	The duplicator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmap<kye,itm,mm,hfn,eqfn>::hmap(hmap<kye,itm,mm,hfn,eqfn> const & that) :
		mMemMan(that.mMemMan)
{
	WatchError

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mMore[tItr] = that.mMore[tItr];
			mKeys[tItr] = that.mKeys[tItr];
			mItems[tItr] = that.mItems[tItr];
		}
	#else
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mMoreKeyItms[tItr] = that.mMoreKeyItms[tItr];
		}
	#endif

	CatchError
}



/*!
	The assigner.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmap<kye,itm,mm,hfn,eqfn> const & hmap<kye,itm,mm,hfn,eqfn>::operator =
		(hmap<kye,itm,mm,hfn,eqfn> const & that)
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
		#else
			delete [] mMoreKeyItms;
		#endif

		mHome = new Itr[that.mMemMan.acquired()];
		#if ParallelArray
			mMore = new Itr[that.mMemMan.acquired()];
			mKeys = new kye[that.mMemMan.acquired()];
			mItems = new itm[that.mMemMan.acquired()];
		#else
			mMoreKeyItms = new t3<Itr,kye,itm>[that.mMemMan.acquired()];
		#endif
	}

	mMemMan = that.mMemMan;

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	{
		mHome[tItr] = that.mHome[tItr];
		#if ParallelArray
			mMore[tItr] = that.mMore[tItr];
			mKeys[tItr] = that.mKeys[tItr];
			mItems[tItr] = that.mItems[tItr];
		#else
			mMoreKeyItms[tItr] = that.mMoreKeyItms[tItr];
		#endif
	}
	return *this;

	CatchError
}



/*!
	The destructor.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmap<kye,itm,mm,hfn,eqfn>::~hmap()
{
	WatchError

	delete [] mHome;
	#if ParallelArray
		delete [] mMore;
		delete [] mKeys;
		delete [] mItems;
	#else
		delete [] mMoreKeyItms;
	#endif

	CatchError
}



/*!
	Synchronise clock.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline void hmap<kye,itm,mm,hfn,eqfn>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}



/*!
	Clear the keys, retaining available memory.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmap<kye,itm,mm,hfn,eqfn>::clear()
{
	WatchError

	if (mMemMan.resetOccupyBll())
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			#if ParallelArray
				Itr & tMore = mMore[tItr];
				if (tMore == InvItr) continue;
				if (tMore == mMemMan.acquired())
					mHome[hfn::iof(mKeys[tItr]) % mMemMan.acquired()] = InvItr;
				tMore = InvItr;
			#else
				Itr & tMore = mMoreKeyItms[tItr].First;
				if (tMore == InvItr) continue;
				if (tMore == mMemMan.acquired())
					mHome[hfn::iof(mMoreKeyItms[tItr].Second) % mMemMan.acquired()] = InvItr;
				tMore = InvItr;
			#endif
		}

	CatchError
}



/*!
	Clear the keys, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmap<kye,itm,mm,hfn,eqfn>::clearMem()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			#if ParallelArray
				Itr & tMore = mMore[tItr];
				if (tMore == InvItr) continue;
				if (tMore == mMemMan.acquired())
					mHome[hfn::iof(mKeys[tItr]) % mMemMan.acquired()] = InvItr;
				tMore = InvItr;
			#else
				Itr & tMore = mMoreKeyItms[tItr].First;
				if (tMore == InvItr) continue;
				if (tMore == mMemMan.acquired())
					mHome[hfn::iof(mMoreKeyItms[tItr].Second) % mMemMan.acquired()] = InvItr;
				tMore = InvItr;
			#endif
		}
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}
	CatchError
}



/*!
	Insert a key-item pair, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmap<kye,itm,mm,hfn,eqfn>::insert(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
Bll hmap<kye,itm,mm,hfn,eqfn>::insertBll(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
Bll hmap<kye,itm,mm,hfn,eqfn>::insertBll(kye const & theKey, itm const & Item, Itr & theItr)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
Itr hmap<kye,itm,mm,hfn,eqfn>::insertItr(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
	Insert a key-item pair and return the iterator if the key is new else InvItr, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmap<kye,itm,mm,hfn,eqfn>::insertItrIfNew(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
Itr hmap<kye,itm,mm,hfn,eqfn>::insertItrIfOld(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
	Insert a key-item pair, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmap<kye,itm,mm,hfn,eqfn>::insertMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
Bll hmap<kye,itm,mm,hfn,eqfn>::insertBllMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
Bll hmap<kye,itm,mm,hfn,eqfn>::insertBllMem(kye const & theKey, itm const & Item, Itr & theItr)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
Itr hmap<kye,itm,mm,hfn,eqfn>::insertItrMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
	Insert a key-item pair and return the iterator if the key is new else InvItr, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmap<kye,itm,mm,hfn,eqfn>::insertItrIfNewMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
	Insert a key-item pair and return the iterator if the key is old else InvItr, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmap<kye,itm,mm,hfn,eqfn>::insertItrIfOldMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr3, tDiff = 1;

	if (tItr2 == InvItr)
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
		while(mMore[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMore[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMore[tItr2] = tItr3;

		mMore[tItr3] = mMemMan.acquired();
		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mMoreKeyItms[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeyItms[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
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
	Remove a key, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmap<kye,itm,mm,hfn,eqfn>::remove(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return;
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
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mMore[tItr2] = InvItr;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mMoreKeyItms[tItr2].First = InvItr;
	#endif

	mMemMan.unoccupy();

	CatchError
}


/*!
	Remove a key and return whether successful, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmap<kye,itm,mm,hfn,eqfn>::removeBll(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return false;
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
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mMore[tItr2] = InvItr;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mMoreKeyItms[tItr2].First = InvItr;
	#endif

	mMemMan.unoccupy();

	return true;

	CatchError
}



/*!
	Remove a key and return Itr when found else InvItr, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmap<kye,itm,mm,hfn,eqfn>::removeItr(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return InvItr;
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
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mMore[tItr2] = InvItr;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mMoreKeyItms[tItr2].First = InvItr;
	#endif

	mMemMan.unoccupy();

	return tItr2;

	CatchError
}




/*!
	Remove a key and return Itr when found else InvItr, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmap<kye,itm,mm,hfn,eqfn>::removeItr(kye const & theKey, itm & Item)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return InvItr;
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
		Item = mItems[tItr2];
		if (tItr2 == tItr3)
			if (mMore[tItr2] == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mMore[tItr2] = InvItr;
	#else
		Item = mMoreKeyItms[tItr2].Third;
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mMoreKeyItms[tItr2].First = InvItr;
	#endif

	mMemMan.unoccupy();

	return tItr2;

	CatchError
}



/*!
	Remove a key and return whether successful, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmap<kye,itm,mm,hfn,eqfn>::removeMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return;
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
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mMore[tItr2] = InvItr;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mMoreKeyItms[tItr2].First = InvItr;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Remove a key and return whether successful, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmap<kye,itm,mm,hfn,eqfn>::removeBllMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return false;
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
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mMore[tItr2] = InvItr;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mMoreKeyItms[tItr2].First = InvItr;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	return true;

	CatchError
}



/*!
	Remove a key and return Itr when found else InvItr, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmap<kye,itm,mm,hfn,eqfn>::removeItrMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return InvItr;
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
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mMore[tItr2] = InvItr;
	#else
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mMoreKeyItms[tItr2].First = InvItr;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	return tItr2;

	CatchError
}




/*!
	Remove a key and return Itr when found else InvItr, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmap<kye,itm,mm,hfn,eqfn>::removeItrMem(kye const & theKey, itm & Item)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return InvItr;
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
		Item = mItems[tItr2];
		if (tItr2 == tItr3)
			if (mMore[tItr2] == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMore[tItr2];
		else
			mMore[tItr3] = mMore[tItr2];
		mMore[tItr2] = InvItr;
	#else
		Item = mMoreKeyItms[tItr2].Third;
		if (tItr2 == tItr3)
			if (mMoreKeyItms[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeyItms[tItr2].First;
		else
			mMoreKeyItms[tItr3].First = mMoreKeyItms[tItr2].First;
		mMoreKeyItms[tItr2].First = InvItr;
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
void hmap<kye,itm,mm,hfn,eqfn>::reallocMemAuto()
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

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
	#else
		t3<Itr,kye,itm> * const tMoreKeyItms = mMoreKeyItms;
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	#if ParallelArray
		mHome[tItr] = mMore[tItr] = InvItr;
	#else
		mHome[tItr] = mMoreKeyItms[tItr].First = InvItr;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tMore[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tMoreKeyItms[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tMoreKeyItms[tItr].Second) % mMemMan.acquired();
		#endif

		if (mHome[tItr1] == InvItr)
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mMore[tItr2] != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMore[tItr2] != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mMore[tItr2] = mMemMan.acquired();
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mMoreKeyItms[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMoreKeyItms[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
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

			while(mMore[tItr2] != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMore[tItr2] != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mMore[tItr1] = tItr2;
			mMore[tItr2] = mMemMan.acquired();
			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mMoreKeyItms[tItr1].First != mMemMan.acquired())
				tItr1 = mMoreKeyItms[tItr1].First;

			Itr tDiff = 1;
			Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

			while(mMoreKeyItms[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMoreKeyItms[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

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
	#else
		delete [] tMoreKeyItms;
	#endif

	CatchError
}



/*!
	Deallocate some memory automatically.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmap<kye,itm,mm,hfn,eqfn>::deallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);
	Dim tAcquired = mMemMan.acquired();
	Itr * const tHome = mHome;

	mMemMan.reallocAuto();

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		Itr * const tMore = mMore;
		kye * const tKeys = mKeys;
		itm * const tItms = mItems;

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
	#else
		t3<Itr,kye,itm> * const tMoreKeyItms = mMoreKeyItms;
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		#if ParallelArray
			mHome[tItr] = mMore[tItr] = InvItr;
		#else
			mHome[tItr] = mMoreKeyItms[tItr].First = InvItr;
		#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tMore[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tMoreKeyItms[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tMoreKeyItms[tItr].Second) % mMemMan.acquired();
		#endif

		if (mHome[tItr1] == InvItr)
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mMore[tItr2] != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMore[tItr2] != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mMore[tItr2] = mMemMan.acquired();
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mMoreKeyItms[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMoreKeyItms[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
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
			while(mMore[tItr2] != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMore[tItr2] != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mMore[tItr1] = tItr2;
			mMore[tItr2] = mMemMan.acquired();
			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mMoreKeyItms[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMoreKeyItms[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

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
	#else
		delete [] tMoreKeyItms;
	#endif

	CatchError
}



/*!
	Adjust memory automatically.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmap<kye,itm,mm,hfn,eqfn>::adjustMemAuto()
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

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
	#else
		t3<Itr,kye,itm> * const tMoreKeyItms = mMoreKeyItms;
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
	#endif

	#if ParallelArray
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMore[tItr] = InvItr;
	#else
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMoreKeyItms[tItr].First = InvItr;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tMore[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tMoreKeyItms[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tMoreKeyItms[tItr].Second) % mMemMan.acquired();
		#endif

		if (mHome[tItr1] == InvItr)
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mMore[tItr2] != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMore[tItr2] != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mMore[tItr2] = mMemMan.acquired();
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mMoreKeyItms[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMoreKeyItms[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
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
			while(mMore[tItr2] != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMore[tItr2] != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mMore[tItr1] = tItr2;
			mMore[tItr2] = mMemMan.acquired();
			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mMoreKeyItms[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMoreKeyItms[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

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
	#else
		delete [] tMoreKeyItms;
	#endif

	CatchError
}



/*!
	Allocate memory.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmap<kye,itm,mm,hfn,eqfn>::allocateMem(Dim const Alloc)
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

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
	#else
		t3<Itr,kye,itm> * const tMoreKeyItms = mMoreKeyItms;
		mMoreKeyItms = new t3<Itr,kye,itm>[mMemMan.acquired()];
	#endif

	#if ParallelArray
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMore[tItr] = InvItr;
	#else
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMoreKeyItms[tItr].First = InvItr;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tMore[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tMoreKeyItms[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tMoreKeyItms[tItr].Second) % mMemMan.acquired();
		#endif

		if (mHome[tItr1] == InvItr)
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mMore[tItr2] != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMore[tItr2] != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mMore[tItr2] = mMemMan.acquired();
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mMoreKeyItms[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMoreKeyItms[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
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
			while(mMore[tItr2] != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMore[tItr2] != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mMore[tItr1] = tItr2;
			mMore[tItr2] = mMemMan.acquired();
			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mMoreKeyItms[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMoreKeyItms[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

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
	#else
		delete [] tMoreKeyItms;
	#endif

	CatchError
}



/*!
	Return the key count.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline Dim hmap<kye,itm,mm,hfn,eqfn>::keyCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the slot count.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline Dim hmap<kye,itm,mm,hfn,eqfn>::slotCount() const
{
	WatchError

	return mMemMan.acquired();

	CatchError
}



/*!
	Return the memory manager.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline mm const & hmap<kye,itm,mm,hfn,eqfn>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Return whether the slot at a given iterator is valid.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline Bll hmap<kye,itm,mm,hfn,eqfn>::occupiedSlot(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mMore[theItr] != InvItr;
	#else
		return mMoreKeyItms[theItr].First != InvItr;
	#endif

	CatchError
}



/*!
	Find a key in the map and return the iterator if found, else return InvItr.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmap<kye,itm,mm,hfn,eqfn>::findItr(kye const & theKey) const
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();
	if (mHome[tItr] == InvItr)
		return InvItr;
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
Bll hmap<kye,itm,mm,hfn,eqfn>::findBll(kye const & theKey) const
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();
	if (mHome[tItr] == InvItr)
		return false;
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
inline kye const & hmap<kye,itm,mm,hfn,eqfn>::operator[](Itr const theItr) const
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
inline kye const & hmap<kye,itm,mm,hfn,eqfn>::key(Itr const theItr) const
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
itm const & hmap<kye,itm,mm,hfn,eqfn>::map(kye const & theKey) const
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();

	Warn(mHome[tItr] == InvItr, eKeyNotFound);

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
itm & hmap<kye,itm,mm,hfn,eqfn>::map(kye const & theKey)
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();

	Warn(mHome[tItr] == InvItr, eKeyNotFound);

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
inline itm const & hmap<kye,itm,mm,hfn,eqfn>::operator()(Itr const theItr) const
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
inline itm & hmap<kye,itm,mm,hfn,eqfn>::operator()(Itr const theItr)
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
inline itm const & hmap<kye,itm,mm,hfn,eqfn>::item(Itr const theItr) const
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
inline itm & hmap<kye,itm,mm,hfn,eqfn>::item(Itr const theItr)
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



#endif // HmapTccIncluded
