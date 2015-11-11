/*!
	@file msquare.cpp
	@brief The test file for MSquare.
	@details This is the implementation file for MSquare.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/idx.hh"
#include "test/tests.hpp"



openKangarooSpace

int testMSquare(int ArgC, char * ArgV[])
{
	Dim N = parseN(ArgV[1]);
	Itn I = parseN(ArgV[2]);
//	Rns R = parseN(ArgV[3]);
	Dim N2 = N*N;
	Dim S = N*(N*N + 1) / 2;

	Rnd theRnd;
	cout << endl << "Seed : " << theRnd.Seed() << endl;

	Hdl tSys = Sys::def();

	EvalTi::def(tSys);

	#if ExecDnwd
	Sys::setMultiCand(tSys);
	#if SimulFixedOnly
	Sys::setMultiFixed(tSys);
	#endif
	#if SimulFlexiOnly
	Sys::setMultiFlexi(tSys);
	#endif
	#endif

	kb<Prm> Vars(N2), Sums(2*N + 2), Eqs(2*N + 2);

	kb2<Hdl> SumHdls(2*N + 2, N);

	for(Idx tIdx = 0; tIdx < N2; ++tIdx)
		Vars[tIdx] = RngVi::def(tSys, 1, N2);

	for (Idx tIdx1 = 0; tIdx1 < N; ++tIdx1)
	{
		kb<Prm> Row(N);
		for (Idx tIdx2 = 0; tIdx2 < N; ++tIdx2)
		{
			Row[tIdx2] = Vars[tIdx1 * N + tIdx2];
//			SumHdls.item(tIdx1, tIdx2) = Row[tIdx2].TermHdl;
		}
		Sums[tIdx1] = GndSumEquXiBiFeVi::def(Xv, tSys, Row.items(), N, GndSumEquXiBiFeVi::bind(S));
//		Sums[tIdx1] = SumXiFeVi::def(Xv, tSys, Row.items(), N);
//		Eqs[tIdx1] = UequXiFcMi::def(Xv, tSys, Sums[tIdx1], S);
	}

	for (Idx tIdx1 = 0; tIdx1 < N; ++tIdx1)
	{
		kb<Prm> Col(N);
		for (Idx tIdx2 = 0; tIdx2 < N; ++tIdx2)
		{
			Col[tIdx2] = Vars[tIdx2 * N + tIdx1];
			SumHdls.item(N + tIdx1, tIdx2) = Col[tIdx2].TermHdl;
		}
		Sums[N + tIdx1] = GndSumEquXiBiFeVi::def(Xv, tSys, Col.items(), N, GndSumEquXiBiFeVi::bind(S));
//		Sums[N + tIdx1] = GndSumXiFeVi::def(Xv, tSys, Col.items(), N);
//		Eqs[N + tIdx1] = UequXiFcMi::def(Xv, tSys, Sums[N + tIdx1], S);
	}
	{
		kb<Prm> Dia(N);
		for (Idx tIdx = 0; tIdx < N; ++tIdx)
		{
			Dia[tIdx] = Vars[tIdx * N + tIdx];
			SumHdls.item(2*N, tIdx) = Dia[tIdx].TermHdl;
		}
		Sums[2*N] = GndSumEquXiBiFeVi::def(Xv, tSys, Dia.items(), N, GndSumEquXiBiFeVi::bind(S));
//		Sums[2*N] = GndSumXiFeVi::def(Xv, tSys, Dia.items(), N);
//		Eqs[2*N] = UequXiFcMi::def(Xv, tSys, Sums[2*N], UequXiFcMi::bind(S));
	}
	{
		kb<Prm> Dia(N);
		for (Idx tIdx = 0; tIdx < N; ++tIdx)
		{
			Dia[tIdx] = Vars[tIdx * N + N - tIdx - 1];
			SumHdls.item(2*N + 1, tIdx) = Dia[tIdx].TermHdl;
		}
		Sums[2*N + 1] = GndSumEquXiBiFeVi::def(Xv, tSys, Dia.items(), N, GndSumEquXiBiFeVi::bind(S));
//		Sums[2*N + 1] = GndSumXiFeVi::def(Xv, tSys, Dia.items(), N);
//		Eqs[2*N + 1] = UequXiFcMi::def(Xv, tSys, Sums[2*N + 1], S);
	}

//	Prm SumEqs = SumXiFcMi::def(Xv, tSys, Sums.items(), Sums.size());
//	Prm SumEqs = SumXiFcMi::def(Xv, tSys, Sums.items(), Sums.size());
	Prm SumEqs = SumXiFcMi::def(Xm, tSys, Eqs.items(), Eqs.size());

	Hdl const SelcHdl = MinTabuIdenSsXi::def(Xm, tSys, SumEqs);
//	Hdl const SelcHdl = MinTabuIdenSsXi::def(Xm, tSys, Vars[0]);

	kb<Itr> Vals(N2);
	for(Idx tIdx = 0; tIdx < N2; ++tIdx)
		Vals[tIdx] = tIdx;
	rndperm<Itr>(Vals.items(), N2, theRnd);

	Sys::execAnewItrVals(tSys, Vals.items());

	Sys::setVarTabuLimit(tSys, 3);

//	#if ExecLazy
//	Sys::execAnew(tSys, SumEqs.TermHdl);
//	#endif

	#if CompLazy
	Sys::setSelcActive(tSys, SelcHdl, true);
	#endif

	Sys const & ss = Sys::ref(tSys);
	RefHdl(Top, SumXiFcMi, tSys, SumEqs.TermHdl);

//	for(Idx tIdx = 0; tIdx < N2; ++tIdx)
//		cout << Vi::ref(tSys, Vars[tIdx].TermHdl).ValueRec().CurrData() << " ";
//	cout << "    ";
//	Int Sss = 0;
//	for(Idx tIdx = 0; tIdx < 2*N + 2; ++tIdx)
//	{
//		cout << FeVi::ref(tSys, Sums[tIdx].TermHdl).ValueRec().CurrData() << " ";
////		cout << FcMi::ref(tSys, Eqs[tIdx].TermHdl).MetricRec().CurrData();
//		Int Ss = 0;
//		for(Idx tIdxx = 0; tIdxx < N; ++tIdxx)
//			Ss += Vi::ref(tSys, SumHdls.item(tIdx, tIdxx)).ValueRec().CurrData();
////		if (Ss != FeVi::ref(tSys, Sums[tIdx].TermHdl).ValueRec().CurrData())
////			cerr << "E" << Ss;
////		if (labs(Ss - S) != FcMi::ref(tSys, Eqs[tIdx].TermHdl).MetricRec().CurrData())
////			cerr << "G" << abs(Ss - S);
//		if (labs(Ss - S) != FeVi::ref(tSys, Sums[tIdx].TermHdl).ValueRec().CurrData())
//			cerr << "G" << labs(Ss - S);
////		Sss += FcMi::ref(tSys, Eqs[tIdx].TermHdl).MetricRec().CurrData();
//		Sss += FeVi::ref(tSys, Sums[tIdx].TermHdl).ValueRec().CurrData();
//		cout << "  ";
//	}
//
//	if (Sss != Top.MetricRec().CurrData())
//		cerr << "K" << Sss;
//	cout << Top.MetricRec().CurrData() << endl;


	while(ss.ExecClk() <= I && Top.MetricRec().CurrData())
	{
		Sys::doSelcExecSwap(tSys, SelcHdl, theRnd);
//		#if ExecLazy
//		Sys::execIncr(tSys, SumEqs.TermHdl);
//		#endif

//		for(Idx tIdx = 0; tIdx < N2; ++tIdx)
//			cout << Vi::ref(tSys, Vars[tIdx].TermHdl).ValueRec().CurrData() << " ";
//		cout << "    ";
//		Int Sss = 0;
//		for(Idx tIdx = 0; tIdx < 2*N + 2; ++tIdx)
//		{
//			cout << FeVi::ref(tSys, Sums[tIdx].TermHdl).ValueRec().CurrData() << " ";
//	//		cout << FcMi::ref(tSys, Eqs[tIdx].TermHdl).MetricRec().CurrData();
//			Int Ss = 0;
//			for(Idx tIdxx = 0; tIdxx < N; ++tIdxx)
//				Ss += Vi::ref(tSys, SumHdls.item(tIdx, tIdxx)).ValueRec().CurrData();
//	//		if (Ss != FeVi::ref(tSys, Sums[tIdx].TermHdl).ValueRec().CurrData())
//	//			cerr << "E" << Ss;
//	//		if (labs(Ss - S) != FcMi::ref(tSys, Eqs[tIdx].TermHdl).MetricRec().CurrData())
//	//			cerr << "G" << abs(Ss - S);
//			if (labs(Ss - S) != FeVi::ref(tSys, Sums[tIdx].TermHdl).ValueRec().CurrData())
//				cerr << "G" << labs(Ss - S);
//	//		Sss += FcMi::ref(tSys, Eqs[tIdx].TermHdl).MetricRec().CurrData();
//			Sss += FeVi::ref(tSys, Sums[tIdx].TermHdl).ValueRec().CurrData();
//			cout << "  ";
//		}
//		if (Sss != Top.MetricRec().CurrData())
//			cerr << "K" << Sss;
//		cout << Top.MetricRec().CurrData() << endl;
	}
	cout << "Clk: "  << ss.ExecClk() << " Metric: " << Top.MetricRec().CurrData() << endl;
	cout << "Time: " << getTime() << " Memory: " << getMemory() << endl;
	return 0;
}


closeKangarooSpace
