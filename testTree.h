#ifndef TESTTREE_H
#define TESTTREE_H

#include <set>
#include "node.h"
using namespace std;

node * createNode(nodeType label);
void traversePreorder(node *n, int depth);
void printNode(node *n, int depth);
bool staticSemantics(node *n, int depth);
void insert(Scanner::Token tk, string label);
void verify(Scanner::Token tk, string label);
void popStack(FILE *out);
void codeGeneration(node *n, FILE *out);

#endif
