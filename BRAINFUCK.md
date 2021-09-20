# Brainf**k Extended
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
|\\*|[Open Comment](#comments-)
\*\\ |[Close Comment](#comments-)
|\/\/|[Single-Line Comment](#comments-)
|d|Prints Debug Information|

---

# Brainf**k Extended
---
## Scratch Memory<br>
### Description
&nbsp;&nbsp;&nbsp;&nbsp;Added special _scratch memory_, which basically acts as a disposible area where you can do simple calculations. It can only have one value inputed: that of the cell in which it was called. Once called with the _{_ symbol, anything within its boundaries has no effect on the parent program. Close it off with the _}_ symbol. It returns to its calling cell the value of the cell on which it was ended. <br>
&nbsp;&nbsp;&nbsp;&nbsp;An unlimited number of scratch memory can be open at once, meaning that you can open scratch memory inside of scratch memory and have no issues. Only one parameter can be passed to the memory. Only the brainf**k.v.c interpreter has unlimited scratch memory as I have decided to deprecate the brainf**k.c interpreter. The compiler has unlimited memory, just like the interpreter.

---
## Comments <br>
### Description
&nbsp;&nbsp;&nbsp;&nbsp;C-Style comment blocks can be opened using _/*_ and closed using _*/_. Comments opened using _//_ and only lasting one line also work.

---
## Instruction Pointer Manipulation<br>
### Description
&nbsp;&nbsp;&nbsp;&nbsp;With the _^_ command, the instruction pointer is returned to the start of the program. With the _~_ command, the instruction pointer is sent to the last cell that has been used in the program, even if it is zero. The trim command can be called using the _|_ operator. It frees all cells which contain the value passed to it, or all that are set to zero past the last non-zero cell. 

### Example
```
++++++>>>>>>>>>>>^[~++++++++^-]~[^+~-]^.>[-]|
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
&nbsp;&nbsp;&nbsp;&nbsp;The _@_ and _!_ operators can be used to open a brainf**k file and run it, and to close said file, respectively. The called file is run isolated from the rest of the program's memory. When calling the file, the cell in which it was called indicates the number of parameters to pass to the included file. Parameters are read starting from the cell after the file was called. Likewise, when exiting an include with _!_, the number of arguments to return is stored in the current cell, and the arguments themselves are in the proceeding cells. Multiple files can be included recursively. In this manner, it is possible to find yourself in an infinite loop, so be careful. Files are included relative to the calling file. For example, if the parent file is in a directory called "bar/foo/", and the interpreter and include file are in the directory "bar/", the parent file should call `@../my_file.b@`.  
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
