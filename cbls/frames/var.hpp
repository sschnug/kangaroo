/*!
	@file var.hpp
	@brief The prototype file for Var class.
	@details This is the prototype file for Var class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see var.cpp
	@see term.hpp
*/



#ifndef VarHppIncluded
#define VarHppIncluded



#include "cbls/frames/reg.hh"
#include "cbls/frames/term.hpp"
#include "cbls/frames/arg.hpp"
#include "cbls/frames/wrp.hpp"



openKangarooSpace



/*!
	@class Var
	@brief A class to represent variables.
	@details This class represents variables.
		Domains of the variables could be static or dynamic.
		Dynamic domains are modified by updating or allowing
		avoidance of recent values. For static variables, the
		dynamic properties coincide with the static properties.
*/
class Var : public Term
{
	public:

		static Var & refm(Hdl const hdlSys, Hdl const hdlVar);			//!< Reference.
		static Var * ptrm(Hdl const hdlSys, Hdl const hdlVar);			//!< Pointer.
		static Var const & refc(Hdl const hdlSys, Hdl const hdlVar);	//!< Reference.
		static Var const * ptrc(Hdl const hdlSys, Hdl const hdlVar);	//!< Pointer.

		//! @name Casting
		//! @{

		static Var const & cast(Term const & theTerm);	//!< Perform casting.
		static Var const * cast(Term const * theTerm);	//!< Perform casting.
		static Var & cast(Term & theTerm);				//!< Perform casting.
		static Var * cast(Term * theTerm);				//!< Perform casting.

		static Bll suit(Term const & theTerm);			//!< Suits casting?
		static Bll suit(Term const * theTerm);			//!< Suits casting?
		static Bll suit(Term & theTerm);				//!< Suits casting?
		static Bll suit(Term * theTerm);				//!< Suits casting?

		//! @}

	public:

		virtual void updateDomain();	 							//!< Update the domain.
		virtual Bll DomainUpdateDefined() const;					//!< Domain update defined.
		#if CompLazyHalf
		Bll DomainUpdateRequired() const;							//!< Domain update required?
		void setDomainUpdateRequired(Bll const SetNotUnset);		//!< Set domain update required.
		#endif //CompLazyHalf

		#if DnwdVarMapFunc
		Sqn findFuncSqn(Hdl const hdlFunc) const;					//!< Find sqn for a given function.
		#endif

		//! @name Wrappers
		//! @{

		virtual Wrp CurrWrap() const = 0;							//!< Current value wrap of the variables.
		virtual Wrp NextWrap() const = 0;							//!< Next value wrap of the variables.
		virtual Wrp StatRandWrap(Rnd & theRnd) const = 0;			//!< Random value chosen from the static domain.
		virtual Wrp DynaRandWrap(Rnd & theRnd) const = 0;			//!< Random value chosen from the dynamic domain.

		//! @}

		//! @name Validity
		//! @{

		virtual Bll validStat(Wrp const & theWrp) const = 0;		//!< Valid with respect to the static domain?
		virtual Bll validDyna(Wrp const & theWrp) const = 0;		//!< Valid with respect to the dynamic domain?

		//! @}
		//! @name Compatibility
		//! @{

		virtual Bll identical(Var const * that) const = 0;		//!< Whether identical?
		virtual Bll identical(Var const & that) const = 0;		//!< Whether identical?
		virtual Bll assignable(Var const * that) const = 0;		//!< Whether assignable?
		virtual Bll assignable(Var const & that) const = 0;		//!< Whether assignable?
		virtual Bll swappable(Var const * that) const = 0;		//!< Whether swappable?
		virtual Bll swappable(Var const & that) const = 0;		//!< Whether swappable?

		//! @}

		//! @name Executions
		//! @{

		virtual void execAnewNext() = 0;						//!< Execute anew with the next value.
		virtual void execAnewWrap(Wrp const & theWrp) = 0;		//!< Execute anew with a given value.
		virtual void execAnewStatRand(Rnd & theRnd) = 0;		//!< Execute anew with a random value form the static domain.
		virtual void execAnewDynaRand(Rnd & theRnd) = 0;		//!< Execute anew with a random value from the dynamic domain.

		virtual void execIncrNext() = 0;						//!< Execute incrementally with the next value.
		virtual void execIncrWrap(Wrp const & theWrp) = 0;		//!< Execute incrementally with a given value.
		virtual void execIncrStatRand(Rnd & theRnd) = 0;		//!< Execute incrementally with a random value form the static domain.
		virtual void execIncrDynaRand(Rnd & theRnd) = 0;		//!< Execute incrementally with a random value from the dynamic domain.

		virtual void execIncrDiff(Var const * that) = 0;		//!< Execute incrementally with another variable's value.
		virtual void execIncrDiff(Var const & that) = 0;		//!< Execute incrementally with another variable's value.
		virtual void execIncrSwap(Var * that) = 0;				//!< Execute incrementally with swapping variables' values.
		virtual void execIncrSwap(Var & that) = 0;				//!< Execute incrementally with swapping variables' values.

		//! @}

		//! @name Simulations
		//! @{

		virtual void simulAnewCurr() = 0;						//!< Simulate anew with the current value.
		virtual void simulAnewWrap(Wrp const & theWrp) = 0;		//!< Simulate anew with a given value.
		virtual void simulAnewStatRand(Rnd & theRnd) = 0;		//!< Simulate anew with a random value form the static domain.
		virtual void simulAnewDynaRand(Rnd & theRnd) = 0;		//!< Simulate anew with a random value from the dynamic domain.

		virtual void simulIncrCurr() = 0;						//!< Simulate incrementally with the current value.
		virtual void simulIncrWrap(Wrp const & theWrp) = 0;		//!< Simulate incrementally with a given value.
		virtual void simulIncrStatRand(Rnd & theRnd) = 0;		//!< Simulate incrementally with a random value form the static domain.
		virtual void simulIncrDynaRand(Rnd & theRnd) = 0;		//!< Simulate incrementally with a random value from the dynamic domain.

		virtual void simulIncrDiff(Var const * that) = 0;		//!< Simulate incrementally with another variable's value.
		virtual void simulIncrDiff(Var const & that) = 0;		//!< Simulate incrementally with another variable's value.
		virtual void simulIncrSwap(Var * that) = 0;				//!< Simulate incrementally with swapping variables' values.
		virtual void simulIncrSwap(Var & that) = 0;				//!< Simulate incrementally with swapping variables' values.

		//! @}

		virtual Bll chkNextCurr() const = 0;					//!< Whether the next value is the current value.
		Bll locked() const;										//!< Whether the variable is locked.

	protected:

		friend class Sys;	// Accesses exec and simul methods.
		friend class Func;	//	Accesses func variable mapping methods.
		friend class Lock;	// Accesses lock methods.

		virtual ~Var();								//!< Destructor.
		Var(Hdl const hdlSys);						//!< Constructor.
		Var(Var const & that);						//!< Duplicator.
		Var const & operator = (Var const & that);	//!< Assigner.

		Hdl defSysVar();							//!< Define the var in the sys.
		virtual void adjustMemAuto();				//!< Adjust memory requirement automatically.

		Lnk DynaUpdtLink() const;					//!< The dynamic update link.
		void setDynaUpdtLink(Lnk const theLink);	//!< Set the dynamic update link.
		void lock(Bll const SetNotUnset);			//!< Lock the variable for updating.
		#if CompLazy
		virtual void setupUndoArgs();				//!< Set up arguments for undo operation.
		#endif // CompLazy

		//! @name Sequent Mapping
		//! @{

		#if DnwdVarMapFunc
			#if DnwdMapFuncVar == MfvVarArrayFunc
			b1<Sqn, kmm> const * mFuncHdlSqns;							//!< Function handle sqn array mapping.
			#elif DnwdMapFuncVar == MfvVarHashFunc
			hm<Hdl,Sqn, xmmh> const * mFuncHdlSqns;						//!< Function handle sqn hash-based mapping.
			#else
				#error Undefined function variable mapping.
			#endif
			void setFuncHdlSqn(Hdl const hdlFunc, Sqn const sqnVar);	//!< Set function handle sqn mapping.
			virtual void setupComputation();							//!< Set up for computation.
		#endif

		//! @}

		//! @name Computation
		//! @{

		virtual void execAnew();	//!< Anew execution; throws error.
		virtual void simulAnew();	//!< Anew simulation; throws error.
		virtual void execIncr();	//!< Incrmental execution; throws error.
		virtual void simulIncr();	//!< Incrmental simulation; throws error.

		#if CompLazy
		virtual void execBklg();	//!< Backlog execution; throws error.
		virtual void emulBklg();	//!< Backlog emulation; throws error.
		#endif

		//! @}

		//! @name Preprocessing
		//! @{

		void runPreSimulAnew();		//!< Preprocessing for anew simulation.
		void runPreExecAnew();		//!< Preprocessing for anew execution.
		void runPreSimulIncr();		//!< Preprocessing for incremental simulation.
		void runPreExecIncr();		//!< Preprocessing for incremental execution.

		//! @}

		/*
			During execution or simulation, a variable is marked before assignment.
			This marking is done by setting the corresponding assignment clock of the var.
			The marking and unmarking process works only when run-time error is traced.
			Note that the use of assignment clocks is different from this for funcs.
		*/

		#if CheckError
		//! @name Clocks
		//! @{

		void updtExecAsgnClk();				//!< Update the exec assign clock of the variable.
		void updtSimulAsgnClk();			//!< Update the simul assign clock of the variable.

		Bll chgdExecAsgnClk() const;		//!< The execution assignment clock has changed?
		Bll chgdSimulAsgnClk() const;		//!< The simulation assignment clock has changed?

		virtual void syncExecAsgnClk();		//!< Synchronize the execution assignment clock.
		virtual void syncSimulAsgnClk();	//!< Synchronize the simulation assignment clock.

		//! @}
		#endif//CheckError

		//! @name Identity
		//! @{

		virtual Bll equate(Term const & theTerm) const;		//!< Check equality.
		Hvl calcTermHvl() const;							//!< Calculate hash.

		//! @}

	protected:

		#if CheckError
		//! @name Clocks
		//! @{

		Clk	mExecAsgnClk;	//!< The execution assignment clock.
		Clk	mSimulAsgnClk;	//!< The simulation assignment clock.

		//! @}
		#endif//CheckError

		Lnk mDynaUpdtLink;	//!< The link for dynamic update.
};



/*!
	Whether a term is suitable for casting?
*/
inline Bll Var::suit(Term & theTerm)
{
	WatchError
	return theTerm.TermGen == Tv;
	CatchError
}



/*!
	Whether a term is suitable for casting?
*/
inline Bll Var::suit(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermGen == Tv;
	CatchError
}



/*!
	Whether a term is suitable for casting?
*/
inline Bll Var::suit(Term const & theTerm)
{
	WatchError
	return theTerm.TermGen == Tv;
	CatchError
}



/*!
	Whether a term is suitable for casting?
*/
inline Bll Var::suit(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);

	return theTerm->TermGen == Tv;
	CatchError
}



/*!
	Perform casting of a term.
*/
inline Var & Var::cast(Term & theTerm)
{
	WatchError
	Warn(theTerm.TermGen != Tv, eTermNotVariable);

	return scast<Var &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline Var * Var::cast(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermGen != Tv, eTermNotVariable);

	return scast<Var *>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline Var const & Var::cast(Term const & theTerm)
{
	WatchError
	Warn(theTerm.TermGen != Tv, eTermNotVariable);

	return scast<Var const &>(theTerm);
	CatchError
}



/*!
	Perform casting of a term.
*/
inline Var const * Var::cast(Term const * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	Warn(theTerm->TermGen != Tv, eTermNotVariable);

	return scast<Var const *>(theTerm);
	CatchError
}



/*!
	Refer to a variable.
*/
inline Var & Var::refm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return Sys::refm(hdlSys).refmVar(hdlVar);
	CatchError
}



/*!
	Point to a variable.
*/
inline Var * Var::ptrm(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return Sys::ptrm(hdlSys)->ptrmVar(hdlVar);
	CatchError
}



/*!
	Refer to a variable.
*/
inline Var const & Var::refc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return Sys::refc(hdlSys).refcVar(hdlVar);
	CatchError
}



/*!
	Point to a variable.
*/
inline Var const * Var::ptrc(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
	return Sys::ptrc(hdlSys)->ptrcVar(hdlVar);
	CatchError
}



/*!
	The constructor.
*/
inline Var::Var(Hdl const hdlSys) : Term(hdlSys),
		#if DnwdVarMapFunc
			#if DnwdMapFuncVar == MfvVarArrayFunc
				mFuncHdlSqns(Null),
			#elif DnwdMapFuncVar == MfvVarHashFunc
				mFuncHdlSqns(Null),
			#endif
		#endif
		#if CheckError
		mExecAsgnClk(NotClk), mSimulAsgnClk(NotClk),
		#endif//CheckError
		mDynaUpdtLink(InvLnk)
{
	WatchError
	setTermGen(Tv);
	CatchError
}



/*!
	The destructor.
*/
inline Var::~Var()
{
	WatchError
	#if DnwdVarMapFunc
		#if DnwdMapFuncVar == MfvVarArrayFunc
			if (mFuncHdlSqns) delete mFuncHdlSqns;
		#elif DnwdMapFuncVar == MfvVarHashFunc
			if (mFuncHdlSqns) delete mFuncHdlSqns;
		#endif
	#endif
	CatchError
}


/*!
	Define a variable in the sys.
*/
inline Hdl Var::defSysVar()
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	return mTermSys.defVar(this);
	CatchError
}



#if CheckError
/*!
	Whether the execution assigment clock has changed?
*/
inline Bll Var::chgdExecAsgnClk() const
{
	WatchError
	return mExecAsgnClk < mTermSys.ExecAsgnClk();
	CatchError
}
#endif//CheckError



#if CheckError
/*!
	Whether the simulation assignment clock has changed?
*/
inline Bll Var::chgdSimulAsgnClk() const
{
	WatchError
	return mSimulAsgnClk < mTermSys.SimulAsgnClk();
	CatchError
}
#endif//CheckError



#if CheckError
/*!
	Synchronize the execution assignment clock.
*/
inline void Var::syncExecAsgnClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);

	if (mExecAsgnClk < InvClk) mExecAsgnClk = NotClk;
	CatchError
}
#endif//CheckError



#if CheckError
/*!
	Synchronize the simulation assignment clock.
*/
inline void Var::syncSimulAsgnClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);

	if (mSimulAsgnClk < InvClk) mSimulAsgnClk = NotClk;
	CatchError
}
#endif//CheckError



#if CheckError
/*!
	Update the exec assignment clock
*/
inline void Var::updtExecAsgnClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(!chgdExecAsgnClk(), eExecAsgnClkNotChgd);

	mExecAsgnClk = mTermSys.ExecAsgnClk();
	CatchError
}
#endif//CheckError




#if CheckError
/*!
	Update the simul assignment clock.
*/
inline void Var::updtSimulAsgnClk()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(mTermSys.chkExecMode(NullComp), eSysUninit);
	Warn(!chgdSimulAsgnClk(), eSimulAsgnClkNotChgd);

	mSimulAsgnClk = mTermSys.SimulAsgnClk();
	CatchError
}
#endif//CheckError




/*!
	Return the dynamic update link.
*/
inline Lnk Var::DynaUpdtLink() const
{
	WatchError
	return mDynaUpdtLink;
	CatchError
}



/*!
	Set the dynamic update link.
*/
inline void Var::setDynaUpdtLink(Lnk const theLink)
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);

	mDynaUpdtLink = theLink;
	CatchError
}



/*!
	Return the locking status of the variable.
*/
inline Bll Var::locked() const
{
	WatchError
	return mExecClk == IdfClk;
	CatchError
}



/*!
	Set the locking status of the variable.
*/
inline void Var::lock(Bll const SetNotUnset)
{
	WatchError
	Warn(mTermSys.mskExecMode(AsgnMode), eExecAsgnMode);
	mExecClk = mSimulClk = SetNotUnset ? IdfClk : NotClk;
	CatchError
}



/*!
	Run preprocessing for anew execution.
*/
inline void Var::runPreExecAnew()
{
	WatchError
	Warn(!mTermSys.chkExecMode(AnewAsgn), eNotExecAnewAsgn);
	Warn(chgdExecAsgnClk(), eExecAsgnClkChgd);
	Warn(locked(), eVarLocked);

	updtExecClk();
	CatchError
}




/*!
	Run preprocessing for incremental execution.
*/
inline void Var::runPreExecIncr()
{
	WatchError
	Warn(!mTermSys.mskExecMode(IncrAsgn), eNotExecIncrAsgn);
	Warn(chgdExecAsgnClk(), eExecAsgnClkChgd);
	Warn(locked(), eVarLocked);

	updtExecClk();
	CatchError
}




/*!
	Run preprocessing for anew simulation.
*/
inline void Var::runPreSimulAnew()
{
	WatchError
	Warn(!mTermSys.chkSimulMode(AnewAsgn), eNotSimulAnewAsgn);
	Warn(chgdSimulAsgnClk(), eSimulAsgnClkChgd);
	Warn(locked(), eVarLocked);

	updtSimulClk();
	CatchError
}




/*!
	Run preprocessing for incremental simulation.
*/
inline void Var::runPreSimulIncr()
{
	WatchError
	Warn(!mTermSys.mskSimulMode(IncrAsgn), eNotSimulIncrAsgn);
	Warn(chgdSimulAsgnClk(), eSimulAsgnClkChgd);
	Warn(locked(), eVarLocked);

	updtSimulClk();
	CatchError
}




/*!
	Calculate the hash value.
*/
inline Hvl Var::calcTermHvl() const
{
	WatchError
	return mixHash(calcHash(this->TermCls), calcHash(this));
	CatchError
}



/*!
	Check equality of two terms.
*/
inline Bll Var::equate(Term const & theTerm) const
{
	WatchError
	return theTerm.TermCls == this->TermCls && this == &theTerm;
	CatchError
}



#if DnwdVarMapFunc
/*!
	Find sqn for a function.
*/
inline Sqn Var::findFuncSqn(Hdl const hdlFunc) const
{
	#if DnwdMapFuncVar == MfvVarArrayFunc
		return mFuncHdlSqns->item(hdlFunc);
	#elif DnwdMapFuncVar == MfvVarHashFunc
		Itr tItr = mFuncHdlSqns->findItr(hdlFunc);
		if (tItr == InvItr)
			return InvSqn;
		else
			return mFuncHdlSqns->item(tItr);
	#else
		#error Undefined function variable mapping.
	#endif
}
#endif


#if DnwdVarMapFunc
/*!
	Set function handle sqn mapping.
*/
inline void Var::setFuncHdlSqn(Hdl const hdlFunc, Sqn const sqnVar)
{
	#if DnwdMapFuncVar == MfvVarArrayFunc
		ccast<b1<Sqn, kmm> *>(mFuncHdlSqns)->item(hdlFunc) = sqnVar;
	#elif DnwdMapFuncVar == MfvVarHashFunc
		ccast<hm<Hdl,Sqn, xmmh> *>(mFuncHdlSqns)->insertMem(hdlFunc, sqnVar);
	#else
		#error Undefined function variable mapping.
	#endif
}
#endif



/*!
	Adjust memory allocation automatically.
*/
inline void Var::adjustMemAuto()
{
	WatchError
	#if DnwdVarMapFunc
		#if DnwdMapFuncVar == MfvVarArrayFunc
		ccast<b1<Sqn, kmm> *>(mFuncHdlSqns)->adjustMemAuto();
		#elif DnwdMapFuncVar == MfvVarHashFunc
		ccast<hm<Hdl,Sqn, xmmh> *>(mFuncHdlSqns)->adjustMemAuto();
		#else
			#error Undefined function variable mapping.
		#endif
	#endif
	Term::adjustMemAuto();
	CatchError
}


closeKangarooSpace


#endif//VarHppIncluded

