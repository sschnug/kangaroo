/*!
	@file navops.tcc
	@brief The source file for template navigational operators.
	@details This is the source file for template navigational operators.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef NavopsTccIncluded
#define NavopsTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace


/*!
	@class flipa
	@brief A class to represent the flip-assign operator.
	@details This class represents the flip-assign operator.
*/
template <typename dt>
class flipa
{
	public:
		typedef dt DatTyp;	//!< @brief Data type. @details Represents data type.

		/*! @brief Operation. @details Perform operation. */
		static void iof(dt & Data)
		{
			WatchError
			Data = -Data;
			CatchError
		}
};




/*!
	@class flipa
	@brief A class to represent the flip-assign operator.
	@details This class represents the flip-assign operator.
*/
template <>
class flipa<B>
{
	public:
		typedef B DatTyp;	//!< @brief Data type. @details Represents data type.

		/*! @brief Operation. @details Perform operation. */
		static void iof(B & Data)
		{
			WatchError
			Data = !Data;
			CatchError
		}
};




/*!
	@class flipc
	@brief A class to represent the flip-cast operator.
	@details This class represents the flip-cast operator.
*/
template <typename it, typename ot>
class flipc
{
	public:
		typedef it InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(it const & Data)
		{
			WatchError
			return -Data;
			CatchError
		}
};



/*!
	@class flipc
	@brief A class to represent the flip-cast operator.
	@details This class represents the flip-cast operator.
*/
template <typename ot>
class flipc<B,ot>
{
	public:
		typedef B InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(B const & Data)
		{
			WatchError
			return !Data;
			CatchError
		}
};



/*!
	@class nexta
	@brief A class to represent the next-assign operator.
	@details This class represents the next-assign operator.
*/
template <typename dt>
class nexta
{
	public:
		typedef dt DatTyp;	//!< @brief Data type. @details Represents data type.

		/*! @brief Operation. @details Perform operation. */
		static void iof(dt & Left, dt const & Right)
		{
			WatchError
			Warn(Right <= 0, eNavigationStep);
			Left += Right;
			CatchError
		}
};



/*!
	@class preva
	@brief A class to represent the previous-assign operator.
	@details This class represents the previous-assign operator.
*/
template <typename dt>
class preva
{
	public:
		typedef dt DatTyp;	//!< @brief Data type. @details Represents data type.

		/*! @brief Operation. @details Perform operation. */
		static void iof(dt & Left, dt const & Right)
		{
			WatchError
			Warn(Right <= 0, eNavigationStep);
			Left -= Right;
			CatchError
		}
};



/*!
	@class nextc
	@brief A class to represent the next-cast operator.
	@details This class represents the next-cast operator.
*/
template <typename it, typename ot>
class nextc
{
	public:
		typedef it InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(it const & Left, it const & Right)
		{
			WatchError
			Warn(Right <= 0, eNavigationStep);
			return Left + Right;
			CatchError
		}
};



/*!
	@class prevc
	@brief A class to represent the previous-cast operator.
	@details This class represents the previous-cast operator.
*/
template <typename it, typename ot>
class prevc
{
	public:
		typedef it InTyp;	//!< @brief Input type. @details Represents input type.
		typedef ot OutTyp;	//!< @brief Output type. @details Represents output type.

		/*! @brief Operation. @details Perform operation. */
		static ot iof(it const & Left, it const & Right)
		{
			WatchError
			Warn(Right <= 0, eNavigationStep);
			return Left - Right;
			CatchError
		}
};


closeEmuSpace



#endif // NavopsTccIncluded
