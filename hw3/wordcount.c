/* Copyright 2022 Xuecheng Liu */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

void helper (FILE *fp,int *nl,int *nw, int *nc);

int main (int argc, char **argv) {
    if (argc < 2) {
        // did not provide neither the option nor the file name
        printf("Usage:./wordcount requires an input file.\n");
        return EXIT_FAILURE;
    }

    if ( strcmp(argv[1],"-l") == 0
        || strcmp(argv[1],"-w") == 0
        || strcmp(argv[1],"-c") == 0) {
    // one option is detected
    if (argc < 3) {
        // missing the file name
        printf("Usage:./wordcount requires an input file.\n");
        return EXIT_FAILURE;
    }
    // loop through each file
    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if( !fp ) {
            fprintf(stderr, "%s will not open. Skipping.\n", argv[i]);
        }else {
            int nl,nw,nc;
            helper(fp,&nl,&nw,&nc);
            if (strcmp(argv[1],"-l") == 0){
                printf("%d\n",nl);
            } else if (strcmp(argv[1],"-w") == 0){
                printf("%d\n",nw);
            }else{
                printf("%d\n",nc);
            }
        }
        fclose(fp);
    }
    } else {
    // no option is detected
        int totalLine = 0;
        for (int i = 1; i < argc; i++) {
            FILE *fp = fopen(argv[i],"r");
            if(!fp) {
                fprintf(stderr, "%s will not open. Skipping.\n", argv[i]);
            } else {
                int nl, nw, nc;
                helper(fp,&nl,&nw,&nc);
                totalLine = totalLine + nl;
                printf("%d %d %d %s\n",nl,nw,nc,argv[i]);
            }
        }
        printf("Total Lines = %d\n",totalLine);
    }
    return EXIT_SUCCESS;
}

// the following code is adopted from text book C Programming
void helper( FILE *fp,int *nl,int *nw, int *nc) {
    int c,numl,numw,numc,state;

    state = OUT;
    numl = numw = numc = 0;
    while ((c = fgetc(fp))!= EOF) {
        ++numc;
        if (c == '\n') {
            ++numl;
        }
        if (c == ' '|| c == '\n'|| c == '\t') {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            ++numw;
        }
    }
    *nl = numl;
    *nw = numw;
    *nc = numc;
}
