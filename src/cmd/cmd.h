#ifndef CMD_H
#define CMD_H

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

typedef struct History {
  char** lines;
  int max_size;
  int size;
  int begin;
} History;

//Print the usage for the shell.
void print_main_help(void);

int file_exist(const char *filename);

#endif