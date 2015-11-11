/*!
	@file aggfcmhns/reg.hh
	@brief The register header file for aggfcmhns.
	@details This is the register header file for aggfcmhns.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef AggFcMHnsRegHhIncluded
#define AggFcMHnsRegHhIncluded


#include "cbls/frames/idx.hh"
#include "cbls/funcs/opfns/idx.hh"


openKangarooSpace
#define AutoClsAggFcMHn (TermStub<FcMHn>::TermCat * 30000 + (thisLine - AutoClsBaseAggFcMHn))
enum { AutoClsBaseAggFcMHn = thisLine};
closeKangarooSpace


//#include "cbls/funcs/fcmhns/aggfcmhns/atmostserialcountxfcmhnt.tcc"
//openKangarooSpace
//rti(AtmostSerialCountXFcMHnT<Bln,Bln>) tcln(AtmostSerialCountXbFcMbHn,AutoClsAggFcMHn);
//rti(AtmostSerialCountXFcMHnT<Bln,Int>) tcln(AtmostSerialCountXbFcMiHn,AutoClsAggFcMHn);
//rti(AtmostSerialCountXFcMHnT<Bln,Flt>) tcln(AtmostSerialCountXbFcMfHn,AutoClsAggFcMHn);
//rti(AtmostSerialCountXFcMHnT<Int,Bln>) tcln(AtmostSerialCountXiFcMbHn,AutoClsAggFcMHn);
//rti(AtmostSerialCountXFcMHnT<Int,Int>) tcln(AtmostSerialCountXiFcMiHn,AutoClsAggFcMHn);
//rti(AtmostSerialCountXFcMHnT<Int,Flt>) tcln(AtmostSerialCountXiFcMfHn,AutoClsAggFcMHn);
//rti(AtmostSerialCountXFcMHnT<Flt,Bln>) tcln(AtmostSerialCountXfFcMbHn,AutoClsAggFcMHn);
//rti(AtmostSerialCountXFcMHnT<Flt,Int>) tcln(AtmostSerialCountXfFcMiHn,AutoClsAggFcMHn);
//rti(AtmostSerialCountXFcMHnT<Flt,Flt>) tcln(AtmostSerialCountXfFcMfHn,AutoClsAggFcMHn);
//closeKangarooSpace


#include "cbls/funcs/fcmhns/aggfcmhns/atmostvaluecountxfcmhnt.tcc"
openKangarooSpace
rti(AtmostValueCountXFcMHnT<Bln,Bln>) tcln(AtmostValueCountXbFcMbHn,AutoClsAggFcMHn);
rti(AtmostValueCountXFcMHnT<Bln,Int>) tcln(AtmostValueCountXbFcMiHn,AutoClsAggFcMHn);
rti(AtmostValueCountXFcMHnT<Bln,Flt>) tcln(AtmostValueCountXbFcMfHn,AutoClsAggFcMHn);
rti(AtmostValueCountXFcMHnT<Int,Bln>) tcln(AtmostValueCountXiFcMbHn,AutoClsAggFcMHn);
rti(AtmostValueCountXFcMHnT<Int,Int>) tcln(AtmostValueCountXiFcMiHn,AutoClsAggFcMHn);
rti(AtmostValueCountXFcMHnT<Int,Flt>) tcln(AtmostValueCountXiFcMfHn,AutoClsAggFcMHn);
rti(AtmostValueCountXFcMHnT<Flt,Bln>) tcln(AtmostValueCountXfFcMbHn,AutoClsAggFcMHn);
rti(AtmostValueCountXFcMHnT<Flt,Int>) tcln(AtmostValueCountXfFcMiHn,AutoClsAggFcMHn);
rti(AtmostValueCountXFcMHnT<Flt,Flt>) tcln(AtmostValueCountXfFcMfHn,AutoClsAggFcMHn);
closeKangarooSpace


#include "cbls/funcs/fcmhns/aggfcmhns/alldiffxfcmhnt.tcc"
openKangarooSpace
rti(AllDiffXFcMHnT<Bln,Bln>) tcln(AllDiffXbFcMbHn,AutoClsAggFcMHn);
rti(AllDiffXFcMHnT<Bln,Int>) tcln(AllDiffXbFcMiHn,AutoClsAggFcMHn);
rti(AllDiffXFcMHnT<Bln,Flt>) tcln(AllDiffXbFcMfHn,AutoClsAggFcMHn);
rti(AllDiffXFcMHnT<Int,Bln>) tcln(AllDiffXiFcMbHn,AutoClsAggFcMHn);
rti(AllDiffXFcMHnT<Int,Int>) tcln(AllDiffXiFcMiHn,AutoClsAggFcMHn);
rti(AllDiffXFcMHnT<Int,Flt>) tcln(AllDiffXiFcMfHn,AutoClsAggFcMHn);
rti(AllDiffXFcMHnT<Flt,Bln>) tcln(AllDiffXfFcMbHn,AutoClsAggFcMHn);
rti(AllDiffXFcMHnT<Flt,Int>) tcln(AllDiffXfFcMiHn,AutoClsAggFcMHn);
rti(AllDiffXFcMHnT<Flt,Flt>) tcln(AllDiffXfFcMfHn,AutoClsAggFcMHn);
closeKangarooSpace


#include "cbls/funcs/fcmhns/aggfcmhns/sumxofcmhnt.tcc"
openKangarooSpace
rti(SumXOFcMHnT<Bln,Int>) tcln(SumXbOFcMiHn,AutoClsAggFcMHn);
rti(SumXOFcMHnT<Int,Int>) tcln(SumXiOFcMiHn,AutoClsAggFcMHn);
rti(SumXOFcMHnT<Bln,Bln>) tcln(SumXbOFcMbHn,AutoClsAggFcMHn);
rti(SumXOFcMHnT<Int,Bln>) tcln(SumXiOFcMbHn,AutoClsAggFcMHn);

rti(SumXOFcMHnT<Bln,Flt>) tcln(SumXbOFcMfHn,AutoClsAggFcMHn);
rti(SumXOFcMHnT<Int,Flt>) tcln(SumXiOFcMfHn,AutoClsAggFcMHn);
rti(SumXOFcMHnT<Flt,Flt>) tcln(SumXfOFcMfHn,AutoClsAggFcMHn);
rti(SumXOFcMHnT<Flt,Int>) tcln(SumXfOFcMiHn,AutoClsAggFcMHn);
rti(SumXOFcMHnT<Flt,Bln>) tcln(SumXfOFcMbHn,AutoClsAggFcMHn);
closeKangarooSpace

#include "cbls/funcs/fcmhns/aggfcmhns/wghtsumkxofcmhnt.tcc"
openKangarooSpace
rti(WghtSumKXOFcMHnT<Bln,Bln,Bln>) tcln(WghtSumKbXbOFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Bln,Bln,Int>) tcln(WghtSumKbXbOFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Bln,Bln,Flt>) tcln(WghtSumKbXbOFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Bln,Int,Bln>) tcln(WghtSumKbXiOFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Bln,Int,Int>) tcln(WghtSumKbXiOFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Bln,Int,Flt>) tcln(WghtSumKbXiOFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Bln,Flt,Bln>) tcln(WghtSumKbXfOFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Bln,Flt,Int>) tcln(WghtSumKbXfOFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Bln,Flt,Flt>) tcln(WghtSumKbXfOFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Int,Bln,Bln>) tcln(WghtSumKiXbOFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Int,Bln,Int>) tcln(WghtSumKiXbOFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Int,Bln,Flt>) tcln(WghtSumKiXbOFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Int,Int,Bln>) tcln(WghtSumKiXiOFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Int,Int,Int>) tcln(WghtSumKiXiOFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Int,Int,Flt>) tcln(WghtSumKiXiOFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Int,Flt,Bln>) tcln(WghtSumKiXfOFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Int,Flt,Int>) tcln(WghtSumKiXfOFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Int,Flt,Flt>) tcln(WghtSumKiXfOFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Flt,Bln,Bln>) tcln(WghtSumKfXbOFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Flt,Bln,Int>) tcln(WghtSumKfXbOFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Flt,Bln,Flt>) tcln(WghtSumKfXbOFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Flt,Int,Bln>) tcln(WghtSumKfXiOFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Flt,Int,Int>) tcln(WghtSumKfXiOFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Flt,Int,Flt>) tcln(WghtSumKfXiOFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Flt,Flt,Bln>) tcln(WghtSumKfXfOFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Flt,Flt,Int>) tcln(WghtSumKfXfOFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXOFcMHnT<Flt,Flt,Flt>) tcln(WghtSumKfXfOFcMfHn,AutoClsAggFcMHn);
closeKangarooSpace


#include "cbls/funcs/fcmhns/aggfcmhns/sumxefcmhnt.tcc"
openKangarooSpace
rti(SumXEFcMHnT<Bln,Int>) tcln(SumXbEFcMiHn,AutoClsAggFcMHn);
rti(SumXEFcMHnT<Int,Int>) tcln(SumXiEFcMiHn,AutoClsAggFcMHn);
rti(SumXEFcMHnT<Bln,Bln>) tcln(SumXbEFcMbHn,AutoClsAggFcMHn);
rti(SumXEFcMHnT<Int,Bln>) tcln(SumXiEFcMbHn,AutoClsAggFcMHn);

rti(SumXEFcMHnT<Bln,Flt>) tcln(SumXbEFcMfHn,AutoClsAggFcMHn);
rti(SumXEFcMHnT<Int,Flt>) tcln(SumXiEFcMfHn,AutoClsAggFcMHn);
rti(SumXEFcMHnT<Flt,Flt>) tcln(SumXfEFcMfHn,AutoClsAggFcMHn);
rti(SumXEFcMHnT<Flt,Int>) tcln(SumXfEFcMiHn,AutoClsAggFcMHn);
rti(SumXEFcMHnT<Flt,Bln>) tcln(SumXfEFcMbHn,AutoClsAggFcMHn);
closeKangarooSpace


#include "cbls/funcs/fcmhns/aggfcmhns/wghtsumkxefcmhnt.tcc"
openKangarooSpace
rti(WghtSumKXEFcMHnT<Bln,Bln,Bln>) tcln(WghtSumKbXbEFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Bln,Bln,Int>) tcln(WghtSumKbXbEFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Bln,Bln,Flt>) tcln(WghtSumKbXbEFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Bln,Int,Bln>) tcln(WghtSumKbXiEFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Bln,Int,Int>) tcln(WghtSumKbXiEFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Bln,Int,Flt>) tcln(WghtSumKbXiEFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Bln,Flt,Bln>) tcln(WghtSumKbXfEFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Bln,Flt,Int>) tcln(WghtSumKbXfEFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Bln,Flt,Flt>) tcln(WghtSumKbXfEFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Int,Bln,Bln>) tcln(WghtSumKiXbEFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Int,Bln,Int>) tcln(WghtSumKiXbEFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Int,Bln,Flt>) tcln(WghtSumKiXbEFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Int,Int,Bln>) tcln(WghtSumKiXiEFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Int,Int,Int>) tcln(WghtSumKiXiEFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Int,Int,Flt>) tcln(WghtSumKiXiEFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Int,Flt,Bln>) tcln(WghtSumKiXfEFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Int,Flt,Int>) tcln(WghtSumKiXfEFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Int,Flt,Flt>) tcln(WghtSumKiXfEFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Flt,Bln,Bln>) tcln(WghtSumKfXbEFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Flt,Bln,Int>) tcln(WghtSumKfXbEFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Flt,Bln,Flt>) tcln(WghtSumKfXbEFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Flt,Int,Bln>) tcln(WghtSumKfXiEFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Flt,Int,Int>) tcln(WghtSumKfXiEFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Flt,Int,Flt>) tcln(WghtSumKfXiEFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Flt,Flt,Bln>) tcln(WghtSumKfXfEFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Flt,Flt,Int>) tcln(WghtSumKfXfEFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXEFcMHnT<Flt,Flt,Flt>) tcln(WghtSumKfXfEFcMfHn,AutoClsAggFcMHn);
closeKangarooSpace


#include "cbls/funcs/fcmhns/aggfcmhns/sumxhfcmhnt.tcc"
openKangarooSpace
rti(SumXHFcMHnT<Bln,Int>) tcln(SumXbHFcMiHn,AutoClsAggFcMHn);
rti(SumXHFcMHnT<Int,Int>) tcln(SumXiHFcMiHn,AutoClsAggFcMHn);
rti(SumXHFcMHnT<Bln,Bln>) tcln(SumXbHFcMbHn,AutoClsAggFcMHn);
rti(SumXHFcMHnT<Int,Bln>) tcln(SumXiHFcMbHn,AutoClsAggFcMHn);

rti(SumXHFcMHnT<Bln,Flt>) tcln(SumXbHFcMfHn,AutoClsAggFcMHn);
rti(SumXHFcMHnT<Int,Flt>) tcln(SumXiHFcMfHn,AutoClsAggFcMHn);
rti(SumXHFcMHnT<Flt,Flt>) tcln(SumXfHFcMfHn,AutoClsAggFcMHn);
rti(SumXHFcMHnT<Flt,Int>) tcln(SumXfHFcMiHn,AutoClsAggFcMHn);
rti(SumXHFcMHnT<Flt,Bln>) tcln(SumXfHFcMbHn,AutoClsAggFcMHn);
closeKangarooSpace


#include "cbls/funcs/fcmhns/aggfcmhns/wghtsumkxhfcmhnt.tcc"
openKangarooSpace
rti(WghtSumKXHFcMHnT<Bln,Bln,Bln>) tcln(WghtSumKbXbHFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Bln,Bln,Int>) tcln(WghtSumKbXbHFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Bln,Bln,Flt>) tcln(WghtSumKbXbHFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Bln,Int,Bln>) tcln(WghtSumKbXiHFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Bln,Int,Int>) tcln(WghtSumKbXiHFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Bln,Int,Flt>) tcln(WghtSumKbXiHFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Bln,Flt,Bln>) tcln(WghtSumKbXfHFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Bln,Flt,Int>) tcln(WghtSumKbXfHFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Bln,Flt,Flt>) tcln(WghtSumKbXfHFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Int,Bln,Bln>) tcln(WghtSumKiXbHFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Int,Bln,Int>) tcln(WghtSumKiXbHFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Int,Bln,Flt>) tcln(WghtSumKiXbHFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Int,Int,Bln>) tcln(WghtSumKiXiHFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Int,Int,Int>) tcln(WghtSumKiXiHFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Int,Int,Flt>) tcln(WghtSumKiXiHFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Int,Flt,Bln>) tcln(WghtSumKiXfHFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Int,Flt,Int>) tcln(WghtSumKiXfHFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Int,Flt,Flt>) tcln(WghtSumKiXfHFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Flt,Bln,Bln>) tcln(WghtSumKfXbHFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Flt,Bln,Int>) tcln(WghtSumKfXbHFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Flt,Bln,Flt>) tcln(WghtSumKfXbHFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Flt,Int,Bln>) tcln(WghtSumKfXiHFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Flt,Int,Int>) tcln(WghtSumKfXiHFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Flt,Int,Flt>) tcln(WghtSumKfXiHFcMfHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Flt,Flt,Bln>) tcln(WghtSumKfXfHFcMbHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Flt,Flt,Int>) tcln(WghtSumKfXfHFcMiHn,AutoClsAggFcMHn);
rti(WghtSumKXHFcMHnT<Flt,Flt,Flt>) tcln(WghtSumKfXfHFcMfHn,AutoClsAggFcMHn);
closeKangarooSpace

#endif // AggFcMHnsRegHhIncluded
