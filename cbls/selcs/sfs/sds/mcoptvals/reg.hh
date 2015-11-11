/*!
	@file sds/mcoptvals/reg.hh
	@brief The register header file for Monte Carlo optimum value sds.
	@details This is the register header file for Monte Carlo optimum value sds.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef McOptValsRegHhIncluded
#define McOptValsRegHhIncluded


openKangarooSpace
#define AutoClsMcOptValSd (SelcStub<Sf>::SelcCat * 20000 + (thisLine - AutoClsBaseMcOptValSd))
enum { AutoClsBaseMcOptValSd = thisLine};
closeKangarooSpace

#include "cbls/selcs/sfs/sds/mcoptvals/mcopt1val1statrangesdvzt.tcc"
openKangarooSpace
rti(McOpt1Val1StatRangeSdVZt<Int, Bln, Dsc >) scln(McMaxVal1StatRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt1Val1StatRangeSdVZt<Int, Int, Dsc >) scln(McMaxVal1StatRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt1Val1StatRangeSdVZt<Int, Flt, Dsc >) scln(McMaxVal1StatRangeSdViZf,AutoClsMcOptValSd);

rti(McOpt1Val1StatRangeSdVZt<Flt, Bln, Dsc >) scln(McMaxVal1StatRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt1Val1StatRangeSdVZt<Flt, Int, Dsc >) scln(McMaxVal1StatRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt1Val1StatRangeSdVZt<Flt, Flt, Dsc >) scln(McMaxVal1StatRangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt1Val1StatRangeSdVZt<Int, Bln, Asc >) scln(McMinVal1StatRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt1Val1StatRangeSdVZt<Int, Int, Asc >) scln(McMinVal1StatRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt1Val1StatRangeSdVZt<Int, Flt, Asc >) scln(McMinVal1StatRangeSdViZf,AutoClsMcOptValSd);

rti(McOpt1Val1StatRangeSdVZt<Flt, Bln, Asc >) scln(McMinVal1StatRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt1Val1StatRangeSdVZt<Flt, Int, Asc >) scln(McMinVal1StatRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt1Val1StatRangeSdVZt<Flt, Flt, Asc >) scln(McMinVal1StatRangeSdVfZf,AutoClsMcOptValSd);
closeKangarooSpace


#include "cbls/selcs/sfs/sds/mcoptvals/mcopt2val1statrangesdvzt.tcc"
openKangarooSpace
rti(McOpt2Val1StatRangeSdVZt<Int, Bln, Dsc,Dsc >) scln(McMaxMaxVal1StatRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Int, Int, Dsc,Dsc >) scln(McMaxMaxVal1StatRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Int, Flt, Dsc,Dsc >) scln(McMaxMaxVal1StatRangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Bln, Dsc,Dsc >) scln(McMaxMaxVal1StatRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Int, Dsc,Dsc >) scln(McMaxMaxVal1StatRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Flt, Dsc,Dsc >) scln(McMaxMaxVal1StatRangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt2Val1StatRangeSdVZt<Int, Bln, Dsc,Asc >) scln(McMaxMinVal1StatRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Int, Int, Dsc,Asc >) scln(McMaxMinVal1StatRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Int, Flt, Dsc,Asc >) scln(McMaxMinVal1StatRangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Bln, Dsc,Asc >) scln(McMaxMinVal1StatRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Int, Dsc,Asc >) scln(McMaxMinVal1StatRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Flt, Dsc,Asc >) scln(McMaxMinVal1StatRangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt2Val1StatRangeSdVZt<Int, Bln, Asc,Dsc >) scln(McMinMaxVal1StatRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Int, Int, Asc,Dsc >) scln(McMinMaxVal1StatRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Int, Flt, Asc,Dsc >) scln(McMinMaxVal1StatRangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Bln, Asc,Dsc >) scln(McMinMaxVal1StatRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Int, Asc,Dsc >) scln(McMinMaxVal1StatRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Flt, Asc,Dsc >) scln(McMinMaxVal1StatRangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt2Val1StatRangeSdVZt<Int, Bln, Asc,Asc >) scln(McMinMinVal1StatRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Int, Int, Asc,Asc >) scln(McMinMinVal1StatRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Int, Flt, Asc,Asc >) scln(McMinMinVal1StatRangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Bln, Asc,Asc >) scln(McMinMinVal1StatRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Int, Asc,Asc >) scln(McMinMinVal1StatRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1StatRangeSdVZt<Flt, Flt, Asc,Asc >) scln(McMinMinVal1StatRangeSdVfZf,AutoClsMcOptValSd);
closeKangarooSpace


//#include "cbls/selcs/sfs/sds/mcoptvals/mcopt1val1dynarangesdvzt.tcc"
#include "cbls/selcs/sfs/sds/mcoptvals/newmcopt1val1dynarangesdvzt.tcc"
openKangarooSpace
rti(McOpt1Val1DynaRangeSdVZt<Int, Bln, Dsc >) scln(McMaxVal1DynaRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt1Val1DynaRangeSdVZt<Int, Int, Dsc >) scln(McMaxVal1DynaRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt1Val1DynaRangeSdVZt<Int, Flt, Dsc >) scln(McMaxVal1DynaRangeSdViZf,AutoClsMcOptValSd);

rti(McOpt1Val1DynaRangeSdVZt<Flt, Bln, Dsc >) scln(McMaxVal1DynaRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt1Val1DynaRangeSdVZt<Flt, Int, Dsc >) scln(McMaxVal1DynaRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt1Val1DynaRangeSdVZt<Flt, Flt, Dsc >) scln(McMaxVal1DynaRangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt1Val1DynaRangeSdVZt<Int, Bln, Asc >) scln(McMinVal1DynaRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt1Val1DynaRangeSdVZt<Int, Int, Asc >) scln(McMinVal1DynaRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt1Val1DynaRangeSdVZt<Int, Flt, Asc >) scln(McMinVal1DynaRangeSdViZf,AutoClsMcOptValSd);

rti(McOpt1Val1DynaRangeSdVZt<Flt, Bln, Asc >) scln(McMinVal1DynaRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt1Val1DynaRangeSdVZt<Flt, Int, Asc >) scln(McMinVal1DynaRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt1Val1DynaRangeSdVZt<Flt, Flt, Asc >) scln(McMinVal1DynaRangeSdVfZf,AutoClsMcOptValSd);
closeKangarooSpace



#include "cbls/selcs/sfs/sds/mcoptvals/mcopt2val1dynarangesdvzt.tcc"
openKangarooSpace
rti(McOpt2Val1DynaRangeSdVZt<Int, Bln, Dsc,Dsc >) scln(McMaxMaxVal1DynaRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Int, Int, Dsc,Dsc >) scln(McMaxMaxVal1DynaRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Int, Flt, Dsc,Dsc >) scln(McMaxMaxVal1DynaRangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Bln, Dsc,Dsc >) scln(McMaxMaxVal1DynaRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Int, Dsc,Dsc >) scln(McMaxMaxVal1DynaRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Flt, Dsc,Dsc >) scln(McMaxMaxVal1DynaRangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt2Val1DynaRangeSdVZt<Int, Bln, Dsc,Asc >) scln(McMaxMinVal1DynaRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Int, Int, Dsc,Asc >) scln(McMaxMinVal1DynaRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Int, Flt, Dsc,Asc >) scln(McMaxMinVal1DynaRangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Bln, Dsc,Asc >) scln(McMaxMinVal1DynaRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Int, Dsc,Asc >) scln(McMaxMinVal1DynaRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Flt, Dsc,Asc >) scln(McMaxMinVal1DynaRangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt2Val1DynaRangeSdVZt<Int, Bln, Asc,Dsc >) scln(McMinMaxVal1DynaRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Int, Int, Asc,Dsc >) scln(McMinMaxVal1DynaRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Int, Flt, Asc,Dsc >) scln(McMinMaxVal1DynaRangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Bln, Asc,Dsc >) scln(McMinMaxVal1DynaRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Int, Asc,Dsc >) scln(McMinMaxVal1DynaRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Flt, Asc,Dsc >) scln(McMinMaxVal1DynaRangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt2Val1DynaRangeSdVZt<Int, Bln, Asc,Asc >) scln(McMinMinVal1DynaRangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Int, Int, Asc,Asc >) scln(McMinMinVal1DynaRangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Int, Flt, Asc,Asc >) scln(McMinMinVal1DynaRangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Bln, Asc,Asc >) scln(McMinMinVal1DynaRangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Int, Asc,Asc >) scln(McMinMinVal1DynaRangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1DynaRangeSdVZt<Flt, Flt, Asc,Asc >) scln(McMinMinVal1DynaRangeSdVfZf,AutoClsMcOptValSd);
closeKangarooSpace



#include "cbls/selcs/sfs/sds/mcoptvals/mcopt1val1rangesdvzt.tcc"
openKangarooSpace
rti(McOpt1Val1RangeSdVZt<Int, Bln, Dsc >) scln(McMaxVal1RangeSdViZb,AutoClsMcOptValSd);
rti(McOpt1Val1RangeSdVZt<Int, Int, Dsc >) scln(McMaxVal1RangeSdViZi,AutoClsMcOptValSd);
rti(McOpt1Val1RangeSdVZt<Int, Flt, Dsc >) scln(McMaxVal1RangeSdViZf,AutoClsMcOptValSd);

rti(McOpt1Val1RangeSdVZt<Flt, Bln, Dsc >) scln(McMaxVal1RangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt1Val1RangeSdVZt<Flt, Int, Dsc >) scln(McMaxVal1RangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt1Val1RangeSdVZt<Flt, Flt, Dsc >) scln(McMaxVal1RangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt1Val1RangeSdVZt<Int, Bln, Asc >) scln(McMinVal1RangeSdViZb,AutoClsMcOptValSd);
rti(McOpt1Val1RangeSdVZt<Int, Int, Asc >) scln(McMinVal1RangeSdViZi,AutoClsMcOptValSd);
rti(McOpt1Val1RangeSdVZt<Int, Flt, Asc >) scln(McMinVal1RangeSdViZf,AutoClsMcOptValSd);

rti(McOpt1Val1RangeSdVZt<Flt, Bln, Asc >) scln(McMinVal1RangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt1Val1RangeSdVZt<Flt, Int, Asc >) scln(McMinVal1RangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt1Val1RangeSdVZt<Flt, Flt, Asc >) scln(McMinVal1RangeSdVfZf,AutoClsMcOptValSd);
closeKangarooSpace



#include "cbls/selcs/sfs/sds/mcoptvals/mcopt2val1rangesdvzt.tcc"
openKangarooSpace
rti(McOpt2Val1RangeSdVZt<Int, Bln, Dsc,Dsc >) scln(McMaxMaxVal1RangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Int, Int, Dsc,Dsc >) scln(McMaxMaxVal1RangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Int, Flt, Dsc,Dsc >) scln(McMaxMaxVal1RangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Bln, Dsc,Dsc >) scln(McMaxMaxVal1RangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Int, Dsc,Dsc >) scln(McMaxMaxVal1RangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Flt, Dsc,Dsc >) scln(McMaxMaxVal1RangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt2Val1RangeSdVZt<Int, Bln, Dsc,Asc >) scln(McMaxMinVal1RangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Int, Int, Dsc,Asc >) scln(McMaxMinVal1RangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Int, Flt, Dsc,Asc >) scln(McMaxMinVal1RangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Bln, Dsc,Asc >) scln(McMaxMinVal1RangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Int, Dsc,Asc >) scln(McMaxMinVal1RangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Flt, Dsc,Asc >) scln(McMaxMinVal1RangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt2Val1RangeSdVZt<Int, Bln, Asc,Dsc >) scln(McMinMaxVal1RangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Int, Int, Asc,Dsc >) scln(McMinMaxVal1RangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Int, Flt, Asc,Dsc >) scln(McMinMaxVal1RangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Bln, Asc,Dsc >) scln(McMinMaxVal1RangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Int, Asc,Dsc >) scln(McMinMaxVal1RangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Flt, Asc,Dsc >) scln(McMinMaxVal1RangeSdVfZf,AutoClsMcOptValSd);

rti(McOpt2Val1RangeSdVZt<Int, Bln, Asc,Asc >) scln(McMinMinVal1RangeSdViZb,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Int, Int, Asc,Asc >) scln(McMinMinVal1RangeSdViZi,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Int, Flt, Asc,Asc >) scln(McMinMinVal1RangeSdViZf,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Bln, Asc,Asc >) scln(McMinMinVal1RangeSdVfZb,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Int, Asc,Asc >) scln(McMinMinVal1RangeSdVfZi,AutoClsMcOptValSd);
rti(McOpt2Val1RangeSdVZt<Flt, Flt, Asc,Asc >) scln(McMinMinVal1RangeSdVfZf,AutoClsMcOptValSd);
closeKangarooSpace



#endif // McOptValsRegHhIncluded
