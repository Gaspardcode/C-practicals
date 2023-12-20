# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra -fsanitize=address
LDFLAGS = -fsanitize=address
LDLIBS =

SRC = test.c replace.c
OBJ = ${SRC:.c=.o}

test: ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} test
 
