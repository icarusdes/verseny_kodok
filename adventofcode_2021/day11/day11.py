import sys 

input_file = open(sys.argv[1], "r") 
lines = input_file.read().splitlines()
iterations = 0

octopi_map = {}
y = 0

debug = False

for line in lines:
    x = 0
    for c in line:
        octopi_map[(x, y)] = int(c) 
        x = x+1
    y = y+1

height, width = y, x

def get_neighbour_coordinates(x, y): 
    return [(x-1, y-1), 
            (x,   y-1), 
            (x+1, y-1), 
            (x-1, y), 
            (x+1, y), 
            (x-1, y+1), 
            (x,   y+1),   
            (x+1, y+1)]

flashed_count = 0
if debug:
    for y in range(height):
        print("\n", end="")
        for x in range (width):
            print(octopi_map[(x, y)], end="")
            #we iterate over every element of the map
    print("\n------------")

while True:
    iterations += 1
    to_process = [] 
    flashed = set()

    current_flash_counter = 0

    for y in range(height): 
        for x in range (width):
            octopi_map[(x, y)] += 1
            if octopi_map[(x, y)] > 9:
                current_flash_counter += 1
                neighbours = get_neighbour_coordinates(x, y)
                to_process.extend(neighbours)
                flashed.add((x, y))
            #we iterate over every element of the map
    if debug:
        print()
        print(to_process)
        print()

    while len(to_process) > 0: 
        c = to_process.pop() 
        if (c in octopi_map) and (c not in flashed): # helyes indexelés és még nem villant
            octopi_map[c] += 1
            if octopi_map[c] > 9:
                neighbours = get_neighbour_coordinates(c[0], c[1])
                to_process.extend(neighbours)
                flashed.add(c)
        else:
            pass #this was an out of bound index


    for y in range(height):
        if debug:
            print("\n", end="")
        for x in range (width):
            if octopi_map[(x, y)] > 9:
                octopi_map[(x, y)] = 0
                flashed_count += 1
            if debug:
                print(octopi_map[(x, y)], end="")
            #we iterate over every element of the map
    if debug:
        print("\n------------")

    if sum(list(octopi_map.values())) == 0:
        break

print (f"Number of iterations were: {iterations}")
print (f"Number of flashes: {flashed_count}")