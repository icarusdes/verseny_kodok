import sys

def find_first_invalid(numbers, preamble):
    current_window = numbers[0:preamble]
    rest = numbers[preamble:]
    for num in rest: 
        found = False
        for wi in current_window: 
            if num - wi in current_window:
                found = True
                break
        if found: 
            current_window.pop(0)
            current_window.append(num)
            continue
        return num

def find_invalid_sequence(numbers, expected_sum): 
    for i in range(len(numbers)):        
        if numbers[i] > expected_sum: 
            continue
        for j in range(1, len(numbers)-i):
            s = sum(numbers[i:i+j])
            if s == expected_sum:
                print(numbers[i:i+j])
                return min(numbers[i:i+j]) + max(numbers[i:i+j])
            if s > expected_sum: 
                break


input_file = open(sys.argv[1])
numbers =  [int(line) for line in input_file.read().splitlines()]
sequence_length = int(sys.argv[2])

first_invalid = find_first_invalid(numbers, sequence_length)
print(first_invalid)
print(find_invalid_sequence(numbers, first_invalid))