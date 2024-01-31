import sys

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

current_coord = (0,0)

dig = {current_coord: 1}

for line in lines:
    direction, amount, color = line.split()
    amount = int(amount)

    if direction == 'U':
        dir = (0, -1)
    elif direction == 'D':
        dir = (0, 1)
    elif direction == 'L':
        dir = (-1, 0)
    elif direction == 'R':
        dir = (1, 0)
    else:
        raise Exception('Unknown direction: ' + direction)
    
    for i in range(amount):
        current_coord = (current_coord[0] + dir[0], current_coord[1] + dir[1])
        if current_coord not in dig:
            dig[current_coord] = 1

min_x = min([x for x,y in dig.keys()])
max_x = max([x for x,y in dig.keys()])
min_y = min([y for x,y in dig.keys()])
max_y = max([y for x,y in dig.keys()])

with open("output.txt", "w") as f:
    for y in range(min_y, max_y+1):
        for x in range(min_x, max_x+1):
            if (x,y) in dig:
                f.write(str(dig[(x,y)]))
            else:
                f.write(' ')
        f.write('\n')

for y in range(min_y, max_y+1):
    for x in range(min_x, max_x+1):
        if (x,y) in dig:
            print(str(dig[(x,y)]), end='')
        else:
            print(' ', end='')
    print()

# The digger starts in a 1 meter cube hole in the ground. They then dig the specified number of meters 
# up (U), down (D), left (L), or right (R), clearing full 1 meter cubes as they go. The directions are given as seen