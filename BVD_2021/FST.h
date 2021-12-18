#pragma once
#include <iostream>
#include "In.h"
//fint делать здесь
//4

//#define INTEGERNODES	FST::NODE (1, FST::RELATION('i', 1)),\
//				FST::NODE (1, FST::RELATION('n', 2)),\
//				FST::NODE (1, FST::RELATION('t', 3)),\
//				FST::NODE()


#define INTEGERNODES	FST::NODE (1, FST::RELATION('f', 1)),\
				FST::NODE (1, FST::RELATION('i', 2)),\
				FST::NODE (1, FST::RELATION('n', 3)),\
				FST::NODE (1, FST::RELATION('t', 4)),\
				FST::NODE()


//7
//#define STRINGNODES	FST::NODE (1, FST::RELATION('s', 1)),\
//				FST::NODE (1, FST::RELATION('t', 2)),\
//				FST::NODE (1, FST::RELATION('r', 3)),\
//				FST::NODE (1, FST::RELATION('i', 4)),\
//				FST::NODE (1, FST::RELATION('n', 5)),\
//				FST::NODE (1, FST::RELATION('g', 6)),\
//				FST::NODE()


#define STRINGNODES	FST::NODE (1, FST::RELATION('f', 1)),\
				FST::NODE (1, FST::RELATION('s', 2)),\
				FST::NODE (1, FST::RELATION('t', 3)),\
				FST::NODE (1, FST::RELATION('r', 4)),\
				FST::NODE (1, FST::RELATION('i', 5)),\
				FST::NODE (1, FST::RELATION('n', 6)),\
				FST::NODE (1, FST::RELATION('g', 7)),\
				FST::NODE()

//5
#define CHARNODES	FST::NODE (1, FST::RELATION('f', 1)),\
				FST::NODE (1, FST::RELATION('c', 2)),\
				FST::NODE (1, FST::RELATION('h', 3)),\
				FST::NODE (1, FST::RELATION('a', 4)),\
				FST::NODE (1, FST::RELATION('r', 5)),\
				FST::NODE()

#define IDNODES	FST::NODE (52, FST::RELATION('a', 1),FST::RELATION('b', 1),FST::RELATION('c', 1),FST::RELATION('d', 1),FST::RELATION('e', 1),\
							   FST::RELATION('f', 1),FST::RELATION('g', 1),FST::RELATION('h', 1),FST::RELATION('i', 1),\
							   FST::RELATION('j', 1),FST::RELATION('k', 1),FST::RELATION('l', 1),FST::RELATION('m', 1),FST::RELATION('n', 1),\
							   FST::RELATION('o', 1),FST::RELATION('p', 1),FST::RELATION('q', 1),FST::RELATION('r', 1),FST::RELATION('s', 1),\
							   FST::RELATION('t', 1),FST::RELATION('u', 1),FST::RELATION('v', 1),FST::RELATION('w', 1),FST::RELATION('x', 1),\
							   FST::RELATION('y', 1),FST::RELATION('z', 1),FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2),\
								 FST::RELATION('d', 2), FST::RELATION('e', 2), \
								 FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2), \
								 FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2), FST::RELATION('m', 2), FST::RELATION('n', 2), \
								 FST::RELATION('o', 2), FST::RELATION('p', 2), FST::RELATION('q', 2), FST::RELATION('r', 2), FST::RELATION('s', 2), \
								 FST::RELATION('t', 2), FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2), \
								 FST::RELATION('y', 2), FST::RELATION('z', 2)),\
				FST::NODE	(52, FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1), \
								 FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), \
								 FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1), FST::RELATION('m', 1), FST::RELATION('n', 1), \
								 FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1), \
								 FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1), \
								 FST::RELATION('y', 1), FST::RELATION('z', 1), FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2), FST::RELATION('e', 2), \
								 FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2), \
								 FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2), FST::RELATION('m', 2), FST::RELATION('n', 2), \
								 FST::RELATION('o', 2), FST::RELATION('p', 2), FST::RELATION('q', 2), FST::RELATION('r', 2), FST::RELATION('s', 2), \
								 FST::RELATION('t', 2), FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2), \
								 FST::RELATION('y', 2), FST::RELATION('z', 2)),\
				FST::NODE()

#define IFNODES	FST::NODE (1, FST::RELATION('i', 1)),\
				FST::NODE (1, FST::RELATION('f', 2)),\
				FST::NODE()


//#define IFNODES	FST::NODE (1, FST::RELATION('f', 1)),\
//				FST::NODE (1, FST::RELATION('i', 2)),\
//				FST::NODE (1, FST::RELATION('f', 3)),\
//				FST::NODE()

#define ELSENODES	FST::NODE (1, FST::RELATION('e', 1)),\
				FST::NODE (1, FST::RELATION('l', 2)),\
				FST::NODE (1, FST::RELATION('s', 3)),\
				FST::NODE (1, FST::RELATION('e', 4)),\
				FST::NODE()

//#define ELSENODES	FST::NODE (1, FST::RELATION('f', 1)),\
//				FST::NODE (1, FST::RELATION('e', 2)),\
//				FST::NODE (1, FST::RELATION('l', 3)),\
//				FST::NODE (1, FST::RELATION('s', 4)),\
//				FST::NODE (1, FST::RELATION('e', 5)),\
//				FST::NODE()

//5
#define MAINNODES	FST::NODE (1, FST::RELATION('m', 1)),\
				FST::NODE (1, FST::RELATION('a', 2)),\
				FST::NODE (1, FST::RELATION('i', 3)),\
				FST::NODE (1, FST::RELATION('n', 4)),\
				FST::NODE()

//6
#define PRINTNODES	FST::NODE (1, FST::RELATION('f', 1)),\
				FST::NODE (1, FST::RELATION('o', 2)),\
				FST::NODE (1, FST::RELATION('u', 3)),\
				FST::NODE (1, FST::RELATION('t', 4)),\
				FST::NODE()

//#define PRINTNODES	FST::NODE (1, FST::RELATION('p', 1)),\
//				FST::NODE (1, FST::RELATION('r', 2)),\
//				FST::NODE (1, FST::RELATION('i', 3)),\
//				FST::NODE (1, FST::RELATION('n', 4)),\
//				FST::NODE (1, FST::RELATION('t', 5)),\
//				FST::NODE()

//7
#define RETURNNODES	FST::NODE (1, FST::RELATION('r', 1)),\
				FST::NODE (1, FST::RELATION('e', 2)),\
				FST::NODE (1, FST::RELATION('t', 3)),\
				FST::NODE (1, FST::RELATION('u', 4)),\
				FST::NODE (1, FST::RELATION('r', 5)),\
				FST::NODE (1, FST::RELATION('n', 6)),\
				FST::NODE()

#define STRLITNODES	FST::NODE (1, FST::RELATION('\"', 1)),\
	FST::NODE (12+14+26*2, 	FST::RELATION('1', 1),FST::RELATION('2', 1),FST::RELATION('3', 1),FST::RELATION('4', 1),FST::RELATION('5', 1),\
					FST::RELATION('6', 1),FST::RELATION('7', 1),FST::RELATION('8', 1),FST::RELATION('9', 1),FST::RELATION('0', 1),\
					FST::RELATION(' ', 1),\
					FST::RELATION('\"', 2),\
					FST::RELATION('!', 1),FST::RELATION('>', 1),FST::RELATION('<', 1),FST::RELATION('~', 1),\
					FST::RELATION('(', 1),FST::RELATION(')', 1),FST::RELATION(',', 1),FST::RELATION('.', 1),\
					FST::RELATION(';', 1),FST::RELATION('=', 1),FST::RELATION('?', 1),FST::RELATION('{', 1),\
					FST::RELATION('}', 1),FST::RELATION('-', 1),\
					FST::RELATION('a', 1),FST::RELATION('b', 1),FST::RELATION('c', 1),FST::RELATION('d', 1),FST::RELATION('e', 1),\
					FST::RELATION('f', 1),FST::RELATION('g', 1),FST::RELATION('h', 1),FST::RELATION('i', 1),\
					FST::RELATION('j', 1),FST::RELATION('k', 1),FST::RELATION('l', 1),FST::RELATION('m', 1),FST::RELATION('n', 1),\
					FST::RELATION('o', 1),FST::RELATION('p', 1),FST::RELATION('q', 1),FST::RELATION('r', 1),FST::RELATION('s', 1),\
					FST::RELATION('t', 1),FST::RELATION('u', 1),FST::RELATION('v', 1),FST::RELATION('w', 1),FST::RELATION('x', 1),\
					FST::RELATION('y', 1),FST::RELATION('z', 1),\
					FST::RELATION('A', 1),FST::RELATION('B', 1),FST::RELATION('C', 1),FST::RELATION('D', 1),FST::RELATION('E', 1),\
					FST::RELATION('F', 1),FST::RELATION('G', 1),FST::RELATION('H', 1),FST::RELATION('I', 1),\
					FST::RELATION('J', 1),FST::RELATION('K', 1),FST::RELATION('L', 1),FST::RELATION('M', 1),FST::RELATION('N', 1),\
					FST::RELATION('O', 1),FST::RELATION('P', 1),FST::RELATION('Q', 1),FST::RELATION('R', 1),FST::RELATION('S', 1),\
					FST::RELATION('T', 1),FST::RELATION('U', 1),FST::RELATION('V', 1),FST::RELATION('W', 1),FST::RELATION('X', 1),\
					FST::RELATION('Y', 1),FST::RELATION('Z', 1)),\
					FST::NODE()

//3
#define CHARLITNODES  FST::NODE (11+13 + 26*2, \
					FST::RELATION('1', 1),FST::RELATION('2', 1),FST::RELATION('3', 1),FST::RELATION('4', 1),FST::RELATION('5', 1),\
					FST::RELATION('6', 1),FST::RELATION('7', 1),FST::RELATION('8', 1),FST::RELATION('9', 1),FST::RELATION('0', 1),\
					FST::RELATION(' ', 1),\
					FST::RELATION('!', 1),FST::RELATION('>', 1),FST::RELATION('<', 1),FST::RELATION('~', 1),\
					FST::RELATION('(', 1),FST::RELATION(')', 1),FST::RELATION(',', 1),FST::RELATION('.', 1),\
					FST::RELATION(';', 1),FST::RELATION('?', 1),FST::RELATION('{', 1),\
					FST::RELATION('}', 1),FST::RELATION('-', 1),\
					FST::RELATION('a', 1),FST::RELATION('b', 1),FST::RELATION('c', 1),FST::RELATION('d', 1),FST::RELATION('e', 1),\
					FST::RELATION('f', 1),FST::RELATION('g', 1),FST::RELATION('h', 1),FST::RELATION('i', 1),\
					FST::RELATION('j', 1),FST::RELATION('k', 1),FST::RELATION('l', 1),FST::RELATION('m', 1),FST::RELATION('n', 1),\
					FST::RELATION('o', 1),FST::RELATION('p', 1),FST::RELATION('q', 1),FST::RELATION('r', 1),FST::RELATION('s', 1),\
					FST::RELATION('t', 1),FST::RELATION('u', 1),FST::RELATION('v', 1),FST::RELATION('w', 1),FST::RELATION('x', 1),\
					FST::RELATION('y', 1),FST::RELATION('z', 1),\
					FST::RELATION('A', 1),FST::RELATION('B', 1),FST::RELATION('C', 1),FST::RELATION('D', 1),FST::RELATION('E', 1),\
					FST::RELATION('F', 1),FST::RELATION('G', 1),FST::RELATION('H', 1),FST::RELATION('I', 1),\
					FST::RELATION('J', 1),FST::RELATION('K', 1),FST::RELATION('L', 1),FST::RELATION('M', 1),FST::RELATION('N', 1),\
					FST::RELATION('O', 1),FST::RELATION('P', 1),FST::RELATION('Q', 1),FST::RELATION('R', 1),FST::RELATION('S', 1),\
					FST::RELATION('T', 1),FST::RELATION('U', 1),FST::RELATION('V', 1),FST::RELATION('W', 1),FST::RELATION('X', 1),\
					FST::RELATION('Y', 1),FST::RELATION('Z', 1)),\
					FST::NODE(1, FST::RELATION('\'', 2)), \
					FST::NODE()

#define INTLITNODES	FST::NODE (10*2+1, FST::RELATION('-', 1),FST::RELATION('1', 1),FST::RELATION('2', 1),FST::RELATION('3', 1),FST::RELATION('4', 1),FST::RELATION('5', 1),\
					FST::RELATION('6', 1),FST::RELATION('7', 1),FST::RELATION('8', 1),FST::RELATION('9', 1),FST::RELATION('0', 1),\
					FST::RELATION('1', 2),FST::RELATION('2', 2),FST::RELATION('3', 2),FST::RELATION('4', 2),FST::RELATION('5', 2),\
					FST::RELATION('6', 2),FST::RELATION('7', 2),FST::RELATION('8', 2),FST::RELATION('9', 2),FST::RELATION('0', 2)),\
					FST::NODE (10*2, FST::RELATION('1', 2),FST::RELATION('2', 2),FST::RELATION('3', 2),FST::RELATION('4', 2),FST::RELATION('5', 2),\
					FST::RELATION('6', 2),FST::RELATION('7', 2),FST::RELATION('8', 2),FST::RELATION('9', 2),FST::RELATION('0', 2),\
					FST::RELATION('1', 1),FST::RELATION('2', 1),FST::RELATION('3', 1),FST::RELATION('4', 1),FST::RELATION('5', 1),\
					FST::RELATION('6', 1),FST::RELATION('7', 1),FST::RELATION('8', 1),FST::RELATION('9', 1),FST::RELATION('0', 1)),\
					FST::NODE()

#define LEFTBRACENODES	FST::NODE (1, FST::RELATION('{', 1)),\
				FST::NODE()

#define BRACELETNODES	FST::NODE (1, FST::RELATION('}', 1)),\
				FST::NODE()

#define LEFTHESISNODES	FST::NODE (1, FST::RELATION('(', 1)),\
				FST::NODE()

#define RIGHTHESISNODES	FST::NODE (1, FST::RELATION(')', 1)),\
				FST::NODE()

#define ATTACHNODES	FST::NODE (1, FST::RELATION('=', 1)),\
				FST::NODE()

#define EQUALNODES	FST::NODE (1, FST::RELATION('~', 1)),\
				FST::NODE()

#define NOTEQUALNODES	FST::NODE (1, FST::RELATION('!', 1)),\
						FST::NODE (1, FST::RELATION('~', 2)),\
				FST::NODE()

#define MORENODES FST::NODE (1, FST::RELATION('>', 1)),\
				FST::NODE()

#define LESSNODES FST::NODE (1, FST::RELATION('<', 1)),\
				FST::NODE()

#define EQUALNMORENODES	FST::NODE (1, FST::RELATION('>', 1)),\
				FST::NODE (1, FST::RELATION('~', 2)),\
				FST::NODE()

#define EQUALNLESSNODES	FST::NODE (1, FST::RELATION('<', 1)),\
				FST::NODE (1, FST::RELATION('~', 2)),\
				FST::NODE()

#define SEMICOLONNODES	FST::NODE (1, FST::RELATION(';', 1)),\
				FST::NODE()

#define COMMANODES	FST::NODE (1, FST::RELATION(',', 1)),\
				FST::NODE()




namespace FST
{
	struct RELATION // ребро:символ -> вершина графа переходов КА
	{
		char symbol;  // символ перехода
		short nnode; // номер смежной вершины
		RELATION(
			char c = 0x00, /// символ перехода
			short ns = NULL // новое состояние
		);
	};

	struct NODE // вершина графа переходов
	{
		short n_relation; // количество инциндентных ребер
		RELATION* relations; // инциндентные ребра
		NODE();
		NODE(
			short n, // количество инциндентных ребер
			RELATION rel, ... // список ребер
		);
	};
	struct FST // недетерминированный конечный автомат
	{
		char* string; // цепочка (строка завершается 0х00)
		short position; // текущая позиция в цепочке
		short nstates;  // количество состояний автомата
		NODE* nodes; // граф переходов: [0] - начальное состояние [nstate-1] - конечное
		short* rstates; // возможные состояния автомата на данной позиции
		FST(
			char* s, // цепочка 
			short ns, // количество состояний автомата
			NODE n, ... // список состояний (граф переходов)
		);
	};
	bool execute( // выполнить распознавание цепочки
		FST& fst // недетерминированный автомат
	);
}

