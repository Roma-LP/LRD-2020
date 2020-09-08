#pragma once
#include<iostream>
#include<string>
using namespace std;
#define IN_MAX_LEN_TEXT 1024*1024		//максимальный размер исходного кода 1МВ
#define IN_CODE_ENDL '\n'				//символ конца строки
#define SIZE 70							//дополнительный размер

//таблица проверки входной информации, индекс = код (Windows-1251) символа
//значения IN::F - запрещенный символБ IN::T - разрешенный символ, IN::I - игнорировать (не вводить),
//			если 0 <= значение < 256  - то вводиться данное значение
//		0		1	  2		3		4		5	  6	     7		8		9	  A		 B		C		D	  E		 F		
/**/#define IN_CODE_TABLE {\
/*0 */IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::F, IN::F, IN::I, IN::F, IN::F, \
/*1 */IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*2 */IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, IN::T, \
/*3 */IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, IN::T, IN::F, IN::T, IN::F, IN::T, \
/*4 */IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
/*5 */IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*6 */IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
/*7 */IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, \
/*8 */IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*9 */IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*A */IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*B */IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*C */IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
/*D */IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
/*E */IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
/*F */IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T }


namespace In {
	struct IN {		//исходные данные
		enum { T = 1024, F = 2048, I = 4096 };	//T - допустимый символ, F - недопустимый, I - игнорировать, иначе заменить
		int size;								//размер исходного кода
		int lines;								//кол-во строк
		int ignor;								//кол-во проигнорированных символов	
	//	unsigned char* text;                    //исходный код (Windows-1251)
		string text;                    //исходный код (Windows-1251)
		unsigned char* textFormated;
		long long int counterLexem; 
		int code[256]= IN_CODE_TABLE;			//таблица проверки: T, F, I новое значние
	};
	IN getIn(wchar_t infile[]);					//ввести и проверить входной поток
	void AddSymbol(unsigned char** ptr, char c);
}
