/*!
	@file msquareval.cpp
	@brief The solution validator program for msquare.
	@details This is the source file for the solution validator for msquare.
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
	if (ArgC > 1)
	{
		cerr << endl << endl;
		cerr << "No commandline parameter is allowed." << endl;
		cerr << "All input are taken from stdin." << endl;
		cerr << "Specify the best-violation first." << endl;
		cerr << "Specify iteration time memory" << endl;
		cerr << "Specifiy tabu-setting, square-dimension." << endl;
		cerr << "Specify the cell values in row-major wise if violation 0." << endl;
		cerr << "Output in the following order:" << endl;
		cerr << "violation iteration time memory tabu-setting square-dimension" << endl;
		cerr << "ValidSolution? MatchingWithViolation?" << endl;		
				
		cerr << endl << endl;
		exit(0);
	}

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

	int Dimen; 
	if (!(cin >> Dimen))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	bool Infeasible = true;
	if (!Violatn)
	{
		Infeasible = false;
		int * msquare = new int[Dimen * Dimen];
		for(int Idx = 0; Idx < Dimen * Dimen; Idx++)
			if (!(cin >> msquare[Idx]) || msquare[Idx] < 0 || msquare[Idx] > Dimen * Dimen)
			{
				cout << "nil" << endl;	
				delete [] msquare;
				return EXIT_SUCCESS;
			}
	
		for(int Idx1 = 0; !Infeasible && Idx1 < Dimen; Idx1++)
		{
			int Sum = 0;
			for(int Idx2 = 0; Idx2 < Dimen; Idx2++)
				Sum += msquare[Idx1 * Dimen + Idx2];
			if (Sum != Dimen * (Dimen * Dimen + 1) / 2)
				Infeasible = true;
		}

		for(int Idx1 = 0; !Infeasible && Idx1 < Dimen; Idx1++)
		{
			int Sum = 0;
			for(int Idx2 = 0; Idx2 < Dimen; Idx2++)
				Sum += msquare[Idx2 * Dimen + Idx1];
			if (Sum != Dimen * (Dimen * Dimen + 1) / 2)
				Infeasible = true;
		}

		int Sum = 0;
		for(int Idx = 0; Idx < Dimen; Idx++)
			Sum += msquare[Idx * Dimen + Idx];
		if (Sum != Dimen * (Dimen * Dimen + 1) / 2)
			Infeasible = true;

		Sum = 0;
		for(int Idx = 0; Idx < Dimen; Idx++)
			Sum += msquare[Idx * Dimen + Dimen - Idx - 1];
		if (Sum != Dimen * (Dimen * Dimen + 1) / 2)
			Infeasible = true;

		sort(msquare, msquare + Dimen * Dimen);
		for(int Idx = 1; !Infeasible && Idx < Dimen * Dimen; Idx++)
			if (msquare[Idx - 1] == msquare[Idx]) 
				Infeasible = true;

		delete [] msquare;
	}

	bool Satisfy = !Violatn;
	cout << Violatn << " " << Iteratn << " " << Time << " " << Memory;
	cout << " " << Tabu << " " << Dimen;
	cout << " " << Infeasible << endl;

	return EXIT_SUCCESS;
}

