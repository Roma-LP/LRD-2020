#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "In.h"
#include "LexAn.h"
#include "Error.h"
#include <iostream>
#include <conio.h>

#include <stack>

using namespace std;


namespace LA
{
	short IDDATATYPE;								// типы данных идентификаторов: integer, string
	short IDTYPE;									// типы идентификаторов: переменная, функция, параметр, литерал
	string IDSCOPE ="Global";/* по умолчанию глобальная |*/	// область видимости: глобальная, главная(Main) функция, функция
	stack<string> IDSCOPE_PREV;						 // предыдущая обсласть видимости (стек)
	bool isfunk = false;  
	bool ismain = false;  
	short countLiteral = 0;							// счетчик литералов
	short indexinIT = 0;							// индекс идентификатора для лексемы
	short countLexem = 0;							// номер лексемы
	short countMain = 0;							// количество взодных точек (Main)
	short line = 0;									//номер строки лексем
	short letter = 0;								 //нобер буквы в строке

	

	void LexicalAnalizator(In::IN newIN, LT::LexTable& newLT_Table, IT::IdTable& newIT_Table)
	{
		IDSCOPE_PREV.push("Global");   //устанавливаем по умолчанию 
		char currentLexem[50]; //данная лексема
		short cLcount = 0; //счетчик букв лексемы
		unsigned char* in = newIN.textFormated;  // идентификатор = newIN.textFormated
		bool snglquts = false; // флаг для записи строк '...'
		short n = strlen((char*)newIN.textFormated);
		for (unsigned short i = 0; i < n; i++)
		{
			if (in[i] != '\n')
			{
				if (in[i] != ' ')
				{
					if (in[i] == '\'')
					{
						snglquts = !snglquts;
					}
					currentLexem[cLcount] = in[i];
					cLcount++;
				}
				else
				{
					if (!snglquts)
					{
						currentLexem[cLcount] = '\0';
						Parsing(currentLexem, countLexem, newLT_Table, newIT_Table);
						countLexem++;   // увеличиваем счетчик лексем
						cLcount = 0;
					}
					else
					{
						currentLexem[cLcount] = in[i];
						cLcount++;
					}
				}
				letter++;
			}
			else
			{
				line++;
				letter = 0;
			}
			//if (line==14 && i==300)
			//if (line == 34)
				//cout << "69";

		}
		if (countMain == 0)
			throw ERROR_THROW(605);   // проверяем на main функцию
		if (countMain!=1)
			throw ERROR_THROW(606);  // проверяем на количесвто main функций
	}
	//разбор
	void Parsing(char* word, short countLexem, LT::LexTable& newLT_Table, IT::IdTable& newIT_Table)
	{
		FST::FST fstInteger(word, 4,
			FST::NODE(1, FST::RELATION('i', 1)),
			FST::NODE(1, FST::RELATION('n', 2)),
			FST::NODE(1, FST::RELATION('t', 3)),
			FST::NODE());
		FST::FST fstUnInteger(word, 5,
			FST::NODE(1, FST::RELATION('u', 1)),
			FST::NODE(1, FST::RELATION('i', 2)),
			FST::NODE(1, FST::RELATION('n', 3)),
			FST::NODE(1, FST::RELATION('t', 4)),
			FST::NODE());
		FST::FST fstString(word, 7,
			FST::NODE(1, FST::RELATION('s', 1)),
			FST::NODE(1, FST::RELATION('t', 2)),
			FST::NODE(1, FST::RELATION('r', 3)),
			FST::NODE(1, FST::RELATION('i', 4)),
			FST::NODE(1, FST::RELATION('n', 5)),
			FST::NODE(1, FST::RELATION('g', 6)),
			FST::NODE());
		FST::FST fstBool(word, 5,
			FST::NODE(1, FST::RELATION('b', 1)),
			FST::NODE(1, FST::RELATION('o', 2)),
			FST::NODE(1, FST::RELATION('o', 3)),
			FST::NODE(1, FST::RELATION('l', 4)),
			FST::NODE());
		FST::FST fstChar(word, 3,
			FST::NODE(1, FST::RELATION('c', 1)),
			FST::NODE(1, FST::RELATION('h', 2)),
			FST::NODE());
		FST::FST fstFunction(word, 9,
			FST::NODE(1, FST::RELATION('f', 1)),
			FST::NODE(1, FST::RELATION('u', 2)),
			FST::NODE(1, FST::RELATION('n', 3)),
			FST::NODE(1, FST::RELATION('c', 4)),
			FST::NODE(1, FST::RELATION('t', 5)),
			FST::NODE(1, FST::RELATION('i', 6)),
			FST::NODE(1, FST::RELATION('o', 7)),
			FST::NODE(1, FST::RELATION('n', 8)),
			FST::NODE()
		);
		FST::FST fstVar(word, 4,
			FST::NODE(1, FST::RELATION('v', 1)),
			FST::NODE(1, FST::RELATION('a', 2)),
			FST::NODE(1, FST::RELATION('r', 3)),
			FST::NODE()
		);
		FST::FST fstReturn(word, 7,
			FST::NODE(1, FST::RELATION('r', 1)),
			FST::NODE(1, FST::RELATION('e', 2)),
			FST::NODE(1, FST::RELATION('t', 3)),
			FST::NODE(1, FST::RELATION('u', 4)),
			FST::NODE(1, FST::RELATION('r', 5)),
			FST::NODE(1, FST::RELATION('n', 6)),
			FST::NODE()
		);
		FST::FST fstPrint(word, 6,
			FST::NODE(1, FST::RELATION('p', 1)),
			FST::NODE(1, FST::RELATION('r', 2)),
			FST::NODE(1, FST::RELATION('i', 3)),
			FST::NODE(1, FST::RELATION('n', 4)),
			FST::NODE(1, FST::RELATION('t', 5)),
			FST::NODE()
		);
		FST::FST fstMain(word, 5,
			FST::NODE(1, FST::RELATION('m', 1)),
			FST::NODE(1, FST::RELATION('a', 2)),
			FST::NODE(1, FST::RELATION('i', 3)),
			FST::NODE(1, FST::RELATION('n', 4)),
			FST::NODE()
		);
		FST::FST fstIf(word, 3,
			FST::NODE(1, FST::RELATION('i', 1)),
			FST::NODE(1, FST::RELATION('f', 2)),
			FST::NODE()
		);
		FST::FST fstElse(word, 5,
			FST::NODE(1, FST::RELATION('e', 1)),
			FST::NODE(1, FST::RELATION('l', 2)),
			FST::NODE(1, FST::RELATION('s', 3)),
			FST::NODE(1, FST::RELATION('e', 4)),
			FST::NODE()
		);
		FST::FST fstLiteralOfTrue(word, 5,
			FST::NODE(1, FST::RELATION('t', 1)),
			FST::NODE(1, FST::RELATION('r', 2)),
			FST::NODE(1, FST::RELATION('u', 3)),
			FST::NODE(1, FST::RELATION('e', 4)),
			FST::NODE()
		);
		FST::FST fstLiteralOfFalse(word, 6,
			FST::NODE(1, FST::RELATION('f', 1)),
			FST::NODE(1, FST::RELATION('a', 2)),
			FST::NODE(1, FST::RELATION('l', 3)),
			FST::NODE(1, FST::RELATION('s', 4)),
			FST::NODE(1, FST::RELATION('e', 5)),
			FST::NODE()
		);
		FST::FST fstFor(word, 4,
			FST::NODE(1, FST::RELATION('f', 1)),
			FST::NODE(1, FST::RELATION('o', 2)),
			FST::NODE(1, FST::RELATION('r', 3)),
			FST::NODE()
		);
		FST::FST fstLiteralOfInteger(word, 2,
			FST::NODE(20, FST::RELATION('0', 0), FST::RELATION('1', 0), FST::RELATION('2', 0), FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0), FST::RELATION('6', 0),
				FST::RELATION('7', 0), FST::RELATION('8', 0), FST::RELATION('9', 0),
				FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),
				FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1)),
			FST::NODE()
		);
		/* мои
		FST::FST fstLiteralOfIntegerTen(word, 3,
			FST::NODE(9, FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),
				FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1)),
			FST::NODE(20, FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),
				FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1),
				FST::RELATION('0', 2), FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), FST::RELATION('4', 2), FST::RELATION('5', 2), FST::RELATION('6', 2),
				FST::RELATION('7', 2), FST::RELATION('8', 2), FST::RELATION('9', 2)),
			FST::NODE()
		);
		FST::FST fstLiteralOfIntegerEight(word, 3,
			FST::NODE(1, FST::RELATION('0', 1)),
			FST::NODE(16, FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),
				FST::RELATION('7', 1), FST::RELATION('0', 2), FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), FST::RELATION('4', 2), FST::RELATION('5', 2), FST::RELATION('6', 2),
				FST::RELATION('7', 2)),
			FST::NODE()
		);*/

		/* влдаа
		FST::FST fstLiteralOfIntegerEight(word, 2,
			FST::NODE(1, FST::RELATION('0', 1)),
			FST::NODE(16, FST::RELATION('0', 0), FST::RELATION('1', 0), FST::RELATION('2', 0), FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0), FST::RELATION('6', 0),
				FST::RELATION('7', 0),
				FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),
				FST::RELATION('7', 1)),
			FST::NODE()
		);
		FST::FST fstLiteralOfIntegerTen(word, 2,
			FST::NODE(20, FST::RELATION('0', 0), FST::RELATION('1', 0), FST::RELATION('2', 0), FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0), FST::RELATION('6', 0),
				FST::RELATION('7', 0), FST::RELATION('8', 0), FST::RELATION('9', 0),
				FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),
				FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1)),
			FST::NODE()
		);*/

		FST::FST fstId(word, 2,
			FST::NODE(72,			   FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('c', 0), FST::RELATION('d', 0), FST::RELATION('e', 0),
				FST::RELATION('f', 0), FST::RELATION('g', 0), FST::RELATION('h', 0), FST::RELATION('i', 0), FST::RELATION('j', 0), FST::RELATION('k', 0),
				FST::RELATION('l', 0), FST::RELATION('m', 0), FST::RELATION('n', 0), FST::RELATION('o', 0), FST::RELATION('p', 0), FST::RELATION('q', 0),
				FST::RELATION('r', 0), FST::RELATION('s', 0), FST::RELATION('t', 0), FST::RELATION('u', 0), FST::RELATION('v', 0), FST::RELATION('w', 0),
				FST::RELATION('x', 0), FST::RELATION('y', 0), FST::RELATION('z', 0), FST::RELATION('0', 0), FST::RELATION('1', 0), FST::RELATION('2', 0),
				FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0), FST::RELATION('6', 0), FST::RELATION('7', 0), FST::RELATION('8', 0),
				FST::RELATION('9', 0), 
				FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1),
				FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1),
				FST::RELATION('l', 1), FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1),
				FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1),
				FST::RELATION('x', 1), FST::RELATION('y', 1), FST::RELATION('z', 1), FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1),
				FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1),
				FST::RELATION('9', 1)),
			FST::NODE()
		);
		FST::FST fstLiteralOfString(word, 3,
			FST::NODE(1, FST::RELATION('\'', 1)),
			FST::NODE(88,
				FST::RELATION('\'', 2), FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1),
				FST::RELATION('e', 1), FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1),
				FST::RELATION('k', 1), FST::RELATION('l', 1), FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1),
				FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1),
				FST::RELATION('w', 1), FST::RELATION('x', 1), FST::RELATION('y', 1), FST::RELATION('z', 1), FST::RELATION('0', 1), FST::RELATION('1', 1),
				FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1),
				FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('а', 1), FST::RELATION('б', 1), FST::RELATION('в', 1), FST::RELATION('г', 1),
				FST::RELATION('д', 1), FST::RELATION('е', 1), FST::RELATION('ё', 1), FST::RELATION('ж', 1), FST::RELATION('з', 1), FST::RELATION('и', 1),
				FST::RELATION('й', 1), FST::RELATION('к', 1), FST::RELATION('л', 1), FST::RELATION('м', 1), FST::RELATION('н', 1), FST::RELATION('о', 1),
				FST::RELATION('п', 1), FST::RELATION('р', 1), FST::RELATION('с', 1), FST::RELATION('т', 1), FST::RELATION('у', 1), FST::RELATION('ф', 1),
				FST::RELATION('х', 1), FST::RELATION('ц', 1), FST::RELATION('ч', 1), FST::RELATION('ш', 1), FST::RELATION('щ', 1), FST::RELATION('ъ', 1),
				FST::RELATION('ы', 1), FST::RELATION('ь', 1), FST::RELATION('э', 1), FST::RELATION('ю', 1), FST::RELATION('я', 1), FST::RELATION(' ', 1),
				FST::RELATION('!', 1), FST::RELATION('?', 1), FST::RELATION('.', 1), FST::RELATION(',', 1), FST::RELATION(';', 1), FST::RELATION('+', 1),
				FST::RELATION('-', 1), FST::RELATION('*', 1), FST::RELATION('/', 1), FST::RELATION('&', 1), FST::RELATION('|', 1), FST::RELATION('~', 1),
				FST::RELATION('(', 1), FST::RELATION(')', 1), FST::RELATION('{', 1), FST::RELATION('}', 1), FST::RELATION('=', 1)
			),
			FST::NODE()
		);
		if (execute(fstInteger)) {
			LT::Add(newLT_Table, LT::createStructLexem(LEX_INTEGER, line, LT_TI_NULLIDX));
			IDDATATYPE = (IT::IDDATATYPE) 4;
			return;
		}
		if (execute(fstUnInteger)) {
			LT::Add(newLT_Table, LT::createStructLexem(LEX_UNINTEGER, line, LT_TI_NULLIDX));
			IDDATATYPE = (IT::IDDATATYPE) 1;
			return;
		}
		if (execute(fstString)) {
			Add(newLT_Table, LT::createStructLexem(LEX_STRING, line, LT_TI_NULLIDX));
			IDDATATYPE = (IT::IDDATATYPE) 2;
			return;
		}
		if (execute(fstBool)) {
			Add(newLT_Table, LT::createStructLexem(LEX_BOOL, line, LT_TI_NULLIDX));
			IDDATATYPE = (IT::IDDATATYPE) 3;
			return;
		}
		if (execute(fstChar)) {
			Add(newLT_Table, LT::createStructLexem(LEX_CHAR, line, LT_TI_NULLIDX));
			IDDATATYPE = (IT::IDDATATYPE) 5;
			return;
		}
		if (execute(fstFunction)) {
			Add(newLT_Table, LT::createStructLexem(LEX_FUNCTION, line, LT_TI_NULLIDX));
			IDTYPE = (IT::IDTYPE) 2;
			isfunk = true;
			return;
		}
		if (execute(fstVar)) {
			Add(newLT_Table, LT::createStructLexem(LEX_VAR, line, LT_TI_NULLIDX));
			IDTYPE = (IT::IDTYPE) 1;
			return;
		}
		if (execute(fstReturn)) {
			Add(newLT_Table, LT::createStructLexem(LEX_RETURN, line, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstPrint)) {
			Add(newLT_Table, LT::createStructLexem(LEX_PRINT, line, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstMain)) {
			Add(newLT_Table, LT::createStructLexem(LEX_MAIN, line, LT_TI_NULLIDX));
			ismain = true;
			IDSCOPE_PREV.push(IDSCOPE);   // записываем область в которую надо будет вернуться
			IDSCOPE = "Main";
			countMain++; 
			return;
		}
		if (execute(fstIf)) {
			Add(newLT_Table, LT::createStructLexem(LEX_IF, line, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstElse)) {
			Add(newLT_Table, LT::createStructLexem(LEX_ELSE, line, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstFor)) {
			Add(newLT_Table, LT::createStructLexem(LEX_FOR, line, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstLiteralOfInteger)) {
			IDTYPE = (IT::IDTYPE) 4;
			IDDATATYPE = (IT::IDDATATYPE) 1;
			CheckEightLiteral(word);
			IT::Entry newEntry = IT::createStructId(word, countLexem, IDDATATYPE ,
													IDTYPE, "LIT", &countLiteral);
			IDTYPE = (IT::IDTYPE) 1; // по умолчанию устанавливаем
			if (!Duplicate(word, newIT_Table))  // проверка на дубликат литерала
			{
				IT::Add(newIT_Table, newEntry);
				countLiteral++;
			}
			indexinIT = FindidinTI(newIT_Table, newEntry);   // находим индекс
			LT::Add(newLT_Table, LT::createStructLexem(LEX_LITERAL, line, indexinIT));

			return;
		}
		/*if (execute(fstLiteralOfIntegerEight)) {
			IDTYPE = (IT::IDTYPE) 4;
			IDDATATYPE = (IT::IDDATATYPE) 1;
			*word = Convert8to10(word);
			IT::Entry newEntry = IT::createStructId(word, countLexem, IDDATATYPE ,
													IDTYPE, "LIT", &countLiteral);
			IDTYPE = (IT::IDTYPE) 1; // по умолчанию устанавливаем
			if (!Duplicate(word, newIT_Table))  // проверка на дубликат литерала
			{
				IT::Add(newIT_Table, newEntry);
				countLiteral++;
			}
			indexinIT = FindidinTI(newIT_Table, newEntry);   // находим индекс
			LT::Add(newLT_Table, LT::createStructLexem(LEX_LITERAL, line, indexinIT));

			return;
		}*/
		if (execute(fstLiteralOfString)) {
			IDTYPE = (IT::IDTYPE) 4;
			IDDATATYPE = (IT::IDDATATYPE) 2;
			IT::Entry newEntry = IT::createStructId(word, countLexem, IDDATATYPE ,
													IDTYPE, "LIT", &countLiteral);
			IDTYPE = (IT::IDTYPE) 1; // по умолчанию устанавливаем
			if (!Duplicate(word, newIT_Table))  // проверка на дубликат литерала
			{
				IT::Add(newIT_Table, newEntry);
				countLiteral++;
			}
			indexinIT = FindidinTI(newIT_Table, newEntry);   // находим индекс
			LT::Add(newLT_Table, LT::createStructLexem(LEX_LITERAL, line, indexinIT));
			
			return;
		}
		if (execute(fstLiteralOfFalse)) {
			IDTYPE = (IT::IDTYPE) 4;
			IDDATATYPE = (IT::IDDATATYPE) 3;
			IT::Entry newEntry = IT::createStructId(word, countLexem, IDDATATYPE ,
													IDTYPE, "LIT", &countLiteral);
			IDTYPE = (IT::IDTYPE) 1; // по умолчанию устанавливаем
			if (!Duplicate(word, newIT_Table))  // проверка на дубликат литерала
			{
				IT::Add(newIT_Table, newEntry);
				countLiteral++;
			}
			indexinIT = FindidinTI(newIT_Table, newEntry);   // находим индекс
			LT::Add(newLT_Table, LT::createStructLexem(LEX_LITERAL, line, indexinIT));
			
			return;
		}
		if (execute(fstLiteralOfTrue)) {
			IDTYPE = (IT::IDTYPE) 4;
			IDDATATYPE = (IT::IDDATATYPE) 3;
			IT::Entry newEntry = IT::createStructId(word, countLexem, IDDATATYPE ,
													IDTYPE, "LIT", &countLiteral);
			IDTYPE = (IT::IDTYPE) 1; // по умолчанию устанавливаем
			if (!Duplicate(word, newIT_Table))  // проверка на дубликат литерала
			{
				IT::Add(newIT_Table, newEntry);
				countLiteral++;
			}
			indexinIT = FindidinTI(newIT_Table, newEntry);   // находим индекс
			LT::Add(newLT_Table, LT::createStructLexem(LEX_LITERAL, line, indexinIT));
			
			return;
		}
		if (execute(fstId)) {
			IT::Entry newEntry = IT::createStructId(word, countLexem, IDDATATYPE ,
													IDTYPE , IDSCOPE, &countLiteral);
			if (isfunk)
			{
				if (!Duplicate(word, newIT_Table))
				{
					IT::Entry newEntry = IT::createStructId(word, countLexem, IDDATATYPE,
						IDTYPE, IDSCOPE, &countLiteral);
					IDSCOPE_PREV.push(IDSCOPE);   // записываем область в которую надо будет вернуться
					IDSCOPE = word;
					isfunk = false;
				}
			}
			bool idInTable = true; // есть ли такой идентификатор в таблице идентификаторов
			
			for (int i = 0; i < newIT_Table.size; i++)
			{
				if ((strcmp(newEntry.id, newIT_Table.table[i].id)==0))  // сравниваем на имя
				{
					if (newEntry.idscope == newIT_Table.table[i].idscope) // сравеиваем на область видимости
					{
						if (newEntry.idtype == 1 && newLT_Table.table[countLexem - 2].lexema == 'v') // проверка на 504 ошибку
						{
							throw ERROR_THROW_IN(504, line, letter);
						}
						else
						{
							idInTable = false;
							break;
						}
					}
					if (newEntry.idtype == 3)  // отделяем параметры и переменные
					{												   //Так как если мы сюда дошли, то только это имеет смысл
						continue;
					}
					else
					{
						if (Call_Function(newIT_Table, newEntry.id))  // это вызов функции?
						{
							idInTable = false;
							break;
						}
					}
				}
			}

			if (idInTable)
			{
				if (newEntry.idtype == 1 && newLT_Table.table[countLexem - 2].lexema != 'v')  // проверка на 505 ошибку
				{
					throw ERROR_THROW_IN(505, line, letter); 
				}
				else
				{
					IT::Add(newIT_Table, newEntry);
				}
			}
			
			indexinIT = FindidinTI(newIT_Table, newEntry);   // находим индекс
			LT::Add(newLT_Table, LT::createStructLexem(LEX_ID, line, indexinIT));
			
			return;
		}
		switch (*word)
		{
		case '(': {
			Add(newLT_Table, LT::createStructLexem(LEX_LEFTHESIS, line, LT_TI_NULLIDX, *word));
			if (IDTYPE == (IT::IDTYPE) 2)
				IDTYPE = (IT::IDTYPE) 3;
			return;
		}
		case ')': {
			Add(newLT_Table, LT::createStructLexem(LEX_RIGHTHESIS, line, LT_TI_NULLIDX, *word));
			if (IDTYPE == (IT::IDTYPE) 3)
				IDTYPE = (IT::IDTYPE) 1;
			return;
		}
		case '{': { Add(newLT_Table, LT::createStructLexem(LEX_LEFTBRACE, line, LT_TI_NULLIDX));  return; }
		case '}': { Add(newLT_Table, LT::createStructLexem(LEX_BRACELET, line, LT_TI_NULLIDX)); return; }
		case ';': { 
					Add(newLT_Table, LT::createStructLexem(LEX_SEMICOLON, line, LT_TI_NULLIDX));
					if ((newLT_Table.table[countLexem - 1].lexema == '}') || (newLT_Table.table[countLexem - 3].lexema == 't'))
					{
						isfunk = false;
						ismain = false;
						IDSCOPE = IDSCOPE_PREV.top(); // записываем в текущую область предыдущую, извлекая из стека верхний элемент
						IDSCOPE_PREV.pop();  // удаляем верхний элемент из стека
					}
				return; }
		case ',': { Add(newLT_Table, LT::createStructLexem(LEX_COMMA, line, LT_TI_NULLIDX));		 return; }
		case '+': { Add(newLT_Table, LT::createStructLexem(LEX_PLUS, line, LT_TI_NULLIDX, *word));		 return; }
		case '*': { Add(newLT_Table, LT::createStructLexem(LEX_STAR, line, LT_TI_NULLIDX, *word));		 return; }
		case '/': { Add(newLT_Table, LT::createStructLexem(LEX_DIRSLASH, line, LT_TI_NULLIDX, *word));	 return; }
		case '-': { Add(newLT_Table, LT::createStructLexem(LEX_MINUS, line, LT_TI_NULLIDX, *word));		 return; }
		case '~': { Add(newLT_Table, LT::createStructLexem(LEX_INVERSION, line, LT_TI_NULLIDX, *word));		 return; }
		case '|': { Add(newLT_Table, LT::createStructLexem(LEX_BATTERYOR, line, LT_TI_NULLIDX, *word));		 return; }
		case '&': { Add(newLT_Table, LT::createStructLexem(LEX_BATTERYAND, line, LT_TI_NULLIDX, *word));		 return; }
		case '=': { Add(newLT_Table, LT::createStructLexem(LEX_EQUAL, line, LT_TI_NULLIDX));		 return; }
		}
		throw ERROR_THROW_IN(502, line, letter);
	}

	bool Duplicate(char* word, IT::IdTable& newIT_Table)
	{
		for (int i = 0; i < newIT_Table.size; i++)
		{
			if (newIT_Table.table[i].idtype == 4)  // выбираем литералы
			{
				if (newIT_Table.table[i].iddatatype == 2) // выбираем тип string
				{
					if (strcmp(word, newIT_Table.table[i].value.vstr->str) == 0) // сравниваем значения string
						return true;
				}
				if (newIT_Table.table[i].iddatatype == 1) // выбираем тип int
				{
					//----------------------------------------------------------------------------------
					if (word[0] != '0' && atoi(word) == 0)
						continue;
					if (newIT_Table.table[i].value.vint==atoi(word)) // сравниваем значения integer, делая из строки в число перевод
						return true;
				}
				if (newIT_Table.table[i].iddatatype == 1) // выбираем тип bool
				{
					if (newIT_Table.table[i].value.vbool==atoi(word)) // сравниваем значения bool, делая из строки в логическое
						return true;
				}

			}
			if (newIT_Table.table[i].idtype == 2)   // выбираем функции
			{
				if (strcmp(word, newIT_Table.table[i].id) == 0) // сравниваем имена функций
				{
					throw ERROR_THROW_IN(503, line, letter); 
				}
			}
		}
		return false; // если нет дупликатов
	}

	int FindidinTI(IT::IdTable& newIT_Table, IT::Entry& entry)
	{
		for (int i = 0; i < newIT_Table.size; i++)
		{
			if ((strcmp(entry.id, newIT_Table.table[i].id) == 0))  // сравниваем на имя
			{
				if (entry.idscope == newIT_Table.table[i].idscope) // сравеиваем на область видимости
				{
					return  i;  // возвращаем индекс лексемы
				}
				if (entry.idtype == 1 && newIT_Table.table[i].idscope=="Global") // если мы хотим добавить функцию из Global
				{
					return i;
				}
			}
			if (newIT_Table.table[i].idtype == 4 && entry.idtype==4) // выбираем литералы
			{
				if (entry.iddatatype == 2) // выбираем тип string
				{
					if (strcmp(entry.value.vstr->str, newIT_Table.table[i].value.vstr->str) == 0) // сравниваем значения string
						return i;
				}
				if (entry.iddatatype == 1) // выбираем тип int
				{
					if (entry.value.vint == newIT_Table.table[i].value.vint) // сравниваем значения integer
						return i;
				}
				if (entry.iddatatype == 1) // выбираем тип bool
				{
					if (entry.value.vbool == newIT_Table.table[i].value.vbool) // сравниваем значения bool
						return i;
				}
			}
		}
	}

	bool Call_Function(IT::IdTable& newIT_Table, char *name) // проверка на вызов функции
	{
		for (short i = 0; i < newIT_Table.size; i++)
		{
			if (newIT_Table.table[i].idtype == 2)  // выбираем функции
			{
				if (newIT_Table.table[i].idscope == "Global") // выбираем функции из глобалльной области видимости
				{
					if (strcmp(name,newIT_Table.table[i].id)==0) // если имя функций одинаково
					{
						return true;
					}
				}
			}
			
		}
		return false;
	}

	int Convert8to10(char* s) {
		
		short n = strlen(s);
		int res = 0;
		for (int i = 0; i < n; ++i) {
			res *= 8;
			res += (s[i] - '0');
		}
		return res;
	}

	void CheckEightLiteral(char*s)
	{
		if (s[0] != '0')
			return;
		else
		{
			for (short i = 1; i < strlen(s); i++)
			{
				if (s[i] != '8' || s[i] != '9')
					continue;
				else
				{
					return;
				}
			}
			int res =Convert8to10(s);
			_itoa(res, s, 10);
		}
	}

}