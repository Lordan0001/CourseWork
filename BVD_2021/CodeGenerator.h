#include <iostream>
#include <fstream>
#include "LT.h"
#include "IT.h"

#define STRCOMPARE_LIB_FUNCTION	   \
"function strcompare(_str1, _str2)\n\
{\n\
	if (_str1.length !== _str2.length) return 0;\n\
	for (let i = 0; i < _str1.length; i++)\n\
	{\n\
		if (_str1[i] !== _str2[i]) return 0;\n\
	}\n\
	return 1;\n\
}\n"

#define STRLENGTH_LIB_FUNCTION	   \
"function strlength(_str)\n\
{\n\
	return _str.length;\n\
}\n"

#define TABULATIONS for(int x = curLevel; x > 0; x--) { out<<"\t"; }
#define PRINTID out << idtable.table[lextable.table[i].idxTI].id;
#define PRINTLIT switch (idtable.table[lextable.table[i].idxTI].iddatatype) {\
				case IT::STR: out << "\"" << idtable.table[lextable.table[i].idxTI].value.vstr.str << "\""; break;\
				case IT::INT: out << idtable.table[lextable.table[i].idxTI].value.vint; break;\
				case IT::CHR: out << '\'' << idtable.table[lextable.table[i].idxTI].value.vchar << '\''; break;\
				}


namespace CG
{
	void GenerateCode(LT::LexTable lextable, IT::IdTable idtable, std::ofstream& out);
}