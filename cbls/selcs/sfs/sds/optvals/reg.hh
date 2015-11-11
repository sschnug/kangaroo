/*!
	@file sds/optvals/reg.hh
	@brief The register header file for optimum value sds.
	@details This is the register header file for optimum value sds.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef OptValsRegHhIncluded
#define OptValsRegHhIncluded


openKangarooSpace
#define AutoClsOptValSd (SelcStub<Sf>::SelcCat * 10000 + (thisLine - AutoClsBaseOptValSd))
enum { AutoClsBaseOptValSd = thisLine};
closeKangarooSpace

#include "cbls/selcs/sfs/sds/optvals/opt1val1statrangesdvzt.tcc"
openKangarooSpace
rti(Opt1Val1StatRangeSdVZt<Int, Bln, Dsc >) scln(MaxVal1StatRangeSdViZb,AutoClsOptValSd);
rti(Opt1Val1StatRangeSdVZt<Int, Int, Dsc >) scln(MaxVal1StatRangeSdViZi,AutoClsOptValSd);
rti(Opt1Val1StatRangeSdVZt<Int, Flt, Dsc >) scln(MaxVal1StatRangeSdViZf,AutoClsOptValSd);

rti(Opt1Val1StatRangeSdVZt<Flt, Bln, Dsc >) scln(MaxVal1StatRangeSdVfZb,AutoClsOptValSd);
rti(Opt1Val1StatRangeSdVZt<Flt, Int, Dsc >) scln(MaxVal1StatRangeSdVfZi,AutoClsOptValSd);
rti(Opt1Val1StatRangeSdVZt<Flt, Flt, Dsc >) scln(MaxVal1StatRangeSdVfZf,AutoClsOptValSd);

rti(Opt1Val1StatRangeSdVZt<Int, Bln, Asc >) scln(MinVal1StatRangeSdViZb,AutoClsOptValSd);
rti(Opt1Val1StatRangeSdVZt<Int, Int, Asc >) scln(MinVal1StatRangeSdViZi,AutoClsOptValSd);
rti(Opt1Val1StatRangeSdVZt<Int, Flt, Asc >) scln(MinVal1StatRangeSdViZf,AutoClsOptValSd);

rti(Opt1Val1StatRangeSdVZt<Flt, Bln, Asc >) scln(MinVal1StatRangeSdVfZb,AutoClsOptValSd);
rti(Opt1Val1StatRangeSdVZt<Flt, Int, Asc >) scln(MinVal1StatRangeSdVfZi,AutoClsOptValSd);
rti(Opt1Val1StatRangeSdVZt<Flt, Flt, Asc >) scln(MinVal1StatRangeSdVfZf,AutoClsOptValSd);
closeKangarooSpace


#include "cbls/selcs/sfs/sds/optvals/opt2val1statrangesdvzt.tcc"
openKangarooSpace
rti(Opt2Val1StatRangeSdVZt<Int, Bln, Dsc,Dsc >) scln(MaxMaxVal1StatRangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Int, Int, Dsc,Dsc >) scln(MaxMaxVal1StatRangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Int, Flt, Dsc,Dsc >) scln(MaxMaxVal1StatRangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Bln, Dsc,Dsc >) scln(MaxMaxVal1StatRangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Int, Dsc,Dsc >) scln(MaxMaxVal1StatRangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Flt, Dsc,Dsc >) scln(MaxMaxVal1StatRangeSdVfZf,AutoClsOptValSd);

rti(Opt2Val1StatRangeSdVZt<Int, Bln, Dsc,Asc >) scln(MaxMinVal1StatRangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Int, Int, Dsc,Asc >) scln(MaxMinVal1StatRangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Int, Flt, Dsc,Asc >) scln(MaxMinVal1StatRangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Bln, Dsc,Asc >) scln(MaxMinVal1StatRangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Int, Dsc,Asc >) scln(MaxMinVal1StatRangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Flt, Dsc,Asc >) scln(MaxMinVal1StatRangeSdVfZf,AutoClsOptValSd);

rti(Opt2Val1StatRangeSdVZt<Int, Bln, Asc,Dsc >) scln(MinMaxVal1StatRangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Int, Int, Asc,Dsc >) scln(MinMaxVal1StatRangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Int, Flt, Asc,Dsc >) scln(MinMaxVal1StatRangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Bln, Asc,Dsc >) scln(MinMaxVal1StatRangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Int, Asc,Dsc >) scln(MinMaxVal1StatRangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Flt, Asc,Dsc >) scln(MinMaxVal1StatRangeSdVfZf,AutoClsOptValSd);

rti(Opt2Val1StatRangeSdVZt<Int, Bln, Asc,Asc >) scln(MinMinVal1StatRangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Int, Int, Asc,Asc >) scln(MinMinVal1StatRangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Int, Flt, Asc,Asc >) scln(MinMinVal1StatRangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Bln, Asc,Asc >) scln(MinMinVal1StatRangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Int, Asc,Asc >) scln(MinMinVal1StatRangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1StatRangeSdVZt<Flt, Flt, Asc,Asc >) scln(MinMinVal1StatRangeSdVfZf,AutoClsOptValSd);
closeKangarooSpace


#include "cbls/selcs/sfs/sds/optvals/opt1val1dynarangesdvzt.tcc"
openKangarooSpace
rti(Opt1Val1DynaRangeSdVZt<Int, Bln, Dsc >) scln(MaxVal1DynaRangeSdViZb,AutoClsOptValSd);
rti(Opt1Val1DynaRangeSdVZt<Int, Int, Dsc >) scln(MaxVal1DynaRangeSdViZi,AutoClsOptValSd);
rti(Opt1Val1DynaRangeSdVZt<Int, Flt, Dsc >) scln(MaxVal1DynaRangeSdViZf,AutoClsOptValSd);

rti(Opt1Val1DynaRangeSdVZt<Flt, Bln, Dsc >) scln(MaxVal1DynaRangeSdVfZb,AutoClsOptValSd);
rti(Opt1Val1DynaRangeSdVZt<Flt, Int, Dsc >) scln(MaxVal1DynaRangeSdVfZi,AutoClsOptValSd);
rti(Opt1Val1DynaRangeSdVZt<Flt, Flt, Dsc >) scln(MaxVal1DynaRangeSdVfZf,AutoClsOptValSd);

rti(Opt1Val1DynaRangeSdVZt<Int, Bln, Asc >) scln(MinVal1DynaRangeSdViZb,AutoClsOptValSd);
rti(Opt1Val1DynaRangeSdVZt<Int, Int, Asc >) scln(MinVal1DynaRangeSdViZi,AutoClsOptValSd);
rti(Opt1Val1DynaRangeSdVZt<Int, Flt, Asc >) scln(MinVal1DynaRangeSdViZf,AutoClsOptValSd);

rti(Opt1Val1DynaRangeSdVZt<Flt, Bln, Asc >) scln(MinVal1DynaRangeSdVfZb,AutoClsOptValSd);
rti(Opt1Val1DynaRangeSdVZt<Flt, Int, Asc >) scln(MinVal1DynaRangeSdVfZi,AutoClsOptValSd);
rti(Opt1Val1DynaRangeSdVZt<Flt, Flt, Asc >) scln(MinVal1DynaRangeSdVfZf,AutoClsOptValSd);
closeKangarooSpace



#include "cbls/selcs/sfs/sds/optvals/opt2val1dynarangesdvzt.tcc"
openKangarooSpace
rti(Opt2Val1DynaRangeSdVZt<Int, Bln, Dsc,Dsc >) scln(MaxMaxVal1DynaRangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Int, Int, Dsc,Dsc >) scln(MaxMaxVal1DynaRangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Int, Flt, Dsc,Dsc >) scln(MaxMaxVal1DynaRangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Bln, Dsc,Dsc >) scln(MaxMaxVal1DynaRangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Int, Dsc,Dsc >) scln(MaxMaxVal1DynaRangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Flt, Dsc,Dsc >) scln(MaxMaxVal1DynaRangeSdVfZf,AutoClsOptValSd);

rti(Opt2Val1DynaRangeSdVZt<Int, Bln, Dsc,Asc >) scln(MaxMinVal1DynaRangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Int, Int, Dsc,Asc >) scln(MaxMinVal1DynaRangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Int, Flt, Dsc,Asc >) scln(MaxMinVal1DynaRangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Bln, Dsc,Asc >) scln(MaxMinVal1DynaRangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Int, Dsc,Asc >) scln(MaxMinVal1DynaRangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Flt, Dsc,Asc >) scln(MaxMinVal1DynaRangeSdVfZf,AutoClsOptValSd);

rti(Opt2Val1DynaRangeSdVZt<Int, Bln, Asc,Dsc >) scln(MinMaxVal1DynaRangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Int, Int, Asc,Dsc >) scln(MinMaxVal1DynaRangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Int, Flt, Asc,Dsc >) scln(MinMaxVal1DynaRangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Bln, Asc,Dsc >) scln(MinMaxVal1DynaRangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Int, Asc,Dsc >) scln(MinMaxVal1DynaRangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Flt, Asc,Dsc >) scln(MinMaxVal1DynaRangeSdVfZf,AutoClsOptValSd);

rti(Opt2Val1DynaRangeSdVZt<Int, Bln, Asc,Asc >) scln(MinMinVal1DynaRangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Int, Int, Asc,Asc >) scln(MinMinVal1DynaRangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Int, Flt, Asc,Asc >) scln(MinMinVal1DynaRangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Bln, Asc,Asc >) scln(MinMinVal1DynaRangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Int, Asc,Asc >) scln(MinMinVal1DynaRangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1DynaRangeSdVZt<Flt, Flt, Asc,Asc >) scln(MinMinVal1DynaRangeSdVfZf,AutoClsOptValSd);
closeKangarooSpace



#include "cbls/selcs/sfs/sds/optvals/opt1val1rangesdvzt.tcc"
openKangarooSpace
rti(Opt1Val1RangeSdVZt<Int, Bln, Dsc >) scln(MaxVal1RangeSdViZb,AutoClsOptValSd);
rti(Opt1Val1RangeSdVZt<Int, Int, Dsc >) scln(MaxVal1RangeSdViZi,AutoClsOptValSd);
rti(Opt1Val1RangeSdVZt<Int, Flt, Dsc >) scln(MaxVal1RangeSdViZf,AutoClsOptValSd);

rti(Opt1Val1RangeSdVZt<Flt, Bln, Dsc >) scln(MaxVal1RangeSdVfZb,AutoClsOptValSd);
rti(Opt1Val1RangeSdVZt<Flt, Int, Dsc >) scln(MaxVal1RangeSdVfZi,AutoClsOptValSd);
rti(Opt1Val1RangeSdVZt<Flt, Flt, Dsc >) scln(MaxVal1RangeSdVfZf,AutoClsOptValSd);

rti(Opt1Val1RangeSdVZt<Int, Bln, Asc >) scln(MinVal1RangeSdViZb,AutoClsOptValSd);
rti(Opt1Val1RangeSdVZt<Int, Int, Asc >) scln(MinVal1RangeSdViZi,AutoClsOptValSd);
rti(Opt1Val1RangeSdVZt<Int, Flt, Asc >) scln(MinVal1RangeSdViZf,AutoClsOptValSd);

rti(Opt1Val1RangeSdVZt<Flt, Bln, Asc >) scln(MinVal1RangeSdVfZb,AutoClsOptValSd);
rti(Opt1Val1RangeSdVZt<Flt, Int, Asc >) scln(MinVal1RangeSdVfZi,AutoClsOptValSd);
rti(Opt1Val1RangeSdVZt<Flt, Flt, Asc >) scln(MinVal1RangeSdVfZf,AutoClsOptValSd);
closeKangarooSpace



#include "cbls/selcs/sfs/sds/optvals/opt2val1rangesdvzt.tcc"
openKangarooSpace
rti(Opt2Val1RangeSdVZt<Int, Bln, Dsc,Dsc >) scln(MaxMaxVal1RangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Int, Int, Dsc,Dsc >) scln(MaxMaxVal1RangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Int, Flt, Dsc,Dsc >) scln(MaxMaxVal1RangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Bln, Dsc,Dsc >) scln(MaxMaxVal1RangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Int, Dsc,Dsc >) scln(MaxMaxVal1RangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Flt, Dsc,Dsc >) scln(MaxMaxVal1RangeSdVfZf,AutoClsOptValSd);

rti(Opt2Val1RangeSdVZt<Int, Bln, Dsc,Asc >) scln(MaxMinVal1RangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Int, Int, Dsc,Asc >) scln(MaxMinVal1RangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Int, Flt, Dsc,Asc >) scln(MaxMinVal1RangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Bln, Dsc,Asc >) scln(MaxMinVal1RangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Int, Dsc,Asc >) scln(MaxMinVal1RangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Flt, Dsc,Asc >) scln(MaxMinVal1RangeSdVfZf,AutoClsOptValSd);

rti(Opt2Val1RangeSdVZt<Int, Bln, Asc,Dsc >) scln(MinMaxVal1RangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Int, Int, Asc,Dsc >) scln(MinMaxVal1RangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Int, Flt, Asc,Dsc >) scln(MinMaxVal1RangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Bln, Asc,Dsc >) scln(MinMaxVal1RangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Int, Asc,Dsc >) scln(MinMaxVal1RangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Flt, Asc,Dsc >) scln(MinMaxVal1RangeSdVfZf,AutoClsOptValSd);

rti(Opt2Val1RangeSdVZt<Int, Bln, Asc,Asc >) scln(MinMinVal1RangeSdViZb,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Int, Int, Asc,Asc >) scln(MinMinVal1RangeSdViZi,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Int, Flt, Asc,Asc >) scln(MinMinVal1RangeSdViZf,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Bln, Asc,Asc >) scln(MinMinVal1RangeSdVfZb,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Int, Asc,Asc >) scln(MinMinVal1RangeSdVfZi,AutoClsOptValSd);
rti(Opt2Val1RangeSdVZt<Flt, Flt, Asc,Asc >) scln(MinMinVal1RangeSdVfZf,AutoClsOptValSd);
closeKangarooSpace



#endif // OptValsRegHhIncluded
