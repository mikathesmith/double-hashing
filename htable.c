#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

/*Double hashing.*/

struct htablerec {
    int capacity;
    int numkeys;
    int *frequencies;
    char **keys;
};


htable htable_new(int size) {
    int i;
    htable result = emalloc(sizeof *result); /*declare htable, allocate memory*/
    result->capacity = size;  
    result->numkeys = 0;
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    result->frequencies = emalloc(result->capacity * sizeof result->frequencies[0]);
    
    for(i=0; i < size; i++){
        result->keys[i] = NULL;
        result->frequencies[i]=0;
    }
    
    return result;
}

static unsigned int htable_word_to_int(char *word){
    unsigned int result=0;
    while(*word != '\0'){
        result= (*word++ + 31 * result);
    }
    return result;
}

static unsigned int htable_step(htable h, unsigned int i_key){
    return 1 + (i_key % (h->capacity-1));
}

int htable_insert(htable h, char *str) {
    unsigned int val = htable_word_to_int(str);
    int rem = val % (unsigned int)h->capacity;
    int collisions=0;
    int step = htable_step(h, val);
    
    /*To find an empty cell, increment rem while its less than capacity and either not null or not
      a cell containing the same str value*/
    while(collisions < h->capacity && h->frequencies[rem]!= 0 && strcmp(h->keys[rem], str) != 0){
        rem+=step;
        rem = rem % h->capacity;
        collisions++;
    }
    
    if(h->frequencies[rem]== 0){ /*If the cell is empty.*/
        h->keys[rem] = emalloc((strlen(str)+1) * sizeof str[0]);
        strcpy(h->keys[rem], str);
        /*h->keys[rem] = val; Insert the value*/
        h->frequencies[rem]++; 
        h->numkeys++; 
        return 1;
    }else if(strcmp(h->keys[rem], str) == 0){  /*you find a cell with the same value.*/
        h->frequencies[rem]++;
        return h->frequencies[rem]; /*Return the new incremented frequency of the cell.*/
    }else{
        return 0;  /*return 0 if there is no empty space and htable is full*/
    }
}

void htable_print(htable h, FILE *stream) {
    int i;
    for(i=0;i<h->capacity;i++){
        if(h->keys[i]!=NULL){
            fprintf(stream, "%d: %s\n", h->frequencies[i], h->keys[i]);
        }
    } 
 }




/*This method sorts numbers in ascending order.*/
int htable_search(htable h, char *str) {
    int collisions=0;
    unsigned int val = htable_word_to_int(str);
    int rem = val % (unsigned int)h->capacity;
    int step = htable_step(h, val);

    while(collisions < h->capacity && h->frequencies[rem]!= 0 && strcmp(h->keys[rem], str) != 0){
        rem+=step;
        rem = rem % h->capacity;
        collisions++;
    }
    
    if(collisions==h->capacity){
        printf("Hashtable does not contain the key");
        return 0;
    }else{
        return h->frequencies[rem];
    }

}



void htable_free(htable h) {
    /* free the memory associated with the flexarray */
  
    free(h->keys);
    free(h->frequencies);        
    
}
