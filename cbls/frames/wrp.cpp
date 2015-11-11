/*!
	@file wrp.cpp
	@brief The implementation file for the Wrap class.
	@details This is the implementation file for the Wrap class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see wrp.hpp
*/



#include "cbls/frames/wrp.hpp"



openKangarooSpace



/*!
	The destructor.
*/
Wrp::~Wrp()
{
	WatchError
	switch(mWtc)
	{
		case Wb2 : delete mBln2; break;
		case Wb3 : delete mBln3; break;
		case Wc2 : delete mCnt2; break;
		case Wc3 : delete mCnt3; break;
		case Wi2 : delete mInt2; break;
		case Wi3 : delete mInt3; break;
		case Wf2 : delete mFlt2; break;
		case Wf3 : delete mFlt3; break;
		case Wbk : delete mBlnk; break;
		case Wck : delete mCntk; break;
		case Wik : delete mIntk; break;
		case Wfk : delete mFltk; break;
		default: break;
	}
	CatchError
}



/*!
	The duplicator.
*/
Wrp::Wrp(Wrp const & that) : mWtc(that.mWtc)
{
	WatchError
	switch(mWtc)
	{
		case Wb : mBln = that.mBln; break;
		case Wc : mCnt = that.mCnt; break;
		case Wi : mInt = that.mInt; break;
		case Wf : mFlt = that.mFlt; break;
		case Wb2 : mBln2 = new t2<Bln,Bln>(*that.mBln2); break;
		case Wb3 : mBln3 = new t3<Bln,Bln,Bln>(*that.mBln3); break;
		case Wc2 : mCnt2 = new t2<Cnt,Cnt>(*that.mCnt2); break;
		case Wc3 : mCnt3 = new t3<Cnt,Cnt,Cnt>(*that.mCnt3); break;
		case Wi2 : mInt2 = new t2<Int,Int>(*that.mInt2); break;
		case Wi3 : mInt3 = new t3<Int,Int,Int>(*that.mInt3); break;
		case Wf2 : mFlt2 = new t2<Flt,Flt>(*that.mFlt2); break;
		case Wf3 : mFlt3 = new t3<Flt,Flt,Flt>(*that.mFlt3); break;
		case Wbk : mBlnk = new b1<Bln,kmm>(*that.mBlnk); break;
		case Wck : mCntk = new b1<Cnt,kmm>(*that.mCntk); break;
		case Wik : mIntk = new b1<Int,kmm>(*that.mIntk); break;
		case Wfk : mFltk = new b1<Flt,kmm>(*that.mFltk); break;
		default: break;
	}
	CatchError
}



/*!
	Clear the wrapper.
*/
void Wrp::clear()
{
	WatchError
	switch(mWtc)
	{
		case Wb2 : delete mBln2; break;
		case Wb3 : delete mBln3; break;
		case Wc2 : delete mCnt2; break;
		case Wc3 : delete mCnt3; break;
		case Wi2 : delete mInt2; break;
		case Wi3 : delete mInt3; break;
		case Wf2 : delete mFlt2; break;
		case Wf3 : delete mFlt3; break;
		case Wbk : delete mBlnk; break;
		case Wck : delete mCntk; break;
		case Wik : delete mIntk; break;
		case Wfk : delete mFltk; break;
		default : break;
	}
	mWtc = Ww;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (Bln const theBln)
{
	WatchError
	if (mWtc != Wb)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wb;
	}
	mBln = theBln;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (Cnt const theCnt)
{
	WatchError
	if (mWtc != Wc)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wc;
	}
	mCnt = theCnt;
	return *this;
	CatchError
}




/*!
	The assigner.
*/
Wrp const & Wrp::operator = (Int const theInt)
{
	WatchError
	if (mWtc != Wi)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wi;
	}
	mInt = theInt;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (Flt const theFlt)
{
	WatchError
	if (mWtc != Wf)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wf;
	}
	mFlt = theFlt;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (t2<Bln,Bln> const & theBln2)
{
	WatchError
	if (mWtc != Wb2)
	{
		switch(mWtc)
		{
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wb2;
		mBln2 = new t2<Bln,Bln>(theBln2);
	}
	else
		*mBln2 = theBln2;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (t3<Bln,Bln,Bln> const & theBln3)
{
	WatchError
	if (mWtc != Wb3)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;

			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wb3;
		mBln3 = new t3<Bln,Bln,Bln>(theBln3);
	}
	else
		*mBln3 = theBln3;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (t2<Cnt,Cnt> const & theCnt2)
{
	WatchError
	if (mWtc != Wc2)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;

			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wc2;
		mCnt2 = new t2<Cnt,Cnt>(theCnt2);
	}
	else
		*mCnt2 = theCnt2;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (t3<Cnt,Cnt,Cnt> const & theCnt3)
{
	WatchError
	if (mWtc != Wc3)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;

			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wc3;
		mCnt3 = new t3<Cnt,Cnt,Cnt>(theCnt3);
	}
	else
		*mCnt3 = theCnt3;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (t2<Int,Int> const & theInt2)
{
	WatchError
	if (mWtc != Wi2)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;

			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wi2;
		mInt2 = new t2<Int,Int>(theInt2);
	}
	else
		*mInt2 = theInt2;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (t3<Int,Int,Int> const & theInt3)
{
	WatchError
	if (mWtc != Wi3)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;

			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wi3;
		mInt3 = new t3<Int,Int,Int>(theInt3);
	}
	else
		*mInt3 = theInt3;
	return *this;
	CatchError
}




/*!
	The assigner.
*/
Wrp const & Wrp::operator = (t2<Flt,Flt> const & theFlt2)
{
	WatchError
	if (mWtc != Wf2)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;

			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wf2;
		mFlt2 = new t2<Flt,Flt>(theFlt2);
	}
	else
		*mFlt2 = theFlt2;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (t3<Flt,Flt,Flt> const & theFlt3)
{
	WatchError
	if (mWtc != Wf3)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;

			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wf3;
		mFlt3 = new t3<Flt,Flt,Flt>(theFlt3);
	}
	else
		*mFlt3 = theFlt3;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (b1<Bln,kmm> const & theBlnk)
{
	WatchError
	if (mWtc != Wbk)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;

			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wbk;
		mBlnk = new b1<Bln,kmm>(theBlnk);
	}
	else
		*mBlnk = theBlnk;
	return *this;
	CatchError
}




/*!
	The assigner.
*/
Wrp const & Wrp::operator = (b1<Cnt,kmm> const & theCntk)
{
	WatchError
	if (mWtc != Wck)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;

			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wck;
		mCntk = new b1<Cnt,kmm>(theCntk);
	}
	else
		*mCntk = theCntk;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (b1<Int,kmm> const & theIntk)
{
	WatchError
	if (mWtc != Wik)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;

			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = Wik;
		mIntk = new b1<Int,kmm>(theIntk);
	}
	else
		*mIntk = theIntk;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (b1<Flt,kmm> const & theFltk)
{
	WatchError
	if (mWtc != Wfk)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;

			default : break;
		}
		mWtc = Wfk;
		mFltk = new b1<Flt,kmm>(theFltk);
	}
	else
		*mFltk = theFltk;
	return *this;
	CatchError
}



/*!
	The assigner.
*/
Wrp const & Wrp::operator = (Wrp const & that)
{
	WatchError
	if (this == &that) return *this;

	if (mWtc != that.mWtc)
	{
		switch(mWtc)
		{
			case Wb2 : delete mBln2; break;
			case Wb3 : delete mBln3; break;
			case Wc2 : delete mCnt2; break;
			case Wc3 : delete mCnt3; break;
			case Wi2 : delete mInt2; break;
			case Wi3 : delete mInt3; break;
			case Wf2 : delete mFlt2; break;
			case Wf3 : delete mFlt3; break;
			case Wbk : delete mBlnk; break;
			case Wck : delete mCntk; break;
			case Wik : delete mIntk; break;
			case Wfk : delete mFltk; break;
			default : break;
		}
		mWtc = that.mWtc;
		switch(mWtc)
		{
			case Wb: mBln = that.mBln; break;
			case Wc: mCnt = that.mCnt; break;
			case Wi: mInt = that.mInt; break;
			case Wf: mFlt = that.mFlt; break;
			case Wb2: mBln2 = new t2<Bln,Bln>(*that.mBln2); break;
			case Wb3: mBln3 = new t3<Bln,Bln,Bln>(*that.mBln3); break;
			case Wc2: mCnt2 = new t2<Cnt,Cnt>(*that.mCnt2); break;
			case Wc3: mCnt3 = new t3<Cnt,Cnt,Cnt>(*that.mCnt3); break;
			case Wi2: mInt2 = new t2<Int,Int>(*that.mInt2); break;
			case Wi3: mInt3 = new t3<Int,Int,Int>(*that.mInt3); break;
			case Wf2: mFlt2 = new t2<Flt,Flt>(*that.mFlt2); break;
			case Wf3: mFlt3 = new t3<Flt,Flt,Flt>(*that.mFlt3); break;
			case Wbk: mBlnk = new b1<Bln,kmm>(*that.mBlnk); break;
			case Wck: mCntk = new b1<Cnt,kmm>(*that.mCntk); break;
			case Wik: mIntk = new b1<Int,kmm>(*that.mIntk); break;
			case Wfk: mFltk = new b1<Flt,kmm>(*that.mFltk); break;
			default: break;
		}
	}
	else
		switch(mWtc)
		{
			case Wb: mBln = that.mBln; break;
			case Wc: mCnt = that.mCnt; break;
			case Wi: mInt = that.mInt; break;
			case Wf: mFlt = that.mFlt; break;
			case Wb2: *mBln2 = *that.mBln2; break;
			case Wb3: *mBln3 = *that.mBln3; break;
			case Wc2: *mCnt2 = *that.mCnt2; break;
			case Wc3: *mCnt3 = *that.mCnt3; break;
			case Wi2: *mInt2 = *that.mInt2; break;
			case Wi3: *mInt3 = *that.mInt3; break;
			case Wf2: *mFlt2 = *that.mFlt2; break;
			case Wf3: *mFlt3 = *that.mFlt3; break;
			case Wbk: *mBlnk = *that.mBlnk; break;
			case Wck: *mCntk = *that.mCntk; break;
			case Wik: *mIntk = *that.mIntk; break;
			case Wfk: *mFltk = *that.mFltk; break;
			default: break;
		}
	return *this;
	CatchError
}



closeKangarooSpace
