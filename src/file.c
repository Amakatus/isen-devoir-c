#include "file.h"
#include "word.h"
#include "linkedlist.h"
#include "stdio.h"
#include <stdlib.h>
#include "dirent.h"
#include <string.h>

#define READ_LIMIT 300

/**
 * @brief Cette fonction lis un fichier passer en paramètre, et sépare le fichier en mot avec strcspn. Ensuite, les tokens sont ajoutées en tant que mot grâce à add_word
 * 
 * @param fileName 
 * @param wordList 
 * @return int 
 */
int read_file(char* fileName, struct LinkedList** wordList) {
    FILE *file;
    char* state;
    char* token;
    char storedFile[READ_LIMIT];
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Erreur à l'ouverture du fichier");
        return 1;
    }
    int lineNumber = 1;
    printf("Ouverture du fichier...\n");
    while (fgets(storedFile, READ_LIMIT, file) != NULL) {
        token = strtok_r(storedFile," ", &state);
        while (token != NULL) {
            token[strcspn(token, "\n")] = 0;
            add_word(wordList, token, lineNumber,fileName);
            token = strtok_r(NULL," ", &state);
        }
        lineNumber++;
    }

    fclose(file);
    return 0;
}


/**
 * @brief Vérifie si les fichiers du dossier passer en paramètres sont corrects. La fonction compare avec le tableau ASCII si les caractères sont des caractères que l'on trouve habituellement dans un texte.
 * 
 * @param argv 
 * @param safeFiles 
 * @param safeFileCount 
 */
void send_safe_file(char *argv[], char* safeFiles[], int* safeFileCount) {
    DIR *dir;
    struct dirent *dent;
    FILE *file;
    char storedFile[READ_LIMIT];
    char filePath[READ_LIMIT];
    int i;
    dir = opendir(argv[1]);
    if (dir != NULL) {
        while ((dent = readdir(dir)) != NULL) {
            if (strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0 || dent->d_name[0] == '.') {
                continue;
            }
            snprintf(filePath, READ_LIMIT, "%s/%s", argv[1], dent->d_name);
            file = fopen(filePath, "r");
            if (file == NULL) {
                continue;
            }
            int count = 1;
            while (fgets(storedFile, READ_LIMIT, file) != NULL) {
                i = 0;
                while (i < READ_LIMIT && storedFile[i] != '\0') {
                    if ((storedFile[i] < 32 || storedFile[i] > 122) && storedFile[i] != '\n') {
                        count++;
                        break;
                    }
                    i++;
                }
                if (count >= 30) break;
            }
            if (count < 30) {
                printf("Le fichier %s est valide\n", dent->d_name);
                safeFiles[*safeFileCount] = strdup(filePath);
                (*safeFileCount)++;
            } else {
                printf("Le fichier %s est invalide\n", dent->d_name);
            }

            fclose(file);
        }
    }
    closedir(dir);
}
