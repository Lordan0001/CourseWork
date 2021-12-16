#pragma once
#define IN_MAX_LEN_TEXT 1024*1024
#define WORDS_MAXSIZE 4096
#define IN_CODE_ENDL  '\n'
#define IN_CODE_TAB   '\t'
#define IN_CODE_SPACE ' '
#define IN_CODE_QUOTE '\''
#define IN_CODE_DOUBLE_QUOTE	'\"'
#define IN_CODE_TABLE {\
	 IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,	IN::D, IN::D, IN::F, IN::F, IN::F, IN::F, IN::F,\
	 IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	 IN::D, IN::D, IN::D, IN::F, IN::F, IN::F, IN::F, IN::D, IN::D, IN::D, IN::F, IN::F, IN::D, IN::T, IN::T, IN::F,\
	 IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::D, IN::D, IN::D, IN::D, IN::T,\
	 IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	 IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F,\
	 IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	 IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::D, IN::F, IN::D, IN::D, IN::F,\
																													\
	 IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	 IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	 IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	 IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	 IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	 IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	 IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	 IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
					}
#define OPERATOR_TABLE {	';', '+', '-', '*', '/', ',', '(', ')', '{', '}', '=', '~', '<', '>', '!', SEPARATOR_SYMBOL, NULL}

namespace In
{
	struct IN
	{
		enum { T = 1024, F = 2048, I = 4096, D = 8192 };
		int size;
		int lines;
		int ignor;
		unsigned char* text;
		int code[256] = IN_CODE_TABLE;

		struct WORD
		{
			unsigned char* word = nullptr;
			int line = -1;
			int pos = -1;
		} words[WORDS_MAXSIZE];
		int tablesize = 0;
	};
	IN getin(wchar_t infile[]);

	unsigned char* strcpy(unsigned char* buff, unsigned char* src, int n);
	void pushword(IN& ri, int l, int p);
	void pushstrlit(IN& ri, int l, int p);
	void CleanCode(IN in);
	void DelSymb(IN in, int index);
}