import sys

possible_solutions = []
def main():

    values = {}
    connections = {}

    with open(sys.argv[1]) as f:
        initial_values, instructions = f.read().split('\n\n')
        for line in initial_values.split('\n'):
            key, value = line.split(": ")
            values[key] = int(value)

        for line in instructions.split('\n'):
            if line == "":
                continue
            value_1, instruction, value_2, _, key = line.strip().split(" ")
            connections[(value_1, value_2, instruction)] = key

    carry_before = None

    for i in range(45):
        sum_1_key_v1 = (f"x{i:02}", f"y{i:02}", "XOR")
        sum_1_key_v2 = (f"y{i:02}", f"x{i:02}", "XOR")

        carry_key_v1 = (f"x{i:02}", f"y{i:02}", "AND")
        carry_key_v2 = (f"y{i:02}", f"x{i:02}", "AND")

        if sum_1_key_v1 in connections:
            sum_1_name = connections[sum_1_key_v1]
        elif sum_1_key_v2 in connections:
            sum_1_name = connections[sum_1_key_v2]
        else:
            raise ValueError("No key found")

        if carry_key_v1 in connections:
            carry_1_name = connections[carry_key_v1]
        elif carry_key_v2 in connections:
            carry_1_name = connections[carry_key_v2]
        else:
            raise ValueError("No key found")
        
        carry_2_name = None
        if carry_before:
            carry_2_key_v1 = (carry_before, sum_1_name, "OR")
            carry_2_key_v2 = (sum_1_name, carry_before, "OR")
            if carry_2_key_v1 in connections:
                carry_2_name = connections[carry_2_key_v1]
            elif carry_2_key_v2 in connections:
                carry_2_name = connections[carry_2_key_v2]
            else:
                raise ValueError("No key found")

        print(sum_1_name)
        

if __name__ == "__main__":
    main()
