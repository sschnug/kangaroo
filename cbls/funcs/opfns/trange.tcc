/*!
	@file trange.tcc
	@brief The source file for ternary range operator templates.
	@details This is the source file for ternary range operator templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef TrangeTccIncluded
#define TrangeTccIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace



/*!
	@class tbccs
	@brief A class to represent the ternary between closed closed operator (satisfaction).
	@details This class represents the ternary between closed closed operator (satisfaction).
*/
template <typename ixt, typename ot> class tbccs
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return Ldat <= Mdat && Mdat <= Rdat; }
};



/*!
	@class tboos
	@brief A class to represent the ternary between open open operator (satisfaction).
	@details This class represents the ternary between open open operator (satisfaction).
*/
template <typename ixt, typename ot> class tboos
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return Ldat < Mdat && Mdat < Rdat; }
};



/*!
	@class tbcos
	@brief A class to represent the ternary between closed open operator (satisfaction).
	@details This class represents the ternary between closed open operator (satisfaction).
*/
template <typename ixt, typename ot> class tbcos
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return Ldat <= Mdat && Mdat < Rdat; }
};



/*!
	@class tbocs
	@brief A class to represent the ternary between open closed operator (satisfaction).
	@details This class represents the ternary between open closed operator (satisfaction).
*/
template <typename ixt, typename ot> class tbocs
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return Ldat < Mdat && Mdat <= Rdat; }
};



/*!
	@class tnbccs
	@brief A class to represent the ternary not between closed closed operator (satisfaction).
	@details This class represents the ternary not between closed closed operator (satisfaction).
*/
template <typename ixt, typename ot> class tnbccs
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return Mdat < Ldat || Rdat < Mdat; }
};



/*!
	@class tnboos
	@brief A class to represent the ternary not between open open operator (satisfaction).
	@details This class represents the ternary not between open open operator (satisfaction).
*/
template <typename ixt, typename ot> class tnboos
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return Mdat <= Ldat || Rdat <= Mdat; }
};



/*!
	@class tnbcos
	@brief A class to represent the ternary not between closed open operator (satisfaction).
	@details This class represents the ternary not between closed open operator (satisfaction).
*/
template <typename ixt, typename ot> class tnbcos
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return Mdat < Ldat || Rdat <= Mdat; }
};



/*!
	@class tnbocs
	@brief A class to represent the ternary not between open closed operator (satisfaction).
	@details This class represents the ternary not between open closed operator (satisfaction).
*/
template <typename ixt, typename ot> class tnbocs
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return Mdat <= Ldat || Rdat < Mdat; }
};



/*!
	@class tbccu
	@brief A class to represent the ternary between closed closed operator (unsatisfaction).
	@details This class represents the ternary between closed closed operator (unsatisfaction).
*/
template <typename ixt, typename ot> class tbccu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
		{
			if (Mdat < Ldat)
				return tc<ixt,ot>::iof(Ldat - Mdat);
			else if (Mdat > Rdat)
				return tc<ixt,ot>::iof(Mdat - Rdat);
			else return 0;
		}
};



/*!
	@class tboou
	@brief A class to represent the ternary between open open operator (unsatisfaction).
	@details This class represents the ternary between open open operator (unsatisfaction).
*/
template <typename ixt, typename ot> class tboou
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
		{
			if (Mdat <= Ldat)
				return tc<ixt,ot>::iof(Ldat - Mdat + 1);
			else if (Mdat >= Rdat)
				return tc<ixt,ot>::iof(Mdat - Rdat + 1);
			else return 0;
		}
};



/*!
	@class tbcou
	@brief A class to represent the ternary between closed open operator (unsatisfaction).
	@details This class represents the ternary between closed open operator (unsatisfaction).
*/
template <typename ixt, typename ot> class tbcou
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
		{
			if (Mdat < Ldat)
				return tc<ixt,ot>::iof(Ldat - Mdat);
			else if (Mdat >= Rdat)
				return tc<ixt,ot>::iof(Mdat - Rdat + 1);
			else return 0;
		}
};



/*!
	@class tbocu
	@brief A class to represent the ternary between open closed operator (unsatisfaction).
	@details This class represents the ternary between open closed operator (unsatisfaction).
*/
template <typename ixt, typename ot> class tbocu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
		{
			if (Mdat <= Ldat)
				return tc<ixt,ot>::iof(Ldat - Mdat + 1);
			else if (Mdat >= Rdat)
				return tc<ixt,ot>::iof(Mdat - Rdat);
			else return 0;
		}
};



/*!
	@class tnbccu
	@brief A class to represent the ternary not between closed closed operator (unsatisfaction).
	@details This class represents the ternary not between closed closed operator (unsatisfaction).
*/
template <typename ixt, typename ot> class tnbccu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
		{
			return tc<ixt,ot>::iof(bmin<ixt,ixt>::iof(
						bmax<ixt,ixt>::iof(Mdat - Ldat + 1, 0),
						bmax<ixt,ixt>::iof(Rdat - Mdat + 1, 0)));
		}
};



/*!
	@class tnboou
	@brief A class to represent the ternary not between open open operator (unsatisfaction).
	@details This class represents the ternary not between open open operator (unsatisfaction).
*/
template <typename ixt, typename ot> class tnboou
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
		{
			return tc<ixt,ot>::iof(bmin<ixt,ixt>::iof(
					bmax<ixt,ixt>::iof(Mdat - Ldat, 0),
					bmax<ixt,ixt>::iof(Rdat - Mdat, 0)));
		}
};



/*!
	@class tnbcou
	@brief A class to represent the ternary not between closed open operator (unsatisfaction).
	@details This class represents the ternary not between closed open operator (unsatisfaction).
*/
template <typename ixt, typename ot> class tnbcou
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
		{
			return tc<ixt,ot>::iof(bmin<ixt,ixt>::iof(
					bmax<ixt,ixt>::iof(Mdat - Ldat + 1, 0),
					bmax<ixt,ixt>::iof(Rdat - Mdat, 0)));
		}
};



/*!
	@class tnbocu
	@brief A class to represent the ternary not between open closed operator (unsatisfaction).
	@details This class represents the ternary not between open closed operator (unsatisfaction).
*/
template <typename ixt, typename ot> class tnbocu
{
	public:
		typedef ixt InxTyp; 				//!< @brief Inx type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Mchk, Bll const Lchk, Bll const Rchk,
				ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Mdat, ixt const & Ldat, ixt const & Rdat)
		{
			return tc<ixt,ot>::iof(bmin<ixt,ixt>::iof(
					bmax<ixt,ixt>::iof(Mdat - Ldat, 0),
					bmax<ixt,ixt>::iof(Rdat - Mdat + 1, 0)));
		}
};


closeKangarooSpace



#endif//TrangeTccIncluded
