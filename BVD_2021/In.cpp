#include <fstream>
#include "stdafx.h"
#include "Error.h"
#include "In.h"
#include "Log.h"
#include "LT.h"

namespace In
{
	IN getin(wchar_t infile[])
	{
		std::ifstream fin(infile);
		if (!fin.is_open()) throw ERROR_THROW(110);

		IN ri = {};
		unsigned char symb;

		fin.seekg(0, fin.end);
		int fileSize = fin.tellg();
		fin.seekg(0, fin.beg);

		int curCol = 0,
			curLine = 0;

		int strlLine = 0,
			strlCol = 0;

		if (fileSize)
		{
			curLine = 1;
			curCol = 1;
		}


		if (fileSize < IN_MAX_LEN_TEXT) ri.text = new unsigned char[fileSize];
		else
		{
			ri.text = new unsigned char[IN_MAX_LEN_TEXT];
			std::cout << "\nВнимание, обьём исходного кода больше допустимого. Возможна потеря данных.\n";
		}
		ri.size = 0;
		ri.ignor = 0;
		bool dquoteflag = false;

		while (fin.tellg() < fileSize && ri.size < IN_MAX_LEN_TEXT)
		{
			symb = fin.get();
			switch (ri.code[(int)symb])
			{
			case ri.T:
				ri.text[ri.size] = symb;
				ri.size++;
				break;
			case ri.F:
				throw ERROR_THROW_IN(111, curLine, curCol - 1);
				break;
			case ri.I:
				ri.ignor++;
				break;
			case ri.D:
				ri.text[ri.size] = symb;
				ri.size++;

				if (symb != IN_CODE_DOUBLE_QUOTE && !dquoteflag)
				{
					if (symb == IN_CODE_QUOTE)
					{
						ri.words[ri.tablesize].word = new unsigned char[3];
						ri.words[ri.tablesize].word[2] = '\0';
						ri.words[ri.tablesize].word[1] = IN_CODE_QUOTE;
						ri.words[ri.tablesize].word[0] = ri.text[ri.size - 2];
						ri.words[ri.tablesize].line = curLine;
						ri.words[ri.tablesize].pos = curCol - 2;
						ri.tablesize++;
						break;
					}
					if (symb == '~' && (ri.words[ri.tablesize - 1].word[0] == '<' || ri.words[ri.tablesize - 1].word[0] == '>' || ri.words[ri.tablesize - 1].word[0] == '!'))
					{
						char temp = ri.words[ri.tablesize - 1].word[0];
						delete ri.words[ri.tablesize - 1].word;
						ri.words[ri.tablesize - 1].word = new unsigned char[3];
						ri.words[ri.tablesize - 1].word[0] = temp;
						ri.words[ri.tablesize - 1].word[1] = symb;
						ri.words[ri.tablesize - 1].word[2] = '\0';
						break;
					}
					pushword(ri, curLine, curCol);
					break;
				}

				if (symb == IN_CODE_DOUBLE_QUOTE && dquoteflag)
				{
					pushstrlit(ri, strlLine, strlCol);
					dquoteflag = false;
					break;
				}

				if (symb == IN_CODE_DOUBLE_QUOTE && !dquoteflag)
				{
					dquoteflag = true;
					strlLine = curLine;
					strlCol = curCol;
				}



				break;
			default:
				ri.text[ri.size] = (char)ri.code[(int)symb];
				ri.size++;
				break;
			}

			if (symb == IN_CODE_ENDL)
			{
				curCol = 1;
				curLine++;
			}
			else curCol++;
		}
		ri.text[ri.size] = '\0';
		fin.close();
		ri.lines = curLine;

		CleanCode(ri);

		/*	for (int i = 0; i < ri.tablesize; i++)
			{
				std::cout << i << "			" << ri.words[i].word << '\n';
			}*/

		return ri;
	}

	unsigned char* strcpy(unsigned char* buff, unsigned char* src, int n)
	{
		if (n > 0)
		{
			for (int i = 0; n > 0; i++, n--)
			{
				buff[i] = src[i];
			}

			return buff;
		}
		else return nullptr;
	}

	void pushword(IN& ri, int l, int p)
	{
		int buffsize = 0;
		for (int i = ri.size - 2; ri.code[(int)ri.text[i]] != ri.D && i >= 0; i--)
		{
			buffsize++;
		}

		if (buffsize)
		{
			unsigned char* buffer = new unsigned char[buffsize + 1];
			buffer[buffsize] = '\0';

			if (strcpy(buffer, &ri.text[ri.size - buffsize - 1], buffsize))
			{
				if (ri.tablesize >= LT_MAXSIZE) throw ERROR_THROW(115);

				ri.words[ri.tablesize].word = new unsigned char[buffsize + 1];
				ri.words[ri.tablesize].word[buffsize] = '\0';
				strcpy(ri.words[ri.tablesize].word, buffer, buffsize);
				ri.words[ri.tablesize].line = l;
				ri.words[ri.tablesize].pos = p - buffsize - 1;
				ri.tablesize++;
			}
			delete[] buffer;
		}

		if (ri.text[ri.size - 1] != IN_CODE_SPACE && ri.text[ri.size - 1] != IN_CODE_ENDL && ri.text[ri.size - 1] != IN_CODE_TAB) //operator itself
		{
			if (ri.tablesize >= LT_MAXSIZE) throw ERROR_THROW(115);

			ri.words[ri.tablesize].word = new unsigned char[2];
			ri.words[ri.tablesize].word[0] = ri.text[ri.size - 1];
			ri.words[ri.tablesize].word[1] = '\0';
			ri.words[ri.tablesize].line = l;
			ri.words[ri.tablesize].pos = p - 1;
			ri.tablesize++;
		}
		return;
	}

	void pushstrlit(IN& ri, int l, int p)
	{
		int buffsize = 2;
		for (int i = ri.size - 2; ri.text[i] != IN_CODE_DOUBLE_QUOTE && i >= 0; i--)
		{
			buffsize++;
		}

		if (buffsize)
		{
			unsigned char* buffer = new unsigned char[buffsize + 1];
			buffer[buffsize] = '\0';

			if (strcpy(buffer, &ri.text[ri.size - buffsize], buffsize))
			{
				if (ri.tablesize >= LT_MAXSIZE) throw ERROR_THROW(115);

				ri.words[ri.tablesize].word = new unsigned char[buffsize + 1];
				ri.words[ri.tablesize].word[buffsize] = '\0';
				strcpy(ri.words[ri.tablesize].word, buffer, buffsize);
				ri.words[ri.tablesize].line = l;
				ri.words[ri.tablesize].pos = p - 1;
				ri.tablesize++;
			}
			delete[] buffer;
		}
	}

	void CleanCode(IN in)
	{
		for (int i = 0; i < in.size && i < IN_MAX_LEN_TEXT; i++) // tabs to spaces
			if (in.text[i] == IN_CODE_TAB)
				in.text[i] = IN_CODE_SPACE;
			else if (in.text[i] == IN_CODE_ENDL)
				in.text[i] = SEPARATOR_SYMBOL;

		int codeTable[] = OPERATOR_TABLE;
		for (int i = 0; i < in.size && i < IN_MAX_LEN_TEXT; i++)
		{
			if (in.text[i] == IN_CODE_SPACE && in.text[i + 1] == IN_CODE_SPACE)
			{
				DelSymb(in, i);
				i--;
			}

			if (in.text[i] == IN_CODE_DOUBLE_QUOTE)
			{
				do
				{
					i++;
				} while (in.text[i] != IN_CODE_DOUBLE_QUOTE);
				i++;
			}

			for (int j = 0; codeTable[j] != NULL; j++)
			{
				if (in.text[i] == codeTable[j])
				{
					if (in.text[i + 1] == IN_CODE_SPACE)
					{
						do
						{
							DelSymb(in, i + 1);
						} while (in.text[i + 1] == IN_CODE_SPACE);
					}

					if (in.text[i - 1] == IN_CODE_SPACE)
					{
						do
						{
							DelSymb(in, i - 1);
							i--;
						} while (in.text[i - 1] == IN_CODE_SPACE);
					}

					break;
				}
			}
		}
	}

	void DelSymb(IN in, int index)
	{
		for (int i = index; i < in.size && i < IN_MAX_LEN_TEXT; i++)
		{
			in.text[i] = in.text[i + 1];
		}
		in.size--;
	}
}