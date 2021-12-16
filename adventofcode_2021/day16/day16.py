import sys
import functools
import operator

try: 
    input_file = open(sys.argv[1], "r")
    line = input_file.readline()
except FileNotFoundError: 
    # using the second argument, as it is.
    line = sys.argv[2]

def hex_to_binary(number_string): 
    return bin(int(number_string, 16))[2:].zfill(4)

input_as_binary = "".join(list(map(hex_to_binary, line)))
versions_sum = 0

def process_package(input_text): 
    version = int(input_text[:3], 2)
    global versions_sum 
    versions_sum += version
    type_id = int(input_text[3:6], 2)
    bits_processed = 6    
    if type_id == 4: 
        #this is a literal value
        num_string = ""
        while True: 
            num_string += input_text[bits_processed+1:bits_processed+5]
            bits_processed += 5
            if input_text[bits_processed-5] == '0': 
                #this was the last number
                break
        return bits_processed, int(num_string, 2)
    else: 
        lenght_type_id = input_text[6]
        bits_processed += 1
        return_values = []
        if lenght_type_id == "0": 
            #next 15 bits contains the total length of the subpockets contained by this packet 
            remaining_length = int(input_text[bits_processed:bits_processed +15], 2)
            bits_processed += 15

            while remaining_length != 0:             
                processed_lenght, value = process_package(input_text[bits_processed: bits_processed + remaining_length])
                return_values.append(value)
                bits_processed += processed_lenght
                remaining_length -= processed_lenght
        else: 
            #next 11 bits contain the number of sub-packets immediately contained by this packet
            remaining_packets = int(input_text[bits_processed:bits_processed +11], 2)
            bits_processed += 11            
            while remaining_packets != 0: 
                processed_lenght, value = process_package(input_text[bits_processed: ])
                return_values.append(value)
                bits_processed += processed_lenght
                remaining_packets -= 1
        if type_id == 0: 
            value = sum(return_values)
        elif type_id == 1: 
            value = functools.reduce(operator.mul, return_values, 1)
        elif type_id == 2: 
            value = min(return_values)
        elif type_id == 3: 
            value = max(return_values)
        elif type_id == 5: 
            value = 1 if return_values[0] > return_values[1] else 0
        elif type_id == 6: 
            value = 1 if return_values[0] < return_values[1] else 0
        elif type_id == 7: 
            value = 1 if return_values[0] == return_values[1] else 0
        else: 
            print("ERROR!")
        return bits_processed, value

b, v = process_package(input_as_binary)

print(f"Version sum is: {versions_sum}")
print(f"Return value is: {v}")