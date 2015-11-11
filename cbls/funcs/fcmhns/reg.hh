/*!
	@file funcs/fcmhns/reg.hh
	@brief The register header file for fcmhns.
	@details This is the register header file for fcmhns.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef FcMHnsRegHhIncluded
#define FcMHnsRegHhIncluded


#include "cbls/frames/idx.hh"
#include "cbls/funcs/opfns/idx.hh"


openKangarooSpace
#define AutoTypFcMHn (TermStub<FcMHn>::TermCat * 10 + (thisLine - AutoTypBaseFcMHn))
enum { AutoTypBaseFcMHn = thisLine};
closeKangarooSpace



#include "cbls/funcs/fcmhns/fcmhnt.tcc"
openKangarooSpace
rti(FcMHnT<Bln>) ttpn(FcMbHn,AutoTypFcMHn);
rti(FcMHnT<Int>) ttpn(FcMiHn,AutoTypFcMHn);
rti(FcMHnT<Flt>) ttpn(FcMfHn,AutoTypFcMHn);
closeKangarooSpace



#include "cbls/funcs/fcmhns/aggofcmhnt.tcc"
openKangarooSpace
rti(AggOFcMHnT<Bln>) tia(AggOFcMbHn);
rti(AggOFcMHnT<Int>) tia(AggOFcMiHn);
rti(AggOFcMHnT<Flt>) tia(AggOFcMfHn);
closeKangarooSpace



#include "cbls/funcs/fcmhns/agghfcmhnt.tcc"
openKangarooSpace
rti(AggHFcMHnT<Bln>) tia(AggHFcMbHn);
rti(AggHFcMHnT<Int>) tia(AggHFcMiHn);
rti(AggHFcMHnT<Flt>) tia(AggHFcMfHn);
closeKangarooSpace



#include "cbls/funcs/fcmhns/aggefcmhnt.tcc"
openKangarooSpace
rti(AggEFcMHnT<Bln>) tia(AggEFcMbHn);
rti(AggEFcMHnT<Int>) tia(AggEFcMiHn);
rti(AggEFcMHnT<Flt>) tia(AggEFcMfHn);
closeKangarooSpace


#include "cbls/funcs/fcmhns/aggfcmhnt.tcc"
openKangarooSpace
rti(AggFcMHnT<Bln>) tia(AggFcMbHn);
rti(AggFcMHnT<Int>) tia(AggFcMiHn);
rti(AggFcMHnT<Flt>) tia(AggFcMfHn);
closeKangarooSpace

#endif//FcMHnsRegHhIncluded
