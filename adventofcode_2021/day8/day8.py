import sys

input_file = open(sys.argv[1], "r")
lines = input_file.read().splitlines() 

unique_count = 0
# corresponding numbers are
#         1  7  4  8
unique = [2, 3, 4, 7]

def sort_string(s): 
    l = list(s)
    l.sort()
    return "".join(l)

def set_as_sorted_list(s): 
    l = list(s)
    l.sort()
    return l

def decode_signals(signals): 
    sorted_by_digit_num = {}
    for signal in signals:
        sorted = list(signal)
        sorted.sort() 
        segment_num = len(sorted)
        if segment_num in sorted_by_digit_num:
            sorted_by_digit_num[segment_num].append(set(sorted))
        else: 
            sorted_by_digit_num[segment_num] = [set(sorted)]

    _a = sorted_by_digit_num[3][0] - sorted_by_digit_num[2][0]
    _cf = sorted_by_digit_num[3][0] & sorted_by_digit_num[2][0]
    _bd = sorted_by_digit_num[4][0] - sorted_by_digit_num[2][0]
    as_list = list(_bd) 
    found_in_every = True
    for digit in sorted_by_digit_num[6]: 
        if as_list[0] not in digit: 
            found_in_every = False
    if found_in_every: 
        _b = set(as_list[0]) 
        _d = set(as_list[1])
    else: 
        _b = set(as_list[1])
        _d = set(as_list[0])

    as_list = list(_cf) 
    found_in_every = True
    for digit in sorted_by_digit_num[6]: 
        if as_list[0] not in digit: 
            found_in_every = False
    if found_in_every: 
        _f = set(as_list[0]) 
        _c = set(as_list[1])
    else: 
        _f = set(as_list[1])
        _c = set(as_list[0])

    _eg = sorted_by_digit_num[7][0] - _a - _b - _c - _d - _f

    as_list = list(_eg) 
    found_in_every = True
    for digit in sorted_by_digit_num[6]: 
        if as_list[0] not in digit: 
            found_in_every = False
    if found_in_every: 
        _g = set(as_list[0]) 
        _e = set(as_list[1])
    else: 
        _g = set(as_list[1])
        _e = set(as_list[0])

    # print(f"a is {_a}")
    # print(f"b is {_b}")
    # print(f"c is {_c}")
    # print(f"d is {_d}")
    # print(f"e is {_e}")
    # print(f"f is {_f}")
    # print(f"g is {_g}")

    digits = {
        "".join(set_as_sorted_list( _a | _b | _c | _e | _f | _g)) : 0, 
        "".join(set_as_sorted_list( _c | _f)) : 1,
        "".join(set_as_sorted_list( _a | _c | _d | _e | _g)) : 2, 
        "".join(set_as_sorted_list( _a | _c | _d | _f | _g)) : 3, 
        "".join(set_as_sorted_list( _b | _c | _d | _f)) : 4, 
        "".join(set_as_sorted_list( _a | _b | _d | _f | _g)) : 5, 
        "".join(set_as_sorted_list( _a | _b | _d | _e | _f | _g)) : 6, 
        "".join(set_as_sorted_list( _a | _c | _f)) : 7, 
        "".join(set_as_sorted_list( _a | _b | _c | _d | _e | _f | _g)) : 8, 
        "".join(set_as_sorted_list( _a | _b | _c | _d | _f | _g)) : 9, 
    }
    return digits

numbers = []
for line in lines: 
    signals, output = line.split(" | ")
    output_digits = output.split()

    digits = decode_signals(signals.split())
    current_num = 0
    for digit in output_digits: 
        current_num = current_num * 10 + digits[sort_string(digit)]
        if len(digit) in unique: 
            unique_count += 1 
    print(current_num)
    numbers.append(current_num)

print(f"Unique count is {unique_count}.")
print(f"Sum is {sum(numbers)}.")
