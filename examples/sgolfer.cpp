/*!
	@file sgolfer.cpp
	@brief The source file for socialgolfer.
	@details This is the source file for socialgolfer.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/



#include "examples/examples.hpp"



/*!
	@fn int SGolfer(int ArgC, char * ArgV[])
*/
int SGolfer(int ArgC, char * ArgV[])
{
	if (ArgC <= 2)
	{
		cerr << endl << endl;
		cerr << "Social Golfer Problem" << endl << endl;
		cerr << "Usage:" << endl;
		cerr << ArgV[0] << " " << ArgV[1] << " -p PerGroup -g NumGroup -w NumWeek -i MaxIter [-t TabuLength -r RestartPeriod -s RandomSeed]" << endl << endl;
		cerr << "Output:" << endl;
		cerr << "BestViolation Iteration Time" << endl;
		cerr << "MemoryUsedByTheProgram" << endl;
		cerr << "TabuLength RestartPeriod PerGroup NumGroup NumWeek"
					"[WeeklyPersonGroups] RandomSeed" << endl;
		cerr << endl << endl;
		return ExitOnFailure;
	}

	Dim T = 0;	//	Tabu size
	Itn I = 0;	//	Max iteration

	Dim P = 0;
	Dim G = 0;
	Dim W = 0;
	Dim R = 0;
	Rnd theRnd;

	for(Idx tIdx = 2; tIdx < castIdx(ArgC); ++tIdx)
	{
		if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 't')
			T = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'i')
			I = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'p')
			P = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'g')
			G = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'w')
			W = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'r')
			R = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 's')
			theRnd.seed(parseN(ArgV[tIdx+1]));
	}

	if(!I || !P || !G || !W)
	{
		cerr << endl;
		cerr << "Error in commandline parameter/value. Run only with parameter " << ArgV[1] << " to see usage." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Dim C = P * G;
	Sys & tSys = Sys::refm(Sys::def());

	EvalTi::def(tSys.SysHdl);
	HintTi::def(tSys.SysHdl);

	Typ tTabuType = QcSv0Tabu::def(tSys.SysHdl, T);

	b1<Prm, kmm> Alloc(W * C), Consts(G);

	//	schedule first week
	for(Idx tK = 0; tK < G; ++tK)
	{
		Consts[tK] = Prm(Tc, ConstVi::def(tSys.SysHdl, tK));
		for(Idx tH = 0; tH < P; ++tH)
			Alloc[tK * P + tH] = Consts[tK];
	}

	//	variables for other weeks.
	for(Idx tJ = 1; tJ < W; ++tJ)
		for(Idx tI = 0; tI < C; ++tI)
			Alloc[tJ * C + tI] = Prm(Tv, StatRangeVarVi::def(tSys.SysHdl, 0, G-1));

	b1<Prm,xmm> Tops;
	for(Idx tJ = 1; tJ < W; ++tJ)
		for(Idx tK = 0; tK < G; ++tK)
		{
			b1<Prm,kmm> Equals(C);
			for(Idx tI = 0; tI < C; tI++)
				Equals[tI] = Prm(Tf, BeqsXiFeVi::def(Xv, tSys.SysHdl, Alloc[tJ * C + tI], Consts[tK]));
			Tops.insertMem(Prm(Tf, TcountEquXiBiFcMi::def(Xv, tSys.SysHdl, Equals.items(), C, TcountEquXiBiFcMi::bind(P)), MasM));// | MasEn));
		}
	for(Idx tI = 0; tI < C - 1; ++tI)
		for(Idx tL = tI + 1; tL < C; ++tL)
		{
			b1<Prm,kmm> Equals(W);
			for(Idx tJ = 0; tJ < W; ++tJ)
				Equals[tJ] = Prm(Tf, BeqsXiFeVi::def(Xv, tSys.SysHdl, Alloc[tJ * C + tI], Alloc[tJ * C + tL]));
			Tops.insertMem(Prm(Tf, TcountLeuXiBiFcMi::def(Xv, tSys.SysHdl, Equals.items(), W, TcountLeuXiBiFcMi::bind(1)), MasM));// | MasEn));
		}

	Prm TopSum = Prm(Tf, SumXiFcMi::def(Xm, tSys.SysHdl, Tops.items(), Tops.itemCount()));

	Hdl const tSelcHdl =  SvTabuMinIdenSsZi::def( Zm, tSys.SysHdl, TopSum, tTabuType);

	Refc(tTopSum, SumXiFcMi, tSys.SysHdl, TopSum.TermHdl);

	b1<Hdl,kmm> VarHdls(W*C - C);
	b1<Wrp,kmm> InitValues(W*C - C);
	for(Idx tJ = 1; tJ < W; ++tJ)
		for(Idx tI = 0; tI < C; ++tI)
		{
			VarHdls[tJ * C + tI - C] =  Alloc[tJ * C + tI].TermHdl;
			InitValues[tJ * C + tI - C] = (tJ * C + tI) % G;
		}
	shuffle<Wrp>(theRnd, InitValues.items(), W*C - C);
	tSys.initialiseVarsWrap(VarHdls.items(), InitValues.items());

	#if CompLazyHalf
	Selc::refm(tSys.SysHdl, tSelcHdl).activate(true);
	#endif

	Itn tSinceRestart = 1;
	Int BestMetric = tTopSum.MetricRec().CurrData();
	QcSv0Tabu & tQcSv0Tabu = QcSv0Tabu::refm(tSys.SysHdl);

	while(tSys.ExecClk() < I && BestMetric > 0)
	{
		if (R)
		{
			if (++tSinceRestart == R)
			{
				tQcSv0Tabu.setAutomatic(false);
				for(Idx tJ = 1; tJ < W; ++tJ)
					for(Idx tI = 0; tI < C; ++tI)
						InitValues[tJ * C + tI - C] = (tJ * C + tI) % G;
				shuffle<Wrp>(theRnd, InitValues.items(), W*C - C);
				tSys.execAnewVarsWrap(VarHdls.items(), InitValues.items());
				tQcSv0Tabu.setAutomatic(true);
				tSinceRestart = 1;
			}
		}
		else
		{
			Selc::selectExecuteSelc1(tSys.SysHdl, tSelcHdl, theRnd);
			#if CompLazyFull
			Term::performExecIncr(Func::ptrm(tSys.SysHdl, TopSum.TermHdl));
			#endif
		}
		if (tTopSum.MetricRec().CurrData() < BestMetric)
			BestMetric = tTopSum.MetricRec().CurrData();
	}

	cout << BestMetric << " " << tSys.ExecClk() << " " << getTime() << " " << getMemory() << endl;
	cout << T << " " << P << " " << G << " " << W;

	for(Idx tIdx = 0; tIdx < C; tIdx++)
		cout << " " << ConstVi::refc(tSys.SysHdl, Alloc[tIdx].TermHdl).Value();
	for(Idx tIdx = C; tIdx < C*W; tIdx++)
		cout << " " << StatRangeVarVi::refc(tSys.SysHdl, Alloc[tIdx].TermHdl).CurrValue();
	cout << endl;
	return ExitOnSuccess;
}

