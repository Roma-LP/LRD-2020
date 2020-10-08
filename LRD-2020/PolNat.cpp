#include <iostream>
#include <stack>
#include "PolNat.h"
#include "IT.h"
#include "LT.h"

using namespace std;

namespace PN
{
	short i = 0;							// ������� ���������� ��������� 
	short j = 0;							// ������� ���������� �������� ������
	short length = 0;						// ����� ��������� ��������� 
	short zap;								// ������� ��� ����������� ����������
	bool call_fnuk = false;					// ������ ��� ����������, �������� �� ��� ������� �������
	short count_pn;							// ���������� ���������� �� ���������� �������� ������
	short end;								// ���������� ���������� �� ������� ����� ���������
	stack <LT::Entry> MyStack;					// ���� �����. ��������
	LT::Entry result[20];						// ��������� (�������� ������)


	bool PolishNotation(LT::LexTable& newLT_Table)
	{
		for (short i = 0; i < newLT_Table.size; i++)
		{
			if (newLT_Table.table[i].lexema == '=')  // �������� ��������� ������������ � ������� =
			{
				FindEndExpression(newLT_Table, i); // ����� ����� ���������
				ConvertingExpression(newLT_Table, i); // ���������� ����� ������ ��� ����� ������������� ���������
				WriteInTablePolNat(newLT_Table, i);   // ������ � ������� �������� ������
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
		j = 0; // �������� ������� result
		zap = 1;  // ����������������� �������� �� 1
		for (; newLT_Table.table[i].lexema != ';'; i++)  // ���� �� �������� ����� ���������
		{
			if (newLT_Table.table[i].lexema == 'i' || newLT_Table.table[i].lexema == 'l')
			{
				result[j++] = newLT_Table.table[i];
				if (newLT_Table.table[i + 1].lexema == '(') // �������� �� ����� �������, �.�. ����������� ������ ..i(..)..
					call_fnuk = true;
			}
			else
			{
				if (newLT_Table.table[i].lexema == 'v') //  �������� �� �������������� �������� (�.�. � ��� ������� v )
				{
					// ���� ��������� � ����� ������ ��� ����� (��� �� ��� �� ����� ���� ���������), ����������� � �������������� ������  
					while (!MyStack.empty() && Priority(MyStack.top().sp_smbl) >= Priority(newLT_Table.table[i].sp_smbl))
					{
						if (MyStack.top().lexema != '[')
						{
							result[j++] = MyStack.top();
							MyStack.pop();
						}
						else break;
					}
					MyStack.push(newLT_Table.table[i]);
					continue;
				}
				if (newLT_Table.table[i].lexema == ',')
				{
					zap++;  // ����� ��������� �������, ������ ��� ��� ������� +1 ��������
					// ������� �� ���������� � ����, � ���� � ����� ���� ��������, �� ��� ���������� � �������������� ������
					while (MyStack.top().sp_smbl == '+' || MyStack.top().sp_smbl == '-' || MyStack.top().sp_smbl == '*' || MyStack.top().sp_smbl == '/')
					{
						result[j++] = MyStack.top();
						MyStack.pop();
					}
					continue;
				}
				else
				{
					if (newLT_Table.table[i].lexema == '(')
					{
						MyStack.push(newLT_Table.table[i]);
						continue;
					}
					if (newLT_Table.table[i].lexema == ')')
					{
						// �� ��� ��� ����� �� �������� ����������� ������, ����������� �� ����� � �������������� ������
						while (MyStack.top().lexema != '(')
						{
							result[j++] = MyStack.top();
							MyStack.pop();
						}
						if (newLT_Table.table[i - 1].lexema == '(') // ������ �������� �� ����� ������� ��� ����������
							zap = 0;
						MyStack.pop(); // ������ ������������ (�.�. ���� �� ����� �� �����, �� ������ � ����� '(')
						if (call_fnuk)
						{
							result[j].lexema = '0' + zap;  // @+
							result[j].idxTI = LT_TI_NULLIDX;
							result[j].sn = newLT_Table.table[i].sn;
							result[j].sp_smbl = LT_NULLSPSMBL;
							zap = 1;
							call_fnuk = false;
							j++;
						}
					}
				}
			}
		}
		while (!MyStack.empty())
		{
			result[j++] = MyStack.top();
			MyStack.pop();
		}
		count_pn = j;  // ���������� ������� ����� ��� �������� �������
	}

	void WriteInTablePolNat(LT::LexTable& newLT_Table, short i)
	{
		short j;
		short n;
		for (j = i + 1, n = 0; n < count_pn; j++, n++)  // j = i+1 �.�. i ��� ����� =, � ��� ����� ��������� �������
			newLT_Table.table[j] = result[n];  // n ��� ��������� ������� ��� result ������� � ���� 

		// ����������� ���������� ��������� (�� ����� ������ �������� ������� '=' � ���������� �������� ������)
		for (short m = 1; m < end - i - count_pn; m++)
		{
			// k= �������� '=' + ���������� PolNat + 1 (��� ��� ��� ����� �������� ��������(�) �������)
			for (short k = i + count_pn + 1; k < newLT_Table.size; k++)
			{
				newLT_Table.table[k] = newLT_Table.table[k + 1];

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

