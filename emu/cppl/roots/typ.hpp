/*!
	@file typ.hpp
	@brief The header file for data types.
	@details This is the header file for data types.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 17.08.2012 QRL NICTA www.nicta.com.au
*/



#ifndef HppIncluded
#define HppIncluded



#include "cppl/prj.hpp"
#include "cppl/opt.hpp"
#include "cppl/lib.hpp"


openEmuSpace


/*
	Through out the entire project, underscores are avoided.
	The main reason is the personal disliking of underscores.
*/



#define scast static_cast
/*!
	@def scast
	@brief A macro to denote static_cast.
	@details This macro denotes static_cast.
*/



#define dcast dynamic_cast
/*!
	@def dcast
	@brief A macro to denote dynamic_cast.
	@details This macro denotes dynamic_cast.
		Dynamic casts are very time-costlier.
		They are avoided whenever possible.
*/



#define ccast const_cast
/*!
	@def ccast
	@brief A macro to denote const_cast.
	@details This macro denotes const_cast.
*/



#define rcast reinterpret_cast
/*!
	@def rcast
	@brief A macro to denote reinterpret_cast.
	@details This macro denotes reinterpret_cast.
*/



/*
	Nil and Null definitions.
*/



/*!
	@def Nil
	@brief A macro to represent void type.
	@details This macro represents void type.
*/
#define Nil void



/*!
	@def Null
	@brief A macro to denote null pointer.
	@details This macro denotes null pointer.
*/
#define Null NULL



/*!
	@class DnzLim
	@brief A class to represent discrete natural and integral number limits.
	@details This class represents discrete natural and integral number limits.
*/
template <typename typ> class DnzLim {};



/*!
	@def regDnzLim(theTyp,theMin,theMax)
	@brief Register a new data type's limits.
	@details Register a new data type's limits.
*/
#define regDnzLim(theTyp,theMin,theMax) \
		template<> class DnzLim<theTyp> { public:	enum { Min = theMin, Max = theMax}; }



/*
	Register limits.
*/
#if FixedWidthType
regDnzLim(uint8_t,0,UINT8_MAX);
regDnzLim(uint16_t,0,UINT16_MAX);
regDnzLim(uint32_t,0,UINT32_MAX);
regDnzLim(uint64_t,0,UINT64_MAX);
regDnzLim(int8_t,INT8_MIN,INT8_MAX);
regDnzLim(int16_t,INT16_MIN,INT16_MAX);
regDnzLim(int32_t,INT32_MIN,INT32_MAX);
regDnzLim(int64_t,INT64_MIN,INT64_MAX);
#else
regDnzLim(unsigned char,0,UCHAR_MAX);
regDnzLim(unsigned short int,0,USHRT_MAX);
regDnzLim(unsigned int,0,UINT_MAX);
regDnzLim(unsigned long long,0,ULONG_LONG_MAX);
regDnzLim(signed char,CHAR_MIN,CHAR_MAX);
regDnzLim(signed short int,SHRT_MIN,SHRT_MAX);
regDnzLim(signed int,INT_MIN,INT_MAX);
regDnzLim(signed long long,LONG_LONG_MIN,LONG_LONG_MAX);
#endif



/*!
	@class DnzLim
	@brief A class to represent size-based discrete natural and integral number types.
	@details This class represents size-based discrete natural and integral number types.
*/
template <int size> class DimDnz {};


/*!
	@def regDimDnz(theDim,theSgn,theUsgn)
	@brief Register a new sized signed and unsigned types.
	@details Register a new sized signed and unsigned types.
*/
#define regDimDnz(theDim,theSgn,theUsgn) \
		template<> class DimDnz<theDim> { public: typedef theSgn Stype; typedef theUsgn Utype; }


/*
	Register types.
*/
regDimDnz(8, int8_t, uint8_t);
regDimDnz(16, int16_t, uint16_t);
regDimDnz(32, int32_t, uint32_t);
regDimDnz(64, int64_t, uint64_t);


/*
	The following types are to be used in
	specifying integral sizes and counts.
*/



/*!
	@var typedef S
	@brief A type to represent single-byte numbers.
	@details This type represents single-byte numbers.
*/
#if FixedWidthType
typedef uint8_t S;
#else
typedef unsigned char S;
#endif


/*!
	@def castS(theS)
	@brief A macro to cast to S.
	@details This macro casts to S.
*/
#define castS(theS) (scast<S>(theS))



/*!
	@enum SLim
	@brief An enum to define single-byte number limits.
	@details This enum defines single-byte number limits.
*/
enum SLim
{
	MinS = DnzLim<S>::Min,		//!< Minimum number.
	MaxS = DnzLim<S>::Max		//!< Maximum number.
};



/*!
	@var typedef D
	@brief A type to represent double-byte numbers.
	@details This type represents double-byte numbers.
*/
#if FixedWidthType
typedef uint16_t D;
#else
typedef unsigned short D;
#endif


/*!
	@def castD(theD)
	@brief A macro to cast to D.
	@details This macro casts to D.
*/
#define castD(theD) (scast<D>(theD))



/*!
	@enum DLim
	@brief An enum to define double-byte number limits.
	@details This enum defines double-byte number limits.
*/
enum DLim
{
	MinD = DnzLim<D>::Min,		//!< Minimum number.
	MaxD = DnzLim<D>::Max		//!< Maximum number.
};



/*!
	@var typedef Q
	@brief A type to represent quad-byte numbers.
	@details This type represents quad-byte numbers.
*/
#if FixedWidthType
typedef uint32_t Q;
#else
typedef unsigned Q;
#endif


/*!
	@def castQ(theQ)
	@brief A macro to cast to Q.
	@details This macro casts to Q.
*/
#define castQ(theQ) (scast<Q>(theQ))



/*!
	@enum QLim
	@brief An enum to define quad-byte number limits.
	@details This enum defines quad-byte number limits.
*/
enum QLim
{
	MinQ = DnzLim<Q>::Min,		//!< Minimum number.
	MaxQ = DnzLim<Q>::Max		//!< Maximum number.
};




/*!
	@var typedef O
	@brief A type to represent octo-byte numbers.
	@details This type represents octo-byte numbers.
*/
#if FixedWidthType
typedef uint64_t O;
#else
typedef unsigned long long O;
#endif


/*!
	@def castO(theO)
	@brief A macro to cast to O.
	@details This macro casts to O.
*/
#define castO(theO) (scast<O>(theO))



/*!
	@enum OLim
	@brief An enum to define octo-byte number limits.
	@details This enum defines octo-byte number limits.
*/
enum OLim
{
	MinO = DnzLim<O>::Min,		//!< Minimum number.
	MaxO = DnzLim<O>::Max		//!< Maximum number.
};




/*
	The followings are the data types supported.
	The default data types are configured by
	defining the default versions of C, Z, N and R.
*/



/*!
	@var typedef C
	@brief A type to represent characters.
	@details This type represents characters.
*/
typedef char C;



/*!
	@def fstrC
	@brief A macro to define the format string for characters.
	@details This macro defines the format string for characters.
*/
#define fstrC "%c"



/*!
	@def castC(theC)
	@brief A macro to cast to C.
	@details This macro casts to C.
*/
#define castC(theC) (scast<C>(theC))



/*!
	@enum CLim
	@brief An enum to define character limits.
	@details This enum defines character limits.
*/
enum CLim
{
	EndC = castC(0)				//!< Ending character.
};



/*!
	@var typedef Cs
	@brief A type to represent cstring.
	@details This type represents cstring.
*/
typedef C const * Cs;



/*!
	@def fstrC
	@brief A macro to define the format string for cstrings.
	@details This macro defines the format string for cstrings.
*/
#define fstrCs "%s"



/*!
	@var typedef B
	@brief A type to represent boolean values.
	@details This type represents boolean values.
*/
typedef bool B;



/*!
	@def fstrB
	@brief A macro to define the format string for boolean values.
	@details This macro defines the format string for boolean values.
*/
#define fstrB "%d"



/*!
	@def castB(theB)
	@brief A macro to cast to B.
	@details This macro casts to B.
*/
#define castB(theB) (scast<B>(theB))



/*!
	@def prsfB
	@brief A macro to define the parsing function for cstring to boolean.
	@details This macro defines the parsing function for cstring to boolean.
*/
#define prsfB(theCs) (castB(atoi(theCs)))



/*!
	@enum BLim
	@brief An enum to define boolean value limits.
	@details This enum defines boolean value limits.
*/
enum BLim
{
	MinB = false,	//!< Minimum boolean value.
	MaxB = true		//!< Maximum boolean value.
};




/*!
	@var typedef N
	@brief A type to represent natural numbers.
	@details This type represents natural numbers.
*/
#if FixedWidthType
	#if DiscSize == SmallSize
		typedef uint16_t N;
	#elif DiscSize == NormalSize
		typedef uint32_t N;
	#elif DiscSize == LargeSize
		typedef uint64_t N;
	#else
		#error Undefined discrete data size specified.
	#endif
#else
	#if DiscSize == SmallSize
		typedef unsigned short N;
	#elif DiscSize == NormalSize
		typedef unsigned int N;
	#elif DiscSize == LargeSize
		typedef unsigned long long N;
	#else
		#error Undefined discrete data size specified.
	#endif
#endif


/*!
	@def fstrN
	@brief A macro to define the format string for natural numbers.
	@details This macro defines the format string for natural numbers.
*/
#if DiscSize == SmallSize
	#define fstrN "%u"
#elif DiscSize == NormalSize
	#define fstrN "%u"
#elif DiscSize == LargeSize
	#define fstrN "%llu"
#else
	#error Undefined discrete data size specified.
#endif


/*!
	@def castN(theN)
	@brief A macro to cast to N.
	@details This macro casts to N.
*/
#define castN(theN) (scast<N>(theN))



/*!
	@def prsfN
	@brief A macro to define the parsing function for cstring to natural numbers.
	@details This macro defines the parsing function for cstring to natural numbers.
*/
#if DiscSize == SmallSize
	#define prsfN(theCs) (castN(atoi(theCs)))
#elif DiscSize == NormalSize
	#define prsfN(theCs) (castN(atoi(theCs)))
#elif DiscSize == LargeSize
	#define prsfN(theCs) (castN(atoll(theCs)))
#else
	#error Undefined discrete data size specified.
#endif




/*!
	@enum NLim
	@brief An enum to define natural number limits.
	@details This enum defines natural number limits.
*/
enum NLim
{
	MinN = DnzLim<N>::Min,		//!< Minimum natural number.
	MaxN = DnzLim<N>::Max		//!< Maximum natural number.
};



/*!
	@var typedef Z
	@brief A type to represent integral numbers.
	@details This type represents integral numbers.
*/
#if FixedWidthType
	#if DiscSize == SmallSize
		typedef int16_t Z;
	#elif DiscSize == NormalSize
		typedef int32_t Z;
	#elif DiscSize == LargeSize
		typedef int64_t Z;
	#else
		#error Undefined discrete data size specified.
	#endif
#else
	#if DiscSize == SmallSize
		typedef short int Z;
	#elif DiscSize == NormalSize
		typedef int Z;
	#elif DiscSize == LargeSize
		typedef long long Z;
	#else
		#error Undefined discrete data size specified.
	#endif
#endif


/*!
	@def fstrZ
	@brief A macro to define the format string for integral numbers.
	@details This macro defines the format string for integral numbers.
*/
#if DiscSize == SmallSize
	#define fstrZ "%d"
#elif DiscSize == NormalSize
	#define fstrZ "%d"
#elif DiscSize == LargeSize
	#define fstrZ "%lld"
#else
	#error Undefined discrete data size specified.
#endif



/*!
	@def prsfZ
	@brief A macro to define the parsing function for cstring to integral numbers.
	@details This macro defines the parsing function for cstring to integral numbers.
*/
#if DiscSize == SmallSize
	#define prsfZ(theCs) (castZ(atoi(theCs)))
#elif DiscSize == NormalSize
	#define prsfZ(theCs) (castZ(atoi(theCs)))
#elif DiscSize == LargeSize
	#define prsfZ(theCs) (castZ(atoll(theCs)))
#else
	#error Undefined discrete data size specified.
#endif



/*!
	@def castZ(theZ)
	@brief A macro to cast to Z.
	@details This macro casts to Z.
*/
#define castZ(theZ) (scast<Z>(theZ))



/*!
	@enum ZLim
	@brief An enum to define integral number limits.
	@details This enum defines integral number limits.
*/
enum ZLim
{
	MinZ = DnzLim<Z>::Min,		//!< Minimum integral number.
	MaxZ = DnzLim<Z>::Max		//!< Maximum integral number.
};


/*!
	@var typedef R
	@brief A type to represent real numbers.
	@details This type represents real numbers.
*/
#if ContSize == SmallSize
	typedef float R;
#elif ContSize == NormalSize
	typedef double R;
#elif ContSize == LargeSize
	typedef long double R;
#else
	#error Undefined continuous data size specified.
#endif



/*!
	@def fstrR
	@brief A macro to define the format string for real numbers.
	@details This macro defines the format string for real numbers.
*/
#if ContSize == SmallSize
	#define fstrR "%e"
#elif ContSize == NormalSize
	#define fstrR "%le"
#elif ContSize == LargeSize
	#define fstrR "%Le"
#else
	#error Undefined continuous data size specified.
#endif



/*!
	@def castR(theR)
	@brief A macro to cast to R.
	@details This macro casts to R.
*/
#define castR(theR) (scast<R>(theR))



/*!
	@def prsfR
	@brief A macro to define the parsing function for cstring to real numbers.
	@details This macro defines the parsing function for cstring to real numbers.
*/
#if ContSize == SmallSize
	#define prsfR(theCs) (castR(strtod(theCs, Null)))
#elif ContSize == NormalSize
	#define prsfR(theCs) (castR(strtod(theCs, Null)))
#elif ContSize == LargeSize
	#define prsfR(theCs) (castR(strtod(theCs, Null)))
#else
	#error Undefined continuous data size specified.
#endif



/*!
	@def MinR
	@brief A macro to define minimum real number limits.
	@details This macro defines minimum real number limits.
		This is not an enum due to not being integral.
*/
#if ContSize == SmallSize
	#define	MinR (-FLT_MAX)
#elif ContSize == NormalSize
	#define	MinR (-DBL_MAX)
#elif ContSize == LargeSize
	#define	MinR (-LDBL_MAX)
#else
	#error Undefined continuous data size specified.
#endif



/*!
	@def MaxR
	@brief A macro to define maximum real number limits.
	@details This macro defines maximum real number limits.
		This is not an enum due to not being integral.
*/
#if ContSize == SmallSize
	#define	MaxR FLT_MAX
#elif ContSize == NormalSize
	#define MaxR DBL_MAX
#elif ContSize == LargeSize
	#define MaxR LDBL_MAX
#else
	#error Undefined continuous data size specified.
#endif



/*!
	@def PrcR
	@brief A macro for custom defined safe precision level.
	@details This macro is for custom defined safe precision level.
		This is not an enum due to not being integral.
*/
#if ContSize == SmallSize
	#define	PrcR 1e-6
#elif ContSize == NormalSize
	#define PrcR 1e-16
#elif ContSize == LargeSize
	#error Precision level for large sized continuous number is not known.
#else
	#error Undefined continuous data size specified.
#endif



/*!
	@def SigR
	@brief A macro for custom defined safe significant level.
	@details This macro is for custom defined safe significant level.
		This is not an enum due to not being integral.
*/
#if ContSize == SmallSize
	#define SigR 1e32
#elif ContSize == NormalSize
	#define	SigR 1e292
#elif ContSize == LargeSize
	#error Safe significant level for large sized continuous number is not known.
#else
	#error Undefined continuous data size specified.
#endif



/*!
	@def HopR
	@brief A macro for custom defined hop size for iterating.
	@details This macro is for custom defined hop size for iterating.
		This is not an enum due to not being integral.
*/
#if ContSize == SmallSize
	#define	HopR 0.1
#elif ContSize == NormalSize
	#define HopR 0.1
#elif ContSize == LargeSize
	#define HopR 0.1
#else
	#error Undefined continuous data size specified.
#endif



/*!
	@def GapR
	@brief A macro to define the gap between unequal real numbers.
	@details This macro defines the gap between unequal real numbers.
*/
#define	GapR 5




/*
	The following data types are used mainly in
	eliminating ambiguation of using the same type in
	various situations and for different purposes.
*/



/*!
	@typedef Bts
	@brief A type to represent bit strings.
	@details This type represents bit strings.
*/
typedef Q Bts;



/*!
	@def castBts(theBts)
	@brief A macro to cast to Bts.
	@details This macro casts to Bts.
*/
#define castBts(theBts) (scast<Bts>(theBts))



/*!
	@typedef Bll
	@brief A type to represent boolean logical levels.
	@details This type represents boolean logical levels.
*/
typedef B Bll;




/*!
	@def castBll(theBll)
	@brief A macro to cast to Bll.
	@details This macro casts to Bll.
*/
#define castBll(theBll) (scast<Bll>(theBll))



/*!
	@typedef Chr
	@brief A type to represent text characters.
	@details This type represents text characters.
*/
typedef C Chr;



/*!
	@def castChr(theChr)
	@brief A macro to cast to Chr.
	@details This macro casts to Chr.
*/
#define castChr(theChr) (scast<Chr>(theChr))



/*!
	@enum ChrLim
	@brief An enum to define text character limits.
	@details This enum defines text character limits.
*/
enum ChrLim
{
	EndChr = EndC	//!< Ending text character.
};



/*!
	@typedef Dim
	@brief A type to represent count and size.
	@details This type represents count and size.
*/
#if MetaSize == SmallSize
typedef D Dim;
#elif MetaSize == NormalSize
typedef Q Dim;
#elif MetaSize == LargeSize
typedef O Dim;
#else
	#error Undefined meta size specified.
#endif



/*!
	@def castDim(theDim)
	@brief A macro to cast to Dim.
	@details This macro casts to Dim.
*/
#define castDim(theDim) (scast<Dim>(theDim))



/*!
	@enum DimLim
	@brief An enum to define dimension limits.
	@details This enum defines dimension limits.
*/
enum DimLim
{
	MinDim = DnzLim<Dim>::Min,	//!< Minimum dimension.
	MaxDim = DnzLim<Dim>::Max	//!< Maximum dimension.
};



/*!
	@typedef Srl
	@brief A type to represent serials.
	@details This type represents serials.
*/
typedef Dim Srl;



/*!
	@def castSrl(theSrl)
	@brief A macro to cast to Srl.
	@details This macro casts to Srl.
*/
#define castSrl(theSrl) (scast<Srl>(theSrl))



/*!
	@enum SrlLim
	@brief An enum to define serial limits.
	@details This enum defines serial limits.
*/
enum SrlLim
{
	MinSrl = MinDim,			//!< Minimum serial.
	MaxSrl = MaxDim - 1,		//!< Maximum serial.
	InvSrl = MaxDim				//!< Invalid serial.
};



/*!
	@typedef Itr
	@brief A type to represent iterators.
	@details This type represents iterators.
*/
typedef Dim Itr;



/*!
	@enum ItrLim
	@brief An enum to define iterator limits.
	@details This enum defines iterator limits.
*/
enum ItrLim
{
	MinItr = MinDim,			//!< Minimum iterator.
	MaxItr = MaxDim - 1,		//!< Maximum iterator.
	InvItr = MaxDim				//!< Invalid iterator.
};



/*!
	@def castItr(theItr)
	@brief A macro to cast to Itr.
	@details This macro casts to Itr.
*/
#define castItr(theItr) (scast<Itr>(theItr))



/*!
	@typedef Idx
	@brief A type to represent indexes.
	@details This type represents indexes.
*/
typedef Dim Idx;



/*!
	@enum IdxLim
	@brief An enum to define index limits.
	@details This enum defines index limits.
*/
enum IdxLim
{
	MinIdx = MinDim,			//!< Minimum index.
	MaxIdx = MaxDim - 1,		//!< Maximum index.
	InvIdx = MaxDim				//!< Invalid index.
};



/*!
	@def castIdx(theIdx)
	@brief A macro to cast to Idx.
	@details This macro casts to Idx.
*/
#define castIdx(theIdx) (scast<Idx>(theIdx))



/*!
	@typedef Num
	@brief A type to represent integral numbers.
	@details This type represents integral numbers.
*/
#if MetaSize == SmallSize
typedef int16_t Num;
#elif MetaSize == NormalSize
typedef int32_t Num;
#elif MetaSize == LargeSize
typedef int64_t Num;
#else
	#error Undefined meta size specified.
#endif


/*!
	@def castNum(theNum)
	@brief A macro to cast to Num.
	@details This macro casts to Num.
*/
#define castNum(theNum) (scast<Num>(theNum))



/*!
	@enum NumLim
	@brief An enum to define number limits.
	@details This enum defines number limits.
*/
enum NumLim
{
	MinNum = DnzLim<Num>::Min,	//!< Minimum number.
	MaxNum = DnzLim<Num>::Max	//!< Maximum number.
};



/*!
	@typedef Clk
	@brief A type to represent clocks.
	@details This type represents clocks.
*/
#if ClockSize == SmallSize
	typedef D Clk;
#elif ClockSize == NormalSize
	typedef Q Clk;
#elif ClockSize == LargeSize
	typedef O Clk;
#else
	#error Undefined clock size specified.
#endif



/*!
	@def castClk(theClk)
	@brief A macro to cast to Clk.
	@details This macro casts to Clk.
*/
#define castClk(theClk) (scast<Clk>(theClk))



/*!
	@enum ClkLim
	@brief An enum to define clock limits.
	@details This enum defines clock limits.
*/
enum ClkLim
{
	NotClk = castClk(0),			//!< Null clock to be used for initialisation.
	MinClk = castClk(1),			//!< Minimum clock to start over the cycle.
	EndClk = DnzLim<Clk>::Max,		//!< Ending clock: the maximum value possible.
	MaxClk = EndClk - 6,			//!< Maximum clock to wrap around the cycle.
	InvClk = EndClk - 5,			//!< Invalid clock to assign invalid values.
	IdfClk = EndClk - 4,			//!< Indefinite clock to be used for locking.
	InfClk = EndClk - 3,			//!< Infinite clock to be used for determinates.
	EtrClk = EndClk - 2,			//!< Eternal clock to be used for constants.
	UdfClk = EndClk - 1				//!< Undefined clock when not at all applicable.
};



closeEmuSpace



#endif // HppIncluded
