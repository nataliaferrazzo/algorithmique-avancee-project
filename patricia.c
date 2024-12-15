#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cJSON.h" // Ensure you have cJSON installed and linked properly
#include "patricia.h"

// Create a new Patricia-Trie node
PatriciaNode* createPatriciaNode(const char *label) {
    PatriciaNode *node = (PatriciaNode *)malloc(sizeof(PatriciaNode));
    node->label = strdup(label);     // Duplicate the label string
    node->children = NULL;           // No children initially
    node->isEndOfWord = false;       // Not an end of a word by default
    node->childrenCount = 0;
    return node;
}

// Insert a word into the Patricia-Trie
void insertPatricia(PatriciaNode *root, const char *word) {
    PatriciaNode *current = root;

    if(current == NULL){
        PatriciaNode *newWordNode = createPatriciaNode(word);
        root->children = (PatriciaNode **)malloc(sizeof(PatriciaNode *) * 2);
        root->children[0] = newWordNode;
        root->childrenCount++;
        return;
    }
    while (*word) {
        bool found = false;

        for (int i = 0; i < current->childrenCount; i++) {
            PatriciaNode *child = current->children[i];
            int matchLen = 0;

            while (word[matchLen] && child->label[matchLen] && word[matchLen] == child->label[matchLen]) {
                matchLen++;
            }

            if (matchLen > 0) {
                if (matchLen == strlen(child->label)) {
                    word += matchLen;
                    current = child;
                    found = true;
                    break;
                } else {
                    PatriciaNode *newChild = createPatriciaNode(child->label + matchLen);
                    newChild->children = child->children;
                    newChild->childrenCount = child->childrenCount;
                    newChild->isEndOfWord = child->isEndOfWord;

                    child->label[matchLen] = '\0';
                    child->children = (PatriciaNode **)malloc(sizeof(PatriciaNode *) * 2);
                    child->children[0] = newChild;
                    child->childrenCount = 1;
                    
                    if(matchLen == strlen(word)){
                        child->isEndOfWord = true;
                        return;
                    }
                    else{
                        child->isEndOfWord = false;
                        PatriciaNode *newWordNode = createPatriciaNode(word + matchLen);
                        newWordNode->isEndOfWord = true;

                        child->children = (PatriciaNode **)realloc(child->children, sizeof(PatriciaNode *) * 2);
                        child->children[1] = newWordNode;
                        child->childrenCount++;
                        return; 
                    }
                    
                    
                }
            }
        }

        if (!found) {
            PatriciaNode *newNode = createPatriciaNode(word);
            newNode->isEndOfWord = true;

            current->children = (PatriciaNode **)realloc(current->children, sizeof(PatriciaNode *) * (current->childrenCount + 1));
            current->children[current->childrenCount++] = newNode;
            return;
        }
    }

    //current->isEndOfWord = false;
}

// Search for a word in the Patricia-Trie
bool searchPatricia(PatriciaNode *root, const char *word) {
    PatriciaNode *current = root;

    while (*word) {
        bool found = false;

        for (int i = 0; i < current->childrenCount; i++) {
            PatriciaNode *child = current->children[i];            
            int matchLen = 0;

            while (word[matchLen] && child->label[matchLen] && word[matchLen] == child->label[matchLen]) {
                matchLen++;
            }

            if (matchLen == strlen(child->label)) {
                word += matchLen;
                current = child;
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return current->isEndOfWord;
        
}

int countWords(PatriciaNode *tree){
    if (tree == NULL) {
        return 0;
    }
    int res = 0;
    if (tree->isEndOfWord){
            res++;
    }
    if (tree->children != NULL) {
        for (int i = 0; i < tree->childrenCount; i++) { // Assuming children is NULL-terminated
            res += countWords(tree->children[i]);
        }
    }
    return res; 
}

void sortChildren(PatriciaNode **children, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(children[i]->label, children[j]->label) > 0) {
                PatriciaNode *temp = children[i];
                children[i] = children[j];
                children[j] = temp;
            }
        }
    }
}

void collectWords(PatriciaNode *tree, char *currentWord, char ***result, int *count) {
    if (tree == NULL) return;

    int len1 = strlen(currentWord);
    int len2 = strlen(tree->label);
    char *newWord = malloc(len1 + len2 + 1); // +1 for '\0'
    strcpy(newWord, currentWord);
    strcat(newWord, tree->label);
    

    // if it's the end of a word add to the result list
    if (tree->isEndOfWord) {
        *result = realloc(*result, (*count + 1) * sizeof(char *));
        (*result)[*count] = strdup(newWord);
        (*count)++;
    }

    sortChildren(tree->children, tree->childrenCount);

    for (int i = 0; i < tree->childrenCount; i++) {
        collectWords(tree->children[i], newWord, result, count);
    }
    free(newWord);
}

char ** ListeMots(PatriciaNode *tree){
    if (tree == NULL) {
        return NULL;
    }
    
    char **list = NULL;
    int count = 0;
    
    collectWords(tree, "", &list, &count);

    return list;
}

//Count the number of pointer to null
int ComptageNil(PatriciaNode *tree){

    if (tree == NULL) {
        return 1;
    }

    int res = 0;
    if (tree->children == NULL){
        return 1;
    }else{
        for (int i = 0; i < tree->childrenCount; i++) { 
            res += ComptageNil(tree->children[i]);
        }
    }
    
    
    return res;
}

int hauteur(PatriciaNode *tree){
    if (tree == NULL) {
        return -1;
    }
    int res = -1; // why is it better to start from -1?
    
    for (int i = 0; i < tree->childrenCount; i++) { 
        int tmp = hauteur(tree->children[i]);
        if(tmp > res){
            res = tmp;
        }        
    }
       
    return res + 1;
}

void calculerProfondeur(PatriciaNode *tree, int profondeurActuelle, int *sommeProfondeurs, int *nbFeuilles) {
    if (tree == NULL) return;

    if (tree->childrenCount == 0) {
        (*sommeProfondeurs) += profondeurActuelle;
        (*nbFeuilles)++;
        return;
    }

    for (int i = 0; i < tree->childrenCount; i++) {
        calculerProfondeur(tree->children[i], profondeurActuelle + 1, sommeProfondeurs, nbFeuilles);
    }
}

float ProfondeurMoyenne(PatriciaNode *tree) {
    if (tree == NULL) return 0;

    int sommeProfondeurs = 0;
    int nbFeuilles = 0;

    calculerProfondeur(tree, 0, &sommeProfondeurs, &nbFeuilles);

    // Calculer la moyenne
    if (nbFeuilles == 0) return 0; // to avoid to divide by zero
    return (float) sommeProfondeurs / nbFeuilles;
}


PatriciaNode *rechercherPrefixe(PatriciaNode *node, const char *mot) {
    if (node == NULL || mot[0] == '\0') return node;

    
    for (int i = 0; i < node->childrenCount; i++) {
        PatriciaNode *child = node->children[i];
        if (strncmp(child->label, mot, strlen(child->label)) == 0) {
            
            return rechercherPrefixe(child, mot + strlen(child->label));
        }
    }
    return NULL;
}

int compterMots(PatriciaNode *node) {
    if (node == NULL) return 0;

    int count = 0;
    if (node->isEndOfWord) count++;

    for (int i = 0; i < node->childrenCount; i++) {
        count += compterMots(node->children[i]);
    }

    return count;
}
int Prefixe(PatriciaNode *tree, char* word){
    PatriciaNode *node = rechercherPrefixe(tree, word);

    if (tree == NULL) return 0;

    return compterMots(node);
}



void libererNoeud(PatriciaNode *node) {
    if (node == NULL) return;

    for (int i = 0; i < node->childrenCount; i++) {
        libererNoeud(node->children[i]);
    }

    // Free the associated structures
    free(node->children);
    free(node->label);
    free(node);
}

PatriciaNode *supprimerMot(PatriciaNode *node, const char *word) {
    if (node == NULL || word[0] == '\0') return node;

    for (int i = 0; i < node->childrenCount; i++) {
        PatriciaNode *current = node->children[i];
        // Check if the label matches the start of the word
        if (strncmp(current->label, word, strlen(current->label)) == 0) {
            // If the word continues beyond this node
            if (strlen(word) > strlen(current->label)) {
                // Recurse into the subtree
                current = supprimerMot(current, word + strlen(current->label));

                // If the current node is now empty, remove it
                if (current->childrenCount == 0 && !current->isEndOfWord){//node->children[i]
                    
                    // Free the current node
                    libererNoeud(current);

                    // Shift the remaining children
                    for (int j = i; j < node->childrenCount - 1; j++) {
                        node->children[j] = node->children[j + 1];
                    }

                    node->childrenCount--;
                    node->children = realloc(node->children, node->childrenCount * sizeof(PatriciaNode *));
                }

                return node;
            } else {
                // This is the node corresponding to the word
                if (strlen(word) == strlen(current->label)) {
                    if (current->isEndOfWord) {
                        current->isEndOfWord = false;

                        // If the node has no children, remove it
                        if (current->childrenCount == 0) {
                            libererNoeud(current);

                            // reindex the other children
                            for (int j = i; j < node->childrenCount - 1; j++) {
                                node->children[j] = node->children[j + 1];
                            }
                            node->childrenCount--;
                            node->children = realloc(node->children, node->childrenCount * sizeof(PatriciaNode *));
                        }
                    }

                    return node; // Return the current node
                }
            }
        }
    }

    return node;
}

// Main function for word deletion
PatriciaNode *Suppression(PatriciaNode *tree, const char *word) {
    if (tree == NULL || word == NULL) return tree;

    return supprimerMot(tree, word);
}

PatriciaNode *MergePatricia(PatriciaNode *tree1, PatriciaNode *tree2){
    char **list_tmp = ListeMots(tree2); //maybe check how to handle the memory and free the list at the end
    int nb = countWords(tree2);
    for(int i = 0; i < nb-1; i++ ){
        insertPatricia(tree1, list_tmp[i]);
    }
    return tree1;
}



// Recursive function to build the Patricia trie
PatriciaNode *buildPatriciaFromJSON(cJSON *json) {
    // Create a PatriciaNode from the current JSON object
    cJSON *label = cJSON_GetObjectItem(json, "label");
    cJSON *isEndOfWord = cJSON_GetObjectItem(json, "is_end_of_word");
    cJSON *children = cJSON_GetObjectItem(json, "children");

    PatriciaNode *node = createPatriciaNode(cJSON_GetStringValue(label));
    node->isEndOfWord = cJSON_IsTrue(isEndOfWord);

    if (cJSON_IsObject(children)) {
        int childCount = 0;
        cJSON *child;

        // Count the number of children
        cJSON_ArrayForEach(child, children) {
            childCount++;
        }

        // Allocate memory for the children
        node->children = (PatriciaNode **)malloc(childCount * sizeof(PatriciaNode *));
        node->childrenCount = childCount;

        int index = 0;
        cJSON_ArrayForEach(child, children) {
            node->children[index++] = buildPatriciaFromJSON(child);
        }
    }

    return node;
}

// Wrapper function to read JSON from a file and build the trie
PatriciaNode *buildPatriciaFromFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'.\n", filename);
        return NULL;
    }

    // Read the entire file into memory
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(fileSize + 1);
    fread(buffer, 1, fileSize, file);
    fclose(file);
    buffer[fileSize] = '\0';

    // Parse the JSON data
    cJSON *json = cJSON_Parse(buffer);
    free(buffer);

    if (!json) {
        fprintf(stderr, "Error: Failed to parse JSON.\n");
        return NULL;
    }

    // Build the Patricia trie
    PatriciaNode *root = buildPatriciaFromJSON(json);

    // Clean up JSON object
    //cJSON_Delete(json);

    return root;
}
