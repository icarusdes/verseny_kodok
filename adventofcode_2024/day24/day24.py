import sys
import re

def main():

    values = {}
    connections = []
    part1 = False

    with open(sys.argv[1]) as f:
        initial_values, instructions = f.read().split('\n\n')
        for line in initial_values.split('\n'):
            print(line)
            key, value = line.split(": ")
            values[key] = int(value)

        for line in instructions.split('\n'):
            if line == "":
                continue
            value_1, instruction, value_2, arrow, key = line.strip().split(" ")
            connections.append((value_1, value_2, instruction, key))
    pass

    if part1:
        while connections:
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
            connections = new_connections

        z_keys = [key for key in values.keys() if key.startswith("z")]
        z_keys.sort()
        print(z_keys)

        res = 0
        for i, key in enumerate(z_keys):
            res += values[key] * (2 ** i)

        print(res)
    else:
        x_keys = [key for key in values.keys() if key.startswith("x")]
        y_keys = [key for key in values.keys() if key.startswith("y")]

        print(x_keys)
        print(y_keys)
        # determine the bits of the input values


if __name__ == "__main__":
    main()
