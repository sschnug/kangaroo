/*!
	@file cppl/opt.hpp
	@brief The header file to list the project options.
	@details The is the header file to list the project options.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 01.01.2013 QRL NICTA www.nicta.com.au
*/



#ifndef CpplOptHppIncluded
#define CpplOptHppIncluded



/*!
	Global parameters that affect the entire project. Setting these parameters with
	different values will result in different systems having different performance
	levels. Some of the parameters have preferred values, some require experimentations.
*/




/*!
	@def CheckError
	@brief Check run time errors.
	@details Check for run time errors. Time performance would degrade if the checkings
			are enforced. The regular assumption is that the user is rational and does
			everything as expected. Therefore, this parameter is normally set to false.
*/
#define CheckError false



/*!
	@def WatchCatchError
	@brief Watch and catch errors.
	@details Watch and catch errors. This macro enables functions
		to be surrounded by WatchError and CatchError. The former
		inserts 'try' and the latter inserts 'catch'. The latter
		also rethrows the caught error, appending the signature
		of the thrower function to the error message. The time
		performance of the program would degrade if this flag
		is enforced. This parameter is normally set to false.
*/
#define WatchCatchError false



/*!
	@def ParallelArray
	@brief Replace arrays of structures with parallel arrays.
	@details Replace arrays of structures with parallel arrays.
		When more than one field is accessed in succession,
		arrays of structures should exhibit more cache-hits
		than parallel arrays. The prefered setting is false.
*/
#define ParallelArray false



/*!
	@def FloatEquality
	@brief Consider appropriate equality comparison for floats.
	@details Consider appropriate equality comparison for floats.
		Floating point numbers are problematic for equality checking.
		This flag ensures approximate equality checking allowing some
		epsilon notion and causing some time cost to the program.
*/
#define FloatEquality true



/*!
	@def FixedWidthType
	@brief Use fixed width types of the compiler.
	@details Use fixed width types of the compiler.
		Using this option enables type size to be defined
		explicitly in terms of number of bits. Otherwise
		the types are determined by the standard data types.
*/
#define FixedWidthType false


/*!
	@def SmallSize
	@brief Consider small memory sizes i.e. 16-bit sizes.
	@details Consider small memory sizes i.e. 16-bit sizes.
		Use this macro in defining data, meta, and clock sizes.
*/
#define SmallSize 1
/*!
	@def NormalSize
	@brief Consider normal memory sizes i.e. 32-bit sizes.
	@details Consider normal memory sizes i.e. 32-bit sizes.
		Use this macro in defining data, meta, and clock sizes.
*/
#define NormalSize 2
/*!
	@def LargeSize
	@brief Consider large memory sizes i.e. 64-bit sizes.
	@details Consider large memory sizes i.e. 64-bit sizes.
		Use this macro in defining data, meta, and clock sizes.
*/
#define LargeSize 3



/*!
	@def DiscSize
	@brief Specify the memory sizes for discrete actual data.
	@details Specify the memory sizes for discrete actual data.
		Use this option to select user-level continuous actual data sizes.
*/
#define DiscSize NormalSize



/*!
	@def ContSize
	@brief Specify the memory sizes for continuous actual data.
	@details Specify the memory sizes for continuous actual data.
		Use this option to select user-level continuous actual data sizes.
*/
#define ContSize NormalSize



/*!
	@def MetaSize
	@brief Specify the memory sizes for meta data.
	@details Specify the memory sizes for meta data.
		Use this option to select system-level meta data sizes.
		The meta-data include dimensions, iterators, serials, and indexes.
*/
#define MetaSize NormalSize



/*!
	@def ClockSize
	@brief Specify the memory sizes for clock data.
	@details Specify the memory sizes for clock data.
		Use this option to select system-level clock sizes.
*/
#define ClockSize NormalSize



/*!
	@def RandomSize
	@brief Specify the random number size.
	@details Specify the random number size.
*/
#define RandomSize NormalSize



/*!
	@def ProcessorSize
	@brief Specify the processor data size.
	@details Specify the processor data size.
*/
#define ProcessorSize NormalSize



/*!
	@def IncompleteCode
	@brief Use this macro to denote that a code segment is incomplete.
	@details Use this macro to denote that a code segment is incomplete.
		This macro will simply allow you to trace down incomplete sections.
*/
#define IncompleteCode




#endif // CpplOptHppIncluded
