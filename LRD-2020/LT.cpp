#include "LT.h"
#include "Error.h"

namespace LT
{
	/*создать таблицу лексем*/
	LexTable  Create(int size)		// емкость таблицы лексем < LT_MAXSIZE
	{
		if (size >= LT_MAXSIZE)
			throw ERROR_THROW(113);
		LexTable lextable = { size, 0, new Entry[size] };
		return lextable;
	}

	/*добавить строку в таблицу лексем*/
	void Add(LexTable& lextable, Entry entry)   // экземпл€р таблицы лексем,  строка таблицы лексем
	{											  
		if (lextable.size >= lextable.maxsize)
			throw ERROR_THROW(113);
		lextable.table[lextable.size++] = entry;
	}

	/*получить строку таблицы лексем*/
	Entry GetEntry(LexTable& lextable, int n)  // экземпл€р таблицы лексем, номер получаемой строки
	{											 
		if (lextable.size < n || n < 0)
			throw ERROR_THROW(5);
		return lextable.table[n];
	}

	/*удалить таблицу лексем (освободить пам€ть)*/
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