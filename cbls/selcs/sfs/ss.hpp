/*!
	@file ss.hpp
	@brief The header file for Ss template class.
	@details This is the header file for Ss template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
*/



#ifndef SsHppIncluded
#define SsHppIncluded



#include "cbls/frames/idx.hh"
#include "cbls/dbases/idx.hpp"
#include "cbls/selcs/reg.hh"
#include "cbls/selcs/sf.hpp"


openKangarooSpace



/*!
	@class Ss
	@brief A template class to represent swap full selcs.
	@details This template class represents swap full selcs.
*/
class Ss : public Sf
{
	protected:

		~Ss();										//!< Destructor.
		Ss(Hdl const hdlSys, Dim const PrmCount);	//!< Constructor.
		Ss(Ss const & that);						//!< Duplicator.
		Ss const & operator = (Ss const & that);	//!< Assigner.

		virtual void execute();						//!< Execute selection.
};



closeKangarooSpace


#endif	//SsTccIncluded
