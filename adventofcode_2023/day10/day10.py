import sys
from colorama import init as colorama_init
from colorama import Fore
from colorama import Style

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

pipe_map = {}
start_coord = None

y = 0
for line in lines:
    x = -1
    for c in line:
        x += 1
        if c == '.' or c == '\n':
            continue
        if c == "S":
            start_coord = (x, y)
        pipe_map[(x, y)] = c
    y += 1

possible_directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

to_direction = {
    "-": (1, 0),
    "|": (0, 1),
    'L': (1, 0),
    '7': (0, 1),
    'J': (0, -1),
    'F': (-1, 0),
}

pipe = {}
possible_connection = [(start_coord,0)]

while possible_connection:
    current_coord, dist = possible_connection.pop()
    pipe[current_coord] = dist
    left_dir = (current_coord[0] - 1, current_coord[1])
    right_dir = (current_coord[0] + 1, current_coord[1])
    up_dir = (current_coord[0], current_coord[1] - 1)
    down_dir = (current_coord[0], current_coord[1] + 1)
    
    if (pipe_map[current_coord] in "-"):
        up_dir = down_dir = None
    if (pipe_map[current_coord] in "|"):
        left_dir = right_dir = None
    if (pipe_map[current_coord] in "L"):
        left_dir = down_dir = None
    if (pipe_map[current_coord] in "7"):
        right_dir = up_dir = None
    if (pipe_map[current_coord] in "J"):
        right_dir = down_dir = None
    if (pipe_map[current_coord] in "F"):
        left_dir = up_dir = None

    if (up_dir in pipe_map) and (pipe_map[up_dir] in "|F7"):
        if up_dir in pipe: 
            if pipe[up_dir] > dist + 1:
                pipe[up_dir] = dist + 1
                possible_connection.append((up_dir, dist + 1))
        else:
            possible_connection.append((up_dir, dist + 1))
    if (down_dir in pipe_map) and (pipe_map[down_dir] in "|JL"):
        if down_dir in pipe:
            if pipe[down_dir] > dist + 1:
                pipe[down_dir] = dist + 1
                possible_connection.append((down_dir, dist + 1))
        else: 
            possible_connection.append((down_dir, dist + 1))
    if (left_dir in pipe_map) and (pipe_map[left_dir] in "-LF"):
        if left_dir in pipe:
            if pipe[left_dir] > dist + 1:
                pipe[left_dir] = dist + 1
                possible_connection.append((left_dir, dist + 1))
        else:
            possible_connection.append((left_dir, dist + 1))
    if (right_dir in pipe_map) and (pipe_map[right_dir] in "-J7"):
        if right_dir in pipe:
            if pipe[right_dir] > dist + 1:
                pipe[right_dir] = dist + 1
                possible_connection.append((right_dir, dist + 1))
        else:
            possible_connection.append((right_dir, dist + 1))
    if start_coord == current_coord:
        if ((up_dir, dist + 1) in possible_connection) and ((left_dir, dist + 1) in possible_connection):
            pipe_map[current_coord] = 'J'
        if ((up_dir, dist + 1) in possible_connection) and ((right_dir, dist + 1) in possible_connection):
            pipe_map[current_coord] = 'L'
        if ((down_dir, dist + 1) in possible_connection) and ((left_dir, dist + 1) in possible_connection):
            pipe_map[current_coord] = '7'
        if ((down_dir, dist + 1) in possible_connection) and ((right_dir, dist + 1) in possible_connection):
            pipe_map[current_coord] = 'F'



# print(pipe)
print(max(pipe.values()))
colorama_init()
internal_list = []

for y in range(len(lines)):
    direction = 0
    previous = None
    for x in range(len(lines[0])):
        if (x, y) in pipe:
            current = pipe_map[(x, y)]
            if current == "-":
                continue
            if current == "|":
                if direction == 1:
                    direction = 0
                else: 
                    direction = 1
            if current == "L":
                previous = current
            if current == "7":
                if previous == "L":
                    if direction == 1:
                        direction = 0
                    else:
                        direction = 1
                if previous == "F":
                    previous = None
            if current == "F":
                previous = current
            if current == "J":
                if previous == "F":
                    if direction == 1:
                        direction = 0
                    else:
                        direction = 1
                if previous == "L":
                    previous = None
        else:
            if direction == 1:
                internal_list.append((x, y))
            
        

for y in range(len(lines)):
    for x in range(len(lines[0])):
        if (x, y) in pipe:
            if (x, y) == start_coord:
                print(f"{Fore.RED}{pipe_map[(x, y)]}{Style.RESET_ALL}", end="")
            elif (x, y) in pipe:
                print(f"{Fore.GREEN}{pipe_map[(x, y)]}{Style.RESET_ALL}", end="")
            else:
                print(pipe_map[(x, y)], end="")
        elif (x, y) in internal_list:
            print(f"{Fore.YELLOW}I{Style.RESET_ALL}", end="")
        elif (x, y) in pipe_map:
            print(pipe_map[(x, y)], end="")
        else: 
            print(".", end="")
    print()

print(len(internal_list))
