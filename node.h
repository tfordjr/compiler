#ifndef NODE_H
#define NODE_H
#include "scanner.cpp"

enum nodeType { 
	PROGRAMn, BLOCKn, VARSn, EXPn, An, Nn, Mn, Rn, STATSn, MSTATn, STATn, 
	INn, OUTn, IFn, LOOPn, ASSIGNn, ROn
};

struct node
{
	nodeType label;
	Scanner::Token tk1;
    Scanner::Token tk2;
    Scanner::Token tk3;
    Scanner::Token tk4;
    Scanner::Token tk5;
	node *child1, *child2, *child3, *child4;
};


#endif
