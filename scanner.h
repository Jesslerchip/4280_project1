// Jessica Seabolt CMP SCI 4280 Project 1 Updated 03/12/2024

#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include <stdio.h>

#define MAX_STATES 4
#define MAX_CHARS 128

enum State {
    START,
    IDENTIFIER,
    INTEGER,
    OPERATOR
};

extern int fsaTable[MAX_STATES][MAX_CHARS];
void initFSATable();
int getNextState(int currentState, unsigned char c);
Token getToken(FILE* inputFile);

#endif