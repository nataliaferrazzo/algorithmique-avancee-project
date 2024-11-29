#include <stdio.h>
#include <stdlib.h>

void readChapter(const char* inputFile, const char* outputFile) {
    // Open the input file for reading in text mode
    FILE *inFile = fopen(inputFile, "r");
    if (!inFile) {
        fprintf(stderr, "Error: Could not open input file '%s'.\n", inputFile);
        return;
    }

    // Open the output file for writing in text mode
    FILE *outFile = fopen(outputFile, "w");
    if (!outFile) {
        fprintf(stderr, "Error: Could not open or create output file '%s'.\n", outputFile);
        fclose(inFile);
        return;
    }
    
    int ch;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n') {
            fputc(' ', outFile); // Replace newline with a space
        } else {
            fputc(ch, outFile); // Write the character as is
        }
    }

    fclose(inFile);
    fclose(outFile);
}

int main() {
    // Replace "input.txt" and "output.txt" with your file paths
    readChapter("./Shakespeare/1henryiv.txt", "./res.txt");

    printf("Processing complete. Check the output file.\n");
    return 0;
}