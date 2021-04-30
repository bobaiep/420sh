#define _POSIX_C_SOURCE 200809L
#include "builtins.h"

//Déclaration de nos builtins:
int sh_cat(char** args);
int sh_cd(char** args);
int sh_echo(char** args);
int sh_exit(char** args);
int sh_history(char** args);
int sh_list_builtins(char** args);
int sh_ls(char** args);
int sh_mkdir(char** args);
int sh_pwd(char** args);
int sh_rm(char** args);

//Les Couleurs :
#define RESET_COLOR "\e[m"
#define GREEN "\e[32m"
#define BLUE "\e[36m" 

//Création d'une liste de nos builtins:
const char* list_builtins[] = {
    "cat",
    "cd",
    "echo",
    "exit",
    "history",
    "list-builtins",
    "ls",
    "mkdir",
    "pwd",
    "rm"
};

pointer_function builtins_func[] = {
    &sh_cat,
    &sh_cd,
    &sh_echo,
    &sh_exit,
    &sh_history,
    &sh_list_builtins,
    &sh_ls,
    &sh_mkdir,
    &sh_pwd,
    &sh_rm
};


const int sh_nb_builtins = 10;
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

int sh_history(char** args){
    if (args){
        print_hist(current->history);
    }

    return 1;
}

int sh_ls(char** args){
    DIR *dirp; 
    struct dirent *dptr; 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd));
    struct stat s;
    struct group *grp;
    struct passwd *pwd;
    char buffer[80];
    int argc = 0;

    for (size_t i = 1; *(args+i) != NULL; i++){
        argc++;
    }

    if(argc<4){   
        dirp=opendir(cwd);

        if (dirp==NULL) {
            printf("No such file or directory\n");
            return(1);
        }

        while((dptr=readdir(dirp))) {
            stat(dptr->d_name,&s);

            if(dptr->d_name[0] != '.'){ 
                
                if(S_ISBLK(s.st_mode))
                    fprintf(stdout, "b" );
                else if(S_ISCHR(s.st_mode))
                    fprintf(stdout, "c" );
                else if(S_ISDIR(s.st_mode))
                    fprintf(stdout, "d" );
                else if(S_ISFIFO(s.st_mode))
                    fprintf(stdout, "p" );
                else if(S_ISLNK(s.st_mode))
                    fprintf(stdout, "l" );
                else if(S_ISREG(s.st_mode))
                    fprintf(stdout, "-" );
                else if(S_ISSOCK(s.st_mode))
                    fprintf(stdout, "s" );

                fprintf(stdout, s.st_mode & S_IRUSR ? "r" : "-" );
                fprintf(stdout, s.st_mode & S_IWUSR ? "w" : "-" );
                fprintf(stdout, s.st_mode & S_IXUSR ? "x" : "-" );
                fprintf(stdout, s.st_mode & S_IRGRP ? "r" : "-" );
                fprintf(stdout, s.st_mode & S_IWGRP ? "w" : "-" );
                fprintf(stdout, s.st_mode & S_IXGRP ? "x" : "-" );
                fprintf(stdout, s.st_mode & S_IROTH ? "r" : "-" );
                fprintf(stdout, s.st_mode & S_IWOTH ? "w" : "-" );
                fprintf(stdout, s.st_mode & S_IXOTH ? "x" : "-" );

                pwd = getpwuid(s.st_uid);
                fprintf(stdout," %s ", pwd->pw_name);

                grp = getgrgid(s.st_gid);
                fprintf(stdout," %s ", grp->gr_name);

                fprintf(stdout," %lld ", (long long)s.st_size);

                strcpy(buffer,ctime(&s.st_mtime));
                buffer[strlen(buffer)-1]='\0';
                fprintf(stdout, " %s ", buffer);

                if(!access(dptr->d_name,F_OK)){ 
                    struct stat st;
                    stat(dptr->d_name, &st);
                    if(S_ISDIR(st.st_mode)) {
                        printf(BLUE"%s     "RESET_COLOR,dptr->d_name); 
                    } 
                    else {
                        printf(GREEN"%s     "RESET_COLOR,dptr->d_name); 
                    }
                } 
                else{
                    printf("%s     ",dptr->d_name);
                }
                printf("\n");
            }
        }
        closedir(dirp);
    } 
    else{
        fprintf(stderr, "Usage :\n   - ls\n");
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

int sh_rm(char** args){
    int param;
    for(int i=1;*(args+i)!=NULL;i++){
        param=open(args[i],O_RDONLY);
        if(param==-1){
            printf("rm: Can't delete %s\n",args[i]);
            continue;
        }
        else{
            remove(args[i]);
        }
    }
    return 1;
}