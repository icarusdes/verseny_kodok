import sys
import re

def isValid(line): 
    m = re.match("^(\d+)-(\d+) ([a-z0-9]): ([a-z0-9]*)$", line, flags = re.IGNORECASE)
    if m != None: 
        first = int(m.group(1)) - 1 
        second = int(m.group(2)) - 1
        char = m.group(3)  
        password = m.group(4)
        return (password[first] != password[second]) and ((password[first] == char) or password[second] == char)
    return False

input_file = open(sys.argv[1], 'r')
valid_passowrds_count = sum(isValid(line) for line in input_file.read().splitlines())    
print("Number of valid passwords are: {}".format(valid_passowrds_count))   
