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
void errorMsg(string);

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
        node-> child1 = VarList(scanner);
        return node;
    } else {
        return node;
    }
}

node *VarList(Scanner scanner){
    node *node = createNode(VARLISTn);

    if (tk.type != "IDENTIFIER")
        errorMsg("IDENTIFIER");    
    node-> tk1 = tk;
    tk = scanner.getNextToken();

    if (tk.lexeme != ":") 
        errorMsg("COLON");
    node-> tk2 = tk;
    tk = scanner.getNextToken(); 
    
    if (tk.type != "INTEGER")
        errorMsg("INTEGER");
    node-> tk3 = tk;
    tk = scanner.getNextToken();

    if (tk.lexeme == ";"){
        node-> tk4 = tk;
        tk = scanner.getNextToken();
    } else if (tk.type == "IDENTIFIER") {
        node-> child1 = VarList(scanner);
    } else {
        errorMsg("; or IDENTIFIER");
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

    cout << "Error: Line " << tk.line << ": local scope 1 tk expected, ";
    cout << tk.lexeme << " token was received instead\n";

    if (tk.lexeme != "xopen")
        errorMsg("xopen");
    tk = scanner.getNextToken();    

    cout << "Error: Line " << tk.line << ": local scope 2 tk expected, ";
    cout << tk.lexeme << " token was received instead\n";

    tk = scanner.getNextToken();    

    cout << "Error: Line " << tk.line << ": local scope 3 tk expected, ";
    cout << tk.lexeme << " token was received instead\n";

    tk = scanner.getNextToken();    

    cout << "Error: Line " << tk.line << ": local scope 4 tk expected, ";
    cout << tk.lexeme << " token was received instead\n";

    if (tk.lexeme == "xin") {
        tk = scanner.getNextToken();
        node-> child1 = Stat(scanner);
    } else if (tk.lexeme == "xout"){
        tk = scanner.getNextToken();
        node-> child1 = Out(scanner);
    } else if (tk.lexeme == "{"){
        tk = scanner.getNextToken();
        node-> child1 = Block(scanner);
    } else if (tk.lexeme == "xcond"){
        tk = scanner.getNextToken();
        node-> child1 = If(scanner);
    } else if (tk.lexeme == "xloop"){
        tk = scanner.getNextToken();
        node-> child1 = Loop(scanner);
    } else if (tk.lexeme == "xlet"){
        tk = scanner.getNextToken();
        node-> child1 = Assign(scanner);
    } else {
        cout << "Error: Line " << tk.line << ": local scope tk expected, ";
        cout << tk.lexeme << " token was received instead\n";
        errorMsg("xin or xout or { or xcond or xloop or xlet");
    }  

    return node;
}

node *In(Scanner scanner){
    node *node = createNode(INn);
    return node;
}

node *Out(Scanner scanner){
    node *node = createNode(OUTn);
    return node;
}

node *Block(Scanner scanner){
    node *node = createNode(BLOCKn);
    return node;
}

node *If(Scanner scanner){
    node *node = createNode(IFn);
    return node;
}

node *Loop(Scanner scanner){
    node *node = createNode(LOOPn);
    return node;
}

node *Assign(Scanner scanner){
    node *node = createNode(ASSIGNn);
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

    if (tk.type != "EOF"){
        cout << "Error: Parsing Error\n";
    }

    return root;
}

void errorMsg(string expected) {
    cout << "Error: Line " << tk.line << ": " << expected << " tk expected, ";
    cout << tk.lexeme << " token was received instead\n";
    //exit(1);
}