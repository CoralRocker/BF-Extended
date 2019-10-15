# Brainfuck Extended

## Repository Directory
**ExamplePrograms/:** Example programs of Brainfuck-Extended and a how-to file about BF-Extended are in here. <br>
**src/:** The source code for the BF-Extended interpreter resides here. It is written in C and works correctly out-of-the-box on all Unix/Linux systems with the standard GNU C library.<br>

## Interpreters

### brainfuck.c
&nbsp;&nbsp;&nbsp;&nbsp; The standard BF-Extended interpreter. The memory for this interpreter is statically allocated. Therefore, BFE programs run using this interpreter are limited to 16,384 cells of data, and  4096 loops open at once. Data is allocated at the start of the program using malloc and is appropriately freed at the end of the program. Memory leaks are only possible if BFE code is badly written and causes the interpreter to crash. Am working on a system to check grammatical correctness of programs, so that memory leaks become avoidable. Allocates 150Kb of memory in RAM. Am working on allowing the user to set loopsize and amount of memory. 

### brainfuck.v.c
&nbsp;&nbsp;&nbsp;&nbsp; The enhanced BF-Extended interpreter. The memory for this interpreter is dynamically allocated by my [Vector](http://.github.com/CoralRocker/C-Vector-Generic) class, allowing for much smaller space in RAM at the cost of slower execution speeds (the difference in speeds is insignificant for most programs). The maximum amount of cells and loops available on this interpreter is 2^64.
