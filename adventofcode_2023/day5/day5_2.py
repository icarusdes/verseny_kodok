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
seed_itervals = []
state = states.SEEDS

for line in lines:
    if not line:
        state = states(state.value + 1)
    else:
        values = line.split(" ")
        if state == states.SEEDS:
            values = values[1:]
            for i in range(0, len(values) // 2):
                begin = int(values[2 * i])
                end = begin + int(values[2 * i + 1])
                seed_itervals.append((begin, end))
            continue
        if len(values) == 2:
            continue
        maps[state].append(list(map(int, values)))

print(maps, flush=True)
print(len(seed_itervals), flush=True)
state = states.SOIL
while states != states.LAST:
    print(seed_itervals, flush=True)
    new_seeds = []
    current_map = maps[state]
    while seed_itervals:
        (current_start, current_stop) = seed_itervals.pop(0)
        changed = False
        for (destination, source, length) in current_map:            
            if (current_start >= source + length) or (current_stop <= source):
                continue
                # nothing to do, seed are not in the interval
            if (current_start >= source) and (current_stop <= source + length):
                # seed is in the interval, we have to transform the whole
                new_seeds.append((current_start - source + destination, current_stop - source + destination))
                changed = True
                break
            if (current_start < source) and (current_stop > source + length):
                # we have to split the seed interval into three parts:
                # 1) the part that is before interval
                # 2) the part that is in the interval
                # 3) the part that is after the interval
                first_part = (current_start, source -1)
                second_part = (destination, destination + length)
                third_part = (source + length, current_stop)
                seed_itervals.append(first_part)
                new_seeds.append(second_part)
                seed_itervals.append(third_part)
                changed = True
                break
            if (current_start < source) and (current_stop <= source + length):
                # we have to split the seed interval into two parts:
                # 1) the part that is before interval
                # 2) the part that is in the interval
                first_part = (current_start, source -1)
                second_part = (destination, current_stop - source + destination)
                seed_itervals.append(first_part)
                new_seeds.append(second_part)
                changed = True
                break
            if (current_start >= source) and (current_stop > source + length):
                # we have to split the seed interval into two parts:
                # 1) the part that is in the interval
                # 2) the part that is after the interval
                first_part = (current_start - source + destination, destination + length)
                second_part = (source + length, current_stop)
                new_seeds.append(first_part)
                seed_itervals.append(second_part)
                changed = True
                break
        if not changed:
            new_seeds.append((current_start, current_stop))
    print(new_seeds, flush=True)
    seed_itervals = new_seeds
    print("-------", flush=True)
    if state == states.LOCATION:
        break
    state = states(state.value + 1) 

print(seed_itervals)
print(min(seed_itervals, key=lambda x: x[0])[0])