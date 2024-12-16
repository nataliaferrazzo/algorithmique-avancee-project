/* For question 5 :
line to compil the main2.c, to test the bash script :
gcc -Wall -g -o main2 main2.c patricia.h patricia.c -I/usr/local/include -L/usr/local/lib -lcjson
line to execute the bash script:
bash ./script.sh inserer 0 "./nomduFile"

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cJSON.h"//cJSON/
#include "patricia.h"  // Include the header for declarations
#include "hybrid.h"

void serializePatriciaNode(FILE *file, PatriciaNode *node, int depth) {
    fprintf(file, "{\n");

    // Indent and write the label
    for (int i = 0; i <= depth; i++) {
        fprintf(file, "\t");
    }
    fprintf(file, "\"label\": \"%s\",\n", node->label);

    // Indent and write the is_end_of_word flag
    for (int i = 0; i <= depth; i++) {
        fprintf(file, "\t");
    }
    fprintf(file, "\"is_end_of_word\": %s,\n", node->isEndOfWord ? "true" : "false");

    // Indent and start the children object
    for (int i = 0; i <= depth; i++) {
        fprintf(file, "\t");
    }
    fprintf(file, "\"children\": {\n");

    // Recursively serialize each child
    for (int i = 0; i < node->childrenCount; i++) {
        if (i > 0) {
            fprintf(file, ",\n");
        }
        for (int j = 0; j <= depth + 1; j++) {
            fprintf(file, "\t");
        }
        fprintf(file, "\"%c\": ", node->children[i]->label[0]);
        serializePatriciaNode(file, node->children[i], depth + 2);
    }

    if (node->childrenCount > 0) {
        fprintf(file, "\n");
    }
    for (int i = 0; i <= depth; i++) {
        fprintf(file, "\t");
    }
    fprintf(file, "}\n");

    // Close the JSON object
    for (int i = 0; i < depth; i++) {
        fprintf(file, "\t");
    }
    fprintf(file, "}");
}













int main(int argc, char *argv[]) {
    
    if (argc != 4 && argc != 5) {
        printf("Usage: %s <command> <trie_type> <input_file> [other arguments]\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[3], "rb");
    if (!inputFile) {
        fprintf(stderr, "Error: Could not open input file '%s'.\n", inputFile);
        return 1;
    }

    const char *command = argv[1];
    const char *trie_type = argv[2];
    int type = atoi(trie_type);

    if (strcmp(command, "inserer\0") == 0) {

        // Call function to create the trie
        if (argc != 4) {//5
            printf("Usage: %s inserer <trie_type> <input_file> <output_file>\n", argv[0]);
            fclose(inputFile);
            return 1;
        }

        FILE *outputFile = fopen("./pat.json", "wb");
        if (!outputFile) {
            fprintf(stderr, "Error: Could not open or create output file '%s'.\n", outputFile);
            fclose(inputFile); // Close the input file before exiting
            return 1;
        }

        char buffer[1024];
        int ch, index = 0;

        if(type == 0){

            PatriciaNode *pat = createPatriciaNode("");
            while ((ch = fgetc(inputFile)) != EOF) {
                if (ch == '\n') {
                    if (index > 0) {
                        buffer[index] = '\0'; // Null-terminate the word
                        insertPatricia(pat, buffer);
                        index = 0; // Reset buffer for the next word
                    }
                } else {
                    if (index < 1023) {
                        buffer[index++] = ch;
                    }
                }
            }
            if (index > 0) {
                buffer[index] = '\0'; // Null-terminate the last word
                insertPatricia(pat, buffer); // Insert the last word into the trie
            }

            //FILE *outputFile = fopen("pat.json", "wb");
            serializePatriciaNode(outputFile, pat, 0);

            fclose(outputFile);
        } else if(type == 1){
            printf("should call insert with hybrid-trie\n");
            
        }
        
        
    } else if (strcmp(command, "fusion") == 0) {

        // Call function to create the trie
        if (argc != 5) {
            printf("Usage: %s inserer <trie_type> <input_file> <output_file>\n", argv[0]);
            fclose(inputFile);
            return 1;
        }

        if(type == 0){

            PatriciaNode *pat1 = buildPatriciaFromFile(argv[3]);
            PatriciaNode *pat2 = buildPatriciaFromFile(argv[4]);
            PatriciaNode *pat3 = MergePatricia(pat1,pat2);

            
            FILE *outputFile = fopen("./pat.json", "wb");
            if (!outputFile) {
                fprintf(stderr, "Error: Could not open or create output file '%s'.\n", outputFile);
                fclose(inputFile); // Close the input file before exiting
                return 1;
            }
            serializePatriciaNode(outputFile, pat3, 0);

            fclose(outputFile);

        } else if(type == 1){

        }

    } else if (strcmp(command, "suppression") == 0) {
        if (argc != 4) {
            printf("Usage: %s suppression <trie_type> <input_file> <output_file>\n", argv[0]);
            fclose(inputFile);
            return 1;
        }
        

        char buffer[1024];
        int ch, index = 0;

        if(type == 0){

            
            PatriciaNode *pat = buildPatriciaFromFile("pat.json");

            

            while ((ch = fgetc(inputFile)) != EOF) {
                if (ch == '\n') {
                    if (index > 0) {
                        buffer[index] = '\0'; // Null-terminate the word
                        Suppression(pat, buffer);
                        index = 0; // Reset buffer for the next word
                    }
                } else {
                    if (index < 1023) {
                        buffer[index++] = ch;
                    }
                }
            }
            if (index > 0) {
                buffer[index] = '\0'; // Null-terminate the last word
                Suppression(pat, buffer); // Insert the last word into the trie
            }

            FILE *outputFile = fopen("pat.json", "wb");
            if (!outputFile) {
                fprintf(stderr, "Error: Could not open or create output file '%s'.\n", outputFile);
                fclose(inputFile); // Close the input file before exiting
                return 1;
            }
            
            serializePatriciaNode(outputFile, pat, 0);

            fclose(outputFile);

        }else if(type == 1){

        }
        // Call function to delete from the trie
        // Similarly handle "delete"
    } else if (strcmp(command, "listeMots") == 0) {
        if (argc != 4) {
            printf("Usage: %s listeMots <trie_type> <input_file>\n", argv[0]);
            fclose(inputFile);
            return 1;
        }
        

        if(type == 0){

            
            PatriciaNode *pat = buildPatriciaFromFile(argv[3]);
            int res = countWords(pat);
            char ** liste = ListeMots(pat);

            FILE *outputFile = fopen("mot.txt", "wb");
            if (!outputFile) {
                fprintf(stderr, "Error: Could not open or create output file '%s'.\n", outputFile);
                fclose(inputFile); // Close the input file before exiting
                return 1;
            }
            
            for (int i = 0; i < res; i++) { //liste[i] != NULL
                fprintf(outputFile, "%s\n", liste[i]); // Write each word followed by a newline
            }
                        
            fclose(outputFile);

        } else if(type == 1){

        }

    } else if (strcmp(command, "profondeurMoyenne") == 0) {
        if (argc != 4) {
            printf("Usage: %s profondeurMoyenne <trie_type> <input_file> \n", argv[0]);
            fclose(inputFile);
            return 1;
        }
        

        if(type == 0){

            PatriciaNode *pat = buildPatriciaFromFile(argv[3]);
            float res = ProfondeurMoyenne(pat);
            

            FILE *outputFile = fopen("profondeur.txt", "wb");
            if (!outputFile) {
                fprintf(stderr, "Error: Could not open or create output file '%s'.\n", outputFile);
                fclose(inputFile); // Close the input file before exiting
                return 1;
            }
            
            fprintf(outputFile, "%f\n", res); // Write each word followed by a newline
                        
            fclose(outputFile);

        } else if(type == 1){

        }

    } else if (strcmp(command, "prefixe") == 0) {
        if (argc != 5) {
            printf("Usage: %s profondeurMoyenne <trie_type> <input_file> <prefixe>\n", argv[0]);
            fclose(inputFile);
            return 1;
        }
        if(type == 0){
            PatriciaNode *pat = buildPatriciaFromFile(argv[3]);//maybe change pat.json to argv[3]
            char **res = ListeMots(rechercherPrefixe(pat, argv[4]));
            

            FILE *outputFile = fopen("prefixe.txt", "wb");
            if (!outputFile) {
                fprintf(stderr, "Error: Could not open or create output file '%s'.\n", outputFile);
                fclose(inputFile); // Close the input file before exiting
                return 1;
            }
            if (res == NULL) return 1;
            for (int i = 0; res[i] != NULL; i++) {
                fprintf(outputFile, "%s\n", res[i]);
            }
                        
            fclose(outputFile);

        } else if(type == 1){

        }
    } else {
        printf("Unknown command: %s\n", command);
        return 1;
    }

    fclose(inputFile);
    return 0;
}



