/*!
	@file brelatn.tcc
	@brief The source file for binary relational operator templates.
	@details This is the source file for binary relational operator templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef BrelatnTccIncluded
#define BrelatnTccIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace



/*!
	@class beqs
	@brief A class to represent the logical equal operator (satisfaction).
	@details This class represents the logical equal operator (satisfaction).
*/
template <typename ixt, typename ot> class beqs
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
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return eq<ixt,Bll>::iof(Ldat, Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bnes
	@brief A class to represent the logical not-equal operator (satisfaction).
	@details This class represents the logical not-equal operator (satisfaction).
*/
template <typename ixt, typename ot> class bnes
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
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return ne<ixt,Bll>::iof(Ldat, Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class blts
	@brief A class to represent the logical less-than operator (satisfaction).
	@details This class represents the logical less-than operator (satisfaction).
*/
template <typename ixt, typename ot> class blts
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return Ldat < Rdat; }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bnlts
	@brief A class to represent the logical not-less-than operator (satisfaction).
	@details This class represents the logical not-less-than operator (satisfaction).
*/
template <typename ixt, typename ot> class bnlts
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return Ldat >= Rdat; }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};




/*!
	@class bgts
	@brief A class to represent the logical greater-than operator (satisfaction).
	@details This class represents the logical greater-than operator (satisfaction).
*/
template <typename ixt, typename ot> class bgts
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return Ldat > Rdat; }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bngts
	@brief A class to represent the logical not-greater-than operator (satisfaction).
	@details This class represents the logical not-greater-than operator (satisfaction).
*/
template <typename ixt, typename ot> class bngts
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return Ldat <= Rdat; }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};




/*!
	@class bles
	@brief A class to represent the logical less-equal operator (satisfaction).
	@details This class represents the logical less-equal operator (satisfaction).
*/
template <typename ixt, typename ot> class bles
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return Ldat <= Rdat; }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bnles
	@brief A class to represent the logical not-less-equal operator (satisfaction).
	@details This class represents the logical not-less-equal operator (satisfaction).
*/
template <typename ixt, typename ot> class bnles
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return Ldat > Rdat; }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};




/*!
	@class bges
	@brief A class to represent the logical greater-equal operator (satisfaction).
	@details This class represents the logical greater-equal operator (satisfaction).
*/
template <typename ixt, typename ot> class bges
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return Ldat >= Rdat; }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bnges
	@brief A class to represent the logical not-greater-equal operator (satisfaction).
	@details This class represents the logical not-greater-equal operator (satisfaction).
*/
template <typename ixt, typename ot> class bnges
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return Ldat < Rdat; }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bequ
	@brief A class to represent the mumerical equal operator (unsatisfaction).
	@details This class represents the mumerical equal operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bequ
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
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(abs(Ldat - Rdat)); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bneu
	@brief A class to represent the mumerical not-equal operator (unsatisfaction).
	@details This class represents the mumerical not-equal operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bneu
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
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return eq<ixt,Bll>::iof(Ldat, Rdat); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return true; }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return false; }
};



/*!
	@class bltu
	@brief A class to represent the mumerical less-than operator (unsatisfaction).
	@details This class represents the mumerical less-than operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bltu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(max(scast<typename DataStub<ixt>::TempBuff>(Ldat - Rdat + 1),
						scast<typename DataStub<ixt>::TempBuff>(0))); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Llp - Rsp + 1),
//						scast<typename DataStub<ixt>::TempBuff>(0)); }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Lsp - Rlp + 1),
//						scast<typename DataStub<ixt>::TempBuff>(0));  }
};



/*!
	@class bnltu
	@brief A class to represent the mumerical not-less-than operator (unsatisfaction).
	@details This class represents the mumerical not-less-than operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bnltu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(max(scast<typename DataStub<ixt>::TempBuff>(Rdat - Ldat),
					scast<typename DataStub<ixt>::TempBuff>(0))); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Llp - Rsp + 1),
//					scast<typename DataStub<ixt>::TempBuff>(0)); }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Lsp - Rlp + 1),
//					scast<typename DataStub<ixt>::TempBuff>(0));  }
};




/*!
	@class bgtu
	@brief A class to represent the mumerical greater-than operator (unsatisfaction).
	@details This class represents the mumerical greater-than operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bgtu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(max(scast<typename DataStub<ixt>::TempBuff>(Rdat - Ldat + 1),
						scast<typename DataStub<ixt>::TempBuff>(0))); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Rlp - Lsp + 1),
//						scast<typename DataStub<ixt>::TempBuff>(0)); }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Rsp - Llp + 1),
//						scast<typename DataStub<ixt>::TempBuff>(0));  }
};



/*!
	@class bngtu
	@brief A class to represent the mumerical not-greater-than operator (unsatisfaction).
	@details This class represents the mumerical not-greater-than operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bngtu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(max(scast<typename DataStub<ixt>::TempBuff>(Ldat - Rdat),
					scast<typename DataStub<ixt>::TempBuff>(0))); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Rlp - Lsp + 1),
//					scast<typename DataStub<ixt>::TempBuff>(0)); }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Rsp - Llp + 1),
//					scast<typename DataStub<ixt>::TempBuff>(0));  }
};



/*!
	@class bleu
	@brief A class to represent the mumerical less-equal operator (unsatisfaction).
	@details This class represents the mumerical less-equal operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bleu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(max(scast<typename DataStub<ixt>::TempBuff>(Ldat - Rdat),
					scast<typename DataStub<ixt>::TempBuff>(0))); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Llp - Rsp),
//					scast<typename DataStub<ixt>::TempBuff>(0)); }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Lsp - Rlp),
//					scast<typename DataStub<ixt>::TempBuff>(0));  }
};



/*!
	@class bnleu
	@brief A class to represent the mumerical not-less-equal operator (unsatisfaction).
	@details This class represents the mumerical not-less-equal operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bnleu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(max(scast<typename DataStub<ixt>::TempBuff>(Rdat - Ldat + 1),
						scast<typename DataStub<ixt>::TempBuff>(0))); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Llp - Rsp),
//						scast<typename DataStub<ixt>::TempBuff>(0)); }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Lsp - Rlp),
//						scast<typename DataStub<ixt>::TempBuff>(0));  }
};





/*!
	@class bgeu
	@brief A class to represent the mumerical greater-equal operator (unsatisfaction).
	@details This class represents the mumerical greater-equal operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bgeu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(max(scast<typename DataStub<ixt>::TempBuff>(Rdat - Ldat),
						scast<typename DataStub<ixt>::TempBuff>(0))); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Rlp - Lsp),
//						scast<typename DataStub<ixt>::TempBuff>(0)); }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Rsp - Llp),
//						scast<typename DataStub<ixt>::TempBuff>(0));  }
};



/*!
	@class bngeu
	@brief A class to represent the mumerical not-greater-equal operator (unsatisfaction).
	@details This class represents the mumerical not-greater-equal operator (unsatisfaction).
*/
template <typename ixt, typename ot> class bngeu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Lchk, Bll const Rchk, ixt const & Ldat, ixt const & Rdat)
			{ return (&Ldat != &Rdat) && (Lchk || Rchk); }

		/*! @brief Operation. @details Perform operation. */
		static ot const iof(ixt const & Ldat, ixt const & Rdat)
			{ return tc<ixt,ot>::iof(max(Ldat - Rdat + 1,  scast<typename DataStub<ixt>::TempBuff>(0))); }

//		/*! @brief Largest possible. @details Compute largest possible. */
//		static ot lpf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Rlp - Lsp),
//					scast<typename DataStub<ixt>::TempBuff>(0)); }
//
//		/*! @brief Smallest possible. @details Compute smallest possible. */
//		static ot spf(ixt const & Lsp, ixt const & Rsp, ixt const & Llp, ixt const & Rlp)
//			{ return max(scast<typename DataStub<ixt>::TempBuff>(Rsp - Llp),
//					scast<typename DataStub<ixt>::TempBuff>(0));  }
};




closeKangarooSpace



#endif//BrelatnTccIncluded
