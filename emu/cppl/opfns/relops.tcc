/*!
	@file relops.tcc
	@brief The source file for template relational operators.
	@details This is the source file for template relational operators.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef RelopsTccIncluded
#define RelopsTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
 @class eqstr
 @brief A class to represent the equal operator for strings.
 @details This class represents the equal operator for strings.
 */		/* This class is to be finalised latter. */
class eqstr
{
	public:
		/*! @brief Operation. @details Perform operation. */
	static B iof(string const & Left, string const & Right)
		{
			WatchError
			return ( Left.compare(Right) == 0 );
			CatchError
		}
};



/*!
	@class eq
	@brief A class to represent the equal operator.
	@details This class represents the equal operator.
*/
template <typename it, typename ot = B>
class eq
{
	public:
		typedef it InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(it const & Left, it const & Right)
		{
			WatchError
			return Left == Right;
			CatchError
		}
};


#if FloatEquality
/*!
	@class eq
	@brief A class to represent the equal operator.
	@details This class represents the equal operator.
*/
template <typename ot>
class eq<R,ot>
{
	public:
		typedef R InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(R const & Left, R const & Right)
		{
			WatchError
			typedef DimDnz<sizeof(R)>::Stype Ztype;
			Ztype zLeft = *(Ztype*)&Left;
			if (zLeft < 0) zLeft = MinZ - zLeft;
			Ztype zRight = *(Ztype*)&Right;
			if (zRight < 0) zRight = MinZ - zRight;
			return (abs(zLeft - zRight) <= GapR);
			CatchError
		}
};
#endif // FloatEquality



/*!
	@class ne
	@brief A class to represent the not-equal operator.
	@details This class represents the not-equal operator.
*/
template <typename it, typename ot = B>
class ne
{
	public:
		typedef it InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(it const & Left, it const & Right)
		{
			WatchError
			return Left != Right;
			CatchError
		}
};



#if FloatEquality
/*!
	@class ne
	@brief A class to represent the not-equal operator.
	@details This class represents the not-equal operator.
*/
template <typename ot>
class ne<R,ot>
{
	public:
		typedef R InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(R const & Left, R const & Right)
		{
			WatchError
			Z zLeft = *(Z*)&Left;
			if (zLeft < 0) zLeft = MinZ - zLeft;
			Z zRight = *(Z*)&Right;
			if (zRight < 0) zRight = MinZ - zRight;
			return (abs(zLeft - zRight) > GapR);
			CatchError
		}
};
#endif // FloatEquality




/*!
	@class gt
	@brief A class to represent the greater-than operator.
	@details This class represents the greater-than operator.
*/
template <typename it, typename ot = B>
class gt
{
	public:
		typedef it InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(it const & Left, it const & Right)
		{
			WatchError
			return Left > Right;
			CatchError
		}
};



/*!
	@class ge
	@brief A class to represent the greater-equal operator.
	@details This class represents the greater-equal operator.
*/
template <typename it, typename ot = B>
class ge
{
	public:
		typedef it InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(it const & Left, it const & Right)
		{
			WatchError
			return Left >= Right;
			CatchError
		}
};



/*!
	@class lt
	@brief A class to represent the less-than operator.
	@details This class represents the less-than operator.
*/
template <typename it, typename ot = B>
class lt
{
	public:
		typedef it InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(it const & Left, it const & Right)
		{
			WatchError
			return Left < Right;
			CatchError
		}
};



/*!
	@class le
	@brief A class to represent the less-equal operator.
	@details This class represents the less-equal operator.
*/
template <typename it, typename ot = B>
class le
{
	public:
		typedef it InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(it const & Left, it const & Right)
		{
			WatchError
			return Left < Right;
			CatchError
		}
};




/*
http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm

// Usable AlmostEqual function

bool AlmostEqual2sComplement(float A, float B, int maxUlps)
{

    // Make sure maxUlps is non-negative and small enough that the

    // default NAN won't compare as equal to anything.

    assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);

    int aInt = *(int*)&A;

    // Make aInt lexicographically ordered as a twos-complement int

    if (aInt < 0)

        aInt = 0x80000000 - aInt;

    // Make bInt lexicographically ordered as a twos-complement int

    int bInt = *(int*)&B;

    if (bInt < 0)

        bInt = 0x80000000 - bInt;

    int intDiff = abs(aInt - bInt);

    if (intDiff <= maxUlps)

        return true;

    return false;

}
*/

closeEmuSpace



#endif // RelopsTccIncluded
