/*!
	@file cppl/msg.hpp
	@brief The header file to list various message texts.
	@details This the header file to list various message texts.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 01.01.2013 QRL NICTA www.nicta.com.au
*/



#ifndef CpplMsgHppIncluded
#define CpplMsgHppIncluded



//	Incomplete
#define eIncompleteCode "Incomplete code segment."


// Null

#define eNullPointer "Null pointer encountered."


// Memory

#define eMemoryAllocation 		"Memory allocation error."
#define eMemorySlotOccupied		"Memmory slot occupied."
#define eMemorySlotUnoccupied	"Unoccupied memory slot."
#define eAllocatedMemoryFull 	"Allocated memory full."
#define eOccupiedMemoryEmpty	"Occupied meory empty."
#define eInsuffMemoryAllocation "Insufficient memory allocation."
#define eUndefMemoryOperation 	"Undefined memory operation."
#define eUnsuitMemoryManager 	"Unsuitable memory manager."


// Dimension

#define eEmptyDimension	"Empty dimension encountered."
#define eNonEmptyDimension "Non-empty dimension encountered."
#define eDimensionMismatch "Mismatched dimension encountered."

// Size

#define eEmptySize	"Empty size encountered."
#define eNonEmptySize "Non-empty size encountered."
#define eSizeMismatch "Mismatched size encountered."

// Count

#define eEmptyCount	"Empty count encountered."
#define eNonEmptyCount "Non-empty count encountered."
#define eCountMismatch "Mismatched count encountered."


// Serial

#define eInvalidSerial "Invalid serial encountered."
#define eSerialBeyondLimit "Serial beyond allowed limit."
#define eTerminalSerial "Terminal serial encountered."


// Iterator

#define eIteratorBeyondLimit "Iterator beyond limit."
#define eInvalidIterator "Invalid iterator encountered."
#define eTerminalIterator "Terminal iterator encountered."


// Index

#define eIndexBeyondLimit "Index beyond limit."
#define eInvalidIndex "Invalid index encountered."


// Math

#define eMathLibrary "Math library error."
#define eModulusByZero "Modulus by zero."
#define eDivisionByZero	"Division by zero."
#define ePowerOfZero "Zero to the power non-positive."
#define eMathOverflow "Mathematical over flow."


// Range

#define eInvalidRange "Invalid range encountered."


// Parsing

#define eParseBoolean	"Invalid boolean value to be parsed."
#define eParseNatural	"Invalid natural number to be parsed."
#define eParseReal		"Invalid real number to be parsed."
#define eParseIntegral	"Invalid integral number to be parsed."


// Input-Output

#define ePipeInOut		"Operating System pipe read/write error."


// Keys

#define eKeyNotFound "Key not found."


//	Clocks

#define eClockConflict "Clock conflicts encountered."


//	Copy

#define eSelfCopy "Copying from self is not allowed."


//	Labels

#define eAlterFixedLabels "Fixed labels cannot be altered."


//	Navigation
#define eNavigationStep "Navigation step-size must be positive."



#endif // CpplMsgHppIncluded
