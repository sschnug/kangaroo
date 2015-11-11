/*!
	@file prm.cpp
	@brief The implementation file for the Prm class.
	@details This is the implementation file for the Prm class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see prm.hpp
*/



#include "cbls/frames/prm.hpp"
#include "cbls/frames/term.hpp"


openKangarooSpace



/*!
	@fn Loc getValueLoc(Term * theTerm, Pss const thePss)
	@details This function decodes parameter specification string.
*/
Loc getValueLoc(Term * theTerm, Pss const thePss)
{
	WatchError
	switch (thePss & ValueSeg)
	{
		case VasV : return theTerm->ValueLoc();
		case MasV : return theTerm->MetricLoc();
		default: Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	@fn Loc getMetricLoc(Term * theTerm, Pss const thePss)
	@details This function decodes parameter specification string.
*/
Loc getMetricLoc(Term * theTerm, Pss const thePss)
{
	WatchError
	switch (thePss & MetricSeg)
	{
		case MasM : return theTerm->MetricLoc();
		case VasM : return theTerm->ValueLoc();
		default: Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	@fn Loc getRankLoc(Term * theTerm, Pss const thePss)
	@details This function decodes parameter specification string.
*/
Loc getRankLoc(Term * theTerm, Pss const thePss)
{
	WatchError
	switch (thePss & RankSeg)
	{
		case RoHn : return theTerm->HintMinLoc();
		case RoHx : return theTerm->HintMaxLoc();
		default: Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	@fn Loc getEvalMinLoc(Term * theTerm, Pss const thePss)
	@details This function decodes parameter specification string.
*/
Loc getEvalMinLoc(Term * theTerm, Pss const thePss)
{
	WatchError
	switch(thePss & MinEvalSeg)
	{
		case EnAsEn : return theTerm->EvalMinLoc(); break;
		case ExAsEn : return theTerm->EvalMaxLoc(); break;
		case MasEn  : return theTerm->MetricLoc(); break;
		case VasEn : return theTerm->ValueLoc(); break;
		default: Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	@fn Loc getHintMinLoc(Term * theTerm, Pss const thePss)
	@details This function decodes parameter specification string.
*/
Loc getHintMinLoc(Term * theTerm, Pss const thePss)
{
	WatchError
	switch(thePss & MinHintSeg)
	{
		case HnAsHn : return theTerm->HintMinLoc();
		case HxAsHn : return theTerm->HintMaxLoc();
		default: Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	@fn Loc getEvalMaxLoc(Term * theTerm, Pss const thePss)
	@details This function decodes parameter specification.
*/
Loc getEvalMaxLoc(Term * theTerm, Pss const thePss)
{
	WatchError
	switch(thePss & MaxEvalSeg)
	{
		case ExAsEx: return theTerm->EvalMaxLoc(); break;
		case EnAsEx: return theTerm->EvalMinLoc(); break;
		case MasEx : return theTerm->MetricLoc(); break;
		case VasEx : return theTerm->ValueLoc(); break;
		default: Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	@fn Loc getHintMaxLoc(Term * theTerm, Pss const thePss)
	@details This function decodes parameter specification string.
*/
Loc getHintMaxLoc(Term * theTerm, Pss const thePss)
{
	WatchError
	switch(thePss & MaxHintSeg)
	{
		case HxAsHx : return theTerm->HintMaxLoc();
		case HnAsHx : return theTerm->HintMinLoc();
		default: Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	@fn Loc getPxLoc(Fss const theFss, Term * theTerm, Pss const thePss)
	@details This function decodes function specification string.
*/
Loc getPxLoc(Fss const theFss, Term * theTerm, Pss const thePss)
{
	WatchError
	switch(theFss & Xvm)
	{
		case Xv : return getValueLoc(theTerm, thePss);
		case Xm : return getMetricLoc(theTerm, thePss);
		default: Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	@fn Loc getPyLoc(Fss const theFss, Term * theTerm, Pss const thePss)
	@details This function decodes function specification string.
*/
Loc getPyLoc(Fss const theFss, Term * theTerm, Pss const thePss)
{
	WatchError
	switch(theFss & Yvm)
	{
		case Yv : return getValueLoc(theTerm, thePss);
		case Ym : return getMetricLoc(theTerm, thePss);
		default: Throw(eInvalidSpec);
	}
	CatchError
}




/*!
	@fn Loc getPzLoc(Fss const theFss, Term * theTerm, Pss const thePss)
	@details This function decodes function specification string.
*/
Loc getPzLoc(Fss const theFss, Term * theTerm, Pss const thePss)
{
	WatchError
	switch(theFss & Zvm)
	{
		case Zv : return getValueLoc(theTerm, thePss);
		case Zm : return getMetricLoc(theTerm, thePss);
		default: Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	@fn Loc getPeLoc(Fss const theFss, Term * theTerm, Pss const thePss)
	@details This function decodes function specification string.
*/
Loc getPeLoc(Fss const theFss, Term * theTerm, Pss const thePss)
{
	WatchError
	switch(theFss & Enx)
	{
		case En : return getEvalMinLoc(theTerm, thePss);
		case Ex : return getEvalMaxLoc(theTerm, thePss);
		default: Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	@fn Loc getPhLoc(Fss const theFss, Term * theTerm, Pss const thePss)
	@details This function decodes function specification string.
*/
Loc getPhLoc(Fss const theFss, Term * theTerm, Pss const thePss)
{
	WatchError
	switch(theFss & Hnx)
	{
		case Hn : return getHintMinLoc(theTerm, thePss);
		case Hx : return getHintMaxLoc(theTerm, thePss);
		default: Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	@fn Loc getPoeLoc(Fss const theFss, Term * theTerm, Pss const thePss)
	@details This function decodes function specification string.
*/
Loc getPoeLoc(Fss const theFss, Term * theTerm, Pss const thePss)
{
	WatchError
	switch(theFss & Onx)
	{
		case On : return getEvalMinLoc(theTerm, thePss);
		case Ox : return getEvalMaxLoc(theTerm, thePss);
		default: Throw(eInvalidSpec);
	}
	CatchError
}




/*!
	@fn Loc getPohLoc(Fss const theFss, Term * theTerm, Pss const thePss)
	@details This function decodes function specification string.
*/
Loc getPohLoc(Fss const theFss, Term * theTerm, Pss const thePss)
{
	WatchError
	switch(theFss & Onx)
	{
		case On : return getHintMinLoc(theTerm, thePss);
		case Ox : return getHintMaxLoc(theTerm, thePss);
		default: Throw(eInvalidSpec);
	}
	CatchError
}



closeKangarooSpace
