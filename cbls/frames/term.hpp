/*!
	@file term.hpp
	@brief The prototype file for Term class.
	@details This is the prototype file for Term class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 03.01.2010 QRL NICTA www.nicta.com.au
	@see term.cpp
*/



#ifndef TermHppIncluded
#define TermHppIncluded



#include "cbls/frames/dat.hpp"
#include "cbls/frames/sys.hpp"

#include "cbls/frames/reg.hh"
#include "cbls/frames/mode.hh"
#include "cbls/frames/arg.hpp"


openKangarooSpace



/*
	Forward declarations.
*/

class Var;
class Func;



/*!
	@class Term
	@brief A class to represent terms.
	@details This class represents terms.
*/
class Term
{
	public:

		Gen const TermGen;	//!< Term genus is either variable, constant or function.
		Cat const TermCat;	//!< Term category considers categories within a genus.
		Typ const TermTyp;	//!< Term type considers data types of a term
		Cls const TermCls;	//!< Term class is a concrete term implementation.

		Hdl const TermHdl;	//!< Term handle is unique within a given term genus.
		Hvl	const TermHvl;	//!< Term hashval is used in quick matching.

	public:

		Bll updatable() const; 					//!< Updatable?
		Bll computable() const; 				//!< Computable?

		virtual Typ ValueType() const;			//!< Value type.
		virtual Typ MetricType() const;			//!< Metric type.

		//! @name Locators
		//! @{

		virtual Loc ValueLoc() const;			//!< Value locator.
		virtual Loc MetricLoc() const;			//!< Metric locator.
		virtual Loc EvalMinLoc() const;			//!< Eval min locator.
		virtual Loc EvalMaxLoc() const;			//!< Eval max locator.
		virtual Loc HintMinLoc() const;			//!< Hint min locator.
		virtual Loc HintMaxLoc() const;			//!< Hint max locator.

		//! @}

		//! @name Computations
		//! @{

		static void performExec(Term & theTerm);		//!< Execute in current (anew or incr) mode.
		static void performSimul(Term & theTerm);		//!< Simulate in current (anew or incr) mode.

		static void performExecAnew(Term & theTerm);	//!< Execute in anew mode.
		static void performExecIncr(Term & theTerm);	//!< Execute in incremental mode.
		static void performSimulAnew(Term & theTerm);	//!< Simulate in anew mode.
		static void performSimulIncr(Term & theTerm);	//!< Simulate in incremental mode.

		static void performExec(Term * theTerm);		//!< Execute in current (anew or incr) mode.
		static void performSimul(Term * theTerm);		//!< Simulate in current (anew or incr) mode.

		static void performExecAnew(Term * theTerm);	//!< Execute in anew mode.
		static void performExecIncr(Term * theTerm);	//!< Execute in incremental mode.
		static void performSimulAnew(Term * theTerm);	//!< Simulate in anew mode.
		static void performSimulIncr(Term * theTerm);	//!< Simulate in incremental mode.

		//! @}

		/*!
			@name Clocks
		*/
		//! @{

		Clk ExecClk() const;	//!< The execution clock.
		Clk SimulClk() const;	//!< The simulation clock.

		//! @}

	protected:

		//! @name Computations
		//! @{

		#if CompLazy
		static void performExecBklg(Term * theTerm);	//!< Execute in backlog mode.
		static void performEmulBklg(Term * theTerm);	//!< Emulate in backlog mode.
		#endif

		//! @}
		#if CompLazy
		//! @name Undo Support
		//! @{

		static void relistEvalUndoArg(Term * theTerm, Lnk const theLnk);	//!< Relist an argument requiring eval undo.
		static void enlistHintUndoArg(Term * theTerm, Lnk const theLnk);	//!< Enlist an argument requiring hint undo.
		static void delistHintUndoArg(Term * theTerm, Lnk const theLnk);	//!< Delist an argument requiring hint undo.

		//! @}
		#endif	//	CompLazy

		#if CompUpwd
		//! @name Schedules
		//! @{

		#if ExecUpwd
		void scheduleExecAnewArgs();	//!< Schedule args for exec anew.
		void scheduleExecIncrArgs();	//!< Schedule args for exec incr.
		#endif

		#if SimulUpwd
		void scheduleSimulAnewArgs();	//!< Schedule args for simul anew.
		void scheduleSimulIncrArgs();	//!< Schedule args for simul incr.
		#endif

		//! @}
		#endif	// CompUpwd

	protected:

		friend class Sys;
		friend class Func;
		friend class Selc;

		virtual ~Term();										//!< Destructor.
		Term(Term const & that);								//!< Duplicator.
		Term(Hdl const hdlSys);									//!< Constructor.
		Term const & operator = (Term const & that);			//!< Assigner.

		virtual void adjustMemAuto();							//!< Adjust memory requirement.
		virtual Lnk setArg(Arg const & theArg);					//!< Set an argument in the term.
		virtual Bll equate(Term const & that) const = 0;		//!< Equality checking.

		//! @name Properties
		//! @{

		void setTermGen(Gen const theTermGen);					//!< Set term genus.
		void setTermCls(Cls const theTermCls);					//!< Set term class.
		void setTermCat(Cat const theTermCat);					//!< Set term category.
		void setTermTyp(Typ const theTermTyp);					//!< Set term type.

		void setTermHdl(Hdl const theTermHdl);					//!< Set term handle.
		void setTermHvl(Hvl const theTermHvl);					//!< Set term hashval.

		void setUpdatable(Bll const SetNotUnset);				//!< Set updatablity.

		//! @}

		//! @name Computations
		//! @{

		virtual void execAnew() = 0;	//!< Compute in anew execution mode.
		virtual void execIncr() = 0;	//!< Compute in incr execution mode.
		virtual void simulAnew() = 0;	//!< Compute in anew simulation mode.
		virtual void simulIncr() = 0;	//!< Compute in incr simulation mode.

		#if CompLazy
		virtual void execBklg() = 0;	//!< Compute in bklg execution mode.
		virtual void emulBklg() = 0;	//!< Compute in bklg emulation mode.
		#endif

		//! @}

		//! @name Clocks
		//! @{

		#if CompLazy
		void updtEmulClk();				//!< Update the emulation clock.
		Bll chgdEmulClk() const;		//!< The emulation clock has changed.
		#endif

		void updtExecClk();				//!< Update the execution clock.
		Bll chgdExecClk() const;		//!< The execution clock has changed?

		void updtSimulClk();			//!< Update the simulation clock.
		Bll chgdSimulClk() const;		//!< The simulation clock has changed?

		//! @}

		//! @name Synchronisation
		//! @{

		virtual void syncExecClk();		//!< Synchronize the execution clock.
		virtual void syncSimulClk();	//!< Synchronize the simulation clock.
		#if ExecDnwd
		virtual void syncExecAsgnClk();	//!< Synchronize the execution assign clock.
		#endif
		#if SimulDnwd
		virtual void syncSimulAsgnClk();//!< Synchronize the simulation assign clock.
		#endif

		//! @}

		//! @name Deferments
		//! @{

		#if CompLazy
		void setupEvalUndoArgs();		//!< Set up arguments requiring undo of eval.
		void setupHintUndoArgs();		//!< Set up arguments requiring undo of hint.
		virtual void setupUndoArgs();	//!< Set up for arguments that might need undo.

		void clearEvalUndoArgs();		//!< Clear arguments requiring eval undo after exec anew.
		void notifyLikelyUndoArgs();	//!< Call arguments to notify likely undo recursively.
		void notifyEvalUndoArgs();		//!< Upon change, call arguments to perform eval undo.
		void notifyHintUndoArgs();		//!< Upon change, call arguments to perform hint undo.
		#endif

		//! @}

	protected:

		Sys & mTermSys;						//!< Term Sys.

		//! @name Arguments
		//! @{

		b1<Arg, xmm> const	mTermAsArgs;	//!< The arguments used in the dependant terms.
		#if CompLazy
		ll<Lnk, kmm> *		mEvalUndoArgs;	//!< The args requiring eval undo; set up by derivatives.
		lu<Lnk, kmm> *		mHintUndoArgs;	//!< The args requiring hint undo; set up by derivatives.
		#endif

		//! @}

		//! @name Clocks
		//! @{

		//	The purpose of the emulation clock extends towards
		//	determination of computability of a term.

		Clk mEmulClk;	//!< The emulation clock.
		Clk mExecClk;	//!< The execution clock.
		Clk	mSimulClk;	//!< The simulation clock.

		//! @}
};



/*!
	The destructor.
*/
inline Term::~Term()
{
	WatchError
	#if CompLazy
	if (mEvalUndoArgs) delete mEvalUndoArgs;
	if (mHintUndoArgs) delete mHintUndoArgs;
	#endif
	CatchError
}



/*!
	Peform execution in current (anew or incr) mode.
*/
inline void Term::performExec(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(!theTerm->mTermSys.mskExecMode(PropMode), eNotExecPropMode);
	if (theTerm->mTermSys.chkExecMode(AnewProp))
		Term::performExecAnew(theTerm);
	else
		Term::performExecIncr(theTerm);
	CatchError
}



/*!
	Peform execution in current (anew or incr) mode.
*/
inline void Term::performExec(Term & theTerm)
{
	WatchError
	Warn(!theTerm.mTermSys.mskExecMode(PropMode), eNotExecPropMode);
	if (theTerm.mTermSys.chkExecMode(AnewProp))
		Term::performExecAnew(theTerm);
	else
		Term::performExecIncr(theTerm);
	CatchError
}



/*!
	Peform simulation in current (anew or incr) mode.
*/
inline void Term::performSimul(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(!theTerm->mTermSys.mskSimulMode(PropMode), eNotSimulPropMode);
	if (theTerm->mTermSys.chkSimulMode(AnewProp))
		Term::performSimulAnew(theTerm);
	else
		Term::performSimulIncr(theTerm);
	CatchError
}



/*!
	Peform simulation in current (anew or incr) mode.
*/
inline void Term::performSimul(Term & theTerm)
{
	WatchError
	Warn(!theTerm.mTermSys.mskSimulMode(PropMode), eNotSimulPropMode);
	if (theTerm.mTermSys.chkSimulMode(AnewProp))
		Term::performSimulAnew(theTerm);
	else
		Term::performSimulIncr(theTerm);
	CatchError
}



/*!
	Peform execution in anew mode.
*/
inline void Term::performExecAnew(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	if (theTerm->chgdExecClk())
		{ theTerm->updtExecClk(); theTerm->execAnew(); }
	//	the following checking is delibourate done on a delayed basis.
	Warn(!theTerm->mTermSys.chkExecMode(AnewProp), eNotExecAnewProp);
	CatchError
}



/*!
	Peform execution in anew mode.
*/
inline void Term::performExecAnew(Term & theTerm)
{
	WatchError
	if (theTerm.chgdExecClk())
		{ theTerm.updtExecClk(); theTerm.execAnew(); }
	//	the following checking is delibourate done on a delayed basis.
	Warn(!theTerm.mTermSys.chkExecMode(AnewProp), eNotExecAnewProp);
	CatchError
}



#if !CompLazyFull
/*!
	Peform execution in incremental mode.
*/
inline void Term::performExecIncr(Term * theTerm)
{
	//another non-inline version exist for CompLazyFull
	WatchError
	Warn(!theTerm, eNullPointer);
	if (theTerm->chgdExecClk())
		{ theTerm->updtExecClk(); theTerm->execIncr(); }
	//	the following checking is delibourate done on a delayed basis.
	Warn(!theTerm->mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);
	CatchError
}
#endif //!CompLazyFull



#if !CompLazyFull
/*!
	Peform execution in incremental mode.
*/
inline void Term::performExecIncr(Term & theTerm)
{
	//another non-inline version exist for CompLazyFull
	WatchError
	if (theTerm.chgdExecClk())
		{ theTerm.updtExecClk(); theTerm.execIncr(); }
	//	the following checking is delibourate done on a delayed basis.
	Warn(!theTerm.mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);
	CatchError
}
#endif //!CompLazyFull



/*!
	Peform simulation in anew mode.
*/
inline void Term::performSimulAnew(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	if (theTerm->chgdSimulClk())
		{ theTerm->updtSimulClk(); theTerm->simulAnew(); }
	//	the following checking is delibourate done on a delayed basis.
	Warn(!theTerm->mTermSys.chkSimulMode(AnewProp), eNotSimulAnewProp);
	CatchError
}



/*!
	Peform simulation in anew mode.
*/
inline void Term::performSimulAnew(Term & theTerm)
{
	WatchError
	if (theTerm.chgdSimulClk())
		{ theTerm.updtSimulClk(); theTerm.simulAnew(); }
	//	the following checking is delibourate done on a delayed basis.
	Warn(!theTerm.mTermSys.chkSimulMode(AnewProp), eNotSimulAnewProp);
	CatchError
}



/*!
	Peform simulation in incremental mode.
*/
inline void Term::performSimulIncr(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	if (theTerm->chgdSimulClk())
		{ theTerm->updtSimulClk(); theTerm->simulIncr(); }
	//	the following checking is delibourate done on a delayed basis.
	Warn(!theTerm->mTermSys.mskSimulMode(IncrProp), eNotSimulIncrProp);
	CatchError
}



/*!
	Peform simulation in incremental mode.
*/
inline void Term::performSimulIncr(Term & theTerm)
{
	WatchError
	if (theTerm.chgdSimulClk())
		{ theTerm.updtSimulClk(); theTerm.simulIncr(); }
	//	the following checking is delibourate done on a delayed basis.
	Warn(!theTerm.mTermSys.mskSimulMode(IncrProp), eNotSimulIncrProp);
	CatchError
}




#if CompLazy
/*!
	Relist an argument for eval undo.
*/
inline void Term::relistEvalUndoArg(Term * theTerm, Lnk const theLnk)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(!theTerm->updatable(), eTermNotUpdatable);
	Warn(theTerm->mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(!theTerm->mEvalUndoArgs, eNullPointer);

	theTerm->mEvalUndoArgs->tagBll(theLnk);
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Enlist an argument for hint undo
*/
inline void Term::enlistHintUndoArg(Term * theTerm, Lnk const theLnk)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(!theTerm->updatable(), eTermNotUpdatable);
	Warn(theTerm->mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(!theTerm->mHintUndoArgs, eNullPointer);

	theTerm->mHintUndoArgs->tagBll(theLnk);
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Delist an argument for hint undo.
*/
inline void Term::delistHintUndoArg(Term * theTerm, Lnk const theLnk)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(!theTerm->updatable(), eTermNotUpdatable);
	Warn(theTerm->mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(!theTerm->mHintUndoArgs, eNullPointer);

	theTerm->mHintUndoArgs->untagBll(theLnk);
	CatchError
}
#endif // CompLazy



/*!
	Set the term class.
*/
inline void Term::setTermCls(Cls const theTermCls)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);
	Warn(theTermCls == TermClsNil, eNilCls);

	ccast<Cls &>(TermCls) = theTermCls;
	CatchError
}



/*!
	Set the term category.
*/
inline void Term::setTermCat(Cat const theTermCat)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);
	Warn(theTermCat == TermCatNil, eNilCat);

	ccast<Cat &>(TermCat) = theTermCat;
	CatchError
}



/*!
	Set the term type.
*/
inline void Term::setTermTyp(Typ const theTermTyp)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);
	Warn(theTermTyp == TermTypNil, eNilTyp);

	ccast<Typ &>(TermTyp) = theTermTyp;
	CatchError
}



/*!
	Set the term handle.
*/
inline void Term::setTermHdl(Hdl const hdlTerm)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);
	Warn(hdlTerm == InvHdl, eInvalidHandle);

	ccast<Hdl &>(TermHdl) = hdlTerm;
	CatchError
}



/*!
	Set the term hashval.
*/
inline void Term::setTermHvl(Hvl const theTermHvl)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	ccast<Hvl &>(TermHvl) = theTermHvl;
	CatchError
}



/*!
	Set the term genus.
*/
inline void Term::setTermGen(Gen const theTermGen)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);
	switch(theTermGen)
	{
		case Tc :
			mExecClk = mSimulClk = EtrClk;
			break;
		case Tv :
			mExecClk = mSimulClk = NotClk;
			mEmulClk = EtrClk;
			break;
		case Tf :
			mEmulClk = mExecClk = mSimulClk = InfClk;
			break;
		default :
			Throw(eTermGenUndefined);
			break;
	}
	ccast<Gen &>(TermGen) = theTermGen;
	CatchError
}



/*!
	Set the updatability (and also computability) of a term.
*/
inline void Term::setUpdatable(Bll const SetNotUnset)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	if (SetNotUnset)
		mEmulClk = mExecClk = mSimulClk = NotClk;
	else
		mEmulClk = mExecClk = mSimulClk = InfClk;
	CatchError
}



/*!
	Return updatability?
*/
inline Bll Term::updatable() const
{
	WatchError
	return mExecClk < InfClk || mSimulClk < InfClk;
	CatchError
}



/*!
	Return computability?
*/
inline Bll Term::computable() const
{
	WatchError
	return mEmulClk < InfClk;
	CatchError
}



#if CompLazy
/*!
	Return whether emulation clock has changed.
*/
inline Bll Term::chgdEmulClk() const
{
	WatchError
	return mEmulClk < mTermSys.EmulClk();
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Update the emulation clock.
*/
inline void Term::updtEmulClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(!chgdEmulClk(), eEmulClkNotChgd);

	mEmulClk = mTermSys.EmulClk();
	CatchError
}
#endif // CompLazy



/*!
	Return whether execution clock has changed.
*/
inline Bll Term::chgdExecClk() const
{
	WatchError
	return mExecClk < mTermSys.ExecClk();
	CatchError
}



/*!
	Update the execution clock.
*/
inline void Term::updtExecClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(!chgdExecClk(), eExecClkNotChgd);

	mExecClk = mTermSys.ExecClk();
	CatchError
}



/*!
	Return whether simulation clock has changed.
*/
inline Bll Term::chgdSimulClk() const
{
	WatchError
	return mSimulClk < mTermSys.SimulClk();
	CatchError
}



/*!
	Update the simulation clock.
*/
inline void Term::updtSimulClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(mTermSys.chkSimulMode(NullComp), eSimulModeNull);
	Warn(!chgdSimulClk(), eSimulClkNotChgd);

	mSimulClk = mTermSys.SimulClk();
	CatchError
}



/*!
	Synchronize with the exec clock of the sys.
*/
inline void Term::syncExecClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);

	#if CompLazy
	if (mEvalUndoArgs) mEvalUndoArgs->syncClk();
	if (mHintUndoArgs) mHintUndoArgs->syncClk();
	if (mEmulClk < InvClk) mEmulClk = NotClk;
	#endif // CompLazy

	if (mExecClk < InvClk) mExecClk = NotClk;
	CatchError
}



/*!
	Synchronize with assign clock of the sys.
*/
inline void Term::syncSimulClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);

	if (mSimulClk < InvClk) mSimulClk = NotClk;
	CatchError
}


#if ExecDnwd
/*!
	Synchronize with the exec assign clock of the sys.
*/
inline void Term::syncExecAsgnClk()
{
	WatchError
	//	nothing to be done.
	CatchError
}
#endif


#if SimulDnwd
/*!
	Synchronize with the simul assign clock of the sys.
*/
inline void Term::syncSimulAsgnClk()
{
	WatchError
	//	nothing to be done.
	CatchError
}
#endif


/*!
	Adjust memory allocation.
*/
inline void Term::adjustMemAuto()
{
	WatchError
	ccast<b1<Arg, xmm> &>(mTermAsArgs).adjustMemAuto();
	CatchError
}



/*!
	Set the given argument in the term.
*/
inline Lnk Term::setArg(Arg const & theArg)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);
	Warn(!theArg.valid(), eInvalidArgument);

	return ccast<b1<Arg, xmm> &>(mTermAsArgs).insertItrMem(theArg);
	CatchError
}



#if CompLazy
/*!
	Set up eval undo arguments.
*/
inline void Term::setupEvalUndoArgs()
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	if (!mEvalUndoArgs)
		mEvalUndoArgs = new ll<Lnk, kmm>(mTermAsArgs.itemCount());
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Set up hint undo arguments.
*/
inline void Term::setupHintUndoArgs()
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	if (!mHintUndoArgs)
		mHintUndoArgs = new lu<Lnk, kmm>(mTermAsArgs.itemCount());
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Clear eval undo arguments.
*/
inline void Term::clearEvalUndoArgs()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskExecMode(AnewMode), eNotExecAnewMode);
	Warn(!mEvalUndoArgs, eNullPointer);

	mEvalUndoArgs->sweep(mTermSys.ExecClk());
	CatchError
}
#endif // CompLazy



/*!
	The execution clock.
*/
inline Clk Term::ExecClk() const
{
	WatchError
	return mExecClk;
	CatchError
}



/*!
	The simulation clock.
*/
inline Clk Term::SimulClk() const
{
	WatchError
	return mSimulClk;
	CatchError
}



closeKangarooSpace


#endif // TermHppIncluded
