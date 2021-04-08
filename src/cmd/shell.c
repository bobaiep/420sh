#include "shell.h"

shell* current;

void shell_init(void){
    if ((current = malloc(sizeof(shell))) == NULL){
        errx(EXIT_FAILURE,"Error while malloc");
    }

    current->name = "420sh";
}

void shell_destroy(void){
    free(current);
}