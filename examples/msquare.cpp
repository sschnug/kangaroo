/*!
	@file msquare.cpp
	@brief The source file for magic square problem.
	@details This is the source file for magic square problem.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#include "examples/examples.hpp"



/*!
	@brief A function to solve magic square problem.
	@details This function solves magic square problem.
	@param ArgC The number of parameters.
	@param ArgV The parameters themselves.
*/
int MSquare(int ArgC, char * ArgV[])
{
	if (ArgC <= 2)
	{
		cerr << endl;
		cerr << "Magic Square Problem" << endl << endl;
		cerr << "Usage:" << endl;
		cerr << ArgV[0] << " " << ArgV[1] << " -n Dimension -i MaxIter [-t TabuLength -s RandSeed]" << endl << endl;
		cerr << "Output:" << endl;
		cerr << "BestViolation IterationCount RunTime MemoryUsage" << endl;
		cerr << "TabuLength SquareDimension [CellValuesRowMajorWise] RandomSeed" << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Dim Dimension = 0;
	Itn MaxIteration = 0;
	Dim TabuLength = 0;
	Rnd theRnd;

	for(Idx tIdx = 2; tIdx < castIdx(ArgC); ++tIdx)
	{
		if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'n')
			Dimension = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 't')
			TabuLength = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'i')
			MaxIteration = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 's')
			theRnd.seed(parseN(ArgV[tIdx+1]));
	}
	if(!Dimension || !MaxIteration)
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

	Typ tTabuType = QcSv0Tabu::def(tSys.SysHdl, TabuLength);

	b1<Prm,kmm> tVars(Dimension * Dimension);
	b1<Prm,kmm> tSums(Dimension + Dimension + 2);

	for(Idx tIdx = 0; tIdx < Dimension * Dimension; ++tIdx)
		tVars[tIdx] = Prm(Tv, StatRangeVarVi::def(tSys.SysHdl, 1, Dimension * Dimension));

	b1<Prm,kmm> tSumVars(Dimension);
	for(Idx tIdx1 = 0; tIdx1 < Dimension; ++tIdx1)
	{
		for(Idx tIdx2 = 0; tIdx2 < Dimension; ++tIdx2)
			tSumVars[tIdx2] = tVars[tIdx1 * Dimension + tIdx2];
		tSums[tIdx1] = Prm(Tf, GndSumEquXiBiFcMi::def(Xv, tSys.SysHdl, tSumVars.items(), Dimension,
				GndSumEquXiBiFcMi::bind(Dimension * (1 + Dimension * Dimension)/2)));
	}
	for(Idx tIdx1 = 0; tIdx1 < Dimension; ++tIdx1)
	{
		for(Idx tIdx2 = 0; tIdx2 < Dimension; ++tIdx2)
			tSumVars[tIdx2] = tVars[tIdx2 * Dimension + tIdx1];
		tSums[Dimension + tIdx1] = Prm(Tf, GndSumEquXiBiFcMi::def(Xv, tSys.SysHdl, tSumVars.items(), Dimension,
				GndSumEquXiBiFcMi::bind(Dimension * (1 + Dimension * Dimension)/2)));
	}

	for(Idx tIdx = 0; tIdx < Dimension; ++tIdx)
		tSumVars[tIdx] = tVars[tIdx * Dimension + tIdx];
	tSums[Dimension + Dimension] = Prm(Tf, GndSumEquXiBiFcMi::def(Xv, tSys.SysHdl, tSumVars.items(), Dimension,
			GndSumEquXiBiFcMi::bind(Dimension * (1 + Dimension * Dimension)/2)));

	for(Idx tIdx = 0; tIdx < Dimension; ++tIdx)
		tSumVars[tIdx] = tVars[tIdx * Dimension + Dimension - 1 - tIdx];
	tSums[Dimension + Dimension + 1] = Prm(Tf, GndSumEquXiBiFcMi::def(Xv, tSys.SysHdl, tSumVars.items(), Dimension,
			GndSumEquXiBiFcMi::bind(Dimension * (1 + Dimension * Dimension)/2)));

	Prm TopSum = Prm(Tf, SumXiFcMi::def(Xm, tSys.SysHdl, tSums.items(), Dimension + Dimension + 2));

	Hdl const tSelcHdl =  SvTabuMinIdenSsZi::def( Zm, tSys.SysHdl, TopSum, tTabuType);

	b1<Hdl,kmm> VarHdls(Dimension * Dimension);
	b1<Wrp,kmm> InitValues(Dimension * Dimension);
	for(Idx tIdx = 0; tIdx < Dimension * Dimension; ++tIdx)
	{
		VarHdls[tIdx] = tIdx;
		InitValues[tIdx] = Wrp(castInt(tIdx + 1));
	}
	shuffle<Wrp>(theRnd, InitValues.items(), Dimension * Dimension);

	tSys.initialiseVarsWrap(VarHdls.items(), InitValues.items());

	#if CompLazyHalf
	Selc::refm(tSys.SysHdl, tSelcHdl).activate(true);
	#endif

	Refc(tTopSum, SumXiFcMi, tSys.SysHdl, TopSum.TermHdl);
	Int BestMetric = tTopSum.MetricRec().CurrData();
	while(tSys.ExecClk() < MaxIteration && BestMetric > 0)
	{
		Selc::selectExecuteSelc1(tSys.SysHdl, tSelcHdl, theRnd);
		#if CompLazyFull
		Term::performExecIncr(Func::ptrm(tSys.SysHdl, TopSum.TermHdl));
		#endif
		if (tTopSum.MetricRec().CurrData() < BestMetric)
			BestMetric = tTopSum.MetricRec().CurrData();
	}

	cout << BestMetric << " " << tSys.ExecClk() << " " << getTime() << " " << getMemory() << endl;
	cout << TabuLength << " " << Dimension;
	if (!BestMetric)
		for(Idx tIdx = 0; tIdx < Dimension * Dimension; ++tIdx)
			cout << " " << StatRangeVarVi::refc(tSys.SysHdl, tIdx).CurrValue();
	cout << " " << theRnd.Seed() << endl;
	return ExitOnSuccess;
}

