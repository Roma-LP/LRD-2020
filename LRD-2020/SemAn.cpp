#include "SemAn.h"

namespace SA
{
	short startMain;
	stack<IT::IDDATATYPE> CallParam;						 // ��������� ������ ������� (����)
	stack<IT::IDDATATYPE> PrototypeParam;					 // ��������� ��������� ������� (����)
	short index;

	void Typecheck(LT::LexTable& newLT_Table, IT::IdTable& newIT_Table)
	{
		
		for (short i = 0; i < newLT_Table.size; i++)
		{
			if (newLT_Table.table[i].lexema == 'm')
			{
				startMain = i;
				break;  // ���� ������ �����
			}
		}

		for (short i = 0; i < newIT_Table.size; i++)
		{
			if (newIT_Table.table[i].idtype == 2) // ���� ������� � ������� �����
			{
				FindAndCheck(i, newLT_Table, newIT_Table);
			}

		}
	}

	void FindAndCheck(short num, LT::LexTable& newLT_Table, IT::IdTable& newIT_Table)
	{
		for (short i = startMain; i < newLT_Table.size; i++)
		{
			if (newLT_Table.table[i].idxTI == num && newLT_Table.table[i-1].lexema!='f')  // ���� ���� �������
			{
				i++; // ������� � ��������� ������� 
				for (; newLT_Table.table[i].lexema != ';' ; i++) // ���� �� ����� ���������
				{
					if (Registration(newLT_Table.table[i].lexema))
					{
						continue;
					}
					index = newLT_Table.table[i].idxTI;
					CallParam.push(newIT_Table.table[index].iddatatype);
				}
				for (short i = num; i < newIT_Table.size; i++)  // �������� ��������� ���� ��� ��������
				{
					if (newIT_Table.table[i + 1].idtype == 3)  // ���� ��������
					{
						PrototypeParam.push(newIT_Table.table[i + 1].iddatatype); // ������ � ����
					}
					else
						break;
				}
			}
		}
		ParamCheck(CallParam.size(), PrototypeParam.size()); // �������� �� ���������� ����������

		for (short i = 0; i < CallParam.size(); i++)
		{
			if (CallParam.top() == PrototypeParam.top()) // �������� �� �������������
			{
				CallParam.pop();
				PrototypeParam.pop();
			}
			else
			{
				throw ERROR_THROW(700);
			}
		}
	}

	bool Registration(char c)
	{
		switch (c)
		{
		case '(':
		case ')':
		case ',':
		{
			return true;
		}
		default:
			return false;
		}
	}

	void ParamCheck(short a, short b)
	{
		if (a == b)
			return;
		else
			throw ERROR_THROW(701);
	}

	void FuncRet(LT::LexTable& newLT_Table, IT::IdTable& newIT_Table)
	{
		short typefunk;
		short typerereturn;
		bool isMain=false;

		for (short i = 0; i < newLT_Table.size; i++)
		{
			if (newLT_Table.table[i].lexema == 'f' && newLT_Table.table[i-2].lexema!='v')
			{
				index = newLT_Table.table[i+1].idxTI;  // ���������� ���������
				typefunk = newIT_Table.table[index].iddatatype;
			}
			if (newLT_Table.table[i].lexema == 'm')
			{
				isMain = true;
				typefunk = 0;
			}
			if (newLT_Table.table[i].lexema == 'r')
			{
				index = newLT_Table.table[i+1].idxTI;
				typerereturn = newIT_Table.table[index].iddatatype;
				if (isMain)
				{
					index = newLT_Table.table[i + 1].idxTI;
					switch (newIT_Table.table[index].iddatatype)
					{
					case 1:
					{
						typerereturn = newIT_Table.table[index].value.vint;
						break;
					}
					case 3:
					{
						typerereturn = newIT_Table.table[index].value.vbool;
						break;
					}
					default:
						typerereturn = -1;
						break;
					}
				}
				if (!(typefunk== typerereturn))
					throw ERROR_THROW_IN(703, newLT_Table.table[i + 1].sn,-1);
			}
		}
	}

	void CheckArgs(LT::LexTable& newLT_Table, IT::IdTable& newIT_Table)
	{
		short typevar;
		for (short i = 0; i < newLT_Table.size; i++)
		{
			if (newLT_Table.table[i].lexema == '=')
			{
				index = newLT_Table.table[i-1].idxTI;  // ���������� ���������
				typevar = newIT_Table.table[index].iddatatype;

				for (; newLT_Table.table[i].lexema != ';'; i++)
				{
					if (newLT_Table.table[i].lexema == 'l' || newLT_Table.table[i].lexema == 'i')
					{
						index = newLT_Table.table[i].idxTI;  // ���������� ���������
						if (typevar != newIT_Table.table[index].iddatatype)
							throw ERROR_THROW_IN(702, newLT_Table.table[i].sn, -1);
					}
				}
			}
		}
	}

	void OutData(LT::LexTable& newLT_Table, IT::IdTable& newIT_Table)
	{
		short sum = 0;
		for (short i = 0; i < newLT_Table.size; i++)
		{
			if (newLT_Table.table[i].lexema == '=')
			{
				for (; newLT_Table.table[i].lexema != ';'; i++)
				{
					if (newLT_Table.table[i].lexema == 'l')
					{
						index = newLT_Table.table[i].idxTI;  // ���������� ���������
						switch (newIT_Table.table[index].iddatatype)
						{
						case 1:
						{
							sum += newIT_Table.table[index].value.vint;
							break;
						}
						case 2:
						{
							sum += newIT_Table.table[index].value.vstr->len;
							break;
						}
						default:
						break;
						}
					}
				}
				if ( sum > 127 || -128 > sum)
				{
					throw ERROR_THROW_IN(704, newLT_Table.table[i].sn, -1);
				}
				sum = 0;
			}
		}
	}

}