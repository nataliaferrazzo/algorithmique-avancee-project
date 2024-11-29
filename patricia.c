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