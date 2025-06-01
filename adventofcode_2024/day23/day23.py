import sys

connections = {}

with open(sys.argv[1], 'r') as f:
    for line in f.readlines():
        print(line.strip())
        pc_a, pc_b = line.strip().split("-")

        if pc_a in connections:
            connections[pc_a].append(pc_b)
        else:
            connections[pc_a] = [pc_b]

        if pc_b in connections:
            connections[pc_b].append(pc_a)
        else:
            connections[pc_b] = [pc_a]

groups_of_at_least_three = []
for key, values in connections.items():
    if len(values) < 2:
        # it doesn't even have 2 connections so it can not be a part of 3
        continue
    for v in values: # my neighbours
        for v2 in connections[v]: # neighbours of my neighbour
            if v2 in values:
                group_of_three = [key, v, v2]
                group_of_three.sort()
                if group_of_three not in groups_of_at_least_three:
                    groups_of_at_least_three.append(group_of_three)

starting_with_t = 0
for three in groups_of_at_least_three:
    print(three)
    for item in three:
        if item.startswith("t"):
            starting_with_t += 1
            break

print(starting_with_t)
