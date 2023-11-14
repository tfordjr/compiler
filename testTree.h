#ifndef TESTTREE_H
#define TESTTREE_H
#include "node.h"

node * createNode(nodeType label);
void traversePreorder(node *n, int depth);
void printNode(node *n, int depth);

#endif
