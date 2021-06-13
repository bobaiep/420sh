#ifndef EXEC_H
#define EXEC_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../builtins/builtins.h"
#include "../parser/parser.h"
#include "../cmd/shell.h"
#include "../cmd/cmd.h"

int sh_launch(char **args);

int sh_execute(char ***args);

void main_loop();

#endif