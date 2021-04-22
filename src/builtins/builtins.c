#include "builtins.h"

//Déclaration de nos builtins:
int sh_cat(char** args);
int sh_cd(char** args);
int sh_echo(char** args);
int sh_pwd(char** args);
int sh_exit(char** args);

//Création d'une liste de nos builtins:
const char* list_builtins[] = {
    "cat",
    "cd",
    "echo",
    "exit",
    "list-builtins",
    "mkdir",
    "pwd"
};

pointer_function builtins_func[] = {
    &sh_cat,
    &sh_cd,
    &sh_echo,
    &sh_exit,
    &sh_list_builtins,
    &sh_mkdir,
    &sh_pwd
};


const int sh_nb_builtins = 7;
/*
int sh_nb_builtins(void){
    return sizeof(list_builtins) / sizeof(char *);
}*/

int sh_list_builtins(char** args){
    if(args){
        printf("Here's a list of available builtins: \n");
        for(int i = 0; i < sh_nb_builtins; i++){
            printf("    %i - %s\n",i,list_builtins[i]);
        }
    }
    return 1;
}

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
            printf("\n");
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
    strcpy(current->oldpwd,current->pwd);
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
    char tmp[4096];
    if (getcwd(tmp,sizeof(tmp)) == NULL){
        perror("420sh");
    }
    strcpy(current->pwd,tmp);
    if (args != NULL)
        printf("%s\n",current->pwd);

    return 1;
}

int sh_exit(char** args __attribute__((unused))){
    return 0;
}

int sh_mkdir(char** args){
    if (args[1] == NULL){
        fprintf(stderr, "mkdir: Missing Operand !\n");
        return 1;
    } 
    else{
        for (int i=1;*(args+i) != NULL; i++) {
            if(file_exist(*(args+i))){
                continue;
            } 
            else {
                mkdir(*(args+i), S_IRUSR | S_IWUSR | S_IXUSR);
            }
        }
    }
    return 1;
}