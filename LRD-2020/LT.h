#pragma once
#define LEXEMA_FIXSIZE  1			// ������������� ������ �������
#define LT_MAXSIZE	    4096		// ������������ ���������� ������ � ������� ������
#define LT_TI_NULLIDX   0xffffffff	// ��� �������� ������� ���������������
#define LT_NULLSPSMBL   '.'		// ��� �������� ��� ����������� �������������� ��������
#define LEX_INTEGER		't'		// ������� ���  uint 
#define LEX_STRING		't'		// ������� ���  string
#define LEX_BOOL		't'		// ������� ���  bool 
#define LEX_CHAR		't'		// ������� ���  let 
#define LEX_ID			'i'		// ������� ���  �������������� 
#define LEX_LITERAL		'l'		// ������� ���  ��������
#define LEX_FUNCTION	'f'		// ������� ���  function
#define LEX_VAR			'v'		// ������� ���  var
#define LEX_RETURN		'r'		// ������� ���  return
#define LEX_PRINT		'p'		// ������� ���  print
#define LEX_MAIN		'm'		// ������� ���  main
#define LEX_IF			'u'		// ������� ���  if
#define LEX_ELSE		'e'		// ������� ���  else
#define LEX_SEMICOLON	';'		// ������� ���  ;
#define LEX_COMMA		','		// ������� ���  ,
#define LEX_LEFTBRACE	'{'		// ������� ���  {
#define LEX_BRACELET	'}'		// ������� ���  }
#define LEX_LEFTHESIS	'('		// ������� ���  (
#define LEX_RIGHTHESIS	')'		// ������� ���  )
#define LEX_PLUS		'o'		// ������� ���  +
#define LEX_MINUS		'o'		// ������� ���  -
#define LEX_STAR		'o'		// ������� ���  *
#define LEX_DIRSLASH	'o'		// ������� ���  /
#define LEX_EQUAL		'='		// ������� ���  =
#define LEX_INVERSION	'o'		// ������� ���  ~ (��������� ��������) 
#define LEX_BATTERYAND	'o'		// ������� ���  & (��������� �)
#define LEX_BATTERYOR	'o'		// ������� ���  | (��������� ���)

namespace LT           // ������� ������
{
	struct Entry   // ������ ������� ������
	{
		char lexema/*[LEXEMA_FIXSIZE]*/;	// ������
		char sp_smbl;					// ����������� ������ ��� �������������� ��������
		int sn;							// ����� ������ � �������� ������
		int idxTI;						// ������ � ������� ��������������� ��� LT_TI_NULLIDX 
	};

	struct LexTable						// ��������� ������� ������
	{
		int maxsize;					// ������� ������� ������ < LT_MAXSIZE
		int size;						// ������� ������ ������� ������ < maxsize
		Entry* table;					// ������ ����� ������� ������
		unsigned char* LexemText;
	};

	LexTable  Create(					// ������� ������� ������
					int size			// ������� ������� ������ < LT_MAXSIZE
					);

	void Add(							// �������� ������ � ������� ������ 
		LexTable& lextable,				// ��������� ������� ������
		Entry entry						// ������ ������� ������
			);

	Entry GetEntry(						// �������� ������ ������� ������
		LexTable& lextable,				// ��������� ������� ������
		int n							// ����� ���������� ������
				  );

	void Delete(LexTable& lextable);	// ������� ������� ������ (���������� ������)
	Entry createStructLexem(char type, int number, int numberInTableId, char operation= LT_NULLSPSMBL);  // �������� ���������� � ��������� �� ��������� -1 
};


