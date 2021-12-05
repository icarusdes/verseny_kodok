import sys

input_file = open(sys.argv[1], 'r')
lines = input_file.read().splitlines()  

x, y = 0, 0

for line in lines: 
    [command, unit] = line.split() 

    if command == "forward": 
        x += int(unit)
    elif command == "down": 
        y += int(unit)
    elif command == "up": 
        y -= int(unit)
        if (y < 0): 
            print("He?")
    else: 
        print ("Baj van")

print( x* y)