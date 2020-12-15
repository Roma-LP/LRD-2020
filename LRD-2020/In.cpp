#include "In.h"
#include "Parm.h"
#include "Error.h"
#include <iostream>
#include <locale>
#include <cwchar>
#include <fstream>
using namespace std;

ifstream reading;
namespace In {
	IN In::getIn(wchar_t infile[]) {
		IN in;
		unsigned char s;
		in.text ="";
		in.size = 0;
		in.lines = 0;
		in.ignor = 0;
		short letter = 0;
		int inCode[256] = IN_CODE_TABLE;
		reading.open(infile);
		if (reading.fail())throw ERROR_THROW(110);

		while (reading.read((char*)&s, 1)) {
			if ((unsigned int)s > 0 && (unsigned int)s < 256)
			{
				if (inCode[(unsigned int)s] == in.F)
				{
					cout<<endl<< s << endl;
					throw ERROR_THROW_IN(111, in.lines, letter);
				}
				else if (inCode[(unsigned int)s] == in.T)
				{
					if (s == IN_CODE_ENDL)
					{
						in.lines++;
						letter = 0;
						in.text += s;
					}
					else
						in.text += s;
				}
				else if (inCode[(unsigned int)s] == in.I)
				{
					in.ignor++;
				}
				else
				{
					in.text += inCode[(unsigned int)s];
				}
			}
			letter++;
			in.size++;
		}

		in.textFormated = new unsigned char[in.size*1.5];
		unsigned char *ptrText = in.textFormated; //указатель на наш текст
		bool spaceAdded = false;
		bool qAdded = false;
		int j = 0;
		for (j = 0; j < in.size; j++)
		{
			if (in.text[j] == '\n' || in.text[j] == '\t' || in.text[j] == ' ')
			{
				continue;
			}
			else
			{
				break;
			}
		}
		for (int i = j; i < in.size; i++)
		{
			
			if (qAdded)
			{
				if (in.text[i] != '"' && in.text[i] != '\'')
				{
					AddSymbol(&ptrText, in.text[i]);
					continue;
				}
			}
			if (in.text[i] != ' ')
			{
				if (in.text[i] == ';' || in.text[i] == ','  || in.text[i] == '+'  || in.text[i] == '/'  || in.text[i] == '~' ||
					in.text[i] == '-' || in.text[i] == '*'  || in.text[i] == '='  || in.text[i] == '\'' || in.text[i]=='"' ||
					in.text[i] == '(' || in.text[i] == ')'  || in.text[i] == '{'  || in.text[i] == '|' ||
					in.text[i] == '}' || in.text[i] == '\n' || in.text[i] == '\t' || in.text[i] == '&' )
				{
					if (in.text[i] == '"' || in.text[i] == '\'')
					{
						AddSymbol(&ptrText, in.text[i]);
						qAdded = !qAdded;
						spaceAdded = false;
						continue;
					}
					if (in.text[i] == '\t')
					{
						continue;
					}
					if (in.text[i] == '\n')
					{
						if (in.text[i + 1] == '\n')
						{
							continue;
						}
						else {
							
								if (spaceAdded)
								{
									//AddSymbol(&ptrText, '|');
									AddSymbol(&ptrText, '\n');
									spaceAdded = true;
									continue;
								}
								else
								{
									AddSymbol(&ptrText, ' ');
									//AddSymbol(&ptrText, '|');
									AddSymbol(&ptrText, '\n');
									spaceAdded = true;
									continue;
								}
							
						}
					}
					if (spaceAdded && in.text[i] != ' ')
					{
						AddSymbol(&ptrText, in.text[i]);
						AddSymbol(&ptrText, ' ');
						spaceAdded = true;
					}
					if (!spaceAdded && in.text[i] != ' ')
					{
						AddSymbol(&ptrText, ' ');
						AddSymbol(&ptrText, in.text[i]);
						AddSymbol(&ptrText, ' ');
						spaceAdded = true;
					}
				}
				else {
					AddSymbol(&ptrText, in.text[i]);
					spaceAdded = false;
				}
			}
			else {
				if (in.text[i + 1] == ' ')
				{
					continue;
				}
				else
				{
					if (spaceAdded && in.text[i] != ' ')
					{
						AddSymbol(&ptrText, in.text[i]);
						spaceAdded = true;
					}
					if (!spaceAdded && in.text[i] != ' ')
					{
						AddSymbol(&ptrText, ' ');
						AddSymbol(&ptrText, in.text[i]);
						spaceAdded = true;
					}
				}
				if (!spaceAdded) {
					AddSymbol(&ptrText, ' ');
					spaceAdded = true;
				}
			}
			//if (in.text[i+1] == '\'')
				//cout << "69";
		}
		AddSymbol(&ptrText, '\0');

		short counterLexem = 0;
		qAdded = false;
		for (int i = 0; i < strlen((char*)in.textFormated); i++)
		{
			if (in.textFormated[i] == '\'' || in.textFormated[i] == '"')
				qAdded = !qAdded;

			if (in.textFormated[i] == ' ' && !qAdded)
			{
				counterLexem++;
			}
		}
		in.counterLexem = counterLexem;
		reading.close();
		return in;
	}

	void AddSymbol(unsigned char** ptr, char c)
	{
		**ptr = c;
		*(*ptr)++;
	}
};

/*
if (in.text[i] != ' ')
			{
				if ( in.text[i] == ';' || in.text[i] == ',' || in.text[i] == '+' ||
					 in.text[i] == '-' || in.text[i] == '*' || in.text[i] == '=' ||
					 in.text[i] == '(' || in.text[i] == ')' || in.text[i] == '{' ||
					 in.text[i] == '}' || in.text[i] == '\n' )
				{
					if (in.text[i] == '\n')
					{
						if (in.text[i + 1] == '\n')
						{
							continue;
						}
						else {
							if (spaceAdded)
							{
								//AddSymbol(&ptrText, '|');
								AddSymbol(&ptrText, '\n');
								spaceAdded = true;
								continue;
							}
							else
							{
								AddSymbol(&ptrText, ' ');
								//AddSymbol(&ptrText, '|');
								AddSymbol(&ptrText, '\n');
								spaceAdded = true;
								continue;
							}
						}
					}
					if (spaceAdded && in.text[i]!=' ')
					{
						AddSymbol(&ptrText, in.text[i]);
						AddSymbol(&ptrText, ' ');
						spaceAdded = true;
					}
					if (!spaceAdded && in.text[i]!=' ')
					{
						AddSymbol(&ptrText, ' ');
						AddSymbol(&ptrText, in.text[i]);
						AddSymbol(&ptrText, ' ');
						spaceAdded = true;
					}
				}
				else {
					AddSymbol(&ptrText, in.text[i]);
					spaceAdded = false;
				}
			}
			else {
				if (in.text[i+1] == ' ')
				{
					continue;
				}
				else
				{
					if (spaceAdded && in.text[i] != ' ')
					{
						AddSymbol(&ptrText, in.text[i]);
						spaceAdded = true;
					}
					if (!spaceAdded && in.text[i] != ' ')
					{
						AddSymbol(&ptrText, ' ');
						AddSymbol(&ptrText, in.text[i]);
						spaceAdded = true;
					}
				}
				if (!spaceAdded) {
					AddSymbol(&ptrText, ' ');
					spaceAdded = true;
				}
			}
			//if (i == 620)
				//cout << "69";*/