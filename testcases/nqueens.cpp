/*!
	@file nqueens.cpp
	@brief The test file for NQueens.
	@details This is the implementation file for NQueens.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/



#include "cbls/idx.hh"
#include "examples/domains.hpp"



openKangarooSpace


int testNQueens(int ArgC, char * ArgV[])
{
	Cnt S = parseCnt(ArgV[1]);	//	Selection
	Dim T = parseDim(ArgV[2]);	//	Tabu size
	Itn I = parseItn(ArgV[3]);	//	Max iteration
	Dim N = parseDim(ArgV[4]);	//	Number of queens


	Dim QueenCount = 4;//parseN(ArgV[1]);
	Itn MaxIter = 10;//parseN(ArgV[2]);
	Rns RandomSeed = 0;//parseN(ArgV[3]);
	Rnd theRnd(RandomSeed);
//	Rnd theRnd;
	cout << endl << "Seed : " << theRnd.Seed() << endl;

	Sys & tSys = Sys::refm(Sys::def());
	EvalTi::def(tSys.SysHdl);
	HintTi::def(tSys.SysHdl);
//	QcSv2Tabu::def(tSys.SysHdl, 10);

//	ConstVt<Int>::def(tSys.SysHdl, 1);

	b1<Prm,kmm> Vars(QueenCount), Adds(QueenCount), Subs(QueenCount), AllDiffs(3);

	for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
	{
		Vars[tIdx] = Prm(Tv, StatRangeVarVi::def(tSys.SysHdl, 1, QueenCount));
		Adds[tIdx] = Prm(Tf, UaddXiFeVi::def(Xv, tSys.SysHdl, Vars[tIdx], UaddXiFeVi::bind(tIdx + 1)));
		Subs[tIdx] = Prm(Tf, UsubXiFeVi::def(Xv, tSys.SysHdl, Vars[tIdx], UsubXiFeVi::bind(tIdx + 1)));
	}

	AllDiffs[0] = Prm(Tf, AllDiffXiFcMiHn::def(Xv, tSys.SysHdl, Vars.items(), QueenCount));
	AllDiffs[1] = Prm(Tf, AllDiffXiFcMiHn::def(Xv, tSys.SysHdl, Adds.items(), QueenCount));
	AllDiffs[2] = Prm(Tf, AllDiffXiFcMiHn::def(Xv, tSys.SysHdl, Subs.items(), QueenCount));

	Prm Sum = Prm(Tf, SumXiHFcMiHn::def(Xm|Hn, tSys.SysHdl, AllDiffs.items(), 3));

	Prm Heap = Prm(Tf, MaxHeapHiFrHi::def(tSys.SysHdl, Sum));
//	Prm Heap = Prm(Tf, Sv2TabuMaxHeapHiFrHi::def(tSys.SysHdl, Sum));

	Hdl const VarSelcHdl = RankedHintVar1Sp::def( tSys.SysHdl, Heap);
	Hdl const ValSelcHdl = MinVal1StatRangeSdViZi::def( Zm, tSys.SysHdl, Sum );
	MinVal1StatRangeSdViZi::refm(tSys.SysHdl, ValSelcHdl).includeCurrValue(true);

	Refc(Top, SumXiHFcMiHn, tSys.SysHdl, Sum.TermHdl);

	tSys.initialiseVarsStatRand(theRnd);
	#if CompLazyHalf
	Selc::refm(tSys.SysHdl, VarSelcHdl).activate(true);
	Selc::refm(tSys.SysHdl, ValSelcHdl).activate(true);
	#endif
	#define DebugOutput
	#ifdef DebugOutput
	{
		Int Cnt0 = 0, Cnt1 = 0, Cnt2 = 0;
		Int Vio0[QueenCount], Vio1[QueenCount], Vio2[QueenCount];
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << RangeVarVi::refc(tSys.SysHdl, Vars[tIdx].TermHdl).ValueRec().CurrData() << " ";
			Idx tIdxx = 0;
			while (tIdxx < tIdx && RangeVarVi::refc(tSys.SysHdl, Vars[tIdx].TermHdl).ValueRec().CurrData() !=
							RangeVarVi::refc(tSys.SysHdl, Vars[tIdxx].TermHdl).ValueRec().CurrData()) ++tIdxx;
			if (tIdxx == tIdx) ++Cnt0;	//	 a new value.
			Vio0[tIdx] = 0;
			for(tIdxx = 0; tIdxx < QueenCount; ++tIdxx)
				Vio0[tIdx] += (tIdxx != tIdx &&
						RangeVarVi::refc(tSys.SysHdl, Vars[tIdx].TermHdl).ValueRec().CurrData() ==
						RangeVarVi::refc(tSys.SysHdl, Vars[tIdxx].TermHdl).ValueRec().CurrData());
		}
		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FeVi::refc(tSys.SysHdl, Adds[tIdx].TermHdl).ValueRec().CurrData() << " ";
			if (FeVi::refc(tSys.SysHdl, Adds[tIdx].TermHdl).ValueRec().CurrData() !=
					RangeVarVi::refc(tSys.SysHdl, Vars[tIdx].TermHdl).ValueRec().CurrData() + castInt(tIdx + 1))
				cerr << "A";
			Idx tIdxx = 0;
			while (tIdxx < tIdx && FeVi::refc(tSys.SysHdl, Adds[tIdx].TermHdl).ValueRec().CurrData() !=
							FeVi::refc(tSys.SysHdl, Adds[tIdxx].TermHdl).ValueRec().CurrData()) ++tIdxx;
			if (tIdxx == tIdx) ++Cnt1;
			Vio1[tIdx] = 0;
			for(tIdxx = 0; tIdxx < QueenCount; ++tIdxx)
				Vio1[tIdx] += (tIdxx != tIdx &&
						FeVi::refc(tSys.SysHdl, Adds[tIdx].TermHdl).ValueRec().CurrData() ==
						FeVi::refc(tSys.SysHdl, Adds[tIdxx].TermHdl).ValueRec().CurrData());
		}
		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FeVi::refc(tSys.SysHdl, Subs[tIdx].TermHdl).ValueRec().CurrData() << " ";
			if (FeVi::refc(tSys.SysHdl, Subs[tIdx].TermHdl).ValueRec().CurrData() !=
					RangeVarVi::refc(tSys.SysHdl, Vars[tIdx].TermHdl).ValueRec().CurrData() - castInt(tIdx + 1))
				cerr << "S";
			Idx tIdxx = 0;
			while (tIdxx < tIdx && FeVi::refc(tSys.SysHdl, Subs[tIdx].TermHdl).ValueRec().CurrData() !=
							FeVi::refc(tSys.SysHdl, Subs[tIdxx].TermHdl).ValueRec().CurrData()) ++tIdxx;
			if (tIdxx == tIdx) ++Cnt2;
			Vio2[tIdx] = 0;
			for(tIdxx = 0; tIdxx < QueenCount; ++tIdxx)
				Vio2[tIdx] += (tIdxx != tIdx &&
						FeVi::refc(tSys.SysHdl, Subs[tIdx].TermHdl).ValueRec().CurrData() ==
						FeVi::refc(tSys.SysHdl, Subs[tIdxx].TermHdl).ValueRec().CurrData());
		}
		cout << "    ";
		cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[0].TermHdl).MetricRec().CurrData() << " ";
		if (FcMiHn::refc(tSys.SysHdl, AllDiffs[0].TermHdl).MetricRec().CurrData() != castInt(QueenCount - Cnt0)) cerr << "X";
		cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[1].TermHdl).MetricRec().CurrData() << " ";
		if (FcMiHn::refc(tSys.SysHdl, AllDiffs[1].TermHdl).MetricRec().CurrData() != castInt(QueenCount - Cnt1)) cerr << "Y";
		cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[2].TermHdl).MetricRec().CurrData() << " ";
		if (FcMiHn::refc(tSys.SysHdl, AllDiffs[2].TermHdl).MetricRec().CurrData() != castInt(QueenCount - Cnt2)) cerr << "Z";
		cout << FcMiHn::refc(tSys.SysHdl, Sum.TermHdl).MetricRec().CurrData() << " ";
		if (FcMiHn::refc(tSys.SysHdl, Sum.TermHdl).MetricRec().CurrData() != castInt(3*QueenCount - Cnt2 - Cnt1 - Cnt0)) cerr << "W";

		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[0].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() << " ";
			if (FcMiHn::refc(tSys.SysHdl, AllDiffs[0].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() != Vio0[tIdx]) cerr << "P";
		}
		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[1].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() << " ";
			if (FcMiHn::refc(tSys.SysHdl, AllDiffs[1].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() != Vio1[tIdx]) cerr << "Q";
		}
		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[2].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() << " ";
			if (FcMiHn::refc(tSys.SysHdl, AllDiffs[2].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() != Vio2[tIdx]) cerr << "R";
		}
		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FcMiHn::refc(tSys.SysHdl, Sum.TermHdl).HintMinRec().HintFlds[tIdx].CurrData() << " ";
			if (FcMiHn::refc(tSys.SysHdl, Sum.TermHdl).HintMinRec().HintFlds[tIdx].CurrData() != Vio0[tIdx] + Vio1[tIdx] + Vio2[tIdx]) cerr << "O";
		}
		cout << endl;
	}
	#endif // DebugOutput

	while(tSys.ExecClk() <= MaxIter && Top.MetricRec().CurrData())
	{
		if (!Selc::selectExecuteSelc2(tSys.SysHdl, VarSelcHdl, ValSelcHdl, theRnd))
			cerr << "WWWWWWWWWWWWWWW" << endl;
		#if CompLazyFull
		Term::performExecIncr(Func::ptrm(tSys.SysHdl, Sum.TermHdl));
		#endif

		#ifdef DebugOutput
		Int Cnt0 = 0, Cnt1 = 0, Cnt2 = 0;
		Int Vio0[QueenCount], Vio1[QueenCount], Vio2[QueenCount];
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << RangeVarVi::refc(tSys.SysHdl, Vars[tIdx].TermHdl).ValueRec().CurrData() << " ";
			Idx tIdxx = 0;
			while (tIdxx < tIdx && RangeVarVi::refc(tSys.SysHdl, Vars[tIdx].TermHdl).ValueRec().CurrData() !=
							RangeVarVi::refc(tSys.SysHdl, Vars[tIdxx].TermHdl).ValueRec().CurrData()) ++tIdxx;
			if (tIdxx == tIdx) ++Cnt0;	//	 a new value.
			Vio0[tIdx] = 0;
			for(tIdxx = 0; tIdxx < QueenCount; ++tIdxx)
				Vio0[tIdx] += (tIdxx != tIdx &&
						RangeVarVi::refc(tSys.SysHdl, Vars[tIdx].TermHdl).ValueRec().CurrData() ==
						RangeVarVi::refc(tSys.SysHdl, Vars[tIdxx].TermHdl).ValueRec().CurrData());
		}
		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FeVi::refc(tSys.SysHdl, Adds[tIdx].TermHdl).ValueRec().CurrData() << " ";
			if (FeVi::refc(tSys.SysHdl, Adds[tIdx].TermHdl).ValueRec().CurrData() !=
					RangeVarVi::refc(tSys.SysHdl, Vars[tIdx].TermHdl).ValueRec().CurrData() + castInt(tIdx + 1))
				cerr << "A";
			Idx tIdxx = 0;
			while (tIdxx < tIdx && FeVi::refc(tSys.SysHdl, Adds[tIdx].TermHdl).ValueRec().CurrData() !=
							FeVi::refc(tSys.SysHdl, Adds[tIdxx].TermHdl).ValueRec().CurrData()) ++tIdxx;
			if (tIdxx == tIdx) ++Cnt1;
			Vio1[tIdx] = 0;
			for(tIdxx = 0; tIdxx < QueenCount; ++tIdxx)
				Vio1[tIdx] += (tIdxx != tIdx &&
						FeVi::refc(tSys.SysHdl, Adds[tIdx].TermHdl).ValueRec().CurrData() ==
						FeVi::refc(tSys.SysHdl, Adds[tIdxx].TermHdl).ValueRec().CurrData());
		}
		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FeVi::refc(tSys.SysHdl, Subs[tIdx].TermHdl).ValueRec().CurrData() << " ";
			if (FeVi::refc(tSys.SysHdl, Subs[tIdx].TermHdl).ValueRec().CurrData() !=
					RangeVarVi::refc(tSys.SysHdl, Vars[tIdx].TermHdl).ValueRec().CurrData() - castInt(tIdx + 1))
				cerr << "S";
			Idx tIdxx = 0;
			while (tIdxx < tIdx && FeVi::refc(tSys.SysHdl, Subs[tIdx].TermHdl).ValueRec().CurrData() !=
							FeVi::refc(tSys.SysHdl, Subs[tIdxx].TermHdl).ValueRec().CurrData()) ++tIdxx;
			if (tIdxx == tIdx) ++Cnt2;
			Vio2[tIdx] = 0;
			for(tIdxx = 0; tIdxx < QueenCount; ++tIdxx)
				Vio2[tIdx] += (tIdxx != tIdx &&
						FeVi::refc(tSys.SysHdl, Subs[tIdx].TermHdl).ValueRec().CurrData() ==
						FeVi::refc(tSys.SysHdl, Subs[tIdxx].TermHdl).ValueRec().CurrData());
		}
		cout << "    ";
		cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[0].TermHdl).MetricRec().CurrData() << " ";
		if (FcMiHn::refc(tSys.SysHdl, AllDiffs[0].TermHdl).MetricRec().CurrData() != castInt(QueenCount - Cnt0)) cerr << "X";
		cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[1].TermHdl).MetricRec().CurrData() << " ";
		if (FcMiHn::refc(tSys.SysHdl, AllDiffs[1].TermHdl).MetricRec().CurrData() != castInt(QueenCount - Cnt1)) cerr << "Y";
		cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[2].TermHdl).MetricRec().CurrData() << " ";
		if (FcMiHn::refc(tSys.SysHdl, AllDiffs[2].TermHdl).MetricRec().CurrData() != castInt(QueenCount - Cnt2)) cerr << "Z";
		cout << FcMiHn::refc(tSys.SysHdl, Sum.TermHdl).MetricRec().CurrData() << " ";
		if (FcMiHn::refc(tSys.SysHdl, Sum.TermHdl).MetricRec().CurrData() != castInt(3*QueenCount - Cnt2 - Cnt1 - Cnt0)) cerr << "W";

		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[0].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() << " ";
			if (FcMiHn::refc(tSys.SysHdl, AllDiffs[0].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() != Vio0[tIdx]) cerr << "P";
		}
		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[1].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() << " ";
			if (FcMiHn::refc(tSys.SysHdl, AllDiffs[1].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() != Vio1[tIdx]) cerr << "Q";
		}
		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FcMiHn::refc(tSys.SysHdl, AllDiffs[2].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() << " ";
			if (FcMiHn::refc(tSys.SysHdl, AllDiffs[2].TermHdl).HintMinRec().HintFlds[tIdx].CurrData() != Vio2[tIdx]) cerr << "R";
		}
		cout << "    ";
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		{
			cout << FcMiHn::refc(tSys.SysHdl, Sum.TermHdl).HintMinRec().HintFlds[tIdx].CurrData() << " ";
			if (FcMiHn::refc(tSys.SysHdl, Sum.TermHdl).HintMinRec().HintFlds[tIdx].CurrData() != Vio0[tIdx] + Vio1[tIdx] + Vio2[tIdx]) cerr << "O";
		}
		cout << endl;
		#endif//DebugOutput

	}
	cerr << "Metric: " << Top.MetricRec().CurrData() << " Clk: " << tSys.ExecClk() << endl;
	cerr << "Time: " << getTime() << " Memory: " << getMemory() << endl;
	for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
		cout << StatRangeVarVi::refc(tSys.SysHdl, tIdx).CurrValue() << " ";
	cout << endl;

	return 0;
}

closeKangarooSpace
