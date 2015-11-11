/*!
	@file iseries.cpp
	@brief The source file for all interval series.
	@details This is the source file for all interval series.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/



#include "examples/examples.hpp"



/*!
	@brief A function to solve all interval series problem.
	@details This function solves all interval series loading problem.
	@param ArgC The number of parameters.
	@param ArgV The parameters themselves.
*/
int ISeries(int ArgC, char * ArgV[])
{
	if (ArgC <= 2)
	{
		cerr << endl;
		cerr << "Usage for All Interval Series" << endl;
		cerr << "Usage:" << endl;
		cerr << ArgV[0] << " " << ArgV[1] << " -n NumElem -i MaxIter [-t TabuLength -s RandSeed]" << endl << endl;
		cerr << "Output:" << endl;
		cerr << "BestViolation IterationCount RunTime MemoryUsage" << endl;
		cerr << "TabuLength NumElement [CellValues] RandomSeed" << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Dim C = 0;	//	Element count
	Itn I = 0;	//	Max iteration
	Dim T = 0; 	//	Tabu size
	Rnd theRnd;

	for(Idx tIdx = 2; tIdx < castIdx(ArgC); ++tIdx)
	{
		if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'n')
			C = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 't')
			T = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'i')
			I = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 's')
			theRnd.seed(parseN(ArgV[tIdx+1]));
	}
	if(!C || !I)
	{
		cerr << endl;
		cerr << "Error in commandline parameter/value. Run only with parameter " << ArgV[1] << " to see usage." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Sys & tSys = Sys::refm(Sys::def());
	#if ExecDnwd
	tSys.setMultiCandExec();
	#endif

	EvalTi::def(tSys.SysHdl);
	HintTi::def(tSys.SysHdl);

	Typ tTabuType = QcSv0Tabu::def(tSys.SysHdl, T);

	b1<Prm, kmm> tVars(C), tDiffs(C - 1);

	for(Idx tIdx = 0; tIdx < C; ++tIdx)
		tVars[tIdx] = Prm(Tv, StatRangeVarVi::def(tSys.SysHdl, 0, C - 1));

	for(Idx tIdx = 0; tIdx < C - 1; ++tIdx)
		tDiffs[tIdx] = Prm(Tf, BdiffXiFeVi::def(Xv, tSys.SysHdl, tVars[tIdx], tVars[tIdx + 1]));

	Prm tAdf =  Prm(Tf, AllDiffXiFcMi::def(Xv, tSys.SysHdl, tDiffs.items(), tDiffs.itemCount()));

	Hdl const tSelcHdl =  SvTabuMinIdenSsZi::def( Zm, tSys.SysHdl, tAdf, tTabuType);

	b1<Hdl,kmm> VarHdls(C);
	b1<Wrp,kmm> InitValues(C);
	for(Idx tIdx = 0; tIdx < C; ++tIdx)
	{
		VarHdls[tIdx] = tIdx;
		InitValues[tIdx] = Wrp(castInt(tIdx));
	}
	shuffle<Wrp>(theRnd, InitValues.items(), C);

	tSys.initialiseVarsWrap(VarHdls.items(), InitValues.items());

	#if CompLazyHalf
	Selc::refm(tSys.SysHdl, tSelcHdl).activate(true);
	#endif

	Refc(AdfRef, AllDiffXiFcMi, tSys.SysHdl, tAdf.TermHdl);
	Int BestMetric = AdfRef.MetricRec().CurrData();
	while(tSys.ExecClk() < I && BestMetric > 0)
	{
		Selc::selectExecuteSelc1(tSys.SysHdl, tSelcHdl, theRnd);
		#if CompLazyFull
		Term::performExecIncr(Func::ptrm(tSys.SysHdl, tAdf.TermHdl));
		#endif
		if (AdfRef.MetricRec().CurrData() < BestMetric)
			BestMetric = AdfRef.MetricRec().CurrData();
	}

	cout << BestMetric << " " << tSys.ExecClk() << " " << getTime() << " " << getMemory() << endl;
	cout << T << " " << C;
	if (!BestMetric)
	for(Idx tIdx = 0; tIdx < C; tIdx++)
		cout << " " << RangeVarVi::refc(tSys.SysHdl, tVars[tIdx].TermHdl).CurrValue();
	cout << " " << theRnd.Seed() << endl;
	return ExitOnSuccess;
}

