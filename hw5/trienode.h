 /* trienode.h contains structure and function declarations for 
   a trie implementation 
   CSE374, HW5, 22Wi 
*/

#ifndef TRIENODE_H
#define TRIENODE_H

#include <stdio.h>

#define MAXLEN 50
#define BRANCHES 9

// trieNode is one node in an 9-tree, where branches correspond to
// # and the T9 alphabet.
typedef struct trieNode {
  struct trieNode *branches[BRANCHES];
  char *word;
} trieNode;



trieNode* makeNode();

void insert(char* word, trieNode* root);

int charToInt(char ch);

trieNode* search(trieNode* trie, char* input);

void free_tree(trieNode *root);


#endif
