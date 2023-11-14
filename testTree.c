#include <stdio.h>
#include <iostream>
#include <string>
#include "token.h"
#include "node.h"
#include "testTree.h"

using namespace std;



string labelNames[] = {
	"PROGRAM", "BLOCK", "VARS", "EXP", "A", "N", "M", "R", "STATS", 
	"MSTAT", "STAT", "IN", "OUT", "IF", "LOOP", "ASSIGN", "RO"
};


node * createNode(nodeType l)
{
	node * root = new node;
	root-> label = l;

	token token1;
	token token2;
	token token3;
	token token4;
	token token5;
	root -> tk1 = token1;
	root -> tk2 = token2;
	root -> tk3 = token3;
	root -> tk4 = token4;
	root -> tk5 = token5;

	root -> child1 = NULL;
	root -> child2 = NULL;
	root -> child3 = NULL;
	root -> child4 = NULL;
	return root;

}


void traversePreorder(node *n, int depth)
{
	if(n)
	{
		printNode(n, depth); 	
		traversePreorder(n-> child1, depth+1); 	
		traversePreorder(n-> child2, depth+1);	
		traversePreorder(n-> child3, depth+1);  
		traversePreorder(n-> child4, depth+1);  
	}
}


void printNode(node *n, int depth)
{
	string space = "";

	for(int i = 0; i< depth*2; i++)
	{
		space= space + " ";
	} 
	
    cout << space << labelNames[n-> label] << ": "; 

	if(n-> tk1.tokenInstance != "")
	{
		cout << n->tk1.tokenInstance << " ";
	}

	if(n-> tk2.tokenInstance != "")
	{
		cout << n->tk2.tokenInstance << " ";
	}

	if(n-> tk3.tokenInstance != "")
	{
   	         cout << n->tk3.tokenInstance << " ";
	}

	if(n-> tk4.tokenInstance != "")
	{
		cout << n->tk4.tokenInstance << " ";
	}

	if(n-> tk5.tokenInstance != "")
	{
		cout << n-> tk5.tokenInstance << " ";
	}	
    
	cout << endl;
}

