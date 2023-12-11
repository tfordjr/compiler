#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <set>
#include <stack>
#include "node.h"
#include "testTree.h"

using namespace std;

std::set <string> idList;    // variable declaration
bool semError = 0;
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
			cout << "\nASM OUTPUT:\n";			
			recGen(n->child2, out);
			fprintf(out, "\nSTOP\n");	
			recGen(n->child1, out);	
			for (int i = 0; i < VarCntr; i++)
				fprintf(out,"T%d 0\n", i);			
			return;
		case VARSn:
			recGen(n->child1, out);
			break;
		case VARLISTn:	
			recGen(n->child1, out);		
			fprintf(out,"%s %s\n",n->tk1.lexeme.c_str(), n->tk3.lexeme.c_str());			
			break;		
		case EXPn:
			recGen(n->child1, out);
			recGen(n->child2, out);
			break;
		case Mn:
			recGen(n->child1, out);
			recGen(n->child2, out);
			if(n->tk1.lexeme == "+"){
				argR = newName(VAR);
				fprintf(out,"\nSTACKR 0\nPOP");         
				fprintf(out,"\nSTORE %s", argR.c_str());     
				fprintf(out,"\nSTACKR 0\nPOP");				 
				fprintf(out,"\nADD %s", argR.c_str());
				fprintf(out,"\nPUSH\nSTACKW 0");
			}
			break;
		case Nn:
			recGen(n->child1, out);	
			recGen(n->child2, out);				
			if(n->tk1.lexeme == "-"){
				argR = newName(VAR);
				fprintf(out,"\nSTACKR 0\nPOP");         
				fprintf(out,"\nSTORE %s", argR.c_str());     
				fprintf(out,"\nSTACKR 0\nPOP");				 
				fprintf(out,"\nSUB %s", argR.c_str());
				fprintf(out,"\nPUSH\nSTACKW 0");
			} else if (n->tk1.lexeme == "~"){
				fprintf(out,"\nSTACKR 0\nPOP"); 
				fprintf(out,"\nMULT -1"); 
				fprintf(out,"\nPUSH\nSTACKW 0");
			}
			break;
		case Rn:
			if(n->tk1.type == "IDENTIFIER"){
				fprintf(out,"\nLOAD %s",n->tk1.lexeme.c_str());
				fprintf(out,"\nPUSH\nSTACKW 0");
			} else if(n->tk1.type == "INTEGER"){
				fprintf(out,"\nLOAD %s",n->tk1.lexeme.c_str());
				fprintf(out,"\nPUSH\nSTACKW 0");				
			}	

			recGen(n->child1, out);   // (<exp>) case, child1 is null except for this case
			break;
		case STATSn:
			recGen(n->child1, out);
			recGen(n->child2, out);
			break;
		case MSTATn:
			recGen(n->child1, out);
			recGen(n->child2, out);
			break;
		case STATn:
			recGen(n->child1, out);
			break;
		case BLOCKn:
			recGen(n->child1, out);
			recGen(n->child2, out);
			break;
		case INn:
			fprintf(out,"READ %s",n->tk1.lexeme.c_str());
			break;
		case OUTn:
			argR = newName(VAR);
			recGen(n->child1, out);
			fprintf(out,"\nSTACKR 0");
			fprintf(out,"\nPOP");
			fprintf(out,"\nSTORE %s",argR.c_str());
			fprintf(out,"\nWRITE %s",argR.c_str());
			break;			
		case IFn:
			recGen(n->child3, out);              /* exprRight */
			argR = newName(VAR);
			fprintf(out,"\nSTORE %s",argR.c_str()); 
			recGen(n->child1, out);              /* exprLeft */			
			fprintf(out,"\nSUB %s",argR.c_str());     /* ACC <- exprLeft - exprRight */
			label = newName(LABEL);
			if (n->child2->tk1.lexeme == "%") {      //  % MODULUS CASE
				fprintf(out,"\nBRZERO %s",label.c_str());
			} else if (n->child2->tk1.lexeme == "<") {      // < LESS THAN
				fprintf(out,"\nBRZPOS %s",label.c_str());
			} else if (n->child2->tk1.lexeme == ">") {      // > GREATER THAN
				fprintf(out,"\nBRZNEG %s",label.c_str());
			} else if (n->child2->tk1.lexeme == "<<") {     // << LESS THAN OR EQUAL
				fprintf(out,"\nBRPOS %s",label.c_str());
			} else if (n->child2->tk1.lexeme == ">>") {    // >> GREATER THAN OR EQUAL
				fprintf(out,"\nBRNEG %s",label.c_str());
			} else if (n->child2->tk1.lexeme == "=") {
				fprintf(out,"\nBRPOS %s",label.c_str());   // = EQUALITY COMPARITOR
				fprintf(out,"\nBRNEG %s",label.c_str());
			}
			recGen(n->child4, out);              
			fprintf(out,"\n%s: NOOP",label.c_str());
			break;
		case LOOPn:
			argR = newName(VAR);
			label = newName(LABEL);
			label2 = newName(LABEL);
			fprintf(out,"\n%s: NOOP",label.c_str());
			recGen(n->child3, out); 
			fprintf(out,"\nSTORE %s",argR.c_str()); 
			recGen(n->child1, out);              /* exprLeft */			
			fprintf(out,"\nSUB %s",argR.c_str());     /* ACC <- exprLeft - exprRight */			
			if (n->child2->tk1.lexeme == "%") {      //  % MODULUS CASE
				fprintf(out,"\nBRZERO %s",label.c_str());
			} else if (n->child2->tk1.lexeme == "<") {      // < LESS THAN
				fprintf(out,"\nBRZPOS %s",label.c_str());
			} else if (n->child2->tk1.lexeme == ">") {      // > GREATER THAN
				fprintf(out,"\nBRZNEG %s",label.c_str());
			} else if (n->child2->tk1.lexeme == "<<") {     // << LESS THAN OR EQUAL
				fprintf(out,"\nBRPOS %s",label.c_str());
			} else if (n->child2->tk1.lexeme == ">>") {    // >> GREATER THAN OR EQUAL
				fprintf(out,"\nBRNEG %s",label.c_str());
			} else if (n->child2->tk1.lexeme == "=") {
				fprintf(out,"\nBRPOS %s",label.c_str());   // = EQUALITY COMPARITOR
				fprintf(out,"\nBRNEG %s",label.c_str());
			}
			recGen(n->child4, out);              
			fprintf(out,"\nBR %s\n",label.c_str());    // LABEL NAME WRONG
			fprintf(out,"\n%s: NOOP",label2.c_str());
			break;
		case ASSIGNn:
			// fprintf(out,"\nSTACKW 0"); 
			
			fprintf(out,"\nLOAD ");    			 
			recGen(n->child1,out);           /* evaluate rhs */
			fprintf(out,"\nSTORE %s",n->tk1.lexeme.c_str());			
			break;	
		case ROn:
			recGen(n->child1, out);
			fprintf(out," %s ",n->tk1.lexeme.c_str());
			break;
	}
}