/**
 * Filename: utils.hpp
 * Author:   Duc Nghia Pham
 * Created:  20th September 2010
 *
 * The header of utils.cpp, containing time functions and comparison functions
 */

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <ctime>

#ifdef WIN32
	#include <sys/timeb.h>
#else
	#include <unistd.h>
	#include <sys/time.h>
	#include <sys/times.h>
#endif

static double startTimeStamp;
static double currentTimeStamp;

#ifdef WIN32
	static struct _timeb tstruct;

	static inline void getCurrentTime() {
		_ftime( &tstruct );
		currentTimeStamp = ((double) tstruct.time + ((double) tstruct.millitm) / 1000.0);
	}
	
	static inline double elapsedTime() {
		getCurrentTime();
		return (currentTimeStamp - startTimeStamp);
	}
	
	static inline int genRandomSeed() {
		_ftime( &tstruct );
		return ((( tstruct.time & 0x001FFFFF ) * 1000) + tstruct.millitm);
	}
#else
	static struct timeval tv;
	static struct timezone tzp;
	static struct tms prog_tms;

	static inline void getCurrentTime() {
		times(&prog_tms);
		currentTimeStamp = (double) prog_tms.tms_utime;
	}
	
	static inline double elapsedTime() {
		double answer;
		
		getCurrentTime();
		answer = ( (currentTimeStamp-startTimeStamp) / ((double) sysconf(_SC_CLK_TCK)) );
		return answer;
	}
	
	static inline int genRandomSeed() {
		gettimeofday(&tv, &tzp);
		return ((( tv.tv_sec & 0x000007FF ) * 1000000) + tv.tv_usec);
	}
#endif

static inline void initTimeCounter() {
	getCurrentTime();
	startTimeStamp = currentTimeStamp;
}

#endif
