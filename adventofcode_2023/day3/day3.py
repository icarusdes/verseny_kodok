import sys

input_file = open(sys.argv[1], "r")

lines = input_file.read().splitlines()
schematics = {}

def is_symbol(c):
    return not c.isnumeric()

y = 0
for line in lines: 
    x=0
    for c in line:
        if c != ".":
            schematics[(x, y)] = c
        x+=1 
    y+=1

shifts = [(0, -1), (-1, 0), (1, 0), (0, 1), (1 , 1), (-1, -1), (1, -1), (-1, 1)]
sum_num = 0
numbers_to_gears = {}


number = None
was_neightbouring_symbol = False
current_gears = []

for y in range(0, len(lines)):
    for x in range(0, len(lines[0])):
        if x == 0:
            if number is not None:
                if was_neightbouring_symbol:
                    sum_num += number
                    for g in current_gears:
                        l = numbers_to_gears.get(g, [])
                        l.append(number)
                        numbers_to_gears[g] = l
                    current_gears = []
                number = None
                was_neightbouring_symbol = False
        if (x, y) in schematics:
            c = schematics[(x, y)]
            print(c, end="")
            if c.isnumeric():
                if number is None:
                    number = int(c)
                else:
                    number = number * 10 + int(c)

                for shift in shifts:
                    new_coord = (x + shift[0], y + shift[1])
                    if (new_coord) in schematics:
                        if is_symbol(schematics[new_coord]):
                            was_neightbouring_symbol = True
                        if schematics[new_coord] == "*" and new_coord not in current_gears:
                            current_gears.append(new_coord)
            else:
                if number is not None:
                    sum_num += number
                    for g in current_gears:
                        l = numbers_to_gears.get(g, [])
                        l.append(number)
                        numbers_to_gears[g] = l
                    current_gears = []
                number = None
                was_neightbouring_symbol = False
        else:
            if number is not None:
                if was_neightbouring_symbol:
                    sum_num += number
                    for g in current_gears:
                        l = numbers_to_gears.get(g, [])
                        l.append(number)
                        numbers_to_gears[g] = l
                    current_gears = []
                number = None
                was_neightbouring_symbol = False
            print(".", end="")
    print()

ratio_sum = 0

for k, v in numbers_to_gears.items():
    if len(v) == 2:
        ratio = v[0] * v[1]
        ratio_sum += ratio

print(sum_num)
print(numbers_to_gears)
print(ratio_sum)