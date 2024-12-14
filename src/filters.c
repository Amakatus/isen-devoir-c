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
    if (searchWord[0] == '*' && searchWord[strlen(searchWord) - 1] == '*') {
        return 2;
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

    if(check_if_wildcard(searchWord) == 0){
        searchWord++;
        return strstr(word->word, searchWord) != NULL;
    } else if (check_if_wildcard(searchWord) == 1){
        searchWord[strlen(searchWord) - 1] = '\0';
        return strstr(word->word,searchWord) != NULL;
    } else if (check_if_wildcard(searchWord) == 2){
        searchWord++;
        searchWord[strlen(searchWord) - 1] = '\0';
        return strstr(word->word,searchWord) != NULL;
    }

    return -1;
}


