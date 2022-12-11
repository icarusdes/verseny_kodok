import sys
import re

input_file = open(sys.argv[1], 'r')

class monkey:
    def __init__(self, items, operation, test, iftrue, iffalse) -> None:
        self.items = items
        self.operation = operation
        self.test = test
        self.iftrue = iftrue
        self.iffalse = iffalse

monkeys = []
smallest_common_multiple = 1

for __monkey in input_file.read().split("\n\n"):
    lines = __monkey.split("\n")
    # monkey_number = int(re.search("Monkey (\d+):", lines[0])[1])
    monkey_items    = [int(item) for item in re.search("Starting items: (.*)", lines[1])[1].split(", ")]
    operation       = re.search("Operation: new = old (.*)", lines[2])[1].split()
    test            = int(re.search("Test: divisible by (\d+)", lines[3])[1])
    iftrue          = int(re.search("If true: throw to monkey (\d+)", lines[4])[1])
    iffalse         = int(re.search("If false: throw to monkey (\d+)", lines[5])[1])

    smallest_common_multiple *= test
    monkeys.append(monkey(monkey_items, operation, test, iftrue, iffalse))

inspections = [0 for _ in range(len(monkeys))]
for round in range(10000):
    for i in range(len(monkeys)):
        current_monkey = monkeys[i]
        while len(current_monkey.items):
            item = current_monkey.items.pop()
            inspections[i] += 1
            match current_monkey.operation:
                case ['*', "old"]: 
                    new_value = item * item
                case ['*', op1]: 
                    new_value = item * int(op1)
                case ['+', "old"]:
                    new_value = item + item
                case ['+', op1]:
                    new_value = item + int(op1)
            new_value %= smallest_common_multiple
            if new_value % current_monkey.test == 0:
                monkeys[current_monkey.iftrue].items.append(new_value)
            else:
                monkeys[current_monkey.iffalse].items.append(new_value)

inspections.sort() 
print(inspections[-1] * inspections[-2])