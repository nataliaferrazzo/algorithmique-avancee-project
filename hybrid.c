#include <stdio.h>
#include "patricia.h"
#include "hybrid.h"

int main() {
    // Patricia-Trie Test
    PatriciaNode *patriciaRoot = createPatriciaNode("");
    insertPatricia(patriciaRoot, "apple");
    insertPatricia(patriciaRoot, "app");
    printf("Patricia-Trie Search 'apple': %s\n", searchPatricia(patriciaRoot, "apple") ? "Found" : "Not Found");

    // Hybrid-Trie Test
    HybridTrieNode *hybridRoot = NULL;
    hybridRoot = insertHybrid(hybridRoot, "apple");
    hybridRoot = insertHybrid(hybridRoot, "app");
    printf("Hybrid-Trie Search 'apple': %s\n", searchHybrid(hybridRoot, "apple") ? "Found" : "Not Found");

    return 0;
}
