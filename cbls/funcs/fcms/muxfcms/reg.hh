/*!
	@file muxfcms/reg.hh
	@brief The register header file for muxfcms.
	@details This is the register header file for muxfcms.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef MuxFcMsRegHhIncluded
#define MuxFcMsRegHhIncluded

#include "cbls/funcs/opfns/idx.hh"

openKangarooSpace
#define AutoClsMuxFcM (TermStub<FcM>::TermCat * 20000 + (thisLine - AutoClsBaseMuxFcM))
enum { AutoClsBaseMuxFcM = thisLine};
closeKangarooSpace


#include "cbls/funcs/fcms/muxfcms/lstidxxyfcmt.tcc"
openKangarooSpace
rti(LstIdxXYFcMt<Int,Bln,Bln>) tcln(LstIdxXiYbFcMb,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Int,Bln,Int>) tcln(LstIdxXiYbFcMi,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Int,Int,Bln>) tcln(LstIdxXiYiFcMb,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Int,Int,Int>) tcln(LstIdxXiYiFcMi,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Int,Flt,Flt>) tcln(LstIdxXiYfFcMf,AutoClsMuxFcM);

rti(LstIdxXYFcMt<Bln,Bln,Bln>) tcln(LstIdxXbYbFcMb,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Bln,Bln,Int>) tcln(LstIdxXbYbFcMi,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Bln,Bln,Flt>) tcln(LstIdxXbYbFcMf,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Bln,Int,Bln>) tcln(LstIdxXbYiFcMb,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Bln,Int,Int>) tcln(LstIdxXbYiFcMi,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Bln,Int,Flt>) tcln(LstIdxXbYiFcMf,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Bln,Flt,Bln>) tcln(LstIdxXbYfFcMb,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Bln,Flt,Int>) tcln(LstIdxXbYfFcMi,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Bln,Flt,Flt>) tcln(LstIdxXbYfFcMf,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Int,Bln,Flt>) tcln(LstIdxXiYbFcMf,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Int,Int,Flt>) tcln(LstIdxXiYiFcMf,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Int,Flt,Bln>) tcln(LstIdxXiYfFcMb,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Int,Flt,Int>) tcln(LstIdxXiYfFcMi,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Flt,Bln,Bln>) tcln(LstIdxXfYbFcMb,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Flt,Bln,Int>) tcln(LstIdxXfYbFcMi,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Flt,Bln,Flt>) tcln(LstIdxXfYbFcMf,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Flt,Int,Bln>) tcln(LstIdxXfYiFcMb,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Flt,Int,Int>) tcln(LstIdxXfYiFcMi,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Flt,Int,Flt>) tcln(LstIdxXfYiFcMf,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Flt,Flt,Bln>) tcln(LstIdxXfYfFcMb,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Flt,Flt,Int>) tcln(LstIdxXfYfFcMi,AutoClsMuxFcM);
rti(LstIdxXYFcMt<Flt,Flt,Flt>) tcln(LstIdxXfYfFcMf,AutoClsMuxFcM);
closeKangarooSpace


#include "cbls/funcs/fcms/muxfcms/iftexyfcmt.tcc"
openKangarooSpace
rti(IfteXYFcMt<Bln,Bln,Bln>) tcln(IfteXbYbFcMb,AutoClsMuxFcM);
rti(IfteXYFcMt<Bln,Bln,Int>) tcln(IfteXbYbFcMi,AutoClsMuxFcM);
rti(IfteXYFcMt<Bln,Int,Bln>) tcln(IfteXbYiFcMb,AutoClsMuxFcM);
rti(IfteXYFcMt<Bln,Int,Int>) tcln(IfteXbYiFcMi,AutoClsMuxFcM);
rti(IfteXYFcMt<Bln,Flt,Flt>) tcln(IfteXbYfFcMf,AutoClsMuxFcM);
rti(IfteXYFcMt<Int,Bln,Bln>) tcln(IfteXiYbFcMb,AutoClsMuxFcM);
rti(IfteXYFcMt<Int,Bln,Int>) tcln(IfteXiYbFcMi,AutoClsMuxFcM);
rti(IfteXYFcMt<Int,Int,Bln>) tcln(IfteXiYiFcMb,AutoClsMuxFcM);
rti(IfteXYFcMt<Int,Int,Int>) tcln(IfteXiYiFcMi,AutoClsMuxFcM);
rti(IfteXYFcMt<Int,Flt,Flt>) tcln(IfteXiYfFcMf,AutoClsMuxFcM);

rti(IfteXYFcMt<Bln,Bln,Flt>) tcln(IfteXbYbFcMf,AutoClsMuxFcM);
rti(IfteXYFcMt<Bln,Int,Flt>) tcln(IfteXbYiFcMf,AutoClsMuxFcM);
rti(IfteXYFcMt<Bln,Flt,Bln>) tcln(IfteXbYfFcMb,AutoClsMuxFcM);
rti(IfteXYFcMt<Bln,Flt,Int>) tcln(IfteXbYfFcMi,AutoClsMuxFcM);
rti(IfteXYFcMt<Int,Bln,Flt>) tcln(IfteXiYbFcMf,AutoClsMuxFcM);
rti(IfteXYFcMt<Int,Int,Flt>) tcln(IfteXiYiFcMf,AutoClsMuxFcM);
rti(IfteXYFcMt<Int,Flt,Bln>) tcln(IfteXiYfFcMb,AutoClsMuxFcM);
rti(IfteXYFcMt<Int,Flt,Int>) tcln(IfteXiYfFcMi,AutoClsMuxFcM);
rti(IfteXYFcMt<Flt,Bln,Bln>) tcln(IfteXfYbFcMb,AutoClsMuxFcM);
rti(IfteXYFcMt<Flt,Bln,Int>) tcln(IfteXfYbFcMi,AutoClsMuxFcM);
rti(IfteXYFcMt<Flt,Bln,Flt>) tcln(IfteXfYbFcMf,AutoClsMuxFcM);
rti(IfteXYFcMt<Flt,Int,Bln>) tcln(IfteXfYiFcMb,AutoClsMuxFcM);
rti(IfteXYFcMt<Flt,Int,Int>) tcln(IfteXfYiFcMi,AutoClsMuxFcM);
rti(IfteXYFcMt<Flt,Int,Flt>) tcln(IfteXfYiFcMf,AutoClsMuxFcM);
rti(IfteXYFcMt<Flt,Flt,Bln>) tcln(IfteXfYfFcMb,AutoClsMuxFcM);
rti(IfteXYFcMt<Flt,Flt,Int>) tcln(IfteXfYfFcMi,AutoClsMuxFcM);
rti(IfteXYFcMt<Flt,Flt,Flt>) tcln(IfteXfYfFcMf,AutoClsMuxFcM);
closeKangarooSpace


#include "cbls/funcs/fcms/muxfcms/iftxyfcmt.tcc"
openKangarooSpace
rti(IftXYFcMt<Bln,Bln,Bln>) tcln(IftXbYbFcMb,AutoClsMuxFcM);
rti(IftXYFcMt<Bln,Bln,Int>) tcln(IftXbYbFcMi,AutoClsMuxFcM);
rti(IftXYFcMt<Bln,Int,Bln>) tcln(IftXbYiFcMb,AutoClsMuxFcM);
rti(IftXYFcMt<Bln,Int,Int>) tcln(IftXbYiFcMi,AutoClsMuxFcM);
rti(IftXYFcMt<Bln,Flt,Flt>) tcln(IftXbYfFcMf,AutoClsMuxFcM);
rti(IftXYFcMt<Int,Bln,Bln>) tcln(IftXiYbFcMb,AutoClsMuxFcM);
rti(IftXYFcMt<Int,Bln,Int>) tcln(IftXiYbFcMi,AutoClsMuxFcM);
rti(IftXYFcMt<Int,Int,Bln>) tcln(IftXiYiFcMb,AutoClsMuxFcM);
rti(IftXYFcMt<Int,Int,Int>) tcln(IftXiYiFcMi,AutoClsMuxFcM);
rti(IftXYFcMt<Int,Flt,Flt>) tcln(IftXiYfFcMf,AutoClsMuxFcM);

rti(IftXYFcMt<Bln,Bln,Flt>) tcln(IftXbYbFcMf,AutoClsMuxFcM);
rti(IftXYFcMt<Bln,Int,Flt>) tcln(IftXbYiFcMf,AutoClsMuxFcM);
rti(IftXYFcMt<Bln,Flt,Bln>) tcln(IftXbYfFcMb,AutoClsMuxFcM);
rti(IftXYFcMt<Bln,Flt,Int>) tcln(IftXbYfFcMi,AutoClsMuxFcM);
rti(IftXYFcMt<Int,Bln,Flt>) tcln(IftXiYbFcMf,AutoClsMuxFcM);
rti(IftXYFcMt<Int,Int,Flt>) tcln(IftXiYiFcMf,AutoClsMuxFcM);
rti(IftXYFcMt<Int,Flt,Bln>) tcln(IftXiYfFcMb,AutoClsMuxFcM);
rti(IftXYFcMt<Int,Flt,Int>) tcln(IftXiYfFcMi,AutoClsMuxFcM);
rti(IftXYFcMt<Flt,Bln,Bln>) tcln(IftXfYbFcMb,AutoClsMuxFcM);
rti(IftXYFcMt<Flt,Bln,Int>) tcln(IftXfYbFcMi,AutoClsMuxFcM);
rti(IftXYFcMt<Flt,Bln,Flt>) tcln(IftXfYbFcMf,AutoClsMuxFcM);
rti(IftXYFcMt<Flt,Int,Bln>) tcln(IftXfYiFcMb,AutoClsMuxFcM);
rti(IftXYFcMt<Flt,Int,Int>) tcln(IftXfYiFcMi,AutoClsMuxFcM);
rti(IftXYFcMt<Flt,Int,Flt>) tcln(IftXfYiFcMf,AutoClsMuxFcM);
rti(IftXYFcMt<Flt,Flt,Bln>) tcln(IftXfYfFcMb,AutoClsMuxFcM);
rti(IftXYFcMt<Flt,Flt,Int>) tcln(IftXfYfFcMi,AutoClsMuxFcM);
rti(IftXYFcMt<Flt,Flt,Flt>) tcln(IftXfYfFcMf,AutoClsMuxFcM);
closeKangarooSpace

#include "cbls/funcs/fcms/muxfcms/niftxyfcmt.tcc"
openKangarooSpace
rti(NiftXYFcMt<Bln,Bln,Bln>) tcln(NiftXbYbFcMb,AutoClsMuxFcM);
rti(NiftXYFcMt<Bln,Bln,Int>) tcln(NiftXbYbFcMi,AutoClsMuxFcM);
rti(NiftXYFcMt<Bln,Int,Bln>) tcln(NiftXbYiFcMb,AutoClsMuxFcM);
rti(NiftXYFcMt<Bln,Int,Int>) tcln(NiftXbYiFcMi,AutoClsMuxFcM);
rti(NiftXYFcMt<Bln,Flt,Flt>) tcln(NiftXbYfFcMf,AutoClsMuxFcM);
rti(NiftXYFcMt<Int,Bln,Bln>) tcln(NiftXiYbFcMb,AutoClsMuxFcM);
rti(NiftXYFcMt<Int,Bln,Int>) tcln(NiftXiYbFcMi,AutoClsMuxFcM);
rti(NiftXYFcMt<Int,Int,Bln>) tcln(NiftXiYiFcMb,AutoClsMuxFcM);
rti(NiftXYFcMt<Int,Int,Int>) tcln(NiftXiYiFcMi,AutoClsMuxFcM);
rti(NiftXYFcMt<Int,Flt,Flt>) tcln(NiftXiYfFcMf,AutoClsMuxFcM);

rti(NiftXYFcMt<Bln,Bln,Flt>) tcln(NiftXbYbFcMf,AutoClsMuxFcM);
rti(NiftXYFcMt<Bln,Int,Flt>) tcln(NiftXbYiFcMf,AutoClsMuxFcM);
rti(NiftXYFcMt<Bln,Flt,Bln>) tcln(NiftXbYfFcMb,AutoClsMuxFcM);
rti(NiftXYFcMt<Bln,Flt,Int>) tcln(NiftXbYfFcMi,AutoClsMuxFcM);
rti(NiftXYFcMt<Int,Bln,Flt>) tcln(NiftXiYbFcMf,AutoClsMuxFcM);
rti(NiftXYFcMt<Int,Int,Flt>) tcln(NiftXiYiFcMf,AutoClsMuxFcM);
rti(NiftXYFcMt<Int,Flt,Bln>) tcln(NiftXiYfFcMb,AutoClsMuxFcM);
rti(NiftXYFcMt<Int,Flt,Int>) tcln(NiftXiYfFcMi,AutoClsMuxFcM);
rti(NiftXYFcMt<Flt,Bln,Bln>) tcln(NiftXfYbFcMb,AutoClsMuxFcM);
rti(NiftXYFcMt<Flt,Bln,Int>) tcln(NiftXfYbFcMi,AutoClsMuxFcM);
rti(NiftXYFcMt<Flt,Bln,Flt>) tcln(NiftXfYbFcMf,AutoClsMuxFcM);
rti(NiftXYFcMt<Flt,Int,Bln>) tcln(NiftXfYiFcMb,AutoClsMuxFcM);
rti(NiftXYFcMt<Flt,Int,Int>) tcln(NiftXfYiFcMi,AutoClsMuxFcM);
rti(NiftXYFcMt<Flt,Int,Flt>) tcln(NiftXfYiFcMf,AutoClsMuxFcM);
rti(NiftXYFcMt<Flt,Flt,Bln>) tcln(NiftXfYfFcMb,AutoClsMuxFcM);
rti(NiftXYFcMt<Flt,Flt,Int>) tcln(NiftXfYfFcMi,AutoClsMuxFcM);
rti(NiftXYFcMt<Flt,Flt,Flt>) tcln(NiftXfYfFcMf,AutoClsMuxFcM);
closeKangarooSpace


#endif // MuxFcMsRegHhIncluded
