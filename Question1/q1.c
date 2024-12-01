#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readChapter(const char* inputFile, const char* outputFile) {
    FILE *inFile = fopen(inputFile, "rb");
    if (!inFile) {
        fprintf(stderr, "Error: Could not open input file '%s'.\n", inputFile);
        return;
    }

    // Open the output file in binary mode for writing
    FILE *outFile = fopen(outputFile, "wb");
    if (!outFile) {
        fprintf(stderr, "Error: Could not open or create output file '%s'.\n", outputFile);
        fclose(inFile); // Close the input file before exiting
        return;
    }
    
    int ch;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n') {
            fputc(' ', outFile); // Replace null character with a space but still "print" the '\n' why?
        } else {
            fputc(ch, outFile); // Write the character as is
        }
    }

    fclose(inFile);
    fclose(outFile);
}

int main() {
    // Replace "input.txt" and "output.txt" with your file paths
    readChapter("./test.txt", "./res.txt");

    printf("Processing complete. Check the output file.\n");
    return 0;
}
