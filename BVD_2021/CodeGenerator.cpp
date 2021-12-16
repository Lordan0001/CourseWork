#include "CodeGenerator.h"

namespace CG
{
	void GenerateCode(LT::LexTable lextable, IT::IdTable idtable, std::ofstream& out)
	{
		out << STRCOMPARE_LIB_FUNCTION;//strcompare add
		out << STRLENGTH_LIB_FUNCTION;//strlength add
		int curLevel = 0;
		bool hesis = false;
		for (int i = 0; i < lextable.size; i++)
		{
			switch (lextable.table[i].lexema[0])
			{
			case LEX_TYPE:
				switch (idtable.table[lextable.table[i + 1].idxTI].idtype)
				{
				case IT::F:
					out << "function ";
					break;
				case IT::V:
					TABULATIONS
						out << "let ";
					i++;
					PRINTID
						out << " = ";
					switch (idtable.table[lextable.table[i].idxTI].iddatatype)
					{
					case IT::STR: out << "\"\""; break;
					case IT::INT: out << "0"; break;
					case IT::CHR: out << "null"; break;
					}
					break;
				case IT::P:break;
				}
				continue;
				break;
			case LEX_ID: if (lextable.table[i + 1].lexema[0] == LEX_ATTACH) TABULATIONS; PRINTID break;
			case LEX_LITERAL: PRINTLIT break;
			case LEX_LEFTBRACE: if (hesis) { out << ')'; hesis = false; } out << "\n"; TABULATIONS out << "{\n"; curLevel++; break;
			case LEX_BRACELET: curLevel--; TABULATIONS out << "}\n"; break;//? \n
			case LEX_LEFTHESIS: out << LEX_LEFTHESIS; break;
			case LEX_RIGHTHESIS: out << LEX_RIGHTHESIS; break;
			case LEX_SEMICOLON: if (hesis) { out << ')'; hesis = false; } out << LEX_SEMICOLON << '\n'; break;
			case LEX_COMMA: out << LEX_COMMA << ' '; break;
			case LEX_RETURN: TABULATIONS out << "return "; break;
			case LEX_PRINT: TABULATIONS out << "console.log("; hesis = true; break;//close )
			case LEX_MAIN: out << "function main()"; break;
			case LEX_ATTACH: out << " = "; break;
			case LEX_IF: TABULATIONS out << "if("; hesis = true; break;
			case LEX_ELSE: TABULATIONS out << "else"; break;
			case LEX_EQUAL: out << " === "; break;
			case LEX_NOTEQUAL: out << " !== "; break;
			case LEX_EQUALNMORE: out << " >= "; break;
			case LEX_EQUALNLESS: out << " <= "; break;
			case LEX_MORE: out << " > "; break;
			case LEX_LESS: out << " < "; break;
			}
		}
		out << "\n//==============================================\nmain()";
	}
}