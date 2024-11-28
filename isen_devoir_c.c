#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROJECT_NAME "isen-devoir-c"
#define READ_LIMIT 200

struct Word {
    char* word;
    struct LineNumbers* line_numbers;
    int count; // occurence de mots
    struct Word *next;
};

struct LineNumbers {
    int index;
    struct LineNumbers *next;
};

int readFile(char* fileName){
    FILE *file;
    char* state;
    char* token;
    char stored_file[READ_LIMIT];
    file = fopen(fileName,"r");
    if (file == NULL){
        printf("Erreur à l'ouverture du fichier");
        return 1;
    }
    printf("Ouverture du fichier...\n");
    while (fgets(stored_file, READ_LIMIT, file) != NULL) {
        printf("Ligne lue : %s \n",stored_file);
        token = strtok_r(stored_file, " ", &state);
        while (token != NULL) {
            printf("Token : %s\n", token);
            token = strtok_r(NULL, " ", &state);
        }
    }
    return 0;

}

struct Word* createWord(const char* word, int line_number){
    struct Word* new_word = (struct Word*)malloc(sizeof(struct Word));
    struct LineNumbers* new_line_numbers = (struct LineNumbers*)malloc(sizeof(struct LineNumbers));
    if (word == NULL ){
        printf("Pas de mot en variable.");
    }
    new_word -> word = word;
    new_word -> count = 1;
    new_word -> next = NULL;

    if (line_number == NULL) {
        printf("Nombre nul trouvé.");
    }

    new_word -> line_numbers = new_line_numbers;
    new_word -> line_numbers -> index = line_number;
    new_word -> line_numbers -> next == NULL;

    return new_word;
}

int checkifWordExist(struct Word* wordList, const char* word){
    do {
        if(strcmp(word,wordList -> word)){
            printf("Le mot existe deja");
            return 0;
        }
        wordList = wordList -> next;
    } while (wordList == NULL);
    printf("Nouveau mot trouve");
    return 1;
}

void addWord(struct Word* wordList, const char* word, int line_number){
    do {
        if(strcmp(word,wordList -> word)){
            wordList -> line_numbers;
            return 0;
        }
        wordList = wordList -> next;
    } while (wordList == NULL);
    printf("Nouveau mot trouve");
    return 1;
}


int main(int argc, char const *argv[])
{
    readFile("test.txt");
    return 0;
}
