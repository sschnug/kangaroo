/*!
	@file funcs/fevs/reg.hh
	@brief The register header file for fevs.
	@details This is the register header file for fevs.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef FeVsRegHhIncluded
#define FeVsRegHhIncluded

#include "cbls/funcs/opfns/idx.hh"

#include "cbls/funcs/fevs/fevt.tcc"
openKangarooSpace
#define AutoTypFeV (TermStub<FeV>::TermCat * 10 + (thisLine - AutoTypBaseFeV))
enum { AutoTypBaseFeV = thisLine};
rti(FeVt<Bln>) ttpn(FeVb,AutoTypFeV);
rti(FeVt<Int>) ttpn(FeVi,AutoTypFeV);
rti(FeVt<Flt>) ttpn(FeVf,AutoTypFeV);
closeKangarooSpace


#include "cbls/funcs/fevs/segfevt.tcc"
openKangarooSpace
rti(SegFeVt<Bln>) tia(SegFeVb);
rti(SegFeVt<Int>) tia(SegFeVi);
rti(SegFeVt<Flt>) tia(SegFeVf);
closeKangarooSpace


#include "cbls/funcs/fevs/aggfevt.tcc"
openKangarooSpace
rti(AggFeVt<Bln>) tia(AggFeVb);
rti(AggFeVt<Int>) tia(AggFeVi);
rti(AggFeVt<Flt>) tia(AggFeVf);
closeKangarooSpace


#include "cbls/funcs/fevs/muxfevt.tcc"
openKangarooSpace
rti(MuxFeVt<Bln>) tia(MuxFeVb);
rti(MuxFeVt<Int>) tia(MuxFeVi);
rti(MuxFeVt<Flt>) tia(MuxFeVf);
closeKangarooSpace


#endif//FeVsRegHhIncluded
