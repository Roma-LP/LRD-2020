#pragma once
#include "IT.h"
#include "LT.h"
#include "In.h"

namespace GN
{
	void Head();
	void Down();
	void Generation(LT::LexTable &newLT_Table, IT::IdTable& newIT_Table);
	void OutValue(short i,LT::LexTable &newLT_Table, IT::IdTable& newIT_Table);
	bool IsProtoStaticLib(short i, LT::LexTable &newLT_Table);  // проверка на прототип статической библиотека 
}
