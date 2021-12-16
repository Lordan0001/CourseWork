#include "IT.h"
#include "LT.h"
#include "Error.h"
#include <iostream>
#include <cstring>

#define MAX_NESTING 3
#define MAIN_FUNCTION "main"
#define ID_LITERAL    "LIT"

namespace IT
{
	IdTable Create(int size)
	{
		if (size >= TI_MAXSIZE) throw ERROR_THROW(117);
		IdTable rt;
		rt.table = new Entry[size];
		rt.maxsize = size;
		rt.size = 0;
		return rt;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size >= idtable.maxsize) throw ERROR_THROW(118);
		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, char id[ID_MAXSIZE]) //????
	{
		Entry re;
		re.idxfirstLE = TI_NULLIDX;
		for (int i = 0; i < idtable.size; i++)
		{
			if (!strcmp(idtable.table[i].id, id))
			{
				re = idtable.table[i];
				break;
			}
		}
		return re;
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE + 1], char scope[ID_MAXSIZE + 1])
	{
		int ri = TI_NULLIDX;

		for (int i = 0; i < idtable.size; i++)
		{
			if (!strncmp(idtable.table[i].id, id, ID_MAXSIZE) && (!strncmp(idtable.table[i].scope, scope, ID_MAXSIZE)))// || !strncmp(scope, GENERAL_SCOPE, ID_MAXSIZE)))
			{
				ri = i;
				break;
			}
		}
		return ri;
	}

	int IsLiteral(IdTable& idtable, char* value)
	{
		int ri = TI_NULLIDX;
		int intValue;
		IDDATATYPE type;
		if (value[0] == IN_CODE_DOUBLE_QUOTE)
		{
			type = STR;
		}
		else if (value[1] == IN_CODE_QUOTE)
		{
			type = CHR;
		}
		else
		{
			type = INT;
			intValue = atoi(value);
		}

		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].idtype == L)
			{
				switch (type)
				{
				case INT:
					if (idtable.table[i].iddatatype == INT && intValue == idtable.table[i].value.vint) { return i; }
					break;
				case CHR:
					if (idtable.table[i].iddatatype == CHR && value[0] == idtable.table[i].value.vchar) { return i; }
					break;
				case STR:
					if (idtable.table[i].iddatatype == STR && (strlen(value) - 2) == idtable.table[i].value.vstr.len && !strncmp(value + 1, idtable.table[i].value.vstr.str, strlen(value) - 2)) { return i; }
					break;

				}
			}
		}

		return ri;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
		delete& idtable;
		return;
	}

	void IdAnalys(LT::LexTable lextable, In::IN in, IdTable& idtable)
	{
		char scopestack[MAX_NESTING][ID_MAXSIZE + 1];
		strcpy_s(scopestack[0], GENERAL_SCOPE);
		scopestack[0][ID_MAXSIZE] = '\0';
		int scopeindex = 0;
		//добавление библиотечных функций и их параметров
		Entry  strcompareID = {};
		strncpy_s(strcompareID.id, (char*)"strcompare", ID_MAXSIZE);
		strncpy_s(strcompareID.scope, GENERAL_SCOPE, ID_MAXSIZE);
		strcompareID.idtype = F;
		strcompareID.iddatatype = INT;
		Add(idtable, strcompareID);

		Entry strcompareStr1 = {};
		strncpy_s(strcompareStr1.id, (char*)"_str1", ID_MAXSIZE);
		strncpy_s(strcompareStr1.scope, (char*)"strcompare", ID_MAXSIZE);
		strcompareStr1.idtype = P;
		strcompareStr1.iddatatype = STR;
		Add(idtable, strcompareStr1);
		Entry strcompareStr2 = {};
		strncpy_s(strcompareStr2.id, (char*)"_str2", ID_MAXSIZE);
		strncpy_s(strcompareStr2.scope, (char*)"strcompare", ID_MAXSIZE);
		strcompareStr2.idtype = P;
		strcompareStr2.iddatatype = STR;
		Add(idtable, strcompareStr2);

		Entry  strlengthID = {};
		strncpy_s(strlengthID.id, (char*)"strlength", ID_MAXSIZE);
		strncpy_s(strlengthID.scope, GENERAL_SCOPE, ID_MAXSIZE);
		strlengthID.idtype = F;
		strlengthID.iddatatype = INT;
		Add(idtable, strlengthID);

		Entry strlenStr = {};
		strncpy_s(strlenStr.id, (char*)"_str", ID_MAXSIZE);
		strncpy_s(strlenStr.scope, (char*)"strlength", ID_MAXSIZE);
		strlenStr.idtype = P;
		strlenStr.iddatatype = STR;
		Add(idtable, strlenStr);

		bool mainFound = false;
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema[0] == LEX_MAIN) // main
			{
				if (mainFound) throw ERROR_THROW_IN(120, lextable.table[i].sn, lextable.table[i].col) else mainFound = true;
				int tableid = IsId(idtable, (char*)in.words[i].word, scopestack[scopeindex]);
				if (tableid == TI_NULLIDX)
				{
					Entry newID = {};
					strncpy_s(newID.id, (char*)in.words[i].word, ID_MAXSIZE);
					strncpy_s(newID.scope, GENERAL_SCOPE, ID_MAXSIZE);
					newID.idtype = F;
					newID.iddatatype = INT;
					newID.idxfirstLE = i;
					Add(idtable, newID);
					lextable.table[i].idxTI = idtable.size - 1;

					//scopeindex++;
					if (scopeindex >= MAX_NESTING) throw ERROR_THROW_IN(121, in.words[i].line, in.words[i].pos);
					memset(scopestack[scopeindex], NULL, ID_MAXSIZE + 1);
					strncpy_s(scopestack[scopeindex], (char*)in.words[i].word, ID_MAXSIZE);
					continue;
				}
			}

			if (lextable.table[i].lexema[0] == LEX_ID)
			{

				if (lextable.table[i - 1].lexema[0] == LEX_TYPE && lextable.table[i + 1].lexema[0] == LEX_SEMICOLON) // if ID declare
				{
					int tableid = IsId(idtable, (char*)in.words[i].word, scopestack[scopeindex]);
					if (tableid == TI_NULLIDX)
					{
						Entry newID = {};
						newID.idtype = V;
						strncpy_s(newID.id, (char*)in.words[i].word, ID_MAXSIZE);
						strncpy_s(newID.scope, scopestack[scopeindex], ID_MAXSIZE);
						if (!strcmp((char*)in.words[i - 1].word, TYPE_INTEGER))	newID.iddatatype = INT;
						if (!strcmp((char*)in.words[i - 1].word, TYPE_STRING))	newID.iddatatype = STR;
						if (!strcmp((char*)in.words[i - 1].word, TYPE_CHAR))	newID.iddatatype = CHR;
						newID.idxfirstLE = i;
						Add(idtable, newID);
						lextable.table[i].idxTI = idtable.size - 1;
						continue;
					}
					else { throw ERROR_THROW_IN(125, in.words[i].line, in.words[i].pos); }
				}

				if (lextable.table[i + 1].lexema[0] == LEX_LEFTHESIS) //if func
				{
					if (lextable.table[i - 1].lexema[0] == LEX_TYPE) //if func declare
					{
						if (mainFound) throw ERROR_THROW_IN(127, lextable.table[i].sn, lextable.table[i].col);
						int tableid = IsId(idtable, (char*)in.words[i].word, (char*)GENERAL_SCOPE);
						if (tableid == TI_NULLIDX)
						{
							Entry newID = {};
							newID.idtype = F;
							strncpy_s(newID.id, (char*)in.words[i].word, ID_MAXSIZE);
							strncpy_s(newID.scope, (char*)GENERAL_SCOPE, ID_MAXSIZE);
							if (!strcmp((char*)in.words[i - 1].word, TYPE_INTEGER))	newID.iddatatype = INT;
							if (!strcmp((char*)in.words[i - 1].word, TYPE_STRING))	newID.iddatatype = STR;
							if (!strcmp((char*)in.words[i - 1].word, TYPE_CHAR))	newID.iddatatype = CHR;
							newID.idxfirstLE = i;
							Add(idtable, newID);
							lextable.table[i].idxTI = idtable.size - 1;

							if (scopeindex >= MAX_NESTING) throw ERROR_THROW_IN(121, in.words[i].line, in.words[i].pos);
							memset(scopestack[scopeindex], NULL, ID_MAXSIZE + 1);
							strncpy_s(scopestack[scopeindex], (char*)in.words[i].word, ID_MAXSIZE);
							continue;
						}
						else throw ERROR_THROW_IN(124, in.words[i].line, in.words[i].pos);
					}

					int tableid = IsId(idtable, (char*)in.words[i].word, (char*)GENERAL_SCOPE); //if func calling
					if (tableid != TI_NULLIDX)
					{
						lextable.table[i].idxTI = tableid;
						continue;
					}
					else throw ERROR_THROW_IN(126, in.words[i].line, in.words[i].pos);
				}

				if (lextable.table[i - 1].lexema[0] == LEX_TYPE
					&&
					(lextable.table[i + 1].lexema[0] == LEX_COMMA || lextable.table[i + 1].lexema[0] == LEX_RIGHTHESIS)
					&&
					(lextable.table[i - 2].lexema[0] == LEX_COMMA || lextable.table[i - 2].lexema[0] == LEX_LEFTHESIS))
				{
					int tableid = IsId(idtable, (char*)in.words[i].word, (char*)GENERAL_SCOPE);
					if (tableid == TI_NULLIDX)
					{
						Entry newID = {};
						newID.idtype = P;
						strncpy_s(newID.id, (char*)in.words[i].word, ID_MAXSIZE);
						strncpy_s(newID.scope, scopestack[scopeindex], ID_MAXSIZE);
						if (!strcmp((char*)in.words[i - 1].word, TYPE_INTEGER))	newID.iddatatype = INT;
						if (!strcmp((char*)in.words[i - 1].word, TYPE_STRING))	newID.iddatatype = STR;
						if (!strcmp((char*)in.words[i - 1].word, TYPE_CHAR))	newID.iddatatype = CHR;
						newID.idxfirstLE = i;
						Add(idtable, newID);
						lextable.table[i].idxTI = idtable.size - 1;
						continue;
					}
					else throw ERROR_THROW_IN(125, in.words[i].line, in.words[i].pos);
				}

				if (IsId(idtable, (char*)in.words[i].word, scopestack[scopeindex]) != TI_NULLIDX) lextable.table[i].idxTI = IsId(idtable, (char*)in.words[i].word, scopestack[scopeindex]);
				else throw ERROR_THROW_IN(126, in.words[i].line, in.words[i].pos);
			}

			if (lextable.table[i].lexema[0] == LEX_LITERAL) // if literal
			{
				int tableid = IsLiteral(idtable, (char*)in.words[i].word);
				if (tableid == TI_NULLIDX)
				{
					Entry newLit = {};
					strcpy_s(newLit.id, ID_LITERAL);
					newLit.idtype = L;
					if (in.words[i].word[0] == IN_CODE_DOUBLE_QUOTE) newLit.iddatatype = STR;
					else if (in.words[i].word[1] == IN_CODE_QUOTE) newLit.iddatatype = CHR;
					else newLit.iddatatype = INT;

					newLit.idxfirstLE = i;

					if (newLit.iddatatype == STR)
					{
						if (strlen((char*)in.words[i].word) - 2 < TI_STR_MAXSIZE)
						{
							strncpy_s(newLit.value.vstr.str, (char*)in.words[i].word + 1, strlen((char*)in.words[i].word) - 2);
							newLit.value.vstr.len = strlen((char*)in.words[i].word) - 2;
						}
						else throw ERROR_THROW_IN(122, in.words[i].line, in.words[i].pos);
					}


					if (newLit.iddatatype == INT)
					{
						newLit.value.vint = atoi((char*)in.words[i].word);
					}

					if (newLit.iddatatype == CHR)
					{
						newLit.value.vchar = in.words[i].word[0];
					}


					Add(idtable, newLit);
					lextable.table[i].idxTI = idtable.size - 1;
				}
				else lextable.table[i].idxTI = tableid;
			}

		}
	}
}