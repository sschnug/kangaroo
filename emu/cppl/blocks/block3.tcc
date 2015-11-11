/*!
	@file block3.tcc
	@brief The source file for the block3 template class.
	@details This is the source file for the block3 template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef Block3TccIncluded
#define Block3TccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class block3
	@brief A class to represent fixed-allocation fixed occupancy 3d arrays.
	@details This class represents fixed-allocation fixed occupancy 3d arrays.
*/
template <typename itm>
class block3
{
	public:

		typedef Nil MmTyp;											//!< Memory manager.

		~block3();													//!< Destructor.
		block3(block3<itm> const & that);							//!< Duplicator.
		block3(Dim const Zcount, Dim const Ycount, Dim const Xcount);	//!< Initialiser.
		block3(itm const *** Items,
				Dim const Zcount, Dim const Ycount, Dim const Xcount);	//!< Duplicator.
		block3<itm> const & operator = (block3<itm> const & that);	//!< Assigner.

		//! @name Synchronise
		//! @{

		void syncClk();										//!< Synchronise clock.

		//! @}
		//! @name Dimensions
		//! @{

		Dim xcount() const;										//!< Get the x-count.
		Dim ycount() const;										//!< Get the y-count.
		Dim zcount() const;										//!< Get the z-count.

		//! @}

		//! @name Items
		//! @{

		itm *** items();										//!< Get the items
		itm const *** items() const;							//!< Get the items.

		itm ** items(Itr const Zitr);							//!< Get the items.
		itm const ** items(Itr const Zitr) const;				//!< Get the items.

		itm ** operator[](Itr const Zitr);						//!< Get the items.
		itm const ** operator[](Itr const Zitr) const;			//!< Get the items.

		itm * items(Itr const Zitr, Itr const Yitr);			//!< Get the items.
		itm const * items(Itr const Zitr, Itr const Yitr) const;//!< Get the items.

		itm & item(Itr const Zitr, Itr const Yitr, Itr const Xitr);				//!< Get an item.
		itm const & item(Itr const Zitr, Itr const Yitr, Itr const Xitr) const;	//!< Get an item.

		//! @}

	private:

		Dim const mZcount;	//!< Zcount.
		Dim const mYcount;	//!< Ycount.
		Dim const mXcount;	//!< Xcount.
		itm ***	  mItems;	//!< The items.
};



/*!
	@def b3
	@brief A macro to denote block3.
	@details This macro denotes block3.
*/
#define b3 block3



/*!
	The initialiser.
*/
template<typename itm>
block3<itm>::block3(Dim const Zcount, Dim const Ycount, Dim const Xcount) :
		mZcount(Zcount), mYcount(Ycount), mXcount(Xcount)
{
	WatchError

	//	Empty counts allowed.

	mItems = new itm ** [mZcount];
	for(Itr tZitr = 0; tZitr < mZcount; ++tZitr)
	{
		mItems[tZitr] = new itm * [mYcount];
		for(Itr tYitr = 0; tYitr < mYcount; ++tYitr)
		{
			mItems[tZitr][tYitr] = new itm [mXcount];
			for(Itr tXitr = 0; tXitr < mXcount; ++tXitr)
				mItems[tZitr][tYitr][tXitr] = itm();
		}
	}
	CatchError
}



/*!
	The duplicator.
*/
template <typename itm>
block3<itm>::block3(block3<itm> const & that) :
		mZcount(that.mZcount), mYcount(that.mYcount), mXcount(that.mXcount)
{
	WatchError

	mItems = new itm ** [mZcount];
	for(Itr tZitr = 0; tZitr < mZcount; ++tZitr)
	{
		mItems[tZitr] = new itm * [mYcount];
		for(Itr tYitr = 0; tYitr < mYcount; ++tYitr)
		{
			mItems[tZitr][tYitr] = new itm [mXcount];
			for(Itr tXitr = 0; tXitr < mXcount; ++tXitr)
				mItems[tZitr][tYitr][tXitr] = that.mItems[tZitr][tYitr][tXitr];
		}
	}

	CatchError
}



/*!
	The duplicator.
*/
template <typename itm>
block3<itm>::block3(itm const *** Items, Dim const Zcount,
	Dim const Ycount, Dim const Xcount) : mZcount(Zcount), mYcount(Ycount), mXcount(Xcount)
{
	WatchError

	// Empty count allowed.
	mItems = new itm ** [mZcount];
	for(Itr tZitr = 0; tZitr < mZcount; ++tZitr)
	{
		mItems[tZitr] = new itm * [mYcount];
		for(Itr tYitr = 0; tYitr < mYcount; ++tYitr)
		{
			mItems[tZitr][tYitr] = new itm [mXcount];
			for(Itr tXitr = 0; tXitr < mXcount; ++tXitr)
				mItems[tZitr][tYitr][tXitr] = Items[tZitr][tYitr][tXitr];
		}
	}

	CatchError
}



/*!
	The destructor.
*/
template <typename itm>
block3<itm>::~block3()
{
	WatchError

	for(Itr tZitr = 0; tZitr < mZcount; ++tZitr)
	{
		for(Itr tYitr = 0; tYitr < mYcount; ++tYitr)
			delete [] mItems[tZitr][tYitr];
		delete [] mItems[tZitr];
	}
	delete [] mItems;

	CatchError
}



/*!
	The assigner.
*/
template <typename itm>
block3<itm> const & block3<itm>::operator = (block3<itm> const & that)
{
	WatchError

	if (&that == this)
		return *this;

	Warn(mZcount != that.mZcount, eCountMismatch);
	Warn(mYcount != that.mYcount, eCountMismatch);
	Warn(mXcount != that.mXcount, eCountMismatch);

	for(Itr tZitr = 0; tZitr < mZcount; ++tZitr)
		for(Itr tYitr = 0; tYitr < mYcount; ++tYitr)
			for(Itr tXitr = 0; tXitr < mXcount; ++tXitr)
				mItems[tZitr][tYitr][tXitr] = that.mItems[tZitr][tYitr][tXitr];

	return *this;

	CatchError
}



/*!
	Synchronise clock.
*/
template <typename itm>
inline void block3<itm>::syncClk()
{
	WatchError

	//	Nothing to be done.

	CatchError
}



/*!
	Return the zcount.
*/
template <typename itm>
inline Dim block3<itm>::zcount() const
{
	WatchError

	return mZcount;

	CatchError
}



/*!
	Return the ycount.
*/
template <typename itm>
inline Dim block3<itm>::ycount() const
{
	WatchError

	return mYcount;

	CatchError
}



/*!
	Return the xcount.
*/
template <typename itm>
inline Dim block3<itm>::xcount() const
{
	WatchError

	return mXcount;

	CatchError
}



/*!
	Return the items, do not free memory with this.
*/
template <typename itm>
inline itm const *** block3<itm>::items() const
{
	WatchError

	return ccast<itm const ***>(mItems);

	CatchError
}



/*!
	Return the items, do not free memory with this.
*/
template <typename itm>
inline itm *** block3<itm>::items()
{
	WatchError

	return mItems;

	CatchError
}



/*!
	Return the items, do not free memory with this.
*/
template <typename itm>
inline itm const ** block3<itm>::items(Itr const Zitr) const
{
	WatchError

	Warn(Zitr >= mZcount, eIteratorBeyondLimit);

	return ccast<itm const **>(mItems[Zitr]);

	CatchError
}



/*!
	Return the items, do not free memory with this.
*/
template <typename itm>
inline itm ** block3<itm>::items(Itr const Zitr)
{
	WatchError

	Warn(Zitr >= mZcount, eIteratorBeyondLimit);

	return mItems[Zitr];

	CatchError
}



/*!
	Return the items; do not free memory with this.
*/
template <typename itm>
inline itm const ** block3<itm>::operator[](Itr const Zitr) const
{
	WatchError

	Warn(Zitr >= mZcount, eIteratorBeyondLimit);

	return ccast<itm const **>(mItems[Zitr]);

	CatchError
}



/*!
	Return an item.
*/
template <typename itm>
inline itm ** block3<itm>::operator[](Itr const Zitr)
{
	WatchError

	Warn(Zitr >= mZcount, eIteratorBeyondLimit);

	return mItems[Zitr];

	CatchError
}



/*!
	Return the items, do not free memory with this.
*/
template <typename itm>
inline itm const * block3<itm>::items(Itr const Zitr, Itr const Yitr) const
{
	WatchError

	Warn(Zitr >= mZcount, eIteratorBeyondLimit);
	Warn(Yitr >= mYcount, eIteratorBeyondLimit);

	return mItems[Zitr][Yitr];

	CatchError
}



/*!
	Return the items, do not free memory with this.
*/
template <typename itm>
inline itm * block3<itm>::items(Itr const Zitr, Itr const Yitr)
{
	WatchError

	Warn(Zitr >= mZcount, eIteratorBeyondLimit);
	Warn(Yitr >= mYcount, eIteratorBeyondLimit);

	return mItems[Zitr][Yitr];

	CatchError
}



/*!
	Return an item.
*/
template <typename itm>
inline itm const & block3<itm>::item(Itr const Zitr, Itr const Yitr, Itr const Xitr) const
{
	WatchError

	Warn(Zitr >= mZcount, eIteratorBeyondLimit);
	Warn(Yitr >= mYcount, eIteratorBeyondLimit);
	Warn(Xitr >= mXcount, eIteratorBeyondLimit);

	return mItems[Zitr][Yitr][Xitr];

	CatchError
}



/*!
	Return an item.
*/
template <typename itm>
inline itm & block3<itm>::item(Itr const Zitr, Itr const Yitr, Itr const Xitr)
{
	WatchError

	Warn(Zitr >= mZcount, eIteratorBeyondLimit);
	Warn(Yitr >= mYcount, eIteratorBeyondLimit);
	Warn(Xitr >= mXcount, eIteratorBeyondLimit);

	return mItems[Zitr][Yitr][Xitr];

	CatchError
}



closeEmuSpace


#endif // Block3TccIncluded
