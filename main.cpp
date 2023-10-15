#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

#include "scanner.cpp"

int main() {
    std::string source_code = "024x, ɀ, Ɂ ; 025x, ɐ, ɑ ; 026x, ɠ, ɡ ; 027x, ɰ,";
    
    Scanner scanner(source_code);

    Scanner::Token token;
    do {
        token = scanner.getNextToken();
        std::cout << "Type: " << token.type << ", Lexeme: " << token.lexeme << " at line " << token.line << std::endl;
        if (token.type == "EOF")
            break;
    } while (true);

    return 0;
}