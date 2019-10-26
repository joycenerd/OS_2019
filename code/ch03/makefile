SHELL=/bin/bash
CC=gcc
CFLAGS=-pthread -lrt
SRC=$(wildcard *.c)
EXE=$(patsubst %.c,%,$(SRC))

all:$(EXE)

%:	%.c
	${CC} $@.c ${CFLAGS} -o $@

clean:
	rm ${EXE}