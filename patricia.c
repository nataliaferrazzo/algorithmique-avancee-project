#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

        if (!found) {
            PatriciaNode *newNode = createPatriciaNode(word);
            newNode->isEndOfWord = true;

            current->children = (PatriciaNode **)realloc(current->children, sizeof(PatriciaNode *) * (current->childrenCount + 1));
            current->children[current->childrenCount++] = newNode;
            return;
        }
    }

    current->isEndOfWord = true;
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
    printf("label: %s\n", tree->label);
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

int ProfondeurMoyenne(PatriciaNode *tree) {
    if (tree == NULL) return 0;

    int sommeProfondeurs = 0;
    int nbFeuilles = 0;

    calculerProfondeur(tree, 0, &sommeProfondeurs, &nbFeuilles);

    // Calculer la moyenne
    if (nbFeuilles == 0) return 0; // to avoid to divide by zero
    return sommeProfondeurs / nbFeuilles;
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







