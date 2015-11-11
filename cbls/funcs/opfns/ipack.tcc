/*!
	@file ipack.tcc
	@brief The source file for integer packing operator templates.
	@details This is the source file for integer packing operator templates templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef IpackTccIncluded
#define IpackTccIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace



/*!
	@class ipack2
	@brief A class to represent the two dimensional integer packing operator.
	@details This class represents the two dimensional integer packing operator.
*/
template <typename ixt, typename ot> class ipack2
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 2;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, Bll const Qchk,
				ixt const & Pdat, ixt const & Qdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat, ixt const & Qdat)
			{
				#if DiscSize == SmallSize
					Warn(Pdat & ~0xFF, eOutOfRange);
					Warn(Qdat & ~0xFF, eOutOfRange);
					return ((Pdat << 8) | Qdat);
				#elif DiscSize == NormalSize
					Warn(Pdat & ~0xFFFF, eOutOfRange);
					Warn(Qdat & ~0xFFFF, eOutOfRange);
					return ((Pdat << 16) | Qdat);
				#elif DiscSize == LargeSize
					Warn(Pdat & ~0xFFFFFFFF, eOutOfRange);
					Warn(Qdat & ~0xFFFFFFFF, eOutOfRange);
					return ((Pdat << 32) | Qdat);
				#else
					#error Undefined discrete data size specified.
				#endif
			}
};




/*!
	@class ipack3
	@brief A class to represent the three dimensional integer packing operator.
	@details This class represents the three dimensional integer packing operator.
*/
template <typename ixt, typename ot> class ipack3
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Pchk, Bll const Qchk, Bll const Rchk,
				ixt const & Pdat, ixt const & Qdat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Pdat, ixt const & Qdat, ixt const & Rdat)
			{
				#if DiscSize == SmallSize
					Warn(Pdat & ~0x1F, eOutOfRange);
					Warn(Qdat & ~0x1F, eOutOfRange);
					Warn(Rdat & ~0x1F, eOutOfRange);
					return ((((Pdat << 5) + Qdat) << 5) + Rdat);
				#elif DiscSize == NormalSize
					Warn(Pdat & ~0x3FF, eOutOfRange);
					Warn(Qdat & ~0x3FF, eOutOfRange);
					Warn(Rdat & ~0x3FF, eOutOfRange);
					return ((((Pdat << 10) + Qdat) << 10) + Rdat);
				#elif DiscSize == LargeSize
					Warn(Pdat & ~0xFFFFF, eOutOfRange);
					Warn(Qdat & ~0xFFFFF, eOutOfRange);
					Warn(Rdat & ~0xFFFFF, eOutOfRange);
					return ((((Pdat << 20) + Qdat) << 20) + Rdat);
				#else
					#error Undefined discrete data size specified.
				#endif
			}
};



closeKangarooSpace



#endif//IpackTccIncluded
