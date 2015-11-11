/*!
	@file psp.cc
	@brief Protien structure prediction main source file.
	@details This is the main source file for protein structure prediction.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 10.05.2012 QRL NICTA www.nicta.com.au
*/

#include "examples/examples.hpp"


class Point
{
	public:
		Int x, y, z;
		Bll operator == (Point const & that) const
			{ return x == that.x && y == that.y && z == that.z; }
};


Hvl const calcHash(Point const & thePoint)
{
	Hvl tHvl = calcHash(thePoint.x);
	tHvl = mixHash(tHvl, calcHash(thePoint.y));
	tHvl = mixHash(tHvl, calcHash(thePoint.z));
	return tHvl;
}

Int vx[12] = { 0, 0, 0, 0, 1, 1,-1,-1, 1,-1, 1,-1};
Int vy[12] = { 1, 1,-1,-1, 0, 0, 0, 0, 1, 1,-1,-1};
Int vz[12] = { 1,-1, 1,-1, 1,-1, 1,-1, 0, 0, 0, 0};


Bll checkNeighbour(Int tx, Int ty, Int tz, Int ttx, Int tty, Int ttz)
{
	Int t = tx - ttx + ty - tty + tz - ttz;
	return t == -2 || t == 0 || t == 2;
}




/*!
	@brief A function to solve wireless mesh channel allocation problem.
	@details This function solves  wireless mesh channel allocation problem.
*/
int PSP(int ArgC, char * ArgV[])
{
	if (ArgC <= 2)
	{
		cerr << endl;
		cout << "Protein Structure Prediction Problem" << endl << endl;
		cerr << "Usage:" << endl;
		cerr << ArgV[0] << " -n ProteinLength -p ProteinHPString -f FitnessUseRatio -i MaxIter [-t TabuLength -s RandomSeed]" << endl << endl;
		cerr << "Output:" << endl;
		cerr << "BestEnergy IterationCount Run-Time MemoryUsage" << endl;
		cerr << "TabuLength" << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Dim ProteinSize = 0;				//	Size of the protein.
	Dim FitnessRatio = 0;				//	Fitness usage ratio.
	Dim MaxIteration = 0;				//	Maximum iteration for local search algorithm.
	Rnd theRnd;							//	Random number generator
	Dim TabuLength = 0;					//	Tabu length for constraint based local search.
	Dim ProteinIdx = 0;					//	Parameter index having the amino acid.

	for(Idx tIdx = 2; tIdx < castIdx(ArgC); ++tIdx)
	{
		if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'n')
			ProteinSize = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'f')
			FitnessRatio = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'i')
			MaxIteration = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 't')
			TabuLength = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'p')
			ProteinIdx = tIdx+1;
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 's')
			theRnd.seed(parseN(ArgV[tIdx+1]));
	}

	if(!MaxIteration || !ProteinIdx || !FitnessRatio)
	{
		cerr << endl;
		cerr << "Error in commandline parameter/value. Run only with parameter " << ArgV[1] << " to see usage." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	b1<Bll,kmm> AminoAcids(ProteinSize);//	Amino acid types of the amino acids.
	for(Idx tIdx = 0; tIdx < ProteinSize; ++tIdx)
		AminoAcids[tIdx] = (ArgV[ProteinIdx][tIdx] == 'H');

	Sys & tSys = Sys::refm(Sys::def());

	#if CompDnwd
		tSys.setMultiCandExec();
		#if SimulFixedFlexi
			#if SelcSimulFlexi
			tSys.setMultiFlexiSimul();
			#else
			tSys.setMultiFixedSimul();
			#endif
		#elif SimulFixedOnly
		tSys.setMultiFixedSimul();
		#elif SimulFlexiOnly
			tSys.setMultiFlexiSimul();
		#endif
	#endif
	EvalTi::def(tSys.SysHdl);
	EvalTi const & tEvalTbl = EvalTi::refc(tSys.SysHdl);
	QcSv2Tabu::def(tSys.SysHdl, TabuLength);

	b1<Prm,kmm> Xvars(ProteinSize);
	b1<Prm,kmm> Yvars(ProteinSize);
	b1<Prm,kmm> Zvars(ProteinSize);
	b1<EvalRecInt const *,kmm> XvarRecs(ProteinSize);
	b1<EvalRecInt const *,kmm> YvarRecs(ProteinSize);
	b1<EvalRecInt const *,kmm> ZvarRecs(ProteinSize);
	b1<StatRangeVarVi *,kmm> XvarPtrs(ProteinSize);
	b1<StatRangeVarVi *,kmm> YvarPtrs(ProteinSize);
	b1<StatRangeVarVi *,kmm> ZvarPtrs(ProteinSize);

	for (Idx tIdx = 0; tIdx < ProteinSize; ++tIdx)
	{
		Xvars[tIdx] = Prm(Tv,StatRangeVarVi::def(tSys.SysHdl, -2 * ProteinSize, 2 * ProteinSize));
		Yvars[tIdx] = Prm(Tv,StatRangeVarVi::def(tSys.SysHdl, -2 * ProteinSize, 2 * ProteinSize));
		Zvars[tIdx] = Prm(Tv,StatRangeVarVi::def(tSys.SysHdl, -2 * ProteinSize, 2 * ProteinSize));

		XvarRecs[tIdx] = tEvalTbl.ptrcEvalRec(StatRangeVarVi::refc(tSys.SysHdl, Xvars[tIdx].TermHdl).ValueLoc());
		YvarRecs[tIdx] = tEvalTbl.ptrcEvalRec(StatRangeVarVi::refc(tSys.SysHdl, Yvars[tIdx].TermHdl).ValueLoc());
		ZvarRecs[tIdx] = tEvalTbl.ptrcEvalRec(StatRangeVarVi::refc(tSys.SysHdl, Zvars[tIdx].TermHdl).ValueLoc());

		XvarPtrs[tIdx] = StatRangeVarVi::ptrm(tSys.SysHdl, Xvars[tIdx].TermHdl);
		YvarPtrs[tIdx] = StatRangeVarVi::ptrm(tSys.SysHdl, Yvars[tIdx].TermHdl);
		ZvarPtrs[tIdx] = StatRangeVarVi::ptrm(tSys.SysHdl, Zvars[tIdx].TermHdl);
	}

	b2<Prm> Dists(ProteinSize, ProteinSize);
	for (Idx tIdx1 = 0; tIdx1 < ProteinSize - 1; ++tIdx1)
		for (Idx tIdx2 = tIdx1 + 1; tIdx2 < ProteinSize; ++tIdx2)
		{
			b1<Prm,kmm> tDist(3);
			tDist[0] = Prm(Tf, UsqrXiFeVi::def(Xv, tSys.SysHdl, Prm(Tf, BsubXiFeVi::def(Xv, tSys.SysHdl, Xvars[tIdx1], Xvars[tIdx2]))));
			tDist[1] = Prm(Tf, UsqrXiFeVi::def(Xv, tSys.SysHdl, Prm(Tf, BsubXiFeVi::def(Xv, tSys.SysHdl, Yvars[tIdx1], Yvars[tIdx2]))));
			tDist[2] = Prm(Tf, UsqrXiFeVi::def(Xv, tSys.SysHdl, Prm(Tf, BsubXiFeVi::def(Xv, tSys.SysHdl, Zvars[tIdx1], Zvars[tIdx2]))));
			Dists.item(tIdx1,tIdx2) = Prm(Tf, SumXiFeVi::def(Xv, tSys.SysHdl, tDist.items(), 3));
		}

	b1<Prm, xmm> Fhdists, Edists, Fhpdists;
	for (Idx tIdx1 = 0; tIdx1 < ProteinSize - 1; ++tIdx1)
	{
		for (Idx tIdx2 = tIdx1 + 1; tIdx2 < ProteinSize; ++tIdx2)
		{
			Fhpdists.insertMem(Dists.item(tIdx1, tIdx2));
			if (!AminoAcids[tIdx1] || !AminoAcids[tIdx2]) continue;
			Fhdists.insertMem(Dists.item(tIdx1, tIdx2));
			Edists.insertMem(Prm(Tf, UeqsXiFeVi::def(Xv, tSys.SysHdl, Dists.item(tIdx1,tIdx2), UeqsXiFeVi::bind(2))));
		}
	}

	Prm Etop = Prm(Tf, SumXiFeVi::def(Xv, tSys.SysHdl, Edists.items(), Edists.itemCount()));
	Prm Fhtop = Prm(Tf, SumXiFeVi::def(Xv, tSys.SysHdl, Fhdists.items(), Fhdists.itemCount()));
	Prm Fhptop = Prm(Tf, SumXiFeVi::def(Xv, tSys.SysHdl, Fhpdists.items(), Fhpdists.itemCount()));

//	random valid initialisation

	hsetd<Point,nmmh> AllDiff(ProteinSize);
	b1<Point,kmm> Points(ProteinSize);
	b1<Idx, kmm> AllDiffIdx(ProteinSize);

	Point tp = {0,0,0};
	Idx ti = 0;
	Points[ti] = tp;
	AllDiffIdx[ti] = AllDiff.insertItr(tp);

	while(ti < ProteinSize - 1)
	{
		Idx vn = uniform(theRnd, 12);
		tp.x = Points[ti].x + vx[vn];
		tp.y = Points[ti].y + vy[vn];
		tp.z = Points[ti].z + vz[vn];
		Cnt tc = 0;
		while (tc < 12 && AllDiff.findBll(tp))
		{
			++tc;
			Idx vni = uniform(theRnd, 12);
			tp.x = Points[ti].x + vx[vni];
			tp.y = Points[ti].y + vy[vni];
			tp.z = Points[ti].z + vz[vni];
		}
		if (tc < 12)
		{
			Points[++ti] = tp;
			AllDiffIdx[ti] = AllDiff.insertItr(tp);
		}
		else
			AllDiff.removeWithItr(AllDiffIdx[--ti]);
	}

	{
		b1<Hdl,kmm> VarHdls(3*ProteinSize);
		b1<Wrp,kmm> ValWrps(3*ProteinSize);
		for(Idx tIdx = 0; tIdx < ProteinSize; ++tIdx)
		{
			VarHdls[tIdx * 3 + 0] = Xvars[tIdx].TermHdl;
			VarHdls[tIdx * 3 + 1] = Yvars[tIdx].TermHdl;
			VarHdls[tIdx * 3 + 2] = Zvars[tIdx].TermHdl;

			ValWrps[tIdx * 3 + 0] = Wrp(Points[tIdx].x);
			ValWrps[tIdx * 3 + 1] = Wrp(Points[tIdx].y);
			ValWrps[tIdx * 3 + 2] = Wrp(Points[tIdx].z);
		}
		tSys.initialiseVarsWrap(VarHdls.items(), ValWrps.items());
	}

	Refm(tEtop, SumXiFeVi, tSys.SysHdl, Etop.TermHdl);
	Refm(tFhtop, SumXiFeVi, tSys.SysHdl, Fhtop.TermHdl);
	Refm(tFhptop, SumXiFeVi, tSys.SysHdl, Fhptop.TermHdl);

	#if CompLazyHalf
	tEtop.require(true);
	#endif

	QcSv2Tabu const & tQcSv2Tabu = QcSv2Tabu::refc(tSys.SysHdl);

	Int BestEnergy = tEtop.ValueRec().CurrData();
	while(tSys.ExecClk() < MaxIteration)
	{
		Int MinFitness = MaxInt;
		Idx MinPointIdx = InvIdx;
		Point tMinPointValue;
		for(Idx tIdx1 = 0; tIdx1 < ProteinSize; ++tIdx1)
		{
			if (tQcSv2Tabu.state(Xvars[tIdx1].TermHdl) ||
					tQcSv2Tabu.state(Yvars[tIdx1].TermHdl) ||
					tQcSv2Tabu.state(Zvars[tIdx1].TermHdl))
				continue;
			Idx kl = tIdx1 == 0 ? tIdx1 + 1: tIdx1 - 1;
			Idx kr = tIdx1 == (ProteinSize - 1)  ? tIdx1 - 1: tIdx1 + 1;

			Hdl AsgnVars[3] = { Xvars[tIdx1].TermHdl, Yvars[tIdx1].TermHdl, Zvars[tIdx1].TermHdl };
			#if SimulFixedFlexi
				#if SelcSimulFlexi
				tSys.setSimulFlexiVars(AsgnVars, 3);
				#else
				tSys.setSimulFixedVars(AsgnVars, 3);
				#endif
			#elif SimulFixedOnly
			tSys.setSimulFixedVars(AsgnVars, 3);
			#elif SimulFlexiOnly
			tSys.setSimulFlexiVars(AsgnVars, 3);
			#endif

			for(Idx tIdx2 = 0; tIdx2 < 12; ++tIdx2)
			{
				Point tPoint = { castInt(XvarRecs[kl]->CurrData() + vx[tIdx2]),
									castInt(YvarRecs[kl]->CurrData() + vy[tIdx2]),
									castInt(ZvarRecs[kl]->CurrData() + vz[tIdx2]) };

				if (AllDiff.findBll(tPoint)) continue;
				if (!checkNeighbour(tPoint.x,tPoint.y,tPoint.z,XvarRecs[kr]->CurrData(),
					YvarRecs[kr]->CurrData(),ZvarRecs[kr]->CurrData())) continue;

				tSys.setSimulMode(DiffAsgn);
				XvarPtrs[tIdx1]->simulIncrValue(tPoint.x);
				YvarPtrs[tIdx1]->simulIncrValue(tPoint.y);
				ZvarPtrs[tIdx1]->simulIncrValue(tPoint.z);
				tSys.setSimulMode(DiffProp);
				#if SimulUpwd
				tSys.propagateSimulIncr();
				#endif
				if (tSys.ExecClk() % FitnessRatio != 0)
				{
					#if SimulDnwd
					Term::performSimulIncr(tFhtop);
					#endif
					if (MinFitness > tFhtop.ValueRec().CurrData())
					{
						MinFitness = tFhtop.ValueRec().CurrData();
						MinPointIdx = tIdx1;
						tMinPointValue = tPoint;
					}
				}
				else
				{
					#if SimulDnwd
					Term::performSimulIncr(tFhptop);
					#endif
					if (MinFitness > tFhptop.ValueRec().CurrData())
					{
						MinFitness = tFhptop.ValueRec().CurrData();
						MinPointIdx = tIdx1;
						tMinPointValue = tPoint;
					}
				}
			}
		}
		if (MinPointIdx != InvIdx)
		{
			Hdl AsgnVars[3] = { Xvars[MinPointIdx].TermHdl, Yvars[MinPointIdx].TermHdl, Zvars[MinPointIdx].TermHdl };
			Wrp AsgnVals[3] = { Wrp(tMinPointValue.x), Wrp(tMinPointValue.y), Wrp(tMinPointValue.z) };
			tSys.execIncrDiffVarsWrap(AsgnVars, AsgnVals, 3);
		}
	}

	cout << BestEnergy << " " << tSys.ExecClk() << " " << getTime() << " " << getMemory() << endl;
	cout << TabuLength;
	cout << " " << theRnd.Seed() << endl;

	return ExitOnSuccess;
}
