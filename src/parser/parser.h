#ifndef PARSER_H
#define PARSER_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* sh_read_line(void);

char** sh_split_line(char *line);

#endif