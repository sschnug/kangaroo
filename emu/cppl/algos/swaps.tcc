/*!
	@file swaps.tcc
	@brief The source file for swap function templates.
	@details This is the source file for swap function templates.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 02.08.2010 QRL NICTA www.nicta.com.au
*/



#ifndef SwapsTccIncluded
#define SwapsTccIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@brief A function to implement the exchange i.e. swap operator.
	@details This function implements the exchange i.e. swap operator.
*/
template <typename pt>
void exchange(pt & Left, pt & Right)
{
	WatchError
	pt Temp = Left;
	Left = Right;
	Right = Temp;
	CatchError
}



closeEmuSpace



#endif // SwapsTccIncluded
