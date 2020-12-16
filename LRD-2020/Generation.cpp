#include <fstream>
#include "Generation.h"

namespace GN
{
	ofstream fout("Generation.html");
	short posmain;          // ������� ������� ������� main
	short index;            // ������ ��� ������ ��������������

	void Head()
	{
		fout << "<!doctype html>" << endl;
		fout << "<html>" << endl;
		fout << "	<head>" << endl;
		
		fout << "		<title>LRD-2020</title>" << endl;
		fout << "		<script src=\"lib.js\"></script>" << endl << endl;
		fout << "		<script type=\"text/javascript\">" << endl << endl;
		fout << "		main()" << endl << endl;
	}
	void Down()
	{
		fout << "		</script>" << endl;
		fout << "	</head>" << endl;
		fout << "	<body>" << endl;
		fout << "	</body>" << endl;
		fout << "</html>" << endl;
		fout.close();
	}



	void Generation(LT::LexTable &newLT_Table, IT::IdTable& newIT_Table)
	{
		short j;
		Head();
		for (int i = 0; i < newLT_Table.size; i++)
		{
			j = newLT_Table.table[i].sn;					// ���������� ����� ������� ������
			for (; newLT_Table.table[i].sn == j; i++)				// ���� ����� ������ ��������� � �������
			{
				switch (newLT_Table.table[i].lexema)
				{
					case LEX_VAR:  // LEX_STRING LEX_BOOL
					{
						if (IsProtoStaticLib(i, newLT_Table))  // �������� �� �������� ����������� ���������� 
						{
							while (newLT_Table.table[i].lexema != ';')
							{
								i++;
							}
							continue;  // � ���� ��� ���, �� ����������
						}
						fout << "var ";
						break;
					}
					case LEX_MAIN:
					{
						fout << "function main()";
						break;
					}
					case LEX_ID:
					{
						index = newLT_Table.table[i].idxTI;
						char* name = newIT_Table.table[index].id;
						fout << name;
						break;
					}
					case LEX_LITERAL:
					{
						OutValue(i, newLT_Table, newIT_Table);
						break;
					}
					case LEX_FUNCTION:
					{
						fout << "function ";
						break;
					}
					case LEX_RETURN:
					{
						fout << "return ";
						break;
					}
					case LEX_PRINT:
					{
						index = newLT_Table.table[i+1].idxTI;  // +1 ��� ��� ��� ����� �����, ��� �� ����� �������
						if (newIT_Table.table[index].idtype == 2)  // �������� �� �������
						{
							fout << "document.writeln(";
							while (newLT_Table.table[i+1].lexema != ';')
							{
								OutValue(i + 1, newLT_Table, newIT_Table);  // +1 ��� ��� ��� ����� ������� ����������, � �� ������� print
							i++;
							}
							fout << ")";
							continue;  // � ���� ��� ���, �� ����������
						}
						fout << "document.writeln(";
						OutValue(i+1, newLT_Table, newIT_Table);  // +1 ��� ��� ��� ����� ������� ����������, � �� ������� print
						i++; //��������� �.�. ��� ���� ���������� ����������, ������� ��� ������
						fout << ")";
						break;
					}
					case 'o':
					{
						fout << newLT_Table.table[i].sp_smbl;
						break;
					}
					case LEX_IF:
					{
						fout << "if";
						break;
					}
					case LEX_ELSE:
					{
						fout << "else";
						break;
					}
					case LEX_COMMA: 
					case LEX_EQUAL:
					case LEX_RIGHTHESIS:
					case LEX_LEFTHESIS:
					case LEX_LEFTBRACE:
					case LEX_BRACELET:
					case LEX_SEMICOLON:
					{
						fout << newLT_Table.table[i].lexema;
						break;
					}
				}
			}
			i--;											// ������� ��������, �.�. ���� for � �������
			fout << endl;							// ��������� ������� ������ ��� ����� ������
			
		}
		Down();
	}

	void OutValue(short i, LT::LexTable &newLT_Table, IT::IdTable& newIT_Table)
	{
		index = newLT_Table.table[i].idxTI;
		if(index!=-1)
		{
			switch (newIT_Table.table[index].idtype)  // ������� ��� ��������������
			{
			case 1:
			case 2:
			case 3:
			{
				fout << newIT_Table.table[index].id;
				return;
			}
			case 4:
			{
				if (newIT_Table.table[index].iddatatype == (IT::IDDATATYPE) 1)
				{
					fout << newIT_Table.table[index].value.vint;
					return;
				}
				if (newIT_Table.table[index].iddatatype == (IT::IDDATATYPE) 2)
				{
					fout << (char*)newIT_Table.table[index].value.vstr->str;
					return;
				}
				if (newIT_Table.table[index].iddatatype == (IT::IDDATATYPE) 3)
				{
					fout << newIT_Table.table[index].value.vbool;
					return;
				}
				if (newIT_Table.table[index].iddatatype == (IT::IDDATATYPE) 4)
				{
					fout << (char*)newIT_Table.table[index].value.vstr->str;
					return;
				}
			}
			
			}
		}
		else
		{
				fout << newLT_Table.table[i].lexema;
		}
	}

	bool IsProtoStaticLib(short i, LT::LexTable &newLT_Table)
	{
		if (newLT_Table.table[i + 2].lexema == 'f')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}