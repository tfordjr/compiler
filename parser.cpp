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

node *Program(Scanner*);
node *Vars(Scanner*);
node *VarList(Scanner*);
node *Exp(Scanner*);
node *M(Scanner*);
node *N(Scanner*);
node *R(Scanner*);
node *Stats(Scanner*);
node *Mstat(Scanner*);
node *Stat(Scanner*);
node *Block(Scanner*);
node *In(Scanner*);
node *Out(Scanner*);
node *If(Scanner*);
node *Loop(Scanner*);
node *Assign(Scanner*);
node *RO(Scanner*);
void errorMsg(string);

node *Program(Scanner *scanner){
    node *node = createNode(PROGRAMn);
    node-> child1 = Vars(scanner);

    if (tk.lexeme != "xopen")
        errorMsg("xopen");
    tk = (*scanner).getNextToken();

    node-> child2 = Stats(scanner);

    if (tk.lexeme != "xclose")
        errorMsg("xclose");
    tk = (*scanner).getNextToken();

    return node;
}

node *Vars(Scanner *scanner){
    node *node = createNode(VARSn);
    if(tk.lexeme == "xdata"){
        tk = (*scanner).getNextToken();
        node-> child1 = VarList(scanner);
    } 
    return node;    
}

node *VarList(Scanner *scanner){
    node *node = createNode(VARLISTn);

    if (tk.type != "IDENTIFIER")
        errorMsg("IDENTIFIER");    
    node-> tk1 = tk;
    tk = (*scanner).getNextToken();

    if (tk.lexeme != ":") 
        errorMsg("COLON");
    node-> tk2 = tk;
    tk = (*scanner).getNextToken(); 
    
    if (tk.type != "INTEGER")
        errorMsg("INTEGER");
    node-> tk3 = tk;
    tk = (*scanner).getNextToken();

    if (tk.lexeme == ";"){
        node-> tk4 = tk;
        tk = (*scanner).getNextToken();
    } else if (tk.type == "IDENTIFIER") {
        node-> child1 = VarList(scanner);
    } else {
        errorMsg("; or IDENTIFIER");
    }                          

    return node;
}

node *Exp(Scanner *scanner){
    node *node = createNode(EXPn);

    node-> child1 = M(scanner);   // Create <M> 

    if (tk.lexeme == "/" || tk.lexeme == "*"){
        node-> tk1 = tk;
        tk = (*scanner).getNextToken();
        node-> child1 = Exp(scanner);
    }         

    return node;
}

node *M(Scanner *scanner){
    node *node = createNode(Mn);

    node-> child1 = N(scanner);

    return node;
}

node *N(Scanner *scanner){
    node *node = createNode(Nn);

    if (tk.lexeme == "~"){   // ~ <N>
        node-> tk1 = tk;
        tk = (*scanner).getNextToken();
        node-> child1 = N(scanner);
    } else {                // <R> - <N> || <R> case
        node-> child1 = R(scanner); // This will advance tk, we don't need to 
        if (tk.lexeme == "-"){    // <R> - <N> case
            node-> tk1 = tk;
            tk = (*scanner).getNextToken();
            node-> child1 = N(scanner); 
        } 
    }

    return node;
}

node *R(Scanner *scanner){
    node *node = createNode(Rn);

    if (tk.lexeme == "(") {        
        node-> child1 = Exp(scanner);
        if(tk.lexeme != ")")
            errorMsg(")");        
    } else if (tk.type != "IDENTIFIER" && tk.type != "INTEGER")
        errorMsg("IDENTIFIER OR INTEGER");
    else
        node->tk1 = tk;

    tk = (*scanner).getNextToken();  
    return node;
}

node *Stats(Scanner *scanner){
    node *node = createNode(STATSn);
    node-> child1 = Stat(scanner);
    node-> child2 = Mstat(scanner);
    return node;
}

node *Mstat(Scanner *scanner){   // I think this code is good but too early to test
    node *node = createNode(MSTATn);
    // if (tk.lexeme == "xin" || tk.lexeme == "xout" || tk.lexeme == "{" || 
    // tk.lexeme == "xcond" || tk.lexeme == "xloop" || tk.lexeme == "xlet"){
    //     node-> child1 = Stat(scanner);
    //     node-> child2 = Mstat(scanner);   
    // }
    return node;
}

node *Stat(Scanner *scanner){
    node *node = createNode(STATn);      

    if (tk.lexeme == "xin") {
        tk = (*scanner).getNextToken();
        node-> child1 = In(scanner);
    } else if (tk.lexeme == "xout"){
        tk = (*scanner).getNextToken();
        node-> child1 = Out(scanner);
    } else if (tk.lexeme == "{"){
        tk = (*scanner).getNextToken();
        node-> child1 = Block(scanner);
    } else if (tk.lexeme == "xcond"){
        tk = (*scanner).getNextToken();
        node-> child1 = If(scanner);
    } else if (tk.lexeme == "xloop"){
        tk = (*scanner).getNextToken();
        node-> child1 = Loop(scanner);
    } else if (tk.lexeme == "xlet"){
        tk = (*scanner).getNextToken();
        node-> child1 = Assign(scanner);
    } else {
        errorMsg("xin or xout or { or xcond or xloop or xlet");
    }  

    return node;
}

node *Block(Scanner *scanner){
    node *node = createNode(BLOCKn);

    node-> child1 = Vars(scanner);
    node-> child2 = Stats(scanner);

    if(tk.lexeme != "}")
        errorMsg("}");
    tk = (*scanner).getNextToken();

    return node;
}

node *In(Scanner *scanner){
    node *node = createNode(INn);

    if (tk.lexeme != ">>")
        errorMsg(">>");    
    tk = (*scanner).getNextToken();
    
    if (tk.type != "IDENTIFIER")
        errorMsg("IDENTIFIER");    
    node-> tk1 = tk;
    tk = (*scanner).getNextToken();

    if (tk.lexeme != ";")
        errorMsg(";");  
    tk = (*scanner).getNextToken();

    return node;
}

node *Out(Scanner *scanner){
    node *node = createNode(OUTn);

    if (tk.lexeme != "<<")
        errorMsg("<<"); 
    tk = (*scanner).getNextToken();

    node-> child1 = Exp(scanner);    // <EXP>

    if (tk.lexeme != ";")
        errorMsg(";");         
    tk = (*scanner).getNextToken();
    
    return node;
}

node *If(Scanner *scanner){
    node *node = createNode(IFn);

    if (tk.lexeme != "[")
        errorMsg("["); 
    tk = (*scanner).getNextToken();

    node-> child1 = Exp(scanner);
    node-> child2 = RO(scanner);
    node-> child3 = Exp(scanner);

    if (tk.lexeme != "]")
        errorMsg("]"); 
    tk = (*scanner).getNextToken();

    node-> child4 = Stat(scanner);

    return node;
}

node *Loop(Scanner *scanner){
    node *node = createNode(LOOPn);

    if (tk.lexeme != "[")
        errorMsg("["); 
    tk = (*scanner).getNextToken();

    node-> child1 = Exp(scanner);
    node-> child2 = RO(scanner);
    node-> child3 = Exp(scanner);

    if (tk.lexeme != "]")
        errorMsg("]"); 
    tk = (*scanner).getNextToken();

    node-> child4 = Stat(scanner);

    return node;
}

node *Assign(Scanner *scanner){
    node *node = createNode(ASSIGNn);

    if (tk.type != "IDENTIFIER")
        errorMsg("IDENTIFIER");    
    node-> tk1 = tk;
    tk = (*scanner).getNextToken();   

    node-> child1 = Exp(scanner);

    if (tk.lexeme != ";")
        errorMsg(";"); 
    tk = (*scanner).getNextToken();

    return node;
}

node *RO(Scanner *scanner){
    node *node = createNode(ROn);
    
    if (tk.lexeme == "<<" || tk.lexeme == ">>"){
        node-> tk1 = tk;
        tk = (*scanner).getNextToken();
        node->tk2 = tk;
        return node;
    } 

    if (tk.lexeme != "<" && tk.lexeme != ">" && tk.lexeme != "=" && tk.lexeme != "%")
        errorMsg("< or > or = or %");
    node-> tk1 = tk;
    tk = (*scanner).getNextToken();

    return node;
}

node *parser(string input) {  

    cout << input << '\n';

    Scanner scanner(input);      
    tk = scanner.getNextToken();

    node *root;
    root = Program(&scanner);    

    if (tk.type != "EOF"){
        cout << "Error: Parsing Error\n";
    }

    return root;
}

void errorMsg(string expected) {
    cout << "Error: Line " << tk.line << ": " << expected << " tk expected, ";
    cout << tk.lexeme << " token was received instead\n";
    exit(1);
}