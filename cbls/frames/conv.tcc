/*!
	@file conv.tcc
	@brief The source file for Conv template class.
	@details This is the source file for Conv template class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 03.01.2010 QRL NICTA www.nicta.com.au
*/



#ifndef ConvTccIncluded
#define ConvTccIncluded



#include "cbls/frames/spec.hpp"



openKangarooSpace



/*!
	@class Conv
	@brief A functor for min-to-max conversion.
	@details This functor is for min-to-max conversion.
*/
template <typename it, typename ot>
class Conv
{
	public:

		Conv(); 													//!< Constructor.
		Conv(Conv<it,ot> const & that); 							//!< Duplicator.
		Conv(Fss const theFss, Pss const thePss); 					//!< Initialiser.
		Conv<it,ot> const & operator = (Conv<it,ot> const & that); 	//!< Assigner.

		ot const operator()(it const Idat);		//!< Perform function.

	private:

		ot const (*mOpf)(it const);				//!< Selected function.

		static ot const DotConv(it const Idat);	//!< Dot min-to-max conversion.
		static ot const NotConv(it const Idat);	//!< Not min-to-max conversion.
		static ot const NegConv(it const Idat);	//!< Neg min-to-max conversion.
		static ot const InvConv(it const Idat);	//!< Inv min-to-max conversion.
};




/*!
	The constructor.
*/
template <typename it, typename ot>
inline Conv<it,ot>::Conv() : mOpf(&DotConv)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The initialiser.
*/
template <typename it, typename ot>
Conv<it,ot>::Conv(Fss const theFss, Pss const thePss)
{
	WatchError
	switch(theFss & OEH)
	{
		case En: //case Hn: case On:	//all are the same.
			switch(thePss & MinConvSeg)
			{
				case OnNot: mOpf = &Conv<it,ot>::NotConv; break;
				case OnNeg: mOpf = &Conv<it,ot>::NegConv; break;
				case OnInv: mOpf = &Conv<it,ot>::InvConv; break;
				default: mOpf = &Conv<it,ot>::DotConv; break;
			} break;
		case Ex: case Hx: case Ox:		// all have different values.
			switch(thePss & MaxConvSeg)
			{
				case OxNot: mOpf = &Conv<it,ot>::NotConv; break;
				case OxNeg: mOpf = &Conv<it,ot>::NegConv; break;
				case OxInv: mOpf = &Conv<it,ot>::InvConv; break;
				default: mOpf = &Conv<it,ot>::DotConv; break;
			} break;
		default : Throw(eInvalidSpec);
	}
	CatchError
}



/*!
	The duplicator.
*/
template <typename it, typename ot>
inline Conv<it,ot>::Conv(Conv<it,ot> const & that) : mOpf(that.mOpf)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The assigner.
*/
template <typename it, typename ot>
inline Conv<it,ot> const & Conv<it,ot>::operator = (Conv<it,ot> const & that)
{
	WatchError
	if (this == &that) return *this;
	mOpf = that.mOpf;
	return *this;
	CatchError
}



/*!
	This function is to perform conversion operation.
*/
template <typename it, typename ot>
inline ot const Conv<it,ot>::operator()(it const Idat)
{
	WatchError
	return (*mOpf)(Idat);
	CatchError
}




/*!
	This function is for dot min-to-max conversion.
*/
template <typename it, typename ot>
inline ot const Conv<it,ot>::DotConv(it const Idat)
{
	WatchError
	return Idat;
	CatchError
}



/*!
	This function is not min-to-max conversion.
*/
template <typename it, typename ot>
inline ot const Conv<it,ot>::NotConv(it const Idat)
{
	WatchError
	return !tc<it,Bll>::iof(Idat);
	CatchError
}



/*!
	This function is for negation min-to-max conversion.
*/
template <typename it, typename ot>
inline ot const Conv<it,ot>::NegConv(it const Idat)
{
	WatchError
	return -Idat;
	CatchError
}



/*!
	This function is for inversion min-to-max conversion.
*/
template <typename it, typename ot>
inline ot const Conv<it,ot>::InvConv(it const Idat)
{
	WatchError
	return 1 / Idat;
	CatchError
}



closeKangarooSpace



#endif // ConvTccIncluded
