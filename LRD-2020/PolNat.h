#pragma once
#include "LT.h"
#include "IT.h"
#include "Log.h"

namespace PN
{
	int Priority(char c);  // получение уровня приоритета
	bool PolishNotation(LT::LexTable& newLT_Table);  // Польская запись 
	void ConvertingExpression(LT::LexTable& newLT_Table, short i); // преобразование выражения в польскую запись
	void WriteInTablePolNat(LT::LexTable& newLT_Table, short i);
	void FindEndExpression(LT::LexTable& newLT_Table, short i); // посик конца выражения
} 
