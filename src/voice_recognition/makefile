CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -lpthread -ldl -lm
LDFLAGS =
LDLIBS = 
LIBS = miniaudio 

SRC = 
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: record


-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} 

# END