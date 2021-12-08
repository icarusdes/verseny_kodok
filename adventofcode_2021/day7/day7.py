import sys 

input_file = open(sys.argv[1], "r")

positions = list(map(int, input_file.readline().split(",")))

def fuel_need_linear(a, b):
    return abs(a-b)

def fuel_need_nonlinear(a, b): 
    return abs(a - b) * ( 1 + abs(a - b)) // 2

fuel_function = fuel_need_linear
if (len(sys.argv) > 2 and (int(sys.argv[2]) == 2)): 
    fuel_function = fuel_need_nonlinear

avg = sum(positions) / len (positions)
min_v = min(positions)
max_v = max(positions)
min_fuel_need = sum([ fuel_function(p, min_v)  for p in positions])
min_fuel_position = min_v

for i in range(min_v+1, max_v+1): 
    fuel_need = sum(( [ fuel_function(p, i)  for p in positions]))
    if fuel_need < min_fuel_need: 
        min_fuel_need = fuel_need
        min_fuel_position = i 

print (f"Minimum fuel need is {min_fuel_need} at position {min_fuel_position}")