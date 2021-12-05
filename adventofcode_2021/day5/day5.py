import sys
import re

input_file = open(sys.argv[1], "r")
lines = input_file.read().splitlines()

vents = {}

for line in lines:  
    x1, y1, x2, y2 = list(map(int, re.split(" -> |,", line)))

    x_inc = 0
    if (x1 > x2): 
        x_inc = -1
    elif (x1 < x2): 
        x_inc = 1

    y_inc = 0
    if (y1 > y2):
        y_inc = -1 
    elif (y2 > y1): 
        y_inc = 1  
 
    dist = abs(x1-x2) if x_inc != 0 else abs(y1-y2)

    for i in range(dist+1):
        x = x1 + i*x_inc
        y = y1 + i*y_inc

        vents[(x, y)] = vents.get((x,y), 0) + 1

print (sum(1 for i in vents.values() if i > 1))