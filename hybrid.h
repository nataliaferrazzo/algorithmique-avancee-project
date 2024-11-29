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
HybridTrieNode* createHybridNode(char character);
HybridTrieNode* insertHybrid(HybridTrieNode *root, const char *word);
bool searchHybrid(HybridTrieNode *root, const char *word);

#endif // HYBRID_H
