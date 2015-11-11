/*!
	@file sss/reg.hh
	@brief The register header file for sss.
	@details This is the register header file for sss.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef SssRegHhIncluded
#define SssRegHhIncluded


#include "cbls/frames/idx.hh"
#include "cbls/selcs/sfs/sss/sszt.tcc"


openKangarooSpace
#define AutoTypSs (SelcStub<Sf>::SelcCat * 100 + (thisLine - AutoTypBaseSs))
enum { AutoTypBaseSs = thisLine};
rti(SsZt<Bln>) stpn(SsZb, AutoTypSs);
rti(SsZt<Int>) stpn(SsZi, AutoTypSs);
rti(SsZt<Flt>) stpn(SsZf, AutoTypSs);
closeKangarooSpace



openKangarooSpace
#define AutoClsSs (SelcStub<Sf>::SelcCat * 3000 + (thisLine - AutoClsBaseSs))
enum { AutoClsBaseSs = thisLine};
closeKangarooSpace

#include "cbls/selcs/sfs/sss/optidensszt.tcc"
openKangarooSpace
rti(OptIdenSsZt<Bln, Dsc >) scln(MaxIdenSsZb,AutoClsSs);
rti(OptIdenSsZt<Bln, Asc >) scln(MinIdenSsZb,AutoClsSs);

rti(OptIdenSsZt<Int, Dsc >) scln(MaxIdenSsZi,AutoClsSs);
rti(OptIdenSsZt<Int, Asc >) scln(MinIdenSsZi,AutoClsSs);

rti(OptIdenSsZt<Flt, Dsc >) scln(MaxIdenSsZf,AutoClsSs);
rti(OptIdenSsZt<Flt, Asc >) scln(MinIdenSsZf,AutoClsSs);
closeKangarooSpace

#include "cbls/selcs/sfs/sss/optcompatsszt.tcc"
openKangarooSpace
rti(OptCompatSsZt<Bln, Dsc >) scln(MaxCompatSsZb,AutoClsSs);
rti(OptCompatSsZt<Bln, Asc >) scln(MinCompatSsZb,AutoClsSs);

rti(OptCompatSsZt<Int, Dsc >) scln(MaxCompatSsZi,AutoClsSs);
rti(OptCompatSsZt<Int, Asc >) scln(MinCompatSsZi,AutoClsSs);

rti(OptCompatSsZt<Flt, Dsc >) scln(MaxCompatSsZf,AutoClsSs);
rti(OptCompatSsZt<Flt, Asc >) scln(MinCompatSsZf,AutoClsSs);
closeKangarooSpace

#include "cbls/selcs/sfs/sss/lockoptidensszt.tcc"
openKangarooSpace
rti(LockOptIdenSsZt<Bln, Dsc >) scln(LockMaxIdenSsZb,AutoClsSs);
rti(LockOptIdenSsZt<Bln, Asc >) scln(LockMinIdenSsZb,AutoClsSs);

rti(LockOptIdenSsZt<Int, Dsc >) scln(LockMaxIdenSsZi,AutoClsSs);
rti(LockOptIdenSsZt<Int, Asc >) scln(LockMinIdenSsZi,AutoClsSs);

rti(LockOptIdenSsZt<Flt, Dsc >) scln(LockMaxIdenSsZf,AutoClsSs);
rti(LockOptIdenSsZt<Flt, Asc >) scln(LockMinIdenSsZf,AutoClsSs);
closeKangarooSpace

#include "cbls/selcs/sfs/sss/lockoptcompatsszt.tcc"
openKangarooSpace
rti(LockOptCompatSsZt<Bln, Dsc >) scln(LockMaxCompatSsZb,AutoClsSs);
rti(LockOptCompatSsZt<Bln, Asc >) scln(LockMinCompatSsZb,AutoClsSs);

rti(LockOptCompatSsZt<Int, Dsc >) scln(LockMaxCompatSsZi,AutoClsSs);
rti(LockOptCompatSsZt<Int, Asc >) scln(LockMinCompatSsZi,AutoClsSs);

rti(LockOptCompatSsZt<Flt, Dsc >) scln(LockMaxCompatSsZf,AutoClsSs);
rti(LockOptCompatSsZt<Flt, Asc >) scln(LockMinCompatSsZf,AutoClsSs);
closeKangarooSpace


#include "cbls/selcs/sfs/sss/svtabuoptidensszt.tcc"
openKangarooSpace
rti(SvTabuOptIdenSsZt<Bln, Dsc >) scln(SvTabuMaxIdenSsZb,AutoClsSs);
rti(SvTabuOptIdenSsZt<Bln, Asc >) scln(SvTabuMinIdenSsZb,AutoClsSs);

rti(SvTabuOptIdenSsZt<Int, Dsc >) scln(SvTabuMaxIdenSsZi,AutoClsSs);
rti(SvTabuOptIdenSsZt<Int, Asc >) scln(SvTabuMinIdenSsZi,AutoClsSs);

rti(SvTabuOptIdenSsZt<Flt, Dsc >) scln(SvTabuMaxIdenSsZf,AutoClsSs);
rti(SvTabuOptIdenSsZt<Flt, Asc >) scln(SvTabuMinIdenSsZf,AutoClsSs);
closeKangarooSpace

#include "cbls/selcs/sfs/sss/svtabuoptcompatsszt.tcc"
openKangarooSpace
rti(SvTabuOptCompatSsZt<Bln, Dsc >) scln(SvTabuMaxCompatSsZb,AutoClsSs);
rti(SvTabuOptCompatSsZt<Bln, Asc >) scln(SvTabuMinCompatSsZb,AutoClsSs);

rti(SvTabuOptCompatSsZt<Int, Dsc >) scln(SvTabuMaxCompatSsZi,AutoClsSs);
rti(SvTabuOptCompatSsZt<Int, Asc >) scln(SvTabuMinCompatSsZi,AutoClsSs);

rti(SvTabuOptCompatSsZt<Flt, Dsc >) scln(SvTabuMaxCompatSsZf,AutoClsSs);
rti(SvTabuOptCompatSsZt<Flt, Asc >) scln(SvTabuMinCompatSsZf,AutoClsSs);
closeKangarooSpace


#include "cbls/selcs/sfs/sss/dvtabuoptidensszt.tcc"
openKangarooSpace
rti(DvTabuOptIdenSsZt<Bln, Dsc >) scln(DvTabuMaxIdenSsZb,AutoClsSs);
rti(DvTabuOptIdenSsZt<Bln, Asc >) scln(DvTabuMinIdenSsZb,AutoClsSs);

rti(DvTabuOptIdenSsZt<Int, Dsc >) scln(DvTabuMaxIdenSsZi,AutoClsSs);
rti(DvTabuOptIdenSsZt<Int, Asc >) scln(DvTabuMinIdenSsZi,AutoClsSs);

rti(DvTabuOptIdenSsZt<Flt, Dsc >) scln(DvTabuMaxIdenSsZf,AutoClsSs);
rti(DvTabuOptIdenSsZt<Flt, Asc >) scln(DvTabuMinIdenSsZf,AutoClsSs);
closeKangarooSpace

#include "cbls/selcs/sfs/sss/dvtabuoptcompatsszt.tcc"
openKangarooSpace
rti(DvTabuOptCompatSsZt<Bln, Dsc >) scln(DvTabuMaxCompatSsZb,AutoClsSs);
rti(DvTabuOptCompatSsZt<Bln, Asc >) scln(DvTabuMinCompatSsZb,AutoClsSs);

rti(DvTabuOptCompatSsZt<Int, Dsc >) scln(DvTabuMaxCompatSsZi,AutoClsSs);
rti(DvTabuOptCompatSsZt<Int, Asc >) scln(DvTabuMinCompatSsZi,AutoClsSs);

rti(DvTabuOptCompatSsZt<Flt, Dsc >) scln(DvTabuMaxCompatSsZf,AutoClsSs);
rti(DvTabuOptCompatSsZt<Flt, Asc >) scln(DvTabuMinCompatSsZf,AutoClsSs);
closeKangarooSpace


#include "cbls/selcs/sfs/sss/svtabulockoptidensszt.tcc"
openKangarooSpace
rti(SvTabuLockOptIdenSsZt<Bln, Dsc >) scln(SvTabuLockMaxIdenSsZb,AutoClsSs);
rti(SvTabuLockOptIdenSsZt<Bln, Asc >) scln(SvTabuLockMinIdenSsZb,AutoClsSs);

rti(SvTabuLockOptIdenSsZt<Int, Dsc >) scln(SvTabuLockMaxIdenSsZi,AutoClsSs);
rti(SvTabuLockOptIdenSsZt<Int, Asc >) scln(SvTabuLockMinIdenSsZi,AutoClsSs);

rti(SvTabuLockOptIdenSsZt<Flt, Dsc >) scln(SvTabuLockMaxIdenSsZf,AutoClsSs);
rti(SvTabuLockOptIdenSsZt<Flt, Asc >) scln(SvTabuLockMinIdenSsZf,AutoClsSs);
closeKangarooSpace

#include "cbls/selcs/sfs/sss/svtabulockoptcompatsszt.tcc"
openKangarooSpace
rti(SvTabuLockOptCompatSsZt<Bln, Dsc >) scln(SvTabuLockMaxCompatSsZb,AutoClsSs);
rti(SvTabuLockOptCompatSsZt<Bln, Asc >) scln(SvTabuLockMinCompatSsZb,AutoClsSs);

rti(SvTabuLockOptCompatSsZt<Int, Dsc >) scln(SvTabuLockMaxCompatSsZi,AutoClsSs);
rti(SvTabuLockOptCompatSsZt<Int, Asc >) scln(SvTabuLockMinCompatSsZi,AutoClsSs);

rti(SvTabuLockOptCompatSsZt<Flt, Dsc >) scln(SvTabuLockMaxCompatSsZf,AutoClsSs);
rti(SvTabuLockOptCompatSsZt<Flt, Asc >) scln(SvTabuLockMinCompatSsZf,AutoClsSs);
closeKangarooSpace


#include "cbls/selcs/sfs/sss/dvtabulockoptidensszt.tcc"
openKangarooSpace
rti(DvTabuLockOptIdenSsZt<Bln, Dsc >) scln(DvTabuLockMaxIdenSsZb,AutoClsSs);
rti(DvTabuLockOptIdenSsZt<Bln, Asc >) scln(DvTabuLockMinIdenSsZb,AutoClsSs);

rti(DvTabuLockOptIdenSsZt<Int, Dsc >) scln(DvTabuLockMaxIdenSsZi,AutoClsSs);
rti(DvTabuLockOptIdenSsZt<Int, Asc >) scln(DvTabuLockMinIdenSsZi,AutoClsSs);

rti(DvTabuLockOptIdenSsZt<Flt, Dsc >) scln(DvTabuLockMaxIdenSsZf,AutoClsSs);
rti(DvTabuLockOptIdenSsZt<Flt, Asc >) scln(DvTabuLockMinIdenSsZf,AutoClsSs);
closeKangarooSpace

#include "cbls/selcs/sfs/sss/dvtabulockoptcompatsszt.tcc"
openKangarooSpace
rti(DvTabuLockOptCompatSsZt<Bln, Dsc >) scln(DvTabuLockMaxCompatSsZb,AutoClsSs);
rti(DvTabuLockOptCompatSsZt<Bln, Asc >) scln(DvTabuLockMinCompatSsZb,AutoClsSs);

rti(DvTabuLockOptCompatSsZt<Int, Dsc >) scln(DvTabuLockMaxCompatSsZi,AutoClsSs);
rti(DvTabuLockOptCompatSsZt<Int, Asc >) scln(DvTabuLockMinCompatSsZi,AutoClsSs);

rti(DvTabuLockOptCompatSsZt<Flt, Dsc >) scln(DvTabuLockMaxCompatSsZf,AutoClsSs);
rti(DvTabuLockOptCompatSsZt<Flt, Asc >) scln(DvTabuLockMinCompatSsZf,AutoClsSs);
closeKangarooSpace


#endif
