import sys
import numpy
import copy

input_file = open(sys.argv[1], 'r')
lines = input_file.read().splitlines()  
lines = [list(map(int, line)) for line in lines]

sum_vec = [0 for i in lines[0]]

for line in lines: 
    sum_vec = numpy.add(sum_vec, line)

most_common = []
least_common = []

for i in sum_vec: 
    if i * 2 > len(lines): 
        most_common.append(1)
        least_common.append(0)
    else:
        most_common.append(0)
        least_common.append(1)

gamma_rate = int("".join([str(i) for i in most_common]), 2)
epsilon_rate = int("".join([str(i) for i in least_common]), 2) 

print (gamma_rate * epsilon_rate)

list_copy = copy.deepcopy(lines)
current_index = 0

while len(list_copy) > 1: 
    print(list_copy)
    sum_num = 0
    for line in list_copy: 
        sum_num += line[current_index]
    filter_num = (sum_num * 2) // len(list_copy) 
    if filter_num != 2: 
        list_copy = list(filter (lambda x: (x[current_index] == filter_num), list_copy))
    current_index+=1

print (list_copy[0])
oxygen_generator_rating = int("".join([str(i) for i in list_copy[0]]), 2)

list_copy = copy.deepcopy(lines)
current_index = 0

while len(list_copy) > 1: 
    sum_num = 0
    for line in list_copy: 
        sum_num += line[current_index]
    filter_num = (sum_num * 2) // len(list_copy)
    list_copy = list(filter (lambda x: (x[current_index] != filter_num), list_copy))
    current_index+=1

print (list_copy[0])

CO2_scrubber_rating = int("".join([str(i) for i in list_copy[0]]), 2)

print (oxygen_generator_rating * CO2_scrubber_rating)