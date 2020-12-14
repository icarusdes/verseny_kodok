import sys

input_file = open(sys.argv[1], "r")
part = int(sys.argv[2])

memory = {}

for line in input_file.read().splitlines():
    address, value = line.split(" = ")
    if address == "mask": 
        mask_bits_1 = 0
        mask_bits_0 = 2**36 - 1
        floating_bits = []
        for i, v in enumerate (value[::-1]):
            if part == 1: 
                if v == "1": 
                    mask_bits_1 = mask_bits_1 | (1 << i)
                elif v == "0":                 
                    mask_bits_0 = mask_bits_0 ^ (1 << i)
                else: 
                    pass                
            else: # part == 2
                if v == "1": 
                    mask_bits_1 = mask_bits_1 | (1 << i)
                elif v == "X":
                    mask_bits_0 = mask_bits_0 ^ (1 << i) #to zero out the floating bits
                    floating_bits.append(i)
                else: 
                    pass
    else: # address looks like mem[x]
        address = int(address[4:-1])
        value = int(value)
        if part == 1:             
            value = (value & mask_bits_0) | mask_bits_1            
            memory[address] = value
        else: # part == 2
            address = (address & mask_bits_0) | mask_bits_1
            for i in range(2 ** len(floating_bits)):
                temp_address = address
                for index, v in enumerate(floating_bits): 
                    if i & (1 << index): 
                        temp_address = temp_address | (1 << v)
                memory[temp_address] = value


print (sum([value for key, value in memory.items()]))