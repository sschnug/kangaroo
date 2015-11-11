/*!
	@file gbrulerval.cpp
	@brief The solution validator program for golombruler.
	@details This is the source file for the solution validator for golombruler.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#include "cstdlib"
#include "iostream"
#include "algorithm"

using namespace std;


/*!
	@fn void main(int ArgC, char * ArgV[])
*/
int main (int ArgC, char * ArgV[])
{
	int Violatn;
	if (!(cin >> Violatn))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int Iteratn;
	if (!(cin >> Iteratn))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	float Time;
	if (!(cin >> Time))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	string sMemory;
	if (!(cin >> sMemory))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}
	double Memory;

	if (sMemory[sMemory.size() - 1] == 'K')
		Memory = atof(sMemory.substr(0, sMemory.size() - 1).c_str()) * 1024;
	else if (sMemory[sMemory.size() - 1] == 'M')
		Memory = atof(sMemory.substr(0, sMemory.size() - 1).c_str()) * 1024 * 1024;
	else if (sMemory[sMemory.size() - 1] == 'G')
		Memory = atof(sMemory.substr(0, sMemory.size() - 1).c_str()) * 1024 * 1024 * 1024;
	else 
		Memory = atof(sMemory.c_str());
	
	int Tabu; 
	if (!(cin >> Tabu))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int Tick; 
	if (!(cin >> Tick))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int Length; 
	if (!(cin >> Length))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	bool Infeasible = true;
	if (!Violatn)
	{
		Infeasible = false;
		int * Ruler = new int[Tick];
		int * Diffs = new int[Tick *(Tick - 1)/2];

		for(int Idx = 0; Idx < Tick; Idx++)
		{
			if (!(cin >> Ruler[Idx]) || Ruler[Idx] < 0 || Ruler[Idx] > Length)	// || (Idx && Ruler[Idx] <= Ruler[Idx - 1]))
			{																	//	commented to accept unorder ticks.
				cout << "nil" << endl;	
				delete [] Ruler;
				delete [] Diffs;
				return EXIT_SUCCESS;
			}
		}

		for(int Idx = 0, Idx1 = 0; Idx1 < Tick - 1; Idx1++)
			for(int Idx2 = Idx1 + 1; Idx2 < Tick; Idx2++)
				Diffs[Idx++] = abs(Ruler[Idx2] - Ruler[Idx1]);

		sort(Diffs, Diffs + Tick * (Tick - 1) / 2);	 
	
		for(int Idx = 1; Idx < Tick * (Tick - 1) / 2; Idx++)
			if (Diffs[Idx - 1] == Diffs[Idx])
			{
				Infeasible = true;
				break;
			}
		delete [] Ruler;
		delete [] Diffs;
	}
	cout << Violatn << " " << Iteratn << " " << Time << " " << Memory;
	cout << " " << Tabu << " " << Tick << " " << Length;
	cout << " " << Infeasible << endl;

	return EXIT_SUCCESS;
}

