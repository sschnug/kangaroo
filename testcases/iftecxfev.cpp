/*!
	@file iftecxfev.cpp
	@brief The test file file for IfteCXFeV.
	@details This is the implementation file for IfteCXFeV.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
*/



#include "test/tests.hpp"



openKangarooSpace

int testIfteCXFeV(int ArgC, char * ArgV[])
{
//	Itn I = 3, J = 3;
	Rnd theRnd(1330538672);
//	Rnd theRnd;
	Itn I = parseN(ArgV[1]);
	Itn J = parseN(ArgV[2]);

	cout << endl << "Seed : " << theRnd.Seed() << endl;

	Hdl tSys = Sys::def();
	EvalTi::def(tSys);
	EvalTb::def(tSys);

	#define N 15
	xb<Prm> tVars(N);

	tVars.append(RngVi::def(tSys, 1, 9));
	tVars.append(RngVi::def(tSys, 1, 9));
	tVars.append(StdVb::def(tSys));
	tVars.append(RngVi::def(tSys, 1, 9));
	tVars.append(RngVi::def(tSys, 1, 9));
	tVars.append(StdVb::def(tSys));

	tVars.append(StdVb::def(tSys));


	tVars.append(RngVi::def(tSys, 1, 9));
	tVars.append(RngVi::def(tSys, 1, 9));
	tVars.append(StdVb::def(tSys));
	tVars.append(RngVi::def(tSys, 1, 9));
	tVars.append(RngVi::def(tSys, 1, 9));
	tVars.append(StdVb::def(tSys));

	tVars.append(StdVb::def(tSys));


	tVars.append(StdVb::def(tSys));

	Prm tIfs[7];

	tIfs[0] = IfteXbYiFeVi::def(Xv|Yv, tSys, tVars[2], tVars[0], tVars[1]);
	tIfs[1] = IfteXbYiFeVi::def(Xv|Yv, tSys, tVars[5], tVars[3], tVars[4]);
	tIfs[2] = IfteXbYiFeVi::def(Xv|Yv, tSys, tVars[6], tIfs[0], tIfs[1]);

	tIfs[3] = IfteXbYiFeVi::def(Xv|Yv, tSys, tVars[9], tVars[7], tVars[8]);
	tIfs[4] = IfteXbYiFeVi::def(Xv|Yv, tSys, tVars[12], tVars[10], tVars[11]);
	tIfs[5] = IfteXbYiFeVi::def(Xv|Yv, tSys, tVars[13], tIfs[3], tIfs[4]);

	tIfs[6] = IfteXbYiFeVi::def(Xv|Yv, tSys, tVars[14], tIfs[2], tIfs[5]);

	cout << "Handle: " << endl;
	cout << tVars[0].TermHdl << " ";\
	cout << tVars[1].TermHdl << " ";\
	cout << tVars[2].TermHdl << " ";\
	cout << tIfs[0].TermHdl << "  ";\
	cout << tVars[3].TermHdl << " ";\
	cout << tVars[4].TermHdl << " ";\
	cout << tVars[5].TermHdl << " ";\
	cout << tIfs[1].TermHdl << "  ";\
	cout << tVars[6].TermHdl << " ";\
	cout << tIfs[2].TermHdl << "  ";\

	cout << tVars[7].TermHdl << " ";\
	cout << tVars[8].TermHdl << " ";\
	cout << tVars[9].TermHdl << " ";\
	cout << tIfs[3].TermHdl << "  ";\
	cout << tVars[10].TermHdl << " ";\
	cout << tVars[11].TermHdl << " ";\
	cout << tVars[12].TermHdl << " ";\
	cout << tIfs[4].TermHdl << "  ";\
	cout << tVars[13].TermHdl << " ";\
	cout << tIfs[5].TermHdl << "  ";\

	cout << tVars[14].TermHdl << " ";\
	cout << tIfs[6].TermHdl << "  ";\
	cout << endl;

	#define XOUTPUT \
		cout << endl << "e ";\
		cout << v0.ValueRec().CurrData() << " ";\
		cout << v1.ValueRec().CurrData() << " ";\
		cout << v2.ValueRec().CurrData() << " ";\
		cout << i0.ValueRec().CurrData() << "  ";\
		cout << v3.ValueRec().CurrData() << " ";\
		cout << v4.ValueRec().CurrData() << " ";\
		cout << v5.ValueRec().CurrData() << " ";\
		cout << i1.ValueRec().CurrData() << "  ";\
		cout << v6.ValueRec().CurrData() << " ";\
		cout << i2.ValueRec().CurrData() << "  ";\
		cout << v7.ValueRec().CurrData() << " ";\
		cout << v8.ValueRec().CurrData() << " ";\
		cout << v9.ValueRec().CurrData() << " ";\
		cout << i3.ValueRec().CurrData() << "  ";\
		cout << v10.ValueRec().CurrData() << " ";\
		cout << v11.ValueRec().CurrData() << " ";\
		cout << v12.ValueRec().CurrData() << " ";\
		cout << i4.ValueRec().CurrData() << "  ";\
		cout << v13.ValueRec().CurrData() << " ";\
		cout << i5.ValueRec().CurrData() << "  ";\
		cout << v14.ValueRec().CurrData() << " ";\
		cout << i6.ValueRec().CurrData() << "  i ";\
		cout << i6.ValueRec().PrevBuff << "  ";\
		cout << i6.ValueRec().CurrBuff << "  ";\
		cout << i6.ValueRec().NextBuff << "  ";\
		cout << i6.ValueRec().PrevClk << "  ";\
		cout << i6.ValueRec().NextClk << "  v ";\
		cout << v14.ValueRec().PrevBuff << "  ";\
		cout << v14.ValueRec().CurrBuff << "  ";\
		cout << v14.ValueRec().NextBuff << "  ";\
		cout << v14.ValueRec().PrevClk << "  ";\
		cout << v14.ValueRec().NextClk << "  ";\
		cout << ss.ExecClk() << "  ";

	#define SOUTPUT \
		cout << endl << "s ";\
		cout << v0.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << v1.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << v2.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << i0.ValueRec().NextData(ss.SimulClk()) << "  ";\
		cout << v3.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << v4.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << v5.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << i1.ValueRec().NextData(ss.SimulClk()) << "  ";\
		cout << v6.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << i2.ValueRec().NextData(ss.SimulClk()) << "  ";\
		cout << v7.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << v8.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << v9.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << i3.ValueRec().NextData(ss.SimulClk()) << "  ";\
		cout << v10.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << v11.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << v12.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << i4.ValueRec().NextData(ss.SimulClk()) << "  ";\
		cout << v13.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << i5.ValueRec().NextData(ss.SimulClk()) << "  ";\
		cout << v14.ValueRec().NextData(ss.SimulClk()) << " ";\
		cout << i6.ValueRec().NextData(ss.SimulClk()) << "  i ";\
		cout << i6.ValueRec().PrevBuff << "  ";\
		cout << i6.ValueRec().CurrBuff << "  ";\
		cout << i6.ValueRec().NextBuff << "  ";\
		cout << i6.ValueRec().PrevClk << "  ";\
		cout << i6.ValueRec().NextClk << "   v ";\
		cout << v14.ValueRec().PrevBuff << "  ";\
		cout << v14.ValueRec().CurrBuff << "  ";\
		cout << v14.ValueRec().NextBuff << "  ";\
		cout << v14.ValueRec().PrevClk << "  ";\
		cout << v14.ValueRec().NextClk << "  ";\
		cout << ss.SimulClk() << "  ";


	#define OUTPUT \
		cout << endl;\
		cout << v0.ValueRec().CurrData() << " ";\
		cout << v1.ValueRec().CurrData() << " ";\
		cout << v2.ValueRec().CurrData() << " ";\
		cout << i0.ValueRec().CurrData() << "." << i0.backlog() << "  ";\
		cout << v3.ValueRec().CurrData() << " ";\
		cout << v4.ValueRec().CurrData() << " ";\
		cout << v5.ValueRec().CurrData() << " ";\
		cout << i1.ValueRec().CurrData() << "." << i1.backlog() << "  ";\
		cout << v6.ValueRec().CurrData() << " ";\
		cout << i2.ValueRec().CurrData() << "." << i2.backlog() <<"  ";\
		cout << v7.ValueRec().CurrData() << " ";\
		cout << v8.ValueRec().CurrData() << " ";\
		cout << v9.ValueRec().CurrData() << " ";\
		cout << i3.ValueRec().CurrData() << "." << i3.backlog() <<"  ";\
		cout << v10.ValueRec().CurrData() << " ";\
		cout << v11.ValueRec().CurrData() << " ";\
		cout << v12.ValueRec().CurrData() << " ";\
		cout << i4.ValueRec().CurrData() << "." << i4.backlog() <<"  ";\
		cout << v13.ValueRec().CurrData() << " ";\
		cout << i5.ValueRec().CurrData() << "." << i5.backlog() <<"  ";\
		cout << v14.ValueRec().CurrData() << " ";\
		cout << i6.ValueRec().CurrData() << "." << i6.backlog() <<"  ";

	#define FUNCTION \
		if (i6.ValueRec().CurrData() !=  \
				(\
					v14.ValueRec().CurrData() ? \
					(\
						v6.ValueRec().CurrData() ? \
						(v2.ValueRec().CurrData() ? v0.ValueRec().CurrData() : v1.ValueRec().CurrData()) : \
						(v5.ValueRec().CurrData() ? v3.ValueRec().CurrData() : v4.ValueRec().CurrData()) \
					) :\
					(\
						v13.ValueRec().CurrData() ? \
						(v9.ValueRec().CurrData() ? v7.ValueRec().CurrData() : v8.ValueRec().CurrData()) : \
						(v12.ValueRec().CurrData() ? v10.ValueRec().CurrData() : v11.ValueRec().CurrData()) \
					)\
				)\
			)\
		{ ++E; cerr  << " E " << ss.ExecClk(); }

	#define SFUNCTION \
		if (i6.ValueRec().NextData(ss.SimulClk()) !=  \
				(\
					v14.ValueRec().NextData(ss.SimulClk()) ? \
					(\
						v6.ValueRec().NextData(ss.SimulClk()) ? \
						(v2.ValueRec().NextData(ss.SimulClk()) ? v0.ValueRec().NextData(ss.SimulClk()) : v1.ValueRec().NextData(ss.SimulClk())) : \
						(v5.ValueRec().NextData(ss.SimulClk()) ? v3.ValueRec().NextData(ss.SimulClk()) : v4.ValueRec().NextData(ss.SimulClk())) \
					) :\
					(\
						v13.ValueRec().NextData(ss.SimulClk()) ? \
						(v9.ValueRec().NextData(ss.SimulClk()) ? v7.ValueRec().NextData(ss.SimulClk()) : v8.ValueRec().NextData(ss.SimulClk())) : \
						(v12.ValueRec().NextData(ss.SimulClk()) ? v10.ValueRec().NextData(ss.SimulClk()) : v11.ValueRec().NextData(ss.SimulClk())) \
					)\
				)\
			)\
		{ ++S; cerr << " S " << ss.ExecClk() << " " << ss.SimulClk(); }


	RefHdl(v0, Vi, tSys, tVars[0].TermHdl);
	RefHdl(v1, Vi, tSys, tVars[1].TermHdl);
	RefHdl(v2, Vb, tSys, tVars[2].TermHdl);
	RefHdl(v3, Vi, tSys, tVars[3].TermHdl);
	RefHdl(v4, Vi, tSys, tVars[4].TermHdl);
	RefHdl(v5, Vb, tSys, tVars[5].TermHdl);
	RefHdl(v6, Vb, tSys, tVars[6].TermHdl);

	RefHdl(v7, Vi, tSys, tVars[7].TermHdl);
	RefHdl(v8, Vi, tSys, tVars[8].TermHdl);
	RefHdl(v9, Vb, tSys, tVars[9].TermHdl);
	RefHdl(v10, Vi, tSys, tVars[10].TermHdl);
	RefHdl(v11, Vi, tSys, tVars[11].TermHdl);
	RefHdl(v12, Vb, tSys, tVars[12].TermHdl);
	RefHdl(v13, Vb, tSys, tVars[13].TermHdl);

	RefHdl(v14, Vb, tSys, tVars[14].TermHdl);

	RefHdl(i0, FeVi, tSys, tIfs[0].TermHdl);
	RefHdl(i1, FeVi, tSys, tIfs[1].TermHdl);
	RefHdl(i2, FeVi, tSys, tIfs[2].TermHdl);
	RefHdl(i3, FeVi, tSys, tIfs[3].TermHdl);
	RefHdl(i4, FeVi, tSys, tIfs[4].TermHdl);
	RefHdl(i5, FeVi, tSys, tIfs[5].TermHdl);
	RefHdl(i6, FeVi, tSys, tIfs[6].TermHdl);

	Sys const & ss = Sys::ref(tSys);

	Cnt E = 0, S = 0;
	Sys::execAnewRndVars(tSys, theRnd);

	#if CompLazy
	Sys::setFuncRequired(tSys, tIfs[6].TermHdl, true);
	#endif

//	XOUTPUT
	FUNCTION
	cout << endl << endl;
	while(ss.ExecClk() <= I)
	{

		Sys::execDiffRndVar(tSys, theRnd);
		XOUTPUT
		FUNCTION
		for(Idx tIdx = 0; tIdx < J; ++tIdx)
		{
//			Sys::simulAnewRndVars(tSys, theRnd);
			Sys::simulDiffRndVar(tSys, theRnd);
			#if SimulDnwd
//			Sys::simulAnew(tSys, tIfs[6].TermHdl);
			Sys::simulIncr(tSys, tIfs[6].TermHdl);
			#endif
//			SOUTPUT
			SFUNCTION
		}
	}
	cout << endl << "E: " << E << " S: " << S << endl;
	cout << "Time: " << getTime() << " Memory: " << getMemory() << endl;
	return 0;
}


closeKangarooSpace
