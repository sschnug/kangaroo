/*!
	@file examples.cc
	@brief The main source file for kangaroo examples.
	@details This is the main source file kangaroo examples.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/



#include "examples/examples.hpp"



/*!
	The main function.
	@param ArgC The number of command-line arguments.
	@param ArgV The command-line arguments.
*/

int main(int ArgC, char * ArgV[])
{
	try
	{
		if (ArgC == 1)
		{
			cerr << "nq: Queens" << endl;
			cerr << "ms: Magic Square" << endl;
			cerr << "is: All Interval Series" << endl;
			cerr << "vl: Vessel Loading" << endl;
			cerr << "gr: Golomb Ruler" << endl;
			cerr << "gc: Graph Color" << endl;
			cerr << "sg: Social Golfer" << endl;
			cerr << "wm: Wireless Mesh" << endl;
			cerr << "ps: Protein Structure" << endl;

			return EXIT_FAILURE;
		}
		if (ArgV[1][0] == 'n' && ArgV[1][1] == 'q')
			return NQueen(ArgC, ArgV);
		else if (ArgV[1][0] == 'm' && ArgV[1][1] == 's')
			return MSquare(ArgC, ArgV);
		else if (ArgV[1][0] == 'i' && ArgV[1][1] == 's')
			return ISeries(ArgC, ArgV);
		else if (ArgV[1][0] == 'v' && ArgV[1][1] == 'l')
			return VLoading(ArgC, ArgV);
		else if (ArgV[1][0] == 'g' && ArgV[1][1] == 'r')
			return GRuler(ArgC, ArgV);
		else if (ArgV[1][0] == 'g' && ArgV[1][1] == 'c')
			return GColor(ArgC, ArgV);
		else if (ArgV[1][0] == 's' && ArgV[1][1] == 'g')
			return SGolfer(ArgC, ArgV);
		else if (ArgV[1][0] == 'w' && ArgV[1][1] == 'm')
			return WMCA(ArgC, ArgV);
		else if (ArgV[1][0] == 'p' && ArgV[1][1] == 's')
			return PSP(ArgC, ArgV);
		else
			cerr << "Error in commandline parameter/values. Run with no parameters to see usage." << endl << endl;
	}
	catch(char c){};
//	catch(Err & theErr)
//	{
//		cout << endl << "Error: " << theErr() << endl;
//		return ExitOnFailure;
//	}
	return ExitOnSuccess;
}

