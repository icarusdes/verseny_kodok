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

# for seat_row in seats: 
#     print(seat_row)

# print() 

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
            if x < 0 or x >= width or y < 0 or y >= height:
                break
            is_occupied = seats[cur_y][cur_x] == 2
            if is_occupied or stop_after_first: 
                break
        occupied += is_occupied == True

while (seats != last_seats): 
    last_seats = copy.deepcopy(seats)
    for i in range(height): 
        for j in range(width): 
            if last_seats[i][j] == 0:
                continue
            occupied_near = 0
            if i > 0: 
                if j > 0: 
                    occupied_near += last_seats[i-1][j-1] == 2
                occupied_near += last_seats[i-1][j] == 2
                if j+1 < width: 
                    occupied_near += last_seats[i-1][j+1] == 2
            if j > 0: 
                occupied_near += last_seats[i][j-1] == 2
            if j+1 < width: 
                occupied_near += last_seats[i][j+1] == 2
            if i+1 < height: 
                if j > 0: 
                    occupied_near += last_seats[i+1][j-1] == 2
                occupied_near += last_seats[i+1][j] == 2
                if j+1 < width: 
                    occupied_near += last_seats[i+1][j+1] == 2
            if last_seats[i][j] == 1 and occupied_near == 0: 
                seats[i][j] = 2
            if seats[i][j] == 2 and occupied_near >= 4: 
                seats[i][j] = 1
    
    # for seat_row in seats: 
    #     print(seat_row)
    # print()

occupied = sum([sum([c == 2 for c in line]) for line in seats])
print(occupied)