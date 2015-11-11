/*!
	@file wmca.cc
	@brief Wireless mesh channel allocation main source file.
	@details This is the main source file for the wireless mesh channel allocation problem.
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@date 10.05.2012 QRL NICTA www.nicta.com.au
*/

#include "examples/examples.hpp"
#include <fstream>

/*!
	@brief A function to solve wireless mesh channel allocation problem.
	@details This function solves  wireless mesh channel allocation problem.
*/
int WMCA(int ArgC, char * ArgV[])
{
	if (ArgC <= 2)
	{
		cerr << endl;
		cout << "Wireless Mesh Channel Allocation Problem" << endl << endl;
		cerr << "Usage:" << endl;
		cerr << ArgV[0] << " -n Radios -k Channels -i MaxIter [-t TabuLength -s RandomSeed]" << endl << endl;
		cerr << "Input:" << endl;
		cerr << "NodeCount LinkCount ConflictCount" << endl << endl;
		cerr << "First in each line, ZeroBasedIndex LinkStartNode LinkEndNode" << endl;
		cerr << "Next in each line, ZeroBasedIndex ConflictLink1 ConflictLink2" << endl << endl;
		cerr << "Output:" << endl;
		cerr << "BestViolation IterationCount Run-Time MemoryUsage" << endl;
		cerr << "TabuLength Interfaces Channels NodeCount LinkCount ConflictCount [BestInterference]" << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	Dim RadioPerNode = 0;				//	Number of radio per node in the network.
	Dim ChannelPerRadio = 0;			//	Number of channels per radio at each node.
	Rnd theRnd;							//	Random number generator

	Dim TabuLength = 0;					//	Tabu length for constraint based local search.
	Dim MaxIteration = 0;				//	Maximum iteration for local search algorithm.

	Dim NodeCount = 0;					//	Number of nodes in the network.
	Dim LinkCount = 0;					//	Number of links between nodes in the network
	Dim ConflictCount = 0;				//	Number of link pairs that conflict with each other.

	for(Idx tIdx = 2; tIdx < castIdx(ArgC); ++tIdx)
	{
		if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'n')
			RadioPerNode = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'k')
			ChannelPerRadio = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 'i')
			MaxIteration = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 't')
			TabuLength = parseN(ArgV[tIdx+1]);
		else if (ArgV[tIdx][0] == '-' && ArgV[tIdx][1] == 's')
			theRnd.seed(parseN(ArgV[tIdx+1]));
	}

	if(!RadioPerNode || !ChannelPerRadio || !MaxIteration)
	{
		cerr << endl;
		cerr << "Error in commandline parameter/value. Run only with parameter " << ArgV[1] << " to see usage." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	std::ifstream fin(ArgV[2]);

	fin >> NodeCount;
	fin >> LinkCount;
	fin >> ConflictCount;

	if(!NodeCount || !LinkCount || !ConflictCount)
	{
		cerr << endl;
		cerr << "Error in input file." << endl;
		cerr << endl;
		return ExitOnFailure;
	}

	b1<t2<Idx,Idx>,xmm> Links;		//	The links each comprising a pair of nodes.
	b1<t2<Idx,Idx>,xmm > Conflicts;	//	The conflicts each comprising a pair of links.
	rl<b1<Idx,xmm>,xmm > NodeLinks;	//	The links incidients on a node in the network.

 	for(Idx tIdx = 0; tIdx < NodeCount; ++tIdx)
		NodeLinks.insertMem();

//	cout << NodeCount << " " << LinkCount << " " << ConflictCount << endl;

	for (Idx tIdx = 0; tIdx < LinkCount; ++tIdx)
	{
		Idx LinkIdx, FirstNode, SecondNode;
		fin >> LinkIdx >> FirstNode >> SecondNode;

		Warn(tIdx != LinkIdx, eIndexMismatch);
		Warn(FirstNode >= NodeCount, eInvalidIndex);
		Warn(SecondNode >= NodeCount, eInvalidIndex);

		Links.insertMem(t2<Idx,Idx>(FirstNode, SecondNode));
		NodeLinks[FirstNode].insertMem(LinkIdx);
		NodeLinks[SecondNode].insertMem(LinkIdx);
//		cout << LinkIdx << " " << FirstNode << " " << SecondNode << endl;
	}
	for (Idx tIdx = 0; tIdx < ConflictCount; ++tIdx)
	{
		Idx ConflictIdx, FirstLink, SecondLink;
		fin >> ConflictIdx >> FirstLink >> SecondLink;
		Warn(tIdx != ConflictIdx, eIndexMismatch);
		Warn(FirstLink >= LinkCount, eInvalidIndex);
		Warn(SecondLink >= LinkCount, eInvalidIndex);
		Conflicts.insertMem(t2<Idx,Idx>(FirstLink, SecondLink));
//		cout << ConflictIdx << " " << FirstLink << " " << SecondLink << endl;
	}

	Sys & tSys = Sys::refm(Sys::def());

	EvalTi::def(tSys.SysHdl);
	HintTi::def(tSys.SysHdl);
	QcSv2Tabu::def(tSys.SysHdl, TabuLength);

	b1<Prm,kmm> 		LinkVars(LinkCount);		//	Variable representing links.
	for (Idx LinkIdx = 0; LinkIdx < LinkCount; ++LinkIdx)
		LinkVars[LinkIdx] = Prm(Tv,StatRangeVarVi::def(tSys.SysHdl, 0, ChannelPerRadio - 1));

	b1<Prm,kmm> tNodeAtmosts(NodeCount);
	for(Idx NodeIdx = 0; NodeIdx < NodeCount; ++NodeIdx)
	{
		b1<Prm,kmm> tChannelTicks(ChannelPerRadio);
		for(Idx ChannIdx = 0; ChannIdx < ChannelPerRadio; ++ChannIdx)
		{
			b1<Prm,kmm> tInciLinkVars(NodeLinks[NodeIdx].itemCount());
			for(Idx LinkIdx = 0; LinkIdx < NodeLinks[NodeIdx].itemCount(); ++LinkIdx)
				tInciLinkVars[LinkIdx] = Prm(Tf, UeqsXiFeVi::def(Xv, tSys.SysHdl,
					LinkVars[NodeLinks[NodeIdx][LinkIdx]], UeqsXiFeVi::bind(ChannIdx)));
			tChannelTicks[ChannIdx] = Prm(Tf, OrsXiFeVi::def(Xv, tSys.SysHdl,
									tInciLinkVars.items(), tInciLinkVars.itemCount()));
		}
		tNodeAtmosts[NodeIdx] = Prm(Tf, UleuXiFcMi::def(Xv, tSys.SysHdl,
					Prm(Tf, SumXiFeVi::def(Xv, tSys.SysHdl, tChannelTicks.items(), ChannelPerRadio)),
					UleuXiFcMi::bind(RadioPerNode)), MasM | MasEn);
	}

	Prm SatisfyTop = Prm(Tf,SumXiEFcMiHn::def(Xm|En, tSys.SysHdl, tNodeAtmosts.items(), tNodeAtmosts.itemCount()), MasM|HnAsHn|RoHn);

	b1<Prm,kmm>			ConflictTests(ConflictCount);	// 	Result for each given conflicting pair of links.
	for(Idx ConflIdx = 0; ConflIdx < ConflictCount; ++ConflIdx)
	{
		Idx FirstLink = Conflicts[ConflIdx].First;
		Idx SecondLink = Conflicts[ConflIdx].Second;

		ConflictTests[ConflIdx] = Prm(Tf, BeqsXiFcMi::def(Xv, tSys.SysHdl, LinkVars[FirstLink], LinkVars[SecondLink]), MasM|MasEn);
	}
	Prm MinimiseTop = Prm(Tf, SumXiEFcMiHn::def(Xm|En, tSys.SysHdl, ConflictTests.items(), ConflictTests.itemCount()), MasM|HnAsHn);

	Prm Tops[2] = {SatisfyTop, MinimiseTop};

	Prm CombinedTop = Prm(Tf, SumXiFcMi::def(Xm, tSys.SysHdl, Tops, 2));
//	Prm CombinedTop = Prm(Tf, SumXiHFcMiHn::def(Xm|Hn, tSys.SysHdl, Tops, 2), MasM|HnAsHn|RoHn);

	Prm SatisfyHeap = Prm(Tf, Sv2TabuMaxHeapHiFrHi::def(tSys.SysHdl, SatisfyTop));
	Hdl SatisfyVarSelc = RankedHintVar1Sp::def(tSys.SysHdl, SatisfyHeap);
	Hdl SatisfyValSelc = MinVal1StatRangeSdViZi::def(Zm, tSys.SysHdl, SatisfyTop);

	Prm MinimiseHeap = Prm(Tf, Sv2TabuMaxHeapHiFrHi::def(tSys.SysHdl, MinimiseTop));
	Hdl MinimiseVarSelc = RankedHintVar1Sp::def(tSys.SysHdl, MinimiseHeap);
	Hdl CombinedValSelc = MinVal1StatRangeSdViZi::def(Zm, tSys.SysHdl, CombinedTop);

	tSys.initialiseVarsStatRand(theRnd);

	Refm(tSatisfyTop, SumXiEFcMiHn, tSys.SysHdl, SatisfyTop.TermHdl);
	Refm(tMinimiseTop, SumXiEFcMiHn, tSys.SysHdl, MinimiseTop.TermHdl);
//	Refm(tCombinedTop, SumXiFcMi, tSys.SysHdl, CombinedTop.TermHdl);

	#if CompLazyHalf
	tSatisfyTop.require(true);
	#endif

	Int BestSat = tSatisfyTop.MetricRec().CurrData();
	Int BestOpt = (BestSat) ? MaxInt : tMinimiseTop.MetricRec().CurrData();

	while(tSys.ExecClk() < MaxIteration && BestOpt > 0)
	{
		#if CompLazyFull
		Term::performExecIncr(tSatisfyTop);
		#endif
		if (tSatisfyTop.MetricRec().CurrData() == 0)
		{
			#if CompLazy
			Term::performExecIncr(tMinimiseTop);
			#endif
			if (BestOpt > tMinimiseTop.MetricRec().CurrData())
				BestOpt = tMinimiseTop.MetricRec().CurrData();
			Selc::selectExecuteSelc2(tSys.SysHdl, MinimiseVarSelc, CombinedValSelc, theRnd);
		}
		else
		{
			Selc::selectExecuteSelc2(tSys.SysHdl, SatisfyVarSelc, SatisfyValSelc, theRnd);
		}
		if (tSatisfyTop.MetricRec().CurrData() < BestSat)
			BestSat = tSatisfyTop.MetricRec().CurrData();
	}

	cout << BestSat << " " << tSys.ExecClk() << " " << getTime() << " " << getMemory() << endl;
	cout << TabuLength << " " << RadioPerNode << " " << ChannelPerRadio << " " << NodeCount << " " << LinkCount << " " << ConflictCount;
	if (!BestSat)
		cout << " " << BestOpt;
	cout << " " << theRnd.Seed() << endl;

	return ExitOnSuccess;
}
