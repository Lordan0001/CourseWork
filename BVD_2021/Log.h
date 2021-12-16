#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"
#include <ctime>

#define MAX_LINE_SIZE 1024
#define DATE_TEMPLATE "Дата: XX.XX.XXXX XX:XX:XX"
#define SEPARATOR_SYMBOL '|'

namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const LOG INITLOG = { L"", NULL };
	LOG  getlog(wchar_t logfile[]);
	void WriteLine(LOG log, char* c, ...);
	void WriteLine(LOG log, wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::IN in);
	void FstCheck(LOG log, In::IN in);
	char* GraphConvert(char* str, int& line, int& col);
	void WriteError(LOG log, Error::ERROR error);
	void Close(LOG log);
}