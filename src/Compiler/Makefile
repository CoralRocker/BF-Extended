CC=gcc
CFLAGS=-Wall
BF=../../ExamplePrograms/Breakpoints.b

compiler: ./compiler.c
	$(CC) $(CFLAGS) compiler.c -o Compiler.o

test: compiler
	./Compiler.o $(BF)
	$(CC) $(CFLAGS) bf.c -O0 -o bf.o

clean:
	rm Compiler.o bf.o bf.c
