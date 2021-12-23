#include "stdafx.h"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "Out.h"
#include "LT.h"
#include "IT.h"
#include "MFST.h"
#include "GRB.h"
#include "Semantics.h"
#include "CodeGenerator.h"
#include <fstream>
#include <string>
using namespace std;
#include <iomanip>

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Log::WriteLine(log, (char*)"\n", "");

		LT::LexTable lextable = LT::Create(in.tablesize);
		LT::LexAnalys(in, lextable);
		Log::WriteLine(log, (char*)"Лексический анализатор завершил свою работу успешно.\nТаблица лексем:\n", "");
		for (int curLine = 1, i = 0; curLine <= lextable.table[lextable.size - 1].sn; curLine++) // lexToLog
		{
			char* t = new char[5];
			_itoa_s(curLine, t, 5, 10);
			Log::WriteLine(log, t, " ", "");
			delete[] t;
			while (lextable.table[i].sn == curLine)
			{
				Log::WriteLine(log, lextable.table[i].lexema, "");
				i++;
			}
			Log::WriteLine(log, (char*)"\n", "");
		}


		int IdTableSize = 0;
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema[0] == LEX_ID || lextable.table[i].lexema[0] == LEX_LITERAL || lextable.table[i].lexema[0] == LEX_MAIN)
			{
				IdTableSize++;
			}
		}
		IT::IdTable idtable = IT::Create(IdTableSize + 5);
		IT::IdAnalys(lextable, in, idtable);
		Log::WriteLine(log, (char*)"Таблица идентификаторов:\n", ""); // id to log
		*(log.stream) << setw(5) << left << "IDX" << setw(32) << "ID" << setw(32) << "SCOPE/VALUE" << setw(16) << "IDTYPE" << setw(16) << "IDDATATYPE" << '\n';
		*(log.stream) << setw(100) << setfill('-') << '-' << '\n';
		for (int i = 0; i < idtable.size; i++)
		{
			*(log.stream) << setfill(' ') << setw(5) << i;
			*(log.stream) << setw(32) << left << idtable.table[i].id;
			if (strcmp(idtable.table[i].id, "LIT")) {
				*(log.stream) << setw(32) << idtable.table[i].scope;
			}
			else {
				switch (idtable.table[i].iddatatype) {
				case IT::STR: *(log.stream) << setw(32) << idtable.table[i].value.vstr.str; break;
				case IT::INT: *(log.stream) << setw(32) << idtable.table[i].value.vint; break;
				case IT::CHR: *(log.stream) << setw(32) << idtable.table[i].value.vchar; break;
				}
			}
			*(log.stream) << setw(16);
			switch (idtable.table[i].idtype) {
			case IT::V: *(log.stream) << "varuable"; break;
			case IT::P: *(log.stream) << "parameter"; break;
			case IT::F: *(log.stream) << "function"; break;
			case IT::L: *(log.stream) << "literal"; break;

			}
			cout << setw(16);
			switch (idtable.table[i].iddatatype) {
			case IT::STR: *(log.stream) << "string"; break;
			case IT::CHR: *(log.stream) << "char"; break;
			case IT::INT: *(log.stream) << "int"; break;
			}
			*(log.stream) << setw(100) << setfill('-') << '\n' << '\n';
		}

		MFST::Mfst mfst(lextable, GRB::getGreibach());
		if (mfst.start(log))
		{
			Log::WriteLine(log, (char*)"Синтаксический анализатор завершил свою работу успешно.\nДерево разбора:\n", "");
			mfst.printrules(log);
		}
		else
		{
			Log::Close(log);
			system("pause");
			return 0;
		}
		SA::SemAnalys(lextable, idtable);
		Log::WriteLine(log, (char*)"Семантический анализатор завершил свою работу успешно.\n", "");
		Out::OUT out = Out::getout(parm.out);
		CG::GenerateCode(lextable, idtable, *(out.stream));
		*(log.stream) << "Генератор кода завершил свою работу успешно.";
		Out::Close(out);
		cout << "Транслятор завершил свою работу успешно!\n";
	}
	catch (Error::ERROR e)
	{
		if (log.stream)
		{
			Log::WriteError(log, e);
			Log::Close(log);
		}
		std::cout << setw(0) << "Ошибка " << e.id << ": " << e.message;
		if (e.inext.line > 0 || e.inext.col >= 0) std::cout << ", строка " << e.inext.line << ", позиция " << e.inext.col;
		cout << "\n";
		system("pause");
		return 0;
	}
	Log::Close(log);
	//перенос из .out в .js
	string line;
	ifstream ini_file{ "in.txt.out" };
	ofstream out_file{ "Check_this.js" };
	if (ini_file && out_file) {

		while (getline(ini_file, line)) {
			out_file << line << "\n";
		}

	}
	else {
		
		printf("Cannot read File");
	}
	ini_file.close();
	out_file.close();

	system("pause");
	return 0;
}