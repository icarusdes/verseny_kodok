import sys

input_file = open(sys.argv[1], 'r')
lines = input_file.read().splitlines()  

x, y, aim = 0, 0, 0

for line in lines: 
    [command, unit] = line.split() 
    unit = int(unit)
    if command == "forward": 
        x += unit
        y += aim * unit
    elif command == "down": 
        aim += int(unit)
    elif command == "up": 
        aim -= int(unit)
        if (y < 0): 
            print("He?")
    else: 
        print ("Baj van")

print( x* y)