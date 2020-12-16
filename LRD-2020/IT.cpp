#include "IT.h"
#include "Error.h"
#include <string.h>
#include <iostream>

namespace IT
{
	/* ������� ������� ���������������*/
	IdTable Create(int size)	// ������� ������� ��������������� < TI_MAXSIZE
	{
		if (size >= TI_MAXSIZE)
			throw ERROR_THROW(114);
		IdTable itable = { size, 0, new Entry[size] };
		return itable;
	}

	/* �������� ������ � ������� ���������������*/
	void Add(IdTable& idtable, Entry entry)  //��������� ������� ���������������, ������ ������� ���������������
	{
		idtable.table[idtable.size++] = entry;
		if (idtable.size >= idtable.maxsize)
			throw ERROR_THROW(113);
	}

	/*�������� ������ ������� ���������������*/
	Entry GetEntry(IdTable& idtable, int n) //��������� ������� ���������������, ����� ���������� ������
	{
		if (idtable.size < n || n < 0)
			throw ERROR_THROW(6);
		return idtable.table[n];
	}

	/*�������: ����� ������ (���� ����), TI_NULLIDX(���� ���)*/
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]) //��������� ������� ���������������, �������������
	{
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id, id) == 0) {
				return i;
			}
		}
		return TI_NULLIDX;
	}

	/*������� ������� ������ (���������� �������)*/
	void Delete(IdTable& ID_MAXSIZEidtable)
	{
		if (!&ID_MAXSIZEidtable)
			throw ERROR_THROW(3);
		delete ID_MAXSIZEidtable.table;
		ID_MAXSIZEidtable.table = nullptr;
	}

	Entry createStructId(char* id, int line, int typeData, int typeID, std::string typeScope, short* countLiteral)
	{
		IT::Entry newItEntry;
		if (typeID == 4)   // �������� �� �������
		{
			char numberCH[3];   // ���������� ��� �����
			_itoa_s(*countLiteral, numberCH, 10);  // ��������� ����� � ������
			char str[7] = "Lit_";  // ��� ��� ��������
			strcat_s(str, numberCH);  // ���������� ��� � �������
			strcpy(newItEntry.id, str); // ��������� (��������) � ��������� ���
			newItEntry.iddatatype = (IT::IDDATATYPE) typeData;
			newItEntry.idtype = (IT::IDTYPE) typeID;
			newItEntry.idscope = typeScope;
			newItEntry.idxfirstLE = line;
			switch ((int)newItEntry.iddatatype)
			{
			case 1: { // integer
				newItEntry.value.vint = atoi(id);
				break;
			}
			case 4:   // char
			case 2: { // string
				newItEntry.value.vstr->len = strlen(id);
				strcpy_s(newItEntry.value.vstr->str, id);
				break;
			}
			case 3: { // bool
				if (strcmp(id, "true") == 0)
				{
					newItEntry.value.vbool = 1;
				}
				else
				{
					if (strcmp(id, "false") == 0)
					{
						newItEntry.value.vbool = 0;
					}
				}
				//newItEntry.value.vbool = atoi(id);
				break;
			}
			default:std::cout << "�������1 ��� " << newItEntry.id;
			}
		}
		else  // ���� ��� �� �������
		{
			short n = strlen(id); // ����� �������������� 
			int i = 0;
			if (isStLib(id))  //�������� �� ����������� ����������
			{
				for (i = 0; i < n; i++) // ��� ������� �����
				{
					newItEntry.id[i] = id[i];
				}
			}
			else
			{
				for (i = 0; (i < n) && (i < ID_MAXSIZE); i++) // ������� �����
				{
					newItEntry.id[i] = id[i];
				}
			}
			newItEntry.id[i] = '\0'; // ����� ��������������
			newItEntry.iddatatype = (IT::IDDATATYPE) typeData;
			newItEntry.idtype = (IT::IDTYPE) typeID;
			newItEntry.idscope = typeScope;
			newItEntry.idxfirstLE = line;
			switch ((int)newItEntry.iddatatype) // ��������� �������� �� ���������
			{
			case 1: { // integer
				newItEntry.value.vint = TI_INT_DEFAULT;
				break;
			}
			case 4:   // char
			case 2: { // string
				newItEntry.value.vstr->len = 0;
				newItEntry.value.vstr->str[0] = TI_STR_DEFAULT;
				newItEntry.value.vstr->str[1] = '\0';
				break;
			}
			case 3: { // bool
				newItEntry.value.vbool = TI_BOOL_DEFAULT;
				break;
			}
			default:std::cout << "�������4 ��� " << newItEntry.id;
			}
		}
		return newItEntry;
	}
	/*�������� �� ����������� �����������*/
	bool isStLib(char* id)
	{
		if (strcmp(id, "strcat") == 0) return true;
		if (strcmp(id, "strcpy") == 0) return true;

		if (strcmp(id, "substr") == 0) return true;
		if (strcmp(id, "strlen") == 0) return true;

		if (strcmp(id, "cntchstr") == 0) return true;
		if (strcmp(id, "strtoint") == 0) return true;

		return false;
	}

}

