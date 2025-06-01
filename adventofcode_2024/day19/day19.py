import sys
import functools

with open(sys.argv[1]) as f:
    towels, flags = f.read().split('\n\n')

towels = towels.split(', ')

@functools.cache
def is_possible(goal):
    sum = 0
    for i in range(0, len(towels)):
        if goal.startswith(towels[i]):
            if len(towels[i]) == len(goal):
                sum += 1
            elif res := is_possible(goal[len(towels[i]):]):
                sum += res
    return sum

is_possible_counter = 0
for flag in flags.split('\n'):
    if flag == "":
        continue
    if res := is_possible(flag):
        is_possible_counter += res
        print(flag, "\t\t - Yes - ", res)
    else:
        print(flag, "\t\t - No - ", 0)

print(is_possible_counter)

