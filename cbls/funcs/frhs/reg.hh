/*!
	@file frhs/reg.hh
	@brief The register prototype file for frhs.
	@details This is the register prototype file for frhs.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef FrHsRegHhIncluded
#define FrHsRegHhIncluded


#include "cbls/frames/idx.hh"


#include "cbls/funcs/frhs/frht.tcc"
openKangarooSpace
#define AutoTypFrH (TermStub<FrH>::TermCat * 10 + (thisLine - AutoTypBaseFrH))
enum { AutoTypBaseFrH = thisLine};
rti(FrHt<Bln>) ttpn(FrHb,AutoTypFrH);
rti(FrHt<Int>) ttpn(FrHi,AutoTypFrH);
rti(FrHt<Flt>) ttpn(FrHf,AutoTypFrH);
closeKangarooSpace

openKangarooSpace
#define AutoClsFrH (TermStub<FrH>::TermCat * 10000 + (thisLine - AutoClsBaseFrH))
enum { AutoClsBaseFrH = thisLine};
closeKangarooSpace

#include "cbls/funcs/frhs/heaphfrh.tcc"

openKangarooSpace
rti(HeapHFrH<Bln,Bln,Dsc >) tcln(MaxHeapHbFrHb, AutoClsFrH);
rti(HeapHFrH<Bln,Bln,Asc >) tcln(MinHeapHbFrHb, AutoClsFrH);

rti(HeapHFrH<Int,Bln,Dsc >) tcln(MaxHeapHiFrHb, AutoClsFrH);
rti(HeapHFrH<Int,Bln,Asc >) tcln(MinHeapHiFrHb, AutoClsFrH);

rti(HeapHFrH<Int,Int,Dsc >) tcln(MaxHeapHiFrHi, AutoClsFrH);
rti(HeapHFrH<Int,Int,Asc >) tcln(MinHeapHiFrHi, AutoClsFrH);

rti(HeapHFrH<Flt,Bln,Dsc >) tcln(MaxHeapHfFrHb, AutoClsFrH);
rti(HeapHFrH<Flt,Bln,Asc >) tcln(MinHeapHfFrHb, AutoClsFrH);

rti(HeapHFrH<Flt,Flt,Dsc >) tcln(MaxHeapHfFrHf, AutoClsFrH);
rti(HeapHFrH<Flt,Flt,Asc >) tcln(MinHeapHfFrHf, AutoClsFrH);
closeKangarooSpace


#include "cbls/funcs/frhs/lockheaphfrh.tcc"

openKangarooSpace
rti(LockHeapHFrH<Bln,Bln,Dsc >) tcln(LockMaxHeapHbFrHb, AutoClsFrH);
rti(LockHeapHFrH<Bln,Bln,Asc >) tcln(LockMinHeapHbFrHb, AutoClsFrH);

rti(LockHeapHFrH<Int,Bln,Dsc >) tcln(LockMaxHeapHiFrHb, AutoClsFrH);
rti(LockHeapHFrH<Int,Bln,Asc >) tcln(LockMinHeapHiFrHb, AutoClsFrH);

rti(LockHeapHFrH<Int,Int,Dsc >) tcln(LockMaxHeapHiFrHi, AutoClsFrH);
rti(LockHeapHFrH<Int,Int,Asc >) tcln(LockMinHeapHiFrHi, AutoClsFrH);

rti(LockHeapHFrH<Flt,Bln,Dsc >) tcln(LockMaxHeapHfFrHb, AutoClsFrH);
rti(LockHeapHFrH<Flt,Bln,Asc >) tcln(LockMinHeapHfFrHb, AutoClsFrH);

rti(LockHeapHFrH<Flt,Flt,Dsc >) tcln(LockMaxHeapHfFrHf, AutoClsFrH);
rti(LockHeapHFrH<Flt,Flt,Asc >) tcln(LockMinHeapHfFrHf, AutoClsFrH);
closeKangarooSpace


#include "cbls/funcs/frhs/sv2tabuheaphfrh.tcc"

openKangarooSpace
rti(Sv2TabuHeapHFrH<Bln,Bln,Dsc >) tcln(Sv2TabuMaxHeapHbFrHb, AutoClsFrH);
rti(Sv2TabuHeapHFrH<Bln,Bln,Asc >) tcln(Sv2TabuMinHeapHbFrHb, AutoClsFrH);

rti(Sv2TabuHeapHFrH<Int,Bln,Dsc >) tcln(Sv2TabuMaxHeapHiFrHb, AutoClsFrH);
rti(Sv2TabuHeapHFrH<Int,Bln,Asc >) tcln(Sv2TabuMinHeapHiFrHb, AutoClsFrH);

rti(Sv2TabuHeapHFrH<Int,Int,Dsc >) tcln(Sv2TabuMaxHeapHiFrHi, AutoClsFrH);
rti(Sv2TabuHeapHFrH<Int,Int,Asc >) tcln(Sv2TabuMinHeapHiFrHi, AutoClsFrH);

rti(Sv2TabuHeapHFrH<Flt,Bln,Dsc >) tcln(Sv2TabuMaxHeapHfFrHb, AutoClsFrH);
rti(Sv2TabuHeapHFrH<Flt,Bln,Asc >) tcln(Sv2TabuMinHeapHfFrHb, AutoClsFrH);

rti(Sv2TabuHeapHFrH<Flt,Flt,Dsc >) tcln(Sv2TabuMaxHeapHfFrHf, AutoClsFrH);
rti(Sv2TabuHeapHFrH<Flt,Flt,Asc >) tcln(Sv2TabuMinHeapHfFrHf, AutoClsFrH);
closeKangarooSpace



#include "cbls/funcs/frhs/sv2tabulockheaphfrh.tcc"

openKangarooSpace
rti(Sv2TabuLockHeapHFrH<Bln,Bln,Dsc >) tcln(Sv2TabuLockMaxHeapHbFrHb, AutoClsFrH);
rti(Sv2TabuLockHeapHFrH<Bln,Bln,Asc >) tcln(Sv2TabuLockMinHeapHbFrHb, AutoClsFrH);

rti(Sv2TabuLockHeapHFrH<Int,Bln,Dsc >) tcln(Sv2TabuLockMaxHeapHiFrHb, AutoClsFrH);
rti(Sv2TabuLockHeapHFrH<Int,Bln,Asc >) tcln(Sv2TabuLockMinHeapHiFrHb, AutoClsFrH);

rti(Sv2TabuLockHeapHFrH<Int,Int,Dsc >) tcln(Sv2TabuLockMaxHeapHiFrHi, AutoClsFrH);
rti(Sv2TabuLockHeapHFrH<Int,Int,Asc >) tcln(Sv2TabuLockMinHeapHiFrHi, AutoClsFrH);

rti(Sv2TabuLockHeapHFrH<Flt,Bln,Dsc >) tcln(Sv2TabuLockMaxHeapHfFrHb, AutoClsFrH);
rti(Sv2TabuLockHeapHFrH<Flt,Bln,Asc >) tcln(Sv2TabuLockMinHeapHfFrHb, AutoClsFrH);

rti(Sv2TabuLockHeapHFrH<Flt,Flt,Dsc >) tcln(Sv2TabuLockMaxHeapHfFrHf, AutoClsFrH);
rti(Sv2TabuLockHeapHFrH<Flt,Flt,Asc >) tcln(Sv2TabuLockMinHeapHfFrHf, AutoClsFrH);
closeKangarooSpace


#endif	//	FrHsRegHhIncluded
