/*!
	@file eval.hpp
	@brief The prototype file for Eval class.
	@details This is the prototype file for Eval class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 23.1.2009 QRL NICTA www.nicta.com.au
	@see eval.cpp
*/



#ifndef EvalHppIncluded
#define EvalHppIncluded



#include "cbls/frames/dat.hpp"
#include "cbls/frames/pbs.tcc"


openKangarooSpace



/*
	Forward declarations.
*/
class Sys;



/*!
	@class Eval
	@brief A class to represent eval tables.
	@details This class represents eval tables.
*/
class Eval
{
	public:

		Srl const TypeSrl;	//!< Data type serial

		//! @name Accesss
		//! @{

		static Eval & refm(Hdl const hdlSys, Srl const srlType);		//!< Reference.
		static Eval * ptrm(Hdl const hdlSys, Srl const srlType);		//!< Pointer.
		static Eval const & refc(Hdl const hdlSys, Srl const srlType);	//!< Reference.
		static Eval const * ptrc(Hdl const hdlSys, Srl const srlType);	//!< Pointer.

		//! @}

	protected:

		friend class Sys;
		friend class pbs<Eval>;

		virtual ~Eval();								//!< Destructor.
		Eval(Eval const & that);						//!< Duplicator.
		Eval(Hdl const hdlSys, Srl const srlType);		//!< Constructor.
		Eval const & operator = (Eval const & that);	//!< Assigner.

		Bll defSysEval();								//!< Define in the sys.

		virtual void syncExecClk() = 0;		//!< Synchronise execution clock.
		virtual void syncSimulClk() = 0;	//!< Synchronise simulation clock.
		virtual void adjustMemAuto() = 0;	//!< Adjust memory automatically.

	protected:

		Sys & mEvalSys;	//!< The sys.
};



closeKangarooSpace



#endif // EvalHppIncluded

