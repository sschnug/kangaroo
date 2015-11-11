/*!
	@file sgolferval.cpp
	@brief The solution validator program for social golfer.
	@details This is the source file for the solution validator for social golfer.
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
		
	int PerGroup; 
	if (!(cin >> PerGroup))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int GroupCount; 
	if (!(cin >> GroupCount))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int WeekCount; 
	if (!(cin >> WeekCount))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int PersonCount = PerGroup * GroupCount;
	int AllocCount = WeekCount * PersonCount;

	bool Infeasible = true;
	if (!Violatn)
	{
		Infeasible = false;
		int * Alloc = new int[AllocCount];
		for(int Idx = 0; Idx < AllocCount; Idx++)
			if (!(cin >> Alloc[Idx]) || Alloc[Idx] < 0 || Alloc[Idx] >= GroupCount)
			{
				cout << "nil" << endl;	
				delete [] Alloc;
				return EXIT_SUCCESS;
			}

		for(int j = 0; !Infeasible && j < WeekCount; j++)
			for(int k = 0; !Infeasible && k < GroupCount; k++)
				{
					int PerCount = 0;
					for(int i = 0; i < PersonCount; i++)
						if (Alloc[j * PersonCount + i] == k)
							PerCount++;
					if (PerCount != PerGroup) Infeasible = true;
				}

		for(int i = 0; !Infeasible && i < PersonCount; i++)
			for(int l = i + 1; !Infeasible && l < PersonCount; l++)
			{
				int MeetCount = 0;
				for(int j =0; !Infeasible && j < WeekCount; j++)
				{
					if (Alloc[j * PersonCount +i] == Alloc[j * PersonCount + l])
					{
						MeetCount++;
						if (MeetCount > 1) Infeasible = true;
					}
				}			
			}
		delete [] Alloc;
	}

	cout << Violatn << " " << Iteratn << " " << Time << " " << Memory;
	cout << " " << 	Tabu << " " << PerGroup << " " << GroupCount << " " << WeekCount;
	cout << " " << Infeasible << endl;

	return EXIT_SUCCESS;
}

