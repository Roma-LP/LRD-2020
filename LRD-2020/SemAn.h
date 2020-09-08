#pragma once
#include "LT.h"
#include "In.h"
#include "IT.h"
#include <stack>
#include "Error.h"

namespace SA
{
	void Typecheck(LT::LexTable& newLT_Table, IT::IdTable& newIT_Table);
	void FindAndCheck(short i, LT::LexTable& newLT_Table, IT::IdTable& newIT_Table);
	bool Registration(char c);
	void ParamCheck(short a, short b);
	void FuncRet(LT::LexTable& newLT_Table, IT::IdTable& newIT_Table);
	void CheckArgs(LT::LexTable& newLT_Table, IT::IdTable& newIT_Table);
	void OutData(LT::LexTable& newLT_Table, IT::IdTable& newIT_Table);
}
