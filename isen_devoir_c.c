#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define PROJECT_NAME "isen-devoir-c"
#define READ_LIMIT 300

struct LinkedList{
    struct LinkedList *next;
    void* data;
};

struct Word {
    char* word;
    FILE file;
    struct LinkedList* line_numbers;
    int count;
};

struct LineNumbers {
    int index;
    int count_per_lign;
};

struct LinkedList* newLinkedList(void* data){
    struct LinkedList* new_ll = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    new_ll -> next = NULL;
    new_ll -> data = data;
    return new_ll; 
}

struct LinkedList* createNewLineNumbers(int line_number){
    if(line_number <= 0){
        perror("ligne inferieure a 0.");
    }
    struct LineNumbers* new_line_numbers = (struct LineNumbers*)malloc(sizeof(struct LineNumbers));
    new_line_numbers -> index = line_number;
    new_line_numbers -> count_per_lign = 1;
    struct LinkedList* new_ll = newLinkedList(new_line_numbers);
    return new_ll;
}

struct LinkedList* createWord(const char* word, int line_number){
    struct Word* new_word = (struct Word*)malloc(sizeof(struct Word));
    if (word == NULL ){
        printf("Pas de mot en variable.");
    }
    new_word -> word = strdup(word);
    new_word -> count = 1;

    if (line_number == 0) {
        printf("Nombre nul trouve.");
    }

    new_word -> line_numbers = createNewLineNumbers(line_number);
    struct LinkedList* new_ll = newLinkedList(new_word);
    return new_ll;
}


int checkifWordExist(struct LinkedList* wordList, const char* word){
    struct LinkedList* current = wordList;
    while (current != NULL){
        struct Word* current_word = (struct Word*) current -> data;
        if(strcmp(word,current_word -> word) == 0){
            printf("Le mot existe deja");
            return 1;
        }
        current = current -> next;
    } 
    return 0;
}


void addWord(struct LinkedList** wordList, const char* word, int line_number) {
    struct LinkedList* current = *wordList;
    while (current != NULL) {
        struct Word* current_word = (struct Word*)current->data;

        if (strcmp(current_word->word, word) == 0) {
            struct LinkedList* line = current_word->line_numbers;
            while (line != NULL) {
                struct LineNumbers* line_numbers = (struct LineNumbers*)line->data;
                if (line_numbers->index == line_number) {
                    line_numbers->count_per_lign++;
                    current_word->count++;
                    return;
                }
                line = line->next;
            }
            struct LinkedList* new_line = createNewLineNumbers(line_number);
            new_line->next = current_word->line_numbers;
            current_word->line_numbers = new_line;
            current_word->count++;
            return;
        }

        current = current->next;
    }

    struct LinkedList* new_word = createWord(word, line_number);
    new_word->next = *wordList;
    *wordList = new_word;
}


void searchWord(struct LinkedList* linkedList, const char* word){
    while(linkedList != NULL){
        struct Word* wordList = (struct Word*) linkedList -> data; 
        if(strcmp(wordList->word,word) == 0){
            printf("Mot trouve dans le fichier : %s\n",wordList->word);
            printf("Occurence %d\n",wordList->count);
            printf("Lignes : \n");
            struct LinkedList* line = wordList->line_numbers;
            while (line != NULL) {
                struct LineNumbers* current_line = (struct LineNumbers*) line -> data;
                printf("L%d (%d fois) ", current_line->index, current_line -> count_per_lign);
                line = line -> next;
            }
            return;
        }
        linkedList = linkedList -> next;
    }
    printf("Mot non trouve %s",word);
}

void listSafeFile(const char *argv[]){ // Pas tres utile , mieux vaut verifier par exemple les 50 premiers caracteres
    DIR *dir;
    struct dirent *dent;
    FILE *file;
    char stored_file[READ_LIMIT];
    char file_path[READ_LIMIT];
    int i;
    dir = opendir(argv[1]);
    if(dir != NULL){
        while((dent=readdir(dir)) != NULL){
            if((strcmp(dent->d_name,".")==0 || strcmp(dent->d_name,"..")==0 || (*dent->d_name) == '.' )){
            } else {
                snprintf(file_path, READ_LIMIT, "%s/%s", argv[1],dent->d_name);
                file = fopen(file_path, "r");

                int is_valid = 1;
                while (fgets(stored_file, READ_LIMIT, file) != NULL) {
                    i = 0;
                    while (i < READ_LIMIT && stored_file[i] != '\0') {
                        if ((stored_file[i] < 32 || stored_file[i] > 122) && stored_file[i] != '\n') {
                            is_valid++;
                            break;
                        }
                        i++;
                    }
                    if (!is_valid) {
                        break;
                    }
                }

                if(is_valid < 30){
                    printf("le fichier %s est un fichier valide\n",dent -> d_name);
                } else {
                    printf("le fichier %s est un fichier invalide\n", dent -> d_name);
                }

                fclose(file);
            }
        }
    }
    closedir(dir);
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


void printWords(struct LinkedList* linkedList) {
    struct Word* wordList = (struct Word*) linkedList -> data;
    while (wordList != NULL) {
        printf("Mot : %s\n", wordList->word);
        printf("Occurence : %d\n", wordList->count);
        printf("Lignes : ");
        struct LinkedList* line = wordList -> line_numbers;
        while(line != NULL) {
            struct LineNumbers* current_line = (struct LineNumbers*) line ->data;
            printf("L%d (%d fois) ", current_line->index, current_line -> count_per_lign);
            line = line->next;
        }
        printf("\n");

        linkedList = linkedList->next;
    }
}


void freeStructs(struct LinkedList* linkedList){
    while(linkedList != NULL){
        struct Word* wordList = (struct Word*) linkedList->data;

        struct LinkedList* lines = wordList->line_numbers;
        while(lines != NULL){
            struct LineNumbers* current_line = (struct LineNumbers*) lines->data;
            free(current_line);
            lines = lines->next;
        }

        free(wordList->word);
        free(wordList);

        struct LinkedList* temp = linkedList;
        linkedList = linkedList->next;
        free(temp);
    }
}



int main(int argc, char const *argv[])
{
    //struct LinkedList* wordList = NULL;
    listSafeFile(argv);
    //readFile("./samples/test.txt",&wordList);
    //printWords(wordList);
    //searchWord(wordList,"Bonjour");
    //freeStructs(wordList);
    return 0;
}
