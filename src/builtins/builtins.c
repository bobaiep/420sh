#define _POSIX_C_SOURCE 200809L
#include "builtins.h"

//Déclaration de nos builtins:
int sh_alias(char** args);
int sh_cat(char** args);
int sh_cd(char** args);
int sh_chmod(char** args);
int sh_cp(char** args);
int sh_echo(char** args);
int sh_exit(char** args);
int sh_history(char** args);
int sh_learn(char** args);
int sh_list_builtins(char** args);
int sh_ls(char** args);
int sh_mkdir(char** args);
int sh_mv(char** args);
int sh_pwd(char** args);
int sh_rm(char** args);
int sh_start_voice(char** args);
int sh_type(char** args);

//Les Couleurs :
#define RESET_COLOR "\e[m"
#define GREEN "\e[32m"
#define BLUE "\e[36m" 
#define RED "\e[31m"

#define BUFFER_SIZE 512

//Création d'une liste de nos builtins:
const char* list_builtins[] = {
    "alias",
    "cat",
    "cd",
    "change-color",
    "chmod",
    "cp",
    "echo",
    "exit",
    "history",
    "learn",
    "list-builtins",
    "ls",
    "mkdir",
    "mv",
    "pwd",
    "rm",
    "start-voice",
    "type"
};

pointer_function builtins_func[] = {
    &sh_alias,
    &sh_cat,
    &sh_cd,
    &sh_change_color,
    &sh_chmod,
    &sh_cp,
    &sh_echo,
    &sh_exit,
    &sh_history,
    &sh_learn,
    &sh_list_builtins,
    &sh_ls,
    &sh_mkdir,
    &sh_mv,
    &sh_pwd,
    &sh_rm,
    &sh_start_voice,
    &sh_type
};

const int sh_nb_builtins = 18;
/*
int sh_nb_builtins(void){
    return sizeof(list_builtins) / sizeof(char *);
}*/

int sh_alias(char** args){
    int argc = 0;
    for (size_t i = 0; *(args+i) != NULL; i++){
        argc++;
    }

    if (argc < 3){
        if (argc == 2){
            print_aliases(current->aliases,args[1]);
        }
        else{
            print_aliases(current->aliases,NULL);
        }
        
        return 1;
    }
    Alias* new = malloc(sizeof(Alias));

    new->alias = malloc(strlen(args[1]) * sizeof(char));
    strcpy(new->alias, args[1]);

    new->cmd = calloc(argc - 2 ,sizeof(char*));
    for (int i = 2; i < argc; i++){
        new->cmd[i-2] = malloc((strlen(args[i]) + 1) * sizeof(char));
        strcpy(new->cmd[i-2],args[i]);
    }

    new->cmd_size = argc - 2;

    add_alias(current->aliases, new);

    return 1;
}

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

int sh_learn(char** args){
    int argc = 0;
    for (int i = 0; *(args+i) != NULL; i++){
        argc++;
    }
    if (argc != 2){
        printf("Usage : learn word\nword : word that you want to add to known words for Voice Recogniton\n");
        return 1;
    }
    else{
        learn(args[1]);
        return 1;
    }
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

int sh_change_color(char** args){
    char* color[3] = {
        RED" - RED : 0\n"RESET_COLOR,
        BLUE" - BLUE : 1\n"RESET_COLOR,
        GREEN" - GREEN : 2\n"RESET_COLOR
    };
    if (args!=NULL && args[1] != NULL){
        if (isNumeric(args[1])){
            current->color = strtol(args[1], (char**)NULL, 10);
            return 1;
        }

        if(strcmp(args[1],"--help") || strcmp(args[1],"-h")){
            printf("Change the color of the prompt with the specified color_id\n");
            printf("Usage : change-color color_id\n");
            printf("color_id :\n");
            for (int i = 0; i < 3; i++){
                printf("%s",color[i]);
            }
        }

        return 1;
    }


    printf("Choose the color of the prompt : \n");
    for (int i = 0; i < 3; i++){
        printf("%s",color[i]);
    }
    scanf("%i", &current->color);
	getchar();
    
    return 1;
}

int sh_cp(char** args){
    FILE* fSrc;
    FILE* fDest;
    char buffer[512]; 
    int NbLus; 
    char outfilename[1000]; 
    int argc = 0;

    for (size_t i = 0; *(args+i) != NULL; i++){
        argc++;
    }

    if(argc == 3){
        if ((fSrc = fopen(args[1], "rb")) == NULL) { 
            fprintf(stderr,"File does not exist !\n");
            return 1;
        }

        fDest = fopen(args[2], "wb");
        if (fDest == NULL){
            sprintf(outfilename, "%s/%s", args[2], basename(args[1])); 
            fDest = fopen(outfilename, "w");
        } 
        else {
            fDest = fopen(args[2], "wb");
        }

        while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0) {
            fwrite(buffer, 1, NbLus, fDest);
        }

        fclose(fDest);
        fclose(fSrc);
    } 
    else{
        printf("Usage: cp path_to_file path_to_new_file\n");
    }
    return 1;
}

int sh_chmod(char** args){
    int max=778;
    int min=0;

    int argc = 0;
    for(size_t i =0; *(args+i) != NULL; i++){
        argc++;
    }
    if (argc < 3 || argc > 3){
        printf("Usage : chmod octal file\n");
        printf("Example : chmod 754 test\nOne digit for each class (user, group and others):\n");
        printf("0 : None\n");
        printf("1 : Execute only\n");
        printf("2 : Write only\n");
        printf("3 : Write and execute \n");
        printf("4 : Read only\n");
        printf("5 : Read and execute\n");
        printf("6 : Read and write \n");
        printf("7 : Read, write and execute\n");
    }
    if(argc==3){
        if(!isNumeric(args[1])){
            fprintf(stderr, "Invalid Argument: first argument must be a number\n");
            return 1;
        }
        int octal= strtol(args[1], (char**)NULL, 10);
        int octalPermissionString = strtol(args[1], (char**)NULL, 8);
        if(octal < min || octal > max){
            fprintf(stderr, "Invalid Octal\n");
            return 1;
        }
        if(file_exist(args[2])){
            chmod(args[2], octalPermissionString);
        } else {
            fprintf(stderr, "File does not exist !\n");
            return 1;
        }
    } 
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

int sh_mv(char** args){
    FILE* old;
    FILE* new;
    char buffer[BUFFER_SIZE];
    int len;
    char outfilename[1000];

    int argc = 0;
    for(size_t i =0; *(args+i) != NULL; i++){
        argc++;
    }

    if (argc > 3 || argc < 3){
        printf("Usage : mv old_file path_to_new_file\n");
        return 1;
    }
    if(argc == 3){
        if ((old = fopen(args[1], "rb")) == NULL) {
            fprintf(stderr,"%s : File does not exist !\n",args[1]);
            return 1;
        }

        new = fopen(args[2], "wb");
        if (new == NULL){
            sprintf(outfilename, "%s/%s", args[2], basename(args[1]));
            new = fopen(outfilename, "w");
        } 
        else {
            new = fopen(args[2], "wb");
        }

        while ((len = fread(buffer, 1, 512, old)) != 0)
        fwrite(buffer, 1, len, new);

        fclose(new);
        fclose(old);
        remove(args[1]);
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

int sh_start_voice(char** args){
    (void)args;

    Response* new = malloc(sizeof(Response));

    char **token;

    new->transcript = malloc(BUFFER_SIZE * sizeof(char));
    new->confidence = malloc(BUFFER_SIZE * sizeof(char));

    get_response(new);

    int confidence = strtol(new->confidence, (char**)NULL, 10);

    for(int i = 0; new->transcript[i]; i++){
        new->transcript[i] = tolower(new->transcript[i]);
    }

    if(confidence > 80){
        add_to_hist(current->history,new->transcript);
        token = sh_split_line(new->transcript);
        char *linked = searchLink(new->transcript);
        if(linked == NULL)
        {
            token = sh_split_line(new->transcript);
            printf(GREEN"Running : %s"RESET_COLOR"\n", new->transcript);   
        }
        else
        {
            token = sh_split_line(linked);
            printf(GREEN"Running : %s"RESET_COLOR"\n", linked);
        }
        sh_execute(&token);
        free(token);
    }
    else{
        char* res = searchLink(new->transcript);
        if(res != NULL)
        {
            printf(GREEN"Running : %s"RESET_COLOR"\n", res);
            add_to_hist(current->history,res);
            token = sh_split_line(res);
            sh_execute(&token);
            free(token);
        }
        else{
            learn(new->transcript);
        }
    }

    free(new->transcript);
    free(new->confidence);
    free(new);
    
    return 1;
}

int sh_type(char** args){
    int argc = 0;
    char found;
    int err;

    char command[BUFFER_SIZE];

    for(size_t i =0; *(args+i) != NULL; i++){
        argc++;
    }
    if (argc == 1){
        printf("\n");
        return 1;
    }
    else{
        for(size_t i = 1; *(args+i) != NULL; i++){
            found = 0;
            int j = 0;
            for (j = 0; j < current->aliases->nb_alias; j++){
                if (strcmp(*(args+i),current->aliases->aliases[j]->alias) == 0){
                    found = 1;
                    printf("%s ls is an alias for",*(args+i));
                    for(int g = 0; g < current->aliases->aliases[j]->cmd_size; g++){
                        printf(" %s", current->aliases->aliases[j]->cmd[g]);
                    }
                    printf("\n");
                    break;
                }
            }
            if (!found){
                for(j = 0; j < sh_nb_builtins; j++){
                    if (strcmp(*(args+i),list_builtins[j]) == 0){
                        found = 1;
                        printf("%s is a shell builtin\n",*(args+i));
                        break;
                    }
                }
            }
            
            if (!found){
                err = snprintf(command,BUFFER_SIZE,"type %s", *(args+i));
                if (err > 0 && err < BUFFER_SIZE){
                    system(command);
                }
                else{
                    continue;
                }
            }
        } 
    }
    return 1;
}