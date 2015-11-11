/*!
	@file blogic.tcc
	@brief The source file for various binary logical operator templates.
	@details This is the source file for binary logical operator templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef BlogicTccIncluded
#define BlogicTccIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace


/*!
	@class bands
	@brief A class to represent the logical and operator (satisfaction).
	@details This class represents the logical and operator (satisfaction).
*/
template <typename ixt, typename ot> class bands
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && tc<ixt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,Bll>::iof(Ldat) && tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf = Lsp && Rsp, tLpf = Llp && Rlp;
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bnands
	@brief A class to represent the logical nand operator (satisfaction).
	@details This class represents the logical nand operator (satisfaction).
*/
template <typename ixt, typename ot> class bnands
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && tc<ixt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return !tc<ixt,Bll>::iof(Ldat) || !tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf = !Lsp || !Rsp, tLpf = !Llp || !Rlp;
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bors
	@brief A class to represent the logical or operator (satisfaction).
	@details This class represents the logical or operator (satisfaction).
*/
template <typename ixt, typename ot> class bors
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && !tc<ixt,Bll>::iof(Rdat)) || (Rchk && !tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,Bll>::iof(Ldat) || tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf = Lsp || Rsp, tLpf = Llp || Rlp;
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bnors
	@brief A class to represent the logical nor operator (satisfaction).
	@details This class represents the logical nor operator (satisfaction).
*/
template <typename ixt, typename ot> class bnors
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && !tc<ixt,Bll>::iof(Rdat)) || (Rchk && !tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return !tc<ixt,Bll>::iof(Ldat) && !tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf = !Lsp && !Rsp, tLpf = !Llp && !Rlp;
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bxors
	@brief A class to represent the logical xor operator (satisfaction).
	@details This class represents the logical xor operator (satisfaction).
*/
template <typename ixt, typename ot> class bxors
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,Bll>::iof(Ldat) != tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bxnors
	@brief A class to represent the logical value xnor operator (satisfaction).
	@details This class represents the logical value xnor operator (satisfaction).
*/
template <typename ixt, typename ot> class bxnors
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,Bll>::iof(Ldat) == tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bimplys
	@brief A class to represent the logical imply operator (satisfaction).
	@details This class represents the logical imply operator (satisfaction).
*/
template <typename ixt, typename ot> class bimplys
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && !tc<ixt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return !tc<ixt,Bll>::iof(Ldat) || tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bnimplys
	@brief A class to represent the logical not imply operator (satisfaction).
	@details This class represents the logical not imply operator (satisfaction).
*/
template <typename ixt, typename ot> class bnimplys
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && !tc<ixt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,Bll>::iof(Ldat) && !tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bandu
	@brief A class to represent the numerical and operator (unsatisfaction).
	@details This class represents the numerical and operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bandu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && tc<ixt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return !tc<ixt,Bll>::iof(Ldat) + !tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return 2; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return 0; }
};



/*!
	@class bnandu
	@brief A class to represent the numerical nand operator (unsatisfaction).
	@details This class represents the numerical nand operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bnandu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && tc<ixt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,Bll>::iof(Ldat) && tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class boru
	@brief A class to represent the numerical or operator (unsatisfaction).
	@details This class represents the numerical or operator (unsatisfaction).
*/
template <typename ixt, typename ot> class boru
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && !tc<ixt,Bll>::iof(Rdat)) || (Rchk && !tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return !tc<ixt,Bll>::iof(Ldat) && !tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bnoru
	@brief A class to represent the numerical nor operator (unsatisfaction).
	@details This class represents the numerical nor operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bnoru
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && !tc<ixt,Bll>::iof(Rdat)) || (Rchk && !tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,Bll>::iof(Ldat) + tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return 2; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return 0; }
};



/*!
	@class bxoru
	@brief A class to represent the numerical xor operator (unsatisfaction).
	@details This class represents the numerical xor operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bxoru
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,Bll>::iof(Ldat) == tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bxnoru
	@brief A class to represent the numerical value xnor operator (unsatisfaction).
	@details This class represents the numerical value xnor operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bxnoru
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,Bll>::iof(Ldat) != tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bimplyu
	@brief A class to represent the numerical imply operator (unsatisfaction).
	@details This class represents the numerical imply operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bimplyu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && !tc<ixt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,Bll>::iof(Ldat) && !tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bnimplyu
	@brief A class to represent the numerical not imply operator (unsatisfaction).
	@details This class represents the numerical not imply operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bnimplyu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && !tc<ixt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return !tc<ixt,Bll>::iof(Ldat) + tc<ixt,Bll>::iof(Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return 2; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return 0; }
};



closeKangarooSpace



#endif//BlogicTccIncluded
