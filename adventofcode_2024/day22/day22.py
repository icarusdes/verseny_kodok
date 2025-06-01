import sys
import math

def calculate_next(value):
    value = ((value * 64) ^ value) % 16777216
    value = (math.floor(value / 32) ^ value) % 16777216
    value = ((value * 2048) ^ value) % 16777216
    return value

def calculate_nth(value, limit = 2000):
    prices = [value % 10]
    for _ in range(limit):
        value = calculate_next(value)
        prices.append(value % 10)
    return value, prices

changes_list = []

if __name__ == '__main__':
    with open(sys.argv[1]) as f:
        sum = 0
        for line in f.readlines():
            limit = 2000
            res, prices = calculate_nth(int(line.strip()), limit)
            changes = [None]
            for i in range(1, limit):
                change = prices[i] - prices[i - 1]
                changes.append(change)
            # print(changes)
            # print(prices)

            change_dict = {}
            for i in range(1, limit-4):
                key = tuple(changes[i:i+4])
                if key in change_dict:
                    pass
                    # nothing to do, since the first occurrence of the sequence will be matched
                else:
                    change_dict[key] = prices[i+3]
            # print(change_dict)
            changes_list.append(change_dict)
            sum += res
        print(sum)
        print(len(changes_list))

    highest_sum = 0
    highest_sum_key = None

    for i in range(-9, 10):
        for j in range(-9, 10):
            if (i + j) > 9 or (9 + i + j) < 0:
                continue
            for k in range(-9, 10):
                if (i + j + k) > 9 or (9 + i + j + k) < 0:
                    continue
                for l in range(-9, 10):
                    if (i + j + k + l) > 9 or (9 + i + j + k + l) < 0:
                        continue

                    key = (i, j, k, l)
                    sum = 0
                    for change_dict in changes_list:
                        if key in change_dict:
                            sum += change_dict[key]
                    if sum > highest_sum:
                        highest_sum = sum
                        highest_sum_key = key

    test_key = (-2, 1, -1, 3)

    print(highest_sum)
    print(highest_sum_key)
