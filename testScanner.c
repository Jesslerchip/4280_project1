#include "scanner.h"
#include "token.h"
#include <stdio.h>

void testScanner(FILE* inputFile) {
    Token token;
    do {
        token = getToken(inputFile);
        // Print the token information
        printf("Token Type: %d, Token Instance: %s, Line: %d, Char: %d\n",
               token.tokenID, token.tokenInstance, token.lineNumber, token.charNumber);
    } while (token.tokenID != EOF_TK);
}