/*!
	@file hint.hpp
	@brief The prototype file for Hint class.
	@details This is the prototype file for Hint class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 23.1.2009 QRL NICTA www.nicta.com.au
	@see hint.cpp
*/



#ifndef HintHppIncluded
#define HintHppIncluded



#include "cbls/frames/dat.hpp"
#include "cbls/frames/pbs.tcc"



openKangarooSpace


/*
	Forward declaration.
*/
class Sys;



/*!
	@class Hint
	@brief A class to represent hint dbfs.
	@details This class represents hint dbfs.
*/
class Hint
{
	public:

		Srl const TypeSrl;			//!< Data type serial

		//! @name Accesss
		//! @{

		static Hint & refm(Hdl const hdlSys, Srl const srlType);		//!< Reference.
		static Hint * ptrm(Hdl const hdlSys, Srl const srlType);		//!< Pointer.
		static Hint const & refc(Hdl const hdlSys, Srl const srlType);	//!< Reference.
		static Hint const * ptrc(Hdl const hdlSys, Srl const srlType);	//!< Pointer.

		//! @}

	protected:

		friend class Sys;
		friend class pbs<Hint>;

		virtual ~Hint();								//!< Destructor.
		Hint(Hint const & that);						//!< Duplicator.
		Hint(Hdl const hdlSys, Srl const srlType);		//!< Constructor.
		Hint const & operator = (Hint const & that);	//!< Assigner.

		Bll defSysHint();								//!< Install in the sys.
		virtual void syncExecClk() = 0;					//!< Synchronise.
		virtual void adjustMemAuto() = 0;				//!< Adjust memory.

	protected:

		Sys & mHintSys;									//!< The sys.
};



closeKangarooSpace



#endif // HintHppIncluded

