import sys

def part1(left_list, right_list):
    left_list.sort()
    right_list.sort()
    return sum([abs(a - b) for a, b in zip(left_list, right_list)])

def part2(left_list, right_list):
    sum = 0
    for i in set(left_list):
        sum += i * right_list.count(i)
    return sum

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 day1.py <input_file>")
        sys.exit(1)

    left_list = []
    right_list = []

    with open(sys.argv[1]) as f:
        for line in f.readlines():
            a, b = map(int, line.strip().split())
            left_list.append(a)
            right_list.append(b)

    print(part1(left_list, right_list))
    print(part2(left_list, right_list))
