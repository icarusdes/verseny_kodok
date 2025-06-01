import sys
import re

map = {}
max_x = 0
max_y = 0
y = 0
with open(sys.argv[1]) as f:
    for line in f.readlines():
        x = 0
        for c in line:
            map[(x, y)] = c
            x += 1
            if x > max_x:
                max_x = x
        y += 1
max_y = y

def get(x, y):
    if (x, y) in map:
        return map[(x, y)]
    return ''

xmas_counter = 0



for i in range(max_y):
    print(i)
    for j in range(max_x):
        for direction in [(1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1)]:
            x, y = j, i
            if get(x + 0 * direction[0], y  + 0 * direction[1]) == 'X':
                if get(x + 1 * direction[0], y  + 1 * direction[1]) == 'M':
                    if get(x + 2 * direction[0], y  + 2 * direction[1]) == 'A':
                        if get(x + 3 * direction[0], y  + 3 * direction[1]) == 'S':
                            xmas_counter += 1
                    else:
                        continue
                else:
                    continue
            else:
                continue

x_mas_counter = 0

print(xmas_counter)
print("-"*80)

votma = []

for i in range(max_y):
    print(i)
    for j in range(max_x):
        for direction in [(1, 1), (-1, 1), (-1, -1), (1, -1)]:
            x, y = j, i
            if get(x + 0 * direction[0], y  + 0 * direction[1]) == 'M':
                if get(x + 1 * direction[0], y  + 1 * direction[1]) == 'A':
                    if get(x + 2 * direction[0], y  + 2 * direction[1]) == 'S':                        
                        kozep = (x + 1 * direction[0], y  + 1 * direction[1])
                        print(kozep)
                        if votma.count(kozep) == 0:
                            votma.append(kozep)
                        else: 
                            x_mas_counter += 1
                    else:
                        continue
                else:
                    continue
            else:
                continue

print(x_mas_counter)