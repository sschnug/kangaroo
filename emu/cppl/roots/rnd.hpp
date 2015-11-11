/*!
	@file rnd.hpp
	@brief The source file for Rnd class.
	@details This is the source file for Rnd class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 23.1.2009 QRL NICTA www.nicta.com.au
*/



#ifndef RndHppIncluded
#define RndHppIncluded



#include "cppl/roots/typ.hpp"
#include "cppl/roots/err.hpp"



openEmuSpace



/*!
	@var typedef Rns
	@brief A type to represent the random number states.
	@details This type represents the random number states.
*/
#if RandomSize == SmallSize
	#error Small size random number generator is not defined.
#elif RandomSize == NormalSize
typedef Q Rns;
#elif RandomSize == LargeSize
	#error Large size random number generator is not defined.
#else
	#error Undefined random data size specified.
#endif



/*!
	@def castRns(theRns)
	@brief A macro to cast to Rns.
	@details This macro casts to Rns.
*/
#define castRns(theRns) (scast<Rns>(theRns))



/*!
	@class Rnd
	@brief A class to represent random number generators.
	@details This class represents random number generators.
*/
class Rnd
{
	public:

		~Rnd();										//!< Destructor.
		Rnd();										//!< Constructor.
		Rnd(Rns const theSeed);						//!< Initialiser.
		Rnd(Rnd const & that);						//!< Duplicator.
		Rnd const & operator = (Rnd const & that);	//!< Assigner.

		/*! @name Generation */
		//! @{

		Rns operator()();							//!< Get a random number.

		//! @}

		/*! @name State */
		//! @{

		void seed();								//!< Set random seed.
		void seed(Rns const theSeed);				//!< Set given seed.
		Rns Seed() const;							//!< Return the seed.

		//! @}

	private:

		/*!
			@enum Settings
			@brief Settings for the linear congruential random number generator.
			@details Settings for the linear congruential random number generator.
		*/
		enum Settings
		{
			#if RandomSize == SmallSize
				#error Small size random number is not defined.
			#elif RandomSize == NormalSize
				#if ProcessorSize == SmallSize
					#error Normal size random number is not defined on small processor.
				#elif ProcessorSize == NormalSize
					mShft  = 16,						//!< The number bits to be shifted.
					mMask  = 0xFFFF,					//!< The bit-mask required in computation.
					mCore  = 0x330e,					//!< The lower-order fixed and core seed.
					mPlus  = 0x000b,					//!< The lower-order additive translation.
					mMult  = 0xe66d,					//!< The lower-order multiplicative factor.
					mFact  = 0x5deec,					//!< The higher-order multiplicative factor.
					mTime  = 0xdeece66d					//!< The combined factor mMult + mFact << 16.
				#elif ProcessorSize == LargeSize
					mShft  = 16,						//!< The number bits to be shifted.
					mCore  = 0x330e,					//!< The lower-order core seed.
					mPlus  = 0x000b,					//!< The additive translation.
					mMult  = 0x5deece66d,				//!< The multiplicative factor.
					mMask  = 0xFFFFFFFFFFFF,			//!< The bit-mask to be used.
				#else
					#error Undefined processor data size specified.
				#endif
	//				mPlus  = 0x14057b7ef767814f,		//!< The additive translation.
	//				mMult  = 0x5851f42d4c957f2d,		//!< The multiplicative factor.
	//				mPlus  = 0xb504f32d,				//!< The additive translation.
	//				mMult  = 0x27bb2ee687b0b0fd,		//!< The multiplicative factor.
	//				mPlus  = 12345,						//!< The additive translation.
	//				mMult  = 1103515245					//!< The multiplicative factor.
			#elif RandomSize == LargeSize
				#error Random number generator is not defined for SmallSize.
			#else
				#error Undefined random data size specified.
			#endif
		};

		#if RandomSize == SmallSize
			#error Small size random number is not defined.
		#elif RandomSize == NormalSize
			#if ProcessorSize == SmallSize
				#error Normal size random number is not defined on small processor.
			#elif ProcessorSize == NormalSize
			typedef Q RnsBuff;							//!< Buffer for computation.
			Rns 	mSeed;								//!< The higher-order flexible seed.
			RnsBuff mAuxl;								//!< The lower-order non-returnable state.
			RnsBuff mMain;								//!< The higher-order returnable state.
			#elif ProcessorSize == LargeSize
			typedef O RnsBuff;							//!< Buffer for computation.
			Rns mSeed;									//!< The current seed.
			RnsBuff mCurr;								//!< The current value.
			#else
				#error Undefined processor data size specified.
			#endif
		#elif RandomSize == LargeSize
			#error Large size random number is not defined.
		#else
			#error Undefined random data size specified.
		#endif
};



/*!
	Generate the next random number.
*/
inline Rns Rnd::operator()()
{
	WatchError
	#if RandomSize == SmallSize
		#error Small size random number is not defined.
	#elif RandomSize == NormalSize
		#if ProcessorSize == SmallSize
			#error Normal size random number is not defined on small processor.
		#elif ProcessorSize == NormalSize
			Rns tAccu = mMult * mAuxl + mPlus;
			mMain = (tAccu >> mShft) + mFact * mAuxl + mTime * mMain;
			mAuxl = tAccu & mMask;
			return mMain;
		#elif ProcessorSize == LargeSize
			mCurr = (mCurr * mMult + mPlus) & mMask;
			return (mCurr >> mShft);
		#else
			#error Undefined processor data size specified.
		#endif
	#elif RandomSize == LargeSize
		#error Large size random number is not defined.
	#else
		#error Undefined random data size specified.
	#endif
	CatchError
}



/*!
	The constructor.
*/
inline Rnd::Rnd() : mSeed(scast<Rns>(std::time(0))),
	#if RandomSize == SmallSize
		#error Small size random number is not defined.
	#elif RandomSize == NormalSize
		#if ProcessorSize == SmallSize
			#error Normal size random number is not defined on small processor.
		#elif ProcessorSize == NormalSize
			mAuxl(mCore), mMain(mSeed)
		#elif ProcessorSize == LargeSize
			mCurr((mSeed << mShft) + mCore)
		#else
			#error Undefined processor data size specified.
		#endif
	#elif RandomSize == LargeSize
		#error Large size random number is not defined.
	#else
		#error Undefined random data size specified.
	#endif
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
inline Rnd::Rnd(Rns const theSeed) : mSeed(theSeed),
	#if RandomSize == SmallSize
		#error Small size random number is not defined.
	#elif RandomSize == NormalSize
		#if ProcessorSize == SmallSize
			#error Normal size random number is not defined on small processor.
		#elif ProcessorSize == NormalSize
			mAuxl(mCore), mMain(mSeed)
		#elif ProcessorSize == LargeSize
			mCurr((mSeed << mShft) + mCore)
		#else
			#error Undefined processor data size specified.
		#endif
	#elif RandomSize == LargeSize
		#error Large size random number is not defined.
	#else
		#error Undefined random data size specified.
	#endif
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
inline Rnd::Rnd(Rnd const & that) : mSeed(that.mSeed),
	#if RandomSize == SmallSize
		#error Small size random number is not defined.
	#elif RandomSize == NormalSize
		#if ProcessorSize == SmallSize
			#error Normal size random number is not defined on small processor.
		#elif ProcessorSize == NormalSize
			mAuxl(that.mAuxl), mMain(that.mMain)
		#elif ProcessorSize == LargeSize
			mCurr(that.mCurr)
		#else
			#error Undefined processor data size specified.
		#endif
	#elif RandomSize == LargeSize
		#error Large size random number is not defined.
	#else
		#error Undefined random data size specified.
	#endif
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
inline Rnd::~Rnd()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
inline Rnd const & Rnd::operator = (Rnd const & that)
{
	WatchError
	if (this == &that)
		return *this;
	mSeed = that.mSeed;
	#if RandomSize == SmallSize
		#error Small size random number is not defined.
	#elif RandomSize == NormalSize
		#if ProcessorSize == SmallSize
			#error Normal size random number is not defined on small processor.
		#elif ProcessorSize == NormalSize
			mAuxl = that.mAuxl;
			mMain = that.mMain;
		#elif ProcessorSize == LargeSize
			mCurr = that.mCurr;
		#else
			#error Undefined processor data size specified.
		#endif
	#elif RandomSize == LargeSize
		#error Large size random number is not defined.
	#else
		#error Undefined random data size specified.
	#endif
	return *this;
	CatchError
}



/*!
	Set a random seed.
*/
inline void Rnd::seed()
{
	WatchError
	mSeed = scast<Rns>(std::time(0));
	#if RandomSize == SmallSize
		#error Small size random number is not defined.
	#elif RandomSize == NormalSize
		#if ProcessorSize == SmallSize
			#error Normal size random number is not defined on small processor.
		#elif ProcessorSize == NormalSize
			mMain = mSeed;
			mAuxl = mCore;
		#elif ProcessorSize == LargeSize
			mCurr = (mSeed << mShft) + mCore;
		#else
			#error Undefined processor data size specified.
		#endif
	#elif RandomSize == LargeSize
		#error Large size random number is not defined.
	#else
		#error Undefined random data size specified.
	#endif
	CatchError
}



/*!
	Set a given seed.
*/
inline void Rnd::seed(Rns const theSeed)
{
	WatchError
	mSeed = theSeed;
	#if RandomSize == SmallSize
		#error Small size random number is not defined.
	#elif RandomSize == NormalSize
		#if ProcessorSize == SmallSize
			#error Normal size random number is not defined on small processor.
		#elif ProcessorSize == NormalSize
			mMain = mSeed;
			mAuxl = mCore;
		#elif ProcessorSize == LargeSize
			mCurr = (mSeed << mShft) + mCore;
		#else
			#error Undefined processor data size specified.
		#endif
	#elif RandomSize == LargeSize
		#error Large size random number is not defined.
	#else
		#error Undefined random data size specified.
	#endif
	CatchError
}



/*!
	Return the seed number.
*/
inline Rns Rnd::Seed() const
{
	WatchError
	return mSeed;
	CatchError
}



closeEmuSpace


#endif // RndHppIncluded

