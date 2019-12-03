# Brainfuck Extended
An extended version of the Brainf**k language that adds a small amount of added Features

---
# BrainFuck
### Existing Features

|Operand|Action|
|:-:|:-|
|+|Increases value of pointer in current cell by 1|
|-|Decreases value of pointer in current cell by 1|
|[|Opens loop|
|]|Closes loop if current cell is equal to zero. Otherwise loops back to corresponding *]*|
|>|Increment the pointer to the next cell|
|<|Decrement the pointer to the prev cell|
|.|Print ASCII value of cell|
|,|Get single character from STDIN|

### Added Features

|Operand|Action|
|:-:|:-|
|{|[Open Scratch Memory](#scratch-memory)
|}|[Close Scratch Memory](#scratch-memory)
|@|[Call File](#file-including)
|!|[Return From File](#file-including)
|#|[Print Number](#print-number)
|^|[Return to start](#instruction-pointer-manipulation)
|~|[Go to end](#instruction-pointer-manipulation)
|\||[Trim program](#instruction-pointer-manipulation)
|\\*|[Open Comment](#Comments)
\*\\ |[Close Comment](#Comments)

---
### Example Program

**[ExamplePrograms/Print_0.b](ExamplePrograms/Print_0.b)**
```
[-]>[-]<
+++ +++ 
[> ++++ ++++ < -]>
[-<+>]<
.
```
**Expected Output**
```
0
```


**Line-By-Line Explanation**<br>
Line 1: Sets cell to zero. Not necessary in a clean, new program, but good practice anyways.  
Line 2: Adds the value 6 to current cell.  
Line 3: Moves to next cell, adds 8 to it, moves back to current cell and subtracts 1. Effectively, multiplies 6 by 8.  
Line 4: Copies content of the next cell to the current one.  
Line 5: Prints the content of the cell. Our cell holds the value *48*, so it will print *0*, as that is the ascii code for 48.  

---

# Brainfuck Extended
---
## Scratch Memory<br>
### Description
&nbsp;&nbsp;&nbsp;&nbsp;Added special _scratch memory_, which basically acts as a disposible area where you can do simple calculations. It can only have one value inputed: that of the cell in which it was called. Once called with the _{_ symbol, anything within its boundaries has no effect on the parent program. Close it off with the _}_ symbol. It returns to its calling cell the value of the cell on which it was ended. <br>
&nbsp;&nbsp;&nbsp;&nbsp;An unlimited number of scratch memory can be open at once, meaning that you can open scratch memory inside of scratch memory and have no issues. Only one parameter can be passed to the memory, however. I may or may not work on adding multiple parameters, as it would not be hard. Only the brainfuck.v.c interpreter has unlimited scratch memory as I have decided to deprecate the brainfuck.c interpreter. 

---
## Comments <br>
### Description
&nbsp;&nbsp;&nbsp;&nbsp;C-Style comment blocks can be opened using _/*_ and closed using _*/_. Comments opened using _//_ and only lasting one line do not exist. 

---
## Instruction Pointer Manipulation<br>
### Description
&nbsp;&nbsp;&nbsp;&nbsp;With the _^_ command, the instruction pointer is returned to the start of the program. With the _~_ command, the instruction pointer is sent to the last cell that has been used in the program, even if it is zero. The trim command can be called using the _|_ operator. It frees all cells which contain the value passed to it, or all that are set to zero past the last non-zero cell. 

### Example
```
++++++
[
	>>>>++++ ++++ /* add 8 to some far off cell... */
	^ /* Return to the first cell... */
	- /* Subtract 1 */
]
>>>>

```

---
## Print Number
### Description
<p>&nbsp;&nbsp;&nbsp;&nbsp;The <i>#</i> command prints the number in the current cell instead of interpreting it as an ASCII code.</p>

### Example

```
/* This prints the number 0 */
++++++[>++++++++<-]>.[-]<[-]

/* This also prints the number 0... */
[-]#
```

---
## File Including
### Description
&nbsp;&nbsp;&nbsp;&nbsp;The _@_ and _!_ operators can be used to open a brainfuck file and run it, and to close said file, respectively. The called file is run isolated from the rest of the program's memory. When calling the file, the cell in which it was called indicates the number of parameters to pass to the included file. Parameters are read starting from the cell after the file was called. Likewise, when exiting an include with _!_, the number of arguments to return is stored in the current cell, and the arguments themselves are in the proceeding cells. Multiple files can be included recursively. In this manner, it is possible to find yourself in an infinite loop, so don't. The path for the file to include must be relative to the executable, but I am working on making it relative to the file it was called from. 

### Example
**EX.b**
```
[-] /* No arguments passed to file */
@Example-Include.b@ /* Call File */
[>+++ +++<-]
```

**Example-Include.b**
```
/* Print the character 0 */
+++ +++
[>++++ ++++<-]
>[<+>-]<
.
[-]
+ /* return 1 parameter */
>++++ ++++< /* Param 1 = 8 */
! /* Return to calling file */
```

---
# [RETURN TO README](README.md)
