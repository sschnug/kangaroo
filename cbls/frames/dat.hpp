/*!
	@file dat.hpp
	@brief The prototype file for data types and limits.
	@details This is the prototype file for data types and limits.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 19.03.2010 QRL NICTA www.nicta.com.au
*/



#ifndef DatHppIncluded
#define DatHppIncluded



#include "cbls/prj.hpp"
#include "cbls/opt.hpp"
#include "cbls/lib.hpp"
#include "cbls/msg.hpp"



openKangarooSpace



/*
	The following data types are used at meta level.
	They help eliminate unambiguation when using
	the same data type for different purposes.
*/


/*!
	@var enum Gen
	@brief An enum to represent genus of terms.
	@details This  type represents genus of terms.
*/
enum Gen
{
	Tu = 0,			//!< Undefined term.
	Tc = 1,			//!< Constant term.
	Tv = 2,			//!< Variable term.
	Tf = 3,			//!< Function term.
	TermUndef = 0,	//!< Undefined term.
	TermConst = 1,	//!< Constant term.
	TermVar = 2,	//!< Variable term.
	TermFunc = 3	//!< Function term.
};



/*!
	@typedef Hdl
	@brief A type to represent the term/selector/algorithm/system  handles.
	@details This type represents the term/selector/algorithm/system handles.
*/
typedef Srl Hdl;



/*!
	@def castHdl(theHdl)
	@brief A macro to cast to Hdl.
	@details This macro casts to Hdl.
*/
#define castHdl(theHdl) (scast<Hdl>(theHdl))



/*!
	@enum HdlLim
	@brief An enum to define handle limit constants.
	@details This enum defines handle limit constants.
*/
enum HdlLim
{
	MinHdl = DnzLim<Hdl>::Min,		//!< Minimum handle.
	MaxHdl = DnzLim<Hdl>::Max - 1,	//!< Maximum handle.
	InvHdl = DnzLim<Hdl>::Max		//!< Invalid handle.
};



/*!
	@typedef Itn
	@brief A type to represent iterations.
	@details This type represents iterations.
*/
typedef Q Itn;



/*!
	@def castItn(theItn)
	@brief A macro to cast to Itn.
	@details This macro casts to Itn.
*/
#define castItn(theItn) (scast<Itn>(theItn))



/*!
	@enum ItnLim
	@brief An enum to define iteration limit constants.
	@details This enum defines iteration limit constants.
*/
enum ItnLim
{
	MinItn = DnzLim<Itn>::Min,		//!< Minimum iteration.
	MaxItn = DnzLim<Itn>::Max - 1,	//!< Maximum iteration.
	InvItn = DnzLim<Itn>::Max		//!< Invalid iteration.
};




/*
	The following data types are used in the internal architecture.
	They help eliminate unambiguation of the same type in various
	situations and for different purposes.
*/



/*!
	@typedef Cat
	@brief A type to represent categories.
	@details This type represents term/selector/algorithm categories.
				Term categories include constant, variable, and function subclasses.
				Selc categories include prep/last/full/swap selectors.
				Algo categories include meta-heuristic driven algorithms.
*/
typedef S Cat;



/*!
	@def castCat(theCat)
	@brief A macro to cast to Cat.
	@details This macro casts to Cat.
*/
#define castCat(theCat) (scast<Cat>(theCat))



/*!
	@typedef Typ
	@brief A type to represent types.
	@details This type represents term/selector/algorithm types.
				Each category of terms/selcetors/algorithm has specific versions
				for each data types (e.g. boolean, integer, or float data types).
*/
typedef S Typ;



/*!
	@def castTyp(theTyp)
	@brief A macro to cast to Typ.
	@details This macro casts to Typ.
*/
#define castTyp(theTyp) (scast<Typ>(theTyp))




/*!
	@typedef Cls
	@brief A type to represent term/selector/algorithm classes.
	@details This type represents term/selector/algorithm classes.
				Term classes include constant, variable, and function subclasses.
				Selector classes include part/last/full/swap selectors.
				Algorithm classes include meta-heuristic driven algorithms.
*/
typedef Q Cls;



/*!
	@def castCls(theCls)
	@brief A macro to cast to Cls.
	@details This macro casts to Cls.
*/
#define castCls(theCls) (scast<Cls>(theCls))




/*!
	@typedef Lvl
	@brief A type to represent function levels.
	@details This type represents function levels.
*/
typedef S Lvl;



/*!
	@def castLvl(theLvl)
	@brief A macro to cast to Lvl.
	@details This macro casts to Lvl.
*/
#define castLvl(theLvl) (scast<Lvl>(theLvl))



/*!
	@enum LvlLim
	@brief An enum to define function level constants.
	@details This enum defines function level constants.
*/
enum LvlLim
{
	MinLvl = DnzLim<Lvl>::Min,		//!< Minimum level.
	MaxLvl = DnzLim<Lvl>::Max - 1,	//!< Maximum level.
	InvLvl = DnzLim<Lvl>::Max		//!< Invalid level.
};



/*!
	@typedef Loc
	@brief A type to represent data object locators.
	@details This type represents data object locators.
*/
typedef Srl Loc;



/*!
	@def castLoc(theLoc)
	@brief A macro to cast to Loc.
	@details This macro casts to Loc.
*/
#define castLoc(theLoc) (scast<Loc>(theLoc))



/*!
	@enum LocLim
	@brief An enum to define locator limit constants.
	@details This enum defines locator limit constants.
*/
enum LocLim
{
	MinLoc = DnzLim<Loc>::Min,		//!< Minimum locator.
	MaxLoc = DnzLim<Loc>::Max - 1,	//!< Maximum locator.
	InvLoc = DnzLim<Loc>::Max		//!< Invalid locator.
};




/*!
	@typedef Pos
	@brief A type to represent parameter position within a function.
	@details This type represents parameter position within a function.
*/
typedef Srl Pos;



/*!
	@enum PosLim
	@brief An enum to define position limit constants.
	@details This enum defines position limit constants.
*/
enum PosLim
{
	MinPos = DnzLim<Pos>::Min,		//!< Minimum position.
	MaxPos = DnzLim<Pos>::Max - 1,	//!< Maximum position.
	InvPos = DnzLim<Pos>::Max		//!< Invalid position.
};



/*!
	@def castPos(thePos)
	@brief A macro to cast to Pos.
	@details This macro casts to Pos.
*/
#define castPos(thePos) (scast<Pos>(thePos))



/*!
	@typedef Sqn
	@brief A type to represent variable sequents within a function.
	@details This type represents variable sequents within a function.
*/
typedef Srl Sqn;



/*!
	@enum SqnLim
	@brief An enum to define sequent constants.
	@details This enum defines sequent limit constants.
*/
enum SqnLim
{
	MinSqn = DnzLim<Sqn>::Min,		//!< Minimum sequent.
	MaxSqn = DnzLim<Pos>::Max - 1,	//!< Maximum sequent.
	InvSqn = DnzLim<Pos>::Max		//!< Invalid sequent.
};



/*!
	@def castSqn(theSqn)
	@brief A macro to cast to Sqn.
	@details This macro casts to Sqn.
*/
#define castSqn(theSqn) (scast<Sqn>(theSqn))




/*!
	@typedef Lnk
	@brief A type to represent links with the system.
	@details This type represents links with the system.
*/
typedef Idx Lnk;



/*!
	@enum LnkLim
	@brief An enum to define link limit constants.
	@details This enum defines link limit constants.
*/
enum LnkLim
{
	MinLnk = DnzLim<Idx>::Min,		//!< Minimum link.
	MaxLnk = DnzLim<Idx>::Max - 1,	//!< Maximum link.
	InvLnk = DnzLim<Idx>::Max		//!< Invalid link.
};



/*!
	@def castLnk(theLnk)
	@brief A macro to cast to Lnk.
	@details This macro casts to Lnk.
*/
#define castLnk(theLnk) (scast<Lnk>(theLnk))



/*
	Supported data types at the interface level.
*/


/*!
	@typedef Bln
	@brief A type to represent boolean type.
	@details This type represents boolean type.
*/
typedef B Bln;



/*!
	@def castBln(theBln)
	@brief A macro to cast to Bln.
	@details This macro casts to Bln.
*/
#define castBln(theBln) (scast<Bln>(theBln))



/*!
	@enum BlnLim
	@brief An enum to define boolean limit constants.
	@details This enum defines boolean limit constants.
*/
enum BlnLim
{
	MinBln = MinB,	//!< Minimum boolean.
	MaxBln = MaxB	//!< Maximum boolean.
};



/*!
	@typedef Int
	@brief A type to represent integer type.
	@details This type represents (signed) integer type.
*/
typedef Z Int;



/*!
	@enum IntLim
	@brief An enum to define integer limit constants.
	@details This enum defines integer limit constants.
*/
enum IntLim
{
	MinInt = MinZ,				//!< Minimum integer.
	MaxInt = MaxZ				//!< Maximum integer.
};



/*!
	@def castInt(theInt)
	@brief A macro to cast to Int.
	@details This macro casts to Int.
*/
#define castInt(theInt) (scast<Int>(theInt))



/*!
	@typedef Cnt
	@brief A type to represent countable type.
	@details This type represents countable (unsigned) type.
*/
typedef N Cnt;



/*!
	@def castCnt(theCnt)
	@brief A macro to cast to Cnt.
	@details This macro casts to Cnt.
*/
#define castCnt(theCnt) (scast<Cnt>(theCnt))



/*!
	@enum CntLim
	@brief An enum to define integer limit constants.
	@details This enum defines integer limit constants.
*/
enum CntLim
{

	MinCnt = MinN,	//!< Minimum countable.
	MaxCnt = MaxN	//!< Maximum countable.
};



/*!
	@typedef Flt
	@brief A type to represent float type.
	@details This type represents float type.
*/
typedef R Flt;



/*!
	@def castFlt(theFlt)
	@brief A macro to cast to Flt.
	@details This macro casts to Flt.
*/
#define castFlt(theFlt) (scast<Flt>(theFlt))



/*!
	@def MinFlt
	@brief A macro to define minimum float limit constant.
	@details This macro defines min float limit constant.
			This is not an enum due to not being integral.
*/
#define	MinFlt MinR



/*!
	@def MaxFlt
	@brief A macro to define maximum float limit constant.
	@details This macro defines maximum float limit constant.
			This is not an enum due to not being integral.
*/
#define	MaxFlt MaxR



/*!
	@def PrcFlt
	@brief A macro to define precisions for float limit constant.
	@details This macro defines precisions float limit constant.
			This is not an enum due to not being integral.
*/
#define	PrcFlt PrcR



/*!
	@def SigFlt
	@brief A macro to define significant float limit constant.
	@details This macro defines significant float limit constant.
			This is used to get a different number from the current.
			This is not an enum due to not being integral.
*/
#define	SigFlt SigR



/*!
	@def HopFlt
	@brief A macro to define float hop size constant.
	@details This macro defines float hop size constant.
			This is used to get discretise the floating point space.
			This is not an enum due to not being integral.
*/
#define	HopFlt 0.1



/*!
	@var enum Ord
	@brief Sorting order.
	@details This enum denotes sorting orders.
*/
enum Ord
{
	Asc,		//!< Ascending order.
	Dsc			//!< Descending order.
};



/*!
	@class OrdStub
	@brief A class to represent sorting order stubs.
	@details This class represents sorting order stubs.
*/
template <Ord const theOrd, typename idt, typename odt> class OrdStub {};


/*!
	@class regOrd
	@brief A macro to register sorting order.
	@details This class is to register sorting order.
*/
#define regOrd(theOrd, theIn, theOut, regOp, invOp, nxtOp, prvOp) \
	template<> class OrdStub<theOrd, theIn, theOut> \
	{ public:   typedef regOp<theIn,theOut> RegOp; typedef invOp<theIn, theOut> InvOp; \
				typedef nxtOp<theIn,theIn> NxtOp; typedef prvOp<theIn,theIn> PrvOp; \
				static theIn const First0; static theIn const Last0; \
				static theIn const First1; static theIn const Last1;}


/*!
	@class defOrd
	@brief A macro to define sorting order.
	@details This class is to define sorting order.
*/
#define defOrd(theOrd, theIn, theOut, theFirst0, theLast0, theFirst1, theLast1) \
	theIn const OrdStub<theOrd,theIn,theOut>::First0 = theFirst0;\
	theIn const OrdStub<theOrd,theIn,theOut>::Last0 = theLast0;\
	theIn const OrdStub<theOrd,theIn,theOut>::First1 = theFirst1;\
	theIn const OrdStub<theOrd,theIn,theOut>::Last1 = theLast1


regOrd(Asc,Bln,Bln,lt,gt,nextc,prevc);
regOrd(Asc,Int,Bln,lt,gt,nextc,prevc);
regOrd(Asc,Flt,Bln,lt,gt,nextc,prevc);
regOrd(Asc,Bln,Int,lt,gt,nextc,prevc);
regOrd(Asc,Int,Int,lt,gt,nextc,prevc);
regOrd(Asc,Flt,Int,lt,gt,nextc,prevc);
regOrd(Asc,Bln,Flt,lt,gt,nextc,prevc);
regOrd(Asc,Int,Flt,lt,gt,nextc,prevc);
regOrd(Asc,Flt,Flt,lt,gt,nextc,prevc);

regOrd(Dsc,Bln,Bln,gt,lt,prevc,nextc);
regOrd(Dsc,Int,Bln,gt,lt,prevc,nextc);
regOrd(Dsc,Flt,Bln,gt,lt,prevc,nextc);
regOrd(Dsc,Bln,Int,gt,lt,prevc,nextc);
regOrd(Dsc,Int,Int,gt,lt,prevc,nextc);
regOrd(Dsc,Flt,Int,gt,lt,prevc,nextc);
regOrd(Dsc,Bln,Flt,gt,lt,prevc,nextc);
regOrd(Dsc,Int,Flt,gt,lt,prevc,nextc);
regOrd(Dsc,Flt,Flt,gt,lt,prevc,nextc);



/*!
	@class DataType
	@brief A class to represent datatype ids.
	@details This class represents unique datatype ids.
*/
template <Typ const theTyp> class DataType {};



/*!
	@class DataStub
	@brief A class to represent data stubs.
	@details This class represents data stubs.
*/
template <typename dat> class DataStub {};



/*!
	@def regDataType(theDat, theTyp, theBuf)
	@brief Register a new data type.
	@details Register a new data type and ensure uniqness.
*/
#define regDataType(theDat, theTyp, theBuf) \
		template<> class DataType<theTyp> { public: typedef theDat Datum; }; \
		template<> class DataStub<theDat> { public: enum { DataTyp = theTyp};\
											typedef theBuf TempBuff;}


/*!
	@class DataTemp
	@brief A class to represent data temporary for inputs.
	@details This class represents data temporary for inputs.
*/
template <typename dat1, typename dat2> class DataTemp {};



/*!
	@def regDataTemp(IDat1, IDat2, TDat)
	@brief Register a data temporary for inputs
	@details Register a data temporary for given inputs.
*/
#define regDataTemp(IDat1, IDat2, TDat) \
		template<> class DataTemp<IDat1,IDat2> { public: typedef TDat Type; }



/*!
	@class DataBuff
	@brief A class to represent data buffer for input to output.
	@details This class represents data buffer for input to output.
*/
template <typename idat, typename odat> class DataBuff {};




/*!
	@def regDataBuff(IDat, ODat, BDat)
	@brief Register a data buffer.
	@details Register a data buff for given input and output.
*/
#define regDataBuff(IDat, ODat, BDat) \
		template<> class DataBuff<IDat,ODat> { public: typedef BDat Type; }


/*!
	@class DataLim
	@brief A class to represent data limits.
	@details This class represents data limits.
*/
template <typename dat> class DataLim {};



/*!
	@def regDataLim(theDat)
	@brief Register a new data type.
	@details Register a new data type and ensure uniqness.
*/
#define regDataLim(theDat) \
		template<> class DataLim<theDat> { public:	static theDat const MinLim; \
													static theDat const MaxLim; }


/*!
	@def defDataLim(theDat, theMin, theMax)
	@brief Register a new data type.
	@details Register a new data type and ensure uniqness.
*/
#define defDataLim(theDat, theMin, theMax) \
		theDat const DataLim<theDat>::MinLim = theMin; \
		theDat const DataLim<theDat>::MaxLim = theMax;



/*!
	Register nulls.
*/
regDataType(Nil, castTyp(0), Nil);
enum { DataTypNil = castTyp(0) /*!< Nil data type. */ };



/*
	Register data types.
*/
regDataType(Bln, castTyp(1), Int);
regDataType(Int, castTyp(2), Int);
regDataType(Cnt, castTyp(3), Cnt);
regDataType(Flt, castTyp(4), Flt);



/*
	Register data temps.
*/
regDataTemp(Bln,Bln,Int);
regDataTemp(Bln,Int,Int);
regDataTemp(Bln,Flt,Flt);
regDataTemp(Int,Bln,Int);
regDataTemp(Int,Int,Int);
regDataTemp(Int,Flt,Flt);
regDataTemp(Flt,Bln,Flt);
regDataTemp(Flt,Int,Flt);
regDataTemp(Flt,Flt,Flt);



/*
	Register data buffers.
*/
regDataBuff(Bln,Bln,Int);
regDataBuff(Bln,Int,Int);
regDataBuff(Bln,Flt,Flt);
regDataBuff(Int,Bln,Int);
regDataBuff(Int,Int,Int);
regDataBuff(Int,Flt,Flt);
regDataBuff(Flt,Bln,Flt);
regDataBuff(Flt,Int,Flt);
regDataBuff(Flt,Flt,Flt);



/*
	Register limits.
*/
regDataLim(Bln);
regDataLim(Int);
regDataLim(Cnt);
regDataLim(Flt);



closeKangarooSpace



#endif // DatHhIncluded
