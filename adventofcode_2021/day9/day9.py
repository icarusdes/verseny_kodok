import sys

input_file = open(sys.argv[1], "r")
lines = input_file.read().splitlines()

heightmap = [list(map(int, line)) for line in lines]

height = len(heightmap)
width = len(heightmap[0])
cavity_risks = []
cavity_coords = []
processed = []
current_basin_count = 0

def should_we_add(x, y): 
    if (x, y) in processed: 
        return False 
    for c in cavity_coords: 
        if c[0] == x and c[1] == y: 
            return False
    return True

def get_neighbour_coordinates(x, y): 
    coordinates = []
    if y > 0: 
        coordinates.append((x, y-1))
    #left
    if x > 0:
        coordinates.append((x - 1, y))
    #right
    if x + 1 < width:
        coordinates.append((x+1, y))
    #down
    if y + 1 < height:
        coordinates.append((x, y+1))
    return coordinates

for x in range(width):
    for y in range(height): 
        # up
        neighbours = get_neighbour_coordinates(x, y)
        smallest = True
        for neighbour_coord in neighbours: 
            _y = neighbour_coord[1]
            _x = neighbour_coord[0]
            if heightmap[_y][_x] < heightmap[y][x]: 
                smallest = False
                break
        if smallest: 
            cavity_risks.append(heightmap[y][x] + 1)
            cavity_coords.append((x, y, current_basin_count))
            current_basin_count += 1 

print(f"Sum of risk levels {sum(cavity_risks)}")

for x in range(width):
    for y in range(height): 
        if heightmap[y][x] == 9: 
           heightmap[y][x] = "X"

while (len(cavity_coords) > 0): 
    c = cavity_coords.pop()
    heightmap[c[1]][c[0]] = c[2]
    neighbours = get_neighbour_coordinates(c[0], c[1])
    processed.append((c[0], c[1]))

    for n in neighbours: 
        _x = n[0]
        _y = n[1]
        if heightmap[_y][_x] != "X" and should_we_add(_x, _y): 
            cavity_coords.append((_x, _y, c[2]))

counter = {}

for row in heightmap: 
    for element in row: 
        if element != "X": 
            counter[element] = counter.get(element, 0) + 1


v = list(counter.values())
v.sort() 
print ( v[-1] * v[-2] * v[-3])