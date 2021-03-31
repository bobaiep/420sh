#ifndef PARSER_H
#define PARSER_H

#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* sh_read_line(void);

char** sh_split_line(char *line);

#endif