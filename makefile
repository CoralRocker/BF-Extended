CC=gcc
CFLAGS=-Wall

all: src/Interpreter/brainfuck.c src/Interpreter/brainfuck-env.c
	$(CC) $(CFLAGS) src/Interpreter/brainfuck.c -o bfe-int
	$(CC) $(CFLAGS) src/Interpreter/brainfuck-env.c -o bfe-env

vector: src/Interpreter/brainfuck.c
	$(CC) $(CFLAGS) src/Interpreter/brainfuck.c -o bfe-int
	
env: src/Interpreter/brainfuck-env.c
	$(CC) $(CFLAGS) src/Interpreter/brainfuck-env.c -o bfe-env

deprecated: src/Interpreter/Deprecated/brainfuck.c
	$(CC) $(CFLAGS) src/Interpreter/Deprecated/brainfuck.c -o bfe-int-dep

debug: src/Interpreter/brainfuck-debuf.c
	$(CC) $(CFLAGS) src/Interpreter/brainfuck-debuf.c -o bfe-dbg
