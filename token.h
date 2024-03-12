// Jessica Seabolt CMP SCI 4280 Project 1 Updated 03/12/2024

#ifndef TOKEN_H
#define TOKEN_H

typedef struct {
    int tokenID;
    char* tokenInstance;
    int lineNumber;
    int charNumber;
} Token;

enum TokenType {
    ID_TK,
    KEYWORD_TK,
    INT_TK,
    OPERATOR_TK,
    EOF_TK
};

#endif