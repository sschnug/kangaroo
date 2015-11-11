/*!
	@file sds/reg.hh
	@brief The register header file for sds.
	@details This is the register header file for sds.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef SdsRegHhIncluded
#define SdsRegHhIncluded


#include "cbls/frames/idx.hh"
#include "cbls/selcs/sfs/sds/sdzt.tcc"


openKangarooSpace
#define AutoTypSd (SelcStub<Sf>::SelcCat * 10 + (thisLine - AutoTypBaseSd))
enum { AutoTypBaseSd = thisLine};
rti(SdZt<Bln>) stpn(SdZb, AutoTypSd);
rti(SdZt<Int>) stpn(SdZi, AutoTypSd);
rti(SdZt<Flt>) stpn(SdZf, AutoTypSd);
closeKangarooSpace

#endif
