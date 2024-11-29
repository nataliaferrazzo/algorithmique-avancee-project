#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "patricia.h"

// Function to insert words and punctuation into the Patricia Trie
void buildPatriciaFromPhrase(PatriciaNode *root, const char *phrase) {
    char buffer[256];
    int pos = 0;

    for (int i = 0; phrase[i]; i++) {
        if (isalnum(phrase[i])) {
            // Build alphanumeric words
            buffer[pos++] = phrase[i];
        } else {
            // Handle the end of a word
            if (pos > 0) {
                buffer[pos] = '\0';        // Null-terminate the word
                insertPatricia(root, buffer); // Insert the word into the Patricia Trie
                pos = 0;                  // Reset the buffer
            }
            // Handle punctuation as a separate token
            if (!isspace(phrase[i])) {
                char punctuation[2] = {phrase[i], '\0'}; // Single-character punctuation
                insertPatricia(root, punctuation);
            }
        }
    }

    // Handle the last word if any
    if (pos > 0) {
        buffer[pos] = '\0';
        insertPatricia(root, buffer);
    }
}

int main() {
    // Example phrase
    const char *phrase = "A quel genial professeur de dactylographie sommes redevables de la superbe phrase ci dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?";
    
    // Create the root of the Patricia Trie
    PatriciaNode *patriciaRoot = createPatriciaNode("");

    // Build the Patricia Trie from the phrase
    buildPatriciaFromPhrase(patriciaRoot, phrase);

    printf("Patricia Trie successfully built from the given phrase.\n");

    // Test searching for words and punctuation
    const char *testTokens[] = {"dactylographie", "A", "phrase", ",", "ci", "dessous,", "?", "inexistent"};
    for (int i = 0; i < 8; i++) {
        printf("Search for '%s': %s\n", testTokens[i], searchPatricia(patriciaRoot, testTokens[i]) ? "Found" : "Not Found");
    }

    return 0;
}