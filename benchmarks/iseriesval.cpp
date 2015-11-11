/*!
	@file iseriesval.cpp
	@brief The solution validator program for all interval series.
	@details This is the source file for the solution validator for all interval series.
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
		int * Series = new int[Length];
		int * Diffs = new int[Length - 1];

		for(int Idx = 0; Idx < Length; Idx++)
		{
			if (!(cin >> Series[Idx]) || Series[Idx] < 0 || Series[Idx] > Length - 1)
			{
				cout << "nil" << endl;	
				delete [] Series;
				delete [] Diffs;
				return EXIT_SUCCESS;
			}
			if (Idx)
				Diffs[Idx - 1] = abs(Series[Idx]  - Series[Idx -1]);
		}

		sort(Series, Series + Length);	 
		sort(Diffs, Diffs + Length - 1);	 
	
		for(int Idx = 1; Idx < Length; Idx++)
			if (Series[Idx - 1] == Series[Idx])
			{
				Infeasible = true;
				break;
			}

		for(int Idx = 1; Idx < Length - 1; Idx++)
			if (Diffs[Idx - 1] == Diffs[Idx])
			{
				Infeasible = true;
				break;
			}
		delete [] Series;
		delete [] Diffs;
	}

	cout << Violatn << " " << Iteratn << " " << Time << " " << Memory;
	cout << " " << Tabu << " " << Length;
	cout << " " << Infeasible << endl;

	return EXIT_SUCCESS;
}

