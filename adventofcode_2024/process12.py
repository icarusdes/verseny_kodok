import sys
import re
import numpy as np

# Button A: X+94, Y+34
# Button B: X+22, Y+67
# Prize: X=8400, Y=5400

def calculate_one_case(case):
    first_line, second_line, prize = case.split('\n')
    dx_a, dy_a = map(int, re.search(r'X\+(\d+), Y\+(\d+)', first_line).groups())
    dx_b, dy_b = map(int, re.search(r'X\+(\d+), Y\+(\d+)', second_line).groups())
    goal_x, goal_y = map(int, re.search(r'X=(\d+), Y=(\d+)', prize).groups())

    print(f"dx_a: {dx_a}, dy_a: {dy_a}")
    print(f"dx_b: {dx_b}, dy_b: {dy_b}")
    print(f"goal_x: {goal_x}, goal_y: {goal_y}")

    min_tokens = None

    for i in range(100):
        for j in range(100):
            if i * dx_a + j * dx_b == goal_x and i * dy_a + j * dy_b == goal_y:
                if min_tokens is None or i*3 + j < min_tokens:
                    min_tokens = i*3 + j
    return min_tokens

def calculate_one_case_v2(case):
    first_line, second_line, prize = case.split('\n')
    dx_a, dy_a = map(int, re.search(r'X\+(\d+), Y\+(\d+)', first_line).groups())
    dx_b, dy_b = map(int, re.search(r'X\+(\d+), Y\+(\d+)', second_line).groups())
    goal_x, goal_y = map(int, re.search(r'X=(\d+), Y=(\d+)', prize).groups())

    print(f"dx_a: {dx_a}, dy_a: {dy_a}")
    print(f"dx_b: {dx_b}, dy_b: {dy_b}")
    goal_x += 10000000000000
    goal_y += 10000000000000
    print(f"goal_x: {goal_x}, goal_y: {goal_y}")

    results = np.linalg.solve([[dx_a, dx_b], [dy_a, dy_b]], [goal_x, goal_y])
    a, b = [int(round(x)) for x in results]
    if a * dx_a + b * dx_b == goal_x and a * dy_a + b * dy_b == goal_y:
        print(f"Results: {results}")
        print(f"a: {a}, b: {b}")
        return a*3 + b
    return None

sum_tokens = 0

with open(sys.argv[1]) as f:
    cases = f.read().split('\n\n')
    for case in cases:        
        min_tokens = calculate_one_case_v2(case)
        print(f"Min tokens: {min_tokens}")
        print("----------------------")

        if min_tokens is not None:
            sum_tokens += min_tokens

print(f"Sum tokens: {sum_tokens}")