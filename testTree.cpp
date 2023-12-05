#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <stack>
#include "node.h"
#include "testTree.h"

using namespace std;

std::set <string> idList;    // variable declaration
bool semError = 0;
std::stack<Scanner::Token> tkStack;    // tk stack
static int LabelCntr = 0;      // unique labels generated
static int VarCntr = 0;        // unique temporaries generated 
static char Name[20];         // for creation of unique names


string labelNames[] = {
	"PROGRAM", "VARS", "VARLIST", "EXP", "M", "N", "R", "STATS", 
	"MSTAT", "STAT", "BLOCK", "IN", "OUT", "IF", "LOOP", "ASSIGN", "RO"
};

node * createNode(nodeType l){     // initialize all possible tokens and children of node
	node * root = new node;
	root-> label = l;

	Scanner::Token token1;
	Scanner::Token token2;
	Scanner::Token token3;
	Scanner::Token token4;
	Scanner::Token token5;
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


void traversePreorder(node *n, int depth){    // Traverse tree preorder, print nodes
	if(n){
		printNode(n, depth); 	
		traversePreorder(n-> child1, depth+1); 	
		traversePreorder(n-> child2, depth+1);	
		traversePreorder(n-> child3, depth+1);  
		traversePreorder(n-> child4, depth+1);  
	}
}


void printNode(node *n, int depth){    // Print nodes, space them out
	string space = "";

	for(int i = 0; i< depth*2; i++)
		space= space + " ";
		
    cout << space << labelNames[n-> label] << ": "; 
	
	if(n-> tk1.lexeme != "")
		cout << n->tk1.lexeme << " ";
	
	if(n-> tk2.lexeme != "")
		cout << n->tk2.lexeme << " ";
	
	if(n-> tk3.lexeme != "")
   	    cout << n->tk3.lexeme << " ";
	
	if(n-> tk4.lexeme != "")
		cout << n->tk4.lexeme << " ";
	
	if(n-> tk5.lexeme != "")
		cout << n-> tk5.lexeme << " ";
	    
	cout << endl;
}

bool staticSemantics(node *n, int depth){
	if(n){
		insert(n->tk1, labelNames[n-> label]);    // Insert variable declarations
		insert(n->tk2, labelNames[n-> label]);
		insert(n->tk3, labelNames[n-> label]);
		insert(n->tk4, labelNames[n-> label]);
		insert(n->tk5, labelNames[n-> label]);

		verify(n->tk1, labelNames[n-> label]);    // identify use without declaration
		verify(n->tk2, labelNames[n-> label]);
		verify(n->tk3, labelNames[n-> label]);
		verify(n->tk4, labelNames[n-> label]);
		verify(n->tk5, labelNames[n-> label]);		
		
		staticSemantics(n-> child1, depth+1); 	  // Recursive Preorder traversal
		staticSemantics(n-> child2, depth+1);	
		staticSemantics(n-> child3, depth+1);  
		staticSemantics(n-> child4, depth+1);  
		
		return semError;
	}
}

void insert(Scanner::Token tk, string label){ // find id declarations and insert to idlist
	if(tk.lexeme != "" && tk.type == "IDENTIFIER" && label == "VARLIST"){
		auto it = idList.find(tk.lexeme);
		if (it != idList.end()) {      	// Found in idList, throw detailed error msg       
        	std::cout << "SEMANTICAL ERROR: redefinition of " << tk.lexeme;
			std::cout << " on line " << tk.line << "\n";
			semError = 1;
		} else {                       	// Not found in idList, add to idList		
			idList.insert(tk.lexeme);
		}
	}	
}

void verify(Scanner::Token tk, string label){  // verify ids are defined in idlist b4 use
	if(tk.lexeme != "" && tk.type == "IDENTIFIER" && label != "VARLIST"){
		auto it = idList.find(tk.lexeme);
		if (it == idList.end()) {     // Not Found in idList, throw detailed error msg       
        	std::cout << "SEMANTICAL ERROR: use without delcaration: " << tk.lexeme;
			std::cout << " on line " << tk.line << "\n";
			semError = 1;
		}
	}
}

void popStack(FILE *out){
	std::string topInstance = tkStack.top().lexeme;
	tkStack.pop();
	topInstance += "\n";
	fprintf(out, topInstance.c_str());
}

static char *newName(nameType what){
	if (what==VAR) // creating new temporary
		sprintf(Name,"T%d",VarCntr++); /* generate a new label as T0, T1, etc */
	else // creating new Label
		sprintf(Name,"L%d",LabelCntr++); /* new lables as L0, L1, etc */
	return(Name);
}

void recGen(node *n, FILE *out){     // recursive code generation
	string label, label2, argR;    // local temp or labels

	if(n == NULL)
		return;	

	switch(n->label){
		case PROGRAMn:
			cout << "PROGRAM:\n";
			recGen(n->child1, out);
			recGen(n->child2, out);
			// popStack(out);
			fprintf(out, "STOP\n");
			return;
		case INn:
			fprintf(out,"\tREAD\t%s\n",n->tk1.lexeme);
			break;
		case ASSIGNn:
			recGen(n->child1,out);           /* evaluate rhs */
			fprintf(out,"\tSTORE\t%s\n",n->tk1.lexeme);
			break;
		case IFn:
			recGen(n->child3, out);              /* exprRight */
			argR = newName(VAR);
			recGen(n->child1, out);              /* exprLeft */
			fprintf(out,"SUB %s\n",argR.c_str());          /* ACC <- exprLeft - exprRight */
			label = newName(LABEL);
			if (n->child2->tk1.lexeme == "==") {     /* False is ACC != 0 */
				fprintf(out,"BRNEG %s\n",label.c_str());
				fprintf(out,"BRPOS %s\n",label.c_str());
			}
			recGen(n->child4, out);              /* dependent statements */
			fprintf(out,"%s:\tNOOP\n",label.c_str());
			break;
	}
}