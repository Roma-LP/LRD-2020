#include "Error.h" // обработка ошибок
#include "Parm.h" // обработка параметров
#include "Log.h" // работа с протоколом
#include "In.h" // ввод исходного Файла
#include "FST.h"
#include <iostream>
#include <locale>
#include <cwchar>
#include "LexAn.h"
#include "MFST.h"
#include "PolNat.h"
#include "Generation.h"
#include "SemAn.h"

int wmain(int argc, const wchar_t * argv[])
{
	setlocale(LC_ALL, "Russian");
	Log::LOG log = Log::INITLOG;

	try
	{
		Parm::PARM parm = Parm::getParm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"Тест: ", L"без ошибок\n", L"");
		Log::WriteLog(log);
		In::IN in = In::getIn(parm.in);
		Log::WriteInsideTextTo_OutFile(parm, in);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);

		LT::LexTable newLT_Table = LT::Create(in.counterLexem);
		IT::IdTable  newIT_Table = IT::Create(in.counterLexem);
		LA::LexicalAnalizator(in, newLT_Table, newIT_Table);
		Log::WtiteTables(log, newLT_Table, newIT_Table);

		MFST::Mfst mfst(newLT_Table, GRB::getGreibach());
		MFST_TRACE_START(log);
		mfst.start(log);
		mfst.savededucation();
		mfst.printrules(log);

		//PN::PolishNotation(newLT_Table);
		//Log::WritePN(log, newLT_Table);

		//SA::Typecheck(newLT_Table, newIT_Table);
		//SA::FuncRet(newLT_Table, newIT_Table);
		//SA::CheckArgs(newLT_Table, newIT_Table);
		//SA::OutData(newLT_Table, newIT_Table);

		//GN::Generation(newLT_Table, newIT_Table);

		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;

};

