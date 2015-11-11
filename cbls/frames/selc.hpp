/*!
	@file selc.hpp
	@brief The prototype file for Selc class.
	@details This is the prototype file for Selc class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 03.01.2010 QRL NICTA www.nicta.com.au
	@see selc.cpp
*/



#ifndef SelcHppIncluded
#define SelcHppIncluded


#include "cbls/frames/dat.hpp"
#include "cbls/frames/reg.hh"
#include "cbls/frames/prm.hpp"
#include "cbls/frames/wrp.hpp"


openKangarooSpace



/*
	Forward declarations.
*/
class Sys;
class Term;
class Prm;
class Func;
class Var;
class Tabu;



/*!
	@class Selc
	@brief A class to represent selectors.
	@details This class represents selectors.
*/
class Selc
{
	public:

		static Selc & refm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Reference
		static Selc * ptrm(Hdl const hdlSys, Hdl const hdlSelc);		//!< Pointer.
		static Selc const & refc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Reference
		static Selc const * ptrc(Hdl const hdlSys, Hdl const hdlSelc);	//!< Pointer.

		static Bll selectExecuteSelc1(Hdl const hdlSys,
									Hdl const hdlSelc,
									Rnd & theRnd);			//!< Select and execute and return whether successful.
		static Bll selectExecuteSelc2(Hdl const hdlSys,
									Hdl const hdlSelc1,
									Hdl const hdlSelc2,
									Rnd & theRnd);			//!< Select and execute and return whether successful.
		static Bll selectExecuteSelcs(Hdl const hdlSys,
									Hdl const * hdlSelcs,
									Dim const SelcCount,
									Rnd & theRnd);			//!< Select and execute and return whether successful.

		Bll performSelection(Rnd & theRnd);			//!< Perform selection.
		void executeSelection();					//!< Execute selection.

		#if CompLazyHalf
		//! @name Activation
		//! @{

		Bll active() const;							//!< Get whether active.
		void activate(Bll const SetNotUnset);		//!< Activate the selector.

		//! @}
		#endif // CompLazyHalf

		//! @name Selections
		//! @{

		void setSelcVar1(Hdl const hdlVar);							//!< Set selected variable.
		void setSelcVar2(Hdl const hdlVar1, Hdl const hdlVar2);		//!< Set selected variables.
		void setSelcVars(Hdl const * hdlVars, Dim const VarCount);	//!< Set selected variables.

		void setSelcVal1(Wrp const & theWrp);						//!< Set selected value.
		void setSelcVal2(Wrp const & theWrp1, Wrp const & theWrp2);	//!< Set selected values.
		void setSelcVals(Wrp const * theWrps, Dim const ValCount);	//!< Set selected values..

		void copySelcVarsVals(Selc const * srcSelc);//!< Copy selected variables and values from the source.
		void copySelcVarsVals(Selc const & srcSelc);//!< Copy selected variables and values from the source.

		void copySelcVars(Selc const * srcSelc);	//!< Copy selected variables from the source.
		void copySelcVars(Selc const & srcSelc);	//!< Copy selected variables from the source.

		void copySelcVals(Selc const * srcSelc);	//!< Copy selected values from the source.
		void copySelcVals(Selc const & srcSelc);	//!< Copy selected values from the source.

		b1<Hdl, xmm> const & SelcVars() const;		//!< The selected variables.
		b1<Wrp, xmm> const & SelcVals() const;		//!< The selected values.

		//! @}

	public:

		Cls const SelcCls;		//!< Selector class.
		Cat const SelcCat;		//!< Selector category.
		Typ const SelcTyp;		//!< Selector type.
		Hdl const SelcHdl;		//!< Selector handle.
		Fss const SelcFss;		//!< Selector specification.
		Hvl const SelcHvl;		//!< Hash value.

		Bll const ExecReady;	//!< Ready for execution?
		Bll const HoldValue;	//!< Contain values?

	protected:

		friend class Sys;		// Accesses only setSelcHdl

		virtual ~Selc();								//!< Destructor.
		Selc(Selc const & that);						//!< Duplicator.
		Selc(Hdl const hdlSys, Dim const PrmCount);		//!< Constructor.
		Selc const & operator = (Selc const & that);	//!< Assigner.

		virtual Bll select(Rnd & theRnd) = 0;			//!< Run the selector, return whether successful.
		virtual void execute() = 0;						//!< Execute the selection made by the selector.
		#if CompLazyHalf
		virtual void require(Bll const SetNotUnset) = 0;//!< Set requirement as per activation.
		#endif // CompLazyHalf

		//! @name Properties
		//! @{

		void setSelcCls(Cls const theSelcCls);		//!< Set selc class.
		void setSelcCat(Cat const theSelcCat);		//!< Set selc category.
		void setSelcTyp(Typ const theSelcTyp);		//!< Set selc type.
		void setSelcHdl(Hdl const theSelcHdl);		//!< Set selc handle.
		void setSelcHvl(Hvl const theSelcHvl);		//!< Set hash value.

		void setExecReady(Bll const SetNotUnset);	//!< Set ready for exec.
		void setHoldValue(Bll const SetNotUnset);	//!< Set whether holds values.

		//! @}

		//! @name Identity
		//! @{

		virtual Bll equate(Selc const & that) const;	//!< Compare selcs for equality.
		Hvl calcSelcHvl() const;						//!< Calculate hash value.

		//! @}

		Hdl defSysSelc();								//!< Define the selector.
		void setParams(Fss const theFss,
			Prm * const thePrms, Dim const PrmCount);	//!< Set the parameters.

	protected:

		Sys & 					mSelcSys;				//!< Selc sys.

		b1<Hdl, xmm>  			mSelcVars;				//!< Selc variables.
		b1<Wrp, xmm>			mSelcVals;				//!< Selc values.

		b1<Term *, kmm> const 	mPrmTerms;				//!< The parameter terms.
		b1<Pss, kmm> const 		mPrmSpecs;				//!< The parameter specs.

		#if CompLazyHalf
		Dim 	 	mActive;							//!< Whether active?
		#endif // CompLazyHalf
};




/*!
	The destructor.
*/
inline Selc::~Selc()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	Return selected variables.
*/
inline b1<Hdl, xmm> const & Selc::SelcVars() const
{
	WatchError
	return mSelcVars;
	CatchError
}


/*!
	Return selected values.
*/
inline b1<Wrp, xmm> const & Selc::SelcVals() const
{
	WatchError
	return mSelcVals;
	CatchError
}


#if CompLazyHalf
/*!
	Return whether the select is active.
*/
inline Bll Selc::active() const
{
	WatchError
	return mActive;
	CatchError
}
#endif // CompLazyHalf




closeKangarooSpace



#endif // SelcHppIncluded
