#include "include/word.h"
#include "string.h"
#include <strings.h>
#include "include/filters.h"

int exactMatch(void* data, void* type){
    struct Word* word = (struct Word*) data;
    char* search_word = (char*) type;
    return (strcmp(word->word,search_word) == 0);
}

int caseInsensitiveMatch(void* data, void* type){
    struct Word* word = (struct Word*) data;
    char* search_word = (char *) type;
    return (strcasecmp(word->word, search_word) == 0);
}

