#ifndef NODE_H
#define NODE_H
#include "token.h"

enum nodeType { 
	PROGRAMn, BLOCKn, VARSn, EXPn, An, Nn, Mn, Rn, STATSn, MSTATn, STATn, 
	INn, OUTn, IFn, LOOPn, ASSIGNn, ROn
};

struct node
{
	nodeType label;
	token tk1, tk2, tk3, tk4, tk5;
	node *child1, *child2, *child3, *child4;
};


#endif
