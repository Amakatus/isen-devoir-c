#include "include/word.h"
#include "string.h"
#include <strings.h>
#include "include/filters.h"

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

