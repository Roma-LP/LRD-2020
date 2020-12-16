#pragma once
#include "LT.h"
#include "In.h"
#include "IT.h"

namespace LA
{
	void LexicalAnalizator(In::IN newIN, LT::LexTable& newLT_Table, IT::IdTable& newIT_Table);
	void Parsing(char* word,short countLexem, LT::LexTable& newLT_Table, IT::IdTable& newIT_Table); //������
	bool Duplicate(char* word, IT::IdTable& newIT_Table);		// ����� ����� ��������� � ������� ���������������
	bool Call_Function(IT::IdTable& newIT_Table, char *name); // �������� �� ����� �������
	int FindidinTI(IT::IdTable& newIT_Table, IT::Entry& entry); // ����� ������� � ������� ��������������� ��� �������
	void Convert8to10(char* s); // ������������ �� ����������� � ���������� ������� ���������
	void Convert2to10(char* s); // ������������ �� �������� � ���������� ������� ���������
}