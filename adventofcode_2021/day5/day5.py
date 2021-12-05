import sys

input_file = open(sys.argv[1], "r")
lines = input_file.read().splitlines()

vents = {}

for line in lines: 
    k1,k2 = line.split(" -> ")
    x1, y1 = list(map(int, k1.split(",")))
    x2, y2 = list(map(int, k2.split(",")))

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
 
    if x_inc != 0:
        dist = abs(x1-x2)
    else: 
        dist = abs(y1-y2)

    for i in range(dist+1):
        x = x1 + i*x_inc
        y = y1 + i*y_inc

        if (x, y) in vents: 
            vents[(x, y)] += 1
        else: 
            vents[(x, y)] = 1

print (sum(1 for i in vents.values() if i > 1))