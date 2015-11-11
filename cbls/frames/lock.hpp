/*!
	@file lock.hpp
	@brief The prototype file for Lock class.
	@details This is the prototype file for Lock class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 06.01.2010 QRL NICTA www.nicta.com.au
	@see lock.cpp
*/



#ifndef LockHppIncluded
#define LockHppIncluded



#include "cbls/frames/dat.hpp"



openKangarooSpace


/*
	Forward declarations.
*/
class Func;
class Var;


/*!
	@class Lock
	@brief A class to represent locked variables respecting lock.
	@details This class represents locked variables repecting lock.
*/
class Lock
{
	public:

		//! @name Access
		//! @{

		static Lock & refm(Hdl const hdlSys);			//!< Reference.
		static Lock * ptrm(Hdl const hdlSys);			//!< Pointer.
		static Lock const & refc(Hdl const hdlSys);		//!< Reference.
		static Lock const * ptrc(Hdl const hdlSys);		//!< Pointer.

		//! @}

		//! @name Operations
		//! @{

		void reset();										//!< Reset the locking states of the variables.
		void set(Hdl const varHdl, Bll const SetNotUnset); 	//!< Set the locking state of the variable.
		void set(Hdl const varHdl1,
				Hdl const varHdl2, Bll const SetNotUnset); 	//!< Set the locking states of the variables.
		void set(Hdl const * varHdls,
				Dim const VarCount, Bll const SetNotUnset);	//!< Set the locking states of the variables.

		//! @}
		//! @name Status
		//! @{

		Bll updates() const;								//!< Whether there is any state updates.
		Bll Status(Hdl const hdlVar) const;					//!< The locking status of the variable.
		b1<Hdl, xmm> const & Updates() const;				//!< The variables with locking state updates.

		//! @}

	protected:

		friend class Sys;									// Access various methods.

		~Lock();											//!< Destructor.
		Lock(Lock const & that);							//!< Duplicator.
		Lock(b1<Var *, xmm> const & theVars);				//!< Constructor.
		Lock const & operator = (Lock const & that);		//!< Assigner.

		void adjustMemAuto();								//!< Adjust memory automatically.

		void regFunc(Func * theFunc);						//!< Register a function for update.

	private:

		b1<Hdl, xmm> mUpdates;			//!< The variables with new states.
		b1<Func *, xmm> mFuncs;			//!< Functions requiring locking status.
		b1<Var *, xmm> const & mVars;	//!< Point to the system vars.
};



/*!
	The constructor.
*/
inline Lock::Lock(b1<Var *, xmm> const & theVars) : mVars(theVars)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The destructor.
*/
inline Lock::~Lock()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The variables having updated states.
*/
inline b1<Hdl, xmm> const & Lock::Updates() const
{
	WatchError
	return mUpdates;
	CatchError
}



/*!
	Whether there is any status update.
*/
inline Bll Lock::updates() const
{
	WatchError
	return mUpdates.itemCount();
	CatchError
}



/*!
	Register a function for update.
*/
inline void Lock::regFunc(Func * theFunc)
{
	WatchError
	mFuncs.insertMem(theFunc);
	CatchError
}



/*!
	Adjust dynamic memory.
*/
inline void Lock::adjustMemAuto()
{
	WatchError
	mUpdates.adjustMemAuto();
	mFuncs.adjustMemAuto();
	CatchError
}



closeKangarooSpace



#endif//LockHppIncluded
