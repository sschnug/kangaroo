/*!
	@file segfcms/reg.hh
	@brief The register header file for segfcms.
	@details This is the register header file for segfcms.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef SegFcMsRegHhIncluded
#define SegFcMsRegHhIncluded

#include "cbls/funcs/opfns/idx.hh"

openKangarooSpace
#define AutoClsSegFcM (TermStub<FcM>::TermCat * 10000 + (thisLine - AutoClsBaseSegFcM))
enum { AutoClsBaseSegFcM = thisLine};
closeKangarooSpace

#include "cbls/funcs/fcms/segfcms/uaryxfcmt.tcc"
openKangarooSpace
rti(UaryXFcMt< ucast<Bln,Int> >) tcln(UcastXbFcMi,AutoClsSegFcM);
rti(UaryXFcMt< ucast<Int,Bln> >) tcln(UcastXiFcMb,AutoClsSegFcM);
rti(UaryXFcMt< ucast<Bln,Flt> >) tcln(UcastXbFcMf,AutoClsSegFcM);
rti(UaryXFcMt< ucast<Flt,Bln> >) tcln(UcastXfFcMb,AutoClsSegFcM);
rti(UaryXFcMt< ucast<Int,Flt> >) tcln(UcastXiFcMf,AutoClsSegFcM);
rti(UaryXFcMt< ucast<Flt,Int> >) tcln(UcastXfFcMi,AutoClsSegFcM);

rti(UaryXFcMt< unots<Bln,Bln> >) tcln(UnotsXbFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unots<Bln,Int> >) tcln(UnotsXbFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unots<Bln,Flt> >) tcln(UnotsXbFcMf,AutoClsSegFcM);
rti(UaryXFcMt< unots<Int,Bln> >) tcln(UnotsXiFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unots<Int,Int> >) tcln(UnotsXiFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unots<Int,Flt> >) tcln(UnotsXiFcMf,AutoClsSegFcM);
rti(UaryXFcMt< unots<Flt,Bln> >) tcln(UnotsXfFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unots<Flt,Int> >) tcln(UnotsXfFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unots<Flt,Flt> >) tcln(UnotsXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< unnots<Bln,Bln> >) tcln(UnnotsXbFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unnots<Bln,Int> >) tcln(UnnotsXbFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unnots<Bln,Flt> >) tcln(UnnotsXbFcMf,AutoClsSegFcM);
rti(UaryXFcMt< unnots<Int,Bln> >) tcln(UnnotsXiFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unnots<Int,Int> >) tcln(UnnotsXiFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unnots<Int,Flt> >) tcln(UnnotsXiFcMf,AutoClsSegFcM);
rti(UaryXFcMt< unnots<Flt,Bln> >) tcln(UnnotsXfFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unnots<Flt,Int> >) tcln(UnnotsXfFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unnots<Flt,Flt> >) tcln(UnnotsXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< unotu<Bln,Bln> >) tcln(UnotuXbFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unotu<Bln,Int> >) tcln(UnotuXbFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unotu<Bln,Flt> >) tcln(UnotuXbFcMf,AutoClsSegFcM);
rti(UaryXFcMt< unotu<Int,Bln> >) tcln(UnotuXiFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unotu<Int,Int> >) tcln(UnotuXiFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unotu<Int,Flt> >) tcln(UnotuXiFcMf,AutoClsSegFcM);
rti(UaryXFcMt< unotu<Flt,Bln> >) tcln(UnotuXfFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unotu<Flt,Int> >) tcln(UnotuXfFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unotu<Flt,Flt> >) tcln(UnotuXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< unnotu<Bln,Bln> >) tcln(UnnotuXbFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unnotu<Bln,Int> >) tcln(UnnotuXbFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unnotu<Bln,Flt> >) tcln(UnnotuXbFcMf,AutoClsSegFcM);
rti(UaryXFcMt< unnotu<Int,Bln> >) tcln(UnnotuXiFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unnotu<Int,Int> >) tcln(UnnotuXiFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unnotu<Int,Flt> >) tcln(UnnotuXiFcMf,AutoClsSegFcM);
rti(UaryXFcMt< unnotu<Flt,Bln> >) tcln(UnnotuXfFcMb,AutoClsSegFcM);
rti(UaryXFcMt< unnotu<Flt,Int> >) tcln(UnnotuXfFcMi,AutoClsSegFcM);
rti(UaryXFcMt< unnotu<Flt,Flt> >) tcln(UnnotuXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< uneg<Int,Int> >) tcln(UnegXiFcMi,AutoClsSegFcM);
rti(UaryXFcMt< uneg<Flt,Flt> >) tcln(UnegXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< uabs<Int,Int> >) tcln(UabsXiFcMi,AutoClsSegFcM);
rti(UaryXFcMt< uabs<Flt,Flt> >) tcln(UabsXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< usin<Flt,Flt> >) tcln(UsinXfFcMf,AutoClsSegFcM);
rti(UaryXFcMt< ucos<Flt,Flt> >) tcln(UcosXfFcMf,AutoClsSegFcM);
rti(UaryXFcMt< utan<Flt,Flt> >) tcln(UtanXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< uasin<Flt,Flt> >) tcln(UasinXfFcMf,AutoClsSegFcM);
rti(UaryXFcMt< uacos<Flt,Flt> >) tcln(UacosXfFcMf,AutoClsSegFcM);
rti(UaryXFcMt< uatan<Flt,Flt> >) tcln(UatanXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< usinh<Flt,Flt> >) tcln(UsinhXfFcMf,AutoClsSegFcM);
rti(UaryXFcMt< ucosh<Flt,Flt> >) tcln(UcoshXfFcMf,AutoClsSegFcM);
rti(UaryXFcMt< utanh<Flt,Flt> >) tcln(UtanhXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< uasinh<Flt,Flt> >) tcln(UasinhXfFcMf,AutoClsSegFcM);
rti(UaryXFcMt< uacosh<Flt,Flt> >) tcln(UacoshXfFcMf,AutoClsSegFcM);
rti(UaryXFcMt< uatanh<Flt,Flt> >) tcln(UatanhXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< uexp<Flt,Flt> >) tcln(UexpXfFcMf,AutoClsSegFcM);
rti(UaryXFcMt< ulog<Flt,Flt> >) tcln(UlogXfFcMf,AutoClsSegFcM);
rti(UaryXFcMt< ulog2<Flt,Flt> >) tcln(Ulog2XfFcMf,AutoClsSegFcM);
rti(UaryXFcMt< ulog10<Flt,Flt> >) tcln(Ulog10XfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< usqr<Int,Int> >) tcln(UsqrXiFcMi,AutoClsSegFcM);
rti(UaryXFcMt< usqr<Int,Flt> >) tcln(UsqrXiFcMf,AutoClsSegFcM);
rti(UaryXFcMt< usqr<Flt,Flt> >) tcln(UsqrXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< usqrt<Flt,Flt> >) tcln(UsqrtXfFcMf,AutoClsSegFcM);

rti(UaryXFcMt< ucube<Int,Int> >) tcln(UcubeXiFcMi,AutoClsSegFcM);
rti(UaryXFcMt< ucube<Int,Flt> >) tcln(UcubeXiFcMf,AutoClsSegFcM);
rti(UaryXFcMt< ucube<Flt,Flt> >) tcln(UcubeXfFcMf,AutoClsSegFcM);

closeKangarooSpace



#include "cbls/funcs/fcms/segfcms/baryxfcmt.tcc"

openKangarooSpace
rti(BaryXFcMt< bands<Bln,Bln> >) 	tcln(BandsXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bands<Bln,Int> >) 	tcln(BandsXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bands<Bln,Flt> >) 	tcln(BandsXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bands<Int,Bln> >) 	tcln(BandsXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bands<Int,Int> >) 	tcln(BandsXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bands<Int,Flt> >) 	tcln(BandsXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bands<Flt,Bln> >) 	tcln(BandsXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bands<Flt,Int> >) 	tcln(BandsXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bands<Flt,Flt> >) 	tcln(BandsXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnands<Bln,Bln> >) 	tcln(BnandsXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnands<Bln,Int> >) 	tcln(BnandsXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnands<Bln,Flt> >) 	tcln(BnandsXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnands<Int,Bln> >) 	tcln(BnandsXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnands<Int,Int> >) 	tcln(BnandsXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnands<Int,Flt> >) 	tcln(BnandsXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnands<Flt,Bln> >) 	tcln(BnandsXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnands<Flt,Int> >) 	tcln(BnandsXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnands<Flt,Flt> >) 	tcln(BnandsXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bors<Bln,Bln> >) 	tcln(BorsXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bors<Bln,Int> >) 	tcln(BorsXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bors<Bln,Flt> >) 	tcln(BorsXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bors<Int,Bln> >) 	tcln(BorsXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bors<Int,Int> >) 	tcln(BorsXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bors<Int,Flt> >) 	tcln(BorsXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bors<Flt,Bln> >) 	tcln(BorsXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bors<Flt,Int> >) 	tcln(BorsXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bors<Flt,Flt> >) 	tcln(BorsXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnors<Bln,Bln> >) 	tcln(BnorsXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnors<Bln,Int> >) 	tcln(BnorsXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnors<Bln,Flt> >) 	tcln(BnorsXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnors<Int,Bln> >) 	tcln(BnorsXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnors<Int,Int> >) 	tcln(BnorsXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnors<Int,Flt> >) 	tcln(BnorsXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnors<Flt,Bln> >) 	tcln(BnorsXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnors<Flt,Int> >) 	tcln(BnorsXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnors<Flt,Flt> >) 	tcln(BnorsXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bxors<Bln,Bln> >) 	tcln(BxorsXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxors<Bln,Int> >) 	tcln(BxorsXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxors<Bln,Flt> >) 	tcln(BxorsXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bxors<Int,Bln> >) 	tcln(BxorsXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxors<Int,Int> >) 	tcln(BxorsXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxors<Int,Flt> >) 	tcln(BxorsXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bxors<Flt,Bln> >) 	tcln(BxorsXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxors<Flt,Int> >) 	tcln(BxorsXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxors<Flt,Flt> >) 	tcln(BxorsXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bxnors<Bln,Bln> >) 	tcln(BxnorsXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxnors<Bln,Int> >) 	tcln(BxnorsXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxnors<Bln,Flt> >) 	tcln(BxnorsXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bxnors<Int,Bln> >) 	tcln(BxnorsXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxnors<Int,Int> >) 	tcln(BxnorsXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxnors<Int,Flt> >) 	tcln(BxnorsXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bxnors<Flt,Bln> >) 	tcln(BxnorsXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxnors<Flt,Int> >) 	tcln(BxnorsXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxnors<Flt,Flt> >) 	tcln(BxnorsXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bimplys<Bln,Bln> >) 	tcln(BimplysXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bimplys<Bln,Int> >) 	tcln(BimplysXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bimplys<Bln,Flt> >) 	tcln(BimplysXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bimplys<Int,Bln> >) 	tcln(BimplysXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bimplys<Int,Int> >) 	tcln(BimplysXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bimplys<Int,Flt> >) 	tcln(BimplysXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bimplys<Flt,Bln> >) 	tcln(BimplysXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bimplys<Flt,Int> >) 	tcln(BimplysXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bimplys<Flt,Flt> >) 	tcln(BimplysXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnimplys<Bln,Bln> >) tcln(BnimplysXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnimplys<Bln,Int> >) tcln(BnimplysXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnimplys<Bln,Flt> >) tcln(BnimplysXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnimplys<Int,Bln> >) tcln(BnimplysXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnimplys<Int,Int> >) tcln(BnimplysXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnimplys<Int,Flt> >) tcln(BnimplysXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnimplys<Flt,Bln> >) tcln(BnimplysXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnimplys<Flt,Int> >) tcln(BnimplysXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnimplys<Flt,Flt> >) tcln(BnimplysXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bandu<Bln,Bln> >) 	tcln(BanduXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bandu<Bln,Int> >) 	tcln(BanduXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bandu<Bln,Flt> >) 	tcln(BanduXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bandu<Int,Bln> >) 	tcln(BanduXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bandu<Int,Int> >) 	tcln(BanduXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bandu<Int,Flt> >) 	tcln(BanduXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bandu<Flt,Bln> >) 	tcln(BanduXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bandu<Flt,Int> >) 	tcln(BanduXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bandu<Flt,Flt> >) 	tcln(BanduXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnandu<Bln,Bln> >) 	tcln(BnanduXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnandu<Bln,Int> >) 	tcln(BnanduXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnandu<Bln,Flt> >) 	tcln(BnanduXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnandu<Int,Bln> >) 	tcln(BnanduXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnandu<Int,Int> >) 	tcln(BnanduXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnandu<Int,Flt> >) 	tcln(BnanduXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnandu<Flt,Bln> >) 	tcln(BnanduXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnandu<Flt,Int> >) 	tcln(BnanduXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnandu<Flt,Flt> >) 	tcln(BnanduXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< boru<Bln,Bln> >) 	tcln(BoruXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< boru<Bln,Int> >) 	tcln(BoruXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< boru<Bln,Flt> >) 	tcln(BoruXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< boru<Int,Bln> >) 	tcln(BoruXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< boru<Int,Int> >) 	tcln(BoruXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< boru<Int,Flt> >) 	tcln(BoruXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< boru<Flt,Bln> >) 	tcln(BoruXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< boru<Flt,Int> >) 	tcln(BoruXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< boru<Flt,Flt> >) 	tcln(BoruXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnoru<Bln,Bln> >) 	tcln(BnoruXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnoru<Bln,Int> >) 	tcln(BnoruXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnoru<Bln,Flt> >) 	tcln(BnoruXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnoru<Int,Bln> >) 	tcln(BnoruXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnoru<Int,Int> >) 	tcln(BnoruXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnoru<Int,Flt> >) 	tcln(BnoruXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnoru<Flt,Bln> >) 	tcln(BnoruXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnoru<Flt,Int> >) 	tcln(BnoruXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnoru<Flt,Flt> >) 	tcln(BnoruXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bxoru<Bln,Bln> >) 	tcln(BxoruXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxoru<Bln,Int> >) 	tcln(BxoruXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxoru<Bln,Flt> >) 	tcln(BxoruXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bxoru<Int,Bln> >) 	tcln(BxoruXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxoru<Int,Int> >) 	tcln(BxoruXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxoru<Int,Flt> >) 	tcln(BxoruXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bxoru<Flt,Bln> >) 	tcln(BxoruXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxoru<Flt,Int> >) 	tcln(BxoruXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxoru<Flt,Flt> >) 	tcln(BxoruXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bxnoru<Bln,Bln> >) 	tcln(BxnoruXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxnoru<Bln,Int> >) 	tcln(BxnoruXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxnoru<Bln,Flt> >) 	tcln(BxnoruXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bxnoru<Int,Bln> >) 	tcln(BxnoruXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxnoru<Int,Int> >) 	tcln(BxnoruXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxnoru<Int,Flt> >) 	tcln(BxnoruXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bxnoru<Flt,Bln> >) 	tcln(BxnoruXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bxnoru<Flt,Int> >) 	tcln(BxnoruXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bxnoru<Flt,Flt> >) 	tcln(BxnoruXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bimplyu<Bln,Bln> >) 	tcln(BimplyuXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bimplyu<Bln,Int> >) 	tcln(BimplyuXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bimplyu<Bln,Flt> >) 	tcln(BimplyuXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bimplyu<Int,Bln> >) 	tcln(BimplyuXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bimplyu<Int,Int> >) 	tcln(BimplyuXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bimplyu<Int,Flt> >) 	tcln(BimplyuXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bimplyu<Flt,Bln> >) 	tcln(BimplyuXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bimplyu<Flt,Int> >) 	tcln(BimplyuXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bimplyu<Flt,Flt> >) 	tcln(BimplyuXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnimplyu<Bln,Bln> >) tcln(BnimplyuXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnimplyu<Bln,Int> >) tcln(BnimplyuXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnimplyu<Bln,Flt> >) tcln(BnimplyuXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnimplyu<Int,Bln> >) tcln(BnimplyuXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnimplyu<Int,Int> >) tcln(BnimplyuXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnimplyu<Int,Flt> >) tcln(BnimplyuXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnimplyu<Flt,Bln> >) tcln(BnimplyuXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnimplyu<Flt,Int> >) tcln(BnimplyuXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnimplyu<Flt,Flt> >) tcln(BnimplyuXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< beqs<Bln,Bln> >) tcln(BeqsXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< beqs<Bln,Int> >) tcln(BeqsXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< beqs<Bln,Flt> >) tcln(BeqsXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< beqs<Int,Bln> >) tcln(BeqsXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< beqs<Int,Int> >) tcln(BeqsXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< beqs<Int,Flt> >) tcln(BeqsXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< beqs<Flt,Bln> >) tcln(BeqsXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< beqs<Flt,Int> >) tcln(BeqsXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< beqs<Flt,Flt> >) tcln(BeqsXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnes<Bln,Bln> >) tcln(BnesXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnes<Bln,Int> >) tcln(BnesXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnes<Bln,Flt> >) tcln(BnesXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnes<Int,Bln> >) tcln(BnesXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnes<Int,Int> >) tcln(BnesXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnes<Int,Flt> >) tcln(BnesXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnes<Flt,Bln> >) tcln(BnesXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnes<Flt,Int> >) tcln(BnesXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnes<Flt,Flt> >) tcln(BnesXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< blts<Bln,Bln> >) tcln(BltsXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< blts<Bln,Int> >) tcln(BltsXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< blts<Bln,Flt> >) tcln(BltsXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< blts<Int,Bln> >) tcln(BltsXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< blts<Int,Int> >) tcln(BltsXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< blts<Int,Flt> >) tcln(BltsXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< blts<Flt,Bln> >) tcln(BltsXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< blts<Flt,Int> >) tcln(BltsXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< blts<Flt,Flt> >) tcln(BltsXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnlts<Bln,Bln> >) tcln(BnltsXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnlts<Bln,Int> >) tcln(BnltsXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnlts<Bln,Flt> >) tcln(BnltsXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnlts<Int,Bln> >) tcln(BnltsXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnlts<Int,Int> >) tcln(BnltsXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnlts<Int,Flt> >) tcln(BnltsXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnlts<Flt,Bln> >) tcln(BnltsXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnlts<Flt,Int> >) tcln(BnltsXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnlts<Flt,Flt> >) tcln(BnltsXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bgts<Bln,Bln> >) tcln(BgtsXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bgts<Bln,Int> >) tcln(BgtsXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bgts<Bln,Flt> >) tcln(BgtsXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bgts<Int,Bln> >) tcln(BgtsXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bgts<Int,Int> >) tcln(BgtsXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bgts<Int,Flt> >) tcln(BgtsXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bgts<Flt,Bln> >) tcln(BgtsXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bgts<Flt,Int> >) tcln(BgtsXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bgts<Flt,Flt> >) tcln(BgtsXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bngts<Bln,Bln> >) tcln(BngtsXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bngts<Bln,Int> >) tcln(BngtsXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bngts<Bln,Flt> >) tcln(BngtsXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bngts<Int,Bln> >) tcln(BngtsXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bngts<Int,Int> >) tcln(BngtsXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bngts<Int,Flt> >) tcln(BngtsXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bngts<Flt,Bln> >) tcln(BngtsXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bngts<Flt,Int> >) tcln(BngtsXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bngts<Flt,Flt> >) tcln(BngtsXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bles<Int,Bln> >) tcln(BlesXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bles<Int,Int> >) tcln(BlesXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bles<Int,Flt> >) tcln(BlesXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bles<Flt,Bln> >) tcln(BlesXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bles<Flt,Int> >) tcln(BlesXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bles<Flt,Flt> >) tcln(BlesXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnles<Int,Bln> >) tcln(BnlesXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnles<Int,Int> >) tcln(BnlesXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnles<Int,Flt> >) tcln(BnlesXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnles<Flt,Bln> >) tcln(BnlesXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnles<Flt,Int> >) tcln(BnlesXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnles<Flt,Flt> >) tcln(BnlesXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bges<Int,Bln> >) tcln(BgesXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bges<Int,Int> >) tcln(BgesXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bges<Int,Flt> >) tcln(BgesXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bges<Flt,Bln> >) tcln(BgesXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bges<Flt,Int> >) tcln(BgesXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bges<Flt,Flt> >) tcln(BgesXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnges<Int,Bln> >) tcln(BngesXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnges<Int,Int> >) tcln(BngesXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnges<Int,Flt> >) tcln(BngesXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnges<Flt,Bln> >) tcln(BngesXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnges<Flt,Int> >) tcln(BngesXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnges<Flt,Flt> >) tcln(BngesXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bequ<Bln,Bln> >) tcln(BequXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bequ<Bln,Int> >) tcln(BequXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bequ<Bln,Flt> >) tcln(BequXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bequ<Int,Bln> >) tcln(BequXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bequ<Int,Int> >) tcln(BequXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bequ<Int,Flt> >) tcln(BequXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bequ<Flt,Bln> >) tcln(BequXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bequ<Flt,Int> >) tcln(BequXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bequ<Flt,Flt> >) tcln(BequXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bneu<Bln,Bln> >) tcln(BneuXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bneu<Bln,Int> >) tcln(BneuXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bneu<Bln,Flt> >) tcln(BneuXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bneu<Int,Bln> >) tcln(BneuXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bneu<Int,Int> >) tcln(BneuXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bneu<Int,Flt> >) tcln(BneuXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bneu<Flt,Bln> >) tcln(BneuXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bneu<Flt,Int> >) tcln(BneuXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bneu<Flt,Flt> >) tcln(BneuXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bltu<Bln,Bln> >) tcln(BltuXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bltu<Bln,Int> >) tcln(BltuXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bltu<Bln,Flt> >) tcln(BltuXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bltu<Int,Bln> >) tcln(BltuXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bltu<Int,Int> >) tcln(BltuXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bltu<Int,Flt> >) tcln(BltuXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bltu<Flt,Bln> >) tcln(BltuXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bltu<Flt,Int> >) tcln(BltuXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bltu<Flt,Flt> >) tcln(BltuXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnltu<Bln,Bln> >) tcln(BnltuXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnltu<Bln,Int> >) tcln(BnltuXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnltu<Bln,Flt> >) tcln(BnltuXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnltu<Int,Bln> >) tcln(BnltuXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnltu<Int,Int> >) tcln(BnltuXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnltu<Int,Flt> >) tcln(BnltuXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnltu<Flt,Bln> >) tcln(BnltuXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnltu<Flt,Int> >) tcln(BnltuXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnltu<Flt,Flt> >) tcln(BnltuXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bgtu<Bln,Bln> >) tcln(BgtuXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bgtu<Bln,Int> >) tcln(BgtuXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bgtu<Bln,Flt> >) tcln(BgtuXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bgtu<Int,Bln> >) tcln(BgtuXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bgtu<Int,Int> >) tcln(BgtuXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bgtu<Int,Flt> >) tcln(BgtuXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bgtu<Flt,Bln> >) tcln(BgtuXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bgtu<Flt,Int> >) tcln(BgtuXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bgtu<Flt,Flt> >) tcln(BgtuXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bngtu<Bln,Bln> >) tcln(BngtuXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bngtu<Bln,Int> >) tcln(BngtuXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bngtu<Bln,Flt> >) tcln(BngtuXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bngtu<Int,Bln> >) tcln(BngtuXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bngtu<Int,Int> >) tcln(BngtuXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bngtu<Int,Flt> >) tcln(BngtuXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bngtu<Flt,Bln> >) tcln(BngtuXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bngtu<Flt,Int> >) tcln(BngtuXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bngtu<Flt,Flt> >) tcln(BngtuXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bleu<Int,Bln> >) tcln(BleuXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bleu<Int,Int> >) tcln(BleuXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bleu<Int,Flt> >) tcln(BleuXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bleu<Flt,Bln> >) tcln(BleuXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bleu<Flt,Int> >) tcln(BleuXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bleu<Flt,Flt> >) tcln(BleuXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bnleu<Int,Bln> >) tcln(BnleuXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnleu<Int,Int> >) tcln(BnleuXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnleu<Int,Flt> >) tcln(BnleuXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bnleu<Flt,Bln> >) tcln(BnleuXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bnleu<Flt,Int> >) tcln(BnleuXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bnleu<Flt,Flt> >) tcln(BnleuXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bgeu<Int,Bln> >) tcln(BgeuXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bgeu<Int,Int> >) tcln(BgeuXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bgeu<Int,Flt> >) tcln(BgeuXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bgeu<Flt,Bln> >) tcln(BgeuXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bgeu<Flt,Int> >) tcln(BgeuXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bgeu<Flt,Flt> >) tcln(BgeuXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bngeu<Int,Bln> >) tcln(BngeuXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bngeu<Int,Int> >) tcln(BngeuXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bngeu<Int,Flt> >) tcln(BngeuXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bngeu<Flt,Bln> >) tcln(BngeuXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bngeu<Flt,Int> >) tcln(BngeuXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bngeu<Flt,Flt> >) tcln(BngeuXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< badd<Bln,Bln> >)  tcln(BaddXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< badd<Bln,Int> >)  tcln(BaddXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< badd<Bln,Flt> >)  tcln(BaddXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< badd<Int,Bln> >)  tcln(BaddXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< badd<Int,Int> >)  tcln(BaddXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< badd<Int,Flt> >)  tcln(BaddXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< badd<Flt,Bln> >)  tcln(BaddXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< badd<Flt,Int> >)  tcln(BaddXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< badd<Flt,Flt> >)  tcln(BaddXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bmult<Bln,Bln> >)  tcln(BmultXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bmult<Bln,Int> >)  tcln(BmultXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bmult<Bln,Flt> >)  tcln(BmultXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bmult<Int,Bln> >)  tcln(BmultXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bmult<Int,Int> >)  tcln(BmultXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bmult<Int,Flt> >)  tcln(BmultXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bmult<Flt,Bln> >)  tcln(BmultXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bmult<Flt,Int> >)  tcln(BmultXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bmult<Flt,Flt> >)  tcln(BmultXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bdiff<Bln,Bln> >)  tcln(BdiffXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bdiff<Bln,Int> >)  tcln(BdiffXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bdiff<Bln,Flt> >)  tcln(BdiffXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bdiff<Int,Bln> >)  tcln(BdiffXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bdiff<Int,Int> >)  tcln(BdiffXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bdiff<Int,Flt> >)  tcln(BdiffXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bdiff<Flt,Bln> >)  tcln(BdiffXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bdiff<Flt,Int> >)  tcln(BdiffXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bdiff<Flt,Flt> >)  tcln(BdiffXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bmax<Bln,Bln> >)  tcln(BmaxXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bmax<Bln,Int> >)  tcln(BmaxXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bmax<Bln,Flt> >)  tcln(BmaxXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bmax<Int,Bln> >)  tcln(BmaxXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bmax<Int,Int> >)  tcln(BmaxXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bmax<Int,Flt> >)  tcln(BmaxXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bmax<Flt,Bln> >)  tcln(BmaxXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bmax<Flt,Int> >)  tcln(BmaxXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bmax<Flt,Flt> >)  tcln(BmaxXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bmin<Bln,Bln> >)  tcln(BminXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bmin<Bln,Int> >)  tcln(BminXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bmin<Bln,Flt> >)  tcln(BminXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bmin<Int,Bln> >)  tcln(BminXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bmin<Int,Int> >)  tcln(BminXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bmin<Int,Flt> >)  tcln(BminXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bmin<Flt,Bln> >)  tcln(BminXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bmin<Flt,Int> >)  tcln(BminXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bmin<Flt,Flt> >)  tcln(BminXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bsub<Bln,Bln> >)  tcln(BsubXbFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bsub<Bln,Int> >)  tcln(BsubXbFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bsub<Bln,Flt> >)  tcln(BsubXbFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bsub<Int,Bln> >)  tcln(BsubXiFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bsub<Int,Int> >)  tcln(BsubXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bsub<Int,Flt> >)  tcln(BsubXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bsub<Flt,Bln> >)  tcln(BsubXfFcMb,AutoClsSegFcM);
rti(BaryXFcMt< bsub<Flt,Int> >)  tcln(BsubXfFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bsub<Flt,Flt> >)  tcln(BsubXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bdiv<Int,Int> >)  tcln(BdivXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bdiv<Int,Flt> >)  tcln(BdivXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bdiv<Flt,Flt> >)  tcln(BdivXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bmod<Int,Int> >)  tcln(BmodXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bmod<Int,Flt> >)  tcln(BmodXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bmod<Flt,Flt> >)  tcln(BmodXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< bpow<Int,Int> >)  tcln(BpowXiFcMi,AutoClsSegFcM);
rti(BaryXFcMt< bpow<Int,Flt> >)  tcln(BpowXiFcMf,AutoClsSegFcM);
rti(BaryXFcMt< bpow<Flt,Flt> >)  tcln(BpowXfFcMf,AutoClsSegFcM);

rti(BaryXFcMt< ipack2<Int,Int> >) tcln(BpackXiFcMi, AutoClsSegFcM);

closeKangarooSpace

#include "cbls/funcs/fcms/segfcms/baryxyfcmt.tcc"
openKangarooSpace
rti(BaryXYFcMt< bhadd<Bln,Int,Bln> >)  tcln(BhaddXbYiFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Bln,Int,Int> >)  tcln(BhaddXbYiFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Bln,Int,Flt> >)  tcln(BhaddXbYiFcMf,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Bln,Flt,Bln> >)  tcln(BhaddXbYfFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Bln,Flt,Int> >)  tcln(BhaddXbYfFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Bln,Flt,Flt> >)  tcln(BhaddXbYfFcMf,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Int,Bln,Bln> >)  tcln(BhaddXiYbFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Int,Bln,Int> >)  tcln(BhaddXiYbFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Int,Bln,Flt> >)  tcln(BhaddXiYbFcMf,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Int,Flt,Bln> >)  tcln(BhaddXiYfFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Int,Flt,Int> >)  tcln(BhaddXiYfFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Int,Flt,Flt> >)  tcln(BhaddXiYfFcMf,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Flt,Bln,Bln> >)  tcln(BhaddXfYbFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Flt,Bln,Int> >)  tcln(BhaddXfYbFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Flt,Bln,Flt> >)  tcln(BhaddXfYbFcMf,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Flt,Int,Bln> >)  tcln(BhaddXfYiFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Flt,Int,Int> >)  tcln(BhaddXfYiFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhadd<Flt,Int,Flt> >)  tcln(BhaddXfYiFcMf,AutoClsSegFcM);

rti(BaryXYFcMt< bhmult<Bln,Int,Bln> >)  tcln(BhmultXbYiFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Bln,Int,Int> >)  tcln(BhmultXbYiFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Bln,Int,Flt> >)  tcln(BhmultXbYiFcMf,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Bln,Flt,Bln> >)  tcln(BhmultXbYfFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Bln,Flt,Int> >)  tcln(BhmultXbYfFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Bln,Flt,Flt> >)  tcln(BhmultXbYfFcMf,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Int,Bln,Bln> >)  tcln(BhmultXiYbFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Int,Bln,Int> >)  tcln(BhmultXiYbFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Int,Bln,Flt> >)  tcln(BhmultXiYbFcMf,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Int,Flt,Bln> >)  tcln(BhmultXiYfFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Int,Flt,Int> >)  tcln(BhmultXiYfFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Int,Flt,Flt> >)  tcln(BhmultXiYfFcMf,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Flt,Bln,Bln> >)  tcln(BhmultXfYbFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Flt,Bln,Int> >)  tcln(BhmultXfYbFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Flt,Bln,Flt> >)  tcln(BhmultXfYbFcMf,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Flt,Int,Bln> >)  tcln(BhmultXfYiFcMb,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Flt,Int,Int> >)  tcln(BhmultXfYiFcMi,AutoClsSegFcM);
rti(BaryXYFcMt< bhmult<Flt,Int,Flt> >)  tcln(BhmultXfYiFcMf,AutoClsSegFcM);
closeKangarooSpace


#include "cbls/funcs/fcms/segfcms/taryxfcmt.tcc"
openKangarooSpace
/* between closed closed satisfaction */
rti(TaryXFcMt< tbccs<Int,Bln> >) tcln(TbccsXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbccs<Int,Int> >) tcln(TbccsXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbccs<Int,Flt> >) tcln(TbccsXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tbccs<Flt,Bln> >) tcln(TbccsXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbccs<Flt,Int> >) tcln(TbccsXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbccs<Flt,Flt> >) tcln(TbccsXfFcMf,AutoClsSegFcM);

/* between open open satisfaction */
rti(TaryXFcMt< tboos<Int,Bln> >) tcln(TboosXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tboos<Int,Int> >) tcln(TboosXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tboos<Int,Flt> >) tcln(TboosXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tboos<Flt,Bln> >) tcln(TboosXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tboos<Flt,Int> >) tcln(TboosXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tboos<Flt,Flt> >) tcln(TboosXfFcMf,AutoClsSegFcM);

/* between closed open satisfaction */
rti(TaryXFcMt< tbcos<Int,Bln> >) tcln(TbcosXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbcos<Int,Int> >) tcln(TbcosXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbcos<Int,Flt> >) tcln(TbcosXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tbcos<Flt,Bln> >) tcln(TbcosXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbcos<Flt,Int> >) tcln(TbcosXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbcos<Flt,Flt> >) tcln(TbcosXfFcMf,AutoClsSegFcM);

/* between open closed satisfaction */
rti(TaryXFcMt< tbocs<Int,Bln> >) tcln(TbocsXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbocs<Int,Int> >) tcln(TbocsXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbocs<Int,Flt> >) tcln(TbocsXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tbocs<Flt,Bln> >) tcln(TbocsXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbocs<Flt,Int> >) tcln(TbocsXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbocs<Flt,Flt> >) tcln(TbocsXfFcMf,AutoClsSegFcM);

/* not between closed closed satisfaction */
rti(TaryXFcMt< tnbccs<Int,Bln> >) tcln(TnbccsXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbccs<Int,Int> >) tcln(TnbccsXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbccs<Int,Flt> >) tcln(TnbccsXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tnbccs<Flt,Bln> >) tcln(TnbccsXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbccs<Flt,Int> >) tcln(TnbccsXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbccs<Flt,Flt> >) tcln(TnbccsXfFcMf,AutoClsSegFcM);

/* not between open open satisfaction */
rti(TaryXFcMt< tnboos<Int,Bln> >) tcln(TnboosXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnboos<Int,Int> >) tcln(TnboosXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnboos<Int,Flt> >) tcln(TnboosXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tnboos<Flt,Bln> >) tcln(TnboosXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnboos<Flt,Int> >) tcln(TnboosXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnboos<Flt,Flt> >) tcln(TnboosXfFcMf,AutoClsSegFcM);

/* not between closed open satisfaction */
rti(TaryXFcMt< tnbcos<Int,Bln> >) tcln(TnbcosXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbcos<Int,Int> >) tcln(TnbcosXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbcos<Int,Flt> >) tcln(TnbcosXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tnbcos<Flt,Bln> >) tcln(TnbcosXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbcos<Flt,Int> >) tcln(TnbcosXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbcos<Flt,Flt> >) tcln(TnbcosXfFcMf,AutoClsSegFcM);

/* not between open closed satisfaction */
rti(TaryXFcMt< tnbocs<Int,Bln> >) tcln(TnbocsXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbocs<Int,Int> >) tcln(TnbocsXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbocs<Int,Flt> >) tcln(TnbocsXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tnbocs<Flt,Bln> >) tcln(TnbocsXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbocs<Flt,Int> >) tcln(TnbocsXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbocs<Flt,Flt> >) tcln(TnbocsXfFcMf,AutoClsSegFcM);

/* between closed closed unsatisfaction */
rti(TaryXFcMt< tbccu<Int,Bln> >) tcln(TbccuXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbccu<Int,Int> >) tcln(TbccuXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbccu<Int,Flt> >) tcln(TbccuXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tbccu<Flt,Bln> >) tcln(TbccuXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbccu<Flt,Int> >) tcln(TbccuXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbccu<Flt,Flt> >) tcln(TbccuXfFcMf,AutoClsSegFcM);

/* between open open unsatisfaction */
rti(TaryXFcMt< tboou<Int,Bln> >) tcln(TboouXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tboou<Int,Int> >) tcln(TboouXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tboou<Int,Flt> >) tcln(TboouXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tboou<Flt,Bln> >) tcln(TboouXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tboou<Flt,Int> >) tcln(TboouXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tboou<Flt,Flt> >) tcln(TboouXfFcMf,AutoClsSegFcM);

/* between closed open unsatisfaction */
rti(TaryXFcMt< tbcou<Int,Bln> >) tcln(TbcouXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbcou<Int,Int> >) tcln(TbcouXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbcou<Int,Flt> >) tcln(TbcouXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tbcou<Flt,Bln> >) tcln(TbcouXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbcou<Flt,Int> >) tcln(TbcouXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbcou<Flt,Flt> >) tcln(TbcouXfFcMf,AutoClsSegFcM);

/* between open closed unsatisfaction */
rti(TaryXFcMt< tbocu<Int,Bln> >) tcln(TbocuXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbocu<Int,Int> >) tcln(TbocuXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbocu<Int,Flt> >) tcln(TbocuXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tbocu<Flt,Bln> >) tcln(TbocuXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tbocu<Flt,Int> >) tcln(TbocuXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tbocu<Flt,Flt> >) tcln(TbocuXfFcMf,AutoClsSegFcM);

/* not between closed closed unsatisfaction */
rti(TaryXFcMt< tnbccu<Int,Bln> >) tcln(TnbccuXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbccu<Int,Int> >) tcln(TnbccuXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbccu<Int,Flt> >) tcln(TnbccuXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tnbccu<Flt,Bln> >) tcln(TnbccuXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbccu<Flt,Int> >) tcln(TnbccuXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbccu<Flt,Flt> >) tcln(TnbccuXfFcMf,AutoClsSegFcM);

/* not between open open unsatisfaction */
rti(TaryXFcMt< tnboou<Int,Bln> >) tcln(TnboouXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnboou<Int,Int> >) tcln(TnboouXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnboou<Int,Flt> >) tcln(TnboouXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tnboou<Flt,Bln> >) tcln(TnboouXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnboou<Flt,Int> >) tcln(TnboouXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnboou<Flt,Flt> >) tcln(TnboouXfFcMf,AutoClsSegFcM);

/* not between closed open unsatisfaction */
rti(TaryXFcMt< tnbcou<Int,Bln> >) tcln(TnbcouXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbcou<Int,Int> >) tcln(TnbcouXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbcou<Int,Flt> >) tcln(TnbcouXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tnbcou<Flt,Bln> >) tcln(TnbcouXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbcou<Flt,Int> >) tcln(TnbcouXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbcou<Flt,Flt> >) tcln(TnbcouXfFcMf,AutoClsSegFcM);

/* not between open closed unsatisfaction */
rti(TaryXFcMt< tnbocu<Int,Bln> >) tcln(TnbocuXiFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbocu<Int,Int> >) tcln(TnbocuXiFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbocu<Int,Flt> >) tcln(TnbocuXiFcMf,AutoClsSegFcM);
rti(TaryXFcMt< tnbocu<Flt,Bln> >) tcln(TnbocuXfFcMb,AutoClsSegFcM);
rti(TaryXFcMt< tnbocu<Flt,Int> >) tcln(TnbocuXfFcMi,AutoClsSegFcM);
rti(TaryXFcMt< tnbocu<Flt,Flt> >) tcln(TnbocuXfFcMf,AutoClsSegFcM);

rti(TaryXFcMt< ipack3<Int,Int> >) tcln(TpackXiFcMi, AutoClsSegFcM);

closeKangarooSpace

#include "cbls/funcs/fcms/segfcms/bindxfcmt.tcc"
openKangarooSpace

rti(BindXFcMt< bind2r<beqs<Bln,Bln> > >) tcln(UeqsXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<beqs<Bln,Int> > >) tcln(UeqsXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<beqs<Bln,Flt> > >) tcln(UeqsXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<beqs<Int,Bln> > >) tcln(UeqsXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<beqs<Int,Int> > >) tcln(UeqsXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<beqs<Int,Flt> > >) tcln(UeqsXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<beqs<Flt,Bln> > >) tcln(UeqsXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<beqs<Flt,Int> > >) tcln(UeqsXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<beqs<Flt,Flt> > >) tcln(UeqsXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bnes<Bln,Bln> > >) tcln(UnesXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnes<Bln,Int> > >) tcln(UnesXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnes<Bln,Flt> > >) tcln(UnesXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnes<Int,Bln> > >) tcln(UnesXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnes<Int,Int> > >) tcln(UnesXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnes<Int,Flt> > >) tcln(UnesXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnes<Flt,Bln> > >) tcln(UnesXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnes<Flt,Int> > >) tcln(UnesXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnes<Flt,Flt> > >) tcln(UnesXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bgts<Bln,Bln> > >) tcln(UgtsXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgts<Bln,Int> > >) tcln(UgtsXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgts<Bln,Flt> > >) tcln(UgtsXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgts<Int,Bln> > >) tcln(UgtsXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgts<Int,Int> > >) tcln(UgtsXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgts<Int,Flt> > >) tcln(UgtsXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgts<Flt,Bln> > >) tcln(UgtsXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgts<Flt,Int> > >) tcln(UgtsXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgts<Flt,Flt> > >) tcln(UgtsXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bngts<Bln,Bln> > >) tcln(UngtsXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngts<Bln,Int> > >) tcln(UngtsXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngts<Bln,Flt> > >) tcln(UngtsXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngts<Int,Bln> > >) tcln(UngtsXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngts<Int,Int> > >) tcln(UngtsXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngts<Int,Flt> > >) tcln(UngtsXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngts<Flt,Bln> > >) tcln(UngtsXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngts<Flt,Int> > >) tcln(UngtsXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngts<Flt,Flt> > >) tcln(UngtsXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<blts<Bln,Bln> > >) tcln(UltsXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<blts<Bln,Int> > >) tcln(UltsXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<blts<Bln,Flt> > >) tcln(UltsXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<blts<Int,Bln> > >) tcln(UltsXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<blts<Int,Int> > >) tcln(UltsXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<blts<Int,Flt> > >) tcln(UltsXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<blts<Flt,Bln> > >) tcln(UltsXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<blts<Flt,Int> > >) tcln(UltsXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<blts<Flt,Flt> > >) tcln(UltsXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bnlts<Bln,Bln> > >) tcln(UnltsXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnlts<Bln,Int> > >) tcln(UnltsXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnlts<Bln,Flt> > >) tcln(UnltsXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnlts<Int,Bln> > >) tcln(UnltsXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnlts<Int,Int> > >) tcln(UnltsXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnlts<Int,Flt> > >) tcln(UnltsXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnlts<Flt,Bln> > >) tcln(UnltsXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnlts<Flt,Int> > >) tcln(UnltsXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnlts<Flt,Flt> > >) tcln(UnltsXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bges<Int,Bln> > >) tcln(UgesXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bges<Int,Int> > >) tcln(UgesXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bges<Int,Flt> > >) tcln(UgesXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bges<Flt,Bln> > >) tcln(UgesXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bges<Flt,Int> > >) tcln(UgesXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bges<Flt,Flt> > >) tcln(UgesXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bnges<Int,Bln> > >) tcln(UngesXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnges<Int,Int> > >) tcln(UngesXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnges<Int,Flt> > >) tcln(UngesXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnges<Flt,Bln> > >) tcln(UngesXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnges<Flt,Int> > >) tcln(UngesXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnges<Flt,Flt> > >) tcln(UngesXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bles<Int,Bln> > >) tcln(UlesXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bles<Int,Int> > >) tcln(UlesXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bles<Int,Flt> > >) tcln(UlesXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bles<Flt,Bln> > >) tcln(UlesXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bles<Flt,Int> > >) tcln(UlesXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bles<Flt,Flt> > >) tcln(UlesXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bnles<Int,Bln> > >) tcln(UnlesXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnles<Int,Int> > >) tcln(UnlesXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnles<Int,Flt> > >) tcln(UnlesXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnles<Flt,Bln> > >) tcln(UnlesXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnles<Flt,Int> > >) tcln(UnlesXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnles<Flt,Flt> > >) tcln(UnlesXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bequ<Bln,Bln> > >) tcln(UequXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bequ<Bln,Int> > >) tcln(UequXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bequ<Bln,Flt> > >) tcln(UequXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bequ<Int,Bln> > >) tcln(UequXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bequ<Int,Int> > >) tcln(UequXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bequ<Int,Flt> > >) tcln(UequXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bequ<Flt,Bln> > >) tcln(UequXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bequ<Flt,Int> > >) tcln(UequXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bequ<Flt,Flt> > >) tcln(UequXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bneu<Bln,Bln> > >) tcln(UneuXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bneu<Bln,Int> > >) tcln(UneuXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bneu<Bln,Flt> > >) tcln(UneuXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bneu<Int,Bln> > >) tcln(UneuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bneu<Int,Int> > >) tcln(UneuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bneu<Int,Flt> > >) tcln(UneuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bneu<Flt,Bln> > >) tcln(UneuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bneu<Flt,Int> > >) tcln(UneuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bneu<Flt,Flt> > >) tcln(UneuXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bgtu<Bln,Bln> > >) tcln(UgtuXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgtu<Bln,Int> > >) tcln(UgtuXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgtu<Bln,Flt> > >) tcln(UgtuXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgtu<Int,Bln> > >) tcln(UgtuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgtu<Int,Int> > >) tcln(UgtuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgtu<Int,Flt> > >) tcln(UgtuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgtu<Flt,Bln> > >) tcln(UgtuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgtu<Flt,Int> > >) tcln(UgtuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgtu<Flt,Flt> > >) tcln(UgtuXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bngtu<Bln,Bln> > >) tcln(UngtuXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngtu<Bln,Int> > >) tcln(UngtuXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngtu<Bln,Flt> > >) tcln(UngtuXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngtu<Int,Bln> > >) tcln(UngtuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngtu<Int,Int> > >) tcln(UngtuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngtu<Int,Flt> > >) tcln(UngtuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngtu<Flt,Bln> > >) tcln(UngtuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngtu<Flt,Int> > >) tcln(UngtuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngtu<Flt,Flt> > >) tcln(UngtuXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bltu<Bln,Bln> > >) tcln(UltuXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bltu<Bln,Int> > >) tcln(UltuXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bltu<Bln,Flt> > >) tcln(UltuXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bltu<Int,Bln> > >) tcln(UltuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bltu<Int,Int> > >) tcln(UltuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bltu<Int,Flt> > >) tcln(UltuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bltu<Flt,Bln> > >) tcln(UltuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bltu<Flt,Int> > >) tcln(UltuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bltu<Flt,Flt> > >) tcln(UltuXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bnltu<Bln,Bln> > >) tcln(UnltuXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnltu<Bln,Int> > >) tcln(UnltuXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnltu<Bln,Flt> > >) tcln(UnltuXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnltu<Int,Bln> > >) tcln(UnltuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnltu<Int,Int> > >) tcln(UnltuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnltu<Int,Flt> > >) tcln(UnltuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnltu<Flt,Bln> > >) tcln(UnltuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnltu<Flt,Int> > >) tcln(UnltuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnltu<Flt,Flt> > >) tcln(UnltuXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bgeu<Int,Bln> > >) tcln(UgeuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgeu<Int,Int> > >) tcln(UgeuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgeu<Int,Flt> > >) tcln(UgeuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgeu<Flt,Bln> > >) tcln(UgeuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgeu<Flt,Int> > >) tcln(UgeuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bgeu<Flt,Flt> > >) tcln(UgeuXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bngeu<Int,Bln> > >) tcln(UngeuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngeu<Int,Int> > >) tcln(UngeuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngeu<Int,Flt> > >) tcln(UngeuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngeu<Flt,Bln> > >) tcln(UngeuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngeu<Flt,Int> > >) tcln(UngeuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bngeu<Flt,Flt> > >) tcln(UngeuXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bleu<Int,Bln> > >) tcln(UleuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bleu<Int,Int> > >) tcln(UleuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bleu<Int,Flt> > >) tcln(UleuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bleu<Flt,Bln> > >) tcln(UleuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bleu<Flt,Int> > >) tcln(UleuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bleu<Flt,Flt> > >) tcln(UleuXfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bind2r<bnleu<Int,Bln> > >) tcln(UnleuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnleu<Int,Int> > >) tcln(UnleuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnleu<Int,Flt> > >) tcln(UnleuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnleu<Flt,Bln> > >) tcln(UnleuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnleu<Flt,Int> > >) tcln(UnleuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bnleu<Flt,Flt> > >) tcln(UnleuXfFcMf,AutoClsSegFcM);

/* addition */
rti(BindXFcMt< bind2r<badd<Bln,Bln> > >) tcln(UaddXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<badd<Bln,Int> > >) tcln(UaddXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<badd<Bln,Flt> > >) tcln(UaddXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<badd<Int,Bln> > >) tcln(UaddXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<badd<Int,Int> > >) tcln(UaddXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<badd<Int,Flt> > >) tcln(UaddXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<badd<Flt,Bln> > >) tcln(UaddXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<badd<Flt,Int> > >) tcln(UaddXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<badd<Flt,Flt> > >) tcln(UaddXfFcMf,AutoClsSegFcM);

/* multiplication */
rti(BindXFcMt< bind2r<bmult<Bln,Bln> > >) tcln(UmultXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmult<Bln,Int> > >) tcln(UmultXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmult<Bln,Flt> > >) tcln(UmultXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmult<Int,Bln> > >) tcln(UmultXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmult<Int,Int> > >) tcln(UmultXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmult<Int,Flt> > >) tcln(UmultXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmult<Flt,Bln> > >) tcln(UmultXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmult<Flt,Int> > >) tcln(UmultXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmult<Flt,Flt> > >) tcln(UmultXfFcMf,AutoClsSegFcM);

/* difference = abs(x-y) */
rti(BindXFcMt< bind2r<bdiff<Bln,Bln> > >) tcln(UdiffXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bdiff<Bln,Int> > >) tcln(UdiffXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bdiff<Bln,Flt> > >) tcln(UdiffXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bdiff<Int,Bln> > >) tcln(UdiffXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bdiff<Int,Int> > >) tcln(UdiffXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bdiff<Int,Flt> > >) tcln(UdiffXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bdiff<Flt,Bln> > >) tcln(UdiffXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bdiff<Flt,Int> > >) tcln(UdiffXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bdiff<Flt,Flt> > >) tcln(UdiffXfFcMf,AutoClsSegFcM);

/* maximum */
rti(BindXFcMt< bind2r<bmax<Bln,Bln> > >) tcln(UmaxXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmax<Bln,Int> > >) tcln(UmaxXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmax<Bln,Flt> > >) tcln(UmaxXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmax<Int,Bln> > >) tcln(UmaxXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmax<Int,Int> > >) tcln(UmaxXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmax<Int,Flt> > >) tcln(UmaxXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmax<Flt,Bln> > >) tcln(UmaxXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmax<Flt,Int> > >) tcln(UmaxXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmax<Flt,Flt> > >) tcln(UmaxXfFcMf,AutoClsSegFcM);

/* minimum */
rti(BindXFcMt< bind2r<bmin<Bln,Bln> > >) tcln(UminXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmin<Bln,Int> > >) tcln(UminXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmin<Bln,Flt> > >) tcln(UminXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmin<Int,Bln> > >) tcln(UminXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmin<Int,Int> > >) tcln(UminXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmin<Int,Flt> > >) tcln(UminXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmin<Flt,Bln> > >) tcln(UminXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmin<Flt,Int> > >) tcln(UminXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmin<Flt,Flt> > >) tcln(UminXfFcMf,AutoClsSegFcM);

/* subtraction */
rti(BindXFcMt< bind2r<bsub<Bln,Bln> > >) tcln(UsubXbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bsub<Bln,Int> > >) tcln(UsubXbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bsub<Bln,Flt> > >) tcln(UsubXbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bsub<Int,Bln> > >) tcln(UsubXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bsub<Int,Int> > >) tcln(UsubXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bsub<Int,Flt> > >) tcln(UsubXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bsub<Flt,Bln> > >) tcln(UsubXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bsub<Flt,Int> > >) tcln(UsubXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bsub<Flt,Flt> > >) tcln(UsubXfFcMf,AutoClsSegFcM);

/* division */
rti(BindXFcMt< bind2r<bdiv<Int,Int> > >)  tcln(UdivXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bdiv<Flt,Flt> > >)  tcln(UdivXfFcMf,AutoClsSegFcM);

/* modulus */
rti(BindXFcMt< bind2r<bmod<Int,Int> > >)  tcln(UmodXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bmod<Flt,Flt> > >)  tcln(UmodXfFcMf,AutoClsSegFcM);

/* power */
rti(BindXFcMt< bind2r<bpow<Int,Int> > >)  tcln(UpowXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind2r<bpow<Flt,Flt> > >)  tcln(UpowXfFcMf,AutoClsSegFcM);

/* between closed closed satisfaction */
rti(BindXFcMt< bind3lr<tbccs<Int,Bln> > >) tcln(UbccsXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbccs<Int,Int> > >) tcln(UbccsXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbccs<Int,Flt> > >) tcln(UbccsXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbccs<Flt,Bln> > >) tcln(UbccsXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbccs<Flt,Int> > >) tcln(UbccsXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbccs<Flt,Flt> > >) tcln(UbccsXfFcMf,AutoClsSegFcM);

/* between open open satisfaction */
rti(BindXFcMt< bind3lr<tboos<Int,Bln> > >) tcln(UboosXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tboos<Int,Int> > >) tcln(UboosXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tboos<Int,Flt> > >) tcln(UboosXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tboos<Flt,Bln> > >) tcln(UboosXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tboos<Flt,Int> > >) tcln(UboosXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tboos<Flt,Flt> > >) tcln(UboosXfFcMf,AutoClsSegFcM);

/* between closed open satisfaction */
rti(BindXFcMt< bind3lr<tbcos<Int,Bln> > >) tcln(UbcosXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbcos<Int,Int> > >) tcln(UbcosXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbcos<Int,Flt> > >) tcln(UbcosXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbcos<Flt,Bln> > >) tcln(UbcosXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbcos<Flt,Int> > >) tcln(UbcosXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbcos<Flt,Flt> > >) tcln(UbcosXfFcMf,AutoClsSegFcM);

/* between open closed satisfaction */
rti(BindXFcMt< bind3lr<tbocs<Int,Bln> > >) tcln(UbocsXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbocs<Int,Int> > >) tcln(UbocsXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbocs<Int,Flt> > >) tcln(UbocsXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbocs<Flt,Bln> > >) tcln(UbocsXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbocs<Flt,Int> > >) tcln(UbocsXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbocs<Flt,Flt> > >) tcln(UbocsXfFcMf,AutoClsSegFcM);

/* not between closed closed satisfaction */
rti(BindXFcMt< bind3lr<tnbccs<Int,Bln> > >) tcln(UnbccsXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbccs<Int,Int> > >) tcln(UnbccsXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbccs<Int,Flt> > >) tcln(UnbccsXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbccs<Flt,Bln> > >) tcln(UnbccsXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbccs<Flt,Int> > >) tcln(UnbccsXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbccs<Flt,Flt> > >) tcln(UnbccsXfFcMf,AutoClsSegFcM);

/* not between open open satisfaction */
rti(BindXFcMt< bind3lr<tnboos<Int,Bln> > >) tcln(UnboosXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnboos<Int,Int> > >) tcln(UnboosXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnboos<Int,Flt> > >) tcln(UnboosXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnboos<Flt,Bln> > >) tcln(UnboosXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnboos<Flt,Int> > >) tcln(UnboosXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnboos<Flt,Flt> > >) tcln(UnboosXfFcMf,AutoClsSegFcM);

/* not between closed open satisfaction */
rti(BindXFcMt< bind3lr<tnbcos<Int,Bln> > >) tcln(UnbcosXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbcos<Int,Int> > >) tcln(UnbcosXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbcos<Int,Flt> > >) tcln(UnbcosXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbcos<Flt,Bln> > >) tcln(UnbcosXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbcos<Flt,Int> > >) tcln(UnbcosXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbcos<Flt,Flt> > >) tcln(UnbcosXfFcMf,AutoClsSegFcM);

/* not between open closed satisfaction */
rti(BindXFcMt< bind3lr<tnbocs<Int,Bln> > >) tcln(UnbocsXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbocs<Int,Int> > >) tcln(UnbocsXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbocs<Int,Flt> > >) tcln(UnbocsXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbocs<Flt,Bln> > >) tcln(UnbocsXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbocs<Flt,Int> > >) tcln(UnbocsXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbocs<Flt,Flt> > >) tcln(UnbocsXfFcMf,AutoClsSegFcM);

/* between closed closed unsatisfaction */
rti(BindXFcMt< bind3lr<tbccu<Int,Bln> > >) tcln(UbccuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbccu<Int,Int> > >) tcln(UbccuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbccu<Int,Flt> > >) tcln(UbccuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbccu<Flt,Bln> > >) tcln(UbccuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbccu<Flt,Int> > >) tcln(UbccuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbccu<Flt,Flt> > >) tcln(UbccuXfFcMf,AutoClsSegFcM);

/* between open open unsatisfaction */
rti(BindXFcMt< bind3lr<tboou<Int,Bln> > >) tcln(UboouXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tboou<Int,Int> > >) tcln(UboouXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tboou<Int,Flt> > >) tcln(UboouXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tboou<Flt,Bln> > >) tcln(UboouXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tboou<Flt,Int> > >) tcln(UboouXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tboou<Flt,Flt> > >) tcln(UboouXfFcMf,AutoClsSegFcM);

/* between closed open unsatisfaction */
rti(BindXFcMt< bind3lr<tbcou<Int,Bln> > >) tcln(UbcouXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbcou<Int,Int> > >) tcln(UbcouXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbcou<Int,Flt> > >) tcln(UbcouXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbcou<Flt,Bln> > >) tcln(UbcouXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbcou<Flt,Int> > >) tcln(UbcouXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbcou<Flt,Flt> > >) tcln(UbcouXfFcMf,AutoClsSegFcM);

/* between open closed unsatisfaction */
rti(BindXFcMt< bind3lr<tbocu<Int,Bln> > >) tcln(UbocuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbocu<Int,Int> > >) tcln(UbocuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbocu<Int,Flt> > >) tcln(UbocuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbocu<Flt,Bln> > >) tcln(UbocuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbocu<Flt,Int> > >) tcln(UbocuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tbocu<Flt,Flt> > >) tcln(UbocuXfFcMf,AutoClsSegFcM);

/* not between closed closed unsatisfaction */
rti(BindXFcMt< bind3lr<tnbccu<Int,Bln> > >) tcln(UnbccuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbccu<Int,Int> > >) tcln(UnbccuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbccu<Int,Flt> > >) tcln(UnbccuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbccu<Flt,Bln> > >) tcln(UnbccuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbccu<Flt,Int> > >) tcln(UnbccuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbccu<Flt,Flt> > >) tcln(UnbccuXfFcMf,AutoClsSegFcM);

/* not between open open unsatisfaction */
rti(BindXFcMt< bind3lr<tnboou<Int,Bln> > >) tcln(UnboouXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnboou<Int,Int> > >) tcln(UnboouXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnboou<Int,Flt> > >) tcln(UnboouXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnboou<Flt,Bln> > >) tcln(UnboouXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnboou<Flt,Int> > >) tcln(UnboouXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnboou<Flt,Flt> > >) tcln(UnboouXfFcMf,AutoClsSegFcM);

/* not between closed open unsatisfaction */
rti(BindXFcMt< bind3lr<tnbcou<Int,Bln> > >) tcln(UnbcouXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbcou<Int,Int> > >) tcln(UnbcouXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbcou<Int,Flt> > >) tcln(UnbcouXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbcou<Flt,Bln> > >) tcln(UnbcouXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbcou<Flt,Int> > >) tcln(UnbcouXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbcou<Flt,Flt> > >) tcln(UnbcouXfFcMf,AutoClsSegFcM);

/* not between open closed unsatisfaction */
rti(BindXFcMt< bind3lr<tnbocu<Int,Bln> > >) tcln(UnbocuXiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbocu<Int,Int> > >) tcln(UnbocuXiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbocu<Int,Flt> > >) tcln(UnbocuXiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbocu<Flt,Bln> > >) tcln(UnbocuXfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbocu<Flt,Int> > >) tcln(UnbocuXfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bind3lr<tnbocu<Flt,Flt> > >) tcln(UnbocuXfFcMf,AutoClsSegFcM);

/* ternary if */
rti(BindXFcMt< bindc3lr<tif<Bln,Bln,Bln> > >) tcln(UifXbKbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Bln,Bln,Int> > >) tcln(UifXbKbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Bln,Int,Bln> > >) tcln(UifXbKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Bln,Int,Int> > >) tcln(UifXbKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Bln,Flt,Flt> > >) tcln(UifXbKfFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Int,Bln,Bln> > >) tcln(UifXiKbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Int,Bln,Int> > >) tcln(UifXiKbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Int,Int,Bln> > >) tcln(UifXiKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Int,Int,Int> > >) tcln(UifXiKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Int,Flt,Flt> > >) tcln(UifXiKfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bindc3lr<tif<Bln,Bln,Flt> > >) tcln(UifXbKbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Bln,Int,Flt> > >) tcln(UifXbKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Bln,Flt,Bln> > >) tcln(UifXbKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Bln,Flt,Int> > >) tcln(UifXbKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Int,Bln,Flt> > >) tcln(UifXiKbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Int,Int,Flt> > >) tcln(UifXiKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Int,Flt,Bln> > >) tcln(UifXiKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Int,Flt,Int> > >) tcln(UifXiKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Flt,Bln,Bln> > >) tcln(UifXfKbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Flt,Bln,Int> > >) tcln(UifXfKbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Flt,Bln,Flt> > >) tcln(UifXfKbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Flt,Int,Bln> > >) tcln(UifXfKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Flt,Int,Int> > >) tcln(UifXfKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Flt,Int,Flt> > >) tcln(UifXfKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Flt,Flt,Bln> > >) tcln(UifXfKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Flt,Flt,Int> > >) tcln(UifXfKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindc3lr<tif<Flt,Flt,Flt> > >) tcln(UifXfKfFcMf,AutoClsSegFcM);

/* indexed list */
rti(BindXFcMt< bindcNd<nil<Int,Bln,Bln> > >) tcln(UilXiKbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Int,Bln,Int> > >) tcln(UilXiKbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Int,Int,Bln> > >) tcln(UilXiKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Int,Int,Int> > >) tcln(UilXiKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Int,Flt,Flt> > >) tcln(UilXiKfFcMf,AutoClsSegFcM);

rti(BindXFcMt< bindcNd<nil<Bln,Bln,Bln> > >) tcln(UilXbKbFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Bln,Bln,Int> > >) tcln(UilXbKbFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Bln,Bln,Flt> > >) tcln(UilXbKbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Bln,Int,Bln> > >) tcln(UilXbKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Bln,Int,Int> > >) tcln(UilXbKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Bln,Int,Flt> > >) tcln(UilXbKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Bln,Flt,Bln> > >) tcln(UilXbKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Bln,Flt,Int> > >) tcln(UilXbKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Bln,Flt,Flt> > >) tcln(UilXbKfFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Int,Bln,Flt> > >) tcln(UilXiKbFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Int,Int,Flt> > >) tcln(UilXiKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Int,Flt,Bln> > >) tcln(UilXiKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindcNd<nil<Int,Flt,Int> > >) tcln(UilXiKfFcMi,AutoClsSegFcM);

/* linear piecewise function with linear search */
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Int,Int,Bln> > >) tcln(UlpflXiKiKiKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Int,Int,Int> > >) tcln(UlpflXiKiKiKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Int,Int,Flt> > >) tcln(UlpflXiKiKiKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Int,Flt,Bln> > >) tcln(UlpflXiKiKiKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Int,Flt,Int> > >) tcln(UlpflXiKiKiKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Int,Flt,Flt> > >) tcln(UlpflXiKiKiKfFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Flt,Int,Bln> > >) tcln(UlpflXiKiKfKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Flt,Int,Int> > >) tcln(UlpflXiKiKfKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Flt,Int,Flt> > >) tcln(UlpflXiKiKfKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Flt,Flt,Bln> > >) tcln(UlpflXiKiKfKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Flt,Flt,Int> > >) tcln(UlpflXiKiKfKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Int,Flt,Flt,Flt> > >) tcln(UlpflXiKiKfKfFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Int,Int,Bln> > >) tcln(UlpflXiKfKiKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Int,Int,Int> > >) tcln(UlpflXiKfKiKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Int,Int,Flt> > >) tcln(UlpflXiKfKiKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Int,Flt,Bln> > >) tcln(UlpflXiKfKiKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Int,Flt,Int> > >) tcln(UlpflXiKfKiKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Int,Flt,Flt> > >) tcln(UlpflXiKfKiKfFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Flt,Int,Bln> > >) tcln(UlpflXiKfKfKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Flt,Int,Int> > >) tcln(UlpflXiKfKfKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Flt,Int,Flt> > >) tcln(UlpflXiKfKfKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Flt,Flt,Bln> > >) tcln(UlpflXiKfKfKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Flt,Flt,Int> > >) tcln(UlpflXiKfKfKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Int,Flt,Flt,Flt,Flt> > >) tcln(UlpflXiKfKfKfFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Int,Int,Bln> > >) tcln(UlpflXfKiKiKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Int,Int,Int> > >) tcln(UlpflXfKiKiKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Int,Int,Flt> > >) tcln(UlpflXfKiKiKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Int,Flt,Bln> > >) tcln(UlpflXfKiKiKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Int,Flt,Int> > >) tcln(UlpflXfKiKiKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Int,Flt,Flt> > >) tcln(UlpflXfKiKiKfFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Flt,Int,Bln> > >) tcln(UlpflXfKiKfKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Flt,Int,Int> > >) tcln(UlpflXfKiKfKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Flt,Int,Flt> > >) tcln(UlpflXfKiKfKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Flt,Flt,Bln> > >) tcln(UlpflXfKiKfKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Flt,Flt,Int> > >) tcln(UlpflXfKiKfKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Int,Flt,Flt,Flt> > >) tcln(UlpflXfKiKfKfFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Int,Int,Bln> > >) tcln(UlpflXfKfKiKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Int,Int,Int> > >) tcln(UlpflXfKfKiKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Int,Int,Flt> > >) tcln(UlpflXfKfKiKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Int,Flt,Bln> > >) tcln(UlpflXfKfKiKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Int,Flt,Int> > >) tcln(UlpflXfKfKiKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Int,Flt,Flt> > >) tcln(UlpflXfKfKiKfFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Flt,Int,Bln> > >) tcln(UlpflXfKfKfKiFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Flt,Int,Int> > >) tcln(UlpflXfKfKfKiFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Flt,Int,Flt> > >) tcln(UlpflXfKfKfKiFcMf,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Flt,Flt,Bln> > >) tcln(UlpflXfKfKfKfFcMb,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Flt,Flt,Int> > >) tcln(UlpflXfKfKfKfFcMi,AutoClsSegFcM);
rti(BindXFcMt< bindiNiddlr<lpfl<Flt,Flt,Flt,Flt,Flt> > >) tcln(UlpflXfKfKfKfFcMf,AutoClsSegFcM);

closeKangarooSpace


#endif//SegFcMsRegHhIncluded
