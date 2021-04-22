#ifndef CMD_H
#define CMD_H

#include <stdio.h>
#include <sys/stat.h>

//Print the usage for the shell.
void print_main_help(void);

int file_exist(const char *filename);

#endif