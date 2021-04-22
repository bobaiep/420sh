#include "cmd.h"

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