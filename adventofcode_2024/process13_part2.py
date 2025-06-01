import sys
import re
import numpy as np

# testsize = (11, 7)
testsize = (101, 103)
number_of_iterations = 10000
pos_and_vel = []

f2 = open("render.txt", "w")

with open(sys.argv[1]) as f:
    for line in f.readlines():
        px, py, vx, vy = map(int, re.search(r'p=(.*),(.*) v=(.*),(.*)', line).groups())        
        pos_and_vel.append((px, py, vx, vy))

for i in range(number_of_iterations):
    print ("Current_iteration: ", i)
    f2.write(f"Current_iteration: {i}\n")
    robots = []

    for px, py, vx, vy in pos_and_vel:
        robots.append(((px + vx * i) % testsize[0], (py + vy * i) % testsize[1]))
    for y in range(testsize[1]):
        for x in range(testsize[0]):
            if (x, y) in robots:
                f2.write("#")
            else:
                f2.write(".")
        f2.write("\n")

    f2.write("----------------------\n")

f2.close()