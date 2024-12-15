#include "word.h"
#include "string.h"
#include <stdio.h>
#include <strings.h>
#include "filters.h"
#include <stdlib.h>

int check_if_wildcard(void* type){
    char* searchWord = (char *) type;
    if (searchWord == NULL || strlen(searchWord) == 0) {
        return -1;
    }
    if (searchWord[0] == '*' && searchWord[strlen(searchWord) - 1] == '*') {
        return 2;
    }
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

int wildcard_match(void *data, void *type) {
    if (data == NULL || type == NULL) {
        return 0;
    }
    
    struct Word* word = (struct Word*) data;
    char* searchWord = (char*) type;

    if (check_if_wildcard(searchWord) == 0) {
        searchWord++;
        size_t searchLen = strlen(searchWord);
        size_t wordLen = strlen(word->word);
        if (wordLen >= searchLen) {
            return strcmp(word->word + wordLen - searchLen, searchWord) == 0;
        }
        return 0;
    }

    if (check_if_wildcard(searchWord) == 1) {
        searchWord[strlen(searchWord) - 1] = '\0';
        return strncmp(word->word, searchWord, strlen(searchWord)) == 0;
    }

    if (check_if_wildcard(searchWord) == 2) {
        if (searchWord == NULL || strlen(searchWord) < 2) {
            return 0;
        }
        char* tempSearchWord = strdup(++searchWord);
        if (tempSearchWord == NULL) {
            return 0;
        }
        tempSearchWord[strlen(tempSearchWord) - 1] = '\0';
        int result = strstr(word->word, tempSearchWord) != NULL;
        free(tempSearchWord);
        return result;
    }

    return -1;
}



