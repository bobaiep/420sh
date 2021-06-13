#ifndef CMD_H
#define CMD_H

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

typedef struct History {
    char** lines;
    int size;
    int start;
} History;

typedef struct Alias {
    char* alias;
    char** cmd;
    int cmd_size;
} Alias;

typedef struct AliasArray {
    Alias** aliases;
    int nb_alias;
    int size;
} AliasArray;


//Print the usage for the shell.
void print_main_help(void);

int file_exist(const char *filename);

int isNumeric(const char *str);

History* history_init();

void add_to_hist(History* hist, char* command);

void print_hist(History* hist);

void hist_destroy(History* hist);

AliasArray* aliases_init(void);

void add_alias(AliasArray* aliases, Alias* alias);

void print_aliases(AliasArray* aliases,char* alias);

void aliases_destroy(AliasArray* aliases);

#endif