import sys
import cmath

input_file = open(sys.argv[1], "r")
line = input_file.readline()

current = 0
santas = [complex(0,0), complex(0,0)]
coords = [complex(0,0)]

directions = {">" : complex(1, 0), 
              "<" : complex(-1, 0), 
              "^" : complex(0, 1),
              "v" : complex(0, -1) 
}

for c in line: 
    santas[current] += directions[c]
    coords.append(santas[current])
    current = (current + 1) % 2 

print (len(list(set(coords))))