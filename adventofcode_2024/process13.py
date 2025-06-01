import sys
import re
import numpy as np

robots = []

# testsize = (11, 7)
testsize = (101, 103)
number_of_iterations = 100

def calculate_one_case(case, size, iterations):

    # p=0,4 v=3,-3
    # p=6,3 v=-1,-3
    px, py, vx, vy = map(int, re.search(r'p=(.*),(.*) v=(.*),(.*)', case).groups())
    return (px + vx * iterations) % size[0], (py + vy * iterations) % size[1]



with open(sys.argv[1]) as f:
    for line in f.readlines():
        x, y = calculate_one_case(line, testsize, number_of_iterations)
        robots.append((x, y))

for y in range(testsize[1]):
    for x in range(testsize[0]):
        if (x, y) in robots:
            print("#", end="")
        else:
            print(".", end="")
    print()


q1 = 0
q2 = 0
q3 = 0
q4 = 0

for x, y in robots:
    print(f"Robot at {x}, {y}")
    if x < testsize[0] // 2 and y < testsize[1] // 2:
        print("Q1")
        q1 += 1
    elif x > testsize[0] // 2 and y < testsize[1] // 2:
        print("Q2")
        q2 += 1
    elif x < testsize[0] // 2 and y > testsize[1] // 2:
        print("Q3")
        q3 += 1
    elif x > testsize[0] // 2 and y > testsize[1] // 2:
        print("Q4")
        q4 += 1

print(q1)
print(q2)
print(q3)
print(q4)
print(q1*q2*q3*q4)