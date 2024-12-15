#include "word.h"
#include "string.h"
#include <stdio.h>
#include <strings.h>
#include "filters.h"
#include <stdlib.h>


/**
 * @brief Vérifie si le mot de recherche contient des caractères de type *. Retourne :

    -1 si le mot est vide,
    0 si le * est au début du mot,
    1 si le * est à la fin du mot,
    2 si le * est à la fois au début et à la fin du mot.
 * 
 * @param type 
 * @return int
 */
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

/**
 * @brief Vérifie si le mot donné correspond exactement au mot recherché, en utilisant une comparaison stricte. Retourne 0 si les mots sont égaux, sinon 1.
 * 
 * @param data 
 * @param type 
 * @return Retourne 0 si c'est le cas, 1 sinon.
 */
int exact_match(void* data, void* type){
    struct Word* word = (struct Word*) data;
    char* searchWord = (char*) type;
    return (strcmp(word->word,searchWord) == 0);
}

/**
 * @brief Vérifie si le mot donné correspond au mot recherché sans tenir compte de la casse (insensible à la casse). Retourne 0 si les mots sont égaux, sinon 1.
 
 * 
 * @param data 
 * @param type 
 * @return Retourne 0 si c'est le cas, 1 sinon.
 */

int case_insensitive_match(void* data, void* type){
    struct Word* word = (struct Word*) data;
    char* searchWord = (char *) type;    
    return (strcasecmp(word->word, searchWord) == 0);
}

/**
 * @brief Vérifie si le mot donné correspond à un mot recherché avec des caractères de type *.
        Si * est à la fin du mot (ex : Bon*), le mot doit commencer par la chaîne avant le *.
        Si * est au début du mot (ex : *Bon), le mot doit finir par la chaîne après le *.
        Si * est à la fois au début et à la fin du mot (ex : *Bon*), le mot peut contenir la chaîne recherchée n'importe où.
        Retourne 1 si le mot correspond au critère, sinon 0.
 * 
 * @param data 
 * @param type 
 * @return int 
 */
int wildcard_match(void *data, void *type) {
    struct Word* word = (struct Word*) data;
    char* searchWord = (char *) type;

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
        char* tempSearchWord = strdup(++searchWord);
        tempSearchWord[strlen(tempSearchWord) - 1] = '\0';
        int result = strstr(word->word, tempSearchWord) != NULL;
        free(tempSearchWord);
        return result;
    }
    return -1;
}




