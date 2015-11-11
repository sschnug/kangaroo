/*!
	@file func.hpp
	@brief The prototype file for Func class.
	@details This is the prototype file for Func class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see func.cpp
*/



#ifndef FuncHppIncluded
#define FuncHppIncluded


#include "cbls/frames/sys.hpp"
#include "cbls/frames/term.hpp"
#include "cbls/frames/prm.hpp"
#include "cbls/frames/arg.hpp"



openKangarooSpace



/*!
	@class Func
	@brief A class to represent functions.
	@details This class represents functions.
*/



class Func : public Term
{
	public:

		static Func & refm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Reference.
		static Func * ptrm(Hdl const hdlSys, Hdl const hdlFunc);		//!< Pointer.
		static Func const & refc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Reference.
		static Func const * ptrc(Hdl const hdlSys, Hdl const hdlFunc);	//!< Pointer.

		//! @name Casting
		//!	@{

		static Func const & cast(Term const & theTerm);	//!< Perform casting.
		static Func const * cast(Term const * theTerm);	//!< Perform casting.
		static Func & cast(Term & theTerm);				//!< Perform casting.
		static Func * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);	//!< Suits casting?
		static Bll suit(Term const * theTerm);	//!< Suits casting?
		static Bll suit(Term & theTerm);		//!< Suits casting?
		static Bll suit(Term * theTerm);		//!< Suits casting?

		//!	@}

	public:

		virtual Bll careLockEffect() const;		//!< Care for lock effect?
		virtual Typ careTabuEffect() const;		//!< Care for tabu effect?
		virtual Bll careFuncVarSqn() const; 	//!< Care func var sqn mapping?

		//! @name Deferment
		//! @{

		#if CompLazyHalf
		Bll required() const;					//!< Whether is required?
		Bll enforced() const;					//!< Whether is enforced?
		Bll defered() const;					//!< Whether is defered?
		void require(Bll const SetNotUnset);	//!< Manipulate requirement.
		#endif // CompLazyHalf
		#if CompLazy
		Bll backlog() const;					//!< Whether has backlog?
		#endif	//CompLazy

		//! @}

	public:

		Fss const FuncFss;					//!< Func spec.
		#if CompUpwd
		Lvl const FuncLvl;					//!< Func level.
		#endif

		b1<Hdl, xmm> const FuncVars;			//!< Func vars.
		rl< b1<Sqn, xmm>, nmm > const PrmVars;	//!< Param vars.

		Sqn findVarSqn(Hdl const hdlVar) const;	//!< Find sqn for a given variable.

	protected:

		friend class Sys;	// Access setParamLink, adjustMemory
		friend class Term;	// Access mExecChgdPrms, mSimulChgdPrms.
		friend class Lock;	// Access computeLockEffect.
		friend class Tabu;	// Access computeTabuEffect.

		~Func();										//!< Destructor.
		Func(Func const & that); 						//!< Duplicator.
		Func(Hdl const hdlSys, Dim const PrmCount);		//!< Constructor.
		Func const & operator = (Func const & that);	//!< Assigner.

		Hdl defSysFunc();					//!< Define the var in the sys.

		void performCompConst();			//!< Computation when not updatable.
		virtual void compConst() = 0;		//!< Computation when not updatable.

		virtual void setupComputation();	//!< Set up for computation.

		virtual void computeTabuEffect();	//!< Compute the tabu effect.
		virtual void computeLockEffect();	//!< Compute the lock effect.

		#if CompUpwd
		//! @name Upward
		//! @{

		#if ExecUpwd
		void clearExecChgdPrms();		//!< Clear the exec changed params.
		#endif
		#if SimulUpwd
		void clearSimulChgdPrms();		//!< Clear the simul changed params.
		#endif

		//! @}
		#endif //CompUpwd

		#if CompLazy
		//! @name Undo Operations
		//! @{

		void performLikelyUndo(Pos const thePos);	//!< Perform likely undo for the parameter.
		void performEvalUndo(Pos const thePos);		//!< Perform eval undo for the parameter.
		void performHintUndo(Pos const thePos);		//!< Perform hint undo for the parameter.

		virtual void undoEval(Pos const thePos) = 0;	//!< Perform eval undo for the parameter.
		virtual void undoHint(Pos const thePos) = 0;	//!< Perform hint undo for the parameter.
		void setEvalUndoDefined(Bll const SetNotUnset);	//!< Set whether eval undo is defined.
		void setHintUndoDefined(Bll const SetNotUnset);	//!< Set whether hint undo is defined.

		//! @}
		#endif	//CompLazy

		//! @name Caching
		//! @{

		#if ExecDnwd
		Bll needExecCandComp();				//!< Need execution cand param computation?
		#endif
		#if SimulDnwdCache
		Bll needSimulCacheComp();			//!< Need simulation cache computation?
		#endif
		#if SimulDnwdFixed
		Bll needSimulFixedComp();			//!< Need simulation fixed param computation?
		#endif
		#if SimulDnwdFlexi
		Bll needSimulFlexiComp();			//!< Need simulation flexi param computation?
		#endif

		//! @}

		//! @name Parameters
		//! @{

		void setParams(Fss const theFss, Prm * const thePrms,
			Dim const PrmCount, Pso const theOrder, Idx * theIdxs = Null);	//!< Set the parameters.
		#if CompDnwd
		void setParamLink(Pos const thePos, Lnk const theLnk);				//!< Set the parameters link.
		#endif//CompDnwd

		//! @}

		//! @name Identity
		//! @{

		Hvl calcTermHvl() const;				 			//!< Calculate term hash value.
		virtual Bll equate(Term const & theTerm) const; 	//!< Compare terms for equality.

		//! @}

		#if CompLazyHalf
		//! @name Requirements
		//! @{

		Lnk ReqFuncLink() const;				//!< The requirement link.
		void setReqFuncLink(Lnk const theLink);	//!< Set the requirement link.

		static void setRequirement(Func * theFunc);		//!< Set requirement for the func.
		static void unsetRequirement(Func * theFunc);	//!< Unset requirement for the func.
		static void setEnforcement(Func * theFunc);		//!< Set the func to be enforced.
		static void unsetEnforcement(Func * theFunc);	//!< Unset the func from enforced.

		//! @}
		#endif // CompLazyHalf

		//! @name Roots
		//! @{

		void defSysRoot();							//!< Define as a root.
		Lnk RootFuncLink() const;					//!< The root link
		void setRootFuncLink(Lnk const theLink);	//!< Set the root link.

		//! @}

		//! @name Memory
		//! @{

		virtual void adjustMemAuto();		//!< Adjust memory requirement automatically.

		//! @}

		//! @name Synchronisation
		//! @{

		virtual void syncExecClk();			//!< Synchronize the execution clock.
		#if ExecDnwd
		virtual void syncExecAsgnClk();		//!< Synchronize the execution assignment clock.
		#endif
		#if SimulDnwd
		virtual void syncSimulAsgnClk();	//!< Synchronize the simulation assignment clock.
		#endif
		#if SimulDnwdCache
		virtual void syncSimulCacheClk();	//!< Synchronize the simulation cache clock.
		#endif

		//! @}

		#if CompDnwd
		//! @name Top-Down
		//! @{

		#if ExecDnwd
		void listCandParams();							//!< List the candidate parameters (block only).
		void markCandParams();							//!< Mark the candidate parameters (list + label).
		#endif//ExecDnwd

		#if SimulDnwdFixed
		void listFixedParams();							//!< List the fixed parameters (block only).
		void markFixedParams();							//!< Mark the fixed parameters (block + label).
		void enumFixedParams(Bll const MarkNotList);	//!< Enumerate the fixed params: mark or list.
		#endif

		#if SimulDnwdFlexi
		void setupFlexiLabels();						//!< Set up flexible parameter labels.
		void listFlexiParams();							//!< List the flexible parameters (block only).
		void markFlexiParams();							//!< Mark the flexible parameters (block + label).
		void enumFlexiParams(Bll const MarkNotList);	//!< Enumerate the flexi params: mark or list.
		#endif

		//! @}
		#endif//CompDnwd

		#if CompLazy
		//! @name Undo Params
		//! @{

		void setupEvalUndoPrms();				//!< Set up parameters for eval undo
		virtual void setupUndoPrms() = 0;		//!< Set up parameters for undo.

		#if CompLazyHalf
		virtual void notifyDeferedPrms() = 0;	//!< Notify deferment to parameters.
		virtual void notifyEnforcedPrms() = 0;	//!< Notify promptness to parameters.
		#endif //CompLazyHalf

		//! @}
		#endif	//CompLazy

	protected:

		b1<Term *, kmm> const 		mPrmTerms;		//!< The parameter terms.
		b1<Pss, kmm> const 			mPrmSpecs;		//!< The parameter specs.

		#if CompDnwd
		b1<Lnk, kmm> const			mPrmLinks;		//!< The link inside the param terms.
		rl< b1<Pos, xmm>, xmm > const mVarUpdtPrms;	//!< Updatable params for the vars.
		#endif//CompDnwd

		#if CompUpwd
			#if UpwdMapFuncVarArray
			b1<Sqn, kmm> const * 	mVarHdlSqns;		//!< Variable serial array mapping.
			#else
			hm<Hdl,Sqn, xmmh> const mVarHdlSqns;		//!< Var serial hash-based mapping.
			#endif
		#endif
		#if CompDnwd
			#if DnwdMapFuncVar == MfvFuncArrayVar
			b1<Sqn, kmm> const * 	mVarHdlSqns;		//!< Variable serial array mapping.
			#elif DnwdMapFuncVar == MfvFuncHashVar
			hm<Hdl,Sqn, xmmh> const mVarHdlSqns;		//!< Var serial hash-based mapping.
			#endif
		#endif

		#if CompLazy
		ll<Pos, kmm>   	    mBacklogPrms;			//!< Parameters that are backlog.
		lf<Pos, kmm>	*	mEvalUndonePrms;		//!< Parameters that are undone.
		#endif // CompLazy

		#if CompLazyHalf
		//! @name Deferment
		//! @{

		Dim 	mRequired;	//!< Requisition count.
		Dim		mEnforced;	//!< Enforcement count.
		Bll		mDefered;	//!< Whether defered?

		//! @}
		#endif	//CompLazyHalf

		//! @name Links
		//! @{

		#if CompLazyHalf
		Lnk		mReqFuncLnk;	//!< Link for required func.
		#endif // CompLazyHalf
		Lnk 	mRootFuncLnk;	//!< Link for root func.

		//! @}

		//! @name Clocks
		//! @{

		#if ExecDnwd
		Clk		mExecAsgnClk;		//!< The execution assignment clock.
		#endif
		#if SimulDnwdFixed
		Clk		mSimulFixedClk;		//!< The simulation assignment clock.
		#endif
		#if SimulDnwdFlexi
		#if FuncFlexiClk
		Clk 	mSimulFlexiClk;		//!< The simulation flexible clock.
		#endif//FuncFlexiClk
		#endif//SimulDnwdFlexi
		#if SimulDnwdCache
		Clk		mSimulCacheClk;		//!< The simulation cache clock.
		#endif

		//! @}

		#if CompDnwd
		//! @name Top-Down
		//! @{

		#if ExecDnwd
		lf<Pos, kmm> mLblCandPrms;				//!< The candidate parameters for execution.
		b1<Pos, xmm> const * mBlkCandPrms;		//!< The candidate parameters for execution.
		#endif//ExecDnwd
		#if SimulDnwdFixed
		lf<Pos, kmm> mLblFixedPrms;				//!< The fixed parameters for simulation
		b1<Pos, xmm> const * mBlkFixedPrms;		//!< The fixed parameters for simulation.
		#endif
		#if SimulDnwdFlexi
		lf<Pos, kmm> * mLblFlexiPrms;			//!< The flexible parameters for simulation.
		b1<Pos, xmm> const * mBlkFlexiPrms;		//!< The flexible parameters for simulation.
		#endif//SimulDnwdFlexi

		//! @}
		#endif //CompDnwd

		#if CompUpwd
		//! @name BottomUp
		//! @{

		#if ExecUpwd
		ll<Pos, kmm> mExecChgdPrms;	//!< The params changed from exec.
		#endif//ExecUpwd
		#if SimulUpwd
		ll<Pos, kmm> mSimulChgdPrms;	//!< The params changed from simul.
		#endif//SimulUpwd

		//! @}
		#endif //CompUpwd

		//! @name Undo
		//! @{

		#if CompLazy
		Bll const mEvalUndoDefined;	//!< Whether undoEval is defined for the function.
		Bll const mHintUndoDefined;	//!< Whether undoHint is defined for the function.
		#endif //CompLazy

		//! @}

	private:

		#if CompDnwd
		static b1<Pos, xmm> const mProxyPrmBlk;		//!< Proxy block for empty parameters.
		#endif

		#if ExecDnwdMultiCand
		b1<Pos, xmm> * mCandMrgBlk;					//!< The candidate parameters for execution.
		#endif

		#if SimulDnwdMultiFixed
		b1<Pos, xmm> * mFixedMrgBlk;				//!< The fixed parameters for simulation.
		#endif
		#if SimulDnwdMultiFlexi
		b1<Pos, xmm> * mFlexiMrgBlk;				//!< The flexible parameters for simulation.
		#endif
};



/*!
	Whether a term is suitable for casting.
*/
inline Bll Func::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermGen == Tf;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll Func::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermGen == Tf;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll Func::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermGen == Tf;
	CatchError
}



/*!
	Whether a term is suitable for casting.
*/
inline Bll Func::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermGen == Tf;
	CatchError
}



/*!
	Perform casting of a term
*/
inline Func const & Func::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermGen != Tf, eTermNotFunction);

	return scast<Func const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term
*/
inline Func const * Func::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermGen != Tf, eTermNotFunction);

	return scast<Func const *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term
*/
inline Func & Func::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermGen != Tf, eTermNotFunction);

	return scast<Func &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term
*/
inline Func * Func::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermGen != Tf, eTermNotFunction);

	return scast<Func *>(theTerm);
	CatchError
}



/*!
	Refer to a function.
*/
inline Func & Func::refm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return Sys::refm(hdlSys).refmFunc(hdlFunc);
	CatchError
}



/*!
	Point to a function.
*/
inline Func * Func::ptrm(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return Sys::ptrm(hdlSys)->ptrmFunc(hdlFunc);
	CatchError
}



/*!
	Refer to a function.
*/
inline Func const & Func::refc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return Sys::refc(hdlSys).refcFunc(hdlFunc);
	CatchError
}



/*!
	Point to a function.
*/
inline Func const * Func::ptrc(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
	return Sys::ptrc(hdlSys)->ptrcFunc(hdlFunc);
	CatchError
}



/*!
	The destructor.
*/
inline Func::~Func()
{
	WatchError
	#if CompUpwd && UpwdMapFuncVarArray
	if (mVarHdlSqns) delete mVarHdlSqns;
	#endif
	#if CompDnwd && DnwdMapFuncVar == MfvFuncArrayVar
	if (mVarHdlSqns) delete mVarHdlSqns;
	#endif
	#if CompLazy
	if (mEvalUndonePrms) delete mEvalUndonePrms;
	#endif // CompLazy

	#if ExecDnwdMultiCand
	if (mCandMrgBlk) delete mCandMrgBlk;
	#endif

	#if SimulDnwdMultiFixed
	if (mFixedMrgBlk) delete mFixedMrgBlk;
	#endif
	#if SimulDnwdMultiFlexi
	if (mFlexiMrgBlk) delete mFlexiMrgBlk;
	#endif
	#if SimulDnwdFlexi
	if (mLblFlexiPrms) delete mLblFlexiPrms;
	#endif
	CatchError
}



/*!
	Define a function in the sys.
*/
inline Hdl Func::defSysFunc()
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	return mTermSys.defFunc(this);
	CatchError
}



#if CompLazyHalf
/*!
	Return whether enforced?
*/
inline Bll Func::enforced() const
{
	WatchError
	return mEnforced;
	CatchError
}
#endif	//CompLazyHalf




#if CompLazyHalf
/*!
	Return whether defered?
*/
inline Bll Func::defered() const
{
	WatchError
	return mDefered;
	CatchError
}
#endif	//CompLazyHalf



#if CompLazyHalf
/*!
	Return whether required?
*/
inline Bll Func::required() const
{
	WatchError
	return mRequired;
	CatchError
}
#endif	//CompLazyHalf



#if CompLazyHalf
/*!
	Manipulate requirement.
*/
inline void Func::require(Bll const SetNotUnset)
{
	WatchError
	Warn(mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(mTermSys.mskExecMode(AsgnMode), eExecAsgnMode);
	Warn(!computable(), eTermNotComputable);

	SetNotUnset ? setRequirement(this) : unsetRequirement(this);
	mTermSys.setFuncRequired(this, SetNotUnset);

	CatchError
}
#endif	//CompLazyHalf


#if CompLazy
/*!
	Return whether has backlog?
*/
inline Bll Func::backlog() const
{
	WatchError
	return mBacklogPrms.tagCount();
	CatchError
}
#endif	//CompLazy




#if CompLazy
/*!
	Perform likely undo for a parameter.
*/
inline void Func::performLikelyUndo(Pos const thePos)
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskExecMode(IncrMode), eNotExecIncrMode);
	Warn(thePos >= mPrmTerms.itemCount(), eIndexBeyondLimit);

	#if CompLazyHalf
	if (!defered() || !chgdExecClk())	// Undefered and executing
		return;
	#else
	if (!chgdExecClk())	// Undefered and executing
		return;
	#endif
	if (mBacklogPrms.tagBll(thePos))	// func does not need likely undo
	{
		if (mBacklogPrms.tagCount() == 1)
			notifyLikelyUndoArgs();
	}
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	Perform eval undo for a parameter.
*/
inline void Func::performEvalUndo(Pos const thePos)
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskExecMode(IncrMode), eNotExecIncrMode);
	Warn(thePos >= mPrmTerms.itemCount(), eIndexBeyondLimit);
	Warn(!mEvalUndonePrms, eNullPointer);

	#if CompLazyHalf
	if (!defered() || !chgdExecClk()) 		// An undefered and executing
		return;								// func does not need uneval.
	#else
	if (!chgdExecClk()) 					// An undefered and executing
		return;								// func does not need uneval.
	#endif

	if (mEvalUndonePrms->tagBll(thePos)) 	// This is required even for !mUnevaldefined.
	{								 		// This tells us whether there was any actual change.
											// In which case, we must perform redo.
		if (mEvalUndoDefined)
			undoEval(thePos);
		if (mBacklogPrms.tagBll(thePos))
		{	if (mBacklogPrms.tagCount() == 1)
				notifyLikelyUndoArgs();
		}
	}
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	Perform hint undo for a parameter.
*/
inline void Func::performHintUndo(Pos const thePos)
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskExecMode(IncrMode), eNotExecIncrMode);
	Warn(thePos >= mPrmTerms.itemCount(), eIndexBeyondLimit);

	#if CompLazyHalf
	if (!defered() || !chgdExecClk()) 	// An undefered and executing
		return;							// func does not need unhint.
	#else
	if (!chgdExecClk()) 				// An undefered and executing
		return;							// func does not need unhint.
	#endif

	if (mHintUndoDefined)
		undoHint(thePos);
	if (mBacklogPrms.tagBll(thePos))
	{
		if (mBacklogPrms.tagCount() == 1)
			notifyLikelyUndoArgs();
	}
	CatchError
}
#endif	//CompLazy



#if SimulDnwdCache
/*!
	Check need for simul cache update and update clock.
*/
inline Bll Func::needSimulCacheComp()
{
	WatchError
	if (mSimulCacheClk == mTermSys.SimulCacheClk()) 	//sys clock because depends on the whole system
		return false;									// rather than the last exec of the term.
	mSimulCacheClk = mTermSys.SimulCacheClk();
	return true;
	CatchError
}
#endif



/*!
	Synchronize the execution clock.
*/
inline void Func::syncExecClk()
{
	WatchError
	#if SimulDnwdCache
	mSimulCacheClk = NotClk;
	#endif

	#if CompLazy
	mBacklogPrms.syncClk();
	if (mEvalUndonePrms)
		mEvalUndonePrms->syncClk();
	#endif // CompLazy

	#if ExecDnwd
	mLblCandPrms.syncClk();
	#endif//ExecDnwd

	#if SimulDnwdFixed
	mLblFixedPrms.syncClk();
	#endif
	#if SimulDnwdFlexi
	if (mLblFlexiPrms)
		mLblFlexiPrms->syncClk();
	#endif

	Term::syncExecClk();
	CatchError
}


#if ExecDnwd
/*!
	Return whether the execution cand params need to be computed.
*/
inline Bll Func::needExecCandComp()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(mTermSys.chkExecMode(NullComp), eSysUninit);

	if (mExecAsgnClk == mTermSys.ExecAsgnClk())
		return false;

	mExecAsgnClk = mTermSys.ExecAsgnClk();
	return true;
	CatchError
}
#endif


#if SimulDnwdFixed
/*!
	Return whether the simulation assignment clock has changed.
*/
inline Bll Func::needSimulFixedComp()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(mTermSys.chkExecMode(NullComp), eSysUninit);

	if (mSimulFixedClk == mTermSys.SimulFixedClk())
		return false;

	mSimulFixedClk = mTermSys.SimulFixedClk();
	return true;
	CatchError
}
#endif



#if SimulDnwdFlexi
/*!
	Return whether the simulation assignment clock has changed.
*/
inline Bll Func::needSimulFlexiComp()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(mTermSys.chkExecMode(NullComp), eSysUninit);

	#if FuncFlexiClk
	if (mSimulFlexiClk == mTermSys.SimulFlexiClk())
		return false;

	mSimulFlexiClk = mTermSys.SimulFlexiClk();
	return true;
	#else
		return mTermSys.chgdSimulFlexiVars();
	#endif
	CatchError
}
#endif




#if ExecDnwd
/*!
	Synchronize the execution assignment clock.
*/
inline void Func::syncExecAsgnClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);

	mExecAsgnClk = NotClk;
	CatchError
}
#endif


#if SimulDnwd
/*!
	Synchronize the simulation assignment clock.
*/
inline void Func::syncSimulAsgnClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);

	#if SimulFixed
	mSimulFixedClk = NotClk;
	#endif
	CatchError
}
#endif


#if SimulDnwdCache
/*!
	Synchronize the simulation cache clock.
*/
inline void Func::syncSimulCacheClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);

	mSimulCacheClk = NotClk;
	CatchError
}
#endif




/*!
	Perform constant function computation.
*/
inline void Func::performCompConst()
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	compConst();
	CatchError
}


#if CompLazy
/*!
	Set whether eval undo is defined.
*/
inline void Func::setEvalUndoDefined(Bll const SetNotUnset)
{
	WatchError
	ccast<Bll &>(mEvalUndoDefined) = SetNotUnset;
	CatchError
}
#endif	//CompLazy



#if CompLazy
/*!
	Set whether hint undo is defined.
*/
inline void Func::setHintUndoDefined(Bll const SetNotUnset)
{
	WatchError
	ccast<Bll &>(mHintUndoDefined) = SetNotUnset;
	CatchError
}
#endif	//CompLazy



#if CompDnwd
/*!
	Set the link for the parameter
*/
inline void Func::setParamLink(Pos const thePos, Lnk const theLnk)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);
	Warn(theLnk == InvLnk, eInvalidLink);

	ccast<b1<Lnk, kmm> &>(mPrmLinks)[thePos] = theLnk;
	CatchError
}
#endif	//CompDnwd



/*!
	Return the root function link.
*/
inline Lnk Func::RootFuncLink() const
{
	WatchError
	return mRootFuncLnk;
	CatchError
}



/*!
	Set the root function link.
*/
inline void Func::setRootFuncLink(Lnk const theLink)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	mRootFuncLnk = theLink;
	CatchError
}



#if CompLazyHalf
/*!
	Return the required function link.
*/
inline Lnk Func::ReqFuncLink() const
{
	WatchError
	return mReqFuncLnk;
	CatchError
}
#endif	//CompLazyHalf



#if CompLazyHalf
/*!
	Set the required function link.
*/
inline void Func::setReqFuncLink(Lnk const theLink)
{
	WatchError
	mReqFuncLnk = theLink;
	CatchError
}
#endif	//CompLazyHalf


/*!
	Adjust memory allocation automatically.
*/
inline void Func::adjustMemAuto()
{
	WatchError
	ccast<b1<Hdl, xmm> &>(FuncVars).adjustMemAuto();
	#if CompUpwd && ! UpwdMapFuncVarArray
		ccast<hm<Hdl,Sqn, xmmh> &>(mVarHdlSqns).adjustMemAuto();
	#endif
	#if CompDnwd && DnwdMapFuncVar == MfvFuncHashVar
		ccast<hm<Hdl,Sqn, xmmh> &>(mVarHdlSqns).adjustMemAuto();
	#endif
	ccast<rl< b1<Sqn, xmm>, nmm> &>(PrmVars).adjustListsMemAuto();
	#if CompDnwd
	ccast<rl< b1<Pos, xmm>, xmm > &>(mVarUpdtPrms).adjustMemAuto();
	ccast<rl< b1<Pos, xmm>, xmm > &>(mVarUpdtPrms).adjustListsMemAuto();
	#endif//CompDnwd

	#if ExecDnwdMultiCand
	if (mCandMrgBlk) mCandMrgBlk->adjustMemAuto();
	#endif

	#if SimulDnwdMultiFixed
	if (mFixedMrgBlk) mFixedMrgBlk->adjustMemAuto();
	#endif
	#if SimulDnwdMultiFlexi
	if (mFlexiMrgBlk) mFlexiMrgBlk->adjustMemAuto();
	#endif
	Term::adjustMemAuto();
	CatchError
}



#if CompLazy
/*!
	Set up parameters for eval undo.
*/
inline void Func::setupEvalUndoPrms()
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	if (!mEvalUndonePrms)
		mEvalUndonePrms = new lf<Pos, kmm>(mPrmTerms.itemCount());
	CatchError
}
#endif	//CompLazy



/*!
	Define as root function.
*/
inline void Func::defSysRoot()
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	mTermSys.defRoot(this);
	CatchError
}



#if ExecUpwd
/*!
	Clear the execution changed parameters.
*/
inline void Func::clearExecChgdPrms()
{
	WatchError
	mExecChgdPrms.sweep(mTermSys.ExecClk());
	CatchError
}
#endif//ExecUpwd



#if SimulUpwd
/*!
	Clear the simulation changed params.
*/
inline void Func::clearSimulChgdPrms()
{
	WatchError
	mSimulChgdPrms.sweep(mTermSys.SimulClk());
	CatchError
}
#endif//SimulUpwd



#if SimulDnwdFixed
/*!
	Enumerate the fixed params.
*/
inline void Func::enumFixedParams(Bll const MarkNotList)
{
	WatchError
	MarkNotList ? markFixedParams() : listFixedParams();
	CatchError
}
#endif


#if SimulDnwdFlexi
/*!
	Enumerate the flexi params.
*/
inline void Func::enumFlexiParams(Bll const MarkNotList)
{
	WatchError
	MarkNotList ? markFlexiParams() : listFlexiParams();
	CatchError
}
#endif



#if CompLazyHalf
/*!
	Set requirement.
*/
inline void Func::setRequirement(Func * theFunc)
{
	WatchError
	Warn(!theFunc, eNullPointer);
	Warn(theFunc->mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(!theFunc->updatable(), eTermNotUpdatable);

	if (++theFunc->mRequired > 1 || theFunc->mEnforced) return;
	if (theFunc->mTermSys.mskExecMode(IncrProp))
		Term::performExecIncr(theFunc);
	theFunc->mDefered = false;
	theFunc->notifyEnforcedPrms();
	CatchError
}
#endif // CompLazyHalf



#if CompLazyHalf
/*!
	Set enforcement.
*/
inline void Func::setEnforcement(Func * theFunc)
{
	WatchError
	Warn(!theFunc, eNullPointer);
	Warn(theFunc->mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(!theFunc->updatable(), eTermNotUpdatable);

	if (++theFunc->mEnforced > 1 || theFunc->mRequired) return;
	if (theFunc->mTermSys.mskExecMode(IncrProp))
		Term::performExecIncr(theFunc);
	theFunc->mDefered = false;
	theFunc->notifyEnforcedPrms();
	CatchError
}
#endif // CompLazyHalf



#if CompLazyHalf
/*!
	Unset requirement.
*/
inline void Func::unsetRequirement(Func * theFunc)
{
	WatchError
	Warn(!theFunc, eNullPointer);
	Warn(theFunc->mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(!theFunc->mRequired, eTermNotRequired);
	Warn(!theFunc->updatable(), eTermNotUpdatable);

	if (--theFunc->mRequired || theFunc->mEnforced) return;
	if (theFunc->mTermSys.mskExecMode(IncrProp))
		Term::performExecIncr(theFunc);
	theFunc->mDefered = true;

	theFunc->notifyDeferedPrms();
	CatchError
}
#endif // CompLazyHalf


#if CompLazyHalf
/*!
	Unset enforcement.
*/
inline void Func::unsetEnforcement(Func * theFunc)
{
	WatchError
	Warn(!theFunc, eNullPointer);
	Warn(theFunc->mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(!theFunc->updatable(), eTermNotUpdatable);

	if (--theFunc->mEnforced || theFunc->mRequired) return;
	if (theFunc->mTermSys.mskExecMode(IncrProp))
		Term::performExecIncr(theFunc);
	theFunc->mDefered = true;

	theFunc->notifyDeferedPrms();
	CatchError
}
#endif	//CompLazyHalf



#if SimulDnwdFlexi
/*!
	Set up flexible parameter labels.
*/
inline void Func::setupFlexiLabels()
{
	WatchError
	if (!mLblFlexiPrms)
		mLblFlexiPrms = new lf<Pos, kmm>(mPrmTerms.itemCount());
	CatchError
}
#endif //SimulDnwdFlexi


closeKangarooSpace




#endif//FuncHppIncluded
