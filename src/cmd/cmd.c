#include "cmd.h"

#define MAX_SIZE_HIST 100

void print_main_help(void){
    printf("======== Welcome to 420sh ========\n");
    printf("Usage:\n");
    printf("    (None) Start 420sh !\n");
    printf("    -v Start 420sh with voice recognition !\n");
    printf("    --voice Start 420sh with voice recognition !\n");

    return;
}

int file_exist(const char *filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    return (exist == 0) ? 1 : 0;
}

int isNumeric(const char *str){
    for(size_t i = 0; *(str+i) != '\0'; i++){
        if(*str < '0' || *str > '9')
            return 0;
    } 
    return 1;
}

History* history_init(){
    History* hist = malloc(sizeof(History));
    
    hist->lines = malloc(MAX_SIZE_HIST * sizeof(char *));
    for (int i = 0; i < MAX_SIZE_HIST; i++){
        hist->lines[i] = malloc(1024 * sizeof(char));
    } 
    hist->size = 0;
    hist->start = 0;

    return hist;
}

void add_to_hist(History* hist, char* command){
    if (hist != NULL){
        if (hist->size < MAX_SIZE_HIST){
            //hist->lines[hist->size++] = command;
            strcpy(hist->lines[hist->size++],command);
        }
        else if (hist->size == MAX_SIZE_HIST){
            //hist->lines[hist->start++] = command;
            strcpy(hist->lines[hist->start++],command);
            hist->start %= MAX_SIZE_HIST;
        }
    }
}

void print_hist(History* hist){
    if (hist != NULL){
        for (int i = hist->start; i < hist->size; i++){
            printf("%i %s",i,hist->lines[i]);
        }
    }
}

void hist_destroy(History* hist){
    for (int i = 0; i < MAX_SIZE_HIST; i++){
        free(hist->lines[i]);
    }
    free(hist->lines);
    free(hist);
}

AliasArray* aliases_init(void){
    AliasArray* aliases = malloc(sizeof(AliasArray));
    
    aliases->nb_alias = 0;

    aliases->size = 100;

    aliases->aliases = malloc(aliases->size * sizeof(Alias));

    return aliases;
}

void add_alias(AliasArray* aliases, Alias* alias){
    if (aliases->nb_alias == aliases->size){
        aliases->size *= 2;
        aliases->aliases = realloc(aliases->aliases,2 * aliases->size * sizeof(Alias));
    }
    aliases->aliases[aliases->nb_alias] = alias;
    aliases->nb_alias++;
}

void print_aliases(AliasArray* aliases,char* alias){
    if (aliases != NULL){
        if (aliases->nb_alias == 0){
            printf("You have not yet created an alias, to create one:\n");
            printf("    alias alias_name cmd\n");
        }
        else{
            if (alias == NULL){
                for (int i = 0; i < aliases->nb_alias; i++){
                    printf("%i %s :",i,aliases->aliases[i]->alias);
                    for (int j = 0 ; j < aliases->aliases[i]->cmd_size; j++){
                        printf(" %s",aliases->aliases[i]->cmd[j]);
                    }
                    printf("\n");
                }
            }else{
                char boo = 0;
                for (int i = 0; i < aliases->nb_alias; i++){
                    if (strcmp(aliases->aliases[i]->alias,alias) == 0){
                        printf("%i %s :",i,aliases->aliases[i]->alias);
                        boo = 1;
                        for (int j = 0 ; j < aliases->aliases[i]->cmd_size; j++){
                            printf(" %s",aliases->aliases[i]->cmd[j]);
                        }
                        printf("\n");
                        break;
                    }
                }
                if (boo == 0){
                    printf("%s doesn't exist, if you want to create an alias named %s:\n",alias,alias);
                    printf("    alias %s cmd\n",alias);
                }
            }
        }
    }
}

void aliases_destroy(AliasArray* aliases){
    for (int i = 0; i < aliases->nb_alias; i++){
        for(int j = 0; j < aliases->aliases[i]->cmd_size; j++){ 
            free(aliases->aliases[i]->cmd[j]);
        }
        free(aliases->aliases[i]->cmd);
        free(aliases->aliases[i]->alias);
        free(aliases->aliases[i]);  
    }
    free(aliases->aliases);
    free(aliases);
}