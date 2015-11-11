/*!
	@file barith.tcc
	@brief The source file for binary arithmetical operator templates.
	@details This is the source file for binary arithmetical operator templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef BarithTccIncluded
#define BarithTccIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace



/*!
	@class badd
	@brief A class to represent the arithmetical add operator.
	@details This class represents the arithmetical add operator.
*/
template <typename ixt, typename ot> class badd
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(Ldat + Rdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf = Lsp + Rsp, tLpf = Llp + Rlp;
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bhadd
	@brief A class to represent the hybrid arithmetical add operator.
	@details This class represents the hybrid arithmetical add operator.
*/
template <typename ixt, typename iyt, typename ot> class bhadd
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef iyt InyTyp; 				//!< @brief Iny type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, iyt const & Rdat)
			{ return (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, iyt const & Rdat)
			{ return tc<typename DataTemp<ixt,iyt>::Type,ot>::iof(Ldat + Rdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, iyt const & Rsp, ixt const & Llp, iyt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf = Lsp + Rsp, tLpf = Llp + Rlp;
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bmult
	@brief A class to represent the arithmetical mult operator.
	@details This class represents the arithmetical mult operator.
*/
template <typename ixt, typename ot> class bmult
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
			{ return tc<ixt,ot>::iof(Ldat * Rdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf, tLpf, a = Llp * Rlp, b = Lsp * Rsp;
//				if (a < b) tSpf = a, tLpf = b; else tSpf = b, tLpf = a;
//				a = Llp * Rsp; b = Lsp * Rlp;
//				if (a < tSpf) tSpf = a; else if (a > tLpf) tLpf = a;
//				if (b < tSpf) tSpf = b; else if (b > tLpf) tLpf = b;
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bhmult
	@brief A class to represent the hybrid arithmetical mult operator.
	@details This class represents the hybrid arithmetical mult operator.
*/
template <typename ixt, typename iyt, typename ot> class bhmult
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef iyt InyTyp; 				//!< @brief Iny type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, iyt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && tc<iyt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, iyt const & Rdat)
			{ return tc<typename DataTemp<ixt,iyt>::Type,ot>::iof(Ldat * Rdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, iyt const & Rsp, ixt const & Llp, iyt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				typedef typename DataTemp<ixt,iyt>::Type TempType;
//				TempType tSpf, tLpf, a = Llp * Rlp, b = Lsp * Rsp;
//				if (a < b) tSpf = a, tLpf = b; else tSpf = b, tLpf = a;
//				a = Llp * Rsp; b = Lsp * Rlp;
//				if (a < tSpf) tSpf = a; else if (a > tLpf) tLpf = a;
//				if (b < tSpf) tSpf = b; else if (b > tLpf) tLpf = b;
//				auxbsl<TempType,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};




/*!
	@class bmax
	@brief A class to represent the arithmetical max operator.
	@details This class represents the arithmetical max operator.
*/
template <typename ixt, typename ot> class bmax
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(max(Ldat, Rdat)); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf = max(Lsp, Rsp), tLpf = max(Llp,Rlp);
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bmin
	@brief A class to represent the arithmetical min operator.
	@details This class represents the arithmetical min operator.
*/
template <typename ixt, typename ot> class bmin
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(min(Ldat, Rdat)); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf = min(Lsp, Rsp), tLpf = min(Llp,Rlp);
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bdiff
	@brief A class to represent the arithmetical diff operator.
	@details This class represents the arithmetical diff operator.
*/
template <typename ixt, typename ot> class bdiff
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Unordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(abs(Ldat - Rdat)); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf = (Llp < Rsp) ? (Rsp - Llp) : ((Rlp < Lsp) ? Lsp - Rlp : 0);
//				ixt tLpf = max(Llp - Rsp, Rlp - Lsp);
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bsub
	@brief A class to represent the arithmetical sub operator.
	@details This class represents the arithmetical sub operator.
*/
template <typename ixt, typename ot> class bsub
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(Ldat - Rdat); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf = Lsp - Rlp;
//				ixt tLpf = Llp - Rsp;
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};


/*!
	@class bdiv
	@brief A class to represent the arithmetical div operator.
	@details This class represents the arithmetical div operator.
*/
template <typename ixt, typename ot> class bdiv
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && tc<ixt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{
				Achk(!tc<ixt,Bll>::iof(Rdat)) Atxt(eDivisionByZero);
				return tc<ixt,ot>::iof(Ldat / Rdat);
			}

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Alert(!Rlp || !Rsp, eDivisionByZero);
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				ixt tSpf, tLpf, a = Llp / Rlp, b = Lsp / Rsp;
//				if (a < b) tSpf = a, tLpf = b; else tSpf = b, tLpf = a;
//				a = Llp / Rsp; b = Lsp / Rlp;
//				if (a < tSpf) tSpf = a; else if (a > tLpf) tLpf = a;
//				if (b < tSpf) tSpf = b; else if (b > tLpf) tLpf = b;
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bmod
	@brief A class to represent the arithmetical mod operator.
	@details This class represents the arithmetical mod operator.
*/
template <typename ixt, typename ot> class bmod
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && tc<ixt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(calcMod(Ldat, Rdat)); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				Throw(eIncompleteCode);
//				ixt tSpf = 0, tLpf = 0;
////				ixt Rl = max(abs(Rlp), abs(Rsp));
////				Alert(!Rl, eDivisionByZero);
////				if (Llp >= 0)
////				{
////					if (Llp < Rl) return Llp;
////					else if (Llp / Rl > Lsp / Rl) return Rl - 1;
////					else return calcMod(Llp, Rl);
////				}
////				else
////				{
////					if (abs(Lsp) < Rl) return Llp;
////					else if (Llp / Rl > Lsp / Rl) return 0;
////					else return calcMod(Llp, Rl);
////				}
////
////				ixt Rs = min(abs(Rlp), abs(Rsp));
////				Alert(!Rs, eDivisionByZero);
////				if (Lsp >= 0)
////				{
////					if (Llp < Rs) return Lsp;
////					else if (Llp / Rs > Lsp / Rs) return 0;
////					else return calcMod(Lsp, Rs);
////				}
////				else
////				{
////					if (abs(Lsp) < Rs) return Lsp;
////					else if (Llp / Rs > Lsp / Rs) return - Rs + 1;
////					else return calcMod(Lsp, Rs);
////				}
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



/*!
	@class bpow
	@brief A class to represent the arithmetical pow operator.
	@details This class represents the arithmetical pow operator.
*/
template <typename ixt, typename ot> class bpow
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (Lchk && Rchk) || (Lchk && tc<ixt,Bll>::iof(Rdat)) || (Rchk && tc<ixt,Bll>::iof(Ldat)); }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(calcPow(Ldat, Rdat)); }

//		/*! @brief Smallest and largest possible. @details Compute smallest and largest possible. */
//		static void slf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp, ot & Spf, ot & Lpf)
//			{
//				Warn(Lsp > Llp, eInvalidRange);
//				Warn(Rsp > Rlp, eInvalidRange);
//				Throw(eIncompleteCode);
//				ixt tSpf = 0, tLpf = 0;
////				min(min(calcPow(Llp, Rlp), calcPow(Lsp, Rsp)), min(calcPow(Llp, Rsp), calcPow(Lsp, Rlp)));
////				max(max(calcPow(Llp, Rlp), calcPow(Lsp, Rsp)), max(calcPow(Llp, Rsp), calcPow(Lsp, Rlp)));
//				auxbsl<ixt,ot>::cast(tSpf, tLpf, Spf, Lpf);
//			}
};



closeKangarooSpace



#endif//BarithTccIncluded
