#pragma once
#include "In.h"
#include <iostream>
#define LEXEMA_FIXSIZE	1
#define LT_MAXSIZE		4096
#define LT_TI_NULLIDX	0xffffffff
#define LEX_MAIN		'm'
#define LEX_INTEGER		't'
#define LEX_STRING		't'
#define LEX_CHAR		't'
#define LEX_TYPE		't'
#define LEX_ID			'i'
#define LEX_LITERAL		'l'
#define LEX_RETURN		'r'
#define LEX_PRINT		'p'
#define LEX_SEMICOLON	';'
#define LEX_COMMA		','
#define LEX_IF			'?'
#define LEX_ELSE		':'
#define LEX_LEFTBRACE	'{'
#define LEX_BRACELET	'}'
#define LEX_LEFTHESIS	'('
#define LEX_RIGHTHESIS	')'
#define LEX_EQUAL		'~'
#define LEX_ATTACH		'='
#define LEX_MORE		'>'
#define LEX_LESS		'<'
#define LEX_EQUALNMORE	'+'
#define LEX_EQUALNLESS	'-'
#define LEX_NOTEQUAL	'!'
#define TYPE_INTEGER	"int"
#define TYPE_STRING		"string"
#define TYPE_CHAR		"char"
//#define LEX_OPERATOR	'v'

#define SEPARATOR_SYMBOL '|'

namespace LT
{
	struct Entry
	{
		char lexema[LEXEMA_FIXSIZE];
		int sn;
		int col;
		int idxTI;
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n);
	void Delete(LexTable& lextable);
	void LexAnalys(In::IN in, LexTable& lextable);
	void strcpy(char* dest, char src[], int n);
	void strcpy(char* dest, char src);
}