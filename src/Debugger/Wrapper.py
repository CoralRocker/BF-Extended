#!/bin/python
import BFUTIL
import BRAINFUCK
import sys

USAGE = """Usage:
    N: step forward in program
    ?: Show help menu
    C: Show current memory number and value
    M: Show current Memory array"""


bf = BRAINFUCK.brainfuck(input("Enter where the BF file is: "))

while 1:
    b = bf.step()
    if not b:
        print("EOF: Exiting...")
        break

    resp = input("Press N to continue, or ? for options: ")[0].lower()
    if resp == "n":
        continue
    elif resp == 'c':
        print(f"Memory Position: {b.mem.BFArrPos} :: {b.mem.BFArray[b.mem.BFArrPos]}")
    elif resp == "?":
        print(USAGE)
