/*!
	@file emu.cpp
	@brief The main source file for emu.
	@details This is the main source file for emu.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/



#include "cppl/idx.hpp"

using namespace emu;

/*
template class b1<N, xmm>;
template class b2<N>;
template class b3<N>;
template class cl<N, xmm>;

template class hm<N,N, xmmh>;
template class hmc<N,N, xmmh>;
template class hmd<N,N, xmmh>;
template class hmf<N,N, xmmh>;

template class hs<N, xmmh>;
template class hsc<N, xmmh>;
template class hsd<N, xmmh>;
template class hsf<N, xmmh>;

template class qc<N, xmmm>;
template class qh<N, lt<N>, xmmm>;
template class qhf<N, N, lt<N>, xmmm>;
template class qhp<N, N, lt<N>, xmmm>;

template class lf<N, xmm>;
template class lc<N, xmm>;
template class ll<N, xmm>;
template class lp<N, xmm>;
template class lu<N, xmm>;


template class ri<N, xmm>;
template class rl<b1<N,xmm>, xmm>;

template class t2<N,N>;
template class t2a<N,N>;
template class t2b<N,N>;
template class t3<N,N,N>;
template class t4<N,N,N,N>;
*/

/*!
	The main function of the program for emu.
	@param ArgC The number of command-line arguments.
	@param ArgV The command-line arguments themselves.
*/
int main(int ArgC, char * ArgV[])
{
	try
	{
//		N M = 50;
//		N Count = 100000000u;
//		N Sum = 0;
//		R t0 = getTime();
//		{
//			kmm tNmem;
//			pile<N,xmm> tPile(Count);
//			for(Itr tItr = 0; tItr < Count; ++tItr)
//				tPile.insertMem(tItr);
////					tPile[tItr] = tItr;
//			cerr << tPile.itemCount() << endl;
//			for(Idx tIdx = 0; tIdx < M; ++tIdx)
//			{
//				for(Itr tItr = 0; tItr < tPile.itemCount(); ++tItr)
//					Sum += tPile[tItr];
//			}
//		}
//		R t1 = getTime();
//		{
//			xpile<N> Oile;
//			for(Itr tItr = 0; tItr < Count; ++tItr)
//				Oile.insertMem(tItr);
//				Oile[tItr] = tItr;
//			cerr << Oile.size() << endl;
//			for(Idx tIdx = 0; tIdx < M; ++tIdx)
//			{
//				for(Itr tItr = 0; tItr < Oile.size(); ++tItr)
//					Sum += Oile[tItr];
//			}
//		}
//		R t2 = getTime();
////		{
////			std::vector<N> Vile;
//////			Vile.resize(Count);
////			for(Itr tItr = 0; tItr < Count; ++tItr)
////				Vile.push_back(tItr);
//////				Vile[tItr] = tItr;
////			cerr << Vile.size() << endl;
////			for(Idx tIdx = 0; tIdx < M; ++tIdx)
////			{
////				for(Itr tItr = 0; tItr < Vile.size(); ++tItr)
////					Sum += Vile[tItr];
////			}
////		}
//		R t3 = getTime();
//		cerr << Sum << " Time: " << t1 - t0 << " " << t2 - t1 << " " << t3 - t2 << endl;

	}
	catch(...) { throw; };
//	catch(Err & theErr)
//	{
//		cerr << endl << "Error: " << theErr() << endl;
//		return ExitOnFailure;
//	}
	return ExitOnSuccess;
}
