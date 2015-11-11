/*!
	@file frames/reg.hh
	@brief The register header file for frames.
	@details This is the register header file for frames.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef FramesRegHhIncluded
#define FramesRegHhIncluded


#include "cbls/frames/dat.hpp"


openKangarooSpace



/*!
	@class TermStub
	@brief A class to represent term stubs.
	@details This class represents term stubs.
*/
template <typename TermMain> class TermStub {};



/*!
	@class TermCategory
	@brief A class to represent term category ids.
	@details This class represents unique term category ids.
*/
template <Cat const theCat> class TermCategory {};



/*!
	@def tctn(theMain, theCat)
	@brief Register a new term category.
	@details Register a new term category and ensure uniqueness.
*/
#define tctn(theMain,theCat) theMain;\
		template<> class TermCategory<theCat> { public: typedef theMain TermMain; };\
		template<> class TermStub<theMain> { public: enum { TermCat = theCat}; }


/*!
	@def tctx(theMain, theAlter, theCat)
	@brief Register a new term category.
	@details Register a new term category and ensure uniqueness.
*/
#define tctx(theMain, theAlter, theCat) theMain;\
		typedef theMain theAlter;\
		template<> class TermCategory<theCat> { public: typedef theMain TermMain; };\
		template<> class TermStub<theMain> { public: enum { TermCat = theCat}; }


/*!
	@class TermType
	@brief A class to represent term type ids.
	@details This class represents unique term type ids.
*/
template <Typ const theTyp> class TermType {};



/*!
	@def ttpn(theMain, theTyp)
	@brief Register a new term type.
	@details Register a new term type and ensure uniqueness.
*/
#define ttpn(theMain, theTyp) theMain;\
		template<> class TermType<theTyp> { public: typedef theMain TermMain; };\
		template<> class TermStub<theMain> { public: enum { TermTyp = theTyp}; }


/*!
	@def ttpx(theMain, theAlter, theTyp)
	@brief Register a new term type.
	@details Register a new term type and ensure uniqueness.
*/
#define ttpx(theMain, theAlter, theTyp) theMain;\
		typedef theMain theAlter;\
		template<> class TermType<theTyp> { public: typedef theMain TermMain; };\
		template<> class TermStub<theMain> { public: enum { TermTyp = theTyp}; }


/*!
	@class TermClass
	@brief A class to represent term class ids.
	@details This class represents unique term class ids.
*/
template <Cls const theCls> class TermClass {};


/*!
	@def tcln(theMain, theCls)
	@brief Register a new term class.
	@details Register a new term class and ensure uniqueness.
*/
#define tcln(theMain, theCls) theMain;\
		template<> class TermClass<theCls> { public: typedef theMain TermMain; };\
		template<> class TermStub<theMain> { public: enum { TermCls = theCls}; }


/*!
	@def tclx(theMain, theAlter, theCls)
	@brief Register a new term class.
	@details Register a new term class and ensure uniqueness.
*/
#define tclx(theMain, theAlter, theCls) theMain;\
		typedef theMain theAlter;\
		template<> class TermClass<theCls> { public: typedef theMain TermMain; };\
		template<> class TermStub<theMain> { public: enum { TermCls = theCls}; }


/*!
	@def ttpcln(theMain, theTyp, theCls)
	@brief Register a new term type cum class.
	@details Register a new term type cum class and ensure uniqueness.
*/
#define ttpcln(theMain, theTyp, theCls) theMain;\
		template<> class TermType<theTyp> { public: typedef theMain TermMain; };\
		template<> class TermClass<theCls> { public: typedef theMain TermMain; };\
		template<> class TermStub<theMain> { public: enum { TermTyp = theTyp, TermCls = theCls}; }


/*!
	@def ttpclx(theMain, theAlter, theTyp, theCls)
	@brief Register a new term type cum class.
	@details Register a new term type cum class and ensure uniqueness.
*/
#define ttpclx(theMain, theAlter, theTyp, theCls) theMain;\
		typedef theMain theAlter;\
		template<> class TermType<theTyp> { public: typedef theMain TermMain; };\
		template<> class TermClass<theCls> { public: typedef theMain TermMain; };\
		template<> class TermStub<theMain> { public: enum { TermTyp = theTyp, TermCls = theCls}; }


/*!
	@def regTermCatTypCls(theMain, theCat, theTyp, theCls)
	@brief Register a new term category cum type cum class.
	@details Register a new term category cum type cum class and ensure uniqueness.
*/
#define regTermCatTypCls(theMain, theCat, theTyp, theCls) \
		template <> class TermCategory<theCat> { public: typedef theMain TermMain; };\
		template<> class TermType<theTyp> { public: typedef theMain TermMain; };\
		template<> class TermClass<theCls> { public: typedef theMain TermMain; };\
		template<> class TermStub<theMain> { public: enum { TermCat = theCat, TermTyp = theTyp, TermCls = theCls}; }


/*
	Register nulls.
*/
regTermCatTypCls(Nil, 0, 0, 0);
enum
{
	TermCatNil = 0, //!< Term category nil.
	TermTypNil = 0, //!< Term type nil.
	TermClsNil = 0 	//!< Term class nil.
};



/*!
	@class SelcStub
	@brief A class to represent selc stubs.
	@details This class represents selc stubs.
*/
template <typename SelcMain> class SelcStub {};



/*!
	@class SelcCategory
	@brief A class to represent selc category ids.
	@details This class represents unique selc category ids.
*/
template <Cat const theCat> class SelcCategory {};



/*!
	@def sctn(theMain, theCat)
	@brief Register a new selc category.
	@details Register a new selc category and ensure uniqueness.
*/
#define sctn(theMain,theCat) theMain;\
		template<> class SelcCategory<theCat> { public: typedef theMain SelcMain; };\
		template<> class SelcStub<theMain> { public: enum { SelcCat = theCat}; }


/*!
	@def sctx(theMain, theAlter, theCat)
	@brief Register a new selc category.
	@details Register a new selc category and ensure uniqueness.
*/
#define sctx(theMain, theAlter, theCat) theMain;\
		typedef theMain theAlter;\
		template<> class SelcCategory<theCat> { public: typedef theMain SelcMain; };\
		template<> class SelcStub<theMain> { public: enum { SelcCat = theCat}; }


/*!
	@class SelcType
	@brief A class to represent selc type ids.
	@details This class represents unique selc type ids.
*/
template <Typ const theTyp> class SelcType {};



/*!
	@def stpn(theMain, theTyp)
	@brief Register a new selc type.
	@details Register a new selc type and ensure uniqueness.
*/
#define stpn(theMain, theTyp) theMain;\
		template<> class SelcType<theTyp> { public: typedef theMain SelcMain; };\
		template<> class SelcStub<theMain> { public: enum { SelcTyp = theTyp}; }


/*!
	@def stpx(theMain, theAlter, theTyp)
	@brief Register a new selc type.
	@details Register a new selc type and ensure uniqueness.
*/
#define stpx(theMain, theAlter, theTyp) theMain;\
		typedef theMain theAlter;\
		template<> class SelcType<theTyp> { public: typedef theMain SelcMain; };\
		template<> class SelcStub<theMain> { public: enum { SelcTyp = theTyp}; }


/*!
	@class SelcClass
	@brief A class to represent selc class ids.
	@details This class represents unique selc class ids.
*/
template <Cls const theCls> class SelcClass {};


/*!
	@def scln(theMain, theCls)
	@brief Register a new selc class.
	@details Register a new selc class and ensure uniqueness.
*/
#define scln(theMain, theCls) theMain;\
		template<> class SelcClass<theCls> { public: typedef theMain SelcMain; };\
		template<> class SelcStub<theMain> { public: enum { SelcCls = theCls}; }


/*!
	@def sclx(theMain, theAlter, theCls)
	@brief Register a new selc class.
	@details Register a new selc class and ensure uniqueness.
*/
#define sclx(theMain, theAlter, theCls) theMain;\
		typedef theMain theAlter;\
		template<> class SelcClass<theCls> { public: typedef theMain SelcMain; };\
		template<> class SelcStub<theMain> { public: enum { SelcCls = theCls}; }


/*!
	@def stpcln(theMain, theTyp, theCls)
	@brief Register a new selc type cum class.
	@details Register a new selc type cum class and ensure uniqueness.
*/
#define stpcln(theMain, theTyp, theCls) theMain;\
		template<> class SelcType<theTyp> { public: typedef theMain SelcMain; };\
		template<> class SelcClass<theCls> { public: typedef theMain SelcMain; };\
		template<> class SelcStub<theMain> { public: enum { SelcTyp = theTyp, SelcCls = theCls}; }


/*!
	@def stpclx(theMain, theAlter, theTyp, theCls)
	@brief Register a new selc type cum class.
	@details Register a new selc type cum class and ensure uniqueness.
*/
#define stpclx(theMain, theAlter, theTyp, theCls) theMain;\
		typedef theMain theAlter;\
		template<> class SelcType<theTyp> { public: typedef theMain SelcMain; };\
		template<> class SelcClass<theCls> { public: typedef theMain SelcMain; };\
		template<> class SelcStub<theMain> { public: enum { SelcTyp = theTyp, SelcCls = theCls}; }


/*!
	@def regSelcCatTypCls(theMain, theCat, theTyp, theCls)
	@brief Register a new selc category cum type cum class.
	@details Register a new selc category cum type cum class and ensure uniqueness.
*/
#define regSelcCatTypCls(theMain, theCat, theTyp, theCls) \
		template <> class SelcCategory<theCat> { public: typedef theMain SelcMain; };\
		template<> class SelcType<theTyp> { public: typedef theMain SelcMain; };\
		template<> class SelcClass<theCls> { public: typedef theMain SelcMain; };\
		template<> class SelcStub<theMain> { public: enum { SelcCat = theCat, SelcTyp = theTyp, SelcCls = theCls}; }

/*
	Register nulls.
*/
regSelcCatTypCls(Nil, 0, 0, 0);
enum
{
	SelcCatNil = 0, //!< Selector category nil.
	SelcTypNil = 0, //!< Selector type nil.
	SelcClsNil = 0 	//!< Selector class nil.
};


/*!
	@class TabuStub
	@brief A class to represent tabu stubs.
	@details This class represents tabu stubs.
*/
template <typename TabuMain> class TabuStub {};


/*!
	@class TabuCategory
	@brief A class to represent tabu category ids.
	@details This class represents unique tabu category ids.
*/
template <Cat const theCat> class TabuCategory {};



/*!
	@def tabuctn(theMain, theCat)
	@brief Register a new tabu category.
	@details Register a new tabu category and ensure uniqueness.
*/
#define tabuctn(theMain,theCat) theMain;\
		template<> class TabuCategory<theCat> { public: typedef theMain TabuMain; };\
		template<> class TabuStub<theMain> { public: enum { TabuCat = theCat}; }


/*!
	@def tabuctx(theMain, theAlter, theCat)
	@brief Register a new tabu category.
	@details Register a new tabu category and ensure uniqueness.
*/
#define tabuctx(theMain, theAlter, theCat) theMain;\
		typedef theMain theAlter;\
		template<> class TabuCategory<theCat> { public: typedef theMain TabuMain; };\
		template<> class TabuStub<theMain> { public: enum { TabuCat = theCat}; }


/*!
	@class TabuClass
	@brief A class to represent tabu class ids.
	@details This class represents unique tabu class ids.
*/
template <Cls const theCls> class TabuClass {};


/*!
	@def tabucln(theMain, theCls)
	@brief Register a new tabu class.
	@details Register a new tabu class and ensure uniqueness.
*/
#define tabucln(theMain, theCls) theMain;\
		template<> class TabuClass<theCls> { public: typedef theMain TabuMain; };\
		template<> class TabuStub<theMain> { public: enum { TabuCls = theCls }; }


/*!
	@def tabuclx(theMain, theAlter, theCls)
	@brief Register a new tabu class.
	@details Register a new tabu class and ensure uniqueness.
*/
#define tabuclx(theMain, theAlter, theCls) theMain;\
		typedef theMain theAlter;\
		template<> class TabuClass<theCls> { public: typedef theMain TabuMain; };\
		template<> class TabuStub<theMain> { public: enum { TabuCls = theCls }; }


/*!
	@class TabuType
	@brief A class to represent tabu type ids.
	@details This class represents unique tabu type ids.
*/
template <Typ const theTyp> class TabuType {};


/*!
	@def tabutpn(theMain, theTyp)
	@brief Register a new tabu type.
	@details Register a new tabu type and ensure uniqueness.
*/
#define tabutpn(theMain, theTyp) theMain;\
		template<> class TabuType<theTyp> { public: typedef theMain TabuMain; };\
		template<> class TabuStub<theMain> { public: enum { TabuTyp = theTyp}; }


/*!
	@def tabutpx(theMain, theAlter, theTyp)
	@brief Register a new tabu type.
	@details Register a new tabu type and ensure uniqueness.
*/
#define tabutpx(theMain, theAlter, theTyp) theMain;\
		typedef theMain theAlter;\
		template<> class TabuType<theTyp> { public: typedef theMain TabuMain; };\
		template<> class TabuStub<theMain> { public: enum { TabuTyp = theTyp}; }


/*!
	@def regTabuCatTypCls(theMain, theCat, theTyp, theCls)
	@brief Register a new tabu class cum type cum category.
	@details Register a new tabu class cum type cum category and ensure uniqueness.
		Mainly used when corresponding class actually does not exist.
*/
#define regTabuCatTypCls(theMain, theCat, theTyp, theCls) \
		template <> class TabuCategory<theCat> { public: typedef theMain TabuMain; };\
		template <> class TabuType<theCat> { public: typedef theMain TabuMain; };\
		template<> class TabuClass<theCls> { public: typedef theMain TabuMain; };\
		template<> class TabuStub<theMain> { public: enum {TabuCls = theCls, TabuTyp = theTyp, TabuCat = theCat }; }



/*
	Register nulls.
*/
regTabuCatTypCls(Nil, 0, 0, 0);
enum
{
	TabuCatNil = 0, //!< Tabu category nil.
	TabuTypNil = 0,	//!< Taby type nil.
	TabuClsNil = 0 	//!< Tabu class nil.
};



/*!
	@def dec
	@brief A macro to declare new classes.
	@details This macro declares new classes.
*/
#define dec class


/*!
	@def reg
	@brief A macro to register new type names.
	@details This macro registers new type names.
*/
#define reg typedef



/*!
	@def rti
	@brief A macro to register template instances.
	@details This macro register template instances.
*/
#define rti(...) reg __VA_ARGS__



/*!
	@def rmit
	@brief A macro to register mandatorily instantiated templates.
	@details This macro registers mandatorily instantiated templates.
*/
#define rmit(...) template class __VA_ARGS__; reg __VA_ARGS__


/*!
	@def tia
	@brief A macro to declare template instance alias.
	@details This macro declares template instance alias.
*/
#define tia(Alias) Alias



closeKangarooSpace



#endif
