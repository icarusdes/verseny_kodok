import sys

input_file = open(sys.argv[1], "r")
lines = input_file.read().splitlines()

ea = lines[0]
image = {}

min_x = 0
min_y = 0
max_x = len(lines[2])
max_y = len(lines) - 2

for y in range(len(lines) - 2):
    current_line = lines[y + 2]
    for x in range(len(current_line)):
        if current_line[x] == "#": 
            image[(x, y)] = 1
        else: 
            image[(x, y)] = 0

def get_index(image, x, y, default_outerbound = 0): 
    index_string = ""
    for _y in range(-1, 2): 
        for _x in range(-1, 2): 
            index_string += str(image.get((x + _x, y + _y), default_outerbound))
    return int(index_string, 2)

def print_image(image): 
    min_x = max_x = min_y = max_y = 0
    for key in list(image.keys()): 
        if(key[0]) < min_x: 
            min_x = key[0]
        if(key[0]) > max_x: 
            max_x = key[0]
        if(key[1]) < min_y: 
            min_y = key[1]
        if(key[1]) > max_y: 
            max_y = key[1]
    for y in range(min_y-1, max_y+1): 
        for x in range(min_x-1, max_x+1):
            print("#" if image.get((x, y), 0) == 1 else ".", end="")
        print()

def enhance_image(image, default_outerbound): 
    min_x = max_x = min_y = max_y = 0
    for key in list(image.keys()): 
        if(key[0]) < min_x: 
            min_x = key[0]
        if(key[0]) > max_x: 
            max_x = key[0]
        if(key[1]) < min_y: 
            min_y = key[1]
        if(key[1]) > max_y: 
            max_y = key[1]
    new_image = {}
    for y in range(min_y-2, max_y+2): 
        for x in range(min_x-2, max_x+2):
            index = get_index(image, x, y, default_outerbound)
            if (ea[index] == "#"): 
                new_image[(x, y)] = 1
            else: 
                new_image[(x, y)] = 0
    return new_image

print(sum(list(image.values())))
is_infinity_white = False
for i in range(50):
    image = enhance_image(image, 1 if is_infinity_white else 0)
    if ea[0] == "#": 
        is_infinity_white = not is_infinity_white
    print(sum(list(image.values())))