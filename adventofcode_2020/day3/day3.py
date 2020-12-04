import sys

input_file = open(sys.argv[1], 'r')
slope = input_file.read().splitlines()
height = len(slope)
width = len(slope[0])

def getCollisions( down, right): 
    jumps = 0
    collisions = 0
    while (jumps * down < height): 
        if slope[jumps * down ][(jumps * right) % width] == '#':
            collisions += 1
        jumps += 1
    return collisions

print ( getCollisions(1,1) * getCollisions(1,3) * getCollisions(1,5) * getCollisions(1,7) * getCollisions(2,1))