/*!
	@file cbls/msg.hpp
	@brief The header file for message texts.
	@details This the heaer file for message texts.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 01.12.2011 QRL NICTA www.nicta.com.au
*/



#ifndef CblsMsgHppIncluded
#define CblsMsgHppIncluded



// Data types

#define eTypeMismatch "Data types mismatch."


// Handle

#define eHandleBeyondLimit "Handle beyond limit."
#define eInvalidHandle "Invalid handle encountered."

//	Token

#define eTokenBeyondLimit "Token beyond limit."
#define eInvalidToken	"Invalid token encountered."


// Type

#define eTypeBeyondLimit "Type beyond limit."
#define eInvalidType "Invalid type encountered."



// Index
#define eIndexMismatch	"Array index mismatch."


// Deferments

#define eUndefUndoArgs 	"Undo arguments not defined."
#define eUndefHintUndo	  "Hint undo not defined."
#define eUndefEvalUndo 	  "Eval undo not defined."


//	Invalids
//
//#define eInvPrm			"Invalid parameter encountered."


//	Links
#define eInvalidLink		"Invalid link encountered."


//	Arguments

#define eInvalidArgument	"Invalid argument encountered."


//	Specification

#define eInvalidSpec		"Invalid specification found."



//	Stratification
#define eWrongGen		"Wrong genous encountered."
#define eWrongTyp 		"Wrong type encountered."
#define eWrongCat		"Wrong category encountered."
#define eWrongCls		"Wrong class encountered."

#define eNilCat			"Nil category encountered."
#define eNilTyp			"Nil type encountered."
#define eNilCls			"Nil class encountered."


//// Range

#define eRangeDefn		"Invalid range defintion."
#define eOutOfRange		"Value out of range."


// Domain

#define eDomainDefn		"Invalid domain definition."
#define eOutOfDomain	"Value out of domain."
#define eDomainNotUpdatable	"Domain not updatable."

// Variables

#define eRandVarSelectLoop 	"Too many iterations in random variable selection loop."
#define eMoreVarsThanAvail	"More variables requested than available."
#define eNoVariableDefined	"No variables defined."
#define eNotEnoughPairVars	"Not enough variables to form full pairs."
#define eNotVarPairAscend	"Variable pair not in ascending order."
#define eUndefUpdateDomain	"Update domain not defined."
#define eDefVariableFirst	"Variables not defined before functions or constants."
#define eDontCareFuncVarSqn "Function does not care variable sequent mapping."

// OOP

#define eUndefDuplicator "Duplicator not defined."
#define eUndefAssigner 	"Assigner not defined."



// Math

#define eStepSize 		"The step size must be positive."

// Swap

#define eValuesForSwap	"No values required in swapping."
#define eOddSwapVars	"Swap variable count is odd."
#define eFewerSwapVars	"Not enough variables for swapping."


// Terms

#define eTermGenUndefined "Term genus undefined,"
#define eTermNotGrounded "Term not grounded."
#define eTermNotConstant "Term not a constant."
#define eTermNotVariable "Term not a variable."
#define eTermNotFunction  "Term not a function."
#define eTermNotUpdatable "Term not updatable."
#define eTermNotComputable "Term not computable."
#define eTermNotRequired  "Term not required."
#define eTermNotEnforced  "Term not enforced."
#define eTermNotDefered   "Term not defered."
#define eTermUpdateBeforeGeun "Set term genus before updatability."


// Selectors

#define eSelcNotActive 			"Selector not active."
#define eSelcNotExecReady 		"Selector not exec ready."
#define eSelcHoldsNoValue		"Selector holds no values."
#define eSelcMoreValsThanVars 	"Selector has more values than variables."
#define eNoVarsSelected			"No variables selected."
#define eSelcVarCount(Count)	"Selector variable count not " << castN(Count)
#define eNoVarsForSelection		"No variables for selection."
#define eDuplicateSelectors		"Duplicate selector encountered."

// Compatibility

#define eVarsNotDifferent	"Variables not different."
#define eVarsNotIdentical	"Variables not identical."
#define eVarsNotSwappable	"Variable values not swappable."
#define eValNotAssignable	"Variable's value not assignable."

// Computation

#define eUndefExecAnew  "Anew execution not defined."
#define eUndefExecIncr  "Incremental execution not defined."
#define eUndefSimulAnew "Anew simulation not defined."
#define eUndefSimulIncr "Incremental simulation not defined."
#define eUndefExecBklg	"Backlog execution not defined."
#define eUndefEmulBklg	"Backlog emulation not defined."

// Data

#define eUndefValueType "Value type udefined."
#define eUndefMetricType "Metric type undefined."
#define eUndefValueHdl "Value handle undefined."
#define eUndefMetricHdl "Metric handle undefined."
#define eUndefEvalMinLoc "Eval min handle undefined."
#define eUndefEvalMaxLoc "Eval max handle undefined."
#define eUndefHinMinLoc "Hint min handle undefined."
#define eUndefHintMaxLoc "Hint max handle undefined."


//	Clocks

#define eSimulAsgnClkChgd "Simulation assignment clock changed."
#define eExecAsgnClkChgd "Execution assignment clock changed."

#define eSimulAsgnClkNotChgd "Simulation assignment clock not changed."
#define eExecAsgnClkNotChgd "Execution assignment clock not changed."

#define eSimulClkNotChgd "Simulation clock not changed."
#define eExecClkNotChgd "Execution clock not changed."
#define eEmulClkNotChgd "Emulation clock not changed."


// Modes

#define eSysUninit "Sys uninitialised yet."
#define eSysNotUninit "Sys not uninitialised."

#define eNotExecAnewAsgn "Not anew execution assignment mode."
#define eNotExecAnewProp "Not anew execution propagation mode."
#define eNotSimulAnewAsgn "Not anew simulation assignment mode."
#define eNotSimulAnewProp "Not anew simulation propagation mode."

#define eNotExecIncrAsgn "Not incremental execution assignment mode."
#define eNotExecIncrProp "Not incremental execution propagation mode."
#define eNotSimulIncrAsgn "Not incremental simulation assignment mode."
#define eNotSimulIncrProp "Not incremental simulation propagation mode."

#define eNotExecIncrMode "Not incremental execution mode."
#define eNotExecAnewMode "Not anew execution mode."
#define eNotSimulIncrMode "Not incremental simulation mode."
#define eNotSimulAnewMode "Not anew simulation mode."

#define eNotExecAsgnMode "Not execution assignment mode."
#define eNotSimulAsgnMode "Not simulation assignment mode."
#define eNotExecPropMode "Not execution propagation mode."
#define eNotSimulPropMode "Not simulation propagation mode."

#define eExecAsgnMode "Execution assignment mode found."
#define eSimulModeNull "Simulation mode is null."

// Assignments

#define eMultiAsgnVars		"Multiple assignment variables found."
#define eDuplicateAsgnVars "Duplicate assignment variables found."
#define eNoExecAsgnVars	"No execution assignment variables."
#define eNotChgdCandVars "Candidate assignment variables not changed."
#define eNotChgdFixedVars "Simulation fixed assignment variables not changed."
#define eNotChgdFlexiVars "Simulation flexible assignment variables not changed."

#define eFlexiIndexMismatch "Flexi index mismatch."
#define eFixedVarsNotLocked "Fixed labels are not locked."

// Run Modes
#define eSetExecAsgnMode "Execution assignment mode after another assignment mode."
#define eSetExecPropMode "Execution propagation mode after inappropriate assignment mode."
#define eSetSimulAsgnMode "Simulation assignment mode after another assignment mode."
#define eSetSimulPropMode "Simulation propagation mode after inappropriate assignment mode."


// Tabu
#define eTabuNotActive "Tabu not active."
#define eUndefTabuCallback "Tabu callback undefined."
#define eUndefAutoTabu "Automatic tabu not defined."
#define eUndefTabuEffect "Compute tabu effect not defined."
#define eTabuInconsistent "Inconsistent tabu found."
#define eTabuLengthLimit "Tabu length beyond given limit."

//	Lock
#define eVarLocked 		"Variable appears to be locked."
#define eUndefLockEffect "Compute lock effect not defined."


// Parameters
#define eEvenParamsRequired					"An even number of parameters required."
#define eParamCount1(Count)					"Param count not " << castN(Count)
#define eParamCount2(MinCount, MaxCount) 	"Param count not in [" << castN(MinCount) << ", " << castN(MaxCount) << "]"


//	Arguments
#define eUndefArgs "Arguments not defined."


//	Schedule Queue
#define eUnknownScheduleQueue "Unknown schedule queue encountered."


#endif // CblsMsgHppIncluded
