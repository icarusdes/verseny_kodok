import sys
import itertools

def values_to_numbers(values):
    x_bits = [key for key in values.keys() if key.startswith("x")]
    x_bits.sort()
    y_bits = [key for key in values.keys() if key.startswith("y")]
    y_bits.sort()
    z_bits = [key for key in values.keys() if key.startswith("z")]
    z_bits.sort()
    x = 0
    for i, key in enumerate(x_bits):
        x += values[key] * (2 ** i)
    y = 0
    for i, key in enumerate(y_bits):
        y += values[key] * (2 ** i)
    z = 0
    for i, key in enumerate(z_bits):
        z += values[key] * (2 ** i)
    return x, y, z

def numbers_to_values(x, y):
    values = {}
    x_bits = [int(i) for i in bin(x)[2:]]
    y_bits = [int(i) for i in bin(y)[2:]]
    for i, bit in enumerate(x_bits):
        values[f"x{i}"] = bit
    for i, bit in enumerate(y_bits):
        values[f"y{i}"] = bit
    return values

def change_connections(connections, comb):
    new_connections = connections[:]
    for i in range(len(comb) // 2):
        value_1, value_2, instruction, key = new_connections[comb[i]]
        value_3, value_4, instruction_2, key_2 = new_connections[comb[i+1]]
        new_connections[comb[i]] = (value_1, value_2, instruction, key_2)
        new_connections[comb[i+1]] = (value_3, value_4, instruction_2, key)
    return new_connections

def run_program(connections, values):
    while connections:
        print(connections)
        print()
        new_connections = []
        for connection in connections:
            value_1, value_2, instruction, key = connection
            if value_1 not in values or value_2 not in values:
                new_connections.append(connection)
                continue
            if instruction == "AND":
                values[key] = values[value_1] & values[value_2]
            elif instruction == "OR":
                values[key] = values[value_1] | values[value_2]
            elif instruction == "XOR":
                values[key] = values[value_1] ^ values[value_2]
        if (connections == new_connections):
            return False
        connections = new_connections
    x, y, z = values_to_numbers(values)
    if x + y == z:
        # one possible solution
        return True
    return False

possible_solutions = []
def main():

    values = {}
    connections = []

    with open(sys.argv[1]) as f:
        initial_values, instructions = f.read().split('\n\n')
        for line in initial_values.split('\n'):
            print(line)
            key, value = line.split(": ")
            values[key] = int(value)

        for line in instructions.split('\n'):
            if line == "":
                continue
            value_1, instruction, value_2, _, key = line.strip().split(" ")
            connections.append((value_1, value_2, instruction, key))

    i = 0
    for i in range(45):
        new_values = numbers_to_values(2**i, 2**i)
        values_copy = values.copy()
        for key, value in new_values.items():
            values_copy[key] = value
        connections_copy = connections.copy()
        if run_program(connections_copy, values_copy):
            print(values_copy)
            possible_solutions.append(values_copy)
            break

    # determine the bits of the input values


if __name__ == "__main__":
    main()
