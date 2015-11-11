/*!
	@file txt.hpp
	@brief The source file for txt class.
	@details This is the source file for txt class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef TxtTccIncluded
#define TxtTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@class txt
	@brief A class to represent texts.
	@details This class represents texts.
*/
template <typename mm>
class txt
{
	public:

		typedef mm MmTyp;						//!< Memory manager type.

		txt();									//!< Constructor.
		txt(mm const & theMm);					//!< Initialiser.
		txt(txt<mm> const & that);				//!< Duplicator.
		txt(Chr const * Chars);					//!< Duplicator.
		txt(Chr const * Chars, Dim const Count);//!< Duplicator.
		txt<mm> const & operator =
				(txt<mm> const & that);			//!< Assigner.
		~txt();									//!< Destructor.

		//! @name Clear
		//! @{

		void clear();								//!< Clear chars, retaining available memory.
		void clearMem();							//!< Clear chars, releasing memory when deemed.

		//! @}

		//! @name Memory
		//! @{

		Dim charCount() const;						//!< Get char count.
		mm const & MemMan() const;					//!< Memory manager.

		void reallocMemAuto();						//!< Reallocate memory automatically.
		void deallocMemAuto();						//!< Deallocate memory automatically.
		void adjustMemAuto();						//!< Adjust memory automatically.
		void allocateMem(Dim const Alloc);			//!< Allocate given extent of memory.

		//! @}

		//! @name Chars
		//! @{

		Chr * chars();										//!< Get the chars.
		Chr const * chars() const;							//!< Get the chars.

		Chr & operator[](Itr const theItr);					//!< Get a char.
		Chr const & operator[](Itr const theItr) const;		//!< Get a char.

		Chr & chr(Itr const theItr);						//!< Get a char.
		Chr const & chr(Itr const theItr) const;			//!< Get a char.

		//! @}

		//! @name Relations
		//! @{

		Bll operator == (Chr const * Chars) const;			//!< Equal operator.
		Bll operator != (Chr const * Chars) const;			//!< Not-Equal operator.
		Bll operator > (Chr const * Chars) const;			//!< Greater than operator.
		Bll operator < (Chr const * Chars) const;			//!< Less than operator.
		Bll operator >= (Chr const * Chars) const;			//!< Greater equal operator.
		Bll operator <= (Chr const * Chars) const;			//!< Less equal operator.

		Bll operator == (txt const & that) const;			//!< Equal operator.
		Bll operator != (txt const & that) const;			//!< Not-Equal operator.
		Bll operator > (txt const & that) const;			//!< Greater than operator.
		Bll operator < (txt const & that) const;			//!< Less than operator.
		Bll operator >= (txt const & that) const;			//!< Greater equal operator.
		Bll operator <= (txt const & that) const;			//!< Less equal operator.

		//! @}



	private:
		mm	   mMemMan;			//!< Memory manager.
		Chr *  mChars;			//!< The chars.
};



/*!
	@def t
	@brief A macro to denote txt.
	@details This macro denotes txt.
*/
#define t txt



/*!
	The constructor.
*/
template<typename mm>
txt<mm>::txt()
{
	WatchError

	mChars = new Chr [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mChars[tItr] = Chr();
	mChars[mMemMan.occupied()] = EndChr;
	CatchError
}



/*!
	The initialiser.
*/
template<typename mm>
txt<mm>::txt(mm const & theMm) : mMemMan(theMm)
{
	WatchError

	mChars = new Chr [mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mChars[tItr] = Chr();
	mChars[mMemMan.occupied()] = EndChr;

	CatchError
}



/*!
	The duplicator.
*/
template <typename mm>
txt<mm>::txt(txt<mm> const & that) : mMemMan(that.mMemMan)
{
	WatchError

	mChars = new Chr [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mChars[tItr] = that.mChars[tItr];
	mChars[mMemMan.occupied()] = EndChr;

	CatchError
}



/*!
	The duplicator.
*/
template <typename mm>
txt<mm>::txt(Chr const * Chars)
{
	WatchError

	Dim tCount = strlen(Chars);

	mMemMan.reinitialise(tCount, tCount);
	mChars = new Chr [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mChars[tItr] = Chars[tItr];
	mChars[mMemMan.occupied()] = EndChr;

	CatchError
}




/*!
	The duplicator.
*/
template <typename mm>
txt<mm>::txt(Chr const * Chars, Dim const Count)
{
	WatchError

	mMemMan.reinitialise(Count, Count);
	mChars = new Chr [mMemMan.acquired()];

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mChars[tItr] = Chars[tItr];
	mChars[mMemMan.occupied()] = EndChr;

	CatchError
}



/*!
	The destructor.
*/
template <typename mm>
txt<mm>::~txt()
{
	WatchError

	delete [] mChars;

	CatchError
}



/*!
	The assigner.
*/
template <typename mm>
txt<mm> const & txt<mm>::operator = (txt<mm> const & that)
{
	WatchError

	if (&that == this)
		return *this;

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		delete [] mChars;
		mChars = new Chr [that.mMemMan.acquired()];
	}

	mMemMan = that.mMemMan;

	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mChars[tItr] = that.mChars[tItr];
	mChars[mMemMan.occupied()] = EndChr;

	return *this;

	CatchError
}



/*!
	Clear chars, retaining available memory.
*/
template<typename mm>
inline void txt<mm>::clear()
{
	WatchError

	mMemMan.resetOccupy();
	mChars[mMemMan.occupied()] = EndChr;

	CatchError
}



/*!
	Clear chars, releasing memory when deemed.
*/
template<typename mm>
inline void txt<mm>::clearMem()
{
	WatchError

	if (mMemMan.resetOccupyBll())
	{
		mChars[mMemMan.occupied()] = EndChr;
		if (mMemMan.needAutoDealloc())
			deallocMemAuto();
	}

	CatchError
}



/*!
	Reallocate more memory automatically.
*/
template<typename mm>
void txt<mm>::reallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);

	mMemMan.reallocAuto();

	Chr * const tChars = mChars;
	mChars = new Chr[mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mChars[tItr] = tChars[tItr];
	mChars[mMemMan.occupied()] = EndChr;

	delete [] tChars;

	CatchError
}



/*!
	Deallocate some memory automatically.
*/
template<typename mm>
void txt<mm>::deallocMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoDealloc(), eMemoryAllocation);

	mMemMan.deallocAuto();

	Chr * const tChars = mChars;
	mChars = new Chr[mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mChars[tItr] = tChars[tItr];
	mChars[mMemMan.occupied()] = EndChr;

	delete [] tChars;

	CatchError
}



/*!
	Adjust memory automatically.
*/
template<typename mm>
void txt<mm>::adjustMemAuto()
{
	WatchError

	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);

	mMemMan.adjustAuto();

	Chr * const tChars = mChars;
	mChars = new Chr[mMemMan.acquired()];
	for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
		mChars[tItr] = tChars[tItr];
	mChars[mMemMan.occupied()] = EndChr;

	delete [] tChars;

	CatchError
}



/*!
	Allocate memory.
*/
template<typename mm>
void txt<mm>::allocateMem(Dim const Alloc)
{
	WatchError

	if (mMemMan.mismatchAlloc(Alloc))
	{
		mMemMan.allocate(Alloc);

		Chr * const tChars = mChars;
		mChars = new Chr[mMemMan.acquired()];
		for(Itr tItr = 0; tItr < mMemMan.occupied(); ++tItr)
			mChars[tItr] = tChars[tItr];
		mChars[mMemMan.occupied()] = EndChr;

		delete [] tChars;
	}

	CatchError
}


/*!
	Return the char count.
*/
template <typename mm>
inline Dim txt<mm>::charCount() const
{
	WatchError

	return mMemMan.occupied();

	CatchError
}



/*!
	Return the memory manager.
*/
template <typename mm>
inline mm const & txt<mm>::MemMan() const
{
	WatchError

	return mMemMan;

	CatchError
}



/*!
	Return the chars; do not free memory with this.
*/
template <typename mm>
inline Chr const * txt<mm>::chars() const
{
	WatchError

	return mChars;

	CatchError
}



/*!
	Return the chars; do not free memory with this.
*/
template <typename mm>
inline Chr * txt<mm>::chars()
{
	WatchError

	return mChars;

	CatchError
}



/*!
	Return a char.
*/
template <typename mm>
inline Chr const & txt<mm>::operator[](Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mChars[theItr];

	CatchError
}



/*!
	Return a char.
*/
template <typename mm>
inline Chr & txt<mm>::operator[](Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mChars[theItr];

	CatchError
}



/*!
	Return a char.
*/
template <typename mm>
inline Chr const & txt<mm>::chr(Itr const theItr) const
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mChars[theItr];

	CatchError
}



/*!
	Return a char.
*/
template <typename mm>
inline Chr & txt<mm>::chr(Itr const theItr)
{
	WatchError

	Warn(mMemMan.beyondOccupied(theItr), eIteratorBeyondLimit);

	return mChars[theItr];

	CatchError
}



/*!
	Equal operator.
*/
template <typename mm>
inline Bll txt<mm>::operator == (Chr const * Chars) const
{
	WatchError
	return !strcmp(mChars, Chars);
	CatchError
}



/*!
	Not-Equal operator.
*/
template <typename mm>
inline Bll txt<mm>::operator != (Chr const * Chars) const
{
	WatchError
	return strcmp(mChars, Chars);
	CatchError
}


/*!
	Greater than operator.
*/
template <typename mm>
inline Bll txt<mm>::operator > (Chr const * Chars) const
{
	WatchError
	return strcmp(mChars, Chars) > 0;
	CatchError
}



/*!
	Less than operator.
*/
template <typename mm>
inline Bll txt<mm>::operator < (Chr const * Chars) const
{
	WatchError
	return strcmp(mChars, Chars) < 0;
	CatchError
}



/*!
	Greater equal operator.
*/
template <typename mm>
inline Bll txt<mm>::operator >= (Chr const * Chars) const
{
	WatchError
	return strcmp(mChars, Chars) >= 0;
	CatchError
}



/*!
	Less equal operator.
*/
template <typename mm>
inline Bll txt<mm>::operator <= (Chr const * Chars) const
{
	WatchError
	return strcmp(mChars, Chars) <= 0;
	CatchError
}



/*!
	Equal operator.
*/
template <typename mm>
inline Bll txt<mm>::operator == (txt const & that) const
{
	WatchError
	return mMemMan.occupied() == that.mMemMan.occupied() &&
		!strcmp(mChars, that.mChars);
	CatchError
}



/*!
	Not-Equal operator.
*/
template <typename mm>
inline Bll txt<mm>::operator != (txt const & that) const
{
	WatchError
	return strcmp(mChars, that.mChars);
	CatchError
}


/*!
	Greater than operator.
*/
template <typename mm>
inline Bll txt<mm>::operator > (txt const & that) const
{
	WatchError
	return strcmp(mChars, that.mChars) > 0;
	CatchError
}



/*!
	Less than operator.
*/
template <typename mm>
inline Bll txt<mm>::operator < (txt const & that) const
{
	WatchError
	return strcmp(mChars, that.mChars) < 0;
	CatchError
}



/*!
	Greater equal operator.
*/
template <typename mm>
inline Bll txt<mm>::operator >= (txt const & that) const
{
	WatchError
	return strcmp(mChars, that.mChars) >= 0;
	CatchError
}



/*!
	Less equal operator.
*/
template <typename mm>
inline Bll txt<mm>::operator <= (txt const & that) const
{
	WatchError
	return strcmp(mChars, that.mChars) <= 0;
	CatchError
}


closeEmuSpace


#endif // TxtTccIncluded
