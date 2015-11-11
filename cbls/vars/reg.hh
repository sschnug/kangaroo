/*!
	@file vars/reg.hh
	@brief The register header file for vars.
	@details This is the register header file for vars.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef VarsRegsHhIncluded
#define VarsRegsHhIncluded


#include "cbls/vars/flipvar.hpp"
#include "cbls/vars/rangevar.hpp"
#include "cbls/vars/listvar.hpp"


#include "cbls/vars/rangevarvt.tcc"
openKangarooSpace
#define AutoTypRangeVar (TermStub<RangeVar>::TermCat * 10 + (thisLine - AutoTypBaseRangeVar))
enum { AutoTypBaseRangeVar = thisLine};
rti(RangeVarVt<Bln>) ttpn(RangeVarVb, AutoTypRangeVar);
rti(RangeVarVt<Int>) ttpn(RangeVarVi, AutoTypRangeVar);
rti(RangeVarVt<Flt>) ttpn(RangeVarVf, AutoTypRangeVar);
closeKangarooSpace


openKangarooSpace
#define AutoClsRangeVar (TermStub<RangeVar>::TermCat * 100 + (thisLine - AutoClsBaseRangeVar))
enum { AutoClsBaseRangeVar = thisLine};
dec tcln(StatRangeVarVi, AutoClsRangeVar);
dec tcln(StatRangeVarVf, AutoClsRangeVar);
dec tcln(DynaRangeCtlVarVi, AutoClsRangeVar);
dec tcln(DynaRangeCtlVarVf, AutoClsRangeVar);
dec tcln(DynaRangeChgVarVi, AutoClsRangeVar);
dec tcln(DynaRangeChgVarVf, AutoClsRangeVar);
closeKangarooSpace


#include "cbls/vars/flipvarvt.tcc"
openKangarooSpace
#define AutoTypFlipVar (TermStub<FlipVar>::TermCat * 10 + (thisLine - AutoTypBaseFlipVar))
enum { AutoTypBaseFlipVar = thisLine};
rti(FlipVarVt<Bln>) ttpn(FlipVarVb, AutoTypFlipVar);
rti(FlipVarVt<Int>) ttpn(FlipVarVi, AutoTypFlipVar);
rti(FlipVarVt<Flt>) ttpn(FlipVarVf, AutoTypFlipVar);
closeKangarooSpace


openKangarooSpace
#define AutoClsFlipVar (TermStub<FlipVar>::TermCat * 100 + (thisLine - AutoClsBaseFlipVar))
enum { AutoClsBaseFlipVar = thisLine};
dec tcln(PropFlipVarVb, AutoClsFlipVar);
dec tcln(PropFlipVarVi, AutoClsFlipVar);
dec tcln(PropFlipVarVf, AutoClsFlipVar);
closeKangarooSpace



//#include "cbls/vars/rngvi.hpp"
//#include "cbls/vars/rngchgvi.hpp"
//#include "cbls/vars/rngctlvi.hpp"
//#include "cbls/vars/rngctlvf.hpp"
//#include "cbls/vars/rngvilu.hpp"
//#include "cbls/vars/rngvf.hpp"

//	boolean flip
//	integer flip
//	real flip
//	integer list
//  real list

//  continuous range
//	enum integer range


#endif//VarsRegsHhIncluded
