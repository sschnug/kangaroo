/*!
	@file tabus/reg.hh
	@brief The register header file for tabu heuristics.
	@details This is the register header file for tabu heuristics.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef TabusRegHhIncluded
#define TabusRegHhIncluded


#include "cbls/frames/idx.hh"


openKangarooSpace
#define AutoTypTabu (thisLine - AutoTypBaseSvTabu)
enum { AutoTypBaseSvTabu = thisLine};
dec tabutpn(Sv0Tabu, AutoTypTabu);
//dec tabutpn(Sv1Tabu, AutoTypTabu);
dec tabutpn(Sv2Tabu, AutoTypTabu);
dec tabutpn(Dv0Tabu, AutoTypTabu);
//dec tabutpn(Dv1Tabu, AutoTypTabu);
dec tabutpn(Dv2Tabu, AutoTypTabu);
//dec tabutpn(Sw0Tabu, AutoTypTabu);
//dec tabutpn(Sw1Tabu, AutoTypTabu);
//dec tabutpn(Sw2Tabu, AutoTypTabu);
closeKangarooSpace


openKangarooSpace
#define AutoClsTabu (thisLine - AutoClsBaseTabu)
enum { AutoClsBaseTabu = thisLine};
dec tabucln(QcSv0Tabu, AutoClsTabu);
dec tabucln(QcSv2Tabu, AutoClsTabu);
dec tabucln(QcDv0Tabu, AutoClsTabu);
dec tabucln(QcDv2Tabu, AutoClsTabu);
closeKangarooSpace



#endif // TabusRegHhIncluded
