CC=gcc
CFLAGS=-Wall

all: src/Deprecated/brainfuck.c src/brainfuck.v.c
	$(CC) $(CFLAGS) src/Deprecated/brainfuck.c -o bfc
	$(CC) $(CFLAGS) src/brainfuck.v.c -o bfcv
vector: src/brainfuck.v.c
	$(CC) $(CFLAGS) src/brainfuck.v.c -o bfcv
	
deprecated: src/Deprecated/brainfuck.c
	$(CC) $(CFLAGS) src/brainfuck.c -o bfc
	
