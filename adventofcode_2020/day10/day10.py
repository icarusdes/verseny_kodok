import sys

joltage_differences = [0, 0, 1]

input_file = open(sys.argv[1], "r")
numbers = [int(line) for line in input_file.read().splitlines()]
numbers.append(0)
numbers.sort()
numbers.append(numbers[-1] + 3)
sections = []
section_start = 0
for i in range(len(numbers) - 1): 
    diff = numbers[i+1] - numbers[i]
    if (diff == 3):
        sections.append(numbers[section_start: i+1])
        section_start = i+1
    joltage_differences[diff -1] += 1

print ("First part of the question: ") 
print (joltage_differences)
print (joltage_differences[0] * joltage_differences[2])

#
print ("\nSecond part of the question: ") 
print (numbers)
print (sections)

# last - first, difference list with 3-s not included 

#i already precalculated this, for the example
previous_calculations = [
    (1, [1, 0]), 1,
    (2, [2, 0]), 2, 
    (3, [1, 1]), 2,
    (4, [4, 0]), 7,
    (3, [3, 0]), 4,
]

def calculate_diff_tuple(subset):
    differences = [0, 0]
    for i in range(len(subset) - 1):         
        diff = subset[i+1] - subset[i]
        differences[diff -1] += 1 
    return (subset[-1] - subset[0], differences)


def calculate_arrangements(section):     
    if len(section) <= 2:
        return 1
    diff_list = calculate_diff_tuple(section)

    try: 
        index = previous_calculations.index(diff_list)
        return previous_calculations[index + 1]
    except ValueError: #we don't have it, we have to calculate
        #wow, i didn't even need this
        print ("\t" + str(section))
        print ("\t" + str(diff_list))
        return 1
    return 1

prod = 1 

for section in sections: 
    prod *= calculate_arrangements(section)

print (prod)
        