/*!
	@file pbd.tcc
	@brief The source file for pbd template class.
	@details This is the source file for pbd template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
	@see error.cpp
*/



#ifndef PbdTccIncluded
#define PbdTccIncluded



#include "cbls/frames/dat.hpp"



openKangarooSpace



/*!
	@class pbd
	@brief A class to represent *densed* pack-bases, best suitable to represent collection of sys and table objects.
	@details This class represents *densed* pack-bases, best suitable to represent collection of sys and table objects.
*/
template <typename pck, typename mm>
class pbd
{
	public:
		~pbd();										//!< Destructor.
		pbd();										//!< Constructor.
		pbd(mm const & theMm);						//!< Initialiser
		pbd(pbd<pck,mm> const & that);				//!< Duplicator.
		pbd<pck,mm> const & operator =
				(pbd<pck,mm> const & that);			//!< Assigner.

		/*!	@name Allocators */
		//! @{

		Dim packCount() const;						//!< Return the pack count.
		mm const & MemMan() const;					//!< Return memory manager.
		void reallocMemAuto();						//!< Reallocate memory automatically.
		void adjustMemAuto();						//!< Adjust memory automatically.
		void allocateMem(Dim const Alloc);			//!< Allocate more memory.

		//!@}

		Srl defPack(pck * const thePack);				//!< Define a pack.

		pck const & refcPack(Srl const theSrl) const;	//!< Get a pack reference.
		pck const * ptrcPack(Srl const theSrl) const;	//!< Get a pack pointer.

		pck & refmPack(Srl const theSrl);				//!< Get a pack reference.
		pck * ptrmPack(Srl const theSrl);				//!< Get a pack pointer.

	private:
		mm     mMemMan;				//!< Memory manager.
		pck ** mPacks;				//!< The packs.
};



/*!
	The constructor.
*/
template<typename pck, typename mm>
pbd<pck,mm>::pbd()
{
	mPacks = new pck * [mMemMan.acquired()];
}



/*!
	The initialiser.
*/
template<typename pck, typename mm>
pbd<pck,mm>::pbd(mm const & theMm) : mMemMan(theMm)
{
	mPacks = new pck * [mMemMan.acquired()];
}



/*!
	The duplicator.
*/
template <typename pck, typename mm>
pbd<pck,mm>::pbd(pbd<pck,mm> const & that) :
		mMemMan(that.mMemMan)
{
	mPacks = new pck * [mMemMan.acquired()];

	for(Srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mPacks[tSrl] = new pck(*that.mPacks[tSrl]);
}



/*!
	The destructor.
*/
template <typename pck, typename mm>
pbd<pck,mm>::~pbd()
{
	for(Srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		delete mPacks[tSrl];

	delete [] mPacks;
}



/*!
	The assigner.
*/
template <typename pck, typename mm> pbd<pck,mm>
const & pbd<pck,mm>::operator = (pbd<pck,mm> const & that)
{
	if (&that == this)
		return *this;

	for(Srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		delete mPacks[tSrl];

	if (mMemMan.mismatchAlloc(that.mMemMan.allocated()))
	{
		delete [] mPacks;
		mPacks = new pck * [mMemMan.acquired()];
	}

	mMemMan = that.mMemMan;
	for(Srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mPacks[tSrl] = new pck(*that.mPacks[tSrl]);

	return *this;
}



/*!
	Reallocate more memory automatically.
*/
template<typename pck, typename mm>
void pbd<pck,mm>::reallocMemAuto()
{

	Warn(!mMemMan.needAutoRealloc(), eMemoryAllocation);
	mMemMan.reallocAuto();

	pck ** tPacks = mPacks;
	mPacks = new pck * [mMemMan.acquired()];
	for(Srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mPacks[tSrl] = tPacks[tSrl];

	delete [] tPacks;
}



/*!
	Adjust the memory automatically.
*/
template<typename pck, typename mm>
void pbd<pck,mm>::adjustMemAuto()
{
	Warn(!mMemMan.needAutoAdjust(), eMemoryAllocation);
	mMemMan.adjustAuto();

	pck ** tPacks = mPacks;
	mPacks = new pck * [mMemMan.acquired()];
	for(Srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mPacks[tSrl] = tPacks[tSrl];

	delete [] tPacks;
}



/*!
	Allocate more memory.
*/
template<typename pck, typename mm>
void pbd<pck,mm>::allocateMem(Dim const Alloc)
{
	Warn(!mMemMan.mismatchAlloc(Alloc), eDimensionMismatch);
	mMemMan.allocate(Alloc);

	pck ** tPacks = mPacks;
	mPacks = new pck * [mMemMan.acquired()];
	for(Srl tSrl = 0; tSrl < mMemMan.occupied(); ++tSrl)
		mPacks[tSrl] = tPacks[tSrl];

	delete [] tPacks;
}



/*!
	Define pack in the pbd and return the handle.
*/
template <typename pck, typename mm>
inline Srl pbd<pck,mm>::defPack(pck * const thePack)
{
	Warn(!thePack, eNullPointer);

	if (mMemMan.needAutoRealloc())
		reallocMemAuto();

	Srl const tSrl = mMemMan.reoccupyItr();
	mPacks[tSrl] = thePack;
	return tSrl;
}



/*!
	Get the pack-count of the pbd.
*/
template <typename pck, typename mm>
inline Dim pbd<pck,mm>::packCount() const
{
	return mMemMan.occupied();
}



/*!
	Get the memory manager.
*/
template <typename pck, typename mm>
inline mm const & pbd<pck,mm>::MemMan() const
{
	return mMemMan;
}



/*!
	Return read access to the pack.
*/
template <typename pck, typename mm>
inline pck const & pbd<pck,mm>::refcPack(Srl const theSrl) const
{
	Warn(mMemMan.beyondOccupied(theSrl), eInvalidHandle);

	return *mPacks[theSrl];
}



/*!
	Return write access to the pack.
*/
template <typename pck, typename mm>
inline pck & pbd<pck,mm>::refmPack(Srl const theSrl)
{
	Warn(mMemMan.beyondOccupied(theSrl), eInvalidHandle);

	return *mPacks[theSrl];
}



/*!
	Return read access to a pack.
*/
template <typename pck, typename mm>
inline pck const * pbd<pck,mm>::ptrcPack(Srl const theSrl) const
{
	Warn(mMemMan.beyondOccupied(theSrl), eInvalidHandle);

	return mPacks[theSrl];
}



/*!
	Return write access to a pack.
*/
template <typename pck, typename mm>
inline pck * pbd<pck,mm>::ptrmPack(Srl const theSrl)
{
	Warn(mMemMan.beyondOccupied(theSrl), eInvalidHandle);

	return mPacks[theSrl];
}



closeKangarooSpace



#endif//PbdTccIncluded
