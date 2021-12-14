import sys
import math
from collections import Counter

input_file = open(sys.argv[1])
lines = input_file.read().splitlines()

template = lines[0]
rules = {}
iterations = 40

for i in range(2, len(lines)): 
    _from, _add = lines[i].split(" -> ")
    rules[_from] = _add

counter_map = {}

for i in range(len(template) -1):         
    current = template[i:i+2] 
    counter_map[current] = counter_map.get(current, 0) + 1

print (counter_map)
print (rules)

for current_it in range(iterations):
    print (current_it)
    new_counter_map = {}
    for key in list(counter_map.keys()): 
        current_count = counter_map[key]
        newkey_1 = "".join([key[0], rules[key]])
        newkey_2 = "".join([rules[key], key[1]])
        new_counter_map[newkey_1] = new_counter_map.get(newkey_1, 0) + current_count
        new_counter_map[newkey_2] = new_counter_map.get(newkey_2, 0) + current_count
    counter_map = new_counter_map

print(counter_map)

part_counter = {}
for key in list(counter_map.keys()): 
    current_count = counter_map[key]
    part_counter[key[0]] = part_counter.get(key[0], 0) + current_count
    part_counter[key[1]] = part_counter.get(key[1], 0) + current_count

nums = []

for key in list(part_counter.keys()): 
    nums.append(int(math.ceil(part_counter[key] / 2)))

print(part_counter)
nums.sort() 

print(nums)
print( nums[-1] - nums[0] )
# print(f"What do you get if you take the quantity of the most common element and subtract the quantity of the least common element? The answer is {most_common[1] - least_common[1]}")