import sys
map = {}

y = 0
with open(sys.argv[1]) as f:
    lines = f.readlines()
    for line in lines:
        x = 0
        for c in line:
            if c != '\n':
                map[(x, y)] = c
            x += 1
        y += 1
        max_x = x
max_y = y

starts = []
for k, v in map.items():
    if v == "0":
        starts.append(k)

directions = [(0, -1), (1, 0), (0, 1), (-1, 0)]

def get_trailhead_value(coords):
    starts = set()
    starts.add(coords)
    for i in range(1, 10):
        # print(starts)
        new_starts = set()
        for s in starts:
            for d in directions:
                new_pos = (s[0] + d[0], s[1] + d[1])
                if new_pos in map and map[new_pos] == str(i):
                    new_starts.add(new_pos)
        starts = new_starts
    return len(starts)

def get_trailhead_rating(coords):
    starts = []
    starts.append(coords)
    for i in range(1, 10):
        # print(starts)
        new_starts = []
        for s in starts:
            for d in directions:
                new_pos = (s[0] + d[0], s[1] + d[1])
                if new_pos in map and map[new_pos] == str(i):
                    new_starts.append(new_pos)
        starts = new_starts
    return len(starts)

sum = 0
sum2 = 0
for s in starts:
    sum += get_trailhead_value(s)
    sum2 += get_trailhead_rating(s)

print(sum)
print(sum2)