#ifndef PARSER_H
#define PARSER_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../cmd/shell.h"

char* sh_read_line(FILE* f);

char** sh_split_line(char *line);

#endif