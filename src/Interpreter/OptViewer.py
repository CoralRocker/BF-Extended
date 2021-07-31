import re
from sys import argv

optList = open("OptimizationData/opts.txt", "r").readlines()

rxp = re.compile("^(\w+) = (.+)")

optList = [rxp.search(opt) for opt in optList]
optList = [(opt.group(1), opt.group(2)) for opt in optList if opt]

rxp2 = re.compile("(\d+\.\d+)")
maxSize = max(map(len,list(map(list, zip(*optList)))[0]))
times =  list(map(lambda opt: rxp2.search(open("OptimizationData/"+opt[0]+".dat","r").readlines()[-1]).group(1), optList))
maxSize = [maxSize]+[max(map(len,list(map(str,times))))]


for index, optTup in enumerate(optList):
    line  = rxp2.search(open("OptimizationData/"+optTup[0]+".dat", "r").readlines()[-1]).group(1)
    spaces = ' '*(maxSize[0] - len(optTup[0]) + 2)
    spaces = [spaces]+[' '*(maxSize[1] - len(str(times[index])) + 2)]
    if argv[1] == '-v':
        print(f"{optTup[0]}{spaces[0]} :> {line}{spaces[1]}{optTup[1]}")
    else:
        print(f"{optTup[0]}{spaces[0]} :> {line}{spaces[1]}{str(optList[0][index-1]-optList[0][index])+(' minute difference ' if index < 1 else '')} {optTup[1]}")

