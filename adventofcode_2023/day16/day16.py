import sys
from enum import Enum

class Direction(Enum):
    NORTH = 1
    SOUTH = 2
    WEST = 3
    EAST = 4

    def __str__(self):
        match self:
            case Direction.NORTH: return '^'
            case Direction.SOUTH: return 'v'
            case Direction.WEST: return '<'
            case Direction.EAST: return '>'

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

maze = {}
rays = [(-1,0, Direction.EAST)]
height = width = len(lines)

y = 0
for line in lines:
    line = line.strip()
    for x in range(len(line)):
        maze[(x, y)] = line[x]
    y += 1

def solve(ray):
    rays = [ray]
    previously_seen = set()
    previously_seen_coords = dict()

    while rays:
        new_rays = []
        for ray in rays:
            previously_seen.add(ray)
            x, y, direction = ray
            if (x, y) not in previously_seen_coords:
                previously_seen_coords[(x,y)] = [direction]
            else:
                previously_seen_coords[(x,y)].append(direction)

            if direction == Direction.NORTH:
                y -= 1
            elif direction == Direction.SOUTH:
                y += 1
            elif direction == Direction.WEST:
                x -= 1
            elif direction == Direction.EAST:
                x += 1
            if x < 0 or x >= width or y < 0 or y >= height:
                continue
            
            if maze[(x, y)] == '.':
                pass
            if maze[(x, y)] == '/':
                if direction == Direction.NORTH:
                    direction = Direction.EAST
                elif direction == Direction.SOUTH:
                    direction = Direction.WEST
                elif direction == Direction.WEST:
                    direction = Direction.SOUTH
                elif direction == Direction.EAST:
                    direction = Direction.NORTH
            if maze[(x, y)] == '\\':
                if direction == Direction.NORTH:
                    direction = Direction.WEST
                elif direction == Direction.SOUTH:
                    direction = Direction.EAST
                elif direction == Direction.WEST:
                    direction = Direction.NORTH
                elif direction == Direction.EAST:
                    direction = Direction.SOUTH
            if maze[(x, y)] == '-':
                if direction == Direction.NORTH or direction == Direction.SOUTH:
                    if (x, y, Direction.WEST) not in previously_seen:
                        new_rays.append((x, y, Direction.WEST))
                    direction = Direction.EAST
                else:
                    pass
            if maze[(x, y)] == '|':
                if direction == Direction.WEST or direction == Direction.EAST:
                    if (x, y, direction) not in previously_seen:
                        new_rays.append((x, y, Direction.NORTH))
                    direction = Direction.SOUTH
                else:
                    pass
            if (x, y, direction) not in previously_seen:
                new_rays.append((x, y, direction))
        rays = new_rays
    return len(previously_seen_coords) - 1

rays_from_north = [(x, -1, Direction.SOUTH) for x in range(width)]
rays_from_south = [(x, height, Direction.NORTH) for x in range(width)]
rays_from_west = [(-1, y, Direction.EAST) for y in range(height)]
rays_from_east = [(width, y, Direction.WEST) for y in range(height)]
rays_from_everywhere = rays_from_north + rays_from_south + rays_from_west + rays_from_east

result = [solve(rays) for rays in rays_from_everywhere]
print(max(result))