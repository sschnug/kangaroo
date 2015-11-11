/*!
	@file hset.tcc
	@brief The source file for hset template class.
	@details This is the source file for hset template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef HsetTccIncluded
#define HsetTccIncluded



#include "cppl/roots/idx.hpp"
#include "cppl/opfns/idx.hpp"
#include "cppl/tuples/idx.hpp"



openEmuSpace



/*!
	@class hset
	@brief A class to represent standard hash sets that use closed hashing.
	@details This class represents standard hash sets that use closed hashing.
*/
template <typename kye, typename mm,
	typename hfn = hv<kye>, typename eqfn = eq<kye> >
class hset
{
	public:

		typedef mm MmTyp;								//!< Memory manager type.

		hset();											//!< Constructor.
		~hset();										//!< Destructor.
		hset(mm const & theMm);							//!< Initialiser.
		hset(hset<kye,mm,hfn,eqfn> const & that);		//!< Duplicator.
		hset<kye,mm,hfn,eqfn> const & operator =
				(hset<kye,mm,hfn,eqfn> const & that);	//!< Assigner.

		//! @name Synchronise
		//! @{

		void syncClk();	//!< Synchronise clock.

		//! @}

		//! @name Clear
		//! @{

		void clear();		//!< Clear keys, retaining available memory.
		void clearMem();	//!< Clear keys, releasing memory when deemed.

		//! @}

		//! @name Insert
		//! @{

		void insert(kye const & theKey);					//!< Insert a key, assuming memory available.
		Bll insertBll(kye const & theKey);					//!< Insert a key, return whether successful, assuming memory available.
		Bll insertBll(kye const & theKey, Itr & theItr);	//!< Insert a key, return whether successful and the iterator, assuming memory available.
		Itr insertItr(kye const & theKey);					//!< Insert a key and return the iterator, assuming memory available.
		Itr insertItrIfNew(kye const & theKey);				//!< Insert a key and return the iterator if the key is new else InvItr, assuming memory available.
		Itr insertItrIfOld(kye const & theKey);				//!< Insert a key and return the iterator if the key is old else InvItr, assuming memory available.

		void insertMem(kye const & theKye);					//!< Insert a key, acquiring memory when needed.
		Bll insertBllMem(kye const & theKye);				//!< Insert a key, return whether successful and the iterator, acquiring memory when needed.
		Bll insertBllMem(kye const & theKye, Itr & theItr);	//!< Insert a key, return whether successful and the iterator, acquiring memory when needed.
		Itr insertItrMem(kye const & theKey);				//!< Insert a key and return the iterator, acquiring memory when needed.
		Itr insertItrIfNewMem(kye const & theKey);			//!< Insert a key and return the iterator if the key is new else InvItr, acquiring memory when needed.
		Itr insertItrIfOldMem(kye const & theKey);			//!< Insert a key and return the iterator if the key is old else InvItr, acquiring memory when needed.

		//! @}

		/*! @name Remove */
		//! @{

		void remove(kye const & theKey);					//!< Remove a key, retaining memory available.
		Bll removeBll(kye const & theKey);					//!< Remove a key and return whether successful, retaining memory available.
		Itr removeItr(kye const & theKey);					//!< Remove a key and return the iterator when found, else InvItr, retaining memory available.

		void removeMem(kye const & theKey);					//!< Remove a key, releasing memory when deemed.
		Bll removeBllMem(kye const & theKey);				//!< Remove a key and return whether successful, releasing memory when deemed.
		Itr removeItrMem(kye const & theKey);				//!< Remove a key and return the iterator when found, else InvItr, releasing memory when deemed.

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

		//! @}

	private:

		mm	  mMemMan;							//!< Memory manager.
		Itr * mHome;							//!< Itr of home keys.
		#if ParallelArray
			Itr * mMore;						//!< Itr of successor keys.
			kye * mKeys;						//!< The array of keys.
		#else
			t2<Itr,kye> * mMoreKeys;			//!< The array of idx, keys.
		#endif
};




/*!
	@def hs
	@brief A macro to denote hset.
	@details This macro denotes hset.
*/
#define hs hset



/*!
	The constructor.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hset<kye,mm,hfn,eqfn>::hset()
{
	WatchError

	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMore[tItr] = InvItr;
	#else
		mMoreKeys = new t2<Itr,kye>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMoreKeys[tItr].First = InvItr;
	#endif

	CatchError
}



/*!
	The initialiser.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hset<kye,mm,hfn,eqfn>::hset(mm const & theMm) : mMemMan(theMm)
{
	WatchError

	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMore[tItr] = InvItr;
	#else
		mMoreKeys = new t2<Itr,kye>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMoreKeys[tItr].First = InvItr;
	#endif

	CatchError
}




/*!
	The duplicator.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hset<kye,mm,hfn,eqfn>::hset(hset<kye,mm,hfn,eqfn> const & that) :
		mMemMan(that.mMemMan)
{
	WatchError

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mMore[tItr] = that.mMore[tItr];
			mKeys[tItr] = that.mKeys[tItr];
		}
	#else
		mMoreKeys = new t2<Itr,kye>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mMoreKeys[tItr] = that.mMoreKeys[tItr];
		}
	#endif

	CatchError
}



/*!
	The assigner.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hset<kye,mm,hfn,eqfn> const & hset<kye,mm,hfn,eqfn>::operator =
		(hset<kye,mm,hfn,eqfn> const & that)
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
		#else
			delete [] mMoreKeys;
		#endif

		mHome = new Itr[that.mMemMan.acquired()];
		#if ParallelArray
			mMore = new Itr[that.mMemMan.acquired()];
			mKeys = new kye[that.mMemMan.acquired()];
		#else
			mMoreKeys = new t2<Itr,kye>[that.mMemMan.acquired()];
		#endif
	}

	mMemMan = that.mMemMan;

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	{
		mHome[tItr] = that.mHome[tItr];
		#if ParallelArray
			mMore[tItr] = that.mMore[tItr];
			mKeys[tItr] = that.mKeys[tItr];
		#else
			mMoreKeys[tItr] = that.mMoreKeys[tItr];
		#endif
	}
	return *this;

	CatchError
}



/*!
	The destructor.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hset<kye,mm,hfn,eqfn>::~hset()
{
	WatchError

	delete [] mHome;
	#if ParallelArray
		delete [] mMore;
		delete [] mKeys;
	#else
		delete [] mMoreKeys;
	#endif

	CatchError
}



/*!
	Synchronise clock.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline void hset<kye,mm,hfn,eqfn>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}



/*!
	Clear the keys, retaining available memory.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hset<kye,mm,hfn,eqfn>::clear()
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
				Itr & tMore = mMoreKeys[tItr].First;
				if (tMore == InvItr) continue;
				if (tMore == mMemMan.acquired())
					mHome[hfn::iof(mMoreKeys[tItr].Second) % mMemMan.acquired()] = InvItr;
				tMore = InvItr;
			#endif
		}

	CatchError
}



/*!
	Clear the keys, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hset<kye,mm,hfn,eqfn>::clearMem()
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
				Itr & tMore = mMoreKeys[tItr].First;
				if (tMore == InvItr) continue;
				if (tMore == mMemMan.acquired())
					mHome[hfn::iof(mMoreKeys[tItr].Second) % mMemMan.acquired()] = InvItr;
				tMore = InvItr;
			#endif
		}
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}
	CatchError
}



/*!
	Insert a key, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hset<kye,mm,hfn,eqfn>::insert(kye const & theKey)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
					return;
				if (mMoreKeys[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();

	CatchError
}



/*!
	Insert a key and return whether successful, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hset<kye,mm,hfn,eqfn>::insertBll(kye const & theKey)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
					return false;
				if (mMoreKeys[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();
	return true;

	CatchError
}





/*!
	Insert a key and return whether successful and the iterator, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hset<kye,mm,hfn,eqfn>::insertBll(kye const & theKey, Itr & theItr)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mMoreKeys[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();
	theItr = tItr3;
	return true;

	CatchError
}



/*!
	Insert a key and return the iterator, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hset<kye,mm,hfn,eqfn>::insertItr(kye const & theKey)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
					return tItr2;
				if (mMoreKeys[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key and return the iterator if the key is new else InvItr, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hset<kye,mm,hfn,eqfn>::insertItrIfNew(kye const & theKey)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
					return InvItr;
				if (mMoreKeys[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}




/*!
	Insert a key and return the iterator if the key is old else InvItr, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hset<kye,mm,hfn,eqfn>::insertItrIfOld(kye const & theKey)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
					return tItr2;
				if (mMoreKeys[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();
	return InvItr;

	CatchError
}



/*!
	Insert a key and return whether successful, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hset<kye,mm,hfn,eqfn>::insertMem(kye const & theKey)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
					return;
				if (mMoreKeys[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();

	CatchError
}



/*!
	Insert a key and return whether successful, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hset<kye,mm,hfn,eqfn>::insertBllMem(kye const & theKey)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
					return false;
				if (mMoreKeys[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();
	return true;

	CatchError
}



/*!
	Insert a key and return whether successful and the iterator, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hset<kye,mm,hfn,eqfn>::insertBllMem(kye const & theKey, Itr & theItr)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mMoreKeys[tItr2].First == mMemMan.acquired()) break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();
	theItr = tItr3;
	return true;

	CatchError
}



/*!
	Insert a key and return the iterator, acquiring memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hset<kye,mm,hfn,eqfn>::insertItrMem(kye const & theKey)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
					return tItr2;
				if (mMoreKeys[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key and return the iterator if the key is new else InvItr, acquiring memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hset<kye,mm,hfn,eqfn>::insertItrIfNewMem(kye const & theKey)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
					return InvItr;
				if (mMoreKeys[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}




/*!
	Insert a key and return the iterator if the key is old else InvItr, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hset<kye,mm,hfn,eqfn>::insertItrIfOldMem(kye const & theKey)
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
				if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
					return tItr2;
				if (mMoreKeys[tItr2].First == mMemMan.acquired())
					break;
				tItr2 = mMoreKeys[tItr2].First;
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
	#else
		while(mMoreKeys[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mMoreKeys[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
			mHome[tItr1] = tItr3;
		else
			mMoreKeys[tItr2].First = tItr3;

		mMoreKeys[tItr3].First = mMemMan.acquired();
		mMoreKeys[tItr3].Second = theKey;
	#endif
	mMemMan.reoccupy();
	return InvItr;

	CatchError
}



/*!
	Remove a key, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hset<kye,mm,hfn,eqfn>::remove(kye const & theKey)
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
				return;
			tItr3 = tItr2;
			tItr2 = mMore[tItr2];
		#else
			if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
				break;
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				return;
			tItr3 = tItr2;
			tItr2 = mMoreKeys[tItr2].First;
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
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeys[tItr2].First;
		else
			mMoreKeys[tItr3].First = mMoreKeys[tItr2].First;
		mMoreKeys[tItr2].First = InvItr;
	#endif

	mMemMan.unoccupy();

	CatchError
}


/*!
	Remove a key and return whether successful, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hset<kye,mm,hfn,eqfn>::removeBll(kye const & theKey)
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
			if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
				break;
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				return false;
			tItr3 = tItr2;
			tItr2 = mMoreKeys[tItr2].First;
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
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeys[tItr2].First;
		else
			mMoreKeys[tItr3].First = mMoreKeys[tItr2].First;
		mMoreKeys[tItr2].First = InvItr;
	#endif

	mMemMan.unoccupy();

	return true;

	CatchError
}



/*!
	Remove a key and return Itr when found else InvItr, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hset<kye,mm,hfn,eqfn>::removeItr(kye const & theKey)
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
			if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
				break;
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				return InvItr;
			tItr3 = tItr2;
			tItr2 = mMoreKeys[tItr2].First;
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
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeys[tItr2].First;
		else
			mMoreKeys[tItr3].First = mMoreKeys[tItr2].First;
		mMoreKeys[tItr2].First = InvItr;
	#endif

	mMemMan.unoccupy();

	return tItr2;

	CatchError
}



/*!
	Remove a key, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hset<kye,mm,hfn,eqfn>::removeMem(kye const & theKey)
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
			if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
				break;
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				return;
			tItr3 = tItr2;
			tItr2 = mMoreKeys[tItr2].First;
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
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeys[tItr2].First;
		else
			mMoreKeys[tItr3].First = mMoreKeys[tItr2].First;
		mMoreKeys[tItr2].First = InvItr;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}


/*!
	Remove a key and return whether successful, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hset<kye,mm,hfn,eqfn>::removeBllMem(kye const & theKey)
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
				return false;
			tItr3 = tItr2;
			tItr2 = mMore[tItr2];
		#else
			if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
				break;
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				return false;
			tItr3 = tItr2;
			tItr2 = mMoreKeys[tItr2].First;
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
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeys[tItr2].First;
		else
			mMoreKeys[tItr3].First = mMoreKeys[tItr2].First;
		mMoreKeys[tItr2].First = InvItr;
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
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hset<kye,mm,hfn,eqfn>::removeItrMem(kye const & theKey)
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
			if (eqfn::iof(mMoreKeys[tItr2].Second, theKey))
				break;
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				return InvItr;
			tItr3 = tItr2;
			tItr2 = mMoreKeys[tItr2].First;
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
			if (mMoreKeys[tItr2].First == mMemMan.acquired())
				mHome[tItr1] = InvItr;
			else
				mHome[tItr1] = mMoreKeys[tItr2].First;
		else
			mMoreKeys[tItr3].First = mMoreKeys[tItr2].First;
		mMoreKeys[tItr2].First = InvItr;
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
template<typename kye, typename mm, typename hfn, typename eqfn>
void hset<kye,mm,hfn,eqfn>::reallocMemAuto()
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

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
	#else
		t2<Itr,kye> * const tMoreKeys = mMoreKeys;
		mMoreKeys = new t2<Itr,kye>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	#if ParallelArray
		mHome[tItr] = mMore[tItr] = InvItr;
	#else
		mHome[tItr] = mMoreKeys[tItr].First = InvItr;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tMore[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tMoreKeys[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tMoreKeys[tItr].Second) % mMemMan.acquired();
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
			#else
				while(mMoreKeys[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMoreKeys[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mMoreKeys[tItr2].First = mMemMan.acquired();
				mMoreKeys[tItr2].Second = tMoreKeys[tItr].Second;
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
		#else
			while(mMoreKeys[tItr1].First != mMemMan.acquired())
				tItr1 = mMoreKeys[tItr1].First;

			Itr tDiff = 1;
			Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

			while(mMoreKeys[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMoreKeys[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mMoreKeys[tItr1].First = tItr2;
			mMoreKeys[tItr2].First = mMemMan.acquired();
			mMoreKeys[tItr2].Second = tMoreKeys[tItr].Second;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tMore;
		delete [] tKeys;
	#else
		delete [] tMoreKeys;
	#endif

	CatchError
}



/*!
	Deallocate some memory automatically.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hset<kye,mm,hfn,eqfn>::deallocMemAuto()
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

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
	#else
		t2<Itr,kye> * const tMoreKeys = mMoreKeys;
		mMoreKeys = new t2<Itr,kye>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		#if ParallelArray
			mHome[tItr] = mMore[tItr] = InvItr;
		#else
			mHome[tItr] = mMoreKeys[tItr].First = InvItr;
		#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tMore[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tMoreKeys[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tMoreKeys[tItr].Second) % mMemMan.acquired();
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
			#else
				while(mMoreKeys[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMoreKeys[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mMoreKeys[tItr2].First = mMemMan.acquired();
				mMoreKeys[tItr2].Second = tMoreKeys[tItr].Second;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		#if ParallelArray
			while(mMore[tItr1] != mMemMan.acquired())
				tItr1 = mMore[tItr1];
		#else
			while(mMoreKeys[tItr1].First != mMemMan.acquired())
				tItr1 = mMoreKeys[tItr1].First;
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
		#else
			while(mMoreKeys[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMoreKeys[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mMoreKeys[tItr1].First = tItr2;
			mMoreKeys[tItr2].First = mMemMan.acquired();
			mMoreKeys[tItr2].Second = tMoreKeys[tItr].Second;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tMore;
		delete [] tKeys;
	#else
		delete [] tMoreKeys;
	#endif

	CatchError
}



/*!
	Adjust memory automatically.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hset<kye,mm,hfn,eqfn>::adjustMemAuto()
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

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
	#else
		t2<Itr,kye> * const tMoreKeys = mMoreKeys;
		mMoreKeys = new t2<Itr,kye>[mMemMan.acquired()];
	#endif

	#if ParallelArray
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMore[tItr] = InvItr;
	#else
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMoreKeys[tItr].First = InvItr;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tMore[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tMoreKeys[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tMoreKeys[tItr].Second) % mMemMan.acquired();
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
			#else
				while(mMoreKeys[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMoreKeys[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mMoreKeys[tItr2].First = mMemMan.acquired();
				mMoreKeys[tItr2].Second = tMoreKeys[tItr].Second;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		#if ParallelArray
			while(mMore[tItr1] != mMemMan.acquired())
				tItr1 = mMore[tItr1];
		#else
			while(mMoreKeys[tItr1].First != mMemMan.acquired())
				tItr1 = mMoreKeys[tItr1].First;
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
		#else
			while(mMoreKeys[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMoreKeys[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mMoreKeys[tItr1].First = tItr2;
			mMoreKeys[tItr2].First = mMemMan.acquired();
			mMoreKeys[tItr2].Second = tMoreKeys[tItr].Second;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tMore;
		delete [] tKeys;
	#else
		delete [] tMoreKeys;
	#endif

	CatchError
}



/*!
	Allocate memory.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hset<kye,mm,hfn,eqfn>::allocateMem(Dim const Alloc)
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

		mMore = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
	#else
		t2<Itr,kye> * const tMoreKeys = mMoreKeys;
		mMoreKeys = new t2<Itr,kye>[mMemMan.acquired()];
	#endif

	#if ParallelArray
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMore[tItr] = InvItr;
	#else
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mMoreKeys[tItr].First = InvItr;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tMore[tItr] == InvItr) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tMoreKeys[tItr].First == InvItr) continue;
			Itr tItr1 = hfn::iof(tMoreKeys[tItr].Second) % mMemMan.acquired();
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
			#else
				while(mMoreKeys[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mMoreKeys[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mMoreKeys[tItr2].First = mMemMan.acquired();
				mMoreKeys[tItr2].Second = tMoreKeys[tItr].Second;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		#if ParallelArray
			while(mMore[tItr1] != mMemMan.acquired())
				tItr1 = mMore[tItr1];
		#else
			while(mMoreKeys[tItr1].First != mMemMan.acquired())
				tItr1 = mMoreKeys[tItr1].First;
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
		#else
			while(mMoreKeys[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mMoreKeys[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mMoreKeys[tItr1].First = tItr2;
			mMoreKeys[tItr2].First = mMemMan.acquired();
			mMoreKeys[tItr2].Second = tMoreKeys[tItr].Second;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tMore;
		delete [] tKeys;
	#else
		delete [] tMoreKeys;
	#endif

	CatchError
}



/*!
	Return the key count.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline Dim hset<kye,mm,hfn,eqfn>::keyCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the slot count.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline Dim hset<kye,mm,hfn,eqfn>::slotCount() const
{
	WatchError

	return mMemMan.acquired();

	CatchError
}



/*!
	Return the memory manager.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline mm const & hset<kye,mm,hfn,eqfn>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Return whether the slot at a given iterator is valid.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline Bll hset<kye,mm,hfn,eqfn>::occupiedSlot(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mMore[theItr] != InvItr;
	#else
		return mMoreKeys[theItr].First != InvItr;
	#endif

	CatchError
}



/*!
	Find a key in the set and return the iterator if found, else return InvItr.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hset<kye,mm,hfn,eqfn>::findItr(kye const & theKey) const
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
			if (eqfn::iof(mMoreKeys[tItr].Second, theKey))
				return tItr;
			if (mMoreKeys[tItr].First == mMemMan.acquired())
				return InvItr;
			tItr = mMoreKeys[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Find a key in the set and return whether found.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hset<kye,mm,hfn,eqfn>::findBll(kye const & theKey) const
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
			if (eqfn::iof(mMoreKeys[tItr].Second, theKey))
				return true;
			if (mMoreKeys[tItr].First == mMemMan.acquired())
				return false;
			tItr = mMoreKeys[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Return a key at a given iterator.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline kye const & hset<kye,mm,hfn,eqfn>::operator[](Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		Warn(mMore[theItr] == InvItr, eMemorySlotUnoccupied);
		return mKeys[theItr];
	#else
		Warn(mMoreKeys[theItr].First == InvItr, eMemorySlotUnoccupied);
		return mMoreKeys[theItr].Second;
	#endif

	CatchError
}



/*!
	Return a key at a given iterator.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline kye const & hset<kye,mm,hfn,eqfn>::key(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		Warn(mMore[theItr] == InvItr, eMemorySlotUnoccupied);
		return mKeys[theItr];
	#else
		Warn(mMoreKeys[theItr].First == InvItr, eMemorySlotUnoccupied);
		return mMoreKeys[theItr].Second;
	#endif

	CatchError
}



closeEmuSpace



#endif // HsetTccIncluded
