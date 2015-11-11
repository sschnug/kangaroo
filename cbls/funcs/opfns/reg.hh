/*!
	@file opfns/reg.hh
	@brief The register header file for operator function templates.
	@details This is the register header file for operator function templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef OpFnsRegHhIncluded
#define OpFnsRegHhIncluded


#include "cbls/funcs/opfns/unary.tcc"

openKangarooSpace

rti(unots<Bln,Bln>) tia(unotsBlnBln);
rti(unots<Bln,Int>) tia(unotsBlnInt);
rti(unots<Int,Bln>) tia(unotsIntBln);
rti(unots<Int,Int>) tia(unotsIntInt);

rti(unnots<Bln,Bln>) tia(unnotsBlnBln);
rti(unnots<Bln,Int>) tia(unnotsBlnInt);
rti(unnots<Int,Bln>) tia(unnotsIntBln);
rti(unnots<Int,Int>) tia(unnotsIntInt);

rti(unotu<Bln,Bln>) tia(unotuBlnBln);
rti(unotu<Bln,Int>) tia(unotuBlnInt);
rti(unotu<Int,Bln>) tia(unotuIntBln);
rti(unotu<Int,Int>) tia(unotuIntInt);

rti(unnotu<Bln,Bln>) tia(unnotuBlnBln);
rti(unnotu<Bln,Int>) tia(unnotuBlnInt);
rti(unnotu<Int,Bln>) tia(unnotuIntBln);
rti(unnotu<Int,Int>) tia(unnotuIntInt);

rti(uneg<Int,Int>) tia(unegIntInt);
rti(uabs<Int,Int>) tia(uabsIntInt);

closeKangarooSpace

#include "cbls/funcs/opfns/barith.tcc"

openKangarooSpace

rti(badd<Bln,Bln>) tia(baddBlnBln);
rti(badd<Bln,Int>) tia(baddBlnInt);
rti(badd<Int,Bln>) tia(baddIntBln);
rti(badd<Int,Int>) tia(baddIntInt);

rti(bmult<Bln,Bln>) tia(bmultBlnBln);
rti(bmult<Bln,Int>) tia(bmultBlnInt);
rti(bmult<Int,Bln>) tia(bmultIntBln);
rti(bmult<Int,Int>) tia(bmultIntInt);

rti(bdiff<Bln,Bln>) tia(bdiffBlnBln);
rti(bdiff<Bln,Int>) tia(bdiffBlnInt);
rti(bdiff<Int,Bln>) tia(bdiffIntBln);
rti(bdiff<Int,Int>) tia(bdiffIntInt);

rti(bmax<Bln,Bln>) tia(bmaxBlnBln);
rti(bmax<Bln,Int>) tia(bmaxBlnInt);
rti(bmax<Int,Bln>) tia(bmaxIntBln);
rti(bmax<Int,Int>) tia(bmaxIntInt);

rti(bmin<Bln,Bln>) tia(bminBlnBln);
rti(bmin<Bln,Int>) tia(bminBlnInt);
rti(bmin<Int,Bln>) tia(bminIntBln);
rti(bmin<Int,Int>) tia(bminIntInt);

rti(bsub<Bln,Bln>) tia(bsubBlnBln);
rti(bsub<Bln,Int>) tia(bsubBlnInt);
rti(bsub<Int,Bln>) tia(bsubIntBln);
rti(bsub<Int,Int>) tia(bsubIntInt);

rti(bdiv<Int,Int>) tia(bdivIntInt);
rti(bmod<Int,Int>) tia(bmodIntInt);
rti(bpow<Int,Int>) tia(bpowIntInt);

closeKangarooSpace

#include "cbls/funcs/opfns/blogic.tcc"

openKangarooSpace

rti(bands<Bln,Bln>) tia(bandsBlnBln);
rti(bands<Bln,Int>) tia(bandsBlnInt);
rti(bands<Int,Bln>) tia(bandsIntBln);
rti(bands<Int,Int>) tia(bandsIntInt);

rti(bnands<Bln,Bln>) tia(bnandsBlnBln);
rti(bnands<Bln,Int>) tia(bnandsBlnInt);
rti(bnands<Int,Bln>) tia(bnandsIntBln);
rti(bnands<Int,Int>) tia(bnandsIntInt);

rti(bors<Bln,Bln>) tia(borsBlnBln);
rti(bors<Bln,Int>) tia(borsBlnInt);
rti(bors<Int,Bln>) tia(borsIntBln);
rti(bors<Int,Int>) tia(borsIntInt);

rti(bnors<Bln,Bln>) tia(bnorsBlnBln);
rti(bnors<Bln,Int>) tia(bnorsBlnInt);
rti(bnors<Int,Bln>) tia(bnorsIntBln);
rti(bnors<Int,Int>) tia(bnorsIntInt);

rti(bxors<Bln,Bln>) tia(bxorsBlnBln);
rti(bxors<Bln,Int>) tia(bxorsBlnInt);
rti(bxors<Int,Bln>) tia(bxorsIntBln);
rti(bxors<Int,Int>) tia(bxorsIntInt);

rti(bxnors<Bln,Bln>) tia(bxnorsBlnBln);
rti(bxnors<Bln,Int>) tia(bxnorsBlnInt);
rti(bxnors<Int,Bln>) tia(bxnorsIntBln);
rti(bxnors<Int,Int>) tia(bxnorsIntInt);

rti(bimplys<Bln,Bln>) tia(bimplysBlnBln);
rti(bimplys<Bln,Int>) tia(bimplysBlnInt);
rti(bimplys<Int,Bln>) tia(bimplysIntBln);
rti(bimplys<Int,Int>) tia(bimplysIntInt);

rti(bnimplys<Bln,Bln>) tia(bnimplysBlnBln);
rti(bnimplys<Bln,Int>) tia(bnimplysBlnInt);
rti(bnimplys<Int,Bln>) tia(bnimplysIntBln);
rti(bnimplys<Int,Int>) tia(bnimplysIntInt);

rti(bandu<Bln,Bln>) tia(banduBlnBln);
rti(bandu<Bln,Int>) tia(banduBlnInt);
rti(bandu<Int,Bln>) tia(banduIntBln);
rti(bandu<Int,Int>) tia(banduIntInt);

rti(bnandu<Bln,Bln>) tia(bnanduBlnBln);
rti(bnandu<Bln,Int>) tia(bnanduBlnInt);
rti(bnandu<Int,Bln>) tia(bnanduIntBln);
rti(bnandu<Int,Int>) tia(bnanduIntInt);

rti(boru<Bln,Bln>) tia(boruBlnBln);
rti(boru<Bln,Int>) tia(boruBlnInt);
rti(boru<Int,Bln>) tia(boruIntBln);
rti(boru<Int,Int>) tia(boruIntInt);

rti(bnoru<Bln,Bln>) tia(bnoruBlnBln);
rti(bnoru<Bln,Int>) tia(bnoruBlnInt);
rti(bnoru<Int,Bln>) tia(bnoruIntBln);
rti(bnoru<Int,Int>) tia(bnoruIntInt);

rti(bxoru<Bln,Bln>) tia(bxoruBlnBln);
rti(bxoru<Bln,Int>) tia(bxoruBlnInt);
rti(bxoru<Int,Bln>) tia(bxoruIntBln);
rti(bxoru<Int,Int>) tia(bxoruIntInt);

rti(bxnoru<Bln,Bln>) tia(bxnoruBlnBln);
rti(bxnoru<Bln,Int>) tia(bxnoruBlnInt);
rti(bxnoru<Int,Bln>) tia(bxnoruIntBln);
rti(bxnoru<Int,Int>) tia(bxnoruIntInt);

rti(bimplyu<Bln,Bln>) tia(bimplyuBlnBln);
rti(bimplyu<Bln,Int>) tia(bimplyuBlnInt);
rti(bimplyu<Int,Bln>) tia(bimplyuIntBln);
rti(bimplyu<Int,Int>) tia(bimplyuIntInt);

rti(bnimplyu<Bln,Bln>) tia(bnimplyuBlnBln);
rti(bnimplyu<Bln,Int>) tia(bnimplyuBlnInt);
rti(bnimplyu<Int,Bln>) tia(bnimplyuIntBln);
rti(bnimplyu<Int,Int>) tia(bnimplyuIntInt);

closeKangarooSpace

#include "cbls/funcs/opfns/brelatn.tcc"

openKangarooSpace

rti(beqs<Bln,Bln>) tia(beqsBlnBln);
rti(beqs<Bln,Int>) tia(beqsBlnInt);
rti(beqs<Int,Bln>) tia(beqsIntBln);
rti(beqs<Int,Int>) tia(beqsIntInt);

rti(bnes<Bln,Bln>) tia(bnesBlnBln);
rti(bnes<Bln,Int>) tia(bnesBlnInt);
rti(bnes<Int,Bln>) tia(bnesIntBln);
rti(bnes<Int,Int>) tia(bnesIntInt);

rti(blts<Bln,Bln>) tia(bltsBlnBln);
rti(blts<Bln,Int>) tia(bltsBlnInt);
rti(blts<Int,Bln>) tia(bltsIntBln);
rti(blts<Int,Int>) tia(bltsIntInt);

rti(bgts<Bln,Bln>) tia(bgtsBlnBln);
rti(bgts<Bln,Int>) tia(bgtsBlnInt);
rti(bgts<Int,Bln>) tia(bgtsIntBln);
rti(bgts<Int,Int>) tia(bgtsIntInt);

rti(bles<Bln,Bln>) tia(blesBlnBln);
rti(bles<Bln,Int>) tia(blesBlnInt);
rti(bles<Int,Bln>) tia(blesIntBln);
rti(bles<Int,Int>) tia(blesIntInt);

rti(bges<Bln,Bln>) tia(bgesBlnBln);
rti(bges<Bln,Int>) tia(bgesBlnInt);
rti(bges<Int,Bln>) tia(bgesIntBln);
rti(bges<Int,Int>) tia(bgesIntInt);

rti(bequ<Bln,Bln>) tia(bequBlnBln);
rti(bequ<Bln,Int>) tia(bequBlnInt);
rti(bequ<Int,Bln>) tia(bequIntBln);
rti(bequ<Int,Int>) tia(bequIntInt);

rti(bneu<Bln,Bln>) tia(bneuBlnBln);
rti(bneu<Bln,Int>) tia(bneuBlnInt);
rti(bneu<Int,Bln>) tia(bneuIntBln);
rti(bneu<Int,Int>) tia(bneuIntInt);

rti(bltu<Bln,Bln>) tia(bltuBlnBln);
rti(bltu<Bln,Int>) tia(bltuBlnInt);
rti(bltu<Int,Bln>) tia(bltuIntBln);
rti(bltu<Int,Int>) tia(bltuIntInt);

rti(bgtu<Bln,Bln>) tia(bgtuBlnBln);
rti(bgtu<Bln,Int>) tia(bgtuBlnInt);
rti(bgtu<Int,Bln>) tia(bgtuIntBln);
rti(bgtu<Int,Int>) tia(bgtuIntInt);

rti(bleu<Bln,Bln>) tia(bleuBlnBln);
rti(bleu<Bln,Int>) tia(bleuBlnInt);
rti(bleu<Int,Bln>) tia(bleuIntBln);
rti(bleu<Int,Int>) tia(bleuIntInt);

rti(bgeu<Bln,Bln>) tia(bgeuBlnBln);
rti(bgeu<Bln,Int>) tia(bgeuBlnInt);
rti(bgeu<Int,Bln>) tia(bgeuIntBln);
rti(bgeu<Int,Int>) tia(bgeuIntInt);

closeKangarooSpace

#include "cbls/funcs/opfns/trange.tcc"

openKangarooSpace

rti(tbccs<Int,Bln>) tia(tbccsIntBln);
rti(tbccs<Int,Int>) tia(tbccsIntInt);

rti(tboos<Int,Bln>) tia(tboosIntBln);
rti(tboos<Int,Int>) tia(tboosIntInt);

rti(tbcos<Int,Bln>) tia(tbcosIntBln);
rti(tbcos<Int,Int>) tia(tbcosIntInt);

rti(tbocs<Int,Bln>) tia(tbocsIntBln);
rti(tbocs<Int,Int>) tia(tbocsIntInt);

rti(tnbccs<Int,Bln>) tia(tnbccsIntBln);
rti(tnbccs<Int,Int>) tia(tnbccsIntInt);

rti(tnboos<Int,Bln>) tia(tnboosIntBln);
rti(tnboos<Int,Int>) tia(tnboosIntInt);

rti(tnbcos<Int,Bln>) tia(tnbcosIntBln);
rti(tnbcos<Int,Int>) tia(tnbcosIntInt);

rti(tnbocs<Int,Bln>) tia(tnbocsIntBln);
rti(tnbocs<Int,Int>) tia(tnbocsIntInt);

rti(tbccu<Int,Bln>) tia(tbccuIntBln);
rti(tbccu<Int,Int>) tia(tbccuIntInt);

rti(tboou<Int,Bln>) tia(tboouIntBln);
rti(tboou<Int,Int>) tia(tboouIntInt);

rti(tbcou<Int,Bln>) tia(tbcouIntBln);
rti(tbcou<Int,Int>) tia(tbcouIntInt);

rti(tbocu<Int,Bln>) tia(tbocuIntBln);
rti(tbocu<Int,Int>) tia(tbocuIntInt);

rti(tnbccu<Int,Bln>) tia(tnbccuIntBln);
rti(tnbccu<Int,Int>) tia(tnbccuIntInt);

rti(tnboou<Int,Bln>) tia(tnboouIntBln);
rti(tnboou<Int,Int>) tia(tnboouIntInt);

rti(tnbcou<Int,Bln>) tia(tnbcouIntBln);
rti(tnbcou<Int,Int>) tia(tnbcouIntInt);

rti(tnbocu<Int,Bln>) tia(tnbocuIntBln);
rti(tnbocu<Int,Int>) tia(tnbocuIntInt);

closeKangarooSpace

#include "cbls/funcs/opfns/tnmux.tcc"

openKangarooSpace

rti(tif<Bln,Bln,Bln>) tia(tifBlnBlnBln);
rti(tif<Bln,Bln,Int>) tia(tifBlnBlnInt);
rti(tif<Bln,Int,Bln>) tia(tifBlnIntBln);
rti(tif<Bln,Int,Int>) tia(tifBlnIntInt);
rti(tif<Int,Bln,Bln>) tia(tifIntBlnBln);
rti(tif<Int,Bln,Int>) tia(tifIntBlnInt);
rti(tif<Int,Int,Bln>) tia(tifIntIntBln);
rti(tif<Int,Int,Int>) tia(tifIntIntInt);

rti(nil<Bln,Bln,Bln>) tia(nilBlnBlnBln);
rti(nil<Bln,Bln,Int>) tia(nilBlnBlnInt);
rti(nil<Bln,Int,Bln>) tia(nilBlnIntBln);
rti(nil<Bln,Int,Int>) tia(nilBlnIntInt);
rti(nil<Int,Bln,Bln>) tia(nilIntBlnBln);
rti(nil<Int,Bln,Int>) tia(nilIntBlnInt);
rti(nil<Int,Int,Bln>) tia(nilIntIntBln);
rti(nil<Int,Int,Int>) tia(nilIntIntInt);

closeKangarooSpace

#include "cbls/funcs/opfns/ipack.tcc"
openKangarooSpace
rti(ipack2<Int,Int>) tia(ipack2IntInt);
rti(ipack3<Int,Int>) tia(ipack3IntInt);
closeKangarooSpace


#endif//OpFnsRegHhIncluded
