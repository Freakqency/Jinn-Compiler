#include "lexer.h"
#include "token.h"

static int getTok() {
    // Handle white space
    static int LastChar = ' ';
    while (isspace(LastChar)) {
        LastChar = getchar();
    }
    // Handle keywords
    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while (isalnum(LastChar)) {
            LastChar = getchar();
            IdentifierStr += LastChar;
        }

        if (IdentifierStr == "def") {
            return tok_def;
        }
        if (IdentifierStr == "extern") {
            return tok_extern;
        }
        return tok_identifier;
    }
    // Handle numbers & .
    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumVal;
        do {
            NumVal += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');
        NumVal = strtod(NumVal.c_str(), 0);
        return tok_number;
    }
    // Skip comments
    if (LastChar == '#') {
        do {
            LastChar = getchar();
        } while (LastChar != EOF || LastChar != '\n' || LastChar != '\r');
    }
    // Handle '+' & EOF
    if (LastChar == EOF) {
        return tok_eof;
    }
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}
