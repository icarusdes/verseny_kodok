import sys
from copy import deepcopy

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

subproblems = []

rows = []
cols = []
for line in lines:
    currentline = line.strip()
    if not currentline:
        subproblems.append((rows, cols))
        rows = []
        cols = []
        continue

    rows.append([c for c in currentline])
    for i in range(len(currentline)):
        if i >= len(cols):
            cols.append([])
        cols[i].append(currentline[i])
subproblems.append((rows, cols))

def solve_subproblem(rows, cols):
    return_list = []
    input_data = [(rows, 100), (cols, 1)]

    for data, multiplier in input_data:
        for i in range(len(data)):
            data_to_test = min(i + 1, len(data) - i - 1 )
            the_same = True
            for j in range(data_to_test):
                if data[i - j] != data[i + 1 + j]:
                    the_same = False
                    break
            if the_same and data_to_test > 0:
                return_list.append((i+1) * multiplier)
    return return_list

sum_score = 0
for problem in subproblems:
    rows, cols = problem
    original_solutions = solve_subproblem(rows=rows, cols=cols)

    new_solutions = []
    new_solutions_found = False
    for i in range(len(rows)):
        for j in range(len(cols)):
            copy_rows = deepcopy(rows)
            copy_cols = deepcopy(cols)
            current = rows[i][j]
            if current == "#":
                copy_rows[i][j] = "."
                copy_cols[j][i] = "."
            elif current == ".":
                copy_rows[i][j] = "#"
                copy_cols[j][i] = "#"
            solutions = solve_subproblem(rows=copy_rows, cols=copy_cols)
            new_solutions.extend(solutions)

    new_sol = set(new_solutions) - set(original_solutions)
    # print(f"Original solution {set(original_solutions)}") 
    # print(f"New solution: {set(new_solutions)}")
    # print(f"Original solution: {new_sol}")
    sum_score += sum(new_sol)
    # print()

print(sum_score)
