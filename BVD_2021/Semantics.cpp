#include "Semantics.h"

namespace SA
{
	void SemAnalys(LT::LexTable lextable, IT::IdTable idtable)
	{
		bool mainContains = false;
		char curFunc[ID_MAXSIZE];
		memset(curFunc, NULL, ID_MAXSIZE);
		for (int i = 0; i < lextable.size; i++)
		{
			if (idtable.table[lextable.table[i].idxTI].idtype == IT::F && i == idtable.table[lextable.table[i].idxTI].idxfirstLE)
			{
				memset(curFunc, NULL, ID_MAXSIZE);
				strcpy_s(curFunc, idtable.table[lextable.table[i].idxTI].id);
			}

			if (lextable.table[i].lexema[0] == LEX_ATTACH)
			{
				if (idtable.table[lextable.table[i - 1].idxTI].iddatatype != idtable.table[lextable.table[i + 1].idxTI].iddatatype)
					throw ERROR_THROW_IN(701, lextable.table[i].sn, lextable.table[i].col);
			}

			if (
				lextable.table[i].lexema[0] == LEX_EQUAL ||
				lextable.table[i].lexema[0] == LEX_NOTEQUAL ||
				lextable.table[i].lexema[0] == LEX_MORE ||
				lextable.table[i].lexema[0] == LEX_LESS ||
				lextable.table[i].lexema[0] == LEX_EQUALNMORE ||
				lextable.table[i].lexema[0] == LEX_EQUALNLESS
				)
			{
				if ((idtable.table[lextable.table[i - 1].idxTI].iddatatype != idtable.table[lextable.table[i + 1].idxTI].iddatatype) ||
					(idtable.table[lextable.table[i - 1].idxTI].iddatatype != IT::INT))
					throw ERROR_THROW_IN(702, lextable.table[i].sn, lextable.table[i].col);
			}

			if (lextable.table[i].lexema[0] == LEX_IF)
			{
				if (idtable.table[lextable.table[i + 1].idxTI].iddatatype != IT::INT) throw ERROR_THROW_IN(703, lextable.table[i].sn, lextable.table[i].col);
			}

			if (lextable.table[i].lexema[0] == LEX_RETURN)
			{
				int indexTI = IT::IsId(idtable, curFunc, (char*)GENERAL_SCOPE);
				if (idtable.table[indexTI].iddatatype != idtable.table[lextable.table[i + 1].idxTI].iddatatype) throw ERROR_THROW_IN(704, lextable.table[i + 1].sn, lextable.table[i + 1].col);
			}

			//parameter check
			if (idtable.table[lextable.table[i].idxTI].idtype == IT::F && i != idtable.table[lextable.table[i].idxTI].idxfirstLE)
			{
				int _j = lextable.table[i].idxTI + 1;
				int _i = i + 2;
				bool error = false;
				while (idtable.table[_j].idtype == IT::P)
				{
					if (lextable.table[_i].lexema[0] != LEX_ID && lextable.table[_i].lexema[0] != LEX_LITERAL) { error = true; break; }
					if (idtable.table[lextable.table[_i].idxTI].iddatatype != idtable.table[_j].iddatatype) { error = true; break; }
					_i += 2;
					_j++;
				}
				if (lextable.table[_i].lexema[0] == LEX_LITERAL || lextable.table[_i].lexema[0] == LEX_ID) error = true;
				if (error) throw ERROR_THROW_IN(705, lextable.table[i].sn, lextable.table[i].col);
			}

			if (lextable.table[i].lexema[0] == LEX_MAIN) mainContains = true; // main check
		}

		if (!mainContains) throw ERROR_THROW(700);
	}
}