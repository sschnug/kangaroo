/*!
	@file gcolor.cpp
	@brief The source file for graphcolor.
	@details This is the source file for graphcolor.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/



#include "examples/examples.hpp"


/*!
	@fn int GColor(int ArgC, char * ArgV[])
*/
int GColor(int ArgC, char * ArgV[])
{
	if (ArgC <= 2)
	{
		cerr << endl << endl;
		cerr << "Graph Coloring Problem" << endl << endl;
		cerr << "Usage:" << endl;
		cerr << ArgV[0] << " " << ArgV[1] << " -i MaxIter [-t TabuLength -s RandomSeed]" << endl << endl;
		cerr << "Input:" << endl;
		cerr << "NumColor EdgeProbability NumVertex, NumEdge EdgeVertexPairs" << endl << endl;
		cerr << "Output:" << endl;
		cerr << "BestViolation Iteration Time" << endl;
		cerr << "MemoryUsedByTheProgram" << endl;
		cerr << "TabuLength NumColor EdgeProbability NumVertex, NumEdge EdgeVertexPairs"
					"[VertexColors] RandomSeed" << endl;
		cerr << endl << endl;
		return ExitOnFailure;
	}

	Dim T = 0;	//	Tabu size
	Itn I = 0;	//	Max iteration
	Rnd theRnd;

	for(Idx tIdx = 2; tIdx < castIdx(ArgC); ++tIdx)
	{
		if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 't')
			T = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'i')
			I = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 's')
			theRnd.seed(parseN(ArgV[tIdx+1]));
	}

	if(!I)
	{
		cerr << endl;
		cerr << "Error in commandline parameter/value. Run only with parameter " << ArgV[1] << " to see usage." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Dim L; cin >> L;				// 	Num color
	Flt P; cin >> P;				// 	Edge probability
	Dim V; cin >> V;				//	Num vertex
	Dim E; cin >> E;				//	Num edges
	b1<Int, kmm> Start(E), End(E);	//	Edges

	for(Idx tIdx = 0; tIdx < E; ++tIdx)
	{
		Int tInt;
		cin >> tInt;
		Start[tIdx] = tInt - 1;		//	zero based numbering
		cin >> tInt;
		End[tIdx] = tInt - 1;		//	zero based numbering
	}

	if (!L || eq<Flt>::iof(P,0) || !V || !E)
	{
		cerr << endl;
		cerr << "Error in input values." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Sys & tSys = Sys::refm(Sys::def());

	EvalTi::def(tSys.SysHdl);
	HintTi::def(tSys.SysHdl);

	QcSv2Tabu::def(tSys.SysHdl, T);


	b1<Prm, kmm> tColors(V), tNotEquals(E);

	for(Idx tIdx = 0; tIdx < V; ++tIdx)
		tColors[tIdx] = Prm(Tv, StatRangeVarVi::def(tSys.SysHdl , 1, L));

	for(Idx tIdx = 0; tIdx < E; ++tIdx)
 		tNotEquals[tIdx] = Prm(Tf, BneuXiFcMi::def(Xv, tSys.SysHdl, tColors[Start[tIdx]], tColors[End[tIdx]]), MasM | MasEn);

	Prm TopSum = Prm(Tf, SumXiEFcMiHn::def(Xm | En, tSys.SysHdl, tNotEquals.items(), tNotEquals.itemCount()));

	Prm HintHeap = Prm(Tf, Sv2TabuMaxHeapHiFrHi::def(tSys.SysHdl, TopSum));

	Hdl const VarSelcHdl = RankedHintVar1Sp::def( tSys.SysHdl, HintHeap);
	Hdl const ValSelcHdl = MinVal1StatRangeSdViZi::def( Zm, tSys.SysHdl, TopSum);
	MinVal1StatRangeSdViZi::refm(tSys.SysHdl, ValSelcHdl).includeCurrValue(false);

	Refc(tTopSum, SumXiEFcMiHn, tSys.SysHdl, TopSum.TermHdl);

	tSys.initialiseVarsStatRand(theRnd);

	#if CompLazyHalf
	Selc::refm(tSys.SysHdl, VarSelcHdl).activate(true);
	Selc::refm(tSys.SysHdl, ValSelcHdl).activate(true);
	#endif

	Int BestMetric = tTopSum.MetricRec().CurrData();
	while(tSys.ExecClk() < I && BestMetric > 0)
	{
		Selc::selectExecuteSelc2(tSys.SysHdl, VarSelcHdl, ValSelcHdl, theRnd);
		#if CompLazyFull
		Term::performExecIncr(Func::ptrm(tSys.SysHdl, TopSum.TermHdl));
		#endif
		if (tTopSum.MetricRec().CurrData() < BestMetric)
			BestMetric = tTopSum.MetricRec().CurrData();
	}

	cout << BestMetric << " " << tSys.ExecClk() << " " << getTime() << " " << getMemory() << endl;
	cout << T << " " << L << " " << P << " " << V << " "<< E;
	for(Idx tIdx = 0; tIdx < E; ++tIdx)
		cout << " " << Start[tIdx] + 1 << " " << End[tIdx] + 1;

	if (!BestMetric)
	{
		for(Idx tIdx = 0; tIdx < V; ++tIdx)
			cout << " " << StatRangeVarVi::refc(tSys.SysHdl, tColors[tIdx].TermHdl).CurrValue();
	}
	cout << " " << theRnd.Seed() << endl;
	return ExitOnSuccess;
}

