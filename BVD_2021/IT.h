#pragma once
#include "LT.h"
#include "In.h"
#define ID_MAXSIZE		255
#define TI_MAXSIZE		4096
#define	TI_INT_DEFAULT	0x00000000
#define TI_STR_DEFAULT	0x00
#define TI_NULLIDX		0xffffffff
#define TI_STR_MAXSIZE	255
#define GENERAL_SCOPE "GENER"

namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2, CHR = 3 };
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };

	struct Entry
	{
		int idxfirstLE;
		char scope[ID_MAXSIZE + 1];
		char id[ID_MAXSIZE + 1];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		union
		{
			int vint;
			struct
			{
				int len;
				char str[TI_STR_MAXSIZE - 1];
			} vstr;
			unsigned char vchar;
		} value;
	};
	struct IdTable
	{
		int maxsize;
		int size;
		Entry* table;
	};
	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);
	Entry GetEntry(IdTable& idtable, char id[ID_MAXSIZE]);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE + 1], char scope[ID_MAXSIZE + 1]);
	int IsLiteral(IdTable& idtable, char* value);
	void Delete(IdTable& idtable);
	void IdAnalys(LT::LexTable lextable, In::IN in, IdTable& idtable);
}