/*!
	@file spec.hpp
	@brief The prototype file for Spec class.
	@details This is the prototype file for Prm class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 03.01.2010 QRL NICTA www.nicta.com.au
	@see prm.cpp
*/



#ifndef SpecHppIncluded
#define SpecHppIncluded



#include "cbls/frames/dat.hpp"



openKangarooSpace


/*
	Forward declaration.
*/
class Term;



/*!
	@enum Pso
	@brief An enum to denote parameter specification ordering.
	@details This enum denotes parameter specification ordering.
*/
enum Pso
{
	Ordered = true,		//!< Ordered parameters.
	Unordered = false	//!< Unordered parameters.
};



/*!
	@enum Psc
	@brief An enum to represent parameter specification constants.
	@details This enum represents parameter specification constants.
*/
enum Psc
{
	VasV = 0x0,					//!< Value as value
	MasV = 0x1,					//!< Metric as value.
	ValueAsValue = 0x0,			//!< Value as value
	MetricAsValue = 0x1,		//!< Metric as value.

	MasM = 0x0,					//!< Metric as metric
	VasM = 0x2,					//!< Value as metric.

	MetricAsMetric = 0x0,		//!< Metric as metric
	ValueAsMetric = 0x2,		//!< Value as metric.

	RoHn = 0x0,					//!< Rank on hint min.
	RoHx = 0x4,					//!< Rank on hint max.
	RankOnHintMin = 0x0,		//!< Rank on hint min.
	RankOnHintMax = 0x4,		//!< Rank on hint max.

	HnAsHn = 0x00,				//!< Hint min as hint min.
	HxAsHn = 0x10,				//!< Hint max as hint min.
	HintMinAsHintMin = 0x00,	//!< Hint min as hint min.
	HintMaxAsHintMin = 0x10,	//!< Hint max as hint min.

	EnAsEn = 0x20,				//!< Eval min as eval min.
	ExAsEn = 0x60,				//!< Eval max as eval min.
	EvalMinAsEvalMin = 0x20,	//!< Eval min as eval min.
	EvalMaxAsEvalMin = 0x60,	//!< Eval max as eval min.

	MasEn = 0xA0,				//!< Metric as eval min.
	VasEn = 0xE0,				//!< Value as eval min.
	MetricAsEvalMin = 0xA0,		//!< Metric as eval min.
	ValueAsEvalMin = 0xE0,		//!< Value as eval min.

	HxAsHx = 0x000,				//!< Hint max as hint max.
	HnAsHx = 0x100,				//!< Hint min as hint max.
	HintMaxAsHintMax = 0x000,	//!< Hint max as hint max.
	HintMinAsHintMax = 0x100,	//!< Hint min as hint max.

	ExAsEx = 0x200,				//!< Eval max as eval max.
	EnAsEx = 0x600,				//!< Eval min as eval max.
	EvalMaxAsEvalMax = 0x200,	//!< Eval min as eval max.
	EvalMinAsEvalMax = 0x600,	//!< Eval max as eval max.

	MasEx = 0xA00,				//!< Metric as eval max.
	VasEx = 0xE00,				//!< Value as eval max.
	MetricAsEvalMax = 0xA00,	//!< Metric as eval max.
	ValueAsEvalMax = 0xE00,		//!< Value as eval max.

	OnDot = 0x0000,				//!< Dot conversion for minimisation.
	OnNot = 0x1000,				//!< Not conversion for minimisation.
	OnNeg = 0x2000,				//!< Neg conversion for minimisation.
	OnInv = 0x3000,				//!< Inv conversion for minimisation.
	MinDotConv = 0x0000,		//!< Dot conversion for minimisation.
	MinNotConv = 0x1000,		//!< Not conversion for minimisation.
	MinNegConv = 0x2000,		//!< Neg conversion for minimisation.
	MinInvConv = 0x3000,		//!< Inv conversion for minimisation.

	OxDot = 0x0000,				//!< Dot conversion for maximisation.
	OxNot = 0x4000,				//!< Not conversion for maximisation.
	OxNeg = 0x8000,				//!< Neg conversion for maximisation.
	OxInv = 0xC000,				//!< Inv conversion for maximisation.
	MaxDotConv = 0x0000,		//!< Dot conversion for maximisation.
	MaxNotConv = 0x4000,		//!< Not conversion for maximisation.
	MaxNegConv = 0x8000,		//!< Neg conversion for maximisation.
	MaxInvConv = 0xC000			//!< Inv conversion for maximisation.
};


/*!
	@enum Psm
	@brief An enum to represent parameter specification masks.
	@details This enum represents parameter specification masks.
*/
enum Psm
{
	DfltPsm = 0x0,		//!< Default specification.

	ValueSeg   = 0x1,	//!< Value segment.
	MetricSeg  = 0x2, 	//!< Metric segment.
	RankSeg    = 0x4,	//!< Rank segment.

	MinEvalChk = 0x20,	//!< Min eval check.
	MinHintSeg = 0x30,	//!< Min hint segment.
	MinEvalSeg = 0xE0,	//!< Min eval segment.

	MaxEvalChk = 0x200,	//!< Max eval check.
	MaxHintSeg = 0x300,	//!< Max hint segment.
	MaxEvalSeg = 0xE00,	//!< Max eval segment.

	AnyEvalChk = 0x220,	//!< Any eval check.

	MinConvSeg = 0x3000,//!< Min convert segment.
	MaxConvSeg = 0xC000	//!< Max convert segment.
};


/*!
	@typedef Pss
	@brief A type to denote parameter specification string.
	@details This type denotes parameter specification string.
*/
typedef Bts Pss;


/*!
	@enum Fsc
	@brief An enum to represent function specification constants.
	@details This enum represents function specification constants.
*/
enum Fsc
{
	Xv = 0x0,		//!< Value as inx parameter.
	Xm = 0x1,		//!< Metric as inx parameter.
	XisValue = 0x0,	//!< Value as inx parameter.
	XisMetric = 0x1,//!< Metric as inx parameter.

	Yv = 0x0,		//!< Value as iny parameter.
	Ym = 0x2,		//!< Metric as iny parameter.
	YisValue = 0x0,	//!< Value as iny parameter.
	YisMetric = 0x2,//!< Metric as iny parameter.

	Zv = 0x0,		//!< Value as inz parameter.
	Zm = 0x4,		//!< Metric as inz parameter.
	ZisValue = 0x0,	//!< Value as inz parameter.
	ZisMetric = 0x4,//!< Metric as inz parameter.

	En = 0x0,		//!< Eval min as eval parameter.
	Ex = 0x8,		//!< Eval max as eval parameter.
	EvalMin = 0x0,	//!< Eval min as eval parameter.
	EvalMax = 0x8,	//!< Eval max as eval parameter.

	Hn = 0x0,		//!< Hint min as hint parameter.
	Hx = 0x10,		//!< Hint max as hint parameter.
	HintMin = 0x0,	//!< Hint min as hint parameter.
	HintMax = 0x10,	//!< Hint max as hint parameter.

	On = 0x00,		//!< Minimisation segments.
	Ox = 0x20,		//!< Maximisation segments.
	OptMin = 0x00,	//!< Minimisation segments.
	OptMax = 0x20	//!< Maximisation segments.
};


/*!
	@enum Fsm
	@brief An enum to represent function specification masks.
	@details This enum represents function specification masks.
*/
enum Fsm
{
	DfltFsm = 0x0,	//!< Default specification.
	Xvm = 0x1,		//!< Both value and metric as inx parameter.
	Yvm = 0x2,		//!< Both value and metric as iny parameter.
	Zvm = 0x4,		//!< Both value and metric as inz parameter.
	Enx = 0x8,		//!< Both eval min and max as eval parameter.
	Hnx = 0x10,		//!< Both hint min and max as hint parameter.
	Onx = 0x20,		//!< Both minimisation and maximisation segments.
	OEH = 0x38		//!< All of the optimisation segments.
};



/*!
	@typedef Fss
	@brief A type to denote function specification string.
	@details This type denotes function specification string.
*/
typedef Bts Fss;



/*!
	@fn Loc getPxLoc(Fss const theFss, Term * theTerm, Pss const thePss);
	@brief A function to decode function specification.
*/
Loc getPxLoc(Fss const theFss, Term * theTerm, Pss const thePss);



/*!
	@fn Loc getPyLoc(Fss const theFss, Term * theTerm, Pss const thePss);
	@brief A function to decode function specification.
*/
Loc getPyLoc(Fss const theFss, Term * theTerm, Pss const thePss);



/*!
	@fn Loc getPzLoc(Fss const theFss, Term * theTerm, Pss const thePss);
	@brief A function to decode function specification.
*/
Loc getPzLoc(Fss const theFss, Term * theTerm, Pss const thePss);



/*!
	@fn Loc getPeLoc(Fss const theFss, Term * theTerm, Pss const thePss);
	@brief A function to decode function specification.
*/
Loc getPeLoc(Fss const theFss, Term * theTerm, Pss const thePss);



/*!
	@fn Loc getPhLoc(Fss const theFss, Term * theTerm, Pss const thePss);
	@brief A function to decode function specification.
*/
Loc getPhLoc(Fss const theFss, Term * theTerm, Pss const thePss);


/*!
	@fn Loc getPoeLoc(Fss const theFss, Term * theTerm, Pss const thePss);
	@brief A function to decode function specification.
*/
Loc getPoeLoc(Fss const theFss, Term * theTerm, Pss const thePss);



/*!
	@fn Loc getPohLoc(Fss const theFss, Term * theTerm, Pss const thePss);
	@brief A function to decode function specification.
*/
Loc getPohLoc(Fss const theFss, Term * theTerm, Pss const thePss);



/*!
	@fn Loc getValueLoc(Term * theTerm, Pss const thePss)
	@brief A function to decode value locator from parameter specification.
*/
Loc getValueLoc(Term * theTerm, Pss const thePss);


/*!
	@fn Loc getMetricLoc(Term * theTerm, Pss const thePss)
	@brief A function to decode metric locator from parameter specification.
*/
Loc getMetricLoc(Term * theTerm, Pss const thePss);


/*!
	@fn Loc getRankLoc(Term * theTerm, Pss const thePss)
	@brief A function to decode rank locator from parameter specification.
*/
Loc getRankLoc(Term * theTerm, Pss const thePss);



/*!
	@fn Loc getEvalMinLoc(Term * theTerm, Pss const thePss)
	@brief A function to decode eval min locator form parameter specification.
*/
Loc getEvalMinLoc(Term * theTerm, Pss const thePss);


/*!
	@fn Loc getHintMinLoc(Term * theTerm, Pss const thePss)
	@brief A function to decode hint min locator from specification.
*/
Loc getHintMinLoc(Term * theTerm, Pss const thePss);



/*!
	@fn Loc getEvalMaxLoc(Term * theTerm, Pss const thePss)
	@brief A function to decode eval max locator from specification.
*/
Loc getEvalMaxLoc(Term * theTerm, Pss const thePss);



/*!
	@fn Loc getHintMaxLoc(Term * theTerm, Pss const thePss)
	@brief A function to decode hint max locator form parameter specification.
*/
Loc getHintMaxLoc(Term * theTerm, Pss const thePss);



/*!
	@fn Bll EvalAsMin(Pss const thePss)
	@brief A function to check whether eval used as min.
	@details This function checks whether eval used as min.
*/
inline Bll EvalAsMin(Pss const thePss)
{
	WatchError
	return thePss & MinEvalChk;
	CatchError
}



/*!
	@fn Bll EvalAsMax(Pss const thePss)
	@brief A function to check whether eval used as max.
	@details This function checks whether eval used as max.
*/
inline Bll EvalAsMax(Pss const thePss)
{
	WatchError
	return thePss & MaxEvalChk;
	CatchError
}


/*!
	@fn Bll EvalAsOpt(Fss const theFss, Pss const thePss)
	@brief A function to check whether eval used as opt.
	@details This function checks whether eval used as opt.
*/
inline Bll EvalAsOpt(Fss const theFss, Pss const thePss)
{
	WatchError
	switch(theFss & Onx)
	{
		case On : return EvalAsMin(thePss);
		case Ox : return EvalAsMax(thePss);
		default: Throw(eInvalidSpec);
	}
	CatchError
}




closeKangarooSpace



#endif // SpecHppIncluded
