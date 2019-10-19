CC=gcc
CFLAGS=-Wall

all: src/brainfuck.c src/brainfuck-env.c
	$(CC) $(CFLAGS) src/brainfuck.c -o bfe-int
	$(CC) $(CFLAGS) src/brainfuck-env.c -o bfe-env

vector: src/brainfuck.v.c
	$(CC) $(CFLAGS) src/brainfuck.v.c -o bfe-int
	
env: src/brainfuck-env.c
	$(CC) $(CFLAGS) src/brainfuck-env.c -o bfe-env

deprecated: src/Deprecated/brainfuck.c
	$(CC) $(CFLAGS) src/brainfuck.c -o bfe-int-dep
	
