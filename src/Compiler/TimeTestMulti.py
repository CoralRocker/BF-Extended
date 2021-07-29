import time
from subprocess import call, DEVNULL
import threading
from os import sched_getaffinity

numThreads = 5
sumArr = [0] * numThreads

def getTiming(threadID, numRuns):
    sumTime = 0
    for i in range(0, numRuns):
        print(f"Run {i+1}/{numRuns}")
        s_t = time.time()
        call("./bf.o", stdout=DEVNULL)
        e_t = time.time()
        sumTime += (e_t - s_t)
    sumArr[threadID] += sumTime

threads = [threading.Thread(target=getTiming, args=(i, 5,)) for i in range(0, numThreads)]
print(f"Running {numThreads * 5} times")

for t in threads:
    t.start()
for t in threads:
    t.join()

print(sumArr)
avg = sum(sumArr)/(numThreads*5)
print(avg)

