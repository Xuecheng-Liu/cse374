#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

#define BRANCHES 9

trieNode* makeNode(){
   trieNode* node = (trieNode*) malloc(sizeof(trieNode));

   // check whether there is enough space on heap
   if (node == NULL){
      fprintf(stderr,"run out of space while allocating memory\n");
      EXIT_FAILURE;
   }

   // set word and all nodes to be null
   node ->word = NULL;
   for(int i = 0; i < BRANCHES; i++){
      node -> branches[i] = NULL;
   }

   return node;
}

void insert(char* word, trieNode* root){
   trieNode* current = root;
   int length = strlen(word) - 1;
   for(int i = 0; i < length; i++){
      int index = charToInt(word[i]) - 2;
      if (current ->branches[index] == NULL){
         current ->branches[index] = makeNode();
      }
      current = current -> branches[index];
   }
   // now process the word
   if (current -> word == NULL){
      // the word is null, we simply change the value of word
      current->word = (char*) malloc(strlen(word)*sizeof(char));
      if (current->word == NULL){
         fprintf(stderr,"run out of space while allocating memory\n");
         EXIT_FAILURE;
      }else{
         strncpy(current->word,word,strlen(word));
      }
   }else{
      // handling onyms
      while(current->word != NULL){
         if(current->branches[BRANCHES-1]==NULL){
            current->branches[BRANCHES-1] = makeNode();
         }
         current = current->branches[BRANCHES-1];
      }
      current->word = (char*) malloc(strlen(word)*sizeof(char));
      if (current->word == NULL){
         fprintf(stderr,"run out of space while allocating memory\n");
         EXIT_FAILURE;
      }else{
         strncpy(current->word,word,strlen(word));
      }
   }
}

int charToInt(char ch){
   int res = 0;
   if (ch == 'a'|| ch == 'b' || ch == 'c'){
      res = 2;
   }else if (ch == 'd'|| ch == 'e' || ch == 'f'){
      res = 3;
   }else if (ch == 'g'|| ch == 'h' || ch == 'i'){
      res = 4;
   }else if (ch == 'j'|| ch == 'k' || ch == 'l'){
      res = 5;
   }else if (ch == 'm'|| ch == 'n' || ch == 'o'){
      res = 6;
   }else if (ch == 'p'|| ch == 'q' || ch == 'r' || ch =='s'){
      res = 7;
   }else if (ch == 't'|| ch == 'u' || ch == 'v'){
      res = 8;
   }else if (ch == 'w'|| ch == 'x' || ch == 'y' || ch =='z'){
      res = 9;
   }
   return res;
}

trieNode* search(trieNode* node, char* input) {
  int flag = 0;
  for (int i = 0; i < strlen(input); i++) {
    int branch_index;
    if (input[i] == '#') {
      branch_index = 8;
      flag = 1;
    } else {
      branch_index = input[i] - '0' - 2;
      if (branch_index < 0) {
        printf("invalid input\n");
        return NULL;
      }
    }
    if (node != NULL) {
      node = node->branches[branch_index];
    }
  }
  if (node != NULL && node->word != NULL) {
    printf("%s", node->word);
    return node;
  } else {
    if (flag == 1) {
      printf("There are no more T9onyms.\n");
    } else {
      printf("Not found in current dictionary.\n");
    }
  }
  return NULL;
}

void free_tree(trieNode *root){
   for (int i = 0; i < BRANCHES;i++){
      if(root ->branches[i] != NULL){
         free_tree(root->branches[i]);
      }
   }
   if (root->word != NULL){
      free(root->word);
   }
   free(root);
}