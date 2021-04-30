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

//Print the usage for the shell.
void print_main_help(void);

int file_exist(const char *filename);

History* history_init();

void add_to_hist(History* hist, char* command);

void print_hist(History* hist);

void hist_destroy(History* hist);

#endif