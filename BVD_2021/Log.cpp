#include "Log.h"
#include "Error.h"
#include "FST.h"
#include <iostream>

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG re = {};
		re.stream = new std::ofstream(logfile);
		wcscpy_s(re.logfile, logfile);

		if (!re.stream->is_open()) throw ERROR_THROW(112);

		return re;
	}

	void WriteLine(LOG log, char* c, ...)
	{
		char** ptr = &c;
		while (*ptr != "")
		{
			*log.stream << *ptr;
			ptr++;
		}
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t** ptr = &c;
		while (*ptr != L"")
		{
			char tmp[MAX_LINE_SIZE];
			size_t tsize = 0;
			wcstombs_s(&tsize, tmp, *ptr, MAX_LINE_SIZE);
			*log.stream << tmp;
			ptr++;
		}
	}

	void WriteLog(LOG log)
	{
		WriteLine(log, (char*)"--- Протокол  --- ", "");
		time_t curSeconds = time(NULL);
		tm curDate;
		localtime_s(&curDate, &curSeconds);
		char buffer[sizeof(DATE_TEMPLATE)];
		strftime(buffer, sizeof(DATE_TEMPLATE), "Дата: %d.%m.%Y %T", &curDate);
		WriteLine(log, buffer, " ---", "");
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		WriteLine(log, (wchar_t*)L"\n--- Параметры ---\n", L"");
		WriteLine(log, (wchar_t*)L"-in : ", parm.in, "\n", L"");
		WriteLine(log, (wchar_t*)L"-out: ", parm.out, "\n", L"");
		WriteLine(log, (wchar_t*)L"-log: ", parm.log, L"");
	}

	void WriteIn(LOG log, In::IN in)
	{
		char buff[64];

		WriteLine(log, (char*)"\n--- Исходные данные ---\n", "");

		_itoa_s(in.size, buff, 10);
		WriteLine(log, (char*)"Количество символов: ", buff, "\n", "");

		_itoa_s(in.ignor, buff, 10);
		WriteLine(log, (char*)"Проигнорировано:     ", buff, "\n", "");

		_itoa_s(in.lines, buff, 10);
		WriteLine(log, (char*)"Количество строк:    ", buff, "");

		//------------------------------------------------------------

		//WriteLine(log, (char*)"\n--- Исходный код ---\n", in.text, "\n-----------------------------", "");
	}

	void FstCheck(LOG log, In::IN in)
	{
		int buffSize = 0, line = 1, col;
		for (int i = 0; i < in.size; i++)
		{
			if (in.text[i] == SEPARATOR_SYMBOL)
			{
				char* buff = new char[buffSize + 1];
				for (int j = 0; j < buffSize; j++)
				{
					buff[j] = in.text[i - buffSize + j];
				}
				buff[buffSize] = '\0';


				char* strConverted = GraphConvert(buff, line, col);

				for (int k = 0; k < buffSize; k++) // удаляем из буфера endl для вывода
				{
					if (buff[k] == '\n')
					{
						for (int q = k; q < buffSize - 1; q++)
						{
							buff[q] = buff[q + 1];
						}
						buffSize--;
						buff[buffSize] = '\0';
						k--;//повторная итерация на случай повторения endl
					}
				}

				FST::FST fst( // new graph
					strConverted,
					6,
					FST::NODE(1, FST::RELATION('s', 1)),
					FST::NODE(2, FST::RELATION(' ', 1), FST::RELATION(' ', 2)),
					FST::NODE(5, FST::RELATION('a', 3), FST::RELATION('b', 3), FST::RELATION('c', 3), FST::RELATION(' ', 4), FST::RELATION(' ', 2)),
					FST::NODE(1, FST::RELATION(' ', 2)),
					FST::NODE(1, FST::RELATION('f', 5)),
					FST::NODE()
				);
				if (FST::execute(fst))
				{
					WriteLine(log, (char*)"Цепочка ", buff, " --- распознана\n", "");
				}
				else
				{
					WriteLine(log, (char*)"Цепочка ", buff, " --- не распознана\n", "");
					if (!strlen(strConverted)) {
						WriteError(log, Error::geterrorin(113, line, col));
						WriteLine(log, (char*)"\n", "");
					}
				}

				buffSize = 0;
				delete[] buff;
				delete[] strConverted;
				continue;
			}
			buffSize++;
		}
	}

	char* GraphConvert(char* str, int& line, int& col)
	{
		int i = 0, newStrSize = 0;
		while (str[i] != '\0') {
			if (strstr(str + i, "start") == str + i ||
				strstr(str + i, "stop") == str + i ||
				strstr(str + i, "send") == str + i ||
				strstr(str + i, "wait") == str + i ||
				strstr(str + i, "show") == str + i ||
				strstr(str + i, " ") == str + i) newStrSize++;
			i++;
		}

		char* newStr = new char[newStrSize + 1];
		newStr[newStrSize] = '\0';

		i = 0;
		int j = 0;
		col = 1;

		while (str[i] != '\0')
		{
			if (str[i] == '\n')
			{
				line++;
				col = 1;
				i++;
				continue;
			}
			if (strstr(str + i, "start") == str + i)
			{
				newStr[j] = 's';
				j++;
				i += strlen("start");
				col += strlen("start");
				continue;
			}
			if (strstr(str + i, "stop") == str + i)
			{
				newStr[j] = 'f';
				j++;
				i += strlen("stop");
				col += strlen("stop");
				continue;
			}
			if (strstr(str + i, "send") == str + i)
			{
				newStr[j] = 'a';
				j++;
				i += strlen("send");
				col += strlen("send");
				continue;
			}
			if (strstr(str + i, "wait") == str + i)
			{
				newStr[j] = 'b';
				j++;
				i += strlen("wait");
				col += strlen("wait");
				continue;
			}
			if (strstr(str + i, "show") == str + i)
			{
				newStr[j] = 'c';
				j++;
				i += strlen("show");
				col += strlen("show");
				continue;
			}
			if (strstr(str + i, " ") == str + i)
			{
				newStr[j] = ' ';
				j++;
				i += strlen(" ");
				col += strlen(" ");
				continue;
			}

			memset(newStr, 0x00, sizeof(char) * newStrSize);
			break;
		}
		return newStr;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		char	errorCode[64],
			errorLine[64],
			errorCol[64];
		_itoa_s(error.id, errorCode, 10);
		_itoa_s(error.inext.line, errorLine, 10);
		_itoa_s(error.inext.col, errorCol, 10);
		WriteLine(log, (char*)"\nОшибка ", errorCode, ": ", error.message, "");

		if (error.inext.col > 0 || error.inext.line > 0)
			WriteLine(log, (char*)", строка ", errorLine, ", столбец ", errorCol, "");
	}

	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
	}
}