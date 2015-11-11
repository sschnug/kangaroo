/*!
	@file pbs.tcc
	@brief The source file for pbs template class.
	@details This is the source file for pbs template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef PbsTccIncluded
#define PbsTccIncluded



#include "cbls/frames/dat.hpp"




openKangarooSpace



/*!
	@class pbs
	@brief A class to represent *sparsed* pack-bases, best suitable to hold tables and tabus
	@details This class represents *sparsed* pack-bases, best suitable to hold tables and tabus.
*/
template <typename pck>
class pbs
{
	public:
		~pbs();											//!< Destructor.
		pbs(Dim const SlotCount);						//!< Initialiser.
		pbs(pbs<pck> const & that);						//!< Duplicator.
		pbs<pck> const & operator =
				(pbs<pck> const & that);				//!< Assigner.

		Dim slotCount() const;							//!< Get slot count.
		Dim packCount() const;							//!< Get pack count.

		Bll defPack(Typ const theTyp, pck * const thePack);	//!< Define a pack.

		pck & refmPack(Typ const theTyp);					//!< Refer to a pack.
		pck * ptrmPack(Typ const theTyp);					//!< Point to a pack.

		pck const & refcPack(Typ const theTyp) const;		//!< Refer to a pack.
		pck const * ptrcPack(Typ const theTyp) const;		//!< Point to a pack.

		pck const & operator[](Itr const theItr) const;		//!< Refer to a pack.
		pck & operator[](Itr const theItr);					//!< Refer to a pack.

		pck const & refcDefPack(Itr const theItr) const;	//!< Refer to a defined pack.
		pck & refmDefPack(Itr const theItr);				//!< Refer to a defined pack.

		pck const * ptrcDefPack(Itr const theItr) const;	//!< Point to a defined pack.
		pck * ptrmDefPack(Itr const theItr);				//!< Point to a defined pack.


	private:
		Dim 	mSlotCount;			//!< Slot count.
		Dim     mPackCount;			//!< Pack size.
		pck ** 	mPacks;				//!< Packs array.
		Typ *	mTypes;				//!< Active packs.
};



/*!
	The initialiser.
*/
template<typename pck>
pbs<pck>::pbs(Dim const SlotCount) : mSlotCount(SlotCount), mPackCount(0)
{
	WatchError
	Warn(!SlotCount, eEmptyCount);

	mPacks = new pck * [mSlotCount];
	mTypes = new Typ [mSlotCount];
	for(Typ tTyp = 0; tTyp < mSlotCount; ++tTyp)
		mPacks[tTyp] = Null;
	CatchError
}



/*!
	The duplicator.
*/
template <typename pck>
pbs<pck>::pbs(pbs<pck> const & that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The destructor.
*/
template <typename pck>
pbs<pck>::~pbs()
{
	WatchError
	for(Idx tIdx = 0; tIdx < mPackCount; ++tIdx)
		delete mPacks[mTypes[tIdx]];
	delete [] mPacks;
	delete [] mTypes;
	CatchError
}



/*!
	The assigner.
*/
template <typename pck>
pbs<pck> const & pbs<pck>::operator =
		(pbs<pck> const & that)
{
	WatchError
	Throw(eUndefAssigner);
	CatchError
}



/*!
	Define the pack for the given type, transfer the ownership of the pack, and return whether successful.
*/
template <typename pck>
inline Bll pbs<pck>::defPack(Typ const theTyp, pck * const thePack)
{
	WatchError
	Warn(theTyp >= mSlotCount, eTypeBeyondLimit);
	Warn(!thePack, eNullPointer);

	if (mPacks[theTyp]) return false;

	mPacks[theTyp] = thePack;
	mTypes[mPackCount++] = theTyp;
	return true;
	CatchError
}



/*!
	Return the slot-count of the pbs.
*/
template <typename pck>
inline Dim pbs<pck>::slotCount() const
{
	WatchError
	return mSlotCount;
	CatchError
}



/*!
	Return the pack-size of the pbs.
*/
template <typename pck>
inline Dim pbs<pck>::packCount() const
{
	WatchError
	return mPackCount;
	CatchError
}



/*!
	Return the reference to a pack.
*/
template <typename pck>
inline pck const & pbs<pck>::refcPack(Typ const theTyp) const
{
	WatchError
	Warn(theTyp >= mSlotCount, eTypeBeyondLimit);
	Warn(!mPacks[theTyp], eNullPointer);

	return *mPacks[theTyp];
	CatchError
}



/*!
	Return the reference to a pack.
*/
template <typename pck>
inline pck & pbs<pck>::refmPack(Typ const theTyp)
{
	WatchError
	Warn(theTyp >= mSlotCount, eTypeBeyondLimit);
	Warn(!mPacks[theTyp], eNullPointer);

	return *mPacks[theTyp];
	CatchError
}



/*!
	Return the pointer to a pack.
*/
template <typename pck>
inline pck const * pbs<pck>::ptrcPack(Typ const theTyp) const
{
	WatchError
	Warn(theTyp >= mSlotCount, eTypeBeyondLimit);
	Warn(!mPacks[theTyp], eNullPointer);

	return mPacks[theTyp];
	CatchError
}



/*!
	Return the pointer to a pack.
*/
template <typename pck>
inline pck * pbs<pck>::ptrmPack(Typ const theTyp)
{
	WatchError
	Warn(theTyp >= mSlotCount, eTypeBeyondLimit);
	Warn(!mPacks[theTyp], eNullPointer);

	return mPacks[theTyp];
	CatchError
}



/*!
	Refer to a defined pack.
*/
template <typename pck>
inline pck const & pbs<pck>::refcDefPack(Itr const theItr) const
{
	WatchError
	Warn(theItr >= mPackCount, eIteratorBeyondLimit);
	return *mPacks[mTypes[theItr]];
	CatchError
}



/*!
	Refer to a defined pack.
*/
template <typename pck>
inline pck & pbs<pck>::refmDefPack(Itr const theItr)
{
	WatchError
	Warn(theItr >= mPackCount, eIteratorBeyondLimit);
	return *mPacks[mTypes[theItr]];
	CatchError
}



/*!
	Point to a defined pack.
*/
template <typename pck>
inline pck const * pbs<pck>::ptrcDefPack(Itr const theItr) const
{
	WatchError
	Warn(theItr >= mPackCount, eIteratorBeyondLimit);
	return mPacks[mTypes[theItr]];
	CatchError
}



/*!
	Point to a defined pack.
*/
template <typename pck>
inline pck * pbs<pck>::ptrmDefPack(Itr const theItr)
{
	WatchError
	Warn(theItr >= mPackCount, eIteratorBeyondLimit);
	return mPacks[mTypes[theItr]];
	CatchError
}



closeKangarooSpace



#endif // PbsTccIncluded
