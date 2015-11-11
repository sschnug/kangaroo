/*!
	@file gcolorval.cpp
	@brief The solution validator program for graphcolor.
	@details This is the source file for the solution validator for graphcolor.
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
	float Memory;

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

	int Color; 
	if (!(cin >> Color))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	float Prob; 
	if (!(cin >> Prob))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int Vertex; 
	if (!(cin >> Vertex))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int Edge; 
	if (!(cin >> Edge))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int * Matrix = new int[Vertex* Vertex];
	for(int Idx1 = 0; Idx1 < Vertex; Idx1++)
		for(int Idx2 = 0; Idx2 < Vertex; Idx2++)
			Matrix[Idx1 * Vertex + Idx2] = 0;
	
	for(int Idx = 0; Idx < Edge; Idx++)
	{
		int Start, End;
		if (!(cin >> Start) || Start < 1 || Start > Vertex || !(cin >> End) || End < 1 || End > Vertex)
		{
			cout << "nil" << endl;	
			delete [] Matrix;
			return EXIT_SUCCESS;
		}
		Matrix[(Start-1)*Vertex + (End - 1)] = 1;
		Matrix[(End -1)*Vertex + (Start -1)] = 1;
	}

	bool Infeasible = true;
	if (!Violatn)
	{
		Infeasible = false;
		int * Label = new int[Vertex];
		for(int Idx = 0; Idx < Vertex; Idx++)
			if (!(cin >> Label[Idx]) || Label[Idx] < 1 || Label[Idx] > Color) 
			{
				cout << "nil" << endl;	
				delete [] Matrix;
				delete [] Label;
				return EXIT_SUCCESS;
			}
		
			for(int Idx1 = 0; !Infeasible && Idx1 < Vertex; Idx1++)
				for(int Idx2 = 0; !Infeasible && Idx2 < Vertex; Idx2++)
					if (Matrix[Idx1 * Vertex + Idx2])
						Infeasible = (Label[Idx1] == Label[Idx2]);
		delete [] Label;
	}

	cout << Violatn << " " << Iteratn << " ";
	cout << Time << " " << Memory << " " << Tabu << " "<< Color << " " << Prob << " " << Vertex << " " << Edge;
	cout << " " << Infeasible << endl;

	delete [] Matrix;
	return EXIT_SUCCESS;
}

