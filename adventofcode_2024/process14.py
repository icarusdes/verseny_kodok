import sys

warehouse = {}
start = None
max_x = 0
max_y = 0


def print_warehouse():
    for y in range(max_y + 1):
        for x in range(max_x + 1):
            if (x, y) in warehouse:
                print(warehouse[(x, y)], end="")
            else:
                print(".", end="")
        print()

with open(sys.argv[1]) as f:
    map_part, directions = f.read().split('\n\n')

for y, line in enumerate(map_part.split('\n')):
    for x, c in enumerate(line):
        if c != ".":
            warehouse[(x, y)] = c
        if c == "@":
            start = (x, y)
        max_x = max(max_x, x)
    max_y = max(max_y, y)

print_warehouse()

def move(start, dir):
    print(f"Moving from {start} in direction {dir}")
    x, y = start
    dx, dy = dir
    new_x, new_y = x + dx, y + dy
    if (new_x, new_y) in warehouse:
        if warehouse[(new_x, new_y)] == "#":
            # nothing happened
            return start
        if warehouse[(new_x, new_y)] == "O":
            new_coords = move((new_x, new_y), dir)
            if new_coords != (new_x, new_y):
                warehouse[(new_x, new_y)] = warehouse[(x, y)]
                del warehouse[(x, y)]
                return (new_x, new_y)
            else:
                return start
            
    # warehouse[(new_x, new_y)] == ".":
    warehouse[(new_x, new_y)] = warehouse[(x, y)]
    del warehouse[(x, y)]
    return (new_x, new_y)
        
for d in directions:
    if d == '\n':
        continue
    if d == '>':
        dir = (1, 0)
    elif d == '<':
        dir = (-1, 0)
    elif d == '^':
        dir = (0, -1)
    elif d == 'v':
        dir = (0, 1)
    start = move(start, dir)
    print_warehouse()
    print("---------------")

sum = 0
for k, v in warehouse.items():
    if v == "O":
        sum += k[1] * 100 + k[0]
        print(k, v, k[1] * 100 + k[0])

print(sum) 