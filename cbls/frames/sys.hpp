/*!
	@file sys.hpp
	@brief The prototype file for Sys class.
	@details This is the prototype file for Sys class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 16.11.2009 QRL NICTA www.nicta.com.au
	@see sys.cpp
*/



#ifndef SysHppIncluded
#define SysHppIncluded


#include "cbls/frames/dat.hpp"

#include "cbls/frames/mode.hh"
#include "cbls/frames/hint.hpp"
#include "cbls/frames/eval.hpp"
#include "cbls/frames/selc.hpp"
#include "cbls/frames/lock.hpp"
#include "cbls/frames/tabu.hpp"

#include "cbls/frames/pbs.tcc"
#include "cbls/frames/pbd.tcc"


openKangarooSpace


/*
	Forward declarations.
*/
class Term;
class Var;
class Const;
class Func;



/*!
	@class Sys
	@brief A class to represent systems.
	@details This class represents systems.
*/
class Sys
{
	public:

		Hdl const SysHdl;									//!< System handle.

		static Hdl def();									//!< Define a system.

		//! @name Access
		//! @{

		static Sys & refm(Hdl const hdlSys);				//!< Refer to a system.
		static Sys * ptrm(Hdl const hdlSys);				//!< Point to a system.
		static Sys const & refc(Hdl const hdlSys);			//!< Refer to a system.
		static Sys const * ptrc(Hdl const hdlSys);			//!< Point to a system.

		Term & refmTerm(Gen const genTerm, Hdl const hdlTerm);				//!< Refer to a term.
		Term * ptrmTerm(Gen const genTerm, Hdl const hdlTerm);				//!< Point to a term.
		Term const & refcTerm(Gen const genTerm, Hdl const hdlTerm) const;	//!< Refer to a term.
		Term const * ptrcTerm(Gen const genTerm, Hdl const hdlTerm) const;	//!< Point to a term.

		Selc & refmSelc(Hdl const hdlSelc);					//!< Refer to a selector.
		Var & refmVar(Hdl const hdlVar);					//!< Refer to a variable.
		Const & refmConst(Hdl const hdlConst);				//!< Refer to a constant.
		Func & refmFunc(Hdl const hdlFunc);					//!< Refer to a function.

		Selc const & refcSelc(Hdl const hdlSelc) const;		//!< Refer to a selector.
		Var const & refcVar(Hdl const hdlVar) const;		//!< Refer to a variable.
		Const const & refcConst(Hdl const hdlConst) const;	//!< Refer to a constant.
		Func const & refcFunc(Hdl const hdlFunc) const;		//!< Refer to a function.

		Selc * ptrmSelc(Hdl const hdlSelc);					//!< Point to a selector.
		Var * ptrmVar(Hdl const hdlVar);					//!< Point to a variable.
		Const * ptrmConst(Hdl const hdlConst);				//!< Point to a constant.
		Func * ptrmFunc(Hdl const hdlFunc);					//!< Point to a function.

		Selc const * ptrcSelc(Hdl const hdlSelc) const;		//!< Point to a selector.
		Var const * ptrcVar(Hdl const hdlVar) const;		//!< Point to a variable.
		Const const * ptrcConst(Hdl const hdlConst) const;	//!< Point to a constant.
		Func const * ptrcFunc(Hdl const hdlFunc) const;		//!< Point to a function.

		Eval & refmEval(Srl const srlType);					//!< Refer to an eval database.
		Eval * ptrmEval(Srl const srlType);					//!< Point to an eval database.
		Eval const & refcEval(Srl const srlType) const;		//!< Refer to an eval database.
		Eval const * ptrcEval(Srl const srlType) const;		//!< Point to an eval database.

		Hint & refmHint(Srl const srlType);					//!< Refer to a hint database.
		Hint * ptrmHint(Srl const srlType);					//!< Point to a hint database.
		Hint const & refcHint(Srl const srlType) const;		//!< Refer to a hint database.
		Hint const * ptrcHint(Srl const srlType) const;		//!< Point to a hint database.

		Tabu & refmTabu(Typ const typTabu);					//!< Refer to a tabu.
		Tabu * ptrmTabu(Typ const typTabu);					//!< Point to a tabu.
		Tabu const & refcTabu(Typ const typTabu) const;		//!< Refer to a tabu.
		Tabu const * ptrcTabu(Typ const typTabu) const;		//!< Point to a tabu.

		Lock & refmLock();									//!< Refer to the lock.
		Lock * ptrmLock();									//!< Point to the lock.
		Lock const & refcLock() const;						//!< Refer to the lock.
		Lock const * ptrcLock() const;						//!< Point to the lock.

		//! @}

		#if CompDnwd
		//! @name Settings
		//! @{

		#if ExecDnwdMultiCand
			Bll const MultiCandExec;				//!< Execution requires candidate multiple variable support.
			void setMultiCandExec();				//!< Set support for multiple variable execution candidate support.
		#endif
		#if SimulDnwdMultiFixed
			Bll const MultiFixedSimul;				//!< Simulation requires fixed multiple variable support.
			void setMultiFixedSimul();				//!< Set support for multiple variable fixed simulation support.
		#endif
		#if SimulDnwdMultiFlexi
			Bll const MultiFlexiSimul;				//!< Simulation requires flexible multiple variable support.
			void setMultiFlexiSimul();				//!< Set support for multiple variable flexible simulation support.
		#endif

		//! @}
		#endif

		//! @name Clocks
		//! @{

		#if CompLazy
			Clk EmulClk() const;					//!< Get the emulation clock.
		#endif
		Clk ExecClk() const;						//!< Get the execution clock.
		Clk SimulClk() const;						//!< Get the simulation clock.
		Clk ExecAsgnClk() const;					//!< Get the execution assignment clock.
		Clk SimulAsgnClk() const;					//!< Get the simulation assignment clock.
		#if SimulDnwdFixed
			Clk SimulFixedClk() const;				//!< Get the fixed simulation clock.
		#endif
		#if SimulDnwdFlexi
			Clk SimulFlexiClk() const;				//!< Get the flexible simulation clock.
		#endif
		#if SimulDnwdCache
			Clk SimulCacheClk() const;				//!< Get the simulation cache clock.
		#endif

		//! @}

		//! @name Modes
		//! @{

		Srm ExecMode() const;						//!< Get execution mode.
		Srm SimulMode() const;						//!< Get simulation mode.

		void setExecMode(Srm const theSrm);			//!< Set the execution mode.
		void setSimulMode(Srm const theSrm);		//!< Set the simulation mode.

		Srs mskExecMode(Srb const theSrb) const;	//!< Mask the execution mode.
		Srs mskSimulMode(Srb const theSrb) const;	//!< Mask the simulation mode.

		Bll chkExecMode(Srm const theSrm) const;	//!< Check execution mode.
		Bll chkSimulMode(Srm const theSrm) const;	//!< Check Simulation mode.

		//! @}

		Dim varCount() const;									//!< Number of variables in the system.
		Dim funcCount() const;									//!< Number of functions in the system.


		//! @name Assignments
		//! @{

		ll<Hdl, xmm> const & ExecAsgnVars() const;				//!< Get the execution assignment variables.

		void setExecAsgnVars();									//!< Set all variables for execution assignment.
		void setExecAsgnVar1(Hdl const hdlVar);					//!< Set a variable for execution assignment.
		void setExecAsgnVars(Hdl const * hdlVars,
							Dim const VarCount);				//!< Set variables for execution assignment.
		void setExecAsgnVar2(Hdl const hdlVar1,
							Hdl const hdlVar2);					//!< Set two variables for execution assignment.

		lp<Hdl, xmm> const & SimulAsgnVars() const;				//!< Get the simulation assignment variables.
		#if SimulFixed
			Bll chgdSimulFixedVars() const;						//!< Whether fixed simulation variables changed?

			void setSimulFixedVar1(Hdl const hdlVar);			//!< Set a variable for simulation assignment.
			void setSimulFixedVars(Hdl const * hdlVars,
									Dim const VarCount);		//!< Set the variables for simulation assignment.
			void setSimulFixedVar2(Hdl const hdlVar1,
									Hdl const hdlVar2);			//!< Set a pair of variables for simulation assignment.
		#endif
		#if SimulFlexi
			Bll chgdSimulFlexiVars() const;						//!< Whether flexible simulation variables changed?
			void setSimulFlexiVar1(Hdl const hdlVar);			//!< Set a variable for simulation assignment.
			void setSimulFlexiVar2(Hdl const hdlVar1,
									Hdl const hdlVar2);			//!< Set a variable for simulation assignment.
			void setSimulFlexiVars(Hdl const * hdlVars,
									Dim const VarCount);		//!< Set a variable for simulation assignment.
		#endif
		#if SimulFixedFlexi
			void altSimulFlexiVar1(Idx const theIdx,
								Hdl const hdlVar);				//!< Alter a variable for simulation assignment.
			void altSimulFlexiVar2(Idx const theIdx,
								Hdl const hdlVar1,
								Hdl const hdlVar2);				//!< Alter a variable for simulation assignment.
			void altSimulFlexiVars(Idx const theIdx,
								Hdl const * hdlVars,
								Dim const VarCount);			//!< Alter a variable for simulation assignment.
		#endif

		//! @}

		//! @name Propagations
		//! @{

		void propagateExecAnew();								//!< Propagate anew execution at the system level.
		void propagateExecIncr();								//!< Propagate incremental execution at the system level.
		#if SimulUpwd
		void propagateSimulAnew();								//!< Propagate anew simulation at the system level.
		void propagateSimulIncr();								//!< Propagate incremental simulation at the system level.
		#endif//SimulUpwd

		//! @}

	public:

		//! @}
		//! @name Computation
		//! @{

		void initialiseVarsStatRand(Rnd & theRnd);			//!< Initialise all variables randomly using static domains.
		void initialiseVarsDynaRand(Rnd & theRnd);			//!< Initialise all variables randomly using dyanmic domains.
		void initialiseVarsWrap(Hdl const * hdlVars,
						Wrp const * theWraps);				//!< Initialise all variables with given wrapped values.
		void initialiseVarsWrapStatRand(
						Hdl const * hdlVars,
						Wrp const * theWraps,
						Dim const VarCount,
						Rnd & theRnd);						//!< Initialise give variables with given wrapped values, and all other variables randomly using static domains.
		void initialiseVarsWrapDynaRand(
						Hdl const * hdlVars,
						Wrp const * theWraps,
						Dim const VarCount,
						Rnd & theRnd);						//!< Initialise give variables with given wrapped values, and all other variables randomly using dynamic domains.

		void execAnewVarsStatRand(Rnd & theRnd);			//!< Execute anew all variables randomly using static domains.
		void execAnewVarsDynaRand(Rnd & theRnd);			//!< Execute anew all variables randomly using dyanmic domains.

		void execAnewRandVar1StatRand(Rnd & theRnd);		//!< Execute anew one variable with a random value from the static domain.
		void execAnewRandVar1DynaRand(Rnd & theRnd);		//!< Execute anew one variable with a random value from the dynamic domain.
		void execAnewRandVar2StatRand(Rnd & theRnd);		//!< Execute anew two variables with random values from the static domains.
		void execAnewRandVar2DynaRand(Rnd & theRnd);		//!< Execute anew two variables with random values from the dynamic domains.
		void execAnewRandVarsStatRand(Dim const VarCount,
									Rnd & theRnd);			//!< Execute anew variables with random values from the static domains.
		void execAnewRandVarsDynaRand(Dim const VarCount,
											Rnd & theRnd);	//!< Execute anew variables with random values from the dynamic domains.

		void execAnewVar1StatRand(Hdl const hdlVar,
										Rnd & theRnd);		//!< Execute anew one variable with a random value from the static domain.
		void execAnewVar1DynaRand(Hdl const hdlVar,
										Rnd & theRnd);		//!< Execute anew one variable with a random value from the dynamic domain.
		void execAnewVar2StatRand(Hdl const hdlVar1,
									Hdl const hdlVar2,
									Rnd & theRnd);			//!< Execute anew two variables with random values from the static domains.
		void execAnewVar2DynaRand(Hdl const hdlVar1,
									Hdl const hdlVar2,
										Rnd & theRnd);		//!< Execute anew two variables with random values from the dynamic domains.
		void execAnewVarsStatRand(Hdl const * hdlVars,
									Dim const VarCount,
									Rnd & theRnd);			//!< Execute anew variables with random values from the static domains.
		void execAnewVarsDynaRand(Hdl const * hdlVars,
									Dim const VarCount,
										Rnd & theRnd);		//!< Execute anew variables with random values from the dynamic domains.

		void execAnewVar1Wrap(Hdl const hdlVar,
							Wrp const & theWrap);			//!< Execute anew only the given variable with given wrapped value.
		void execAnewVar2Wrap(Hdl const hdlVar1,
							Hdl const hdlVar2,
							Wrp const & theWrap1,
							Wrp const & theWrap2);			//!< Execute anew only the given variables with given wrapped values.
		void execAnewVarsWrap(Hdl const * hdlVars,
						Wrp const * theWraps);				//!< Execute anew all variables with given wrapped values.
		void execAnewVarsWrap(Hdl const * hdlVars,
						Wrp const * theWraps,
						Dim const VarCount);				//!< Execute anew only the given variables with given wrapped values.

		void execIncrDiffRandVar1StatRand(Rnd & theRnd);	//!< Execute incremental difference of one variable with a random value from the static domain.
		void execIncrDiffRandVar1DynaRand(Rnd & theRnd);	//!< Execute incremental difference of one variable with a random value from the dynamic domain.
		void execIncrDiffRandVar2StatRand(Rnd & theRnd);	//!< Execute incremental differences of two variables with random values from the static domains.
		void execIncrDiffRandVar2DynaRand(Rnd & theRnd);	//!< Execute incremental differences of two variables with random values from the dynamic domains.
		void execIncrDiffRandVarsStatRand(Dim const VarCount,
											Rnd & theRnd);	//!< Execute incremental differences of variables with random values from the static domains.
		void execIncrDiffRandVarsDynaRand(Dim const VarCount,
											Rnd & theRnd);	//!< Execute incremental differences of variables with random values from the dynamic domains.

		void execIncrDiffVar1StatRand(Hdl const hdlVar,
										Rnd & theRnd);		//!< Execute incremental difference of one variable with a random value from the static domain.
		void execIncrDiffVar1DynaRand(Hdl const hdlVar,
										Rnd & theRnd);		//!< Execute incremental difference of one variable with a random value from the dynamic domain.
		void execIncrDiffVar2StatRand(Hdl const hdlVar1,
									Hdl const hdlVar2,
									Rnd & theRnd);			//!< Execute incremental differences of two variables with random values from the static domains.
		void execIncrDiffVar2DynaRand(Hdl const hdlVar1,
									Hdl const hdlVar2,
										Rnd & theRnd);		//!< Execute incremental difference of two variables with random values from the dynamic domains.
		void execIncrDiffVarsStatRand(Hdl const * hdlVars,
									Dim const VarCount,
									Rnd & theRnd);			//!< Execute incremental differences of variables with random values from the static domains.
		void execIncrDiffVarsDynaRand(Hdl const * hdlVars,
									Dim const VarCount,
										Rnd & theRnd);		//!< Execute incremental difference of variables with random values from the dynamic domains.

		void execIncrDiffVar1Wrap(Hdl const hdlVar,
							Wrp const & theWrap);			//!< Execute incrementally only the given variable with given wrapped value.
		void execIncrDiffVar2Wrap(Hdl const hdlVar1,
							Hdl const hdlVar2,
							Wrp const & theWrap1,
							Wrp const & theWrap2);			//!< Execute incrementally only the given variables with given wrapped values.
		void execIncrDiffVarsWrap(Hdl const * hdlVars,
							Wrp const * theWraps,
							Dim const VarCount);			//!< Execute incrementally only the given variables with given wrapped values.

		void execIncrSwapRandVar2(Rnd & theRnd);			//!< Execute incremental swap between a given variable and a random variable.
		void execIncrSwapRandVar1(Hdl const hdlVar,
							Rnd & theRnd);					//!< Execute incremental swap between a given variable and a random variable.
		void execIncrSwapVar2(Hdl const hdlVar1,
							Hdl const hdlVar2);				//!< Execute incremental swap of the given two variables.

		void simulAnewVarsWrap(Hdl const * hdlVars,
						Wrp const * theWraps);				//!< Simulate anew all variables with given wrapped values.
		void simulAnewVarsWrap(Hdl const * hdlVars,
						Wrp const * theWraps,
						Dim const VarCount);				//!< Simulate anew only the given variables with given wrapped values.

		void simulIncrDiffVar1Wrap(Hdl const hdlVar,
							Wrp const & theWrap);			//!< Simulate incrementally only the given variable with given wrapped value.
		#if SimulFixed
		void resimulIncrDiffVar1Wrap(Wrp const & theWrap);	//!< Resimulate incrementally only the given variable with given wrapped value.
		#endif
		void simulIncrDiffVar2Wrap(Hdl const hdlVar1,
							Hdl const hdlVar2,
							Wrp const & theWrap1,
							Wrp const & theWrap2);			//!< Simulate incrementally only the given variables with given wrapped values.
		#if SimulFixed
		void resimulIncrDiffVar2Wrap(Wrp const & theWrap1,
							Wrp const & theWrap2);			//!< Resimulate incrementally only the given variables with given wrapped values.
		#endif
		void simulIncrDiffVarsWrap(Hdl const * hdlVars,
							Wrp const * theWraps,
							Dim const VarCount);			//!< Simulate incrementally only the given variables with given wrapped values.
		#if SimulFixed
		void resimulIncrDiffVarsWrap(Wrp const * theWraps);	//!< Simulate incrementally only the given variables with given wrapped values.
		#endif
		void simulIncrSwapVar2(Hdl const hdlVar1,
							Hdl const hdlVar2);				//!< Simulate incremental swap of the given two variables.

		#if SimulFixedFlexi
		void simulIncrSplitSwapVar1(Hdl const hdlVar);		//!< Simulate incremental split swap with the given variable, which would form pair with the resimul variable.
		void resimulIncrSplitSwapVar1(Hdl const hdlVar);	//!< Resimulate incremental split swap with the given variable, which would form pair with the simul variable.
		#endif

		//! @}

		void adjustMemAuto();					//!< Adjust memory.
		virtual ~Sys();							//!< Destructor.

	protected:

		Sys();											//!< Constructor.
		Sys(Sys const & that);							//!< Duplicator.
		Sys const & operator = (Sys const & that);		//!< Assigner.

		static pbd<Sys,xmm> & SysBase();				//!< Return system collection.

	protected:

		friend class Term;		//!< Access def/ref/ptr terms.
		friend class Func;		//!< Access def/ref/ptr functions.
		friend class Var;		//!< Access def/ref/ptr variables.
		friend class Const;		//!< Access def/ref/ptr constants.
		friend class Selc;		//!< Access def/ref/ptr selectors.
		friend class Eval;		//!< Access def/ref/ptr evals.
		friend class Hint;		//!< Access def/ref/ptr hints.
		friend class Lock;		//!< Access def/ref/ptr locks.
		friend class Tabu;		//!< Access def/ref/ptr tabu.

		enum
		{
			mDfltTbls = 16		//!< Default number of tables.
		};

		/*!
			@class thash
			@brief A class to represent dereferenced hash for terms.
			@details This class represents dereferenced hash for terms.
		*/
		class thash
		{
			public:
				static Hvl iof(Term const * theTerm);	//!< Calculate hash value.
		};

		/*!
			@class tequal
			@brief A class to represent dereferenced equal for terms.
			@details This class represents dereferenced equal for terms.
		*/
		class tequal
		{
			public:
				static Bll iof(Term const * Left, Term const * Right);	//!< Equal operator.
		};

		/*!
			@class shash
			@brief A class to represent dereferenced hash for selectors.
			@details This class represents dereferenced hash for selectors.
		*/
		class shash
		{
			public:
				static Hvl iof(Selc const * theSelc);	//!< Calculate hash value.
		};

		/*!
			@class sequal
			@brief A class to represent dereferenced equal for selectors.
			@details This class represents dereferenced equal for selectors.
		*/
		class sequal
		{
			public:
				static Bll iof(Selc const * Left, Selc const * Right);	//!< Equal operator.
		};

		//! @name Clocks
		//! @{

		void tickExecClk();				//!< Tick the execution clock.
		void tickSimulClk();			//!< Tick the simulation clock.
		void tickExecAsgnClk();			//!< Tick the execution assignment clock.
		void tickSimulAsgnClk();		//!< Tick the simulation assignment clock.
		#if SimulDnwdFixed
			void updtSimulFixedClk();	//!< Update the simulation fixed clock.
		#endif
		#if SimulDnwdFlexi
			void updtSimulFlexiClk();	//!< Update the simulation flexi clock.
		#endif
		#if SimulDnwdCache
			void tickSimulCacheClk();	//!< Tick the simulation cache clock.
		#endif

		//! @}

		void setupComputation();		//!< Set up for system computation.
		void initPropagation();			//!< Initial propagation.

		#if ExecUpwd
			void scheduleExecQueue(Func * theFunc);	//!< Schedule for execution.
		#endif
		#if SimulUpwd
			void scheduleSimulQueue(Func * theFunc);//!< Schedule for simulation.
		#endif
		#if CompLazyHalf
			void setFuncRequired(Func * theFunc,
								Bll const Require);			//!< Set a required function.
			void setVarUpdateRequired(Var * theVar,
								Bll const Update);			//!< Set a dynamic variable update.
			Bll VarUpdateRequired(Var const * theVar);		//!< Whether var update is requried.
		#endif
		//! @name Definitions
		//! @{

		void defRoot(Func * theFunc);		//!< Define a root.
		Hdl defConst(Const * theConst);		//!< Define a constant.
		Hdl defVar(Var * theVar);			//!< Define a variable.
		Hdl defFunc(Func * theFunc);		//!< Define a function.

		Hdl defSelc(Selc * theSelc);		//!< Define a selector.
		Bll defEval(Eval * theEval);		//!< Define an eval database.
		Bll defHint(Hint * theHint);		//!< Define a hint database.
		Bll defTabu(Tabu * theTabu);		//!< Define a tabu database.

		//! @}

	protected:

		Srm mExecMode;			//!< Execution mode.
		Srm mSimulMode;			//!< Simulation mode.

		//! @name Clocks
		//! @{

		Clk mExecClk;			//!< Execution clock.
		Clk mSimulClk;			//!< Simulation clock.
		Clk mExecAsgnClk;		//!< Execution assignment clock.
		Clk mSimulAsgnClk;		//!< Simulation assignment clock.
		#if SimulDnwdFixed
			Clk mSimulFixedClk;	//!< Simulation fixed clock.
		#endif
		#if SimulDnwdFlexi
			Clk mSimulFlexiClk;	//!< Simulation flexi clock.
		#endif
		#if SimulDnwdCache
			Clk mSimulCacheClk;	//!< Simulation cache clock.
		#endif

		//! @}

		//! @name Terms
		//! @{

		hs<Term *, xmmh, thash, tequal> mTermSet;			//!< Check uniquenes.
		b1<Const *, xmm> mConstBlk;							//!< Constant terms.
		b1<Var *, xmm> mVarBlk;								//!< Variable terms.
		b1<Var *, xmm> mDynUpdtVars;						//!< Dynamically updatable vars.
		#if CompLazyHalf
		lu<Itr, xmm> mReqUpdtVars;							//!< Required updatable vars.
		#endif
		b1<Func *, xmm> mFuncBlk;							//!< Function terms.
		b1<Func *, xmm> mRootFuncs;							//!< Holds the root functions.
		#if CompLazyHalf
			b1<Func *, xmm> mReqFuncs;						//!< Holds the required functions.
		#endif
		#if CompUpwd
		Lvl mMaxFuncLvl;									//!< Maximum functional level.
		#endif

		//! @}

		//! @name Scheduling
		//! @{

		#if ExecUpwd
			#if (ScheduleQueue == SchQsIterAllLvls)
				b1<Bll,xmm> mBlkExecFuncs;					//!< Label of execution functions.
				rl< b1<Hdl,xmm>,xmm > mRckExecFuncs;		//!< Rack of execution functions.
			#elif (ScheduleQueue == SchQsStdHeapLvls)
				b1<Bll,xmm> mBlkExecFuncs;					//!< Label of execution functions.
				rl< b1<Hdl,xmm>,xmm > mRckExecFuncs;		//!< Rack of execution functions.
				qh<Lvl,gt<Lvl>,xmm> mHipExecFuncs;			//!< Heap of execution functions.
			#elif (ScheduleQueue == SchQsAltHeapLvls)
				b1<Bll,xmm> mBlkExecFuncs;					//!< Label of execution functions.
				rl< b1<Hdl,xmm>, xmm > mRckExecFuncs;		//!< Rack of execution functions.
				qhf<Lvl,Lvl,gt<Lvl>,xmm > mHipExecFuncs;	//!< Heap of execution functions.
			#elif (ScheduleQueue == SchStdHeapLvls)
				b1<Bll,xmm> mBlkExecFuncs;					//!< Label of execution functions.
				qh<t2a<Lvl,Hdl>,
					gt<t2a<Lvl,Hdl> >, xmm > mHipExecFuncs;	//!< Heap of execution functions.
			#elif (ScheduleQueue == SchStdHeapHdls)
				b1<Bll,xmm> mBlkExecFuncs;					//!< Label of execution functions.
				qh<Hdl,gt<Hdl>,xmm> mHipExecFuncs;			//!< Heap of execution functions.
			#elif (ScheduleQueue == SchAltHeapLvls)
				qhf<Lvl,Hdl,gt<Lvl>,xmm > mHipExecFuncs;	//!< Heap of execution functions.
			#elif (ScheduleQueue == SchAltHeapHdls)
				qhf<Hdl,Hdl,gt<Hdl>,xmm > mHipExecFuncs;	//!< Heap of execution functions.
			#else
				#error eUnknownScheduleQueue
			#endif
		#endif
		#if SimulUpwd
			#if (ScheduleQueue == SchQsIterAllLvls)
				b1<Bll, xmm> mBlkSimulFuncs;				//!< Label of simulation functions.
				rl< b1<Hdl, xmm>, xmm > mRckSimulFuncs;		//!< Rack of simulation functions.
			#elif (ScheduleQueue == SchQsStdHeapLvls)
				b1<Bll, xmm> mBlkSimulFuncs;				//!< Label of simulation functions.
				rl< b1<Hdl, xmm>, xmm > mRckSimulFuncs;		//!< Rack of simulation functions.
				qh<Lvl,gt<Lvl>,xmm > mHipSimulFuncs;		//!< Heap of simulation functions.
			#elif (ScheduleQueue == SchQsAltHeapLvls)
				b1<Bll,xmm> mBlkSimulFuncs;					//!< Label of simulation functions.
				rl< b1<Hdl,xmm>,xmm > mRckSimulFuncs;		//!< Rack of simulation functions.
				qhf<Lvl,Lvl,gt<Lvl>,xmm > mHipSimulFuncs;	//!< Heap of simulation functions.
			#elif (ScheduleQueue == SchStdHeapLvls)
				b1<Bll,xmm> mBlkSimulFuncs;					//!< Label of simulation functions.
				qh<t2a<Lvl,Hdl>,
					gt<t2a<Lvl,Hdl> >,xmm> mHipSimulFuncs;	//!< Heap of simulation functions.
			#elif (ScheduleQueue == SchStdHeapHdls)
				b1<Bll,xmm> mBlkSimulFuncs;					//!< Label of simulation functions.
				qh<Hdl,gt<Hdl>, xmm> mHipSimulFuncs;		//!< Heap of simulation functions.
			#elif (ScheduleQueue == SchAltHeapLvls)
				qhf<Lvl,Hdl,gt<Hdl>,xmm > mHipSimulFuncs;	//!< Heap of simulation functions.
			#elif (ScheduleQueue == SchAltHeapHdls)
				qhf<Hdl,Hdl,gt<Hdl>,xmm > mHipSimulFuncs;	//!< Heap of simulation functions.
			#else
				#error eUnknownScheduleQueue
			#endif
		#endif

		//! @}

		//! @name Assignments
		//! @{

		ll<Hdl, xmm> 	mExecAsgnVars;	//!< Execution assignment variables.
		lp<Hdl, xmm> 	mSimulAsgnVars;	//!< Simulation assignment variables.
		Lock			mSysLock;		//!< Holds the system lock.

		//! @}

		//! @name Database
		//! @{

		pbs<Eval> mEvalDbs;			//!< Eval databases.
		pbs<Hint> mHintDbs;			//!< Hint databases.
		pbs<Tabu> mTabuDbs;			//!< Tabu databases.

		//! @}

		//! @name Selectors
		//! @{

		b1<Selc *, xmm> mSelcBlk;					//!< Holds all selectors.
		hs<Selc *, xmmh, shash, sequal> mSelcSet;	//!< Check selectors' uniqueness.

		//! @}

		#if DnwdSysMapFuncVar

			//! @name Mapping
			//! @{

			#if DnwdMapFuncVar == MfvSysArray2VarFunc
			b2<Sqn> const * mMfvArray2VarFunc;
			#elif DnwdMapFuncVar == MfvSysArray2FuncVar
			b2<Sqn> const * mMfvArray2FuncVar;
			#elif DnwdMapFuncVar == MfvSysArrayVarHashFunc
			rl<hm<Hdl,Sqn, xmmh>, kmm> const * mMfvArrayVarHashFunc;
			#elif DnwdMapFuncVar == MfvSysArrayFuncHashVar
			rl<hm<Hdl,Sqn, xmmh>, kmm> const * mMfvArrayFuncHashVar;
			#else
				#error Undefined function variable mapping.
			#endif
			void setSqn(Hdl const hdlFunc, Hdl const hdlVar, Sqn const theSqn);
			Sqn const findSqn(Hdl const hdlFunc, Hdl const hdlVar) const;
			//! @}

		#endif // DnwdSysMapFuncVar
};



/*!
	Define a system in the sysbase.
*/
inline Hdl Sys::def()
{
	WatchError
	Hdl tHdl = SysBase().defPack(new Sys());
	ccast<Hdl &>(SysBase().refcPack(tHdl).SysHdl) = tHdl;
	return tHdl;
	CatchError
}



/*!
	Refer to a system in the sysbase.
*/
inline Sys & Sys::refm(Hdl const hdlSys)
{
	WatchError
	return SysBase().refmPack(hdlSys);
	CatchError
}


/*!
	Point to a system in the sysbase.
*/
inline Sys * Sys::ptrm(Hdl const hdlSys)
{
	WatchError
	return SysBase().ptrmPack(hdlSys);
	CatchError
}



/*!
	Refer to a system in the sysbase.
*/
inline Sys const & Sys::refc(Hdl const hdlSys)
{
	WatchError
	return SysBase().refcPack(hdlSys);
	CatchError
}


/*!
	Point to a system in the sysbase.
*/
inline Sys const * Sys::ptrc(Hdl const hdlSys)
{
	WatchError
	return SysBase().ptrcPack(hdlSys);
	CatchError
}


#if ExecDnwdMultiCand
/*!
	Set up exec candidate params.
*/
inline void Sys::setMultiCandExec()
{
	WatchError
	Warn(!chkExecMode(NullComp), eSysNotUninit);

	ccast<Bll &>(MultiCandExec) = true;
	CatchError
}
#endif//ExecDnwdMultiCand



#if SimulDnwdMultiFixed
/*!
	Set up simul fixed candidate params.
*/
inline void Sys::setMultiFixedSimul()
{
	WatchError
	Warn(!chkExecMode(NullComp), eSysNotUninit);

	ccast<Bll &>(MultiFixedSimul) = true;
	CatchError
}
#endif//SimulDnwdMultiFixed


#if SimulDnwdMultiFlexi
/*!
	Set up simul flexible candidate params.
*/
inline void Sys::setMultiFlexiSimul()
{
	WatchError
	Warn(!chkExecMode(NullComp), eSysNotUninit);

	ccast<Bll &>(MultiFlexiSimul) = true;
	CatchError
}
#endif//SimulDnwdMultiFlexi



#if CompLazy
/*!
	Return emulation clock.
*/
inline Clk Sys::EmulClk() const
{
	WatchError
	return mExecClk;
	CatchError
}
#endif



/*!
	Return execution clock.
*/
inline Clk Sys::ExecClk() const
{
	WatchError
	return mExecClk;
	CatchError
}



/*!
	Return simulation clock.
*/
inline Clk Sys::SimulClk() const
{
	WatchError
	return mSimulClk;
	CatchError
}


/*!
	Return execution assignment clock.
*/
inline Clk Sys::ExecAsgnClk() const
{
	WatchError
	return mExecAsgnClk;
	CatchError
}



/*!
	Return simulation assignment clock.
*/
inline Clk Sys::SimulAsgnClk() const
{
	WatchError
	return mSimulAsgnClk;
	CatchError
}


#if SimulDnwdFixed
/*!
	Return simulation fixed clock.
*/
inline Clk Sys::SimulFixedClk() const
{
	WatchError
	return mSimulFixedClk;
	CatchError
}
#endif



#if SimulDnwdFlexi
/*!
	Return simulation flexi clock.
*/
inline Clk Sys::SimulFlexiClk() const
{
	WatchError
	return mSimulFlexiClk;
	CatchError
}
#endif



#if SimulDnwdCache
/*!
	Return simulation cache clock.
*/
inline Clk Sys::SimulCacheClk() const
{
	WatchError
	return mSimulCacheClk;
	CatchError
}
#endif



/*!
	Return execution mode.
*/
inline Srm Sys::ExecMode() const
{
	WatchError
	return mExecMode;
	CatchError
}




/*!
	Return simulation mode.
*/
inline Srm Sys::SimulMode() const
{
	WatchError
	return mSimulMode;
	CatchError
}



/*!
	Check the execution mode.
*/
inline Bll Sys::chkExecMode(Srm const theSrm) const
{
	WatchError
	return mExecMode == theSrm;
	CatchError
}



/*!
	Check the simulation mode.
*/
inline Bll Sys::chkSimulMode(Srm const theSrm) const
{
	WatchError
	return mSimulMode == theSrm;
	CatchError
}



/*!
	Mask the execution mode.
*/
inline Srs Sys::mskExecMode(Srb const theSrb) const
{
	WatchError
	return mExecMode & theSrb;
	CatchError
}



/*!
	Mask the simulation mode.
*/
inline Srs Sys::mskSimulMode(Srb const theSrb) const
{
	WatchError
	return mSimulMode & theSrb;
	CatchError
}



/*!
	Set the execution mode.
*/
inline void Sys::setExecMode(Srm const theSrm)
{
	WatchError
	if (theSrm & AsgnMode)
	{
		Warn(mExecMode & AsgnMode, eSetExecAsgnMode);
		Warn((theSrm & IncrMode) && (mExecMode == NullComp), eSysUninit);

		tickExecClk();
	}

	#if CheckError
		else if (theSrm & PropMode)
		{
			Warn(theSrm != (mExecMode << 1), eSetExecPropMode);
			Warn((theSrm & SwapMode) && mExecAsgnVars.tagCount() % 2, eOddSwapVars);
		}
	#endif//CheckError

	mExecMode = theSrm;
	mSimulMode = NullComp;	//	new simulation required.
	#if SimulDnwdCache
		tickSimulCacheClk();//	to invalidate caches.
	#endif
	CatchError
}



/*!
	Set the simulation mode.
*/
inline void Sys::setSimulMode(Srm const theSrm)
{
	WatchError
	if (theSrm & AsgnMode)
	{
		Warn(!(mExecMode & PropMode), eNotExecPropMode);
		Warn(mSimulMode & AsgnMode, eSetSimulAsgnMode);

		tickSimulClk();
	}

	#if CheckError
		else if (theSrm & PropMode)
		{
			Warn(theSrm != (mSimulMode << 1), eSetSimulPropMode);
			Warn((theSrm & SwapMode) && mSimulAsgnVars.tagCount() % 2, eOddSwapVars);
		}
	#endif//CheckError

	mSimulMode = theSrm;
	CatchError
}




/*!
	Return system variable count.
*/
inline Dim Sys::varCount() const
{
	WatchError
	return mVarBlk.itemCount();
	CatchError
}



/*!
	Return system function count.
*/
inline Dim Sys::funcCount() const
{
	WatchError
	return mFuncBlk.itemCount();
	CatchError
}




/*!
	Return execution assignment variables.
*/
inline ll<Hdl, xmm> const & Sys::ExecAsgnVars() const
{
	WatchError
	return mExecAsgnVars;
	CatchError
}



/*!
	Return simulation assignment variables.
*/
inline lp<Hdl, xmm> const & Sys::SimulAsgnVars() const
{
	WatchError
	return mSimulAsgnVars;
	CatchError
}



#if SimulDnwdFixed
/*!
	Update the assignment clock in the system.
*/
inline void Sys::updtSimulFixedClk()
{
	WatchError
	mSimulFixedClk = mSimulAsgnClk;
	CatchError
}
#endif



#if SimulDnwdFlexi
/*!
	Update the assignment clock in the system.
*/
inline void Sys::updtSimulFlexiClk()
{
	WatchError
	mSimulFlexiClk = mSimulAsgnClk;
	CatchError
}
#endif



#if SimulDnwdFixed
/*!
	Check whether simulation fixed variables changed.
*/
inline Bll Sys::chgdSimulFixedVars() const
{
	WatchError
	return mSimulFixedClk == mSimulAsgnClk;
	CatchError
}
#endif


#if SimulDnwdFlexi
/*!
	Check whether simulation flexible variables changed.
*/
inline Bll Sys::chgdSimulFlexiVars() const
{
	WatchError
	return mSimulFlexiClk == mSimulAsgnClk;
	CatchError
}
#endif



/*!
	Define an eval base in the system.
*/
inline Bll Sys::defEval(Eval * theEval)
{
	WatchError
	Warn(!chkExecMode(NullComp), eSysNotUninit);
	Warn(!theEval, eNullPointer);

	return mEvalDbs.defPack(theEval->TypeSrl, theEval);
	CatchError
}



/*!
	Define a hint base in the system.
*/
inline Bll Sys::defHint(Hint * theHint)
{
	WatchError
	Warn(!chkExecMode(NullComp), eSysNotUninit);
	Warn(!theHint, eNullPointer);

	return mHintDbs.defPack(theHint->TypeSrl, theHint);
	CatchError
}



/*!
	Define a tabu base in the system.
*/
inline Bll Sys::defTabu(Tabu * theTabu)
{
	WatchError
	Warn(!chkExecMode(NullComp), eSysNotUninit);
	Warn(!theTabu, eNullPointer);

	return mTabuDbs.defPack(theTabu->TabuTyp, theTabu);
	CatchError
}



/*!
	Return selector pointer.
*/
inline Selc * Sys::ptrmSelc(Hdl const hdlSelc)
{
	WatchError
	return mSelcBlk[hdlSelc];
	CatchError
}



/*!
	Return select reference.
*/
inline Selc & Sys::refmSelc(Hdl const hdlSelc)
{
	WatchError
	return *mSelcBlk[hdlSelc];
	CatchError
}



/*!
	Return selector pointer.
*/
inline Selc const * Sys::ptrcSelc(Hdl const hdlSelc) const
{
	WatchError
	return mSelcBlk[hdlSelc];
	CatchError
}



/*!
	Return select reference.
*/
inline Selc const & Sys::refcSelc(Hdl const hdlSelc) const
{
	WatchError
	return *mSelcBlk[hdlSelc];
	CatchError
}




/*!
	Refer to an eval dbf in the system.
*/
inline Eval & Sys::refmEval(Srl const srlType)
{
	WatchError
	return mEvalDbs.refmPack(srlType);
	CatchError
}




/*!
	Refer to an eval dbf in the system.
*/
inline Eval const & Sys::refcEval(Srl const srlType) const
{
	WatchError
	return mEvalDbs.refcPack(srlType);
	CatchError
}



/*!
	Pointer to an eval dbf in the system.
*/
inline Eval * Sys::ptrmEval(Srl const srlType)
{
	WatchError
	return mEvalDbs.ptrmPack(srlType);
	CatchError
}



/*!
	Pointer to an eval dbf in the system.
*/
inline Eval const * Sys::ptrcEval(Srl const srlType) const
{
	WatchError
	return mEvalDbs.ptrcPack(srlType);
	CatchError
}



/*!
	Refer to a hint dbf in the system.
*/
inline Hint & Sys::refmHint(Srl const srlType)
{
	WatchError
	return mHintDbs.refmPack(srlType);
	CatchError
}



/*!
	Refer to a hint dbf in the system.
*/
inline Hint const & Sys::refcHint(Srl const srlType) const
{
	WatchError
	return mHintDbs.refcPack(srlType);
	CatchError
}



/*!
	Pointer to a hint dbf in the system.
*/
inline Hint * Sys::ptrmHint(Srl const srlType)
{
	WatchError
	return mHintDbs.ptrmPack(srlType);
	CatchError
}



/*!
	Pointer to a hint dbf in the system.
*/
inline Hint const * Sys::ptrcHint(Srl const srlType) const
{
	WatchError
	return mHintDbs.ptrcPack(srlType);
	CatchError
}



/*!
	Return variable pointer.
*/
inline Var * Sys::ptrmVar(Hdl const hdlVar)
{
	WatchError
	return mVarBlk[hdlVar];
	CatchError
}



/*!
	Return variable reference.
*/
inline Var & Sys::refmVar(Hdl const hdlVar)
{
	WatchError
	return *mVarBlk[hdlVar];
	CatchError
}



/*!
	Return variable pointer.
*/
inline Var const * Sys::ptrcVar(Hdl const hdlVar) const
{
	WatchError
	return mVarBlk[hdlVar];
	CatchError
}



/*!
	Return variable reference.
*/
inline Var const & Sys::refcVar(Hdl const hdlVar) const
{
	WatchError
	return *mVarBlk[hdlVar];
	CatchError
}



/*!
	Return function pointer.
*/
inline Func * Sys::ptrmFunc(Hdl const hdlFunc)
{
	WatchError
	return mFuncBlk[hdlFunc];
	CatchError
}



/*!
	Return function reference.
*/
inline Func & Sys::refmFunc(Hdl const hdlFunc)
{
	WatchError
	return *mFuncBlk[hdlFunc];
	CatchError
}



/*!
	Return function pointer.
*/
inline Func const * Sys::ptrcFunc(Hdl const hdlFunc) const
{
	WatchError
	return mFuncBlk[hdlFunc];
	CatchError
}



/*!
	Return function reference.
*/
inline Func const & Sys::refcFunc(Hdl const hdlFunc) const
{
	WatchError
	return *mFuncBlk[hdlFunc];
	CatchError
}


/*!
	Return constant pointer.
*/
inline Const * Sys::ptrmConst(Hdl const hdlConst)
{
	WatchError
	return mConstBlk[hdlConst];
	CatchError
}



/*!
	Return constant reference.
*/
inline Const & Sys::refmConst(Hdl const hdlConst)
{
	WatchError
	return *mConstBlk[hdlConst];
	CatchError
}



/*!
	Return constant pointer.
*/
inline Const const * Sys::ptrcConst(Hdl const hdlConst) const
{
	WatchError
	return mConstBlk[hdlConst];
	CatchError
}



/*!
	Return constant reference.
*/
inline Const const & Sys::refcConst(Hdl const hdlConst) const
{
	WatchError
	return *mConstBlk[hdlConst];
	CatchError
}



/*!
	Return lock pointer.
*/
inline Lock * Sys::ptrmLock()
{
	WatchError
	return &mSysLock;
	CatchError
}



/*!
	Return lock reference.
*/
inline Lock & Sys::refmLock()
{
	WatchError
	return mSysLock;
	CatchError
}



/*!
	Return lock pointer.
*/
inline Lock const * Sys::ptrcLock() const
{
	WatchError
	return &mSysLock;
	CatchError
}



/*!
	Return lock reference.
*/
inline Lock const & Sys::refcLock() const
{
	WatchError
	return mSysLock;
	CatchError
}



/*!
	Refer to a tabu in the system.
*/
inline Tabu & Sys::refmTabu(Typ const typTabu)
{
	WatchError
	return mTabuDbs.refmPack(typTabu);
	CatchError
}




/*!
	Refer to a tabu in the system.
*/
inline Tabu const & Sys::refcTabu(Typ const typTabu) const
{
	WatchError
	return mTabuDbs.refcPack(typTabu);
	CatchError
}



/*!
	Pointer to a tabu in the system.
*/
inline Tabu * Sys::ptrmTabu(Typ const typTabu)
{
	WatchError
	return mTabuDbs.ptrmPack(typTabu);
	CatchError
}



/*!
	Pointer to a tabu in the system.
*/
inline Tabu const * Sys::ptrcTabu(Typ const typTabu) const
{
	WatchError
	return mTabuDbs.ptrcPack(typTabu);
	CatchError
}



closeKangarooSpace


#endif // SysHppIncluded
