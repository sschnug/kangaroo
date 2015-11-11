/*!
	@file term.cpp
	@brief The implementation file for the Term class.
	@details This is the implementation file for the Term class.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 05.10.2009 QRL NICTA www.nicta.com.au
	@see term.hpp
*/



#include "cbls/frames/term.hpp"
#include "cbls/frames/func.hpp"



openKangarooSpace



/*!
	The constructor.
*/
Term::Term(Hdl const hdlSys) : TermGen(Tu), TermCat(TermCatNil),
		TermTyp(TermTypNil), TermCls(TermClsNil), TermHdl(InvHdl),
		TermHvl(0), mTermSys(Sys::refm(hdlSys)), mTermAsArgs()
		#if CompLazy
		, mEvalUndoArgs(Null), mHintUndoArgs(Null)
		#endif // CompLazy
		, mEmulClk(UdfClk), mExecClk(UdfClk), mSimulClk(UdfClk)
{
	WatchError
	//	nothing to be done.
	CatchError
}



/*!
	The duplicator.
*/
Term::Term(Term const & that) : TermGen(Tu), TermCat(TermCatNil),
		TermTyp(TermTypNil), TermCls(TermClsNil), TermHdl(InvHdl),
		TermHvl(0),mTermSys(that.mTermSys), mTermAsArgs()
		#if CompLazy
		, mEvalUndoArgs(Null), mHintUndoArgs(Null)
		#endif // CompLazy
		, mEmulClk(UdfClk), mExecClk(UdfClk), mSimulClk(UdfClk)
{
	WatchError
	Throw(eUndefDuplicator);
	CatchError
}



/*!
	The assigner.
*/
Term const & Term::operator = (Term const & that)
{
	WatchError
	if (this == &that)
		return *this;
	Throw(eUndefAssigner);
	CatchError
}



#if CompLazyFull
/*!
	Peform execution in incremental mode.
*/
void Term::performExecIncr(Term * theTerm)
{
	//another inline version exist for !CompLazyFull
	WatchError
	Warn(!theTerm, eNullPointer);

	if (theTerm->chgdExecClk() && theTerm->computable()
			&& Func::cast(theTerm)->backlog())
		{ theTerm->updtExecClk(); theTerm->execBklg(); }

	//	the following checking is delibourately done on a delayed basis.
	Warn(!theTerm->mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);
	CatchError
}
#endif //CompLazyFull



#if CompLazyFull
/*!
	Peform execution in incremental mode.
*/
void Term::performExecIncr(Term & theTerm)
{
	//another inline version exist for !CompLazyFull
	WatchError
	if (theTerm.chgdExecClk() && theTerm.computable()
			&& Func::cast(theTerm).backlog())
		{ theTerm.updtExecClk(); theTerm.execBklg(); }

	//	the following checking is delibourately done on a delayed basis.
	Warn(!theTerm.mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);
	CatchError
}
#endif //CompLazyFull



#if CompLazy
/*!
	Peform execution in bklg mode.
*/
void Term::performExecBklg(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	if (theTerm->chgdExecClk() && theTerm->computable()
			&& Func::cast(theTerm)->backlog())
		{ theTerm->updtExecClk(); theTerm->execBklg(); }
	//	the following checking is delibourate done on a delayed basis.
	Warn(!theTerm->mTermSys.mskExecMode(IncrProp), eNotExecIncrProp);
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Peform emulation in bklog mode.
*/
void Term::performEmulBklg(Term * theTerm)
{
	WatchError
	Warn(!theTerm, eNullPointer);
	// the first cond also implies computability.
	if (theTerm->chgdEmulClk() && Func::cast(theTerm)->backlog())
		{ theTerm->updtEmulClk(); theTerm->emulBklg(); }
	//	the following checking is delibourate done on a delayed basis.
	Warn(!theTerm->mTermSys.mskSimulMode(IncrProp), eNotSimulIncrProp);
	CatchError
}
#endif // CompLazy



#if ExecUpwd
/*!
	Schedule term args for execution.
*/
void Term::scheduleExecAnewArgs()
{
	WatchError
	for(Idx tIdx = 0; tIdx < mTermAsArgs.itemCount(); ++tIdx)
	{
		Func * tArgFunc = mTermAsArgs[tIdx].ArgFunc;
		if (tArgFunc->computable())
			mTermSys.scheduleExecQueue(tArgFunc);
	}
	CatchError
}
#endif//ExecUpwd



#if ExecUpwd
/*!
	Schedule term args for execution.
*/
void Term::scheduleExecIncrArgs()
{
	WatchError
	for(Idx tIdx = 0; tIdx < mTermAsArgs.itemCount(); ++tIdx)
	{
		Func * tArgFunc = mTermAsArgs[tIdx].ArgFunc;
		if (tArgFunc->computable())
		{
			mTermSys.scheduleExecQueue(tArgFunc);
			Pos tArgPos = mTermAsArgs[tIdx].ArgPos;
			tArgFunc->mExecChgdPrms.tag(tArgPos);
		}
	}
	CatchError
}
#endif//ExecUpwd



#if SimulUpwd
/*!
	Schedule term args for simul.
*/
void Term::scheduleSimulAnewArgs()
{
	WatchError
	for(Idx tIdx = 0; tIdx < mTermAsArgs.itemCount(); ++tIdx)
	{
		Func * tArgFunc = mTermAsArgs[tIdx].ArgFunc;
		if (tArgFunc->computable())
			mTermSys.scheduleSimulQueue(tArgFunc);
	}
	CatchError
}
#endif//SimulUpwd



#if SimulUpwd
/*!
	Schedule term args for simul.
*/
void Term::scheduleSimulIncrArgs()
{
	WatchError
	for(Idx tIdx = 0; tIdx < mTermAsArgs.itemCount(); ++tIdx)
	{
		Func * tArgFunc = mTermAsArgs[tIdx].ArgFunc;
		if (tArgFunc->computable())
		{
			mTermSys.scheduleSimulQueue(tArgFunc);
			Pos tArgPos = mTermAsArgs[tIdx].ArgPos;
			tArgFunc->mSimulChgdPrms.tag(tArgPos);
		}
	}
	CatchError
}
#endif//SimulUpwd



#if CompLazy
/*!
	Set up the arguments for undo operation.
*/
void Term::setupUndoArgs()
{
	WatchError
	Throw(eUndefUndoArgs);
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Call arguments to perform likely undo recursively.
*/
void Term::notifyLikelyUndoArgs()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskExecMode(IncrMode), eNotExecIncrMode);

	if (mEvalUndoArgs)
	{
		for(Itr tItr = 0; tItr < mEvalUndoArgs->tagCount(); ++tItr)
		{
			Lnk const & tLnk = mEvalUndoArgs->serial(tItr);
			Arg const & tArg = mTermAsArgs[tLnk];

			Warn(!tArg.valid(), eInvalidArgument);

			Func * tArgFunc = tArg.ArgFunc;
			Pos const & tArgPos = tArg.ArgPos;
			tArgFunc->performLikelyUndo(tArgPos);
		}
	}

	if (mHintUndoArgs)
		for(Itr tItr = 0; tItr < mHintUndoArgs->tagCount(); ++tItr)
		{
			Lnk const & tLnk = mHintUndoArgs->serial(tItr);

			if (mEvalUndoArgs && mEvalUndoArgs->tagged(tLnk))
				continue;

			Arg const & tArg = mTermAsArgs[tLnk];

			Warn(!tArg.valid(), eInvalidArgument);

			Func * tArgFunc = tArg.ArgFunc;
			Pos const & tArgPos = tArg.ArgPos;
			tArgFunc->performLikelyUndo(tArgPos);
		}
	CatchError
}
#endif // CompLazy


#if CompLazy
/*!
	Call arguments to perform eval undo operation.
*/
void Term::notifyEvalUndoArgs()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskExecMode(IncrMode), eNotExecIncrMode);
	Warn(!mEvalUndoArgs, eNullPointer);

	for(Itr tItr = 0; tItr < mEvalUndoArgs->tagCount(); ++tItr)
	{
		Lnk const & tLnk = mEvalUndoArgs->serial(tItr);
		Arg const & tArg = mTermAsArgs[tLnk];

		Warn(!tArg.valid(), eInvalidArgument);

		Func * tArgFunc = tArg.ArgFunc;
		Pos const & tArgPos = tArg.ArgPos;

		tArgFunc->performEvalUndo(tArgPos);
	}
	mEvalUndoArgs->sweep(mTermSys.ExecClk());
	CatchError
}
#endif // CompLazy



#if CompLazy
/*!
	Call arguments to perform hint undo operation.
*/
void Term::notifyHintUndoArgs()
{
	WatchError
	Warn(!updatable(), eTermNotUpdatable);
	Warn(!mTermSys.mskExecMode(IncrMode), eNotExecIncrMode);
	Warn(!mHintUndoArgs, eNullPointer);

	for(Itr tItr = 0; tItr < mHintUndoArgs->tagCount(); ++tItr)
	{
		Lnk const & tLnk = mHintUndoArgs->serial(tItr);
		Arg const & tArg = mTermAsArgs[tLnk];

		Warn(!tArg.valid(), eInvalidArgument);

		Func * tArgFunc = tArg.ArgFunc;
		Pos const & tArgPos = tArg.ArgPos;
		tArgFunc->performHintUndo(tArgPos);
	}
	CatchError
}
#endif // CompLazy


/*!
	Value type.
*/
Typ Term::ValueType() const
{
	WatchError
	Throw(eUndefValueType);
	CatchError
}



/*!
	Metric type.
*/
Typ Term::MetricType() const
{
	WatchError
	Throw(eUndefMetricType);
	CatchError
}



/*!
	Value locator.
*/
Loc Term::ValueLoc() const
{
	WatchError
	return InvLoc;
	CatchError
}



/*!
	Metric locator.
*/
Loc Term::MetricLoc() const
{
	WatchError
	return InvLoc;
	CatchError
}



/*!
	Eval max locator.
*/
Loc Term::EvalMaxLoc() const
{
	WatchError
	return InvLoc;
	CatchError
}



/*!
	Eval min locator.
*/
Loc Term::EvalMinLoc() const
{
	WatchError
	return InvLoc;
	CatchError
}



/*!
	Hint max locator.
*/
Loc Term::HintMaxLoc() const
{
	WatchError
	return InvLoc;
	CatchError
}



/*!
	Hint min locator.
*/
Loc Term::HintMinLoc() const
{
	WatchError
	return InvLoc;
	CatchError
}



closeKangarooSpace
