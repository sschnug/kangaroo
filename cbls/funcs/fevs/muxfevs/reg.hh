/*!
	@file muxfevs/reg.hh
	@brief The register header file for muxfevs.
	@details This is the register header file for muxfevs.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef MuxFeVsRegHhIncluded
#define MuxFeVsRegHhIncluded

#include "cbls/funcs/opfns/idx.hh"

openKangarooSpace
#define AutoClsMuxFeV (TermStub<FeV>::TermCat * 20000 + (thisLine - AutoClsBaseMuxFeV))
enum { AutoClsBaseMuxFeV = thisLine};
closeKangarooSpace


#include "cbls/funcs/fevs/muxfevs/lstidxxyfevt.tcc"
openKangarooSpace
rti(LstIdxXYFeVt<Int,Bln,Bln>) tcln(LstIdxXiYbFeVb,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Int,Bln,Int>) tcln(LstIdxXiYbFeVi,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Int,Int,Bln>) tcln(LstIdxXiYiFeVb,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Int,Int,Int>) tcln(LstIdxXiYiFeVi,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Int,Flt,Flt>) tcln(LstIdxXiYfFeVf,AutoClsMuxFeV);

rti(LstIdxXYFeVt<Bln,Bln,Bln>) tcln(LstIdxXbYbFeVb,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Bln,Bln,Int>) tcln(LstIdxXbYbFeVi,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Bln,Bln,Flt>) tcln(LstIdxXbYbFeVf,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Bln,Int,Bln>) tcln(LstIdxXbYiFeVb,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Bln,Int,Int>) tcln(LstIdxXbYiFeVi,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Bln,Int,Flt>) tcln(LstIdxXbYiFeVf,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Bln,Flt,Bln>) tcln(LstIdxXbYfFeVb,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Bln,Flt,Int>) tcln(LstIdxXbYfFeVi,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Bln,Flt,Flt>) tcln(LstIdxXbYfFeVf,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Int,Bln,Flt>) tcln(LstIdxXiYbFeVf,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Int,Int,Flt>) tcln(LstIdxXiYiFeVf,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Int,Flt,Bln>) tcln(LstIdxXiYfFeVb,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Int,Flt,Int>) tcln(LstIdxXiYfFeVi,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Flt,Bln,Bln>) tcln(LstIdxXfYbFeVb,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Flt,Bln,Int>) tcln(LstIdxXfYbFeVi,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Flt,Bln,Flt>) tcln(LstIdxXfYbFeVf,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Flt,Int,Bln>) tcln(LstIdxXfYiFeVb,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Flt,Int,Int>) tcln(LstIdxXfYiFeVi,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Flt,Int,Flt>) tcln(LstIdxXfYiFeVf,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Flt,Flt,Bln>) tcln(LstIdxXfYfFeVb,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Flt,Flt,Int>) tcln(LstIdxXfYfFeVi,AutoClsMuxFeV);
rti(LstIdxXYFeVt<Flt,Flt,Flt>) tcln(LstIdxXfYfFeVf,AutoClsMuxFeV);
closeKangarooSpace


#include "cbls/funcs/fevs/muxfevs/iftexyfevt.tcc"
openKangarooSpace
rti(IfteXYFeVt<Bln,Bln,Bln>) tcln(IfteXbYbFeVb,AutoClsMuxFeV);
rti(IfteXYFeVt<Bln,Bln,Int>) tcln(IfteXbYbFeVi,AutoClsMuxFeV);
rti(IfteXYFeVt<Bln,Int,Bln>) tcln(IfteXbYiFeVb,AutoClsMuxFeV);
rti(IfteXYFeVt<Bln,Int,Int>) tcln(IfteXbYiFeVi,AutoClsMuxFeV);
rti(IfteXYFeVt<Bln,Flt,Flt>) tcln(IfteXbYfFeVf,AutoClsMuxFeV);
rti(IfteXYFeVt<Int,Bln,Bln>) tcln(IfteXiYbFeVb,AutoClsMuxFeV);
rti(IfteXYFeVt<Int,Bln,Int>) tcln(IfteXiYbFeVi,AutoClsMuxFeV);
rti(IfteXYFeVt<Int,Int,Bln>) tcln(IfteXiYiFeVb,AutoClsMuxFeV);
rti(IfteXYFeVt<Int,Int,Int>) tcln(IfteXiYiFeVi,AutoClsMuxFeV);
rti(IfteXYFeVt<Int,Flt,Flt>) tcln(IfteXiYfFeVf,AutoClsMuxFeV);

rti(IfteXYFeVt<Bln,Bln,Flt>) tcln(IfteXbYbFeVf,AutoClsMuxFeV);
rti(IfteXYFeVt<Bln,Int,Flt>) tcln(IfteXbYiFeVf,AutoClsMuxFeV);
rti(IfteXYFeVt<Bln,Flt,Bln>) tcln(IfteXbYfFeVb,AutoClsMuxFeV);
rti(IfteXYFeVt<Bln,Flt,Int>) tcln(IfteXbYfFeVi,AutoClsMuxFeV);
rti(IfteXYFeVt<Int,Bln,Flt>) tcln(IfteXiYbFeVf,AutoClsMuxFeV);
rti(IfteXYFeVt<Int,Int,Flt>) tcln(IfteXiYiFeVf,AutoClsMuxFeV);
rti(IfteXYFeVt<Int,Flt,Bln>) tcln(IfteXiYfFeVb,AutoClsMuxFeV);
rti(IfteXYFeVt<Int,Flt,Int>) tcln(IfteXiYfFeVi,AutoClsMuxFeV);
rti(IfteXYFeVt<Flt,Bln,Bln>) tcln(IfteXfYbFeVb,AutoClsMuxFeV);
rti(IfteXYFeVt<Flt,Bln,Int>) tcln(IfteXfYbFeVi,AutoClsMuxFeV);
rti(IfteXYFeVt<Flt,Bln,Flt>) tcln(IfteXfYbFeVf,AutoClsMuxFeV);
rti(IfteXYFeVt<Flt,Int,Bln>) tcln(IfteXfYiFeVb,AutoClsMuxFeV);
rti(IfteXYFeVt<Flt,Int,Int>) tcln(IfteXfYiFeVi,AutoClsMuxFeV);
rti(IfteXYFeVt<Flt,Int,Flt>) tcln(IfteXfYiFeVf,AutoClsMuxFeV);
rti(IfteXYFeVt<Flt,Flt,Bln>) tcln(IfteXfYfFeVb,AutoClsMuxFeV);
rti(IfteXYFeVt<Flt,Flt,Int>) tcln(IfteXfYfFeVi,AutoClsMuxFeV);
rti(IfteXYFeVt<Flt,Flt,Flt>) tcln(IfteXfYfFeVf,AutoClsMuxFeV);
closeKangarooSpace


#include "cbls/funcs/fevs/muxfevs/iftxyfevt.tcc"
openKangarooSpace
rti(IftXYFeVt<Bln,Bln,Bln>) tcln(IftXbYbFeVb,AutoClsMuxFeV);
rti(IftXYFeVt<Bln,Bln,Int>) tcln(IftXbYbFeVi,AutoClsMuxFeV);
rti(IftXYFeVt<Bln,Int,Bln>) tcln(IftXbYiFeVb,AutoClsMuxFeV);
rti(IftXYFeVt<Bln,Int,Int>) tcln(IftXbYiFeVi,AutoClsMuxFeV);
rti(IftXYFeVt<Bln,Flt,Flt>) tcln(IftXbYfFeVf,AutoClsMuxFeV);
rti(IftXYFeVt<Int,Bln,Bln>) tcln(IftXiYbFeVb,AutoClsMuxFeV);
rti(IftXYFeVt<Int,Bln,Int>) tcln(IftXiYbFeVi,AutoClsMuxFeV);
rti(IftXYFeVt<Int,Int,Bln>) tcln(IftXiYiFeVb,AutoClsMuxFeV);
rti(IftXYFeVt<Int,Int,Int>) tcln(IftXiYiFeVi,AutoClsMuxFeV);
rti(IftXYFeVt<Int,Flt,Flt>) tcln(IftXiYfFeVf,AutoClsMuxFeV);

rti(IftXYFeVt<Bln,Bln,Flt>) tcln(IftXbYbFeVf,AutoClsMuxFeV);
rti(IftXYFeVt<Bln,Int,Flt>) tcln(IftXbYiFeVf,AutoClsMuxFeV);
rti(IftXYFeVt<Bln,Flt,Bln>) tcln(IftXbYfFeVb,AutoClsMuxFeV);
rti(IftXYFeVt<Bln,Flt,Int>) tcln(IftXbYfFeVi,AutoClsMuxFeV);
rti(IftXYFeVt<Int,Bln,Flt>) tcln(IftXiYbFeVf,AutoClsMuxFeV);
rti(IftXYFeVt<Int,Int,Flt>) tcln(IftXiYiFeVf,AutoClsMuxFeV);
rti(IftXYFeVt<Int,Flt,Bln>) tcln(IftXiYfFeVb,AutoClsMuxFeV);
rti(IftXYFeVt<Int,Flt,Int>) tcln(IftXiYfFeVi,AutoClsMuxFeV);
rti(IftXYFeVt<Flt,Bln,Bln>) tcln(IftXfYbFeVb,AutoClsMuxFeV);
rti(IftXYFeVt<Flt,Bln,Int>) tcln(IftXfYbFeVi,AutoClsMuxFeV);
rti(IftXYFeVt<Flt,Bln,Flt>) tcln(IftXfYbFeVf,AutoClsMuxFeV);
rti(IftXYFeVt<Flt,Int,Bln>) tcln(IftXfYiFeVb,AutoClsMuxFeV);
rti(IftXYFeVt<Flt,Int,Int>) tcln(IftXfYiFeVi,AutoClsMuxFeV);
rti(IftXYFeVt<Flt,Int,Flt>) tcln(IftXfYiFeVf,AutoClsMuxFeV);
rti(IftXYFeVt<Flt,Flt,Bln>) tcln(IftXfYfFeVb,AutoClsMuxFeV);
rti(IftXYFeVt<Flt,Flt,Int>) tcln(IftXfYfFeVi,AutoClsMuxFeV);
rti(IftXYFeVt<Flt,Flt,Flt>) tcln(IftXfYfFeVf,AutoClsMuxFeV);
closeKangarooSpace

#include "cbls/funcs/fevs/muxfevs/niftxyfevt.tcc"
openKangarooSpace
rti(NiftXYFeVt<Bln,Bln,Bln>) tcln(NiftXbYbFeVb,AutoClsMuxFeV);
rti(NiftXYFeVt<Bln,Bln,Int>) tcln(NiftXbYbFeVi,AutoClsMuxFeV);
rti(NiftXYFeVt<Bln,Int,Bln>) tcln(NiftXbYiFeVb,AutoClsMuxFeV);
rti(NiftXYFeVt<Bln,Int,Int>) tcln(NiftXbYiFeVi,AutoClsMuxFeV);
rti(NiftXYFeVt<Bln,Flt,Flt>) tcln(NiftXbYfFeVf,AutoClsMuxFeV);
rti(NiftXYFeVt<Int,Bln,Bln>) tcln(NiftXiYbFeVb,AutoClsMuxFeV);
rti(NiftXYFeVt<Int,Bln,Int>) tcln(NiftXiYbFeVi,AutoClsMuxFeV);
rti(NiftXYFeVt<Int,Int,Bln>) tcln(NiftXiYiFeVb,AutoClsMuxFeV);
rti(NiftXYFeVt<Int,Int,Int>) tcln(NiftXiYiFeVi,AutoClsMuxFeV);
rti(NiftXYFeVt<Int,Flt,Flt>) tcln(NiftXiYfFeVf,AutoClsMuxFeV);

rti(NiftXYFeVt<Bln,Bln,Flt>) tcln(NiftXbYbFeVf,AutoClsMuxFeV);
rti(NiftXYFeVt<Bln,Int,Flt>) tcln(NiftXbYiFeVf,AutoClsMuxFeV);
rti(NiftXYFeVt<Bln,Flt,Bln>) tcln(NiftXbYfFeVb,AutoClsMuxFeV);
rti(NiftXYFeVt<Bln,Flt,Int>) tcln(NiftXbYfFeVi,AutoClsMuxFeV);
rti(NiftXYFeVt<Int,Bln,Flt>) tcln(NiftXiYbFeVf,AutoClsMuxFeV);
rti(NiftXYFeVt<Int,Int,Flt>) tcln(NiftXiYiFeVf,AutoClsMuxFeV);
rti(NiftXYFeVt<Int,Flt,Bln>) tcln(NiftXiYfFeVb,AutoClsMuxFeV);
rti(NiftXYFeVt<Int,Flt,Int>) tcln(NiftXiYfFeVi,AutoClsMuxFeV);
rti(NiftXYFeVt<Flt,Bln,Bln>) tcln(NiftXfYbFeVb,AutoClsMuxFeV);
rti(NiftXYFeVt<Flt,Bln,Int>) tcln(NiftXfYbFeVi,AutoClsMuxFeV);
rti(NiftXYFeVt<Flt,Bln,Flt>) tcln(NiftXfYbFeVf,AutoClsMuxFeV);
rti(NiftXYFeVt<Flt,Int,Bln>) tcln(NiftXfYiFeVb,AutoClsMuxFeV);
rti(NiftXYFeVt<Flt,Int,Int>) tcln(NiftXfYiFeVi,AutoClsMuxFeV);
rti(NiftXYFeVt<Flt,Int,Flt>) tcln(NiftXfYiFeVf,AutoClsMuxFeV);
rti(NiftXYFeVt<Flt,Flt,Bln>) tcln(NiftXfYfFeVb,AutoClsMuxFeV);
rti(NiftXYFeVt<Flt,Flt,Int>) tcln(NiftXfYfFeVi,AutoClsMuxFeV);
rti(NiftXYFeVt<Flt,Flt,Flt>) tcln(NiftXfYfFeVf,AutoClsMuxFeV);
closeKangarooSpace


#include "cbls/funcs/fevs/muxfevs/ctlsumxyfevt.tcc"
openKangarooSpace
rti(CtlSumXYFeVt<Bln,Bln,Bln>) tcln(CtlSumXbYbFeVb,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Bln,Bln,Int>) tcln(CtlSumXbYbFeVi,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Bln,Int,Bln>) tcln(CtlSumXbYiFeVb,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Bln,Int,Int>) tcln(CtlSumXbYiFeVi,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Bln,Flt,Flt>) tcln(CtlSumXbYfFeVf,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Int,Bln,Bln>) tcln(CtlSumXiYbFeVb,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Int,Bln,Int>) tcln(CtlSumXiYbFeVi,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Int,Int,Bln>) tcln(CtlSumXiYiFeVb,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Int,Int,Int>) tcln(CtlSumXiYiFeVi,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Int,Flt,Flt>) tcln(CtlSumXiYfFeVf,AutoClsMuxFeV);

rti(CtlSumXYFeVt<Bln,Bln,Flt>) tcln(CtlSumXbYbFeVf,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Bln,Int,Flt>) tcln(CtlSumXbYiFeVf,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Bln,Flt,Bln>) tcln(CtlSumXbYfFeVb,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Bln,Flt,Int>) tcln(CtlSumXbYfFeVi,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Int,Bln,Flt>) tcln(CtlSumXiYbFeVf,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Int,Int,Flt>) tcln(CtlSumXiYiFeVf,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Int,Flt,Bln>) tcln(CtlSumXiYfFeVb,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Int,Flt,Int>) tcln(CtlSumXiYfFeVi,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Flt,Bln,Bln>) tcln(CtlSumXfYbFeVb,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Flt,Bln,Int>) tcln(CtlSumXfYbFeVi,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Flt,Bln,Flt>) tcln(CtlSumXfYbFeVf,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Flt,Int,Bln>) tcln(CtlSumXfYiFeVb,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Flt,Int,Int>) tcln(CtlSumXfYiFeVi,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Flt,Int,Flt>) tcln(CtlSumXfYiFeVf,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Flt,Flt,Bln>) tcln(CtlSumXfYfFeVb,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Flt,Flt,Int>) tcln(CtlSumXfYfFeVi,AutoClsMuxFeV);
rti(CtlSumXYFeVt<Flt,Flt,Flt>) tcln(CtlSumXfYfFeVf,AutoClsMuxFeV);
closeKangarooSpace


#endif // MuxFeVsRegHhIncluded
