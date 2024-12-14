#include "word.h"
#include "string.h"
#include <strings.h>
#include "filters.h"
#include <stdlib.h>

int check_if_wildcard(void* type){
    char* searchWord = (char *) type;
    if (searchWord == NULL || strlen(searchWord) == 0) {
        return -1;
    }
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

int wildcard_match(void *data, const void *type){
    struct Word* word = (struct Word*) data;
    char* searchWord = (char *) type;
    char* newSearchWord = strdup(searchWord);
    switch (check_if_wildcard(searchWord)){
        case 0:
            newSearchWord++;
            return strstr(word->word, newSearchWord) != NULL;
        case 1:
            newSearchWord[strlen(newSearchWord) - 1] = '\0';
            return strstr(word->word, newSearchWord) != NULL;
        case 2:
            newSearchWord++;
            newSearchWord[strlen(newSearchWord) - 1] = '\0';
            return strstr(word->word, newSearchWord) != NULL;
    }
    return -1;
}


