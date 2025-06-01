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
        if c == ".":
            warehouse[(x*2, y)] = '.'
            warehouse[(x*2+1, y)] = '.'
        if c == "@":
            start = (x*2, y)
            warehouse[(x*2, y)] = '@'
            warehouse[(x*2+1, y)] = '.'
        if c == "#":
            warehouse[(x*2, y)] = '#'
            warehouse[(x*2+1, y)] = '#'
        if c == "O":
            warehouse[(x*2, y)] = '['
            warehouse[(x*2+1, y)] = ']'
        max_x = max(max_x, x*2 + 1)
    max_y = max(max_y, y)

print_warehouse()

def can_be_moved(start, dir):
    x, y = start
    dx, dy = dir
    if (dx == 1 or dx == -1):
        # moving horizontally
        new_x, new_y = x + dx, y
        if (new_x, new_y) in warehouse:
            if warehouse[(new_x, new_y)] == "#":
                # nothing happened
                return False
            if (warehouse[(new_x, new_y)] == "[" or
                warehouse[(new_x, new_y)] == "]"):
                can_move = can_be_moved((new_x, new_y), dir)
                return can_move
        # warehouse[(new_x, new_y)] == ".":
        return True
    else: # if (dy == 1 or dy == -1):
        # moving vertically
        new_x, new_y = x, y + dy
        if (new_x, new_y) in warehouse:
            if warehouse[(new_x, new_y)] == "#":
                # nothing happened
                return False
            if warehouse[(new_x, new_y)] == "[":
                can_move1 = can_be_moved((new_x, new_y), dir)
                can_move2 = can_be_moved((new_x+1, new_y), dir)
                return can_move1 and can_move2
            elif warehouse[(new_x, new_y)] == "]":                
                can_move1 = can_be_moved((new_x, new_y), dir)
                can_move2 = can_be_moved((new_x-1, new_y), dir)
                return can_move1 and can_move2
        # warehouse[(new_x, new_y)] == ".":
        return True


def move(start, dir):
    # print(f"Moving from {start} in direction {dir}")
    x, y = start
    dx, dy = dir
    if (dx == 1 or dx == -1):
        new_x, new_y = x + dx, y
        # move only called after can_be_moved is True, so we don't have to check for walls
        if (new_x, new_y) in warehouse:
            if (warehouse[(new_x, new_y)] == "[" or
                warehouse[(new_x, new_y)] == "]"):
                move((new_x, new_y), dir)
                warehouse[(new_x, new_y)] = warehouse[(x, y)]
                del warehouse[(x, y)]
                return (new_x, new_y)
        # warehouse[(new_x, new_y)] == ".":
        warehouse[(new_x, new_y)] = warehouse[(x, y)]
        del warehouse[(x, y)]
        return (new_x, new_y)
    else:  # if (dy == 1 or dy == -1):
        new_x, new_y = x, y + dy
        if (new_x, new_y) in warehouse:
            if warehouse[(new_x, new_y)] == "[":
                move((new_x, new_y), dir)
                move((new_x+1, new_y), dir)
                warehouse[(new_x, new_y)] = warehouse[(x, y)]
                del warehouse[(x, y)]
                return (new_x, new_y)
            elif warehouse[(new_x, new_y)] == "]":
                move((new_x, new_y), dir)
                move((new_x-1, new_y), dir)
                warehouse[(new_x, new_y)] = warehouse[(x, y)]
                del warehouse[(x, y)]
                return  (new_x, new_y)
            else: # warehouse[(new_x, new_y)] == "@":
                # this can't be because @ is always the start point 
                # so it cant be at (new_x, new_y) coords yet
                warehouse[(new_x, new_y)] = warehouse[(x, y)]
                del warehouse[(x, y)]
                return (new_x, new_y)
        else: # warehouse[(new_x, new_y)] == ".":
            warehouse[(new_x, new_y)] = warehouse[(x, y)]
            del warehouse[(x, y)]
            return (new_x, new_y)

def score(x, y):
    closest_x_edge = min(x, max_x - (x+1))
    closest_y_edge = min(y, max_y - y)
    distance_x = abs(closest_x_edge - x)
    distance_y = abs(closest_y_edge - y)
    return distance_y * 100 + distance_x

def score2(x, y):
    return y * 100 + x


for d in directions:
    print("---------------")
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
    # print('dir:', dir)
    can_move = can_be_moved(start, dir)
    # print('can_move:', can_move)
    if can_move:
        start = move(start, dir)
    # start = move(start, dir)
print_warehouse()

sum = 0
for k, v in warehouse.items():
    if v == "[":
        sum += score2(k[0], k[1])
        print(k, v, score2(k[0], k[1]))

print(sum)
