#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include <fstream>

using namespace std;

#include "scanner.h"
#include "testTree.h"
#include "node.h"
#include "parser.h"

int main(int argc, char* argv[]){
    
    std::string outfileName;
    std::ifstream inputFile;  // File Object
    std::string input;        // input buffer will hold input regardless of input method

    if (argc > 2) {    //If too many args provided
        std::cerr << "Too many arguments" << std::endl;
        return 1;
    } else if (argc == 1) {        //  If no args are provided, read stdin
        std::cout << "Needs to read from keyboard..." << std::endl;
        std::string line;

        while (std::getline(std::cin, line)) {
            input += line + '\n';  // store stdin in input string
        } 
        outfileName = "outfile.asm";
    } else {
        outfileName = std::string(argv[1]) + ".asm";
        std::string filename = std::string(argv[1]) + ".f23"; // append .f23 to filename
        inputFile.open(filename);
        if (!inputFile) {
            std::cerr << "Can't open file..." << std::endl;  // error checking file
            return 1;
        } else {
            std::cout << "File opened successfully!" << std::endl;          
	    std:: string line;       

            while (std::getline(inputFile, line)) {
                input += line + '\n';   // Store input file in input string
            }     
        }
    }      
 
    // Scanner scanner(input);   // run this and nothing below to 
    // Scanner::Token token;     // get only raw scanner output!
    // std::cout << "RAW SCANNER OUTPUT: \n";
    // do {
    //     token = scanner.getNextToken();
    //     std::cout << "Type: " << token.type << ", Lexeme: " << token.lexeme << " at line " << token.line << std::endl;
    //     if (token.type == "EOF")
    //         break;
    // } while (true);

    std::cout << "\nSource Program:\n" << input << "\nParse Tree output: \n";
    node *root = parser(input);       // build parse tree, scanner happens within parser
    traversePreorder(root, 0);        // print parse tree
    
    bool semError = staticSemantics(root, 0);      // check for static semantics
    if(semError){
        cout << "semError returned.\n";       // end execution if semantic errors
        return 0;
    }


    FILE *outFile = fopen(outfileName.c_str(), "w");     // .asm file generation
    // std::ofstream outFile(outfileName);     
    if(!outFile){
        cout << ".asm file creation failed";
        return 0;
    }

    recGen(root, outFile);

    fclose(outFile);

    return 0;
}