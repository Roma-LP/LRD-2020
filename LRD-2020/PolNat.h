#pragma once
#include "LT.h"
#include "IT.h"
#include "Log.h"

namespace PN
{
	int Priority(char c);  // ��������� ������ ����������
	bool PolishNotation(LT::LexTable& newLT_Table);  // �������� ������ 
	void ConvertingExpression(LT::LexTable& newLT_Table, short i); // �������������� ��������� � �������� ������
	void WriteInTablePolNat(LT::LexTable& newLT_Table, short i);
	void FindEndExpression(LT::LexTable& newLT_Table, short i); // ����� ����� ���������
} 
