import sys

y = 0
with open(sys.argv[1]) as f:
    initial_arrangement = [int(num) for num in f.readline().split()]

print(initial_arrangement)
# for i in range(int(sys.argv[2])):
#     print(i)
#     new_arrangement = []
#     for num in initial_arrangement:
#         digits = str(num)
#         length = len(digits)
#         if num == 0:
#             new_arrangement.append(1)
#         elif length % 2 == 0:            
#             new_arrangement.append(int(digits[:length//2]))
#             new_arrangement.append(int(digits[length//2:]))
#         else:
#             new_arrangement.append(num * 2024)
#     initial_arrangement = new_arrangement

cache = {}

def how_long_it_becomes(num, cycles_left):
    if cycles_left == 0:
        return 1
    if (num, cycles_left) in cache:
        return cache[(num, cycles_left)]
    digits = str(num)
    length = len(digits)
    if num == 0:
        result = how_long_it_becomes(1, cycles_left-1)
    elif length % 2 == 0:
        result = (how_long_it_becomes(int(digits[:length//2]), cycles_left-1) +
                 how_long_it_becomes(int(digits[length//2:]), cycles_left-1))
    else:
        result = how_long_it_becomes(num * 2024, cycles_left-1)
    cache[(num, cycles_left)] = result
    return result

sum = 0
for num in initial_arrangement:
    sum += how_long_it_becomes(num, int(sys.argv[2]))

print(sum)