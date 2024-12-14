#include "word.h"
#include "string.h"
#include <strings.h>
#include "filters.h"
#include "fnmatch.h"

int check_if_wildcard(void* type){
    char* searchWord = (char *) type;
    if(searchWord[0] == '*'){
        return 0;
    } if (searchWord[strlen(searchWord) - 1] == '*'){
        return 1;
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
    return (strcasecmp(word->word, searchWord) == 0);
}

int wildcard_match(void *data, void *type){
    struct Word* word = (struct Word*) data;
    char* searchWord = (char *) type;
    if(check_if_wildcard(searchWord) != -1){
        return fnmatch(searchWord, word->word, 0);
    }
    return 0;
}


