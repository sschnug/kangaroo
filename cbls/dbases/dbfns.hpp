/*!
	@file dbfns.hpp
	@brief The header file for database functions.
	@details This the header file for database functions.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 01.12.2011 QRL NICTA www.nicta.com.au
*/


#include "cbls/dbases/reg.hpp"


#ifndef DbFnsHppIncluded
#define DbFnsHppIncluded


openKangarooSpace


/*!
	@brief A constant's value from its value type and eval table.
	@details A constant's value from its value type and eval table.
*/
template <typename dat>
inline dat const & ConstValue(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
		EvalTbl<dat> const & tEvalTbl = EvalTbl<dat>::refc(hdlSys);
		Const const & tConst = Const::refc(hdlSys,hdlVar);
		Warn(tConst.ValueType() != DataStub<dat>::DataTyp, eWrongTyp);
		return tEvalTbl.refcEvalRec(tConst.ValueLoc()).CurrData();
	CatchError
}



/*!
	@brief A variable's value from its value type and eval table.
	@details A variable's value from its value type and eval table.
*/
template <typename dat>
inline dat const & VarCurrValue(Hdl const hdlSys, Hdl const hdlVar)
{
	WatchError
		EvalTbl<dat> const & tEvalTbl = EvalTbl<dat>::refc(hdlSys);
		Var const & tVar = Var::refc(hdlSys,hdlVar);
		Warn(tVar.ValueType() != DataStub<dat>::DataTyp, eWrongTyp);
		return tEvalTbl.refcEvalRec(tVar.ValueLoc()).CurrData();
	CatchError
}


/*!
	@brief A functions's value from its value type and eval table.
	@details A functions's value from its value type and eval table.
*/
template <typename dat>
inline dat const & FuncCurrValue(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
		EvalTbl<dat> const & tEvalTbl = EvalTbl<dat>::refc(hdlSys);
		Func const & tFunc = Func::refc(hdlSys,hdlFunc);
		Warn(tFunc.ValueType() != DataStub<dat>::DataTyp, eWrongTyp);
		return tEvalTbl.refcEvalRec(tFunc.ValueLoc()).CurrData();
	CatchError
}



/*!
	@brief A functions's value from its value type and eval table.
	@details A functions's value from its value type and eval table.
*/
template <typename dat>
inline dat const & FuncNextValue(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
		EvalTbl<dat> const & tEvalTbl = EvalTbl<dat>::refc(hdlSys);
		Func const & tFunc = Func::refc(hdlSys,hdlFunc);
		Warn(tFunc.ValueType() != DataStub<dat>::DataTyp, eWrongTyp);
		return tEvalTbl.refcEvalRec(tFunc.ValueLoc()).NextData(Sys::refc(hdlSys).SimulClk());
	CatchError
}



/*!
	@brief A functions's metric from its metric type and eval table.
	@details A functions's metric from its metric type and eval table.
*/
template <typename dat>
inline dat const & FuncCurrMetric(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
		EvalTbl<dat> const & tEvalTbl = EvalTbl<dat>::refc(hdlSys);
		Func const & tFunc = Func::refc(hdlSys,hdlFunc);
		Warn(tFunc.MetricType() != DataStub<dat>::DataTyp, eWrongTyp);
		return tEvalTbl.refcEvalRec(tFunc.MetricLoc()).CurrData();
	CatchError
}



/*!
	@brief A functions's metric from its metric type and eval table.
	@details A functions's metric from its metric type and eval table.
*/
template <typename dat>
inline dat const & FuncNextMetric(Hdl const hdlSys, Hdl const hdlFunc)
{
	WatchError
		EvalTbl<dat> const & tEvalTbl = EvalTbl<dat>::refc(hdlSys);
		Func const & tFunc = Func::refc(hdlSys,hdlFunc);
		Warn(tFunc.MetricType() != DataStub<dat>::DataTyp, eWrongTyp);
		return tEvalTbl.refcEvalRec(tFunc.MetricLoc()).NextData(Sys::refc(hdlSys).SimulClk());
	CatchError
}



closeKangarooSpace



#endif // DbFnsHppIncluded
