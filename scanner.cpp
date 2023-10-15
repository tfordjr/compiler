#include <iostream>
#include <string>
#include <cctype>

class Scanner {
public:
    Scanner(const std::string& source) : source(source), position(0), line(1) {}

    struct Token {
        std::string type;
        std::string lexeme;
        int line;
    };

    Token getNextToken() {
        Token token;
        char current_char;

		

        while (position < source.size()) {   	

            current_char = source[position];

            if (std::isspace(current_char)) {
                if (current_char == '\n') {
                    line++;
                }
                position++;
                continue;
            }

            if (std::isalpha(current_char) && islower(current_char)) {
                if (current_char != 'x'){
		    position++;
		    continue;
		}

                token.type = "IDENTIFIER";
                while (position < source.size() && isalnum(source[position])) {
                    if(token.lexeme.size() < 8)
                        token.lexeme += source[position++];
                    else{
                        token.line = line;
		        return token;                         
		    }
                }
                if (token.lexeme == "xopen" || token.lexeme == "xclose" || token.lexeme == "xloop" ||
                    token.lexeme == "xdata" || token.lexeme == "xexit" || token.lexeme == "xin" ||
                    token.lexeme == "xout" || token.lexeme == "xcond" || token.lexeme == "xthen" ||
                    token.lexeme == "xlet" || token.lexeme == "xfunc") {
                    token.type = "KEYWORD";
                }
		token.line = line;
                return token;
            }

            if (isIdentifierChar(current_char)) {
                reportError("error: scanner.cpp: Identifiers must start with 'x'.");
                position++;
                continue;
            }

            if (current_char == '$') {
                token.type = "COMMENT";
                position++;
                while (position < source.size() && source[position] != '$') {
                    token.lexeme += source[position++];
                }
                if (position < source.size() && source[position] == '$') {
                    position++;
                } else {
                    reportError("error: scanner.cpp: comment does not close with '$'");
                }
		token.line = line;
                return token;
            }

            if (isOperatorChar(current_char)) {
                token.type = "OPERATOR";
                token.lexeme += current_char;
                position++;
                if (position < source.size() && isOperatorChar(source[position]) 
                    && ((token.lexeme == "<") && (source[position] == *"<") 
                    || (token.lexeme == ">") && (source[position] == *">"))) {
                    token.lexeme += source[position++];
                }
		token.line = line;
                return token;
            }

            if (std::isdigit(current_char)) {
                token.type = "INTEGER";
                while (position < source.size() && std::isdigit(source[position])) {
                    if(token.lexeme.size() < 8)
                        token.lexeme += source[position++];
                    else{
			token.line = line;
                        return token;
		    }
                }
		token.line = line;
                return token;
            }
            
            reportError("error: scanner.cpp: Unexpected character: " + current_char);
            position++;
        }

        token.type = "EOF";
        token.line = line;
        return token;
    }

private:
    const std::string& source;
    size_t position;
    int line;

    bool isIdentifierChar(char c) {
        return isalnum(c) && islower(c);
    }

    bool isOperatorChar(char c) {
        std::string operators = "=<>~:;+-*/%.(),{}[]";
        return operators.find(c) != std::string::npos;
    }

    void reportError(const std::string& message) {
        std::cerr << "LEXICAL ERROR at line " << line << ": " << message << std::endl;        
    }
};
