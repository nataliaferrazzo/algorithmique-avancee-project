#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cJSON/cJSON.h"
#include "patricia.h"  // Include the header for declarations

// Function to convert a Patricia Trie node to JSON
cJSON* patriciaToJson(PatriciaNode *node) {
    if (node == NULL) {
        return NULL;
    }

    // Create a JSON object for the current node
    cJSON *jsonNode = cJSON_CreateObject();

    // Add the label of the current node
    cJSON_AddStringToObject(jsonNode, "label", node->label);

    // Add the is_end_of_word flag to the JSON object (true/false)
    cJSON_AddStringToObject(jsonNode, "is_end_of_word", node->isEndOfWord ? "yes" : "no");

    // If the node has children, recursively add them as a JSON object
    if (node->childrenCount > 0) {
        cJSON *childrenObject = cJSON_CreateObject();

        for (int i = 0; i < node->childrenCount; i++) {
            // Recursive call to process each child node
            cJSON *childJson = patriciaToJson(node->children[i]);
            if (childJson != NULL) {
                // Add each child as a key-value pair in the children object
                cJSON_AddItemToObject(childrenObject, node->children[i]->label, childJson);
            }
        }

        // Add the children object to the current node
        cJSON_AddItemToObject(jsonNode, "children", childrenObject);
    }

    return jsonNode;
}

// Function to save the Patricia Trie to a JSON file
void savePatriciaToJsonFile(PatriciaNode *root, const char *filename) {
    // Convert the Patricia Trie to JSON
    cJSON *jsonRoot = patriciaToJson(root);
    
    // Serialize the JSON object to a string
    char *jsonString = cJSON_Print(jsonRoot);
    
    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        // Write the JSON string to the file
        fprintf(file, "%s", jsonString);
        fclose(file);
        printf("Successfully saved the Patricia Trie to %s\n", filename);
    } else {
        printf("Error: Unable to open file for writing\n");
    }

    // Clean up
    free(jsonString);
    cJSON_Delete(jsonRoot);
}

// Function to insert words and punctuation into the Patricia Trie
PatriciaNode* buildPatriciaFromPhrase(PatriciaNode *root, const char *phrase) {
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
    return root;
}

int main() {
    // Example phrase
    const char *phrase = "A quel genial professeur de dactylographie sommes redevables de la superbe phrase ci dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?";
    
    // Create the root of the Patricia Trie
    PatriciaNode *patriciaRoot = createPatriciaNode("");

    // Build the Patricia Trie from the phrase
    PatriciaNode *pat = buildPatriciaFromPhrase(patriciaRoot, phrase);
    printf("Patricia Trie successfully built from the given phrase.\n");

    int res = countWords(pat);
    printf("Number of words in patricia tree of the example: %d\nShould be 37.\n", res);
    printf("Tree height: %d\n", hauteur(pat)); // This might not work as expected (see your comment).
    
    // Save the Patricia Trie to a JSON file
    savePatriciaToJsonFile(pat, "patricia_trie.json");
    return 0;
}
