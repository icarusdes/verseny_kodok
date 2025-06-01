import sys
import re

mem = {}

if sys.argv[1] == "input.txt":
    grid_size = 71
    limit = 1024
else:
    grid_size = 7
    limit = 12  

for x in range(grid_size):
    for y in range(grid_size):
        mem[(x, y)] = 1

with open(sys.argv[1]) as f:
    for i, line in enumerate(f.readlines()):
        if i >= limit:
            break
        x, y = map(int, line.strip().split(","))
        print(i, " - ", x, y)
        del mem[(x, y)]

start = (0, 0)
stop = (grid_size - 1, grid_size - 1)

def get_neighbours(x, y):
    return [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]

def heuristic(a, cost):
    return cost + abs(a[0] - stop[0]) + abs(a[1] - stop[1])

steps = 0

def bfs():
    global steps
    queue = [(start, 0)]
    visited = set()
    while queue:
        steps += 1
        current, dist = queue.pop(0)

        if steps % 100 == 0:
            print(steps, current, dist)
            print(len(queue), len(visited))

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

print(bfs())