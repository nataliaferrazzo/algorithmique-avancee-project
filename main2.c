/* For question 5 :
line to compil the main2.c, to test the bash script :
gcc -Wall -g -o main2 main2.c patricia.h patricia.c
line to execute the bash script:
bash ./script.sh create 0 fiel1.txt file2.txt

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "patricia.h"

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

int main(int argc, char *argv[]) {
    printf("in the main file");
    if (argc < 3) {
        printf("Usage: %s <command> <trie_type> [other arguments]\n", argv[0]);
        return 1;
    }

    const char *command = argv[1];
    const char *trie_type = argv[2];

    if (strcmp(command, "create\0") == 0) {
        
        // Call function to create the trie
        if (argc != 5) {
            printf("Usage: %s create <trie_type> <input_file> <output_file>\n", argv[0]);
            return 1;
        }
        const char *input_file = argv[3];
        const char *output_file = argv[4];
        
        int type = atoi(trie_type);
        if(type == 0){
            const char *phrase = "A quel genial professeur de dactylographie sommes redevables de la superbe phrase ci dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?";
            // Create the root of the Patricia Trie
            PatriciaNode *patriciaRoot = createPatriciaNode("");

            // Build the Patricia Trie from the phrase
            PatriciaNode * pat = buildPatriciaFromPhrase(patriciaRoot, phrase);

            int res = countWords(pat);
            char** list2 = ListeMots(pat);
            for(int i = 0; i < res-1; i++ ){
                printf("%s\n", list2[i]);
            }
            //createTrie(trie_type, input_file, output_file);
        }else if(type == 1){
            //call the create fct with hybrides tries
        }
        
    } else if (strcmp(command, "insert") == 0) {
        // Call function to insert into the trie
        // Similarly handle "insert"
    } else if (strcmp(command, "delete") == 0) {
        // Call function to delete from the trie
        // Similarly handle "delete"
    } else {
        printf("Unknown command: %s\n", command);
        return 1;
    }

    return 0;
}



