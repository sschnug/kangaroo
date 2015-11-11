/*!
	@file nqueenval.cpp
	@brief The solution validator program for n-queen problem.
	@details This is the source file of the solution validator for n-queen problem
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
		cerr << "Specify violation iteration time memory" << endl;
		cerr << "Specifiy the number of queens." << endl;
		cerr << "Specify the queen positions." << endl;
		cerr << "Output in the following order:" << endl;
		cerr << "violation iteration time memory queen-count" << endl;
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

	int Queen; 
	if (!(cin >> Queen))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	bool Infeasible = true;
	if (!Violatn)
	{
		Infeasible = false;
		int * Queens = new int[Queen];
		int * Pluss = new int[Queen];
		int * Minuss = new int[Queen];

		for(int Idx = 0; Idx < Queen; Idx++)
		{
			if (!(cin >> Queens[Idx]) || Queens[Idx] < 0 || Queens[Idx] > Queen)
			{
				cout << "nil" << endl;	
				delete [] Queens;
				delete [] Pluss;
				delete [] Minuss;
				return EXIT_SUCCESS;
			}
			Pluss[Idx] = Queens[Idx] + Idx + 1;
			Minuss[Idx] = Queens[Idx] - Idx - 1;
		}

		sort(Queens, Queens + Queen);	 
		sort(Pluss, Pluss + Queen);	 
		sort(Minuss, Minuss + Queen);	 
	
		for(int Idx = 1; Idx < Queen; Idx++)
			if (Queens[Idx - 1] == Queens[Idx] || Pluss[Idx - 1] == Pluss[Idx] || Minuss[Idx - 1] == Minuss[Idx])
			{
				Infeasible = true;
				break;
			}

		delete [] Queens;
		delete [] Pluss;
		delete [] Minuss;
	}

	cout << Violatn << " " << Iteratn << " ";
	cout << Time << " " << Memory << " " << Queen;
	cout << " " << Infeasible << endl;

	return EXIT_SUCCESS;
}

