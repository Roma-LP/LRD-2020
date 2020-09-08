#include <iostream>
#include <stack>
#include "PolNat.h"
#include "IT.h"
#include "LT.h"

using namespace std;

namespace PN
{
	short i = 0;							// счетчик начального выражения 
	short j = 0;							// счетчик результата польской записи
	short length = 0;						// длина исходного выражения 
	short zap;								// счетчик для определения параметров
	bool call_fnuk = false;					// флажок для опрделения, является ли это вызовом функции
	short count_pn;							// переменная отвечающая за количество польской записи
	short end;								// переменная отвечающая за позицию конца выражения
	stack <LT::Entry> MyStack;					// стэк арифм. операций
	LT::Entry result[20];						// результат (польская запись)


	bool PolishNotation(LT::LexTable& newLT_Table)
	{
		for (short i = 0; i < newLT_Table.size; i++)
		{
			if (newLT_Table.table[i].lexema == '=')  // выбираем выражения начинающиеся с лексемы =
			{
				FindEndExpression(newLT_Table, i); // посик конца выражения
				ConvertingExpression(newLT_Table, i); // отправляем номер начала где нужно преобразовать выражение
				WriteInTablePolNat(newLT_Table, i);   // запись в таблицу польской записи
			}
		}
		return (result != NULL ? true : false);
	}

	int Priority(char c)
	{
		if (c == ')' || c == '(')
		{
			return 0;
		}
		if (c == ',')
		{
			return 1;
		}
		if (c == '+' || c == '-')
		{
			return 2;
		}
		if (c == '*' || c == '/')
		{
			return 3;
		}
		return -1;
	}

	void ConvertingExpression(LT::LexTable& newLT_Table, short i)
	{
		j = 0; // обнуляем счетчик result
		zap = 1;  // переустанавливаем значение на 1
		for (; newLT_Table.table[i].lexema != ';'; i++)  // пока не встретим конец выражения
		{
			
		}
		
	}

	void WriteInTablePolNat(LT::LexTable& newLT_Table, short i)
	{
		short j;
		short n;
		for ( j = i + 1, n = 0; n < count_pn; j++,n++)  // j = i+1 т.к. i это номер =, а нам нужна следующая позиция
			newLT_Table.table[j] = result[n];  // n это отдельный счетчик для result начиная с нуля 

		// высчитываем количестов переносов (от окнца строки отнимаем позицию '=' и количество польской записи)
		for (short m=1;m<end-i- count_pn;m++)   
		{
			// k= позициии '=' + количество PolNat + 1 (так как нам нужно сдвигать следующи(е) лексемы)
			for (short k = i+count_pn+1; k < newLT_Table.size; k++)  
			{
				newLT_Table.table[k] = newLT_Table.table[k+1];
				
			}
			//delete newLT_Table.table[newLT_Table.size];
			newLT_Table.size--;
		}
	}

	void FindEndExpression(LT::LexTable& newLT_Table, short i)
	{
		while (newLT_Table.table[i].lexema != ';')
			i++;
		end = i;
	}
}

