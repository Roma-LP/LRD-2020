#include "LT.h"
#include "Error.h"

namespace LT
{
	/*������� ������� ������*/
	LexTable  Create(int size)		// ������� ������� ������ < LT_MAXSIZE
	{
		if (size >= LT_MAXSIZE)
			throw ERROR_THROW(113);
		LexTable lextable = { size, 0, new Entry[size] };
		return lextable;
	}

	/*�������� ������ � ������� ������*/
	void Add(LexTable& lextable, Entry entry)   // ��������� ������� ������,  ������ ������� ������
	{											  
		if (lextable.size >= lextable.maxsize)
			throw ERROR_THROW(113);
		lextable.table[lextable.size++] = entry;
	}

	/*�������� ������ ������� ������*/
	Entry GetEntry(LexTable& lextable, int n)  // ��������� ������� ������, ����� ���������� ������
	{											 
		if (lextable.size < n || n < 0)
			throw ERROR_THROW(5);
		return lextable.table[n];
	}

	/*������� ������� ������ (���������� ������)*/
	void Delete(LexTable& lextable)
	{
		if (!&lextable)
			throw ERROR_THROW(3);
		delete lextable.table;
		lextable.table = nullptr;
	}

	Entry createStructLexem(char type, int number, int numberInTableId, char operation)
	{
		Entry newLexem;
		newLexem.lexema = type;
		newLexem.sn = number;
		newLexem.idxTI = numberInTableId;
		newLexem.sp_smbl = operation;
		return newLexem;
	}
}