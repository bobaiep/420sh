#420sh's Makefile
#Author : marius.andre

CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -O3 `pkg-config --cflags gtk+-3.0`
LDFLAGS= -lpthread -lm -ldl `pkg-config --libs gtk+-3.0` -rdynamic
LIBS= miniaudio 

SRC= main.c src/builtins/builtins.c src/gui/gui.c src/cmd/cmd.c src/exec/exec.c src/parser/parser.c src/cmd/shell.c src/voice_recognition/voice_recognition.c src/voice_recognition/library/miniaudio.c
OBJ= $(SRC:.c=.o)
DEP= $(SRC:.c=.d)

all: main

main: $(OBJ)

clean:
	rm -rf src/voice_recognition/toSend.wav  src/voice_recognition/toSend src/voice_recognition/sync-request.json src/voice_recognition/response.json
	$(RM) $(OBJ) $(OBJ_TESTS) $(DEP) $(DEP_TESTS) main && clear
# END