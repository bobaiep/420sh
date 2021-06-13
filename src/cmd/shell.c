#include "shell.h"
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

shell* current;

#define PROMPT_SIZE 512 + 4096
#define HOST_NAME_MAX 64
#define USER_NAME_MAX 32

#define RESET_COLOR "\e[m"
#define GREEN "\e[32m"
#define BLUE "\e[36m" 
#define RED "\e[31m"

int gethostname(char *name, size_t len);

void shell_init(int pipe_fds){
    if ((current = malloc(sizeof(shell))) == NULL){
        errx(EXIT_FAILURE,"Error while malloc");
    }

    current->name = "420sh";

    current->pipe_fds = pipe_fds;

    current->history = history_init();

    current->aliases = aliases_init();

    current->color = 0;

    sh_pwd(NULL);
	strcpy(current->oldpwd,current->pwd);
    strcpy(current->exe_pwd,current->pwd);

    current->prompt = malloc(PROMPT_SIZE * sizeof(char));

    getlogin_r(current->username,USER_NAME_MAX + 1);
    gethostname(current->hostname, HOST_NAME_MAX + 1);
}

void shell_destroy(void){
    hist_destroy(current->history);
    aliases_destroy(current->aliases);
    free(current->prompt);
    free(current);
}

void set_prompt(void){
    switch (current->color)
    {
        case 0:
            snprintf(current->prompt,PROMPT_SIZE,RED"[%s@%s"RESET_COLOR" %s"RED"]$"RESET_COLOR, current->username, current->hostname, current->pwd);
            break;
        case 1:
            snprintf(current->prompt,PROMPT_SIZE,BLUE"[%s@%s"RESET_COLOR" %s"BLUE"]$"RESET_COLOR, current->username, current->hostname, current->pwd);
            break;
        case 2:
            snprintf(current->prompt,PROMPT_SIZE,GREEN"[%s@%s"RESET_COLOR" %s"GREEN"]$"RESET_COLOR, current->username, current->hostname, current->pwd);
            break;
        default:
            snprintf(current->prompt,PROMPT_SIZE,RED"[%s@%s"RESET_COLOR" %s"RED"]$"RESET_COLOR, current->username, current->hostname, current->pwd);
            break;
    }
}