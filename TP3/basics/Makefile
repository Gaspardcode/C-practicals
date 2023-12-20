# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -fsanitize=address
LDFLAGS = -fsanitize=address
LDLIBS =

SRC = test.c basics.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

test: ${OBJ}

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} test

# END
