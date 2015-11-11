/*!
	@file err.hpp
	@brief The source file for Err class.
	@details This is the source file for Err class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 01.01.2013 QRL NICTA www.nicta.com.au
*/



#ifndef ErrHppIncluded
#define ErrHppIncluded



#include "cppl/msg.hpp"
#include "cppl/roots/typ.hpp"



openEmuSpace


/*!
	@class Err
	@brief A class to represent error objects.
	@details This class represents error objects.
		This class allows composing the error message
		in a convenient way just like the output streams.
*/
class Err
{
	public:

		~Err();										//!< Destructor.
		Err();										//!< Constructor.
		Err(Err const & that);						//!< Duplicator.
		Err const & operator = (Err const & that);	//!< Assigner.

		/*! @name Formation */
		//! @{

		Err & operator << (C const * theCs);		//!< Append a cstring.
		Err & operator << (B const theB);			//!< Append a boolean value.
		Err & operator << (N const & theN);			//!< Append a countable number.
		Err & operator << (Z const & theZ);			//!< Append an integer number.
		Err & operator << (R const & theR);			//!< Append a real number.

		//! @}

		/*! @name Extraction */
		//! @{

		C const * operator()() const;				//!< Return the message.

		//! @}

	private:

		static N const 		mAlloc = 4095u;			//!< Allocation for message.
		C 					mBuff[mAlloc + 1u];		//!< Buffer for the message.
		N 					mFree;					//!< Number of free spaces.
};



/*!
	@def thisFile
	@brief The name of the file being compiled.
	@details The name of the file currently being compiled.
*/
#define thisFile __FILE__



/*!
	@def thisLine
	@brief The number of the line being compiled.
	@details The number of the line currently being compiled.
*/
#define thisLine __LINE__



/*!
	@def thisFunc
	@brief The name of the function being compiled.
	@details The name of the function currently being compiled.
*/
#define thisFunc __FUNCTION__



/*!
	@def Warn(Check, Text)
	@brief Warn only when CheckError is set.
	@details Warn only when CheckError is set; otherwise,
		do not warn. Use this macro to enforce optional
		run-time checking that should be performed during
		debug running but should be skipped to improve
		time performance during final running.
*/
#if CheckError
	#define Warn(Check, Text) \
		if (Check) throw Err() << Text << "\n@" \
				<< thisFile << " #" << castN(thisLine)
#else
	#define Warn(Check, Text)
#endif


/*!
	@def Wchk(...)
	@brief Warn only when CheckError is set.
	@details Warn only when CheckError is set. This macro
		is used with template classes that have multiple
		template parameters and thus need comma in the
		parameter of the Warn macro. This macro only deals
		with the check condition of the Warn macro and is to be
		used in conjunction with the Wtxt macro.
*/
#if CheckError
	#define Wchk(...) if (__VA_ARGS__)
#else
	#define Wchk(...)
#endif



/*!
	@def Wtxt(...)
	@brief Warn only when CheckError is set.
	@details Warn only when CheckError is set. This macro
		is used with template classes that have multiple
		template parameters and thus need comma in the
		parameter of the Warn macro. This macro only deals
		with the text description of the Warn macro and is to be
		used in conjunction with the Wchk macro.
*/
#if CheckError
	#define Wtxt(...) throw Err() << __VA_ARGS__ << "\n@" \
			<< thisFile << " #" << castN(thisLine)
#else
	#define Wtxt(...)
#endif




/*!
	@def Alert(Check, Text)
	@brief Alert both when CheckError is on or off.
	@details Alert both when CheckError is on or off.
		Use this macro to enforce mandatory	run-time
		checking that must be performed regardless of
		debug running or final running.
*/
#define Alert(Check, Text) \
		if (Check) throw Err() << Text << "\n@" \
				<< thisFile << " #" << castN(thisLine)


/*!
	@def Achk(...)
	@brief Alert both when CheckError is on or off.
	@details Alert both when CheckError is on or off.
		This macro is used with template classes that
		have multiple template parameters and thus
		need comma in the parameter of the Warn macro.
		This macro only deals with the check condition
		of the Alert macro and is to be used in conjunction
		with the Atxt macro.
*/
#define Achk(...) if (__VA_ARGS__)



/*!
	@def Atxt(...)
	@brief Alert both when CheckError is on or off.
	@details Alert both when CheckError is on or off.
		This macro is used with template classes that
		have multiple template parameters and thus
		need comma in the parameter of the Warn macro.
*/
#define Atxt(...) throw Err() << __VA_ARGS__ << "\n@" \
			<< thisFile << " #" << castN(thisLine)



/*!
	@def Throw(...)
	@brief Throw error unconditionally.
	@details Throw error unconditionally. The parameter
		of this macro is the error description, which
		might contain commas.
*/
#define Throw(...) throw Err()<< __VA_ARGS__ << "\n@" \
			<< thisFile << " #" << castN(thisLine)



/*!
	@def WatchError
	@brief Watch over the code when CheckError is true.
	@details Watch over the code when CheckError is true;
			otherwise ignore. The macro essentially inserts
			'try' in the code.
*/
#if WatchCatchError
	#define WatchError try {
#else
	#define WatchError
#endif



/*!
	@def CatchError
	@brief When CheckError is set, catch the error.
	@details When CheckError is set, catch the error,
			add more messages, and rethrow.
*/
#if WatchCatchError
	#define CatchError } catch(Err & theErr) \
		{ theErr << "\n@" << thisFile << " $" << thisFunc; throw; }
#else
	#define CatchError
#endif




/*!
	The constructor.
*/
inline Err::Err()
{
	*mBuff = EndC;
	mFree = mAlloc;
}



/*!
	The duplicator.
*/
inline Err::Err(Err const & that)
{
	strcpy(mBuff, that.mBuff);
	mFree = that.mFree;
}



/*!
	The destructor.
*/
inline Err::~Err()
{
	// nothing to be done.
}



/*!
	The assigner.
*/
inline Err const & Err::operator = (Err const & that)
{
	if (&that != this)
		return *this;

	strcpy(mBuff, that.mBuff);
	mFree = that.mFree;
	return *this;
}



/*!
	Add texts to the message.
*/
inline Err & Err::operator << (C const * theCs)
{
	if (!theCs || !*theCs)
		return *this;

	N tLength = strlen(theCs);
	if (mFree < tLength)
		return *this;

	strcat(mBuff, theCs);
	mFree = mFree - tLength;
	return *this;
}



/*!
	Add a boolean number to the message.
*/
inline Err & Err::operator << (B const theB)
{
	C tB[32u];
	sprintf(tB, fstrB, theB);
	N tLength = strlen(tB);
	if (mFree < tLength)
		return *this;

	strcat(mBuff, tB);
	mFree = mFree - tLength;
	return *this;
}



/*!
	Add a countable number to the message.
*/
inline Err & Err::operator << (N const & theN)
{
	C tN[32u];
	sprintf(tN, fstrN, theN);

	N tLength = strlen(tN);
	if (mFree < tLength)
		return *this;

	strcat(mBuff, tN);
	mFree = mFree - tLength;
	return *this;
}



/*!
	Add an integer number to the message.
*/
inline Err & Err::operator << (Z const & theZ)
{
	C tZ[32u];
	sprintf(tZ, fstrZ, theZ);

	N tLength = strlen(tZ);
	if (mFree < tLength)
		return *this;

	strcat(mBuff, tZ);
	mFree = mFree - tLength;
	return *this;
}




/*!
	Add a real number to the message.
*/
inline Err & Err::operator << (R const & theR)
{
	C tR[32u];
	sprintf(tR, fstrR, theR);

	N tLength = strlen(tR);
	if (mFree < tLength)
		return *this;

	strcat(mBuff, tR);
	mFree = mFree - tLength;
	return *this;
}



/*!
	Return the error message.
*/
inline C const * Err::operator()() const
{
	return mBuff;
}



closeEmuSpace



#endif // ErrHppIncluded

