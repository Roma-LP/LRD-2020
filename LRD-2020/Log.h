/*#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"

#pragma warning(disable: 4996)

using namespace std;

namespace Log
{
	struct LOG
	{
		wchar_t *logfile;
		ofstream *stream;

		LOG()
		{
			this->logfile = new wchar_t[PARM_MAX_SIZE];
			this->stream = new ofstream;
		}
	};

	LOG getlog(wchar_t *logfile);
	void WriteLine(LOG log, const char *c, ...);
	void WriteLine(LOG log, const wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::IN in);
	void WriteKey(LOG log, char*c, bool b);
	void WriteError(LOG log, Error::ERROR error);
	void Close(LOG log);
	void WriteInsideTextTo_OutFile(Parm::PARM parm, In::IN in);
}
*/

#pragma once
#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "LT.h"
#include "IT.h"
using namespace std;
namespace Log   // ������ � ����������
{
	struct LOG   //��������
	{
		wchar_t logfile[PARM_MAX_SIZE];   // ��� ����� ���������
		std::ofstream* stream;			  // �������� ����� ��������� 
	};
	static const LOG INITLOG = { L"", NULL };					// ��������� ��� ��������� ������������� LOG
	LOG getlog(wchar_t logfile[]);								// ������������ ��������� LOG
	void WriteLine(LOG log, const char *c, ...);				// ������� � �������� ������������ �����
	void WriteLine(LOG log, const wchar_t *c, ...);				// ������� � �������� ������������ �����
	void WriteLog(LOG log);										// ������� � �������� ���������
	void WriteParm(LOG log, Parm::PARM parm);					// ������� � �������� ���������� � �������� ����������
	void WriteIn(LOG log, In::IN in);							// ������� � �������� ���������� � ������� ������
	void WriteError(LOG log, Error::ERROR error);				// ������� � �������� ���������� �� ������
	void Close(LOG log);										// ������� ��������
	void WriteInsideTextTo_OutFile(Parm::PARM parm, In::IN in); // ������ � ���� out
	void WtiteTables(LOG log, LT::LexTable newLT_Table, IT::IdTable newIT_Table);  // ����� ������
	void WritePN(Log::LOG log, LT::LexTable& newLT_Table);		// ������ �������� ������ � ����
};