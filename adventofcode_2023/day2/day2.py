import sys

global_limit = { 'red': 12, 'green': 13, 'blue': 14}
sum_part1 = 0
sum_part2 = 0

with open(sys.argv[1]) as f:
    lines = f.readlines()

game_number = 1
for line in lines:
    draws = line[line.find(":")+1:].replace(";", "").replace(",", "").split()
    possible = True
    game_limit = { 'red': 0, 'green': 0, 'blue': 0}
    for i in range(0, len(draws) // 2):
        current_value = int(draws[i*2])
        current_color = draws[i*2+1]
        if current_value > global_limit[current_color]:
            possible = False
        if current_value > game_limit[current_color]:
            game_limit[current_color] = current_value
    
    power = game_limit['red'] * game_limit['green'] * game_limit['blue']
    if possible:
        sum_part1 += game_number
    sum_part2 += power
    game_number += 1

print(f"Part 1: {sum_part1}")
print(f"Part 2: {sum_part2}")