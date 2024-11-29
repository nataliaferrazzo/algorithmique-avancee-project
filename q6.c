#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "patricia.h"

// Function to remove the trailing newline character
void removeNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Function to convert a string to lowercase
void toLowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Function to process a word (convert to lowercase)
void processWord(char *word) {
    toLowercase(word);
}

int main() {
    const char *filename = "./Shakespeare/1henryiv.txt";

    // Open the file
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return 1;
    }

    // Create the root of the Patricia Trie
    PatriciaNode *patriciaRoot = createPatriciaNode("");

    char line[256]; // Buffer to hold each line
    while (fgets(line, sizeof(line), file)) {
        removeNewline(line);  // Remove the trailing newline character
        processWord(line);    // Clean the word
        if (strlen(line) > 0) {
            insertPatricia(patriciaRoot, line); // Insert the word into the Patricia Trie
        }
    }

    fclose(file); // Close the file

    printf("Patricia Trie successfully built from %s\n", filename);

    // Test searching for a word
    const char *testWord = "heared";
    printf("Search for '%s': %s\n", testWord, searchPatricia(patriciaRoot, testWord) ? "Found" : "Not Found");

    // Free memory (optional: implement a cleanup function for Patricia Trie nodes)
    return 0;
}
