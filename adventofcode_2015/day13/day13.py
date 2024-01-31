import argparse
import itertools
import unittest
import re

"""
Alice would gain 54 happiness units by sitting next to Bob.
Alice would lose 79 happiness units by sitting next to Carol.
Alice would lose 2 happiness units by sitting next to David.
Bob would gain 83 happiness units by sitting next to Alice.
Bob would lose 7 happiness units by sitting next to Carol.
Bob would lose 63 happiness units by sitting next to David.
Carol would lose 62 happiness units by sitting next to Alice.
Carol would gain 60 happiness units by sitting next to Bob.
Carol would gain 55 happiness units by sitting next to David.
David would gain 46 happiness units by sitting next to Alice.
David would lose 7 happiness units by sitting next to Bob.
David would gain 41 happiness units by sitting next to Carol.
"""

def parse_row(line: str):
    match = re.match(r"(\w+) would (gain|lose) (\d+) happiness units by sitting next to (\w+).", line)
    if match:
        if match.group(2) == "gain":
            return (match.group(1), match.group(4), int(match.group(3)))
        else:
            return (match.group(1), match.group(4), -int(match.group(3)))
    else:
        raise ValueError(f"Could not parse row: {line}")


class TestParse(unittest.TestCase):

    def test_successful_parse(self):
        self.assertEqual(parse_row("Alice would gain 54 happiness units by sitting next to Bob."), ("Alice", "Bob", 54))
        self.assertEqual(parse_row("Alice would lose 79 happiness units by sitting next to Carol."), ("Alice", "Carol", -79))

    def test_unsuccesful_parse(self):
        with self.assertRaises(ValueError):
            parse_row("Alice would 54 happiness units by sitting next Bob")

def solve_part1(input: dict[tuple[str, str], int]) -> int:
    people = set()
    values = []
    for key in input.keys():
        people.add(key[0])
    for perm in itertools.permutations(people):
        current_value = 0
        for i in range(len(perm)):
            current_value += input[(perm[i], perm[(i+1) % len(perm)])]
            current_value += input[(perm[(i+1) % len(perm)], perm[i])]
        values.append(current_value)
    return max(values)

def solve_part2(input: dict[tuple[str, str], int]) -> int:
    people = set()
    for key in input.keys():
        people.add(key[0])
    
    for person in people:
        input[(person, "Me")] = 0
        input[("Me", person)] = 0
    return solve_part1(input)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", help="input file")
    parser.add_argument("--part", help="part 1 or 2", default=1, type=int)
    args = parser.parse_args()

    input_file = open(args.input, "r")
    parsed_lines = [parse_row(line) for line in input_file.readlines()]
    seating = {}
    for row in parsed_lines:
        seating[(row[0], row[1])] = row[2]
    if args.part == 1:
        print(solve_part1(seating))
    else:
        print(solve_part2(seating))

if __name__ == "__main__":
    main()