CC=gcc
CFLAGS=-Wall
BF=../../ExamplePrograms/Breakpoints.b

compiler: ./compiler.c
	$(CC) $(CFLAGS) compiler.c -o Compiler

test: compiler
	./Compiler $(BF)
	$(CC) $(CFLAGS) bf.c -O0 -o bf.o

clean:
	rm Compiler bf.o bf.c
