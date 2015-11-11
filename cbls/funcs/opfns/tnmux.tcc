/*!
	@file tnmux.tcc
	@brief The source file for 3/n-ary multiplexer templates.
	@details This is the source file for ternary multiplexer templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef TnmuxTccIncluded
#define TnmuxTccIncluded



#include "cbls/frames/idx.hh"



openKangarooSpace



/*!
	@class tif
	@brief A class to represent the ternary conditional operator.
	@details This class represents the ternary conditional operator.
*/
template <typename ixt, typename iyt, typename ot> class tif
{
	public:
		typedef ixt InxTyp;					//!< @brief Inx type. @details Input type.
		typedef iyt InyTyp; 				//!< @brief Iny type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 3;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Cchk, Bll const Tchk, Bll const Echk,
				ixt const & Cdat, iyt const & Tdat, iyt const & Edat)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Cdat, iyt const & Tdat, iyt const & Edat)
			{ return tc<ixt,Bll>::iof(Cdat) ? tc<iyt,ot>::iof(Tdat) : tc<iyt,ot>::iof(Edat); }
};



/*!
	@class nil
	@brief A class to represent the n-ary indexed list element operator.
	@details This class represents the n-ary indexed list element operator.
*/
template <typename ixt, typename iyt, typename ot> class nil
{
	public:
		typedef ixt InxTyp;					//!< @brief Inx type. @details Input type.
		typedef iyt InyTyp; 				//!< @brief Iny type. @details Input type.
		typedef ot OutTyp; 					//!< @brief Out type. @details Output type.

		static Dim const Arity = 0;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Cchk, ixt const & Cdat, Bll const * Echks,
					iyt const * Edats, Dim const Size)
			{ return true; IncompleteCode }

		/*! @brief Operation. @details Perform operation. */
		static ot iof(ixt const & Cdat, iyt const * Edats, Dim const Size)
		{
			return tc<iyt,ot>::iof(Edats[scast<Dim>(Cdat) >= Size ? 0 : Cdat]);
		}
};



/*!
	@class lpfl
	@brief A class to represent the linear piece-wise function with linear search.
	@details This class represents the linear piece-wise function with linear search.
*/
template <typename ixt, typename iyt, typename izt, typename ikt, typename ot> class lpfl
{
	public:
		typedef ixt InxTyp;					//!< @brief Inx type. @details Input type.
		typedef iyt InyTyp; 				//!< @brief Iny type. @details Input type.
		typedef izt InzTyp; 				//!< @brief Inz type. @details Input type.
		typedef ikt InkTyp; 				//!< @brief Ink type. @details Input type.
		typedef  ot OutTyp; 				//!< @brief Out type. @details Output type.

		typedef typename DataBuff<ixt,iyt>::Type        ProdTyp;
		typedef typename DataBuff<ProdTyp,izt>::Type    FinalTyp;

		static Dim const Arity = 0;			//!< Arity
		static Pso const Order = Ordered;	//!< Order.

		/*! @brief Check. @details Check operation required? */
		static Bll chk(Bll const Xchk, ixt const & Xdat, Bll const * Xchks, ixt const * Xdats,
					Bll const * Ychks, iyt const * Ydats, Bll const * Zchks, izt const * Zdats,
					Dim const IntervalCount)
			{ return true; IncompleteCode }

		/*! @brief Operation.
			@details Calculate the following function
				if Xdat < Xdats[0] then return dfltLeft
				for all i 0..IntervalCount -1 ::
					if Xdat is in [ Xdats[i], Xdats[i+1] )
						then return Xdat * Ydats[i] + Zdats[i]
				if ( Xdat >= Xdats[IntervalCount-1] ) then return dfltRight
		*/
		static ot iof(ixt const & Xdat, ixt const * Xdats, iyt const * Ydats, izt const * Zdats,
					Dim const IntervalCount, ikt const dfltLeft, ikt const dfltRight)
		{
			Warn(IntervalCount < 1, eParamCount2(1, MaxDim));
			// Xdats size == IntervalCount + 1
			// Ydats size == IntervalCount
			// Zdats size == IntervalCount

			if ( Xdat < Xdats[0] ) return tc<ikt,ot>::iof(dfltLeft);
			Idx tIdx = 1;
			for ( ; (tIdx <= IntervalCount) && (Xdat >= Xdats[tIdx]); ++tIdx );
			if ( tIdx > IntervalCount ) return tc<ikt,ot>::iof(dfltRight);

			--tIdx;
			return tc<FinalTyp,ot>::iof(Xdat * Ydats[tIdx] + Zdats[tIdx]);
		}
};



closeKangarooSpace



#endif//TnmuxTccIncluded
