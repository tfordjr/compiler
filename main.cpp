#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

#include "scanner.cpp"

int main(int argc, char* argv[]) {

    std::ifstream inputFile;  
    std::string input; 

    if (argc > 2) {
        std::cerr << "Too many arguments" << std::endl;
        return 1;
    } else if (argc == 1) {
        std::cout << "Needs to read from keyboard..." << std::endl;
        std::string line;
        while (std::getline(std::cin, line)) {
            input += line + "\n";  // Append the line to the input string
        } 
    } else {
        std::string filename = std::string(argv[1]) + ".f23";
        inputFile.open(filename);
        if (!inputFile) {
            std::cerr << "Can't open file..." << std::endl;
            return 1;
        } else {
            std::cout << "File opened successfully!" << std::endl;          
	    std:: string line;       

            while (std::getline(inputFile, line)) {
                input += line + "\n";
            }
     
        }
    }    


    std::string source_code = "024x, ɀ, Ɂ ; 025x, ɐ, ɑ ; 026x, ɠ, ɡ ; 027x, ɰ,";
    
    Scanner scanner(input);

    Scanner::Token token;
    do {
        token = scanner.getNextToken();
        std::cout << "Type: " << token.type << ", Lexeme: " << token.lexeme << " at line " << token.line << std::endl;
        if (token.type == "EOF")
            break;
    } while (true);

    return 0;
}
