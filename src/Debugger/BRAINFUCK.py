import sys

ERROR_RETURN = -1
ERROR_EOF = -2

class mem:
    def __init__(self, bfarr, bfpos, lparr, lppos):
        self.bfarr = bfarr
        self.bfpos = bfpos
        self.lparr = lparr
        self.lppos = lppos

class brainfuck:
    def __init__(self, filename):
        self.filearr = [open(filename, 'r')]
        self.fnamearr = [filename]
        self.bfarr = [0]
        self.bfpos = 0
        self.lparr = []
        self.lppos = -1
        self.memarr = [mem(self.bfarr,self.bfpos,self.lparr,self.lppos)] #Used to store mem states for scratch memory
        self.f = self.filearr[0]
        self.curpos = 0
    
    def step(self, n=1):
        for i in range(n):
            c = self.f.read(1)
            if not c:
                return ERROR_RETURN
            
            if c == '/':
                cur = self.f.tell()
                c = self.f.read(1)
                if c == '*':
                    c = self.f.read(2)
                    tmp = self.f.tell()-1
                    while True:
                        if c == '*/':
                            break;
                        if not c:
                            return ERROR_EOF
                        self.f.seek(tmp) # Go back one pos in file
                        c = self.f.read(2)
                        tmp = self.f.tell()-1
                elif c == '/':
                    c = self.f.read(1)
                    while c != chr(10):
                        c = self.f.read(1)
            
            elif c == '+':
                self.bfarr[self.bfpos] += 1
            
            elif c == '-':
                self.bfarr[self.bfpos] -= 1
            
            elif c == '>':
                self.bfpos += 1
                if len(self.bfarr) <= self.bfpos:
                    self.bfarr.append(0)
            
            elif c == '<':
                self.bfpos = self.bfpos - 1 if self.bfpos != 0 else 0
            
            elif c == '[':
                if self.bfarr[self.bfpos] == 0:
                    while c != ']':
                        c = self.f.read(1)
                else:
                    self.lparr.append(self.f.tell())
                    self.lppos += 1
            
            elif c == ']':
                if not self.bfarr[self.bfpos] == 0:
                    self.f.seek(self.lparr[self.lppos])
                else:
                    self.lparr.pop()
                    self.lppos -= 1
            
            elif c == '.':
                print(f"{self.bfarr[self.bfpos]:c}",end='')
            
            elif c == ',':
                self.bfarr[self.bfpos] = sys.stdin.read(1)
            
            self.curpos = self.f.tell()
            
        return 0

    def memDisplay(self, out='dec'):
        if out=='dec':
            for i in range(len(self.bfarr)):
                print(f"{self.bfarr[i]:3d}", end='  ')
                if i % 20 == 0 and i != 0:
                    print("")
        
                    
