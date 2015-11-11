/*!
	@file hsetf.tcc
	@brief The source file for hsetf template class.
	@details This is the source file for hsetf template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef HsetfTccIncluded
#define HsetfTccIncluded



#include "cppl/roots/idx.hpp"
#include "cppl/opfns/idx.hpp"
#include "cppl/tuples/idx.hpp"


openEmuSpace



/*!
	@class hsetf
	@brief A class to represent hash sets with clocks and doubly linked list to enable *fast* reset and remove.
	@details This class represents hash sets with clocks and doubly linked list to enable *fast* reset and remove.
*/
template <typename kye, typename mm,
	typename hfn = hv<kye>, typename eqfn = eq<kye> >
class hsetf
{
	public:

		typedef mm MmTyp;								//!< Memory manager type.

		hsetf();										//!< Constructor.
		~hsetf();										//!< Destructor.
		hsetf(mm const & theMm);						//!< Initialiser.
		hsetf(hsetf<kye,mm,hfn,eqfn> const & that);		//!< Duplicator.
		hsetf<kye,mm,hfn,eqfn> const & operator =
				(hsetf<kye,mm,hfn,eqfn> const & that);	//!< Assigner.

		//! @name Synchronise
		//! @{

		void syncClk();	//!< Synchronise clock.

		//! @}

		//! @name Clear
		//! @{

		void clear();							//!< Clear keys only when needed, retaining available memory.
		void clear(Clk const theClk);			//!< Clear keys only when needed, retaining available memory.
		void clearMust();						//!< Clear keys mandatorily, retaining available memory.
		void clearMust(Clk const theClk);		//!< Clear keys mandatorily, retaining available memory.

		void clearMem();						//!< Clear keys only when needed, releasing memory when deemed.
		void clearMem(Clk const theClk);		//!< Clear keys only when needed, releasing memory when deemed.
		void clearMustMem();					//!< Clear keys mandatorily, releasing memory when deemed.
		void clearMustMem(Clk const theClk);	//!< Clear keys mandatorily, releasing memory when deemed.

		//! @}

		//! @name Insert
		//! @{

		void insert(kye const & theKye);					//!< Insert a key, assuming memory available.
		Bll insertBll(kye const & theKye);					//!< Insert a key, return whether successful, assuming memory available.
		Bll insertBll(kye const & theKye, Itr & theItr);	//!< Insert a key, return whether successful and the iterator, assuming memory available.
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

		void remove(kye const & theKey);			//!< Remove a key, retaining memory available.
		Bll removeBll(kye const & theKey);			//!< Remove a key and return whether successful, retaining memory available.
		Itr removeItr(kye const & theKey);			//!< Remove a key and return the iterator when found, else InvItr, retaining memory available.
		void removeWithItr(Itr const theItr);		//!< Remove a key represented by an iterator, retaining memory available.
		Bll removeBllWithItr(Itr const theItr);		//!< Remove a key represented by an iterator and return whether succesfull, retaining memory available.

		void removeMem(kye const & theKey);			//!< Remove a key, releasing memory when deemed.
		Bll removeBllMem(kye const & theKey);		//!< Remove a key and return whether successful, releasing memory when deemed.
		Itr removeItrMem(kye const & theKey);		//!< Remove a key and return the iterator when found, else InvItr, releasing memory when deemed.
		void removeWithItrMem(Itr const theItr);	//!< Remove a key represented by an iterator, releasing memory when deemed.
		Bll removeBllWithItrMem(Itr const theItr);	//!< Remove a key represented by an iterator and return whether succesfull, releasing memory when deemed.

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

		mm	mMemMan;							//!< Memory manager.

		Dim mClk;								//!< Clock of the hset.

		Itr * mHome;							//!< Itr of home keys.
		#if ParallelArray
			Itr * mSucc;						//!< Itr of successor keys.
			Itr * mPrec;						//!< Itr of predecessor keys.
			kye * mKeys;						//!< The array of keys.
			Clk * mClkHs;						//!< The clocks for home.
			Clk * mClkKs;						//!< The clocks for keys.
		#else
			t3<Itr,Itr,kye> * mSPKIs;		//!< The array of succ, prec, key.
			t2<Clk,Clk> * mClkHKs;				//!< The clocks for home and keys.
		#endif
};



/*!
	@def hsf
	@brief A macro to denote hsetf.
	@details This macro denotes hsetf.
*/
#define hsf hsetf



/*!
	The constructor.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hsetf<kye,mm,hfn,eqfn>::hsetf() : mClk(NotClk)
{
	WatchError
	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];

		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHs[tItr] = mClkKs[tItr] = EndClk;
	#else
		mSPKIs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHKs[tItr].First = mClkHKs[tItr].Second = EndClk;
	#endif

	CatchError
}



/*!
	The initialiser.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hsetf<kye,mm,hfn,eqfn>::hsetf(mm const & theMm) : mMemMan(theMm), mClk(NotClk)
{
	WatchError
	Alert(mMemMan.LoadDenom <= mMemMan.LoadNumer, eUnsuitMemoryManager);
	Alert(!mMemMan.LoadNumer, eUnsuitMemoryManager);

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];

		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHs[tItr] = mClkKs[tItr] = EndClk;
	#else
		mSPKIs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHKs[tItr].First = mClkHKs[tItr].Second = EndClk;
	#endif

	CatchError
}



/*!
	The duplicator.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hsetf<kye,mm,hfn,eqfn>::hsetf(hsetf<kye,mm,hfn,eqfn> const & that) :
		mMemMan(that.mMemMan), mClk(that.mClk)
{
	WatchError

	mHome = new Itr[mMemMan.acquired()];
	#if ParallelArray
		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mSucc[tItr] = that.mSucc[tItr];
			mPrec[tItr] = that.mPrec[tItr];
			mKeys[tItr] = that.mKeys[tItr];
			mClkKs[tItr] = that.mClkKs[tItr];
			mClkHs[tItr] = that.mClkHs[tItr];
		}
	#else
		mSPKIs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
		{
			mHome[tItr] = that.mHome[tItr];
			mSPKIs[tItr] = that.mSPKIs[tItr];
			mClkHKs[tItr] = that.mClkHKs[tItr];
		}
	#endif

	CatchError
}



/*!
	The assigner.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hsetf<kye,mm,hfn,eqfn> const & hsetf<kye,mm,hfn,eqfn>::operator =
		(hsetf<kye,mm,hfn,eqfn> const & that)
{
	WatchError

	if (this == &that)
		return *this;

	if (mMemMan.acquired() != that.mMemMan.acquired())
	{
		delete [] mHome;
		#if ParallelArray
			delete [] mSucc;
			delete [] mPrec;
			delete [] mKeys;
			delete [] mClkHs;
			delete [] mClkKs;
		#else
			delete [] mSPKIs;
			delete [] mClkHKs;
		#endif

		mHome = new Itr[that.mMemMan.acquired()];
		#if ParallelArray
			mSucc = new Itr[that.mMemMan.acquired()];
			mPrec = new Itr[that.mMemMan.acquired()];
			mKeys = new kye[that.mMemMan.acquired()];
			mClkHs = new Clk[that.mMemMan.acquired()];
			mClkKs = new Clk[that.mMemMan.acquired()];
		#else
			mSPKIs = new t3<Itr,Itr,kye>[that.mMemMan.acquired()];
			mClkHKs = new t2<Clk,Clk>[that.mMemMan.acquired()];
		#endif
	}

	mMemMan = that.mMemMan;
	mClk = that.mClk;

	for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
	{
		mHome[tItr] = that.mHome[tItr];
		#if ParallelArray
			mSucc[tItr] = that.mSucc[tItr];
			mPrec[tItr] = that.mPrec[tItr];
			mKeys[tItr] = that.mKeys[tItr];
			mClkHs[tItr] = that.mClkHs[tItr];
			mClkKs[tItr] = that.mClkKs[tItr];
		#else
			mSPKIs[tItr] = that.mSPKIs[tItr];
			mClkHKs[tItr] = that.mClkHKs[tItr];
		#endif
	}
	return *this;

	CatchError
}



/*!
	The destructor.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
hsetf<kye,mm,hfn,eqfn>::~hsetf()
{
	WatchError

	delete [] mHome;
	#if ParallelArray
		delete [] mSucc;
		delete [] mPrec;
		delete [] mKeys;
		delete [] mClkHs;
		delete [] mClkKs;
	#else
		delete [] mSPKIs;
		delete [] mClkHKs;
	#endif

	CatchError
}



/*!
	Synchronize the clock.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::syncClk()
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
	Clear the set when needed, retaining available memory.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::clear()
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
	Clear the set with a new clock, retaining available memory.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::clearMust()
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
	Clear the set when needed, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::clearMem()
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
	Clear the set with a new clock, release memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::clearMustMem()
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
	Clear the set when needed with the given clock, retaining available memory.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::clear(Clk const theClk)
{
	WatchError

	Warn(mClk == theClk, eClockConflict);
	if (mMemMan.resetOccupyBll())
		mClk = theClk;

	CatchError
}



/*!
	Clear the set mandatorily with the given clock, retaining available memory.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::clearMust(Clk const theClk)
{
	WatchError

	Warn(mClk == theClk, eClockConflict);
	mMemMan.resetOccupy();
	mClk = theClk;

	CatchError
}



/*!
	Clear the set when needed with the given clock, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::clearMem(Clk const theClk)
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
	Clear the set mandatorily with the given clock, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::clearMustMem(Clk const theClk)
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
	Insert a key, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::insert(kye const & theKey)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
				if (mSucc[tItr2] == tItr0) break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return;
				if (mSPKIs[tItr2].First == tItr0) break;
				tItr2 = mSPKIs[tItr2].First;
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
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();

	CatchError
}



/*!
	Insert a key, return whether successful, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetf<kye,mm,hfn,eqfn>::insertBll(kye const & theKey)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
				if (mSucc[tItr2] == tItr0) break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return false;
				if (mSPKIs[tItr2].First == tItr0) break;
				tItr2 = mSPKIs[tItr2].First;
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
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return true;

	CatchError
}



/*!
	Insert a key, return whether successful and the iterator, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetf<kye,mm,hfn,eqfn>::insertBll(kye const & theKey, Itr & theItr)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
				if (mSucc[tItr2] == tItr0) break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mSPKIs[tItr2].First == tItr0) break;
				tItr2 = mSPKIs[tItr2].First;
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
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
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
Itr hsetf<kye,mm,hfn,eqfn>::insertItr(kye const & theKey)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key and return the iterator when the key is new else return InvItr, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetf<kye,mm,hfn,eqfn>::insertItrIfNew(kye const & theKey)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key and return the iterator when the key is old else return InvItr, assuming memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetf<kye,mm,hfn,eqfn>::insertItrIfOld(kye const & theKey)
{
	WatchError

	Warn(mMemMan.fullyOccupied(), eAllocatedMemoryFull);

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return InvItr;

	CatchError
}



/*!
	Insert a key, return whether successful, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::insertMem(kye const & theKey)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
				if (mSucc[tItr2] == tItr0) break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return;
				if (mSPKIs[tItr2].First == tItr0) break;
				tItr2 = mSPKIs[tItr2].First;
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
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();

	CatchError
}



/*!
	Insert a key, return whether successful, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetf<kye,mm,hfn,eqfn>::insertBllMem(kye const & theKey)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
				if (mSucc[tItr2] == tItr0) break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
					return false;
				if (mSPKIs[tItr2].First == tItr0) break;
				tItr2 = mSPKIs[tItr2].First;
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
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return true;

	CatchError
}



/*!
	Insert a key, return whether successful and the iterator, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetf<kye,mm,hfn,eqfn>::insertBllMem(kye const & theKey, Itr & theItr)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
				if (mSucc[tItr2] == tItr0) break;
				tItr2 = mSucc[tItr2];
			#else
				if (eqfn::iof(mSPKIs[tItr2].Third, theKey))
				{
					theItr = tItr2;
					return false;
				}
				if (mSPKIs[tItr2].First == tItr0) break;
				tItr2 = mSPKIs[tItr2].First;
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
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
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
Itr hsetf<kye,mm,hfn,eqfn>::insertItrMem(kye const & theKey)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key and return the iterator when the key is new else return InvItr, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetf<kye,mm,hfn,eqfn>::insertItrIfNewMem(kye const & theKey)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return tItr3;

	CatchError
}



/*!
	Insert a key and return the iterator when the key is old else return InvItr, acquiring memory when needed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetf<kye,mm,hfn,eqfn>::insertItrIfOldMem(kye const & theKey)
{
	WatchError

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	Itr tItr0 = tItr2, tItr3, tDiff = 1;

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
		while(mClkKs[tItr3] == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkKs[tItr3] == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHs[tItr1] != mClk)
		{
			mClkHs[tItr1] = mClk;
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

		mClkKs[tItr3] = mClk;
		mKeys[tItr3] = theKey;
	#else
		while(mClkHKs[tItr3].Second == mClk && tDiff < mMemMan.acquired())
			tItr3 = (tItr3 + tDiff++) % mMemMan.acquired();

		while(mClkHKs[tItr3].Second == mClk)
			tItr3 = (tItr3 + 1) % mMemMan.acquired();

		if (mClkHKs[tItr1].First != mClk)
		{
			mHome[tItr1] = tItr3;
			mClkHKs[tItr1].First = mClk;
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

		mClkHKs[tItr3].Second = mClk;
		mSPKIs[tItr3].Third = theKey;
	#endif
	mMemMan.reoccupy();
	return InvItr;

	CatchError
}



/*!
	Remove a key in the set, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::remove(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return;
	#else
		if (mClkHKs[tItr1].First != mClk) return;
	#endif
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
			mClkHs[tItr1] = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mClkKs[tItr2] = NotClk;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mClkHKs[tItr1].First = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mClkHKs[tItr2].Second = NotClk;
	#endif

	mMemMan.unoccupy();

	CatchError
}



/*!
	Remove a key in the set and whether successful, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetf<kye,mm,hfn,eqfn>::removeBll(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return false;
	#else
		if (mClkHKs[tItr1].First != mClk) return false;
	#endif
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
			mClkHs[tItr1] = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mClkKs[tItr2] = NotClk;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mClkHKs[tItr1].First = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mClkHKs[tItr2].Second = NotClk;
	#endif

	mMemMan.unoccupy();
	return true;

	CatchError
}



/*!
	Remove a key in the set and if found return the iterator, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetf<kye,mm,hfn,eqfn>::removeItr(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return InvItr;
	#else
		if (mClkHKs[tItr1].First != mClk) return InvItr;
	#endif
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
			mClkHs[tItr1] = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mClkKs[tItr2] = NotClk;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mClkHKs[tItr1].First = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mClkHKs[tItr2].Second = NotClk;
	#endif

	mMemMan.unoccupy();
	return tItr2;

	CatchError
}



/*!
	Remove a key represented by an iterator, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::removeWithItr(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		if (mClkKs[theItr] != mClk) return;

		Itr tItr1 = hfn::iof(mKeys[theItr]) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSucc[theItr] == theItr)
			mClkHs[tItr1] = NotClk;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSucc[theItr];

			Itr tItr3 = mPrec[theItr];
			Itr tItr4 = mSucc[theItr];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mClkKs[theItr] = NotClk;
	#else
		if (mClkHKs[theItr].Second != mClk) return;
		Itr tItr1 = hfn::iof(mSPKIs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKIs[theItr].First == theItr)
			mClkHKs[tItr1].First = NotClk;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKIs[theItr].First;

			Itr tItr3 = mSPKIs[theItr].Second;
			Itr tItr4 = mSPKIs[theItr].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mClkHKs[theItr].Second = NotClk;
	#endif

	mMemMan.unoccupy();

	CatchError
}



/*!
	Remove a key represented by an iterator and return whether succesfull, retaining memory available.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetf<kye,mm,hfn,eqfn>::removeBllWithItr(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		if (mClkKs[theItr] != mClk) return false;

		Itr tItr1 = hfn::iof(mKeys[theItr]) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSucc[theItr] == theItr)
			mClkHs[tItr1] = NotClk;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSucc[theItr];

			Itr tItr3 = mPrec[theItr];
			Itr tItr4 = mSucc[theItr];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mClkKs[theItr] = NotClk;
	#else
		if (mClkHKs[theItr].Second != mClk) return false;
		Itr tItr1 = hfn::iof(mSPKIs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKIs[theItr].First == theItr)
			mClkHKs[tItr1].First = NotClk;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKIs[theItr].First;

			Itr tItr3 = mSPKIs[theItr].Second;
			Itr tItr4 = mSPKIs[theItr].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mClkHKs[theItr].Second = NotClk;
	#endif

	mMemMan.unoccupy();

	return true;

	CatchError
}



/*!
	Remove a key in the set, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::removeMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return;
	#else
		if (mClkHKs[tItr1].First != mClk) return;
	#endif
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
			mClkHs[tItr1] = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mClkKs[tItr2] = NotClk;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mClkHKs[tItr1].First = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mClkHKs[tItr2].Second = NotClk;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	CatchError
}



/*!
	Remove a key in the set and return whether successful, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetf<kye,mm,hfn,eqfn>::removeBllMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return false;
	#else
		if (mClkHKs[tItr1].First != mClk) return false;
	#endif
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
			mClkHs[tItr1] = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mClkKs[tItr2] = NotClk;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mClkHKs[tItr1].First = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mClkHKs[tItr2].Second = NotClk;
	#endif

	mMemMan.unoccupy();

	if (mMemMan.needAutoDealloc())
		deallocMemAuto();

	return true;

	CatchError
}



/*!
	Remove a key in the set and if found return the iterator, releasing memory when deemed.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetf<kye,mm,hfn,eqfn>::removeItrMem(kye const & theKey)
{
	WatchError

	Itr tItr1 = hfn::iof(theKey) % mMemMan.acquired();
	Itr tItr2 = mHome[tItr1];
	#if ParallelArray
		if (mClkHs[tItr1] != mClk) return InvItr;
	#else
		if (mClkHKs[tItr1].First != mClk) return InvItr;
	#endif
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
			mClkHs[tItr1] = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSucc[tItr2];

			Itr tItr3 = mPrec[tItr2];
			Itr tItr4 = mSucc[tItr2];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mClkKs[tItr2] = NotClk;
	#else
		if (mSPKIs[tItr2].First == tItr2)
			mClkHKs[tItr1].First = NotClk;
		else
		{
			if (tItr2 == tItr0)
				mHome[tItr1] = mSPKIs[tItr2].First;

			Itr tItr3 = mSPKIs[tItr2].Second;
			Itr tItr4 = mSPKIs[tItr2].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mClkHKs[tItr2].Second = NotClk;
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
void hsetf<kye,mm,hfn,eqfn>::removeWithItrMem(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		if (mClkKs[theItr] != mClk) return;

		Itr tItr1 = hfn::iof(mKeys[theItr]) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSucc[theItr] == theItr)
			mClkHs[tItr1] = NotClk;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSucc[theItr];

			Itr tItr3 = mPrec[theItr];
			Itr tItr4 = mSucc[theItr];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mClkKs[theItr] = NotClk;
	#else
		if (mClkHKs[theItr].Second != mClk) return;
		Itr tItr1 = hfn::iof(mSPKIs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKIs[theItr].First == theItr)
			mClkHKs[tItr1].First = NotClk;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKIs[theItr].First;

			Itr tItr3 = mSPKIs[theItr].Second;
			Itr tItr4 = mSPKIs[theItr].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mClkHKs[theItr].Second = NotClk;
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
Bll hsetf<kye,mm,hfn,eqfn>::removeBllWithItrMem(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondAcquired(theItr), eIteratorBeyondLimit);

	#if ParallelArray
		if (mClkKs[theItr] != mClk) return false;

		Itr tItr1 = hfn::iof(mKeys[theItr]) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSucc[theItr] == theItr)
			mClkHs[tItr1] = NotClk;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSucc[theItr];

			Itr tItr3 = mPrec[theItr];
			Itr tItr4 = mSucc[theItr];
			mSucc[tItr3] = tItr4;
			mPrec[tItr4] = tItr3;
		}

		mClkKs[theItr] = NotClk;
	#else
		if (mClkHKs[theItr].Second != mClk) return false;
		Itr tItr1 = hfn::iof(mSPKIs[theItr].Third) % mMemMan.acquired();
		Itr tItr0 = mHome[tItr1];

		if (mSPKIs[theItr].First == theItr)
			mClkHKs[tItr1].First = NotClk;
		else
		{
			if (theItr == tItr0)
				mHome[tItr1] = mSPKIs[theItr].First;

			Itr tItr3 = mSPKIs[theItr].Second;
			Itr tItr4 = mSPKIs[theItr].First;
			mSPKIs[tItr3].First = tItr4;
			mSPKIs[tItr4].Second = tItr3;
		}

		mClkHKs[theItr].Second = NotClk;
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
void hsetf<kye,mm,hfn,eqfn>::reallocMemAuto()
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
		Clk * const tClkHs = mClkHs;
		Clk * const tClkKs = mClkKs;

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];
	#else
		t3<Itr,Itr,kye> * const tSPKIs = mSPKIs;
		t2<Clk,Clk> * const tClkHKs = mClkHKs;
		mSPKIs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
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
			Itr tItr1 = hfn::iof(tSPKIs[tItr].Third) % mMemMan.acquired();
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
				mSucc[tItr2] = tItr2;
				mPrec[tItr2] = tItr2;
				mKeys[tItr2] = tKeys[tItr];
			#else
				while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkHKs[tItr2].Second == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHKs[tItr1].First = mClk;
				mClkHKs[tItr2].Second = mClk;
				mSPKIs[tItr2].First = tItr2;
				mSPKIs[tItr2].Second = tItr2;
				mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
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

			while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkKs[tItr2] == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkKs[tItr2] = mClk;
			mSucc[tItr2] = tItr0;
			mPrec[tItr2] = tItr1;
			mSucc[tItr1] = tItr2;
			mPrec[tItr0] = tItr2;

			mKeys[tItr2] = tKeys[tItr];
		#else
			while(mSPKIs[tItr1].First != tItr0)
				tItr1 = mSPKIs[tItr1].First;

			Itr tDiff = 1;
			Itr tItr2 = (tItr1 + tDiff) % mMemMan.acquired();

			while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkHKs[tItr2].Second == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkHKs[tItr2].Second = mClk;
			mSPKIs[tItr2].First = tItr0;
			mSPKIs[tItr2].Second = tItr1;
			mSPKIs[tItr1].First = tItr2;
			mSPKIs[tItr0].Second = tItr2;
			mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
		delete [] tClkHs;
		delete [] tClkKs;
	#else
		delete [] tSPKIs;
		delete [] tClkHKs;
	#endif

	CatchError
}



/*!
	Deallocate memory automatically
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::deallocMemAuto()
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
		Clk * const tClkHs = mClkHs;
		Clk * const tClkKs = mClkKs;

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];
	#else
		t3<Itr,Itr,kye> * const tSPKIs = mSPKIs;
		t2<Clk,Clk> * const tClkHKs = mClkHKs;
		mSPKIs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
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
			Itr tItr1 = hfn::iof(tSPKIs[tItr].Third) % mMemMan.acquired();
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
				mSucc[tItr2] = tItr2;
				mPrec[tItr2] = tItr2;
				mKeys[tItr2] = tKeys[tItr];
			#else
				while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkHKs[tItr2].Second == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHKs[tItr1].First = mClk;
				mClkHKs[tItr2].Second = mClk;
				mSPKIs[tItr2].First = tItr2;
				mSPKIs[tItr2].Second = tItr2;
				mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
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
			while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkKs[tItr2] == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkKs[tItr2] = mClk;
			mSucc[tItr2] = tItr0;
			mPrec[tItr2] = tItr1;
			mSucc[tItr1] = tItr2;
			mSucc[tItr0] = tItr2;

			mKeys[tItr2] = tKeys[tItr];
		#else
			while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkHKs[tItr2].Second == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkHKs[tItr2].Second = mClk;
			mSPKIs[tItr2].First = tItr0;
			mSPKIs[tItr2].Second = tItr1;
			mSPKIs[tItr1].First = tItr2;
			mSPKIs[tItr0].Second = tItr2;

			mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
		delete [] tClkHs;
		delete [] tClkKs;
	#else
		delete [] tSPKIs;
		delete [] tClkHKs;
	#endif

	CatchError
}



/*!
	Adjust the memory automatically.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::adjustMemAuto()
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
		Clk * const tClkHs = mClkHs;
		Clk * const tClkKs = mClkKs;

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];
	#else
		t3<Itr,Itr,kye> * const tSPKIs = mSPKIs;
		t2<Clk,Clk> * const tClkHKs = mClkHKs;
		mSPKIs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
	#endif

	#if ParallelArray
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHs[tItr] = mClkKs[tItr] = EndClk;
	#else
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHKs[tItr].First = mClkHKs[tItr].Second = EndClk;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tClkKs[tItr] != mClk) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tClkHKs[tItr].Second != mClk) continue;
			Itr tItr1 = hfn::iof(tSPKIs[tItr].Third) % mMemMan.acquired();
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

				mSucc[tItr2] = tItr2;
				mPrec[tItr2] = tItr2;
				mKeys[tItr2] = tKeys[tItr];
			#else
				while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkHKs[tItr2].Second == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHKs[tItr1].First = mClk;
				mClkHKs[tItr2].Second = mClk;
				mSPKIs[tItr2].First = tItr2;
				mSPKIs[tItr2].Second = tItr2;
				mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
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
			while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkKs[tItr2] == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkKs[tItr2] = mClk;
			mSucc[tItr2] = tItr0;
			mPrec[tItr2] = tItr1;
			mSucc[tItr1] = tItr2;
			mSucc[tItr0] = tItr2;
			mKeys[tItr2] = tKeys[tItr];
		#else
			while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkHKs[tItr2].Second == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkHKs[tItr2].Second = mClk;
			mSPKIs[tItr2].First = tItr0;
			mSPKIs[tItr2].Second = tItr1;
			mSPKIs[tItr1].First = tItr2;
			mSPKIs[tItr1].Second = tItr2;
			mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
		delete [] tClkHs;
		delete [] tClkKs;
	#else
		delete [] tSPKIs;
		delete [] tClkHKs;
	#endif

	CatchError
}



/*!
	Allocate memory.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
void hsetf<kye,mm,hfn,eqfn>::allocateMem(Dim const Alloc)
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
		Clk * const tClkHs = mClkHs;
		Clk * const tClkKs = mClkKs;

		mSucc = new Itr[mMemMan.acquired()];
		mPrec = new Itr[mMemMan.acquired()];
		mKeys = new kye[mMemMan.acquired()];
		mClkHs = new Clk[mMemMan.acquired()];
		mClkKs = new Clk[mMemMan.acquired()];
	#else
		t3<Itr,Itr,kye> * const tSPKIs = mSPKIs;
		t2<Clk,Clk> * const tClkHKs = mClkHKs;
		mSPKIs = new t3<Itr,Itr,kye>[mMemMan.acquired()];
		mClkHKs = new t2<Clk,Clk>[mMemMan.acquired()];
	#endif

	#if ParallelArray
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHs[tItr] = mClkKs[tItr] = EndClk;
	#else
		for(Itr tItr = 0; tItr < mMemMan.acquired(); ++tItr)
			mClkHKs[tItr].First = mClkHKs[tItr].Second = EndClk;
	#endif

	for (Itr tItr = 0; tItr < tAcquired; ++tItr)
	{
		#if ParallelArray
			if (tClkKs[tItr] != mClk) continue;
			Itr tItr1 = hfn::iof(tKeys[tItr]) % mMemMan.acquired();
		#else
			if (tClkHKs[tItr].Second != mClk) continue;
			Itr tItr1 = hfn::iof(tSPKIs[tItr].Third) % mMemMan.acquired();
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

				mSucc[tItr2] = tItr2;
				mPrec[tItr2] = tItr2;
				mKeys[tItr2] = tKeys[tItr];
			#else
				while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
					tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();
				while(mClkHKs[tItr2].Second == mClk)
					tItr2 = (tItr2 + 1) % mMemMan.acquired();

				mHome[tItr1] = tItr2;
				mClkHKs[tItr1].First = mClk;
				mClkHKs[tItr2].Second = mClk;
				mSPKIs[tItr2].First = tItr2;
				mSPKIs[tItr2].Second = tItr2;
				mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
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
			while(mClkKs[tItr2] == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkKs[tItr2] == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkKs[tItr2] = mClk;
			mSucc[tItr2] = tItr0;
			mPrec[tItr2] = tItr1;
			mSucc[tItr1] = tItr2;
			mSucc[tItr0] = tItr2;
			mKeys[tItr2] = tKeys[tItr];
		#else
			while(mClkHKs[tItr2].Second == mClk && tDiff < mMemMan.acquired())
				tItr2 = (tItr2 + tDiff++) % mMemMan.acquired();

			while(mClkHKs[tItr2].Second == mClk)
				tItr2 = (tItr2 + 1) % mMemMan.acquired();

			mClkHKs[tItr2].Second = mClk;
			mSPKIs[tItr2].First = tItr0;
			mSPKIs[tItr2].Second = tItr1;
			mSPKIs[tItr1].First = tItr2;
			mSPKIs[tItr1].Second = tItr2;
			mSPKIs[tItr2].Third = tSPKIs[tItr].Third;
		#endif
	}

	delete [] tHome;
	#if ParallelArray
		delete [] tSucc;
		delete [] tPrec;
		delete [] tKeys;
		delete [] tClkHs;
		delete [] tClkKs;
	#else
		delete [] tSPKIs;
		delete [] tClkHKs;
	#endif

	CatchError
}



/*!
	Return the key count.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline Dim hsetf<kye,mm,hfn,eqfn>::keyCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the slot count.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline Dim hsetf<kye,mm,hfn,eqfn>::slotCount() const
{
	WatchError

	return mMemMan.acquired();

	CatchError
}



/*!
	Return the memory manager.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline mm const & hsetf<kye,mm,hfn,eqfn>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Return whether the slot at a given iterator is valid.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
inline Bll hsetf<kye,mm,hfn,eqfn>::occupiedSlot(Itr const theItr) const
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
	Find a key in the set and return the iterator if found, else return InvItr.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Itr hsetf<kye,mm,hfn,eqfn>::findItr(kye const & theKey) const
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();
	#if ParallelArray
	if (mClkHs[tItr] != mClk) return InvItr;
	#else
	if (mClkHKs[tItr].First != mClk) return InvItr;
	#endif
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
	Find a key in the set and return whether found.
*/
template<typename kye, typename mm, typename hfn, typename eqfn>
Bll hsetf<kye,mm,hfn,eqfn>::findBll(kye const & theKey) const
{
	WatchError

	Itr tItr = hfn::iof(theKey) % mMemMan.acquired();
	#if ParallelArray
	if (mClkHs[tItr] != mClk) return false;
	#else
	if (mClkHKs[tItr].First != mClk) return false;
	#endif
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
template<typename kye, typename mm, typename hfn, typename eqfn>
inline kye const & hsetf<kye,mm,hfn,eqfn>::operator[](Itr const theItr) const
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
template<typename kye, typename mm, typename hfn, typename eqfn>
inline kye const & hsetf<kye,mm,hfn,eqfn>::key(Itr const theItr) const
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




closeEmuSpace



#endif // HsetfTccIncluded
