#include "builtins.h"

//Déclaration de nos builtins:
int sh_cd(char** args);
int sh_exit(char** args);
int sh_help(char** args);

//Création d'une liste de nos builtins:
const char* list_builtins[] = {
    "cd",
    "exit"
};

pointer_function builtins_func[] = {
    &sh_cd,
    &sh_exit
};


const int sh_nb_builtins = 2;
/*
int sh_nb_builtins(void){
    return sizeof(list_builtins) / sizeof(char *);
}*/

int sh_cd(char** args){
    if (args[1] == NULL){
        args[1] = getenv("HOME");
    }
    else{
        if (chdir(args[1]) != 0){
            perror("420sh");
        }
    }
    return 1;
}

int sh_exit(char** args __attribute__((unused))){
    return 0;
}