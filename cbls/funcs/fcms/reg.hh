/*!
	@file funcs/fcms/reg.hh
	@brief The register header file for fcms.
	@details This is the register header file for fcms.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef FcMsRegHhIncluded
#define FcMsRegHhIncluded

#include "cbls/funcs/opfns/idx.hh"

#include "cbls/funcs/fcms/fcmt.tcc"
openKangarooSpace
#define AutoTypFcM (TermStub<FcM>::TermCat * 10 + (thisLine - AutoTypBaseFcM))
enum { AutoTypBaseFcM = thisLine};
rti(FcMt<Bln>) ttpn(FcMb,AutoTypFcM);
rti(FcMt<Int>) ttpn(FcMi,AutoTypFcM);
rti(FcMt<Flt>) ttpn(FcMf,AutoTypFcM);
closeKangarooSpace


#include "cbls/funcs/fcms/segfcmt.tcc"
openKangarooSpace
rti(SegFcMt<Bln>) tia(SegFcMb);
rti(SegFcMt<Int>) tia(SegFcMi);
rti(SegFcMt<Flt>) tia(SegFcMf);
closeKangarooSpace


#include "cbls/funcs/fcms/aggfcmt.tcc"
openKangarooSpace
rti(AggFcMt<Bln>) tia(AggFcMb);
rti(AggFcMt<Int>) tia(AggFcMi);
rti(AggFcMt<Flt>) tia(AggFcMf);
closeKangarooSpace


#include "cbls/funcs/fcms/muxfcmt.tcc"
openKangarooSpace
rti(MuxFcMt<Bln>) tia(MuxFcMb);
rti(MuxFcMt<Int>) tia(MuxFcMi);
rti(MuxFcMt<Flt>) tia(MuxFcMf);
closeKangarooSpace


#endif//FcMsRegHhIncluded
