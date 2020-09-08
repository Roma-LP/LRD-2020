#include "Parm.h"
#include "Error.h"
#include <iostream>
#include <locale>
#include <cwchar>
#include <cstring>



namespace Parm {

	PARM getParm(int argc, const wchar_t* argv[]) {
		bool in = false, out = false, log = false;
		int i = argc;
		wchar_t forout[PARM_MAX_SIZE] = L"";
		wchar_t forlog[PARM_MAX_SIZE] = L"";
		wchar_t forin[PARM_MAX_SIZE] = L"";

		PARM e;

		for (int i = 0; i < argc; i++) {
			if (wcslen(*(argv + i)) > ERROR_MAXSIZE_MESSAGE) { throw ERROR_THROW(104) }
			int size = wcslen(*(argv + i));
		}

		for (int i = 0; i < argc; i++)
		{
			if (wcsstr(*(argv + i), PARM_OUT))
			{
				out = true;
				const wchar_t *a = wcsstr(*(argv + i), (wchar_t*)L"C");
				wcsncpy_s(e.out, a, wcslen(a));
				break;
			}
		}
		for (int i = 0; i < argc; i++)
		{
			if (wcsstr(*(argv + i), PARM_LOG))
			{
				log = true;
				const wchar_t *a = wcsstr(*(argv + i), (wchar_t*)L"C");
				wcsncpy_s(e.log, a, wcslen(a));
				break;

			}
		}
		for (int i = 0; i < argc; i++)
		{
			if (wcsstr(*(argv + i), PARM_IN))
			{

				in = true;
				const wchar_t *a = wcsstr(*(argv + i), (wchar_t*)L"C");
				

				wcsncpy_s(forout, a, wcslen(a));
				wcsncpy_s(forlog, a, wcslen(a));
				wcsncpy_s(forin, a, wcslen(a));

				if(AddTXT(a, wcslen(a)))
					wcsncat_s(forin, TXT, wcslen(TXT));   //добавление .txt к файлу in
				wprintf(L"%ls\n", forin);
				wcsncpy_s(e.in, forin, wcslen(forin));
				break;
			}
		}
		if (!in) throw ERROR_THROW(100);
		if (!out) {
			wcsncat_s(forout, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT));
			wprintf(L"%ls\n", forout);
			wcsncpy_s(e.out, forout, wcslen(forout));
		}

		if (!log) {
			wcsncat_s(forlog, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));
			wprintf(L"%ls\n", forlog);
			wcsncpy_s(e.log, forlog, wcslen(forlog));
		}

		

		return e;

	}

	bool AddTXT(const wchar_t *Filein, int size)
	{
		int pos=-1; // позиция начала расширения файла
		for (int i = 0; i < size; i++)
		{
			if (Filein[i] == '.')
				pos = i;
		}
		if (pos == -1)
			return true;
		if (Filein[pos + 1] == 't' && Filein[pos + 2] == 'x' && Filein[pos + 3] == 't')
			return false;
		else
			return true;
	}
};