import sys
from enum import Enum

with open(sys.argv[1], "r") as input_file:
    lines = input_file.read().splitlines()

class states(Enum):
    SEEDS = 1
    SOIL = 2
    FERTILIZER = 3
    WATER = 4
    LIGHT = 5
    TEMPERATURE = 6
    HUMIDITY = 7
    LOCATION = 8
    LAST = 9

maps = { v : [] for v in states}
locations = []
seeds = []
state = states.SEEDS

for line in lines:
    if not line:
        state = states(state.value + 1)
    else:
        values = line.split(" ")
        if state == states.SEEDS:
            for i in range (0, len(values) // 2):
                for j in range(int(values[2 * (i+1)])):
                    seeds.append(int(values[2 * i + 1]) + j)
            continue
        if len(values) == 2:
            continue
        maps[state].append(list(map(int, values)))

print(maps, flush=True)
print(len(seeds), flush=True)
state = states.SOIL
while states != states.LAST:
    print(seeds, flush=True)
    new_seeds = []
    current_map = maps[state]
    for v in seeds:
        found = False
        for interval in current_map:
            if (interval[1] <= v)  and (v < interval[1] + interval[2]):
                new_seeds.append(v - interval[1] + interval[0])
                found = True
                break
        if not found:
            new_seeds.append(v)
    seeds = new_seeds
    if state == states.LOCATION:
        break
    state = states(state.value + 1)
print(seeds)
print(min(seeds))