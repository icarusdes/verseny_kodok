import sys

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

district = {}

y=0
for line in lines:
    x=0
    for c in line.strip():
        district[(x,y)] = int(c)
        x+=1
    y+=1

height = len(lines)
width = len(lines[0].strip())

def draw_district(district):
    for y in range(0, height):
        for x in range(0, width):
            print(district[(x,y)], end='')
        print()

#             x y   value
start_node = (0,0)

def get_neighbors(node):
    x,y = node
    neighbor_coords = []
    if (x-1, y) in district:
        neighbor_coords.append((x-1, y))
    if (x+1, y) in district:
        neighbor_coords.append((x+1, y))
    if (x, y-1) in district:
        neighbor_coords.append((x, y-1))
    if (x, y+1) in district:
        neighbor_coords.append((x, y+1))
    return neighbor_coords

def heuristic(node):
    x,y = node
    return width - x + height - y

def solve(district, start_node):
    # A* algorithm
    # https://en.wikipedia.org/wiki/A*_search_algorithm
    open_set = [start_node]
    closed_set = set()
    came_from = dict()
    g_score = dict()
    f_score = dict()

    g_score[start_node] = 0
    f_score[start_node] = heuristic(start_node)

    while open_set:
        current = min(open_set, key=lambda x: f_score[x])
        
    return None

result = solve(district, start_node)

draw_district(district)
print(result)