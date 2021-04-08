#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <err.h>

typedef struct shell{
    char* name;
    char oldpwd[4096];
    char pwd[4096];
} shell;

extern shell* current;

void shell_init(void);

void shell_destroy(void);

#endif