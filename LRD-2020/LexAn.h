#pragma once
#include "LT.h"
#include "In.h"
#include "IT.h"

namespace LA
{
	void LexicalAnalizator(In::IN newIN, LT::LexTable& newLT_Table, IT::IdTable& newIT_Table);
	void Parsing(char* word,short countLexem, LT::LexTable& newLT_Table, IT::IdTable& newIT_Table); //разбор
	bool Duplicate(char* word, IT::IdTable& newIT_Table);		// поиск копий литералов в таблице идентификаторов
	bool Call_Function(IT::IdTable& newIT_Table, char *name); // проверка на вызов функции
	int FindidinTI(IT::IdTable& newIT_Table, IT::Entry& entry); // поиск индекса в таблице идентификаторов для лексемы
	int Convert8to10(char* s); // конвертируем из весмеричной в десятичную систему счисления
	int Convert2to10(char* s); // конвертируем из двоичной в десятичную систему счисления
	void CheckEightLiteral(char*s); // проверка на восмиричный литерал
}