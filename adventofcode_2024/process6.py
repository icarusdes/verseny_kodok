import sys

sum = 0
sum2 = 0

def calculate_possible_results_v1(previous_calcs, components):
    new_calcs = []
    if len(components) == 0:
        return previous_calcs
    for calc in previous_calcs:
        new_calcs.append(calc + components[0])
        new_calcs.append(calc * components[0])
    return calculate_possible_results_v1(new_calcs, components[1:])

def calculate_possible_results_v2(previous_calcs, components):
    new_calcs = []
    if len(components) == 0:
        return previous_calcs
    for calc in previous_calcs:
        new_calcs.append(calc + components[0])
        new_calcs.append(calc * components[0])
        new_calcs.append(int(str(calc) + str(components[0])))
    return calculate_possible_results_v2(new_calcs, components[1:])

with open(sys.argv[1]) as f:
    lines = f.readlines()
    for line in lines:
        result, components = line.split(":")
        result = int(result)
        components = [int(c) for c in components.strip().split(" ")]
        print (result, components)

        possible_results = calculate_possible_results_v1([components[0]], components[1:])
        possible_results_v2 = calculate_possible_results_v2([components[0]], components[1:])
        answer1 = result in possible_results
        answer2 = result in possible_results_v2
        print (answer1, answer2)
        if answer1:
            sum += result
        if answer2:
            sum2 += result

print(sum)
print(sum2)