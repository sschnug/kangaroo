/*!
	@file nqueen.cpp
	@brief The example program for NQueen.
	@details This is the example program for NQueen.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/



#include "examples/examples.hpp"



/*!
	@brief A function to solve n-queen problem.
	@details This function solves n-queen problem.
	@param ArgC The number of parameters.
	@param ArgV The parameters themselves.
*/
int NQueen(int ArgC, char * ArgV[])
{
	// Print usage if not sufficient commandline parameters
	if (ArgC <= 2)
	{
		cerr << endl;
		cout << "N-Queen Problem" << endl << endl;
		cerr << "Usage:" << endl;
		cerr << ArgV[0] << " -n NumQueen -i MaxIter [-s RandomSeed]" << endl;
		cerr << endl;
		cerr << "Output:" << endl;
		cerr << "BestViolation IterationCount Run-Time MemoryUsage" << endl;
		cerr << "QueenCount [QueenPositions] RandomSeed." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Dim QueenCount = 0;
	Itn MaxIteration = 0;
	Rnd theRnd;

	for(Idx tIdx = 2; tIdx < castIdx(ArgC); ++tIdx)
	{
		if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'n')
			QueenCount = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'i')
			MaxIteration = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 's')
			theRnd.seed(parseN(ArgV[tIdx+1]));
	}
	if(!QueenCount || !MaxIteration)
	{
		cerr << endl;
		cerr << "Error in commandline parameter/value. Run only with parameter " << ArgV[1] << " to see usage." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Sys & tSys = Sys::refm(Sys::def());

	EvalTi::def(tSys.SysHdl);
	HintTi::def(tSys.SysHdl);

	b1<Prm,kmm> Vars(QueenCount), Adds(QueenCount), Subs(QueenCount), AllDiffs(3);

	for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
	{
		Vars[tIdx] = Prm(Tv, StatRangeVarVi::def(tSys.SysHdl, 1, QueenCount));
		Adds[tIdx] = Prm(Tf, UaddXiFeVi::def(Xv, tSys.SysHdl, Vars[tIdx], UaddXiFeVi::bind(tIdx + 1)));
		Subs[tIdx] = Prm(Tf, UsubXiFeVi::def(Xv, tSys.SysHdl, Vars[tIdx], UsubXiFeVi::bind(tIdx + 1)));
//		cerr << "Add handle " << Adds[tIdx].TermHdl << " " << "Sub handle " << Subs[tIdx].TermHdl << endl;
	}

	AllDiffs[0] = Prm(Tf, AllDiffXiFcMiHn::def(Xv, tSys.SysHdl, Vars.items(), QueenCount));
	AllDiffs[1] = Prm(Tf, AllDiffXiFcMiHn::def(Xv, tSys.SysHdl, Adds.items(), QueenCount));
	AllDiffs[2] = Prm(Tf, AllDiffXiFcMiHn::def(Xv, tSys.SysHdl, Subs.items(), QueenCount));

//	cerr << "alldiff handles " << AllDiffs[0].TermHdl << " " << AllDiffs[1].TermHdl << " " << AllDiffs[2].TermHdl << endl;

	Prm TopSum = Prm(Tf, SumXiHFcMiHn::def(Xm|Hn, tSys.SysHdl, AllDiffs.items(), 3));

	Prm HintHeap = Prm(Tf, MaxHeapHiFrHi::def(tSys.SysHdl, TopSum));

//	cerr << "topsum " << TopSum.TermHdl << " heap " << HintHeap.TermHdl << endl;

	Hdl const VarSelcHdl = RankedHintVar1Sp::def( tSys.SysHdl, HintHeap);
	Hdl const ValSelcHdl = MinVal1StatRangeSdViZi::def( Zm, tSys.SysHdl, TopSum);
	MinVal1StatRangeSdViZi::refm(tSys.SysHdl, ValSelcHdl).includeCurrValue(false);

	Refc(tTopSum, SumXiHFcMiHn, tSys.SysHdl, TopSum.TermHdl);

	tSys.initialiseVarsStatRand(theRnd);

	#if CompLazyHalf
	Selc::refm(tSys.SysHdl, VarSelcHdl).activate(true);
	Selc::refm(tSys.SysHdl, ValSelcHdl).activate(true);
	#endif

	Int BestMetric = tTopSum.MetricRec().CurrData();
	while(tSys.ExecClk() < MaxIteration && BestMetric > 0)
	{
//		cerr << tSys.ExecClk() << " " << tTopSum.MetricRec().CurrData() << " " <<
//				AllDiffXiFcMiHn::refc(tSys.SysHdl, AllDiffs[0].TermHdl).MetricRec().CurrData() << " " <<
//				AllDiffXiFcMiHn::refc(tSys.SysHdl, AllDiffs[1].TermHdl).MetricRec().CurrData() << " " <<
//				AllDiffXiFcMiHn::refc(tSys.SysHdl, AllDiffs[2].TermHdl).MetricRec().CurrData();
//
//		cerr << "    ";
//		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
//			cerr << " " << StatRangeVarVi::refc(tSys.SysHdl, Vars[tIdx].TermHdl).CurrValue();
//		cerr << "    ";
//
//		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
//			cerr << " " << UaddXiFeVi::refc(tSys.SysHdl, Adds[tIdx].TermHdl).ValueRec().CurrData();
//		cerr << "    ";
//
//		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
//			cerr << " " << UsubXiFeVi::refc(tSys.SysHdl, Subs[tIdx].TermHdl).ValueRec().CurrData();
//		cerr << "    ";
//
//		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
//			cerr << " " << AllDiffXiFcMiHn::refc(tSys.SysHdl, AllDiffs[0].TermHdl).HintMinRec().HintFlds[tIdx].CurrData();
//		cerr << "    ";
//
//		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
//			cerr << " " << AllDiffXiFcMiHn::refc(tSys.SysHdl, AllDiffs[1].TermHdl).HintMinRec().HintFlds[tIdx].CurrData();
//		cerr << "    ";
//
//		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
//			cerr << " " << AllDiffXiFcMiHn::refc(tSys.SysHdl, AllDiffs[2].TermHdl).HintMinRec().HintFlds[tIdx].CurrData();
//		cerr << "    ";
//
//		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
//			cerr << " " << SumXiHFcMiHn::refc(tSys.SysHdl, TopSum.TermHdl).HintMinRec().HintFlds[tIdx].CurrData();
//		cerr << "    ";
//
//		cerr << endl << endl;

		Selc::selectExecuteSelc2(tSys.SysHdl, VarSelcHdl, ValSelcHdl, theRnd);
		#if CompLazyFull
		Term::performExecIncr(Func::ptrm(tSys.SysHdl, TopSum.TermHdl));
		#endif
		if (tTopSum.MetricRec().CurrData() < BestMetric)
			BestMetric = tTopSum.MetricRec().CurrData();
	}
	cout << BestMetric << " " << tSys.ExecClk() << " " << getTime() << " " << getMemory() << endl;
	cout << QueenCount;
	if (!BestMetric)
		for(Idx tIdx = 0; tIdx < QueenCount; ++tIdx)
			cout << " " << StatRangeVarVi::refc(tSys.SysHdl, tIdx).CurrValue();
	cout << " " << theRnd.Seed() << endl;
	return ExitOnSuccess;
}

