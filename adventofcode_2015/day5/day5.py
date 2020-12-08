import sys

input_file = open(sys.argv[1], "r")

def nice_old(line): 
    if sum([c in "aiueo" for c in line]) < 3: 
        return False
    if len(line) <= 1: 
        return False
    double_char = False
    for i in range(0, len(line) -1): 
        if line[i] == line[i+1]:
            double_char = True
            break
    if not double_char:
        return False
    for part in ["ab", "cd", "pq", "xy"]: 
        if part in line:
            return False
    
    return True

def nice(line): 
    if len(line) <= 3:
        return False
    found_duplicate = False
    for i in range(0, len(line) - 2): 
        sub = line[i:i+2]
        if sub in line[i+2:]: 
            found_duplicate = True
            break 
    if not found_duplicate: 
        return False

    found_dist = False
    for i in range(0, len(line) - 2): 
        if line[i] == line[i+2]: 
            found_dist = True
            break 
    if not found_dist: 
        return False

    return True

naughty_list = [nice(line) for line in input_file.read().splitlines()]
print(sum(naughty_list))
