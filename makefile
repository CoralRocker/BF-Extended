CC=gcc
CFLAGS=-Wall

all: src/Debugger/Wrapper.py src/Interpreter/brainfuck.c src/Interpreter/brainfuck-env.c src/Interpreter/BRAINFUCK.py
	rm bfe-*
	$(CC) $(CFLAGS) src/Interpreter/brainfuck.c -o bfe-int
	$(CC) $(CFLAGS) src/Interpreter/brainfuck-env.c -o bfe-env
	ln -s src/Interpreter/BRAINFUCK.py bfe-py
	ln -s src/Debugger/Wrapper.py bfe-dbg

vector: src/Interpreter/brainfuck.c
	$(CC) $(CFLAGS) src/Interpreter/brainfuck.c -o bfe-int
	
env: src/Interpreter/brainfuck-env.c
	$(CC) $(CFLAGS) src/Interpreter/brainfuck-env.c -o bfe-env

python: src/Interpreter/BRAINFUCK.py
	ln -s src/Interpreter/BRAINFUCK.py bfe-py

debug: src/Debugger/Wrapper.py
	ln -s src/Debugger/Wrapper.py bfe-dbg

deprecated: src/Interpreter/Deprecated/brainfuck.c
	$(CC) $(CFLAGS) src/Interpreter/Deprecated/brainfuck.c -o bfe-int-dep

