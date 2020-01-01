# Brainfuck Extended

## Interpreters

### [src/Interpreter/brainfuck.c](src/Interpreter/brainfuck.c)
&nbsp;&nbsp;&nbsp;&nbsp; The enhanced BF-Extended interpreter. The memory for this interpreter is dynamically allocated by my [Vector](http://github.com/CoralRocker/C-Vector-Generic) class, allowing for much smaller space in RAM at the cost of slower execution speeds (the difference in speeds is insignificant for most programs). The maximum amount of cells and loops available on this interpreter is either 2<sup>64</sup> cells and loops, or the maximum amount of memory, whichever comes first. Memory leaks are only possible if BFE code is badly written and causes the interpreter to crash. Am working on a system to check grammatical correctness of programs, so that memory leaks become avoidable.

### [src/Interpreter/brainfuck-env.c](src/Interpreter/brainfuck-env.c)
&nbsp;&nbsp;&nbsp;&nbsp; The same interpreter as src/Interpreter/brainfuck.c, except that it uses a python-like dynamic input system where input from standard input is interpreted as it is written. Does not have comments because it does not make sense to have them. entering ? or h will show a small usage guide for brainfuck. entering q or Q will quit out of the interpreter. Unless an interrupt is sent, the program will always end without memory leaks.

### [src/Interpreter/BRAAINFUCK.py](src/Interpreter/BRAINFUCK.py)
&nbsp;&nbsp;&nbsp;&nbsp; The same interpreter as src/Interpreter/brainfuck.c, but written in python. It is slower, and just exists because it is the base for the python debugger. There's no real reason to use it as it consumes significantly more memory and is slower, but whatever.

### [src/Interpreter/Deprecated/brainfuck.c](src/Interpreter/Deprecated/brainfuck.c) -- DEPRECATED!
&nbsp;&nbsp;&nbsp;&nbsp; The memory for this interpreter is statically allocated. Therefore, BFE programs run using this interpreter are limited to 16,384 cells of data, and  4096 loops open at once. Data is allocated at the start of the program using malloc and is appropriately freed at the end of the program. Memory leaks are only possible if BFE code is badly written and causes the interpreter to crash. Am working on a system to check grammatical correctness of programs, so that memory leaks become avoidable. Allocates 150Kb of memory in RAM. Am working on allowing the user to set loopsize and amount of memory. 
&nbsp;&nbsp;&nbsp;&nbsp; This interpreter is deprecated because it is much harder to code for it than the brainfuck.v.c interpreter, and its speed advantage over the vector-based interpreter is negligible at best. It works, but does not have the same features as brainfuck.v.c. It will not be updated further. It does not have unlimited amounts of scratch memory like brainfuck.v.c does. In short, don't use this.

## Compiler
### [src/Compiler/](src/Compiler/)
&nbsp;&nbsp;&nbsp;&nbsp;Still working out the way I want this to work. Therefore, nothing actually works in here yet. Hence, no file, in C or otherwise. It will compile directly to ASM when its done, but there might be a version which compiles to C. I don't know yet. No compiler code is written yet

## Debugger
### [src/Debugger/](src/Debugger/)
&nbsp;&nbsp;&nbsp;&nbsp; The Python debugger. It is not done yet, but it does function the same as the Python interpreter. It will be written in NCurses, and, if I find the time, possibly in TKinter too. Allows user to step through their program.

## [Makefile](makefile)

| Make target | input file(s) | Output Executable(s) |
|:-:|:-|:-|
|all|[src/Interpreter/brainfuck-env.c](src/Interpreter/brainfuck-env.c); [src/Interpreter/brainfuck.c](src/Interpreter/brainfuck.c); [src/Interpreter/BRAINFUCK.py](src/Interpreter/BRAINFUCK.py)|bfe-int; bfe-env; bfe-py|
|vector|[src/Interpreter/brainfuck.c](src/Interpreter/brainfuck.c)|bfe-int|
|env|[src/Interpreter/brainfuck-env.c](src/Interpreter/brainfuck-env.c)|bfe-env|
|python|[src/Interpreter/BRAINFUCK.py](src/Interpreter/BRAINFUCK.py)|bfe-py|
|deprecated|[src/Interpreter/Deprecated/brainfuck.c](src/Interpreter/Deprecated/brainfuck.c)|bfe-int-dep|

# [RETURN TO README](/README.md)
