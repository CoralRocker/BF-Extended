CC=gcc
CFLAGS=-Wall

all: src/Interpreter/brainfuck.c src/Interpreter/brainfuck-env.c src/Interpreter/BRAINFUCK.py
	$(CC) $(CFLAGS) src/Interpreter/brainfuck.c -o bfe-int
	$(CC) $(CFLAGS) src/Interpreter/brainfuck-env.c -o bfe-env
	ln -s src/Interpreter/BRAINFUCK.py bfe-py

vector: src/Interpreter/brainfuck.c
	$(CC) $(CFLAGS) src/Interpreter/brainfuck.c -o bfe-int
	
env: src/Interpreter/brainfuck-env.c
	$(CC) $(CFLAGS) src/Interpreter/brainfuck-env.c -o bfe-env

python: src/Interpreter/BRAINFUCK.py
	ln -s src/Interpreter/BRAINFUCK.py bfe-py

deprecated: src/Interpreter/Deprecated/brainfuck.c
	$(CC) $(CFLAGS) src/Interpreter/Deprecated/brainfuck.c -o bfe-int-dep

