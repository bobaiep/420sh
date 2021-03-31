#420sh's Makefile
#Author : marius.andre

CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -g

SRC= src/main.c src/builtins/builtins.c src/cmd/cmd.c src/exec/exec.c src/parser/parser.c
OBJ= $(SRC:.c=.o)
DEP= $(SRC:.c=.d)

all: main 

main: $(OBJ)

clean:
	$(RM) $(OBJ) $(OBJ_TESTS) $(DEP) $(DEP_TESTS) main && clear
# END