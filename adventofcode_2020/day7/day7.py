import re
import sys

input_file = open(sys.argv[1], "r")
bag_map = {}

def process_line(line): 
    m = re.match("^([a-z ]+) bags contain ([0-9a-z ,]+)\.$", line)
    contents = re.sub(r" bag[s]*", "", m.group(2)).split(",")
    bags_inside = []
    if contents != ["no other"]: 
        for content in contents: 
            m2 = re.match("^(\d+) ([a-z ]*)$", content.strip())
            bags_inside.append((int(m2.group(1)), m2.group(2)))
    bag_map[m.group(1)] = bags_inside

for line in input_file.read().splitlines(): 
    result = process_line(line)

if (sys.argv[2] == "1"): 
    del bag_map["shiny gold"]
    can_contain = []
    can_contain_not_processed = ["shiny gold"]
    while (len(can_contain_not_processed) > 0): 
        current = can_contain_not_processed.pop()
        to_be_removed = []
        for (key, value) in bag_map.items():
            for (num, name) in value: 
                if current == name: 
                    can_contain.append(key)
                    can_contain_not_processed.append(key)
                    to_be_removed.append(key)
        for k in to_be_removed: 
            del bag_map[k]
    print (len(can_contain))
else: 
    to_process = [(1, "shiny gold")]
    num_bags = -1

    while len(to_process) > 0: 
        current = to_process.pop()
        num_bags += current[0]
        bags_contained = bag_map[current[1]]
        for bag in bags_contained: 
            to_process.append((bag[0]* current[0], bag[1]))

    print(num_bags)
