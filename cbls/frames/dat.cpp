/*!
	@file dat.cpp
	@brief The implementation file for data types and limits.
	@details This is the implementation file for data types and limits.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/



#include "cbls/frames/dat.hpp"



openKangarooSpace



/*
	Define ordering meta-data.
*/


defOrd(Asc,Bln,Bln,MinBln,MaxBln,MinBln,MaxBln);
defOrd(Asc,Int,Bln,MinInt,MaxInt,(MinInt+1),(MaxInt-1));
defOrd(Asc,Flt,Bln,MinFlt,MaxFlt,(MinFlt+SigFlt),(MaxFlt-SigFlt));
defOrd(Asc,Bln,Int,MinBln,MaxBln,MinBln,MaxBln);
defOrd(Asc,Int,Int,MinInt,MaxInt,(MinInt+1),(MaxInt-1));
defOrd(Asc,Flt,Int,MinFlt,MaxFlt,(MinFlt+SigFlt),(MaxFlt-SigFlt));
defOrd(Asc,Bln,Flt,MinBln,MaxBln,MinBln,MaxBln);
defOrd(Asc,Int,Flt,MinInt,MaxInt,(MinInt+1),(MaxInt-1));
defOrd(Asc,Flt,Flt,MinFlt,MaxFlt,(MinFlt+SigFlt),(MaxFlt-SigFlt));

defOrd(Dsc,Bln,Bln,MaxBln,MinBln,MaxBln,MinBln);
defOrd(Dsc,Int,Bln,MaxInt,MinInt,(MaxInt-1),(MinInt+1));
defOrd(Dsc,Flt,Bln,MaxFlt,MinFlt,(MaxFlt-SigFlt),(MinFlt+SigFlt));
defOrd(Dsc,Bln,Int,MaxBln,MinBln,MaxBln,MinBln);
defOrd(Dsc,Int,Int,MaxInt,MinInt,(MaxInt-1),(MinInt+1));
defOrd(Dsc,Flt,Int,MaxFlt,MinFlt,(MaxFlt-SigFlt),(MinFlt+SigFlt));
defOrd(Dsc,Bln,Flt,MaxBln,MinBln,MaxBln,MinBln);
defOrd(Dsc,Int,Flt,MaxInt,MinInt,(MaxInt-1),(MinInt+1));
defOrd(Dsc,Flt,Flt,MaxFlt,MinFlt,(MaxFlt-SigFlt),(MinFlt+SigFlt));



/*
	Define data limit constants.
*/
defDataLim(Bln, false, true);		//!< Data limits for boolean.
defDataLim(Int, MinInt, MaxInt);	//!< Data limits for integer.
defDataLim(Cnt, MinCnt, MaxCnt);	//!< Data limits for countable.
defDataLim(Flt, MinFlt, MaxFlt);	//!< Data limits for float.



closeKangarooSpace
