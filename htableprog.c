#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "htable.h"

int main(int argc, char**argv) {
    /*htable h=htable_new(113);
    char word[256];
    char op;

    while(2==scanf(" %c %255s", &op, word)){
        if('+'==op){
            htable_insert(h, word);
        }else if('?'==op){
            printf("%d %s\n", htable_search(h, word), word);
        }
    }

    htable_free(h);*/
    


    

    
    htable h=NULL;
    char word[256];
    if(argc>0){
        h = htable_new(atoi(argv[1]));
    }else{
        fprintf(stderr,"Please input a capacity.");
    }

    while(getword(word, sizeof word, stdin) != EOF){
        htable_insert(h, word);
    }

        
    htable_print(h, stdout);
    htable_free(h);

    

    
    return EXIT_SUCCESS;
}
