#include "word.h"
#include "string.h"
#include <strings.h>
#include "filters.h"

int check_if_wildcard(void* type){
    char* searchWord = (char *) type;
    int i = 0;
    while(i < (int) strlen(searchWord)){
        if(searchWord[i] == '*'){
            return i;
        }
        i++;
    }
    return -1;
}
                                                                          
int exact_match(void* data, void* type){
    struct Word* word = (struct Word*) data;
    char* searchWord = (char*) type;
    return (strcmp(word->word,searchWord) == 0);
}

int case_insensitive_match(void* data, void* type){
    struct Word* word = (struct Word*) data;
    char* searchWord = (char *) type;
    if(check_if_wildcard(type) >= 0){
        
    }    
    return (strcasecmp(word->word, searchWord) == 0);
}


