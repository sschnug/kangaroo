/*!
	@file bind.tcc
	@brief The source file for bounded operator templates.
	@details This is the source file for bounded operator templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef BindTccIncluded
#define BindTccIncluded



#include "cbls/frames/idx.hh"


openKangarooSpace



/*!
	@class nest
	@brief A class to represent the nested bounded operators.
	@details This class represents the nested bounded operators.
*/
template <typename bop, typename top> class nest
{
	public:
		typedef bop Bop;					//!< @brief Bop. @details Bottom operator.
		typedef top Top;					//!< @brief Top. @details Top operator.
		typedef typename Bop::InxTyp InxTyp;//!< @brief Inx type. @details Input type.
		typedef typename Top::OutTyp OutTyp;//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		Bop const mBop;
		Top const mTop;

		/*! @brief Destructor. @details The destructor. */
		~nest()
			{ /* Nothing to be done. */ }

		/*! @brief Constructor. @details The constructor. */
		nest() : mBop(), mTop()
			{ /* Nothing to be done. */ }

		/*! @brief Duplicator. @details The duplicator. */
		nest(nest<bop,top> const & that) : mBop(that.mBop), mTop(that.mTop)
			{ /* Nothing to be done. */ }

		/*! @brief Assigner. @details The assigner. */
		nest<bop,top> const & operator=(nest<bop,top> const & that)
		{
			if (this != that)
				mBop = that.mBop, mTop = that.mTop;
			return * this;
		}

		/*! @brief Initialiser. @details The initialiser. */
		nest(Bop const & theBop, Top const & theTop) : mBop(theBop), mTop(theTop)
			{ /* Nothing to be done. */ }

		/*! @brief Check. @details Check operation required? */
		Bll chk(Bll const Ichk, InxTyp const & Idat) const
			{ return mTop.chk(mBop.chk(Ichk, Idat), mBop.iof(Idat));  }

		/*! @brief Operation. @details Perform operation. */
		OutTyp iof(InxTyp const & Idat) const
			{ return mTop.iof(mBop.iof(Idat)); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		void slf(InxTyp const & Isp, InxTyp const & Ilp, OutTyp & Osp, OutTyp & Olp)
//			{
//				typename Bop::OutTyp tSp, tLp;
//				mBop.slf(Isp, Ilp, tSp, tLp);
//				mTop.slf(tSp, tLp, Osp, Olp);
//			}

		Hvl hashval() const
			{ return mixHash(mBop.hashval(), mTop.hashval()); }

		Bll equate(nest<bop,top> const & that) const
			{ return mBop.equate(that.mBop) && mTop.equate(that.mTop); }
};



/*!
	@class bind1
	@brief A class to represent the pseudo bound unary operator.
	@details This class represents the pseudo bound unary operator.
*/
template <typename op> class bind1
{
	public:
		typedef op Op;						//!< @brief Op. @details Operator.
		typedef typename Op::InxTyp InxTyp; //!< @brief Inx type. @details Input type.
		typedef typename Op::OutTyp OutTyp; //!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Destructor. @details The destructor. */
		~bind1()
			{ /* Nothing to be done. */ }

		/*! @brief Constructor. @details The constructor. */
		bind1()
			{ /* Nothing to be done. */ }

		/*! @brief Duplicator. @details The duplicator. */
		bind1(bind1<op> const & that)
			{ /* Nothing to be done. */ }

		/*! @brief Assigner. @details The assigner. */
		bind1<op> const & operator=(bind1<op> const & that)
		{
			return * this;
		}

		/*! @brief Check. @details Check operation required? */
		Bll chk(Bll const Chk, InxTyp const & Dat) const
			{ return Op::chk(Chk,Dat); }

		/*! @brief Operation. @details Perform operation. */
		OutTyp iof(InxTyp const & Dat) const
			{ return Op::iof(Dat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		void slf(InxTyp const & Isp, InxTyp const & Ilp, OutTyp & Osp, OutTyp & Olp)
//			{
//				Op::slf(Isp, Ilp, Osp, Olp);
//			}

		Hvl hashval() const
			{ return 0; }

		Bll equate(bind1<op> const & that) const
			{ return true; }
};



/*!
	@class bind2r
	@brief A class to represent the right-bound binary operator.
	@details This class represents the right-bound binary operator.
*/
template <typename op> class bind2r
{
	public:
		typedef op Op;						//!< @brief Op. @details Operator.
		typedef typename Op::InxTyp InxTyp; //!< @brief Inx type. @details Input type.
		typedef typename Op::OutTyp OutTyp; //!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		InxTyp const mRdat;

		/*! @brief Destructor. @details The destructor. */
		~bind2r()
			{ /* Nothing to be done. */ }

		/*! @brief Constructor. @details The constructor. */
		bind2r() : mRdat()
			{ /* Nothing to be done. */ }

		/*! @brief Duplicator. @details The duplicator. */
		bind2r(bind2r<op> const & that) : mRdat(that.mRdat)
			{ /* Nothing to be done. */ }

		/*! @brief Assigner. @details The assigner. */
		bind2r<op> const & operator=(bind2r<op> const & that)
		{
			if (this != that)
				mRdat = that.mRdat;
			return * this;
		}

		/*! @brief Initialiser. @details The initialiser. */
		bind2r(InxTyp const & theRdat) : mRdat(theRdat)
			{ /* Nothing to be done. */ }

		/*! @brief Check. @details Check operation required? */
		Bll chk(Bll const Lchk, InxTyp const & Ldat) const
			{ return Op::chk(Lchk, false, Ldat, mRdat); }

		/*! @brief Operation. @details Perform operation. */
		OutTyp iof(InxTyp const & Ldat) const
			{ return Op::iof(Ldat, mRdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		void slf(InxTyp const & Isp, InxTyp const & Ilp, OutTyp & Osp, OutTyp & Olp)
//			{
//				Op::slf(Isp, mRdat, Ilp, mRdat, Osp, Olp);
//			}

		Hvl hashval() const
			{ return calcHash(mRdat); }

		Bll equate(bind2r<op> const & that) const
			{ return eq<InxTyp,Bll>::iof(mRdat, that.mRdat); }
};




/*!
	@class bind2l
	@brief A class to represent the left-bound binary operator.
	@details This class represents the left bound binary operator.
*/
template <typename op> class bind2l
{
	public:
		typedef op Op;						//!< @brief Op. @details Operator.
		typedef typename Op::InxTyp InxTyp; //!< @brief Inx type. @details Input type.
		typedef typename Op::OutTyp OutTyp; //!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		InxTyp const mLdat;

		/*! @brief Destructor. @details The destructor. */
		~bind2l()
			{ /* Nothing to be done. */ }

		/*! @brief Constructor. @details The constructor. */
		bind2l() : mLdat()
			{ /* Nothing to be done. */ }

		/*! @brief Duplicator. @details The duplicator. */
		bind2l(bind2l<op> const & that) : mLdat(that.mLdat)
			{ /* Nothing to be done. */ }

		/*! @brief Assigner. @details The assigner. */
		bind2l<op> const & operator=(bind2l<op> const & that)
		{
			if (this != that)
				mLdat = that.mLdat;
			return * this;
		}

		/*! @brief Initialiser. @details The initialiser. */
		bind2l(InxTyp const & theLdat) : mLdat(theLdat)
			{}

		/*! @brief Check. @details Check operation required? */
		Bll chk(Bll const Rchk, InxTyp const & Rdat) const
			{ return Op::chk(false, Rchk, mLdat, Rdat); }

		/*! @brief Operation. @details Perform operation. */
		OutTyp iof(InxTyp const & Rdat) const
			{ return Op::iof(mLdat, Rdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		void slf(InxTyp const & Isp, InxTyp const & Ilp, OutTyp & Osp, OutTyp & Olp)
//			{
//				Op::slf(mLdat, Isp, mLdat, Ilp, Osp, Olp);
//			}

		Hvl hashval() const
			{ return calcHash(mLdat); }

		Bll equate(bind2l<op> const & that) const
			{ return mLdat == that.mLdat; }
};



/*!
	@class bind3lr
	@brief A class to represent the left-right-bound ternary operator.
	@details This class represents the left-right-bound ternary operator.
*/
template <typename op> class bind3lr
{
	public:
		typedef op Op;						//!< @brief Op. @details Operator.
		typedef typename Op::InxTyp InxTyp; //!< @brief Inx type. @details Input type.
		typedef typename Op::OutTyp OutTyp; //!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		InxTyp const mLdat;
		InxTyp const mRdat;

		/*! @brief Destructor. @details The destructor. */
		~bind3lr()
			{ /* Nothing to be done. */ }

		/*! @brief Constructor. @details The constructor. */
		bind3lr() : mLdat(), mRdat()
			{ /* Nothing to be done. */ }

		/*! @brief Duplicator. @details The duplicator. */
		bind3lr(bind3lr<op> const & that) : mLdat(that.mLdat), mRdat(that.mRdat)
			{ /* Nothing to be done. */ }

		/*! @brief Assigner. @details The assigner. */
		bind3lr<op> const & operator=(bind3lr<op> const & that)
		{
			if (this != that)
				mLdat = that.mLdat, mRdat = that.mRdat;
			return * this;
		}

		/*! @brief Initialiser. @details The initialiser. */
		bind3lr(InxTyp const & theLdat, InxTyp const & theRdat) :
					mLdat(theLdat), mRdat(theRdat)
			{}

		/*! @brief Check. @details Check operation required? */
		Bll chk(Bll const Mchk, InxTyp const & Mdat) const
			{ return Op::chk(Mchk, false, false, Mdat, mLdat, mRdat); }

		/*! @brief Operation. @details Perform operation. */
		OutTyp iof(InxTyp const & Mdat) const
			{ return Op::iof(Mdat, mLdat, mRdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		void slf(InxTyp const & Isp, InxTyp const & Ilp, OutTyp & Osp, OutTyp & Olp)
//			{
//				Op::slf(Isp, mLdat, mRdat, Ilp, mLdat, mRdat, Osp, Olp);
//			}

		Hvl hashval() const
			{ return mixHash(calcHash(mLdat), calcHash(mRdat)); }

		Bll equate(bind3lr<op> const & that) const
			{ return eq<InxTyp,Bll>::iof(mLdat, that.mLdat) &&
					eq<InxTyp,Bll>::iof(mRdat, that.mRdat); }
};



/*!
	@class bindc3lr
	@brief A class to represent the left-right-bound conditional ternary operator.
	@details This class represents the left-right-bound conditional ternary operator.
*/
template <typename op> class bindc3lr
{
	public:
		typedef op Op;						//!< @brief Op. @details Operator.
		typedef typename op::InxTyp InxTyp;	//!< @brief Inx type. @details Input type.
		typedef typename Op::InyTyp InyTyp; //!< @brief Iny type. @details Input type.
		typedef typename Op::OutTyp OutTyp; //!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		InyTyp const mLdat;
		InyTyp const mRdat;

		/*! @brief Destructor. @details The destructor. */
		~bindc3lr()
			{ /* Nothing to be done. */ }

		/*! @brief Constructor. @details The constructor. */
		bindc3lr() : mLdat(), mRdat()
			{ /* Nothing to be done. */ }

		/*! @brief Duplicator. @details The duplicator. */
		bindc3lr(bindc3lr<op> const & that) : mLdat(that.mLdat), mRdat(that.mRdat)
			{ /* Nothing to be done. */ }

		/*! @brief Assigner. @details The assigner. */
		bindc3lr<op> const & operator=(bindc3lr<op> const & that)
		{
			if (this != that)
				mLdat = that.mLdat, mRdat = that.mRdat;
			return * this;
		}

		/*! @brief Initialiser. @details The initialiser. */
		bindc3lr(InyTyp const & theLdat, InyTyp const & theRdat) : mLdat(theLdat), mRdat(theRdat)
			{}

		/*! @brief Check. @details Check operation required? */
		Bll chk(Bll const Cchk, InxTyp const & Cdat) const
			{ return Op::chk(Cchk, false, false, Cdat, mLdat, mRdat); }

		/*! @brief Operation. @details Perform operation. */
		OutTyp iof(InxTyp const & Cdat) const
			{ return Op::iof(Cdat, mLdat, mRdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		void slf(InxTyp const & Csp, InxTyp const & Clp, OutTyp & Osp, OutTyp & Olp)
//			{
//				Op::slf(Csp, mLdat, mRdat, Clp, mLdat, mRdat, Osp, Olp);
//			}

		Hvl hashval() const
			{ return mixHash(calcHash(mLdat), calcHash(mRdat)); }

		Bll equate(bindc3lr<op> const & that) const
			{ return eq<InyTyp,Bll>::iof(mLdat, that.mLdat) &&
				eq<InyTyp,Bll>::iof(mRdat, that.mRdat); }
};



/*!
	@class bindcNd
	@brief A class to represent the input-bound n-ary conditional operator.
	@details This class represents the input-bound n-ary conditional operator.
*/
template <typename op> class bindcNd
{
	public:
		typedef op Op;						//!< @brief Op. @details Operator.
		typedef typename Op::InxTyp InxTyp;	//!< @brief Inx type. @details Input type.
		typedef typename Op::InyTyp InyTyp;	//!< @brief Iny type. @details Input type.
		typedef typename Op::OutTyp OutTyp; //!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		b1<InyTyp,kmm> const mIdats;

		/*! @brief Destructor. @details The destructor. */
		~bindcNd()
			{ /* Nothing to be done. */ }

		/*! @brief Constructor. @details The constructor. */
		bindcNd() : mIdats(0)
			{ /* Nothing to be done. */ }

		/*! @brief Duplicator. @details The duplicator. */
		bindcNd(bindcNd<op> const & that) : mIdats(that.mIdats)
			{ /* Nothing to be done. */ }

		/*! @brief Assigner. @details The assigner. */
		bindcNd<op> const & operator=(bindcNd<op> const & that)
		{
			if (this != that)
				mIdats = that.mIdats;
			return * this;
		}

		/*! @brief Initialiser. @details The initialiser. */
		bindcNd(InyTyp const * theIdats, Dim const theCount) : mIdats(theIdats, theCount)
			{}

		/*! @brief Check. @details Check operation required? */
		Bll chk(Bll const Cchk, InxTyp const & Cdat) const
		{
			b1<Bll,kmm> tIchks(mIdats.itemCount());
			for(Idx tIdx = 0; tIdx < mIdats.itemCount(); ++tIdx)
				tIchks[tIdx] = false;
			return Op::chk(Cchk, Cdat, tIchks.items(), mIdats.items(), mIdats.itemCount());
		}

		/*! @brief Operation. @details Perform operation. */
		OutTyp iof(InxTyp const & Cdat) const
			{ return Op::iof(Cdat, mIdats.items(), mIdats.itemCount()); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		void slf(InxTyp const & Csp, InxTyp const & Clp, OutTyp & Osp, OutTyp & Olp)
//			{
//				Op::slf(Csp, mIdats.items(), mIdats.itemCount(), Clp, mIdats.items(), mIdats.itemCount(), Osp, Olp);
//			}

		Hvl hashval() const
		{
			Hvl tHvl = 0;
			for(Idx tIdx = 0; tIdx < mIdats.itemCount(); ++tIdx)
				tHvl = mixHash(tHvl, calcHash(mIdats[tIdx]));
			return tHvl;
		}

		Bll equate(bindcNd<op> const & that) const
		{
			if (this == & that) return true;
			for(Idx tIdx = 0; tIdx < mIdats.itemCount(); ++tIdx)
				if (ne<InyTyp,Bll>::iof(mIdats[tIdx], that.mIdats[tIdx]))
					return false;
			return true;
		}
};




/*!
	@class bindiNiddlr
	@brief A class to represent the input-bound n-ary intervals and related data operator.
	@details This class represents the input-bound n-ary intervals and related data data operator.
*/
template <typename op> class bindiNiddlr
{
	public:
		typedef op Op;						//!< @brief Op. @details Operator.
		typedef typename Op::InxTyp InxTyp;	//!< @brief Inx type. @details Input type.
		typedef typename Op::InyTyp InyTyp;	//!< @brief Iny type. @details Input type.
		typedef typename Op::InzTyp InzTyp;	//!< @brief Inz type. @details Input type.
		typedef typename Op::InkTyp InkTyp;	//!< @brief Ink type. @details Input type.
		typedef typename Op::OutTyp OutTyp; //!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		b1<InxTyp,kmm> mXdats;
		b1<InyTyp,kmm> mYdats;
		b1<InzTyp,kmm> mZdats;
		InkTyp		   mLeft;
		InkTyp		   mRight;

		/*! @brief Destructor. @details The destructor. */
		~bindiNiddlr()
			{ /* Nothing to be done. */ }

		/*! @brief Constructor. @details The constructor. */
		bindiNiddlr()
			{ /* Nothing to be done. */ }

		/*! @brief Duplicator. @details The duplicator. */
		bindiNiddlr(bindiNiddlr<op> const & that) : mXdats(that.mXdats), mYdats(that.mYdats),
					mZdats(that.mZdats), mLeft(that.mLeft), mRight(that.mRight)
			{ /* Nothing to be done. */ }

		/*! @brief Assigner. @details The assigner. */
		bindiNiddlr<op> const & operator=(bindiNiddlr<op> const & that)
		{
			if (this != that)
			{
				mXdats = that.mXdats;
				mYdats = that.mYdats;
				mZdats = that.mZdats;
				mLeft  = that.mLeft;
				mRight = that.mRight;
			}
			return * this;
		}

		/*! @brief Initialiser. @details The initialiser. */
		bindiNiddlr(InxTyp const * Xdats, InyTyp const * Ydats, InzTyp const * Zdats,
				Dim const IntervalCount, InkTyp const dfltLeft, InkTyp const dlftRight) :
				mXdats(Xdats, IntervalCount + 1), mYdats(Ydats, IntervalCount),
				mZdats(Zdats, IntervalCount), mLeft(dfltLeft), mRight(dlftRight)
			{}

		/*! @brief Check. @details Check operation required? */
		Bll chk(Bll const Xchk, InxTyp const & Xdat) const
		{
			b1<Bll,kmm> tXchks(mXdats.itemCount()), tYchks(mYdats.itemCount()), tZchks(mYdats.itemCount());
			for(Idx tIdx = 0; tIdx < mXdats.itemCount(); ++tIdx)
				tXchks[tIdx] = false;
			for(Idx tIdx = 0; tIdx < mYdats.itemCount(); ++tIdx)
				tYchks[tIdx] = false;
			for(Idx tIdx = 0; tIdx < mZdats.itemCount(); ++tIdx)
				tZchks[tIdx] = false;
			return Op::chk(Xchk, Xdat, tXchks.items(), mXdats.items(), tYchks.items(), mYdats.items(),
				tZchks.items(), mZdats.items(), mZdats.itemCount());
		}

		/*! @brief Operation. @details Perform operation. */
		OutTyp iof(InxTyp const & Xdat) const
			{ return Op::iof(Xdat, mXdats.items(), mYdats.items(), mZdats.items(), mZdats.itemCount(), mLeft, mRight); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		void slf(InxTyp const & Csp, InxTyp const & Clp, OutTyp & Osp, OutTyp & Olp)
//			{
//				Op::slf(Csp, mXdats.items(), mXdats.itemCount(), mYdats.items(), mYdats.itemCount(),
//						Clp, mXdats.items(), mXdats.itemCount(), mYdats.items(), mYdats.itemCount(), Osp, Olp);
//			}

		Hvl hashval() const
		{
			Hvl tHvl = 0;
			for(Idx tIdx = 0; tIdx < mXdats.itemCount(); ++tIdx)
				tHvl = mixHash(tHvl, calcHash(mXdats[tIdx]));
			for(Idx tIdx = 0; tIdx < mYdats.itemCount(); ++tIdx)
				tHvl = mixHash(tHvl, calcHash(mYdats[tIdx]));
			for(Idx tIdx = 0; tIdx < mZdats.itemCount(); ++tIdx)
				tHvl = mixHash(tHvl, calcHash(mZdats[tIdx]));
			tHvl = mixHash(tHvl, mLeft);
			tHvl = mixHash(tHvl, mRight);
			return tHvl;
		}

		Bll equate(bindiNiddlr<op> const & that) const
		{
			if (this == & that) return true;
			if (ne<InkTyp,Bll>::iof(mLeft, that.mLeft)) return false;
			if (ne<InkTyp,Bll>::iof(mRight, that.mRight)) return false;
			for(Idx tIdx = 0; tIdx < mXdats.itemCount(); ++tIdx)
				if (ne<InxTyp,Bll>::iof(mXdats[tIdx], that.mXdats[tIdx]))
					return false;
			for(Idx tIdx = 0; tIdx < mYdats.itemCount(); ++tIdx)
				if (ne<InyTyp,Bll>::iof(mYdats[tIdx], that.mYdats[tIdx]))
					return false;
			for(Idx tIdx = 0; tIdx < mZdats.itemCount(); ++tIdx)
				if (ne<InzTyp,Bll>::iof(mZdats[tIdx], that.mZdats[tIdx]))
					return false;
			return true;
		}
};



closeKangarooSpace



#endif//BindTccIncluded
