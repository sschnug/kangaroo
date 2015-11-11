/*!
	@file rsc.hpp
	@brief The source file for resource functions.
	@details This is the source file for resource functions.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 19.03.2010 QRL NICTA www.nicta.com.au
*/



#ifndef RscHppIncluded
#define RscHppIncluded



#include "cppl/roots/idx.hpp"



openEmuSpace



/*!
	@fn R getTime()
	@brief Return the time used by the program in seconds.
	@details This function returns the time used by the program in seconds
*/
inline R getTime()
{
	WatchError
	struct tms sTime;
	times(&sTime);
	return castR(sTime.tms_utime + sTime.tms_stime + sTime.tms_cutime
				+ sTime.tms_cstime) / castR(sysconf(_SC_CLK_TCK));
	CatchError
}



/*!
	@fn R getMemory()
	@brief Return the memory used by the program in bytes.
	@details This function returns the memory used by the program in bytes.
*/
inline R getMemory()
{
	WatchError
	//	#!/bin/bash
	//	pmap  `ps | grep $1 | awk '{print $1;}'` | tail -1 | awk '{print $2;}'

	C tBuff[50u], tUnit; R tMem;
	sprintf(tBuff, "bash -c \"pmap %d | tail -1\"", getpid());

	FILE *fp = popen(tBuff, "r" );
	if (fscanf(fp,fstrCs, tBuff) == EOF)
		Throw(ePipeInOut);
	if (fscanf(fp,fstrR, &tMem) == EOF)
		Throw(ePipeInOut);
	if (fscanf(fp,fstrC, &tUnit) == EOF)
		Throw(ePipeInOut);
	pclose( fp );

	switch(tUnit)
	{
		case 'K' : case 'k' : tMem *= 1024; break;
		case 'M' : case 'm' : tMem *= 1048576u; break;
		case 'G' : case 'g' : tMem *= 1073741824u; break;
	}
	return tMem;
	CatchError
}




closeEmuSpace



#endif // RscHppIncluded
