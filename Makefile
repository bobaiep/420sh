#420sh's Makefile
#Author : marius.andre

CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -O3 -lpthread -lm -ldl
LDFLAGS= 
LIBS= miniaudio

SRC= main.c src/builtins/builtins.c src/cmd/cmd.c src/exec/exec.c src/parser/parser.c src/cmd/shell.c src/voice_recognition/voice_recognition.c
OBJ= $(SRC:.c=.o)
DEP= $(SRC:.c=.d)

all: main

main: $(OBJ)

clean:
	$(RM) $(OBJ) $(OBJ_TESTS) $(DEP) $(DEP_TESTS) main && clear
# END