# BF-Extended
An extended version of the Brainf**k language that adds a small amount of added Features

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

### Example Program

**Print_0.bf**
```
[-]
+++ +++ 
[> ++++ ++++ < -]
>[-<+>]<
.
```

**Line-By-Line Explanation**
Line 1: Sets cell to zero. Not necessary in a clean, new program, but good practice anyways.  
Line 2: Adds the value 6 to current cell.  
Line 3: Moves to next cell, adds 8 to it, moves back to current cell and subtracts 1. Effectively, multiplies 6 by 8.  
Line 4: Copies content of the next cell to the current one.  
Line 5: Prints the content of the cell. Our cell holds the value *48*, so it will print *0*, as that is the ascii code for 48.  
