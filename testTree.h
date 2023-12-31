#ifndef TESTTREE_H
#define TESTTREE_H

#include <set>
#include "node.h"
using namespace std;

typedef enum {VAR, LABEL} nameType;    

node * createNode(nodeType label);
void traversePreorder(node *n, int depth);
void printNode(node *n, int depth);
bool staticSemantics(node *n, int depth);
void insert(Scanner::Token tk, string label);
void verify(Scanner::Token tk, string label);
static char *newName(nameType what);
void recGen(node *n, FILE *out);

#endif
