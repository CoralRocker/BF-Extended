# Brainfuck Extended
## Example Programs
### [Breakpoints.b](Breakpoints.b)
&nbsp;&nbsp;&nbsp;&nbsp;This program's purpose is to test whether or not a brainfuck interpreter/compiler has any bugs or errors. Its is commented and does not use any Brainfuck-Extended features such as scratch memory or comments. It tests to make sure that loops work correctly, that the cell pointer cannot go behind the first cell, and that negative numbers don't exist.

#### Expected output:
```
00
0
0
```
### [Breakpoints-Extended.b](Breakpoints-Extended.b)
&nbsp;&nbsp;&nbsp;&nbsp;This program's purpose is to test the capabilities of the new brainfuck interpreter.

#### Expected output:
```
00
```
#### Bad outputs:
**Comments Not Working?**
```
100
```
Anything other than two characters being printed means comments didn't work...<br>
**Scratch Memory Not Working?**
```
50
```
**Return-to-0 Operator Not Working?**
```
01
```

### [CharRead.b](CharRead.b)
&nbsp;&nbsp;&nbsp;&nbsp;Reads input from the terminal until a newline is entered. Then, prints it back out.

### [HugeSize.b](HugeSize.b)
&nbsp;&nbsp;&nbsp;&nbsp;Not yet written. Will check what size of integers work. I.E. are numbers 8, 16, 32, or 64  bit?

### [Modulus.b](Modulus.b)
&nbsp;&nbsp;&nbsp;&nbsp;Runs the modulus of 17 and 5. Returns ```2```. It's a proof-of-concept and can be loaded with any numbers in the first and second cells.

### [Powers.b](Powers.b)
&nbsp;&nbsp;&nbsp;&nbsp;Raises 2 to the power of 24.

### [Print_0.b](Print_0.b)

### [Scratch.b](Scratch.b)

### [SubLong.b](SubLong.b)

# [RETURN TO README](/README.md)
