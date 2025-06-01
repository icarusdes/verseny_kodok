import sys
import functools

map = {}
start = (0, 0)
visited = set()
y = 0
max_x = 0
with open(sys.argv[1]) as f:
    lines = f.readlines()
    for line in lines:
        x = 0
        for c in line:
            if c != '\n':
                print(c, end="")
            if c == '#':
                map[(x, y)] = 1
            elif c == '^':
                start = (x, y)
            else:
                pass
            x += 1
        print()
        y += 1
        max_x = x
max_y = y

def simulate(start, map):
    visited = {}
    directions = [(0, -1), (1, 0), (0, 1), (-1, 0)]
    current_direction = 0

    while True:
        next_position = (start[0] + directions[current_direction][0], start[1] + directions[current_direction][1])
        if next_position[0] < 0 or next_position[0] > max_x or next_position[1] < 0 or next_position[1] > max_y:
            # we left the bounds
            break
        if next_position in map and map[next_position] == 1:
            current_direction = (current_direction + 1) % 4
            continue
        else:
            start = next_position
        if start in visited:
            if current_direction in visited[start]:
                # we caused a loop
                return True, visited
            else:
                visited[start].append(current_direction)
        else:
            visited[start] = [current_direction]
        
    return False, visited


looped, visited = simulate(start, map)
print(looped)
print(visited)
print(len(visited))

print("Part 2")
print("Not implemented")

possible_loops = 0
for v in visited:
    changed_map = map.copy()
    changed_map[v] = 1
    looped, v = simulate(start, changed_map)
    if looped:
        possible_loops += 1

print(possible_loops)
