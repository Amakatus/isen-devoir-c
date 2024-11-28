#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROJECT_NAME "isen-devoir-c"
#define READ_LIMIT 200

struct Word;

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
