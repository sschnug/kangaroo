/*!
	@file consts/reg.hpp
	@brief The register header file for consts.
	@details This is the register header file for consts.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 10.01.2012 QRL NICTA www.nicta.com.au
*/


#ifndef ConstsRegHppIncluded
#define ConstsRegHppIncluded


#include "cbls/consts/constv.hpp"

#include "cbls/consts/constvt.tcc"
openKangarooSpace

#define AutoClsConstV (TermStub<ConstV>::TermCat * 10 + (thisLine - AutoClsBaseConstV))
enum { AutoClsBaseConstV = thisLine};
rti(ConstVt<Bln>) ttpcln(ConstVb, AutoClsConstV, AutoClsConstV);
rti(ConstVt<Int>) ttpcln(ConstVi, AutoClsConstV, AutoClsConstV);
rti(ConstVt<Flt>) ttpcln(ConstVf, AutoClsConstV, AutoClsConstV);


closeKangarooSpace



#endif//ConstsRegHppIncluded
