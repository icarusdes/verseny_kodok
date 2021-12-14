import sys
from collections import Counter

input_file = open(sys.argv[1])
lines = input_file.read().splitlines()

template = lines[0]
rules = {}
iterations = 40

for i in range(2, len(lines)): 
    _from, _add = lines[i].split(" -> ")
    rules[_from] = _add

print (rules)
print (template) 

for current_it in range(iterations):
    print(current_it)
    new_template = []
    for i in range(len(template) - 1): 
        new_template.append(template[i])
        new_template.append( rules[template[i:i+2]])
    new_template.append(template[-1])
    template = "".join(new_template)
    # print (template) 

c = Counter(template)
ordered_counted_list = c.most_common() 
most_common = ordered_counted_list[0]
least_common = ordered_counted_list[-1]

print(f"What do you get if you take the quantity of the most common element and subtract the quantity of the least common element? The answer is {most_common[1] - least_common[1]}")