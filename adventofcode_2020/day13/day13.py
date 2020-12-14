import sys
from functools import reduce


input_file = open(sys.argv[1], "r")
part = int(sys.argv[2])
lines = input_file.read().splitlines() 

if part == 1: 
    current_time = int(lines[0])
    buses = [int(num) for num in filter(lambda x: x != "x", lines[1].split(","))]
    min_waitings = [bus - (current_time % bus) for bus in buses]
    min_wait = min(min_waitings)
    bus_num = buses[min_waitings.index(min_wait)]
    print(min_wait * bus_num)
else: 

    def chinese_remainder(n, a):
        sum = 0
        prod = reduce(lambda a, b: a*b, n)
        for n_i, a_i in zip(n, a):
            p = prod // n_i
            sum += a_i * mul_inv(p, n_i) * p
        return sum % prod

    def mul_inv(a, b):
        b0 = b
        x0, x1 = 0, 1
        if b == 1: return 1
        while a > 1:
            q = a // b
            a, b = b, a%b
            x0, x1 = x1 - q * x0, x0
        if x1 < 0: x1 += b0
        return x1

    def filter_to_zero(value):
        if value == 'x':
            return 0
        return int(value)

    buses = [filter_to_zero(num) for num in lines[1].split(",")]
    filtered_buses = [b for b in filter ( lambda x: x[1] != 0, enumerate(buses))]

    n = [b[1] for b in filtered_buses]
    r = [-b[0] for b in filtered_buses]

    print(chinese_remainder(n, r))
