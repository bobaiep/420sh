#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <err.h>

typedef struct shell{
    char* name;
    char* oldpwd;
    char* pwd;
} shell;

extern shell* current;

void shell_init(void);

void shell_destroy(void);

#endif