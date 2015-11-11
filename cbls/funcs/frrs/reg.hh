/*!
	@file frrs/reg.hh
	@brief The register prototype file for frrs.
	@details This is the register prototype file for frrs.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef FrRsRegHhIncluded
#define FrRsRegHhIncluded


#include "cbls/frames/idx.hh"


#include "cbls/funcs/frrs/frrt.tcc"
openKangarooSpace
#define AutoTypFrR (TermStub<FrR>::TermCat * 10 + (thisLine - AutoTypBaseFrR))
enum { AutoTypBaseFrR = thisLine};
rti(FrRt<Bln>) ttpn(FrRb,AutoTypFrR);
rti(FrRt<Int>) ttpn(FrRi,AutoTypFrR);
rti(FrRt<Flt>) ttpn(FrRf,AutoTypFrR);
closeKangarooSpace

openKangarooSpace
#define AutoClsFrR (TermStub<FrR>::TermCat * 10000 + (thisLine - AutoClsBaseFrR))
enum { AutoClsBaseFrR = thisLine};
closeKangarooSpace

#include "cbls/funcs/frrs/prmheapxfrrt.tcc"

openKangarooSpace
rti(PrmHeapXFrRt<Bln,Bln,Dsc >) tcln(PrmMaxHeapXbFrRb, AutoClsFrR);
rti(PrmHeapXFrRt<Bln,Bln,Asc >) tcln(PrmMinHeapXbFrRb, AutoClsFrR);

rti(PrmHeapXFrRt<Int,Bln,Dsc >) tcln(PrmMaxHeapXiFrRb, AutoClsFrR);
rti(PrmHeapXFrRt<Int,Bln,Asc >) tcln(PrmMinHeapXiFrRb, AutoClsFrR);

rti(PrmHeapXFrRt<Int,Int,Dsc >) tcln(PrmMaxHeapXiFrRi, AutoClsFrR);
rti(PrmHeapXFrRt<Int,Int,Asc >) tcln(PrmMinHeapXiFrRi, AutoClsFrR);

rti(PrmHeapXFrRt<Flt,Bln,Dsc >) tcln(PrmMaxHeapXfFrRb, AutoClsFrR);
rti(PrmHeapXFrRt<Flt,Bln,Asc >) tcln(PrmMinHeapXfFrRb, AutoClsFrR);

rti(PrmHeapXFrRt<Flt,Flt,Dsc >) tcln(PrmMaxHeapXfFrRf, AutoClsFrR);
rti(PrmHeapXFrRt<Flt,Flt,Asc >) tcln(PrmMinHeapXfFrRf, AutoClsFrR);
closeKangarooSpace


#include "cbls/funcs/frrs/varprmheapxfrrt.tcc"

openKangarooSpace
rti(VarPrmHeapXFrRt<Bln,Bln,Dsc >) tcln(VarPrmMaxHeapXbFrRb, AutoClsFrR);
rti(VarPrmHeapXFrRt<Bln,Bln,Asc >) tcln(VarPrmMinHeapXbFrRb, AutoClsFrR);

rti(VarPrmHeapXFrRt<Int,Bln,Dsc >) tcln(VarPrmMaxHeapXiFrRb, AutoClsFrR);
rti(VarPrmHeapXFrRt<Int,Bln,Asc >) tcln(VarPrmMinHeapXiFrRb, AutoClsFrR);

rti(VarPrmHeapXFrRt<Int,Int,Dsc >) tcln(VarPrmMaxHeapXiFrRi, AutoClsFrR);
rti(VarPrmHeapXFrRt<Int,Int,Asc >) tcln(VarPrmMinHeapXiFrRi, AutoClsFrR);

rti(VarPrmHeapXFrRt<Flt,Bln,Dsc >) tcln(VarPrmMaxHeapXfFrRb, AutoClsFrR);
rti(VarPrmHeapXFrRt<Flt,Bln,Asc >) tcln(VarPrmMinHeapXfFrRb, AutoClsFrR);

rti(VarPrmHeapXFrRt<Flt,Flt,Dsc >) tcln(VarPrmMaxHeapXfFrRf, AutoClsFrR);
rti(VarPrmHeapXFrRt<Flt,Flt,Asc >) tcln(VarPrmMinHeapXfFrRf, AutoClsFrR);
closeKangarooSpace


#include "cbls/funcs/frrs/lockvarprmheapxfrrt.tcc"
openKangarooSpace
rti(LockVarPrmHeapXFrRt<Bln,Bln,Dsc >) tcln(LockVarPrmMaxHeapXbFrRb, AutoClsFrR);
rti(LockVarPrmHeapXFrRt<Bln,Bln,Asc >) tcln(LockVarPrmMinHeapXbFrRb, AutoClsFrR);

rti(LockVarPrmHeapXFrRt<Int,Bln,Dsc >) tcln(LockVarPrmMaxHeapXiFrRb, AutoClsFrR);
rti(LockVarPrmHeapXFrRt<Int,Bln,Asc >) tcln(LockVarPrmMinHeapXiFrRb, AutoClsFrR);

rti(LockVarPrmHeapXFrRt<Int,Int,Dsc >) tcln(LockVarPrmMaxHeapXiFrRi, AutoClsFrR);
rti(LockVarPrmHeapXFrRt<Int,Int,Asc >) tcln(LockVarPrmMinHeapXiFrRi, AutoClsFrR);

rti(LockVarPrmHeapXFrRt<Flt,Bln,Dsc >) tcln(LockVarPrmMaxHeapXfFrRb, AutoClsFrR);
rti(LockVarPrmHeapXFrRt<Flt,Bln,Asc >) tcln(LockVarPrmMinHeapXfFrRb, AutoClsFrR);

rti(LockVarPrmHeapXFrRt<Flt,Flt,Dsc >) tcln(LockVarPrmMaxHeapXfFrRf, AutoClsFrR);
rti(LockVarPrmHeapXFrRt<Flt,Flt,Asc >) tcln(LockVarPrmMinHeapXfFrRf, AutoClsFrR);
closeKangarooSpace


#include "cbls/funcs/frrs/sv2tabuvarprmheapxfrrt.tcc"

openKangarooSpace
rti(Sv2TabuVarPrmHeapXFrRt<Bln,Bln,Dsc >) tcln(Sv2TabuVarPrmMaxHeapXbFrRb, AutoClsFrR);
rti(Sv2TabuVarPrmHeapXFrRt<Bln,Bln,Asc >) tcln(Sv2TabuVarPrmMinHeapXbFrRb, AutoClsFrR);

rti(Sv2TabuVarPrmHeapXFrRt<Int,Bln,Dsc >) tcln(Sv2TabuVarPrmMaxHeapXiFrRb, AutoClsFrR);
rti(Sv2TabuVarPrmHeapXFrRt<Int,Bln,Asc >) tcln(Sv2TabuVarPrmMinHeapXiFrRb, AutoClsFrR);

rti(Sv2TabuVarPrmHeapXFrRt<Int,Int,Dsc >) tcln(Sv2TabuVarPrmMaxHeapXiFrRi, AutoClsFrR);
rti(Sv2TabuVarPrmHeapXFrRt<Int,Int,Asc >) tcln(Sv2TabuVarPrmMinHeapXiFrRi, AutoClsFrR);

rti(Sv2TabuVarPrmHeapXFrRt<Flt,Bln,Dsc >) tcln(Sv2TabuVarPrmMaxHeapXfFrRb, AutoClsFrR);
rti(Sv2TabuVarPrmHeapXFrRt<Flt,Bln,Asc >) tcln(Sv2TabuVarPrmMinHeapXfFrRb, AutoClsFrR);

rti(Sv2TabuVarPrmHeapXFrRt<Flt,Flt,Dsc >) tcln(Sv2TabuVarPrmMaxHeapXfFrRf, AutoClsFrR);
rti(Sv2TabuVarPrmHeapXFrRt<Flt,Flt,Asc >) tcln(Sv2TabuVarPrmMinHeapXfFrRf, AutoClsFrR);
closeKangarooSpace


#include "cbls/funcs/frrs/sv2tabulockvarprmheapxfrrt.tcc"
openKangarooSpace
rti(Sv2TabuLockVarPrmHeapXFrRt<Bln,Bln,Dsc >) tcln(Sv2TabuLockVarPrmMaxHeapXbFrRb, AutoClsFrR);
rti(Sv2TabuLockVarPrmHeapXFrRt<Bln,Bln,Asc >) tcln(Sv2TabuLockVarPrmMinHeapXbFrRb, AutoClsFrR);

rti(Sv2TabuLockVarPrmHeapXFrRt<Int,Bln,Dsc >) tcln(Sv2TabuLockVarPrmMaxHeapXiFrRb, AutoClsFrR);
rti(Sv2TabuLockVarPrmHeapXFrRt<Int,Bln,Asc >) tcln(Sv2TabuLockVarPrmMinHeapXiFrRb, AutoClsFrR);

rti(Sv2TabuLockVarPrmHeapXFrRt<Int,Int,Dsc >) tcln(Sv2TabuLockVarPrmMaxHeapXiFrRi, AutoClsFrR);
rti(Sv2TabuLockVarPrmHeapXFrRt<Int,Int,Asc >) tcln(Sv2TabuLockVarPrmMinHeapXiFrRi, AutoClsFrR);

rti(Sv2TabuLockVarPrmHeapXFrRt<Flt,Bln,Dsc >) tcln(Sv2TabuLockVarPrmMaxHeapXfFrRb, AutoClsFrR);
rti(Sv2TabuLockVarPrmHeapXFrRt<Flt,Bln,Asc >) tcln(Sv2TabuLockVarPrmMinHeapXfFrRb, AutoClsFrR);

rti(Sv2TabuLockVarPrmHeapXFrRt<Flt,Flt,Dsc >) tcln(Sv2TabuLockVarPrmMaxHeapXfFrRf, AutoClsFrR);
rti(Sv2TabuLockVarPrmHeapXFrRt<Flt,Flt,Asc >) tcln(Sv2TabuLockVarPrmMinHeapXfFrRf, AutoClsFrR);
closeKangarooSpace



#endif	//	FrRsRegHhIncluded
