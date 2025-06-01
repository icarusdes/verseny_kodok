import sys
import re

mem = {}

if sys.argv[1] == "input.txt":
    grid_size = 71
    limit = 1024
else:
    grid_size = 7
    limit = 12

corruptions = []
current_corruption = limit

for x in range(grid_size):
    for y in range(grid_size):
        mem[(x, y)] = 1

with open(sys.argv[1]) as f:
    for i, line in enumerate(f.readlines()):
        x, y = map(int, line.strip().split(","))
        corruptions.append((x, y))

for i in range(limit):
    del mem[corruptions[i]]

start = (0, 0)
stop = (grid_size - 1, grid_size - 1)

def get_neighbours(x, y):
    return [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]

def bfs():
    queue = [(start, 0)]
    visited = set()
    while queue:
        current, dist = queue.pop(0)

        if current == stop:
            return dist
        visited.add(current)
        for neighbour in get_neighbours(*current):
            if neighbour in visited:
                continue
            if neighbour not in mem:
                continue
            found = False
            for v in queue:
                if v[0] == neighbour:
                    found = True
                    break
            if found:
                continue
            queue.append((neighbour, dist + 1))

while True: 
    result = bfs()
    print(result)
    if result:
        print("Solution found")
        print("Corruption: ", current_corruption)
        del mem[corruptions[current_corruption]]
        current_corruption += 1
    else:
        print(current_corruption-1)
        print(corruptions[current_corruption-1])
        print("No solution found")
        break