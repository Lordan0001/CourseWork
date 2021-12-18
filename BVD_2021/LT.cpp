#include <iostream>
#include "LT.h"
#include "Error.h"
#include "In.h"
#include "FST.h"
#include "IT.h"

#define FSTTABLESIZE 25

namespace LT
{
	LexTable Create(int size)
	{
		if (size >= LT_MAXSIZE) throw ERROR_THROW(114);
		LexTable rt;
		rt.table = new Entry[size];
		rt.maxsize = size;
		rt.size = 0;
		return rt;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size >= lextable.maxsize) throw ERROR_THROW(115);
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		if (n > lextable.size) throw ERROR_THROW(116);
		return lextable.table[n];
	}

	void Delete(LexTable& lextable)// доработать maybe
	{
		delete[] lextable.table;
		delete& lextable;
	}

	void LexAnalys(In::IN in, LexTable& lextable)
	{
		FST::FST fstINT(nullptr, 5, INTEGERNODES);
		FST::FST fstSTR(nullptr, 8, STRINGNODES);
		FST::FST fstCHAR(nullptr, 6, CHARNODES);
		FST::FST fstMAIN(nullptr, 5, MAINNODES);
		FST::FST fstPRNT(nullptr, 5, PRINTNODES);
		FST::FST fstRTRN(nullptr, 7, RETURNNODES);
		FST::FST fstID(nullptr, 3, IDNODES);
		FST::FST fstSTRL(nullptr, 3, STRLITNODES);
		FST::FST fstCHARL(nullptr, 3, CHARLITNODES);
		FST::FST fstINTL(nullptr, 3, INTLITNODES);
		FST::FST fstLBRACE(nullptr, 2, LEFTBRACENODES);
		FST::FST fstRBRACE(nullptr, 2, BRACELETNODES);
		FST::FST fstRHESIS(nullptr, 2, RIGHTHESISNODES);
		FST::FST fstLHESIS(nullptr, 2, LEFTHESISNODES);
		FST::FST fstATTACH(nullptr, 2, ATTACHNODES);
		FST::FST fstSEMICLN(nullptr, 2, SEMICOLONNODES);
		FST::FST fstCOMMA(nullptr, 2, COMMANODES);
		FST::FST fstEQUAL(nullptr, 2, EQUALNODES);
		FST::FST fstMORE(nullptr, 2, MORENODES);
		FST::FST fstLESS(nullptr, 2, LESSNODES);
		FST::FST fstNOTEQUAL(nullptr, 3, NOTEQUALNODES);
		FST::FST fstEQUALNMORE(nullptr, 3, EQUALNMORENODES);
		FST::FST fstEQUALNLESS(nullptr, 3, EQUALNLESSNODES);
		FST::FST fstIF(nullptr, 3, IFNODES);
		FST::FST fstELSE(nullptr, 5, ELSENODES);




		FST::FST FSTtable[FSTTABLESIZE] =
		{ fstINT, fstSTR, fstCHAR,
			fstMAIN, fstPRNT, fstRTRN,
			fstEQUAL, fstNOTEQUAL, fstEQUALNMORE, fstEQUALNLESS, fstMORE, fstLESS,
			fstSTRL, fstCHARL, fstINTL,
			fstLBRACE, fstRBRACE, fstRHESIS, fstLHESIS,
			fstSEMICLN, fstCOMMA, fstATTACH,
			fstIF, fstELSE,
			fstID };
		char lexems[FSTTABLESIZE] =
		{ LEX_INTEGER, LEX_STRING, LEX_CHAR,
			LEX_MAIN, LEX_PRINT, LEX_RETURN,
			LEX_EQUAL, LEX_NOTEQUAL, LEX_EQUALNMORE, LEX_EQUALNLESS, LEX_MORE, LEX_LESS,
			LEX_LITERAL, LEX_LITERAL, LEX_LITERAL,
			LEX_LEFTBRACE, LEX_BRACELET,  LEX_RIGHTHESIS, LEX_LEFTHESIS,
			LEX_SEMICOLON, LEX_COMMA, LEX_ATTACH,
			LEX_IF, LEX_ELSE,
			LEX_ID };

		for (int i = 0; i < in.tablesize; i++)
		{
			bool recognized = false;
			for (int j = 0; j < FSTTABLESIZE; j++)
			{
				FSTtable[j].rstates[0] = 0;
				FSTtable[j].position = -1;
				FSTtable[j].string = (char*)in.words[i].word;
				if (FST::execute(FSTtable[j]))
				{
					Entry entry;
					strcpy(entry.lexema, lexems[j]);
					entry.sn = in.words[i].line;
					entry.col = in.words[i].pos;
					entry.idxTI = TI_NULLIDX;
					Add(lextable, entry);
					recognized = true;
					break;
				}
			}
			if (!recognized) throw ERROR_THROW_IN(119, in.words[i].line, in.words[i].pos);
		}
		return;
	}

	void strcpy(char* dest, char src[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			dest[i] = src[i];
		}
		dest[n] = '\0';
		return;
	}
	void strcpy(char* dest, char src)
	{
		dest[0] = src;

		dest[1] = '\0';
		return;
	}
}