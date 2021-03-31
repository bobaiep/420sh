#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef PARSER_H
#define PARSER_H

char* sh_read_line(void);

char** sh_split_line(char *line);

#endif