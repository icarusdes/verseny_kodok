import sys 

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

universe_map = {}

y = 0
for line in lines:
    x = 0
    for c in line.strip():
        if c == '.':
            pass
        else:
            universe_map[(x, y)] = c
        x += 1
    y += 1

empty_rows = []
empty_cols = []
rows = set([y for (_,y) in universe_map.keys()])
cols = set([x for (x,_) in universe_map.keys()])

for i in range(len(lines[0]) - 1):
    if i not in cols:
        empty_cols.append(i)

for i in range(len(lines)):
    if i not in rows:
        empty_rows.append(i)
part1 = False

if part1:
    shift = 1
else:     
    shift = 10 - 1
    shift = 100 - 1
    shift = 1000000 - 1

eul = []
for (x,y) in universe_map.keys():

    shift_x = 0
    for empty_col in empty_cols:
        if empty_col < x:
            shift_x += shift
    x += shift * sum([1 for empty_col in empty_cols if empty_col < x])
    y += shift * sum([1 for empty_row in empty_rows if empty_row < y])

    eul.append((x,y))

sum_dist = 0

for i in range(len(eul)):
    for j in range (i + 1, len(eul)):
        dist_x = abs(eul[i][0] - eul[j][0])
        dist_y = abs(eul[i][1] - eul[j][1])
        sum_dist += dist_x + dist_y

print(sum_dist)