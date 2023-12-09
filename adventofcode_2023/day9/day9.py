import sys

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

sum = 0
sum2 = 0

for line in lines:
    interpolations = []
    start = list(map(int, line.split(' ')))
    interpolations.append(start)
    all_zero = False
    while not all_zero:
        new_line = []
        last_line = interpolations[-1]
        all_zero = True
        for i in range(len(last_line)-1):
            diff = last_line[i+1] - last_line[i]
            new_line.append(diff)
            if diff != 0:
                all_zero = False
        interpolations.append(new_line)
    length = len(interpolations)
    for i in range(length-1, 0, -1):
        diff = interpolations[i][-1]
        last_value = interpolations[i-1][-1]
        new_value = last_value + diff
        interpolations[i-1].append(new_value)
    
    for i in range(length-1, 0, -1):
        diff = interpolations[i][0]
        first_value = interpolations[i-1][0]
        new_value = first_value - diff
        interpolations[i-1].insert(0, new_value)
    

    for i in range(len(interpolations)):
        print("  " *i, str(interpolations[i]))
    sum += interpolations[0][-1]
    sum2 += interpolations[0][0]
    print()

print(sum)
print(sum2)
            