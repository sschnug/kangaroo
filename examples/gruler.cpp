/*!
	@file gruler.cpp
	@brief The source file for golombruler.
	@details This is the source file for golombruler.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#include "examples/examples.hpp"
/*
int Table[] =
{
0,	0,
1, 	0,
2 ,	1,
3 ,	3,
4 ,	6,
5 ,	11,
6 ,	17,
7 ,	25,
8 ,	34,
9 ,	44,
10, 55,
11, 72,
12, 85,
13, 106,
14, 127,
15, 151,
16, 177,
17, 199,
18, 216,
19, 246,
20, 283,
21, 333,
22, 356,
23,	372,
24,	425,
25,	480,
26,	492,
27,	553,
28,	585,
29,	623,
30,	680,
31,	747,
32,	784,
33,	859,
34,	938,
35,	987,
36,	1005,
37,	1099,
38,	1146,
39,	1252,
40,	1282,
41,	1305,
42,	1397,
43,	1507,
44,	1596,
45,	1687,
46,	1703,
47,	1804,
48,	1887,
49,	1958,
50,	2094,
51,	2190,
52,	2270,
53,	2347,
54,	2373,
55,	2598,
56,	2725,
57,	2773,
58,	2851,
59,	2911,
60,	3019,
61,	3134,
62,	3215,
63,	3391,
64,	3527,
65,	3593,
66,	3757,
67,	3819,
68,	3956,
69,	4145,
70,	4217,
71,	4330,
72,	4473,
73,	4513,
74,	4753,
75,	4982,
76,	5089,
77,	5204,
78,	5299,
79,	5408,
80,	5563,
81,	5717,
82,	5814,
83,	6020,
84,	6159,
85,	6410,
86,	6537,
87,	6708,
88,	6745,
89,	6778,
90,	6967,
91,	7542,
92,	7617,
93,	7726,
94,	7884,
95,	7967,
96,	8121,
97,	8357,
98,	8462,
99,	8540,
100, 8831,
101, 8897,
102, 9218,
103, 9408,
104, 9581,
105, 9884,
106, 10135,
107, 10241,
108, 10415,
109, 10583,
110, 10767,
111, 11108,
112, 11292,
113, 11423,
114, 11764,
115, 12212,
116, 12412,
117, 12517,
118, 12741,
119, 12911,
120, 13089,
121, 13280,
122, 13521,
123, 13761,
124, 13948,
125, 14055,
126, 14348,
127, 14460,
128, 14821,
129, 15075,
130, 15275,
131, 15548,
132, 15893,
133, 16192,
134, 16296,
135, 16622,
136, 16766,
137, 17031,
138, 17124,
139, 17579,
140, 17938,
141, 18601,
142, 18751,
143, 18941,
144, 19123,
145, 19325,
146, 19628,
147, 19757,
148, 20037,
149, 20265,
150, 20521
};
*/

/*!
	@fn void GRuler(int ArgC, char * ArgV[])
*/
int GRuler(int ArgC, char * ArgV[])
{
	if (ArgC <= 2)
	{
		cerr << endl << endl;
		cerr << "Golomb Ruler Problem" << endl << endl;
		cerr << "Usage:" << endl;
		cerr << ArgV[0] << " " << ArgV[1] << " -n NumTicks -d MaxValue -i MaxIter [-t TabuLength -s RandomSeed -a Approach]" << endl << endl;
		cerr << "Output:" << endl;
		cerr << "BestViolation Iteration Time" << endl;
		cerr << "MemoryUsedByTheProgram" << endl;
		cerr << "TabuLength NumTics MaxValue [TickValues] RandomSeed" << endl;
		cerr << endl << endl;
		return ExitOnFailure;
	}

	Dim T = 0;	//	Tabu size
	Itn I = 0;	//	Iteration
	Dim M = 0;	//	NumTicks
	Dim L = 0;	//	DomainSize
	Dim A = 1;	//	Approach
	Rnd theRnd;

	for(Idx tIdx = 2; tIdx < castIdx(ArgC); ++tIdx)
	{
		if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 't')
			T = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'n')
			M = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'd')
			L = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'i')
			I = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'a')
			A = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 's')
			theRnd.seed(parseN(ArgV[tIdx+1]));
	}

	if(!I || !M)
	{
		cerr << endl;
		cerr << "Error in commandline parameter/value. Run only with parameter " << ArgV[1] << " to see usage." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Sys & tSys = Sys::refm(Sys::def());

	EvalTi::def(tSys.SysHdl);
	HintTi::def(tSys.SysHdl);

	QcSv2Tabu::def(tSys.SysHdl, T);

	b1<Prm, kmm> Diffs(M * (M - 1) / 2);
	//	The first variable is 0 and is not created.
	//	The first M-1 diffs are just the variables because
	// 		subtracting zero from them does not make any difference.
	if (A == 0)	//	static range
		for(Idx tIdx = 0; tIdx < M - 1; ++tIdx)
			Diffs[tIdx] = Prm(Tv, StatRangeVarVi::def(tSys.SysHdl, 1, L));
	else	//	dynamic range
		for(Idx tIdx = 0; tIdx < M - 1; ++tIdx)
			Diffs[tIdx] = Prm(Tv, DynaRangeCtlVarVi::def(tSys.SysHdl, 1, L));

	//	Create differences for all other pairs of variables.
	if (A == 0)	//	static range
		for(Idx tIdx1 = 0, tIdx = M - 1; tIdx1 < M - 2; ++tIdx1)
			for(Idx tIdx2 = tIdx1 + 1; tIdx2 < M - 1; ++tIdx2)
				Diffs[tIdx++] = Prm(Tf, BdiffXiFeVi::def(Xv, tSys.SysHdl, Diffs[tIdx2], Diffs[tIdx1]));	//	difference because unsorted.
	else //	dynamic range
		for(Idx tIdx1 = 0, tIdx = M - 1; tIdx1 < M - 2; ++tIdx1)
			for(Idx tIdx2 = tIdx1 + 1; tIdx2 < M - 1; ++tIdx2)
				Diffs[tIdx++] = Prm(Tf, BsubXiFeVi::def(Xv, tSys.SysHdl, Diffs[tIdx2], Diffs[tIdx1]));	//	subtraction because sorted.

	Prm tAdf =  Prm(Tf, AllDiffXiFcMiHn::def(Xv, tSys.SysHdl, Diffs.items(), Diffs.itemCount()));

	Prm HintHeap = Prm(Tf, Sv2TabuMaxHeapHiFrHi::def(tSys.SysHdl, tAdf));

	Hdl VarSelcHdl, ValSelcHdl;
	VarSelcHdl = RankedHintVar1Sp::def( tSys.SysHdl, HintHeap);
	if (A == 0)
	{
		ValSelcHdl = MinVal1StatRangeSdViZi::def( Zm, tSys.SysHdl, tAdf);
		MinVal1StatRangeSdViZi::refm(tSys.SysHdl, ValSelcHdl).includeCurrValue(false);
	}
	else
	{
		ValSelcHdl = MinVal1DynaRangeSdViZi::def( Zm, tSys.SysHdl, tAdf);
		MinVal1DynaRangeSdViZi::refm(tSys.SysHdl, ValSelcHdl).includeCurrValue(true);

		b1<Prm, kmm> Bounds(2 * (M - 1));
		Bounds[0] = Prm(Tc, ConstVi::def(tSys.SysHdl, 1));
		for(Idx tIdx = 0, ttIdx = 1; tIdx < M - 2; ++tIdx)
		{
			Bounds[ttIdx++] = Prm(Tf, UsubXiFeVi::def(Xv, tSys.SysHdl, Diffs[tIdx + 1], UsubXiFeVi::bind(1)));
			Bounds[ttIdx++] = Prm(Tf, UaddXiFeVi::def(Xv, tSys.SysHdl, Diffs[tIdx], UaddXiFeVi::bind(1)));
		}
		Bounds[2*M - 3] = Prm(Tc, ConstVi::def(tSys.SysHdl, L));

		for(Idx tIdx = 0; tIdx < M - 1; ++tIdx)
			DynaRangeCtlVarVi::refm(tSys.SysHdl, Diffs[tIdx].TermHdl).setDynaRangeX(Xv, Bounds[2*tIdx], Bounds[2*tIdx + 1]);
	}

	b1<Hdl, kmm> tHdls(M - 1);
	b1<Wrp, kmm> tWrps(M - 1);

	{
		b1<Int, kmm> tInit(M - 1);
		hset<Int, nmmh> tInitSet(M-1);
		for(Idx tIdx = 0; tIdx < M - 1; ++tIdx)
		{
			Int tInt = uniform(theRnd, castInt(1), castInt(L));
			while(!tInitSet.insertBll(tInt))
				tInt = uniform(theRnd, castInt(1), castInt(L));
			tInit[tIdx] = tInt;
			tHdls[tIdx] = Diffs[tIdx].TermHdl;
		}
		if (A != 0)
			itemsort<Int, lt<Int> >(tInit.items(), M - 1);
		for(Idx tIdx = 0; tIdx < M - 1; ++tIdx)
			tWrps[tIdx] = Wrp(tInit[tIdx]);
	}

	tSys.initialiseVarsWrap(tHdls.items(), tWrps.items());

	#if CompLazyHalf
	Selc::refm(tSys.SysHdl, VarSelcHdl).activate(true);
	Selc::refm(tSys.SysHdl, ValSelcHdl).activate(true);
	#endif

	Refc(tAdfRef, AllDiffXiFcMiHn, tSys.SysHdl, tAdf.TermHdl);

	Int BestMetric = tAdfRef.MetricRec().CurrData();
	while(tSys.ExecClk() < I && BestMetric > 0)
	{
//		cout << "clock " << tSys.ExecClk() << " ";
//		cout << " 0";
//		for(Idx tIdx = 0; tIdx < M - 1; ++tIdx)
//			cout << " " << DynaRangeCtlVarVi::refc(tSys.SysHdl, Diffs[tIdx].TermHdl).CurrValue();
//		cout << " hint ";
//		for(Idx tIdx = 0; tIdx < M - 1; ++tIdx)
//			cout << tAdfRef.HintMinRec().HintFlds[tIdx].CurrData() << " ";
//		cout << endl;

		Selc::selectExecuteSelc2(tSys.SysHdl, VarSelcHdl, ValSelcHdl, theRnd);
		#if CompLazyFull
		Term::performExecIncr(Func::ptrm(tSys.SysHdl, tAdf.TermHdl));
		#endif
		if (tAdfRef.MetricRec().CurrData() < BestMetric)
			BestMetric = tAdfRef.MetricRec().CurrData();
	}

	cout << BestMetric << " " << tSys.ExecClk() << " " << getTime() << " " << getMemory() << endl;
	cout << T << " " << M << " " << L;
	if (!BestMetric)
	{
		cout << " 0";
		for(Idx tIdx = 0; tIdx < M - 1; ++tIdx)
			cout << " " << DynaRangeCtlVarVi::refc(tSys.SysHdl, Diffs[tIdx].TermHdl).CurrValue();
	}
	cout << " " << theRnd.Seed() << endl;
	return ExitOnSuccess;
}

