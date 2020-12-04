import sys
from itertools import combinations 

input_file = open(sys.argv[1], 'r')
numbers = [int(line) for line in input_file.read().splitlines()]   
comb = combinations(numbers, 3) 
  
for i in list(comb): 
    if i[0] + i[1] + i[2] == 2020: 
        print(i[0]*i[1]*i[2])
        break