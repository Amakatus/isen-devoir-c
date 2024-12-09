#include "include/file.h"
#include "include/word.h"
#include "linkedlist.h"
#include "stdio.h"
#include <stdlib.h>
#include "dirent.h"
#include <string.h>

#define READ_LIMIT 300

struct LinkedList* createFile(char* fileName){
    struct LinkedList* new_ll = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    new_ll->next = NULL;
    new_ll->data = fileName;
    return new_ll;
}

int readFile(char* fileName, struct LinkedList** wordList) {
    FILE *file;
    char* state;
    char* token;
    char stored_file[READ_LIMIT];
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Erreur à l'ouverture du fichier");
        return 1;
    }
    int line_number = 1;
    printf("Ouverture du fichier...\n");
    while (fgets(stored_file, READ_LIMIT, file) != NULL) {
        //printf("Ligne lue : %d %s \n", line_number, stored_file);
        token = strtok_r(stored_file," ", &state);
        while (token != NULL) {
            //printf("%s\n", token);
            token[strcspn(token, "\n")] = 0;
            addWord(wordList, token, line_number);
            token = strtok_r(NULL," ", &state);
        }
        line_number++;
    }

    fclose(file);
    return 0;
}

void listSafeFile(const char *argv[]){
    DIR *dir;
    struct dirent *dent;
    FILE *file;
    char stored_file[READ_LIMIT];
    char file_path[READ_LIMIT];
    int i;
    int y = 0;
    char* safe_file[10];
    dir = opendir(argv[1]);
    if(dir != NULL){
        while((dent=readdir(dir)) != NULL){
            if((strcmp(dent->d_name,".")==0 || strcmp(dent->d_name,"..")==0 || (*dent->d_name) == '.' )){
            } else {
                snprintf(file_path, READ_LIMIT, "%s/%s", argv[1],dent->d_name);
                file = fopen(file_path, "r");

                int count = 1;
                while (fgets(stored_file, READ_LIMIT, file) != NULL) {
                    i = 0;
                    while (i < READ_LIMIT && stored_file[i] != '\0') {
                        if ((stored_file[i] < 32 || stored_file[i] > 122) && stored_file[i] != '\n') {
                            count++;
                            break;
                        }
                        i++;
                    }
                    if (!count) {
                        break;
                    }
                }

                if(count < 30){
                    printf("le fichier %s est un fichier valide\n",dent->d_name);
                    safe_file[y] = dent->d_name;
                } else {
                    printf("le fichier %s est un fichier invalide\n", dent->d_name);
                }
                y++;

                fclose(file);
            }
        }
    }
    closedir(dir);
}
