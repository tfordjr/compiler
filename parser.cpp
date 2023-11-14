#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cctype>
#include "scanner.cpp"
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

node * parser(string input) {  

    Scanner scanner(input);   
    Scanner::Token token;
    tk = scanner.getNextToken();   
    
    node * root;
    root = Program();
    if (token.type == "EOF"){
        return root;
    } else {
        cout << "Error: Parsing Error\n"
        exit(1);
    }
}

