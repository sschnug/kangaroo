/*!
	@file sd.hpp
	@brief The source file for Sd template class.
	@details This is the source file for Sd template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SdHppIncluded
#define SdHppIncluded



#include "cbls/selcs/sf.hpp"


openKangarooSpace



/*!
	@class Sd
	@brief A template class to represent differential full selcs.
	@details This template class represents differential full selcs.
*/
class Sd : public Sf
{
	protected:

		~Sd();										//!< Destructor.
		Sd(Hdl const hdlSys, Dim const PrmCount);	//!< Constructor.
		Sd(Sd const & that);						//!< Duplicator.
		Sd const & operator = (Sd const & that);	//!< Assigner.

		virtual void execute();						//!< Execute selection.
};



closeKangarooSpace


#endif	//SdTccIncluded
