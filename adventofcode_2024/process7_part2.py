import sys

map = {}
frequences = {}

antinodes = set()

y = 0
max_x = 0
with open(sys.argv[1]) as f:
    lines = f.readlines()
    for line in lines:
        x = 0
        for c in line:
            if c != '.' and c != '\n':
                map[(x, y)] = c
                if c not in frequences:
                    frequences[c] = [(x, y)]
                else:
                    frequences[c].append((x, y))
            x += 1
        y += 1
        max_x = x -1
max_y = y -1 

for y in range(max_y):
    for x in range(max_x):
        if (x, y) in map:
            print(map[(x, y)], end="")
        elif (x, y) in antinodes:
            print("#", end="")
        else:
            print(".", end="")
    print()

for k, v in frequences.items():
    print(k, v)
    for i in range(len(v)):
        for j in range(i+1, len(v)):
            diff_x, diff_y = v[j][0] - v[i][0], v[j][1] - v[i][1]
            
            diff = 1
            while True:
                new_x = v[i][0] - diff * diff_x
                new_y = v[i][1] - diff * diff_y
                if new_x < 0 or new_x > max_x or new_y < 0 or new_y > max_y:
                    break
                else:
                    antinodes.add((new_x, new_y))
                diff += 1

            diff = 1
            while True:
                new_x = v[j][0] + diff * diff_x
                new_y = v[j][1] + diff * diff_y
                if new_x < 0 or new_x > max_x or new_y < 0 or new_y > max_y:
                    break
                else:
                    antinodes.add((new_x, new_y))
                diff += 1

print("-------------------")

for v in map.keys():
    if v not in antinodes:
        antinodes.add(v)

for y in range(max_y + 1):
    for x in range(max_x +1):
        if (x, y) in map:
            print(map[(x, y)], end="")
        elif (x, y) in antinodes:
            print("#", end="")
        else:
            print(".", end="")
    print()

print(len(antinodes))
