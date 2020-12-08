import re 
import sys

def parse_one_line(line):
    m = re.match("(\d+)x(\d+)x(\d+)", line)
    return [int(m.group(i+1)) for i in range(3)]
    
def wrapping_paper(dimensions):
    l, w, h = dimensions
    sides = [l*w, w*h, h*l]
    return sum(side *2 for side in sides) + min(sides)

def ribbon(dimensions): 
    l, w, h = dimensions
    perimetes = [ 2*l + 2*w, 2*h + 2*w, 2*l + 2*h]
    return min(perimetes) + l*w*h

input_file = open(sys.argv[1], "r")
dimensions = [parse_one_line(line) for line in input_file.read().splitlines()]

print (sum(wrapping_paper(dim) for dim in dimensions))
print (sum(ribbon(dim) for dim in dimensions))