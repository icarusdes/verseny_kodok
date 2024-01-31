import sys
from copy import deepcopy

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

dish = {}

y = 0
for line in lines:
    x = 0
    for c in line.strip():
        dish[(x,y)] = c
        x += 1
    y += 1

previous_dishes = []

# print the dish

def roll_north(dish):
    # slide in a direction (which is currently north)
    last_empty = [None for i in range(len(lines))]
    for y in range(len(lines)):
        for x in range(len(lines[0].strip())):
            current = dish[(x,y)]
            if current == '.': 
                if last_empty[x] == None:
                    last_empty[x] = y
            elif current == '#':
                last_empty[x] = None
            else: # current == 'O'
                if last_empty[x] != None:
                    dish[(x,last_empty[x])] = 'O'
                    dish[(x,y)] = '.'
                    last_empty[x] += 1

def roll_south(dish):
    last_empty = [None for i in range(len(lines))]
    for y in range(len(lines)-1, -1, -1):
        for x in range(len(lines[0].strip())):
            current = dish[(x,y)]
            if current == '.': 
                if last_empty[x] == None:
                    last_empty[x] = y
            elif current == '#':
                last_empty[x] = None
            else: # current == 'O'
                if last_empty[x] != None:
                    dish[(x,last_empty[x])] = 'O'
                    dish[(x,y)] = '.'
                    last_empty[x] -= 1

def roll_east(dish):
    last_empty = [None for i in range(len(lines[0].strip()))]
    for x in range(len(lines[0].strip())-1, -1, -1):
        for y in range(len(lines)):
            current = dish[(x,y)]
            if current == '.': 
                if last_empty[y] == None:
                    last_empty[y] = x
            elif current == '#':
                last_empty[y] = None
            else: # current == 'O'
                if last_empty[y] != None:
                    dish[(last_empty[y],y)] = 'O'
                    dish[(x,y)] = '.'
                    last_empty[y] -= 1

def roll_west(dish):
    last_empty = [None for i in range(len(lines[0].strip()))]
    for x in range(len(lines[0].strip())):
        for y in range(len(lines)):
            current = dish[(x,y)]
            if current == '.': 
                if last_empty[y] == None:
                    last_empty[y] = x
            elif current == '#':
                last_empty[y] = None
            else: # current == 'O'
                if last_empty[y] != None:
                    dish[(last_empty[y],y)] = 'O'
                    dish[(x,y)] = '.'
                    last_empty[y] += 1

cycle = 0
first = True
while dish not in previous_dishes:
    previous_dishes.append(deepcopy(dish))
    roll_north(dish)
    roll_west(dish)
    roll_south(dish)
    roll_east(dish)
    cycle += 1

first_repetion_index = previous_dishes.index(dish)
current_index = cycle
cycle_length = current_index - first_repetion_index
target_cycle = 1000000000
closest_cycle = ((1000000000 - first_repetion_index) // cycle_length) * cycle_length + first_repetion_index
current_repetion = target_cycle - closest_cycle + first_repetion_index


print(first_repetion_index)
print(current_index)
print(target_cycle)

load = 0
height = len(lines)
for y in range(len(lines)):
    for x in range(len(lines[0].strip())):
        if previous_dishes[current_repetion][(x,y)] == 'O':
            load += height - y

for y in range(len(lines)):
    for x in range(len(lines[0].strip())):
        print(previous_dishes[current_repetion][(x,y)], end='')
    print()

print(load)
