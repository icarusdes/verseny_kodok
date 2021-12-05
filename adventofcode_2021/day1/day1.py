import sys
from itertools import combinations 

input_file = open(sys.argv[1], 'r')
numbers = [int(line) for line in input_file.read().splitlines()]  

increased = 0 

for i in range (len(numbers) -3): 
    if sum(numbers[i:i+3]) < sum(numbers[i+1:i+4]): 
        increased += 1

print ("Numbers increased this many times: ", increased)