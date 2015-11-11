/*!
	@file hmapd.tcc
	@brief The source file for hmapd template class.
	@details This is the source file for hmapd template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef HmapdTccIncluded
#define HmapdTccIncluded



#include "cppl/roots/idx.hpp"
#include "cppl/opfns/idx.hpp"
#include "cppl/tuples/idx.hpp"


openEmuSpace



/*!
	@class hmapd
	@brief A class to represent hash maps with *doubly* linked list to have fast remove after find.
	@details This class represents hash maps with *doubly* linked list to have fast remove after find.
*/
template <typename kye, typename itm, typename mm,
typename hfn = hv<kye>, typename eqfn = eq<kye> >
class hmapd
{
	public:

		typedef mm MmTyp;									//!< Memory manager type.

		hmapd();											//!< Constructor.
		~hmapd();											//!< Destructor.
		hmapd(mm const & theMm);							//!< Initialiser.
		hmapd(hmapd<kye,itm,mm,hfn,eqfn> const & that);		//!< Duplicator.
		hmapd<kye,itm,mm,hfn,eqfn> const & operator =
				(hmapd<kye,itm,mm,hfn,eqfn> const & that);	//!< Assigner.

		//! @name Synchronise
		//! @{

		void syncClk();	//!< Synchronise clock.

		//! @}

		//! @name Clear
		//! @{

		void clear();							//!< Clear items only when needed, retaining available memory.
		void clearMem();						//!< Clear items only when needed, releasing memory when deemed.

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

		void remove(kye const & theKey);					//!< Remove a key, retaining memory available.
		Bll removeBll(kye const & theKey);					//!< Remove a key and return whether successful, retaining memory available.
		Itr removeItr(kye const & theKey);					//!< Remove a key and return the iterator when found, else InvItr, retaining memory available.
		Itr removeItr(kye const & theKey, itm & Item);		//!< Remove a key and return the iterator and item when found, else return InvItr, retaining memory available.
		void removeWithItr(Itr const theItr);				//!< Remove a key represented by an iterator, retaining memory available.
		Bll removeBllWithItr(Itr const theItr);				//!< Remove a key represented by an iterator and return whether succesfull, retaining memory available.

		void removeMem(kye const & theKey);					//!< Remove a key, releasing memory when deemed.
		Bll removeBllMem(kye const & theKey);				//!< Remove a key and return whether successful, releasing memory when deemed.
		Itr removeItrMem(kye const & theKey);				//!< Remove a key and return the iterator when found, else InvItr, releasing memory when deemed.
		Itr removeItrMem(kye const & theKey, itm & Item);	//!< Remove a key and return the iterator and item when found, else return InvItr, releasing memory when deemed.
		void removeWithItrMem(Itr const theItr);			//!< Remove a key represented by an iterator, releasing memory when deemed.
		Bll removeBllWithItrMem(Itr const theItr);			//!< Remove a key represented by an iterator and return whether succesfull, releasing memory when deemed.

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

		mm		mMemMan;						//!< Memory manager.
		Itr * mHome;							//!< Itr of home keys.
		#if ParallelArray
			Itr * mSucc;						//!< Itr of successor keys.
			Itr * mPrec;						//!< Itr of predecessor keys.
			kye * mKeys;						//!< The array of keys.
			itm * mItems;						//!< The array of items.
		#else
			t4<Itr,Itr,kye,itm> * mSPKIs;		//!< The array of succ, prec, key, item.
		#endif
};



/*!
	@def hmd
	@brief A macro to denote hmapd.
	@details This macro denotes hmapd.
*/
#define hmd hmapd



/*!
	The constructor.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmapd<kye,itm,mm,hfn,eqfn>::hmapd()
{
	WatchError
	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
	#else
		mSPKIs = new t4<Itr,Itr,kye,itm>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSPKIs[tItr].First = mSPKIs[tItr].Second = InvItr;
	#endif

	CatchError
}



/*!
	The initialiser.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmapd<kye,itm,mm,hfn,eqfn>::hmapd(mm const & theMm) : mMemMan(theMm)
{
	WatchError
	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
	#else
		mSPKIs = new t4<Itr,Itr,kye,itm>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSPKIs[tItr].First = mSPKIs[tItr].Second = InvItr;
	#endif

	CatchError
}



/*!
	The duplicator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmapd<kye,itm,mm,hfn,eqfn>::hmapd(hmapd<kye,itm,mm,hfn,eqfn> const & that) : mMemMan(that.mMemMan)
{
	WatchError

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mSucc[tItr] = that.mSucc[tItr];
			mPrec[tItr] = that.mPrec[tItr];
			mKeys[tItr] = that.mKeys[tItr];
			mItems[tItr] = that.mItems[tItr];
		}
	#else
		mSPKIs = new t4<Itr,Itr,kye,itm>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mSPKIs[tItr] = that.mSPKIs[tItr];
		}
	#endif

	CatchError
}



/*!
	The assigner.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmapd<kye,itm,mm,hfn,eqfn> const & hmapd<kye,itm,mm,hfn,eqfn>::operator =
		(hmapd<kye,itm,mm,hfn,eqfn> const & that)
{
	WatchError

	if (this == &that)
		return *this;

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		delete [] mHome;
		#if ParallelArray
			delete [] mSucc;
			delete [] mPrec;
			delete [] mKeys;
			delete [] mItems;
		#else
			delete [] mSPKIs;
		#endif

		mHome = new Itr[that.mMemMan.acquired()];
		#if ParallelArray
			mSucc = new Itr[that.mMemMan.acquired()];
			mPrec = new Itr[that.mMemMan.acquired()];
			mKeys = new kye[that.mMemMan.acquired()];
			mItems = new itm[that.mMemMan.acquired()];
		#else
			mSPKIs = new t4<Itr,Itr,kye,itm>[that.mMemMan.acquired()];
		#endif
	}

	mMemMan = that.mMemMan;

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	{
		mHome[tItr] = that.mHome[tItr];
		#if ParallelArray
			mSucc[tItr] = that.mSucc[tItr];
			mPrec[tItr] = that.mPrec[tItr];
			mKeys[tItr] = that.mKeys[tItr];
			mItems[tItr] = that.mItems[tItr];
		#else
			mSPKIs[tItr] = that.mSPKIs[tItr];
		#endif
	}
	return *this;

	CatchError
}



/*!
	The destructor.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
hmapd<kye,itm,mm,hfn,eqfn>::~hmapd()
{
	WatchError

	delete [] mHome;
	#if ParallelArray
		delete [] mSucc;
		delete [] mPrec;
		delete [] mKeys;
		delete [] mItems;
	#else
		delete [] mSPKIs;
	#endif

	CatchError
}



/*!
	Synchronise clock.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline void hmapd<kye,itm,mm,hfn,eqfn>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}



/*!
	Clear the map, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapd<kye,itm,mm,hfn,eqfn>::clear()
{
	WatchError

	if (mMemMan.resetOccupyBll())
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			#if ParallelArray
				Itr & tSucc = mSucc[tItr];
				if (tSucc == InvItr) continue;
				Itr & tPrec = mPrec[tItr];
				if (tSucc <= tItr)
					mHome[hfn::iof(mKeys[tItr]) % mMemMan.acquired()] = InvItr;
				tPrec = tSucc = InvItr;
			#else
				Itr & tSucc = mSPKIs[tItr].First;
				if (tSucc == InvItr) continue;
				Itr & tPrec = mSPKIs[tItr].Second;
				if (tSucc <= tItr)
					mHome[hfn::iof(mSPKIs[tItr].Third) % mMemMan.acquired()] = InvItr;
				tPrec = tSucc = InvItr;
			#endif
		}

	CatchError
}



/*!
	Clear the map, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapd<kye,itm,mm,hfn,eqfn>::clearMem()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			#if ParallelArray
				Itr & tSucc = mSucc[tItr];
				if (tSucc == InvItr) continue;
				Itr & tPrec = mPrec[tItr];
				if (tSucc <= tItr)
					mHome[hfn::iof(mKeys[tItr]) % mMemMan.acquired()] = InvItr;
				tPrec = tSucc = InvItr;
			#else
				Itr & tSucc = mSPKIs[tItr].First;
				if (tSucc == InvItr) continue;
				Itr & tPrec = mSPKIs[tItr].Second;
				if (tSucc <= tItr)
					mHome[hfn::iof(mSPKIs[tItr].Third) % mMemMan.acquired()] = InvItr;
				tPrec = tSucc = InvItr;
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
void hmapd<kye,itm,mm,hfn,eqfn>::insert(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

	if (tItr2 == InvItr)
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return;
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return;
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
	#endif

	mMemMan.reoccupy();

	CatchError
}



/*!
	Insert a key-item pair, return whether successful, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapd<kye,itm,mm,hfn,eqfn>::insertBll(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

	if (tItr2 == InvItr)
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return false;
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return false;
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
	#endif

	mMemMan.reoccupy();
	return true;

	CatchError
}



/*!
	Insert a key-item pair, return whether successful and the iterator, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapd<kye,itm,mm,hfn,eqfn>::insertBll(kye const & theKey, itm const & Item, Itr & theItr)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
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
Itr hmapd<kye,itm,mm,hfn,eqfn>::insertItr(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

	if (tItr2 == InvItr)
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return tItr2;
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return tItr2;
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}





/*!
	Insert a key-item pair and return the iterator if the key is new else InvItr, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapd<kye,itm,mm,hfn,eqfn>::insertItrIfNew(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

	if (tItr2 == InvItr)
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return InvItr;
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return InvItr;
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key-item pair and return the iterator if the key is old else InvItr, assuming memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapd<kye,itm,mm,hfn,eqfn>::insertItrIfOld(kye const & theKey, itm const & Item)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

	if (tItr2 == InvItr)
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return tItr2;
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return tItr2;
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
	#endif
	mMemMan.reoccupy();
	return InvItr;

	CatchError
}




/*!
	Insert a key-item pair, return whether successful, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapd<kye,itm,mm,hfn,eqfn>::insertMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

	if (tItr2 == InvItr)
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return;
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return;
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
	#endif

	mMemMan.reoccupy();

	CatchError
}



/*!
	Insert a key-item pair, return whether successful, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapd<kye,itm,mm,hfn,eqfn>::insertBllMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

	if (tItr2 == InvItr)
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return false;
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return false;
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
	#endif

	mMemMan.reoccupy();
	return true;

	CatchError
}



/*!
	Insert a key-item pair, return whether successful and the iterator, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapd<kye,itm,mm,hfn,eqfn>::insertBllMem(kye const & theKey, itm const & Item, Itr & theItr)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
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
Itr hmapd<kye,itm,mm,hfn,eqfn>::insertItrMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

	if (tItr2 == InvItr)
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return tItr2;
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return tItr2;
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}





/*!
	Insert a key-item pair and return the iterator if the key is new else InvItr, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapd<kye,itm,mm,hfn,eqfn>::insertItrIfNewMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

	if (tItr2 == InvItr)
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return InvItr;
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return InvItr;
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key-item pair and return the iterator if the key is old else InvItr, acquiring memory when needed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapd<kye,itm,mm,hfn,eqfn>::insertItrIfOldMem(kye const & theKey, itm const & Item)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

	if (tItr2 == InvItr)
		tItr3 = tItr1;
	else
	{
		while(true)
		{
			#if ParallelArray
				if (eqfn::iof(mKeys[tItr2], theKey))
					return tItr2;
				if (mSucc[tItr2] == tItr0)
					break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return tItr2;
				if (mSPKIs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKIs[tItr2].First;
			#endif
		}
		tItr3 = (tItr2 + tDiff++) % mMemMan.acquired();
	}

	#if ParallelArray
		while(mSucc[tItr3] != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSucc[tItr3] != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSucc[tItr3] = tItr3;
			mPrec[tItr3] = tItr3;
		}
		else
		{
			mSucc[tItr3] = tItr0;
			mPrec[tItr3] = tItr2;
			mSucc[tItr2] = tItr3;
			mPrec[tItr0] = tItr3;
		}

		mKeys[tItr3] = theKey;
		mItems[tItr3] = Item;
	#else
		while(mSPKIs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKIs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKIs[tItr3].First = tItr3;
			mSPKIs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKIs[tItr3].First = tItr0;
			mSPKIs[tItr3].Second = tItr2;
			mSPKIs[tItr2].First = tItr3;
			mSPKIs[tItr0].Second = tItr3;
		}

		mSPKIs[tItr3].Third = theKey;
		mSPKIs[tItr3].Fourth = Item;
	#endif
	mMemMan.reoccupy();
	return InvItr;

	CatchError
}



/*!
	Remove a key, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapd<kye,itm,mm,hfn,eqfn>::remove(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return;
	Itr tItr0 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mSucc[tItr2] == tItr0)
				return;
			tItr2 = mSucc[tItr2];
		#else
			if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				break;
			if (mSPKIs[tItr2].First == tItr0)
				return;
			tItr2 = mSPKIs[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (mSucc[tItr2] == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[tItr2] = InvItr;
		mPrec[tItr2] = InvItr;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mSPKIs[tItr2].First = InvItr;
		mSPKIs[tItr2].Second = InvItr;
	#endif

	mMemMan.unoccupy();

	CatchError
}



/*!
	Remove a key and return whether successful, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapd<kye,itm,mm,hfn,eqfn>::removeBll(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return false;
	Itr tItr0 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mSucc[tItr2] == tItr0)
				return false;
			tItr2 = mSucc[tItr2];
		#else
			if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				break;
			if (mSPKIs[tItr2].First == tItr0)
				return false;
			tItr2 = mSPKIs[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (mSucc[tItr2] == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[tItr2] = InvItr;
		mPrec[tItr2] = InvItr;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mSPKIs[tItr2].First = InvItr;
		mSPKIs[tItr2].Second = InvItr;
	#endif

	mMemMan.unoccupy();
	return true;

	CatchError
}



/*!
	Remove a key and return the iterator when found, else InvItr, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapd<kye,itm,mm,hfn,eqfn>::removeItr(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return InvItr;
	Itr tItr0 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mSucc[tItr2] == tItr0)
				return InvItr;
			tItr2 = mSucc[tItr2];
		#else
			if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				break;
			if (mSPKIs[tItr2].First == tItr0)
				return InvItr;
			tItr2 = mSPKIs[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (mSucc[tItr2] == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[tItr2] = InvItr;
		mPrec[tItr2] = InvItr;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mSPKIs[tItr2].First = InvItr;
		mSPKIs[tItr2].Second = InvItr;
	#endif

	mMemMan.unoccupy();
	return tItr2;

	CatchError
}



/*!
	Remove a key and return the iterator and item when found, else return InvItr, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapd<kye,itm,mm,hfn,eqfn>::removeItr(kye const & theKey, itm & Item)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return InvItr;
	Itr tItr0 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mSucc[tItr2] == tItr0)
				return InvItr;
			tItr2 = mSucc[tItr2];
		#else
			if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				break;
			if (mSPKIs[tItr2].First == tItr0)
				return InvItr;
			tItr2 = mSPKIs[tItr2].First;
		#endif
	}
	#if ParallelArray
		Item = mItems[tItr2];
		if (mSucc[tItr2] == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[tItr2] = InvItr;
		mPrec[tItr2] = InvItr;
	#else
		Item = mSPKIs[tItr2].Fourth;

		if (mSPKIs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;
			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}
		mSPKIs[tItr2].First = InvItr;
		mSPKIs[tItr2].Second = InvItr;
	#endif

	mMemMan.unoccupy();
	return tItr2;

	CatchError
}



/*!
	Remove a key represented by an iterator and return whether succesfull, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapd<kye,itm,mm,hfn,eqfn>::removeWithItr(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		if (mSucc[theItr] == InvItr) return;

		Itr tItr1 = hfn::iof(mKeys[theItr]) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSucc[theItr] == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSucc[theItr];

			Itr tItr3 = mPrec[theItr];
			Itr tItr4 = mSucc[theItr];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[theItr] = InvItr;
		mPrec[theItr] = InvItr;
	#else
		if (mSPKIs[theItr].First == InvItr) return;
		Itr tItr1 = hfn::iof(mSPKIs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKIs[theItr].First == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKIs[theItr].First;

			Itr tItr3 = mSPKIs[theItr].Second;
			Itr tItr4 = mSPKIs[theItr].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mSPKIs[theItr].First = InvItr;
		mSPKIs[theItr].Second = InvItr;
	#endif

	mMemMan.unoccupy();

	CatchError
}



/*!
	Remove a key represented by an iterator and return whether succesfull, retaining memory available.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapd<kye,itm,mm,hfn,eqfn>::removeBllWithItr(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		if (mSucc[theItr] == InvItr) return false;

		Itr tItr1 = hfn::iof(mKeys[theItr]) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSucc[theItr] == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSucc[theItr];

			Itr tItr3 = mPrec[theItr];
			Itr tItr4 = mSucc[theItr];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[theItr] = InvItr;
		mPrec[theItr] = InvItr;
	#else
		if (mSPKIs[theItr].First == InvItr) return false;
		Itr tItr1 = hfn::iof(mSPKIs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKIs[theItr].First == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKIs[theItr].First;

			Itr tItr3 = mSPKIs[theItr].Second;
			Itr tItr4 = mSPKIs[theItr].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mSPKIs[theItr].First = InvItr;
		mSPKIs[theItr].Second = InvItr;
	#endif

	mMemMan.unoccupy();
	return true;

	CatchError
}



/*!
	Remove a key and return the iterator when found, else InvItr, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapd<kye,itm,mm,hfn,eqfn>::removeMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return;
	Itr tItr0 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mSucc[tItr2] == tItr0)
				return;
			tItr2 = mSucc[tItr2];
		#else
			if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				break;
			if (mSPKIs[tItr2].First == tItr0)
				return;
			tItr2 = mSPKIs[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (mSucc[tItr2] == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[tItr2] = InvItr;
		mPrec[tItr2] = InvItr;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mSPKIs[tItr2].First = InvItr;
		mSPKIs[tItr2].Second = InvItr;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Remove a key and return the iterator when found, else InvItr, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapd<kye,itm,mm,hfn,eqfn>::removeBllMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return false;
	Itr tItr0 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mSucc[tItr2] == tItr0)
				return false;
			tItr2 = mSucc[tItr2];
		#else
			if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				break;
			if (mSPKIs[tItr2].First == tItr0)
				return false;
			tItr2 = mSPKIs[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (mSucc[tItr2] == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[tItr2] = InvItr;
		mPrec[tItr2] = InvItr;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mSPKIs[tItr2].First = InvItr;
		mSPKIs[tItr2].Second = InvItr;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	return true;

	CatchError
}



/*!
	Remove a key and return the iterator when found, else InvItr, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapd<kye,itm,mm,hfn,eqfn>::removeItrMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return InvItr;
	Itr tItr0 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mSucc[tItr2] == tItr0)
				return InvItr;
			tItr2 = mSucc[tItr2];
		#else
			if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				break;
			if (mSPKIs[tItr2].First == tItr0)
				return InvItr;
			tItr2 = mSPKIs[tItr2].First;
		#endif
	}

	#if ParallelArray
		if (mSucc[tItr2] == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[tItr2] = InvItr;
		mPrec[tItr2] = InvItr;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mSPKIs[tItr2].First = InvItr;
		mSPKIs[tItr2].Second = InvItr;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	return tItr2;

	CatchError
}



/*!
	Remove a key and return the iterator and item when found, else return InvItr, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapd<kye,itm,mm,hfn,eqfn>::removeItrMem(kye const & theKey, itm & Item)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	if (tItr2 == InvItr)
		return InvItr;
	Itr tItr0 = tItr2;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr2], theKey))
				break;
			if (mSucc[tItr2] == tItr0)
				return InvItr;
			tItr2 = mSucc[tItr2];
		#else
			if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				break;
			if (mSPKIs[tItr2].First == tItr0)
				return InvItr;
			tItr2 = mSPKIs[tItr2].First;
		#endif
	}
	#if ParallelArray
		Item = mItems[tItr2];
		if (mSucc[tItr2] == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[tItr2] = InvItr;
		mPrec[tItr2] = InvItr;
	#else
		Item = mSPKIs[tItr2].Fourth;

		if (mSPKIs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;
			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}
		mSPKIs[tItr2].First = InvItr;
		mSPKIs[tItr2].Second = InvItr;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	return tItr2;

	CatchError
}



/*!
	Remove a key represented by an iterator and return whether succesfull, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapd<kye,itm,mm,hfn,eqfn>::removeWithItrMem(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		if (mSucc[theItr] == InvItr) return;

		Itr tItr1 = hfn::iof(mKeys[theItr]) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSucc[theItr] == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSucc[theItr];

			Itr tItr3 = mPrec[theItr];
			Itr tItr4 = mSucc[theItr];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[theItr] = InvItr;
		mPrec[theItr] = InvItr;
	#else
		if (mSPKIs[theItr].First == InvItr) return;
		Itr tItr1 = hfn::iof(mSPKIs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKIs[theItr].First == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKIs[theItr].First;

			Itr tItr3 = mSPKIs[theItr].Second;
			Itr tItr4 = mSPKIs[theItr].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mSPKIs[theItr].First = InvItr;
		mSPKIs[theItr].Second = InvItr;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Remove a key represented by an iterator and return whether succesfull, releasing memory when deemed.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapd<kye,itm,mm,hfn,eqfn>::removeBllWithItrMem(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		if (mSucc[theItr] == InvItr) return false;

		Itr tItr1 = hfn::iof(mKeys[theItr]) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSucc[theItr] == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSucc[theItr];

			Itr tItr3 = mPrec[theItr];
			Itr tItr4 = mSucc[theItr];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mSucc[theItr] = InvItr;
		mPrec[theItr] = InvItr;
	#else
		if (mSPKIs[theItr].First == InvItr) return false;
		Itr tItr1 = hfn::iof(mSPKIs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKIs[theItr].First == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKIs[theItr].First;

			Itr tItr3 = mSPKIs[theItr].Second;
			Itr tItr4 = mSPKIs[theItr].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mSPKIs[theItr].First = InvItr;
		mSPKIs[theItr].Second = InvItr;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	return true;

	CatchError
}



/*!
	Reallocate memory automatically.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapd<kye,itm,mm,hfn,eqfn>::reallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);

	Dim tAcquired = mMemMan.acquired();
	Itr * const tHome = mHome;

	mMemMan.reallocAuto();

	mHome = new Itr[mMemMan.acquired()];

	#if ParallelArray
		Itr * const tSucc = mSucc;
		Itr * const tPrec = mPrec;
		kye * const tKeys = mKeys;
		itm * const tItms = mItems;

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
	#else
		t4<Itr,Itr,kye,itm> * const tSPKIs = mSPKIs;
		mSPKIs = new t4<Itr,Itr,kye,itm>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	#if ParallelArray
		mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
	#else
		mHome[tItr] = mSPKIs[tItr].First = mSPKIs[tItr].Second = InvItr;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tSucc[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tSPKIs[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tSPKIs[tItr].Third) % mMemMan.acquired();
		#endif

		if (mHome[tItr1] == InvItr)
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mSucc[tItr2] != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSucc[tItr2] != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mSucc[tItr2] = tItr2;
				mPrec[tItr2] = tItr2;
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mSPKIs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSPKIs[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mSPKIs[tItr2].First = tItr2;
				mSPKIs[tItr2].Second = tItr2;
				mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
				mSPKIs[tItr2].Fourth = tSPKIs[tItr].Fourth;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		Itr tItr0 = tItr1;

		#if ParallelArray
			while(mSucc[tItr1] != tItr0)
				tItr1 = mSucc[tItr1];

			Itr tDiff = 1;
			Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

			while(mSucc[tItr2] != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSucc[tItr2] != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSucc[tItr2] = tItr0;
			mPrec[tItr2] = tItr1;
			mSucc[tItr1] = tItr2;
			mPrec[tItr0] = tItr2;

			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mSPKIs[tItr1].First != tItr0)
				tItr1 = mSPKIs[tItr1].First;

			Itr tDiff = 1;
			Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

			while(mSPKIs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSPKIs[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSPKIs[tItr2].First = tItr0;
			mSPKIs[tItr2].Second = tItr1;
			mSPKIs[tItr1].First = tItr2;
			mSPKIs[tItr0].Second = tItr2;
			mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
			mSPKIs[tItr2].Fourth = tSPKIs[tItr].Fourth;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
		delete [] tItms;
	#else
		delete [] tSPKIs;
	#endif

	CatchError
}



/*!
	Deallocate memory automatically.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapd<kye,itm,mm,hfn,eqfn>::deallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);

	Dim tAcquired = mMemMan.acquired();
	Itr * const tHome = mHome;

	mMemMan.deallocAuto();

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		Itr * const tSucc = mSucc;
		Itr * const tPrec = mPrec;
		kye * const tKeys = mKeys;
		itm * const tItms = mItems;

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
	#else
		t4<Itr,Itr,kye,itm> * const tSPKIs = mSPKIs;
		mSPKIs = new t4<Itr,Itr,kye,itm>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		#if ParallelArray
			mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
		#else
			mHome[tItr] = mSPKIs[tItr].First = mSPKIs[tItr].Second = InvItr;
		#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tSucc[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tSPKIs[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tSPKIs[tItr].Third) % mMemMan.acquired();
		#endif

		if (mHome[tItr1] == InvItr)
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mSucc[tItr2] != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSucc[tItr2] != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mSucc[tItr2] = tItr2;
				mPrec[tItr2] = tItr2;
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mSPKIs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSPKIs[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mSPKIs[tItr2].First = tItr2;
				mSPKIs[tItr2].Second = tItr2;
				mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
				mSPKIs[tItr2].Fourth = tSPKIs[tItr].Fourth;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		Itr tItr0 = tItr1;
		#if ParallelArray
			while(mSucc[tItr1] != tItr0)
				tItr1 = mSucc[tItr1];
		#else
			while(mSPKIs[tItr1].First != tItr0)
				tItr1 = mSPKIs[tItr1].First;
		#endif

		Itr tDiff = 1;
		Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

		#if ParallelArray
			while(mSucc[tItr2] != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSucc[tItr2] != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSucc[tItr2] = tItr0;
			mPrec[tItr2] = tItr1;
			mSucc[tItr1] = tItr2;
			mSucc[tItr0] = tItr2;

			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mSPKIs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSPKIs[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSPKIs[tItr2].First = tItr0;
			mSPKIs[tItr2].Second = tItr1;
			mSPKIs[tItr1].First = tItr2;
			mSPKIs[tItr0].Second = tItr2;

			mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
			mSPKIs[tItr2].Fourth = tSPKIs[tItr].Fourth;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
		delete [] tItms;
	#else
		delete [] tSPKIs;
	#endif

	CatchError
}



/*!
	Adjust the memory automatically.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapd<kye,itm,mm,hfn,eqfn>::adjustMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);

	Dim tAcquired = mMemMan.acquired();
	Itr * const tHome = mHome;

	mMemMan.adjustAuto();

	mHome = new Itr[mMemMan.acquired()];

	#if ParallelArray
		Itr * const tSucc = mSucc;
		Itr * const tPrec = mPrec;
		kye * const tKeys = mKeys;
		itm * const tItms = mItems;

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
	#else
		t4<Itr,Itr,kye,itm> * const tSPKIs = mSPKIs;
		mSPKIs = new t4<Itr,Itr,kye,itm>[mMemMan.acquired()];
	#endif

	#if ParallelArray
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
	#else
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSPKIs[tItr].First = mSPKIs[tItr].Second = InvItr;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tSucc[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tSPKIs[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tSPKIs[tItr].Third) % mMemMan.acquired();
		#endif

		if (mHome[tItr1] == InvItr)
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mSucc[tItr2] != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSucc[tItr2] != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;

				mSucc[tItr2] = tItr2;
				mPrec[tItr2] = tItr2;
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mSPKIs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSPKIs[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mSPKIs[tItr2].First = tItr2;
				mSPKIs[tItr2].Second = tItr2;
				mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
				mSPKIs[tItr2].Fourth = tSPKIs[tItr].Fourth;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		Itr tItr0 = tItr1;

		#if ParallelArray
			while(mSucc[tItr1] != tItr0)
				tItr1 = mSucc[tItr1];
		#else
			while(mSPKIs[tItr1].First != tItr0)
				tItr1 = mSPKIs[tItr1].First;
		#endif

		Itr tDiff = 1;
		Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

		#if ParallelArray
			while(mSucc[tItr2] != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSucc[tItr2] != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSucc[tItr2] = tItr0;
			mPrec[tItr2] = tItr1;
			mSucc[tItr1] = tItr2;
			mSucc[tItr0] = tItr2;
			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mSPKIs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSPKIs[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSPKIs[tItr2].First = tItr0;
			mSPKIs[tItr2].Second = tItr1;
			mSPKIs[tItr1].First = tItr2;
			mSPKIs[tItr1].Second = tItr2;
			mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
			mSPKIs[tItr2].Fourth = tSPKIs[tItr].Fourth;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
		delete [] tItms;
	#else
		delete [] tSPKIs;
	#endif

	CatchError
}



/*!
	Allocate memory.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
void hmapd<kye,itm,mm,hfn,eqfn>::allocateMem(Dim const Alloc)
{
	WatchError

	if (!mMemMan.mismatchAlloc(Alloc)) return;

	Dim tAcquired = mMemMan.acquired();
	Itr * const tHome = mHome;

	mMemMan.allocate(Alloc);

	mHome = new Itr[mMemMan.acquired()];

	#if ParallelArray
		Itr * const tSucc = mSucc;
		Itr * const tPrec = mPrec;
		kye * const tKeys = mKeys;
		itm * const tItms = mItems;

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mItems = new itm[mMemMan.acquired()];
	#else
		t4<Itr,Itr,kye,itm> * const tSPKIs = mSPKIs;
		mSPKIs = new t4<Itr,Itr,kye,itm>[mMemMan.acquired()];
	#endif

	#if ParallelArray
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
	#else
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSPKIs[tItr].First = mSPKIs[tItr].Second = InvItr;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tSucc[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tSPKIs[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tSPKIs[tItr].Third) % mMemMan.acquired();
		#endif

		if (mHome[tItr1] == InvItr)
		{
			Itr tItr2 = tItr1;
			Itr tDiff = 1;

			#if ParallelArray
				while(mSucc[tItr2] != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSucc[tItr2] != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;

				mSucc[tItr2] = tItr2;
				mPrec[tItr2] = tItr2;
				mKeys[tItr2] = tKeys[tItr];
				mItems[tItr2] = tItms[tItr];
			#else
				while(mSPKIs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSPKIs[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mSPKIs[tItr2].First = tItr2;
				mSPKIs[tItr2].Second = tItr2;
				mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
				mSPKIs[tItr2].Fourth = tSPKIs[tItr].Fourth;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		Itr tItr0 = tItr1;

		#if ParallelArray
			while(mSucc[tItr1] != tItr0)
				tItr1 = mSucc[tItr1];
		#else
			while(mSPKIs[tItr1].First != tItr0)
				tItr1 = mSPKIs[tItr1].First;
		#endif

		Itr tDiff = 1;
		Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

		#if ParallelArray
			while(mSucc[tItr2] != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSucc[tItr2] != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSucc[tItr2] = tItr0;
			mPrec[tItr2] = tItr1;
			mSucc[tItr1] = tItr2;
			mSucc[tItr0] = tItr2;
			mKeys[tItr2] = tKeys[tItr];
			mItems[tItr2] = tItms[tItr];
		#else
			while(mSPKIs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSPKIs[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSPKIs[tItr2].First = tItr0;
			mSPKIs[tItr2].Second = tItr1;
			mSPKIs[tItr1].First = tItr2;
			mSPKIs[tItr1].Second = tItr2;
			mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
			mSPKIs[tItr2].Fourth = tSPKIs[tItr].Fourth;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
		delete [] tItms;
	#else
		delete [] tSPKIs;
	#endif

	CatchError
}




/*!
	Return the key count.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline Dim hmapd<kye,itm,mm,hfn,eqfn>::keyCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the slot count.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline Dim hmapd<kye,itm,mm,hfn,eqfn>::slotCount() const
{
	WatchError

	return mMemMan.acquired();

	CatchError
}



/*!
	Return the memory manager.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline mm const & hmapd<kye,itm,mm,hfn,eqfn>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Whether the slot for the iterator is occupied.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline Bll hmapd<kye,itm,mm,hfn,eqfn>::occupiedSlot(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mSucc[theItr] != InvItr;
	#else
		return mSPKIs[theItr].First != InvItr;
	#endif

	CatchError
}



/*!
	Find a key in the map, or return InvItr if not found.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Itr hmapd<kye,itm,mm,hfn,eqfn>::findItr(kye const & theKey) const
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();
	if (mHome[tItr] == InvItr)
		return InvItr;
	tItr = mHome[tItr];
	Itr tItr0 = tItr;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr], theKey))
				return tItr;
			if (mSucc[tItr] == tItr0)
				return InvItr;
			tItr = mSucc[tItr];
		#else
			if (eqfn::iof(mSPKIs[tItr].Third, theKey))
				return tItr;
			if (mSPKIs[tItr].First == tItr0)
				return InvItr;
			tItr = mSPKIs[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Find a key in the map and return whether found.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
Bll hmapd<kye,itm,mm,hfn,eqfn>::findBll(kye const & theKey) const
{
	WatchError
	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();
	if (mHome[tItr] == InvItr)
		return false;
	tItr = mHome[tItr];
	Itr tItr0 = tItr;
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr], theKey))
				return true;
			if (mSucc[tItr] == tItr0)
				return false;
			tItr = mSucc[tItr];
		#else
			if (eqfn::iof(mSPKIs[tItr].Third, theKey))
				return true;
			if (mSPKIs[tItr].First == tItr0)
				return false;
			tItr = mSPKIs[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Return a key at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline kye const & hmapd<kye,itm,mm,hfn,eqfn>::operator[](Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mKeys[theItr];
	#else
		return mSPKIs[theItr].Third;
	#endif

	CatchError
}



/*!
	Return a key at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline kye const & hmapd<kye,itm,mm,hfn,eqfn>::key(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mKeys[theItr];
	#else
		return mSPKIs[theItr].Third;
	#endif

	CatchError
}



/*!
	Return data for the key, or throw an error if not exists.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
itm const & hmapd<kye,itm,mm,hfn,eqfn>::map(kye const & theKey) const
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();

	Warn(mHome[tItr] == InvItr, eKeyNotFound);

	tItr = mHome[tItr];
	#if CheckError
	Itr tItr0 = tItr;
	#endif
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr], theKey))
				return mItems[tItr];

			Warn(mSucc[tItr] == tItr0, eKeyNotFound);

			tItr = mSucc[tItr];
		#else
			if (eqfn::iof(mSPKIs[tItr].Third, theKey))
				return mSPKIs[tItr].Fourth;

			Warn(mSPKIs[tItr].First == tItr0, eKeyNotFound);

			tItr = mSPKIs[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Return data for the key, or throw an error if not exists.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
itm & hmapd<kye,itm,mm,hfn,eqfn>::map(kye const & theKey)
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();

	Warn(mHome[tItr] == InvItr, eKeyNotFound);

	tItr = mHome[tItr];
	#if CheckError
	Itr tItr0 = tItr;
	#endif
	while(true)
	{
		#if ParallelArray
			if (eqfn::iof(mKeys[tItr], theKey))
				return mItems[tItr];

			Warn(mSucc[tItr] == tItr0, eKeyNotFound);

			tItr = mSucc[tItr];
		#else
			if (eqfn::iof(mSPKIs[tItr].Third, theKey))
				return mSPKIs[tItr].Fourth;

			Warn(mSPKIs[tItr].First == tItr0, eKeyNotFound);

			tItr = mSPKIs[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Return the item at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline itm const & hmapd<kye,itm,mm,hfn,eqfn>::operator()(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mItems[theItr];
	#else
		return mSPKIs[theItr].Fourth;
	#endif

	CatchError
}



/*!
	Return the item at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline itm & hmapd<kye,itm,mm,hfn,eqfn>::operator()(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mItems[theItr];
	#else
		return mSPKIs[theItr].Fourth;
	#endif

	CatchError
}



/*!
	Return the item at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline itm const & hmapd<kye,itm,mm,hfn,eqfn>::item(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mItems[theItr];
	#else
		return mSPKIs[theItr].Fourth;
	#endif

	CatchError
}



/*!
	Return the item at a given iterator.
*/
template<typename kye, typename itm, typename mm, typename hfn, typename eqfn>
inline itm & hmapd<kye,itm,mm,hfn,eqfn>::item(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mItems[theItr];
	#else
		return mSPKIs[theItr].Fourth;
	#endif

	CatchError
}



closeEmuSpace



#endif // HmapdTccIncluded
