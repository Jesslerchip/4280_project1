// Jessica Seabolt CMP SCI 4280 Project 1 Updated 03/12/2024

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
        printf("Enter input (press Ctrl+D on a new line to stop):\n");
    }

    testScanner(inputFile);

    if (inputFile != stdin) {
        fclose(inputFile);
    }

    return 0;
}