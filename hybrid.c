#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hybrid.h"

HybridTrieNode* createHybridTrie(char character) {
    HybridTrieNode *node = (HybridTrieNode *)malloc(sizeof(HybridTrieNode));
    node->character = character;    // Initialize with the given character
    node->left = NULL;              
    node->middle = NULL;            
    node->right = NULL;             
    node->isEndOfWord = NULL;      
    return node;
}

HybridTrieNode* insertHybridTrie(HybridTrieNode *root, const char *word) {
    if (root == NULL) {
        root = createHybridTrie(*word);
    }

    // Traverse the tree based on character comparison
    if (*word < root->character) {
        // Insert in the left subtree (word's character is smaller)
        root->left = insertHybridTrie(root->left, word);
    } else if (*word > root->character) {
        // Insert in the right subtree (word's character is larger)
        root->right = insertHybridTrie(root->right, word);
    } else {
        // Character matches the current node
        if (*(word + 1) == '\0') {
            // We are at the last character of the word, mark as end of word
            root->isEndOfWord = true;
        } else {
            // Move to the middle subtree for the next character in the word
            root->middle = insertHybridTrie(root->middle, word + 1);
        }
    }

    return root;
}

int countWordsHybrid(HybridTrieNode *tree) {
    if (tree == NULL) {
        return 0;
    }

    int res = 0;
    
    if (tree->isEndOfWord) {
        res++;
    }
    // Recursively count words in the left, middle, and right subtrees
    res += countWordsHybrid(tree->left);
    res += countWordsHybrid(tree->middle);
    res += countWordsHybrid(tree->right);

    return res;
}


void collectWordsH(HybridTrieNode *tree, char *currentWord, char ***result, int *count) {
    if (tree == NULL) return;

    int len1 = strlen(currentWord);
    int len2 = 1; // Current node's character (not a string)
    char *newWord = malloc(len1 + len2 + 1); // +1 for '\0'
    strcpy(newWord, currentWord);
    newWord[len1] = tree->character;  // Add the character of the current node
    newWord[len1 + 1] = '\0';         // Null-terminate the string

    // if it's the end of a word, add to the result list
    if (tree->isEndOfWord) {
        *result = realloc(*result, (*count + 1) * sizeof(char *));
        (*result)[*count] = strdup(newWord);
        (*count)++;
    }

    // Traverse the children: left, middle, right
    collectWordsH(tree->left, currentWord, result, count);      // Traverse left child
    collectWordsH(tree->middle, newWord, result, count);    // Traverse middle child
    collectWordsH(tree->right, currentWord, result, count);     // Traverse right child
    
    free(newWord);
}

char ** ListeMotsHybrid(HybridTrieNode *tree) {
    if (tree == NULL) {
        return NULL;
    }

    char **list = NULL;
    int count = 0;

    collectWordsH(tree, "", &list, &count);

    return list;
}

bool Recherche(HybridTrieNode *tree, char *word){
    if(tree == NULL) return false;
    if(strlen(word) == 1){
        return tree->isEndOfWord;
    }
    if(*word > tree->character){
        return Recherche(tree->right, word);

    }else if(*word < tree->character){
        return Recherche(tree->left, word);
    }else{
        return Recherche(tree->middle, word +1);
    }
    
}

int comptageNil(HybridTrieNode *tree){
    if (tree == NULL) return 1;
    int res = 0;
    return res + comptageNil(tree->left) + comptageNil(tree->middle) + comptageNil(tree->right);
}

int hauteurHybrid(HybridTrieNode *tree) {
    if (tree == NULL) {
        return -1; 
    }

    // Calculer la hauteur de chaque sous-arbre (gauche, milieu, droite)
    int leftHeight = hauteurHybrid(tree->left);
    int middleHeight = hauteurHybrid(tree->middle);
    int rightHeight = hauteurHybrid(tree->right);

    // La hauteur de l'arbre est la hauteur maximale parmi les trois sous-arbres, plus 1
    int maxHeight = leftHeight > middleHeight ? leftHeight : middleHeight;
    maxHeight = rightHeight > maxHeight ? rightHeight : maxHeight;

    return maxHeight + 1;
}

int calculerProfondeurMoyenne(HybridTrieNode *tree, int currentDepth, int *sumDepth, int *leafCount) {
    if (tree == NULL) {
        return 0;
    }

    // Vérifier si c'est une feuille (si aucune des branches gauche, droite, ou middle n'existe)
    if (tree->left == NULL && tree->middle == NULL && tree->right == NULL) {
        *sumDepth += currentDepth;  // Ajouter la profondeur de la feuille à la somme
        (*leafCount)++;             // Incrémenter le nombre de feuilles
    }

    calculerProfondeurMoyenne(tree->left, currentDepth + 1, sumDepth, leafCount);    
    calculerProfondeurMoyenne(tree->middle, currentDepth + 1, sumDepth, leafCount);  
    calculerProfondeurMoyenne(tree->right, currentDepth + 1, sumDepth, leafCount);   

    return 0;
}

int ProfMoyenne(HybridTrieNode *tree) {
    int sumDepth = 0;
    int leafCount = 0;

    // Démarrer le calcul à partir de la racine avec une profondeur initiale de 0
    calculerProfondeurMoyenne(tree, 0, &sumDepth, &leafCount);

    // Si l'arbre ne contient pas de feuilles, retourner 0 (par sécurité)
    if (leafCount == 0) {
        return 0;
    }

    // Calculer la profondeur moyenne des feuilles
    return sumDepth / leafCount;
}


int PrefixeH(HybridTrieNode *tree, const char *prefixe) {
    // Traverse the tree until we find the node where the prefix ends
    int index = 0;

    while (tree != NULL && prefixe[index +1] != '\0') {
        if (prefixe[index] < tree->character) {
            tree = tree->left;  // Move to the left child if the current char is smaller
        } else if (prefixe[index] > tree->character) {
            tree = tree->right;  // Move to the right child if the current char is larger
        } else {
            tree = tree->middle;  // Move to the middle child if the current char matches
            index++;  // Move to the next character in the prefix
        }
    }

    // If we reached the end of the prefix and found the node, count words starting from this node
    if (prefixe[index + 1] == '\0') {
        while (prefixe[index] != tree->character){
            if (prefixe[index] < tree->character) {
                tree = tree->left;  // Move to the left child if the current char is smaller
            } else if (prefixe[index] > tree->character) {
                tree = tree->right;  // Move to the right child if the current char is larger
            }
        }

        printf("tree label: %c\n", tree->character);
        if( tree->isEndOfWord == true){
            return 1 + countWordsHybrid(tree->middle);
        }
        return countWordsHybrid(tree->middle);  // Count all words starting from the current node
    }

    // If we didn't find the prefix, return 0 (no words have this prefix)
    return 0;
}

HybridTrieNode* suppressionHelper(HybridTrieNode *root, const char *word, int index) {
    if (root == NULL) {
        return NULL;  // The word is not found, so nothing to delete
    }

    // Traverse the trie based on character comparisons
    if (word[index] < root->character) {
        root->left = suppressionHelper(root->left, word, index);  // Move to the left subtree
    } else if (word[index] > root->character) {
        root->right = suppressionHelper(root->right, word, index);  // Move to the right subtree
    } else {
        // Move to the middle subtree when characters match
        if (word[index + 1] == '\0') {
            // We're at the end of the word, mark it as not end-of-word
            root->isEndOfWord = false;
        } else {
            root->middle = suppressionHelper(root->middle, word, index + 1);
        }
    }

    // After deleting the word, check if the current node can be deleted
    // A node can be deleted if it's not the end of a word and has no children
    if (root->isEndOfWord == false && root->left == NULL && root->middle == NULL && root->right == NULL) {
        free(root);  // Delete this node as it is no longer needed
        return NULL;
    }

    return root;  // Return the node if it is still needed
}

HybridTrieNode* SuppressionH(HybridTrieNode *root, const char *word) {
    return suppressionHelper(root, word, 0);  // Start deletion from the root and index 0
}

