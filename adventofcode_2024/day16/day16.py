import sys

maze = {}
start = None
end   = None

max_x = 0
max_y = 0

# enum containing the possible directions
class Direction:
    EAST = 0
    NORTH = 1
    WEST = 2
    SOUTH = 3

def direction_to_coord_diff(coord_diff):
    if coord_diff == (1, 0):
        return Direction.EAST
    if coord_diff == (-1, 0):
        return Direction.WEST
    if coord_diff == (0, 1):
        return Direction.SOUTH
    if coord_diff == (0, -1):
        return Direction.NORTH

def coord_diff_to_direction(direction):
    if direction == Direction.EAST:
        return (1, 0)
    if direction == Direction.WEST:
        return (-1, 0)
    if direction == Direction.SOUTH:
        return (0, 1)
    if direction == Direction.NORTH:
        return (0, -1)


# number of turns to make to go from one direction to another
def turns_to_make(from_dir, to_dir):
    return min(abs(from_dir - to_dir), 4 - abs(from_dir - to_dir))

assert turns_to_make(Direction.EAST, Direction.NORTH) == 1
assert turns_to_make(Direction.NORTH, Direction.EAST) == 1
assert turns_to_make(Direction.EAST, Direction.WEST) == 2

with open(sys.argv[1]) as f:
    map_part = f.read()

for y, line in enumerate(map_part.split('\n')):
    for x, c in enumerate(line):
        if c == ".":
            maze[(x, y)] = c
        if c == "S":
            maze[(x, y)] = c
            start = (x, y)
        if c == "E":
            maze[(x, y)] = c
            end = (x, y)
        max_x = max(max_x, x)
    max_y = max(max_y, y)

current_state = (start, Direction.EAST, 0, [start])
open_set = []
closed_set = []

open_set.append(current_state)

def heuristic(coords):
    return abs(coords[0] - end[0]) + abs(coords[1] - end[1])

def cost(current_state, nextcoord):
    diff_x = nextcoord[0] - current_state[0][0]
    diff_y =  nextcoord[1] - current_state[0][1]
    direction_to_step_towards = direction_to_coord_diff((diff_x, diff_y))
    turns = turns_to_make(current_state[1], direction_to_step_towards)
    return turns * 1000 + 1

def neighbors(x, y):
    return [(x+1, y), (x-1, y), (x, y+1), (x, y-1)]


print (start, end)
cost_limit = None

touched_tiles = []

merged = None

while open_set:
    current_state = min(open_set, key=lambda x: x[2])
    open_set.remove(current_state)
    closed_set.append(current_state)

    current_x = current_state[0][0]
    current_y = current_state[0][1]

    # print("-------------------------------------------------")
    # for y in range(max_y):
    #     for x in range(max_x + 1):
    #         if (x, y) in maze:
    #             if (x, y) in current_state[3]:
    #                 print("O", end="")
    #             else:
    #                 print(maze[(x, y)], end="")
    #         else:
    #             print("#", end="")
    #     print()
    # print(current_state)

    # print(current_state)

    if current_state[0] == end:
        print("Found on of the ends: ", current_state)
        cost_limit = current_state[2]
        touched_tiles.extend(current_state[3])

        for y in range(max_y):
            for x in range(max_x + 1):
                if (x, y) in maze:
                    if (x, y) in touched_tiles:
                        print("O", end="")
                    else:
                        print(maze[(x, y)], end="")
                else:
                    print("#", end="")
            print()

    if cost_limit and current_state[2] > cost_limit:
        print("Cost limit reached")
        break

    for dir in [Direction.EAST, Direction.NORTH, Direction.WEST, Direction.SOUTH]:
        neighbor = (current_x + coord_diff_to_direction(dir)[0],
                    current_y + coord_diff_to_direction(dir)[1])
        # we have to determine which neighbor is in which direction so we can calculate their cost
        if neighbor not in maze:
            continue

        if neighbor in current_state[3]:
            found = True
            # print("Already visited")

        found = False
        for i in range(len(closed_set)):
            if closed_set[i][0] == neighbor and closed_set[i][1] == dir:
                found = True
                break

        if found:
            continue

        if dir == current_state[1]:
            cost_to_neighbor = 1
        else:
            cost_to_neighbor = cost(current_state, neighbor)

        updated = False
        for i in range(len(open_set)):
            if open_set[i][0] == neighbor:
                # if the neighbor is already in the open set
                # we have to see if there is one with the same directions and a lower cost
                # if there is one, we have to update it, otherwise it will be a new entry
                if open_set[i][1] == dir:
                    if open_set[i][2] > current_state[2] + cost_to_neighbor:
                        open_set[i] = (neighbor, dir, current_state[2] + cost_to_neighbor, current_state[3] + [neighbor])
                        updated = True
                        # print("Updated with a lower cost route")
                    elif open_set[i][2] == current_state[2] + cost_to_neighbor:
                        # print("Found a route with the same cost", current_state[0])
                        # print("Previous path:", open_set[i][3])
                        # print("Current path:", current_state[3] + [neighbor])
                        open_set[i] = (neighbor, dir, current_state[2] + cost_to_neighbor, open_set[i][3] + current_state[3] + [neighbor])
                        # print("Updated path:", open_set[i][3])
                        updated = True
                        merged = open_set[i][0]
                    break
        if not updated:
            open_set.append((neighbor, dir, current_state[2] + cost_to_neighbor, current_state[3] + [neighbor]))


touched_tiles = list(set(touched_tiles))
print("Touched tiles: ", len(touched_tiles))
