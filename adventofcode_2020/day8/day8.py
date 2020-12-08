import re
import sys

input_file = open(sys.argv[1], "r")
memory = []; 
acc = 0; 
ip = 0; 

for line in input_file.read().splitlines(): 
    current_command = line.split()
    memory.append([current_command[0], int(current_command[1]), 0])

for i in range(len(memory) -1, -1, -1): 
    original = "jmp"
    if memory[i][0] == "acc": 
        continue
    elif memory[i][0] == "jmp":
        memory[i][0] = "nop"
    else: #nop
        memory[i][0] = "jmp"
        original = "nop"

    while ip != len(memory) and memory[ip][2] == 0: 
        memory[ip][2] += 1
        if memory[ip][0] == "acc":
            acc += memory[ip][1]
        elif memory[ip][0] == "nop": 
            pass
        else: # jmp
            ip += memory[ip][1]
            continue
        ip += 1
    
    if ip == len(memory): #vegigfutottunk es azert leptunk ki
        break
    
    #kovetkezo futtatashoz visszaallitjuk az eredeti allapotot
    memory[i][0] = original
    ip = 0
    acc = 0
    for j in range(len(memory)):
        memory[j][2] = 0

print(acc)
    
