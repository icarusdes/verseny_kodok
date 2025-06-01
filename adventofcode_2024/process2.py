import sys
import re

sum = 0
enabled=True

regex_all = re.compile(r'(do\(\))|(don\'t\(\))|(mul\((\d+),(\d+)\))')

with open(sys.argv[1]) as f:
    for line in f:
        print(line)
        match = re.findall(regex_all, line)
        for m in match:
            print(m)
            if m[0] != '':
                enabled = True
            elif m[1] != '':
                enabled = False
            elif m[2] != '':
                if enabled:
                    sum += int(m[3]) * int(m[4])

print(sum)
            
