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

node *Program(Scanner);
node *Vars(Scanner);
node *VarList(Scanner);
node *Exp(Scanner);
node *M(Scanner);
node *N(Scanner);
node *R(Scanner);
node *Stats(Scanner);
node *Mstat(Scanner);
node *Stat(Scanner);
node *Block(Scanner);
node *In(Scanner);
node *Out(Scanner);
node *If(Scanner);
node *Loop(Scanner);
node *Assign(Scanner);
node *RO(Scanner);


node *Program(Scanner scanner){
    node *node = createNode(PROGRAMn);
    node-> child1 = Vars(scanner);
    node-> child2 = Stats(scanner);
    return node;
}

node *Vars(Scanner scanner){
    node *node = createNode(VARSn);
    if(tk.lexeme == "xdata"){
        tk = scanner.getNextToken();
        VarList(scanner);
        return node;
    } else {
        return node;
    }
}

node *VarList(Scanner scanner){
    node *node = createNode(VARLISTn);
    string buffer = "";

    if (tk.type == "IDENTIFIER"){
        buffer += tk.lexeme + " ";
        tk = scanner.getNextToken();
        if (tk.lexeme == ":") {
            buffer += tk.lexeme + " ";
            tk = scanner.getNextToken(); 
            if (tk.type == "INTEGER"){
                buffer += tk.lexeme + " ";
                tk = scanner.getNextToken();
                if (tk.lexeme == ";"){
                    buffer += tk.lexeme + " ";
                    tk = scanner.getNextToken();
                    cout << buffer << "\n";
                    return node;
                } else if (tk.type == "IDENTIFIER") {
                    cout << buffer << "\n";
                    VarList(scanner);
                } else {
                    cout << "Error: Line " << tk.line << "; or ID tk expected,";
                    cout << tk.lexeme << " token was received instead";
                    exit(1);
                }
            }
        }               
    }
    return node;
}

node *Stats(Scanner scanner){
    node *node = createNode(STATSn);
    node-> child1 = Stat(scanner);
    node-> child2 = Mstat(scanner);
    return node;
}

node *Stat(Scanner scanner){
    node *node = createNode(STATn);
    return node;
}

node *Mstat(Scanner scanner){
    node *node = createNode(MSTATn);
    return node;
}

node *parser(string input) {  

    Scanner scanner(input);      
    tk = scanner.getNextToken();

    node *root;
    root = Program(scanner);

    // DELETE
    // while(tk.type != "EOF"){
    //     tk = scanner.getNextToken();
    // }
    // DELETE

    if (tk.type != "EOF"){
        cout << "Error: Parsing Error\n";
    }

    return root;
}

