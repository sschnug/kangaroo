/*!
	@file vloadingval.cpp
	@brief The solution validator program for vesselloading.
	@details This is the source file for the solution validator for vesselloading.
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

	int Width; 
	if (!(cin >> Width))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int MaxDim; 
	if (!(cin >> MaxDim))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int MinDim; 
	if (!(cin >> MinDim))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

/*	int MaxCVR; 
	if (!(cin >> MaxCVR))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}
*/
	int Count; 
	if (!(cin >> Count))
	{
		cout << "nil" << endl;	
		return EXIT_SUCCESS;
	}

	int * Lengths = new int[Count];
	int * Widths = new int[Count];

	for(int Idx = 0; Idx < Count; Idx++)
	{
		cin >> Lengths[Idx];
		cin >> Widths[Idx];
	}

	bool Infeasible = true;
	if (!Violatn)
	{
		Infeasible = false;
		int * Varx = new int[Count];
		int * Vary = new int [Count];
		int * Vard = new int[Count];
		int * Varxp = new int[Count];	
		int * Varyp = new int[Count];	


		for(int Idx = 0; Idx < Count; Idx++)
			if (!(cin >> Varx[Idx]))
			{
				cout << "nil" << endl;	
				delete [] Lengths; delete [] Widths; delete [] Varx; delete [] Vary; 
				delete [] Vard; delete [] Varxp; delete [] Varyp;
				return EXIT_SUCCESS;
			}
		for(int Idx = 0; Idx < Count; Idx++)
			if (!(cin >> Vary[Idx]))
			{
				cout << "nil" << endl;	
				delete [] Lengths; delete [] Widths; delete [] Varx; delete [] Vary; 
				delete [] Vard; delete [] Varxp; delete [] Varyp;
				return EXIT_SUCCESS;
			}
		for(int Idx = 0; Idx < Count; Idx++)
			if (!(cin >> Vard[Idx]))
			{
				cout << "nil" << endl;	
				delete [] Lengths; delete [] Widths; delete [] Varx; delete [] Vary; 
				delete [] Vard; delete [] Varxp; delete [] Varyp;
				return EXIT_SUCCESS;
			}
		for(int Idx = 0; !Infeasible && Idx < Count; Idx++)
		{
			if (Varx[Idx] > Length || Vary[Idx] > Width || Vard[Idx] > 1) Infeasible = true;
			Varxp[Idx] = Varx[Idx] + (Vard[Idx] ? Lengths[Idx] : Widths[Idx]);
			Varyp[Idx] = Vary[Idx] + (Vard[Idx] ? Widths[Idx] : Lengths[Idx]);
			if (Varxp[Idx] > Length || Varyp[Idx] > Width) Infeasible = true;		
		}	
		for(int Idx1 = 0; !Infeasible && Idx1 < Count - 1; Idx1++)
			for(int Idx2 = Idx1 + 1; !Infeasible && Idx2 < Count; Idx2++)
				if (!(Varx[Idx2]  >= Varxp[Idx1] || Varxp[Idx2] <= Varx[Idx1] || Vary[Idx2]  >= Varyp[Idx1] || Varyp[Idx2] <= Vary[Idx1]))
					Infeasible = true;

		delete [] Varx; delete [] Vary; 
		delete [] Vard; delete [] Varxp; delete [] Varyp;
	}
	delete [] Lengths; delete [] Widths; 

	cout << Violatn << " " << Iteratn << " " << Time << " " << Memory << " ";
	cout << Tabu << " " << Length << " " << Width << " " << MaxDim << " " << MinDim << " " /*<< MaxCVR << " "*/ << Count;
	cout << " " << Infeasible << endl;

	return EXIT_SUCCESS;
}

