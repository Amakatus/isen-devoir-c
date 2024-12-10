#include "include/file.h"
#include "include/word.h"
#include "linkedlist.h"
#include "stdio.h"
#include <stdlib.h>
#include "dirent.h"
#include <string.h>

#define READ_LIMIT 300

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
        token = strtok_r(stored_file," ", &state);
        while (token != NULL) {
            token[strcspn(token, "\n")] = 0;
            addWord(wordList, token, line_number,fileName);
            token = strtok_r(NULL," ", &state);
        }
        line_number++;
    }

    fclose(file);
    return 0;
}

void sendSafeFile(const char *argv[], char* safe_file[], int* safe_file_count) {
    DIR *dir;
    struct dirent *dent;
    FILE *file;
    char stored_file[READ_LIMIT];
    char file_path[READ_LIMIT];
    int i;
    dir = opendir(argv[1]);
    if (dir != NULL) {
        while ((dent = readdir(dir)) != NULL) {
            if (strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0 || dent->d_name[0] == '.') {
                continue; // au lieu des else ?
            }
            
            snprintf(file_path, READ_LIMIT, "%s/%s", argv[1], dent->d_name);
            file = fopen(file_path, "r");
            if (file == NULL) {
                continue;
            }

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
                if (count >= 30) break;
            }

            if (count < 30) {
                printf("Le fichier %s est valide\n", dent->d_name);
                safe_file[*safe_file_count] = strdup(file_path); // Ajoute le chemin complet du fichier
                (*safe_file_count)++;
            } else {
                printf("Le fichier %s est invalide\n", dent->d_name);
            }

            fclose(file);
        }
    }
    closedir(dir);
}
