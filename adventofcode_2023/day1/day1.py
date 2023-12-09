import sys

input_file = open(sys.argv[1], 'r')
lines = input_file.read().splitlines()
# numbers = []
sum = 0
string_to_num = {
    'one': '1',
    'two': '2',
    'three': '3',
    'four' : '4',
    'five' : '5',
    'six' : '6',
    'seven' : '7',
    'eight' : '8',
    'nine' : '9'
}

for line in lines:
    print (line)
    i = 0
    while i < len(line):
        one = line[i:i+3]
        four = line[i:i+4]
        three = line[i:i+5]
        if one in string_to_num:
            line = line.replace(one, string_to_num[one], 1)
            break
        if four in string_to_num:
            line = line.replace(four, string_to_num[four], 1)
            break
        if three in string_to_num:
            line = line.replace(three, string_to_num[three], 1)
            break
        i += 1
    i = len(line) - 3
    while i > 0:
        one = line[i:i+3]
        four = line[i:i+4]
        three = line[i:i+5]
        if one in string_to_num:
            line = line[:i] + string_to_num[one] + line[i+3:]
            break
        if four in string_to_num:
            line = line[:i] + string_to_num[four] + line[i+4:]
            break
        if three in string_to_num:
            line = line[:i] + string_to_num[three] + line[i+5:]
            break
        i -= 1
    print(line)
    l = []
    for c in line:
        # decides if c is a digit and if it, it adds to a list
        if c.isdigit():
            l.append(int(c))
    print(l[0] * 10 + l[-1])
    sum += l[0] * 10 + l[-1]

print(sum) 