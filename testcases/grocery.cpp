/*!
	@file grocery.cpp
	@brief The test file for MSquare.
	@details This is the implementation file for MSquare.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/


#include "test/tests.hpp"

openKangarooSpace

int testGrocery(int ArgC, char * ArgV[])
{
	Dim N  = 4; // parseN(ArgV[1]);
	Itn I  = 100;//parseN(ArgV[1]);
	Itn Tp =  2 ;// parseN(ArgV[2]);
	cerr << endl << "I  : " << I << endl;
	cerr << "Tp : " << Tp << endl;

	Rnd theRnd;//(1330452982);
	cout << endl << "Seed : " << theRnd.Seed() << endl;

	Hdl tSys = Sys::def();
	EvalTb::def(tSys);
	EvalTi::def(tSys);
	HintTi::def(tSys);

	#if ExecDnwd
	Sys::setMultiCand(tSys);
	#endif

	kb<Prm> Vars(N), Times(3);

	kb<Prm> Ctrs(N + 1);

	for(Idx tIdx = 0; tIdx < N; ++tIdx)
		Vars[tIdx] = RngVi::def(tSys, 0, 711);

	kb<Int> coefs(4);
	for ( Idx i = 0; i < N; ++i )
		coefs[i] = (1);

	Prm WSum = WghtSumKiXiFeVi::def( Xv, tSys, coefs.items(), Vars.items(), N );

	Ctrs[0] = Prm( UequXiFcMi::def( Xv, tSys, WSum, 711 ), Lm);

	Ctrs[1] = Prm( BltuXiFcMi::def( Xv, tSys, Vars[0], Vars[1] ), Lm);
	Ctrs[2] = Prm( BltuXiFcMi::def( Xv, tSys, Vars[1], Vars[2] ), Lm);
	Ctrs[3] = Prm( BltuXiFcMi::def( Xv, tSys, Vars[2], Vars[3] ), Lm);

	Times[0] = BmultXiFeVi::def( Xv, tSys, Vars[0],  Vars[1] );
	Times[1] = BmultXiFeVi::def( Xv, tSys, Times[0], Vars[2] );
	Times[2] = BmultXiFeVi::def( Xv, tSys, Times[1], Vars[3] );

	Ctrs[4] = Prm( UequXiFcMi::def( Xv, tSys, Times[2], 711000000 ), Lm);

	Prm Sum  = Prm(SumXiEFcMiD::def( Xm|El, tSys, Ctrs.items(), Ctrs.size()), Rd);

	RefHdl(Top, SumXiEFcMiD, tSys, Sum.TermHdl);

//	Hdl const SelcHdl = MinIdenSsXi::def(Xm, tSys, Sum);

	Prm Heap = TabuMaxHeapHiFrHi::def(tSys, Sum );

	Hdl const VarSelcHdl = RankVarSp::def( tSys, Heap);

	Hdl const ValSelcHdl = MinValSdXi::def( Xm, tSys, Sum );

//	kb<Itr> Vals(N);
//	for(Idx tIdx = 0; tIdx < N; ++tIdx)
//		Vals[tIdx] = tIdx;
//	rndperm<Itr>(Vals.items(), N, theRnd);
//
//	Sys::execAnewItrVals(tSys, Vals.items());

	Sys::setVarTabuLimit(tSys, Tp);

	Sys::execAnewRndVars(tSys, theRnd);

	#if CompLazy
//	Sys::setSelcActive(tSys, SelcHdl, true);
	Sys::setSelcActive(tSys, VarSelcHdl, true);
	Sys::setSelcActive(tSys, ValSelcHdl, true);
	#endif
	Sys const & ss = Sys::ref(tSys);

//	cout << ss.ExecClk() << " v ";
//	Int ws = 0;
//	for (Idx tIdx = 0; tIdx < N; ++tIdx)
//	{
//		ws += coefs[tIdx] * Vi::ref(tSys, Vars[tIdx].TermHdl).ValueRec().CurrData();
//		cout << Vi::ref(tSys, Vars[tIdx].TermHdl).ValueRec().CurrData() << " ";
//	}
//
//	cout << "f ";
//
//	cout << FeVi::ref(tSys, WSum.TermHdl).ValueRec().CurrData() << " ";
//
//	cout << FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() << " ";
//
//	if (ws != FeVi::ref(tSys, WSum.TermHdl).ValueRec().CurrData())
//		cerr << "W" << ws;
//	if (bequ<Int,Bln>::ifo(ws, 711) != FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData())
//		cerr << "E0";
//
//
//	cout << FcMb::ref(tSys, Ctrs[1].TermHdl).MetricRec().CurrData() << " ";
//	if (bltu<Int,Bln>::ifo(Vi::ref(tSys, Vars[0].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[1].TermHdl).ValueRec().CurrData())
//		!= FcMb::ref(tSys, Ctrs[1].TermHdl).MetricRec().CurrData()) cerr << "E1";
//
//	cout << FcMb::ref(tSys, Ctrs[2].TermHdl).MetricRec().CurrData() << " ";
//	if (bltu<Int,Bln>::ifo(Vi::ref(tSys, Vars[1].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[2].TermHdl).ValueRec().CurrData())
//		!= FcMb::ref(tSys, Ctrs[2].TermHdl).MetricRec().CurrData()) cerr << "E2";
//
//	cout << FcMb::ref(tSys, Ctrs[3].TermHdl).MetricRec().CurrData() << " ";
//	if (bltu<Int,Bln>::ifo(Vi::ref(tSys, Vars[2].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[3].TermHdl).ValueRec().CurrData())
//		!= FcMb::ref(tSys, Ctrs[3].TermHdl).MetricRec().CurrData()) cerr << "E3";
//
//	cout << FeVi::ref(tSys, Times[0].TermHdl).ValueRec().CurrData() << " ";
//	if (bmult<Int,Int>::ifo(Vi::ref(tSys, Vars[0].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[1].TermHdl).ValueRec().CurrData())
//		!= FeVi::ref(tSys, Times[0].TermHdl).ValueRec().CurrData()) cerr << "M0";
//
//	cout << FeVi::ref(tSys, Times[1].TermHdl).ValueRec().CurrData() << " ";
//	if (bmult<Int,Int>::ifo(FeVi::ref(tSys, Times[0].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[2].TermHdl).ValueRec().CurrData())
//		!= FeVi::ref(tSys, Times[1].TermHdl).ValueRec().CurrData()) cerr << "M1";
//
//	cout << FeVi::ref(tSys, Times[2].TermHdl).ValueRec().CurrData() << " ";
//	if (bmult<Int,Int>::ifo(FeVi::ref(tSys, Times[1].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[3].TermHdl).ValueRec().CurrData())
//		!= FeVi::ref(tSys, Times[2].TermHdl).ValueRec().CurrData()) cerr << "M2";
//
//	cout << FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() << " ";
//	if (bequ<Int,Bln>::ifo(FeVi::ref(tSys, Times[2].TermHdl).ValueRec().CurrData(), 7110000) != FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData())
//		cerr << "E4";
//
//	cout << Top.MetricRec().CurrData();
//	if (FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[1].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[2].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[3].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() != Top.MetricRec().CurrData())
//			cerr << "T";
//
//	cout << " h ";
//	for(Sln tSln = 0; tSln < N; ++tSln)
//		cout << Top.DescentRec().HintFlds[tSln].CurrData() << " ";
//
//	if (FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[1].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() != Top.DescentRec().HintFlds[0].CurrData())
//			cerr << "H0";
//	if (FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[1].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[2].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() != Top.DescentRec().HintFlds[1].CurrData())
//			cerr << "H1";
//
//	if (FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[2].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[3].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() != Top.DescentRec().HintFlds[2].CurrData())
//			cerr << "H2";
//
//	if (FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[3].TermHdl).MetricRec().CurrData() +
//		FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() != Top.DescentRec().HintFlds[3].CurrData())
//			cerr << "H3";
//
//	cout << endl;

	while (ss.ExecClk() <= I && Top.MetricRec().CurrData() )
	{
		Sys::doSelcPairExecDiff( tSys, VarSelcHdl, ValSelcHdl, theRnd );

//		cout << ss.ExecClk() << " v ";
//		Int ws = 0;
//		for (Idx tIdx = 0; tIdx < N; ++tIdx)
//		{
//			ws += coefs[tIdx] * Vi::ref(tSys, Vars[tIdx].TermHdl).ValueRec().CurrData();
//			cout << Vi::ref(tSys, Vars[tIdx].TermHdl).ValueRec().CurrData() << " ";
//		}
//
//		cout << "f ";
//
//		cout << FeVi::ref(tSys, WSum.TermHdl).ValueRec().CurrData() << " ";
//		cout << FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() << " ";
//		if (ws != FeVi::ref(tSys, WSum.TermHdl).ValueRec().CurrData())
//			cerr << "W" << ws;
//		if (bequ<Int,Bln>::ifo(ws, 711) != FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData())
//			cerr << "E0";
//		cout << FcMb::ref(tSys, Ctrs[1].TermHdl).MetricRec().CurrData() << " ";
//		if (bltu<Int,Bln>::ifo(Vi::ref(tSys, Vars[0].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[1].TermHdl).ValueRec().CurrData())
//			!= FcMb::ref(tSys, Ctrs[1].TermHdl).MetricRec().CurrData()) cerr << "E1 ";
//
//		cout << FcMb::ref(tSys, Ctrs[2].TermHdl).MetricRec().CurrData() << " ";
//		if (bltu<Int,Bln>::ifo(Vi::ref(tSys, Vars[1].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[2].TermHdl).ValueRec().CurrData())
//			!= FcMb::ref(tSys, Ctrs[2].TermHdl).MetricRec().CurrData()) cerr << "E2 ";
//
//		cout << FcMb::ref(tSys, Ctrs[3].TermHdl).MetricRec().CurrData() << " ";
//		if (bltu<Int,Bln>::ifo(Vi::ref(tSys, Vars[2].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[3].TermHdl).ValueRec().CurrData())
//			!= FcMb::ref(tSys, Ctrs[3].TermHdl).MetricRec().CurrData()) cerr << "E3 ";
//
//		cout << FeVi::ref(tSys, Times[0].TermHdl).ValueRec().CurrData() << " ";
//		if (bmult<Int,Int>::ifo(Vi::ref(tSys, Vars[0].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[1].TermHdl).ValueRec().CurrData())
//			!= FeVi::ref(tSys, Times[0].TermHdl).ValueRec().CurrData()) cerr << "M0 ";
//
//		cout << FeVi::ref(tSys, Times[1].TermHdl).ValueRec().CurrData() << " ";
//		if (bmult<Int,Int>::ifo(FeVi::ref(tSys, Times[0].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[2].TermHdl).ValueRec().CurrData())
//			!= FeVi::ref(tSys, Times[1].TermHdl).ValueRec().CurrData()) cerr << "M1";
//
//		cout << FeVi::ref(tSys, Times[2].TermHdl).ValueRec().CurrData() << " ";
//		if (bmult<Int,Int>::ifo(FeVi::ref(tSys, Times[1].TermHdl).ValueRec().CurrData(), Vi::ref(tSys, Vars[3].TermHdl).ValueRec().CurrData())
//			!= FeVi::ref(tSys, Times[2].TermHdl).ValueRec().CurrData()) cerr << "M2";
//
//		cout << FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() << " ";
//		if (bequ<Int,Bln>::ifo(FeVi::ref(tSys, Times[2].TermHdl).ValueRec().CurrData(), 7110000) != FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData())
//			cerr << "E4";
//
//		cout << Top.MetricRec().CurrData();
//		if (FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[1].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[2].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[3].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() != Top.MetricRec().CurrData())
//				cerr << "T";
//
//		cout << " h ";
//		for(Sln tSln = 0; tSln < N; ++tSln)
//			cout << Top.DescentRec().HintFlds[tSln].CurrData() << " ";
//
//		if (FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[1].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() != Top.DescentRec().HintFlds[0].CurrData())
//				cerr << "H0";
//		if (FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[1].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[2].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() != Top.DescentRec().HintFlds[1].CurrData())
//				cerr << "H1";
//
//		if (FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[2].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[3].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() != Top.DescentRec().HintFlds[2].CurrData())
//				cerr << "H2";
//
//		if (FcMb::ref(tSys, Ctrs[0].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[3].TermHdl).MetricRec().CurrData() +
//			FcMb::ref(tSys, Ctrs[4].TermHdl).MetricRec().CurrData() != Top.DescentRec().HintFlds[3].CurrData())
//				cerr << "H3";
//
//		cout << endl;
	}

/*
	cout << "Iteration: " << ss.ExecClk() << endl;
	for (Idx tIdx = 0; tIdx < N; ++tIdx)
		cout << Vi::ref(tSys, Vars[tIdx].TermHdl).ValueRec().CurrData() << " ";
	cout << Top.MetricRec().CurrData();
	cout << endl;

//	while (ss.ExecClk() <= I && Top.MetricRec().CurrData() ) {
//		Sys::doSelcExecSwap(tSys, SelcHdl, SelcHdl, theRnd);
//		cout << "Iteration: " << ss.ExecClk() << endl;
//		for (Idx tIdx = 0; tIdx < N; ++tIdx)
//			cout << Vi::ref(tSys, Vars[tIdx].TermHdl).ValueRec().CurrData() << " ";
//		cout << "    ";
//		cout << Top.MetricRec().CurrData() << endl;
//	}
	while (ss.ExecClk() <= I && Top.MetricRec().CurrData() ) {
		Sys::doSelcExecDiff( tSys, VarSelcHdl, ValSelcHdl, theRnd );
//		cout << "Iteration: " << ss.ExecClk() << endl;
//		int vsum = 0, vprod = 1;
//		for (Idx tIdx = 0; tIdx < N; ++tIdx) {
//			int _val = Vi::ref(tSys, Vars[tIdx].TermHdl).ValueRec().CurrData();
//			cout << _val << " ";
//			vsum  += _val;
//			vprod *= _val;
//		}
//		cout << endl;
//
//		int ct[5];
//		ct[0] = UequXiFcMi::ref( tSys, Ctrs[0].TermHdl ).MetricRec().CurrData();
//		ct[1] = BltuXiFcMi::ref( tSys, Ctrs[1].TermHdl ).MetricRec().CurrData();
//		ct[2] = BltuXiFcMi::ref( tSys, Ctrs[2].TermHdl ).MetricRec().CurrData();
//		ct[3] = BltuXiFcMi::ref( tSys, Ctrs[3].TermHdl ).MetricRec().CurrData();
//		ct[4] = UequXiFcMi::ref( tSys, Ctrs[4].TermHdl ).MetricRec().CurrData();
//
//		for (Idx tIdx = 0; tIdx <= N; ++tIdx) {
//			cout << ct[tIdx] << "  ";
//		}
//		cout << endl;
//
//		cout << "  WSum: " << WghtSumXiFeVi::ref( tSys, WSum.TermHdl ).ValueRec().CurrData() << " == " << vsum << endl;
//		cout << "  Prod: " << BmultXiFeVi::ref( tSys, Times[2].TermHdl ).ValueRec().CurrData() << " == " << vprod <<  endl;
//		cout << "  Top Metric: " << Top.MetricRec().CurrData() << endl;

	}*/
	cout << "Metric: " << Top.MetricRec().CurrData() << endl;
	return 0;
}


closeKangarooSpace
