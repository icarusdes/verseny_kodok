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
            if c != '.':
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
            
            if v[i][0] - diff_x < 0 or v[i][0] - diff_x > max_x or v[i][1] - diff_y < 0 or v[i][1] - diff_y > max_y:
                pass
            else:
                antinodes.add((v[i][0] - diff_x, v[i][1] - diff_y))
            
            if v[j][0] + diff_x < 0 or v[j][0] + diff_x > max_x or v[j][1] + diff_y < 0 or v[j][1] + diff_y > max_y:
                continue
            else:
                antinodes.add((v[j][0] + diff_x, v[j][1] + diff_y))

print(antinodes)
print(len(antinodes))

for y in range(max_y + 1):
    for x in range(max_x +1):
        if (x, y) in map:
            print(map[(x, y)], end="")
        elif (x, y) in antinodes:
            print("#", end="")
        else:
            print(".", end="")
    print()