/*!
	@file vloadinggen.cpp
	@brief The problem generator program for vessel loading problem.
	@details This is the source file for the problem generator program for vessel loading problem.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#include "cstdlib"
#include "iostream"
#include "vector"
#include "ctime"

using namespace std;


/*!
	@fn void main(int ArgC, char * ArgV[])
*/
int main (int ArgC, char * ArgV[])
{
	if (ArgC < 2)
	{
		cerr << endl;
		cerr << "Usage: " << ArgV[0] << " -l Length -w Width -x MaxDim -y MinDim -c MaxCVR*100 -s NumSeed" << endl;
		cerr << "Length: Length of the rectangular area." << endl;
		cerr << "Width: Width of the rectangular area." << endl;
		cerr << "MaxDim: Maximum dimension of a vessel." << endl;
		cerr << "MinDim: Minimum dimension of a vessel." << endl;
		cerr << "MaxCVR: Maximu SumOfContainerAreas to VesselArea Ratio." << endl;
		cerr << "NumSeed: The seed of the random number generator." << endl;
		cerr << endl;
		cerr << "Output: " << endl;
		cerr << "Length Width MaxDim MinDim VesselCount VesselLengthAndWidths" << endl;
		cerr << endl;
		return EXIT_FAILURE;
	}

	int Length = 0;			// Length of the big rectangle.
	int Width  = 0;			// Width of the big rectangle.
	int MaxDim = 0;			// Maximum dimension of the small rectangles.
	int MinDim = 0;			// Minimum dimension of the small rectangles.
	int MaxCVR = 0;			// Maximum SumOfContainerAreas to VesselArea Ratio
	int Seed   = time(0);	// seed of the random number.
	
	for(int i = 1; i < ArgC; ++i)
	{
		if (ArgV[i][0] == '-' && ArgV[i][1] == 'l')
			Length = atoi(ArgV[i+1]);
		else if (ArgV[i][0] == '-' && ArgV[i][1] == 'w')
			Width = atoi(ArgV[i+1]);
		else if (ArgV[i][0] == '-' && ArgV[i][1] == 'x')
			MaxDim = atoi(ArgV[i+1]);
		else if (ArgV[i][0] == '-' && ArgV[i][1] == 'n')
			MinDim = atoi(ArgV[i+1]);
		else if (ArgV[i][0] == '-' && ArgV[i][1] == 'c')
			MaxCVR = atoi(ArgV[i+1]);
		else if (ArgV[i][0] == '-' && ArgV[i][1] == 's')
			Seed = atoi(ArgV[i+1]);
	}
	if (!Length || !Width || !MaxDim || !MinDim || !MaxCVR || Length < Width || MaxDim < MinDim)
	{
		cerr << endl;
		cerr << "Error in commandline parameter/value. Run with no parameter to see usage." << endl;
		cerr << endl;
		return EXIT_FAILURE;
	}

	cout << Length << " " << Width << " " << MaxDim << " " << MinDim << " " << MaxCVR;
	srand(Seed);
	int Area = 0, Count = 0;
	vector<int> xvec, yvec;
	int MaxArea = ( Length * Width * MaxCVR ) / 100;
	int MinContArea = MinDim * MinDim; 
	int DimDiff = MaxDim - MinDim + 1;
	while ( Area + MinContArea <= MaxArea )
	{
		int CArea = 0;
		int xx = 0; int yy = 0;
		if ( Area + MinContArea + 1 >= MaxArea ) {
			xx = MinDim;
			yy = MinDim;
		} else {
			do {
				xx = ( random() % DimDiff ) + MinDim;
				yy = ( random() % DimDiff ) + MinDim;
				CArea  = xx * yy;
			} while ( Area + CArea > MaxArea );
		}
		
		if (xx >= yy) xvec.push_back(xx), yvec.push_back(yy);
		else xvec.push_back(yy), yvec.push_back(xx);
		Area += xx * yy; Count += 1;
	}	 
	cout << " " << Count;
	for(int Idx = 0; Idx < Count; Idx++)
		cout << " " << xvec[Idx] << " " << yvec[Idx];
	cout << endl;
	return EXIT_SUCCESS;
}

