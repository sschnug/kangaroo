/*!
	@file unary.tcc
	@brief The source file for unary operator templates.
	@details This is the source file for unary operator templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef UnaryTccIncluded
#define UnaryTccIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace



/*!
	@class ucast
	@brief A class to represent the unary cast operator.
	@details This class represents the unary cast operator.
*/
template <typename ixt, typename ot> class ucast
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
			{ return tc<ixt,ot>::iof(Pdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slpf(ixt const & Psp, ixt const & Plp, ot & Spf, ot & Lpf)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				Spf = iof(Psp); Lpf = iof(Plp);
//			}
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{ return Psp; }
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{ return Plp; }
};




/*!
	@class unots
	@brief A class to represent the unary not operator (satisfaction).
	@details This class represents the unary not operator (satisfaction).
*/
template <typename ixt, typename ot> class unots
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
			{ return !tc<ixt,Bll>::iof(Pdat); }

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{ return false; }
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{ return true; }
};


/*!
	@class unnots
	@brief A class to represent the unary not-not operator (satisfaction).
	@details This class represents the unary not-not operator (satisfaction).
*/
template <typename ixt, typename ot> class unnots
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
			{ return tc<ixt,Bll>::iof(Pdat); }

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{ return false; }
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{ return true; }
};



/*!
	@class unotu
	@brief A class to represent the unary not operator (unsatisfaction).
	@details This class represents the unary not operator (unsatisfaction).
*/
template <typename ixt, typename ot> class unotu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
			{ return tc<ixt,Bll>::iof(Pdat); }
};


/*!
	@class unnotu
	@brief A class to represent the unary not-not operator (unsatisfaction).
	@details This class represents the unary not-not operator (unsatisfaction).
*/
template <typename ixt, typename ot> class unnotu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
			{ return !tc<ixt,Bll>::iof(Pdat); }
};



/*!
	@class uneg
	@brief A class to represent the unary neg operator.
	@details This class represents the unary neg operator.
*/
template <typename ixt, typename ot> class uneg
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
			{ return -Pdat; }
};



/*!
	@class uabs
	@brief A class to represent the unary abs operator.
	@details This class represents the unary abs operator.
*/
template <typename ixt, typename ot> class uabs
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
			{ return abs(Pdat); }
};



/*!
	@class usin
	@brief A class to represent the unary sin operator.
	@details This class represents the unary sin operator.
*/
template <typename ixt, typename ot> class usin
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = sin(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}
};




/*!
	@class uasin
	@brief A class to represent the unary asin operator.
	@details This class represents the unary asin operator.
*/
template <typename ixt, typename ot> class uasin
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = asin(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}
};



/*!
	@class usinh
	@brief A class to represent the unary sinh operator.
	@details This class represents the unary sinh operator.
*/
template <typename ixt, typename ot> class usinh
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = sinh(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}
};



/*!
	@class uasinh
	@brief A class to represent the unary asinh operator.
	@details This class represents the unary asinh operator.
*/
template <typename ixt, typename ot> class uasinh
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = log(Pdat + sqrt(1 + Pdat * Pdat));
			Alert(errno, eMathLibrary);
			return tResult;
		}
};



/*!
	@class ucos
	@brief A class to represent the unary cos operator.
	@details This class represents the unary cos operator.
*/
template <typename ixt, typename ot> class ucos
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = cos(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}
};



/*!
	@class uacos
	@brief A class to represent the unary acos operator.
	@details This class represents the unary acos operator.
*/
template <typename ixt, typename ot> class uacos
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = acos(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}
};



/*!
	@class ucosh
	@brief A class to represent the unary cosh operator.
	@details This class represents the unary cosh operator.
*/
template <typename ixt, typename ot> class ucosh
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = cosh(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}
};



/*!
	@class uacosh
	@brief A class to represent the unary acosh operator.
	@details This class represents the unary acosh operator.
*/
template <typename ixt, typename ot> class uacosh
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = log(Pdat + sqrt(Pdat * Pdat - 1));
			Alert(errno, eMathLibrary);
			return tResult;
		}
};


/*!
	@class utan
	@brief A class to represent the unary tan operator.
	@details This class represents the unary tan operator.
*/
template <typename ixt, typename ot> class utan
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = tan(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}
};


/*!
	@class uatan
	@brief A class to represent the unary atan operator.
	@details This class represents the unary atan operator.
*/
template <typename ixt, typename ot> class uatan
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = atan(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Psp);
//			}
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Plp);
//			}
};



/*!
	@class utanh
	@brief A class to represent the unary tanh operator.
	@details This class represents the unary tanh operator.
*/
template <typename ixt, typename ot> class utanh
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = tanh(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Psp);
//			}
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Plp);
//			}
};



/*!
	@class uatanh
	@brief A class to represent the unary atanh operator.
	@details This class represents the unary atanh operator.
*/
template <typename ixt, typename ot> class uatanh
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = log((1 + Pdat)/(1 - Pdat))/2;
			Alert(errno, eMathLibrary);
			return tResult;
		}

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Psp);
//			}
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Plp);
//			}
};




/*!
	@class uexp
	@brief A class to represent the unary exp operator.
	@details This class represents the unary exp operator.
*/
template <typename ixt, typename ot> class uexp
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = exp(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Psp);
//			}
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Plp);
//			}
};



/*!
	@class ulog
	@brief A class to represent the unary log operator.
	@details This class represents the unary log operator.
*/
template <typename ixt, typename ot> class ulog
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = log(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Psp);
//			}
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Plp);
//			}
};



/*!
	@class ulog10
	@brief A class to represent the unary log10 operator.
	@details This class represents the unary log10 operator.
*/
template <typename ixt, typename ot> class ulog10
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = log10(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Psp);
//			}
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Plp);
//			}
};



/*!
	@class ulog2
	@brief A class to represent the unary log2 operator.
	@details This class represents the unary log2 operator.
*/
template <typename ixt, typename ot> class ulog2
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = log(Pdat) / log(2);
			Alert(errno, eMathLibrary);
			return tResult;
		}

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Psp);
//			}
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Plp);
//			}
};



/*!
	@class usqrt
	@brief A class to represent the unary sqrt operator.
	@details This class represents the unary sqrt operator.
*/
template <typename ixt, typename ot> class usqrt
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
		{
			Flt tResult = sqrt(Pdat);
			Alert(errno, eMathLibrary);
			return tResult;
		}

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Psp);
//			}
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Plp);
//			}
};



/*!
	@class usqr
	@brief A class to represent the unary sqr operator.
	@details This class represents the unary sqr operator.
*/
template <typename ixt, typename ot> class usqr
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
			{ return Pdat * Pdat; }

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				if (Psp > 0) return iof(Plp);
//				if (Plp < 0) return iof(Psp);
//				return 0;
//			}
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return max(iof(Plp), iof(Psp));
//			}
//
//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slpf(ixt const & Psp, ixt const & Plp, ot & Spf, ot & Lpf)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				Spf = iof(Psp); Lpf = iof(Plp);
//			}
};



/*!
	@class ucube
	@brief A class to represent the unary cube operator.
	@details This class represents the unary cube operator.
*/
template <typename ixt, typename ot> class ucube
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 1;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, ixt const & Pdat)
			{ return Pchk; }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat)
			{ return Pdat * Pdat * Pdat; }

//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Psp);
//			}
//
//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Psp, ixt const & Plp)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				return iof(Plp);
//			}
//
//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slpf(ixt const & Psp, ixt const & Plp, ot & Spf, ot & Lpf)
//			{
//				Warn(Psp > Plp, eRangeDefn);
//				Spf = iof(Psp); Lpf = iof(Plp);
//			}
};



closeKangarooSpace



#endif//UnaryTccIncluded
