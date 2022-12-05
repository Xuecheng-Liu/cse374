/* tnine is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode.  It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"
#include <ctype.h>


// run_session run the on-going decoding interaction with the
// user.  It requires a previously build wordTrie to work.
void run_session(trieNode *wordTrie);

int main(int argc, char **argv) {
  FILE *dictionary = NULL;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
    return EXIT_FAILURE;
  } else {
    dictionary = fopen(argv[1], "r");
    if (!dictionary) {
      fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  }

  // build the trie
  trieNode* root = makeNode();
  int bufferLength = 255;
  char buffer[bufferLength]; 
  while(fgets(buffer, bufferLength, dictionary)) {
    insert(buffer,root);
  }
  // run interactive session
  run_session(root);
  printf("session end\n");
  // clean up
  free_tree(root);
  return(EXIT_SUCCESS);
}

void run_session(trieNode *root){
  char input[MAXLEN];
  printf("Enter \"exit\" to quit.\n");
  trieNode* curr;
  while(1){
    printf("Enter Key Sequence (or \"#\" for next word):\n> ");
    scanf("%s",input);

    if (strcmp(input,"exit") == 0){
      break;
    }else{
      if (strcmp(input,"#") != 0){
          curr = search(root,input);
      }else{
          curr = search(curr,input);
      }  
    }
    }
  }







