#pragma once
#define LEXEMA_FIXSIZE  1			// фиксированный размер лексемы
#define LT_MAXSIZE	    4096		// максимальное количество сткрок в таблице лексем
#define LT_TI_NULLIDX   0xffffffff	// нет элемента таблицы идентификаторов
#define LT_NULLSPSMBL   '.'		// нет элемента для специальной арифметической операций
#define LEX_INTEGER		't'		// лексема для  int 
#define LEX_UNINTEGER	't'		// лексема для  uint 
#define LEX_STRING		't'		// лексема для  string
#define LEX_BOOL		't'		// лексема для  bool 
#define LEX_CHAR		't'		// лексема для  char
#define LEX_ID			'i'		// лексема для  идентификатора 
#define LEX_LITERAL		'l'		// лексема для  литерала
#define LEX_FUNCTION	'f'		// лексема для  function
#define LEX_VAR			'v'		// лексема для  var
#define LEX_RETURN		'r'		// лексема для  return
#define LEX_PRINT		'p'		// лексема для  print
#define LEX_MAIN		'm'		// лексема для  main
#define LEX_IF			'u'		// лексема для  if
#define LEX_ELSE		'e'		// лексема для  else
#define LEX_FOR			'w'		// лексема для  for
#define LEX_SEMICOLON	';'		// лексема для  ;
#define LEX_COMMA		','		// лексема для  ,
#define LEX_LEFTBRACE	'{'		// лексема для  {
#define LEX_BRACELET	'}'		// лексема для  }
#define LEX_LEFTHESIS	'('		// лексема для  (
#define LEX_RIGHTHESIS	')'		// лексема для  )
#define LEX_PLUS		'o'		// лексема для  +
#define LEX_MINUS		'o'		// лексема для  -
#define LEX_STAR		'o'		// лексема для  *
#define LEX_DIRSLASH	'o'		// лексема для  /
#define LEX_EQUAL		'='		// лексема для  =
#define LEX_INVERSION	'o'		// лексема для  ~ (побитовая инверсия) 
#define LEX_BATTERYAND	'o'		// лексема для  & (побитовое и)
#define LEX_BATTERYOR	'o'		// лексема для  | (побитовое или)

namespace LT           // таблица лексем
{
	struct Entry   // строка таблицы лексем
	{
		char lexema/*[LEXEMA_FIXSIZE]*/;	// лесема
		char sp_smbl;					// специальный символ для арифметической операций
		int sn;							// номер строки в исходном тексте
		int idxTI;						// индекс в таблице идентификаторов или LT_TI_NULLIDX 
	};

	struct LexTable						// экземпляр таблицы лексем
	{
		int maxsize;					// емкость таблицы лексем < LT_MAXSIZE
		int size;						// текущий размер таблицы дексем < maxsize
		Entry* table;					// массив строк таблицы лексем
		unsigned char* LexemText;
	};

	LexTable  Create(					// создать таблицу лексем
					int size			// емкость таблицы лексем < LT_MAXSIZE
					);

	void Add(							// добавить строку в таблицу лексем 
		LexTable& lextable,				// экземпляр таблицы лексем
		Entry entry						// строка таблицы лексем
			);

	Entry GetEntry(						// получить строку таблицы лексем
		LexTable& lextable,				// экземпляр таблицы лексем
		int n							// номер получаемой строки
				  );

	void Delete(LexTable& lextable);	// удалить таблицу лексем (освободить память)
	Entry createStructLexem(char type, int number, int numberInTableId, char operation= LT_NULLSPSMBL);  // создание струкрутры с праметром по умолчанию -1 
};


