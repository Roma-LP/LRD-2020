#pragma once
//#include <iostream>
#include <string>
#define ID_MAXSIZE		5			// максимальное количество символов в идентификаторе
#define TI_MAXSIZE		4096		// максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT	0x00000000	// значение по умолчанию дл€ типа integer
#define TI_STR_DEFAULT	0x00		// значение по умолчанию дл€ типа string
#define TI_NULLIDX		0xffffffff	// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	255				 

namespace IT			// таблица идентификаторов
{
	enum IDDATATYPE	 { UINT = 1, STR = 2, BOOL = 3, INT = 4, CHR = 5};	// типы данных идентификаторов: uninteger, string, bool, integer, char
	enum IDTYPE		 { V = 1, F = 2, P = 3, L = 4 };	// типы идентификаторов: переменна€, функци€, параметр, литерал

	struct Entry		// строка таблицы идентификаторов
	{
		int			idxfirstLE;			// индекс первой строки в таблице лексем
		char		id[15];	// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE	iddatatype;			// тип данных идентификаторов: uninteger, string, bool, integer, char
		IDTYPE		idtype;				// тип идентификатора: переменна€, функци€, параметр, литерал
		std::string		idscope;			// область видимости: глобальна€, главна€(Main) функци€, функци€
		union
		{
			int		vint;				// значение integer
			bool	vbool;				// значение bool
			struct 
			{
				char len;						// количество символов в string
				char str[TI_STR_MAXSIZE - 1];	// символы string
			}  vstr[TI_STR_MAXSIZE];			// значение string
		} value;			//значение идентификатора
	};

	struct IdTable				// экземпл€р таблицы идентификаторов
	{
		int maxsize;			// емкость таблицы идентификаторов  < TI_MAXSIZE
		int size;				// текущий размер таблицы идентификаторов < maxsize
		Entry* table;			//  массив строк таблицы идентификаторов
	};

	IdTable Create(				// создать таблицу идентификаторов
					int size	// емкость таблицы идентификаторов < TI_MAXSIZE
				  );
	void Add(					// добавить строку в таблицу идентификаторов
			IdTable& idtable,	// экземпл€р таблицы идентификаторов
			Entry entry			// строка таблицы идентификаторов
			);

	Entry GetEntry(				// получить строку таблицы идентификаторов
					IdTable& idtable,	//экземпл€р таблицы идентификаторов
					int n				// номер получаемой строки
				  );
	int IsId(					// возврат: номер строки (если есть), TI_NULLIDX(есди нет)
			IdTable& idtable,		// экземпл€р таблицы идентификаторов
			char id[ID_MAXSIZE]		// идентификатор
			);
	void Delete(IdTable& idtable); // удалить таблицу лексем (освободить па€м€ть)

	Entry createStructId(char* id, int line, int typeData, int typeID, std::string typeScope, short* countLiteral);
	
	bool isStLib(char* id); //проверка на стандартную билблиотеку
};




