#!/bin/python
import BFUTIL
import BRAINFUCK
import sys

bf = BRAINFUCK.brainfuck(sys.argv[1])

while 1:
    b = bf.step()
    if not b:
        print("EOF: Exiting...")
        break

    resp = input("Press N to continue, or ? for options: ")[0].lower()
    if resp == "n":
        continue
    elif resp == "?":
        print("TODO")
