/*!
	@file sps/reg.hh
	@brief The register header file for sps.
	@details This is the register header file for sps.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef SpsRegHhIncluded
#define SpsRegHhIncluded


#include "cbls/frames/idx.hh"
#include "cbls/selcs/sps/spxt.tcc"


openKangarooSpace
#define AutoTypSp (SelcStub<Sp>::SelcCat * 10 + (thisLine - AutoTypBaseSp))
enum { AutoTypBaseSp = thisLine};
rti(SpXt<Nil>) stpn(SpXn, AutoTypSp);
rti(SpXt<Bln>) stpn(SpXb, AutoTypSp);
rti(SpXt<Int>) stpn(SpXi, AutoTypSp);
rti(SpXt<Flt>) stpn(SpXf, AutoTypSp);
closeKangarooSpace

openKangarooSpace
#define AutoClsSp (SelcStub<Sp>::SelcCat * 10000 + (thisLine - AutoClsBaseSp))
enum { AutoClsBaseSp = thisLine};
dec scln(SameFuncVar1Sp,AutoClsSp);
dec scln(LockSameFuncVar1Sp,AutoClsSp);
dec scln(SvTabuSameFuncVar1Sp,AutoClsSp);
dec scln(SvTabuLockSameFuncVar1Sp,AutoClsSp);

dec scln(RankedHintVar1Sp,AutoClsSp);
dec scln(RankedRateVar1Sp,AutoClsSp);
closeKangarooSpace

#endif
