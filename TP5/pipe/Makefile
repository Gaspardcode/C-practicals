CC = gcc
CFLAGS = -Wall -Wextra

EXE = chg_case manager

all:$(EXE)

$(foreach f, $(EXE), $(eval $(f):))

.PHONY: clean

clean:
	${RM} $(EXE)

