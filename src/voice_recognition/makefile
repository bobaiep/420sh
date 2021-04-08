CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS = 
LIBS = gstreamer-1.0

SRC = echo.c echo_test.c single_server.c loop_server.c fork_server.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: voice_recognition


-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} 

# END