// Jessica Seabolt CMP SCI 4280 Project 1 Updated 03/12/2024

#include <stdio.h>
#include "scanner.h"
#include "testScanner.h"

int main(int argc, char *argv[]) {
    FILE *inputFile = NULL;

    if (argc > 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    } else if (argc == 2) {
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            printf("Unable to open file: %s\n", argv[1]);
            return 1;
        }
    } else {
        inputFile = stdin;
    }

    initFSATable();
    testScanner(inputFile);

    if (inputFile != stdin) {
        fclose(inputFile);
    }

    return 0;
}