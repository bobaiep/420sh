#include "builtins.h"

//Déclaration de nos builtins:
int sh_cat(char** args);
int sh_cd(char** args);
int sh_echo(char** args);
int sh_pwd(char** args);
int sh_exit(char** args);

//Création d'une liste de nos builtins:
const char* list_builtins[] = {
    "cd",
    "cat",
    "echo",
    "pwd",
    "exit"
};

pointer_function builtins_func[] = {
    &sh_cd,
    &sh_cat,
    &sh_echo,
    &sh_pwd,
    &sh_exit
};


const int sh_nb_builtins = 5;
/*
int sh_nb_builtins(void){
    return sizeof(list_builtins) / sizeof(char *);
}*/

int sh_cat(char** args){
    int i;
    int res;
    int byte_lu; 
    char buf[1024];
    ssize_t t;

    for (i = 1; *(args+i) != NULL; i++){
        res = open(args[i],O_RDONLY);
        if(res == -1){
            printf("File does not exist !\n");
        } 
        else{
            while((byte_lu = read(res,buf,1024))>0){
                t = write(STDOUT_FILENO,buf,byte_lu);
                close(t);
            }
        }
    }
    if (args[1]==NULL){
        printf("There is nothing to cat\n");
    }
    return 1;
}


int sh_cd(char** args){
    if (args[1] == NULL){
        if (chdir(getenv("HOME")) != 0){
            perror("420sh");
        }
    }
    else{
        if (chdir(args[1]) != 0){
            perror("420sh");
        }
    }
    current->oldpwd = current->pwd;
    sh_pwd(NULL);
    return 1;
}

int sh_echo(char** args){
    for (size_t i = 1; *(args+i) != NULL; i++)
    {
        printf("%s ", *(args+i));
    }
    printf("\n");

    return 1;
}

int sh_pwd(char** args __attribute__((unused))){
    current->pwd = getcwd(NULL,0);
    if (current->pwd == NULL){
        perror("420sh");
    }
    if (args != NULL)
        printf("%s\n",current->pwd);

    return 1;
}

int sh_exit(char** args __attribute__((unused))){
    return 0;
}