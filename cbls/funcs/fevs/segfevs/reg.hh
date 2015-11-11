/*!
	@file segfevs/reg.hh
	@brief The register header file for segfevs.
	@details This is the register header file for segfevs.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef SegFeVsRegHhIncluded
#define SegFeVsRegHhIncluded

#include "cbls/funcs/opfns/idx.hh"

openKangarooSpace
#define AutoClsSegFeV (TermStub<FeV>::TermCat * 10000 + (thisLine - AutoClsBaseSegFeV))
enum { AutoClsBaseSegFeV = thisLine};
closeKangarooSpace

#include "cbls/funcs/fevs/segfevs/uaryxfevt.tcc"
openKangarooSpace
rti(UaryXFeVt< ucast<Bln,Int> >) tcln(UcastXbFeVi,AutoClsSegFeV);
rti(UaryXFeVt< ucast<Int,Bln> >) tcln(UcastXiFeVb,AutoClsSegFeV);
rti(UaryXFeVt< ucast<Bln,Flt> >) tcln(UcastXbFeVf,AutoClsSegFeV);
rti(UaryXFeVt< ucast<Flt,Bln> >) tcln(UcastXfFeVb,AutoClsSegFeV);
rti(UaryXFeVt< ucast<Int,Flt> >) tcln(UcastXiFeVf,AutoClsSegFeV);
rti(UaryXFeVt< ucast<Flt,Int> >) tcln(UcastXfFeVi,AutoClsSegFeV);

rti(UaryXFeVt< unots<Bln,Bln> >) tcln(UnotsXbFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unots<Bln,Int> >) tcln(UnotsXbFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unots<Bln,Flt> >) tcln(UnotsXbFeVf,AutoClsSegFeV);
rti(UaryXFeVt< unots<Int,Bln> >) tcln(UnotsXiFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unots<Int,Int> >) tcln(UnotsXiFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unots<Int,Flt> >) tcln(UnotsXiFeVf,AutoClsSegFeV);
rti(UaryXFeVt< unots<Flt,Bln> >) tcln(UnotsXfFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unots<Flt,Int> >) tcln(UnotsXfFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unots<Flt,Flt> >) tcln(UnotsXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< unnots<Bln,Bln> >) tcln(UnnotsXbFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unnots<Bln,Int> >) tcln(UnnotsXbFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unnots<Bln,Flt> >) tcln(UnnotsXbFeVf,AutoClsSegFeV);
rti(UaryXFeVt< unnots<Int,Bln> >) tcln(UnnotsXiFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unnots<Int,Int> >) tcln(UnnotsXiFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unnots<Int,Flt> >) tcln(UnnotsXiFeVf,AutoClsSegFeV);
rti(UaryXFeVt< unnots<Flt,Bln> >) tcln(UnnotsXfFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unnots<Flt,Int> >) tcln(UnnotsXfFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unnots<Flt,Flt> >) tcln(UnnotsXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< unotu<Bln,Bln> >) tcln(UnotuXbFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unotu<Bln,Int> >) tcln(UnotuXbFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unotu<Bln,Flt> >) tcln(UnotuXbFeVf,AutoClsSegFeV);
rti(UaryXFeVt< unotu<Int,Bln> >) tcln(UnotuXiFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unotu<Int,Int> >) tcln(UnotuXiFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unotu<Int,Flt> >) tcln(UnotuXiFeVf,AutoClsSegFeV);
rti(UaryXFeVt< unotu<Flt,Bln> >) tcln(UnotuXfFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unotu<Flt,Int> >) tcln(UnotuXfFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unotu<Flt,Flt> >) tcln(UnotuXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< unnotu<Bln,Bln> >) tcln(UnnotuXbFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unnotu<Bln,Int> >) tcln(UnnotuXbFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unnotu<Bln,Flt> >) tcln(UnnotuXbFeVf,AutoClsSegFeV);
rti(UaryXFeVt< unnotu<Int,Bln> >) tcln(UnnotuXiFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unnotu<Int,Int> >) tcln(UnnotuXiFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unnotu<Int,Flt> >) tcln(UnnotuXiFeVf,AutoClsSegFeV);
rti(UaryXFeVt< unnotu<Flt,Bln> >) tcln(UnnotuXfFeVb,AutoClsSegFeV);
rti(UaryXFeVt< unnotu<Flt,Int> >) tcln(UnnotuXfFeVi,AutoClsSegFeV);
rti(UaryXFeVt< unnotu<Flt,Flt> >) tcln(UnnotuXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< uneg<Int,Int> >) tcln(UnegXiFeVi,AutoClsSegFeV);
rti(UaryXFeVt< uneg<Flt,Flt> >) tcln(UnegXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< uabs<Int,Int> >) tcln(UabsXiFeVi,AutoClsSegFeV);
rti(UaryXFeVt< uabs<Flt,Flt> >) tcln(UabsXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< usin<Flt,Flt> >) tcln(UsinXfFeVf,AutoClsSegFeV);
rti(UaryXFeVt< ucos<Flt,Flt> >) tcln(UcosXfFeVf,AutoClsSegFeV);
rti(UaryXFeVt< utan<Flt,Flt> >) tcln(UtanXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< uasin<Flt,Flt> >) tcln(UasinXfFeVf,AutoClsSegFeV);
rti(UaryXFeVt< uacos<Flt,Flt> >) tcln(UacosXfFeVf,AutoClsSegFeV);
rti(UaryXFeVt< uatan<Flt,Flt> >) tcln(UatanXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< usinh<Flt,Flt> >) tcln(UsinhXfFeVf,AutoClsSegFeV);
rti(UaryXFeVt< ucosh<Flt,Flt> >) tcln(UcoshXfFeVf,AutoClsSegFeV);
rti(UaryXFeVt< utanh<Flt,Flt> >) tcln(UtanhXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< uasinh<Flt,Flt> >) tcln(UasinhXfFeVf,AutoClsSegFeV);
rti(UaryXFeVt< uacosh<Flt,Flt> >) tcln(UacoshXfFeVf,AutoClsSegFeV);
rti(UaryXFeVt< uatanh<Flt,Flt> >) tcln(UatanhXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< uexp<Flt,Flt> >) tcln(UexpXfFeVf,AutoClsSegFeV);
rti(UaryXFeVt< ulog<Flt,Flt> >) tcln(UlogXfFeVf,AutoClsSegFeV);
rti(UaryXFeVt< ulog2<Flt,Flt> >) tcln(Ulog2XfFeVf,AutoClsSegFeV);
rti(UaryXFeVt< ulog10<Flt,Flt> >) tcln(Ulog10XfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< usqr<Int,Int> >) tcln(UsqrXiFeVi,AutoClsSegFeV);
rti(UaryXFeVt< usqr<Int,Flt> >) tcln(UsqrXiFeVf,AutoClsSegFeV);
rti(UaryXFeVt< usqr<Flt,Flt> >) tcln(UsqrXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< usqrt<Int,Int> >) tcln(UsqrtXiFeVi,AutoClsSegFeV);
rti(UaryXFeVt< usqrt<Flt,Int> >) tcln(UsqrtXfFeVi,AutoClsSegFeV);
rti(UaryXFeVt< usqrt<Int,Flt> >) tcln(UsqrtXiFeVf,AutoClsSegFeV);
rti(UaryXFeVt< usqrt<Flt,Flt> >) tcln(UsqrtXfFeVf,AutoClsSegFeV);

rti(UaryXFeVt< ucube<Int,Int> >) tcln(UcubeXiFeVi,AutoClsSegFeV);
rti(UaryXFeVt< ucube<Int,Flt> >) tcln(UcubeXiFeVf,AutoClsSegFeV);
rti(UaryXFeVt< ucube<Flt,Flt> >) tcln(UcubeXfFeVf,AutoClsSegFeV);

closeKangarooSpace



#include "cbls/funcs/fevs/segfevs/baryxfevt.tcc"

openKangarooSpace
rti(BaryXFeVt< bands<Bln,Bln> >) 	tcln(BandsXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bands<Bln,Int> >) 	tcln(BandsXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bands<Bln,Flt> >) 	tcln(BandsXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bands<Int,Bln> >) 	tcln(BandsXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bands<Int,Int> >) 	tcln(BandsXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bands<Int,Flt> >) 	tcln(BandsXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bands<Flt,Bln> >) 	tcln(BandsXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bands<Flt,Int> >) 	tcln(BandsXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bands<Flt,Flt> >) 	tcln(BandsXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnands<Bln,Bln> >) 	tcln(BnandsXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnands<Bln,Int> >) 	tcln(BnandsXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnands<Bln,Flt> >) 	tcln(BnandsXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnands<Int,Bln> >) 	tcln(BnandsXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnands<Int,Int> >) 	tcln(BnandsXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnands<Int,Flt> >) 	tcln(BnandsXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnands<Flt,Bln> >) 	tcln(BnandsXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnands<Flt,Int> >) 	tcln(BnandsXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnands<Flt,Flt> >) 	tcln(BnandsXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bors<Bln,Bln> >) 	tcln(BorsXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bors<Bln,Int> >) 	tcln(BorsXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bors<Bln,Flt> >) 	tcln(BorsXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bors<Int,Bln> >) 	tcln(BorsXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bors<Int,Int> >) 	tcln(BorsXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bors<Int,Flt> >) 	tcln(BorsXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bors<Flt,Bln> >) 	tcln(BorsXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bors<Flt,Int> >) 	tcln(BorsXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bors<Flt,Flt> >) 	tcln(BorsXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnors<Bln,Bln> >) 	tcln(BnorsXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnors<Bln,Int> >) 	tcln(BnorsXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnors<Bln,Flt> >) 	tcln(BnorsXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnors<Int,Bln> >) 	tcln(BnorsXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnors<Int,Int> >) 	tcln(BnorsXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnors<Int,Flt> >) 	tcln(BnorsXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnors<Flt,Bln> >) 	tcln(BnorsXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnors<Flt,Int> >) 	tcln(BnorsXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnors<Flt,Flt> >) 	tcln(BnorsXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bxors<Bln,Bln> >) 	tcln(BxorsXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxors<Bln,Int> >) 	tcln(BxorsXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxors<Bln,Flt> >) 	tcln(BxorsXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bxors<Int,Bln> >) 	tcln(BxorsXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxors<Int,Int> >) 	tcln(BxorsXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxors<Int,Flt> >) 	tcln(BxorsXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bxors<Flt,Bln> >) 	tcln(BxorsXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxors<Flt,Int> >) 	tcln(BxorsXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxors<Flt,Flt> >) 	tcln(BxorsXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bxnors<Bln,Bln> >) 	tcln(BxnorsXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxnors<Bln,Int> >) 	tcln(BxnorsXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxnors<Bln,Flt> >) 	tcln(BxnorsXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bxnors<Int,Bln> >) 	tcln(BxnorsXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxnors<Int,Int> >) 	tcln(BxnorsXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxnors<Int,Flt> >) 	tcln(BxnorsXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bxnors<Flt,Bln> >) 	tcln(BxnorsXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxnors<Flt,Int> >) 	tcln(BxnorsXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxnors<Flt,Flt> >) 	tcln(BxnorsXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bimplys<Bln,Bln> >) 	tcln(BimplysXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bimplys<Bln,Int> >) 	tcln(BimplysXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bimplys<Bln,Flt> >) 	tcln(BimplysXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bimplys<Int,Bln> >) 	tcln(BimplysXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bimplys<Int,Int> >) 	tcln(BimplysXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bimplys<Int,Flt> >) 	tcln(BimplysXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bimplys<Flt,Bln> >) 	tcln(BimplysXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bimplys<Flt,Int> >) 	tcln(BimplysXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bimplys<Flt,Flt> >) 	tcln(BimplysXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnimplys<Bln,Bln> >) tcln(BnimplysXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnimplys<Bln,Int> >) tcln(BnimplysXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnimplys<Bln,Flt> >) tcln(BnimplysXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnimplys<Int,Bln> >) tcln(BnimplysXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnimplys<Int,Int> >) tcln(BnimplysXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnimplys<Int,Flt> >) tcln(BnimplysXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnimplys<Flt,Bln> >) tcln(BnimplysXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnimplys<Flt,Int> >) tcln(BnimplysXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnimplys<Flt,Flt> >) tcln(BnimplysXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bandu<Bln,Bln> >) 	tcln(BanduXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bandu<Bln,Int> >) 	tcln(BanduXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bandu<Bln,Flt> >) 	tcln(BanduXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bandu<Int,Bln> >) 	tcln(BanduXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bandu<Int,Int> >) 	tcln(BanduXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bandu<Int,Flt> >) 	tcln(BanduXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bandu<Flt,Bln> >) 	tcln(BanduXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bandu<Flt,Int> >) 	tcln(BanduXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bandu<Flt,Flt> >) 	tcln(BanduXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnandu<Bln,Bln> >) 	tcln(BnanduXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnandu<Bln,Int> >) 	tcln(BnanduXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnandu<Bln,Flt> >) 	tcln(BnanduXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnandu<Int,Bln> >) 	tcln(BnanduXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnandu<Int,Int> >) 	tcln(BnanduXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnandu<Int,Flt> >) 	tcln(BnanduXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnandu<Flt,Bln> >) 	tcln(BnanduXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnandu<Flt,Int> >) 	tcln(BnanduXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnandu<Flt,Flt> >) 	tcln(BnanduXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< boru<Bln,Bln> >) 	tcln(BoruXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< boru<Bln,Int> >) 	tcln(BoruXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< boru<Bln,Flt> >) 	tcln(BoruXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< boru<Int,Bln> >) 	tcln(BoruXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< boru<Int,Int> >) 	tcln(BoruXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< boru<Int,Flt> >) 	tcln(BoruXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< boru<Flt,Bln> >) 	tcln(BoruXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< boru<Flt,Int> >) 	tcln(BoruXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< boru<Flt,Flt> >) 	tcln(BoruXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnoru<Bln,Bln> >) 	tcln(BnoruXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnoru<Bln,Int> >) 	tcln(BnoruXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnoru<Bln,Flt> >) 	tcln(BnoruXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnoru<Int,Bln> >) 	tcln(BnoruXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnoru<Int,Int> >) 	tcln(BnoruXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnoru<Int,Flt> >) 	tcln(BnoruXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnoru<Flt,Bln> >) 	tcln(BnoruXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnoru<Flt,Int> >) 	tcln(BnoruXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnoru<Flt,Flt> >) 	tcln(BnoruXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bxoru<Bln,Bln> >) 	tcln(BxoruXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxoru<Bln,Int> >) 	tcln(BxoruXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxoru<Bln,Flt> >) 	tcln(BxoruXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bxoru<Int,Bln> >) 	tcln(BxoruXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxoru<Int,Int> >) 	tcln(BxoruXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxoru<Int,Flt> >) 	tcln(BxoruXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bxoru<Flt,Bln> >) 	tcln(BxoruXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxoru<Flt,Int> >) 	tcln(BxoruXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxoru<Flt,Flt> >) 	tcln(BxoruXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bxnoru<Bln,Bln> >) 	tcln(BxnoruXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxnoru<Bln,Int> >) 	tcln(BxnoruXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxnoru<Bln,Flt> >) 	tcln(BxnoruXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bxnoru<Int,Bln> >) 	tcln(BxnoruXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxnoru<Int,Int> >) 	tcln(BxnoruXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxnoru<Int,Flt> >) 	tcln(BxnoruXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bxnoru<Flt,Bln> >) 	tcln(BxnoruXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bxnoru<Flt,Int> >) 	tcln(BxnoruXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bxnoru<Flt,Flt> >) 	tcln(BxnoruXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bimplyu<Bln,Bln> >) 	tcln(BimplyuXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bimplyu<Bln,Int> >) 	tcln(BimplyuXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bimplyu<Bln,Flt> >) 	tcln(BimplyuXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bimplyu<Int,Bln> >) 	tcln(BimplyuXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bimplyu<Int,Int> >) 	tcln(BimplyuXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bimplyu<Int,Flt> >) 	tcln(BimplyuXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bimplyu<Flt,Bln> >) 	tcln(BimplyuXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bimplyu<Flt,Int> >) 	tcln(BimplyuXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bimplyu<Flt,Flt> >) 	tcln(BimplyuXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnimplyu<Bln,Bln> >) tcln(BnimplyuXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnimplyu<Bln,Int> >) tcln(BnimplyuXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnimplyu<Bln,Flt> >) tcln(BnimplyuXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnimplyu<Int,Bln> >) tcln(BnimplyuXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnimplyu<Int,Int> >) tcln(BnimplyuXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnimplyu<Int,Flt> >) tcln(BnimplyuXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnimplyu<Flt,Bln> >) tcln(BnimplyuXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnimplyu<Flt,Int> >) tcln(BnimplyuXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnimplyu<Flt,Flt> >) tcln(BnimplyuXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< beqs<Bln,Bln> >) tcln(BeqsXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< beqs<Bln,Int> >) tcln(BeqsXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< beqs<Bln,Flt> >) tcln(BeqsXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< beqs<Int,Bln> >) tcln(BeqsXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< beqs<Int,Int> >) tcln(BeqsXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< beqs<Int,Flt> >) tcln(BeqsXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< beqs<Flt,Bln> >) tcln(BeqsXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< beqs<Flt,Int> >) tcln(BeqsXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< beqs<Flt,Flt> >) tcln(BeqsXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnes<Bln,Bln> >) tcln(BnesXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnes<Bln,Int> >) tcln(BnesXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnes<Bln,Flt> >) tcln(BnesXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnes<Int,Bln> >) tcln(BnesXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnes<Int,Int> >) tcln(BnesXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnes<Int,Flt> >) tcln(BnesXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnes<Flt,Bln> >) tcln(BnesXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnes<Flt,Int> >) tcln(BnesXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnes<Flt,Flt> >) tcln(BnesXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< blts<Bln,Bln> >) tcln(BltsXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< blts<Bln,Int> >) tcln(BltsXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< blts<Bln,Flt> >) tcln(BltsXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< blts<Int,Bln> >) tcln(BltsXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< blts<Int,Int> >) tcln(BltsXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< blts<Int,Flt> >) tcln(BltsXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< blts<Flt,Bln> >) tcln(BltsXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< blts<Flt,Int> >) tcln(BltsXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< blts<Flt,Flt> >) tcln(BltsXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnlts<Bln,Bln> >) tcln(BnltsXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnlts<Bln,Int> >) tcln(BnltsXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnlts<Bln,Flt> >) tcln(BnltsXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnlts<Int,Bln> >) tcln(BnltsXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnlts<Int,Int> >) tcln(BnltsXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnlts<Int,Flt> >) tcln(BnltsXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnlts<Flt,Bln> >) tcln(BnltsXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnlts<Flt,Int> >) tcln(BnltsXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnlts<Flt,Flt> >) tcln(BnltsXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bgts<Bln,Bln> >) tcln(BgtsXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bgts<Bln,Int> >) tcln(BgtsXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bgts<Bln,Flt> >) tcln(BgtsXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bgts<Int,Bln> >) tcln(BgtsXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bgts<Int,Int> >) tcln(BgtsXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bgts<Int,Flt> >) tcln(BgtsXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bgts<Flt,Bln> >) tcln(BgtsXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bgts<Flt,Int> >) tcln(BgtsXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bgts<Flt,Flt> >) tcln(BgtsXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bngts<Bln,Bln> >) tcln(BngtsXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bngts<Bln,Int> >) tcln(BngtsXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bngts<Bln,Flt> >) tcln(BngtsXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bngts<Int,Bln> >) tcln(BngtsXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bngts<Int,Int> >) tcln(BngtsXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bngts<Int,Flt> >) tcln(BngtsXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bngts<Flt,Bln> >) tcln(BngtsXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bngts<Flt,Int> >) tcln(BngtsXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bngts<Flt,Flt> >) tcln(BngtsXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bles<Int,Bln> >) tcln(BlesXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bles<Int,Int> >) tcln(BlesXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bles<Int,Flt> >) tcln(BlesXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bles<Flt,Bln> >) tcln(BlesXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bles<Flt,Int> >) tcln(BlesXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bles<Flt,Flt> >) tcln(BlesXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnles<Int,Bln> >) tcln(BnlesXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnles<Int,Int> >) tcln(BnlesXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnles<Int,Flt> >) tcln(BnlesXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnles<Flt,Bln> >) tcln(BnlesXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnles<Flt,Int> >) tcln(BnlesXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnles<Flt,Flt> >) tcln(BnlesXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bges<Int,Bln> >) tcln(BgesXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bges<Int,Int> >) tcln(BgesXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bges<Int,Flt> >) tcln(BgesXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bges<Flt,Bln> >) tcln(BgesXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bges<Flt,Int> >) tcln(BgesXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bges<Flt,Flt> >) tcln(BgesXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnges<Int,Bln> >) tcln(BngesXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnges<Int,Int> >) tcln(BngesXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnges<Int,Flt> >) tcln(BngesXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnges<Flt,Bln> >) tcln(BngesXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnges<Flt,Int> >) tcln(BngesXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnges<Flt,Flt> >) tcln(BngesXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bequ<Bln,Bln> >) tcln(BequXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bequ<Bln,Int> >) tcln(BequXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bequ<Bln,Flt> >) tcln(BequXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bequ<Int,Bln> >) tcln(BequXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bequ<Int,Int> >) tcln(BequXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bequ<Int,Flt> >) tcln(BequXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bequ<Flt,Bln> >) tcln(BequXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bequ<Flt,Int> >) tcln(BequXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bequ<Flt,Flt> >) tcln(BequXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bneu<Bln,Bln> >) tcln(BneuXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bneu<Bln,Int> >) tcln(BneuXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bneu<Bln,Flt> >) tcln(BneuXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bneu<Int,Bln> >) tcln(BneuXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bneu<Int,Int> >) tcln(BneuXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bneu<Int,Flt> >) tcln(BneuXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bneu<Flt,Bln> >) tcln(BneuXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bneu<Flt,Int> >) tcln(BneuXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bneu<Flt,Flt> >) tcln(BneuXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bltu<Bln,Bln> >) tcln(BltuXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bltu<Bln,Int> >) tcln(BltuXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bltu<Bln,Flt> >) tcln(BltuXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bltu<Int,Bln> >) tcln(BltuXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bltu<Int,Int> >) tcln(BltuXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bltu<Int,Flt> >) tcln(BltuXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bltu<Flt,Bln> >) tcln(BltuXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bltu<Flt,Int> >) tcln(BltuXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bltu<Flt,Flt> >) tcln(BltuXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnltu<Bln,Bln> >) tcln(BnltuXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnltu<Bln,Int> >) tcln(BnltuXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnltu<Bln,Flt> >) tcln(BnltuXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnltu<Int,Bln> >) tcln(BnltuXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnltu<Int,Int> >) tcln(BnltuXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnltu<Int,Flt> >) tcln(BnltuXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnltu<Flt,Bln> >) tcln(BnltuXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnltu<Flt,Int> >) tcln(BnltuXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnltu<Flt,Flt> >) tcln(BnltuXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bgtu<Bln,Bln> >) tcln(BgtuXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bgtu<Bln,Int> >) tcln(BgtuXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bgtu<Bln,Flt> >) tcln(BgtuXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bgtu<Int,Bln> >) tcln(BgtuXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bgtu<Int,Int> >) tcln(BgtuXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bgtu<Int,Flt> >) tcln(BgtuXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bgtu<Flt,Bln> >) tcln(BgtuXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bgtu<Flt,Int> >) tcln(BgtuXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bgtu<Flt,Flt> >) tcln(BgtuXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bngtu<Bln,Bln> >) tcln(BngtuXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bngtu<Bln,Int> >) tcln(BngtuXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bngtu<Bln,Flt> >) tcln(BngtuXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bngtu<Int,Bln> >) tcln(BngtuXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bngtu<Int,Int> >) tcln(BngtuXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bngtu<Int,Flt> >) tcln(BngtuXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bngtu<Flt,Bln> >) tcln(BngtuXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bngtu<Flt,Int> >) tcln(BngtuXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bngtu<Flt,Flt> >) tcln(BngtuXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bleu<Int,Bln> >) tcln(BleuXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bleu<Int,Int> >) tcln(BleuXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bleu<Int,Flt> >) tcln(BleuXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bleu<Flt,Bln> >) tcln(BleuXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bleu<Flt,Int> >) tcln(BleuXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bleu<Flt,Flt> >) tcln(BleuXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bnleu<Int,Bln> >) tcln(BnleuXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnleu<Int,Int> >) tcln(BnleuXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnleu<Int,Flt> >) tcln(BnleuXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bnleu<Flt,Bln> >) tcln(BnleuXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bnleu<Flt,Int> >) tcln(BnleuXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bnleu<Flt,Flt> >) tcln(BnleuXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bgeu<Int,Bln> >) tcln(BgeuXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bgeu<Int,Int> >) tcln(BgeuXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bgeu<Int,Flt> >) tcln(BgeuXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bgeu<Flt,Bln> >) tcln(BgeuXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bgeu<Flt,Int> >) tcln(BgeuXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bgeu<Flt,Flt> >) tcln(BgeuXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bngeu<Int,Bln> >) tcln(BngeuXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bngeu<Int,Int> >) tcln(BngeuXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bngeu<Int,Flt> >) tcln(BngeuXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bngeu<Flt,Bln> >) tcln(BngeuXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bngeu<Flt,Int> >) tcln(BngeuXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bngeu<Flt,Flt> >) tcln(BngeuXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< badd<Bln,Bln> >)  tcln(BaddXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< badd<Bln,Int> >)  tcln(BaddXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< badd<Bln,Flt> >)  tcln(BaddXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< badd<Int,Bln> >)  tcln(BaddXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< badd<Int,Int> >)  tcln(BaddXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< badd<Int,Flt> >)  tcln(BaddXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< badd<Flt,Bln> >)  tcln(BaddXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< badd<Flt,Int> >)  tcln(BaddXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< badd<Flt,Flt> >)  tcln(BaddXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bmult<Bln,Bln> >)  tcln(BmultXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bmult<Bln,Int> >)  tcln(BmultXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bmult<Bln,Flt> >)  tcln(BmultXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bmult<Int,Bln> >)  tcln(BmultXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bmult<Int,Int> >)  tcln(BmultXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bmult<Int,Flt> >)  tcln(BmultXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bmult<Flt,Bln> >)  tcln(BmultXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bmult<Flt,Int> >)  tcln(BmultXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bmult<Flt,Flt> >)  tcln(BmultXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bdiff<Bln,Bln> >)  tcln(BdiffXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bdiff<Bln,Int> >)  tcln(BdiffXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bdiff<Bln,Flt> >)  tcln(BdiffXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bdiff<Int,Bln> >)  tcln(BdiffXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bdiff<Int,Int> >)  tcln(BdiffXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bdiff<Int,Flt> >)  tcln(BdiffXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bdiff<Flt,Bln> >)  tcln(BdiffXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bdiff<Flt,Int> >)  tcln(BdiffXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bdiff<Flt,Flt> >)  tcln(BdiffXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bmax<Bln,Bln> >)  tcln(BmaxXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bmax<Bln,Int> >)  tcln(BmaxXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bmax<Bln,Flt> >)  tcln(BmaxXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bmax<Int,Bln> >)  tcln(BmaxXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bmax<Int,Int> >)  tcln(BmaxXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bmax<Int,Flt> >)  tcln(BmaxXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bmax<Flt,Bln> >)  tcln(BmaxXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bmax<Flt,Int> >)  tcln(BmaxXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bmax<Flt,Flt> >)  tcln(BmaxXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bmin<Bln,Bln> >)  tcln(BminXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bmin<Bln,Int> >)  tcln(BminXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bmin<Bln,Flt> >)  tcln(BminXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bmin<Int,Bln> >)  tcln(BminXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bmin<Int,Int> >)  tcln(BminXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bmin<Int,Flt> >)  tcln(BminXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bmin<Flt,Bln> >)  tcln(BminXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bmin<Flt,Int> >)  tcln(BminXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bmin<Flt,Flt> >)  tcln(BminXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bsub<Bln,Bln> >)  tcln(BsubXbFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bsub<Bln,Int> >)  tcln(BsubXbFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bsub<Bln,Flt> >)  tcln(BsubXbFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bsub<Int,Bln> >)  tcln(BsubXiFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bsub<Int,Int> >)  tcln(BsubXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bsub<Int,Flt> >)  tcln(BsubXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bsub<Flt,Bln> >)  tcln(BsubXfFeVb,AutoClsSegFeV);
rti(BaryXFeVt< bsub<Flt,Int> >)  tcln(BsubXfFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bsub<Flt,Flt> >)  tcln(BsubXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bdiv<Int,Int> >)  tcln(BdivXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bdiv<Int,Flt> >)  tcln(BdivXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bdiv<Flt,Flt> >)  tcln(BdivXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bmod<Int,Int> >)  tcln(BmodXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bmod<Int,Flt> >)  tcln(BmodXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bmod<Flt,Flt> >)  tcln(BmodXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< bpow<Int,Int> >)  tcln(BpowXiFeVi,AutoClsSegFeV);
rti(BaryXFeVt< bpow<Int,Flt> >)  tcln(BpowXiFeVf,AutoClsSegFeV);
rti(BaryXFeVt< bpow<Flt,Flt> >)  tcln(BpowXfFeVf,AutoClsSegFeV);

rti(BaryXFeVt< ipack2<Int,Int> >) tcln(BpackXiFeVi, AutoClsSegFeV);

closeKangarooSpace


#include "cbls/funcs/fevs/segfevs/baryxyfevt.tcc"
openKangarooSpace
rti(BaryXYFeVt< bhadd<Bln,Int,Bln> >)  tcln(BhaddXbYiFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Bln,Int,Int> >)  tcln(BhaddXbYiFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Bln,Int,Flt> >)  tcln(BhaddXbYiFeVf,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Bln,Flt,Bln> >)  tcln(BhaddXbYfFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Bln,Flt,Int> >)  tcln(BhaddXbYfFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Bln,Flt,Flt> >)  tcln(BhaddXbYfFeVf,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Int,Bln,Bln> >)  tcln(BhaddXiYbFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Int,Bln,Int> >)  tcln(BhaddXiYbFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Int,Bln,Flt> >)  tcln(BhaddXiYbFeVf,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Int,Flt,Bln> >)  tcln(BhaddXiYfFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Int,Flt,Int> >)  tcln(BhaddXiYfFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Int,Flt,Flt> >)  tcln(BhaddXiYfFeVf,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Flt,Bln,Bln> >)  tcln(BhaddXfYbFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Flt,Bln,Int> >)  tcln(BhaddXfYbFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Flt,Bln,Flt> >)  tcln(BhaddXfYbFeVf,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Flt,Int,Bln> >)  tcln(BhaddXfYiFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Flt,Int,Int> >)  tcln(BhaddXfYiFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhadd<Flt,Int,Flt> >)  tcln(BhaddXfYiFeVf,AutoClsSegFeV);

rti(BaryXYFeVt< bhmult<Bln,Int,Bln> >)  tcln(BhmultXbYiFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Bln,Int,Int> >)  tcln(BhmultXbYiFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Bln,Int,Flt> >)  tcln(BhmultXbYiFeVf,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Bln,Flt,Bln> >)  tcln(BhmultXbYfFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Bln,Flt,Int> >)  tcln(BhmultXbYfFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Bln,Flt,Flt> >)  tcln(BhmultXbYfFeVf,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Int,Bln,Bln> >)  tcln(BhmultXiYbFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Int,Bln,Int> >)  tcln(BhmultXiYbFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Int,Bln,Flt> >)  tcln(BhmultXiYbFeVf,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Int,Flt,Bln> >)  tcln(BhmultXiYfFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Int,Flt,Int> >)  tcln(BhmultXiYfFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Int,Flt,Flt> >)  tcln(BhmultXiYfFeVf,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Flt,Bln,Bln> >)  tcln(BhmultXfYbFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Flt,Bln,Int> >)  tcln(BhmultXfYbFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Flt,Bln,Flt> >)  tcln(BhmultXfYbFeVf,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Flt,Int,Bln> >)  tcln(BhmultXfYiFeVb,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Flt,Int,Int> >)  tcln(BhmultXfYiFeVi,AutoClsSegFeV);
rti(BaryXYFeVt< bhmult<Flt,Int,Flt> >)  tcln(BhmultXfYiFeVf,AutoClsSegFeV);
closeKangarooSpace



#include "cbls/funcs/fevs/segfevs/taryxfevt.tcc"
openKangarooSpace
/* between closed closed satisfaction */
rti(TaryXFeVt< tbccs<Int,Bln> >) tcln(TbccsXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbccs<Int,Int> >) tcln(TbccsXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbccs<Int,Flt> >) tcln(TbccsXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tbccs<Flt,Bln> >) tcln(TbccsXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbccs<Flt,Int> >) tcln(TbccsXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbccs<Flt,Flt> >) tcln(TbccsXfFeVf,AutoClsSegFeV);

/* between open open satisfaction */
rti(TaryXFeVt< tboos<Int,Bln> >) tcln(TboosXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tboos<Int,Int> >) tcln(TboosXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tboos<Int,Flt> >) tcln(TboosXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tboos<Flt,Bln> >) tcln(TboosXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tboos<Flt,Int> >) tcln(TboosXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tboos<Flt,Flt> >) tcln(TboosXfFeVf,AutoClsSegFeV);

/* between closed open satisfaction */
rti(TaryXFeVt< tbcos<Int,Bln> >) tcln(TbcosXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbcos<Int,Int> >) tcln(TbcosXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbcos<Int,Flt> >) tcln(TbcosXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tbcos<Flt,Bln> >) tcln(TbcosXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbcos<Flt,Int> >) tcln(TbcosXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbcos<Flt,Flt> >) tcln(TbcosXfFeVf,AutoClsSegFeV);

/* between open closed satisfaction */
rti(TaryXFeVt< tbocs<Int,Bln> >) tcln(TbocsXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbocs<Int,Int> >) tcln(TbocsXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbocs<Int,Flt> >) tcln(TbocsXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tbocs<Flt,Bln> >) tcln(TbocsXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbocs<Flt,Int> >) tcln(TbocsXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbocs<Flt,Flt> >) tcln(TbocsXfFeVf,AutoClsSegFeV);

/* not between closed closed satisfaction */
rti(TaryXFeVt< tnbccs<Int,Bln> >) tcln(TnbccsXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbccs<Int,Int> >) tcln(TnbccsXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbccs<Int,Flt> >) tcln(TnbccsXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tnbccs<Flt,Bln> >) tcln(TnbccsXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbccs<Flt,Int> >) tcln(TnbccsXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbccs<Flt,Flt> >) tcln(TnbccsXfFeVf,AutoClsSegFeV);

/* not between open open satisfaction */
rti(TaryXFeVt< tnboos<Int,Bln> >) tcln(TnboosXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnboos<Int,Int> >) tcln(TnboosXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnboos<Int,Flt> >) tcln(TnboosXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tnboos<Flt,Bln> >) tcln(TnboosXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnboos<Flt,Int> >) tcln(TnboosXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnboos<Flt,Flt> >) tcln(TnboosXfFeVf,AutoClsSegFeV);

/* not between closed open satisfaction */
rti(TaryXFeVt< tnbcos<Int,Bln> >) tcln(TnbcosXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbcos<Int,Int> >) tcln(TnbcosXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbcos<Int,Flt> >) tcln(TnbcosXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tnbcos<Flt,Bln> >) tcln(TnbcosXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbcos<Flt,Int> >) tcln(TnbcosXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbcos<Flt,Flt> >) tcln(TnbcosXfFeVf,AutoClsSegFeV);

/* not between open closed satisfaction */
rti(TaryXFeVt< tnbocs<Int,Bln> >) tcln(TnbocsXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbocs<Int,Int> >) tcln(TnbocsXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbocs<Int,Flt> >) tcln(TnbocsXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tnbocs<Flt,Bln> >) tcln(TnbocsXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbocs<Flt,Int> >) tcln(TnbocsXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbocs<Flt,Flt> >) tcln(TnbocsXfFeVf,AutoClsSegFeV);

/* between closed closed unsatisfaction */
rti(TaryXFeVt< tbccu<Int,Bln> >) tcln(TbccuXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbccu<Int,Int> >) tcln(TbccuXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbccu<Int,Flt> >) tcln(TbccuXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tbccu<Flt,Bln> >) tcln(TbccuXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbccu<Flt,Int> >) tcln(TbccuXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbccu<Flt,Flt> >) tcln(TbccuXfFeVf,AutoClsSegFeV);

/* between open open unsatisfaction */
rti(TaryXFeVt< tboou<Int,Bln> >) tcln(TboouXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tboou<Int,Int> >) tcln(TboouXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tboou<Int,Flt> >) tcln(TboouXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tboou<Flt,Bln> >) tcln(TboouXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tboou<Flt,Int> >) tcln(TboouXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tboou<Flt,Flt> >) tcln(TboouXfFeVf,AutoClsSegFeV);

/* between closed open unsatisfaction */
rti(TaryXFeVt< tbcou<Int,Bln> >) tcln(TbcouXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbcou<Int,Int> >) tcln(TbcouXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbcou<Int,Flt> >) tcln(TbcouXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tbcou<Flt,Bln> >) tcln(TbcouXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbcou<Flt,Int> >) tcln(TbcouXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbcou<Flt,Flt> >) tcln(TbcouXfFeVf,AutoClsSegFeV);

/* between open closed unsatisfaction */
rti(TaryXFeVt< tbocu<Int,Bln> >) tcln(TbocuXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbocu<Int,Int> >) tcln(TbocuXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbocu<Int,Flt> >) tcln(TbocuXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tbocu<Flt,Bln> >) tcln(TbocuXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tbocu<Flt,Int> >) tcln(TbocuXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tbocu<Flt,Flt> >) tcln(TbocuXfFeVf,AutoClsSegFeV);

/* not between closed closed unsatisfaction */
rti(TaryXFeVt< tnbccu<Int,Bln> >) tcln(TnbccuXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbccu<Int,Int> >) tcln(TnbccuXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbccu<Int,Flt> >) tcln(TnbccuXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tnbccu<Flt,Bln> >) tcln(TnbccuXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbccu<Flt,Int> >) tcln(TnbccuXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbccu<Flt,Flt> >) tcln(TnbccuXfFeVf,AutoClsSegFeV);

/* not between open open unsatisfaction */
rti(TaryXFeVt< tnboou<Int,Bln> >) tcln(TnboouXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnboou<Int,Int> >) tcln(TnboouXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnboou<Int,Flt> >) tcln(TnboouXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tnboou<Flt,Bln> >) tcln(TnboouXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnboou<Flt,Int> >) tcln(TnboouXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnboou<Flt,Flt> >) tcln(TnboouXfFeVf,AutoClsSegFeV);

/* not between closed open unsatisfaction */
rti(TaryXFeVt< tnbcou<Int,Bln> >) tcln(TnbcouXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbcou<Int,Int> >) tcln(TnbcouXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbcou<Int,Flt> >) tcln(TnbcouXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tnbcou<Flt,Bln> >) tcln(TnbcouXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbcou<Flt,Int> >) tcln(TnbcouXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbcou<Flt,Flt> >) tcln(TnbcouXfFeVf,AutoClsSegFeV);

/* not between open closed unsatisfaction */
rti(TaryXFeVt< tnbocu<Int,Bln> >) tcln(TnbocuXiFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbocu<Int,Int> >) tcln(TnbocuXiFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbocu<Int,Flt> >) tcln(TnbocuXiFeVf,AutoClsSegFeV);
rti(TaryXFeVt< tnbocu<Flt,Bln> >) tcln(TnbocuXfFeVb,AutoClsSegFeV);
rti(TaryXFeVt< tnbocu<Flt,Int> >) tcln(TnbocuXfFeVi,AutoClsSegFeV);
rti(TaryXFeVt< tnbocu<Flt,Flt> >) tcln(TnbocuXfFeVf,AutoClsSegFeV);

rti(TaryXFeVt< ipack3<Int,Int> >) tcln(TpackXiFeVi, AutoClsSegFeV);

closeKangarooSpace

#include "cbls/funcs/fevs/segfevs/bindxfevt.tcc"
openKangarooSpace

rti(BindXFeVt< bind2r<beqs<Bln,Bln> > >) tcln(UeqsXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<beqs<Bln,Int> > >) tcln(UeqsXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<beqs<Bln,Flt> > >) tcln(UeqsXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<beqs<Int,Bln> > >) tcln(UeqsXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<beqs<Int,Int> > >) tcln(UeqsXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<beqs<Int,Flt> > >) tcln(UeqsXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<beqs<Flt,Bln> > >) tcln(UeqsXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<beqs<Flt,Int> > >) tcln(UeqsXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<beqs<Flt,Flt> > >) tcln(UeqsXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bnes<Bln,Bln> > >) tcln(UnesXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnes<Bln,Int> > >) tcln(UnesXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnes<Bln,Flt> > >) tcln(UnesXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnes<Int,Bln> > >) tcln(UnesXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnes<Int,Int> > >) tcln(UnesXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnes<Int,Flt> > >) tcln(UnesXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnes<Flt,Bln> > >) tcln(UnesXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnes<Flt,Int> > >) tcln(UnesXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnes<Flt,Flt> > >) tcln(UnesXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bgts<Bln,Bln> > >) tcln(UgtsXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgts<Bln,Int> > >) tcln(UgtsXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgts<Bln,Flt> > >) tcln(UgtsXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgts<Int,Bln> > >) tcln(UgtsXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgts<Int,Int> > >) tcln(UgtsXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgts<Int,Flt> > >) tcln(UgtsXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgts<Flt,Bln> > >) tcln(UgtsXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgts<Flt,Int> > >) tcln(UgtsXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgts<Flt,Flt> > >) tcln(UgtsXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bngts<Bln,Bln> > >) tcln(UngtsXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngts<Bln,Int> > >) tcln(UngtsXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngts<Bln,Flt> > >) tcln(UngtsXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngts<Int,Bln> > >) tcln(UngtsXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngts<Int,Int> > >) tcln(UngtsXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngts<Int,Flt> > >) tcln(UngtsXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngts<Flt,Bln> > >) tcln(UngtsXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngts<Flt,Int> > >) tcln(UngtsXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngts<Flt,Flt> > >) tcln(UngtsXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<blts<Bln,Bln> > >) tcln(UltsXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<blts<Bln,Int> > >) tcln(UltsXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<blts<Bln,Flt> > >) tcln(UltsXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<blts<Int,Bln> > >) tcln(UltsXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<blts<Int,Int> > >) tcln(UltsXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<blts<Int,Flt> > >) tcln(UltsXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<blts<Flt,Bln> > >) tcln(UltsXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<blts<Flt,Int> > >) tcln(UltsXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<blts<Flt,Flt> > >) tcln(UltsXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bnlts<Bln,Bln> > >) tcln(UnltsXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnlts<Bln,Int> > >) tcln(UnltsXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnlts<Bln,Flt> > >) tcln(UnltsXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnlts<Int,Bln> > >) tcln(UnltsXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnlts<Int,Int> > >) tcln(UnltsXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnlts<Int,Flt> > >) tcln(UnltsXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnlts<Flt,Bln> > >) tcln(UnltsXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnlts<Flt,Int> > >) tcln(UnltsXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnlts<Flt,Flt> > >) tcln(UnltsXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bges<Int,Bln> > >) tcln(UgesXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bges<Int,Int> > >) tcln(UgesXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bges<Int,Flt> > >) tcln(UgesXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bges<Flt,Bln> > >) tcln(UgesXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bges<Flt,Int> > >) tcln(UgesXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bges<Flt,Flt> > >) tcln(UgesXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bnges<Int,Bln> > >) tcln(UngesXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnges<Int,Int> > >) tcln(UngesXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnges<Int,Flt> > >) tcln(UngesXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnges<Flt,Bln> > >) tcln(UngesXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnges<Flt,Int> > >) tcln(UngesXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnges<Flt,Flt> > >) tcln(UngesXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bles<Int,Bln> > >) tcln(UlesXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bles<Int,Int> > >) tcln(UlesXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bles<Int,Flt> > >) tcln(UlesXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bles<Flt,Bln> > >) tcln(UlesXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bles<Flt,Int> > >) tcln(UlesXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bles<Flt,Flt> > >) tcln(UlesXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bnles<Int,Bln> > >) tcln(UnlesXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnles<Int,Int> > >) tcln(UnlesXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnles<Int,Flt> > >) tcln(UnlesXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnles<Flt,Bln> > >) tcln(UnlesXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnles<Flt,Int> > >) tcln(UnlesXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnles<Flt,Flt> > >) tcln(UnlesXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bequ<Bln,Bln> > >) tcln(UequXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bequ<Bln,Int> > >) tcln(UequXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bequ<Bln,Flt> > >) tcln(UequXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bequ<Int,Bln> > >) tcln(UequXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bequ<Int,Int> > >) tcln(UequXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bequ<Int,Flt> > >) tcln(UequXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bequ<Flt,Bln> > >) tcln(UequXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bequ<Flt,Int> > >) tcln(UequXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bequ<Flt,Flt> > >) tcln(UequXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bneu<Bln,Bln> > >) tcln(UneuXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bneu<Bln,Int> > >) tcln(UneuXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bneu<Bln,Flt> > >) tcln(UneuXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bneu<Int,Bln> > >) tcln(UneuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bneu<Int,Int> > >) tcln(UneuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bneu<Int,Flt> > >) tcln(UneuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bneu<Flt,Bln> > >) tcln(UneuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bneu<Flt,Int> > >) tcln(UneuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bneu<Flt,Flt> > >) tcln(UneuXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bgtu<Bln,Bln> > >) tcln(UgtuXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgtu<Bln,Int> > >) tcln(UgtuXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgtu<Bln,Flt> > >) tcln(UgtuXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgtu<Int,Bln> > >) tcln(UgtuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgtu<Int,Int> > >) tcln(UgtuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgtu<Int,Flt> > >) tcln(UgtuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgtu<Flt,Bln> > >) tcln(UgtuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgtu<Flt,Int> > >) tcln(UgtuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgtu<Flt,Flt> > >) tcln(UgtuXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bngtu<Bln,Bln> > >) tcln(UngtuXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngtu<Bln,Int> > >) tcln(UngtuXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngtu<Bln,Flt> > >) tcln(UngtuXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngtu<Int,Bln> > >) tcln(UngtuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngtu<Int,Int> > >) tcln(UngtuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngtu<Int,Flt> > >) tcln(UngtuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngtu<Flt,Bln> > >) tcln(UngtuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngtu<Flt,Int> > >) tcln(UngtuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngtu<Flt,Flt> > >) tcln(UngtuXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bltu<Bln,Bln> > >) tcln(UltuXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bltu<Bln,Int> > >) tcln(UltuXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bltu<Bln,Flt> > >) tcln(UltuXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bltu<Int,Bln> > >) tcln(UltuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bltu<Int,Int> > >) tcln(UltuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bltu<Int,Flt> > >) tcln(UltuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bltu<Flt,Bln> > >) tcln(UltuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bltu<Flt,Int> > >) tcln(UltuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bltu<Flt,Flt> > >) tcln(UltuXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bnltu<Bln,Bln> > >) tcln(UnltuXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnltu<Bln,Int> > >) tcln(UnltuXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnltu<Bln,Flt> > >) tcln(UnltuXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnltu<Int,Bln> > >) tcln(UnltuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnltu<Int,Int> > >) tcln(UnltuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnltu<Int,Flt> > >) tcln(UnltuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnltu<Flt,Bln> > >) tcln(UnltuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnltu<Flt,Int> > >) tcln(UnltuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnltu<Flt,Flt> > >) tcln(UnltuXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bgeu<Int,Bln> > >) tcln(UgeuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgeu<Int,Int> > >) tcln(UgeuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgeu<Int,Flt> > >) tcln(UgeuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgeu<Flt,Bln> > >) tcln(UgeuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgeu<Flt,Int> > >) tcln(UgeuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bgeu<Flt,Flt> > >) tcln(UgeuXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bngeu<Int,Bln> > >) tcln(UngeuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngeu<Int,Int> > >) tcln(UngeuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngeu<Int,Flt> > >) tcln(UngeuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngeu<Flt,Bln> > >) tcln(UngeuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngeu<Flt,Int> > >) tcln(UngeuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bngeu<Flt,Flt> > >) tcln(UngeuXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bleu<Int,Bln> > >) tcln(UleuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bleu<Int,Int> > >) tcln(UleuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bleu<Int,Flt> > >) tcln(UleuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bleu<Flt,Bln> > >) tcln(UleuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bleu<Flt,Int> > >) tcln(UleuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bleu<Flt,Flt> > >) tcln(UleuXfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bind2r<bnleu<Int,Bln> > >) tcln(UnleuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnleu<Int,Int> > >) tcln(UnleuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnleu<Int,Flt> > >) tcln(UnleuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnleu<Flt,Bln> > >) tcln(UnleuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnleu<Flt,Int> > >) tcln(UnleuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bnleu<Flt,Flt> > >) tcln(UnleuXfFeVf,AutoClsSegFeV);

/* addition */
rti(BindXFeVt< bind2r<badd<Bln,Bln> > >) tcln(UaddXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<badd<Bln,Int> > >) tcln(UaddXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<badd<Bln,Flt> > >) tcln(UaddXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<badd<Int,Bln> > >) tcln(UaddXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<badd<Int,Int> > >) tcln(UaddXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<badd<Int,Flt> > >) tcln(UaddXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<badd<Flt,Bln> > >) tcln(UaddXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<badd<Flt,Int> > >) tcln(UaddXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<badd<Flt,Flt> > >) tcln(UaddXfFeVf,AutoClsSegFeV);

/* multiplication */
rti(BindXFeVt< bind2r<bmult<Bln,Bln> > >) tcln(UmultXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmult<Bln,Int> > >) tcln(UmultXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmult<Bln,Flt> > >) tcln(UmultXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmult<Int,Bln> > >) tcln(UmultXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmult<Int,Int> > >) tcln(UmultXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmult<Int,Flt> > >) tcln(UmultXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmult<Flt,Bln> > >) tcln(UmultXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmult<Flt,Int> > >) tcln(UmultXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmult<Flt,Flt> > >) tcln(UmultXfFeVf,AutoClsSegFeV);

/* difference = abs(x-y) */
rti(BindXFeVt< bind2r<bdiff<Bln,Bln> > >) tcln(UdiffXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bdiff<Bln,Int> > >) tcln(UdiffXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bdiff<Bln,Flt> > >) tcln(UdiffXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bdiff<Int,Bln> > >) tcln(UdiffXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bdiff<Int,Int> > >) tcln(UdiffXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bdiff<Int,Flt> > >) tcln(UdiffXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bdiff<Flt,Bln> > >) tcln(UdiffXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bdiff<Flt,Int> > >) tcln(UdiffXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bdiff<Flt,Flt> > >) tcln(UdiffXfFeVf,AutoClsSegFeV);

/* maximum */
rti(BindXFeVt< bind2r<bmax<Bln,Bln> > >) tcln(UmaxXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmax<Bln,Int> > >) tcln(UmaxXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmax<Bln,Flt> > >) tcln(UmaxXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmax<Int,Bln> > >) tcln(UmaxXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmax<Int,Int> > >) tcln(UmaxXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmax<Int,Flt> > >) tcln(UmaxXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmax<Flt,Bln> > >) tcln(UmaxXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmax<Flt,Int> > >) tcln(UmaxXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmax<Flt,Flt> > >) tcln(UmaxXfFeVf,AutoClsSegFeV);

/* minimum */
rti(BindXFeVt< bind2r<bmin<Bln,Bln> > >) tcln(UminXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmin<Bln,Int> > >) tcln(UminXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmin<Bln,Flt> > >) tcln(UminXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmin<Int,Bln> > >) tcln(UminXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmin<Int,Int> > >) tcln(UminXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmin<Int,Flt> > >) tcln(UminXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmin<Flt,Bln> > >) tcln(UminXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmin<Flt,Int> > >) tcln(UminXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmin<Flt,Flt> > >) tcln(UminXfFeVf,AutoClsSegFeV);

/* subtraction */
rti(BindXFeVt< bind2r<bsub<Bln,Bln> > >) tcln(UsubXbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bsub<Bln,Int> > >) tcln(UsubXbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bsub<Bln,Flt> > >) tcln(UsubXbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bsub<Int,Bln> > >) tcln(UsubXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bsub<Int,Int> > >) tcln(UsubXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bsub<Int,Flt> > >) tcln(UsubXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bsub<Flt,Bln> > >) tcln(UsubXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bsub<Flt,Int> > >) tcln(UsubXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bsub<Flt,Flt> > >) tcln(UsubXfFeVf,AutoClsSegFeV);

/* division */
rti(BindXFeVt< bind2r<bdiv<Int,Int> > >)  tcln(UdivXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bdiv<Flt,Flt> > >)  tcln(UdivXfFeVf,AutoClsSegFeV);

/* modulus */
rti(BindXFeVt< bind2r<bmod<Int,Int> > >)  tcln(UmodXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bmod<Flt,Flt> > >)  tcln(UmodXfFeVf,AutoClsSegFeV);

/* power */
rti(BindXFeVt< bind2r<bpow<Int,Int> > >)  tcln(UpowXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind2r<bpow<Flt,Flt> > >)  tcln(UpowXfFeVf,AutoClsSegFeV);

/* between closed closed satisfaction */
rti(BindXFeVt< bind3lr<tbccs<Int,Bln> > >) tcln(UbccsXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbccs<Int,Int> > >) tcln(UbccsXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbccs<Int,Flt> > >) tcln(UbccsXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbccs<Flt,Bln> > >) tcln(UbccsXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbccs<Flt,Int> > >) tcln(UbccsXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbccs<Flt,Flt> > >) tcln(UbccsXfFeVf,AutoClsSegFeV);

/* between open open satisfaction */
rti(BindXFeVt< bind3lr<tboos<Int,Bln> > >) tcln(UboosXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tboos<Int,Int> > >) tcln(UboosXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tboos<Int,Flt> > >) tcln(UboosXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tboos<Flt,Bln> > >) tcln(UboosXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tboos<Flt,Int> > >) tcln(UboosXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tboos<Flt,Flt> > >) tcln(UboosXfFeVf,AutoClsSegFeV);

/* between closed open satisfaction */
rti(BindXFeVt< bind3lr<tbcos<Int,Bln> > >) tcln(UbcosXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbcos<Int,Int> > >) tcln(UbcosXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbcos<Int,Flt> > >) tcln(UbcosXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbcos<Flt,Bln> > >) tcln(UbcosXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbcos<Flt,Int> > >) tcln(UbcosXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbcos<Flt,Flt> > >) tcln(UbcosXfFeVf,AutoClsSegFeV);

/* between open closed satisfaction */
rti(BindXFeVt< bind3lr<tbocs<Int,Bln> > >) tcln(UbocsXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbocs<Int,Int> > >) tcln(UbocsXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbocs<Int,Flt> > >) tcln(UbocsXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbocs<Flt,Bln> > >) tcln(UbocsXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbocs<Flt,Int> > >) tcln(UbocsXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbocs<Flt,Flt> > >) tcln(UbocsXfFeVf,AutoClsSegFeV);

/* not between closed closed satisfaction */
rti(BindXFeVt< bind3lr<tnbccs<Int,Bln> > >) tcln(UnbccsXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbccs<Int,Int> > >) tcln(UnbccsXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbccs<Int,Flt> > >) tcln(UnbccsXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbccs<Flt,Bln> > >) tcln(UnbccsXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbccs<Flt,Int> > >) tcln(UnbccsXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbccs<Flt,Flt> > >) tcln(UnbccsXfFeVf,AutoClsSegFeV);

/* not between open open satisfaction */
rti(BindXFeVt< bind3lr<tnboos<Int,Bln> > >) tcln(UnboosXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnboos<Int,Int> > >) tcln(UnboosXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnboos<Int,Flt> > >) tcln(UnboosXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnboos<Flt,Bln> > >) tcln(UnboosXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnboos<Flt,Int> > >) tcln(UnboosXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnboos<Flt,Flt> > >) tcln(UnboosXfFeVf,AutoClsSegFeV);

/* not between closed open satisfaction */
rti(BindXFeVt< bind3lr<tnbcos<Int,Bln> > >) tcln(UnbcosXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbcos<Int,Int> > >) tcln(UnbcosXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbcos<Int,Flt> > >) tcln(UnbcosXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbcos<Flt,Bln> > >) tcln(UnbcosXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbcos<Flt,Int> > >) tcln(UnbcosXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbcos<Flt,Flt> > >) tcln(UnbcosXfFeVf,AutoClsSegFeV);

/* not between open closed satisfaction */
rti(BindXFeVt< bind3lr<tnbocs<Int,Bln> > >) tcln(UnbocsXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbocs<Int,Int> > >) tcln(UnbocsXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbocs<Int,Flt> > >) tcln(UnbocsXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbocs<Flt,Bln> > >) tcln(UnbocsXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbocs<Flt,Int> > >) tcln(UnbocsXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbocs<Flt,Flt> > >) tcln(UnbocsXfFeVf,AutoClsSegFeV);

/* between closed closed unsatisfaction */
rti(BindXFeVt< bind3lr<tbccu<Int,Bln> > >) tcln(UbccuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbccu<Int,Int> > >) tcln(UbccuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbccu<Int,Flt> > >) tcln(UbccuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbccu<Flt,Bln> > >) tcln(UbccuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbccu<Flt,Int> > >) tcln(UbccuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbccu<Flt,Flt> > >) tcln(UbccuXfFeVf,AutoClsSegFeV);

/* between open open unsatisfaction */
rti(BindXFeVt< bind3lr<tboou<Int,Bln> > >) tcln(UboouXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tboou<Int,Int> > >) tcln(UboouXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tboou<Int,Flt> > >) tcln(UboouXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tboou<Flt,Bln> > >) tcln(UboouXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tboou<Flt,Int> > >) tcln(UboouXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tboou<Flt,Flt> > >) tcln(UboouXfFeVf,AutoClsSegFeV);

/* between closed open unsatisfaction */
rti(BindXFeVt< bind3lr<tbcou<Int,Bln> > >) tcln(UbcouXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbcou<Int,Int> > >) tcln(UbcouXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbcou<Int,Flt> > >) tcln(UbcouXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbcou<Flt,Bln> > >) tcln(UbcouXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbcou<Flt,Int> > >) tcln(UbcouXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbcou<Flt,Flt> > >) tcln(UbcouXfFeVf,AutoClsSegFeV);

/* between open closed unsatisfaction */
rti(BindXFeVt< bind3lr<tbocu<Int,Bln> > >) tcln(UbocuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbocu<Int,Int> > >) tcln(UbocuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbocu<Int,Flt> > >) tcln(UbocuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbocu<Flt,Bln> > >) tcln(UbocuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbocu<Flt,Int> > >) tcln(UbocuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tbocu<Flt,Flt> > >) tcln(UbocuXfFeVf,AutoClsSegFeV);

/* not between closed closed unsatisfaction */
rti(BindXFeVt< bind3lr<tnbccu<Int,Bln> > >) tcln(UnbccuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbccu<Int,Int> > >) tcln(UnbccuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbccu<Int,Flt> > >) tcln(UnbccuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbccu<Flt,Bln> > >) tcln(UnbccuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbccu<Flt,Int> > >) tcln(UnbccuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbccu<Flt,Flt> > >) tcln(UnbccuXfFeVf,AutoClsSegFeV);

/* not between open open unsatisfaction */
rti(BindXFeVt< bind3lr<tnboou<Int,Bln> > >) tcln(UnboouXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnboou<Int,Int> > >) tcln(UnboouXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnboou<Int,Flt> > >) tcln(UnboouXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnboou<Flt,Bln> > >) tcln(UnboouXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnboou<Flt,Int> > >) tcln(UnboouXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnboou<Flt,Flt> > >) tcln(UnboouXfFeVf,AutoClsSegFeV);

/* not between closed open unsatisfaction */
rti(BindXFeVt< bind3lr<tnbcou<Int,Bln> > >) tcln(UnbcouXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbcou<Int,Int> > >) tcln(UnbcouXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbcou<Int,Flt> > >) tcln(UnbcouXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbcou<Flt,Bln> > >) tcln(UnbcouXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbcou<Flt,Int> > >) tcln(UnbcouXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbcou<Flt,Flt> > >) tcln(UnbcouXfFeVf,AutoClsSegFeV);

/* not between open closed unsatisfaction */
rti(BindXFeVt< bind3lr<tnbocu<Int,Bln> > >) tcln(UnbocuXiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbocu<Int,Int> > >) tcln(UnbocuXiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbocu<Int,Flt> > >) tcln(UnbocuXiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbocu<Flt,Bln> > >) tcln(UnbocuXfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbocu<Flt,Int> > >) tcln(UnbocuXfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bind3lr<tnbocu<Flt,Flt> > >) tcln(UnbocuXfFeVf,AutoClsSegFeV);

/* ternary if */
rti(BindXFeVt< bindc3lr<tif<Bln,Bln,Bln> > >) tcln(UifXbKbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Bln,Bln,Int> > >) tcln(UifXbKbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Bln,Int,Bln> > >) tcln(UifXbKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Bln,Int,Int> > >) tcln(UifXbKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Bln,Flt,Flt> > >) tcln(UifXbKfFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Int,Bln,Bln> > >) tcln(UifXiKbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Int,Bln,Int> > >) tcln(UifXiKbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Int,Int,Bln> > >) tcln(UifXiKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Int,Int,Int> > >) tcln(UifXiKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Int,Flt,Flt> > >) tcln(UifXiKfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bindc3lr<tif<Bln,Bln,Flt> > >) tcln(UifXbKbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Bln,Int,Flt> > >) tcln(UifXbKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Bln,Flt,Bln> > >) tcln(UifXbKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Bln,Flt,Int> > >) tcln(UifXbKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Int,Bln,Flt> > >) tcln(UifXiKbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Int,Int,Flt> > >) tcln(UifXiKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Int,Flt,Bln> > >) tcln(UifXiKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Int,Flt,Int> > >) tcln(UifXiKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Flt,Bln,Bln> > >) tcln(UifXfKbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Flt,Bln,Int> > >) tcln(UifXfKbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Flt,Bln,Flt> > >) tcln(UifXfKbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Flt,Int,Bln> > >) tcln(UifXfKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Flt,Int,Int> > >) tcln(UifXfKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Flt,Int,Flt> > >) tcln(UifXfKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Flt,Flt,Bln> > >) tcln(UifXfKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Flt,Flt,Int> > >) tcln(UifXfKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindc3lr<tif<Flt,Flt,Flt> > >) tcln(UifXfKfFeVf,AutoClsSegFeV);

/* indexed list */
rti(BindXFeVt< bindcNd<nil<Int,Bln,Bln> > >) tcln(UilXiKbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Int,Bln,Int> > >) tcln(UilXiKbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Int,Int,Bln> > >) tcln(UilXiKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Int,Int,Int> > >) tcln(UilXiKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Int,Flt,Flt> > >) tcln(UilXiKfFeVf,AutoClsSegFeV);

rti(BindXFeVt< bindcNd<nil<Bln,Bln,Bln> > >) tcln(UilXbKbFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Bln,Bln,Int> > >) tcln(UilXbKbFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Bln,Bln,Flt> > >) tcln(UilXbKbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Bln,Int,Bln> > >) tcln(UilXbKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Bln,Int,Int> > >) tcln(UilXbKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Bln,Int,Flt> > >) tcln(UilXbKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Bln,Flt,Bln> > >) tcln(UilXbKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Bln,Flt,Int> > >) tcln(UilXbKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Bln,Flt,Flt> > >) tcln(UilXbKfFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Int,Bln,Flt> > >) tcln(UilXiKbFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Int,Int,Flt> > >) tcln(UilXiKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Int,Flt,Bln> > >) tcln(UilXiKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindcNd<nil<Int,Flt,Int> > >) tcln(UilXiKfFeVi,AutoClsSegFeV);

/* linear piecewise function with linear search */
//for explanation of XiKiKiKi go to the definition of lpfl, see the first 4 template parameters
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Int,Int,Bln> > >) tcln(UlpflXiKiKiKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Int,Int,Int> > >) tcln(UlpflXiKiKiKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Int,Int,Flt> > >) tcln(UlpflXiKiKiKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Int,Flt,Bln> > >) tcln(UlpflXiKiKiKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Int,Flt,Int> > >) tcln(UlpflXiKiKiKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Int,Flt,Flt> > >) tcln(UlpflXiKiKiKfFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Flt,Int,Bln> > >) tcln(UlpflXiKiKfKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Flt,Int,Int> > >) tcln(UlpflXiKiKfKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Flt,Int,Flt> > >) tcln(UlpflXiKiKfKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Flt,Flt,Bln> > >) tcln(UlpflXiKiKfKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Flt,Flt,Int> > >) tcln(UlpflXiKiKfKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Int,Flt,Flt,Flt> > >) tcln(UlpflXiKiKfKfFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Int,Int,Bln> > >) tcln(UlpflXiKfKiKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Int,Int,Int> > >) tcln(UlpflXiKfKiKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Int,Int,Flt> > >) tcln(UlpflXiKfKiKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Int,Flt,Bln> > >) tcln(UlpflXiKfKiKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Int,Flt,Int> > >) tcln(UlpflXiKfKiKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Int,Flt,Flt> > >) tcln(UlpflXiKfKiKfFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Flt,Int,Bln> > >) tcln(UlpflXiKfKfKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Flt,Int,Int> > >) tcln(UlpflXiKfKfKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Flt,Int,Flt> > >) tcln(UlpflXiKfKfKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Flt,Flt,Bln> > >) tcln(UlpflXiKfKfKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Flt,Flt,Int> > >) tcln(UlpflXiKfKfKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Int,Flt,Flt,Flt,Flt> > >) tcln(UlpflXiKfKfKfFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Int,Int,Bln> > >) tcln(UlpflXfKiKiKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Int,Int,Int> > >) tcln(UlpflXfKiKiKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Int,Int,Flt> > >) tcln(UlpflXfKiKiKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Int,Flt,Bln> > >) tcln(UlpflXfKiKiKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Int,Flt,Int> > >) tcln(UlpflXfKiKiKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Int,Flt,Flt> > >) tcln(UlpflXfKiKiKfFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Flt,Int,Bln> > >) tcln(UlpflXfKiKfKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Flt,Int,Int> > >) tcln(UlpflXfKiKfKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Flt,Int,Flt> > >) tcln(UlpflXfKiKfKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Flt,Flt,Bln> > >) tcln(UlpflXfKiKfKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Flt,Flt,Int> > >) tcln(UlpflXfKiKfKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Int,Flt,Flt,Flt> > >) tcln(UlpflXfKiKfKfFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Int,Int,Bln> > >) tcln(UlpflXfKfKiKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Int,Int,Int> > >) tcln(UlpflXfKfKiKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Int,Int,Flt> > >) tcln(UlpflXfKfKiKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Int,Flt,Bln> > >) tcln(UlpflXfKfKiKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Int,Flt,Int> > >) tcln(UlpflXfKfKiKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Int,Flt,Flt> > >) tcln(UlpflXfKfKiKfFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Flt,Int,Bln> > >) tcln(UlpflXfKfKfKiFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Flt,Int,Int> > >) tcln(UlpflXfKfKfKiFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Flt,Int,Flt> > >) tcln(UlpflXfKfKfKiFeVf,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Flt,Flt,Bln> > >) tcln(UlpflXfKfKfKfFeVb,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Flt,Flt,Int> > >) tcln(UlpflXfKfKfKfFeVi,AutoClsSegFeV);
rti(BindXFeVt< bindiNiddlr<lpfl<Flt,Flt,Flt,Flt,Flt> > >) tcln(UlpflXfKfKfKfFeVf,AutoClsSegFeV);

closeKangarooSpace


#endif//SegFeVsRegHhIncluded
