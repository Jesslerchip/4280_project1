#include <stdio.h>
#include "testScanner.h"

int main(int argc, char* argv[]) {
    FILE* inputFile;

    if (argc > 2) {
        printf("Error: Too many arguments\n");
        return 1;
    } else if (argc == 2) {
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            printf("Error: Unable to open file %s\n", argv[1]);
            return 1;
        }
    } else {
        inputFile = stdin;
    }

    testScanner(inputFile);

    if (inputFile != stdin) {
        fclose(inputFile);
    }

    return 0;
}