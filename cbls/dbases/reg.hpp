/*!
	@file dbases/reg.hpp
	@brief The register header file for dbases.
	@details This is the register header file for dbases.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 25.07.2010 QRL NICTA www.nicta.com.au
*/


#ifndef DbasesRegHppIncluded
#define DbasesRegHppIncluded


#include "cbls/dbases/evalrec.tcc"
#include "cbls/dbases/evaltbl.tcc"
#include "cbls/dbases/hintfld.tcc"
#include "cbls/dbases/hintrec.tcc"
#include "cbls/dbases/hinttbl.tcc"


openKangarooSpace

rti(EvalRec<Bln>) EvalRecBln;
rti(EvalRec<Int>) EvalRecInt;
rti(EvalRec<Flt>) EvalRecFlt;

rti(EvalTbl<Bln>) EvalTblBln;
rti(EvalTbl<Int>) EvalTblInt;
rti(EvalTbl<Flt>) EvalTblFlt;

reg EvalTbl<Bln> EvalTb;
reg EvalTbl<Int> EvalTi;
reg EvalTbl<Flt> EvalTf;

rti(HintFld<Bln>) HintFldBln;
rti(HintFld<Int>) HintFldInt;
rti(HintFld<Flt>) HintFldFlt;

rti(HintRec<Bln>) HintRecBln;
rti(HintRec<Int>) HintRecInt;
rti(HintRec<Flt>) HintRecFlt;

rti(HintTbl<Bln>) HintTblBln;
rti(HintTbl<Int>) HintTblInt;
rti(HintTbl<Flt>) HintTblFlt;

reg HintTbl<Bln> HintTb;
reg HintTbl<Int> HintTi;
reg HintTbl<Flt> HintTf;

closeKangarooSpace


#endif//DbasesRegHppIncluded
