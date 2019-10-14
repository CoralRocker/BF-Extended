CC=gcc
CFLAGS=-Wall

all: src/brainfuck.c src/brainfuck.v.c
	$(CC) $(CFLAGS) src/brainfuck.c -o bfc
	$(CC) $(CFLAGS) src/brainfuck.v.c -o bfcv

