import sys

garden = {}

with open(sys.argv[1]) as f:
    y = 0 
    for line in f.readlines():
        x = 0
        for c in line.strip():
            garden[(x, y)] = c
            x += 1
        y += 1

print(garden)

unprocessed_tiles = set(garden.keys()) 
plots=[]

while unprocessed_tiles:
    plot = []
    stack = [unprocessed_tiles.pop()]
    while stack:
        tile = stack.pop()
        plot.append(tile)
        for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            neighbor = (tile[0] + dx, tile[1] + dy)
            if neighbor in unprocessed_tiles and garden[neighbor] == garden[tile]:
                stack.append(neighbor)
                unprocessed_tiles.remove(neighbor)
    plots.append(plot)

print(plots)

def get_perimeter_for_plot(plot):
    perimeter = 0
    for tile in plot:
        for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            neighbor = (tile[0] + dx, tile[1] + dy)
            if neighbor not in plot:
                perimeter += 1
    return perimeter

def get_perimeter_for_plot_v2(plot):
    unprocessed_sides = []
    for tile in plot:
        for dx, dy, dir in [(1, 0, 0), (0, 1, 1), (-1, 0, 2), (0, -1, 3)]:
            neighbor = (tile[0] + dx, tile[1] + dy)
            if neighbor not in plot:
                unprocessed_sides.append((tile, dir))
    
    sides = 0
    while unprocessed_sides:
        sides += 1
        stack = [unprocessed_sides.pop(0)]
        while stack:
            side, dir = stack.pop(0)
            dx1, dy1 = [(0, 1), (1, 0)][dir % 2]
            neighbor1 = (side[0] + dx1, side[1] + dy1)
            neighbor2 = (side[0] - dx1, side[1] - dy1)
            if (neighbor1, dir) in unprocessed_sides:
                unprocessed_sides.remove((neighbor1, dir))
                stack.append((neighbor1, dir))
            if (neighbor2, dir) in unprocessed_sides:
                unprocessed_sides.remove((neighbor2, dir))
                stack.append((neighbor2, dir))
            
    return sides

checksum = 0
checksum_v2 = 0
for plot in plots:
    print("Plot:", plot)
    size = len(plot)
    perimeter = get_perimeter_for_plot(plot)
    perimeter_2 = get_perimeter_for_plot_v2(plot)
    checksum += size * perimeter
    checksum_v2 += size * perimeter_2
    print("Size:", size)
    print("Perimeterv1:", perimeter)
    print("Perimeterv2:", perimeter_2)
    print("---------------------------------")
print(checksum)
print(checksum_v2)