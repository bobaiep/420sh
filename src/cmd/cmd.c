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