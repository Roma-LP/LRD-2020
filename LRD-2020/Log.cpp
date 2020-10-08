#include <iostream>
#include <ctime>
#include "Parm.h"
#include "Log.h"
#include "Error.h"
#include "LT.h"
#include "IT.h"
#include "In.h"
#include <fstream>
#include <cstdlib>

namespace Log
{
	LOG Log::getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new std::ofstream;
		log.stream->open(logfile);
		if (!log.stream->is_open())
			throw ERROR_THROW(112);
		wcscpy_s(log.logfile, logfile);
		return log;
	}

	void WriteLine(LOG log, const char *c, ...)
	{
		const char **ptr = &c;

		while (*ptr != "")
		{
			*log.stream << *ptr;
			ptr++;
		}
	}

	void WriteLine(LOG log, const wchar_t* wc, ...)
	{
		const wchar_t **ptr = &wc;

		char temp[100];

		while (*ptr != L"")
		{
			wcstombs(temp, *ptr++, sizeof(temp));
			*log.stream << temp;
		}
	}

	void WriteLog(LOG log)
	{
		time_t rawtime;
		struct tm timeinfo;			//структура хранящая текущее время
		char buffer[100];

		time(&rawtime);					//текущая дата в секундах
		localtime_s(&timeinfo, &rawtime);	//текущее локальное время, представленное в структуре

		*log.stream << "-----Протокол----- " << endl;
		strftime(buffer, 100, "Дата: %d.%m.%Y %A %H:%M:%S", &timeinfo);
		*log.stream << buffer << endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char inInfo[PARM_MAX_SIZE];
		char outInfo[PARM_MAX_SIZE];
		char logInfo[PARM_MAX_SIZE];

		wcstombs(inInfo, parm.in, sizeof(inInfo));
		wcstombs(outInfo, parm.out, sizeof(outInfo));
		wcstombs(logInfo, parm.log, sizeof(logInfo));

		*log.stream << "\n-----Параметры----- " << endl;
		*log.stream << "-in:\t" << inInfo << endl;
		*log.stream << "-log:\t" << logInfo << endl;
		*log.stream << "-out:\t" << outInfo << endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "\n-----Исходные данные----- " << endl;
		*log.stream << "Количество символов: " << in.size << endl;
		*log.stream << "Проигнорировано    : " << in.ignor << endl;
		*log.stream << "Количество строк   : " << in.lines + 1 << endl << endl;
	}

	void WriteInsideTextTo_OutFile(Parm::PARM parm, In::IN in)
	{
		ofstream outFile;
		outFile.open(parm.out);

		if (!outFile)
			ERROR_THROW(1);

		outFile << in.textFormated;
		outFile.close();
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		if (error.id == 100 || error.id == 113)
		{
			*log.stream << "ОШИБКА " << error.id << ": " << error.message << "\n";
			cout << "ОШИБКА " << error.id << ": " << error.message << "\n";
		}
		else
		{
			*log.stream << "ОШИБКА " << error.id << ": " << error.message << "\n"
				<< "Строка " << error.inext.line << ", позиция: " << error.inext.column << endl;
			cout << "ОШИБКА " << error.id << ": " << error.message << "\n"
				<< "Строка " << error.inext.line << ", позиция: " << error.inext.column << endl;
		}
		log.stream->close();
	}

	void WtiteTables(LOG log, LT::LexTable newLT_Table, IT::IdTable newIT_Table)
	{
		short j;
		*log.stream << "Таблица лексем:" << endl;
		for (int i = 0; i < newLT_Table.size; i++)
		{
			*log.stream << newLT_Table.table[i].sn << '\t';		// вывод номера строки
			j = newLT_Table.table[i].sn;					// записываем номер текущей строки
			for (; newLT_Table.table[i].sn == j; i++)				// пока номер строки совпадает с текущей
			{
				*log.stream << newLT_Table.table[i].lexema;	// выводим лексему текущей строки
				if (newLT_Table.table[i].idxTI != LT_TI_NULLIDX)       // вывод ссылок
					*log.stream << "[" << newLT_Table.table[i].idxTI << "]";
				if (newLT_Table.table[i].sp_smbl != LT_NULLSPSMBL)		// вывод арифметической операции
					if (newLT_Table.table[i].lexema != '(' && newLT_Table.table[i].lexema != ')')
						*log.stream << "[" << newLT_Table.table[i].sp_smbl << "]";
			}
			i--;											// удаляем единичку, т.к. цикл for(121) её добавит
			*log.stream << endl;							// добавляем переход строки для новой строки
		}
		*log.stream << endl << endl << endl << "Таблица идентификаторов:" << endl;
		*log.stream << "Идентификатор: \t" << "Тип: \t\t" << "Тип данных: \t" << "Область видимости: \t" << "Значение: \t" << "Номер первого вхождения:" << endl;
		for (int i = 0; i < newIT_Table.size; i++)
		{
			*log.stream << newIT_Table.table[i].id << "\t\t";		// вывод идентификатора

			switch (newIT_Table.table[i].idtype)					// вывод Тип(переменная, функция, параметр, литерал) идентификатора
			{
			case 1: {*log.stream << "Переменная" << "\t"; break; }
			case 2: {*log.stream << "Функция   " << "\t"; break; }
			case 3: {*log.stream << "Параметр  " << "\t"; break; }
			case 4: {*log.stream << "Литерал   " << "\t"; break; }
			}

			switch (newIT_Table.table[i].iddatatype)				// вывод Тип данных(integer, string) идентификатора
			{
			case 1: {*log.stream << "integer" << "\t\t"; break; }
			case 2: {*log.stream << "string " << "\t\t"; break; }
			case 3: {*log.stream << "boolean" << "\t\t"; break; }
			}

			*log.stream << newIT_Table.table[i].idscope << "\t\t\t";  // вывод области видимости идентификатора

			switch (newIT_Table.table[i].iddatatype)						// вывод значения идентификатора
			{
			case 1: {*log.stream << newIT_Table.table[i].value.vint; break; }
			case 2: {*log.stream << newIT_Table.table[i].value.vstr->str; break; }
			case 3: {*log.stream << newIT_Table.table[i].value.vbool; break; }
			}

			*log.stream << "\t\t\t" << newIT_Table.table[i].idxfirstLE << endl; // вывод первого вхождения идентификатора

			if (i % 4 == 0 && i != 0)  // отступ в таблице через каждые 4 строки
				*log.stream << endl;
		}

	}

	void WritePN(Log::LOG log, LT::LexTable& newLT_Table)
	{
		typedef LT::LexTable& lt;
		short j;
		*log.stream << "Таблица лексем (Польская запись):" << endl;
		cout << "Таблица лексем (Польская запись):" << endl;
		for (int i = 0; i < newLT_Table.size; i++)
		{
			*log.stream << newLT_Table.table[i].sn << '\t';		// вывод номера строки
			cout << newLT_Table.table[i].sn << '\t';		// вывод номера строки
			j = newLT_Table.table[i].sn;					// записываем номер текущей строки
			for (; newLT_Table.table[i].sn == j; i++)				// пока номер строки совпадает с текущей
			{
				*log.stream << newLT_Table.table[i].lexema;	// выводим лексему текущей строки
				cout << newLT_Table.table[i].lexema;	// выводим лексему текущей строки
				if (newLT_Table.table[i].sp_smbl != LT_NULLSPSMBL)		// вывод арифметической операции
					if (newLT_Table.table[i].lexema != '(' && newLT_Table.table[i].lexema != ')')
					{

						*log.stream << "[" << newLT_Table.table[i].sp_smbl << "]";
						cout << "[" << newLT_Table.table[i].sp_smbl << "]";
					}
			}
			i--;											// удаляем единичку, т.к. цикл for(121) её добавит
			*log.stream << endl;							// добавляем переход строки для новой строки
			cout << endl;							// добавляем переход строки для новой строки
		}
	}

	void Close(LOG log)
	{
		(*log.stream).close();
	}
}