#ifndef BUILTINS_H
#define BUILTINS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef int (*pointer_function) (char**);

/*Change directory in the shell.
args[0] is "cd", args[1] is the directory, 
If no directory is specified, change the current directory to HOME*/
int sh_cd(char** args);

//Always returns 0, to terminate execution.
int sh_exit(char** args);

extern const char* list_builtins[2];

extern const int sh_nb_builtins;

extern pointer_function builtins_func[2];

#endif