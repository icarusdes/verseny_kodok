import sys 
import copy

number_map = {
    ".": 0, 
    "L": 1, 
}

input_file = open(sys.argv[1], "r")
seats = []
for line in input_file.read().splitlines(): 
    seat_row = [number_map[c] for c in line]
    seats.append(seat_row)
        
height = len(seats)
width = len(seats[0])

last_seats = []

dirs = ["w", "nw", "n", "ne", "e", "se", "s", "sw"]
dir_shifts = {
    "w" : [-1, 0], 
    "nw" : [-1, -1],
    "n" : [0, -1], 
    "ne": [1, -1], 
    "e" : [1, 0],
    "se" : [1, 1],
    "s" : [0, 1],
    "sw": [-1, 1]
}

def get_occupied_sets_in_every_direction(seats, x, y, stop_after_first = True): 
    occupied_number = 0
    for dir in dirs: 
        shift = dir_shifts[dir]
        cur_x = x
        cur_y = y
        is_occupied = False
        while True: 
            cur_x += shift[0]
            cur_y += shift[1]
            if cur_x < 0 or cur_x >= width or cur_y < 0 or cur_y >= height:
                break
            if seats[cur_y][cur_x] == 1: #this is an empty seat
                break
            elif seats[cur_y][cur_x] == 2: 
                is_occupied = True
                break
            if stop_after_first: 
                break
        occupied_number += is_occupied == True
    return occupied_number

is_part_one = int(sys.argv[2]) == 1

stop_after_first = is_part_one #is this the first part of the question or second
occupied_near_limit = 4 if is_part_one else 5

while (seats != last_seats): 
    last_seats = copy.deepcopy(seats)
    for i in range(height): 
        for j in range(width): 
            if last_seats[i][j] == 0:
                continue
            occupied_near = get_occupied_sets_in_every_direction(last_seats, j, i, stop_after_first)            
            if last_seats[i][j] == 1 and occupied_near == 0: 
                seats[i][j] = 2
            if seats[i][j] == 2 and occupied_near >= occupied_near_limit: 
                seats[i][j] = 1

occupied = sum([sum([c == 2 for c in line]) for line in seats])
print(occupied)