#ifndef HYBRID_H
#define HYBRID_H

#include <stdbool.h>

// Structure for a Hybrid-Trie node
typedef struct HybridTrieNode {
    char character;                   // Character stored in the node
    struct HybridTrieNode *left;      // Left child
    struct HybridTrieNode *middle;    // Middle child
    struct HybridTrieNode *right;     // Right child
    bool isEndOfWord;                 // Flag to indicate the end of a word
} HybridTrieNode;

// Function declarations

bool searchHybrid(HybridTrieNode *root, const char *word);
int countWordsHybrid(HybridTrieNode *tree);
char ** ListeMotsHybrid(HybridTrieNode *tree);
int comptageNil(HybridTrieNode *tree);
bool Recherche(HybridTrieNode *tree, char *word);
int hauteurHybrid(HybridTrieNode *tree);
int ProfMoyenne(HybridTrieNode *tree);
int PrefixeH(HybridTrieNode *tree, const char *prefixe);
HybridTrieNode* createHybridTrie(char character);
HybridTrieNode* insertHybridTrie(HybridTrieNode *root, const char *word);
HybridTrieNode* SuppressionH(HybridTrieNode *root, const char *word);



#endif // HYBRID_H
