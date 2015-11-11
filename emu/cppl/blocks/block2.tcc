/*!
	@file block2.tcc
	@brief The source file for the block2 template class.
	@details This is the source file for the block2 template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef Block2TccIncluded
#define Block2TccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class block2
	@brief A class to represent fixed-allocation fixed occupancy 2d arrays.
	@details This class represents fixed-allocation fixed occupancy 2d arrays.
*/
template <typename itm>
class block2
{
	public:

		typedef Nil MmTyp;													//!< Memory manager.

		~block2();															//!< Destructor.
		block2(block2<itm> const & that);									//!< Duplicator.
		block2(Dim const Rcount, Dim const Ccount);							//!< Initialiser.
		block2(itm const ** Items, Dim const Rcount, Dim const Ccount);		//!< Duplicator.
		block2<itm> const & operator = (block2<itm> const & that);			//!< Assigner.

		//! @name Synchronise
		//! @{

		void syncClk();										//!< Synchronise clock.

		//! @}
		//! @name Dimensions
		//! @{

		Dim rcount() const;										//!< Get the row count.
		Dim ccount() const;										//!< Get the column count.

		//! @}

		//! @name Items
		//! @{

		itm ** items();											//!< Get the items
		itm const ** items() const;								//!< Get the items.

		itm * items(Itr const Ritr);							//!< Get the items.
		itm const * items(Itr const Ritr) const;				//!< Get the items.

		itm * operator[](Itr const Ritr);						//!< Get the items.
		itm const * operator[](Itr const theItr) const;			//!< Get the items,

		itm & item(Itr const Ritr, Itr const Citr);				//!< Get an item.
		itm const & item(Itr const Ritr, Itr const Citr) const;	//!< Get an item.

		//! @}

	private:

		Dim const mRcount;	//!< Row count.
		Dim const mCcount;	//!< Column count.
		itm **	  mItems;	//!< The items.
};



/*!
	@def b2
	@brief A macro to denote block2.
	@details This macro denotes block2.
*/
#define b2 block2



/*!
	The initialiser.
*/
template<typename itm>
block2<itm>::block2(Dim const Rcount, Dim const Ccount) :
		mRcount(Rcount), mCcount(Ccount)
{
	WatchError

	//	Empty counts allowed.

	mItems = new itm * [mRcount];
	for(Itr tRitr = 0; tRitr < mRcount; ++tRitr)
	{
		mItems[tRitr] = new itm [mCcount];
		for(Itr tCitr = 0; tCitr < mCcount; ++tCitr)
			mItems[tRitr][tCitr] = itm();
	}
	CatchError
}



/*!
	The duplicator.
*/
template <typename itm>
block2<itm>::block2(block2<itm> const & that) :
		mRcount(that.mRcount), mCcount(that.mCcount)
{
	WatchError

	mItems = new itm * [mRcount];
	for(Itr tRitr = 0; tRitr < mRcount; ++tRitr)
	{
		mItems[tRitr] = new itm [mCcount];
		for(Itr tCitr = 0; tCitr < mCcount; ++tCitr)
			mItems[tRitr][tCitr] = that.mItems[tRitr][tCitr];
	}

	CatchError
}



/*!
	The duplicator.
*/
template <typename itm>
block2<itm>::block2(itm const ** Items, Dim const Rcount, Dim const Ccount) :
	mRcount(Rcount), mCcount(Ccount)
{
	WatchError

	// Empty count allowed.
	mItems = new itm * [mRcount];
	for(Itr tRitr = 0; tRitr < mRcount; ++tRitr)
	{
		mItems[tRitr] = new itm [mCcount];
		for(Itr tCitr = 0; tCitr < mCcount; ++tCitr)
			mItems[tRitr][tCitr] = Items[tRitr][tCitr];
	}

	CatchError
}



/*!
	The destructor.
*/
template <typename itm>
block2<itm>::~block2()
{
	WatchError

	for(Itr tRitr = 0; tRitr < mRcount; ++tRitr)
		delete [] mItems[tRitr];
	delete [] mItems;

	CatchError
}



/*!
	The assigner.
*/
template <typename itm>
block2<itm> const & block2<itm>::operator = (block2<itm> const & that)
{
	WatchError

	if (&that == this)
		return *this;

	Warn(mRcount != that.mRcount, eCountMismatch);
	Warn(mCcount != that.mCcount, eCountMismatch);

	for(Itr tRitr = 0; tRitr < mRcount; ++tRitr)
		for(Itr tCitr = 0; tCitr < mCcount; ++tCitr)
			mItems[tRitr][tCitr] = that.mItems[tRitr][tCitr];

	return *this;

	CatchError
}



/*!
	Synchronise clock.
*/
template <typename itm>
inline void block2<itm>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}



/*!
	Return the row count.
*/
template <typename itm>
inline Dim block2<itm>::rcount() const
{
	WatchError

	return mRcount;

	CatchError
}



/*!
	Return the column count.
*/
template <typename itm>
inline Dim block2<itm>::ccount() const
{
	WatchError

	return mCcount;

	CatchError
}



/*!
	Return the items, do not free memory with this.
*/
template <typename itm>
inline itm const ** block2<itm>::items() const
{
	WatchError

	return ccast<itm const **>(mItems);

	CatchError
}



/*!
	Return the items, do not free memory with this.
*/
template <typename itm>
inline itm ** block2<itm>::items()
{
	WatchError

	return mItems;

	CatchError
}



/*!
	Return the items, do not free memory with this.
*/
template <typename itm>
inline itm const * block2<itm>::items(Itr const Ritr) const
{
	WatchError

	Warn(Ritr >= mRcount, eIteratorBeyondLimit);

	return mItems[Ritr];

	CatchError
}



/*!
	Return the items, do not free memory with this.
*/
template <typename itm>
inline itm * block2<itm>::items(Itr const Ritr)
{
	WatchError

	Warn(Ritr >= mRcount, eIteratorBeyondLimit);

	return mItems[Ritr];

	CatchError
}



/*!
	Return the items; do not free memory with this.
*/
template <typename itm>
inline itm const * block2<itm>::operator[](Itr const Ritr) const
{
	WatchError

	Warn(Ritr >= mRcount, eIteratorBeyondLimit);

	return mItems[Ritr];

	CatchError
}



/*!
	Return an item.
*/
template <typename itm>
inline itm * block2<itm>::operator[](Itr const Ritr)
{
	WatchError

	Warn(Ritr >= mRcount, eIteratorBeyondLimit);

	return mItems[Ritr];

	CatchError
}



/*!
	Return an item.
*/
template <typename itm>
inline itm const & block2<itm>::item(Itr const Ritr, Itr const Citr) const
{
	WatchError

	Warn(Ritr >= mRcount, eIteratorBeyondLimit);
	Warn(Citr >= mCcount, eIteratorBeyondLimit);

	return mItems[Ritr][Citr];

	CatchError
}



/*!
	Return an item.
*/
template <typename itm>
inline itm & block2<itm>::item(Itr const Ritr, Itr const Citr)
{
	WatchError

	Warn(Ritr >= mRcount, eIteratorBeyondLimit);
	Warn(Citr >= mCcount, eIteratorBeyondLimit);

	return mItems[Ritr][Citr];

	CatchError
}



closeEmuSpace


#endif // Block2TccIncluded
