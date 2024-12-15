#ifndef PATRICIA_H
#define PATRICIA_H

#include <stdbool.h>

// Structure for a Patricia-Trie node
typedef struct PatriciaNode {
    char *label;                     // Key fragment stored in this node
    struct PatriciaNode **children;  // Array of pointers to child nodes
    bool isEndOfWord;                // Flag to indicate the end of a word
    int childrenCount;               // Number of children
} PatriciaNode;

// Function declarations
PatriciaNode* createPatriciaNode(const char *label);
void insertPatricia(PatriciaNode *root, const char *word);
bool searchPatricia(PatriciaNode *root, const char *word);
int countWords(PatriciaNode *root);
int hauteur(PatriciaNode *tree);
char ** ListeMots(PatriciaNode *tree);
int ComptageNil(PatriciaNode *tree);
float ProfondeurMoyenne(PatriciaNode *tree);
int Prefixe(PatriciaNode *tree, char* word);
PatriciaNode *Suppression(PatriciaNode *tree, const char *word);
PatriciaNode *MergePatricia(PatriciaNode *tree1, PatriciaNode *tree2);
PatriciaNode *buildPatriciaFromFile(const char *filename);
PatriciaNode *rechercherPrefixe(PatriciaNode *node, const char *mot);

#endif // PATRICIA_H
