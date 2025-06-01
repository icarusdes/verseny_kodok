import sys
import re

# input looks like 
# Register A: 729
# Register B: 0
# Register C: 0

# Program: 0,1,5,4,3,0

reg_a = 0
reg_b = 0
reg_c = 0

program = []

with open(sys.argv[1]) as f:
    for line in f.readlines():
        if match := re.match(r"Register A: (\d+)", line):
            reg_a = int(match.group(1))
        if match := re.match(r"Register B: (\d+)", line):
            reg_b = int(match.group(1))
        if match := re.match(r"Register C: (\d+)", line):
            reg_c = int(match.group(1))
        if match := re.match(r"Program: (.+)", line):
            program = list(map(int, match.group(1).split(",")))

instruction_pointer = 0

def get_operand(operand, is_literal):
    if is_literal:
        return operand
    
    if operand <= 3:
        pass # they are the values themselfs
    elif operand == 4:
        operand = reg_a
    elif operand == 5:
        operand = reg_b
    elif operand == 6:
        operand = reg_c
    else:
        raise ValueError(f"Invalid operand {operand}")
    return operand

while instruction_pointer < len(program):
    current_instruction = program[instruction_pointer]
    operand = program[instruction_pointer + 1]

    if current_instruction == 0:
        # adv instruction - division
        # numerator is in reg_a, denominator is the param
        reg_a = int(reg_a / (2** get_operand(operand, False)))
    elif current_instruction == 1:
        # bxl - bitwise xor
        reg_b = reg_b ^ get_operand(operand, True)
    elif current_instruction == 2:
        # bst / combo operand modulo 8
        reg_b = get_operand(operand, False) % 8
    elif current_instruction == 3:
        # jnz - jump if not zero
        if reg_a != 0:
            instruction_pointer = get_operand(operand, True)
            continue
    elif current_instruction == 4:
        # bxc - bitwise xor between reg_b and reg_c
        reg_b = reg_b ^ reg_c
    elif current_instruction == 5:
        # out - output
        print(get_operand(operand, False) % 8, end=',')
    elif current_instruction == 6:
        # bdv instruction - division
        # numerator is in reg_a, denominator is the param
        reg_b = int(reg_a / (2** get_operand(operand, False)))
    elif current_instruction == 7:
        # cdv instruction - division
        # numerator is in reg_a, denominator is the param
        reg_c = int(reg_a / (2** get_operand(operand, False)))
    else:
        raise ValueError(f"Invalid instruction {current_instruction}")

    instruction_pointer += 2

print()