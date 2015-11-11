/*!
	@file tcops.tcc
	@brief The source file for template type casting operators.
	@details This is the source file for template type casting operators.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef TcopsTccIncluded
#define TcopsTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace




/*!
	@class tc
	@brief A class to represent the type cast operator.
	@details This class represents the type cast operator.
*/
template <typename it, typename ot>
class tc
{
	public:
		typedef it InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(it const & Idat)
		{
			WatchError
			return Idat;
			CatchError
		}

//		/*! @brief Perform bound casting @details Perform casting of the bounds. */
//		static void slf(it const & iSp, it const & iLp, ot & oSp, ot & oLp)
//			{
//				Warn(iSp > iLp, eInvalidRange);
//				oSp = iSp, oLp = iLp;
//				Warn(oSp > oLp, eInvalidRange);
//			}
};


#if FloatEquality
/*!
	@class tc
	@brief A class to represent the cast operator.
	@details This class represents the cast operator.
*/
template <>
class tc<R,B>
{
	public:
		typedef R InTyp;	//!< @brief Input type. @details Represents input type.
		typedef B OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static B iof(R const & Idat)
		{
			WatchError
			Z zIdat = *(Z*)&Idat;
			if (zIdat < 0) zIdat = MinZ - zIdat;
			union { Z zZero; R rZero;};
			rZero = 0.0;
			if (zZero < 0) zZero = MinZ - zZero;
			return (abs(zIdat - zZero) > GapR);
			CatchError
		}

//		/*! @brief Perform bound casting @details Perform casting of the bounds. */
//		static void slf(R const & iSp, R const & iLp, B & oSp, B & oLp)
//			{
//				Warn(iSp > iLp, eInvalidRange);
//				oSp = iSp > 0 || iLp < 0; oLp = iof(iSp) || iof(iLp);
//				Warn(oSp > oLp, eInvalidRange);
//			}
};
#endif // FloatEquality


closeEmuSpace



#endif // TcopsTccIncluded
