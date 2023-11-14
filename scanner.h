#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <cctype>

class Scanner {
public:
    Scanner(const std::string& source);

    struct Token {
        std::string type;
        std::string lexeme;
        int line;
    };

    Token getNextToken();

private:
    const std::string& source;
    size_t position;
    int line;

    bool isIdentifierChar(char c);

    bool isOperatorChar(char c);

    void reportError(const std::string& message);
};

#endif // SCANNER_H
