// Jessica Seabolt CMP SCI 4280 Project 1 Updated 03/12/2024

#include "scanner.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 256

int lineNumber = 1;
int charNumber = 1;

char reservedWords[16][9] = {
    "start", "stop", "while", "repeat", "until", "label", "return",
    "cin", "cout", "tape", "jump", "if", "then", "pick", "create", "set"
};

Token getToken(FILE* inputFile) {
    Token token;
    char buffer[MAX_TOKEN_LEN + 1];
    int bufferIndex = 0;
    int state = 0;
    int c;

    while (1) {
        c = fgetc(inputFile);

        if (c == EOF) {
            token.tokenID = EOF_TK;
            token.tokenInstance = NULL;
            token.lineNumber = lineNumber;
            token.charNumber = charNumber;
            return token;
        }

        switch (state) {
            case 0:
                if (isalpha(c)) {
                    state = 1;
                    buffer[bufferIndex++] = c;
                } else if (isdigit(c)) {
                    state = 3;
                    buffer[bufferIndex++] = c;
                } else if (c == '/' && (c = fgetc(inputFile)) == '/') {
                    state = 5;
                } else if (strchr("=<>:+-*/^.(),{}[];|&!", c) != NULL) {
                    state = 6;
                    buffer[bufferIndex++] = c;
                } else if (isspace(c)) {
                    if (c == '\n') {
                        lineNumber++;
                        charNumber = 1;
                    } else {
                        charNumber++;
                    }
                } else {
                    printf("SCANNER ERROR: Invalid character '%c' at line %d, char %d\n", c, lineNumber, charNumber);
                    charNumber++;
                }
                break;

            case 1:
                if (isalnum(c) || c == '_') {
                    if (bufferIndex < MAX_TOKEN_LEN) {
                        buffer[bufferIndex++] = c;
                    } else {
                        printf("SCANNER ERROR: Identifier too long at line %d, char %d\n", lineNumber, charNumber);
                    }
                } else {
                    buffer[bufferIndex] = '\0';
                    ungetc(c, inputFile);
                    token.tokenInstance = strdup(buffer);
                    int i;
                    for (i = 0; i < 16; i++) {
                        if (strcmp(reservedWords[i], buffer) == 0) {
                            token.tokenID = KEYWORD_TK;
                            break;
                        }
                    }
                    if (i == 16) {
                        token.tokenID = ID_TK;
                    }
                    token.lineNumber = lineNumber;
                    token.charNumber = charNumber;
                    charNumber += bufferIndex;
                    return token;
                }
                break;

            case 3:
                if (isdigit(c)) {
                    if (bufferIndex < MAX_TOKEN_LEN) {
                        buffer[bufferIndex++] = c;
                    } else {
                        printf("SCANNER ERROR: Integer too long at line %d, char %d\n", lineNumber, charNumber);
                    }
                } else {
                    buffer[bufferIndex] = '\0';
                    ungetc(c, inputFile);
                    token.tokenInstance = strdup(buffer);
                    token.tokenID = INT_TK;
                    token.lineNumber = lineNumber;
                    token.charNumber = charNumber;
                    charNumber += bufferIndex;
                    return token;
                }
                break;

            case 5:
                while (c != '\n' && c != EOF) {
                    c = fgetc(inputFile);
                }
                if (c == '\n') {
                    lineNumber++;
                    charNumber = 1;
                }
                state = 0;
                break;

        case 6:
            if (strchr("=<>:+-*/^.(),{}[];|&!", c) != NULL) {
                if (bufferIndex == 0 || (bufferIndex == 1 && (buffer[0] == '=' || buffer[0] == ':' || buffer[0] == '|' || buffer[0] == '&')) || (bufferIndex == 2 && (buffer[1] == '!'))) {
                    buffer[bufferIndex++] = c;
                    if (bufferIndex == 2 && (strcmp(buffer, "==") == 0 || strcmp(buffer, ":=") == 0 || strcmp(buffer, "||") == 0 || strcmp(buffer, "&&") == 0)) {
                        buffer[bufferIndex] = '\0';
                        token.tokenInstance = strdup(buffer);
                        token.tokenID = OPERATOR_TK;
                        token.lineNumber = lineNumber;
                        token.charNumber = charNumber;
                        charNumber += bufferIndex;
                        return token;
                    }
                    else if (bufferIndex == 3 && (strcmp(buffer, "=!=") == 0)) {
                        buffer[bufferIndex] = '\0';
                        token.tokenInstance = strdup(buffer);
                        token.tokenID = OPERATOR_TK;
                        token.lineNumber = lineNumber;
                        token.charNumber = charNumber;
                        charNumber += bufferIndex;
                        return token;
                    }
                } else {
                    ungetc(c, inputFile);
                    buffer[bufferIndex] = '\0';
                    token.tokenInstance = strdup(buffer);
                    token.tokenID = OPERATOR_TK;
                    token.lineNumber = lineNumber;
                    token.charNumber = charNumber;
                    charNumber += bufferIndex;
                    return token;
                }
            } else {
                ungetc(c, inputFile);
                if (bufferIndex > 0) {
                    buffer[bufferIndex] = '\0';
                    token.tokenInstance = strdup(buffer);
                    token.tokenID = OPERATOR_TK;
                    token.lineNumber = lineNumber;
                    token.charNumber = charNumber;
                    charNumber += bufferIndex;
                    return token;
                } else {
                    printf("SCANNER ERROR: Invalid character '%c' at line %d, char %d\n", c, lineNumber, charNumber);
                    charNumber++;
                    state = 0;
                    buffer[0] = '\0';
                    bufferIndex = 0;
                }
            }
            break;
        }
    }
}