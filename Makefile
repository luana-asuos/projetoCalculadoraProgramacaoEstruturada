CC=gcc
CFLAGS=-Wall -Wextra -std=c99

all: calc

calc: src/main.c src/calc.c src/bigint.c src/io.c src/custom_op.c
$(CC) $(CFLAGS) -o calc src/main.c src/calc.c src/bigint.c src/io.c src/custom_op.c

clean:
rm -f calc