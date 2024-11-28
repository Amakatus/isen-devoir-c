#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROJECT_NAME "isen-devoir-c"
#define READ_LIMIT 200

struct Word {
    char* word;
    char* line_numbers;
    int count; // occurence de mots
    struct Word *next;
};

struct Word* createWord(const char* word, int line_number){
    struct Word* new_word = (struct Word*)malloc(sizeof(struct Word)); //rajouter erreur
    new_word -> word = strdup(word);
    new_word -> line_numbers = line_number;
    new_word -> count = 1;
    new_word -> next = NULL;
    return new_word;
}

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

int main(int argc, char const *argv[])
{
    readFile("test.txt");
    return 0;
}
