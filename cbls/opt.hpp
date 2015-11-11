/*!
	@file cbls/opt.hpp
	@brief The header file to list the project options.
	@details The is the header file to list the project options.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 01.12.2011 QRL NICTA www.nicta.com.au
*/



#ifndef CblsOptHppIncluded
#define CblsOptHppIncluded



/*!
	@def PropagationAlgo
	@brief Specify propagation algorithm.
	@details Specifiy the propagation algorithm.
		0: HalfLazy Propagation, TopDown Execution, TopDown Simulation.
		1: Prompt Propagation, BottomUp Execution, BottomUp Simulation.
		2: Prompt Propagation, BottomUp Execution, TopDown Simulation.
		3: Prompt Propagation, TopDown Execution, BottomUp Simulation.
		4: Prompt Propagation, TopDown Execution, TopDown Simulation.
		5: FullLazy Propagation, TopDown Execution, TopDown Simulation.
 */
#define PropagationAlgo 0
#undef PropagationAlgo



#include "algorithm.option"
#ifndef PropagationAlgo
#define PropagationAlgo 0
#endif


/*!
	@def PrpLhEdSd
	@brief Propagation Mode: Lazy(Half), Exec(Dnwd), Simul(Dnwd)
	@details Propagation Mode: Lazy(Half), Exec(Dnwd), Simul(Dnwd)
*/
#define PrpLhEdSd 0
/*!
	@def PrpLoEuSu
	@brief Propagation Mode: Lazy(Off), Exec(Upwd), Simul(Upwd)
	@details Propagation Mode: Lazy(Off), Exec(Upwd), Simul(Upwd)
*/
#define PrpLoEuSu 1
/*!
	@def PrpLoEuSd
	@brief Propagation Mode: Lazy(Off), Exec(Upwd), Simul(Dnwd)
	@details Propagation Mode: Lazy(Off), Exec(Upwd), Simul(Dnwd)
*/
#define PrpLoEuSd 2
/*!
	@def PrpLoEdSu
	@brief Propagation Mode: Lazy(Off), Exec(Dnwd), Simul(Upwd)
	@details Propagation Mode: Lazy(Off), Exec(Dnwd), Simul(Upwd)
*/
#define PrpLoEdSu 3
/*!
	@def PrpLoEdSd
	@brief Propagation Mode: Lazy(Off), Exec(Dnwd), Simul(Dnwd)
	@details Propagation Mode: Lazy(Off), Exec(Dnwd), Simul(Dnwd)
*/
#define PrpLoEdSd 4
/*!
	@def PrpLfEdSd
	@brief Propagation Mode: Lazy(Full), Exec(Dnwd), Simul(Dnwd)
	@details Propagation Mode: Lazy(Full), Exec(Dnwd), Simul(Dnwd)
*/
#define PrpLfEdSd 5


/*!
  Propagation strategies
*/
#if (PropagationAlgo == PrpLoEuSu)
	#define CompLazy  false
	#define ExecDnwd  false
	#define SimulDnwd false
	#define PropagationType "Lazy(Off), Exec(Upwd), Simul(Upwd)"
#elif (PropagationAlgo == PrpLoEuSd)
	#define CompLazy  false
	#define ExecDnwd  false
	#define SimulDnwd true
	#define PropagationType "Lazy(Off), Exec(Upwd), Simul(Dnwd)"
#elif (PropagationAlgo == PrpLoEdSu)
	#define CompLazy  false
	#define ExecDnwd  true
	#define SimulDnwd false
	#define PropagationType "Lazy(Off), Exec(Dnwd), Simul(Upwd)"
#elif (PropagationAlgo == PrpLoEdSd)
	#define CompLazy  false
	#define ExecDnwd  true
	#define SimulDnwd true
	#define PropagationType "Lazy(Off), Exec(Dnwd), Simul(Dnwd)"
#elif (PropagationAlgo == PrpLfEdSd)
	#define CompLazy  true
	#define ExecDnwd  true
	#define SimulDnwd true
	#define CompLazyFull true
	#define PropagationType "Lazy(Full), Exec(Dnwd), Simul(Dnwd)"
#else	//if (PropagationAlgo == PrpLhEdSd)
	#define CompLazy  true
	#define ExecDnwd  true
	#define SimulDnwd true
	#define CompLazyHalf true
	#define PropagationType "Lazy(Half), Exec(Dnwd), Simul(Dnwd)"
#endif



/* The above part needs to be handled later. */



/*!
	Global parameters that affect the entire implementation. Setting the parameters
	with different values will result in different system having different performance
	levels. Some of the parameters have preferred values, some require experimentations.
*/


/*!
	@def CompLazy
	@brief Source code related to lazy computation
	@details Source code segment related to lazy computation.
*/

/*!
	@def ExecDnwd
	@brief Source code related to top down execution.
	@details Source code segment related to top down execution.
*/

/*!
	@def SimulDnwd
	@brief Source code related to top down simulation.
	@details Source code segment related to top down simulation.
*/

/*!
	@def CompLazyFull
	@brief Source code related to fully lazy computation.
	@details Source code segment related to fully lazy computation.
*/

/*!
	@def CompLazyHalf
	@brief Source code related to half lazy computation.
	@details Source code segment related to half lazy computation.
*/


/*!
	@def MfvVarHashFunc
	@brief Store the function-variable-sequent mapping at variables using hash on functions.
	@details Store the function-variable-sequent mapping at variables using hash on functions.
*/
#define MfvVarHashFunc			0
/*!
	@def MfvVarArrayFunc
	@brief Store the function-variable-sequent mapping at variables using array of functions.
	@details Store the function-variable-sequent mapping at variables using array of functions.
*/
#define MfvVarArrayFunc			1
/*!
	@def MfvFuncHashVar
	@brief Store the function-variable-sequent mapping at functions using hash on variables.
	@details Store the function-variable-sequent mapping at functions using hash on variables.
*/
#define MfvFuncHashVar 			2
/*!
	@def MfvFuncArrayVar
	@brief Store the function-variable-sequent mapping at functions using array of variables.
	@details Store the function-variable-sequent mapping at functions using array of variables.
*/
#define MfvFuncArrayVar			3
/*!
	@def MfvSysArray2VarFunc
	@brief Store the function-variable-sequent mapping at systems using 2d-array of variables by functions.
	@details Store the function-variable-sequent mapping at systems using 2d-array of variables by functions.
*/
#define MfvSysArray2VarFunc		4
/*!
	@def MfvSysArray2FuncVar
	@brief Store the function-variable-sequent mapping at systems using 2d-array of functions by variables.
	@details Store the function-variable-sequent mapping at systems using 2d-array of functions by variables.
*/
#define MfvSysArray2FuncVar		5
/*!
	@def MfvSysRackFuncVar
	@brief Store the function-variable-sequent mapping at systems using array on variables and hash on functions.
	@details Store the function-variable-sequent mapping at systems using array on variables and hash on functions.
*/
#define MfvSysArrayVarHashFunc		6
/*!
	@def MfvSysRackVarFunc
	@brief Store the function-variable-sequent mapping at systems using array on functions and hash on variables.
	@details Store the function-variable-sequent mapping at systems using array on functions and hash on variables.
*/
#define MfvSysArrayFuncHashVar		7



/*!
	@def DnwdMapFuncVar
	@brief Specify how to implement function variable sequent mapping in down-ward computation.
	@details Specify how to implement function variable sequent mapping in down-ward computation.
*/
#define DnwdMapFuncVar	0


/*!
	@def UpwdMapFuncVarArray
	@brief Specify whether function variable sequent mapping in up-ward computation is array-based or hash-based.
	@details Specify whether function variable sequent mapping in up-ward computation is array-based or hash-based.
*/
#define UpwdMapFuncVarArray	false



/*!
	@def VarStateArray
	@brief Use an array-based variable status instead of hash-based data structures.
	@details Use an array-based variable status instead of hash-based data structures.
		This option would use a memory-intensive sparse array to obtain speed.
		Not using this option means compact memory with slower computation speed.
*/
#define VarStateArray false


/*!
	@def ConsistentRandom
	@brief Use consistent random selection by using a costly sorting function.
	@details Use consistent random selection by using a costly sorting function.
		Even when a pseudo-random number generator is used, the ordering of the
		things to be selected could be assorted. This option ensures a canonical
		ordering of the things to be selected.
*/
#define ConsistentRandom false



/*!
	@name SchQsIterAllLvls
	@brief Array of queues, flag whether scheduled, iterate all possible levels.
	@details Array of queues, flag whether scheduled, iterate all possible levels.
*/
#define	SchQsIterAllLvls 0
/*!
	@name SchQsStdHeapLvls
	@brief Array of queues, flag whether scheduled, standard heap of levels.
	@details Array of queues, flag whether scheduled, standard heap of levels.
*/
#define	SchQsStdHeapLvls 1
/*!
	@name SchQsAltHeapLvls
	@brief Array of queues, flag whether scheduled, alternative heap of levels.
	@details Array of queues, flag whether scheduled, alternative heap of levels.
*/
#define	SchQsAltHeapLvls 2
/*!
	@name SchStdHeapLvls
	@brief Standard heap of levels of the functions scheduled.
	@details Standard heap of levels of the functions scheduled.
*/
#define	SchStdHeapLvls   3
/*!
	@name SchStdHeapTkns
	@brief Standard heap of handles of the functions scheduled.
	@details Standard heap of handles of the functions scheduled.
*/
#define	SchStdHeapHdls   4
/*!
	@name SchAltHeapLvls
	@brief Alternative heap of levels of the functions scheduled.
	@details Alternative heap of levels of the functions scheduled.
*/
#define	SchAltHeapLvls	 5
/*!
	@name SchAltHeapHdls
	@brief Alternative heap of handles of the functions scheduled.
	@details Alternative heap of handles of the functions scheduled.
*/
#define	SchAltHeapHdls	 6


/*!
	@def ScheduleQueue
	@brief Select the schedule queue for bottom-up computation.
	@details Select the schedule queue for bottom-up computation.
*/
#define ScheduleQueue 6	//SchQsIterAllLvls



/*!
	@def SimulFixed
	@brief Use fixed simulation for both top-down and bottom-up computation.
	@details Use fixed simulation for both top-down and bottom-up computation.
		Using this option in top-down mode enables caching undo computations.
*/
#define SimulFixed true



/*!
	@def SimulFixed
	@brief Use flexi simulation for both top-down and bottom-up computation.
	@details Use flexi simulation for both top-down and bottom-up computation.
*/
#define SimulFlexi true



/*!
	@def SelcSimulDflt
	@brief Use the appropriate simulation for the selectors.
	@details Use the appropriate simulation for the selectors.
*/
#define SelcSimulDflt  true



/*!
	@def SelcSimulFixed
	@brief Use the fixed simulation for the selectors.
	@details Use the fixed simulation for the selectors.
*/
#define SelcSimulFixed true



/*!
	@def SelcSimulDflt
	@brief Use the appropriate simulation at the system level.
	@details Use the appropriate simulation at the system level.
*/
#define SysSimulDflt  true



/*!
	@def SelcSimulFlexi
	@brief Use the flexi simulation at the system level.
	@details Use the flexi simulation at the system level.
*/
#define SysSimulFlexi true



/*!
	@def FuncFlexiClk
	@brief Use clocks in functions for flexible assignments in simulations.
	@details Use clocks in functions for flexible assignments in simulations.
		This option is just ornamental. It just introduces symmetries with
		clocks for fixed assignments inside a function. Nevertheless, turning
		the option on should slightly slow down top-down computations. The
		preferred setting is therefore false.
*/
#define FuncFlexiClk false



/*!
	@def ExecMultiCand
	@brief Multiple variables allowed in execution.
	@details Multiple variables allowed in execution
*/
#define ExecMultiCand true



/*!
	@def SimulMultiFixed
	@brief Multiple variables allowed in fixed simulation.
	@details Multiple variables allowed in fixed simulation.
*/
#define SimulMultiFixed true



/*!
	@def SimulMultiFlexi
	@brief Multiple variables allowed in flexi simulation.
	@details Multiple variables allowed in flexi simulation.
*/
#define SimulMultiFlexi true





/*	The following are the derived options. These are used for convenience. */



/*!
	@def ExecUpwd
	@brief Source code related to bottom up execution.
	@details Source code segment related to defered execution.
*/
#define ExecUpwd !ExecDnwd



/*!
	@def SimulUpwd
	@brief Source code related to bottom up simulation.
	@details Source code segment related to defered simulation.
*/
#define SimulUpwd !SimulDnwd



/*!
	@def CompDnwd
	@brief Source code related to top down computation.
	@details Source code segment related to top down computation.
*/
#define CompDnwd (ExecDnwd || SimulDnwd)



/*!
	@def CompUpwd
	@brief Source code related to bottom up computation.
	@details Source code segment related to bottom up computation.
*/
#define CompUpwd (ExecUpwd || SimulUpwd)



/* Determine CompLazyFull and CompLazyHalf options */
#ifndef CompLazyFull
	#define CompLazyFull false
#endif
#ifndef CompLazyHalf
	#define CompLazyHalf false
#endif



/*!
	@def ExecLazy
	@brief Source code related to lazy top down execution.
	@details Source code segment related to lazy top down execution.
*/
#define ExecLazy (ExecDnwd && CompLazy)



/*!
	@def SimulLazy
	@brief Source code related to lazy top down simulation.
	@details Source code segment related to lazy top down simulation.
*/
#define SimulLazy (SimulDnwd && CompLazy)



/*!
	@def ExecUpwdLazy
	@brief Source code related to bottom-up or lazy top-down execution.
	@details Source code segment related to bottom-up or lazy top-down execution.
*/
#define ExecUpwdLazy (ExecUpwd || ExecLazy)



/*!
	@def SimulFixedFlexi
	@brief Source code related to combined fixed and flexi simulation.
	@details Source code segment related to combined fixed and flexi simulation.
*/
#define SimulFixedFlexi (SimulFixed && SimulFlexi)



/*!
	@def SimulFixedOnly
	@brief Source code related to fixed simulation only.
	@details Source code segment related to fixed simulation only.
*/
#define SimulFixedOnly (SimulFixed && !SimulFlexi)



/*!
	@def SimulFlexiOnly
	@brief Source code related to flexi simulation only.
	@details Source code segment related to flexi simulation only.
*/
#define SimulFlexiOnly (!SimulFixed && SimulFlexi)



/*!
	@def SimulDnwdFixed
	@brief Source code related to top down fixed simulation.
	@details Source code segment related to top down fixed simulation.
*/
#define SimulDnwdFixed (SimulDnwd && SimulFixed)



/*!
	@def SimulDnwdFlexi
	@brief Source code related to top down flexi simulation.
	@details Source code segment related to top down flexi simulation.
*/
#define SimulDnwdFlexi (SimulDnwd && SimulFlexi)



/*!
	@def SimulDnwdCache
	@brief Source code related to top down simulation cache
	@details Source code segment related to top down simulation cache.
*/
#define SimulDnwdCache (SimulDnwd && (CompLazy || SimulFixed))



/*!
	@def SelcSimulFlexi
	@brief Source code related to flexi simulation in selectors.
	@details Source code segment related to flexi simulation in selectors.
*/
#define SelcSimulFlexi !SelcSimulFixed



/*!
	@def SysSimulFixed
	@brief Source code related to fixed simulation in systems.
	@details Source code segment related to fixed simulation in systems.
*/
#define SysSimulFixed !SysSimulFlexi



/*!
	@def ExecDnwdMultiCand
	@brief Multiple variables allowed in downward execution.
	@details Multiple variables allowed in downward execution
*/
#define ExecDnwdMultiCand (ExecDnwd && ExecMultiCand)



/*!
	@def SimulDnwdMultiFixed
	@brief Multiple variables allowed in downward fixed simulation.
	@details Multiple variables allowed in downward fixed simulation.
*/
#define SimulDnwdMultiFixed (SimulDnwdFixed && SimulMultiFixed)



/*!
	@def SimulDnwdMultiFlexi
	@brief Multiple variables allowed in downward flexi simulation.
	@details Multiple variables allowed in downward flexi simulation.
*/
#define SimulDnwdMultiFlexi (SimulDnwdFlexi && SimulMultiFlexi)



/*!
	@def DnwdVarMapFunc
	@brief Store function variable maps in variables in down-ward computation.
	@details Store function variable maps in variables in down-ward computation.
*/
#define DnwdVarMapFunc (CompDnwd && (DnwdMapFuncVar == MfvVarArrayFunc || DnwdMapFuncVar == MfvVarHashFunc))



/*!
	@def DnwdSysMapFuncVar
	@brief Store function variable maps in systems in down-ward computation.
	@details Store function variable maps in systems in down-ward computation.
*/
#define DnwdSysMapFuncVar (CompDnwd && (DnwdMapFuncVar == MfvSysArray2VarFunc || \
										DnwdMapFuncVar == MfvSysArray2FuncVar || \
										DnwdMapFuncVar == MfvSysArrayFuncHashVar || \
										DnwdMapFuncVar == MfvSysArrayVarHashFunc))

/*	Option compatibility checkings */


#if CompLazy && (!ExecDnwd || !SimulDnwd)
	#error CompLazy must require ExecDnwd and SimulDnwd.
#endif

#if CompLazy && (ExecUpwd || SimulUpwd)
	#error CompLazy not possible with ExecUpwd or SimulUpwd.
#endif

#if ExecDnwd && ExecUpwd
	#error Both ExecDnwd and ExecUpwd cannot be set.
#endif

#if !ExecDnwd && !ExecUpwd
	#error At least one of ExecDnwd or ExecUpwd must be set.
#endif

#if SimulDnwd && SimulUpwd
	#error Both SimulDnwd and SimulUpwd cannot be set.
#endif

#if !SimulDnwd && !SimulUpwd
	#error At least one of SimulDnwd or SimulUpwd must be set.
#endif

#if !SimulFixed && !SimulFlexi
	#error At least of one SimulFixed or SimulFlexi must be set.
#endif


#endif // CblsOptHppIncluded
