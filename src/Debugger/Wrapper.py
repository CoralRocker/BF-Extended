#!/bin/python
import BFUTIL
import BRAINFUCK
import sys

bf = BRAINFUCK.brainfuck(sys.argv[1])

while 1:
    b = bf.step()
    if not b:
        break
