import sys
import functools

rules = []
lines = []
rules_finished = False
sum = 0
sum2 = 0

not_ordered = []

with open(sys.argv[1]) as f:
    lines = f.readlines()

#find the empty line and split into rules and page lists

for i in range(0, len(lines)):
    if not rules_finished:       
        if lines[i].strip() == "":
            rules_finished = True
            rules = [(int(rule[0]), int(rule[1])) for rule in rules]
            print(rules)
        else:
            rules.append(lines[i].strip().split("|"))
    else:
        pages = lines[i].strip().split(",")
        pages = [int(page) for page in pages]
        ordered = True
        for i in range(0, len(pages)-1):
            for j in range(i+1, len(pages)):
                if rules.count((pages[i], pages[j])) == 0:
                    ordered = False
                    break
        if ordered:
            print(pages)
            sum += pages[len(pages) // 2]
        else:
            not_ordered.append(pages)
print(sum)

def make_comparator():
    def compare(x, y):
        if rules.count((x, y)) == 1:
            return -1
        elif rules.count((y, x)) == 1:
            return 1
        else:
            return 0
    return compare

for pages in not_ordered:
    sorted_pages = sorted(pages, key= functools.cmp_to_key(make_comparator()))
    sum2 += sorted_pages[len(sorted_pages) // 2]

print(sum2)