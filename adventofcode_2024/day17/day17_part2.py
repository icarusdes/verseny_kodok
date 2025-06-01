
reversed_program = [
    2,4,
    1,5,
    7,5,
    1,6,
    0,3,
    4,6,
    5,5,
    3,0
][::-1]

octet_index = 0
possible_values = [0] # it has to be zero, for the program to end

while octet_index < len(reversed_program):
    new_possible_values = []
    for value in possible_values:
        for i in range(8):
            reg_a = value * 8 + i           # preparation
            reg_b = reg_a % 8               # 2,4
            reg_b = reg_b ^ 5               # 1,5
            reg_c = int(reg_a / (2**reg_b)) # 7,5
            reg_b = reg_b ^ 6               # 1,6
            reg_b = reg_b ^ reg_c           # 4,6
            out = reg_b % 8                 # 5,5
            pass                            # 3,0 - if reg_a != 0 jump to 0
            if out == reversed_program[octet_index]:
                new_possible_values.append(reg_a)
    octet_index += 1
    possible_values = new_possible_values

print(min(possible_values))
