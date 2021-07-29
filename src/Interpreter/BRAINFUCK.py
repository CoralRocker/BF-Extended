#!/bin/python
import sys

def modInsert(l, index, value):
    if index < len(l):
        l[index] = value
    else:
        l.append(value)
    return value

class Memory:
    def __init__(self, BFA=[0], BFAP=0, BFLP=[], BFLPP=-1):
        self.BFArray = BFA
        self.BFArrPos = BFAP
        self.BFLpArr = BFLP
        self.BFLpPos = BFLPP

    def len(self, arr="BF"):
        if arr == "BF":
            return len(self.BFArray)
        elif arr == "LP":
            return len(self.BFLpArr)
        else:
            print(f"Memory.len(arr) requires a valid argument.\nArgument supplied: {arr}")
            return -1
    def getCur(self, arr="BF"):
        if arr == "BF":
            return self.BFArray[self.BFArrPos]
        elif arr == "LP":
            return self.BFLpArr[self.BFLpPos]
        else:
            print(f"Memory.getCur(arr) requires a valid argument.\nArgument supplied: {arr}")
            return -1
    def get(self, index, arr="BF"):
        if arr == "BF":
            return self.BFArray[index]
        elif arr == "LP":
            return self.BFLpArr[index]
        else:
            print(f"Memory.get(index, arr) requires a valid argument.\nArguments supplied: {index}, {arr}")
            return -1

class CURPLACE:
    def __init__(self, memarr, farrs, fpos):
        self.mem = memarr[len(memarr)-1]
        self.memarr = memarr
        self.curmem = memarr[len(memarr)-1]
        self.fname = farrs[1]
        self.farr = farrs[0]
        self.fpos = fpos
        self.comment = False

class brainfuck:
    
    def __init__(self, fileName):
        self.fileArray = []
        self.fnameArray = [fileName]
        self.fileArray.append(open(self.fnameArray[0], "r"))
        self.MemoryArray = [Memory()]
        self.curMem = self.MemoryArray[0]
        
        self.f = self.fileArray[0]
        
    def step(self):
        c = self.f.read(1)
        if not c:
            return 0
        if c == '/':
            cur = self.f.tell()
            if self.f.read(1) == '*':
                self.comment = True
            else:
                self.f.seek(cur)
        elif c == '*':
            cur = self.f.tell()
            if self.f.read(1) == '/':
                self.comment = False
            else:
                self.f.seek(cur)
        elif not self.comment:
            if c == '+':
                self.curMem.BFArray[self.curMem.BFArrPos] += 1
            elif c == '-':
                self.curMem.BFArray[self.curMem.BFArrPos] -= 1
                if self.curMem.BFArray[self.curMem.BFArrPos] < 0:
                    self.curMem.BFArray[self.curMem.BFArrPos] = 0
            elif c == '>':
                self.curMem.BFArrPos += 1
                if len(self.curMem.BFArray) >= self.curMem.BFArrPos:
                    self.curMem.BFArray.append(0)
            elif c == '<':
                self.curMem.BFArrPos -= 1
                if self.curMem.BFArrPos < 0:
                    self.curMem.BFArrPos = 0
            elif c == '[':
                if self.curMem.BFArray[self.curMem.BFArrPos] == 0:
                    while c != ']':
                        c = self.f.read(1)
                else:
                    self.curMem.BFLpArr.append(self.f.tell())
                    self.curMem.BFLpPos += 1
            elif c == ']':
                if self.curMem.BFArray[self.curMem.BFArrPos] != 0:
                    self.f.seek(self.curMem.BFLpArr[self.curMem.BFLpPos])
                else:
                    self.curMem.BFLpArr.pop()
                    self.curMem.BFLpPos -= 1
            elif c == '.':
                print("%c" % self.curMem.BFArray[self.curMem.BFArrPos], end='')
            elif c == ',':
                self.curMem.BFArray[self.curMem.BFArrPo] = sys.stdin.read(1)
            elif c == '{':
                self.MemoryArray.append(Memory(BFA=[self.curMem.BFArray[self.curMem.BFArrPos]]))
                self.curMem = self.MemoryArray[len(self.MemoryArray)-1]
            elif c == '}':
                MemArrLen = len(self.MemoryArray)
                self.MemoryArray[MemArrLen-2].BFArray[self.MemoryArray[MemArrLen-2].BFArrPos] = self.curMem.BFArray[self.curMem.BFArrPos]
                self.MemoryArray.pop()
                self.curMem = self.MemoryArray[MemArrLen-2]
            elif c == '#':
                print(self.curMem.BFArray[self.curMem.BFArrPos], end='')
            
            elif c == '@':
                tempstr = ""
                c = self.f.read(1)
                while c != '@':
                    tempstr += c
                    c = self.f.read(1)
                from os import path
                filePath = path.abspath(self.fnameArray[len(self.fnameArray)-1])
                fPathList = filePath.split("/")
                fPathList.pop()
                filePath = "/".join(fPathList)
                filePath += tempstr if tempstr[0]=='/' else "/"+tempstr

                try:
                    tempfile = open(filePath, "r")
                    self.fnameArray.append(filePath)
                except:
                    print("Error Occured.")
                    print(f"Error: {sys.exc_info()}")
                    quit()
                else:
                    self.fileArray.append(tempfile)
                    self.f = self.fileArray[len(self.fileArray)-1]
                
                numItems =  self.curMem.BFArray[self.curMem.BFArrPos]
                tempmem = Memory()
                for i in range(1, numItems+1):
                    tempMem.BFArray.append(self.curMem.BFArray[self.curMem.BFArrPos + i])
                self.MemoryArray.append(tempmem)
                self.curMem = self.MemoryArray[len(self.MemoryArray)-1]
            
            elif c == '!':
                numItems =  self.curMem.BFArray[self.curMem.BFArrPos]
                tempmem = self.MemoryArray[len(self.MemoryArray)-2]
                for i in range(numItems):
                    modInsert(tempmem.BFArray, tempmem.BFArrPos+i, self.curMem.BFArray[self.curMem.BFArrPos+i])
                self.fileArray.pop()
                self.fnameArray.pop()
                f = self.fileArray[len(self.fileArray)-1]
            elif c == '^':
                self.curMem.BFArrPos = 0
            elif c == '~':
                self.curMem.BFArrPos = self.curMem.len() - 1
            elif c == '|':
                opt = self.curMem.getCur()
                if opt == 0:
                    pos = self.curMem.len()
                    while pos != 0:
                        val = self.curMem.get(pos)
                        if val == 0:
                            self.curMem.BFArray.pop()
                        elif val != 0:
                            break;
                        pos -= 1
                else:
                    pos = 0
                    while pos < self.curMem.len():
                        if self.curMem.get(pos) == opt:
                            self.curMem.BFArray.pop(pos)
                        else:
                            pos += 1
            elif c == 'd':
                print(f"Current Cell:{self.curMem.BFArrPos}\nCurrent Size:{self.curMem.len()}\nCurrent Value:{self.curMem.getCur()}")
        return CURPLACE(self.MemoryArray, [self.fileArray, self.fnameArray], self.f.tell())

bf = brainfuck(sys.argv[1])
while 1:
    b = bf.step()
    if not b:
        break
