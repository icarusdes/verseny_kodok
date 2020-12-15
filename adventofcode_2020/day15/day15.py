import sys

try:
    current_input = [int(i) for i in sys.argv[1].split(",")]
except IndexError:
    current_input = [0,3,6]

try:
    to_stop = int(sys.argv[2])
except IndexError:
    to_stop = 2020

data = {}
for k, v in enumerate(current_input[:-1]):
    data[v] = k + 1
last_number = current_input[-1]; 
current_turn = len(current_input); 
 
while current_turn < to_stop: 
    if last_number in data: 
        temp = current_turn - data[last_number]
        data[last_number] = current_turn
        last_number = temp
    else: 
        data[last_number] = current_turn
        last_number = 0
    current_turn += 1

print(last_number)