#ifndef NODE_H
#define NODE_H
#include "scanner.h"
enum nodeType { 
	PROGRAMn, VARSn, VARLISTn, EXPn, Mn, Nn, Rn, STATSn, MSTATn, STATn, 
	BLOCKn, INn, OUTn, IFn, LOOPn, ASSIGNn, ROn
};

struct node {
	nodeType label;
	Scanner::Token tk1;
    Scanner::Token tk2;
    Scanner::Token tk3;
    Scanner::Token tk4;
    Scanner::Token tk5;
	node *child1, *child2, *child3, *child4;
};


#endif
