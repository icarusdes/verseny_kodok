import sys

maze = {}
start = None
end   = None

max_x = 0
max_y = 0

with open(sys.argv[1]) as f:
    for y, line in enumerate(f.read().split('\n')):
        for x, c in enumerate(line):
            if c == ".":
                maze[(x, y)] = c
            if c == "S":
                maze[(x, y)] = c
                start = (x, y)
            if c == "E":
                maze[(x, y)] = c
                end = (x, y)
            max_x = max(max_x, x)
        max_y = max(max_y, y)

open_set = [(start, [])]
closed_set = []

def get_neighbours(x, y):
    return [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]

the_route = None

while open_set:
    current = open_set.pop()
    # print(current)
    closed_set.append(current[0])
    if current[0] == end:
        the_route = current[1][:] + [current[0]]
        print(len(current[1]))
        print("Solution found")
        # print(current[1])
        break
    neighbour_count = 0
    for neighbour in get_neighbours(*current[0]):
        if neighbour in closed_set:
            continue
        if neighbour not in maze:
            continue
        open_set.append((neighbour, current[1][:] + [current[0]]))
        neighbour_count += 1

print(the_route)

cheats = {}

more_than_hundred_spare = 0

for i in range(len(the_route)):
    for j in range(i + 3,len(the_route)):
        distance_x = abs(the_route[j][0] - the_route[i][0])
        distance_y = abs(the_route[j][1] - the_route[i][1])

        if (distance_x == 2 and distance_y == 0) or (distance_x == 0 and distance_y == 2):
            shortcut_length = j - i - 2
            if shortcut_length not in cheats:
                cheats[shortcut_length] = 1
            else:
                cheats[shortcut_length] += 1
            if shortcut_length >= 100:
                more_than_hundred_spare += 1

keys_sorted = sorted(cheats.keys())
for key in keys_sorted:
    print(f"There are {cheats[key]} cheats that save {key} picoseconds.")

print(f"There are {more_than_hundred_spare} cheats that save more than 100 picoseconds.")
