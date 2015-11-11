/*!
	@file hsetd.tcc
	@brief The source file for hsetd template class.
	@details This is the source file for hsetd template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef HsetdTccIncluded
#define HsetdTccIncluded



#include "cppl/roots/idx.hpp"
#include "cppl/opfns/idx.hpp"
#include "cppl/tuples/idx.hpp"


openEmuSpace



/*!
	@class hsetd
	@brief A class to represent hash sets with *doubly* linked list to have fast remove after find.
	@details This class represents hash sets with *doubly* linked list to have fast remove after find.
*/
template <typename kye, typename mm,
typename hfn = hv<kye>, typename eqfn = eq<kye> >
class hsetd
{
	public:

		typedef mm MmTyp;								//!< Memory manager type.

		hsetd();										//!< Constructor.
		~hsetd();										//!< Destructor.
		hsetd(mm const & theMm);						//!< Initialiser.
		hsetd(hsetd<kye,mm,hfn,eqfn> const & that);		//!< Duplicator.
		hsetd<kye,mm,hfn,eqfn> const & operator =
				(hsetd<kye,mm,hfn,eqfn> const & that);	//!< Assigner.

		//! @name Synchronise
		//! @{

		void syncClk();	//!< Synchronise clock.

		//! @}

		//! @name Clear
		//! @{

		void clear();							//!< Clear kyes only when needed, retaining available memory.
		void clearMem();						//!< Clear keys only when needed, releasing memory when deemed.

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
		Bll insertBllMem(kye const & theKye);				//!< Insert a key, return whether successful, acquiring memory when needed.
		Bll insertBllMem(kye const & theKye, Itr & theItr);	//!< Insert a key, return whether successful and the iterator, acquiring memory when needed.
		Itr insertItrMem(kye const & theKey);				//!< Insert a key and return the iterator, acquiring memory when needed.
		Itr insertItrIfNewMem(kye const & theKey);			//!< Insert a key and return the iterator if the key is new else InvItr, acquiring memory when needed.
		Itr insertItrIfOldMem(kye const & theKey);			//!< Insert a key and return the iterator if the key is old else InvItr, acquiring memory when needed.

		//! @}

		/*! @name Remove */
		//! @{

		void remove(kye const & theKey);					//!< Remove a key, retaining memory available.
		Bll removeBll(kye const & theKey);					//!< Remove a key and whether successful, retaining memory available.
		Itr removeItr(kye const & theKey);					//!< Remove a key and return the iterator when found, else InvItr, retaining memory available.
		void removeWithItr(Itr const theItr);				//!< Remove a key represented by an iterator, retaining memory available.
		Bll removeBllWithItr(Itr const theItr);				//!< Remove a key represented by an iterator and return whether succesfull, retaining memory available.

		void removeMem(kye const & theKey);					//!< Remove a key, releasing memory when deemed.
		Bll removeBllMem(kye const & theKey);				//!< Remove a key and whether successful, releasing memory when deemed.
		Itr removeItrMem(kye const & theKey);				//!< Remove a key and return the iterator when found, else InvItr, releasing memory when deemed.
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

		//! @}

	private:

		mm		mMemMan;						//!< Memory manager.
		Itr * mHome;							//!< Itr of home keys.
		#if ParallelArray
			Itr * mSucc;						//!< Itr of successor keys.
			Itr * mPrec;						//!< Itr of predecessor keys.
			kye * mKeys;						//!< The array of keys.
		#else
			t3<Itr,Itr,kye> * mSPKs;		//!< The array of succ, prec, key.
		#endif
};



/*!
	@def hsd
	@brief A macro to denote hsetd.
	@details This macro denotes hsetd.
*/
#define hsd hsetd



/*!
	The constructor.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hsetd<kye,mm,hfn,eqfn>::hsetd()
{
	WatchError
	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
	#else
		mSPKs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSPKs[tItr].First = mSPKs[tItr].Second = InvItr;
	#endif

	CatchError
}



/*!
	The initialiser.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hsetd<kye,mm,hfn,eqfn>::hsetd(mm const & theMm) : mMemMan(theMm)
{
	WatchError
	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
	#else
		mSPKs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSPKs[tItr].First = mSPKs[tItr].Second = InvItr;
	#endif

	CatchError
}



/*!
	The duplicator.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hsetd<kye,mm,hfn,eqfn>::hsetd(hsetd<kye,mm,hfn,eqfn> const & that) : mMemMan(that.mMemMan)
{
	WatchError

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mSucc[tItr] = that.mSucc[tItr];
			mPrec[tItr] = that.mPrec[tItr];
			mKeys[tItr] = that.mKeys[tItr];
		}
	#else
		mSPKs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mSPKs[tItr] = that.mSPKs[tItr];
		}
	#endif

	CatchError
}



/*!
	The assigner.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hsetd<kye,mm,hfn,eqfn> const & hsetd<kye,mm,hfn,eqfn>::operator =
		(hsetd<kye,mm,hfn,eqfn> const & that)
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
		#else
			delete [] mSPKs;
		#endif

		mHome = new Itr[that.mMemMan.acquired()];
		#if ParallelArray
			mSucc = new Itr[that.mMemMan.acquired()];
			mPrec = new Itr[that.mMemMan.acquired()];
			mKeys = new kye[that.mMemMan.acquired()];
		#else
			mSPKs = new t3<Itr,Itr,kye>[that.mMemMan.acquired()];
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
		#else
			mSPKs[tItr] = that.mSPKs[tItr];
		#endif
	}
	return *this;

	CatchError
}



/*!
	The destructor.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hsetd<kye,mm,hfn,eqfn>::~hsetd()
{
	WatchError

	delete [] mHome;
	#if ParallelArray
		delete [] mSucc;
		delete [] mPrec;
		delete [] mKeys;
	#else
		delete [] mSPKs;
	#endif

	CatchError
}



/*!
	Synchronise clock.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline void hsetd<kye,mm,hfn,eqfn>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}



/*!
	Clear the set, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetd<kye,mm,hfn,eqfn>::clear()
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
				Itr & tSucc = mSPKs[tItr].First;
				if (tSucc == InvItr) continue;
				Itr & tPrec = mSPKs[tItr].Second;
				if (tSucc <= tItr)
					mHome[hfn::iof(mSPKs[tItr].Third) % mMemMan.acquired()] = InvItr;
				tPrec = tSucc = InvItr;
			#endif
		}

	CatchError
}



/*!
	Clear the set, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetd<kye,mm,hfn,eqfn>::clearMem()
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
				Itr & tSucc = mSPKs[tItr].First;
				if (tSucc == InvItr) continue;
				Itr & tPrec = mSPKs[tItr].Second;
				if (tSucc <= tItr)
					mHome[hfn::iof(mSPKs[tItr].Third) % mMemMan.acquired()] = InvItr;
				tPrec = tSucc = InvItr;
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
void hsetd<kye,mm,hfn,eqfn>::insert(kye const & theKey)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
					return;
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
	#endif

	mMemMan.reoccupy();

	CatchError
}



/*!
	Insert a key, return whether successful, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetd<kye,mm,hfn,eqfn>::insertBll(kye const & theKey)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
					return false;
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
	#endif

	mMemMan.reoccupy();
	return true;

	CatchError
}



/*!
	Insert a key, return whether successful and the iterator, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetd<kye,mm,hfn,eqfn>::insertBll(kye const & theKey, Itr & theItr)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
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
Itr hsetd<kye,mm,hfn,eqfn>::insertItr(kye const & theKey)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
					return tItr2;
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}





/*!
	Insert a key and return the iterator if the key is new else InvItr, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetd<kye,mm,hfn,eqfn>::insertItrIfNew(kye const & theKey)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
					return InvItr;
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key and return the iterator if the key is old else InvItr, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetd<kye,mm,hfn,eqfn>::insertItrIfOld(kye const & theKey)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
					return tItr2;
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return InvItr;

	CatchError
}




/*!
	Insert a key, return whether successful, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetd<kye,mm,hfn,eqfn>::insertMem(kye const & theKey)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
					return;
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
	#endif

	mMemMan.reoccupy();

	CatchError
}



/*!
	Insert a key, return whether successful, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetd<kye,mm,hfn,eqfn>::insertBllMem(kye const & theKey)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
					return false;
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
	#endif

	mMemMan.reoccupy();
	return true;

	CatchError
}



/*!
	Insert a key, return whether successful and the iterator, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetd<kye,mm,hfn,eqfn>::insertBllMem(kye const & theKey, Itr & theItr)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
	#endif

	mMemMan.reoccupy();
	theItr = tItr3;
	return true;

	CatchError
}



/*!
	Insert a key and return the iterator, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetd<kye,mm,hfn,eqfn>::insertItrMem(kye const & theKey)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
					return tItr2;
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}





/*!
	Insert a key and return the iterator if the key is new else InvItr, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetd<kye,mm,hfn,eqfn>::insertItrIfNewMem(kye const & theKey)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
					return InvItr;
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key and return the iterator if the key is old else InvItr, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetd<kye,mm,hfn,eqfn>::insertItrIfOldMem(kye const & theKey)
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
				if (eqfn::iof(mSPKs[tItr2].Third, theKey))
					return tItr2;
				if (mSPKs[tItr2].First == tItr0)
					break;
				tItr2 = mSPKs[tItr2].First;
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
	#else
		while(mSPKs[tItr3].First != InvItr && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mSPKs[tItr3].First != InvItr)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (tItr2 == InvItr)
		{
			mHome[tItr1] = tItr3;
			mSPKs[tItr3].First = tItr3;
			mSPKs[tItr3].Second = tItr3;
		}
		else
		{
			mSPKs[tItr3].First = tItr0;
			mSPKs[tItr3].Second = tItr2;
			mSPKs[tItr2].First = tItr3;
			mSPKs[tItr0].Second = tItr3;
		}

		mSPKs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return InvItr;

	CatchError
}




/*!
	Remove a key and return the iterator when found, else InvItr, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetd<kye,mm,hfn,eqfn>::remove(kye const & theKey)
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
			if (eqfn::iof(mSPKs[tItr2].Third, theKey))
				break;
			if (mSPKs[tItr2].First == tItr0)
				return;
			tItr2 = mSPKs[tItr2].First;
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
		if (mSPKs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKs[tItr2].First;

			Itr tItr3 = mSPKs[tItr2].Second;
			Itr tItr4 = mSPKs[tItr2].First;
			mSPKs[tItr3].First = tItr4;
			mSPKs[tItr4].Second = tItr3;
		}

		mSPKs[tItr2].First = InvItr;
		mSPKs[tItr2].Second = InvItr;
	#endif

	mMemMan.unoccupy();

	CatchError
}


/*!
	Remove a key and return the iterator when found, else InvItr, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetd<kye,mm,hfn,eqfn>::removeBll(kye const & theKey)
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
			if (eqfn::iof(mSPKs[tItr2].Third, theKey))
				break;
			if (mSPKs[tItr2].First == tItr0)
				return false;
			tItr2 = mSPKs[tItr2].First;
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
		if (mSPKs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKs[tItr2].First;

			Itr tItr3 = mSPKs[tItr2].Second;
			Itr tItr4 = mSPKs[tItr2].First;
			mSPKs[tItr3].First = tItr4;
			mSPKs[tItr4].Second = tItr3;
		}

		mSPKs[tItr2].First = InvItr;
		mSPKs[tItr2].Second = InvItr;
	#endif

	mMemMan.unoccupy();
	return true;

	CatchError
}



/*!
	Remove a key and return the iterator when found, else InvItr, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetd<kye,mm,hfn,eqfn>::removeItr(kye const & theKey)
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
			if (eqfn::iof(mSPKs[tItr2].Third, theKey))
				break;
			if (mSPKs[tItr2].First == tItr0)
				return InvItr;
			tItr2 = mSPKs[tItr2].First;
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
		if (mSPKs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKs[tItr2].First;

			Itr tItr3 = mSPKs[tItr2].Second;
			Itr tItr4 = mSPKs[tItr2].First;
			mSPKs[tItr3].First = tItr4;
			mSPKs[tItr4].Second = tItr3;
		}

		mSPKs[tItr2].First = InvItr;
		mSPKs[tItr2].Second = InvItr;
	#endif

	mMemMan.unoccupy();
	return tItr2;

	CatchError
}



/*!
	Remove a key represented by an iterator and return whether succesfull, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetd<kye,mm,hfn,eqfn>::removeWithItr(Itr const theItr)
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
		if (mSPKs[theItr].First == InvItr) return;
		Itr tItr1 = hfn::iof(mSPKs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKs[theItr].First == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKs[theItr].First;

			Itr tItr3 = mSPKs[theItr].Second;
			Itr tItr4 = mSPKs[theItr].First;
			mSPKs[tItr3].First = tItr4;
			mSPKs[tItr4].Second = tItr3;
		}

		mSPKs[theItr].First = InvItr;
		mSPKs[theItr].Second = InvItr;
	#endif

	mMemMan.unoccupy();

	CatchError
}


/*!
	Remove a key represented by an iterator and return whether succesfull, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetd<kye,mm,hfn,eqfn>::removeBllWithItr(Itr const theItr)
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
		if (mSPKs[theItr].First == InvItr) return false;
		Itr tItr1 = hfn::iof(mSPKs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKs[theItr].First == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKs[theItr].First;

			Itr tItr3 = mSPKs[theItr].Second;
			Itr tItr4 = mSPKs[theItr].First;
			mSPKs[tItr3].First = tItr4;
			mSPKs[tItr4].Second = tItr3;
		}

		mSPKs[theItr].First = InvItr;
		mSPKs[theItr].Second = InvItr;
	#endif

	mMemMan.unoccupy();
	return true;

	CatchError
}




/*!
	Remove a key and return whether successful, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetd<kye,mm,hfn,eqfn>::removeMem(kye const & theKey)
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
			if (eqfn::iof(mSPKs[tItr2].Third, theKey))
				break;
			if (mSPKs[tItr2].First == tItr0)
				return;
			tItr2 = mSPKs[tItr2].First;
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
		if (mSPKs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKs[tItr2].First;

			Itr tItr3 = mSPKs[tItr2].Second;
			Itr tItr4 = mSPKs[tItr2].First;
			mSPKs[tItr3].First = tItr4;
			mSPKs[tItr4].Second = tItr3;
		}

		mSPKs[tItr2].First = InvItr;
		mSPKs[tItr2].Second = InvItr;
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
Bll hsetd<kye,mm,hfn,eqfn>::removeBllMem(kye const & theKey)
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
			if (eqfn::iof(mSPKs[tItr2].Third, theKey))
				break;
			if (mSPKs[tItr2].First == tItr0)
				return false;
			tItr2 = mSPKs[tItr2].First;
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
		if (mSPKs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKs[tItr2].First;

			Itr tItr3 = mSPKs[tItr2].Second;
			Itr tItr4 = mSPKs[tItr2].First;
			mSPKs[tItr3].First = tItr4;
			mSPKs[tItr4].Second = tItr3;
		}

		mSPKs[tItr2].First = InvItr;
		mSPKs[tItr2].Second = InvItr;
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
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetd<kye,mm,hfn,eqfn>::removeItrMem(kye const & theKey)
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
			if (eqfn::iof(mSPKs[tItr2].Third, theKey))
				break;
			if (mSPKs[tItr2].First == tItr0)
				return InvItr;
			tItr2 = mSPKs[tItr2].First;
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
		if (mSPKs[tItr2].First == tItr2)
			mHome[tItr1] = InvItr;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKs[tItr2].First;

			Itr tItr3 = mSPKs[tItr2].Second;
			Itr tItr4 = mSPKs[tItr2].First;
			mSPKs[tItr3].First = tItr4;
			mSPKs[tItr4].Second = tItr3;
		}

		mSPKs[tItr2].First = InvItr;
		mSPKs[tItr2].Second = InvItr;
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
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetd<kye,mm,hfn,eqfn>::removeWithItrMem(Itr const theItr)
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
		if (mSPKs[theItr].First == InvItr) return;
		Itr tItr1 = hfn::iof(mSPKs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKs[theItr].First == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKs[theItr].First;

			Itr tItr3 = mSPKs[theItr].Second;
			Itr tItr4 = mSPKs[theItr].First;
			mSPKs[tItr3].First = tItr4;
			mSPKs[tItr4].Second = tItr3;
		}

		mSPKs[theItr].First = InvItr;
		mSPKs[theItr].Second = InvItr;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Remove a key represented by an iterator and return whether succesfull, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetd<kye,mm,hfn,eqfn>::removeBllWithItrMem(Itr const theItr)
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
		if (mSPKs[theItr].First == InvItr) return false;
		Itr tItr1 = hfn::iof(mSPKs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKs[theItr].First == theItr)
			mHome[tItr1] = InvItr;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKs[theItr].First;

			Itr tItr3 = mSPKs[theItr].Second;
			Itr tItr4 = mSPKs[theItr].First;
			mSPKs[tItr3].First = tItr4;
			mSPKs[tItr4].Second = tItr3;
		}

		mSPKs[theItr].First = InvItr;
		mSPKs[theItr].Second = InvItr;
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
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetd<kye,mm,hfn,eqfn>::reallocMemAuto()
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

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
	#else
		t3<Itr,Itr,kye> * const tSPKIs = mSPKs;
		mSPKs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	#if ParallelArray
		mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
	#else
		mHome[tItr] = mSPKs[tItr].First = mSPKs[tItr].Second = InvItr;
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
			#else
				while(mSPKs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSPKs[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mSPKs[tItr2].First = tItr2;
				mSPKs[tItr2].Second = tItr2;
				mSPKs[tItr2].Third = tSPKIs[tItr].Third;
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
		#else
			while(mSPKs[tItr1].First != tItr0)
				tItr1 = mSPKs[tItr1].First;

			Itr tDiff = 1;
			Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

			while(mSPKs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSPKs[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSPKs[tItr2].First = tItr0;
			mSPKs[tItr2].Second = tItr1;
			mSPKs[tItr1].First = tItr2;
			mSPKs[tItr0].Second = tItr2;
			mSPKs[tItr2].Third = tSPKIs[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
	#else
		delete [] tSPKIs;
	#endif

	CatchError
}



/*!
	Deallocate memory automatically.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetd<kye,mm,hfn,eqfn>::deallocMemAuto()
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

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
	#else
		t3<Itr,Itr,kye> * const tSPKIs = mSPKs;
		mSPKs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
	#endif

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		#if ParallelArray
			mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
		#else
			mHome[tItr] = mSPKs[tItr].First = mSPKs[tItr].Second = InvItr;
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
			#else
				while(mSPKs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSPKs[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mSPKs[tItr2].First = tItr2;
				mSPKs[tItr2].Second = tItr2;
				mSPKs[tItr2].Third = tSPKIs[tItr].Third;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		Itr tItr0 = tItr1;
		#if ParallelArray
			while(mSucc[tItr1] != tItr0)
				tItr1 = mSucc[tItr1];
		#else
			while(mSPKs[tItr1].First != tItr0)
				tItr1 = mSPKs[tItr1].First;
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
		#else
			while(mSPKs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSPKs[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSPKs[tItr2].First = tItr0;
			mSPKs[tItr2].Second = tItr1;
			mSPKs[tItr1].First = tItr2;
			mSPKs[tItr0].Second = tItr2;

			mSPKs[tItr2].Third = tSPKIs[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
	#else
		delete [] tSPKIs;
	#endif

	CatchError
}



/*!
	Adjust the memory automatically.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetd<kye,mm,hfn,eqfn>::adjustMemAuto()
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

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
	#else
		t3<Itr,Itr,kye> * const tSPKIs = mSPKs;
		mSPKs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
	#endif

	#if ParallelArray
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
	#else
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSPKs[tItr].First = mSPKs[tItr].Second = InvItr;
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
			#else
				while(mSPKs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSPKs[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mSPKs[tItr2].First = tItr2;
				mSPKs[tItr2].Second = tItr2;
				mSPKs[tItr2].Third = tSPKIs[tItr].Third;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		Itr tItr0 = tItr1;

		#if ParallelArray
			while(mSucc[tItr1] != tItr0)
				tItr1 = mSucc[tItr1];
		#else
			while(mSPKs[tItr1].First != tItr0)
				tItr1 = mSPKs[tItr1].First;
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
		#else
			while(mSPKs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSPKs[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSPKs[tItr2].First = tItr0;
			mSPKs[tItr2].Second = tItr1;
			mSPKs[tItr1].First = tItr2;
			mSPKs[tItr1].Second = tItr2;
			mSPKs[tItr2].Third = tSPKIs[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
	#else
		delete [] tSPKIs;
	#endif

	CatchError
}



/*!
	Allocate memory.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetd<kye,mm,hfn,eqfn>::allocateMem(Dim const Alloc)
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

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
	#else
		t3<Itr,Itr,kye> * const tSPKIs = mSPKs;
		mSPKs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
	#endif

	#if ParallelArray
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSucc[tItr] = mPrec[tItr] = InvItr;
	#else
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mHome[tItr] = mSPKs[tItr].First = mSPKs[tItr].Second = InvItr;
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
			#else
				while(mSPKs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mSPKs[tItr2].First != InvItr)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mSPKs[tItr2].First = tItr2;
				mSPKs[tItr2].Second = tItr2;
				mSPKs[tItr2].Third = tSPKIs[tItr].Third;
			#endif
			continue;
		}

		tItr1 = mHome[tItr1];
		Itr tItr0 = tItr1;

		#if ParallelArray
			while(mSucc[tItr1] != tItr0)
				tItr1 = mSucc[tItr1];
		#else
			while(mSPKs[tItr1].First != tItr0)
				tItr1 = mSPKs[tItr1].First;
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
		#else
			while(mSPKs[tItr2].First != InvItr && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mSPKs[tItr2].First != InvItr)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mSPKs[tItr2].First = tItr0;
			mSPKs[tItr2].Second = tItr1;
			mSPKs[tItr1].First = tItr2;
			mSPKs[tItr1].Second = tItr2;
			mSPKs[tItr2].Third = tSPKIs[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
	#else
		delete [] tSPKIs;
	#endif

	CatchError
}




/*!
	Return the key count.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline Dim hsetd<kye,mm,hfn,eqfn>::keyCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the slot count.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline Dim hsetd<kye,mm,hfn,eqfn>::slotCount() const
{
	WatchError

	return mMemMan.acquired();

	CatchError
}



/*!
	Return the memory manager.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline mm const & hsetd<kye,mm,hfn,eqfn>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Whether the slot for the iterator is occupied.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline Bll hsetd<kye,mm,hfn,eqfn>::occupiedSlot(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mSucc[theItr] != InvItr;
	#else
		return mSPKs[theItr].First != InvItr;
	#endif

	CatchError
}



/*!
	Find a key in the set, or return InvItr if not found.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetd<kye,mm,hfn,eqfn>::findItr(kye const & theKey) const
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
			if (eqfn::iof(mSPKs[tItr].Third, theKey))
				return tItr;
			if (mSPKs[tItr].First == tItr0)
				return InvItr;
			tItr = mSPKs[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Find a key in the set and return whether found.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetd<kye,mm,hfn,eqfn>::findBll(kye const & theKey) const
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
			if (eqfn::iof(mSPKs[tItr].Third, theKey))
				return true;
			if (mSPKs[tItr].First == tItr0)
				return false;
			tItr = mSPKs[tItr].First;
		#endif
	}

	CatchError
}



/*!
	Return a key at a given iterator.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline kye const & hsetd<kye,mm,hfn,eqfn>::operator[](Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mKeys[theItr];
	#else
		return mSPKs[theItr].Third;
	#endif

	CatchError
}



/*!
	Return a key at a given iterator.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline kye const & hsetd<kye,mm,hfn,eqfn>::key(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		return mKeys[theItr];
	#else
		return mSPKs[theItr].Third;
	#endif

	CatchError
}



closeEmuSpace



#endif // HsetdTccIncluded
