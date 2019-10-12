# BF-Extended
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

---
### Example Program

**ExamplePrograms/Print_0.b**
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
&nbsp;&nbsp;&nbsp;&nbsp;Currently, only one _scratch memory_ register can be open at any given instance. This means that _scratch memory_ cannot be placed inside other _scratch memory_ blocks. I am working on a solution for this however. Only one parameter can be passed to the _scratch memory_ at once, and only one cell can be returned from it. This will not change. 
### Example Program
**ExamplePrograms/Scratch.b**
```
[-]>[-]>[-]<
+++ > ++ <
{
	[->+++<]
	>
}
<+++ +++ 
[> ++++ ++++ > ++++ ++++ <<-]
>.[-]++++++++++.>.
```
**Expected Output**
```
9
2
```

### Line-By-Line Explanation<br>
**Line 1:** Clears cells 1 and 2 in the program.<br>
**Line 2:** Sets cell 1 to 3 and cell 2 to 2.<br>
**Line 3:** Opens the scratch memory on cell 1.<br>
**Line 4:** The value of cell 1 in the parent program is 3. Thus, the value of cell 0 in the scratch memory is also 3. Multiplies cell 0 by 3 and places the output in cell 1.<br>
**Line 5:** Moves pointer to cell 1.<br>
**Line 6:** Exits scratch memory. This returns the value of 9 to cell 1, because the value of the cell in which we exited was 9.<br>
**Line 7:** Sets cell 0 to 6<br>
**Line 8:** adds 48 (ASCII `0`) to cell 1 and 2.<br>
**Line 9:** Prints the value of cell 1, prints a newline, prints cell 2.

---
