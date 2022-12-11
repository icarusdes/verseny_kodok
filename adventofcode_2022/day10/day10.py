import sys

input_file = open(sys.argv[1], 'r')

reg_x = 1
reg_values = []

for line in input_file.read().splitlines():
    reg_values.append(reg_x)
    match line.split():
        case ["noop"]:
            pass
        case ["addx", value]:
            reg_values.append(reg_x)
            reg_x += int(value)

signal_strength = [reg_values[cycle-1] * cycle for cycle in [20 + 40 * i for i in range(6)]]
print(sum(signal_strength))

for i in range(0, 240):
    current_x = i % 40
    if current_x == 0:
        print()
    if reg_values[i] - 1 <= current_x and reg_values[i] + 1 >= current_x:
        print('#', end="")
    else:
        print('.', end="")
print()