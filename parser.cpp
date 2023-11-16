#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cctype>
#include "scanner.h"
#include "parser.h"
#include "testTree.h"
using namespace std;

string tokenNames[]= {"EOFTk", "IDTk", "INTTk", "ASSIGNTk",
	"COMPARETk", "LESSTHANEQTk", "GREATERTHANEQTk",
	"COLONTk", "INCREMENTTk", "DECREMENTTk", "MULTIPLYTk",
	"DIVIDETk", "MODULUSTk", "DOTTk", "LPARENTHESISTk",
	"RPARENTHESISTk", "COMMATk",  "LBRACETk",
 	"RBRACETk", "SEMICOLONTk", "LBRACKETTk", "RBRACKETTk",  
	"KEYWORDTk", "ERROR", "FALSEID"
};

Scanner::Token tk;
char c;

node *Program();
node *Vars();
node *VarList();
node *Exp();
node *M();
node *N();
node *R();
node *Stats();
node *Mstat();
node *Stat();
node *Block();
node *In();
node *Out();
node *If();
node *Loop();
node *Assign();
node *RO();


node *Program(){
    node *node = createNode(PROGRAMn);
    node-> child1 = Vars();
    node-> child2 = Stats();
    return node;
}

node *Vars(){
    node *node = createNode(VARSn);
    if(tk.lexeme == "xdata"){
        cout << "xdata is lexeme\n";
    } else {
        return node;
    }
}

node *Stats(){
    node *node = createNode(STATSn);
    return node;
}



node *parser(string input) {  

    Scanner scanner(input);   
    Scanner::Token token;
    tk = scanner.getNextToken();

    node *root;
    root = Program();


    // DELETE
    // while(tk.type != "EOF"){
    //     tk = scanner.getNextToken();
    // }
    // DELETE

    if (tk.type != "EOF"){
        cout << "Error: Parsing Error\n";
    }

    return root;

    // if (tk.type == "EOF"){
    //     return root;
    // } else {
    //     cout << "Error: Parsing Error\n";        
    //     exit(1);
    // }
}

