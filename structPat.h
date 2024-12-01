#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26 // Size of the alphabet (A-Z)

typedef struct pat_tries {
    char * label;
    bool isLeaf;                         // Flag indicating whether this node is the end of a word
    pat_tries* children[ALPHABET_SIZE];      // Array of pointers to cells (each corresponding to a letter A-Z)
} pat_tries;

