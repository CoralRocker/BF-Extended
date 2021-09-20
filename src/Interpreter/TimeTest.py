import time
from subprocess import call, DEVNULL

numRuns = 25
sumTime = 0

print(f"Running {numRuns} times")
for i in range(0, numRuns):
    print(f"Run {i+1}/{numRuns}")
    s_t = time.time()
    call(["./bfint.o"," SpeedTest/speed.b"])
    e_t = time.time()
    sumTime += (e_t - s_t)
print(f"Took an average of {sumTime/numRuns} seconds")
