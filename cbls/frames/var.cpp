/*!
	@file var.cpp
	@brief The implementation file for the Var class.
	@details This is the implementation file for the Var class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see var.hpp
*/



#include "cbls/frames/var.hpp"
#include "cbls/frames/func.hpp"



openKangarooSpace



/*!
	The duplicator.
*/
Var::Var(Var const & that) : Term(that)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Var const & Var::operator = (Var const & that)
{
	WatchError
	if (this == &that)
		return *this;

	Throw(eUndefAssigner);
	CatchError
}



/*!
	Perform anew execution.
*/
void Var::execAnew()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Perform anew simulation.
*/
void Var::simulAnew()
{
	WatchError
	//	nothing to be done.
	CatchError
}


/*!
	Peform incremental execution.
*/
void Var::execIncr()
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	Perform incremental simulation.
*/
void Var::simulIncr()
{
	WatchError
	//	nothing to be done.
	CatchError
}


#if CompLazy
/*!
	Perform backlog execution.
*/
void Var::execBklg()
{
	WatchError
	//	nothing to be done.
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Perform backlog emulation.
*/
void Var::emulBklg()
{
	WatchError
	//	nothing to be done.
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Set up the undo arguments.
*/
void Var::setupUndoArgs()
{
	WatchError
	setupEvalUndoArgs();
	CatchError
}
#endif // CompLazy



/*!
	Update the domain. This methods is to be called for the variables
	that support domain update. It will recompute the domains of the variables.
*/
void Var::updateDomain()
{
	WatchError
	Throw(eUndefUpdateDomain);
	CatchError
}


/*!
	Domain update defined?
*/
inline Bll Var::DomainUpdateDefined() const
{
	WatchError
	return false;
	CatchError
}



#if CompLazyHalf
/*!
	Domain update required?
*/
Bll Var::DomainUpdateRequired() const
{
	WatchError
	Warn(!DomainUpdateDefined(), eDomainNotUpdatable);
	return mTermSys.VarUpdateRequired(this);
	CatchError
}
#endif	//	CompLazyHalf



#if CompLazyHalf
/*!
	Set domain update required.
*/

void Var::setDomainUpdateRequired(Bll const SetNotUnset)
{
	WatchError
	Warn(!DomainUpdateDefined(), eDomainNotUpdatable);
	mTermSys.setVarUpdateRequired(this, SetNotUnset);
	CatchError
}
#endif	//	CompLazyHalf



#if DnwdVarMapFunc
/*!
	Set up for computation.
*/
void Var::setupComputation()
{
	WatchError
	Warn(!mTermSys.chkExecMode(NullComp), eSysNotUninit);
	#if DnwdMapFuncVar == MfvVarHashFunc
		if (!mFuncHdlSqns)
			mFuncHdlSqns = new hm<Hdl,Sqn, xmmh>;
	#elif DnwdMapFuncVar == MfvVarArrayFunc
		if (!mFuncHdlSqns)
		{
			mFuncHdlSqns = new b1<Sqn, kmm>(mTermSys.funcCount());
			for(Hdl tHdl = 0; tHdl < mTermSys.funcCount(); ++tHdl)
				ccast<b1<Sqn, kmm> *>(mFuncHdlSqns)->item(tHdl) = InvSqn;
		}
	#endif

	CatchError
}
#endif




closeKangarooSpace
