import sys

input_file = open(sys.argv[1], "r")

lines = input_file.read().splitlines()
cavemap = {}

y = 0
for line in lines: 
    x=0
    for c in line:
        cavemap[(x, y)] = int(c)
        x+=1 
    y+=1

height = width = len(lines)

part2 = True
if part2:
    for i in range(0, 5):
        for j in range(0, 5):
            if i == 0 and j == 0:
                continue
            for x in range(width):
                for y in range(height):
                    new_value = cavemap[(x, y)] + i + j
                    if new_value > 9:
                        new_value -= 9
                    cavemap[(i * width + x, j * height + y)] = new_value

print("New map generated")

def get_neighbour_coordinates(x, y): 
    return [(x,   y-1), 
            (x-1, y), 
            (x+1, y), 
            (x,   y+1)]

#            x y  risk_so_far
start_list = [(0, 0, 0)]
processed_points = set()

print(len(cavemap))

while True:
    current_element = start_list.pop(0)
    risk_so_far, x, y = current_element[0], current_element[1], current_element[2]

    if not part2:
        if x == (width - 1) and y == (height - 1):
            print(f"The risk so far were: {risk_so_far}")
            break
    else:
        if x == (width*5 - 1) and y == (height*5 - 1):
            print(f"The risk so far were: {risk_so_far}")
            break

    neighbours = get_neighbour_coordinates(x, y)
    for n in neighbours:
        _x = n[0]
        _y = n[1]
        if n not in processed_points and n in cavemap:
            add = True
            for s in start_list:
                if s[1] == _x and s[2] == _y:
                    add = False
            if add:
                start_list.append((risk_so_far + cavemap[(_x, _y)], _x, _y))
    start_list.sort()
    processed_points.add((x, y))