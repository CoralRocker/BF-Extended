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

