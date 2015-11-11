/*!
	@file vloading.cpp
	@brief The source file for vessel loading problem.
	@details This is the source file for vessel loading problem.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/



#include "examples/examples.hpp"



/*!
	@brief A function to solve vesel loading problem.
	@details This function solves vesel loading problem.
	@param ArgC The number of parameters.
	@param ArgV The parameters themselves.
*/
int VLoading(int ArgC, char * ArgV[])
{
	if (ArgC <= 2)
	{
		cerr << endl << endl;
		cerr << "Vessel Loading Problem" << endl << endl;
		cerr << "Usage:" << endl;
		cerr << ArgV[0] << " " << ArgV[1] << " -i MaxIter [-t TabuLength -s RandomSeed]" << endl << endl;
		cerr << "Input:" << endl;
		cerr << "Length Width MaxDim MinDim MaxCVR Count VesselLengthAndWidths" << endl << endl;
		cerr << "Output:" << endl;
		cerr << "BestViolation Iteration Time" << endl;
		cerr << "MemoryUsedByTheProgram" << endl;
		cerr << "TabuLength Length Width MaxDim MinDim MaxCVR Count"
					"VesselLengthAndWidths [VesselXandYandDirsWhenNoViolation] RandomSeed" << endl;
		cerr << endl << endl;
		return ExitOnFailure;
	}

	Itn MaxIteration = 0;
	Dim TabuLength = 0;
	Rnd theRnd;

	for(Idx tIdx = 2; tIdx < castIdx(ArgC); ++tIdx)
	{
		if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 't')
			TabuLength = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'i')
			MaxIteration = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 's')
			theRnd.seed(parseN(ArgV[tIdx+1]));
	}

	if(!MaxIteration)
	{
		cerr << endl;
		cerr << "Error in commandline parameter/value. Run only with parameter " << ArgV[1] << " to see usage." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Sys & tSys = Sys::refm(Sys::def());

	EvalTi::def(tSys.SysHdl);
	HintTi::def(tSys.SysHdl);

	QcSv2Tabu::def(tSys.SysHdl, TabuLength);

	Dim L; cin >> L;
	Dim W; cin >> W;
	Dim MaxD; cin >> MaxD;
	Dim MinD; cin >> MinD;
	Dim MaxCVR; cin >> MaxCVR;
	Dim C; cin >> C;

	if (!L || !W || !MaxD || !MinD || !MaxCVR || !C || L < W || MaxD < MinD)
	{
		cerr << endl;
		cerr << "Error in input values." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	b1<Prm, kmm> tX(C), tY(C), tD(C), tL(C), tW(C), tLP(C), tWP(C), tXP(C), tYP(C);

	for(Idx tIdx = 0; tIdx < C; ++tIdx)
	{
		Int tIntL; cin >> tIntL;
		tL[tIdx] = Prm(Tc,ConstVi::def(tSys.SysHdl, tIntL));

		Int tIntW; cin >> tIntW;
		tW[tIdx] = Prm(Tc, ConstVi::def(tSys.SysHdl, tIntW));

		if (!tIntL || !tIntW)
		{
			cerr << endl;
			cerr << "Error in input values." << endl;
			cerr << endl;
			return ExitOnFailure;
		}
	}

	for(Idx tIdx = 0; tIdx < C; ++tIdx)
	{
		tX[tIdx] = Prm(Tv, StatRangeVarVi::def(tSys.SysHdl, 0, L));
		tY[tIdx] = Prm(Tv, StatRangeVarVi::def(tSys.SysHdl, 0, W));
		tD[tIdx] = Prm(Tv, StatRangeVarVi::def(tSys.SysHdl, 0, 1));	//	true means L, false means W
	}

	for(Idx tIdx = 0; tIdx < C; ++tIdx)
	{
		tLP[tIdx] = Prm(Tf, IfteXiYiFeVi::def(Xv | Yv, tSys.SysHdl, tD[tIdx], tL[tIdx], tW[tIdx]));	//	true means L, false means W
		tWP[tIdx] = Prm(Tf, IfteXiYiFeVi::def(Xv | Yv, tSys.SysHdl, tD[tIdx], tW[tIdx], tL[tIdx]));	//	true means W, false means L
	}

	for(Idx tIdx = 0; tIdx < C; ++tIdx)
	{
		tXP[tIdx] = Prm(Tf, BaddXiFeVi::def(Xv, tSys.SysHdl, tX[tIdx], tLP[tIdx]));
		tYP[tIdx] = Prm(Tf, BaddXiFeVi::def(Xv, tSys.SysHdl, tY[tIdx], tWP[tIdx]));
	}

	b1<Prm, kmm> tConstrs(2 * C + C*(C - 1) / 2);
	for(Idx tIdx = 0; tIdx < C; ++tIdx)
	{
		tConstrs[tIdx * 2] = Prm(Tf, UleuXiFcMi::def(Xv, tSys.SysHdl, tXP[tIdx], UleuXiFcMi::bind(L)), MasM | MasEn);
		tConstrs[tIdx * 2 + 1] = Prm(Tf, UleuXiFcMi::def(Xv, tSys.SysHdl, tYP[tIdx], UleuXiFcMi::bind(W)), MasM | MasEn);
	}

	for(Idx tIdx1 = 0, tIdx = 2* C; tIdx1 < C - 1; tIdx1++)
		for(Idx tIdx2 = tIdx1 + 1; tIdx2 < C; tIdx2++)
		{
			b1<Prm, kmm> tPair(4);
			tPair[0] = Prm(Tf, BgesXiFeVi::def(Xv, tSys.SysHdl, tX[tIdx2], tXP[tIdx1]));
			tPair[1] = Prm(Tf, BlesXiFeVi::def(Xv, tSys.SysHdl, tXP[tIdx2], tX[tIdx1]));
			tPair[2] = Prm(Tf, BgesXiFeVi::def(Xv, tSys.SysHdl, tY[tIdx2], tYP[tIdx1]));
			tPair[3] = Prm(Tf, BlesXiFeVi::def(Xv, tSys.SysHdl, tYP[tIdx2], tY[tIdx1]));
			tConstrs[tIdx++] = Prm(Tf, NorsXiFcMi::def(Xv, tSys.SysHdl, tPair.items(), tPair.itemCount()), MasM | MasEn);
		}

	Prm TopSum = Prm(Tf, SumXiEFcMiHn::def(Xm | En, tSys.SysHdl, tConstrs.items(), tConstrs.itemCount()));

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
	while(tSys.ExecClk() < MaxIteration && BestMetric > 0)
	{
		Selc::selectExecuteSelc2(tSys.SysHdl, VarSelcHdl, ValSelcHdl, theRnd);
		#if CompLazyFull
		Term::performExecIncr(Func::ptrm(tSys.SysHdl, TopSum.TermHdl));
		#endif
		if (tTopSum.MetricRec().CurrData() < BestMetric)
			BestMetric = tTopSum.MetricRec().CurrData();
	}

	cout << BestMetric << " " << tSys.ExecClk() << " " << getTime() << " " << getMemory() << endl;
	cout << TabuLength << " " << L << " " << W << " " << MaxD << " "<< MinD << " ";//<< MaxCVR << " "
	cout << C;
	for(Idx tIdx = 0; tIdx < C; ++tIdx)
	{
		cout << " " << ConstVi::refc(tSys.SysHdl, tL[tIdx].TermHdl).Value();
		cout << " " << ConstVi::refc(tSys.SysHdl, tW[tIdx].TermHdl).Value();
	}

	if (!BestMetric)
	{
		for(Idx tIdx = 0; tIdx < C; ++tIdx)
			cout << " " << RangeVarVi::refc(tSys.SysHdl, tX[tIdx].TermHdl).CurrValue();
		for(Idx tIdx = 0; tIdx < C; ++tIdx)
			cout << " " << RangeVarVi::refc(tSys.SysHdl, tY[tIdx].TermHdl).CurrValue();
		for(Idx tIdx = 0; tIdx < C; ++tIdx)
			cout << " " << RangeVarVi::refc(tSys.SysHdl, tD[tIdx].TermHdl).CurrValue();
	}
	cout << " " << theRnd.Seed() << endl;
	return ExitOnSuccess;
}

