import sys
import re

input_file = open(sys.argv[1], "r")
lines = input_file.read().splitlines()

vents = {}

# https://docs.python.org/3.0/whatsnew/3.0.html#ordering-comparisons 
def cmp(a, b):
    return (a > b) - (a < b) 

for line in lines:  
    x1, y1, x2, y2 = list(map(int, re.split(" -> |,", line)))

    x_inc = cmp(x2, x1)
    y_inc = cmp(y2, y1)
 
    dist = abs(x1-x2) if x_inc != 0 else abs(y1-y2)

    for i in range(dist+1):
        x = x1 + i*x_inc
        y = y1 + i*y_inc

        vents[(x, y)] = vents.get((x,y), 0) + 1

print (sum(1 for i in vents.values() if i > 1))