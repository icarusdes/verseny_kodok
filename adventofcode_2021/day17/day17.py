import math

# test_input = "target area: x=20..30, y=-10..-5"
# max_x = 30
# min_x = 20
# max_y = -5
# min_y = -10

real_input = "target area: x=201..230, y=-99..-65" 
#i won't do text parsing, because i don't really have to :) 
min_x = 201
max_x = 230
max_y = -65
min_y = -99


def simulate(vx, vy): 
    x, y = 0, 0

    while y >= min_y: 
        if min_x <= x and x <= max_x and min_y <= y and y <= max_y: 
            return True
        x += vx
        if vx > 0: 
            vx -= 1
        y += vy
        vy -= 1

    return False

width = max_x - min_x
# x(x+1) / 2 should be at least min_x 
# x^2 + x - 2*min_x = 0
c = -2*min_x
# x1,2 = (-b +- sqrt(b^2 - 4ac)) / 2a
x_2 =  (-1 + math.sqrt(1 - 4*c)) / 2

minimum_horizontal_speed = math.ceil(x_2)
maximum_horizontal_speed = max_x

print (f"The minimum horizontal speed is: {minimum_horizontal_speed}")
print (f"The maximum horizontal speed is: {maximum_horizontal_speed}")

maximum_vertical_speed = abs(min_y) - 1 
minimum_vertical_speed = min_y 

possible_speeds = set()

for vx in range(minimum_horizontal_speed, maximum_horizontal_speed+1): 
    for vy in range (minimum_vertical_speed, maximum_vertical_speed+1): 
        if simulate(vx, vy): 
            possible_speeds.add((vx, vy))

print(len(possible_speeds))