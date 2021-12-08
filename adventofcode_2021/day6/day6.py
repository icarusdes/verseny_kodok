import sys 

input_file = open(sys.argv[1], "r")

ages = list(map(int, input_file.readline().split(",")))
days = int(sys.argv[2])

temp = {}
for i in range(9): 
    temp[i] = ages.count(i)
ages = temp

for _ in range(days):
    new_ages = {}
    for i in range(8):
        new_ages[i] = ages[i+1] 
    new_ages[8] = ages[0]
    new_ages[6] += ages[0]
    ages = new_ages

print (sum(ages.values()))