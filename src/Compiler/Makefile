CC=gcc
CFLAGS=-Wall
BF=../../ExamplePrograms/Breakpoints.b

compiler: ./compiler.c
	$(CC) $(CFLAGS) compiler.c -o Compiler

test: compiler
	./Compiler $(BF)
	$(CC) $(CFLAGS) bf.c -o bf.o

