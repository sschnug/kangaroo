/*!
	@file wrp.hpp
	@brief The prototype file for Wrp class.
	@details This is the prototype file for Wrp class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 03.01.2010 QRL NICTA www.nicta.com.au
*/



#ifndef WrpHppIncluded
#define WrpHppIncluded



#include "cbls/frames/dat.hpp"



openKangarooSpace



/*!
	@var enum Wtc
	@brief Wrapper type constants.
	@details Wrapper type constants.
*/
enum Wtc
{
	Ww,		//!< Empty wrapper.
	Wb,		//!< Boolean wrapper.
	Wc,		//!< Countable wrapper.
	Wi,		//!< Integer wrapper.
	Wf,		//!< Float wrapper.
	Wb2,	//!< Boolean pair wrapper.
	Wb3,	//!< Boolean triple wrapper
	Wc2,	//!< Countable pair wrapper.
	Wc3,	//!< Countable triple wrapper.
	Wi2,	//!< Integer pair wrapper.
	Wi3,	//!< Integer triple wrapper.
	Wf2,	//!< Float pair wrapper.
	Wf3,	//!< Float triple wrapper.
	Wbk,	//!< Boolean array wrapper.
	Wck,	//!< Countable array wrapper.
	Wik,	//!< Integer array wrapper.
	Wfk		//!< Float array wrapper.
};



/*!
	@class Wrp
	@brief A class to represent wrappers for variable values.
	@details This class represents wrappers for variable values.
*/
class Wrp
{
	public:

		~Wrp();											//!< Destructor.
		Wrp();											//!< Constructor.

		explicit Wrp(Bln const theBln);					//!< Initialiser.
		explicit Wrp(Cnt const & theCnt);				//!< Initialiser.
		explicit Wrp(Int const & theInt);				//!< Initialiser.
		explicit Wrp(Flt const & theFlt);				//!< Initialiser.
		explicit Wrp(t2<Bln,Bln> const & theBln2);		//!< Initialiser.
		explicit Wrp(t3<Bln,Bln,Bln> const & theBln3);	//!< Initialiser.
		explicit Wrp(t2<Cnt,Cnt> const & theCnt2);		//!< Initialiser.
		explicit Wrp(t3<Cnt,Cnt,Cnt> const & theCnt3);	//!< Initialiser.
		explicit Wrp(t2<Int,Int> const & theInt2);		//!< Initialiser.
		explicit Wrp(t3<Int,Int,Int> const & theInt3);	//!< Initialiser.
		explicit Wrp(t2<Flt,Flt> const & theFlt2);		//!< Initialiser.
		explicit Wrp(t3<Flt,Flt,Flt> const & theFlt3);	//!< Initialiser.
		explicit Wrp(b1<Bln,kmm> const & theBlnk);		//!< Initialiser.
		explicit Wrp(b1<Cnt,kmm> const & theCntk);		//!< Initialiser.
		explicit Wrp(b1<Int,kmm> const & theIntk);		//!< Initialiser.
		explicit Wrp(b1<Flt,kmm> const & theFltk);		//!< Initialiser.

		Wrp(Wrp const & that);							//!< Duplicator.

		void clear();									//!< Clear.

		Wrp const & operator = (Bln const theBln);					//!< Assigner.
		Wrp const & operator = (Cnt const theCnt);					//!< Assigner.
		Wrp const & operator = (Int const theInt);					//!< Assigner.
		Wrp const & operator = (Flt const theFlt);					//!< Assigner.
		Wrp const & operator = (t2<Bln,Bln> const & theBln2);		//!< Assigner.
		Wrp const & operator = (t3<Bln,Bln,Bln> const & theBln3);	//!< Assigner.
		Wrp const & operator = (t2<Cnt,Cnt> const & theCnt2);		//!< Assigner.
		Wrp const & operator = (t3<Cnt,Cnt,Cnt> const & theCnt3);	//!< Assigner.
		Wrp const & operator = (t2<Int,Int> const & theInt2);		//!< Assigner.
		Wrp const & operator = (t3<Int,Int,Int> const & theInt3);	//!< Assigner.
		Wrp const & operator = (t2<Flt,Flt> const & theFlt2);		//!< Assigner.
		Wrp const & operator = (t3<Flt,Flt,Flt> const & theFlt3);	//!< Assigner.
		Wrp const & operator = (b1<Bln,kmm> const & theBlnk);		//!< Assigner.
		Wrp const & operator = (b1<Cnt,kmm> const & theCntk);		//!< Assigner.
		Wrp const & operator = (b1<Int,kmm> const & theIntk);		//!< Assigner.
		Wrp const & operator = (b1<Flt,kmm> const & theFltk);		//!< Assigner.

		Wrp const & operator = (Wrp const & that);		//!< Assigner.

		void item(Bln & theBln) const;				//!< Item retrieve.
		void item(Cnt & theCnt) const;				//!< Item retrieve.
		void item(Int & theInt) const;				//!< Item retrieve.
		void item(Flt & theFlt) const;				//!< Item retrieve.
		void item(t2<Bln,Bln> & theBln2) const;		//!< Item retrieve.
		void item(t3<Bln,Bln,Bln> & theBln3) const;	//!< Item retrieve.
		void item(t2<Cnt,Cnt> & theCnt2) const;		//!< Item retrieve.
		void item(t3<Cnt,Cnt,Cnt> & theCnt3) const;	//!< Item retrieve.
		void item(t2<Int,Int> & theInt2) const;		//!< Item retrieve.
		void item(t3<Int,Int,Int> & theInt3) const;	//!< Item retrieve.
		void item(t2<Flt,Flt> & theFlt2) const;		//!< Item retrieve.
		void item(t3<Flt,Flt,Flt> & theFlt3) const;	//!< Item retrieve.
		void item(b1<Bln,kmm> & theBlnk) const;		//!< Item retrieve.
		void item(b1<Cnt,kmm> & theCntk) const;		//!< Item retrieve.
		void item(b1<Int,kmm> & theIntk) const;		//!< Item retrieve.
		void item(b1<Flt,kmm> & theFltk) const;		//!< Item retrieve.

		Wtc WrapType() const;							//!< Wrapper type.
		Bll chkWrap(Wtc const theWtc) const;			//!< Check wrapper.

		Bln const & itemBln() const;					//!< Boolean.
		Cnt const & itemCnt() const;					//!< Countable.
		Int const & itemInt() const;					//!< Integer.
		Flt const & itemFlt() const;					//!< Float.
		t2<Bln,Bln> const & itemBln2() const;			//!< Boolean pair.
		t3<Bln,Bln,Bln> const & itemBln3() const;		//!< Boolean triple.
		t2<Cnt,Cnt> const & itemCnt2() const;			//!< Countable pair.
		t3<Cnt,Cnt,Cnt> const & itemCnt3() const;		//!< Countable triple.
		t2<Int,Int> const & itemInt2() const;			//!< Integer pair.
		t3<Int,Int,Int> const & itemInt3() const;		//!< Integer triple.
		t2<Flt,Flt> const & itemFlt2() const;			//!< Float pair.
		t3<Flt,Flt,Flt> const & itemFlt3() const;		//!< Float triple.
		b1<Bln,kmm> const & itemBlnk() const;			//!< Boolean array.
		b1<Cnt,kmm> const & itemCntk() const;			//!< Countable array.
		b1<Int,kmm> const & itemIntk() const;			//!< Integer array.
		b1<Flt,kmm> const & itemFltk() const;			//!< Float array.

		Bln & itemBln();								//!< Boolean.
		Cnt & itemCnt();								//!< Countable.
		Int & itemInt();								//!< Integer.
		Flt & itemFlt();								//!< Float.
		t2<Bln,Bln> & itemBln2();						//!< Boolean pair.
		t3<Bln,Bln,Bln> & itemBln3();					//!< Boolean triple.
		t2<Cnt,Cnt> & itemCnt2();						//!< Countable pair.
		t3<Cnt,Cnt,Cnt> & itemCnt3();					//!< Countable triple.
		t2<Int,Int> & itemInt2();						//!< Integer pair.
		t3<Int,Int,Int> & itemInt3();					//!< Integer triple.
		t2<Flt,Flt> & itemFlt2();						//!< Float pair.
		t3<Flt,Flt,Flt> & itemFlt3();					//!< Float triple.
		b1<Bln,kmm> & itemBlnk();						//!< Boolean array.
		b1<Cnt,kmm> & itemCntk();						//!< Countable array.
		b1<Int,kmm> & itemIntk();						//!< Integer array.
		b1<Flt,kmm> & itemFltk();						//!< Float array.

	private:

		Wtc mWtc;										//!< Wrapper type.

		union
		{
			Bln mBln;									//!< Boolean.
			Cnt mCnt;									//!< Countable.
			Int mInt;									//!< Integer.
			Flt mFlt;									//!< Float.
			t2<Bln,Bln> * mBln2;						//!< Countable pair.
			t3<Bln,Bln,Bln> * mBln3;					//!< Countable triple.
			t2<Cnt,Cnt> * mCnt2;						//!< Countable pair.
			t3<Cnt,Cnt,Cnt> * mCnt3;					//!< Countable triple.
			t2<Int,Int> * mInt2;						//!< Integer pair.
			t3<Int,Int,Int> * mInt3;					//!< Integer triple.
			t2<Flt,Flt> * mFlt2;						//!< Float pair.
			t3<Flt,Flt,Flt> * mFlt3;					//!< Float triple.
			b1<Bln,kmm> * mBlnk;						//!< Boolean array.
			b1<Cnt,kmm> * mCntk;						//!< Countable array.
			b1<Int,kmm> * mIntk;						//!< Integer array.
			b1<Flt,kmm> * mFltk;						//!< Float array.
		};
};



/*!
	The constructor.
*/
inline Wrp::Wrp() : mWtc(Ww)
{
	WatchError
	//	nothing to be done.
	CatchError
}




/*!
	The initialiser.
*/
inline Wrp::Wrp(Bln const theBln)
{
	WatchError
	mWtc = Wb;
	mBln = theBln;
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(Cnt const & theCnt)
{
	WatchError
	mWtc = Wc;
	mCnt = theCnt;
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(Int const & theInt)
{
	WatchError
	mWtc = Wi;
	mInt = theInt;
	CatchError
}




/*!
	The initialiser.
*/
inline Wrp::Wrp(Flt const & theFlt)
{
	WatchError
	mWtc = Wf;
	mFlt = theFlt;
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(t2<Bln,Bln> const & theBln2)
{
	WatchError
	mWtc = Wb2;
	mBln2 = new t2<Bln,Bln>(theBln2);
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(t3<Bln,Bln,Bln> const & theBln3)
{
	WatchError
	mWtc = Wb3;
	mBln3 = new t3<Bln,Bln,Bln>(theBln3);
	CatchError
}




/*!
	The initialiser.
*/
inline Wrp::Wrp(t2<Cnt,Cnt> const & theCnt2)
{
	WatchError
	mWtc = Wc2;
	mCnt2 = new t2<Cnt,Cnt>(theCnt2);
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(t3<Cnt,Cnt,Cnt> const & theCnt3)
{
	WatchError
	mWtc = Wc3;
	mCnt3 = new t3<Cnt,Cnt,Cnt>(theCnt3);
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(t2<Int,Int> const & theInt2)
{
	WatchError
	mWtc = Wi2;
	mInt2 = new t2<Int,Int>(theInt2);
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(t3<Int,Int,Int> const & theInt3)
{
	WatchError
	mWtc = Wi3;
	mInt3 = new t3<Int,Int,Int>(theInt3);
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(t2<Flt,Flt> const & theFlt2)
{
	WatchError
	mWtc = Wf2;
	mFlt2 = new t2<Flt,Flt>(theFlt2);
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(t3<Flt,Flt,Flt> const & theFlt3)
{
	WatchError
	mWtc = Wf3;
	mFlt3 = new t3<Flt,Flt,Flt>(theFlt3);
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(b1<Bln,kmm> const & theBlnk)
{
	WatchError
	mWtc = Wbk;
	mBlnk = new b1<Bln,kmm>(theBlnk);
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(b1<Cnt,kmm> const & theCntk)
{
	WatchError
	mWtc = Wck;
	mCntk = new b1<Cnt,kmm>(theCntk);
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(b1<Int,kmm> const & theIntk)
{
	WatchError
	mWtc = Wik;
	mIntk = new b1<Int,kmm>(theIntk);
	CatchError
}



/*!
	The initialiser.
*/
inline Wrp::Wrp(b1<Flt,kmm> const & theFltk)
{
	WatchError
	mWtc = Wfk;
	mFltk = new b1<Flt,kmm>(theFltk);
	CatchError
}


/*!
	Return a boolean.
*/
inline void Wrp::item(Bln & theBln) const
{
	WatchError
	Warn(mWtc != Wb, eTypeMismatch);

	theBln = mBln;
	CatchError
}



/*!
	Return a countable.
*/
inline void Wrp::item(Cnt & theCnt) const
{
	WatchError
	Warn(mWtc != Wc, eTypeMismatch);

	theCnt = mCnt;
	CatchError
}



/*!
	Return an integer.
*/
inline void Wrp::item(Int & theInt) const
{
	WatchError
	Warn(mWtc != Wi, eTypeMismatch);

	theInt = mInt;
	CatchError
}




/*!
	Return a float.
*/
inline void Wrp::item(Flt & theFlt) const
{
	WatchError
	Warn(mWtc != Wf, eTypeMismatch);

	theFlt = mFlt;
	CatchError
}



/*!
	Return a boolean pair.
*/
inline void Wrp::item(t2<Bln,Bln> & theBln2) const
{
	WatchError
	Warn(mWtc != Wb2, eTypeMismatch);

	theBln2 = *mBln2;
	CatchError
}



/*!
	Return a boolean triple.
*/
inline void Wrp::item(t3<Bln,Bln,Bln> & theBln3) const
{
	WatchError
	Warn(mWtc != Wb3, eTypeMismatch);

	theBln3 = *mBln3;
	CatchError
}



/*!
	Return a countable pair.
*/
inline void Wrp::item(t2<Cnt,Cnt> & theCnt2) const
{
	WatchError
	Warn(mWtc != Wc2, eTypeMismatch);

	theCnt2 = *mCnt2;
	CatchError
}



/*!
	Return a countable triple.
*/
inline void Wrp::item(t3<Cnt,Cnt,Cnt> & theCnt3) const
{
	WatchError
	Warn(mWtc != Wc3, eTypeMismatch);

	theCnt3 = *mCnt3;
	CatchError
}



/*!
	Return an integer pair.
*/
inline void Wrp::item(t2<Int,Int> & theInt2) const
{
	WatchError
	Warn(mWtc != Wi2, eTypeMismatch);

	theInt2 = *mInt2;
	CatchError
}



/*!
	Return an integer triple.
*/
inline void Wrp::item(t3<Int,Int,Int> & theInt3) const
{
	WatchError
	Warn(mWtc != Wi3, eTypeMismatch);

	theInt3 = *mInt3;
	CatchError
}



/*!
	Return a float pair.
*/
inline void Wrp::item(t2<Flt,Flt> & theFlt2) const
{
	WatchError
	Warn(mWtc != Wf2, eTypeMismatch);

	theFlt2 = *mFlt2;
	CatchError
}



/*!
	Return a float triple.
*/
inline void Wrp::item(t3<Flt,Flt,Flt> & theFlt3) const
{
	WatchError
	Warn(mWtc != Wf3, eTypeMismatch);

	theFlt3 = *mFlt3;
	CatchError
}




/*!
	Return a boolean array.
*/
inline void Wrp::item(b1<Bln,kmm> & theBlnk) const
{
	WatchError
	Warn(mWtc != Wbk, eTypeMismatch);

	theBlnk = *mBlnk;
	CatchError
}



/*!
	Return a countable array.
*/
inline void Wrp::item(b1<Cnt,kmm> & theCntk) const
{
	WatchError
	Warn(mWtc != Wck, eTypeMismatch);

	theCntk = *mCntk;
	CatchError
}




/*!
	Return an integer array.
*/
inline void Wrp::item(b1<Int,kmm> & theIntk) const
{
	WatchError
	Warn(mWtc != Wik, eTypeMismatch);

	theIntk = *mIntk;
	CatchError
}




/*!
	Return a float array.
*/
inline void Wrp::item(b1<Flt,kmm> & theFltk) const
{
	WatchError
	Warn(mWtc != Wfk, eTypeMismatch);

	theFltk = *mFltk;
	CatchError
}



/*!
	Check wrapper.
*/
inline Bll Wrp::chkWrap(Wtc const theWtc) const
{
	WatchError
	return mWtc == theWtc;
	CatchError
}



/*!
	Wrapper type.
*/
inline Wtc Wrp::WrapType() const
{
	WatchError
	return mWtc;
	CatchError
}




/*!
	Return a boolean.
*/
inline Bln const & Wrp::itemBln() const
{
	WatchError
	Warn(mWtc != Wb, eTypeMismatch);

	return mBln;
	CatchError
}



/*!
	Return an integer.
*/
inline Cnt const & Wrp::itemCnt() const
{
	WatchError
	Warn(mWtc != Wc, eTypeMismatch);

	return mCnt;
	CatchError
}



/*!
	Return an integer.
*/
inline Int const & Wrp::itemInt() const
{
	WatchError
	Warn(mWtc != Wi, eTypeMismatch);

	return mInt;
	CatchError
}




/*!
	Return a countable.
*/
inline Flt const & Wrp::itemFlt() const
{
	WatchError
	Warn(mWtc != Wf, eTypeMismatch);

	return mFlt;
	CatchError
}



/*!
	Return a boolean pair.
*/
inline t2<Bln,Bln> const & Wrp::itemBln2() const
{
	WatchError
	Warn(mWtc != Wb2, eTypeMismatch);

	return *mBln2;
	CatchError
}



/*!
	Return a boolean triple.
*/
inline t3<Bln,Bln,Bln> const & Wrp::itemBln3() const
{
	WatchError
	Warn(mWtc != Wb3, eTypeMismatch);

	return *mBln3;
	CatchError
}



/*!
	Return a countable pair.
*/
inline t2<Cnt,Cnt> const & Wrp::itemCnt2() const
{
	WatchError
	Warn(mWtc != Wc2, eTypeMismatch);

	return *mCnt2;
	CatchError
}



/*!
	Return a countable pair.
*/
inline t3<Cnt,Cnt,Cnt> const & Wrp::itemCnt3() const
{
	WatchError
	Warn(mWtc != Wc3, eTypeMismatch);

	return *mCnt3;
	CatchError
}



/*!
	Return an integer pair.
*/
inline t2<Int,Int> const & Wrp::itemInt2() const
{
	WatchError
	Warn(mWtc != Wi2, eTypeMismatch);

	return *mInt2;
	CatchError
}



/*!
	Return an integer triple.
*/
inline t3<Int,Int,Int> const & Wrp::itemInt3() const
{
	WatchError
	Warn(mWtc != Wi3, eTypeMismatch);

	return *mInt3;
	CatchError
}



/*!
	Return a float pair.
*/
inline t2<Flt,Flt> const & Wrp::itemFlt2() const
{
	WatchError
	Warn(mWtc != Wf2, eTypeMismatch);

	return *mFlt2;
	CatchError
}



/*!
	Return a float triple.
*/
inline t3<Flt,Flt,Flt> const & Wrp::itemFlt3() const
{
	WatchError
	Warn(mWtc != Wf3, eTypeMismatch);

	return *mFlt3;
	CatchError
}




/*!
	Return a boolean array.
*/
inline b1<Bln,kmm> const & Wrp::itemBlnk() const
{
	WatchError
	Warn(mWtc != Wbk, eTypeMismatch);

	return *mBlnk;
	CatchError
}



/*!
	Return a countable array.
*/
inline b1<Cnt,kmm> const & Wrp::itemCntk() const
{
	WatchError
	Warn(mWtc != Wck, eTypeMismatch);

	return *mCntk;
	CatchError
}




/*!
	Return an integer array.
*/
inline b1<Int,kmm> const & Wrp::itemIntk() const
{
	WatchError
	Warn(mWtc != Wik, eTypeMismatch);

	return *mIntk;
	CatchError
}




/*!
	Return a float array.
*/
inline b1<Flt,kmm> const & Wrp::itemFltk() const
{
	WatchError
	Warn(mWtc != Wfk, eTypeMismatch);

	return *mFltk;
	CatchError
}



/*!
	Return a boolean.
*/
inline Bln & Wrp::itemBln()
{
	WatchError
	Warn(mWtc != Wb, eTypeMismatch);

	return mBln;
	CatchError
}



/*!
	Return a countable.
*/
inline Cnt & Wrp::itemCnt()
{
	WatchError
	Warn(mWtc != Wc, eTypeMismatch);

	return mCnt;
	CatchError
}



/*!
	Return an integer.
*/
inline Int & Wrp::itemInt()
{
	WatchError
	Warn(mWtc != Wi, eTypeMismatch);

	return mInt;
	CatchError
}



/*!
	Return a float.
*/
inline Flt & Wrp::itemFlt()
{
	WatchError
	Warn(mWtc != Wf, eTypeMismatch);

	return mFlt;
	CatchError
}



/*!
	Return a boolean pair.
*/
inline t2<Bln,Bln> & Wrp::itemBln2()
{
	WatchError
	Warn(mWtc != Wb2, eTypeMismatch);

	return *mBln2;
	CatchError
}



/*!
	Return a boolean triple.
*/
inline t3<Bln,Bln,Bln> & Wrp::itemBln3()
{
	WatchError
	Warn(mWtc != Wb3, eTypeMismatch);

	return *mBln3;
	CatchError
}



/*!
	Return a countable pair.
*/
inline t2<Cnt,Cnt> & Wrp::itemCnt2()
{
	WatchError
	Warn(mWtc != Wc2, eTypeMismatch);

	return *mCnt2;
	CatchError
}



/*!
	Return a countable triple.
*/
inline t3<Cnt,Cnt,Cnt> & Wrp::itemCnt3()
{
	WatchError
	Warn(mWtc != Wc3, eTypeMismatch);

	return *mCnt3;
	CatchError
}




/*!
	Return an integer pair.
*/
inline t2<Int,Int> & Wrp::itemInt2()
{
	WatchError
	Warn(mWtc != Wi2, eTypeMismatch);

	return *mInt2;
	CatchError
}



/*!
	Return an integer triple.
*/
inline t3<Int,Int,Int> & Wrp::itemInt3()
{
	WatchError
	Warn(mWtc != Wi3, eTypeMismatch);

	return *mInt3;
	CatchError
}



/*!
	Return a float pair.
*/
inline t2<Flt,Flt> & Wrp::itemFlt2()
{
	WatchError
	Warn(mWtc != Wf2, eTypeMismatch);

	return *mFlt2;
	CatchError
}



/*!
	Return a float triple.
*/
inline t3<Flt,Flt,Flt> & Wrp::itemFlt3()
{
	WatchError
	Warn(mWtc != Wf3, eTypeMismatch);

	return *mFlt3;
	CatchError
}



/*!
	Return a boolean array.
*/
inline b1<Bln,kmm> & Wrp::itemBlnk()
{
	WatchError
	Warn(mWtc != Wbk, eTypeMismatch);

	return *mBlnk;
	CatchError
}




/*!
	Return a countable array.
*/
inline b1<Cnt,kmm> & Wrp::itemCntk()
{
	WatchError
	Warn(mWtc != Wck, eTypeMismatch);

	return *mCntk;
	CatchError
}




/*!
	Return an integer array.
*/
inline b1<Int,kmm> & Wrp::itemIntk()
{
	WatchError
	Warn(mWtc != Wik, eTypeMismatch);

	return *mIntk;
	CatchError
}




/*!
	Return a float array.
*/
inline b1<Flt,kmm> & Wrp::itemFltk()
{
	WatchError
	Warn(mWtc != Wfk, eTypeMismatch);

	return *mFltk;
	CatchError
}



closeKangarooSpace



#endif // WrpHppIncluded
